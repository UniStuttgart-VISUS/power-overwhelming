// <copyright file="nvapi_util.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_util.h"

#include "nvapi_error_category.h"


/*
 * PWROWG_DETAIL_NAMESPACE::set_nvapi_identity
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::set_nvapi_identity(
        _In_ sensor_description_builder& builder,
        _In_ NvPhysicalGpuHandle gpu,
        _In_z_ const wchar_t *id_prefix) {
    assert(id_prefix != nullptr);
    NvU32 bus_id = 0;
    NvU32 device_id = 0;
    NvU32 ext_device_id = 0;
    NvU32 revision_id = 0;
    NvU32 sub_system_id = 0;
    NvU32 slot_id = 0;

    // Pass on the handle to the sensor.
    builder.with_private_data(gpu);

    // Get some info about the GPU to create a unique ID.
    throw_if_nvapi_failed(nvapi_library::instance()
        ._nvapi_get_gpu_bus_id(&bus_id, gpu));
    throw_if_nvapi_failed(nvapi_library::instance()
        ._nvapi_get_gpu_pci_identifiers(&device_id, &sub_system_id,
            &revision_id, &ext_device_id, gpu));
    throw_if_nvapi_failed(nvapi_library::instance()
        ._nvapi_get_gpu_slot_id(&slot_id, gpu));

    // Set the ID strings.
    builder.with_path(L"%x.%x.%x.%x:%u.%u", device_id,
        ext_device_id, revision_id, sub_system_id, slot_id, bus_id);
    builder.with_id(L"%s/%x.%x.%x.%x:%u.%u", id_prefix, device_id,
        ext_device_id, revision_id, sub_system_id, slot_id, bus_id);

    return builder;
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
