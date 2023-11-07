#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_segment_display_4x7_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Segment Display 4x7 Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SegmentDisplay4x7V2 sd;
	segment_display_4x7_v2_create(&sd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	segment_display_4x7_v2_set_brightness(&sd, 7); // Set to full brightness

	// Blink colon 10 times
	int i;
	for(i = 0; i < 10; ++i) {

		// Activate segments of colon
		segment_display_4x7_v2_set_selected_segment(&sd, 32, true);
		segment_display_4x7_v2_set_selected_segment(&sd, 33, true);

		millisleep(250);

		// Deactivate segments of colon
		segment_display_4x7_v2_set_selected_segment(&sd, 32, false);
		segment_display_4x7_v2_set_selected_segment(&sd, 33, false);
	}

	printf("Press key to exit\n");
	getchar();
	segment_display_4x7_v2_destroy(&sd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
