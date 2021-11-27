#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_air_quality.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Air Quality Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	AirQuality aq;
	air_quality_create(&aq, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current all values
	int32_t iaq_index, temperature, humidity, air_pressure; uint8_t iaq_index_accuracy;
	if(air_quality_get_all_values(&aq, &iaq_index, &iaq_index_accuracy, &temperature,
	                              &humidity, &air_pressure) < 0) {
		fprintf(stderr, "Could not get all values, probably timeout\n");
		return 1;
	}

	printf("IAQ Index: %d\n", iaq_index);

	if(iaq_index_accuracy == AIR_QUALITY_ACCURACY_UNRELIABLE) {
		printf("IAQ Index Accuracy: Unreliable\n");
	} else if(iaq_index_accuracy == AIR_QUALITY_ACCURACY_LOW) {
		printf("IAQ Index Accuracy: Low\n");
	} else if(iaq_index_accuracy == AIR_QUALITY_ACCURACY_MEDIUM) {
		printf("IAQ Index Accuracy: Medium\n");
	} else if(iaq_index_accuracy == AIR_QUALITY_ACCURACY_HIGH) {
		printf("IAQ Index Accuracy: High\n");
	}

	printf("Temperature: %f °C\n", temperature/100.0);
	printf("Humidity: %f %%RH\n", humidity/100.0);
	printf("Air Pressure: %f hPa\n", air_pressure/100.0);

	printf("Press key to exit\n");
	getchar();
	air_quality_destroy(&aq);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
