#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_16x2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 16x2 Bricklet

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

	// Turn backlight on
	lcd_16x2_backlight_on(&lcd);

	// Write "Hello World"
	lcd_16x2_write_line(&lcd, 0, 0, "Hello World");

	printf("Press key to exit\n");
	getchar();
	lcd_16x2_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
