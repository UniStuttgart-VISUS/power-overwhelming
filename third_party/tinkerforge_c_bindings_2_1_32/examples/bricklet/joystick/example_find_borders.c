#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_joystick.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Joystick Bricklet

// Callback function for position reached callback
void cb_position_reached(int16_t x, int16_t y, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(y == 100) {
		printf("Top\n");
	} else if(y == -100) {
		printf("Bottom\n");
	}

	if(x == 100) {
		printf("Right\n");
	} else if(x == -100) {
		printf("Left\n");
	}

	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Joystick j;
	joystick_create(&j, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 0.2 seconds (200ms)
	joystick_set_debounce_period(&j, 200);

	// Register position reached callback to function cb_position_reached
	joystick_register_callback(&j,
	                           JOYSTICK_CALLBACK_POSITION_REACHED,
	                           (void (*)(void))cb_position_reached,
	                           NULL);

	// Configure threshold for position "outside of -99, -99 to 99, 99"
	joystick_set_position_callback_threshold(&j, 'o', -99, 99, -99, 99);

	printf("Press key to exit\n");
	getchar();
	joystick_destroy(&j);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
