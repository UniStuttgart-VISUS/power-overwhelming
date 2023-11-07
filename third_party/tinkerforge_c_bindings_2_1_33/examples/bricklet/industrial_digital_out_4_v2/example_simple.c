#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_out_4_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalOut4V2 ido4;
	industrial_digital_out_4_v2_create(&ido4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set channels alternating high/low 10 times with 100 ms delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(100);
		bool value[4] = {true, false, false, false};
		industrial_digital_out_4_v2_set_value(&ido4, value);
		millisleep(100);
		bool value_1[4] = {false, true, false, false};
		industrial_digital_out_4_v2_set_value(&ido4, value_1);
		millisleep(100);
		bool value_2[4] = {false, false, true, false};
		industrial_digital_out_4_v2_set_value(&ido4, value_2);
		millisleep(100);
		bool value_3[4] = {false, false, false, true};
		industrial_digital_out_4_v2_set_value(&ido4, value_3);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_digital_out_4_v2_destroy(&ido4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
