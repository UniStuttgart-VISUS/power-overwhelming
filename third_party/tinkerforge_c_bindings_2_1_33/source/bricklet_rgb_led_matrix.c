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

#include "bricklet_rgb_led_matrix.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*FrameStarted_CallbackFunction)(uint32_t frame_number, void *user_data);

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
	uint8_t red[64];
} ATTRIBUTE_PACKED SetRed_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRed_Request;

typedef struct {
	PacketHeader header;
	uint8_t red[64];
} ATTRIBUTE_PACKED GetRed_Response;

typedef struct {
	PacketHeader header;
	uint8_t green[64];
} ATTRIBUTE_PACKED SetGreen_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGreen_Request;

typedef struct {
	PacketHeader header;
	uint8_t green[64];
} ATTRIBUTE_PACKED GetGreen_Response;

typedef struct {
	PacketHeader header;
	uint8_t blue[64];
} ATTRIBUTE_PACKED SetBlue_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBlue_Request;

typedef struct {
	PacketHeader header;
	uint8_t blue[64];
} ATTRIBUTE_PACKED GetBlue_Response;

typedef struct {
	PacketHeader header;
	uint16_t frame_duration;
} ATTRIBUTE_PACKED SetFrameDuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameDuration_Request;

typedef struct {
	PacketHeader header;
	uint16_t frame_duration;
} ATTRIBUTE_PACKED GetFrameDuration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DrawFrame_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSupplyVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetSupplyVoltage_Response;

typedef struct {
	PacketHeader header;
	uint32_t frame_number;
} ATTRIBUTE_PACKED FrameStarted_Callback;

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

static void rgb_led_matrix_callback_wrapper_frame_started(DevicePrivate *device_p, Packet *packet) {
	FrameStarted_CallbackFunction callback_function;
	void *user_data;
	FrameStarted_Callback *callback;

	if (packet->header.length != sizeof(FrameStarted_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameStarted_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RGB_LED_MATRIX_CALLBACK_FRAME_STARTED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RGB_LED_MATRIX_CALLBACK_FRAME_STARTED];
	callback = (FrameStarted_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->frame_number = leconvert_uint32_from(callback->frame_number);

	callback_function(callback->frame_number, user_data);
}

void rgb_led_matrix_create(RGBLEDMatrix *rgb_led_matrix, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(rgb_led_matrix, uid, ipcon_p, 2, 0, 0, RGB_LED_MATRIX_DEVICE_IDENTIFIER);

	device_p = rgb_led_matrix->p;

	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_RED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_RED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_GREEN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_GREEN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_BLUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_BLUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_FRAME_DURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_FRAME_DURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_DRAW_FRAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_SUPPLY_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_MATRIX_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RGB_LED_MATRIX_CALLBACK_FRAME_STARTED] = rgb_led_matrix_callback_wrapper_frame_started;

	ipcon_add_device(ipcon_p, device_p);
}

void rgb_led_matrix_destroy(RGBLEDMatrix *rgb_led_matrix) {
	device_release(rgb_led_matrix->p);
}

int rgb_led_matrix_get_response_expected(RGBLEDMatrix *rgb_led_matrix, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rgb_led_matrix->p, function_id, ret_response_expected);
}

int rgb_led_matrix_set_response_expected(RGBLEDMatrix *rgb_led_matrix, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rgb_led_matrix->p, function_id, response_expected);
}

int rgb_led_matrix_set_response_expected_all(RGBLEDMatrix *rgb_led_matrix, bool response_expected) {
	return device_set_response_expected_all(rgb_led_matrix->p, response_expected);
}

void rgb_led_matrix_register_callback(RGBLEDMatrix *rgb_led_matrix, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(rgb_led_matrix->p, callback_id, function, user_data);
}

int rgb_led_matrix_get_api_version(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_api_version[3]) {
	return device_get_api_version(rgb_led_matrix->p, ret_api_version);
}

int rgb_led_matrix_set_red(RGBLEDMatrix *rgb_led_matrix, uint8_t red[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetRed_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_RED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.red, red, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_red(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_red[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetRed_Request request;
	GetRed_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_RED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_red, response.red, 64 * sizeof(uint8_t));

	return ret;
}

int rgb_led_matrix_set_green(RGBLEDMatrix *rgb_led_matrix, uint8_t green[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetGreen_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_GREEN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.green, green, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_green(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_green[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetGreen_Request request;
	GetGreen_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_GREEN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_green, response.green, 64 * sizeof(uint8_t));

	return ret;
}

int rgb_led_matrix_set_blue(RGBLEDMatrix *rgb_led_matrix, uint8_t blue[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetBlue_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_BLUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.blue, blue, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_blue(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_blue[64]) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetBlue_Request request;
	GetBlue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_BLUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_blue, response.blue, 64 * sizeof(uint8_t));

	return ret;
}

int rgb_led_matrix_set_frame_duration(RGBLEDMatrix *rgb_led_matrix, uint16_t frame_duration) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetFrameDuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_FRAME_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_duration = leconvert_uint16_to(frame_duration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_frame_duration(RGBLEDMatrix *rgb_led_matrix, uint16_t *ret_frame_duration) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetFrameDuration_Request request;
	GetFrameDuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_FRAME_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_duration = leconvert_uint16_from(response.frame_duration);

	return ret;
}

int rgb_led_matrix_draw_frame(RGBLEDMatrix *rgb_led_matrix) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	DrawFrame_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_DRAW_FRAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_supply_voltage(RGBLEDMatrix *rgb_led_matrix, uint16_t *ret_voltage) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetSupplyVoltage_Request request;
	GetSupplyVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_SUPPLY_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_uint16_from(response.voltage);

	return ret;
}

int rgb_led_matrix_get_spitfp_error_count(RGBLEDMatrix *rgb_led_matrix, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_set_bootloader_mode(RGBLEDMatrix *rgb_led_matrix, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_get_bootloader_mode(RGBLEDMatrix *rgb_led_matrix, uint8_t *ret_mode) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_set_write_firmware_pointer(RGBLEDMatrix *rgb_led_matrix, uint32_t pointer) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_write_firmware(RGBLEDMatrix *rgb_led_matrix, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_set_status_led_config(RGBLEDMatrix *rgb_led_matrix, uint8_t config) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_get_status_led_config(RGBLEDMatrix *rgb_led_matrix, uint8_t *ret_config) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_get_chip_temperature(RGBLEDMatrix *rgb_led_matrix, int16_t *ret_temperature) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_reset(RGBLEDMatrix *rgb_led_matrix) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_write_uid(RGBLEDMatrix *rgb_led_matrix, uint32_t uid) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_matrix_read_uid(RGBLEDMatrix *rgb_led_matrix, uint32_t *ret_uid) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int rgb_led_matrix_get_identity(RGBLEDMatrix *rgb_led_matrix, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rgb_led_matrix->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_MATRIX_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
