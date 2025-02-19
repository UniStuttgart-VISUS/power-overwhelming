// <copyright file="visa_instrument_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visa_instrument_impl.h"

#include <stdexcept>

#include "no_visa_error_msg.h"
#include "visa_library.h"
#include "zero_memory.h"


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create
 */
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl *
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create(
        _In_ const std::string& path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new) {
    std::lock_guard<decltype(_lock_instruments)> l(_lock_instruments);
    visa_instrument_impl *retval = nullptr;

    auto it = _instruments.find(path);
    if (it != _instruments.end()) {
        // Reuse existing instrument for same connection.
        retval = it->second;

        if (is_new != nullptr) {
            *is_new = false;
        }

        assert(retval->_counter > 0);

    } else {
        // If no existing scope was found or if the previous scope has been
        // deleted, create a new one.
        retval = new visa_instrument_impl();

        {
            auto status = visa_library::instance().viOpenDefaultRM(
                &retval->resource_manager);
            if (status < VI_SUCCESS) {
                delete retval;
                throw visa_exception(status, "The VISA default resource "
                    "manager could not be opened.");
            }
        }

        {
            auto status = visa_library::instance().viOpen(
                retval->resource_manager, path.c_str(), 0, timeout,
                &retval->session);
            if (status < VI_SUCCESS) {
                delete retval;
                throw visa_exception(status);
            }
        }

        // Check for VXI support as in rscore from R&S. This is mostly
        // interesting for how we can retrieve the status bytes from the
        // instrument.
        // Note to future self: This is copied from R&S and I have no idea
        // why certain interfaces support VXI and otherd do not, in particular
        // the "SOCKET" stuff. Therefore, this should not necessarily to be
        // considered correct.
        switch (retval->interface_type()) {
            case VI_INTF_GPIB:
            case VI_INTF_GPIB_VXI:
            case VI_INTF_USB:
                retval->vxi = true;
                break;

            case VI_INTF_TCPIP:
                retval->vxi = (retval->resource_class() != "SOCKET");
                break;

            default:
                retval->vxi = false;
                break;
        }

        retval->_path = path;

        _instruments[path] = retval;

        if (is_new != nullptr) {
            *is_new = true;
        }

        assert(retval->_counter == 0);
    } /* if (it != _instruments.end()) */

    ++retval->_counter;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create
 */
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl *
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create(
        _In_z_ const wchar_t *path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to a VISA instrument must not "
            "be null.");
    }

    return create(PWROWG_NAMESPACE::convert_string<char>(path), timeout,
        is_new);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create
 */
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl *
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::create(
        _In_z_ const char *path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to a VISA instrument must not "
            "be null.");
    }

    return create(std::string(path), timeout, is_new);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::foreach
 */
