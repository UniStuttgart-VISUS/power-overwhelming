// <copyright file="graphics_device.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cstddef>

//#define POWER_OVERWHELIMG_FORCE_D3D11

#if defined(_WIN32)
#include <winsdkver.h>

#if (defined(_WIN32_MAXVER) && (_WIN32_MAXVER >= 0x0A00) && !defined(POWER_OVERWHELIMG_FORCE_D3D11))
#include <d3d12.h>
#include <dxgi1_4.h>

#define POWER_OVERWHELMING_GPU_ABSTRACTION (12)
#define POWER_OVERWHELMING_NATIVE_ADAPTER_TYPE IDXGIAdapter
#define POWER_OVERWHELMING_NATIVE_DEVICE_TYPE ID3D12Device
#define POWER_OVERWHALMING_NATIVE_FACTORY_TYPE IDXGIFactory4

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "windowscodecs.lib")

#else /* (defined(_WIN32_MAXVER) && (_WIN32_MAXVER >= 0x0A00) ... */
#include <d3d11.h>
#include <dxgi.h>

#define POWER_OVERWHELMING_GPU_ABSTRACTION (11)
#define POWER_OVERWHELMING_NATIVE_ADAPTER_TYPE IDXGIAdapter
#define POWER_OVERWHELMING_NATIVE_DEVICE_TYPE ID3D11Device
#define POWER_OVERWHALMING_NATIVE_FACTORY_TYPE IDXGIFactory1

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "windowscodecs.lib")

#endif /* (defined(_WIN32_MAXVER) && (_WIN32_MAXVER >= 0x0A00) ... */

#include <Windows.h>
#include <wincrypt.h>

#pragma comment(lib, "crypt32.lib")

#else /* defined(_WIN32) */
#define POWER_OVERWHELMING_GPU_ABSTRACTION (0)
#define POWER_OVERWHELMING_NATIVE_ADAPTER_TYPE void
#define POWER_OVERWHELMING_NATIVE_DEVICE_TYPE void
#define POWER_OVERWHALMING_NATIVE_FACTORY_TYPE void

#endif /* defined(_WIN32) */

#include "power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// An abstraction of a GPU in the system, which can be used to generate
    /// artifical load and to put the device into a stable power state, ie to
    /// diable GPU boost.
    /// </summary>
    class POWER_OVERWHELMING_API graphics_device final {

    public:

        /// <summary>
        /// The native adapter handle used by the abstraction.
        /// </summary>
        typedef POWER_OVERWHELMING_NATIVE_ADAPTER_TYPE adapter_type;

        /// <summary>
        /// The native device handle used by the abstraction.
        /// </summary>
        typedef POWER_OVERWHELMING_NATIVE_DEVICE_TYPE device_type;

        /// <summary>
        /// The native DXGI factory used by the abstraction to enumerate the
        /// devices.
        /// </summary>
        typedef POWER_OVERWHALMING_NATIVE_FACTORY_TYPE factory_type;

        /// <summary>
        /// Create instances for all GPUs in the device.
        /// </summary>
        /// <param name="outDevices">Receives the device objects, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cntDevices">The available space in
        /// <paramref name="outDevices" />.</param>
        /// <param name="onlyHardware">If <c>true</c>, which is the default,
        /// return only hardware devices and exclude software emulation like
        /// WARP devices.</param>
        /// <returns>The number of devices available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="outDevices" />, not all devices have been returned.
        /// </returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="outDevices" /> is <c>nullptr</c>, but
        /// <paramref name="cntDevices" /> is not zero.</exception>
        /// <exception cref="std::system_error">If the devices could not be
        /// enumerated due to an error in the underlying APIs.</exception>
        static std::size_t all(graphics_device *outDevices,
            const std::size_t cntDevices, const bool onlyHardware = true);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This instance does not represent an actual device and cannot be used
        /// for anything. Use the static factory function to retrieve an actual
        /// device abstraction.
        /// </remarks>
        graphics_device(void) noexcept;

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        graphics_device(const graphics_device& rhs);

        /// <summary>
        /// Move <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        graphics_device(graphics_device&& rhs) noexcept;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~graphics_device(void);

        /// <summary>
        /// Gets a unique identifier for the device.
        /// </summary>
        /// <returns>The ID of the device. The object remains owner of
        /// the memory returned. The returned pointer may be <c>nullptr</c>, eg
        /// if called on an invalid device.</returns>
        /// <exception cref="std::bad_alloc">If the there was not enough memory
        /// to store the device ID.</exception>
        /// <exception cref="std::system_error">If the device ID could not be
        /// determines.</exception>
        inline const wchar_t *id(void) const {
            this->assert_id_and_name();
            return this->_id;
        }

        /// <summary>
        /// Gets the human-readable name of the device.
        /// </summary>
        /// <returns>The name of the device. The object remains owner of
        /// the memory returned. The returned pointer may be <c>nullptr</c>, eg
        /// if called on an invalid device.</returns>
        /// <exception cref="std::bad_alloc">If the there was not enough memory
        /// to store the device name.</exception>
        /// <exception cref="std::system_error">If the device name could not be
        /// determines.</exception>
        inline const wchar_t *name(void) const {
            this->assert_id_and_name();
            return this->_name;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        graphics_device operator =(const graphics_device& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        graphics_device operator =(graphics_device&& rhs) noexcept;

        /// <summary>
        /// Determines whether the device is valid.
        /// </summary>
        /// <returns><c>true</c> if the device is valid, <c>false</c>
        /// otherwise.</returns>
        operator bool(void) const noexcept;

        /// <summary>
        /// Exposes the native device type.
        /// </summary>
        /// <remarks>
        /// The reference count is not incremented by this operator. If the
        /// caller wishes to keep the return value, it must increment the
        /// reference count by itself.
        /// </remarks>
        /// <returns>The underlying native device.</returns>
        inline operator device_type *(void) noexcept {
            return this->_device;
        }

    private:

        void assert_id_and_name(void) const;

        adapter_type *_adapter;
        device_type *_device;
        mutable wchar_t *_id;
        mutable wchar_t *_name;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
