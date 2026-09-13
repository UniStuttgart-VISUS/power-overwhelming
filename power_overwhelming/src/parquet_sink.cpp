// <copyright file="parquet_sink.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
#include "visus/pwrowg/parquet_sink.h"

#include "parquet_sink_impl.h"

/*
 * PWROWG_NAMESPACE::parquet_sink::parquet_sink
 */
PWROWG_NAMESPACE::parquet_sink::parquet_sink(
        _In_ const parquet_configuration& config)
    : _impl(new detail::parquet_sink_impl(config)) { }


/*
 * PWROWG_NAMESPACE::parquet_sink::~parquet_sink
 */
PWROWG_NAMESPACE::parquet_sink::~parquet_sink(void) noexcept {
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::parquet_sink::operator =
 */
PWROWG_NAMESPACE::parquet_sink& PWROWG_NAMESPACE::parquet_sink::operator =(
        _Inout_ parquet_sink&& rhs) noexcept {
    if (this != &rhs) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::parquet_sink::end_row_group
 */
void PWROWG_NAMESPACE::parquet_sink::end_row_group(void) {
    assert(this->_impl != nullptr);
    this->_impl->writer.EndRowGroup();
}


/*
 * PWROWG_NAMESPACE::parquet_sink::write_sample
 */
void PWROWG_NAMESPACE::parquet_sink::write_sample(
        _In_ const sample& s,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt) {
    assert(sensors != nullptr);
    assert(this->_impl != nullptr);
    this->_impl->writer << s.timestamp.value();

    switch (this->_impl->identity) {
        case parquet_identity_column::index:
            this->_impl->writer << static_cast<int>(s.source);
            break;

        default:
            this->_impl->writer << this->_impl->get_identity(sensors, s.source);
            break;
    }

    if (this->_impl->raw) {
        // Unfortunately, the copy is required to make the type check in Parquet
        // happy.
        std::array<char, sizeof(sample::reading)> v;
        static_assert(sizeof(v) == sizeof(sample::reading), "Size mismatch");
        std::copy(s.reading.bytes,
            s.reading.bytes + sizeof(sample::reading),
            v.begin());
        this->_impl->writer << v;
    } else {
        switch (sensors[s.source].reading_type()) {
            case reading_type::floating_point:
                this->_impl->writer << s.reading.floating_point;
                break;

            case reading_type::signed_integer:
                this->_impl->writer << static_cast<float>(
                    s.reading.signed_integer);
                break;

            case reading_type::unsigned_integer:
                this->_impl->writer << static_cast<float>(
                    s.reading.unsigned_integer);
                break;

            default:
                assert(false);
                this->_impl->writer << 0.0f;
                break;
        }
    }

    this->_impl->writer << parquet::EndRow;
}

#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */
