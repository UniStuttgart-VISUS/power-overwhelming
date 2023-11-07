#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_quad_relay_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Quad Relay Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialQuadRelayV2 iqr;
	industrial_quad_relay_v2_create(&iqr, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn relays alternating on/off 10 times with 100 ms delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(100);
		bool value[4] = {true, false, false, false};
		industrial_quad_relay_v2_set_value(&iqr, value);
		millisleep(100);
		bool value_1[4] = {false, true, false, false};
		industrial_quad_relay_v2_set_value(&iqr, value_1);
		millisleep(100);
		bool value_2[4] = {false, false, true, false};
		industrial_quad_relay_v2_set_value(&iqr, value_2);
		millisleep(100);
		bool value_3[4] = {false, false, false, true};
		industrial_quad_relay_v2_set_value(&iqr, value_3);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_quad_relay_v2_destroy(&iqr);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
