#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_linear_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Linear Poti Bricklet

// Callback function for position callback
void cb_position(uint16_t position, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Position: %u %%\n", position); // Range: 0 to 100
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LinearPoti lp;
	linear_poti_create(&lp, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register position callback to function cb_position
	linear_poti_register_callback(&lp,
	                              LINEAR_POTI_CALLBACK_POSITION,
	                              (void (*)(void))cb_position,
	                              NULL);

	// Set period for position callback to 0.05s (50ms)
	// Note: The position callback is only called every 0.05 seconds
	//       if the position has changed since the last call!
	linear_poti_set_position_callback_period(&lp, 50);

	printf("Press key to exit\n");
	getchar();
	linear_poti_destroy(&lp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
