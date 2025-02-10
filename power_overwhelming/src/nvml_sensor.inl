// <copyright file="nvml_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_descriptions
 */
template<class TOutput, class TInput>
TInput PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_descriptions(
        _In_ TOutput oit,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end) {
    auto retval = move_front_if(begin, end, [](const sensor_description& d) {
        return starts_with(d.name(), L"NVML/");
    });

    for (auto it = begin; it != retval; ++it) {
        *oit++ = std::make_shared<nvml_sensor>(
            *sensor_description_builder::private_data<nvmlDevice_t>(*it),
            index++);
    }

    return retval;
}
