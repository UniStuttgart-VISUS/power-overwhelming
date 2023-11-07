#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dual_relay.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Dual Relay Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DualRelay dr;
	dual_relay_create(&dr, UID, &ipcon);

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
		dual_relay_set_state(&dr, true, false);
		millisleep(1000);
		dual_relay_set_state(&dr, false, true);
	}

	printf("Press key to exit\n");
	getchar();
	dual_relay_destroy(&dr);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
