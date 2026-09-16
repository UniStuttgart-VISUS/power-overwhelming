// <copyright file="hdf5_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::hdf5_sink::write_samples
 */
template<class TIterator>
void PWROWG_NAMESPACE::hdf5_sink::write_samples(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt) {
    this->write(sensors, cnt);
    const auto samples = std::distance(begin, end);
    auto buffer = this->buffer(samples);
    std::copy(begin, end, buffer);
    this->write(buffer, samples);
}
