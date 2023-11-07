#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_in_4_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital In 4 Bricklet 2.0

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

	// Configure rising edge count (channel 3) with 10ms debounce
	industrial_digital_in_4_v2_set_edge_count_configuration(&idi4, 3, 0, 10);

	// Get edge count 10 times with 1s delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(1000);

		// Get current edge count
		uint32_t count;
		if(industrial_digital_in_4_v2_get_edge_count(&idi4, 3, false, &count) < 0) {
			fprintf(stderr, "Could not get edge count, probably timeout\n");
			return 1;
		}

		printf("Count: %u\n", count);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_digital_in_4_v2_destroy(&idi4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
