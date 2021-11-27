#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_uv_light_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your UV Light Bricklet 2.0

// Callback function for UV index callback
void cb_uvi(int32_t uvi, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("UV Index: %f\n", uvi/10.0);
	printf("UV index > 3. Use sunscreen!\n");
}

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

	// Register UV index callback to function cb_uvi
	uv_light_v2_register_callback(&uvl,
	                              UV_LIGHT_V2_CALLBACK_UVI,
	                              (void (*)(void))cb_uvi,
	                              NULL);

	// Configure threshold for UV index "greater than 3"
	// with a debounce period of 1s (1000ms)
	uv_light_v2_set_uvi_callback_configuration(&uvl, 1000, false, '>', 3*10, 0);

	printf("Press key to exit\n");
	getchar();
	uv_light_v2_destroy(&uvl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
