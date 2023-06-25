// <copyright file="msr_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Print data for all CPU cores.
/// </summary>
void sample_msr_sensor(void);

/// <summary>
/// Print data for all CPU cores using the pure sampling API.
/// </summary>
void sample_msr_sensor_data(void);

/// <summary>
/// Sample all supported MSR sensors for the specified number of seconds.
/// </summary>
void sample_msr_sensor_async(const unsigned int dt);
