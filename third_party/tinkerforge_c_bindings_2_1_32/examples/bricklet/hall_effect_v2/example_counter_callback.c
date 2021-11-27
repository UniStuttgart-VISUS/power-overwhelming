#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_hall_effect_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet 2.0

// Callback function for counter callback
void cb_counter(uint32_t counter, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Counter: %u\n", counter);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HallEffectV2 he;
	hall_effect_v2_create(&he, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Configure counter with ±3000µT threshold and 10ms debounce
	hall_effect_v2_set_counter_config(&he, 3000, -3000, 10000);

	// Register counter callback to function cb_counter
	hall_effect_v2_register_callback(&he,
	                                 HALL_EFFECT_V2_CALLBACK_COUNTER,
	                                 (void (*)(void))cb_counter,
	                                 NULL);

	// Set period for counter callback to 0.1s (100ms)
	hall_effect_v2_set_counter_callback_configuration(&he, 100, true);

	printf("Press key to exit\n");
	getchar();
	hall_effect_v2_destroy(&he);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
