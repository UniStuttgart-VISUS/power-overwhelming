#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io16.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-16 Bricklet

// Callback function for interrupt callback
void cb_interrupt(char port, uint8_t interrupt_mask, uint8_t value_mask,
                  void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Port: %c\n", port);
	printf("Interrupt Mask: %u\n", interrupt_mask);
	printf("Value Mask: %u\n", value_mask);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO16 io;
	io16_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register interrupt callback to function cb_interrupt
	io16_register_callback(&io,
	                       IO16_CALLBACK_INTERRUPT,
	                       (void (*)(void))cb_interrupt,
	                       NULL);

	// Enable interrupt on pin 2 of port A
	io16_set_port_interrupt(&io, 'a', 1 << 2);

	printf("Press key to exit\n");
	getchar();
	io16_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
