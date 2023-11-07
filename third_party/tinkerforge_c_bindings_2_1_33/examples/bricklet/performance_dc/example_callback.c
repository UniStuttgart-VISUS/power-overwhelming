#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_performance_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Performance DC Bricklet

// Use velocity reached callback to swing back and forth
// between full speed forward and full speed backward
void cb_velocity_reached(int16_t velocity, void *user_data) {
	PerformanceDC *pdc = (PerformanceDC *)user_data;

	if(velocity == 32767) {
		printf("Velocity: Full speed forward, now turning backward\n");
		performance_dc_set_velocity(pdc, -32767);
	} else if(velocity == -32767) {
		printf("Velocity: Full speed backward, now turning forward\n");
		performance_dc_set_velocity(pdc, 32767);
	} else {
		printf("Error\n"); // Can only happen if another program sets velocity
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PerformanceDC pdc;
	performance_dc_create(&pdc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register velocity reached callback to function cb_velocity_reached
	performance_dc_register_callback(&pdc,
	                                 PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED,
	                                 (void (*)(void))cb_velocity_reached,
	                                 &pdc);

	// Enable velocity reached callback
	performance_dc_set_velocity_reached_callback_configuration(&pdc, true);

	// The acceleration has to be smaller or equal to the maximum
	// acceleration of the DC motor, otherwise the velocity reached
	// callback will be called too early
	performance_dc_set_motion(&pdc, 4096, 4096); // Slow acceleration (12.5 %/s)
	performance_dc_set_velocity(&pdc, 32767); // Full speed forward (100 %)

	// Enable motor power
	performance_dc_set_enabled(&pdc, true);

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	performance_dc_set_motion(&pdc, 4096,
	                          16384); // Fast decceleration (50 %/s) for stopping
	performance_dc_set_velocity(&pdc, 0); // Request motor stop
	millisleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	performance_dc_set_enabled(&pdc, false); // Disable motor power

	performance_dc_destroy(&pdc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
