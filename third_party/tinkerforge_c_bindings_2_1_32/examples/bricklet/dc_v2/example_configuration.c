#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_dc_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your DC Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	DCV2 dc;
	dc_v2_create(&dc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	dc_v2_set_drive_mode(&dc, DC_V2_DRIVE_MODE_DRIVE_COAST);
	dc_v2_set_pwm_frequency(&dc, 10000); // Use PWM frequency of 10 kHz
	dc_v2_set_motion(&dc, 4096,
	                 16384); // Slow acceleration (12.5 %/s), fast decceleration (50 %/s) for stopping
	dc_v2_set_velocity(&dc, 32767); // Full speed forward (100 %)
	dc_v2_set_enabled(&dc, true); // Enable motor power

	printf("Press key to exit\n");
	getchar();

	dc_v2_set_velocity(&dc, 0); // Stop motor before disabling motor power
	millisleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	dc_v2_set_enabled(&dc, false); // Disable motor power

	dc_v2_destroy(&dc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
