// <copyright file="visa_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>
#include <vector>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include <visa.h>
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

#include "library_base.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#if defined(POWER_OVERWHELMING_WITH_VISA)
#define __POWER_OVERWHELMING_VISA_FUNC(f) decltype(&f) f = nullptr
#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
#define __POWER_OVERWHELMING_VISA_FUNC(f)
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// A wrapper around the Virtual Instrument Software Architecture API, which
    /// allows for loading the library at runtime.
    /// </summary>
    class visa_library final : public library_base {

    public:

        /// <summary>
        /// Gets the only instance of the class.
        /// </summary>
        /// <returns>The only instance of this class.</returns>
        /// <exception cref="std::system_error">If the library could not
        /// be loaded, eg because the VISA SDK has not been installed on the
        /// machine or the VISA DLL has not been deployed.
        /// </exception>
        static const visa_library& instance(void);

        /// <summary>
        /// Find the device strings for connected instruments matching the given
        /// search expression.
        /// </summary>
        /// <remarks>
        /// This method can be called even if the library has been compiled
        /// without support for VISA. In this case an empty result set will
        /// be returned.
        /// </remarks>
        /// <param name="expression">A search expression for VISA devices. See
        /// https://zone.ni.com/reference/en-XX/help/370131S-01/ni-visa/vifindrsrc/
        /// for details.</param>
        /// <returns>A list of matching device identifiers that can be used
        /// to open a per-instrument scope.</returns>
        /// <exception cref="visa_exception">If the operation failed.
        /// </exception>
        std::vector<std::string> find_resource(
            const char *expression = "?*") const;

        __POWER_OVERWHELMING_VISA_FUNC(viClear);
        __POWER_OVERWHELMING_VISA_FUNC(viClose);
        __POWER_OVERWHELMING_VISA_FUNC(viDisableEvent);
        __POWER_OVERWHELMING_VISA_FUNC(viDiscardEvents);
        __POWER_OVERWHELMING_VISA_FUNC(viEnableEvent);
        __POWER_OVERWHELMING_VISA_FUNC(viFindNext);
        __POWER_OVERWHELMING_VISA_FUNC(viFindRsrc);
        __POWER_OVERWHELMING_VISA_FUNC(viGetAttribute);
        __POWER_OVERWHELMING_VISA_FUNC(viInstallHandler);
        __POWER_OVERWHELMING_VISA_FUNC(viOpen);
        __POWER_OVERWHELMING_VISA_FUNC(viOpenDefaultRM);
        __POWER_OVERWHELMING_VISA_FUNC(viPrintf);
        __POWER_OVERWHELMING_VISA_FUNC(viRead);
        __POWER_OVERWHELMING_VISA_FUNC(viReadSTB);
        __POWER_OVERWHELMING_VISA_FUNC(viSetAttribute);
        __POWER_OVERWHELMING_VISA_FUNC(viSetBuf);
        __POWER_OVERWHELMING_VISA_FUNC(viStatusDesc);
        __POWER_OVERWHELMING_VISA_FUNC(viUninstallHandler);
        __POWER_OVERWHELMING_VISA_FUNC(viWaitOnEvent);
        __POWER_OVERWHELMING_VISA_FUNC(viWrite);

    private:

        visa_library(void);
    };

#undef __POWER_OVERWHELMING_VISA_FUNC

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
