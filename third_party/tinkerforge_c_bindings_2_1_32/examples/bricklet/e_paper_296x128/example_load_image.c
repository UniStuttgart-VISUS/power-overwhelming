// Tested with gcc:
// > gcc -pthread example_load_image.c ip_connection.c bricklet_e_paper_296x128.c -lgd -lm -o example

#include <stdio.h>
#include <math.h>
#include <gd.h> // https://libgd.github.io/

#include "ip_connection.h"
#include "bricklet_e_paper_296x128.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your E-Paper 296x128 Bricklet
#define WIDTH 296
#define HEIGHT 128

// Convert GD Image to matching color boolean array
void bool_array_from_image(gdImagePtr image, bool *pixels, uint8_t r, uint8_t g, uint8_t b) {
	int row, column, index;

	// Convert pixels into pages
	for (row = 0; row < HEIGHT; row++) {
		for (column = 0; column < WIDTH; column++) {
			index = gdImageGetPixel(image, column, row);
			pixels[row*WIDTH + column] = gdImageRed(image, index) == r && gdImageGreen(image, index) == g && gdImageBlue(image, index) == b;
		}
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	EPaper296x128 epaper;
	e_paper_296x128_create(&epaper, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Download example image here:
	// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
	FILE *file = fopen("tf_red.png", "rb");
	gdImagePtr image = gdImageCreateFromPng(file);
	
	bool pixels[HEIGHT * WIDTH];

	// Get black/white pixels from image and write them to the Bricklet buffer
	bool_array_from_image(image, pixels, 0xFF, 0xFF, 0xFF); 
	e_paper_296x128_write_black_white(&epaper, 0, 0, WIDTH-1, HEIGHT-1, pixels, HEIGHT*WIDTH);

	// Get red pixels from image and write them to the Bricklet buffer
	bool_array_from_image(image, pixels, 0xFF, 0, 0); 
	e_paper_296x128_write_color(&epaper, 0, 0, WIDTH-1, HEIGHT-1, pixels, HEIGHT*WIDTH);

	// Draw buffered values to the display
	e_paper_296x128_draw(&epaper);

	gdImageDestroy(image);

	printf("Press key to exit\n");
	getchar();
	e_paper_296x128_destroy(&epaper);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
