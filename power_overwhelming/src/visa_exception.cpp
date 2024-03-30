// <copyright file="visa_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_exception.h"

#include "visa_library.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Convert a VISA error code to an error message.
    /// </summary>
    /// <param name="rm"></param>
    /// <param name="status"></param>
    /// <returns></returns>
    static std::string visa_to_string(const visa_exception::value_type status) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
        ViSession rm;
        // Documentation says 256 would be OK, but most sample code uses 1K.
        ViChar retval[1024];

        if (visa_library::instance().viOpenDefaultRM(&rm) == VI_SUCCESS) {
            visa_library::instance().viStatusDesc(rm, status, retval);
            visa_library::instance().viClose(rm);
            // Documentation says that the error string is valid even if
            // viStatusDesc fails, so we just return whatever we get ...
            return retval;

        } else {
            return std::to_string(status);
        }

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
        return std::to_string(status);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::visa_exception::throw_on_error
 */
void visus::power_overwhelming::visa_exception::throw_on_error(
        const value_type status) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    if (status < VI_SUCCESS) {
        throw visa_exception(status);
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::visa_exception::throw_unless_succeeded
 */
void visus::power_overwhelming::visa_exception::throw_unless_succeeded(
        const value_type status) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    if (status != VI_SUCCESS) {
        throw visa_exception(status);
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::visa_exception::visa_exception
 */
visus::power_overwhelming::visa_exception::visa_exception(const value_type code)
    : std::runtime_error(detail::visa_to_string(code).c_str()), _code(code) { }
