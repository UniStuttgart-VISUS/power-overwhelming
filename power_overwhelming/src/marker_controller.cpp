// <copyright file="marker_controller.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/marker_controller.h"

#include "marker_sensor.h"


/*
 * PWROWG_NAMESPACE::marker_controller::emit
 */
bool PWROWG_NAMESPACE::marker_controller::emit(
        _In_ const timestamp timestamp,
        _In_ const unsigned int id) {
    return this->_sensor.emit(timestamp, id);
}


/*
 * PWROWG_NAMESPACE::marker_controller::emit
 */
bool PWROWG_NAMESPACE::marker_controller::emit(
        _In_ const timestamp timestamp,
        _Out_opt_ unsigned int *id) {
    return this->_sensor.emit(timestamp, id);
}
