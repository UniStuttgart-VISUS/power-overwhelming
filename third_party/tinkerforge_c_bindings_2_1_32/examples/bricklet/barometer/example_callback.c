#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_barometer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet

// Callback function for air pressure callback
void cb_air_pressure(int32_t air_pressure, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Air Pressure: %f hPa\n", air_pressure/1000.0);
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

	// Register air pressure callback to function cb_air_pressure
	barometer_register_callback(&b,
	                            BAROMETER_CALLBACK_AIR_PRESSURE,
	                            (void (*)(void))cb_air_pressure,
	                            NULL);

	// Set period for air pressure callback to 1s (1000ms)
	// Note: The air pressure callback is only called every second
	//       if the air pressure has changed since the last call!
	barometer_set_air_pressure_callback_period(&b, 1000);

	printf("Press key to exit\n");
	getchar();
	barometer_destroy(&b);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
