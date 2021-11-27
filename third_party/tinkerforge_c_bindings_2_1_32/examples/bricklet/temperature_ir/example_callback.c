#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_temperature_ir.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Temperature IR Bricklet

// Callback function for object temperature callback
void cb_object_temperature(int16_t temperature, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Object Temperature: %f °C\n", temperature/10.0);
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

	// Register object temperature callback to function cb_object_temperature
	temperature_ir_register_callback(&tir,
	                                 TEMPERATURE_IR_CALLBACK_OBJECT_TEMPERATURE,
	                                 (void (*)(void))cb_object_temperature,
	                                 NULL);

	// Set period for object temperature callback to 1s (1000ms)
	// Note: The object temperature callback is only called every second
	//       if the object temperature has changed since the last call!
	temperature_ir_set_object_temperature_callback_period(&tir, 1000);

	printf("Press key to exit\n");
	getchar();
	temperature_ir_destroy(&tir);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
