#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_moisture.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Moisture Bricklet

// Callback function for moisture value reached callback
void cb_moisture_reached(uint16_t moisture, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Moisture Value: %u\n", moisture);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Moisture m;
	moisture_create(&m, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 1 second (1000ms)
	moisture_set_debounce_period(&m, 1000);

	// Register moisture value reached callback to function cb_moisture_reached
	moisture_register_callback(&m,
	                           MOISTURE_CALLBACK_MOISTURE_REACHED,
	                           (void (*)(void))cb_moisture_reached,
	                           NULL);

	// Configure threshold for moisture value "greater than 200"
	moisture_set_moisture_callback_threshold(&m, '>', 200, 0);

	printf("Press key to exit\n");
	getchar();
	moisture_destroy(&m);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
