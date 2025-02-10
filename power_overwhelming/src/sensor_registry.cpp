// <copyright file="sensor_registry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor_registry.h"


std::size_t PWROWG_DETAIL_NAMESPACE::sensor_registry::descriptions0(
    _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
    _In_ std::size_t cnt,
    _In_ type_list<>,
    _In_ const sensor_array_configuration_impl &);
