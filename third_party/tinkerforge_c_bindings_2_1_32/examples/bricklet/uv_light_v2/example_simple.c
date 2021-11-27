#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_uv_light_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your UV Light Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	UVLightV2 uvl;
	uv_light_v2_create(&uvl, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current UV-A
	int32_t uva;
	if(uv_light_v2_get_uva(&uvl, &uva) < 0) {
		fprintf(stderr, "Could not get UV-A, probably timeout\n");
		return 1;
	}

	printf("UV-A: %f mW/m²\n", uva/10.0);

	// Get current UV-B
	int32_t uvb;
	if(uv_light_v2_get_uvb(&uvl, &uvb) < 0) {
		fprintf(stderr, "Could not get UV-B, probably timeout\n");
		return 1;
	}

	printf("UV-B: %f mW/m²\n", uvb/10.0);

	// Get current UV index
	int32_t uvi;
	if(uv_light_v2_get_uvi(&uvl, &uvi) < 0) {
		fprintf(stderr, "Could not get UV index, probably timeout\n");
		return 1;
	}

	printf("UV Index: %f\n", uvi/10.0);

	printf("Press key to exit\n");
	getchar();
	uv_light_v2_destroy(&uvl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
