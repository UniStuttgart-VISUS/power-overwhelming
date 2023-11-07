#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_128x64.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 128x64 Bricklet

// Callback function for GUI button pressed callback
void cb_gui_button_pressed(uint8_t index, bool pressed, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Index: %u\n", index);
	printf("Pressed: %s\n", pressed ? "true" : "false");
	printf("\n");
}

// Callback function for GUI slider value callback
void cb_gui_slider_value(uint8_t index, uint8_t value, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Index: %u\n", index);
	printf("Value: %u\n", value);
	printf("\n");
}

// Callback function for GUI tab selected callback
void cb_gui_tab_selected(int8_t index, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Index: %d\n", index);
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

	// Register GUI button pressed callback to function cb_gui_button_pressed
	lcd_128x64_register_callback(&lcd,
	                             LCD_128X64_CALLBACK_GUI_BUTTON_PRESSED,
	                             (void (*)(void))cb_gui_button_pressed,
	                             NULL);

	// Register GUI slider value callback to function cb_gui_slider_value
	lcd_128x64_register_callback(&lcd,
	                             LCD_128X64_CALLBACK_GUI_SLIDER_VALUE,
	                             (void (*)(void))cb_gui_slider_value,
	                             NULL);

	// Register GUI tab selected callback to function cb_gui_tab_selected
	lcd_128x64_register_callback(&lcd,
	                             LCD_128X64_CALLBACK_GUI_TAB_SELECTED,
	                             (void (*)(void))cb_gui_tab_selected,
	                             NULL);

	// Clear display
	lcd_128x64_clear_display(&lcd);
	lcd_128x64_remove_all_gui(&lcd);

	// Add GUI elements: Button, Slider and Graph with 60 data points
	lcd_128x64_set_gui_button(&lcd, 0, 0, 0, 60, 20, "button");
	lcd_128x64_set_gui_slider(&lcd, 0, 0, 30, 60, LCD_128X64_DIRECTION_HORIZONTAL, 50);
	lcd_128x64_set_gui_graph_configuration(&lcd, 0, LCD_128X64_GRAPH_TYPE_LINE, 62, 0,
	                                       60, 52, "X", "Y");

	// Add a few data points (the remaining points will be 0)
	uint8_t data[12] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240};
	lcd_128x64_set_gui_graph_data(&lcd, 0, data, 12);

	// Add 5 text tabs without and configure it for click and swipe without auto-redraw
	lcd_128x64_set_gui_tab_configuration(&lcd, LCD_128X64_CHANGE_TAB_ON_CLICK_AND_SWIPE,
	                                     false);
	lcd_128x64_set_gui_tab_text(&lcd, 0, "Tab A");
	lcd_128x64_set_gui_tab_text(&lcd, 1, "Tab B");
	lcd_128x64_set_gui_tab_text(&lcd, 2, "Tab C");
	lcd_128x64_set_gui_tab_text(&lcd, 3, "Tab D");
	lcd_128x64_set_gui_tab_text(&lcd, 4, "Tab E");

	// Set period for GUI button pressed callback to 0.1s (100ms)
	lcd_128x64_set_gui_button_pressed_callback_configuration(&lcd, 100, true);

	// Set period for GUI slider value callback to 0.1s (100ms)
	lcd_128x64_set_gui_slider_value_callback_configuration(&lcd, 100, true);

	// Set period for GUI tab selected callback to 0.1s (100ms)
	lcd_128x64_set_gui_tab_selected_callback_configuration(&lcd, 100, true);

	printf("Press key to exit\n");
	getchar();
	lcd_128x64_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
