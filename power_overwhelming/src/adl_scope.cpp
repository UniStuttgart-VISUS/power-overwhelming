// <copyright file="adl_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_ADL)
#include "adl_scope.h"

#include <cassert>
#include <cstdint>

#include "adl_error_category.h"
#include "amd_display_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::adl_scope::allocate
 */
void *__stdcall PWROWG_DETAIL_NAMESPACE::adl_scope::allocate(int cnt) {
    return new (std::nothrow) std::uint8_t[cnt];
}


/*
 * PWROWG_DETAIL_NAMESPACE::adl_scope::deallocate
 */
void __stdcall PWROWG_DETAIL_NAMESPACE::adl_scope::deallocate(void **buffer) {
    assert(buffer != nullptr);
    delete static_cast<std::uint8_t *>(*buffer);
    *buffer = nullptr;
}


/*
 * PWROWG_DETAIL_NAMESPACE::adl_scope::adl_scope
 */
PWROWG_DETAIL_NAMESPACE::adl_scope::adl_scope(void) : _handle(0) {
    auto status = amd_display_library::instance().ADL2_Main_Control_Create(
        adl_scope::allocate, 1, &this->_handle);
    throw_if_adl_failed(status);
}


/*
 * PWROWG_DETAIL_NAMESPACE::adl_scope::~adl_scope
 */
PWROWG_DETAIL_NAMESPACE::adl_scope::~adl_scope(void) {
    amd_display_library::instance().ADL2_Main_Control_Destroy(this->_handle);
}

#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */
