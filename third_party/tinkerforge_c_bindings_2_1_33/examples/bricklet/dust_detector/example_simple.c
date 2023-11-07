#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dust_detector.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Dust Detector Bricklet

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

	// Get current dust density
	uint16_t dust_density;
	if(dust_detector_get_dust_density(&dd, &dust_density) < 0) {
		fprintf(stderr, "Could not get dust density, probably timeout\n");
		return 1;
	}

	printf("Dust Density: %u µg/m³\n", dust_density);

	printf("Press key to exit\n");
	getchar();
	dust_detector_destroy(&dd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
