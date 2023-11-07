#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_load_cell.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Load Cell Bricklet

// Callback function for weight reached callback
void cb_weight_reached(int32_t weight, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Weight: %d g\n", weight);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LoadCell lc;
	load_cell_create(&lc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 1 second (1000ms)
	load_cell_set_debounce_period(&lc, 1000);

	// Register weight reached callback to function cb_weight_reached
	load_cell_register_callback(&lc,
	                            LOAD_CELL_CALLBACK_WEIGHT_REACHED,
	                            (void (*)(void))cb_weight_reached,
	                            NULL);

	// Configure threshold for weight "greater than 200 g"
	load_cell_set_weight_callback_threshold(&lc, '>', 200, 0);

	printf("Press key to exit\n");
	getchar();
	load_cell_destroy(&lc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
