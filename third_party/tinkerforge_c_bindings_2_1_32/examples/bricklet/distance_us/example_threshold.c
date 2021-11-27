#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_us.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance US Bricklet

// Callback function for distance value reached callback
void cb_distance_reached(uint16_t distance, void *user_data) {
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

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	distance_us_set_debounce_period(&dus, 10000);

	// Register distance value reached callback to function cb_distance_reached
	distance_us_register_callback(&dus,
	                              DISTANCE_US_CALLBACK_DISTANCE_REACHED,
	                              (void (*)(void))cb_distance_reached,
	                              NULL);

	// Configure threshold for distance value "smaller than 200"
	distance_us_set_distance_callback_threshold(&dus, '<', 200, 0);

	printf("Press key to exit\n");
	getchar();
	distance_us_destroy(&dus);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
