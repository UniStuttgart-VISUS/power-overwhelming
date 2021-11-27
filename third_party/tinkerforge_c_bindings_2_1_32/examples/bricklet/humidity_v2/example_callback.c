#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_humidity_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Humidity Bricklet 2.0

// Callback function for humidity callback
void cb_humidity(uint16_t humidity, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Humidity: %f %%RH\n", humidity/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HumidityV2 h;
	humidity_v2_create(&h, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register humidity callback to function cb_humidity
	humidity_v2_register_callback(&h,
	                              HUMIDITY_V2_CALLBACK_HUMIDITY,
	                              (void (*)(void))cb_humidity,
	                              NULL);

	// Set period for humidity callback to 1s (1000ms) without a threshold
	humidity_v2_set_humidity_callback_configuration(&h, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	humidity_v2_destroy(&h);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
