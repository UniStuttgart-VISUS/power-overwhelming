// <copyright file="hmc8015_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/visa_instrument.h"

#include <string>

#include "power_overwhelming/measurement_data.h"

#include "basic_sampler_source.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="hmc8015_sensor" />.
    /// </summary>
    struct hmc8015_sensor_impl final
            : public basic_sampler_source<hmc8015_sensor_impl> {

        visa_instrument instrument;

        std::wstring sensor_name;

        inline hmc8015_sensor_impl(_In_z_ const wchar_t *path,
                _In_ const visa_instrument::timeout_type timeout)
                : instrument(path, timeout) {
            this->initialise();
        }

        inline hmc8015_sensor_impl(_In_z_ const char *path,
                _In_ const visa_instrument::timeout_type timeout)
                : instrument(path, timeout) {
            this->initialise();
        }

        void initialise(void);

        measurement_data sample(void) const;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
