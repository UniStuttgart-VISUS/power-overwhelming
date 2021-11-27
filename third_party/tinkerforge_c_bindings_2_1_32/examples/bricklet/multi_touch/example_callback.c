#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_multi_touch.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet

// Callback function for touch state callback
void cb_touch_state(uint16_t state, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(state & (1 << 12)) {
		printf("In proximity, ");
	}

	if((state & 0xfff) == 0) {
		printf("No electrodes touched\n");
	} else {
		printf("Electrodes ");
		int i;
		for(i = 0; i < 12; i++) {
			if(state & (1 << i)) {
				printf("%d ", i);
			}
		}
		printf("touched\n");
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MultiTouch mt;
	multi_touch_create(&mt, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register touch state callback to function cb_touch_state
	multi_touch_register_callback(&mt,
	                              MULTI_TOUCH_CALLBACK_TOUCH_STATE,
	                              (void (*)(void))cb_touch_state,
	                              NULL);

	printf("Press key to exit\n");
	getchar();
	multi_touch_destroy(&mt);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
