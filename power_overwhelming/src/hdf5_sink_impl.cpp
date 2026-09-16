// <copyright file="hdf5_sink_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_HDF5)
#include "hdf5_sink_impl.h"

#include "visus/pwrowg/sample.h"


/*
 * PWROWG_DETAIL_NAMESPACE::hdf5_sensor_description::create
 */
H5::CompType PWROWG_DETAIL_NAMESPACE::hdf5_sensor_description::create(void) {
    H5::StrType string_type(H5::PredType::C_S1, H5T_VARIABLE);
    string_type.setCset(H5T_CSET_UTF8);

    H5::CompType retval(sizeof(hdf5_sensor_description));
    retval.insertMember("source",
        HOFFSET(hdf5_sensor_description, source),
        H5::PredType::NATIVE_UINT32);
    retval.insertMember("id",
        HOFFSET(hdf5_sensor_description, id),
        string_type);
    retval.insertMember("label",
        HOFFSET(hdf5_sensor_description, label),
        string_type);
    retval.insertMember("name",
        HOFFSET(hdf5_sensor_description, name),
        string_type);
    retval.insertMember("path",
        HOFFSET(hdf5_sensor_description, path),
        string_type);
    static_assert(sizeof(reading_type) == sizeof(uint32_t), "The HDF5 "
        "implementation assumes the reading_type to be 32 bit.");
    retval.insertMember("reading_type",
        HOFFSET(hdf5_sensor_description, reading_type),
        H5::PredType::NATIVE_UINT32);
    static_assert(sizeof(reading_unit) == sizeof(uint32_t), "The HDF5 "
        "implementation assumes the reading_unit to be 32 bit.");
    retval.insertMember("reading_unit",
        HOFFSET(hdf5_sensor_description, reading_unit),
        H5::PredType::NATIVE_UINT32);
    retval.insertMember("sensor_class",
        HOFFSET(hdf5_sensor_description, sensor_class),
        string_type);
    static_assert(sizeof(sensor_type) == sizeof(uint32_t), "The HDF5 "
        "implementation assumes the sensor_type to be 32 bit.");
    retval.insertMember("sensor_type",
        HOFFSET(hdf5_sensor_description, sensor_type),
        H5::PredType::NATIVE_UINT32);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::hdf5_sensor_description::hdf5_sensor_description
 */
PWROWG_DETAIL_NAMESPACE::hdf5_sensor_description::hdf5_sensor_description(
        _In_ const std::uint32_t source,
        _In_ const sensor_description& desc,
        _Inout_ std::set<std::string>& buffer)
    : source(source),
        label(nullptr),
        reading_type(desc.reading_type()),
        reading_unit(desc.reading_unit()),
        sensor_type(desc.sensor_type()) {
    this->id = buffer.insert(PWROWG_NAMESPACE::convert_string<char>(
        desc.id())).first->c_str();

    if (desc.label() != nullptr) {
        this->label = buffer.insert(PWROWG_NAMESPACE::convert_string<char>(
            desc.label())).first->c_str();
    }

    this->name = buffer.insert(PWROWG_NAMESPACE::convert_string<char>(
        desc.name())).first->c_str();

    this->path = buffer.insert(PWROWG_NAMESPACE::convert_string<char>(
        desc.path())).first->c_str();

    this->sensor_class = buffer.insert(
        desc.sensor_class().to_string<char>()).first->c_str();
}


/*
 * PWROWG_DETAIL_NAMESPACE::hdf5_sink_impl::hdf5_sink_impl
 */
PWROWG_DETAIL_NAMESPACE::hdf5_sink_impl::hdf5_sink_impl(
        _In_ const hdf5_configuration& config)
    : file(config.path(), config.overwrite() ? H5F_ACC_TRUNC : H5F_ACC_EXCL),
        raw(config.raw()),
        sensors_written(false) {
    // Create a dynamically sized data space for the sensors.
    hsize_t initial[] = { 0 };
    hsize_t maximum[] = { H5S_UNLIMITED };
    H5::DataSpace space(std::size(initial), initial, maximum);

    // Create an empty data set using the specified chunk size.
    H5::DSetCreatPropList props;
    hsize_t chunks[] = { config.chunk_size() };
    props.setChunk(std::size(chunks), chunks);

    // Construct the HDF5 representation of a sample.
    this->type = H5::CompType(sizeof(PWROWG_NAMESPACE::sample));
    static_assert(sizeof(timestamp) == sizeof(std::int64_t), "The HDF5 "
        "implementation assumes the timestamp to be 64 bit.");
    this->type.insertMember("timestamp",
        HOFFSET(PWROWG_NAMESPACE::sample, timestamp),
        H5::PredType::NATIVE_INT64);
    static_assert(sizeof(PWROWG_NAMESPACE::sample::source_type) 
        == sizeof(std::uint32_t), "The HDF5 implementation assumes the source "
        "index to be 32 bit.");
    this->type.insertMember("source",
        HOFFSET(PWROWG_NAMESPACE::sample, source),
        H5::PredType::NATIVE_UINT32);

    if (raw) {
        hsize_t cnt_bytes[] = { 4 };
        H5::ArrayType bytes_type(H5::PredType::NATIVE_UINT8,
            std::size(cnt_bytes), cnt_bytes);
        this->type.insertMember("reading",
            HOFFSET(PWROWG_NAMESPACE::sample, reading),
            bytes_type);
    } else {
        this->type.insertMember("reading",
            HOFFSET(PWROWG_NAMESPACE::sample, reading),
            H5::PredType::NATIVE_FLOAT);
    }

    this->samples = file.createDataSet("samples", this->type, space, props);
}

#endif /* !defined(POWER_OVERWHELMING_WITH_HDF5) */
