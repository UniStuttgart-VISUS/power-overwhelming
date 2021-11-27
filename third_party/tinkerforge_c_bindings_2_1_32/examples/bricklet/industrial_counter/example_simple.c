#define __STDC_FORMAT_MACROS // for PRId64/PRIu64 in C++

#include <stdio.h>
#include <inttypes.h>

#include "ip_connection.h"
#include "bricklet_industrial_counter.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Counter Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialCounter ic;
	industrial_counter_create(&ic, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current counter from channel 0
	int64_t counter;
	if(industrial_counter_get_counter(&ic, INDUSTRIAL_COUNTER_CHANNEL_0, &counter) < 0) {
		fprintf(stderr, "Could not get counter from channel 0, probably timeout\n");
		return 1;
	}

	printf("Counter (Channel 0): %" PRId64 "\n", counter);

	// Get current signal data from channel 0
	uint16_t duty_cycle; uint64_t period; uint32_t frequency; bool value;
	if(industrial_counter_get_signal_data(&ic, INDUSTRIAL_COUNTER_CHANNEL_0, &duty_cycle,
	                                      &period, &frequency, &value) < 0) {
		fprintf(stderr, "Could not get signal data from channel 0, probably timeout\n");
		return 1;
	}

	printf("Duty Cycle (Channel 0): %f %%\n", duty_cycle/100.0);
	printf("Period (Channel 0): %" PRIu64 " ns\n", period);
	printf("Frequency (Channel 0): %f Hz\n", frequency/1000.0);
	printf("Value (Channel 0): %s\n", value ? "true" : "false");

	printf("Press key to exit\n");
	getchar();
	industrial_counter_destroy(&ic);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
