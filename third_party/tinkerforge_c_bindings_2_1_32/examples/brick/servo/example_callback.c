#include <stdio.h>

#include "ip_connection.h"
#include "brick_servo.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your Servo Brick

// Use position reached callback to swing back and forth
void cb_position_reached(uint8_t servo_num, int16_t position, void *user_data) {
	Servo *servo = (Servo *)user_data;

	if(position == 9000) {
		printf("Position: 90°, going to -90°\n");
		servo_set_position(servo, servo_num, -9000);
	} else if(position == -9000) {
		printf("Position: -90°, going to 90°\n");
		servo_set_position(servo, servo_num, 9000);
	} else {
		printf("Error\n"); // Can only happen if another program sets position
	}
}

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

	// Register position reached callback to function cb_position_reached
	servo_register_callback(&servo,
	                        SERVO_CALLBACK_POSITION_REACHED,
	                        (void (*)(void))cb_position_reached,
	                        &servo);

	// Enable position reached callback
	servo_enable_position_reached_callback(&servo);

	// Set velocity to 100°/s. This has to be smaller or equal to the
	// maximum velocity of the servo you are using, otherwise the position
	// reached callback will be called too early
	servo_set_velocity(&servo, 0, 10000);
	servo_set_position(&servo, 0, 9000);
	servo_enable(&servo, 0);

	printf("Press key to exit\n");
	getchar();

	servo_disable(&servo, 0);

	servo_destroy(&servo);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
