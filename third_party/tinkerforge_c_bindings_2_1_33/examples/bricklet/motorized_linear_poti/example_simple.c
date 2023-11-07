#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motorized_linear_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Motorized Linear Poti Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	MotorizedLinearPoti mlp;
	motorized_linear_poti_create(&mlp, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current position
	uint16_t position;
	if(motorized_linear_poti_get_position(&mlp, &position) < 0) {
		fprintf(stderr, "Could not get position, probably timeout\n");
		return 1;
	}

	printf("Position: %u\n", position); // Range: 0 to 100

	printf("Press key to exit\n");
	getchar();
	motorized_linear_poti_destroy(&mlp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
