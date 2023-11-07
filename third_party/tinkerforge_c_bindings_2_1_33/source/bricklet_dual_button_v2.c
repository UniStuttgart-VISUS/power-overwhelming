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

#include "bricklet_dual_button_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*StateChanged_CallbackFunction)(uint8_t button_l, uint8_t button_r, uint8_t led_l, uint8_t led_r, void *user_data);

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
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED SetLEDState_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLEDState_Request;

typedef struct {
	PacketHeader header;
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED GetLEDState_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetButtonState_Request;

typedef struct {
	PacketHeader header;
	uint8_t button_l;
	uint8_t button_r;
} ATTRIBUTE_PACKED GetButtonState_Response;

typedef struct {
	PacketHeader header;
	uint8_t button_l;
	uint8_t button_r;
	uint8_t led_l;
	uint8_t led_r;
} ATTRIBUTE_PACKED StateChanged_Callback;

typedef struct {
	PacketHeader header;
	uint8_t led;
	uint8_t state;
} ATTRIBUTE_PACKED SetSelectedLEDState_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetStateChangedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStateChangedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetStateChangedCallbackConfiguration_Response;

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

static void dual_button_v2_callback_wrapper_state_changed(DevicePrivate *device_p, Packet *packet) {
	StateChanged_CallbackFunction callback_function;
	void *user_data;
	StateChanged_Callback *callback;

	if (packet->header.length != sizeof(StateChanged_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StateChanged_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DUAL_BUTTON_V2_CALLBACK_STATE_CHANGED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DUAL_BUTTON_V2_CALLBACK_STATE_CHANGED];
	callback = (StateChanged_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->button_l, callback->button_r, callback->led_l, callback->led_r, user_data);
}

void dual_button_v2_create(DualButtonV2 *dual_button_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(dual_button_v2, uid, ipcon_p, 2, 0, 0, DUAL_BUTTON_V2_DEVICE_IDENTIFIER);

	device_p = dual_button_v2->p;

	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_LED_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_LED_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_BUTTON_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_SELECTED_LED_STATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_STATE_CHANGED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_STATE_CHANGED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DUAL_BUTTON_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DUAL_BUTTON_V2_CALLBACK_STATE_CHANGED] = dual_button_v2_callback_wrapper_state_changed;

	ipcon_add_device(ipcon_p, device_p);
}

void dual_button_v2_destroy(DualButtonV2 *dual_button_v2) {
	device_release(dual_button_v2->p);
}

int dual_button_v2_get_response_expected(DualButtonV2 *dual_button_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dual_button_v2->p, function_id, ret_response_expected);
}

int dual_button_v2_set_response_expected(DualButtonV2 *dual_button_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dual_button_v2->p, function_id, response_expected);
}

int dual_button_v2_set_response_expected_all(DualButtonV2 *dual_button_v2, bool response_expected) {
	return device_set_response_expected_all(dual_button_v2->p, response_expected);
}

void dual_button_v2_register_callback(DualButtonV2 *dual_button_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(dual_button_v2->p, callback_id, function, user_data);
}

int dual_button_v2_get_api_version(DualButtonV2 *dual_button_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(dual_button_v2->p, ret_api_version);
}

int dual_button_v2_set_led_state(DualButtonV2 *dual_button_v2, uint8_t led_l, uint8_t led_r) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetLEDState_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.led_l = led_l;
	request.led_r = led_r;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_get_led_state(DualButtonV2 *dual_button_v2, uint8_t *ret_led_l, uint8_t *ret_led_r) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetLEDState_Request request;
	GetLEDState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_led_l = response.led_l;
	*ret_led_r = response.led_r;

	return ret;
}

int dual_button_v2_get_button_state(DualButtonV2 *dual_button_v2, uint8_t *ret_button_l, uint8_t *ret_button_r) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetButtonState_Request request;
	GetButtonState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_BUTTON_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_button_l = response.button_l;
	*ret_button_r = response.button_r;

	return ret;
}

int dual_button_v2_set_selected_led_state(DualButtonV2 *dual_button_v2, uint8_t led, uint8_t state) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetSelectedLEDState_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_SELECTED_LED_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.led = led;
	request.state = state;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_set_state_changed_callback_configuration(DualButtonV2 *dual_button_v2, bool enabled) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetStateChangedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_STATE_CHANGED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_get_state_changed_callback_configuration(DualButtonV2 *dual_button_v2, bool *ret_enabled) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetStateChangedCallbackConfiguration_Request request;
	GetStateChangedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_STATE_CHANGED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int dual_button_v2_get_spitfp_error_count(DualButtonV2 *dual_button_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int dual_button_v2_set_bootloader_mode(DualButtonV2 *dual_button_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dual_button_v2_get_bootloader_mode(DualButtonV2 *dual_button_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dual_button_v2_set_write_firmware_pointer(DualButtonV2 *dual_button_v2, uint32_t pointer) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_write_firmware(DualButtonV2 *dual_button_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = dual_button_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int dual_button_v2_set_status_led_config(DualButtonV2 *dual_button_v2, uint8_t config) {
	DevicePrivate *device_p = dual_button_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_get_status_led_config(DualButtonV2 *dual_button_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dual_button_v2_get_chip_temperature(DualButtonV2 *dual_button_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int dual_button_v2_reset(DualButtonV2 *dual_button_v2) {
	DevicePrivate *device_p = dual_button_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_write_uid(DualButtonV2 *dual_button_v2, uint32_t uid) {
	DevicePrivate *device_p = dual_button_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dual_button_v2_read_uid(DualButtonV2 *dual_button_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = dual_button_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int dual_button_v2_get_identity(DualButtonV2 *dual_button_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dual_button_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DUAL_BUTTON_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
