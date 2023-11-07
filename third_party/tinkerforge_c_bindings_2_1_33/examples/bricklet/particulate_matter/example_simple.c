#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_particulate_matter.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Particulate Matter Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	ParticulateMatter pm;
	particulate_matter_create(&pm, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current PM concentration
	uint16_t pm10, pm25, pm100;
	if(particulate_matter_get_pm_concentration(&pm, &pm10, &pm25, &pm100) < 0) {
		fprintf(stderr, "Could not get PM concentration, probably timeout\n");
		return 1;
	}

	printf("PM 1.0: %u µg/m³\n", pm10);
	printf("PM 2.5: %u µg/m³\n", pm25);
	printf("PM 10.0: %u µg/m³\n", pm100);

	printf("Press key to exit\n");
	getchar();
	particulate_matter_destroy(&pm);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
