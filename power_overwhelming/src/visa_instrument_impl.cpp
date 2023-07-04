// <copyright file="visa_instrument_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_instrument_impl.h"

#include <stdexcept>

#include "visa_library.h"


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::create
 */
visus::power_overwhelming::detail::visa_instrument_impl *
visus::power_overwhelming::detail::visa_instrument_impl::create(
        _In_ const std::string& path, _In_ const std::uint32_t timeout) {
    std::lock_guard<decltype(_lock_instruments)> l(_lock_instruments);
    visa_instrument_impl *retval = nullptr;

    auto it = _instruments.find(path);
    if (it != _instruments.end()) {
        // Reuse existing instrument for same connection.
        retval = it->second;

    } else {
        // If no existing scope was found or if the previous scope has been
        // deleted, create a new one.
        retval = new visa_instrument_impl();

#if defined(POWER_OVERWHELMING_WITH_VISA)
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

        retval->_path = path;

        _instruments[path] = retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
        throw std::logic_error("The library was compiled without support "
            "for the Virtual Instrument Software Architecture.");
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    } /* if (it != _instruments.end()) */

    ++retval->_counter;
    return retval;
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::create
 */
visus::power_overwhelming::detail::visa_instrument_impl *
visus::power_overwhelming::detail::visa_instrument_impl::create(
        _In_z_ const wchar_t *path, _In_ const std::uint32_t timeout) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to a VISA instrument must not "
            "be null.");
    }

    return create(power_overwhelming::convert_string<char>(path), timeout);
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::create
 */
visus::power_overwhelming::detail::visa_instrument_impl *
visus::power_overwhelming::detail::visa_instrument_impl::create(
        _In_z_ const char *path, _In_ const std::uint32_t timeout) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to a VISA instrument must not "
            "be null.");
    }

    return create(std::string(path), timeout);
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::~visa_instrument_impl
 */
visus::power_overwhelming::detail::visa_instrument_impl::~visa_instrument_impl(
        void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    visa_library::instance().viClose(this->session);
    visa_library::instance().viClose(this->resource_manager);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::identify
 */
std::string visus::power_overwhelming::detail::visa_instrument_impl::identify(
        void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    const auto cmd = "*IDN?\n";
    this->write_all(reinterpret_cast<const byte_type *>(cmd) , ::strlen(cmd));
    auto retval = this->read_all();

    auto it = std::find_if(retval.begin(), retval.end(),
        [](const byte_type b) { return ((b == '\r') || (b == '\n')); });
    if (it != retval.end()) {
        // TODO: potential hazard when writing this
        *it = '\0';
    }

    return retval.as<char>();

#else/*defined(POWER_OVERWHELMING_WITH_VISA) */
    return "";
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::read
 */
std::size_t visus::power_overwhelming::detail::visa_instrument_impl::read(
        _Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const {
    assert(buffer != nullptr);
#if defined(POWER_OVERWHELMING_WITH_VISA)
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viRead(this->session,
            buffer,
            static_cast<ViUInt32>(cnt),
            &retval));
    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::read_all
 */
visus::power_overwhelming::blob
visus::power_overwhelming::detail::visa_instrument_impl::read_all(
        _In_ const std::size_t buffer_size) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
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
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return blob();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::release
 */
std::size_t visus::power_overwhelming::detail::visa_instrument_impl::release(
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
 * visus::power_overwhelming::detail::visa_instrument_impl::system_error
 */
int visus::power_overwhelming::detail::visa_instrument_impl::system_error(
        _Out_ std::string& message) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
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
        throw std::runtime_error("The instrumet responded unexpectedly.");
    }
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    message = "";
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::write
 */
std::size_t visus::power_overwhelming::detail::visa_instrument_impl::write(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    assert(buffer != nullptr);
#if defined(POWER_OVERWHELMING_WITH_VISA)
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viWrite(this->session,
            buffer,
            static_cast<ViUInt32>(cnt),
            &retval));
    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::write
 */
void visus::power_overwhelming::detail::visa_instrument_impl::write(
        _In_z_ const char *str) const {
    assert(str != nullptr);
    return this->write_all(reinterpret_cast<const byte_type *>(str),
        ::strlen(str));
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::write_all
 */
void visus::power_overwhelming::detail::visa_instrument_impl::write_all(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
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
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::_instruments
 */
std::map<std::string, visus::power_overwhelming::detail::visa_instrument_impl *>
visus::power_overwhelming::detail::visa_instrument_impl::_instruments;


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::_lock_instruments
 */
std::mutex
visus::power_overwhelming::detail::visa_instrument_impl::_lock_instruments;
