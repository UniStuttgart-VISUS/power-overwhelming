// <copyright file="adl_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <atomic>
#include <cinttypes>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A RAII container for the ADL library.
    /// </summary>
    /// <remarks>
    /// The implementation holds a global counter of active scopes and
    /// initialises the library only if it has not yet been initialised.
    /// Likewise, the library is not freed unless the last scope was
    /// destroyed.
    /// </remarks>
    class adl_scope final {

    public:

        /// <summary>
        /// Memory allocator passed to the ADL.
        /// </summary>
        /// <param name="cnt"></param>
        /// <returns></returns>
        static void *__stdcall allocate(int cnt);

        /// <summary>
        /// Deallocates memory that has been obtained from
        /// <see cref="allocate" />.
        /// </summary>
        /// <param name="buffer"></param>
        static void __stdcall deallocate(void **buffer);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <exception cref="adl_exception">If the ADL could not be loaded.
        /// </exception>
        adl_scope(void);

        adl_scope(const adl_scope&) = delete;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~adl_scope(void);

        adl_scope& operator =(const adl_scope&) = delete;

    private:

        static std::atomic<std::size_t> _cnt;

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
