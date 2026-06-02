// <copyright file="rtx_quantity.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::rtx_quantity::rtx_quantity
 */
template<class TRep, class TPeriod>
PWROWG_NAMESPACE::rtx_quantity::rtx_quantity(
        _In_ const std::chrono::duration<TRep, TPeriod> value)
        : _unit(nullptr) {
    if (std::is_same<TPeriod, std::nano>::value) {
        this->_value = static_cast<float>(value.count());
        detail::safe_assign(this->_unit, "ns");

    } else if (std::is_same<TPeriod, std::micro>::value) {
        this->_value = static_cast<float>(value.count());
        detail::safe_assign(this->_unit, "us");

    } else if (std::is_same<TPeriod, std::milli>::value) {
        this->_value = static_cast<float>(value.count());
        detail::safe_assign(this->_unit, "ms");

    } else if (std::is_same<TPeriod, std::ratio<1>>::value) {
        this->_value = static_cast<float>(value.count());
        detail::safe_assign(this->_unit, "s");

    } else if (std::is_same<TPeriod, std::kilo>::value) {
        this->_value = static_cast<float>(value.count());
        detail::safe_assign(this->_unit, "ks");

    } else {
        typedef std::chrono::duration<float, std::milli> frac_millis;
        this->_value = std::chrono::duration_cast<frac_millis>(value).count();
        detail::safe_assign(this->_unit, "ms");
    }
}
