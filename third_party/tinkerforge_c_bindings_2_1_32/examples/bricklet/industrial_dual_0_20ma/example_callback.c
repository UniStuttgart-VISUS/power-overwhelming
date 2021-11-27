#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_0_20ma.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual 0-20mA Bricklet

// Callback function for current callback
void cb_current(uint8_t sensor, int32_t current, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Sensor: %u\n", sensor);
	printf("Current: %f mA\n", current/1000000.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDual020mA id020;
	industrial_dual_0_20ma_create(&id020, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register current callback to function cb_current
	industrial_dual_0_20ma_register_callback(&id020,
	                                         INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT,
	                                         (void (*)(void))cb_current,
	                                         NULL);

	// Set period for current (sensor 1) callback to 1s (1000ms)
	// Note: The current (sensor 1) callback is only called every second
	//       if the current (sensor 1) has changed since the last call!
	industrial_dual_0_20ma_set_current_callback_period(&id020, 1, 1000);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_0_20ma_destroy(&id020);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
