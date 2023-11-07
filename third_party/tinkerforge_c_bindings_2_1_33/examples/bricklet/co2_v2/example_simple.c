#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_co2_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your CO2 Bricklet 2.0

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

	// Get current all values
	uint16_t co2_concentration, humidity; int16_t temperature;
	if(co2_v2_get_all_values(&co2, &co2_concentration, &temperature, &humidity) < 0) {
		fprintf(stderr, "Could not get all values, probably timeout\n");
		return 1;
	}

	printf("CO2 Concentration: %u ppm\n", co2_concentration);
	printf("Temperature: %f °C\n", temperature/100.0);
	printf("Humidity: %f %%RH\n", humidity/100.0);

	printf("Press key to exit\n");
	getchar();
	co2_v2_destroy(&co2);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
