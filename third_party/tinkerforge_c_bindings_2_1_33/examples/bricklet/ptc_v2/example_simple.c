#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_ptc_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your PTC Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PTCV2 ptc;
	ptc_v2_create(&ptc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current temperature
	int32_t temperature;
	if(ptc_v2_get_temperature(&ptc, &temperature) < 0) {
		fprintf(stderr, "Could not get temperature, probably timeout\n");
		return 1;
	}

	printf("Temperature: %f °C\n", temperature/100.0);

	printf("Press key to exit\n");
	getchar();
	ptc_v2_destroy(&ptc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
