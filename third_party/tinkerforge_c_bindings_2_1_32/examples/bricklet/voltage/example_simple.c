#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Voltage v;
	voltage_create(&v, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current voltage
	uint16_t voltage;
	if(voltage_get_voltage(&v, &voltage) < 0) {
		fprintf(stderr, "Could not get voltage, probably timeout\n");
		return 1;
	}

	printf("Voltage: %f V\n", voltage/1000.0);

	printf("Press key to exit\n");
	getchar();
	voltage_destroy(&v);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
