#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_moisture.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Moisture Bricklet

// Callback function for moisture value callback
void cb_moisture(uint16_t moisture, void *user_data) {
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

	// Register moisture value callback to function cb_moisture
	moisture_register_callback(&m,
	                           MOISTURE_CALLBACK_MOISTURE,
	                           (void (*)(void))cb_moisture,
	                           NULL);

	// Set period for moisture value callback to 1s (1000ms)
	// Note: The moisture value callback is only called every second
	//       if the moisture value has changed since the last call!
	moisture_set_moisture_callback_period(&m, 1000);

	printf("Press key to exit\n");
	getchar();
	moisture_destroy(&m);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
