#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_moisture.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Moisture Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Moisture m;
	moisture_create(&m, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current moisture value
	uint16_t moisture;
	if(moisture_get_moisture_value(&m, &moisture) < 0) {
		fprintf(stderr, "Could not get moisture value, probably timeout\n");
		return 1;
	}

	printf("Moisture Value: %u\n", moisture);

	printf("Press key to exit\n");
	getchar();
	moisture_destroy(&m);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
