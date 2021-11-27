#include <stdio.h>

#include "ip_connection.h"
#include "brick_servo.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your Servo Brick

// Due to the internal clock dividing mechanism of the Servo Brick not all
// arbitrary PWM frequency values can be achieved. For example, the upper most
// three available PWM frequency values are 1MHz, 500kHz and 250kHz. The steps
// are coarser on the high frequency end and much finer on the low end. You can
// set any value here between 15Hz and 1MHz and the Servo Brick will try to
// match it as closely as possible.
#define PWM_FREQUENCY 175000 // in Hz [15Hz to 1MHz]
#define PWM_DUTY_CYCLE 20 // in % [0% to 100%]

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Servo servo;
	servo_create(&servo, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set degree range to 0-100, this will allow to
	// set the PWM duty cycle in 1% steps
	servo_set_degree(&servo, 0, 0, 100);

	// Set PWM frequency (1-65535µs == 1MHz-15Hz)
	int period = 1000000 / PWM_FREQUENCY;

	if (period < 1) {
		period = 1; // 1MHz
	} else if (period > 65535) {
		period = 65535; // ~15Hz
	}

	servo_set_pulse_width(&servo, 0, 0, period);
	servo_set_period(&servo, 0, period);

	// Fast acceleration and full speed
	servo_set_acceleration(&servo, 0, 65535);
	servo_set_velocity(&servo, 0, 65535);

	// Set PWM duty cycle (0-100 %)
	int position = PWM_DUTY_CYCLE;

	if (position < 0) {
		position = 0;
	} else if (position > 100) {
		position = 100;
	}

	servo_set_position(&servo, 0, position);

	// Enable PWM signal
	servo_enable(&servo, 0);

	printf("Press key to exit\n");
	getchar();
	servo_disable(&servo, 0);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
