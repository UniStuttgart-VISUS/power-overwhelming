#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ambient_light_v3.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

// Callback function for illuminance callback
void cb_illuminance(uint32_t illuminance, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Illuminance: %f lx\n", illuminance/100.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AmbientLightV3 al;
	ambient_light_v3_create(&al, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register illuminance callback to function cb_illuminance
	ambient_light_v3_register_callback(&al,
	                                   AMBIENT_LIGHT_V3_CALLBACK_ILLUMINANCE,
	                                   (void (*)(void))cb_illuminance,
	                                   NULL);

	// Set period for illuminance callback to 1s (1000ms) without a threshold
	ambient_light_v3_set_illuminance_callback_configuration(&al, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	ambient_light_v3_destroy(&al);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
