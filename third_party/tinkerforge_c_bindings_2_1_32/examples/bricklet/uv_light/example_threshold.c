#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_uv_light.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your UV Light Bricklet

// Callback function for UV light reached callback
void cb_uv_light_reached(uint32_t uv_light, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("UV Light: %f mW/m²\n", uv_light/10.0);
	printf("UV Index > 3. Use sunscreen!\n");
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

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	uv_light_set_debounce_period(&uvl, 10000);

	// Register UV light reached callback to function cb_uv_light_reached
	uv_light_register_callback(&uvl,
	                           UV_LIGHT_CALLBACK_UV_LIGHT_REACHED,
	                           (void (*)(void))cb_uv_light_reached,
	                           NULL);

	// Configure threshold for UV light "greater than 75 mW/m²"
	uv_light_set_uv_light_callback_threshold(&uvl, '>', 75*10, 0);

	printf("Press key to exit\n");
	getchar();
	uv_light_destroy(&uvl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
