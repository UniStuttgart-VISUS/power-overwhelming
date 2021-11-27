#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_accelerometer_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Accelerometer Bricklet 2.0

// Callback function for acceleration callback
void cb_acceleration(int32_t x, int32_t y, int32_t z, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Acceleration [X]: %f g\n", x/10000.0);
	printf("Acceleration [Y]: %f g\n", y/10000.0);
	printf("Acceleration [Z]: %f g\n", z/10000.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AccelerometerV2 a;
	accelerometer_v2_create(&a, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register acceleration callback to function cb_acceleration
	accelerometer_v2_register_callback(&a,
	                                   ACCELEROMETER_V2_CALLBACK_ACCELERATION,
	                                   (void (*)(void))cb_acceleration,
	                                   NULL);

	// Set period for acceleration callback to 1s (1000ms)
	accelerometer_v2_set_acceleration_callback_configuration(&a, 1000, false);

	printf("Press key to exit\n");
	getchar();
	accelerometer_v2_destroy(&a);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
