// <copyright file="measurement_data.measurement_data_series" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/measurement_data_series.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * visus::power_overwhelming::measurement_data_series::resize
 */
_Ret_maybenull_ visus::power_overwhelming::measurement_data_series::value_type *
visus::power_overwhelming::measurement_data_series::resize(
        _Inout_ measurement_data_series& series, _In_ const std::size_t size) {
    if (size == 0) {
        // If all of the data are to be truncated, deallocate the buffer.
        delete[] series._data;
        series._data = nullptr;
        series._size = 0;

    } else if (size < series._size) {
        // This is a shrink. Do not change the allocation, just pretend the size
        // is now smaller.
        series._size = size;

    } else {
        // Grow the buffer and copy the existing data to the begin of the new
        // buffer.
        auto buffer = new value_type[size];
        std::copy(series.begin(), series.end(), buffer);
        delete[] series._data;
        series._data = buffer;
        series._size = size;
    }

    return series._data;
}


/*
 * visus::power_overwhelming::measurement_data_series::measurement_data_series
 */
visus::power_overwhelming::measurement_data_series::measurement_data_series(
        _In_z_ const char_type *sensor)
        : _data(nullptr), _sensor(nullptr), _size(0) {
    if (sensor == nullptr) {
        throw std::invalid_argument("The name of the sensor must not be null.");
    }

    detail::safe_assign(this->_sensor, sensor);
}


/*
 * visus::power_overwhelming::measurement_data_series::measurement_data_series
 */
visus::power_overwhelming::measurement_data_series::measurement_data_series(
        _Inout_ measurement_data_series&& rhs) noexcept
        : _data(rhs._data), _sensor(rhs._sensor), _size(rhs._size) {
    rhs._data = nullptr;
    rhs._sensor = nullptr;
    rhs._size = 0;
}


/*
 * visus::power_overwhelming::measurement_data_series::~measurement_data_series
 */
visus::power_overwhelming::measurement_data_series::~measurement_data_series(
        void) {
    delete[] this->_data;
    delete[] this->_sensor;
}


/*
 * visus::power_overwhelming::measurement_data_series::begin
 */
_Ret_maybenull_ const visus::power_overwhelming::measurement_data_series::value_type *
visus::power_overwhelming::measurement_data_series::begin(void) const noexcept {
    return (this->_size > 0) ? this->_data : nullptr;
}


/*
 * visus::power_overwhelming::measurement_data_series::end
 */
_Ret_maybenull_ const visus::power_overwhelming::measurement_data_series::value_type *
visus::power_overwhelming::measurement_data_series::end(void) const noexcept {
    return (this->_size > 0) ? this->_data + this->_size : nullptr;
}
