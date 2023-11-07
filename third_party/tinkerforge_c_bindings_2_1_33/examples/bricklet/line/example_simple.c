#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_line.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Line Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Line l;
	line_create(&l, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current reflectivity
	uint16_t reflectivity;
	if(line_get_reflectivity(&l, &reflectivity) < 0) {
		fprintf(stderr, "Could not get reflectivity, probably timeout\n");
		return 1;
	}

	printf("Reflectivity: %u\n", reflectivity);

	printf("Press key to exit\n");
	getchar();
	line_destroy(&l);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
