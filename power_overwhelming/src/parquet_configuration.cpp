// <copyright file="parquet_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/parquet_configuration.h"

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::parquet_configuration::parquet_configuration
 */
PWROWG_NAMESPACE::parquet_configuration::parquet_configuration(
        _In_z_ const wchar_t *path,
        _In_ const parquet_identity_column identity)
        : _identity(identity), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the Parquet file must "
            "be specified.");
    }

    auto p = convert_string<char>(path);
    detail::safe_assign(this->_path, p);
}


/*
 * PWROWG_NAMESPACE::parquet_configuration::parquet_configuration
 */
PWROWG_NAMESPACE::parquet_configuration::parquet_configuration(
        _In_z_ const char *path,
        _In_ const parquet_identity_column identity)
        : _identity(identity), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the Parquet file must "
            "be specified.");
    }

    detail::safe_assign(this->_path, path);
}


/*
 * PWROWG_NAMESPACE::parquet_configuration::parquet_configuration
 */
PWROWG_NAMESPACE::parquet_configuration::parquet_configuration(
        _In_z_ const wchar_t *path)
    : parquet_configuration(path, parquet_identity_column::index) { }


/*
 * PWROWG_NAMESPACE::parquet_configuration::parquet_configuration
 */
PWROWG_NAMESPACE::parquet_configuration::parquet_configuration(
        _In_z_ const char *path)
    : parquet_configuration(path, parquet_identity_column::index) { }


/*
 * PWROWG_NAMESPACE::parquet_configuration::string_identity
 */
bool PWROWG_NAMESPACE::parquet_configuration::string_identity(
        void) const noexcept {
    switch (this->_identity) {
        case parquet_identity_column::index:
            return false;

        case parquet_identity_column::id:
        case parquet_identity_column::label:
        default:
            return true;
    }
}
