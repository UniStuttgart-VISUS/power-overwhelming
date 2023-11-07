#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_barometer_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet 2.0

// Callback function for air pressure callback
void cb_air_pressure(int32_t air_pressure, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Air Pressure: %f hPa\n", air_pressure/1000.0);
	printf("Enjoy the potentially good weather!\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	BarometerV2 b;
	barometer_v2_create(&b, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register air pressure callback to function cb_air_pressure
	barometer_v2_register_callback(&b,
	                               BAROMETER_V2_CALLBACK_AIR_PRESSURE,
	                               (void (*)(void))cb_air_pressure,
	                               NULL);

	// Configure threshold for air pressure "greater than 1025 hPa"
	// with a debounce period of 1s (1000ms)
	barometer_v2_set_air_pressure_callback_configuration(&b, 1000, false, '>', 1025*1000, 0);

	printf("Press key to exit\n");
	getchar();
	barometer_v2_destroy(&b);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
