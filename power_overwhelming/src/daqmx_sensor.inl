// <copyright file="daqmx_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::daqmx_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    typedef sensor_description desc_type;
    assert(owner != nullptr);

    // Move the NI-DAQmx sensor to the front of the list.
    auto retval = move_front_if(begin, end, is_daqmx_sensor);

    // If there is no NI-DAQmx-based sensor, bail out directly.
    if (begin == retval) {
        return retval;
    }

    // Create the sensor, which is always one managing every sensor within
    // [begin, retval[.
    dst.emplace_back(begin, retval, index, owner, config);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::daqmx_sensor
 */
template<class TIterator> PWROWG_DETAIL_NAMESPACE::daqmx_sensor::daqmx_sensor(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ std::size_t index,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config)
    : _index(index),
        _owner(owner) {
    typedef sensor_description_builder builder_type;
    typedef daqmx_sensor_definition private_type;

    std::transform(begin, end,
        std::back_inserter(this->_sensors),
        [](const auto& d) {
            return *builder_type::private_data<private_type>(d);
        });
}
