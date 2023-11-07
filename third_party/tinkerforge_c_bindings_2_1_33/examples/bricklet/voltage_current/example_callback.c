#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage_current.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage/Current Bricklet

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
	VoltageCurrent vc;
	voltage_current_create(&vc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register current callback to function cb_current
	voltage_current_register_callback(&vc,
	                                  VOLTAGE_CURRENT_CALLBACK_CURRENT,
	                                  (void (*)(void))cb_current,
	                                  NULL);

	// Set period for current callback to 1s (1000ms)
	// Note: The current callback is only called every second
	//       if the current has changed since the last call!
	voltage_current_set_current_callback_period(&vc, 1000);

	printf("Press key to exit\n");
	getchar();
	voltage_current_destroy(&vc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
