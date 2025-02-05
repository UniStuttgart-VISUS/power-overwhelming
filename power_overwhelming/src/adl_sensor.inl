// <copyright file="adl_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions
 */
template<class TOutput>
void PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions(_In_ TOutput oit,
        _In_ const configuration_type& config) {
}


/*
 * PWROWG_DETAIL_NAMESPACE::adl_sensor::from_descriptions
 */
template<class TOutput, class TInput>
TInput PWROWG_DETAIL_NAMESPACE::adl_sensor::from_descriptions(
        _In_ TOutput oit,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end) {
    auto retval = move_front_if(begin, end, [](const sensor_description& d) {
        return starts_with(d.name(), L"ADL/");
    });

    for (auto it = begin; it != retval; ++it) {
        //*oit++ = std::make_shared<adl_sensor>(
        //    *sensor_description_builder::private_data<nvmlDevice_t>(*it),
        //    index++);
    }

    return retval;
}