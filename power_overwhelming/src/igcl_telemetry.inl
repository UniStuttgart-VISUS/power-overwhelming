// <copyright file="igcl_telemetry.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::find_igcl_telemetry_disp
 */
template<class TContainer>
typename const TContainer::value_type&
PWROWG_DETAIL_NAMESPACE::find_igcl_telemetry_disp(
        _In_ const TContainer& disps,
        _In_ const ctl_oc_telemetry_item_t& item) {
    constexpr auto lut = make_igcl_data_type_list();
    assert(lut.size() == disps.size());

    for (std::size_t i = 0; i < lut.size(); ++i) {
        if (lut[i] == item.type) {
            return disps[i];
        }
    }

    throw std::invalid_argument("The given telemetry type is unsupported.");
}


/*
 * PWROWG_DETAIL_NAMESPACE::dispatch_igcl_unit_traits
 */
template<class TCallback, ctl_units_t... Units>
bool PWROWG_DETAIL_NAMESPACE::dispatch_igcl_unit_traits(
        _In_ const ctl_units_t unit,
        _In_ const TCallback callback,
        igcl_unit_dispatch_list<Units...>) {
    constexpr std::array<ctl_units_t, sizeof...(Units)> lut = { Units... };
    std::vector<std::function<void(void)>> dispatchers = {
        [unit, callback](void) {
            typedef igcl_unit_traits<Units> traits;
            callback(static_cast<traits *>(nullptr));
        }...
    };

    for (std::size_t i = 0; i < lut.size(); ++i) {
        if (lut[i] == unit) {
            dispatchers[i]();
            return true;
        }
    }

    return false;
}
