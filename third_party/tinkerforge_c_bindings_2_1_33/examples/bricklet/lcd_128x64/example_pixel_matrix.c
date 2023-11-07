#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_128x64.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your OLED 128x64 Bricklet
#define WIDTH 128
#define HEIGHT 64

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

	// Draw checkerboard pattern
	int row, column;
	bool pixels[HEIGHT * WIDTH];

	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++) {
			pixels[row * WIDTH + column] = (row / 8) % 2 == (column / 8) % 2;
		}
	}

	lcd_128x64_write_pixels(&lcd, 0, 0, WIDTH-1, HEIGHT-1, pixels, HEIGHT*WIDTH);

	printf("Press key to exit\n");
	getchar();
	lcd_128x64_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
