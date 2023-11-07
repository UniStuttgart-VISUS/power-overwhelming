#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_color_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Color Bricklet 2.0

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
	ColorV2 c;
	color_v2_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register color callback to function cb_color
	color_v2_register_callback(&c,
	                           COLOR_V2_CALLBACK_COLOR,
	                           (void (*)(void))cb_color,
	                           NULL);

	// Set period for color callback to 0.1s (100ms)
	color_v2_set_color_callback_configuration(&c, 100, false);

	printf("Press key to exit\n");
	getchar();
	color_v2_destroy(&c);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
