#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_0_20ma_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual 0-20mA Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDual020mAV2 id020;
	industrial_dual_0_20ma_v2_create(&id020, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current current from channel 0
	int32_t current;
	if(industrial_dual_0_20ma_v2_get_current(&id020, 0, &current) < 0) {
		fprintf(stderr, "Could not get current from channel 0, probably timeout\n");
		return 1;
	}

	printf("Current (Channel 0): %f mA\n", current/1000000.0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_0_20ma_v2_destroy(&id020);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
