#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io16_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-16 Bricklet 2.0

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

	// Configure channel 7 [A7] as output low
	io16_v2_set_configuration(&io, 7, 'o', false);

	// Set channel 7 [A7] alternating high/low 10 times with 100 ms delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(100);
		io16_v2_set_selected_value(&io, 7, true);
		millisleep(100);
		io16_v2_set_selected_value(&io, 7, false);
	}

	printf("Press key to exit\n");
	getchar();
	io16_v2_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
