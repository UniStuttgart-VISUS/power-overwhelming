#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_linear_poti_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Linear Poti Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LinearPotiV2 lp;
	linear_poti_v2_create(&lp, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current position
	uint8_t position;
	if(linear_poti_v2_get_position(&lp, &position) < 0) {
		fprintf(stderr, "Could not get position, probably timeout\n");
		return 1;
	}

	printf("Position: %u %%\n", position);

	printf("Press key to exit\n");
	getchar();
	linear_poti_v2_destroy(&lp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
