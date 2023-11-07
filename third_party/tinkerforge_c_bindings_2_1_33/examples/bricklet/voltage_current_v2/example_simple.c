#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_voltage_current_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Voltage/Current Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	VoltageCurrentV2 vc;
	voltage_current_v2_create(&vc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current voltage
	int32_t voltage;
	if(voltage_current_v2_get_voltage(&vc, &voltage) < 0) {
		fprintf(stderr, "Could not get voltage, probably timeout\n");
		return 1;
	}

	printf("Voltage: %f V\n", voltage/1000.0);

	// Get current current
	int32_t current;
	if(voltage_current_v2_get_current(&vc, &current) < 0) {
		fprintf(stderr, "Could not get current, probably timeout\n");
		return 1;
	}

	printf("Current: %f A\n", current/1000.0);

	printf("Press key to exit\n");
	getchar();
	voltage_current_v2_destroy(&vc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
