#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_relay.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual Relay Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDualRelay idr;
	industrial_dual_relay_create(&idr, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn relays alternating on/off 10 times with 1 second delay
	int i;
	for(i = 0; i < 5; ++i) {
		millisleep(1000);
		industrial_dual_relay_set_value(&idr, true, false);
		millisleep(1000);
		industrial_dual_relay_set_value(&idr, false, true);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_dual_relay_destroy(&idr);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
