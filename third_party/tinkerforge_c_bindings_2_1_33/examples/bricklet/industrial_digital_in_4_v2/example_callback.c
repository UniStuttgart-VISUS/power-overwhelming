#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_in_4_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital In 4 Bricklet 2.0

// Callback function for value callback
void cb_value(uint8_t channel, bool changed, bool value, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(channel == INDUSTRIAL_DIGITAL_IN_4_V2_CHANNEL_0) {
		printf("Channel: 0\n");
	} else if(channel == INDUSTRIAL_DIGITAL_IN_4_V2_CHANNEL_1) {
		printf("Channel: 1\n");
	} else if(channel == INDUSTRIAL_DIGITAL_IN_4_V2_CHANNEL_2) {
		printf("Channel: 2\n");
	} else if(channel == INDUSTRIAL_DIGITAL_IN_4_V2_CHANNEL_3) {
		printf("Channel: 3\n");
	}

	printf("Changed: %s\n", changed ? "true" : "false");
	printf("Value: %s\n", value ? "true" : "false");
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalIn4V2 idi4;
	industrial_digital_in_4_v2_create(&idi4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register value callback to function cb_value
	industrial_digital_in_4_v2_register_callback(&idi4,
	                                             INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_VALUE,
	                                             (void (*)(void))cb_value,
	                                             NULL);

	// Set period for value (channel 1) callback to 0.1s (100ms)
	industrial_digital_in_4_v2_set_value_callback_configuration(&idi4, 1, 100, false);

	printf("Press key to exit\n");
	getchar();
	industrial_digital_in_4_v2_destroy(&idi4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
