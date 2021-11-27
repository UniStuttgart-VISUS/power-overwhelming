#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_accelerometer_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Accelerometer Bricklet 2.0

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

	// Get current acceleration
	int32_t x, y, z;
	if(accelerometer_v2_get_acceleration(&a, &x, &y, &z) < 0) {
		fprintf(stderr, "Could not get acceleration, probably timeout\n");
		return 1;
	}

	printf("Acceleration [X]: %f g\n", x/10000.0);
	printf("Acceleration [Y]: %f g\n", y/10000.0);
	printf("Acceleration [Z]: %f g\n", z/10000.0);

	printf("Press key to exit\n");
	getchar();
	accelerometer_v2_destroy(&a);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
