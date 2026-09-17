    // <copyright file="hdf5_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hdf5_configuration.h"

#include <map>
#include <string>
#include <stdexcept>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration
 */
PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration(
        _In_z_ const wchar_t *path,
        _In_ const bool overwrite)
        : _chunk_size(1024), _overwrite(overwrite), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the HDF5 file must "
            "be specified.");
    }

    this->_meta_data.emplace<std::map<std::string, std::string>>();

    auto p = convert_string<char>(path);
    detail::safe_assign(this->_path, p);

}


/*
 * PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration
 */
PWROWG_NAMESPACE::hdf5_configuration::hdf5_configuration(
        _In_z_ const char *path,
        _In_ const bool overwrite)
        : _chunk_size(1024), _overwrite(overwrite), _raw(false) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid path for the HDF5 file must "
            "be specified.");
    }

    detail::safe_assign(this->_path, path);

    this->_meta_data.emplace<std::map<std::string, std::string>>();
}


/*
 * PWROWG_NAMESPACE::hdf5_configuration::meta_data
 */
std::size_t PWROWG_NAMESPACE::hdf5_configuration::meta_data(
        _Out_writes_opt_(cnt) const char **keys,
        _In_ std::size_t cnt) const noexcept {
    auto retval = this->_meta_data.get<std::map<std::string, std::string>>();
    if (retval == nullptr) {
        return 0;
    }

    // Fix nonsensical input.
    if (keys == nullptr) {
        cnt = 0;
    }

    if (cnt >= retval->size()) {
        std::transform(retval->begin(), retval->end(), keys,
            [](const auto& item) { return item.first.c_str(); });
    }

    return retval->size();
}


/*
 * PWROWG_NAMESPACE::hdf5_configuration::meta_data
 */
_Ret_maybenull_z_ const char *PWROWG_NAMESPACE::hdf5_configuration::meta_data(
        _In_z_ const char *key) const noexcept {
    if (key == nullptr) {
        return nullptr;
    }

    auto map = this->_meta_data.get<std::map<std::string, std::string>>();
    if (map == nullptr) {
        return nullptr;
    }

    auto it = map->find(key);
    return (it != map->end()) ? it->second.c_str() : nullptr;
}


/*
 * PWROWG_NAMESPACE::hdf5_configuration::meta_data
 */
PWROWG_NAMESPACE::hdf5_configuration&
PWROWG_NAMESPACE::hdf5_configuration::meta_data(_In_z_ const char *key,
        _In_z_ const char *value) {
    if ((key == nullptr) || (*key == 0)) {
        throw std::invalid_argument("A valid key is required.");
    }

    auto map = this->_meta_data.get<std::map<std::string, std::string>>();
    if (map == nullptr) {
        map = &this->_meta_data.emplace<std::map<std::string, std::string>>();
    }
    assert(map != nullptr);

    (*map)[key] = (value != nullptr) ? value : "";

    return *this;
}
