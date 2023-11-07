#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_uv_light.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your UV Light Bricklet

// Callback function for UV light callback
void cb_uv_light(uint32_t uv_light, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("UV Light: %f mW/m²\n", uv_light/10.0);
}

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

	// Register UV light callback to function cb_uv_light
	uv_light_register_callback(&uvl,
	                           UV_LIGHT_CALLBACK_UV_LIGHT,
	                           (void (*)(void))cb_uv_light,
	                           NULL);

	// Set period for UV light callback to 1s (1000ms)
	// Note: The UV light callback is only called every second
	//       if the UV light has changed since the last call!
	uv_light_set_uv_light_callback_period(&uvl, 1000);

	printf("Press key to exit\n");
	getchar();
	uv_light_destroy(&uvl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
