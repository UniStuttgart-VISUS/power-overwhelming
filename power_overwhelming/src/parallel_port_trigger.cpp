// <copyright file="parallel_port_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/parallel_port_trigger.h"

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <thread>

#if !defined(_WIN32)
#include <fcntl.h>
#include <unistd.h>
#include <linux/ppdev.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#endif /* !defined(_WIN32) */

#include "power_overwhelming/convert_string.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The ITU Morse code table.
    /// </summary>
    static const struct {
        wchar_t symbol;
        const wchar_t *code;
    } morse_table[] = {
        { L'a', L".-" },
        { L'ä', L".-.-" },
        { L'b', L"-..." },
        { L'c', L"-.-." },
        { L'd', L"-.." },
        { L'e', L"." },
        { L'f', L"..-." },
        { L'g', L"--." },
        { L'h', L"...." },
        { L'i', L".." },
        { L'j', L".---" },
        { L'k', L"-.-" },
        { L'l', L".-.." },
        { L'm', L"--" },
        { L'n', L"-." },
        { L'o', L"---" },
        { L'ö', L"---." },
        { L'p', L".--." },
        { L'q', L"--.-" },
        { L'r', L".-." },
        { L's', L"..." },
        { L't', L"-" },
        { L'u', L"..-" },
        { L'ü', L"..--" },
        { L'v', L"...-" },
        { L'w', L".--" },
        { L'x', L"-..-" },
        { L'y', L"-.--" },
        { L'z', L"--.." },
        { L'0', L"-----" },
        { L'1', L".----" },
        { L'2', L"..---" },
        { L'3', L"...--" },
        { L'4', L"....-" },
        { L'5', L"....." },
        { L'6', L"-...." },
        { L'7', L"--..." },
        { L'8', L"---.." },
        { L'9', L"----." },
        { L',', L"--..--" },
        { L'!', L"-.-.--" },
        { L'?', L"..--.." },
        { L'.', L".-.-.-" },

        { L'è', L".-..-" },
        { L'é', L"..-.." },
        { L'ß', L"...--.." },
        { L':', L"---..." },
        { L';', L"-.-.-." },
        { L'-', L"-....-" },
        { L'_', L"..--.-" },
        { L'(', L"-.--." },
        { L')', L"-.--.-" },
        { L'\'', L".----." },
        { L'=', L"-...-" },
        { L'+', L".-.-." },
        { L'/', L"-..-." },
        { L'@', L".--.-." },
        { L'"', L".-..-." },

        { L' ', L"/" },
        { 0, nullptr }
    };

} /* namespace detail */
} /* power_overwhelming */
} /* visus */


/*
 * visus::power_overwhelming::parallel_port_trigger::to_morse
 */
