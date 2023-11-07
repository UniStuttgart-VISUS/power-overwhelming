#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "brick_stepper.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your Stepper Brick

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

	stepper_set_motor_current(&stepper, 800); // 800 mA
	stepper_set_step_mode(&stepper, 8); // 1/8 step mode
	stepper_set_max_velocity(&stepper, 2000); // Velocity 2000 steps/s

	// Slow acceleration (500 steps/s^2),
	// Fast deacceleration (5000 steps/s^2)
	stepper_set_speed_ramping(&stepper, 500, 5000);

	stepper_enable(&stepper); // Enable motor power
	stepper_set_steps(&stepper, 60000); // Drive 60000 steps forward

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
