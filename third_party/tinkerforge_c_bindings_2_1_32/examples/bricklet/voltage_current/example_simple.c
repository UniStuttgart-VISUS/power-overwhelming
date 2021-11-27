#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage_current.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage/Current Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	VoltageCurrent vc;
	voltage_current_create(&vc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current voltage
	int32_t voltage;
	if(voltage_current_get_voltage(&vc, &voltage) < 0) {
		fprintf(stderr, "Could not get voltage, probably timeout\n");
		return 1;
	}

	printf("Voltage: %f V\n", voltage/1000.0);

	// Get current current
	int32_t current;
	if(voltage_current_get_current(&vc, &current) < 0) {
		fprintf(stderr, "Could not get current, probably timeout\n");
		return 1;
	}

	printf("Current: %f A\n", current/1000.0);

	printf("Press key to exit\n");
	getchar();
	voltage_current_destroy(&vc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
