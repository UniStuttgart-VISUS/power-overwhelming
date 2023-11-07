#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_nfc.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your NFC Bricklet
#define NDEF_URI "www.tinkerforge.com"

// Callback function for cardemu state changed callback
void cb_cardemu_state_changed(uint8_t state, bool idle, void *user_data) {
	NFC *nfc = (NFC *)user_data;

	(void)idle; // avoid unused parameter warning

	if(state == NFC_CARDEMU_STATE_IDLE) {
		uint8_t i = 0;
		uint8_t ndef_record_uri[512];
		const char *ptr_ndef_uri = NDEF_URI;

		memset(ndef_record_uri, 0, 512);

		// Only short records are supported
		ndef_record_uri[0] = 0xD1;
		ndef_record_uri[1] = 0x01;
		ndef_record_uri[2] = strlen(NDEF_URI) + 1;
		ndef_record_uri[3] = 'U';
		ndef_record_uri[4] = 0x04;

		while (*ptr_ndef_uri) {
			ndef_record_uri[5 + i] = *ptr_ndef_uri;
			i++;
			ptr_ndef_uri++;
		}

		nfc_cardemu_write_ndef(nfc, ndef_record_uri, strlen(NDEF_URI) + 5);
		nfc_cardemu_start_discovery(nfc);
	}
	else if(state == NFC_CARDEMU_STATE_DISCOVER_READY) {
		nfc_cardemu_start_transfer(nfc, NFC_CARDEMU_TRANSFER_WRITE);
	}
	else if(state == NFC_CARDEMU_STATE_DISCOVER_ERROR) {
		printf("Discover error\n");
	}
	else if(state == NFC_CARDEMU_STATE_TRANSFER_NDEF_ERROR) {
		printf("Transfer NDEF error\n");
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

	// Register cardemu state changed callback to function cb_cardemu_state_changed
	nfc_register_callback(&nfc,
	                      NFC_CALLBACK_CARDEMU_STATE_CHANGED,
	                      (void (*)(void))cb_cardemu_state_changed,
	                      &nfc);

	// Enable cardemu mode
	nfc_set_mode(&nfc, NFC_MODE_CARDEMU);

	printf("Press key to exit\n");
	getchar();
	nfc_destroy(&nfc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
