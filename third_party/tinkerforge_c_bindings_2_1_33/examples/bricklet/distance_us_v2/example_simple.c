#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_us_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DistanceUSV2 dus;
	distance_us_v2_create(&dus, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current distance
	uint16_t distance;
	if(distance_us_v2_get_distance(&dus, &distance) < 0) {
		fprintf(stderr, "Could not get distance, probably timeout\n");
		return 1;
	}

	printf("Distance: %f cm\n", distance/10.0);

	printf("Press key to exit\n");
	getchar();
	distance_us_v2_destroy(&dus);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
