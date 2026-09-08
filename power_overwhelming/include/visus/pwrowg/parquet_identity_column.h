// <copyright file="parquet_identity_column.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PARQUET_IDENTITY_COLUMN_H)
#define _PWROWG_PARQUET_IDENTITY_COLUMN_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Identifies the sensor property that is used as the identity column for
/// a reading in a Parquet file.
/// </summary>
enum class parquet_identity_column {

    /// <summary>
    /// Use the sensor index. This is the default and requires least memory.
    /// </summary>
    index = 0,

    /// <summary>
    /// Use the sensor ID string.
    /// </summary>
    id,

    /// <summary>
    /// Use the user-defined label. If a sensor does not have a label, the
    /// sensor ID string is used.
    /// </summary>
    label
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_PARQUET_IDENTITY_COLUMN_H) */
