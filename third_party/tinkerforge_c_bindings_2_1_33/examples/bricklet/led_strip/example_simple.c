#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_led_strip.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LED Strip Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LEDStrip ls;
	led_strip_create(&ls, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set first 10 LEDs to green
	uint8_t r[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t g[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0};
	uint8_t b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	led_strip_set_rgb_values(&ls, 0, 10, r, g, b);

	printf("Press key to exit\n");
	getchar();
	led_strip_destroy(&ls);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
