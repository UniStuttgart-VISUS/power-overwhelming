// <copyright file="hdf5_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HDF5_SINK_H)
#define _PWROWG_HDF5_SINK_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_HDF5)
#include "visus/pwrowg/hdf5_configuration.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { struct hdf5_sink_impl; }


/// <summary>
/// A sink writing to an HDF5 file.
/// </summary>
class POWER_OVERWHELMING_API hdf5_sink {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="configuration">Configures the behaviour of the sink.
    /// </param>
    explicit hdf5_sink(_In_z_ const hdf5_configuration& configuration);

    hdf5_sink(const hdf5_sink&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~hdf5_sink(void) noexcept {
        this->dispose();
    }

    /// <summary>
    /// Disposes the sink, flushing all data to disk and closing the file.
    /// </summary>
    void dispose(void) noexcept;

    hdf5_sink& operator =(const hdf5_sink&) = delete;

    /// <summary>
    /// Answer whether the sink is valid, ie has not been disposed.
    /// </summary>
    /// <returns><see langword="true "/> if the sink is valid,
    /// <see langword="false" /> otherwise.</returns>
    inline operator bool(void) const noexcept {
        return (this->_impl != nullptr);
    }

protected:

    /// <summary>
    /// Write the given range of samples to the <see cref="_file" />.
    /// </summary>
    template<class TIterator>
    void write_samples(_In_ const TIterator begin,
        _In_ const TIterator end,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt);

private:

    /// <summary>
    /// Makes sure that the internal conversion buffer holds at least
    /// <paramref name="cnt" /> elements and returns a pointer to the first
    /// element. The internal buffer is required because we must have
    /// contiguous memory for HDF5 which our public API does not require.
    /// </summary>
    _Ret_valid_ sample *buffer(_In_ const std::size_t cnt);

    /// <summary>
    /// Inserts the given samples to the appropriate data space in the file.
    /// </summary>
    void write(_In_reads_(cnt) sample *samples,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Inserts the sensor description data space to the file. The call has no
    /// effect if the sensors have already been written to the file.
    /// </summary>
    void write(_In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt);

    detail::hdf5_sink_impl *_impl;

};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/hdf5_sink.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_HDF5) */
#endif /* !defined(_PWROWG_HDF5_SINK_H) */
