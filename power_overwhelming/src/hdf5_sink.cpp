// <copyright file="hdf5_sink.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hdf5_sink.h"

#include <stdexcept>

#if defined(_WIN32)
//#include <processenv.h>
#endif /* defined(_WIN32) */

#include "friendly_timestamp.h"
#include "hdf5_sink_impl.h"
#include "io_util.h"


/*
 * PWROWG_NAMESPACE::hdf5_sink::hdf5_sink
 */
PWROWG_NAMESPACE::hdf5_sink::hdf5_sink(
        _In_z_ const hdf5_configuration& configuration)
    : _impl(new detail::hdf5_sink_impl(configuration)) { }


/*
 * PWROWG_NAMESPACE::hdf5_sink::dispose
 */
void PWROWG_NAMESPACE::hdf5_sink::dispose(void) noexcept {
    if (this->_impl == nullptr) {
        return;
    }

    this->_impl->file.close();
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::hdf5_sink::buffer
 */
_Ret_valid_ PWROWG_NAMESPACE::sample *PWROWG_NAMESPACE::hdf5_sink::buffer(
        _In_ const std::size_t cnt) {
    assert(this->_impl != nullptr);
    if (this->_impl->buffer.size() < cnt) {
        this->_impl->buffer.resize(cnt);
    }

    return this->_impl->buffer.data();
}


/*
 * PWROWG_NAMESPACE::hdf5_sink::write
 */
void PWROWG_NAMESPACE::hdf5_sink::write(_In_reads_(cnt) sample *samples,
        _In_ const std::size_t cnt) {
    assert(this->_impl != nullptr);
    assert(samples != nullptr);

    if (!this->_impl->raw) {
        for (std::size_t i = 0; i < cnt; ++i) {
            const auto c = this->_impl->converters[samples[i].source];
            auto& s = samples[i];
            s.reading.floating_point = c(s.reading);
        }
    }

    // Compute the new size of the data space and extend the data set
    // accordingly.
    auto current_space = this->_impl->samples.getSpace();
    hsize_t current_dims[1];
    current_space.getSimpleExtentDims(current_dims, nullptr);

    hsize_t new_dims[] = { current_dims[0] + cnt };
    this->_impl->samples.extend(new_dims);

    // Select the hyper slab appended to the file and fill it.
    H5::DataSpace file_space = this->_impl->samples.getSpace();
    hsize_t count[] = { cnt };
    file_space.selectHyperslab(H5S_SELECT_SET, count, current_dims);
    H5::DataSpace mem_space(1, count);

    this->_impl->samples.write(samples,
        this->_impl->type,
        mem_space,
        file_space);
}


/*
 * PWROWG_NAMESPACE::hdf5_sink::write
 */
void PWROWG_NAMESPACE::hdf5_sink::write(
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt) {
    assert(this->_impl != nullptr);
    assert(sensors != nullptr);
    if (this->_impl->sensors_written) {
        return;
    }

    // Create the converter functions if necessary.
    if (!this->_impl->raw) {
        this->_impl->converters.reserve(cnt);
        std::transform(sensors, sensors + cnt,
            std::back_inserter(this->_impl->converters),
            [](const sensor_description& d) {
                switch (d.reading_type()) {
                    case reading_type::floating_point:
                        return &detail::hdf5_sink_impl::from_floating_point;
                    case reading_type::signed_integer:
                        return &detail::hdf5_sink_impl::from_signed_integer;
                    case reading_type::unsigned_integer:
                        return &detail::hdf5_sink_impl::from_unsigned_integer;
                    default:
                        throw std::invalid_argument("Unsupported type of "
                            "sensor reading.");
                }
            });
    }

    // Convert the descriptions into a HDF5-friendly representation.
    std::vector<detail::hdf5_sensor_description> data;
    std::set<std::string> strings;
    data.reserve(cnt);
    std::uint32_t source = 0;
    std::transform(sensors,
        sensors + cnt,
        std::back_inserter(data),
        [&strings, &source](const sensor_description& d) {
            return detail::hdf5_sensor_description(source++, d, strings);
        });

    // Create the data space.
    hsize_t dims[] = { cnt };
    H5::DataSpace space(std::size(dims), dims);

    // Create the data set and write the data.
    auto type = detail::hdf5_sensor_description::create();
    auto dataset = this->_impl->file.createDataSet("sensors", type, space);
    dataset.write(data.data(), type);

    this->_impl->sensors_written = true;
}


///*
// * PWROWG_NAMESPACE::pwog_sink::write_meta_data
// */
//void PWROWG_NAMESPACE::pwog_sink::write_meta_data(void) {
//    auto timestamp = detail::friendly_timestamp<char>();
//    this->_file << make_pwog_meta_data("Timestamp", timestamp);
//
//#if defined(_WIN32)
//    this->_file << make_pwog_meta_data("CommandLine", ::GetCommandLineA());
//#else /* defined(_WIN32) */
//    auto fh = detail::open("/proc/self/cmdline", O_RDONLY);
//    try {
//        const auto cmd = detail::read_all_bytes(fh);
//        this->_file << make_pwog_meta_data("CommandLine",
//            reinterpret_cast<const char *>(cmd.data()));
//        ::close(fh);
//    } catch (...) {
//        ::close(fh);
//    }
//#endif /* defined(_WIN32) */
//}
