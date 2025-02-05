// <copyright file="sensor_description_builder.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_DESCRIPTION_BUILDER_H)
#define _PWROWG_SENSOR_DESCRIPTION_BUILDER_H
#pragma once

#include "visus/pwrowg/sensor_description.h"

#include "string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A builder class for <see cref="sensor_description" />.
/// </summary>
class POWER_OVERWHELMING_API sensor_description_builder final {

public:

    /// <summary>
    /// Gets, if any, the private data stored in <paramref name="desc" />.
    /// </summary>
    /// <remarks>
    /// The caller must known the correct type of the private data. No check will
    /// be performed to prevent invalid casts.
    /// </remarks>
    /// <typeparam name="TType">The type of the data stored in
    /// <paramref name="desc" />.</typeparam>
    /// <param name="desc">The sensor description to retrieve the private data
    /// from.</param>
    /// <returns>A pointer to the private data if anything has been stored in
    /// <paramref name="desc" />.</returns>
    template<class TType>
    static TType *private_data(_In_ sensor_description& desc) {
        return desc._private.get<TType>();
    }

    /// <summary>
    /// Gets, if any, the private data stored in <paramref name="desc" />.
    /// </summary>
    /// <remarks>
    /// The caller must known the correct type of the private data. No check will
    /// be performed to prevent invalid casts.
    /// </remarks>
    /// <typeparam name="TType">The type of the data stored in
    /// <paramref name="desc" />.</typeparam>
    /// <param name="desc">The sensor description to retrieve the private data
    /// from.</param>
    /// <returns>A pointer to the private data if anything has been stored in
    /// <paramref name="desc" />.</returns>
    template<class TType>
    static const TType *private_data(_In_ const sensor_description& desc) {
        return desc._private.get<TType>();
    }

    /// <summary>
    /// Create a new builder.
    /// </summary>
    /// <returns>A new builder.</returns>
    static inline sensor_description_builder create(void) {
        return sensor_description_builder();
    }

    /// <summary>
    /// Answer the description that has been built so far.
    /// </summary>
    /// <remarks>
    /// The builder will return a new description, but keep the state of the
    /// description built so far, which enables sensor implementations to create
    /// multiple similar descriptions by only changing subsets of properties.
    /// </remarks>
    /// <returns>The description that has been created.</returns>
    inline sensor_description build(void) {
        return this->_desc;
    }

    /// <summary>
    /// Configures the unit of measurement produced by the sensor.
    /// </summary>
    /// <param name="unit">The unit produced by the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description_builder& measured_in(_In_ const reading_unit unit);

    /// <summary>
    /// Configures the type of data produced by the sensor.
    /// </summary>
    /// <param name="type">The type of data produced by the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description_builder& produces(_In_ const reading_type type);

    /// <summary>
    /// Configure the description with the given unique sensor ID.
    /// </summary>
    /// <param name="id">A unique ID for the sensor in the description.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="id" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_id(_In_z_ const wchar_t *id);

    /// <summary>
    /// Configure the description with the given unique sensor ID.
    /// </summary>
    /// <param name="id">A unique ID for the sensor in the description.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="id" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_id(_In_z_ const char *id);

    /// <summary>
    /// Configure the user-defined label for the sensor.
    /// </summary>
    /// <param name="label">An optional label for the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description_builder& with_label(_In_opt_z_ const wchar_t *label);

    /// <summary>
    /// Configure the description with the given human-readable sensor name.
    /// </summary>
    /// <param name="name">A name for the sensor in the description.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_name(_In_z_ const wchar_t *name);

    /// <summary>
    /// Configure the description with the given human-readable sensor name.
    /// </summary>
    /// <param name="name">A name for the sensor in the description.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_name(_In_z_ const char *name);

    /// <summary>
    /// Format the humand-readable sensor name in the description.
    /// </summary>
    /// <typeparam name="TArgs">The types of the arguments to be formatted.
    /// </typeparam>
    /// <param name="format">The printf-style format string.</param>
    /// <param name="args">The arguments to be formatted.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="format" /> is
    /// <c>nullptr</c>.</exception>
    template<class... TArgs> sensor_description_builder& with_name(
            _In_z_ const wchar_t *format,
            _In_ TArgs&&... args) {
        const auto name = format_string(format, std::forward<TArgs>(args)...);
        return this->with_name(name.c_str());
    }

    /// <summary>
    /// Format the humand-readable sensor name in the description.
    /// </summary>
    /// <typeparam name="TArgs">The types of the arguments to be formatted.
    /// </typeparam>
    /// <param name="format">The printf-style format string.</param>
    /// <param name="args">The arguments to be formatted.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="format" /> is
    /// <c>nullptr</c>.</exception>
    template<class... TArgs> sensor_description_builder& with_name(
            _In_z_ const char *format,
            _In_ TArgs&&... args) {
        const auto name = format_string(format, std::forward<TArgs>(args)...);
        return this->with_name(name.c_str());
    }

    /// <summary>
    /// Configure the device path of the sensor in the description.
    /// </summary>
    /// <param name="path">The unique sensor path.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_path(_In_z_ const wchar_t *path);

    /// <summary>
    /// Configure the device path of the sensor in the description.
    /// </summary>
    /// <param name="path">The unique sensor path.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <c>nullptr</c>.</exception>
    sensor_description_builder& with_path(_In_z_ const char *path);

    /// <summary>
    /// Add the given <paramref name="data" /> as private data to be used by the
    /// sensor.
    /// </summary>
    /// <remarks>
    /// <para>This field is typically used for sensors to store additional data
    /// required to reconstruct a sensor from a
    /// <see cref="sensor_description" />.</para>
    /// <para>Callers can use the <see cref="private_data" /> method to get
    /// access to this object later on.</para>
    /// </remarks>
    /// <typeparam name="TType">The type of the data to be stored.</typeparam>
    /// <param name="data">The data to be stored.</param>
    /// <returns><c>*this</c>.</returns>
    template<class TType>
    sensor_description_builder& with_private_data(_In_ const TType& data) {
        this->_desc._private = type_erased_storage(data);
        return *this;
    }

    /// <summary>
    /// Sets the type of sensor described here.
    /// </summary>
    /// <param name="type">The type of the sensor.</param>
    /// <param name="editable">The parts of <paramref name="type" /> that the
    /// user is allowed to edit. This defaults to nothing.</param>
    /// <returns><c>*this</c>.</returns>
    inline sensor_description_builder& with_type(_In_ const sensor_type type,
        _In_ const sensor_type editable = sensor_type::unknown);

    /// <summary>
    /// Configure the device vendor.
    /// </summary>
    /// <param name="vendor">The vendor of the sensor or monitore
    /// device.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description_builder& with_vendor(_In_opt_z_ const wchar_t *vendor);

private:

    sensor_description _desc;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_DESCRIPTION_BUILDER_H) */
