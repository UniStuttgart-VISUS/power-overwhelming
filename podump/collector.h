// <copyright file="collector.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Run the collector on all available sensors.
/// </summary>
void collect_all(const wchar_t *output, const unsigned int dt);

/// <summary>
/// Run the collector using the sensors from a configuration file.
/// </summary>
void collect_template(const wchar_t *tpl, const unsigned int dt);
