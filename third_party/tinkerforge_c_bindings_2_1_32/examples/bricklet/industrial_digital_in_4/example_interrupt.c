#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_industrial_digital_in_4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Industrial Digital In 4 Bricklet

// Callback function for interrupt callback
void cb_interrupt(uint16_t interrupt_mask, uint16_t value_mask, void *user_data) {
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
	IndustrialDigitalIn4 idi4;
	industrial_digital_in_4_create(&idi4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register interrupt callback to function cb_interrupt
	industrial_digital_in_4_register_callback(&idi4,
	                                          INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT,
	                                          (void (*)(void))cb_interrupt,
	                                          NULL);

	// Enable interrupt on pin 0
	industrial_digital_in_4_set_interrupt(&idi4, 1 << 0);

	printf("Press key to exit\n");
	getchar();
	industrial_digital_in_4_destroy(&idi4);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
