#include <stdio.h>

#include "ip_connection.h"
#include "brick_hat_zero.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XXYYZZ" // Change XXYYZZ to the UID of your HAT Zero Brick

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HATZero hz;
	hat_zero_create(&hz, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current voltage
	uint16_t voltage;
	if(hat_zero_get_usb_voltage(&hz, &voltage) < 0) {
		fprintf(stderr, "Could not get voltage, probably timeout\n");
		return 1;
	}

	printf("Voltage: %f V\n", voltage/1000.0);

	printf("Press key to exit\n");
	getchar();
	hat_zero_destroy(&hz);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
