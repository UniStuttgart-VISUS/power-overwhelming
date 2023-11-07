#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_oled_128x64.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your OLED 128x64 Bricklet
#define WIDTH 128
#define HEIGHT 64

void draw_matrix(OLED128x64 *oled, bool pixels[HEIGHT][WIDTH]) {
	uint8_t pages[HEIGHT / 8][WIDTH];
	int row, column, bit;

	// Convert pixels into pages
	for (row = 0; row < HEIGHT / 8; row++) {
		for (column = 0; column < WIDTH; column++) {
			pages[row][column] = 0;

			for (bit = 0; bit < 8; bit++) {
				if (pixels[(row * 8) + bit][column]) {
					pages[row][column] |= 1 << bit;
				}
			}
		}
	}

	// Write all pages
	oled_128x64_new_window(oled, 0, WIDTH - 1, 0, HEIGHT / 8 - 1);

	for (row = 0; row < HEIGHT / 8; row++) {
		for (column = 0; column < WIDTH; column += 64) {
			oled_128x64_write(oled, &pages[row][column]);
		}
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	OLED128x64 oled;
	oled_128x64_create(&oled, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Clear display
	oled_128x64_clear_display(&oled);

	// Draw checkerboard pattern
	int row, column;
	bool pixels[HEIGHT][WIDTH];

	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++) {
			pixels[row][column] = (row / 8) % 2 == (column / 8) % 2;
		}
	}

	draw_matrix(&oled, pixels);

	printf("Press key to exit\n");
	getchar();
	oled_128x64_destroy(&oled);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
