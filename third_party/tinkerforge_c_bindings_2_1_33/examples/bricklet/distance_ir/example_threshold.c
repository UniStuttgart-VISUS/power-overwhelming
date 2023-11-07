#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_ir.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance IR Bricklet

// Callback function for distance reached callback
void cb_distance_reached(uint16_t distance, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Distance: %f cm\n", distance/10.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DistanceIR dir;
	distance_ir_create(&dir, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	distance_ir_set_debounce_period(&dir, 10000);

	// Register distance reached callback to function cb_distance_reached
	distance_ir_register_callback(&dir,
	                              DISTANCE_IR_CALLBACK_DISTANCE_REACHED,
	                              (void (*)(void))cb_distance_reached,
	                              NULL);

	// Configure threshold for distance "smaller than 30 cm"
	distance_ir_set_distance_callback_threshold(&dir, '<', 30*10, 0);

	printf("Press key to exit\n");
	getchar();
	distance_ir_destroy(&dir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
