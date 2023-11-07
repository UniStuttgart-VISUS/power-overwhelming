#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_energy_monitor.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Energy Monitor Bricklet

// Callback function for energy data callback
void cb_energy_data(int32_t voltage, int32_t current, int32_t energy, int32_t real_power,
                    int32_t apparent_power, int32_t reactive_power, uint16_t power_factor,
                    uint16_t frequency, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Voltage: %f V\n", voltage/100.0);
	printf("Current: %f A\n", current/100.0);
	printf("Energy: %f Wh\n", energy/100.0);
	printf("Real Power: %f h\n", real_power/100.0);
	printf("Apparent Power: %f VA\n", apparent_power/100.0);
	printf("Reactive Power: %f var\n", reactive_power/100.0);
	printf("Power Factor: %f\n", power_factor/1000.0);
	printf("Frequency: %f Hz\n", frequency/100.0);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	EnergyMonitor em;
	energy_monitor_create(&em, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register energy data callback to function cb_energy_data
	energy_monitor_register_callback(&em,
	                                 ENERGY_MONITOR_CALLBACK_ENERGY_DATA,
	                                 (void (*)(void))cb_energy_data,
	                                 NULL);

	// Set period for energy data callback to 1s (1000ms)
	energy_monitor_set_energy_data_callback_configuration(&em, 1000, false);

	printf("Press key to exit\n");
	getchar();
	energy_monitor_destroy(&em);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
