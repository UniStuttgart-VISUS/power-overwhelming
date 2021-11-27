#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rotary_encoder_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Rotary Encoder Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RotaryEncoderV2 re;
	rotary_encoder_v2_create(&re, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current count without reset
	int32_t count;
	if(rotary_encoder_v2_get_count(&re, false, &count) < 0) {
		fprintf(stderr, "Could not get count without reset, probably timeout\n");
		return 1;
	}

	printf("Count: %d\n", count);

	printf("Press key to exit\n");
	getchar();
	rotary_encoder_v2_destroy(&re);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
