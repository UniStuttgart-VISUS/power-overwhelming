// <copyright file="emi_device.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <string>
#include <vector>

#include "setup_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private wrapper around the device handle for an EMI-capable piece of
    /// hardware.
    /// </summary>
    /// <remarks>
    /// <para>There are multiple reasons for this class existing. First, we need
    /// to manage the file handle (RAII) and ideally cache the metadata for
    /// multiple requests. Second, as EMIv2 has multiple channels per device,
    /// multiple sensors may share one device. Therefore, we want to be able to
    /// share a device between multiple sensor implementations such that we can
    /// query all channels at once in an asynchronous sampling scenario.</para>
    /// </remarks>
    class emi_device final {

#if defined(_WIN32)
    public:

        /// <summary>
        /// The type encapsulating the EMI metadata.
        /// </summary>
        typedef std::vector<std::uint8_t> metadata_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the EMI device.</param>
        explicit emi_device(const std::basic_string<TCHAR>& path);

        emi_device(const emi_device&) = delete;

        /// <summary>
        /// Initialise a new instance by moving another.
        /// </summary>
        /// <param name="rhs">The object ot be moved.</param>
        emi_device(emi_device&& rhs) noexcept;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~emi_device(void) noexcept;

        /// <summary>
        /// Answer the number of channels provided by the device.
        /// </summary>
        /// <returns>The number of channels provided by the device.</returns>
        decltype(EMI_METADATA_V2::ChannelCount) channels(void) const;

        /// <summary>
        /// Gets the EMI metadata for the device.
        /// </summary>
        /// <remarks>
        /// <para>Metadata are retrieved lazily, but cached in the
        /// object.</para>
        /// <para>The interpretation of the buffer returned is dependent on the
        /// <see cref="emi_device::version" />. For more details, see
        /// https://learn.microsoft.com/en-us/windows/win32/api/emi/ni-emi-ioctl_emi_get_metadata.
        /// </remarks>
        /// <returns>The EMI metadata.</returns>
        /// <exception cref="std::system_error">In case one of the API calls
        /// failed.</exception>
        const metadata_type& metadata(void) const;

        /// <summary>
        /// Gets the EMI metadata for the device.
        /// </summary>
        /// <remarks>
        /// No checks are performed to ensure whether the requested type matches
        /// the actual type of the metadata.
        /// </remarks>
        /// <typeparam name="TMetadata">The actual type of the metadata, which
        /// must match the version of the interface.</typeparam>
        /// <returns>The EMI metadata.</returns>
        /// <exception cref="std::system_error">In case one of the API calls
        /// failed.</exception>
        template<class TMetadata>
        inline const TMetadata *metadata_as(void) const {
            return reinterpret_cast<const TMetadata *>(this->metadata().data());
        }

        /// <summary>
        /// Gets the version of the EMI interface.
        /// </summary>
        /// <remarks>
        /// The version is retrieved lazily, but cached in the object.
        /// </remarks>
        /// <returns>The version of the EMI interface.</returns>
        /// <exception cref="std::system_error">In case one of the API calls
        /// failed.</exception>
        EMI_VERSION version(void) const;

        emi_device& operator =(const emi_device&) = delete;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        /// <returns><c>*this</c>.</returns>
        emi_device& operator =(emi_device&& rhs) noexcept;

        /// <summary>
        /// Answer whether the device handle is valid.
        /// </summary>
        /// <returns><c>true</c> if the handle is valid, <c>false</c> otherwise.
        /// </returns>
        inline operator bool(void) const noexcept {
            return (this->_handle != INVALID_HANDLE_VALUE);
        }

        /// <summary>
        /// Exposes the native file handle.
        /// </summary>
        /// <remarks>
        /// Callers must not close this handle as the object remains its owner.
        /// </remarks>
        /// <returns>The handle for the device.</returns>
        inline operator HANDLE(void) const noexcept {
            return this->_handle;
        }

    private:

        HANDLE _handle;
        mutable metadata_type _metadata;
        mutable EMI_VERSION _version;
#endif /* defined(_WIN32) */
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
