#include <stdio.h>

#include "ip_connection.h"
#include "brick_hat.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your HAT Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HAT hat;
	hat_create(&hat, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn Raspberry Pi and Bricklets off in 2 seconds for 30 minutes with sleep indicator enabled
	hat_set_sleep_mode(&hat, 2, 1800, true, true, true);

	printf("Press key to exit\n");
	getchar();
	hat_destroy(&hat);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
