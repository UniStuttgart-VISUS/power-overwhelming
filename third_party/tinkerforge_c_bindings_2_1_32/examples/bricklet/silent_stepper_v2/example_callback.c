#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_silent_stepper_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Silent Stepper Bricklet 2.0

// Use position reached callback to program random movement
void cb_position_reached(int32_t position, void *user_data) {
	(void)position; // avoid unused parameter warning

	SilentStepperV2 *ss = (SilentStepperV2 *)user_data;
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

	silent_stepper_v2_set_speed_ramping(ss, acc, dec);
	silent_stepper_v2_set_max_velocity(ss, vel);
	silent_stepper_v2_set_steps(ss, steps);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SilentStepperV2 ss;
	silent_stepper_v2_create(&ss, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register position reached callback to function cb_position_reached
	silent_stepper_v2_register_callback(&ss,
	                                    SILENT_STEPPER_V2_CALLBACK_POSITION_REACHED,
	                                    (void (*)(void))cb_position_reached,
	                                    &ss);

	silent_stepper_v2_set_step_configuration(&ss, SILENT_STEPPER_V2_STEP_RESOLUTION_8,
	                                         true); // 1/8 steps (interpolated)
	silent_stepper_v2_set_enabled(&ss, true); // Enable motor power
	silent_stepper_v2_set_steps(&ss, 1); // Drive one step forward to get things going

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	silent_stepper_v2_stop(&ss); // Request motor stop
	silent_stepper_v2_set_speed_ramping(&ss, 500,
	                                    5000); // Fast deacceleration (5000 steps/s^2) for stopping
	millisleep(400); // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
	silent_stepper_v2_set_enabled(&ss, false); // Disable motor power

	silent_stepper_v2_destroy(&ss);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
