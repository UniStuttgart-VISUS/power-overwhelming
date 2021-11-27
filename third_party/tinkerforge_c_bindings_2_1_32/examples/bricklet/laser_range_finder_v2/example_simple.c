#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_laser_range_finder_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Laser Range Finder Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LaserRangeFinderV2 lrf;
	laser_range_finder_v2_create(&lrf, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn laser on and wait 250ms for very first measurement to be ready
	laser_range_finder_v2_set_enable(&lrf, true);
	millisleep(250);

	// Get current distance
	int16_t distance;
	if(laser_range_finder_v2_get_distance(&lrf, &distance) < 0) {
		fprintf(stderr, "Could not get distance, probably timeout\n");
		return 1;
	}

	printf("Distance: %d cm\n", distance);

	printf("Press key to exit\n");
	getchar();

	// Turn laser off
	laser_range_finder_v2_set_enable(&lrf, false);

	laser_range_finder_v2_destroy(&lrf);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
