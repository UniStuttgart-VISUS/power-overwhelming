#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_segment_display_4x7.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Segment Display 4x7 Bricklet

const uint8_t digits[] = {0x3f,0x06,0x5b,0x4f,
                          0x66,0x6d,0x7d,0x07,
                          0x7f,0x6f,0x77,0x7c,
                          0x39,0x5e,0x79,0x71}; // 0~9,A,b,C,d,E,F

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SegmentDisplay4x7 sd;
	segment_display_4x7_create(&sd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Write "4223" to the display with full brightness without colon
	uint8_t segments[4] = {digits[4], digits[2], digits[2], digits[3]};
	segment_display_4x7_set_segments(&sd, segments, 7, false);

	printf("Press key to exit\n");
	getchar();
	segment_display_4x7_destroy(&sd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
