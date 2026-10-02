// <copyright file="msr_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <Windows.h>
#include <winioctl.h>

#include "visus/pwrowg/on_exit.h"


#define IOCTL_RAPL_REGISTERS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA)


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(msr_test) {

    TEST_METHOD(test_ioctl_rapl_registers) {
        auto handle = ::CreateFileW(L"\\\\.\\PowerOverwhelmingRaplMsrs\\0",
            GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, NULL);
        if (handle != INVALID_HANDLE_VALUE) {
            pwrowg_on_exit([&handle](void) { ::CloseHandle(handle); });

            {
                std::uint8_t buffer;
                ULONG returned = 0;
                Assert::IsFalse(::DeviceIoControl(handle, IOCTL_RAPL_REGISTERS, nullptr, 0, &buffer, sizeof(buffer), &returned, nullptr));
                Assert::AreEqual(int(ERROR_INSUFFICIENT_BUFFER), int(::GetLastError()), L"Buffer must at least accept one MSR", LINE_INFO());
            }

            {
                std::uint32_t buffer;
                ULONG returned = 0;
                Assert::IsFalse(::DeviceIoControl(handle, IOCTL_RAPL_REGISTERS, nullptr, 0, &buffer, sizeof(buffer), &returned, nullptr));
                Assert::AreEqual(int(ERROR_INSUFFICIENT_BUFFER), int(::GetLastError()), L"More than one MSR", LINE_INFO());
            }

            {
                std::vector<std::uint32_t> buffer(1);
                auto error = ERROR_INSUFFICIENT_BUFFER;
                ULONG returned = 0;

                while (error == ERROR_INSUFFICIENT_BUFFER) {
                    Assert::IsTrue(buffer.size() * sizeof(buffer[0]) < MAXDWORD, L"Buffer does not grow too large", LINE_INFO());
                    const auto size = static_cast<DWORD>(buffer.size() * sizeof(buffer[0]));
                    const auto success = ::DeviceIoControl(handle, IOCTL_RAPL_REGISTERS, nullptr, 0, buffer.data(), size, &returned, nullptr);
                    error = ::GetLastError();

                    if (!success) {
                        Assert::AreEqual(int(ERROR_INSUFFICIENT_BUFFER), int(error), L"Only expected error is buffer being too small", LINE_INFO());
                        buffer.resize(buffer.size() * 2);
                        ::SetLastError(ERROR_SUCCESS);
                        Assert::IsTrue(::GetLastError() == ERROR_SUCCESS, L"Error cleared", LINE_INFO());
                    }
                }

                Assert::AreEqual(int(ERROR_SUCCESS), int(error), L"Expected success after buffer is large enough.", LINE_INFO());
                Assert::IsTrue(returned % sizeof(buffer[0]) == 0, L"Returned bytes must be a multiple of the MSR size.", LINE_INFO());
                buffer.resize(returned / sizeof(buffer[0]));
                Assert::IsTrue(std::none_of(buffer.begin(), buffer.end(), [](const auto& v) { return v == 0; }), L"All MSR offsets must be non-zero.", LINE_INFO());
            }
        }
    }
};

PWROWG_TEST_NAMESPACE_END
