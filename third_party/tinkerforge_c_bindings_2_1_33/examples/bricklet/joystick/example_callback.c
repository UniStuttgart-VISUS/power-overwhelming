#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_joystick.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Joystick Bricklet

// Callback function for pressed callback
void cb_pressed(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Pressed\n");
}

// Callback function for released callback
void cb_released(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Released\n");
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

	// Register pressed callback to function cb_pressed
	joystick_register_callback(&j,
	                           JOYSTICK_CALLBACK_PRESSED,
	                           (void (*)(void))cb_pressed,
	                           NULL);

	// Register released callback to function cb_released
	joystick_register_callback(&j,
	                           JOYSTICK_CALLBACK_RELEASED,
	                           (void (*)(void))cb_released,
	                           NULL);

	printf("Press key to exit\n");
	getchar();
	joystick_destroy(&j);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
