// Tested with gcc:
// > gcc -pthread example_scribble.c ip_connection.c bricklet_oled_128x64_v2.c -lgd -lm -o example

#include <stdio.h>
#include <math.h>
#include <gd.h> // https://libgd.github.io/

#define IPCON_EXPOSE_MILLISLEEP

#include "ip_connection.h"
#include "bricklet_oled_128x64_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your OLED 128x64 Bricklet 2.0
#define WIDTH 128
#define HEIGHT 64

void draw_image(OLED128x64V2 *oled, gdImagePtr image) {
	bool pixels[HEIGHT * WIDTH];
	int row, column, index;

	// Convert pixels into pages
	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++) {
			index = gdImageGetPixel(image, column, row);
			pixels[row*WIDTH + column] = gdImageRed(image, index) > 0;
		}
	}

	oled_128x64_v2_write_pixels(oled, 0, 0, WIDTH-1, HEIGHT-1, pixels, HEIGHT*WIDTH);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	OLED128x64V2 oled;
	oled_128x64_v2_create(&oled, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Clear display
	oled_128x64_v2_clear_display(&oled);

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
