#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_linear_poti_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Linear Poti Bricklet 2.0

// Callback function for position callback
void cb_position(uint8_t position, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Position: %u %%\n", position);
}

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

	// Register position callback to function cb_position
	linear_poti_v2_register_callback(&lp,
	                                 LINEAR_POTI_V2_CALLBACK_POSITION,
	                                 (void (*)(void))cb_position,
	                                 NULL);

	// Set period for position callback to 0.25s (250ms) without a threshold
	linear_poti_v2_set_position_callback_configuration(&lp, 250, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	linear_poti_v2_destroy(&lp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
