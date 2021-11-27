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

	// Set pin 0 on port A to output low
	io16_set_port_configuration(&io, 'a', 1 << 0, 'o', false);

	// Set pin 0 and 7 on port B to output high
	io16_set_port_configuration(&io, 'b', (1 << 0) | (1 << 7), 'o', true);

	printf("Press key to exit\n");
	getchar();
	io16_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
