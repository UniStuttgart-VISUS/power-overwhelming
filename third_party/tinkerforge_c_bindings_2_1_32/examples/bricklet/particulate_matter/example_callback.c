#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_particulate_matter.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Particulate Matter Bricklet

// Callback function for PM concentration callback
void cb_pm_concentration(uint16_t pm10, uint16_t pm25, uint16_t pm100, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("PM 1.0: %u µg/m³\n", pm10);
	printf("PM 2.5: %u µg/m³\n", pm25);
	printf("PM 10.0: %u µg/m³\n", pm100);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	ParticulateMatter pm;
	particulate_matter_create(&pm, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register PM concentration callback to function cb_pm_concentration
	particulate_matter_register_callback(&pm,
	                                     PARTICULATE_MATTER_CALLBACK_PM_CONCENTRATION,
	                                     (void (*)(void))cb_pm_concentration,
	                                     NULL);

	// Set period for PM concentration callback to 1s (1000ms)
	particulate_matter_set_pm_concentration_callback_configuration(&pm, 1000, false);

	printf("Press key to exit\n");
	getchar();
	particulate_matter_destroy(&pm);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
