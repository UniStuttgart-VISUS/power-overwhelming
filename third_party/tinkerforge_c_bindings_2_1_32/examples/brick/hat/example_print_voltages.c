#include <stdio.h>

#include "ip_connection.h"
#include "brick_hat.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your HAT Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HAT hat;
	hat_create(&hat, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current get voltages
	uint16_t voltage_usb, voltage_dc;
	if(hat_get_voltages(&hat, &voltage_usb, &voltage_dc) < 0) {
		fprintf(stderr, "Could not get get voltages, probably timeout\n");
		return 1;
	}

	printf("Voltage USB: %f V\n", voltage_usb/1000.0);
	printf("Voltage DC: %f V\n", voltage_dc/1000.0);

	printf("Press key to exit\n");
	getchar();
	hat_destroy(&hat);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
