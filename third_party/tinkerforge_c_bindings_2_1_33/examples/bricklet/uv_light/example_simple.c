#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_uv_light.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your UV Light Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	UVLight uvl;
	uv_light_create(&uvl, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current UV light
	uint32_t uv_light;
	if(uv_light_get_uv_light(&uvl, &uv_light) < 0) {
		fprintf(stderr, "Could not get UV light, probably timeout\n");
		return 1;
	}

	printf("UV Light: %f mW/m²\n", uv_light/10.0);

	printf("Press key to exit\n");
	getchar();
	uv_light_destroy(&uvl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
