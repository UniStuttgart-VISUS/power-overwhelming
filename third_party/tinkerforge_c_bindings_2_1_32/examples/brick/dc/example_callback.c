#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "brick_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your DC Brick

// Use velocity reached callback to swing back and forth
// between full speed forward and full speed backward
void cb_velocity_reached(int16_t velocity, void *user_data) {
	DC *dc = (DC *)user_data;

	if(velocity == 32767) {
		printf("Velocity: Full speed forward, now turning backward\n");
		dc_set_velocity(dc, -32767);
	} else if(velocity == -32767) {
		printf("Velocity: Full speed backward, now turning forward\n");
		dc_set_velocity(dc, 32767);
	} else {
		printf("Error\n"); // Can only happen if another program sets velocity
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DC dc;
	dc_create(&dc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// The acceleration has to be smaller or equal to the maximum
	// acceleration of the DC motor, otherwise the velocity reached
	// callback will be called too early
	dc_set_acceleration(&dc, 4096); // Slow acceleration (12.5 %/s)
	dc_set_velocity(&dc, 32767); // Full speed forward (100 %)

	// Register velocity reached callback to function cb_velocity_reached
	dc_register_callback(&dc,
	                     DC_CALLBACK_VELOCITY_REACHED,
	                     (void (*)(void))cb_velocity_reached,
	                     &dc);

	// Enable motor power
	dc_enable(&dc);

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	dc_set_acceleration(&dc, 16384); // Fast decceleration (50 %/s) for stopping
	dc_set_velocity(&dc, 0); // Request motor stop
	millisleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	dc_disable(&dc); // Disable motor power

	dc_destroy(&dc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
