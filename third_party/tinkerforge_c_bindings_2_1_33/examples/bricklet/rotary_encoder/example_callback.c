#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rotary_encoder.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Rotary Encoder Bricklet

// Callback function for count callback
void cb_count(int32_t count, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Count: %d\n", count);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RotaryEncoder re;
	rotary_encoder_create(&re, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register count callback to function cb_count
	rotary_encoder_register_callback(&re,
	                                 ROTARY_ENCODER_CALLBACK_COUNT,
	                                 (void (*)(void))cb_count,
	                                 NULL);

	// Set period for count callback to 0.05s (50ms)
	// Note: The count callback is only called every 0.05 seconds
	//       if the count has changed since the last call!
	rotary_encoder_set_count_callback_period(&re, 50);

	printf("Press key to exit\n");
	getchar();
	rotary_encoder_destroy(&re);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
