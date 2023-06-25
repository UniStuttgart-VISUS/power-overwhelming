// <copyright file="emi_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Samples all EMI sensors once and prints their values on the console.
/// </summary>
void sample_emi_sensor(void);

/// <summary>
/// Samples all EMI sensors once using the pure sampling API and prints their
/// values on the console.
/// </summary>
void sample_emi_sensor_data(void);

/// <summary>
/// Samples all EMI sensors for the specified number of seconds.
/// </summary>
void sample_emi_sensor_async(const unsigned int dt);
