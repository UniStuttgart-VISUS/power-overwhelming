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

#include "bricklet_uv_light.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*UVLight_CallbackFunction)(uint32_t uv_light, void *user_data);

typedef void (*UVLightReached_CallbackFunction)(uint32_t uv_light, void *user_data);

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
} ATTRIBUTE_PACKED GetUVLight_Request;

typedef struct {
	PacketHeader header;
	uint32_t uv_light;
} ATTRIBUTE_PACKED GetUVLight_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetUVLightCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVLightCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetUVLightCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED SetUVLightCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUVLightCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED GetUVLightCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED SetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED GetDebouncePeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t uv_light;
} ATTRIBUTE_PACKED UVLight_Callback;

typedef struct {
	PacketHeader header;
	uint32_t uv_light;
} ATTRIBUTE_PACKED UVLightReached_Callback;

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

static void uv_light_callback_wrapper_uv_light(DevicePrivate *device_p, Packet *packet) {
	UVLight_CallbackFunction callback_function;
	void *user_data;
	UVLight_Callback *callback;

	if (packet->header.length != sizeof(UVLight_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UVLight_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_CALLBACK_UV_LIGHT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_CALLBACK_UV_LIGHT];
	callback = (UVLight_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->uv_light = leconvert_uint32_from(callback->uv_light);

	callback_function(callback->uv_light, user_data);
}

static void uv_light_callback_wrapper_uv_light_reached(DevicePrivate *device_p, Packet *packet) {
	UVLightReached_CallbackFunction callback_function;
	void *user_data;
	UVLightReached_Callback *callback;

	if (packet->header.length != sizeof(UVLightReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UVLightReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_CALLBACK_UV_LIGHT_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + UV_LIGHT_CALLBACK_UV_LIGHT_REACHED];
	callback = (UVLightReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->uv_light = leconvert_uint32_from(callback->uv_light);

	callback_function(callback->uv_light, user_data);
}

void uv_light_create(UVLight *uv_light, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(uv_light, uid, ipcon_p, 2, 0, 0, UV_LIGHT_DEVICE_IDENTIFIER);

	device_p = uv_light->p;

	device_p->response_expected[UV_LIGHT_FUNCTION_GET_UV_LIGHT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[UV_LIGHT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[UV_LIGHT_CALLBACK_UV_LIGHT] = uv_light_callback_wrapper_uv_light;
	device_p->callback_wrappers[UV_LIGHT_CALLBACK_UV_LIGHT_REACHED] = uv_light_callback_wrapper_uv_light_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void uv_light_destroy(UVLight *uv_light) {
	device_release(uv_light->p);
}

int uv_light_get_response_expected(UVLight *uv_light, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(uv_light->p, function_id, ret_response_expected);
}

int uv_light_set_response_expected(UVLight *uv_light, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(uv_light->p, function_id, response_expected);
}

int uv_light_set_response_expected_all(UVLight *uv_light, bool response_expected) {
	return device_set_response_expected_all(uv_light->p, response_expected);
}

void uv_light_register_callback(UVLight *uv_light, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(uv_light->p, callback_id, function, user_data);
}

int uv_light_get_api_version(UVLight *uv_light, uint8_t ret_api_version[3]) {
	return device_get_api_version(uv_light->p, ret_api_version);
}

int uv_light_get_uv_light(UVLight *uv_light, uint32_t *ret_uv_light) {
	DevicePrivate *device_p = uv_light->p;
	GetUVLight_Request request;
	GetUVLight_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_GET_UV_LIGHT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uv_light = leconvert_uint32_from(response.uv_light);

	return ret;
}

int uv_light_set_uv_light_callback_period(UVLight *uv_light, uint32_t period) {
	DevicePrivate *device_p = uv_light->p;
	SetUVLightCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_get_uv_light_callback_period(UVLight *uv_light, uint32_t *ret_period) {
	DevicePrivate *device_p = uv_light->p;
	GetUVLightCallbackPeriod_Request request;
	GetUVLightCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int uv_light_set_uv_light_callback_threshold(UVLight *uv_light, char option, uint32_t min, uint32_t max) {
	DevicePrivate *device_p = uv_light->p;
	SetUVLightCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_SET_UV_LIGHT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint32_to(min);
	request.max = leconvert_uint32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_get_uv_light_callback_threshold(UVLight *uv_light, char *ret_option, uint32_t *ret_min, uint32_t *ret_max) {
	DevicePrivate *device_p = uv_light->p;
	GetUVLightCallbackThreshold_Request request;
	GetUVLightCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_GET_UV_LIGHT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint32_from(response.min);
	*ret_max = leconvert_uint32_from(response.max);

	return ret;
}

int uv_light_set_debounce_period(UVLight *uv_light, uint32_t debounce) {
	DevicePrivate *device_p = uv_light->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int uv_light_get_debounce_period(UVLight *uv_light, uint32_t *ret_debounce) {
	DevicePrivate *device_p = uv_light->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_debounce = leconvert_uint32_from(response.debounce);

	return ret;
}

int uv_light_get_identity(UVLight *uv_light, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = uv_light->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), UV_LIGHT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
