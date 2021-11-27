#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_analog_out_v3.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Analog Out Bricklet 3.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AnalogOutV3 ao;
	analog_out_v3_create(&ao, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set output voltage to 3.3V
	analog_out_v3_set_output_voltage(&ao, 3300);

	printf("Press key to exit\n");
	getchar();
	analog_out_v3_destroy(&ao);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