std::size_t PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::foreach(
        _In_ const std::function<bool(visa_instrument_impl *)>& callback) {
    if (!callback) {
        throw std::invalid_argument("The enumeration callback for VISA "
            "instruments must not be nullptr.");
    }

    std::size_t retval = 0;

    std::lock_guard<decltype(_lock_instruments)> l(_lock_instruments);
    for (auto& i : _instruments) {
        ++retval;
        if (!callback(i.second)) {
            break;
        }
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::~visa_instrument_impl
 */
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::~visa_instrument_impl(
        void) {
    visa_library::instance().viClose(this->session);
    visa_library::instance().viClose(this->resource_manager);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::check_system_error
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::check_system_error(
        void) const {
    if (this->enable_system_checks) {
        this->throw_on_system_error();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::disable_event
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::disable_event(
        _In_ const ViEventType event_type, _In_ const ViUInt16 mechanism) {
    visa_exception::throw_on_error(visa_library::instance().viDisableEvent(
        this->session, event_type, mechanism));
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::enable_event
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::enable_event(
        _In_  const ViEventType event_type,
        _In_ const ViUInt16 mechanism,
        _In_ const ViEventFilter context) {
    // Cf. https://www.ni.com/docs/de-DE/bundle/ni-visa/page/ni-visa/vienableevent.html
    visa_exception::throw_on_error(visa_library::instance().viEnableEvent(
        this->session, event_type, mechanism, context));
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::flush_data
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::flush_data(void) {
    std::array<std::uint8_t, 1024> buffer;
    auto have_more = true;
    ViUInt32 requested = 8;
    ViUInt32 read = 0;

    while (have_more) {
        auto status = detail::visa_library::instance().viRead(
            this->session,
            buffer.data(),
            requested,
            &read);

        auto have_more = (status == VI_SUCCESS_MAX_CNT);

        if (!have_more) {
            visa_exception::throw_on_error(status);
            // I honestly do not know why one would do that, but R&s are doing
            // it in their code and as it works more reliably then ours, I guess
            // it is beneficial somehow ...
            have_more = (buffer[read - 1] != '\n');
        }

        // We assume a small amount of data in the buffer left initially, but if
        // we did not read everything, request progressively more in subsequent
        // calls to speed up the process.
        requested = (std::min)(2 * requested,
            static_cast<ViUInt32>(buffer.size()));
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::identify
 */
std::string PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::identify(
        void) const {
    const auto cmd = "*IDN?\n";
    this->write_all(reinterpret_cast<const byte_type *>(cmd) , ::strlen(cmd));
    auto id = this->read_all();

    auto retval = id.as<char>();
    _Analysis_assume_(retval != nullptr);
    *::strchr(retval, '\n') = 0;

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::install_handler
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::install_handler(
        _In_ const ViEventType event_type,
        _In_ const ViHndlr handler,
        _In_ ViAddr context) {
    visa_exception::throw_on_error(visa_library::instance().viInstallHandler(
        this->session, event_type, handler, context));
    this->check_system_error();
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::interface_type
 */
std::uint16_t
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::interface_type(
        void) const {
    std::uint16_t retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viGetAttribute(this->session, VI_ATTR_INTF_TYPE, &retval));
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read
 */
std::size_t PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read(
        _Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const {
    assert(buffer != nullptr);
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viRead(this->session,
            buffer,
            static_cast<ViUInt32>(cnt),
            &retval));
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read_all
 */
PWROWG_NAMESPACE::blob
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read_all(
        _In_ const std::size_t buffer_size) const {
    static const std::size_t min_size = 1;

    blob retval((std::max)(buffer_size, min_size));
    ViUInt32 offset = 0;
    ViUInt32 read = 0;
    ViStatus status = VI_SUCCESS_MAX_CNT;

    while (status == VI_SUCCESS_MAX_CNT) {
        status = detail::visa_library::instance().viRead(
            this->session,
            retval.as<ViByte>(offset),
            static_cast<ViUInt32>(retval.size() - offset),
            &read);
        offset += read;

        if (status == VI_SUCCESS_MAX_CNT) {
            // Increase the buffer size if the message was not completely read.
            // The 50% increase is something used by many STL vector
            // implementations, so it is probably a reasonable heuristic.
            retval.grow(retval.size() + (std::max)(retval.size() / 2,
                min_size));
        } else {
            // Terminate in case of any error.
            visa_exception::throw_on_error(status);
        }
    };

    retval.truncate(offset);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read_binary
 */
PWROWG_NAMESPACE::blob
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::read_binary(
        void) const {
    blob retval(16);
    std::size_t size = 0;

    this->read(retval.begin(), 2);
    if (*retval.as<char>(0) != '#') {
        throw std::runtime_error("The instrument did not send the expected "
            "type of binary response.");
    }

    if (*retval.as<char>(1) == '(') {
        // This is the "variable length" mode where the data starts with
        // #(<number of bytes>). We need to read the input character by
        // character until we read the closing parenthesis.
        byte_type byte = 0;
        bool need_more = true;

        assert(size == 0);
        while (need_more) {
            this->read(&byte, 1);

            if ((byte >= '0') && (byte <= '9')) {
                size *= 10;
                size += byte - '0';

            } else if (byte == ')') {
                need_more = false;

            } else {
                throw std::runtime_error("The variable-length header contains "
                    "non-numeric characters.");
            }
        }

    } else {
        // This is the "normal length" more where the data starts with
        // #<digits><number of bytes>. In this mode, the second character
        // is the number of digits to follow (at most 9).
        *retval.as<char>(2) = 0;
        const auto digits = std::atoi(retval.as<char>(1));

        // If the number of digits is zero, we must do an unbounded read.
        if (digits == 0) {
            // TODO: check whether we need to remove a line break
            return this->read_all();
        }

        retval.reserve(digits + 1);
        this->read(retval.begin(), digits);

        *retval.as<char>(digits) = 0;
        size = std::atoi(retval.as<char>());
    }

    retval.resize(size);
    assert(retval.size() == size);

    while (size > 0) {
        size -= this->read(retval.end() - size, size);
    }

    // Read and discard all junk that might be in the buffer. If we do not
    // do this, the next query could be interrupted. This might also fail,
    // in which case we just ignore it.
    try {
        this->read_all();
    } catch (...) { }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::release
 */
std::size_t PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::release(
        void) {
    auto expected = this->_counter.load();

    while (!this->_counter.compare_exchange_weak(expected, expected - 1));

    if (expected == 1) {
        std::lock_guard<decltype(_lock_instruments)> l(_lock_instruments);
        _instruments.erase(this->_path);
        delete this;
    }

    // Note: Do not use counter at this point! Only local variables are still
    // alive after deleting the object!
    return (expected - 1);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::resource_class
 */
std::string
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::resource_class(
        void) const {
    ViChar retval[256];
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viGetAttribute(this->session, VI_ATTR_RSRC_CLASS, retval));
    retval[sizeof(retval) - 1] = 0;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::system_error
 */
int PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::system_error(
        _Out_ std::string& message) const {
    this->write(":SYST:ERR?\n");
    auto status = this->read_all();

    auto delimiter = std::find_if(status.begin(), status.end(),
        [](const byte_type b) { return b == ','; });

    if ((delimiter != nullptr) && (delimiter != status.end())) {
        *delimiter = '\0';

        // Skip the delimiter itself.
        ++delimiter;

        // Trim any leading spaces and quotes.
        for (; (delimiter != status.end()) && (std::isspace(*delimiter)
            || (*delimiter == '"')); ++delimiter);

        // Trim any trailing spaces and quotes.
        auto end = status.rbegin();
        for (; (end != status.rend()) && (std::isspace(*end)
            || (*end == '"')); --end);

        // Skip the delimiter itself.
        ++end;

        message = std::string(delimiter, end);

        return std::atoi(reinterpret_cast<char *>(status.data()));
    } else {
        throw std::runtime_error("The instrument responded unexpectedly.");
    }
}


/*
 * ...::detail::visa_instrument_impl::throw_on_system_error
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::throw_on_system_error(
        void) const {
    static const auto have_error = static_cast<ViUInt16>(
        visa_status_byte::error_queue_not_empty);

    // First of all, determine the instrument status to check whether there i
    // something in the queue to retrieve.
    ViUInt16 status;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viReadSTB(this->session, &status));

    if ((status & have_error) == 0) {
        // If the error queue is empty, do not retrieve the status.
        return;
    }

    std::string message;
    auto error = this->system_error(message);
    assert(error != 0);
    if (error == 0) {
        // If there is no error, which should never happen, bail out, too. We
        // check this condition although this code path should be unreachable in
        // order to prevent the infamous "The operation completed successfully"
        // exceptions. If the above assertion is violated, callers might want to
        // check whether they are concurrently clearing the error queue, which
        // would be a bug.
        return;
    }

    if (message.empty()) {
        // If we have no custom message, display the error code.
        message = std::to_string(error);
    }

    throw std::runtime_error(message);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::uninstall_handler
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::uninstall_handler(
        _In_ const ViEventType event_type,
        _In_ const ViHndlr handler,
        _In_ ViAddr context) {
    visa_exception::throw_on_error(visa_library::instance().viUninstallHandler(
        this->session, event_type, handler, context));
    this->check_system_error();
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write
 */
std::size_t PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    assert(buffer != nullptr);
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viWrite(this->session,
            buffer,
            static_cast<ViUInt32>(cnt),
            &retval));
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write(
        _In_z_ const char *str) const {
    assert(str != nullptr);
    auto len = ::strlen(str);

    if (this->auto_terminate() && (str[len - 1] != this->terminal_character)) {
        std::vector<byte_type> term(len + 1);
        ::memcpy(term.data(), str, len * sizeof(char));
        term[len++] = this->terminal_character;
        this->write_all(term.data(), len);

    } else {
        this->write_all(reinterpret_cast<const byte_type *>(str), len);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write_all
 */
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::write_all(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    ViUInt32 last = 0;
    ViUInt32 total = 0;

    while (total < cnt) {
        visa_exception::throw_on_error(detail::visa_library::instance()
            .viWrite(this->session,
                buffer + total,
                cnt - total,
                &last));
        total += last;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::_instruments
 */
std::map<std::string, PWROWG_DETAIL_NAMESPACE::visa_instrument_impl *>
PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::_instruments;


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::_lock_instruments
 */
std::mutex PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::_lock_instruments;

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
