#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_co2_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your CO2 Bricklet 2.0

// Callback function for all values callback
void cb_all_values(uint16_t co2_concentration, int16_t temperature, uint16_t humidity,
                   void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("CO2 Concentration: %u ppm\n", co2_concentration);
	printf("Temperature: %f °C\n", temperature/100.0);
	printf("Humidity: %f %%RH\n", humidity/100.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	CO2V2 co2;
	co2_v2_create(&co2, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register all values callback to function cb_all_values
	co2_v2_register_callback(&co2,
	                         CO2_V2_CALLBACK_ALL_VALUES,
	                         (void (*)(void))cb_all_values,
	                         NULL);

	// Set period for all values callback to 1s (1000ms)
	co2_v2_set_all_values_callback_configuration(&co2, 1000, false);

	printf("Press key to exit\n");
	getchar();
	co2_v2_destroy(&co2);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
