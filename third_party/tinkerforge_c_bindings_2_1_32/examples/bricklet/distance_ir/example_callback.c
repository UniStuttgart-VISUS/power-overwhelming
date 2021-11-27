#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_distance_ir.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Distance IR Bricklet

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
	DistanceIR dir;
	distance_ir_create(&dir, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register distance callback to function cb_distance
	distance_ir_register_callback(&dir,
	                              DISTANCE_IR_CALLBACK_DISTANCE,
	                              (void (*)(void))cb_distance,
	                              NULL);

	// Set period for distance callback to 0.2s (200ms)
	// Note: The distance callback is only called every 0.2 seconds
	//       if the distance has changed since the last call!
	distance_ir_set_distance_callback_period(&dir, 200);

	printf("Press key to exit\n");
	getchar();
	distance_ir_destroy(&dir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
