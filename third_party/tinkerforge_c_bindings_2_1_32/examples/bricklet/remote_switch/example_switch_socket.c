#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_remote_switch.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Remote Switch Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RemoteSwitch rs;
	remote_switch_create(&rs, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Switch on a type A socket with house code 17 and receiver code 1.
	// House code 17 is 10001 in binary (least-significant bit first)
	// and means that the DIP switches 1 and 5 are on and 2-4 are off.
	// Receiver code 1 is 10000 in binary (least-significant bit first)
	// and means that the DIP switch A is on and B-E are off.
	remote_switch_switch_socket_a(&rs, 17, 1, REMOTE_SWITCH_SWITCH_TO_ON);

	printf("Press key to exit\n");
	getchar();
	remote_switch_destroy(&rs);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
