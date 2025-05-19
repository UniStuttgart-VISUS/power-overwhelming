// <copyright file="rohde_und_schwarz.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Query the HMC8015 power analyser.
/// </summary>
void query_hmc8015(void);

/// <summary>
/// Query RTA4004 or RTB2004 oscilloscopes.
/// </summary>
void query_rtx_instrument(void);

/// <summary>
/// Apply the configuration builder to RTA4004 or RTB2004 oscilloscopes.
/// </summary>
void configure_rtx_instrument(void);
