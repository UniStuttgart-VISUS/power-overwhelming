// <copyright file="visa_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visus/pwrowg/visa_instrument.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <system_error>

#if !defined(_WIN32)
#include <sys/time.h>
#endif /* !defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"

#include "no_visa_error_msg.h"
#include "visa_instrument_impl.h"
#include "visa_library.h"


/*
 * PWROWG_NAMESPACE::visa_instrument::find_resources
 */
PWROWG_NAMESPACE::blob PWROWG_NAMESPACE::visa_instrument::find_resources(
        _In_z_ const wchar_t *query) {
    typedef wchar_t char_type;
    if (query == nullptr) {
        throw std::invalid_argument("The instrument query cannot be null.");
    }

    auto q = convert_string<char>(query);
    auto devices = detail::visa_library::instance().find_resource(q.c_str());

    const auto len = std::accumulate(devices.begin(), devices.end(),
        static_cast<std::size_t>(0), [](std::size_t s, const std::string& d) {
            return s + d.size() + 1;
        }) + 1;

    blob retval(len * sizeof(char_type));
    auto cur = retval.as<char_type>();
    const auto end = reinterpret_cast<char_type *>(retval.end());
    assert(cur != nullptr);
    assert(end != nullptr);

    for (auto& d : devices) {
        detail::convert_string(cur, end - cur, d.c_str(), d.size());
        cur += d.size();
        *cur++ = 0;
    }

    *cur = 0;

    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::find_resources
 */
PWROWG_NAMESPACE::blob PWROWG_NAMESPACE::visa_instrument::find_resources(
        _In_z_ const char *query) {
    typedef char char_type;
    if (query == nullptr) {
        throw std::invalid_argument("The instrument query cannot be null.");
    }

    auto devices = detail::visa_library::instance().find_resource(query);

    const auto len = std::accumulate(devices.begin(), devices.end(),
        static_cast<std::size_t>(0), [](std::size_t s, const std::string& d) {
            return s + d.size() + 1;
        }) + 1;

    blob retval(len * sizeof(char_type));
    auto cur = retval.as<char_type>();
    assert(cur != nullptr);

    for (auto& d : devices) {
        std::copy(d.begin(), d.end(), cur);
        cur += d.size();
        *cur++ = 0;
    }

    *cur = 0;

    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::find_resources
 */
PWROWG_NAMESPACE::blob PWROWG_NAMESPACE::visa_instrument::find_resources(
        _In_z_ const wchar_t *vendor_id, _In_z_ const wchar_t *instrument_id) {
    if (vendor_id == nullptr) {
        throw std::invalid_argument("The instrument vendor cannot be null.");
    }
    if (instrument_id == nullptr) {
        throw std::invalid_argument("The instrument ID cannot be null.");
    }

    std::wstring query(L"?*::");    // Any protocol
    query += vendor_id;             // Only specified vendor
    query += L"::";
    query += instrument_id;         // Only specified instrument
    query += L"::?*::INSTR";        // All serial numbers

    return find_resources(query.c_str());
}


/*
 * PWROWG_NAMESPACE::visa_instrument::find_resources
 */
PWROWG_NAMESPACE::blob PWROWG_NAMESPACE::visa_instrument::find_resources(
        _In_z_ const char *vendor_id, _In_z_ const char *instrument_id) {
    if (vendor_id == nullptr) {
        throw std::invalid_argument("The instrument vendor cannot be null.");
    }
    if (instrument_id == nullptr) {
        throw std::invalid_argument("The instrument ID cannot be null.");
    }

    std::string query("?*::");  // Any protocol
    query += vendor_id;         // Only specified vendor
    query += "::";
    query += instrument_id;     // Only specified instrument
    query += "::?*::INSTR";     // All serial numbers

    return find_resources(query.c_str());
}


/*
 * PWROWG_NAMESPACE::visa_instrument::foreach_instance
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::foreach_instance(
        _In_ bool (*callback)(visa_instrument&, void *),
        _In_opt_ void *context){
    if (callback == nullptr) {
        throw std::invalid_argument("The enumeration callback for VISA "
            "instruments must not be nullptr.");
    }

    return detail::visa_instrument_impl::foreach(
            [callback, context](detail::visa_instrument_impl *i) {
        visa_instrument instrument;
        auto retval = true;

        instrument._impl = i;
        try {
            retval = callback(instrument, context);
        } catch (...) {
            retval = false;
        }
        instrument._impl = nullptr;

        return retval;
    });
}


/*
 * PWROWG_NAMESPACE::visa_instrument::rohde_und_schwarz
 */
constexpr const char *PWROWG_NAMESPACE::visa_instrument::rohde_und_schwarz;


/*
 * PWROWG_NAMESPACE::visa_instrument::rohde_und_schwarz
 */
constexpr const PWROWG_NAMESPACE::visa_instrument::timeout_type
PWROWG_NAMESPACE::visa_instrument::default_timeout;


/*
 * PWROWG_NAMESPACE::visa_instrument::visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::visa_instrument(void)
    : _impl(nullptr) { }


/*
 * PWROWG_NAMESPACE::visa_instrument::visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::visa_instrument(
        _In_z_ const wchar_t *path, _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout, nullptr);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::visa_instrument(
        _In_z_ const char *path, _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout, nullptr);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::visa_instrument(
        _Out_ bool &is_new_connection,
        _In_z_ const wchar_t *path,
        _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout,
        &is_new_connection);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::visa_instrument(
        _Out_ bool &is_new_connection,
        _In_z_ const char *path,
        _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout,
        &is_new_connection);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::~visa_instrument
 */
PWROWG_NAMESPACE::visa_instrument::~visa_instrument(void) {
    if (this->_impl != nullptr) {
        this->_impl->release();
    }
}


/*
 * PWROWG_NAMESPACE::visa_instrument::aliased
 */
bool PWROWG_NAMESPACE::visa_instrument::aliased(void) const noexcept {
    return ((this->_impl != nullptr) && (this->_impl->counter() > 0));
}


/*
 * PWROWG_NAMESPACE::visa_instrument::alias_of
 */
bool PWROWG_NAMESPACE::visa_instrument::alias_of(
        _In_ const visa_instrument& instrument) const noexcept {
    return ((this->_impl != nullptr) && (this->_impl == instrument._impl));
}


/*
 * PWROWG_NAMESPACE::visa_instrument::attribute
 */
const PWROWG_NAMESPACE::visa_instrument &
PWROWG_NAMESPACE::visa_instrument::attribute(
        _Out_ void *dst, _In_ ViAttr name) const {
    detail::throw_if_visa_failed(
        detail::visa_library::instance().viGetAttribute(
            this->check_not_disposed().session, name, dst));
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::attribute
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::attribute(_In_ ViAttr name,
        _In_ ViAttrState value) {
    detail::throw_if_visa_failed(
        detail::visa_library::instance().viSetAttribute(
            this->check_not_disposed().session, name, value));
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::beep
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::beep(_In_ const std::size_t cnt) {
    for (std::size_t i = 0; i < cnt; ++i) {
        this->write("SYST:BEEP:IMM\n");
    }
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::beep_on_error
 */
bool PWROWG_NAMESPACE::visa_instrument::beep_on_error(void) {
    auto response = this->query("SYST:BEEP:ERR:STAT?\n");
    auto r = response.as<char>();
    assert(r != nullptr);
    auto status = std::atoi(r);
    return (status != 0);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::beep_on_error
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::beep_on_error(
        _In_ const bool enable) {
    auto& impl = this->check_not_disposed();
    impl.format("SYST:BEEP:ERR:STAT %s\n", enable ? "ON" : "OFF");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::buffer
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::buffer(
        _In_ const std::uint16_t mask, _In_ const std::uint32_t size) {
    detail::throw_if_visa_failed(
        detail::visa_library::instance().viSetBuf(
            this->check_not_disposed().session, mask, size));
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::clear
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::clear(void) {
    detail::throw_if_visa_failed(
        detail::visa_library::instance().viClear(
            this->check_not_disposed().session));
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::clear_status
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::clear_status(void) {
    this->check_not_disposed().write("*CLS\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::enable_system_checks
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::enable_system_checks(
        _In_ const bool enable) {
    this->check_not_disposed().enable_system_checks = enable;
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::event_status
 */
PWROWG_NAMESPACE::visa_event_status
PWROWG_NAMESPACE::visa_instrument::event_status(void) const {
    auto response = this->query("*ESR?\n");
    auto r = response.as<char>();
    assert(r != nullptr);
    auto status = std::atoi(r);
    return static_cast<visa_event_status>(status);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::event_status
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::event_status(
        _In_ const visa_event_status status) {
    auto s = static_cast<int>(status);
    this->check_not_disposed().format("*ESE %u; *OPC?\n", s);
    this->read_all();
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::identify
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::identify(
        _Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const {
    auto retval = this->check_not_disposed().identify();

    if (dst != nullptr) {
        auto converted = convert_string<wchar_t>(retval);
        ::wcsncpy(dst, converted.c_str(), cnt);
        dst[cnt - 1] = 0;
    }

    return (retval.size() + 1);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::identify
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::identify(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) const {
    auto retval = this->check_not_disposed().identify();

    if (dst != nullptr) {
        ::strncpy(dst, retval.c_str(), cnt);
        dst[cnt - 1] = 0;
    }

    return (retval.size() + 1);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::identify
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::identify(
        _In_opt_ std::nullptr_t dst,
        _In_ const std::size_t cnt) {
    auto id = this->check_not_disposed().identify();
    return (id.size() + 1);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::interface_type
 */
std::uint16_t PWROWG_NAMESPACE::visa_instrument::interface_type(
        void) const {
    return this->check_not_disposed().interface_type();
}



/*
 * PWROWG_NAMESPACE::visa_instrument::name
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::name(
        _Out_writes_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const {
    auto retval = this->name(nullptr, 0);

    if ((dst != nullptr) && (cnt >= retval)) {
        std::vector<char> buffer(retval);
        retval = this->name(buffer.data(), buffer.size());
        auto name = convert_string<wchar_t>(buffer.data());

#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
        ::wcscpy_s(dst, cnt, name.c_str());
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
        ::wcscpys(dst, name.c_str());
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::name
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::name(
        _Out_writes_(cnt) char *dst,
        _In_ const std::size_t cnt) const {
    auto name = this->query("SYST:NAME?\n");
    auto n = name.as<char>();
    _Analysis_assume_(n != nullptr);

    detail::trim_eol(n);
    n = detail::trim_if(n, [](const char c) { return c == '"'; });
    auto retval = ::strlen(n) + 1;

    if ((dst != nullptr) && (cnt >= retval)) {
#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
        ::strcpy_s(dst, cnt, n);
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
        ::strcpy(dst, n);
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::name
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::name(
        _In_opt_ const std::nullptr_t dst,
        _In_ const std::size_t cnt) const {
    return this->name(static_cast<char *>(nullptr), 0);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::name
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::name(_In_z_ const wchar_t *name) {
    if (name == nullptr) {
        throw std::invalid_argument("The name of the instrument must not be "
            "null.");
    }

    auto n = convert_string<char>(name);
    return this->name(n.c_str());
}


/*
 * PWROWG_NAMESPACE::visa_instrument::name
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::name(_In_z_ const char *name) {
    if (name == nullptr) {
        throw std::invalid_argument("The name of the instrument must not be "
            "null.");
    }

    auto& impl = this->check_not_disposed();
    impl.format("SYST:NAME \"%s\"\n", name);
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::on_operation_complete
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::on_operation_complete(
        _In_opt_ void(*callback)(visa_instrument&, void *),
        _In_opt_ void *context,
        _In_opt_ void (*context_deleter)(void *)) {
    auto& impl = this->check_not_disposed();

    // Remember whether a callback was set before, which we need to know in
    // order install or uninstall the handler and enabling the necessary
    // service requests.
    const auto was_on = static_cast<bool>(impl.opc_callback);

    // Set or remove the callback and the context passed to it.
    impl.opc_callback = callback;
    impl.opc_callback.context(context, context_deleter);

    if (impl.opc_callback && !was_on) {
        auto es = this->event_status();
        this->event_status(es | visa_event_status::operation_complete);
        auto ss = this->service_request_status();
        this->service_request_status(ss | visa_status_byte::master_status);

        impl.install_handler(VI_EVENT_SERVICE_REQ, &on_event, this);
        impl.enable_event(VI_EVENT_SERVICE_REQ);

    } else if (!impl.opc_callback && was_on) {
        impl.disable_event(VI_EVENT_SERVICE_REQ);
        impl.uninstall_handler(VI_EVENT_SERVICE_REQ, &on_event, this);

        auto es = this->event_status();
        this->event_status(es | ~visa_event_status::operation_complete);
        // Note: While we disable the OPC event flag, we do not disable
        // the events on master status, because this could be used for
        // something else. The caller must do that on his own if this is
        // desired.
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::operation_complete
 */
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::operation_complete(
        void) const {
    // Cf. https://www.rohde-schwarz.com/at/driver-pages/fernsteuerung/measurements-synchronization_231248.html
    this->query("*OPC?\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::operation_complete_async
 */
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::operation_complete_async(
        void) const {
    // Cf. https://www.rohde-schwarz.com/at/driver-pages/fernsteuerung/measurements-synchronization_231248.html
    this->write("*OPC\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::path
 */
_Ret_maybenull_z_
const char *
PWROWG_NAMESPACE::visa_instrument::path(void) const noexcept {
    return (*this) ? this->_impl->path().c_str() : nullptr;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::query
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::visa_instrument::query(
        _In_reads_bytes_(cnt) const byte_type *query,
        _In_ const std::size_t cnt,
        _In_ const std::size_t buffer_size) const {
    auto& impl = this->check_not_disposed();
    impl.write(query, cnt);
    // Note: we cannot check the system state in case of a query as this is a
    // query in itself that cannot overlap.
    return this->read_all(buffer_size);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::query
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::visa_instrument::query(_In_z_ const char *query,
        _In_ const std::size_t buffer_size) const {
    auto& impl = this->check_not_disposed();
    impl.write(query);
    // Note: we cannot check the system state in case of a query as this is a
    // query in itself that cannot overlap.
    return this->read_all(buffer_size);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::query
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::visa_instrument::query(_In_z_ const wchar_t *query,
        _In_ const std::size_t buffer_size) const {
    auto& impl = this->check_not_disposed();
    auto q = convert_string<char>(query);
    impl.write(q.c_str());
    // Note: we cannot check the system state in case of a query as this is a
    // query in itself that cannot overlap.
    return this->read_all(buffer_size);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::read
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::read(
        _Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer to receive data from a VISA "
            "instrument must not be null.");
    }

    auto& impl = this->check_not_disposed();
    return impl.read(buffer, cnt);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::read_all
 */
PWROWG_NAMESPACE::blob PWROWG_NAMESPACE::visa_instrument::read_all(
        _In_ const std::size_t buffer_size) const {
    auto& impl = this->check_not_disposed();
    blob retval(buffer_size);
    return impl.read_all(retval);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::read_binary
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::visa_instrument::read_binary(void) const {
    auto& impl = this->check_not_disposed();
    auto retval = impl.read_binary();
    // Note: It is not reasonable to check for system errors here, because the
    // read_binary method tries reading all junk at the end, which will
    // inevitably cause an error.
    //this->throw_on_system_error();
    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::reset
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::reset(
        _In_ const bool flush_buffers,
        _In_ const bool clear_status) {
    if (flush_buffers) {
        // First, do the R&S flush ...
        this->check_not_disposed();
        try {
            this->_impl->flush_data();
        } catch (...) { /* Ignore this. */ }

        // ... then, do the standard VISA flush.
        this->try_clear();
    }

    if (clear_status) {
        this->write("*CLS\n");
    }

    this->query("*RST;*OPC?\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::service_request_status
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::service_request_status(
        _In_ const visa_status_byte status) {
    auto s = static_cast<int>(status);
    this->check_not_disposed().format("*SRE %u; *OPC?\n", s);
    this->read_all();
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::service_request_status
 */
PWROWG_NAMESPACE::visa_status_byte
PWROWG_NAMESPACE::visa_instrument::service_request_status(void) const {
    auto response = this->query("*SRE?\n");
    auto r = response.as<char>();
    assert(r != nullptr);
    auto status = std::atoi(r);
    return static_cast<visa_status_byte>(status);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::synchronise_clock
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::synchronise_clock(
        _In_ const bool utc) {
#if defined(_WIN32)
    SYSTEMTIME time;
    if (utc) {
        ::GetSystemTime(&time);
    } else {
        ::GetLocalTime(&time);
    }

    this->check_not_disposed().format("SYST:TIME %d, %d, %d\n",
        time.wHour, time.wMinute, time.wSecond);
    this->check_not_disposed().format("SYST:DATE %d, %d, %d\n",
        time.wYear, time.wMonth, time.wDay);

#else /* defined(_WIN32) */
    struct timeval tv;
    struct timezone tz;

    if (::gettimeofday(&tv, &tz) != 0) {
        throw std::system_error(errno, std::system_category());
    }

    if (utc) {
        tv.tv_sec -= tz.tz_minuteswest * 60;
    }

    auto time = localtime(&tv.tv_sec);

    this->check_not_disposed().format("SYST:TIME %d, %d, %d\n",
        time->tm_hour, time->tm_min, time->tm_sec);
    this->check_not_disposed().format("SYST:DATE %d, %d, %d\n",
        time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);
#endif /* defined(_WIN32) */

    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::status
 */
PWROWG_NAMESPACE::visa_status_byte
PWROWG_NAMESPACE::visa_instrument::status(void) const {
    ViUInt16 retval;
    detail::throw_if_visa_failed(
        detail::visa_library::instance().viReadSTB(
            this->check_not_disposed().session, &retval));
    return static_cast<visa_status_byte>(retval);

    // Note: R&S does the following, but NI's documentation suggests that
    // viReadSTB will issue *STB? by itself as a fallback, so we try the easier
    // one ...

    //if (this->check_not_disposed().vxi) {
    //    ViUInt16 retval;
    //    visa_exception::throw_on_error(detail::visa_library::instance()
    //        .viReadSTB(this->check_not_disposed().session, &retval));
    //    return static_cast<std::int32_t>(retval);

    //} else {
    //    this->write("*STB?\n");
    //    auto response = this->read_all();
    //    *response.rend() = 0;
    //    return std::atoi(response.as<char>());
    //}
}


/*
 * PWROWG_NAMESPACE::visa_instrument::system_error
 */
int PWROWG_NAMESPACE::visa_instrument::system_error(void) const {
    auto status = this->query(":SYST:ERR?\n");

    if (!status.empty()) {
        _Analysis_assume_(status.begin() != nullptr);
        _Analysis_assume_(status.end() != nullptr);
        auto delimiter = std::find_if(status.begin(),
            status.end(),
            [](const byte_type b) { return b == ','; });

        if ((delimiter != nullptr) && (delimiter != status.end())) {
            *delimiter = '\0';
            auto s = reinterpret_cast<char *>(status.begin());
            assert(s != nullptr);
            return std::atoi(s);
        }
    }

    throw std::runtime_error("The instrument responded unexpectedly when "
        "retrieving its error status.");
}


/*
 * PWROWG_NAMESPACE::visa_instrument::throw_on_system_error
 */
void PWROWG_NAMESPACE::visa_instrument::throw_on_system_error(
        void) const {
    // This method is lenient, so if the instrument is invalid, do not check
    // anything and do not raise an exception either.
    if (this->_impl != nullptr) {
        this->_impl->throw_on_system_error();
    }
}


/*
 * PWROWG_NAMESPACE::visa_instrument::timeout
 */
PWROWG_NAMESPACE::visa_instrument::timeout_type
PWROWG_NAMESPACE::visa_instrument::timeout(void) const {
    ViUInt32 retval;
    this->attribute(&retval, VI_ATTR_TMO_VALUE);
    return static_cast<timeout_type>(retval);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::timeout
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::timeout(
        _In_ const timeout_type timeout) {
    return this->attribute(VI_ATTR_TMO_VALUE, timeout);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::try_clear
 */
bool PWROWG_NAMESPACE::visa_instrument::try_clear(void) {
    auto status = detail::visa_library::instance().viClear(
        this->check_not_disposed().session);
    return (status == VI_SUCCESS);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::wait
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::wait(void) {
    this->query("*WAI\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::write
 */
std::size_t PWROWG_NAMESPACE::visa_instrument::write(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer being written to the "
            "instrument must not be null.");
    }

    auto& impl = this->check_not_disposed();
    auto retval = impl.write(buffer, cnt);
    impl.check_system_error();
    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::write
 */
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::write(
        _In_z_ const char *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("The string to write to the device must "
            "not be null.");
    }

    auto& impl = this->check_not_disposed();
    impl.write(str);
    impl.check_system_error();
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::write
 */
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::write(
        _In_z_ const wchar_t *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("The string to write to the device must "
            "not be null.");
    }

    auto& impl = this->check_not_disposed();
    auto s = convert_string<char>(str);

    if (s.back() != impl.terminal_character) {
        s += impl.terminal_character;
    }

    impl.write_all(reinterpret_cast<const byte_type *>(s.data()), s.size());
    impl.check_system_error();
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::write_all
 */
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::write_all(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer being written to the "
            "instrument must not be null.");
    }

    auto& impl = this->check_not_disposed();
    impl.write_all(buffer, cnt);
    impl.check_system_error();
    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::operator =
 */
PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::operator =(
        _Inout_ visa_instrument&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::operator bool
 */
PWROWG_NAMESPACE::visa_instrument::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * PWROWG_NAMESPACE::visa_instrument::check_not_disposed
 */
PWROWG_NAMESPACE::detail::visa_instrument_impl&
PWROWG_NAMESPACE::visa_instrument::check_not_disposed(void) {
    if (*this) {
        assert(this->_impl != nullptr);
        return *this->_impl;
    } else {
        throw std::runtime_error("An instrument which has been disposed by "
            "a move operation cannot be used anymore.");
    }
}


/*
 * PWROWG_NAMESPACE::visa_instrument::check_not_disposed
 */
const PWROWG_NAMESPACE::detail::visa_instrument_impl&
PWROWG_NAMESPACE::visa_instrument::check_not_disposed(void) const {
    if (*this) {
        assert(this->_impl != nullptr);
        return *this->_impl;
    } else {
        throw std::runtime_error("An instrument which has been disposed by "
            "a move operation cannot be used anymore.");
    }
}


/*
 * PWROWG_NAMESPACE::visa_instrument::on_event
 */
ViStatus _VI_FUNCH PWROWG_NAMESPACE::visa_instrument::on_event(
        ViSession session, ViEventType event_type, ViEvent event,
        ViAddr context) {
    auto that = static_cast<visa_instrument *>(context);

    if ((event_type == VI_EVENT_SERVICE_REQ)
            && (that != nullptr)
            && (that->_impl != nullptr)) {
        try {
            // According to
            // https://www.ni.com/docs/de-DE/bundle/ni-visa/page/ni-visa/vi_event_service_req.html,
            // we must read the status byte here for the callback to work. We
            // have to do that anyway, because this seems to be the only way
            // to distinguish between OPC events and other status changes.
            if (that->status() && visa_status_byte::operation_status) {
                auto events = that->event_status();
                if (events && visa_event_status::operation_complete) {
                    that->_impl->opc_callback(*that);
                }
            }
        } catch (...) {
            // If the event handler does not return, which is the case when we
            // throw an exception, we must free the event object manually. Cf.
            // https://www.ni.com/docs/de-DE/bundle/ni-visa/page/ni-visa/vieventhandler.html
            detail::visa_library::instance().viClose(event);
            throw;
        }
    }

    return VI_SUCCESS;
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
