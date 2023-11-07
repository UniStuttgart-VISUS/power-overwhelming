#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rotary_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Rotary Poti Bricklet

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

	// Get current position
	int16_t position;
	if(rotary_poti_get_position(&rp, &position) < 0) {
		fprintf(stderr, "Could not get position, probably timeout\n");
		return 1;
	}

	printf("Position: %d\n", position); // Range: -150 to 150

	printf("Press key to exit\n");
	getchar();
	rotary_poti_destroy(&rp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
