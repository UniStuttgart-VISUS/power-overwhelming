#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motion_detector.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Motion Detector Bricklet

// Callback function for motion detected callback
void cb_motion_detected(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Motion Detected\n");
}

// Callback function for detection cycle ended callback
void cb_detection_cycle_ended(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Detection Cycle Ended (next detection possible in ~3 seconds)\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MotionDetector md;
	motion_detector_create(&md, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register motion detected callback to function cb_motion_detected
	motion_detector_register_callback(&md,
	                                  MOTION_DETECTOR_CALLBACK_MOTION_DETECTED,
	                                  (void (*)(void))cb_motion_detected,
	                                  NULL);

	// Register detection cycle ended callback to function cb_detection_cycle_ended
	motion_detector_register_callback(&md,
	                                  MOTION_DETECTOR_CALLBACK_DETECTION_CYCLE_ENDED,
	                                  (void (*)(void))cb_detection_cycle_ended,
	                                  NULL);

	printf("Press key to exit\n");
	getchar();
	motion_detector_destroy(&md);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
