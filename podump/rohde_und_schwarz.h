// <copyright file="rohde_und_schwarz.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// Query the HMC8015 power anaylser.
/// </summary>
void query_hmc8015(void);

/// <summary>
/// Query RTA4004 or RTB2004 oscilloscopes.
/// </summary>
void query_rtx(void);

/// <summary>
/// Query RTA4004 or RTB2004 oscilloscopes.
/// </summary>
void query_rtx_instrument(void);
