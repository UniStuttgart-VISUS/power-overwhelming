// <copyright file="msr_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/msr_configuration.h"

#include "string_functions.h"

/*
 * PWROWG_NAMESPACE::msr_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::msr_configuration::id(
    0x144D90FD, 0xAF00, 0x4E88, 0xAF32, 0x05, 0x33, 0x0A, 0xCD, 0x2B, 0x20);


/*
 * PWROWG_NAMESPACE::msr_configuration::start_driver
 */
PWROWG_NAMESPACE::msr_configuration&
PWROWG_NAMESPACE::msr_configuration::start_driver(_In_z_ const wchar_t *path,
        _In_opt_z_ const wchar_t *name) {
    detail::safe_assign(this->_driver_name, name);
    detail::safe_assign(this->_driver_path, path);
    return *this;
}
