#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ambient_light.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet

// Callback function for illuminance callback
void cb_illuminance(uint16_t illuminance, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Illuminance: %f lx\n", illuminance/10.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AmbientLight al;
	ambient_light_create(&al, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register illuminance callback to function cb_illuminance
	ambient_light_register_callback(&al,
	                                AMBIENT_LIGHT_CALLBACK_ILLUMINANCE,
	                                (void (*)(void))cb_illuminance,
	                                NULL);

	// Set period for illuminance callback to 1s (1000ms)
	// Note: The illuminance callback is only called every second
	//       if the illuminance has changed since the last call!
	ambient_light_set_illuminance_callback_period(&al, 1000);

	printf("Press key to exit\n");
	getchar();
	ambient_light_destroy(&al);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
