// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_sensor.h"

#include <vector>

#include "adl_exception.h"
#include "adl_sensor_impl.h"
#include "adl_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Creates sensors for all adapters matching <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate"></typeparam>
    /// <param name="predicate"></param>
    /// <returns></returns>
    template<class TPredicate>
    static std::vector<adl_sensor> for_predicate(const TPredicate& predicate) {
        std::vector<AdapterInfo> adapters;
        std::vector<adl_sensor> retval;
        adl_scope scope;

        {
            int cnt;

            auto status = detail::amd_display_library::instance()
                .ADL_Adapter_NumberOfAdapters_Get(&cnt);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }

            adapters.resize(cnt);
            retval.reserve(cnt);
        }

        for (auto& a : adapters) {
            if (predicate(a)) {
                retval.emplace_back(new detail::adl_sensor_impl(a));
            }
        }

        return retval;
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::adl_sensor::for_all
 */
std::size_t visus::power_overwhelming::adl_sensor::for_all(adl_sensor *outSensors,
        const std::size_t cntSensors) {
    try {
        int cnt = 0;
        int retval = 0;
        detail::adl_scope scope;

        {
            auto status = detail::amd_display_library::instance()
                .ADL_Adapter_NumberOfAdapters_Get(&cnt);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        if (cntSensors > 0) {
            std::vector<AdapterInfo> adapters;
            adapters.resize(retval);

            {
                auto status = detail::amd_display_library::instance()
                    .ADL_Adapter_AdapterInfo_Get(adapters.data(),
                    static_cast<int>(adapters.size() * sizeof(AdapterInfo)));
                if (status != ADL_OK) {
                    throw adl_exception(status);
                }
            }

            for (int i = 0; (i < retval) && (i < cntSensors); ++i) {
                outSensors[i] = adl_sensor(new detail::adl_sensor_impl(
                    adapters[i]));
            }

        } /* end if ((outSensors != nullptr) && (cntSensors > 0)) */

        return retval;
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::adl_sensor::from_index
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_index(const int index,
        const adl_sensor_source source) {
    adl_sensor retval;

    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(nullptr, index, &retval._impl->device);
    if (status != ADL_OK) {
        throw adl_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::adl_sensor::from_udid
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_udid(const char *udid,
        const adl_sensor_source source) {
    if (udid == nullptr) {
        throw std::invalid_argument("The unique device identifier cannot be "
            "null.");
    }

    auto retval = detail::for_predicate([&](const AdapterInfo &a) {
        return (::strcmp(udid, a.strUDID) == 0);
    });

    if (retval.size() != 1) {
        throw std::invalid_argument("The unique device identifier did not "
            "match a single device.");
    }

    return std::move(retval.front());
}


/*
 * visus::power_overwhelming::adl_sensor::adl_sensor
 */
visus::power_overwhelming::adl_sensor::adl_sensor(void)
    : _impl(new detail::adl_sensor_impl()) { }


/*
 * visus::power_overwhelming::adl_sensor::~adl_sensor
 */
visus::power_overwhelming::adl_sensor::~adl_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::adl_sensor::name
 */
const wchar_t *visus::power_overwhelming::adl_sensor::name(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->sensor_name.c_str();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::operator =
 */
visus::power_overwhelming::adl_sensor&
visus::power_overwhelming::adl_sensor::operator =(adl_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::adl_sensor::operator bool
 */
visus::power_overwhelming::adl_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}
