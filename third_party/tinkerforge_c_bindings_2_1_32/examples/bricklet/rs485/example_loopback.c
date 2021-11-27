#include <stdio.h>
#include <stdlib.h>

// For this example connect the RX+/- pins to TX+/- pins on the same Bricklet
// and configure the DIP switch on the Bricklet to full-duplex mode

#include "ip_connection.h"
#include "bricklet_rs485.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RS485 Bricklet

// Callback function for read callback
void cb_read(char *message, uint16_t message_length, void *user_data) {
	char *buffer;

	(void)user_data; // avoid unused parameter warning

	// Assume that the message consists of ASCII characters and
	// convert it from an array of chars to a NUL-terminated string
	buffer = (char *)malloc(message_length + 1); // +1 for the NUL-terminator
	memcpy(buffer, message, message_length);
	buffer[message_length] = '\0';

	printf("Message: \"%s\"\n", buffer);
	free(buffer);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RS485 rs485;
	rs485_create(&rs485, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Enable full-duplex mode
	rs485_set_rs485_configuration(&rs485, 115200, RS485_PARITY_NONE, RS485_STOPBITS_1,
	                              RS485_WORDLENGTH_8, RS485_DUPLEX_FULL);

	// Register read callback to function cb_read
	rs485_register_callback(&rs485,
	                        RS485_CALLBACK_READ,
	                        (void (*)(void))cb_read,
	                        NULL);

	// Enable read callback
	rs485_enable_read_callback(&rs485);

	// Write "test" string
	char buffer[] = {'t', 'e', 's', 't'};
	uint16_t written;
	rs485_write(&rs485, buffer, sizeof(buffer), &written);

	printf("Press key to exit\n");
	getchar();
	rs485_destroy(&rs485);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
