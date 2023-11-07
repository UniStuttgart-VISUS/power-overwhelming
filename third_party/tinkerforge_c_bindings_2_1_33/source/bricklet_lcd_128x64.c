/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_lcd_128x64.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TouchPosition_CallbackFunction)(uint16_t pressure, uint16_t x, uint16_t y, uint32_t age, void *user_data);

typedef void (*TouchGesture_CallbackFunction)(uint8_t gesture, uint32_t duration, uint16_t pressure_max, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint32_t age, void *user_data);

typedef void (*GUIButtonPressed_CallbackFunction)(uint8_t index, bool pressed, void *user_data);

typedef void (*GUISliderValue_CallbackFunction)(uint8_t index, uint8_t value, void *user_data);

typedef void (*GUITabSelected_CallbackFunction)(int8_t index, void *user_data);

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(push)
	#pragma pack(1)
	#define ATTRIBUTE_PACKED
#elif defined __GNUC__
	#ifdef _WIN32
		// workaround struct packing bug in GCC 4.7 on Windows
		// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52991
		#define ATTRIBUTE_PACKED __attribute__((gcc_struct, packed))
	#else
		#define ATTRIBUTE_PACKED __attribute__((packed))
	#endif
#else
	#error unknown compiler, do not know how to enable struct packing
#endif

typedef struct {
	PacketHeader header;
	uint8_t x_start;
	uint8_t y_start;
	uint8_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[56];
} ATTRIBUTE_PACKED WritePixelsLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t x_start;
	uint8_t y_start;
	uint8_t x_end;
	uint8_t y_end;
} ATTRIBUTE_PACKED ReadPixelsLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[60];
} ATTRIBUTE_PACKED ReadPixelsLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ClearDisplay_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t backlight;
	uint8_t invert;
	uint8_t automatic_draw;
} ATTRIBUTE_PACKED SetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t backlight;
	uint8_t invert;
	uint8_t automatic_draw;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t line;
	uint8_t position;
	char text[22];
} ATTRIBUTE_PACKED WriteLine_Request;

typedef struct {
	PacketHeader header;
	uint8_t force_complete_redraw;
} ATTRIBUTE_PACKED DrawBufferedFrame_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTouchPosition_Request;

typedef struct {
	PacketHeader header;
	uint16_t pressure;
	uint16_t x;
	uint16_t y;
	uint32_t age;
} ATTRIBUTE_PACKED GetTouchPosition_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetTouchPositionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTouchPositionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetTouchPositionCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t pressure;
	uint16_t x;
	uint16_t y;
	uint32_t age;
} ATTRIBUTE_PACKED TouchPosition_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTouchGesture_Request;

typedef struct {
	PacketHeader header;
	uint8_t gesture;
	uint32_t duration;
	uint16_t pressure_max;
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_end;
	uint16_t y_end;
	uint32_t age;
} ATTRIBUTE_PACKED GetTouchGesture_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetTouchGestureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTouchGestureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetTouchGestureCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t gesture;
	uint32_t duration;
	uint16_t pressure_max;
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_end;
	uint16_t y_end;
	uint32_t age;
} ATTRIBUTE_PACKED TouchGesture_Callback;

typedef struct {
	PacketHeader header;
	uint8_t position_x_start;
	uint8_t position_y_start;
	uint8_t position_x_end;
	uint8_t position_y_end;
	uint8_t color;
} ATTRIBUTE_PACKED DrawLine_Request;

typedef struct {
	PacketHeader header;
	uint8_t position_x_start;
	uint8_t position_y_start;
	uint8_t position_x_end;
	uint8_t position_y_end;
	uint8_t fill;
	uint8_t color;
} ATTRIBUTE_PACKED DrawBox_Request;

typedef struct {
	PacketHeader header;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t font;
	uint8_t color;
	char text[22];
} ATTRIBUTE_PACKED DrawText_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t width;
	uint8_t height;
	char text[16];
} ATTRIBUTE_PACKED SetGUIButton_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUIButton_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t width;
	uint8_t height;
	char text[16];
} ATTRIBUTE_PACKED GetGUIButton_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED RemoveGUIButton_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetGUIButtonPressedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGUIButtonPressedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetGUIButtonPressedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUIButtonPressed_Request;

typedef struct {
	PacketHeader header;
	uint8_t pressed;
} ATTRIBUTE_PACKED GetGUIButtonPressed_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t pressed;
} ATTRIBUTE_PACKED GUIButtonPressed_Callback;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t length;
	uint8_t direction;
	uint8_t value;
} ATTRIBUTE_PACKED SetGUISlider_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUISlider_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t length;
	uint8_t direction;
	uint8_t value;
} ATTRIBUTE_PACKED GetGUISlider_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED RemoveGUISlider_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetGUISliderValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGUISliderValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetGUISliderValueCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUISliderValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t value;
} ATTRIBUTE_PACKED GetGUISliderValue_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t value;
} ATTRIBUTE_PACKED GUISliderValue_Callback;

