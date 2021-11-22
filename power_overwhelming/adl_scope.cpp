// <copyright file="adl_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_scope.h"

#include <cassert>

#include "adl_exception.h"
#include "amd_display_library.h"


/*
 * visus::power_overwhelming::detail::adl_scope::allocate
 */
void *__stdcall visus::power_overwhelming::detail::adl_scope::allocate(
        int cnt) {
    return new (std::nothrow) std::uint8_t[cnt];
}


/*
 * visus::power_overwhelming::detail::adl_scope::deallocate
 */
void __stdcall visus::power_overwhelming::detail::adl_scope::deallocate(
        void **buffer) {
    assert(buffer != nullptr);
    delete static_cast<std::uint8_t *>(*buffer);
    *buffer = nullptr;
}


/*
 * visus::power_overwhelming::detail::adl_scope::adl_scope
 */
visus::power_overwhelming::detail::adl_scope::adl_scope(void) {
    if (adl_scope::_cnt++ == 0) {
        auto status = amd_display_library::instance().ADL_Main_Control_Create(
            adl_scope::allocate, 1);
        if (status == ADL_OK) {
            throw adl_exception(status);
        }
    }
}


/*
 * visus::power_overwhelming::detail::adl_scope::~adl_scope
 */
visus::power_overwhelming::detail::adl_scope::~adl_scope(void) {
    assert(adl_scope::_cnt.load() > 0);
    if (--adl_scope::_cnt == 0) {
        amd_display_library::instance().ADL_Main_Control_Destroy();
    }
}


/*
 * visus::power_overwhelming::detail::adl_scope::_cnt
 */
std::atomic<std::size_t> visus::power_overwhelming::detail::adl_scope::_cnt = 0;
