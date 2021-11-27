#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_analog_in_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual Analog In Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDualAnalogInV2 idai;
	industrial_dual_analog_in_v2_create(&idai, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current voltage from channel 0
	int32_t voltage;
	if(industrial_dual_analog_in_v2_get_voltage(&idai, 0, &voltage) < 0) {
		fprintf(stderr, "Could not get voltage from channel 0, probably timeout\n");
		return 1;
	}

	printf("Voltage (Channel 0): %f V\n", voltage/1000.0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_analog_in_v2_destroy(&idai);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
