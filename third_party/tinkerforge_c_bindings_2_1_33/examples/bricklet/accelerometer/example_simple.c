#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_accelerometer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Accelerometer Bricklet

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

	// Get current acceleration
	int16_t x, y, z;
	if(accelerometer_get_acceleration(&a, &x, &y, &z) < 0) {
		fprintf(stderr, "Could not get acceleration, probably timeout\n");
		return 1;
	}

	printf("Acceleration [X]: %f g\n", x/1000.0);
	printf("Acceleration [Y]: %f g\n", y/1000.0);
	printf("Acceleration [Z]: %f g\n", z/1000.0);

	printf("Press key to exit\n");
	getchar();
	accelerometer_destroy(&a);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
