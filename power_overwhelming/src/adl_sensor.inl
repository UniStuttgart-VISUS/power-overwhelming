// <copyright file="adl_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::adl_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::adl_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    assert(owner != nullptr);

    // Find out which are the ADL sensors.
    auto retval = move_front_if(begin, end, is_adl_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Group the sensors by their adapter.
    std::sort(begin, retval,
            [](const sensor_description &lhs, const sensor_description &rhs) {
        auto pdl = *builder_type::private_data<private_data>(lhs);
        auto pdr = *builder_type::private_data<private_data>(rhs);
        return (pdl->adapter < pdr->adapter);
    });

    for (auto it = begin; it != retval; /* [sic] */) {
        auto pd = builder_type::private_data<private_data>(*it);
        auto adapter = pd->adapter;
        std::vector<ADL_PMLOG_SENSORS> sources;

        while (it != retval) {
            auto pd = builder_type::private_data<private_data>(*it);
            if (pd->adapter != adapter) {
                break;
            }

            sources.push_back(pd->source);
            ++it;
        }

        dst.emplace_back(adapter, sources, owner->configuration->interval,
            index);
        index += sources.size();
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;
}
