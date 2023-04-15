// <copyright file="io_util.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "io_util.h"

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include <system_error>


/*
 * visus::power_overwhelming::detail::read_all_bytes
 */
std::vector<std::uint8_t> visus::power_overwhelming::detail::read_all_bytes(
        _In_ const int fd) {
    std::vector<std::uint8_t> retval;

    // Get an estimate of the memory we need and seek to the begin of the file.
    {
        const auto size = ::lseek(fd, 0, SEEK_END);
        if (size < 0) {
#if defined(_WIN32)
            throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
            throw std::system_error(errno, std::system_category());
#endif /* defined(_WIN32) */
        }

        retval.resize(static_cast<std::size_t>(size) + 1);

        const auto pos = ::lseek(fd, 0, SEEK_SET);
        if (pos < 0) {
#if defined(_WIN32)
            throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
            throw std::system_error(errno, std::system_category());
#endif /* defined(_WIN32) */
        }
    }

    auto dst = retval.data();
    auto cnt = 0;
    auto rem = static_cast<unsigned int>(retval.size());

    while ((cnt = ::read(fd, dst, rem)) > 0) {
        dst += cnt;

        if (rem > cnt) {
            rem -= cnt;

        } else {
            auto a = (std::max)(retval.size() / 2, static_cast<std::size_t>(1));
            retval.resize(retval.size() + a);
            rem += a;
            rem -= cnt;
        }
    }

    if (cnt < 0) {
#if defined(_WIN32)
        throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
        throw std::system_error(errno, std::system_category());
#endif /* defined(_WIN32) */
    }

    static_assert(sizeof(*(retval.data())) == 1, "value_type must be a byte.");
    retval.resize(dst - retval.data());

    return retval;
}
