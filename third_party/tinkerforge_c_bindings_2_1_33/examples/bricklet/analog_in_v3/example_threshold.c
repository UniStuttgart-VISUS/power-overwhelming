#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_analog_in_v3.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Analog In Bricklet 3.0

// Callback function for voltage callback
void cb_voltage(uint16_t voltage, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Voltage: %f V\n", voltage/1000.0);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AnalogInV3 ai;
	analog_in_v3_create(&ai, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register voltage callback to function cb_voltage
	analog_in_v3_register_callback(&ai,
	                               ANALOG_IN_V3_CALLBACK_VOLTAGE,
	                               (void (*)(void))cb_voltage,
	                               NULL);

	// Configure threshold for voltage "smaller than 5 V"
	// with a debounce period of 1s (1000ms)
	analog_in_v3_set_voltage_callback_configuration(&ai, 1000, false, '<', 5*1000, 0);

	printf("Press key to exit\n");
	getchar();
	analog_in_v3_destroy(&ai);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
