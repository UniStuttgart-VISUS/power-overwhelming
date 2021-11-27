#include <stdio.h>

#include "ip_connection.h"
#include "brick_imu.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your IMU Brick

// Callback function for quaternion callback
void cb_quaternion(float x, float y, float z, float w, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Quaternion [X]: %f\n", x);
	printf("Quaternion [Y]: %f\n", y);
	printf("Quaternion [Z]: %f\n", z);
	printf("Quaternion [W]: %f\n", w);
	printf("\n");
}

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

	// Register quaternion callback to function cb_quaternion
	imu_register_callback(&imu,
	                      IMU_CALLBACK_QUATERNION,
	                      (void (*)(void))cb_quaternion,
	                      NULL);

	// Set period for quaternion callback to 1s (1000ms)
	imu_set_quaternion_period(&imu, 1000);

	printf("Press key to exit\n");
	getchar();
	imu_destroy(&imu);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
