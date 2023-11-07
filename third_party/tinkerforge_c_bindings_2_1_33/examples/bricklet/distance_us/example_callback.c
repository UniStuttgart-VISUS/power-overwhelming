#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_us.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet

// Callback function for distance value callback
void cb_distance(uint16_t distance, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Distance Value: %u\n", distance);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DistanceUS dus;
	distance_us_create(&dus, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register distance value callback to function cb_distance
	distance_us_register_callback(&dus,
	                              DISTANCE_US_CALLBACK_DISTANCE,
	                              (void (*)(void))cb_distance,
	                              NULL);

	// Set period for distance value callback to 0.2s (200ms)
	// Note: The distance value callback is only called every 0.2 seconds
	//       if the distance value has changed since the last call!
	distance_us_set_distance_callback_period(&dus, 200);

	printf("Press key to exit\n");
	getchar();
	distance_us_destroy(&dus);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