typedef struct {
	PacketHeader header;
	uint8_t change_tab_config;
	uint8_t clear_gui;
} ATTRIBUTE_PACKED SetGUITabConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGUITabConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t change_tab_config;
	uint8_t clear_gui;
} ATTRIBUTE_PACKED GetGUITabConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
	char text[5];
} ATTRIBUTE_PACKED SetGUITabText_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUITabText_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
	char text[5];
} ATTRIBUTE_PACKED GetGUITabText_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t icon[21];
} ATTRIBUTE_PACKED SetGUITabIcon_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUITabIcon_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
	uint8_t icon[21];
} ATTRIBUTE_PACKED GetGUITabIcon_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED RemoveGUITab_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED SetGUITabSelected_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetGUITabSelectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGUITabSelectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetGUITabSelectedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGUITabSelected_Request;

typedef struct {
	PacketHeader header;
	int8_t index;
} ATTRIBUTE_PACKED GetGUITabSelected_Response;

typedef struct {
	PacketHeader header;
	int8_t index;
} ATTRIBUTE_PACKED GUITabSelected_Callback;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t graph_type;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t width;
	uint8_t height;
	char text_x[4];
	char text_y[4];
} ATTRIBUTE_PACKED SetGUIGraphConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUIGraphConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
	uint8_t graph_type;
	uint8_t position_x;
	uint8_t position_y;
	uint8_t width;
	uint8_t height;
	char text_x[4];
	char text_y[4];
} ATTRIBUTE_PACKED GetGUIGraphConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint16_t data_length;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[59];
} ATTRIBUTE_PACKED SetGUIGraphDataLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetGUIGraphDataLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t data_length;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[59];
} ATTRIBUTE_PACKED GetGUIGraphDataLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED RemoveGUIGraph_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED RemoveAllGUI_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetTouchLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTouchLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetTouchLEDConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t error_count_ack_checksum;
	uint32_t error_count_message_checksum;
	uint32_t error_count_frame;
	uint32_t error_count_overflow;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED SetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
	uint32_t pointer;
} ATTRIBUTE_PACKED SetWriteFirmwarePointer_Request;

typedef struct {
	PacketHeader header;
	uint8_t data[64];
} ATTRIBUTE_PACKED WriteFirmware_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED WriteFirmware_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Reset_Request;

typedef struct {
	PacketHeader header;
	uint32_t uid;
} ATTRIBUTE_PACKED WriteUID_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadUID_Request;

typedef struct {
	PacketHeader header;
	uint32_t uid;
} ATTRIBUTE_PACKED ReadUID_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIdentity_Request;

typedef struct {
	PacketHeader header;
	char uid[8];
	char connected_uid[8];
	char position;
	uint8_t hardware_version[3];
	uint8_t firmware_version[3];
	uint16_t device_identifier;
} ATTRIBUTE_PACKED GetIdentity_Response;

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(pop)
#endif
#undef ATTRIBUTE_PACKED

