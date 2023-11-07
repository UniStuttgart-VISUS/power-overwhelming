#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_compass.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Compass Bricklet

// Callback function for heading callback
void cb_heading(int16_t heading, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Heading: %f °\n", heading/10.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Compass c;
	compass_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register heading callback to function cb_heading
	compass_register_callback(&c,
	                          COMPASS_CALLBACK_HEADING,
	                          (void (*)(void))cb_heading,
	                          NULL);

	// Set period for heading callback to 0.1s (100ms) without a threshold
	compass_set_heading_callback_configuration(&c, 100, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	compass_destroy(&c);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
