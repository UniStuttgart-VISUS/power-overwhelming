// <copyright file="visa_scope_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_scope_impl.h"

#include <stdexcept>

#include "visa_library.h"


/*
 * visus::power_overwhelming::detail::visa_scope_impl::visa_scope_impl
 */
visus::power_overwhelming::detail::visa_scope_impl::visa_scope_impl(
        const std::string& path, const std::uint32_t timeout)
        : resource_manager(0), session(0) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    {
        auto status = visa_library::instance().viOpenDefaultRM(
            &this->resource_manager);
        if (status < VI_SUCCESS) {
            throw visa_exception(status, "The VISA default resource manager "
                "could not be opened.");
        }
    }

    {
        auto status = visa_library::instance().viOpen(this->resource_manager,
            path.c_str(), 0, timeout, &this->session);
        if (status < VI_SUCCESS) {
            visa_library::instance().viClose(this->resource_manager);
            throw visa_exception(status);
        }
    }

        //CHECKERR(viOpenDefaultRM(&defaultRM))
        //CHECKERR(viOpen(defaultRM, (ViRsrc) resource, 0, 3000, io))
        //CHECKERR(viSetAttribute(*io, VI_ATTR_USER_DATA_32, defaultRM))
        //CHECKERR(viClear(*io))

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error("The library was compiled without support for the "
        "Virtual Instrument Software Architecture.");
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_scope_impl::~visa_scope_impl
 */
visus::power_overwhelming::detail::visa_scope_impl::~visa_scope_impl(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    visa_library::instance().viClose(this->session);
    visa_library::instance().viClose(this->resource_manager);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}
