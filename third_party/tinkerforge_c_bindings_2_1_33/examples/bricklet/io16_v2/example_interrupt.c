#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io16_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-16 Bricklet 2.0

// Callback function for input value callback
void cb_input_value(uint8_t channel, bool changed, bool value, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Channel: %u\n", channel);
	printf("Changed: %s\n", changed ? "true" : "false");
	printf("Value: %s\n", value ? "true" : "false");
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO16V2 io;
	io16_v2_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register input value callback to function cb_input_value
	io16_v2_register_callback(&io,
	                          IO16_V2_CALLBACK_INPUT_VALUE,
	                          (void (*)(void))cb_input_value,
	                          NULL);

	// Set period for input value (channel 4 [A4]) callback to 0.5s (500ms)
	io16_v2_set_input_value_callback_configuration(&io, 4, 500, false);

	printf("Press key to exit\n");
	getchar();
	io16_v2_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
