#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_servo_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Servo Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	ServoV2 s;
	servo_v2_create(&s, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
	//          and operating angle -100 to 100°
	servo_v2_set_degree(&s, 0, -10000, 10000);
	servo_v2_set_pulse_width(&s, 0, 1000, 2000);
	servo_v2_set_period(&s, 0, 19500);
	servo_v2_set_motion_configuration(&s, 0, 500000, 1000,
	                                  1000); // Full velocity with slow ac-/deceleration


	// Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95 to 1.95ms
	//          and operating angle -90 to 90°
	servo_v2_set_degree(&s, 5, -9000, 9000);
	servo_v2_set_pulse_width(&s, 5, 950, 1950);
	servo_v2_set_period(&s, 5, 20000);
	servo_v2_set_motion_configuration(&s, 5, 500000, 500000,
	                                  500000); // Full velocity with full ac-/deceleration

	servo_v2_set_position(&s, 0, 10000); // Set to most right position
	servo_v2_set_enable(&s, 0, true);

	servo_v2_set_position(&s, 5, -9000); // Set to most left position
	servo_v2_set_enable(&s, 5, true);

	printf("Press key to exit\n");
	getchar();

	servo_v2_set_enable(&s, 0, false);
	servo_v2_set_enable(&s, 5, false);

	servo_v2_destroy(&s);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
