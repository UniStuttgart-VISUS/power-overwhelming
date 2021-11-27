#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_nfc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your NFC Bricklet

// Callback function for reader state changed callback
void cb_reader_state_changed(uint8_t state, bool idle, void *user_data) {
	NFC *nfc = (NFC *)user_data;

	(void)idle; // avoid unused parameter warning

	if(state == NFC_READER_STATE_IDLE) {
		nfc_reader_request_tag_id(nfc);
	}
	else if(state == NFC_READER_STATE_REQUEST_TAG_ID_READY) {
		int ret = 0;
		char tag_byte[8];
		char tag_info[256];
		uint8_t ret_tag_type = 0;
		uint8_t ret_tag_id_length = 0;
		uint8_t *ret_tag_id = (uint8_t *)malloc(32);

		ret = nfc_reader_get_tag_id(nfc, &ret_tag_type, ret_tag_id, &ret_tag_id_length);

		if(ret != E_OK) {
			free(ret_tag_id);

			return;
		}

		memset(tag_info, 0, 256);
		sprintf(tag_info, "Found tag of type %d with ID [", ret_tag_type);

		for(uint8_t i = 0; i < ret_tag_id_length; i++) {
			memset(tag_byte, 0, 8);

			if(i < ret_tag_id_length - 1){
				sprintf(tag_byte, "0x%X ", ret_tag_id[i]);
			}
			else {
				sprintf(tag_byte, "0x%X", ret_tag_id[i]);
				strcat(tag_byte, "]");
			}

			strcat(tag_info, tag_byte);
		}

		free(ret_tag_id);
		printf("%s\n", tag_info);
	}
	else if(state == NFC_READER_STATE_REQUEST_TAG_ID_ERROR) {
		printf("Request tag ID error\n");
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
