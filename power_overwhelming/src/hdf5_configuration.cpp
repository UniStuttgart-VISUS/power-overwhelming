// <copyright file="hdf5_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hdf5_configuration.h"

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration
 */
PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration(
        _In_z_ const wchar_t *path,
        _In_ const bool overwrite)
        : _chunk_size(1024), _overwrite(_overwrite), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the HDF5 file must "
            "be specified.");
    }

    auto p = convert_string<char>(path);
    detail::safe_assign(this->_path, p);
}


/*
 * PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration
 */
PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration(
        _In_z_ const char *path,
        _In_ const bool overwrite)
        : _chunk_size(1024), _overwrite(_overwrite), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the HDF5 file must "
            "be specified.");
    }

    detail::safe_assign(this->_path, path);
}
