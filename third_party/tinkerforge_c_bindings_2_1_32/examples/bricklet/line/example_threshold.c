#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_line.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Line Bricklet

// Callback function for reflectivity reached callback
void cb_reflectivity_reached(uint16_t reflectivity, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Reflectivity: %u\n", reflectivity);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Line l;
	line_create(&l, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 1 second (1000ms)
	line_set_debounce_period(&l, 1000);

	// Register reflectivity reached callback to function cb_reflectivity_reached
	line_register_callback(&l,
	                       LINE_CALLBACK_REFLECTIVITY_REACHED,
	                       (void (*)(void))cb_reflectivity_reached,
	                       NULL);

	// Configure threshold for reflectivity "greater than 2000"
	line_set_reflectivity_callback_threshold(&l, '>', 2000, 0);

	printf("Press key to exit\n");
	getchar();
	line_destroy(&l);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
