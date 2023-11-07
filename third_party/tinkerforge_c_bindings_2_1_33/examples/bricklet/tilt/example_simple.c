#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_tilt.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Tilt Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Tilt t;
	tilt_create(&t, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current tilt state
	uint8_t state;
	if(tilt_get_tilt_state(&t, &state) < 0) {
		fprintf(stderr, "Could not get tilt state, probably timeout\n");
		return 1;
	}

	if(state == TILT_TILT_STATE_CLOSED) {
		printf("Tilt State: Closed\n");
	} else if(state == TILT_TILT_STATE_OPEN) {
		printf("Tilt State: Open\n");
	} else if(state == TILT_TILT_STATE_CLOSED_VIBRATING) {
		printf("Tilt State: Closed Vibrating\n");
	}

	printf("Press key to exit\n");
	getchar();
	tilt_destroy(&t);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
