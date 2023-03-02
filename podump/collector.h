// <copyright file="collector.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


/// <summary>
/// Run the collector on all available sensors.
/// </summary>
void collect_all(const wchar_t *output, const unsigned int dt);

/// <summary>
/// Run the collector using the sensors from a configuration file.
/// </summary>
void collect_template(const wchar_t *tpl, const unsigned int dt);
