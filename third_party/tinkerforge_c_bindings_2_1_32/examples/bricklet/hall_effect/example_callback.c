#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_hall_effect.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet

// Callback function for edge count callback
void cb_edge_count(uint32_t count, bool value, void *user_data) {
	(void)value; (void)user_data; // avoid unused parameter warning

	printf("Count: %u\n", count);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HallEffect he;
	hall_effect_create(&he, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register edge count callback to function cb_edge_count
	hall_effect_register_callback(&he,
	                              HALL_EFFECT_CALLBACK_EDGE_COUNT,
	                              (void (*)(void))cb_edge_count,
	                              NULL);

	// Set period for edge count callback to 0.05s (50ms)
	// Note: The edge count callback is only called every 0.05 seconds
	//       if the edge count has changed since the last call!
	hall_effect_set_edge_count_callback_period(&he, 50);

	printf("Press key to exit\n");
	getchar();
	hall_effect_destroy(&he);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
