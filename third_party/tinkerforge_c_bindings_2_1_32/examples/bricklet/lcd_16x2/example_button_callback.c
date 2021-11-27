#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_16x2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 16x2 Bricklet

// Callback function for button pressed callback
void cb_button_pressed(uint8_t button, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Button Pressed: %u\n", button);
}

// Callback function for button released callback
void cb_button_released(uint8_t button, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Button Released: %u\n", button);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LCD16x2 lcd;
	lcd_16x2_create(&lcd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register button pressed callback to function cb_button_pressed
	lcd_16x2_register_callback(&lcd,
	                           LCD_16X2_CALLBACK_BUTTON_PRESSED,
	                           (void (*)(void))cb_button_pressed,
	                           NULL);

	// Register button released callback to function cb_button_released
	lcd_16x2_register_callback(&lcd,
	                           LCD_16X2_CALLBACK_BUTTON_RELEASED,
	                           (void (*)(void))cb_button_released,
	                           NULL);

	printf("Press key to exit\n");
	getchar();
	lcd_16x2_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
