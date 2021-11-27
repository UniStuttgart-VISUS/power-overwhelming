// This example is Windows only. Link to user32.lib in addition to ws2_32.lib

#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

#include "ip_connection.h"
#include "bricklet_joystick.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Joystick Bricklet

// Fake a mouse button event
void send_mouse_button(uint32_t event) {
	INPUT input;

	memset(&input, 0, sizeof(INPUT));

	input.type = INPUT_MOUSE;
	input.mi.dwFlags = event;

	SendInput(1, &input, sizeof(INPUT));
}

// Fake a mouse move event
void send_mouse_move(int16_t x, int16_t y) {
	INPUT input;
	memset(&input, 0, sizeof(INPUT));

	input.type = INPUT_MOUSE;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;

	SendInput(1, &input, sizeof(INPUT));
}

// Callback function for pressed and released events
void cb_pressed(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	send_mouse_button(MOUSEEVENTF_LEFTDOWN);
}

void cb_released(void *user_data) {
	(void)user_data; // avoid unused parameter warning

	send_mouse_button(MOUSEEVENTF_LEFTUP);
}

// Joystick moves mouse and the button is mapped to left mouse button
int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Joystick j;
	joystick_create(&j, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register pressed callback to function cb_pressed
	joystick_register_callback(&j,
	                           JOYSTICK_CALLBACK_PRESSED,
	                           (void (*)(void))cb_pressed,
	                           NULL);

	// Register released callback to function cb_released
	joystick_register_callback(&j,
	                           JOYSTICK_CALLBACK_RELEASED,
	                           (void (*)(void))cb_released,
	                           NULL);

	printf("Press ctrl+c to exit\n");

	while(true) {
		// Get current position
		int16_t x, y;
		if(joystick_get_position(&j, &x, &y) < 0) {
			fprintf(stderr, "Could not get position, probably timeout\n");
			return 1;
		}

		x = x / 4; // Slow down by factor of 4
		y = -y / 4; // Slow down by factor of 4 and invert axis

		send_mouse_move(x, y);

		Sleep(25); // Check Joystick position every 0.025s (25ms)
	}

	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}

#else

int main(void) {
	printf("This example is Windows only!\n");
	return 0;
}

#endif
