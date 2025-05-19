// <copyright file="powenetics_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::powenetics_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    assert(owner != nullptr);

    // Find out which are the Powenetics sensors.
    auto retval = move_front_if(begin, end, is_powenetics_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Group the sensors by their COM port.
    sort_by_path(begin, retval);

    for (auto it = begin; it != retval; /* [sic] */) {
        const std::wstring port(it->path());
        std::map<index_type, selector_type> indices;

        while ((it != retval) && equals(it->path(), port)) {
            auto s = builder_type::private_data<selector_type>(*it);
            if (s == nullptr) {
                assert(false);
                continue;
            }

            indices[index++] = *s;
            ++it;
#if (defined(DEBUG) || defined(_DEBUG))
            --_rem;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
        }

        dst.emplace_back(port.c_str(), std::move(indices), owner);
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;
}
