// <copyright file="visa_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/visa_instrument.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <system_error>

#if !defined(_WIN32)
#include <sys/time.h>
#endif /* !defined(_WIN32) */

#include "visa_exception.h"
#include "visa_instrument_impl.h"
#include "visa_library.h"


/*
 * visus::power_overwhelming::visa_instrument::rohde_und_schwarz
 */
constexpr const char *
visus::power_overwhelming::visa_instrument::rohde_und_schwarz;


/*
 * visus::power_overwhelming::visa_instrument::visa_instrument
 */
visus::power_overwhelming::visa_instrument::visa_instrument(void)
    : _impl(nullptr) { }


/*
 * visus::power_overwhelming::visa_instrument::visa_instrument
 */
visus::power_overwhelming::visa_instrument::visa_instrument(
        _In_z_ const wchar_t *path, _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout);
}


/*
 * visus::power_overwhelming::visa_instrument::visa_instrument
 */
visus::power_overwhelming::visa_instrument::visa_instrument(
        _In_z_ const char *path, _In_ const timeout_type timeout)
        : _impl(nullptr) {
    this->_impl = detail::visa_instrument_impl::create(path, timeout);
}


/*
 * visus::power_overwhelming::visa_instrument::~visa_instrument
 */
visus::power_overwhelming::visa_instrument::~visa_instrument(void) {
    detail::visa_instrument_impl::release(this->_impl);
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::visa_instrument::attribute
 */
ViAttrState visus::power_overwhelming::visa_instrument::attribute(
        _In_ ViAttr name) const {
    ViAttrState retval;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viGetAttribute(this->check_not_disposed()->session, name, &retval));
    return retval;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::visa_instrument::attribute
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::attribute(_In_ ViAttr name,
        _In_ ViAttrState value) {
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viSetAttribute(this->check_not_disposed()->session, name, value));
    return *this;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * visus::power_overwhelming::visa_instrument::clear
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::clear(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viClear(this->check_not_disposed()->session));
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::visa_instrument::clear_status
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::clear_status(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    this->check_not_disposed()->write("*CLS\n");
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::visa_instrument::path
 */
_Ret_maybenull_z_
const char *visus::power_overwhelming::visa_instrument::path(
        void) const noexcept {
    return (*this) ? this->_impl->path.c_str() : nullptr;
}


/*
 * visus::power_overwhelming::visa_instrument::query
 */
visus::power_overwhelming::blob
visus::power_overwhelming::visa_instrument::query(
        _In_reads_bytes_(cnt) const byte_type *query,
        _In_ const std::size_t cnt,
        _In_ const std::size_t buffer_size) const {
    return this->write_all(query, cnt).read_all(buffer_size);
}


/*
 * visus::power_overwhelming::visa_instrument::query
 */
visus::power_overwhelming::blob
visus::power_overwhelming::visa_instrument::query(_In_z_ const char *query,
        _In_ const std::size_t buffer_size) const {
    return this->write(query).read_all(buffer_size);
}


/*
 * visus::power_overwhelming::visa_instrument::query
 */
visus::power_overwhelming::blob
visus::power_overwhelming::visa_instrument::query(_In_z_ const wchar_t *query,
        _In_ const std::size_t buffer_size) const {
    return this->write(query).read_all(buffer_size);
}


/*
 * visus::power_overwhelming::visa_instrument::read
 */
std::size_t visus::power_overwhelming::visa_instrument::read(
        _Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer to receive data from a VISA "
            "instrument must not be null.");
    }

    return this->check_not_disposed()->read(buffer, cnt);
}


/*
 * visus::power_overwhelming::visa_instrument::read_all
 */
visus::power_overwhelming::blob
visus::power_overwhelming::visa_instrument::read_all(
        _In_ const std::size_t buffer_size) const {
    return this->check_not_disposed()->read_all(buffer_size);
}


