// <copyright file="pwog_file.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PWOG_FILE_H)
#define _PWROWG_PWOG_FILE_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"

#include "io_util.h"


PWROWG_DETAIL_NAMESPACE_BEGIN


class PWROWG_TEST_API pwog_file final {

public:

    /// <summary>
    /// The fourcc at the begin of each file.
    /// </summary>
    static constexpr const std::uint32_t fourcc = 'PWOG';

private:

#if defined(_WIN32)
    typedef HANDLE handle_type;
#else /* defined(_WIN32 */
    typedef int handle_type;
#endif /* defined(_WIN32 */

    handle_type _handle;
    bool _swap;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_PWOG_FILE_H) */
