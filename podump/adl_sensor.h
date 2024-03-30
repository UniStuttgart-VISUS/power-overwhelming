// <copyright file="adl_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
///  Print data for all supported AMD cards.
/// </summary>
void sample_adl_sensor(void);

/// <summary>
/// Print data for all supported AMD cards using the pure sample method.
/// </summary>
void sample_adl_sensor_data(void);

/// <summary>
/// Sample all supported ADL sensors for the specified number of seconds.
/// </summary>
void sample_adl_sensor_async(const unsigned int dt);

/// <summary>
/// Sample AMD card with specific udid.
/// </summary>
void sample_adl_from_udid(const char *udid);
