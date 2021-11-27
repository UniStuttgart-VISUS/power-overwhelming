#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_load_cell_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Load Cell Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LoadCellV2 lc;
	load_cell_v2_create(&lc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current weight
	int32_t weight;
	if(load_cell_v2_get_weight(&lc, &weight) < 0) {
		fprintf(stderr, "Could not get weight, probably timeout\n");
		return 1;
	}

	printf("Weight: %d g\n", weight);

	printf("Press key to exit\n");
	getchar();
	load_cell_v2_destroy(&lc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
