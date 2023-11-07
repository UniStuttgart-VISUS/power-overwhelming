#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_dual_analog_in.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Dual Analog In Bricklet

// Callback function for voltage reached callback
void cb_voltage_reached(uint8_t channel, int32_t voltage, void *user_data) {
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
	IndustrialDualAnalogIn idai;
	industrial_dual_analog_in_create(&idai, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	industrial_dual_analog_in_set_debounce_period(&idai, 10000);

	// Register voltage reached callback to function cb_voltage_reached
	industrial_dual_analog_in_register_callback(&idai,
	                                            INDUSTRIAL_DUAL_ANALOG_IN_CALLBACK_VOLTAGE_REACHED,
	                                            (void (*)(void))cb_voltage_reached,
	                                            NULL);

	// Configure threshold for voltage (channel 1) "greater than 10 V"
	industrial_dual_analog_in_set_voltage_callback_threshold(&idai, 1, '>', 10*1000, 0);

	printf("Press key to exit\n");
	getchar();
	industrial_dual_analog_in_destroy(&idai);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
