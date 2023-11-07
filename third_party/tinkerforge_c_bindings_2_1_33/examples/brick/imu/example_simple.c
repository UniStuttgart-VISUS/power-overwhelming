#include <stdio.h>

#include "ip_connection.h"
#include "brick_imu.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your IMU Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IMU imu;
	imu_create(&imu, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current quaternion
	float x, y, z, w;
	if(imu_get_quaternion(&imu, &x, &y, &z, &w) < 0) {
		fprintf(stderr, "Could not get quaternion, probably timeout\n");
		return 1;
	}

	printf("Quaternion [X]: %f\n", x);
	printf("Quaternion [Y]: %f\n", y);
	printf("Quaternion [Z]: %f\n", z);
	printf("Quaternion [W]: %f\n", w);

	printf("Press key to exit\n");
	getchar();
	imu_destroy(&imu);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
