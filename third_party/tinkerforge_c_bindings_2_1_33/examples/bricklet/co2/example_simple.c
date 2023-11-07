#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_co2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your CO2 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	CO2 co2;
	co2_create(&co2, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current CO2 concentration
	uint16_t co2_concentration;
	if(co2_get_co2_concentration(&co2, &co2_concentration) < 0) {
		fprintf(stderr, "Could not get CO2 concentration, probably timeout\n");
		return 1;
	}

	printf("CO2 Concentration: %u ppm\n", co2_concentration);

	printf("Press key to exit\n");
	getchar();
	co2_destroy(&co2);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
