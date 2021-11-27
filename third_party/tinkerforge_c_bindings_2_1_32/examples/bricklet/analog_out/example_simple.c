#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_analog_out.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Analog Out Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AnalogOut ao;
	analog_out_create(&ao, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set output voltage to 3.3V
	analog_out_set_voltage(&ao, 3300);

	printf("Press key to exit\n");
	getchar();
	analog_out_destroy(&ao);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
