// <copyright file="emi_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::emi_sensor::from_descriptions(
    _In_ list_type &dst,
    _In_ sample::source_type index,
    _In_ const TInput begin,
    _In_ const TInput end,
    _In_ const sensor_array_impl *owner,
    _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;

    // Find out which are the EMI sensors.
    auto retval = move_front_if(begin, end, is_emi_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Group the sensors by their device, which is identified by the path.
    std::sort(begin, retval,
        [](const sensor_description &lhs, const sensor_description &rhs) {
        return (compare(lhs.path(), rhs.path(), true) < 0);
    });

    for (auto it = begin; it != retval; /* [sic] */) {
        std::vector<USHORT> channels;
        auto path = it->path();

        while ((it != retval) && equals(it->path(), path)) {
            auto c = builder_type::private_data<USHORT>(*it++);
            if (c != nullptr) {
                channels.push_back(*c);
            }
#if (defined(DEBUG) || defined(_DEBUG))
            --_rem;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
        }

        auto used_indices = (std::max)(channels.size(),
            static_cast<std::size_t>(1));
        dst.emplace_back(path, std::move(channels), index);
        index += used_indices;
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;
}
