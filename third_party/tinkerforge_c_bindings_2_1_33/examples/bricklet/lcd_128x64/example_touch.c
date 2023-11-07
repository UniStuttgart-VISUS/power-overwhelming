#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_128x64.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 128x64 Bricklet

// Callback function for touch position callback
void cb_touch_position(uint16_t pressure, uint16_t x, uint16_t y, uint32_t age,
                       void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Pressure: %u\n", pressure);
	printf("X: %u\n", x);
	printf("Y: %u\n", y);
	printf("Age: %u\n", age);
	printf("\n");
}

// Callback function for touch gesture callback
void cb_touch_gesture(uint8_t gesture, uint32_t duration, uint16_t pressure_max,
                      uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end,
                      uint32_t age, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	if(gesture == LCD_128X64_GESTURE_LEFT_TO_RIGHT) {
		printf("Gesture: Left To Right\n");
	} else if(gesture == LCD_128X64_GESTURE_RIGHT_TO_LEFT) {
		printf("Gesture: Right To Left\n");
	} else if(gesture == LCD_128X64_GESTURE_TOP_TO_BOTTOM) {
		printf("Gesture: Top To Bottom\n");
	} else if(gesture == LCD_128X64_GESTURE_BOTTOM_TO_TOP) {
		printf("Gesture: Bottom To Top\n");
	}

	printf("Duration: %u\n", duration);
	printf("Pressure Max: %u\n", pressure_max);
	printf("X Start: %u\n", x_start);
	printf("X End: %u\n", x_end);
	printf("Y Start: %u\n", y_start);
	printf("Y End: %u\n", y_end);
	printf("Age: %u\n", age);
	printf("\n");
}

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

	// Register touch position callback to function cb_touch_position
	lcd_128x64_register_callback(&lcd,
	                             LCD_128X64_CALLBACK_TOUCH_POSITION,
	                             (void (*)(void))cb_touch_position,
	                             NULL);

	// Register touch gesture callback to function cb_touch_gesture
	lcd_128x64_register_callback(&lcd,
	                             LCD_128X64_CALLBACK_TOUCH_GESTURE,
	                             (void (*)(void))cb_touch_gesture,
	                             NULL);

	// Set period for touch position callback to 0.1s (100ms)
	lcd_128x64_set_touch_position_callback_configuration(&lcd, 100, true);

	// Set period for touch gesture callback to 0.1s (100ms)
	lcd_128x64_set_touch_gesture_callback_configuration(&lcd, 100, true);

	printf("Press key to exit\n");
	getchar();
	lcd_128x64_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
