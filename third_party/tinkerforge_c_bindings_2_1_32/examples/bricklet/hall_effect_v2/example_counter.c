#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_hall_effect_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HallEffectV2 he;
	hall_effect_v2_create(&he, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current count without counter reset
	uint32_t count;
	if(hall_effect_v2_get_counter(&he, false, &count) < 0) {
		fprintf(stderr, "Could not get count without counter reset, probably timeout\n");
		return 1;
	}

	printf("Count: %u\n", count);

	printf("Press key to exit\n");
	getchar();
	hall_effect_v2_destroy(&he);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
