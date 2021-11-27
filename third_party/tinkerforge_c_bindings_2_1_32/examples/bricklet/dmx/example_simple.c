#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dmx.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your DMX Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DMX dmx;
	dmx_create(&dmx, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Configure Bricklet as DMX master
	dmx_set_dmx_mode(&dmx, DMX_DMX_MODE_MASTER);

	// Write DMX frame with 3 channels
	uint8_t frame[3] = {255, 128, 0};
	dmx_write_frame(&dmx, frame, 3);

	printf("Press key to exit\n");
	getchar();
	dmx_destroy(&dmx);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
