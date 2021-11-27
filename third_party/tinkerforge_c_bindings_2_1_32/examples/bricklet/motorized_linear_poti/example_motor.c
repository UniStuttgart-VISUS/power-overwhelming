#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_motorized_linear_poti.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Motorized Linear Poti Bricklet

// Callback function for position reached callback
void cb_position_reached(uint16_t position, void *user_data) {
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

	// Register position reached callback to function cb_position_reached
	motorized_linear_poti_register_callback(&mlp,
	                                        MOTORIZED_LINEAR_POTI_CALLBACK_POSITION_REACHED,
	                                        (void (*)(void))cb_position_reached,
	                                        NULL);

	// Move slider smooth to the middle
	motorized_linear_poti_set_motor_position(&mlp, 50,
	                                         MOTORIZED_LINEAR_POTI_DRIVE_MODE_SMOOTH,
	                                         false);

	printf("Press key to exit\n");
	getchar();
	motorized_linear_poti_destroy(&mlp);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
