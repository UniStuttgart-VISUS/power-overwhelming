// <copyright file="power_overwhelming_api.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


#if defined(POWER_OVERWHELMING_EXPORTS)
#define POWER_OVERWHELMING_API __declspec(dllexport)
#else /* defined(POWER_OVERWHELMING_EXPORTS) */
#define POWER_OVERWHELMING_API __declspec(dllimport)
#endif /* defined(POWER_OVERWHELMING_EXPORTS) */
