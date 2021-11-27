#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_temperature_ir_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Temperature IR Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	TemperatureIRV2 tir;
	temperature_ir_v2_create(&tir, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current ambient temperature
	int16_t ambient_temperature;
	if(temperature_ir_v2_get_ambient_temperature(&tir, &ambient_temperature) < 0) {
		fprintf(stderr, "Could not get ambient temperature, probably timeout\n");
		return 1;
	}

	printf("Ambient Temperature: %f °C\n", ambient_temperature/10.0);

	// Get current object temperature
	int16_t object_temperature;
	if(temperature_ir_v2_get_object_temperature(&tir, &object_temperature) < 0) {
		fprintf(stderr, "Could not get object temperature, probably timeout\n");
		return 1;
	}

	printf("Object Temperature: %f °C\n", object_temperature/10.0);

	printf("Press key to exit\n");
	getchar();
	temperature_ir_v2_destroy(&tir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
