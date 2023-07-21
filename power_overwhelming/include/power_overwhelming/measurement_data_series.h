// <copyright file="measurement_data_series.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/measurement_data.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Container for a series of <see cref="measurement_data" /> obtained from
    /// a single <see cref="sensor" />.
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    class POWER_OVERWHELMING_API measurement_data_series final {

    public:

        /// <summary>
        /// The type of string characters.
        /// </summary>
        typedef wchar_t char_type;

        /// <summary>
        /// The type of measurements being stored in the series.
        /// </summary>
        typedef measurement_data value_type;

        /// <summary>
        /// Resizes the data series to the specified number of elements, keeping
        /// at most <paramref name="series" /> of the existing values.
        /// </summary>
        /// <remarks>
        /// <para>Typically, this method is only used by sensors generating data
        /// series who need to grow the buffer to store new samples.</para>
        /// <para>If the data series is growing, the values past the original
        /// size of the series are initialised as invalid. Callers should make
        /// sure to truncate the data series to the range of valid samples
        /// before handing it to any client code.</para>
        /// </remarks>
        /// <param name="series">The series to be resized.</param>
        /// <param name="size">The new size of the data series.</param>
        /// <returns>A pointer to the new begin of the values in
        /// <paramref name="series" />.</returns>
        /// <exception cref="std::bad_alloc">If the allocation of heap memory
        /// for the data failed.</exception>
        static _Ret_maybenull_ value_type *resize(
            _Inout_ measurement_data_series& series,
            _In_ const std::size_t size);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="sensor">The name of the sensor.</param>
        /// <param name="size">The number of values to allocate.</param>
        /// <exception cref="std::invalid_argument">If
        /// <exception cref="std::bad_alloc">If the allocation of heap memory
        /// failed.</exception>
        explicit measurement_data_series(_In_z_ const char_type *sensor);

        /// <summary>
        /// Initialise from move.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        measurement_data_series(_Inout_ measurement_data_series&& rhs) noexcept;

        /// <summary>
        /// FInalises the instance.
        /// </summary>
        ~measurement_data_series(void);

        /// <summary>
        /// Answer the last data element.
        /// </summary>
        /// <returns>The last data element in the series.</returns>
        /// <exception cref="std::range_error">If the data series is empty.
        /// </exception>
        const value_type& back(void) const;

        /// <summary>
        /// Answer a pointer to the first data element.
        /// </summary>
        /// <returns>A pointer to the first value or <c>nullptr</c> if the
        /// data series is empty.</returns>
        _Ret_maybenull_ const value_type *begin(void) const noexcept;

        /// <summary>
        /// Answer a pointer to the data.
        /// </summary>
        /// <returns>A pointer to the data.</returns>
        inline _Ret_maybenull_ const value_type *data(void) const noexcept {
            return this->_data;
        }

        /// <summary>
        /// Answer whether the data series is empty.
        /// </summary>
        /// <returns><c>true</c> if the data series contains no elements,
        /// <c>false</c> otherwise.</returns>
        inline bool empty(void) const noexcept {
            return ((this->_data == nullptr) || (this->_size == 0));
        }

        /// <summary>
        /// Answer the first data element.
        /// </summary>
        /// <returns>The first data element in the series.</returns>
        /// <exception cref="std::range_error">If the data series is empty.
        /// </exception>
        const value_type& front(void) const;

        /// <summary>
        /// A pointer to the element <i>after</i> the last valid value.
        /// </summary>
        /// <returns>A pointer to the first invalid element after the data or
        /// <c>nullptr</c> if the data series is empty.</returns>
        _Ret_maybenull_ const value_type *end(void) const noexcept;

        /// <summary>
        /// Returns the <paramref name="i" />th sample in the series.
        /// </summary>
        /// <param name="i">The zero-based index of the sample to retrieve.
        /// </param>
        /// <returns>The sample at the specified position.</returns>
        /// <exception cref="std::range_error">If <paramref name="i" /> does
        /// not designate a valid sample position.</exception>
        const value_type& sample(_In_ const std::size_t i) const;

        /// <summary>
        /// Answer the name of the sensor.
        /// </summary>
        /// <returns>The name of the sensor the values are from.</returns>
        _Ret_maybenull_z_ inline const char_type *sensor(void) const noexcept {
            return this->_sensor;
        }

        /// <summary>
        /// Answer the number of values in the data series.
        /// </summary>
        /// <returns>The number of values in the data series.</returns>
        inline std::size_t size(void) const noexcept {
            return this->_size;
        }

        /// <summary>
        /// Answer whether the data series is valid.
        /// </summary>
        /// <returns><c>true</c> if the data series is valid, <c>false</c>
        /// otherwise.</returns>
        inline operator bool(void) const noexcept {
            return (this->_sensor != nullptr);
        }

    private:

        value_type *_data;
        char_type *_sensor;
        std::size_t _size;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
