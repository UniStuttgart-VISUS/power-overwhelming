#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>
#include <stdlib.h>

#include "ip_connection.h"
#include "brick_stepper.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your Stepper Brick

// Use position reached callback to program random movement
void cb_position_reached(int32_t position, void *user_data) {
	(void)position; // avoid unused parameter warning

	Stepper *stepper = (Stepper *)user_data;
	int32_t steps;

	if(rand() % 2) {
		steps = (rand() % 4000) + 1000; // steps (forward)
		printf("Driving forward: %d steps\n", steps);
	} else {
		steps = -((rand() % 4000) + 1000); // steps (backward)
		printf("Driving backward: %d steps\n", steps);
	}

	int16_t vel = (rand() % 1800) + 200; // steps/s
	uint16_t acc = (rand() % 900) + 100; // steps/s^2
	uint16_t dec = (rand() % 900) + 100; // steps/s^2

	printf("Configuration (vel, acc, dec): %d, %d %d\n", vel, acc, dec);

	stepper_set_speed_ramping(stepper, acc, dec);
	stepper_set_max_velocity(stepper, vel);
	stepper_set_steps(stepper, steps);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Stepper stepper;
	stepper_create(&stepper, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register position reached callback to function cb_position_reached
	stepper_register_callback(&stepper,
	                          STEPPER_CALLBACK_POSITION_REACHED,
	                          (void (*)(void))cb_position_reached,
	                          &stepper);

	stepper_enable(&stepper); // Enable motor power
	stepper_set_steps(&stepper, 1); // Drive one step forward to get things going

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	stepper_stop(&stepper); // Request motor stop
	stepper_set_speed_ramping(&stepper, 500,
	                          5000); // Fast deacceleration (5000 steps/s^2) for stopping
	millisleep(400); // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
	stepper_disable(&stepper); // Disable motor power

	stepper_destroy(&stepper);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
