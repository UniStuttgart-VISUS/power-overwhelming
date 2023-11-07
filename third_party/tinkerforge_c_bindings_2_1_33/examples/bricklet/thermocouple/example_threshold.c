#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_thermocouple.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Thermocouple Bricklet

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
	Thermocouple t;
	thermocouple_create(&t, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	thermocouple_set_debounce_period(&t, 10000);

	// Register temperature reached callback to function cb_temperature_reached
	thermocouple_register_callback(&t,
	                               THERMOCOUPLE_CALLBACK_TEMPERATURE_REACHED,
	                               (void (*)(void))cb_temperature_reached,
	                               NULL);

	// Configure threshold for temperature "greater than 30 °C"
	thermocouple_set_temperature_callback_threshold(&t, '>', 30*100, 0);

	printf("Press key to exit\n");
	getchar();
	thermocouple_destroy(&t);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
