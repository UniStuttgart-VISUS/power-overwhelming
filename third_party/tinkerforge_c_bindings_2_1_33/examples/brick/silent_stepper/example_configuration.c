#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "brick_silent_stepper.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your Silent Stepper Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SilentStepper ss;
	silent_stepper_create(&ss, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	silent_stepper_set_motor_current(&ss, 800); // 800 mA
	silent_stepper_set_step_configuration(&ss, SILENT_STEPPER_STEP_RESOLUTION_8,
	                                      true); // 1/8 steps (interpolated)
	silent_stepper_set_max_velocity(&ss, 2000); // Velocity 2000 steps/s

	// Slow acceleration (500 steps/s^2),
	// Fast deacceleration (5000 steps/s^2)
	silent_stepper_set_speed_ramping(&ss, 500, 5000);

	silent_stepper_enable(&ss); // Enable motor power
	silent_stepper_set_steps(&ss, 60000); // Drive 60000 steps forward

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	silent_stepper_stop(&ss); // Request motor stop
	silent_stepper_set_speed_ramping(&ss, 500,
	                                 5000); // Fast deacceleration (5000 steps/s^2) for stopping
	millisleep(400); // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
	silent_stepper_disable(&ss); // Disable motor power

	silent_stepper_destroy(&ss);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
