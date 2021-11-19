// <copyright file="nvml_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


#if defined(POWER_OVERWHELMING_WITH_NVML)
namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A RAII container for the NVML library.
    /// </summary>
    /// <remarks>
    /// As NVML uses an internal reference counter, multiple scopes can be use
    /// by an application. NVML will not be unloaded unless the last scope was
    /// destroyed.
    /// </remarks>
    class nvml_scope final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <exception cref="nvml_exception">If the NVML could not be loaded.
        /// </exception>
        nvml_scope(void);

        nvml_scope(const nvml_scope&) = delete;

        /// <summary>
        /// Moves <paramref name="rhs" /> to a new instance.
        /// </summary>
        /// <remarks>
        /// This operation abandons <paramref name="rhs" />, ie the NVML library
        /// will not be released if <paramref name="rhs" /> leaves its scope.
        /// Instead, ownership is transferred to the new object.
        /// </remarks>
        /// <param name="rhs"></param>
        nvml_scope(nvml_scope&& rhs) noexcept : _abandoned(false) {
            rhs._abandoned = true;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~nvml_scope(void);

        nvml_scope& operator =(const nvml_scope&) = delete;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <remarks>
        /// This operation abandons <paramref name="rhs" />, ie the NVML library
        /// will not be released if <paramref name="rhs" /> leaves its scope.
        /// Instead, ownership is transferred to this object.
        /// </remarks>
        /// <param name="rhs"></param>
        /// <returns><c>*this</c></returns>
        nvml_scope& operator =(nvml_scope&& rhs) noexcept;

    private:

        bool _abandoned;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
