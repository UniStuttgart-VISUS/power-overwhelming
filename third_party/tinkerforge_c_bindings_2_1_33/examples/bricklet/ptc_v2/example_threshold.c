#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ptc_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your PTC Bricklet 2.0

// Callback function for temperature callback
void cb_temperature(int32_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Temperature: %f °C\n", temperature/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PTCV2 ptc;
	ptc_v2_create(&ptc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register temperature callback to function cb_temperature
	ptc_v2_register_callback(&ptc,
	                         PTC_V2_CALLBACK_TEMPERATURE,
	                         (void (*)(void))cb_temperature,
	                         NULL);

	// Configure threshold for temperature "greater than 30 °C"
	// with a debounce period of 1s (1000ms)
	ptc_v2_set_temperature_callback_configuration(&ptc, 1000, false, '>', 30*100, 0);

	printf("Press key to exit\n");
	getchar();
	ptc_v2_destroy(&ptc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
