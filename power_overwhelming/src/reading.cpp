// <copyright file="reading.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/reading.h"

#include <cassert>


/*
 * PWROWG_NAMESPACE::to_float
 */
float PWROWG_NAMESPACE::to_float(_In_ const reading& reading,
        _In_ const reading_type type) noexcept {
    switch (type) {
        case reading_type::floating_point:
            return reading.floating_point;

        case reading_type::signed_integer:
            return static_cast<float>(reading.signed_integer);

        case reading_type::unsigned_integer:
            return static_cast<float>(reading.unsigned_integer);

        default:
            // This should be unreachable. If we get here, there is a new type
            // of reading that must be handled.
            assert(false);
            return 0.0f;
    }
}
