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
		uint8_t ret_tag_type = 0;
		uint8_t ret_tag_id_length = 0;
		uint8_t *ret_tag_id = (uint8_t *)malloc(32);

		ret = nfc_reader_get_tag_id(nfc, &ret_tag_type, ret_tag_id, &ret_tag_id_length);

		if(ret != E_OK) {
			free(ret_tag_id);

			return;
		}

		if(ret_tag_type != NFC_TAG_TYPE_TYPE2) {
			printf("Tag is not type-2\n");
			free(ret_tag_id);

			return;
		}

		printf("Found tag of type %d with ID [0x%X 0x%X 0x%X 0x%X]\n",
		       ret_tag_type,
		       ret_tag_id[0],
		       ret_tag_id[1],
		       ret_tag_id[2],
		       ret_tag_id[3]);
		free(ret_tag_id);
		nfc_reader_request_page(nfc, 1, 4);
	}
	else if(state == NFC_READER_STATE_REQUEST_TAG_ID_ERROR) {
		printf("Request tag ID error\n");
	}
	else if(state == NFC_READER_STATE_REQUEST_PAGE_READY) {
		int ret = 0;
		uint16_t ret_data_length = 0;
		uint8_t *ret_data = (uint8_t *)malloc(4);

		ret = nfc_reader_read_page(nfc, ret_data, &ret_data_length);

		if(ret != E_OK) {
			free(ret_data);

			return;
		}
		printf("Page read: 0x%X 0x%X 0x%X 0x%X\n",
		       ret_data[0],
		       ret_data[1],
		       ret_data[2],
		       ret_data[3]);
		nfc_reader_write_page(nfc, 1, ret_data, ret_data_length);
		free(ret_data);
	}
	else if(state == NFC_READER_STATE_WRITE_PAGE_READY) {
		printf("Write page ready\n");
	}
	else if(state == NFC_READER_STATE_REQUEST_PAGE_ERROR) {
		printf("Request page error\n");
	}
	else if(state == NFC_READER_STATE_WRITE_PAGE_ERROR) {
		printf("Write page error\n");
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
