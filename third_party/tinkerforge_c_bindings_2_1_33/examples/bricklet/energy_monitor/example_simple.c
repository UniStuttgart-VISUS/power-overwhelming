#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_energy_monitor.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Energy Monitor Bricklet

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

	// Get current energy data
	int32_t voltage, current, energy, real_power, apparent_power, reactive_power;
	uint16_t power_factor, frequency;
	if(energy_monitor_get_energy_data(&em, &voltage, &current, &energy, &real_power,
	                                  &apparent_power, &reactive_power, &power_factor,
	                                  &frequency) < 0) {
		fprintf(stderr, "Could not get energy data, probably timeout\n");
		return 1;
	}

	printf("Voltage: %f V\n", voltage/100.0);
	printf("Current: %f A\n", current/100.0);
	printf("Energy: %f Wh\n", energy/100.0);
	printf("Real Power: %f h\n", real_power/100.0);
	printf("Apparent Power: %f VA\n", apparent_power/100.0);
	printf("Reactive Power: %f var\n", reactive_power/100.0);
	printf("Power Factor: %f\n", power_factor/1000.0);
	printf("Frequency: %f Hz\n", frequency/100.0);

	printf("Press key to exit\n");
	getchar();
	energy_monitor_destroy(&em);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
