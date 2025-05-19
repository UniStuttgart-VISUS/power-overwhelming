// <copyright file="atomic_utilities.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/atomic_utilities.h"

#if defined(_WIN32)
#include <malloc.h>
#endif /* defined(_WIN32) */


/*
 * PWROWG_NAMESPACE::allocate_for_atomic
 */
_Ret_valid_ void *PWROWG_NAMESPACE::allocate_for_atomic(
        _In_ const std::size_t size) {
#if defined(_WIN32)
    void *retval = ::_aligned_malloc(size, false_sharing_range);
#else /* defined(_WIN32) */
    void *retval = std::aligned_alloc(false_sharing_range, size);
#endif /* defined(_WIN32) */

    if (retval == nullptr) {
        throw std::bad_alloc();
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::free_for_atomic
 */
void PWROWG_NAMESPACE::free_for_atomic(_In_opt_ void *ptr) noexcept {
    if (ptr != nullptr) {
#if defined(_WIN32)
        ::_aligned_free(ptr);
#else /* defined(_WIN32) */
        ::free(ptr);
#endif /* defined(_WIN32) */
    }
}