/*
 * visus::power_overwhelming::visa_instrument::reset
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::reset(void) {
    this->check_not_disposed()->write("*RST\n");
    this->throw_on_system_error();
    return *this;
}


///*
// * visus::power_overwhelming::visa_instrument::set_buffer
// */
//visus::power_overwhelming::visa_instrument&
//visus::power_overwhelming::visa_instrument::set_buffer(
//        _In_ const std::uint16_t mask, _In_ const std::uint32_t size) {
//#if defined(POWER_OVERWHELMING_WITH_VISA)
//    visa_exception::throw_on_error(detail::visa_library::instance()
//        .viSetBuf(this->check_not_disposed()->session, mask, size));
//#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
//    return *this;
//}


/*
 * visus::power_overwhelming::visa_instrument::synchronise_clock
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::synchronise_clock(
        _In_ const bool utc) {
#if defined(_WIN32)
    SYSTEMTIME time;
    if (utc) {
        ::GetSystemTime(&time);
    } else {
        ::GetLocalTime(&time);
    }

    this->check_not_disposed()->write("SYST:TIME %d, %d, %d\n",
        time.wHour, time.wMinute, time.wSecond);
    this->throw_on_system_error();
    this->check_not_disposed()->write("SYST:DATE %d, %d, %d\n",
        time.wYear, time.wMonth, time.wDay);
    this->throw_on_system_error();

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

    this->check_not_disposed()->write("SYST:TIME %d, %d, %d\n",
        time->tm_hour, time->tm_min, time->tm_sec);
    this->throw_on_system_error();
    this->check_not_disposed()->write("SYST:DATE %d, %d, %d\n",
        time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);
    this->throw_on_system_error();

#endif /* defined(_WIN32) */

    return *this;
}


/*
 * visus::power_overwhelming::visa_instrument::system_error
 */
int visus::power_overwhelming::visa_instrument::system_error(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto status = this->query(":SYST:ERR?\n");
    auto delimiter = std::find_if(status.begin(), status.end(),
        [](const byte_type b) { return b == ','; });

    if (delimiter != status.end()) {
        *delimiter = '\0';
        return std::atoi(reinterpret_cast<char *>(status.data()));
    } else {
        throw std::runtime_error("The instrument responded unexpectedly.");
    }
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::visa_instrument::write
 */
std::size_t visus::power_overwhelming::visa_instrument::write(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer being written to the "
            "instrument must not be null.");
    }

    return this->check_not_disposed()->write(buffer, cnt);
}


/*
 * visus::power_overwhelming::visa_instrument::write_all
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::write_all(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer being written to the "
            "instrument must not be null.");
    }

    this->check_not_disposed()->write_all(buffer, cnt);
    return *this;
}


/*
 * visus::power_overwhelming::visa_instrument::write
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::write(
        _In_z_ const char *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("The string to write to the device must "
            "not be null.");
    }

    return this->write_all(reinterpret_cast<const byte_type *>(str),
        ::strlen(str));
}


/*
 * visus::power_overwhelming::visa_instrument::write
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::write(
        _In_z_ const wchar_t *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("The string to write to the device must "
            "not be null.");
    }

    auto s = convert_string<char>(str);
    return this->write_all(reinterpret_cast<const byte_type *>(s.data()),
        s.size());
}


/*
 * visus::power_overwhelming::visa_instrument::operator =
 */
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::operator =(
        _Inout_ visa_instrument&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}

/*
 * visus::power_overwhelming::visa_instrument::operator bool
 */
visus::power_overwhelming::visa_instrument::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::visa_instrument::check_not_disposed
 */
visus::power_overwhelming::detail::visa_instrument_impl *
visus::power_overwhelming::visa_instrument::check_not_disposed(void) const {
    if (*this) {
        assert(this->_impl != nullptr);
        return this->_impl;
    } else {
        throw std::runtime_error("An instrument which has been disposed by "
            "a move operation cannot be used anymore.");
    }
}
