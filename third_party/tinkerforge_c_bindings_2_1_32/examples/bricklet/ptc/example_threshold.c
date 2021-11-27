#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ptc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your PTC Bricklet

// Callback function for temperature reached callback
void cb_temperature_reached(int32_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Temperature: %f °C\n", temperature/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PTC ptc;
	ptc_create(&ptc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	ptc_set_debounce_period(&ptc, 10000);

	// Register temperature reached callback to function cb_temperature_reached
	ptc_register_callback(&ptc,
	                      PTC_CALLBACK_TEMPERATURE_REACHED,
	                      (void (*)(void))cb_temperature_reached,
	                      NULL);

	// Configure threshold for temperature "greater than 30 °C"
	ptc_set_temperature_callback_threshold(&ptc, '>', 30*100, 0);

	printf("Press key to exit\n");
	getchar();
	ptc_destroy(&ptc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
