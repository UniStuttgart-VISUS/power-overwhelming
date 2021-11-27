#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_remote_switch_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Remote Switch Bricklet 2.0

// Callback function for remote status a callback
void cb_remote_status_a(uint8_t house_code, uint8_t receiver_code, uint8_t switch_to,
                        uint16_t repeats, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("House Code: %u\n", house_code);
	printf("Receiver Code: %u\n", receiver_code);

	if(switch_to == REMOTE_SWITCH_V2_SWITCH_TO_OFF) {
		printf("Switch To: Off\n");
	} else if(switch_to == REMOTE_SWITCH_V2_SWITCH_TO_ON) {
		printf("Switch To: On\n");
	}

	printf("Repeats: %u\n", repeats);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RemoteSwitchV2 rs;
	remote_switch_v2_create(&rs, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Configure to receive from remote type A with minimum repeats set to 1 and enable callback
	remote_switch_v2_set_remote_configuration(&rs, REMOTE_SWITCH_V2_REMOTE_TYPE_A, 1,
	                                          true);

	// Register remote status a callback to function cb_remote_status_a
	remote_switch_v2_register_callback(&rs,
	                                   REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A,
	                                   (void (*)(void))cb_remote_status_a,
	                                   NULL);

	printf("Press key to exit\n");
	getchar();
	remote_switch_v2_destroy(&rs);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
