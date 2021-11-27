#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_current12.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Current12 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Current12 c;
	current12_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current current
	int16_t current;
	if(current12_get_current(&c, &current) < 0) {
		fprintf(stderr, "Could not get current, probably timeout\n");
		return 1;
	}

	printf("Current: %f A\n", current/1000.0);

	printf("Press key to exit\n");
	getchar();
	current12_destroy(&c);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
