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

#include "bricklet_lcd_16x2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ButtonPressed_CallbackFunction)(uint8_t button, void *user_data);

typedef void (*ButtonReleased_CallbackFunction)(uint8_t button, void *user_data);

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
	uint8_t line;
	uint8_t position;
	char text[16];
} ATTRIBUTE_PACKED WriteLine_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ClearDisplay_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED BacklightOn_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED BacklightOff_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsBacklightOn_Request;

typedef struct {
	PacketHeader header;
	uint8_t backlight;
} ATTRIBUTE_PACKED IsBacklightOn_Response;

typedef struct {
	PacketHeader header;
	uint8_t cursor;
	uint8_t blinking;
} ATTRIBUTE_PACKED SetConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t cursor;
	uint8_t blinking;
} ATTRIBUTE_PACKED GetConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t button;
} ATTRIBUTE_PACKED IsButtonPressed_Request;

typedef struct {
	PacketHeader header;
	uint8_t pressed;
} ATTRIBUTE_PACKED IsButtonPressed_Response;

typedef struct {
	PacketHeader header;
	uint8_t button;
} ATTRIBUTE_PACKED ButtonPressed_Callback;

typedef struct {
	PacketHeader header;
	uint8_t button;
} ATTRIBUTE_PACKED ButtonReleased_Callback;

typedef struct {
	PacketHeader header;
	uint8_t index;
	uint8_t character[8];
} ATTRIBUTE_PACKED SetCustomCharacter_Request;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED GetCustomCharacter_Request;

typedef struct {
	PacketHeader header;
	uint8_t character[8];
} ATTRIBUTE_PACKED GetCustomCharacter_Response;

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

static void lcd_16x2_callback_wrapper_button_pressed(DevicePrivate *device_p, Packet *packet) {
	ButtonPressed_CallbackFunction callback_function;
	void *user_data;
	ButtonPressed_Callback *callback;

	if (packet->header.length != sizeof(ButtonPressed_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ButtonPressed_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_16X2_CALLBACK_BUTTON_PRESSED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_16X2_CALLBACK_BUTTON_PRESSED];
	callback = (ButtonPressed_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->button, user_data);
}

static void lcd_16x2_callback_wrapper_button_released(DevicePrivate *device_p, Packet *packet) {
	ButtonReleased_CallbackFunction callback_function;
	void *user_data;
	ButtonReleased_Callback *callback;

	if (packet->header.length != sizeof(ButtonReleased_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ButtonReleased_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LCD_16X2_CALLBACK_BUTTON_RELEASED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LCD_16X2_CALLBACK_BUTTON_RELEASED];
	callback = (ButtonReleased_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->button, user_data);
}

void lcd_16x2_create(LCD16x2 *lcd_16x2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(lcd_16x2, uid, ipcon_p, 2, 0, 1, LCD_16X2_DEVICE_IDENTIFIER);

	device_p = lcd_16x2->p;

	device_p->response_expected[LCD_16X2_FUNCTION_WRITE_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_CLEAR_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_BACKLIGHT_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_BACKLIGHT_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_IS_BACKLIGHT_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_16X2_FUNCTION_SET_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_GET_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_16X2_FUNCTION_IS_BUTTON_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_16X2_FUNCTION_SET_CUSTOM_CHARACTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LCD_16X2_FUNCTION_GET_CUSTOM_CHARACTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LCD_16X2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LCD_16X2_CALLBACK_BUTTON_PRESSED] = lcd_16x2_callback_wrapper_button_pressed;
	device_p->callback_wrappers[LCD_16X2_CALLBACK_BUTTON_RELEASED] = lcd_16x2_callback_wrapper_button_released;

	ipcon_add_device(ipcon_p, device_p);
}

void lcd_16x2_destroy(LCD16x2 *lcd_16x2) {
	device_release(lcd_16x2->p);
}

int lcd_16x2_get_response_expected(LCD16x2 *lcd_16x2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(lcd_16x2->p, function_id, ret_response_expected);
}

int lcd_16x2_set_response_expected(LCD16x2 *lcd_16x2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(lcd_16x2->p, function_id, response_expected);
}

int lcd_16x2_set_response_expected_all(LCD16x2 *lcd_16x2, bool response_expected) {
	return device_set_response_expected_all(lcd_16x2->p, response_expected);
}

void lcd_16x2_register_callback(LCD16x2 *lcd_16x2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(lcd_16x2->p, callback_id, function, user_data);
}

int lcd_16x2_get_api_version(LCD16x2 *lcd_16x2, uint8_t ret_api_version[3]) {
	return device_get_api_version(lcd_16x2->p, ret_api_version);
}

int lcd_16x2_write_line(LCD16x2 *lcd_16x2, uint8_t line, uint8_t position, const char *text) {
	DevicePrivate *device_p = lcd_16x2->p;
	WriteLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_WRITE_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.line = line;
	request.position = position;
	string_copy(request.text, text, 16);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_clear_display(LCD16x2 *lcd_16x2) {
	DevicePrivate *device_p = lcd_16x2->p;
	ClearDisplay_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_CLEAR_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_backlight_on(LCD16x2 *lcd_16x2) {
	DevicePrivate *device_p = lcd_16x2->p;
	BacklightOn_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_BACKLIGHT_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_backlight_off(LCD16x2 *lcd_16x2) {
	DevicePrivate *device_p = lcd_16x2->p;
	BacklightOff_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_BACKLIGHT_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_is_backlight_on(LCD16x2 *lcd_16x2, bool *ret_backlight) {
	DevicePrivate *device_p = lcd_16x2->p;
	IsBacklightOn_Request request;
	IsBacklightOn_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_IS_BACKLIGHT_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_backlight = response.backlight != 0;

	return ret;
}

int lcd_16x2_set_config(LCD16x2 *lcd_16x2, bool cursor, bool blinking) {
	DevicePrivate *device_p = lcd_16x2->p;
	SetConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_SET_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.cursor = cursor ? 1 : 0;
	request.blinking = blinking ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_get_config(LCD16x2 *lcd_16x2, bool *ret_cursor, bool *ret_blinking) {
	DevicePrivate *device_p = lcd_16x2->p;
	GetConfig_Request request;
	GetConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_GET_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_cursor = response.cursor != 0;
	*ret_blinking = response.blinking != 0;

	return ret;
}

int lcd_16x2_is_button_pressed(LCD16x2 *lcd_16x2, uint8_t button, bool *ret_pressed) {
	DevicePrivate *device_p = lcd_16x2->p;
	IsButtonPressed_Request request;
	IsButtonPressed_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_IS_BUTTON_PRESSED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.button = button;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pressed = response.pressed != 0;

	return ret;
}

int lcd_16x2_set_custom_character(LCD16x2 *lcd_16x2, uint8_t index, uint8_t character[8]) {
	DevicePrivate *device_p = lcd_16x2->p;
	SetCustomCharacter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_SET_CUSTOM_CHARACTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;
	memcpy(request.character, character, 8 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int lcd_16x2_get_custom_character(LCD16x2 *lcd_16x2, uint8_t index, uint8_t ret_character[8]) {
	DevicePrivate *device_p = lcd_16x2->p;
	GetCustomCharacter_Request request;
	GetCustomCharacter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_GET_CUSTOM_CHARACTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_character, response.character, 8 * sizeof(uint8_t));

	return ret;
}

int lcd_16x2_get_identity(LCD16x2 *lcd_16x2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = lcd_16x2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LCD_16X2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

#ifdef __cplusplus
}
#endif
