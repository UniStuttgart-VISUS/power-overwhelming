// <copyright file="lpt_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <conio.h>
#include <Windows.h>
#include <tchar.h>

#include <wil/resource.h>
#include <wil/result.h>

#include <visus/pwrowg/string_functions.h>
#include <visus/pwrowg/timestamp.h>


/// <summary>
/// Describes the current test run.
/// </summary>
struct test_run final {
    wil::unique_event event;
    std::ofstream output;
    std::atomic<bool> running;
    visus::pwrowg::timestamp write_start;
    visus::pwrowg::timestamp write_end;
};


/// <summary>
/// Reads from the specified LPT port and logs the result.
/// </summary>
void read_port(_In_ const std::basic_string<TCHAR>& path, _In_ test_run& test) {
    typedef std::chrono::duration<float, std::milli> millis;
    wil::unique_hfile port(CreateFile(path.c_str(), GENERIC_READ, 0, nullptr,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
    THROW_LAST_ERROR_IF(!port);

    char data;
    DWORD read;

    while (test.running.load(std::memory_order_acquire)) {
        THROW_LAST_ERROR_IF(!::ReadFile(port.get(), &data, sizeof(data),
            &read, nullptr));
        const auto read_time = visus::pwrowg::timestamp::now();
        assert(read == 1);

        const auto write_time = visus::pwrowg::timestamp::middle(
            test.write_start, test.write_end);
        const auto elapsed = std::chrono::duration_cast<millis>(
            read_time - write_time);

        test.output
            << test.write_start.value() << ","
            << test.write_end.value() << ","
            << write_time.value() << ","
            << data << ","
            << read_time.value() << ","
            << elapsed.count() << ","
            << std::endl;

        test.event.SetEvent();
    }
}

/// <summary>
/// Writes to the specified LPT port.
/// </summary>
/// <param name="path"></param>
/// <param name="test"></param>
void write_port(_In_ const std::basic_string<TCHAR>& path,
        _In_ test_run& test) {
    wil::unique_hfile port(CreateFile(path.c_str(), GENERIC_WRITE, 0, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
    THROW_LAST_ERROR_IF(!port);

    char data = 'a';
    DWORD written;

    while (test.running.load(std::memory_order_acquire)) {
        test.event.wait();

        test.write_start = visus::pwrowg::timestamp::now();
        THROW_LAST_ERROR_IF(!::WriteFile(port.get(), &data, sizeof(data),
            &written, nullptr));
        test.write_end = visus::pwrowg::timestamp::now();
        assert(written == 1);

        if (++data > 'z') {
            data = 'a';
        }
    }
}


/// <summary>
/// Entry point of the lpt_test application, which writes from one LPT port to
/// another, measuring latency.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;

    std::wcout << L"lpt_test" << std::endl;
    std::wcout << L"© 2026 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << L"All rights reserved."
        << std::endl << std::endl;

    std::basic_string<TCHAR> output_path;
    std::basic_string<TCHAR> source_port;
    std::basic_string<TCHAR> target_port;

    {
        auto end = argv + argc;
        auto it = std::find_if(argv, end, [](const TCHAR *a) {
            return visus::pwrowg::detail::equals(a, _T("/output"), true);
        });

        if ((it != end) && (++it != end)) {
            output_path = *it;
        }
    }

    {
        auto end = argv + argc;
        auto it = std::find_if(argv, end, [](const TCHAR *a) {
            return visus::pwrowg::detail::equals(a, _T("/source"), true);
        });

        if ((it != end) && (++it != end)) {
            source_port = *it;
        }
    }

    {
        auto end = argv + argc;
        auto it = std::find_if(argv, end, [](const TCHAR *a) {
            return visus::pwrowg::detail::equals(a, _T("/target"), true);
        });

        if ((it != end) && (++it != end)) {
            target_port = *it;
        }
    }

    if (output_path.empty() || source_port.empty() || target_port.empty()) {
        return -2;
    }

    try {
        wil::unique_hfile port(CreateFile(source_port.c_str(), GENERIC_READ, 0,
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
        THROW_LAST_ERROR_IF(!port);

        test_run test;
        test.event.create();
        test.running.store(true, std::memory_order_release);
        test.output.open(output_path, std::ios::trunc);

        test.output << "write_start,write_end,write_time,data,read_time,"
            << "elapsed" << std::endl;

        std::thread reader(read_port, target_port, std::ref(test));
        std::thread writer(write_port, source_port, std::ref(test));

        std::wcout << L"Press any key to stop the test..." << std::endl;
        ::_getch();
        test.running.store(false, std::memory_order_release);

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
