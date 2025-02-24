// <copyright file="udbpd.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "usbpd.h"

#include <chrono>
#include <cstring>
#include <memory>
#include <thread>

#include <PDTesterAPI.h>


/// <summary>
/// A callback which we do not know what it is good for, because the sample does
/// not use it either. However, it cannot be empty.
/// </summary>
/// <param name="event_code"></param>
static void event_callback(const int event_code) { }


/*
 * usb_pd_tester_close
 */
void usb_pd_tester_close(usb_pd_tester tester) {
    delete tester;
}


/*
 * ::usb_pd_tester_enumerate
 */
char *usb_pd_tester_enumerate(const std::size_t timeout,
        const std::size_t wait) {
    // The sample says that 16 characters for the name is OK ...
    constexpr std::size_t max_len = 16;

    PDTester tester;
    char hacknomatik[MAX_NUM_TESTERS * max_len];
    char *testers[MAX_NUM_TESTERS];

    // Build the output array expected by the enumerator.
    for (std::size_t i = 0; i < MAX_NUM_TESTERS; ++i) {
        testers[i] = hacknomatik + i * sizeof(hacknomatik) / MAX_NUM_TESTERS;
        testers[i][0] = 0;
    }

    // Compute the point in time where we give up finding devices.
    const auto deadline = std::chrono::steady_clock::now()
        + std::chrono::milliseconds(timeout);

    // Find the PD testers attached to the system. Note: If this does not find
    // anything although a device has been attached, the software probably
    // crashed before and did not disconnect properly. The PD tester needs to be
    // power cycled in this case.
    do {
        auto cnt = tester.GetConnectedDevices(testers);

        if (cnt > 0) {
            // Measure how much memory we need to allocate for the return value.
            std::size_t size = 1;
            for (int i = 0; i < cnt; ++i) {
                size += ::strnlen_s(testers[i], max_len) + 1;
            }

            // Copy the paths to the output buffer.
            auto retval = new char[size];
            auto dst = retval;
            for (int i = 0; i < cnt; ++i) {
                auto src = testers[i];
                while ((*dst++ = *src++) != 0);
            }
            *dst = 0;

            return retval;
        }

        // Another magic number from the sample for the sleep here ...
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    } while (deadline < std::chrono::steady_clock::now());

    return nullptr;
}

/*
 * ::usb_pd_tester_free
 */
void usb_pd_tester_free(char *dst) {
    delete[] dst;
}


/*
 * ::usb_pd_tester_open
 */
usb_pd_tester usb_pd_tester_open(const char *path) {
    if (path == nullptr) {
        return nullptr;
    }

    auto retval = std::make_unique<PDTester>();
    if (retval->Connect(const_cast<char *>(path), event_callback)) {
        return retval.release();
    } else {
        return nullptr;
    }
}


/*
 * ::usb_pd_tester_query
 */
bool usb_pd_tester_query(usb_pd_tester tester,
        std::uint8_t *temperature,
        std::uint16_t *voltage,
        std::uint16_t *set_current,
        std::uint16_t *current,
        std::uint16_t *loopback_current) {
    if (tester == nullptr) {
        return false;
    }

    return (tester->GetStatistics(temperature,
        voltage,
        set_current,
        current,
        loopback_current) != FALSE);
}
