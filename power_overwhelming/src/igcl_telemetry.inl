// <copyright file="igcl_telemetry.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::visit
 */
template<class TCallback, ctl_data_type_t... Types>
bool PWROWG_DETAIL_NAMESPACE::visit(
        _In_ const ctl_oc_telemetry_item_t& item,
        _In_ const TCallback callback,
        const igcl_data_type_dispatch_list<Types...>) {
    static constexpr std::array<ctl_data_type_t, sizeof...(Types)> types = {
        Types...
    };

    if (!item.bSupported) {
        return false;
    }

    // Note: Do not make this static!
    // TODO: I think this is expensive. Can we hack that such that this list is only created once?
    auto dispatchers = make_igcl_data_type_dispatchers(callback,
        igcl_data_type_dispatch_list<Types...>());

    for (std::size_t i = 0; i < types.size(); ++i) {
        if (item.type == types[i]) {
            dispatchers[i](item);
            return true;
        }
    }

    return false;
}
