// <copyright file="visa_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visa_error_category.h"

#include <string>

#include "visa_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::visa_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::visa_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, visa_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::visa_error_category::message(
        int status) const {
    ViSession rm;
    // Documentation says 256 would be OK, but most sample code uses 1K.
    ViChar retval[1024];

    if (visa_library::instance().viOpenDefaultRM(&rm) == VI_SUCCESS) {
        visa_library::instance().viStatusDesc(rm,
            static_cast<ViStatus>(status),
            retval);
        visa_library::instance().viClose(rm);
        // Documentation says that the error string is valid even if
        // viStatusDesc fails, so we just return whatever we get ...
        return retval;

    } else {
        return std::to_string(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::visa_category(
        void) noexcept {
    static const visa_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_visa_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_visa_failed(
        _In_ const ViStatus status,
        _In_opt_z_ const char *message) {
    if (status < VI_SUCCESS) {
        if (message == nullptr) {
            throw std::system_error(status, visa_category());
        } else {
            throw std::system_error(status, visa_category(), message);
        }
    }
}


///*
// * PWROWG_DETAIL_NAMESPACE::throw_unless_visa_succeeded
// */
//void PWROWG_DETAIL_NAMESPACE::throw_unless_visa_succeeded(
//        _In_ const ViStatus status,
//        _In_opt_z_ const char *message) {
//    if (status != VI_SUCCESS) {
//        if (message == nullptr) {
//            throw std::system_error(status, visa_category());
//        } else {
//            throw std::system_error(status, visa_category(), message);
//        }
//    }
//}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
