// <copyright file="emi_sensor.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


/// <summary>
/// Samples all EMI sensors once and prints their values on the console.
/// </summary>
void sample_emi_sensor(void);

/// <summary>
/// Samples all EMI sensors for the specified number of seconds.
/// </summary>
void sample_emi_sensor_async(const unsigned int dt);
