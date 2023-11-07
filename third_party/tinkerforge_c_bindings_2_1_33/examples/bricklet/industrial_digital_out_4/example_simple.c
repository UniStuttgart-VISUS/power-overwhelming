#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_out_4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital Out 4 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IndustrialDigitalOut4 ido4;
	industrial_digital_out_4_create(&ido4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set pins alternating high/low 10 times with 100ms delay
	int i;
	for(i = 0; i < 10; ++i) {
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 0);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 1);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 2);
		millisleep(100);
		industrial_digital_out_4_set_value(&ido4, 1 << 3);
	}

	printf("Press key to exit\n");
	getchar();
	industrial_digital_out_4_destroy(&ido4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
