#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-4 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO4 io;
	io4_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current value as bitmask
	uint8_t value_mask;
	if(io4_get_value(&io, &value_mask) < 0) {
		fprintf(stderr, "Could not get value as bitmask, probably timeout\n");
		return 1;
	}

	printf("Value Mask: %u\n", value_mask);

	printf("Press key to exit\n");
	getchar();
	io4_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
