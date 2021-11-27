#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_isolator.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Isolator Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Isolator i;
	isolator_create(&i, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current statistics
	uint32_t messages_from_brick, messages_from_bricklet;
	uint16_t connected_bricklet_device_identifier; char connected_bricklet_uid[8];
	if(isolator_get_statistics(&i, &messages_from_brick, &messages_from_bricklet,
	                           &connected_bricklet_device_identifier,
	                           connected_bricklet_uid) < 0) {
		fprintf(stderr, "Could not get statistics, probably timeout\n");
		return 1;
	}

	printf("Messages From Brick: %u\n", messages_from_brick);
	printf("Messages From Bricklet: %u\n", messages_from_bricklet);
	printf("Connected Bricklet Device Identifier: %u\n", connected_bricklet_device_identifier);
	printf("Connected Bricklet UID: %s\n", connected_bricklet_uid);

	printf("Press key to exit\n");
	getchar();
	isolator_destroy(&i);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
