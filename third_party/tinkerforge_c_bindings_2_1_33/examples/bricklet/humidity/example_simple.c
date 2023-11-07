#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_humidity.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Humidity Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Humidity h;
	humidity_create(&h, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current humidity
	uint16_t humidity;
	if(humidity_get_humidity(&h, &humidity) < 0) {
		fprintf(stderr, "Could not get humidity, probably timeout\n");
		return 1;
	}

	printf("Humidity: %f %%RH\n", humidity/10.0);

	printf("Press key to exit\n");
	getchar();
	humidity_destroy(&h);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
