// <copyright file="visa_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_exception.h"

#include "visa_library.h"


#if defined(POWER_OVERWHELMING_WITH_VISA)
/// <summary>
/// Convert a VISA error code to an error message.
/// </summary>
/// <param name="rm"></param>
/// <param name="status"></param>
/// <returns></returns>
static std::string visa_to_string(const ViSession vi,
        const ViStatus status) {
    // Documentation says 256 would be OK, but most sample code uses 1K.
    ViChar retval[1024];
    auto& visa = visus::power_overwhelming::detail::visa_library::instance();
    visa.viStatusDesc(vi, status, retval);
    // Documentation says that the error string is valid even if viStatusDesc
    // fails, so we just return whatever we get ...
    return retval;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::visa_exception::visa_exception
 */
visus::power_overwhelming::visa_exception::visa_exception(const ViSession vi,
        const value_type code)
    : std::exception(visa_to_string(vi, code).c_str()), _code(code) { }
// TODO: Is there any way to obtain a meaningful error string from VISA?
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
