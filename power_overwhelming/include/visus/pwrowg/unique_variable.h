// <copyright file="unique_variable.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_UNIQUE_VARIABLE_H)
#define _PWROWG_UNIQUE_VARIABLE_H
#pragma once

#include "visus/pwrowg/macro_concat.h"


/// <summary>
/// Andrei Alexandrescu's unique variable generator.
/// </summary>
/// <param name="p">The prefix to the variable name. This must be a letter or
/// special character that is allowed as the first character in a variable name.
/// </param>
#if defined(__COUNTER__)
#define PWROWG_UNIQUE_VARIABLE(p) PWROWG_CONCAT(p, __COUNTER__)
#else /* defined(__COUNTER__) */
#define PWROWG_UNIQUE_VARIABLE(p) PWROWG_CONCAT(p, __LINE__)
#endif /* defined(__COUNTER__) */


#endif /* !defined(_PWROWG_UNIQUE_VARIABLE_H) */
