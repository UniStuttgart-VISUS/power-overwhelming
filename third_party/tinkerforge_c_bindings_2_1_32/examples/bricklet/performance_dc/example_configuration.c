#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_performance_dc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Performance DC Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PerformanceDC pdc;
	performance_dc_create(&pdc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	performance_dc_set_drive_mode(&pdc, PERFORMANCE_DC_DRIVE_MODE_DRIVE_COAST);
	performance_dc_set_pwm_frequency(&pdc, 10000); // Use PWM frequency of 10 kHz
	performance_dc_set_motion(&pdc, 4096, 4096); // Slow ac-/deceleration (12.5 %/s)
	performance_dc_set_velocity(&pdc, 32767); // Full speed forward (100 %)
	performance_dc_set_enabled(&pdc, true); // Enable motor power

	printf("Press key to exit\n");
	getchar();

	// Stop motor before disabling motor power
	performance_dc_set_motion(&pdc, 4096,
	                          16384); // Fast decceleration (50 %/s) for stopping
	performance_dc_set_velocity(&pdc, 0); // Request motor stop
	millisleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	performance_dc_set_enabled(&pdc, false); // Disable motor power

	performance_dc_destroy(&pdc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
