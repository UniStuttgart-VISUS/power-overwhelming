// <copyright file="adl_sensor.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


/// <summary>
///  Print data for all supported AMD cards.
/// </summary>
void sample_adl_sensor(void);

/// <summary>
/// Sample all supported ADL sensors for the specified number of seconds.
/// </summary>
void sample_adl_sensor_async(const unsigned int dt);

/// <summary>
/// Sample AMD card with specific udid.
/// </summary>
void sample_adl_from_udid(const char *udid);
