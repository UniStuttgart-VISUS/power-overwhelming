#define IPCON_EXPOSE_MILLISLEEP

#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_xmc1400_breakout.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your XMC1400 Breakout Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	XMC1400Breakout xb;
	xmc1400_breakout_create(&xb, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set Port 1, Pin 0 alternating high/low for 5 times with 1s delay
	int i;
	for(i = 0; i < 5; ++i) {
		millisleep(1000);
		xmc1400_breakout_set_gpio_config(&xb, 1, 0,
		                                 XMC1400_BREAKOUT_GPIO_MODE_OUTPUT_PUSH_PULL, 0,
		                                 false);
		millisleep(1000);
		xmc1400_breakout_set_gpio_config(&xb, 1, 0,
		                                 XMC1400_BREAKOUT_GPIO_MODE_OUTPUT_PUSH_PULL, 0,
		                                 true);
	}

	printf("Press key to exit\n");
	getchar();
	xmc1400_breakout_destroy(&xb);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
