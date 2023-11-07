#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your IO-4 Bricklet

// Callback function for interrupt callback
void cb_interrupt(uint8_t interrupt_mask, uint8_t value_mask, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Interrupt Mask: %u\n", interrupt_mask);
	printf("Value Mask: %u\n", value_mask);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO4 io;
	io4_create(&io, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register interrupt callback to function cb_interrupt
	io4_register_callback(&io,
	                      IO4_CALLBACK_INTERRUPT,
	                      (void (*)(void))cb_interrupt,
	                      NULL);

	// Enable interrupt on pin 0
	io4_set_interrupt(&io, 1 << 0);

	printf("Press key to exit\n");
	getchar();
	io4_destroy(&io);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
