// <copyright file="tinkerforge.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Print values of all Tinkerforge bricklets, obtained via for_all.
/// </summary>
void sample_all_tinkerforge_sensors(void);

/// <summary>
/// Print values of all Tinkerforge bricklets attached to the machine.
/// </summary>
void sample_tinkerforge_sensor(void);

/// <summary>
/// Print values of all Tinkerforge bricklets attached to the machine using the
/// pure sampling API.
/// </summary>
void sample_tinkerforge_sensor_data(void);

/// <summary>
/// Samples all Tinkerforge bricklets attached to the machine for the specified
/// time span.
/// </summary>
void sample_tinkerforge_sensor_async(const unsigned int dt);

/// <summary>
/// Samples all Tinkerforge bricklets attached to the machine for the specified
/// time span.
/// </summary>
void sample_tinkerforge_power_async(const unsigned int dt);

/// <summary>
/// Print text on a Tinkerforge LCD.
/// </summary>
/// <param name="text"></param>
void print_tinkerforge_display(const char *text = "Power overwhelming!");
