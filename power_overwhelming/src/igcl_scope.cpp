// <copyright file="igcl_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_scope.h"

#include "igcl_library.h"
#include "igcl_error_category.h"


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_scope::igcl_scope
 */
PWROWG_DETAIL_NAMESPACE::igcl_scope::igcl_scope(void) : _args { } {
    this->_args.Size = sizeof(this->_args);
    this->_args.AppVersion= CTL_IMPL_VERSION;
    auto status = igcl_library::instance()._ctlInit(&this->_args,
        &this->_handle);
    throw_if_igcl_failed(status);
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_scope::~igcl_scope
 */
PWROWG_DETAIL_NAMESPACE::igcl_scope::~igcl_scope(void) {
    igcl_library::instance()._ctlClose(this->_handle);
}
#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
