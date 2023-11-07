#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_joystick.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Joystick Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Joystick j;
	joystick_create(&j, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current position
	int16_t x, y;
	if(joystick_get_position(&j, &x, &y) < 0) {
		fprintf(stderr, "Could not get position, probably timeout\n");
		return 1;
	}

	printf("Position [X]: %d\n", x);
	printf("Position [Y]: %d\n", y);

	printf("Press key to exit\n");
	getchar();
	joystick_destroy(&j);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
