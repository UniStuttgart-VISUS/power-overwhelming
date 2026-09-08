// <copyright file="parquet_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::parquet_sink::write_samples
 */
template<class TIterator>
void PWROWG_NAMESPACE::parquet_sink::write_samples(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const sensor_description *sensors) {
    assert(sensors != nullptr);
    for (auto it = begin; it != end; ++it) {
        this->write_sample(*it, sensors);
    }
    this->end_row_group();
}
