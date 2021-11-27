#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_e_paper_296x128.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your E-Paper 296x128 Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	EPaper296x128 ep;
	e_paper_296x128_create(&ep, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Use black background
	e_paper_296x128_fill_display(&ep, E_PAPER_296X128_COLOR_BLACK);

	// Write big white "Hello World" in the middle of the screen
	e_paper_296x128_draw_text(&ep, 16, 48, E_PAPER_296X128_FONT_24X32,
	                          E_PAPER_296X128_COLOR_WHITE,
	                          E_PAPER_296X128_ORIENTATION_HORIZONTAL, "Hello World");
	e_paper_296x128_draw(&ep);

	printf("Press key to exit\n");
	getchar();
	e_paper_296x128_destroy(&ep);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
