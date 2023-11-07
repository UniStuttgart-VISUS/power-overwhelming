#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motion_detector_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Motion Detector Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MotionDetectorV2 md;
	motion_detector_v2_create(&md, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn blue backlight LEDs on (maximum brightness)
	motion_detector_v2_set_indicator(&md, 255, 255, 255);

	printf("Press key to exit\n");
	getchar();
	motion_detector_v2_destroy(&md);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
