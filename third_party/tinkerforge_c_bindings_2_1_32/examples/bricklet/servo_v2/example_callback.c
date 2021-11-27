#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_servo_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Servo Bricklet 2.0

// Use position reached callback to swing back and forth
void cb_position_reached(uint16_t servo_channel, int16_t position, void *user_data) {
	ServoV2 *s = (ServoV2 *)user_data;

	if(position == 9000) {
		printf("Position: 90°, going to -90°\n");
		servo_v2_set_position(s, servo_channel, -9000);
	} else if(position == -9000) {
		printf("Position: -90°, going to 90°\n");
		servo_v2_set_position(s, servo_channel, 9000);
	} else {
		printf("Error\n"); // Can only happen if another program sets position
	}
}

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

	// Register position reached callback to function cb_position_reached
	servo_v2_register_callback(&s,
	                           SERVO_V2_CALLBACK_POSITION_REACHED,
	                           (void (*)(void))cb_position_reached,
	                           &s);

	// Enable position reached callback
	servo_v2_set_position_reached_callback_configuration(&s, 0, true);

	// Set velocity to 100°/s. This has to be smaller or equal to the
	// maximum velocity of the servo you are using, otherwise the position
	// reached callback will be called too early
	servo_v2_set_motion_configuration(&s, 0, 10000, 500000, 500000);
	servo_v2_set_position(&s, 0, 9000);
	servo_v2_set_enable(&s, 0, true);

	printf("Press key to exit\n");
	getchar();

	servo_v2_set_enable(&s, 0, false);

	servo_v2_destroy(&s);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
