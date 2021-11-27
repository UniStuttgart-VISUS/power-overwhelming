#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_compass.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Compass Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Compass c;
	compass_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current heading
	int16_t heading;
	if(compass_get_heading(&c, &heading) < 0) {
		fprintf(stderr, "Could not get heading, probably timeout\n");
		return 1;
	}

	printf("Heading: %f °\n", heading/10.0);

	printf("Press key to exit\n");
	getchar();
	compass_destroy(&c);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
