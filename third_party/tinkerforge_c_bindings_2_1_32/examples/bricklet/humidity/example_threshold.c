#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_humidity.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Humidity Bricklet

// Callback function for humidity reached callback
void cb_humidity_reached(uint16_t humidity, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Humidity: %f %%RH\n", humidity/10.0);
	printf("Recommended humidity for human comfort is 30 to 60 %%RH.\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Humidity h;
	humidity_create(&h, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	humidity_set_debounce_period(&h, 10000);

	// Register humidity reached callback to function cb_humidity_reached
	humidity_register_callback(&h,
	                           HUMIDITY_CALLBACK_HUMIDITY_REACHED,
	                           (void (*)(void))cb_humidity_reached,
	                           NULL);

	// Configure threshold for humidity "outside of 30 to 60 %RH"
	humidity_set_humidity_callback_threshold(&h, 'o', 30*10, 60*10);

	printf("Press key to exit\n");
	getchar();
	humidity_destroy(&h);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
