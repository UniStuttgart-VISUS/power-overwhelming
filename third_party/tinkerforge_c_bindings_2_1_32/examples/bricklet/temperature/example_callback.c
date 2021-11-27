#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_temperature.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Temperature Bricklet

// Callback function for temperature callback
void cb_temperature(int16_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Temperature: %f °C\n", temperature/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Temperature t;
	temperature_create(&t, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register temperature callback to function cb_temperature
	temperature_register_callback(&t,
	                              TEMPERATURE_CALLBACK_TEMPERATURE,
	                              (void (*)(void))cb_temperature,
	                              NULL);

	// Set period for temperature callback to 1s (1000ms)
	// Note: The temperature callback is only called every second
	//       if the temperature has changed since the last call!
	temperature_set_temperature_callback_period(&t, 1000);

	printf("Press key to exit\n");
	getchar();
	temperature_destroy(&t);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
