#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_multi_touch.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Multi Touch Bricklet

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

	// Get current touch state
	uint16_t state;
	if(multi_touch_get_touch_state(&mt, &state) < 0) {
		fprintf(stderr, "Could not get touch state, probably timeout\n");
		return 1;
	}

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

	printf("Press key to exit\n");
	getchar();
	multi_touch_destroy(&mt);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
