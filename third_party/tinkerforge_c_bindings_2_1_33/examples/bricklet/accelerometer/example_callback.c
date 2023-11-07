#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_accelerometer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Accelerometer Bricklet

// Callback function for acceleration callback
void cb_acceleration(int16_t x, int16_t y, int16_t z, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Acceleration [X]: %f g\n", x/1000.0);
	printf("Acceleration [Y]: %f g\n", y/1000.0);
	printf("Acceleration [Z]: %f g\n", z/1000.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Accelerometer a;
	accelerometer_create(&a, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register acceleration callback to function cb_acceleration
	accelerometer_register_callback(&a,
	                                ACCELEROMETER_CALLBACK_ACCELERATION,
	                                (void (*)(void))cb_acceleration,
	                                NULL);

	// Set period for acceleration callback to 1s (1000ms)
	// Note: The acceleration callback is only called every second
	//       if the acceleration has changed since the last call!
	accelerometer_set_acceleration_callback_period(&a, 1000);

	printf("Press key to exit\n");
	getchar();
	accelerometer_destroy(&a);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
