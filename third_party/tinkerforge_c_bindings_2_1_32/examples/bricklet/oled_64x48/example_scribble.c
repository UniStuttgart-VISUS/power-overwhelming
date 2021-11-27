#include <stdio.h>
#include <math.h>
#include <gd.h> // https://libgd.github.io/

#define IPCON_EXPOSE_MILLISLEEP

#include "ip_connection.h"
#include "bricklet_oled_64x48.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your OLED 64x48 Bricklet
#define WIDTH 64
#define HEIGHT 48

void draw_image(OLED64x48 *oled, gdImagePtr image) {
	uint8_t pages[HEIGHT / 8][WIDTH];
	int row, column, bit, index;

	// Convert pixels into pages
	for (row = 0; row < HEIGHT / 8; row++) {
		for (column = 0; column < WIDTH; column++) {
			pages[row][column] = 0;

			for (bit = 0; bit < 8; bit++) {
				index = gdImageGetPixel(image, column, (row * 8) + bit);

				if (gdImageRed(image, index) > 0) {
					pages[row][column] |= 1 << bit;
				}
			}
		}
	}

	// Write all pages
	oled_64x48_new_window(oled, 0, WIDTH - 1, 0, HEIGHT / 8 - 1);

	for (row = 0; row < HEIGHT / 8; row++) {
		oled_64x48_write(oled, pages[row]);
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	OLED64x48 oled;
	oled_64x48_create(&oled, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Clear display
	oled_64x48_clear_display(&oled);

	// Draw rotating line
	gdImagePtr image = gdImageCreate(WIDTH, HEIGHT);
	int black = gdImageColorAllocate(image, 0, 0, 0);
	int white = gdImageColorAllocate(image, 255, 255, 255);
	int origin_x = WIDTH / 2;
	int origin_y = HEIGHT / 2;
	int length = HEIGHT / 2 - 2;
	int angle = 0;

	printf("Press ctrl+c exit\n");

	while (true) {
		double radians = M_PI * angle / 180.0;
		int x = (int)(origin_x + length * cos(radians));
		int y = (int)(origin_y + length * sin(radians));

		gdImageFilledRectangle(image, 0, 0, WIDTH, HEIGHT, black);
		gdImageLine(image, origin_x, origin_y, x, y, white);

		draw_image(&oled, image);
		millisleep(25);

		angle++;
	}

	gdImageDestroy(image);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
