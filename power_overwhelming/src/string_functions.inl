// <copyright file="string_functions.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::safe_assign
 */
template<class TChar>
void visus::power_overwhelming::detail::safe_assign(
        _Inout_opt_z_ TChar *& dst,
        _In_opt_z_ const TChar *src) {
    if (dst != src) {
        safe_assign(dst, nullptr);
        assert(dst == nullptr);
        dst = safe_duplicate(src);
    }
}


/*
 * visus::power_overwhelming::detail::safe_assign
 */
template<class TChar>
void visus::power_overwhelming::detail::safe_assign(
        _Inout_opt_z_ TChar *& dst,
        _Inout_opt_z_ TChar *&& src) noexcept {
    if (src != dst) {
        safe_assign(dst, nullptr);
        assert(dst == nullptr);
        dst = src;
        src = nullptr;
    }
}


/*
 * visus::power_overwhelming::detail::safe_assign
 */
template<class TChar>
void visus::power_overwhelming::detail::safe_assign(
        _Inout_opt_z_ TChar *& dst, _In_ const std::nullptr_t) noexcept {
    if (dst != nullptr) {
        ::free(dst);
        dst = nullptr;
    }
}
