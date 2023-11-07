#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io16.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-16 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO16 io;
	io16_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current value from port A as bitmask
	uint8_t value_mask_a;
	if(io16_get_port(&io, 'a', &value_mask_a) < 0) {
		fprintf(stderr, "Could not get value from port A as bitmask, probably timeout\n");
		return 1;
	}

	printf("Value Mask (Port A): %u\n", value_mask_a);

	// Get current value from port B as bitmask
	uint8_t value_mask_b;
	if(io16_get_port(&io, 'b', &value_mask_b) < 0) {
		fprintf(stderr, "Could not get value from port B as bitmask, probably timeout\n");
		return 1;
	}

	printf("Value Mask (Port B): %u\n", value_mask_b);

	printf("Press key to exit\n");
	getchar();
	io16_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
