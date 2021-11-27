#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage_current.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage/Current Bricklet

// Callback function for power reached callback
void cb_power_reached(int32_t power, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Power: %f W\n", power/1000.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	VoltageCurrent vc;
	voltage_current_create(&vc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	voltage_current_set_debounce_period(&vc, 10000);

	// Register power reached callback to function cb_power_reached
	voltage_current_register_callback(&vc,
	                                  VOLTAGE_CURRENT_CALLBACK_POWER_REACHED,
	                                  (void (*)(void))cb_power_reached,
	                                  NULL);

	// Configure threshold for power "greater than 10 W"
	voltage_current_set_power_callback_threshold(&vc, '>', 10*1000, 0);

	printf("Press key to exit\n");
	getchar();
	voltage_current_destroy(&vc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
