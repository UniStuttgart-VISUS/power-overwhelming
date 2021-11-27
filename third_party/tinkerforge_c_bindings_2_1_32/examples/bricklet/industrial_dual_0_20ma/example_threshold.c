#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_0_20ma.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual 0-20mA Bricklet

// Callback function for current reached callback
void cb_current_reached(uint8_t sensor, int32_t current, void *user_data) {
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

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	industrial_dual_0_20ma_set_debounce_period(&id020, 10000);

	// Register current reached callback to function cb_current_reached
	industrial_dual_0_20ma_register_callback(&id020,
	                                         INDUSTRIAL_DUAL_0_20MA_CALLBACK_CURRENT_REACHED,
	                                         (void (*)(void))cb_current_reached,
	                                         NULL);

	// Configure threshold for current (sensor 1) "greater than 10 mA"
	industrial_dual_0_20ma_set_current_callback_threshold(&id020, 1, '>', 10*1000000, 0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_0_20ma_destroy(&id020);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