static void lcd_128x64_callback_wrapper_touch_position(DevicePrivate *device_p, Packet *packet) {
	TouchPosition_CallbackFunction callback_function;
	void *user_data;
	TouchPosition_Callback *callback;

	if (packet->header.length != sizeof(TouchPosition_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (TouchPosition_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_TOUCH_POSITION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_TOUCH_POSITION];
	callback = (TouchPosition_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->pressure = leconvert_uint16_from(callback->pressure);
	callback->x = leconvert_uint16_from(callback->x);
	callback->y = leconvert_uint16_from(callback->y);
	callback->age = leconvert_uint32_from(callback->age);

	callback_function(callback->pressure, callback->x, callback->y, callback->age, user_data);
}

static void lcd_128x64_callback_wrapper_touch_gesture(DevicePrivate *device_p, Packet *packet) {
	TouchGesture_CallbackFunction callback_function;
	void *user_data;
	TouchGesture_Callback *callback;

	if (packet->header.length != sizeof(TouchGesture_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (TouchGesture_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_TOUCH_GESTURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_TOUCH_GESTURE];
	callback = (TouchGesture_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->duration = leconvert_uint32_from(callback->duration);
	callback->pressure_max = leconvert_uint16_from(callback->pressure_max);
	callback->x_start = leconvert_uint16_from(callback->x_start);
	callback->y_start = leconvert_uint16_from(callback->y_start);
	callback->x_end = leconvert_uint16_from(callback->x_end);
	callback->y_end = leconvert_uint16_from(callback->y_end);
	callback->age = leconvert_uint32_from(callback->age);

	callback_function(callback->gesture, callback->duration, callback->pressure_max, callback->x_start, callback->y_start, callback->x_end, callback->y_end, callback->age, user_data);
}

static void lcd_128x64_callback_wrapper_gui_button_pressed(DevicePrivate *device_p, Packet *packet) {
	GUIButtonPressed_CallbackFunction callback_function;
	void *user_data;
	GUIButtonPressed_Callback *callback;
	bool unpacked_pressed;

	if (packet->header.length != sizeof(GUIButtonPressed_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GUIButtonPressed_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_BUTTON_PRESSED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_BUTTON_PRESSED];
	callback = (GUIButtonPressed_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_pressed = callback->pressed != 0;

	callback_function(callback->index, unpacked_pressed, user_data);
}

static void lcd_128x64_callback_wrapper_gui_slider_value(DevicePrivate *device_p, Packet *packet) {
	GUISliderValue_CallbackFunction callback_function;
	void *user_data;
	GUISliderValue_Callback *callback;

	if (packet->header.length != sizeof(GUISliderValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GUISliderValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_SLIDER_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_SLIDER_VALUE];
	callback = (GUISliderValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->index, callback->value, user_data);
}

static void lcd_128x64_callback_wrapper_gui_tab_selected(DevicePrivate *device_p, Packet *packet) {
	GUITabSelected_CallbackFunction callback_function;
	void *user_data;
	GUITabSelected_Callback *callback;

	if (packet->header.length != sizeof(GUITabSelected_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GUITabSelected_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_TAB_SELECTED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_128X64_CALLBACK_GUI_TAB_SELECTED];
	callback = (GUITabSelected_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->index, user_data);
}

void lcd_128x64_create(LCD128x64 *lcd_128x64, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(lcd_128x64, uid, ipcon_p, 2, 0, 1, LCD_128X64_DEVICE_IDENTIFIER);

	device_p = lcd_128x64->p;

	device_p->response_expected[LCD_128X64_FUNCTION_WRITE_PIXELS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_READ_PIXELS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_CLEAR_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_WRITE_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_DRAW_BUFFERED_FRAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_TOUCH_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_TOUCH_POSITION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_TOUCH_POSITION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_TOUCH_GESTURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_TOUCH_GESTURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_TOUCH_GESTURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_DRAW_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_DRAW_BOX] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_DRAW_TEXT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_BUTTON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_BUTTON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_REMOVE_GUI_BUTTON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_BUTTON_PRESSED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_BUTTON_PRESSED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_BUTTON_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_SLIDER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_SLIDER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_REMOVE_GUI_SLIDER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_SLIDER_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_SLIDER_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_SLIDER_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_TAB_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_TAB_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_TAB_TEXT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_TAB_TEXT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_TAB_ICON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_TAB_ICON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_REMOVE_GUI_TAB] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_TAB_SELECTED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_TAB_SELECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_TAB_SELECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_TAB_SELECTED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_GRAPH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_GRAPH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_GUI_GRAPH_DATA_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_GUI_GRAPH_DATA_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_REMOVE_GUI_GRAPH] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_REMOVE_ALL_GUI] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_TOUCH_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_TOUCH_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_128X64_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_128X64_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LCD_128X64_CALLBACK_TOUCH_POSITION] = lcd_128x64_callback_wrapper_touch_position;
	device_p->callback_wrappers[LCD_128X64_CALLBACK_TOUCH_GESTURE] = lcd_128x64_callback_wrapper_touch_gesture;
	device_p->callback_wrappers[LCD_128X64_CALLBACK_GUI_BUTTON_PRESSED] = lcd_128x64_callback_wrapper_gui_button_pressed;
	device_p->callback_wrappers[LCD_128X64_CALLBACK_GUI_SLIDER_VALUE] = lcd_128x64_callback_wrapper_gui_slider_value;
	device_p->callback_wrappers[LCD_128X64_CALLBACK_GUI_TAB_SELECTED] = lcd_128x64_callback_wrapper_gui_tab_selected;

	ipcon_add_device(ipcon_p, device_p);
}

void lcd_128x64_destroy(LCD128x64 *lcd_128x64) {
	device_release(lcd_128x64->p);
}

int lcd_128x64_get_response_expected(LCD128x64 *lcd_128x64, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(lcd_128x64->p, function_id, ret_response_expected);
}

int lcd_128x64_set_response_expected(LCD128x64 *lcd_128x64, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(lcd_128x64->p, function_id, response_expected);
}

int lcd_128x64_set_response_expected_all(LCD128x64 *lcd_128x64, bool response_expected) {
	return device_set_response_expected_all(lcd_128x64->p, response_expected);
}

void lcd_128x64_register_callback(LCD128x64 *lcd_128x64, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(lcd_128x64->p, callback_id, function, user_data);
}

int lcd_128x64_get_api_version(LCD128x64 *lcd_128x64, uint8_t ret_api_version[3]) {
	return device_get_api_version(lcd_128x64->p, ret_api_version);
}

int lcd_128x64_write_pixels_low_level(LCD128x64 *lcd_128x64, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint16_t pixels_length, uint16_t pixels_chunk_offset, bool pixels_chunk_data[448]) {
	DevicePrivate *device_p = lcd_128x64->p;
	WritePixelsLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_WRITE_PIXELS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = x_start;
	request.y_start = y_start;
	request.x_end = x_end;
	request.y_end = y_end;
	request.pixels_length = leconvert_uint16_to(pixels_length);
	request.pixels_chunk_offset = leconvert_uint16_to(pixels_chunk_offset);
	memset(request.pixels_chunk_data, 0, 56); for (i = 0; i < 448; i++) request.pixels_chunk_data[i / 8] |= (pixels_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_read_pixels_low_level(LCD128x64 *lcd_128x64, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint16_t *ret_pixels_length, uint16_t *ret_pixels_chunk_offset, bool ret_pixels_chunk_data[480]) {
	DevicePrivate *device_p = lcd_128x64->p;
	ReadPixelsLowLevel_Request request;
	ReadPixelsLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_READ_PIXELS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = x_start;
	request.y_start = y_start;
	request.x_end = x_end;
	request.y_end = y_end;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pixels_length = leconvert_uint16_from(response.pixels_length);
	*ret_pixels_chunk_offset = leconvert_uint16_from(response.pixels_chunk_offset);
	for (i = 0; i < 480; i++) ret_pixels_chunk_data[i] = (response.pixels_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int lcd_128x64_clear_display(LCD128x64 *lcd_128x64) {
	DevicePrivate *device_p = lcd_128x64->p;
	ClearDisplay_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_CLEAR_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_display_configuration(LCD128x64 *lcd_128x64, uint8_t contrast, uint8_t backlight, bool invert, bool automatic_draw) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetDisplayConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.contrast = contrast;
	request.backlight = backlight;
	request.invert = invert ? 1 : 0;
	request.automatic_draw = automatic_draw ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_display_configuration(LCD128x64 *lcd_128x64, uint8_t *ret_contrast, uint8_t *ret_backlight, bool *ret_invert, bool *ret_automatic_draw) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetDisplayConfiguration_Request request;
	GetDisplayConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_contrast = response.contrast;
	*ret_backlight = response.backlight;
	*ret_invert = response.invert != 0;
	*ret_automatic_draw = response.automatic_draw != 0;

	return ret;
}

int lcd_128x64_write_line(LCD128x64 *lcd_128x64, uint8_t line, uint8_t position, const char *text) {
	DevicePrivate *device_p = lcd_128x64->p;
	WriteLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_WRITE_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.line = line;
	request.position = position;
	string_copy(request.text, text, 22);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_draw_buffered_frame(LCD128x64 *lcd_128x64, bool force_complete_redraw) {
	DevicePrivate *device_p = lcd_128x64->p;
	DrawBufferedFrame_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_DRAW_BUFFERED_FRAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.force_complete_redraw = force_complete_redraw ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_touch_position(LCD128x64 *lcd_128x64, uint16_t *ret_pressure, uint16_t *ret_x, uint16_t *ret_y, uint32_t *ret_age) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetTouchPosition_Request request;
	GetTouchPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_TOUCH_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pressure = leconvert_uint16_from(response.pressure);
	*ret_x = leconvert_uint16_from(response.x);
	*ret_y = leconvert_uint16_from(response.y);
	*ret_age = leconvert_uint32_from(response.age);

	return ret;
}

int lcd_128x64_set_touch_position_callback_configuration(LCD128x64 *lcd_128x64, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetTouchPositionCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_TOUCH_POSITION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_touch_position_callback_configuration(LCD128x64 *lcd_128x64, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetTouchPositionCallbackConfiguration_Request request;
	GetTouchPositionCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_TOUCH_POSITION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int lcd_128x64_get_touch_gesture(LCD128x64 *lcd_128x64, uint8_t *ret_gesture, uint32_t *ret_duration, uint16_t *ret_pressure_max, uint16_t *ret_x_start, uint16_t *ret_y_start, uint16_t *ret_x_end, uint16_t *ret_y_end, uint32_t *ret_age) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetTouchGesture_Request request;
	GetTouchGesture_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_TOUCH_GESTURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_gesture = response.gesture;
	*ret_duration = leconvert_uint32_from(response.duration);
	*ret_pressure_max = leconvert_uint16_from(response.pressure_max);
	*ret_x_start = leconvert_uint16_from(response.x_start);
	*ret_y_start = leconvert_uint16_from(response.y_start);
	*ret_x_end = leconvert_uint16_from(response.x_end);
	*ret_y_end = leconvert_uint16_from(response.y_end);
	*ret_age = leconvert_uint32_from(response.age);

	return ret;
}

int lcd_128x64_set_touch_gesture_callback_configuration(LCD128x64 *lcd_128x64, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetTouchGestureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_TOUCH_GESTURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_touch_gesture_callback_configuration(LCD128x64 *lcd_128x64, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetTouchGestureCallbackConfiguration_Request request;
	GetTouchGestureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_TOUCH_GESTURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int lcd_128x64_draw_line(LCD128x64 *lcd_128x64, uint8_t position_x_start, uint8_t position_y_start, uint8_t position_x_end, uint8_t position_y_end, bool color) {
	DevicePrivate *device_p = lcd_128x64->p;
	DrawLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_DRAW_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x_start = position_x_start;
	request.position_y_start = position_y_start;
	request.position_x_end = position_x_end;
	request.position_y_end = position_y_end;
	request.color = color ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_draw_box(LCD128x64 *lcd_128x64, uint8_t position_x_start, uint8_t position_y_start, uint8_t position_x_end, uint8_t position_y_end, bool fill, bool color) {
	DevicePrivate *device_p = lcd_128x64->p;
	DrawBox_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_DRAW_BOX, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x_start = position_x_start;
	request.position_y_start = position_y_start;
	request.position_x_end = position_x_end;
	request.position_y_end = position_y_end;
	request.fill = fill ? 1 : 0;
	request.color = color ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_draw_text(LCD128x64 *lcd_128x64, uint8_t position_x, uint8_t position_y, uint8_t font, bool color, const char *text) {
	DevicePrivate *device_p = lcd_128x64->p;
	DrawText_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_DRAW_TEXT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x = position_x;
	request.position_y = position_y;
	request.font = font;
	request.color = color ? 1 : 0;
	string_copy(request.text, text, 22);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_gui_button(LCD128x64 *lcd_128x64, uint8_t index, uint8_t position_x, uint8_t position_y, uint8_t width, uint8_t height, const char *text) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUIButton_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_BUTTON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	request.position_x = position_x;
	request.position_y = position_y;
	request.width = width;
	request.height = height;
	string_copy(request.text, text, 16);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_button(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_active, uint8_t *ret_position_x, uint8_t *ret_position_y, uint8_t *ret_width, uint8_t *ret_height, char ret_text[16]) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUIButton_Request request;
	GetGUIButton_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_BUTTON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;
	*ret_position_x = response.position_x;
	*ret_position_y = response.position_y;
	*ret_width = response.width;
	*ret_height = response.height;
	memcpy(ret_text, response.text, 16);

	return ret;
}

int lcd_128x64_remove_gui_button(LCD128x64 *lcd_128x64, uint8_t index) {
	DevicePrivate *device_p = lcd_128x64->p;
	RemoveGUIButton_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_REMOVE_GUI_BUTTON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_gui_button_pressed_callback_configuration(LCD128x64 *lcd_128x64, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUIButtonPressedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_BUTTON_PRESSED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_button_pressed_callback_configuration(LCD128x64 *lcd_128x64, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUIButtonPressedCallbackConfiguration_Request request;
	GetGUIButtonPressedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_BUTTON_PRESSED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int lcd_128x64_get_gui_button_pressed(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_pressed) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUIButtonPressed_Request request;
	GetGUIButtonPressed_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_BUTTON_PRESSED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pressed = response.pressed != 0;

	return ret;
}

int lcd_128x64_set_gui_slider(LCD128x64 *lcd_128x64, uint8_t index, uint8_t position_x, uint8_t position_y, uint8_t length, uint8_t direction, uint8_t value) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUISlider_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_SLIDER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	request.position_x = position_x;
	request.position_y = position_y;
	request.length = length;
	request.direction = direction;
	request.value = value;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_slider(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_active, uint8_t *ret_position_x, uint8_t *ret_position_y, uint8_t *ret_length, uint8_t *ret_direction, uint8_t *ret_value) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUISlider_Request request;
	GetGUISlider_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_SLIDER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;
	*ret_position_x = response.position_x;
	*ret_position_y = response.position_y;
	*ret_length = response.length;
	*ret_direction = response.direction;
	*ret_value = response.value;

	return ret;
}

int lcd_128x64_remove_gui_slider(LCD128x64 *lcd_128x64, uint8_t index) {
	DevicePrivate *device_p = lcd_128x64->p;
	RemoveGUISlider_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_REMOVE_GUI_SLIDER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_gui_slider_value_callback_configuration(LCD128x64 *lcd_128x64, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUISliderValueCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_SLIDER_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_slider_value_callback_configuration(LCD128x64 *lcd_128x64, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUISliderValueCallbackConfiguration_Request request;
	GetGUISliderValueCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_SLIDER_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int lcd_128x64_get_gui_slider_value(LCD128x64 *lcd_128x64, uint8_t index, uint8_t *ret_value) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUISliderValue_Request request;
	GetGUISliderValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_SLIDER_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = response.value;

	return ret;
}

int lcd_128x64_set_gui_tab_configuration(LCD128x64 *lcd_128x64, uint8_t change_tab_config, bool clear_gui) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUITabConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_TAB_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.change_tab_config = change_tab_config;
	request.clear_gui = clear_gui ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_tab_configuration(LCD128x64 *lcd_128x64, uint8_t *ret_change_tab_config, bool *ret_clear_gui) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUITabConfiguration_Request request;
	GetGUITabConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_TAB_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_change_tab_config = response.change_tab_config;
	*ret_clear_gui = response.clear_gui != 0;

	return ret;
}

int lcd_128x64_set_gui_tab_text(LCD128x64 *lcd_128x64, uint8_t index, const char *text) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUITabText_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_TAB_TEXT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	string_copy(request.text, text, 5);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_tab_text(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_active, char ret_text[5]) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUITabText_Request request;
	GetGUITabText_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_TAB_TEXT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;
	memcpy(ret_text, response.text, 5);

	return ret;
}

int lcd_128x64_set_gui_tab_icon(LCD128x64 *lcd_128x64, uint8_t index, bool icon[168]) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUITabIcon_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_TAB_ICON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	memset(request.icon, 0, 21); for (i = 0; i < 168; i++) request.icon[i / 8] |= (icon[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_tab_icon(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_active, bool ret_icon[168]) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUITabIcon_Request request;
	GetGUITabIcon_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_TAB_ICON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;
	for (i = 0; i < 168; i++) ret_icon[i] = (response.icon[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int lcd_128x64_remove_gui_tab(LCD128x64 *lcd_128x64, uint8_t index) {
	DevicePrivate *device_p = lcd_128x64->p;
	RemoveGUITab_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_REMOVE_GUI_TAB, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_gui_tab_selected(LCD128x64 *lcd_128x64, uint8_t index) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUITabSelected_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_TAB_SELECTED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_gui_tab_selected_callback_configuration(LCD128x64 *lcd_128x64, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUITabSelectedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_TAB_SELECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_tab_selected_callback_configuration(LCD128x64 *lcd_128x64, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUITabSelectedCallbackConfiguration_Request request;
	GetGUITabSelectedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_TAB_SELECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int lcd_128x64_get_gui_tab_selected(LCD128x64 *lcd_128x64, int8_t *ret_index) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUITabSelected_Request request;
	GetGUITabSelected_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_TAB_SELECTED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_index = response.index;

	return ret;
}

int lcd_128x64_set_gui_graph_configuration(LCD128x64 *lcd_128x64, uint8_t index, uint8_t graph_type, uint8_t position_x, uint8_t position_y, uint8_t width, uint8_t height, const char *text_x, const char *text_y) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUIGraphConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_GRAPH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	request.graph_type = graph_type;
	request.position_x = position_x;
	request.position_y = position_y;
	request.width = width;
	request.height = height;
	string_copy(request.text_x, text_x, 4);

	string_copy(request.text_y, text_y, 4);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_graph_configuration(LCD128x64 *lcd_128x64, uint8_t index, bool *ret_active, uint8_t *ret_graph_type, uint8_t *ret_position_x, uint8_t *ret_position_y, uint8_t *ret_width, uint8_t *ret_height, char ret_text_x[4], char ret_text_y[4]) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUIGraphConfiguration_Request request;
	GetGUIGraphConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_GRAPH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;
	*ret_graph_type = response.graph_type;
	*ret_position_x = response.position_x;
	*ret_position_y = response.position_y;
	*ret_width = response.width;
	*ret_height = response.height;
	memcpy(ret_text_x, response.text_x, 4);
	memcpy(ret_text_y, response.text_y, 4);

	return ret;
}

int lcd_128x64_set_gui_graph_data_low_level(LCD128x64 *lcd_128x64, uint8_t index, uint16_t data_length, uint16_t data_chunk_offset, uint8_t data_chunk_data[59]) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetGUIGraphDataLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_GUI_GRAPH_DATA_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	request.data_length = leconvert_uint16_to(data_length);
	request.data_chunk_offset = leconvert_uint16_to(data_chunk_offset);
	memcpy(request.data_chunk_data, data_chunk_data, 59 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_gui_graph_data_low_level(LCD128x64 *lcd_128x64, uint8_t index, uint16_t *ret_data_length, uint16_t *ret_data_chunk_offset, uint8_t ret_data_chunk_data[59]) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetGUIGraphDataLowLevel_Request request;
	GetGUIGraphDataLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_GUI_GRAPH_DATA_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_data_length = leconvert_uint16_from(response.data_length);
	*ret_data_chunk_offset = leconvert_uint16_from(response.data_chunk_offset);
	memcpy(ret_data_chunk_data, response.data_chunk_data, 59 * sizeof(uint8_t));

	return ret;
}

int lcd_128x64_remove_gui_graph(LCD128x64 *lcd_128x64, uint8_t index) {
	DevicePrivate *device_p = lcd_128x64->p;
	RemoveGUIGraph_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_REMOVE_GUI_GRAPH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_remove_all_gui(LCD128x64 *lcd_128x64) {
	DevicePrivate *device_p = lcd_128x64->p;
	RemoveAllGUI_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_REMOVE_ALL_GUI, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_set_touch_led_config(LCD128x64 *lcd_128x64, uint8_t config) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetTouchLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_TOUCH_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_touch_led_config(LCD128x64 *lcd_128x64, uint8_t *ret_config) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetTouchLEDConfig_Request request;
	GetTouchLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_TOUCH_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int lcd_128x64_get_spitfp_error_count(LCD128x64 *lcd_128x64, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_error_count_ack_checksum = leconvert_uint32_from(response.error_count_ack_checksum);
	*ret_error_count_message_checksum = leconvert_uint32_from(response.error_count_message_checksum);
	*ret_error_count_frame = leconvert_uint32_from(response.error_count_frame);
	*ret_error_count_overflow = leconvert_uint32_from(response.error_count_overflow);

	return ret;
}

int lcd_128x64_set_bootloader_mode(LCD128x64 *lcd_128x64, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int lcd_128x64_get_bootloader_mode(LCD128x64 *lcd_128x64, uint8_t *ret_mode) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_mode = response.mode;

	return ret;
}

int lcd_128x64_set_write_firmware_pointer(LCD128x64 *lcd_128x64, uint32_t pointer) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_write_firmware(LCD128x64 *lcd_128x64, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = lcd_128x64->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int lcd_128x64_set_status_led_config(LCD128x64 *lcd_128x64, uint8_t config) {
	DevicePrivate *device_p = lcd_128x64->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_get_status_led_config(LCD128x64 *lcd_128x64, uint8_t *ret_config) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int lcd_128x64_get_chip_temperature(LCD128x64 *lcd_128x64, int16_t *ret_temperature) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int16_from(response.temperature);

	return ret;
}

int lcd_128x64_reset(LCD128x64 *lcd_128x64) {
	DevicePrivate *device_p = lcd_128x64->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_write_uid(LCD128x64 *lcd_128x64, uint32_t uid) {
	DevicePrivate *device_p = lcd_128x64->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_128x64_read_uid(LCD128x64 *lcd_128x64, uint32_t *ret_uid) {
	DevicePrivate *device_p = lcd_128x64->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uid = leconvert_uint32_from(response.uid);

	return ret;
}

int lcd_128x64_get_identity(LCD128x64 *lcd_128x64, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = lcd_128x64->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LCD_128X64_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_uid, response.uid, 8);
	memcpy(ret_connected_uid, response.connected_uid, 8);
	*ret_position = response.position;
	memcpy(ret_hardware_version, response.hardware_version, 3 * sizeof(uint8_t));
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	*ret_device_identifier = leconvert_uint16_from(response.device_identifier);

	return ret;
}

int lcd_128x64_write_pixels(LCD128x64 *lcd_128x64, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, bool *pixels, uint16_t pixels_length) {
	DevicePrivate *device_p = lcd_128x64->p;
	int ret = 0;
	uint16_t pixels_chunk_offset = 0;
	bool pixels_chunk_data[448];
	uint16_t pixels_chunk_length;

	if (pixels_length == 0) {
		memset(&pixels_chunk_data, 0, sizeof(bool) * 448);

		ret = lcd_128x64_write_pixels_low_level(lcd_128x64, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (pixels_chunk_offset < pixels_length) {
			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 448) {
				pixels_chunk_length = 448;
			}

			memcpy(pixels_chunk_data, &pixels[pixels_chunk_offset], sizeof(bool) * pixels_chunk_length);
			memset(&pixels_chunk_data[pixels_chunk_length], 0, sizeof(bool) * (448 - pixels_chunk_length));

			ret = lcd_128x64_write_pixels_low_level(lcd_128x64, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				break;
			}

			pixels_chunk_offset += 448;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int lcd_128x64_read_pixels(LCD128x64 *lcd_128x64, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, bool *ret_pixels, uint16_t *ret_pixels_length) {
	DevicePrivate *device_p = lcd_128x64->p;
	int ret = 0;
	uint16_t pixels_length = 0;
	uint16_t pixels_chunk_offset;
	bool pixels_chunk_data[480];
	bool pixels_out_of_sync;
	uint16_t pixels_chunk_length;

	*ret_pixels_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = lcd_128x64_read_pixels_low_level(lcd_128x64, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	pixels_out_of_sync = pixels_chunk_offset != 0;

	if (!pixels_out_of_sync) {
		pixels_chunk_length = pixels_length - pixels_chunk_offset;

		if (pixels_chunk_length > 480) {
			pixels_chunk_length = 480;
		}

		memcpy(ret_pixels, pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
		*ret_pixels_length = pixels_chunk_length;

		while (*ret_pixels_length < pixels_length) {
			ret = lcd_128x64_read_pixels_low_level(lcd_128x64, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			pixels_out_of_sync = pixels_chunk_offset != *ret_pixels_length;

			if (pixels_out_of_sync) {
				break;
			}

			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 480) {
				pixels_chunk_length = 480;
			}

			memcpy(&ret_pixels[*ret_pixels_length], pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
			*ret_pixels_length += pixels_chunk_length;
		}
	}

	if (pixels_out_of_sync) {
		*ret_pixels_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (pixels_chunk_offset + 480 < pixels_length) {
			ret = lcd_128x64_read_pixels_low_level(lcd_128x64, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

int lcd_128x64_set_gui_graph_data(LCD128x64 *lcd_128x64, uint8_t index, uint8_t *data, uint16_t data_length) {
	DevicePrivate *device_p = lcd_128x64->p;
	int ret = 0;
	uint16_t data_chunk_offset = 0;
	uint8_t data_chunk_data[59];
	uint16_t data_chunk_length;

	if (data_length == 0) {
		memset(&data_chunk_data, 0, sizeof(uint8_t) * 59);

		ret = lcd_128x64_set_gui_graph_data_low_level(lcd_128x64, index, data_length, data_chunk_offset, data_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (data_chunk_offset < data_length) {
			data_chunk_length = data_length - data_chunk_offset;

			if (data_chunk_length > 59) {
				data_chunk_length = 59;
			}

			memcpy(data_chunk_data, &data[data_chunk_offset], sizeof(uint8_t) * data_chunk_length);
			memset(&data_chunk_data[data_chunk_length], 0, sizeof(uint8_t) * (59 - data_chunk_length));

			ret = lcd_128x64_set_gui_graph_data_low_level(lcd_128x64, index, data_length, data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				break;
			}

			data_chunk_offset += 59;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int lcd_128x64_get_gui_graph_data(LCD128x64 *lcd_128x64, uint8_t index, uint8_t *ret_data, uint16_t *ret_data_length) {
	DevicePrivate *device_p = lcd_128x64->p;
	int ret = 0;
	uint16_t data_length = 0;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[59];
	bool data_out_of_sync;
	uint16_t data_chunk_length;

	*ret_data_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = lcd_128x64_get_gui_graph_data_low_level(lcd_128x64, index, &data_length, &data_chunk_offset, data_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	data_out_of_sync = data_chunk_offset != 0;

	if (!data_out_of_sync) {
		data_chunk_length = data_length - data_chunk_offset;

		if (data_chunk_length > 59) {
			data_chunk_length = 59;
		}

		memcpy(ret_data, data_chunk_data, sizeof(uint8_t) * data_chunk_length);
		*ret_data_length = data_chunk_length;

		while (*ret_data_length < data_length) {
			ret = lcd_128x64_get_gui_graph_data_low_level(lcd_128x64, index, &data_length, &data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			data_out_of_sync = data_chunk_offset != *ret_data_length;

			if (data_out_of_sync) {
				break;
			}

			data_chunk_length = data_length - data_chunk_offset;

			if (data_chunk_length > 59) {
				data_chunk_length = 59;
			}

			memcpy(&ret_data[*ret_data_length], data_chunk_data, sizeof(uint8_t) * data_chunk_length);
			*ret_data_length += data_chunk_length;
		}
	}

	if (data_out_of_sync) {
		*ret_data_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (data_chunk_offset + 59 < data_length) {
			ret = lcd_128x64_get_gui_graph_data_low_level(lcd_128x64, index, &data_length, &data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

#ifdef __cplusplus
}
#endif
