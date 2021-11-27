#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motorized_linear_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Motorized Linear Poti Bricklet

// Callback function for position callback
void cb_position(uint16_t position, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Position: %u\n", position); // Range: 0 to 100
}

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

	// Register position callback to function cb_position
	motorized_linear_poti_register_callback(&mlp,
	                                        MOTORIZED_LINEAR_POTI_CALLBACK_POSITION,
	                                        (void (*)(void))cb_position,
	                                        NULL);

	// Set period for position callback to 0.05s (50ms) without a threshold
	motorized_linear_poti_set_position_callback_configuration(&mlp, 50, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	motorized_linear_poti_destroy(&mlp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
