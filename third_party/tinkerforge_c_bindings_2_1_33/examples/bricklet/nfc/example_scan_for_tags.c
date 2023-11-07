#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_nfc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your NFC Bricklet

// Callback function for reader state changed callback
void cb_reader_state_changed(uint8_t state, bool idle, void *user_data) {
	NFC *nfc = (NFC *)user_data;

	if(state == NFC_READER_STATE_REQUEST_TAG_ID_READY) {
		uint8_t ret_tag_type;
		uint8_t ret_tag_id_length;
		uint8_t ret_tag_id[32];

		if(nfc_reader_get_tag_id(nfc, &ret_tag_type, ret_tag_id, &ret_tag_id_length) < 0) {
			fprintf(stderr, "Could not get tag ID\n");
			return;
		}

		printf("Found tag of type %d with ID [", ret_tag_type);

		for(uint8_t i = 0; i < ret_tag_id_length; i++) {
			printf("0x%02X", ret_tag_id[i]);

			if(i < ret_tag_id_length - 1) {
				printf(" ");
			}
		}

		printf("]\n");
	}

	if(idle) {
		nfc_reader_request_tag_id(nfc);
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	NFC nfc;
	nfc_create(&nfc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register reader state changed callback to function cb_reader_state_changed
	nfc_register_callback(&nfc,
	                      NFC_CALLBACK_READER_STATE_CHANGED,
	                      (void (*)(void))cb_reader_state_changed,
	                      &nfc);

	// Enable reader mode
	nfc_set_mode(&nfc, NFC_MODE_READER);

	printf("Press key to exit\n");
	getchar();
	nfc_destroy(&nfc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
