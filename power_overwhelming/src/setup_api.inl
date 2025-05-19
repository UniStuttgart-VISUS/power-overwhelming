// <copyright file="setup_api.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::enumerate_device_interface
 */
template<class TCallback>
std::size_t PWROWG_DETAIL_NAMESPACE::enumerate_device_interface(
        const GUID& interface_class, TCallback callback) {
    auto hDev = SetupDiGetClassDevs(&interface_class, nullptr, NULL,
        DIGCF_DEVICEINTERFACE);
    if (hDev == INVALID_HANDLE_VALUE) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    auto guard = on_exit([hDev](void) {
        ::SetupDiDestroyDeviceInfoList(hDev);
    });

    SP_DEVICE_INTERFACE_DATA did;
    ::ZeroMemory(&did, sizeof(did));
    did.cbSize = sizeof(did);

    DWORD retval = 0;
    while(::SetupDiEnumDeviceInterfaces(hDev, nullptr, &interface_class, retval,
            &did)) {
        ++retval;
        if (!callback(hDev, did)) {
            break;
        }
    }

    {
        auto e = ::GetLastError();
        switch (e) {
            case ERROR_SUCCESS:
            case ERROR_NO_MORE_ITEMS:
                break;

            default:
                throw std::system_error(e, std::system_category());
        }
    }

    return retval;
}
#endif /* defined(_WIN32) */
