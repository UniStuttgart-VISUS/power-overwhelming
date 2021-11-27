#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_joystick_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Joystick Bricklet 2.0

// Callback function for pressed callback
void cb_pressed(bool pressed, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Pressed: %s\n", pressed ? "true" : "false");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	JoystickV2 j;
	joystick_v2_create(&j, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register pressed callback to function cb_pressed
	joystick_v2_register_callback(&j,
	                              JOYSTICK_V2_CALLBACK_PRESSED,
	                              (void (*)(void))cb_pressed,
	                              NULL);

	// Set period for pressed callback to 0.01s (10ms)
	joystick_v2_set_pressed_callback_configuration(&j, 10, true);

	printf("Press key to exit\n");
	getchar();
	joystick_v2_destroy(&j);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
