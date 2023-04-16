// <copyright file="io_util.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "io_util.h"

#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <Windows.h>
#else /* defined(_WIN32) */
#include <unistd.h>
#include <sys/types.h>
#endif /* defined(_WIN32) */


#if defined(_WIN32)
#define THROW_LAST_ERROR() throw std::system_error(::GetLastError(),\
    std::system_category())
#else /* defined(_WIN32) */
#define THROW_LAST_ERROR() throw std::system_error(errno,\
    std::system_category())
#endif /* defined(_WIN32) */


/*
 * visus::power_overwhelming::detail::open
 */
POWER_OVERWHELMING_API int visus::power_overwhelming::detail::open(
        _In_z_ const char *path, _In_ const int flags, _In_ const int mode) {
    if (path == nullptr) {
        throw std::invalid_argument("The path must be a valid string.");
    }

    auto retval = ::open(path, flags, mode);
    if (retval == -1) {
        THROW_LAST_ERROR();
    }

    return retval;
}



/*
 * visus::power_overwhelming::detail::read_all_bytes
 */
std::vector<std::uint8_t> visus::power_overwhelming::detail::read_all_bytes(
        _In_ const int fd) {
    std::vector<std::uint8_t> retval;

    // Get an estimate of the memory we need and seek to the begin of the file.
    {
        const auto size = seek(fd, 0, posix_seek_origin::end);
        retval.resize(static_cast<std::size_t>(size) + 1);
        seek(fd, 0, posix_seek_origin::begin);
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

    if (cnt == -1) {
        THROW_LAST_ERROR();
    }

    static_assert(sizeof(*(retval.data())) == 1, "value_type must be a byte.");
    retval.resize(dst - retval.data());

    return retval;
}


/*
 * visus::power_overwhelming::detail::read_bytes
 */
void visus::power_overwhelming::detail::read_bytes(_In_ const int fd,
        _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt) {
    auto d = static_cast<std::uint8_t *>(dst);
    auto c = 0;
    auto rem = static_cast<int>(cnt);

    while ((rem > 0) && ((c = ::read(fd, dst, rem)) > 0)) {
        d += c;
        rem -= c;
    }

    if (cnt == -1) {
        THROW_LAST_ERROR();
    }

    if (rem > 0) {
#if defined(_WIN32)
        throw std::system_error(ERROR_NO_MORE_ITEMS, std::system_category());
#else /* defined(_WIN32) */
        throw std::system_error(E2BIG, std::system_category());
#endif /* defined(_WIN32) */
    }
}


/*
 * visus::power_overwhelming::detail::seek
 */
std::streamoff visus::power_overwhelming::detail::seek(_In_ const int fd,
        _In_ const std::streamoff offset,
        _In_ const posix_seek_origin origin) {
#if defined(_WIN32)
    auto retval = ::_lseeki64(fd, offset, static_cast<int>(origin));
#else /* defined(_WIN32 ) */
    auto retval = ::lseek64(fd, offset, static_cast<int>(origin));
#endif /* defined(_WIN32) */

    if (retval == -1) {
        THROW_LAST_ERROR();
    }

    return retval;
}
