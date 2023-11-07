#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_analog_in_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual Analog In Bricklet 2.0

// Callback function for voltage callback
void cb_voltage(uint8_t channel, int32_t voltage, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Channel: %u\n", channel);
	printf("Voltage: %f V\n", voltage/1000.0);
	printf("\n");
}

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

	// Register voltage callback to function cb_voltage
	industrial_dual_analog_in_v2_register_callback(&idai,
	                                               INDUSTRIAL_DUAL_ANALOG_IN_V2_CALLBACK_VOLTAGE,
	                                               (void (*)(void))cb_voltage,
	                                               NULL);

	// Configure threshold for voltage (channel 0) "greater than 10 V"
	// with a debounce period of 10s (10000ms)
	industrial_dual_analog_in_v2_set_voltage_callback_configuration(&idai, 0, 10000, false, '>', 10*1000, 0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_analog_in_v2_destroy(&idai);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
