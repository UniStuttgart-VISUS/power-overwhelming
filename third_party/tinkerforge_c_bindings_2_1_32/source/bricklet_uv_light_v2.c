/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_uv_light_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*UVA_CallbackFunction)(int32_t uva, void *user_data);

typedef void (*UVB_CallbackFunction)(int32_t uvb, void *user_data);

typedef void (*UVI_CallbackFunction)(int32_t uvi, void *user_data);

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
} ATTRIBUTE_PACKED GetUVA_Request;

typedef struct {
	PacketHeader header;
	int32_t uva;
} ATTRIBUTE_PACKED GetUVA_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetUVACallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVACallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetUVACallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t uva;
} ATTRIBUTE_PACKED UVA_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVB_Request;

typedef struct {
	PacketHeader header;
	int32_t uvb;
} ATTRIBUTE_PACKED GetUVB_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetUVBCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVBCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetUVBCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t uvb;
} ATTRIBUTE_PACKED UVB_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVI_Request;

typedef struct {
	PacketHeader header;
	int32_t uvi;
} ATTRIBUTE_PACKED GetUVI_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetUVICallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVICallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetUVICallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t uvi;
} ATTRIBUTE_PACKED UVI_Callback;

typedef struct {
	PacketHeader header;
	uint8_t integration_time;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
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

static void uv_light_v2_callback_wrapper_uva(DevicePrivate *device_p, Packet *packet) {
	UVA_CallbackFunction callback_function;
	void *user_data;
	UVA_Callback *callback;

	if (packet->header.length != sizeof(UVA_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UVA_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVA];
	callback = (UVA_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->uva = leconvert_int32_from(callback->uva);

	callback_function(callback->uva, user_data);
}

static void uv_light_v2_callback_wrapper_uvb(DevicePrivate *device_p, Packet *packet) {
	UVB_CallbackFunction callback_function;
	void *user_data;
	UVB_Callback *callback;

	if (packet->header.length != sizeof(UVB_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UVB_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVB];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVB];
	callback = (UVB_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->uvb = leconvert_int32_from(callback->uvb);

	callback_function(callback->uvb, user_data);
}

static void uv_light_v2_callback_wrapper_uvi(DevicePrivate *device_p, Packet *packet) {
	UVI_CallbackFunction callback_function;
	void *user_data;
	UVI_Callback *callback;

	if (packet->header.length != sizeof(UVI_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UVI_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVI];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_V2_CALLBACK_UVI];
	callback = (UVI_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->uvi = leconvert_int32_from(callback->uvi);

	callback_function(callback->uvi, user_data);
}

void uv_light_v2_create(UVLightV2 *uv_light_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(uv_light_v2, uid, ipcon_p, 2, 0, 0, UV_LIGHT_V2_DEVICE_IDENTIFIER);

	device_p = uv_light_v2->p;

	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_UVA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVB] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_UVB_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVB_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVI] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_UVI_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_UVI_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[UV_LIGHT_V2_CALLBACK_UVA] = uv_light_v2_callback_wrapper_uva;
	device_p->callback_wrappers[UV_LIGHT_V2_CALLBACK_UVB] = uv_light_v2_callback_wrapper_uvb;
	device_p->callback_wrappers[UV_LIGHT_V2_CALLBACK_UVI] = uv_light_v2_callback_wrapper_uvi;

	ipcon_add_device(ipcon_p, device_p);
}

void uv_light_v2_destroy(UVLightV2 *uv_light_v2) {
	device_release(uv_light_v2->p);
}

int uv_light_v2_get_response_expected(UVLightV2 *uv_light_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(uv_light_v2->p, function_id, ret_response_expected);
}

int uv_light_v2_set_response_expected(UVLightV2 *uv_light_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(uv_light_v2->p, function_id, response_expected);
}

int uv_light_v2_set_response_expected_all(UVLightV2 *uv_light_v2, bool response_expected) {
	return device_set_response_expected_all(uv_light_v2->p, response_expected);
}

void uv_light_v2_register_callback(UVLightV2 *uv_light_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(uv_light_v2->p, callback_id, function, user_data);
}

int uv_light_v2_get_api_version(UVLightV2 *uv_light_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(uv_light_v2->p, ret_api_version);
}

int uv_light_v2_get_uva(UVLightV2 *uv_light_v2, int32_t *ret_uva) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVA_Request request;
	GetUVA_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uva = leconvert_int32_from(response.uva);

	return ret;
}

int uv_light_v2_set_uva_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetUVACallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_UVA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_get_uva_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVACallbackConfiguration_Request request;
	GetUVACallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int uv_light_v2_get_uvb(UVLightV2 *uv_light_v2, int32_t *ret_uvb) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVB_Request request;
	GetUVB_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVB, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uvb = leconvert_int32_from(response.uvb);

	return ret;
}

int uv_light_v2_set_uvb_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetUVBCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_UVB_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_get_uvb_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVBCallbackConfiguration_Request request;
	GetUVBCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVB_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int uv_light_v2_get_uvi(UVLightV2 *uv_light_v2, int32_t *ret_uvi) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVI_Request request;
	GetUVI_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVI, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uvi = leconvert_int32_from(response.uvi);

	return ret;
}

int uv_light_v2_set_uvi_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetUVICallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_UVI_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_get_uvi_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetUVICallbackConfiguration_Request request;
	GetUVICallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_UVI_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int uv_light_v2_set_configuration(UVLightV2 *uv_light_v2, uint8_t integration_time) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.integration_time = integration_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_get_configuration(UVLightV2 *uv_light_v2, uint8_t *ret_integration_time) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_integration_time = response.integration_time;

	return ret;
}

int uv_light_v2_get_spitfp_error_count(UVLightV2 *uv_light_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int uv_light_v2_set_bootloader_mode(UVLightV2 *uv_light_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int uv_light_v2_get_bootloader_mode(UVLightV2 *uv_light_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int uv_light_v2_set_write_firmware_pointer(UVLightV2 *uv_light_v2, uint32_t pointer) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_write_firmware(UVLightV2 *uv_light_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = uv_light_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int uv_light_v2_set_status_led_config(UVLightV2 *uv_light_v2, uint8_t config) {
	DevicePrivate *device_p = uv_light_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_get_status_led_config(UVLightV2 *uv_light_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int uv_light_v2_get_chip_temperature(UVLightV2 *uv_light_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int uv_light_v2_reset(UVLightV2 *uv_light_v2) {
	DevicePrivate *device_p = uv_light_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_write_uid(UVLightV2 *uv_light_v2, uint32_t uid) {
	DevicePrivate *device_p = uv_light_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_v2_read_uid(UVLightV2 *uv_light_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = uv_light_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int uv_light_v2_get_identity(UVLightV2 *uv_light_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = uv_light_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
