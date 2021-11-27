#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_can_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your CAN Bricklet 2.0

// Callback function for frame read callback
void cb_frame_read(uint8_t frame_type, uint32_t identifier,
                   uint8_t *data, uint16_t data_length, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(frame_type == CAN_V2_FRAME_TYPE_STANDARD_DATA) {
		printf("Frame Type: Standard Data\n");
	} else if(frame_type == CAN_V2_FRAME_TYPE_STANDARD_REMOTE) {
		printf("Frame Type: Standard Remote\n");
	} else if(frame_type == CAN_V2_FRAME_TYPE_EXTENDED_DATA) {
		printf("Frame Type: Extended Data\n");
	} else if(frame_type == CAN_V2_FRAME_TYPE_EXTENDED_REMOTE) {
		printf("Frame Type: Extended Remote\n");
	}

	printf("Identifier: %u\n", identifier);
	printf("Data (Length: %d):", data_length);

	uint8_t i;
	for (i = 0; i < data_length && i < 8; ++i) {
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
	CANV2 can;
	can_v2_create(&can, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Configure transceiver for loopback mode
	can_v2_set_transceiver_configuration(&can, 1000000, 625,
	                                     CAN_V2_TRANSCEIVER_MODE_LOOPBACK);

	// Register frame read callback to function cb_frame_read
	can_v2_register_callback(&can,
	                         CAN_V2_CALLBACK_FRAME_READ,
	                         (void (*)(void))cb_frame_read,
	                         NULL);

	// Enable frame read callback
	can_v2_set_frame_read_callback_configuration(&can, true);

	// Write standard data frame with identifier 1742 and 3 bytes of data
	uint8_t data[3] = {42, 23, 17};
	bool success;
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, 1742, data, 3, &success);

	printf("Press key to exit\n");
	getchar();

	can_v2_set_frame_read_callback_configuration(&can, false);

	can_v2_destroy(&can);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
