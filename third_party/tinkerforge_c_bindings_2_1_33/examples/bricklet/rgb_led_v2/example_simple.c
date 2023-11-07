#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rgb_led_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RGB LED Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RGBLEDV2 rl;
	rgb_led_v2_create(&rl, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set light blue color
	rgb_led_v2_set_rgb_value(&rl, 0, 170, 234);

	printf("Press key to exit\n");
	getchar();
	rgb_led_v2_destroy(&rl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
