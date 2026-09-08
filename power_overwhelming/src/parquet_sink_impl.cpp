// <copyright file="parquet_sink_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
#include "parquet_sink_impl.h"

#include "visus/pwrowg/sample.h"


/*
 * PWROWG_DETAIL_NAMESPACE::parquet_sink_impl::parquet_sink_impl
 */
PWROWG_DETAIL_NAMESPACE::parquet_sink_impl::parquet_sink_impl(
        _In_ const parquet_configuration& config)
        : identity(config.identity()), raw(config.raw()) {
    assert(config.path() != nullptr);
    auto parquet_props = parquet::WriterProperties::Builder()
        .created_by("Power Overwhelming")
        ->version(parquet::ParquetVersion::PARQUET_2_6)
        ->build();
    auto arrow_props = parquet::ArrowWriterProperties::Builder()
        .store_schema()
        ->build();

    PARQUET_ASSIGN_OR_THROW(this->stream,
        arrow::io::FileOutputStream::Open(config.path()));
    //PARQUET_ASSIGN_OR_THROW(this->writer,
    //    parquet::arrow::FileWriter::Open(
    //        nullptr,
    //        //*batch_stream->schema().get(),
    //        arrow::default_memory_pool(),
    //        this->stream,
    //        parquet_props,
    //        arrow_props));

    parquet::schema::NodeVector fields;
    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "timestamp",
        parquet::Repetition::REQUIRED,
        parquet::Type::INT64,
        parquet::ConvertedType::INT_64
    ));

    if (config.string_identity()) {
        fields.push_back(parquet::schema::PrimitiveNode::Make(
            "sensor",
            parquet::Repetition::REQUIRED,
            parquet::Type::BYTE_ARRAY,
            parquet::ConvertedType::UTF8
        ));
    } else {
        fields.push_back(parquet::schema::PrimitiveNode::Make(
            "sensor",
            parquet::Repetition::REQUIRED,
            parquet::Type::INT32,
            parquet::ConvertedType::INT_32
        ));
    }

    if (this->raw) {
        fields.push_back(parquet::schema::PrimitiveNode::Make(
            "value",
            parquet::Repetition::REQUIRED,
            parquet::Type::FIXED_LEN_BYTE_ARRAY,
            parquet::ConvertedType::NONE,
            sizeof(sample::reading)
        ));
    } else {
        fields.push_back(parquet::schema::PrimitiveNode::Make(
            "value",
            parquet::Repetition::REQUIRED,
            parquet::Type::FLOAT,
            parquet::ConvertedType::NONE
        ));
    }

    auto schema = std::static_pointer_cast<parquet::schema::GroupNode>(
        parquet::schema::GroupNode::Make(
            "readings",
            parquet::Repetition::REQUIRED,
            fields));

    this->writer = parquet::StreamWriter(parquet::ParquetFileWriter::Open(
        this->stream, schema, parquet_props));
    // TODO: All of this is a stopgap solution. We should use the Parquet
    // batches directly as TLS buffers.
}


/*
 * PWROWG_DETAIL_NAMESPACE::parquet_sink_impl::get_identity
 */
const std::string& PWROWG_DETAIL_NAMESPACE::parquet_sink_impl::get_identity(
        _In_reads_(idx) const sensor_description *sensors,
        _In_ const size_t idx) {
    assert(sensors != nullptr);
    static const std::string empty;

    switch (this->identity) {
        case parquet_identity_column::id:
            for (std::size_t i = this->identities.size(); i <= idx; ++i) {
                this->identities.push_back(this->get_id(sensors, i));
            }
            break;

        case parquet_identity_column::label:
            for (std::size_t i = this->identities.size(); i <= idx; ++i) {
                this->identities.push_back(this->get_label(sensors, i));
            }
            break;

        default:
            return empty;
    }

    assert(this->identities.size() > idx);
    return this->identities[idx];
}

#endif /* !defined(_PWROWG_PARQUET_SINK_IMPL_H) */
