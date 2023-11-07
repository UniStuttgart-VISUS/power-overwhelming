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

#include "bricklet_ambient_light_v3.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Illuminance_CallbackFunction)(uint32_t illuminance, void *user_data);

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
} ATTRIBUTE_PACKED GetIlluminance_Request;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED GetIlluminance_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED SetIlluminanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED GetIlluminanceCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t illuminance;
} ATTRIBUTE_PACKED Illuminance_Callback;

typedef struct {
	PacketHeader header;
	uint8_t illuminance_range;
	uint8_t integration_time;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t illuminance_range;
	uint8_t integration_time;
} ATTRIBUTE_PACKED GetConfiguration_Response;

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

static void ambient_light_v3_callback_wrapper_illuminance(DevicePrivate *device_p, Packet *packet) {
	Illuminance_CallbackFunction callback_function;
	void *user_data;
	Illuminance_Callback *callback;

	if (packet->header.length != sizeof(Illuminance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Illuminance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_V3_CALLBACK_ILLUMINANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_V3_CALLBACK_ILLUMINANCE];
	callback = (Illuminance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint32_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

void ambient_light_v3_create(AmbientLightV3 *ambient_light_v3, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(ambient_light_v3, uid, ipcon_p, 2, 0, 0, AMBIENT_LIGHT_V3_DEVICE_IDENTIFIER);

	device_p = ambient_light_v3->p;

	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_SET_ILLUMINANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_ILLUMINANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_V3_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[AMBIENT_LIGHT_V3_CALLBACK_ILLUMINANCE] = ambient_light_v3_callback_wrapper_illuminance;

	ipcon_add_device(ipcon_p, device_p);
}

void ambient_light_v3_destroy(AmbientLightV3 *ambient_light_v3) {
	device_release(ambient_light_v3->p);
}

int ambient_light_v3_get_response_expected(AmbientLightV3 *ambient_light_v3, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ambient_light_v3->p, function_id, ret_response_expected);
}

int ambient_light_v3_set_response_expected(AmbientLightV3 *ambient_light_v3, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ambient_light_v3->p, function_id, response_expected);
}

int ambient_light_v3_set_response_expected_all(AmbientLightV3 *ambient_light_v3, bool response_expected) {
	return device_set_response_expected_all(ambient_light_v3->p, response_expected);
}

void ambient_light_v3_register_callback(AmbientLightV3 *ambient_light_v3, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(ambient_light_v3->p, callback_id, function, user_data);
}

int ambient_light_v3_get_api_version(AmbientLightV3 *ambient_light_v3, uint8_t ret_api_version[3]) {
	return device_get_api_version(ambient_light_v3->p, ret_api_version);
}

int ambient_light_v3_get_illuminance(AmbientLightV3 *ambient_light_v3, uint32_t *ret_illuminance) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetIlluminance_Request request;
	GetIlluminance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_ILLUMINANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_illuminance = leconvert_uint32_from(response.illuminance);

	return ret;
}

int ambient_light_v3_set_illuminance_callback_configuration(AmbientLightV3 *ambient_light_v3, uint32_t period, bool value_has_to_change, char option, uint32_t min, uint32_t max) {
	DevicePrivate *device_p = ambient_light_v3->p;
	SetIlluminanceCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_SET_ILLUMINANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_uint32_to(min);
	request.max = leconvert_uint32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_get_illuminance_callback_configuration(AmbientLightV3 *ambient_light_v3, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint32_t *ret_min, uint32_t *ret_max) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetIlluminanceCallbackConfiguration_Request request;
	GetIlluminanceCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_ILLUMINANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;
	*ret_option = response.option;
	*ret_min = leconvert_uint32_from(response.min);
	*ret_max = leconvert_uint32_from(response.max);

	return ret;
}

int ambient_light_v3_set_configuration(AmbientLightV3 *ambient_light_v3, uint8_t illuminance_range, uint8_t integration_time) {
	DevicePrivate *device_p = ambient_light_v3->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.illuminance_range = illuminance_range;
	request.integration_time = integration_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_get_configuration(AmbientLightV3 *ambient_light_v3, uint8_t *ret_illuminance_range, uint8_t *ret_integration_time) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_illuminance_range = response.illuminance_range;
	*ret_integration_time = response.integration_time;

	return ret;
}

int ambient_light_v3_get_spitfp_error_count(AmbientLightV3 *ambient_light_v3, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int ambient_light_v3_set_bootloader_mode(AmbientLightV3 *ambient_light_v3, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = ambient_light_v3->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int ambient_light_v3_get_bootloader_mode(AmbientLightV3 *ambient_light_v3, uint8_t *ret_mode) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int ambient_light_v3_set_write_firmware_pointer(AmbientLightV3 *ambient_light_v3, uint32_t pointer) {
	DevicePrivate *device_p = ambient_light_v3->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_write_firmware(AmbientLightV3 *ambient_light_v3, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = ambient_light_v3->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int ambient_light_v3_set_status_led_config(AmbientLightV3 *ambient_light_v3, uint8_t config) {
	DevicePrivate *device_p = ambient_light_v3->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_get_status_led_config(AmbientLightV3 *ambient_light_v3, uint8_t *ret_config) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int ambient_light_v3_get_chip_temperature(AmbientLightV3 *ambient_light_v3, int16_t *ret_temperature) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int ambient_light_v3_reset(AmbientLightV3 *ambient_light_v3) {
	DevicePrivate *device_p = ambient_light_v3->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_write_uid(AmbientLightV3 *ambient_light_v3, uint32_t uid) {
	DevicePrivate *device_p = ambient_light_v3->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_v3_read_uid(AmbientLightV3 *ambient_light_v3, uint32_t *ret_uid) {
	DevicePrivate *device_p = ambient_light_v3->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int ambient_light_v3_get_identity(AmbientLightV3 *ambient_light_v3, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ambient_light_v3->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_V3_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
