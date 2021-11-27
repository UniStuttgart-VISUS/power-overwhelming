#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ambient_light_v3.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

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

	// Get current Illuminance
	uint32_t illuminance;
	if(ambient_light_v3_get_illuminance(&al, &illuminance) < 0) {
		fprintf(stderr, "Could not get Illuminance, probably timeout\n");
		return 1;
	}

	printf("Illuminance: %f lx\n", illuminance/100.0);

	printf("Press key to exit\n");
	getchar();
	ambient_light_v3_destroy(&al);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
