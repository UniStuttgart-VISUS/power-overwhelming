#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_barometer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet

// Callback function for air pressure reached callback
void cb_air_pressure_reached(int32_t air_pressure, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Air Pressure: %f hPa\n", air_pressure/1000.0);
	printf("Enjoy the potentially good weather!\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Barometer b;
	barometer_create(&b, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	barometer_set_debounce_period(&b, 10000);

	// Register air pressure reached callback to function cb_air_pressure_reached
	barometer_register_callback(&b,
	                            BAROMETER_CALLBACK_AIR_PRESSURE_REACHED,
	                            (void (*)(void))cb_air_pressure_reached,
	                            NULL);

	// Configure threshold for air pressure "greater than 1025 hPa"
	barometer_set_air_pressure_callback_threshold(&b, '>', 1025*1000, 0);

	printf("Press key to exit\n");
	getchar();
	barometer_destroy(&b);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
