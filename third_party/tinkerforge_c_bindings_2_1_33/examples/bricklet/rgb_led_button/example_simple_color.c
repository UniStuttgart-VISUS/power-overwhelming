#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rgb_led_button.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RGB LED Button Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RGBLEDButton rlb;
	rgb_led_button_create(&rlb, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set light blue color
	rgb_led_button_set_color(&rlb, 0, 170, 234);

	printf("Press key to exit\n");
	getchar();
	rgb_led_button_destroy(&rlb);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
