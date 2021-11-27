#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_accelerometer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Accelerometer Bricklet

// Callback function for acceleration reached callback
void cb_acceleration_reached(int16_t x, int16_t y, int16_t z, void *user_data) {
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

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	accelerometer_set_debounce_period(&a, 10000);

	// Register acceleration reached callback to function cb_acceleration_reached
	accelerometer_register_callback(&a,
	                                ACCELEROMETER_CALLBACK_ACCELERATION_REACHED,
	                                (void (*)(void))cb_acceleration_reached,
	                                NULL);

	// Configure threshold for acceleration "greater than 2 g, 2 g, 2 g"
	accelerometer_set_acceleration_callback_threshold(&a, '>', 2*1000, 0, 2*1000, 0, 2*1000, 0);

	printf("Press key to exit\n");
	getchar();
	accelerometer_destroy(&a);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
