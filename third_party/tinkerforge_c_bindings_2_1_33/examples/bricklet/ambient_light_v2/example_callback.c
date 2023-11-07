#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ambient_light_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 2.0

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
	AmbientLightV2 al;
	ambient_light_v2_create(&al, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register illuminance callback to function cb_illuminance
	ambient_light_v2_register_callback(&al,
	                                   AMBIENT_LIGHT_V2_CALLBACK_ILLUMINANCE,
	                                   (void (*)(void))cb_illuminance,
	                                   NULL);

	// Set period for illuminance callback to 1s (1000ms)
	// Note: The illuminance callback is only called every second
	//       if the illuminance has changed since the last call!
	ambient_light_v2_set_illuminance_callback_period(&al, 1000);

	printf("Press key to exit\n");
	getchar();
	ambient_light_v2_destroy(&al);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
