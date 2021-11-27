#define __STDC_FORMAT_MACROS // for PRId64/PRIu64 in C++

#include <stdio.h>
#include <inttypes.h>

#include "ip_connection.h"
#include "bricklet_industrial_counter.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Counter Bricklet

// Callback function for all counter callback
void cb_all_counter(int64_t counter[4], void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Counter (Channel 0): %" PRId64 "\n", counter[0]);
	printf("Counter (Channel 1): %" PRId64 "\n", counter[1]);
	printf("Counter (Channel 2): %" PRId64 "\n", counter[2]);
	printf("Counter (Channel 3): %" PRId64 "\n", counter[3]);
	printf("\n");
}

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

	// Register all counter callback to function cb_all_counter
	industrial_counter_register_callback(&ic,
	                                     INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER,
	                                     (void (*)(void))cb_all_counter,
	                                     NULL);

	// Set period for all counter callback to 1s (1000ms)
	industrial_counter_set_all_counter_callback_configuration(&ic, 1000, true);

	printf("Press key to exit\n");
	getchar();
	industrial_counter_destroy(&ic);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
