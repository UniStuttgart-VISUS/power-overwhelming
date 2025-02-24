// <copyright file="udbpd.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "usbpd.h"

#include <PDTesterAPI.h>



//PDTester tester;
//// The sample says that 16 characters for the name is OK ...
//char hacknomatik[MAX_NUM_TESTERS * 16];
//char *testers[MAX_NUM_TESTERS];
//
//// Handle potential misuse of API.
//if (dst == nullptr) {
//    cnt = 0;
//}
//
//// Build the output array expected by the enumerator.
//for (std::size_t i = 0; i < MAX_NUM_TESTERS; ++i) {
//    testers[i] = hacknomatik + i * sizeof(hacknomatik) / MAX_NUM_TESTERS;
//}
//
//// Compute the point in time where we give up finding devices.
//const auto deadline = std::chrono::steady_clock::now()
//+ std::chrono::milliseconds(config.timeout());
//
//// Find the PD testers attached to the system. Note: If this does not find
//// anything although a device has been attached, the software probably
//// crashed before and did not disconnect properly. The PD tester needs to be
//// power cycled in this case.
//do {
//    retval = tester.GetConnectedDevices(testers);
//    // Another magic number from the sample for the sleep here ...
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//} while ((retval < 1) && (deadline < std::chrono::steady_clock::now()));
//
