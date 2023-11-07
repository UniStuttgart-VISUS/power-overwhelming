#include <stdio.h>

// FIXME: This example is incomplete

#include "ip_connection.h"
#include "bricklet_led_strip_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LED Strip Bricklet 2.0

// Use frame started callback to move the active LED every frame
void cb_frame_started(uint16_t length, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Length: %u\n", length);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LEDStripV2 ls;
	led_strip_v2_create(&ls, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set frame duration to 50ms (20 frames per second)
	led_strip_v2_set_frame_duration(&ls, 50);

	// Register frame started callback to function cb_frame_started
	led_strip_v2_register_callback(&ls,
	                               LED_STRIP_V2_CALLBACK_FRAME_STARTED,
	                               (void (*)(void))cb_frame_started,
	                               NULL);

	printf("Press key to exit\n");
	getchar();
	led_strip_v2_destroy(&ls);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
