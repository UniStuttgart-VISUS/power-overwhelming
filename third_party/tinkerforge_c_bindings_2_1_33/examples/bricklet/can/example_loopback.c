#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_can.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your CAN Bricklet

// Callback function for frame read callback
void cb_frame_read(uint8_t frame_type, uint32_t identifier, uint8_t data[8],
                   uint8_t length, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(frame_type == CAN_FRAME_TYPE_STANDARD_DATA) {
		printf("Frame Type: Standard Data\n");
	} else if(frame_type == CAN_FRAME_TYPE_STANDARD_REMOTE) {
		printf("Frame Type: Standard Remote\n");
	} else if(frame_type == CAN_FRAME_TYPE_EXTENDED_DATA) {
		printf("Frame Type: Extended Data\n");
	} else if(frame_type == CAN_FRAME_TYPE_EXTENDED_REMOTE) {
		printf("Frame Type: Extended Remote\n");
	}

	printf("Identifier: %u\n", identifier);
	printf("Data (Length: %d):", length);

	uint8_t i;
	for (i = 0; i < length && i < 8; ++i) {
		printf(" %d", data[i]);
	}

	printf("\n");
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	CAN can;
	can_create(&can, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Configure transceiver for loopback mode
	can_set_configuration(&can, CAN_BAUD_RATE_1000KBPS, CAN_TRANSCEIVER_MODE_LOOPBACK, 0);

	// Register frame read callback to function cb_frame_read
	can_register_callback(&can,
	                      CAN_CALLBACK_FRAME_READ,
	                      (void (*)(void))cb_frame_read,
	                      NULL);

	// Enable frame read callback
	can_enable_frame_read_callback(&can);

	// Write standard data frame with identifier 1742 and 3 bytes of data
	uint8_t data[8] = {42, 23, 17, 0, 0, 0, 0, 0};
	bool success;
	can_write_frame(&can, CAN_FRAME_TYPE_STANDARD_DATA, 1742, data, 3, &success);

	printf("Press key to exit\n");
	getchar();

	can_disable_frame_read_callback(&can);

	can_destroy(&can);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
