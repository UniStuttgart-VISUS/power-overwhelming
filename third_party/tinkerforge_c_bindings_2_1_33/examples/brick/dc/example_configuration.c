#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "brick_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your DC Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DC dc;
	dc_create(&dc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	dc_set_drive_mode(&dc, DC_DRIVE_MODE_DRIVE_COAST);
	dc_set_pwm_frequency(&dc, 10000); // Use PWM frequency of 10 kHz
	dc_set_acceleration(&dc, 4096); // Slow acceleration (12.5 %/s)
	dc_set_velocity(&dc, 32767); // Full speed forward (100 %)
	dc_enable(&dc); // Enable motor power

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	dc_set_acceleration(&dc, 16384); // Fast decceleration (50 %/s) for stopping
	dc_set_velocity(&dc, 0); // Request motor stop
	millisleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	dc_disable(&dc); // Disable motor power

	dc_destroy(&dc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
