#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_analog_out.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Analog Out Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialAnalogOut iao;
	industrial_analog_out_create(&iao, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set output voltage to 3.3V
	industrial_analog_out_set_voltage(&iao, 3300);
	industrial_analog_out_enable(&iao);

	printf("Press key to exit\n");
	getchar();

	industrial_analog_out_disable(&iao);

	industrial_analog_out_destroy(&iao);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
