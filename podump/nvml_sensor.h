// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Print data for all supported NVIDIA cards.
/// </summary>
void sample_nvml_sensor(void);

/// <summary>
/// Sample all supported NVML sensors for the specified number of seconds.
/// </summary>
void sample_nvml_sensor_async(const unsigned int dt);
