#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_solid_state_relay_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Solid State Relay Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SolidStateRelayV2 ssr;
	solid_state_relay_v2_create(&ssr, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn relay on/off 10 times with 1 second delay
	int i;
	for(i = 0; i < 5; ++i) {
		millisleep(1000);
		solid_state_relay_v2_set_state(&ssr, true);
		millisleep(1000);
		solid_state_relay_v2_set_state(&ssr, false);
	}

	printf("Press key to exit\n");
	getchar();
	solid_state_relay_v2_destroy(&ssr);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
