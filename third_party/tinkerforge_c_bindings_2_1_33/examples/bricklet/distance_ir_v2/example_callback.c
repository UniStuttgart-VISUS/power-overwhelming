#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_ir_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance IR Bricklet 2.0

// Callback function for distance callback
void cb_distance(uint16_t distance, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Distance: %f cm\n", distance/10.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DistanceIRV2 dir;
	distance_ir_v2_create(&dir, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register distance callback to function cb_distance
	distance_ir_v2_register_callback(&dir,
	                                 DISTANCE_IR_V2_CALLBACK_DISTANCE,
	                                 (void (*)(void))cb_distance,
	                                 NULL);

	// Set period for distance callback to 1s (1000ms) without a threshold
	distance_ir_v2_set_distance_callback_configuration(&dir, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	distance_ir_v2_destroy(&dir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
