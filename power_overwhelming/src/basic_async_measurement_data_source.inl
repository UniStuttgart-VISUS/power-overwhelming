// <copyright file="basic_async_measurement_data_source.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::basic_async_measurement_data_source<TDerived>::deliver_async
 */
template<class TDerived>
void visus::power_overwhelming::detail::basic_async_measurement_data_source<
        TDerived>::deliver_async(void) const {
    auto that = static_cast<const TDerived *>(this);
    auto sample = that->sample(this->_async_sampling.resolution());
    this->_async_sampling(that->sensor_name.c_str(), sample);
}


/*
 * ...::basic_async_measurement_data_source<TDerived>::update_async
 */
template<class TDerived>
void visus::power_overwhelming::detail::basic_async_measurement_data_source<
        TDerived>::update_async(_Inout_ async_sampling&& sampling) {
    this->_async_sampling = std::move(sampling);
}
