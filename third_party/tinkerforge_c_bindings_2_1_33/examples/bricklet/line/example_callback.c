#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_line.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Line Bricklet

// Callback function for reflectivity callback
void cb_reflectivity(uint16_t reflectivity, void *user_data) {
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

	// Register reflectivity callback to function cb_reflectivity
	line_register_callback(&l,
	                       LINE_CALLBACK_REFLECTIVITY,
	                       (void (*)(void))cb_reflectivity,
	                       NULL);

	// Set period for reflectivity callback to 1s (1000ms)
	// Note: The reflectivity callback is only called every second
	//       if the reflectivity has changed since the last call!
	line_set_reflectivity_callback_period(&l, 1000);

	printf("Press key to exit\n");
	getchar();
	line_destroy(&l);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
