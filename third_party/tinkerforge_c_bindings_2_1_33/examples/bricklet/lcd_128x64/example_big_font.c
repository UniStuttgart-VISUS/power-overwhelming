#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_128x64.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 128x64 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LCD128x64 lcd;
	lcd_128x64_create(&lcd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Clear display
	lcd_128x64_clear_display(&lcd);

	// Write "Hello World" with big 24x32 font
	lcd_128x64_draw_text(&lcd, 0, 0, LCD_128X64_FONT_24X32, LCD_128X64_COLOR_BLACK,
	                     "24x32");

	printf("Press key to exit\n");
	getchar();
	lcd_128x64_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