std::size_t visus::power_overwhelming::parallel_port_trigger::to_morse(
        _Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *message) {
    if (message == nullptr) {
        throw std::invalid_argument("The message to be encoded cannot be "
            "null.");
    }

    auto cur = dst;
    const auto end = message + ::wcslen(message);
    auto rem = (dst != nullptr) ? cnt : 0;
    std::size_t retval = 1;
    auto symbol = message;

    for (const wchar_t *s = message; s != end; ++s) {
        for (std::size_t i = 0; detail::morse_table[i].symbol != 0; ++i) {
            if (std::tolower(*symbol) == detail::morse_table[i].symbol) {
                const auto code = detail::morse_table[i].code;
                const auto len = ::wcslen(code);
                const auto space = ((s + 1) < end);

                retval += len;
                if (space) {
                    // Note: If 's' is not the last character in the input, we
                    // need to add a space between its code and the next code.
                    ++retval;
                }

                if (rem > 0) {
                    // We can append the code to the output buffer, so do it. It
                    // is safe to assume that the output buffer is not null at
                    // this poins, as we force 'rem' to zero if this is the case.
                    ::wcsncpy(cur, code, rem);
                    cur += (std::min)(len, rem);
                    rem -= (std::min)(len, rem);

                    if (space && (rem > 0)) {
                        *cur++ = ' ';
                        --rem;
                    }
                }

                break;
            }
        }

        ++symbol;
    }

    if ((dst != nullptr) && (cnt >= 1)) {
        if (retval < cnt) {
            dst[retval] = 0;
        } else {
            dst[cnt - 1] = 0;
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger
 */
visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger(void)
    : _handle(invalid_handle) { }


/*
 * visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger
 */
visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger(
        _In_z_ const wchar_t *path) : _handle(invalid_handle) {
    this->open(path);
}


/*
 * visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger
 */
visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger(
        _In_z_ const char *path) : _handle(invalid_handle) {
    this->open(path);
}


/*
 * visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger
 */
visus::power_overwhelming::parallel_port_trigger::parallel_port_trigger(
        _Inout_ parallel_port_trigger&& rhs) noexcept : _handle(rhs._handle) {
    rhs._handle = invalid_handle;
}


/*
 * visus::power_overwhelming::parallel_port_trigger::~parallel_port_trigger
 */
visus::power_overwhelming::parallel_port_trigger::~parallel_port_trigger(void) {
    this->close();
}


/*
 * visus::power_overwhelming::parallel_port_trigger::close
 */
void visus::power_overwhelming::parallel_port_trigger::close(void) noexcept {
    if (this->_handle != invalid_handle) {
#if defined(_WIN32)
        ::CloseHandle(this->_handle);
#else /* defined(_WIN32) */
        ::ioctl(this->_handle, PPRELEASE);
        ::close(this->_handle);
#endif /* defined(_WIN32) */
        this->_handle = invalid_handle;
    }
}


/*
 * visus::power_overwhelming::parallel_port_trigger::morse
 */
void visus::power_overwhelming::parallel_port_trigger::morse(
        _In_opt_z_ const wchar_t *code,
        _In_ const milliseconds_type base_time,
        _In_ const parallel_port_pin on,
        _In_ const parallel_port_pin off) const {
    const auto high = to_value(on);
    const auto low = to_value(off);
    const std::chrono::milliseconds time_unit(base_time);

    this->write(off);

    auto symbol = code;
    while ((symbol != nullptr) && (*symbol != 0)) {
        switch (*symbol++) {
            case L' ':
                // Pause between characters == 3 dits.
                std::this_thread::sleep_for(3 * time_unit);
                break;

            case L'/':
                // Pause between words == 7 dits.
                std::this_thread::sleep_for(7 * time_unit);
                break;

            case L'.':
                // 1 dit == 1 time unit.
                this->write(high);
                std::this_thread::sleep_for(time_unit);
                this->write(low);
                break;

            case L'-':
                // 1 dah == 3 dits.
                this->write(high);
                std::this_thread::sleep_for(3 * time_unit);
                this->write(low);
                break;

            default:
                break;
        }
    }
}


/*
 * visus::power_overwhelming::parallel_port_trigger::open
 */
void visus::power_overwhelming::parallel_port_trigger::open(
        _In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The specified path is invalid.");
    }

    this->close();
    assert(this->_handle == invalid_handle);

#if defined(_WIN32)
    this->_handle = ::CreateFileW(path, GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (this->_handle == invalid_handle) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
#else /* defined(_WIN32) */
    auto p = convert_string<char>(path);
    this->open(p.c_str());
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::parallel_port_trigger::open
 */
void visus::power_overwhelming::parallel_port_trigger::open(
        _In_z_ const char *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The specified path is invalid.");
    }

    this->close();
    assert(this->_handle == invalid_handle);

#if defined(_WIN32)
    this->_handle = ::CreateFileA(path, GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (this->_handle == invalid_handle) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
#else /* defined(_WIN32) */
    this->_handle = ::open(path, O_RDWR);
    if (this->_handle == invalid_handle) {
        throw std::system_error(errno, std::system_category());
    }

    if (::ioctl(this->_handle, PPCLAIM) != 0) {
        ::close(this->_handle);
        this->_handle = invalid_handle;
        throw std::system_error(errno, std::system_category());
    }
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::parallel_port_trigger::write
 */
void visus::power_overwhelming::parallel_port_trigger::write(
        _In_ const value_type data) const {
#if defined(_WIN32)
    DWORD written = 0;
    if (!::WriteFile(this->_handle, &data, sizeof(data), &written, nullptr)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
#else /* defined(_WIN32) */
    if (::ioctl(this->_handle, PPWDATA, &data) != 0) {
        throw std::system_error(errno, std::system_category());
    }
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::parallel_port_trigger::pulse
 */
void visus::power_overwhelming::parallel_port_trigger::pulse(
        _In_ const value_type data,
        _In_ const milliseconds_type period) const {
    this->write(data);
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
    this->write(static_cast<value_type>(0));
}


/*
 * visus::power_overwhelming::parallel_port_trigger::pulse
 */
void visus::power_overwhelming::parallel_port_trigger::pulse(
        _In_ const parallel_port_pin pins,
        _In_ const milliseconds_type period) const {
    this->pulse(to_value(pins), period);
}


/*
 * visus::power_overwhelming::parallel_port_trigger::write
 */
void visus::power_overwhelming::parallel_port_trigger::write(
        _In_ const parallel_port_pin pins) const {
    this->write(to_value(pins));
}


/*
 * visus::power_overwhelming::parallel_port_trigger::operator =
 */
visus::power_overwhelming::parallel_port_trigger&
visus::power_overwhelming::parallel_port_trigger::operator =(
        _Inout_ parallel_port_trigger&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = invalid_handle;
    }

    return *this;
}


/*
 * visus::power_overwhelming::parallel_port_trigger::operator bool
 */
visus::power_overwhelming::parallel_port_trigger::operator bool(
        void) const noexcept {
    return (this->_handle != invalid_handle);
}


/*
 * visus::power_overwhelming::parallel_port_trigger::invalid_handle
 */
constexpr const visus::power_overwhelming::parallel_port_trigger::handle_type
visus::power_overwhelming::parallel_port_trigger::invalid_handle;
