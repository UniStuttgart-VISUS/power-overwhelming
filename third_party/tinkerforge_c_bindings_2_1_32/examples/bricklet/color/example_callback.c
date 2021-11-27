#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_color.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Color Bricklet

// Callback function for color callback
void cb_color(uint16_t r, uint16_t g, uint16_t b, uint16_t c, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Color [R]: %u\n", r);
	printf("Color [G]: %u\n", g);
	printf("Color [B]: %u\n", b);
	printf("Color [C]: %u\n", c);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Color c;
	color_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register color callback to function cb_color
	color_register_callback(&c,
	                        COLOR_CALLBACK_COLOR,
	                        (void (*)(void))cb_color,
	                        NULL);

	// Set period for color callback to 1s (1000ms)
	// Note: The color callback is only called every second
	//       if the color has changed since the last call!
	color_set_color_callback_period(&c, 1000);

	printf("Press key to exit\n");
	getchar();
	color_destroy(&c);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
