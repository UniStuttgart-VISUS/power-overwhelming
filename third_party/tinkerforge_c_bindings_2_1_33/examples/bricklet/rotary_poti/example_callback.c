#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rotary_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Rotary Poti Bricklet

// Callback function for position callback
void cb_position(int16_t position, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Position: %d\n", position); // Range: -150 to 150
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RotaryPoti rp;
	rotary_poti_create(&rp, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register position callback to function cb_position
	rotary_poti_register_callback(&rp,
	                              ROTARY_POTI_CALLBACK_POSITION,
	                              (void (*)(void))cb_position,
	                              NULL);

	// Set period for position callback to 0.05s (50ms)
	// Note: The position callback is only called every 0.05 seconds
	//       if the position has changed since the last call!
	rotary_poti_set_position_callback_period(&rp, 50);

	printf("Press key to exit\n");
	getchar();
	rotary_poti_destroy(&rp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
