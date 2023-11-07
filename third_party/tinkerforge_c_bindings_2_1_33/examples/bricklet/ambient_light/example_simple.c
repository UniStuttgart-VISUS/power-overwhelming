#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ambient_light.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet

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

	// Get current illuminance
	uint16_t illuminance;
	if(ambient_light_get_illuminance(&al, &illuminance) < 0) {
		fprintf(stderr, "Could not get illuminance, probably timeout\n");
		return 1;
	}

	printf("Illuminance: %f lx\n", illuminance/10.0);

	printf("Press key to exit\n");
	getchar();
	ambient_light_destroy(&al);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
