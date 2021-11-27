#include <stdio.h>
#include <stdlib.h>

// For this example connect the RX1 and TX pin to receive the send message

#include "ip_connection.h"
#include "bricklet_rs232_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RS232 Bricklet 2.0

// Callback function for read callback
void cb_read(char *message, uint16_t message_length, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	// Assume that the message consists of ASCII characters and
	// convert it from an array of chars to a NUL-terminated string
	char *buffer = (char *)malloc(message_length + 1); // +1 for the NUL-terminator
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
	RS232V2 rs232;
	rs232_v2_create(&rs232, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register read callback to function cb_read
	rs232_v2_register_callback(&rs232,
	                           RS232_V2_CALLBACK_READ,
	                           (void (*)(void))cb_read,
	                           NULL);

	// Enable read callback
	rs232_v2_enable_read_callback(&rs232);

	// Write "test" string
	const char *message = "test";
	uint16_t written;
	rs232_v2_write(&rs232, message, strlen(message), &written);

	printf("Press key to exit\n");
	getchar();
	rs232_v2_destroy(&rs232);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
