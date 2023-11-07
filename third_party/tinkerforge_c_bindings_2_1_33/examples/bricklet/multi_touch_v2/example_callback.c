#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_multi_touch_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet 2.0

// Callback function for touch state callback
void cb_touch_state(bool state[13], void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Electrode 0: %s\n", state[0] ? "true" : "false");
	printf("Electrode 1: %s\n", state[1] ? "true" : "false");
	printf("Electrode 2: %s\n", state[2] ? "true" : "false");
	printf("Electrode 3: %s\n", state[3] ? "true" : "false");
	printf("Electrode 4: %s\n", state[4] ? "true" : "false");
	printf("Electrode 5: %s\n", state[5] ? "true" : "false");
	printf("Electrode 6: %s\n", state[6] ? "true" : "false");
	printf("Electrode 7: %s\n", state[7] ? "true" : "false");
	printf("Electrode 8: %s\n", state[8] ? "true" : "false");
	printf("Electrode 9: %s\n", state[9] ? "true" : "false");
	printf("Electrode 10: %s\n", state[10] ? "true" : "false");
	printf("Electrode 11: %s\n", state[11] ? "true" : "false");
	printf("Proximity: %s\n", state[12] ? "true" : "false");
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MultiTouchV2 mt;
	multi_touch_v2_create(&mt, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register touch state callback to function cb_touch_state
	multi_touch_v2_register_callback(&mt,
	                                 MULTI_TOUCH_V2_CALLBACK_TOUCH_STATE,
	                                 (void (*)(void))cb_touch_state,
	                                 NULL);

	// Set period for touch state callback to 0.01s (10ms)
	multi_touch_v2_set_touch_state_callback_configuration(&mt, 10, true);

	printf("Press key to exit\n");
	getchar();
	multi_touch_v2_destroy(&mt);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
