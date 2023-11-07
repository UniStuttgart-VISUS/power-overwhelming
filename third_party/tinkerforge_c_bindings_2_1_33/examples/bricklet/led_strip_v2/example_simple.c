#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_led_strip_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LED Strip Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LEDStripV2 ls;
	led_strip_v2_create(&ls, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set first 3 LEDs to red, green and blue
	uint8_t value[9] = {255, 0, 0, 0, 255, 0, 0, 0, 255};
	led_strip_v2_set_led_values(&ls, 0, value, 9);

	printf("Press key to exit\n");
	getchar();
	led_strip_v2_destroy(&ls);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
