#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_0_20ma_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual 0-20mA Bricklet 2.0

// Callback function for current callback
void cb_current(uint8_t channel, int32_t current, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Channel: %u\n", channel);
	printf("Current: %f mA\n", current/1000000.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDual020mAV2 id020;
	industrial_dual_0_20ma_v2_create(&id020, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register current callback to function cb_current
	industrial_dual_0_20ma_v2_register_callback(&id020,
	                                            INDUSTRIAL_DUAL_0_20MA_V2_CALLBACK_CURRENT,
	                                            (void (*)(void))cb_current,
	                                            NULL);

	// Set period for current (channel 0) callback to 1s (1000ms) without a threshold
	industrial_dual_0_20ma_v2_set_current_callback_configuration(&id020, 0, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_0_20ma_v2_destroy(&id020);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
