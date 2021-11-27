#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dust_detector.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Dust Detector Bricklet

// Callback function for dust density callback
void cb_dust_density(uint16_t dust_density, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Dust Density: %u µg/m³\n", dust_density);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DustDetector dd;
	dust_detector_create(&dd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register dust density callback to function cb_dust_density
	dust_detector_register_callback(&dd,
	                                DUST_DETECTOR_CALLBACK_DUST_DENSITY,
	                                (void (*)(void))cb_dust_density,
	                                NULL);

	// Set period for dust density callback to 1s (1000ms)
	// Note: The dust density callback is only called every second
	//       if the dust density has changed since the last call!
	dust_detector_set_dust_density_callback_period(&dd, 1000);

	printf("Press key to exit\n");
	getchar();
	dust_detector_destroy(&dd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
