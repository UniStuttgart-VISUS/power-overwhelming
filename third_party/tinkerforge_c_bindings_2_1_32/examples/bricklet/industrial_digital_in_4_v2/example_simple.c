#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_in_4_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital In 4 Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalIn4V2 idi4;
	industrial_digital_in_4_v2_create(&idi4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current value
	bool value[4];
	if(industrial_digital_in_4_v2_get_value(&idi4, value) < 0) {
		fprintf(stderr, "Could not get value, probably timeout\n");
		return 1;
	}

	printf("Channel 0: %s\n", value[0] ? "true" : "false");
	printf("Channel 1: %s\n", value[1] ? "true" : "false");
	printf("Channel 2: %s\n", value[2] ? "true" : "false");
	printf("Channel 3: %s\n", value[3] ? "true" : "false");

	printf("Press key to exit\n");
	getchar();
	industrial_digital_in_4_v2_destroy(&idi4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
