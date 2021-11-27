#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_quad_relay.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Quad Relay Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialQuadRelay iqr;
	industrial_quad_relay_create(&iqr, UID, &ipcon);

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
		industrial_quad_relay_set_value(&iqr, 1 << 0);
		millisleep(100);
		industrial_quad_relay_set_value(&iqr, 1 << 1);
		millisleep(100);
		industrial_quad_relay_set_value(&iqr, 1 << 2);
		millisleep(100);
		industrial_quad_relay_set_value(&iqr, 1 << 3);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_quad_relay_destroy(&iqr);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
