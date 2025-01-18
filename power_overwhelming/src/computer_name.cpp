// <copyright file="computer_name.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/computer_name.h"

#include <system_error>

#if defined(_WIN32)
#include <Windows.h>
#else /* defined(_WIN32) */
#include <algorithm>
#include <cstring>

#include <sys/utsname.h>

#include <errno.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#if defined(_WIN32)
    /// <summary>
    /// Traits class for the <c>GetComputerName</c> API.
    /// </summary>
    /// <typeparam name="TChar">The type of the character to retrieve the
    /// computer name as.</typeparam>
    template<class TChar> struct computer_name_api { };

    /// <summary>
    /// Specialisation for MBCS.
    /// </summary>
    template<> struct computer_name_api<char> {
        typedef char char_type;
        typedef DWORD size_type;
        static inline BOOL get(char_type *buffer, size_type *size) {
            return ::GetComputerNameA(buffer, size);
        }
    };

    /// <summary>
    /// Specialisation for UTF16.
    /// </summary>
    template<> struct computer_name_api<wchar_t> {
        typedef wchar_t char_type;
        typedef DWORD size_type;
        static inline BOOL get(char_type *buffer, size_type *size) {
            return ::GetComputerNameW(buffer, size);
        }
    };

    /// <summary>
    /// Generic implementation of <c>GetComputerName</c>.
    /// </summary>
    template<class TChar>
    std::size_t computer_name(TChar *dst, const std::size_t cnt) {
        auto size = (dst != nullptr)
            ? static_cast<DWORD>(cnt)
            : static_cast<DWORD>(0);

        if (!computer_name_api<TChar>::get(dst, &size)) {
            const auto error = ::GetLastError();
            if ((error != ERROR_BUFFER_OVERFLOW) || (cnt >= size)) {
                throw std::system_error(error, std::system_category());
            }
        }

        return size;
    }
#endif /* defined(_WIN32) */

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::computer_name
 */
std::size_t visus::power_overwhelming::computer_name(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) {
#if defined(_WIN32)
    return detail::computer_name(dst, cnt);

#else /* defined(_WIN32) */
    struct utsname names; 
    if (uname(&names) != 0) {
        throw std::system_error(errno, std::system_category());
    }

    auto retval = std::strlen(names.nodename) + 1;
    if ((dst != nullptr) || (cnt > retval)) {
        ::strncpy(dst, names.nodename, cnt);
        dst[cnt - 1] = 0;
    }

    return retval;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::computer_name
 */
std::size_t visus::power_overwhelming::computer_name(
        _Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) {
#if defined(_WIN32)
    return detail::computer_name(dst, cnt);

#else /* defined(_WIN32) */
    if ((dst == nullptr) || (cnt == 0)) {
        return computer_name(static_cast<char *>(nullptr), 0);

    } else {
        // Performance off ...
        std::vector<char> buffer(cnt);
        auto retval = computer_name(buffer.data(), buffer.size());
        auto result = convert_string<char>(buffer.data());
        std::copy(result.begin(), result.end(), dst);
        return retval;
    }
#endif /* defined(_WIN32) */
}
