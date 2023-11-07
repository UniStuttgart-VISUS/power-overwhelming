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

#include "bricklet_rgb_led_button.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ButtonStateChanged_CallbackFunction)(uint8_t state, void *user_data);

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
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ATTRIBUTE_PACKED SetColor_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColor_Request;

typedef struct {
	PacketHeader header;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ATTRIBUTE_PACKED GetColor_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetButtonState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED GetButtonState_Response;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED ButtonStateChanged_Callback;

typedef struct {
	PacketHeader header;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ATTRIBUTE_PACKED SetColorCalibration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetColorCalibration_Request;

typedef struct {
	PacketHeader header;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ATTRIBUTE_PACKED GetColorCalibration_Response;

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

static void rgb_led_button_callback_wrapper_button_state_changed(DevicePrivate *device_p, Packet *packet) {
	ButtonStateChanged_CallbackFunction callback_function;
	void *user_data;
	ButtonStateChanged_Callback *callback;

	if (packet->header.length != sizeof(ButtonStateChanged_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ButtonStateChanged_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RGB_LED_BUTTON_CALLBACK_BUTTON_STATE_CHANGED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RGB_LED_BUTTON_CALLBACK_BUTTON_STATE_CHANGED];
	callback = (ButtonStateChanged_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state, user_data);
}

void rgb_led_button_create(RGBLEDButton *rgb_led_button, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(rgb_led_button, uid, ipcon_p, 2, 0, 0, RGB_LED_BUTTON_DEVICE_IDENTIFIER);

	device_p = rgb_led_button->p;

	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_SET_COLOR] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_COLOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_BUTTON_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_SET_COLOR_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_COLOR_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_BUTTON_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RGB_LED_BUTTON_CALLBACK_BUTTON_STATE_CHANGED] = rgb_led_button_callback_wrapper_button_state_changed;

	ipcon_add_device(ipcon_p, device_p);
}

void rgb_led_button_destroy(RGBLEDButton *rgb_led_button) {
	device_release(rgb_led_button->p);
}

int rgb_led_button_get_response_expected(RGBLEDButton *rgb_led_button, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rgb_led_button->p, function_id, ret_response_expected);
}

int rgb_led_button_set_response_expected(RGBLEDButton *rgb_led_button, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rgb_led_button->p, function_id, response_expected);
}

int rgb_led_button_set_response_expected_all(RGBLEDButton *rgb_led_button, bool response_expected) {
	return device_set_response_expected_all(rgb_led_button->p, response_expected);
}

void rgb_led_button_register_callback(RGBLEDButton *rgb_led_button, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(rgb_led_button->p, callback_id, function, user_data);
}

int rgb_led_button_get_api_version(RGBLEDButton *rgb_led_button, uint8_t ret_api_version[3]) {
	return device_get_api_version(rgb_led_button->p, ret_api_version);
}

int rgb_led_button_set_color(RGBLEDButton *rgb_led_button, uint8_t red, uint8_t green, uint8_t blue) {
	DevicePrivate *device_p = rgb_led_button->p;
	SetColor_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_SET_COLOR, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.red = red;
	request.green = green;
	request.blue = blue;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_get_color(RGBLEDButton *rgb_led_button, uint8_t *ret_red, uint8_t *ret_green, uint8_t *ret_blue) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetColor_Request request;
	GetColor_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_COLOR, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_red = response.red;
	*ret_green = response.green;
	*ret_blue = response.blue;

	return ret;
}

int rgb_led_button_get_button_state(RGBLEDButton *rgb_led_button, uint8_t *ret_state) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetButtonState_Request request;
	GetButtonState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_BUTTON_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_state = response.state;

	return ret;
}

int rgb_led_button_set_color_calibration(RGBLEDButton *rgb_led_button, uint8_t red, uint8_t green, uint8_t blue) {
	DevicePrivate *device_p = rgb_led_button->p;
	SetColorCalibration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_SET_COLOR_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.red = red;
	request.green = green;
	request.blue = blue;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_get_color_calibration(RGBLEDButton *rgb_led_button, uint8_t *ret_red, uint8_t *ret_green, uint8_t *ret_blue) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetColorCalibration_Request request;
	GetColorCalibration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_COLOR_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_red = response.red;
	*ret_green = response.green;
	*ret_blue = response.blue;

	return ret;
}

int rgb_led_button_get_spitfp_error_count(RGBLEDButton *rgb_led_button, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int rgb_led_button_set_bootloader_mode(RGBLEDButton *rgb_led_button, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = rgb_led_button->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rgb_led_button_get_bootloader_mode(RGBLEDButton *rgb_led_button, uint8_t *ret_mode) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rgb_led_button_set_write_firmware_pointer(RGBLEDButton *rgb_led_button, uint32_t pointer) {
	DevicePrivate *device_p = rgb_led_button->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_write_firmware(RGBLEDButton *rgb_led_button, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = rgb_led_button->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int rgb_led_button_set_status_led_config(RGBLEDButton *rgb_led_button, uint8_t config) {
	DevicePrivate *device_p = rgb_led_button->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_get_status_led_config(RGBLEDButton *rgb_led_button, uint8_t *ret_config) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rgb_led_button_get_chip_temperature(RGBLEDButton *rgb_led_button, int16_t *ret_temperature) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int rgb_led_button_reset(RGBLEDButton *rgb_led_button) {
	DevicePrivate *device_p = rgb_led_button->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_write_uid(RGBLEDButton *rgb_led_button, uint32_t uid) {
	DevicePrivate *device_p = rgb_led_button->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_button_read_uid(RGBLEDButton *rgb_led_button, uint32_t *ret_uid) {
	DevicePrivate *device_p = rgb_led_button->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int rgb_led_button_get_identity(RGBLEDButton *rgb_led_button, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rgb_led_button->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_BUTTON_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
