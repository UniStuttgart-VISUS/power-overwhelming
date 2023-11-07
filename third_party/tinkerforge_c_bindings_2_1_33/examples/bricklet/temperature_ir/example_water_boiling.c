#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_temperature_ir.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Temperature IR Bricklet

// Callback function for object temperature reached callback
void cb_object_temperature_reached(int16_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Object Temperature: %f °C\n", temperature/10.0);
	printf("The water is boiling!\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	TemperatureIR tir;
	temperature_ir_create(&tir, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set emissivity to 0.98 (emissivity of water, 65535 * 0.98 = 64224.299)
	temperature_ir_set_emissivity(&tir, 64224);

	// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
	temperature_ir_set_debounce_period(&tir, 10000);

	// Register object temperature reached callback to function
	// cb_object_temperature_reached
	temperature_ir_register_callback(&tir,
	                                 TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE_REACHED,
	                                 (void (*)(void))cb_object_temperature_reached,
	                                 NULL);

	// Configure threshold for object temperature "greater than 100 °C"
	temperature_ir_set_object_temperature_callback_threshold(&tir, '>', 100*10, 0);

	printf("Press key to exit\n");
	getchar();
	temperature_ir_destroy(&tir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
