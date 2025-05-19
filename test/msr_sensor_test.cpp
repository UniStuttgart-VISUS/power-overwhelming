// <copyright file="msr_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(msr_sensor_test) {

public:

    TEST_METHOD(test_transient_service) {
        auto path = driver_path();

        if (::GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES) {
            // Note: this will fail due to missing signature on most systems.
            //detail::transient_driver d(path.c_str(), L"pwrowgrapltest");
            ::Sleep(2000);
        }
    }

    static std::wstring driver_path(void) {
        HMODULE handle;
        Assert::IsTrue(GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPWSTR>(&msr_sensor_test::driver_path),
            &handle), L"Got test DLL handle", LINE_INFO());

        wchar_t path[MAX_PATH];
        ::GetModuleFileNameW(handle, path, MAX_PATH);
        Assert::AreEqual(DWORD(0), ::GetLastError(), L"Got module path", LINE_INFO());

        std::wstring retval(path);

        auto file_start = retval.find_last_of(L'\\');
        Assert::AreNotEqual(std::wstring::npos, file_start, L"Found file", LINE_INFO());
        ++file_start;

        auto file = retval.substr(file_start);

        {
            std::wregex rx(L"([^\\.]+).+", std::wregex::icase);
            file = std::regex_replace(file, rx, L"\\\\$1\\\\");
        }

        retval.erase(file_start);
        retval += L"pwrowgrapldrv.sys";

        {
            std::wregex rx(file, std::wregex::icase);
            retval = std::regex_replace(retval, rx, L"\\pwrowgrapldrv\\");
        }

        return retval;
    }

};

PWROWG_TEST_NAMESPACE_END
