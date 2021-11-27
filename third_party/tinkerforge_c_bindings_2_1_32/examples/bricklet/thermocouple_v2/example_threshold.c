#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_thermocouple_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Thermocouple Bricklet 2.0

// Callback function for temperature callback
void cb_temperature(int32_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Temperature: %f °C\n", temperature/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	ThermocoupleV2 t;
	thermocouple_v2_create(&t, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register temperature callback to function cb_temperature
	thermocouple_v2_register_callback(&t,
	                                  THERMOCOUPLE_V2_CALLBACK_TEMPERATURE,
	                                  (void (*)(void))cb_temperature,
	                                  NULL);

	// Configure threshold for temperature "greater than 30 °C"
	// with a debounce period of 10s (10000ms)
	thermocouple_v2_set_temperature_callback_configuration(&t, 10000, false, '>', 30*100, 0);

	printf("Press key to exit\n");
	getchar();
	thermocouple_v2_destroy(&t);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
