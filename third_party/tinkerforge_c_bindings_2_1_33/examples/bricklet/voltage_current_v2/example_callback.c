#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage_current_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage/Current Bricklet 2.0

// Callback function for current callback
void cb_current(int32_t current, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Current: %f A\n", current/1000.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	VoltageCurrentV2 vc;
	voltage_current_v2_create(&vc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register current callback to function cb_current
	voltage_current_v2_register_callback(&vc,
	                                     VOLTAGE_CURRENT_V2_CALLBACK_CURRENT,
	                                     (void (*)(void))cb_current,
	                                     NULL);

	// Set period for current callback to 1s (1000ms) without a threshold
	voltage_current_v2_set_current_callback_configuration(&vc, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	voltage_current_v2_destroy(&vc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
