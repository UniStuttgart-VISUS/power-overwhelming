#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io16_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-16 Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO16V2 io;
	io16_v2_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current value
	bool value[16];
	if(io16_v2_get_value(&io, value) < 0) {
		fprintf(stderr, "Could not get value, probably timeout\n");
		return 1;
	}

	printf("Channel 0 [A0]: %s\n", value[0] ? "true" : "false");
	printf("Channel 1 [A1]: %s\n", value[1] ? "true" : "false");
	printf("Channel 2 [A2]: %s\n", value[2] ? "true" : "false");
	printf("Channel 3 [A3]: %s\n", value[3] ? "true" : "false");
	printf("Channel 4 [A4]: %s\n", value[4] ? "true" : "false");
	printf("Channel 5 [A5]: %s\n", value[5] ? "true" : "false");
	printf("Channel 6 [A6]: %s\n", value[6] ? "true" : "false");
	printf("Channel 7 [A7]: %s\n", value[7] ? "true" : "false");
	printf("Channel 8 [B0]: %s\n", value[8] ? "true" : "false");
	printf("Channel 9 [B1]: %s\n", value[9] ? "true" : "false");
	printf("Channel 10 [B2]: %s\n", value[10] ? "true" : "false");
	printf("Channel 11 [B3]: %s\n", value[11] ? "true" : "false");
	printf("Channel 12 [B4]: %s\n", value[12] ? "true" : "false");
	printf("Channel 13 [B5]: %s\n", value[13] ? "true" : "false");
	printf("Channel 14 [B6]: %s\n", value[14] ? "true" : "false");
	printf("Channel 15 [B7]: %s\n", value[15] ? "true" : "false");

	printf("Press key to exit\n");
	getchar();
	io16_v2_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
