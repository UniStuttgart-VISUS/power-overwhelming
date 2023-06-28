// <copyright file="string_functions.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <memory>
#include <string>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Frees <paramref name="dst" />, if not <c>nullptr</c>, and assigns a copy
    /// of <paramref name="src" /> to it.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// <para>It is safe to assign a string to itself. Nothing will happen in
    /// this case.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to receive the copy of
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.</param>
    /// <param name="src">The string to be copied. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    template<class TChar>
    void safe_assign(_Inout_opt_z_ TChar *& dst, _In_opt_z_ const TChar *src);

    /// <summary>
    /// Frees <paramref name="dst" /> if necessary, moves
    /// <paramref name="src" /> to this variable and sets the source
    /// <c>nullptr</c>.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// <para>It is safe to assign a string to itself. Nothing will happen in
    /// this case.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to receive 
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.
    /// </param>
    /// <param name="src">The pointer to be moved. If not <c>nullptr</c>, this
    /// string must have been allocated on the heap using <see cref="malloc" />.
    /// </param>
    template<class TChar> void safe_assign(_Inout_opt_z_ TChar *& dst,
        _Inout_opt_z_ TChar *&& src) noexcept;

    /// <summary>
    /// Frees <paramref name="dst" />, if not <c>nullptr</c>, and assigns a copy
    /// of <paramref name="src" /> to it.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to receive the copy of
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.</param>
    /// <param name="src">The string to be copied.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    template<class TChar>
    inline void safe_assign(_Inout_opt_z_ TChar *& dst,
            _In_ const std::basic_string<TChar>& src) {
        safe_assign(dst, src.c_str());
    }

    /// <summary>
    /// Frees <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to be freed. If not
    /// <c>nullptr</c>, the memory for this string must have been allocated on
    /// the heap using <see cref="malloc" />.</param>
    /// <param name="src">A <c>nullptr</c>.</param>
    template<class TChar> void safe_assign(_Inout_opt_z_ TChar *& dst,
        _In_ const std::nullptr_t src) noexcept;

    /// <summary>
    /// Duplicates <paramref name="src" />.
    /// </summary>
    /// <param name="src">The string variable to duplicated. The memory returned
    /// must be released using <see cref="free" />. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    _Ret_maybenull_z_ POWER_OVERWHELMING_API wchar_t *safe_duplicate(
        _In_opt_z_ const wchar_t *src);

    /// <summary>
    /// Duplicates <paramref name="src" />.
    /// </summary>
    /// <param name="src">The string variable to duplicated. The memory returned
    /// must be released using <see cref="free" />. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    _Ret_maybenull_z_ POWER_OVERWHELMING_API char *safe_duplicate(
        _In_opt_z_ const char *src);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "string_functions.inl"
