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

#include "bricklet_hall_effect.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*EdgeCount_CallbackFunction)(uint32_t count, bool value, void *user_data);

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
} ATTRIBUTE_PACKED GetValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t value;
} ATTRIBUTE_PACKED GetValue_Response;

typedef struct {
	PacketHeader header;
	uint8_t reset_counter;
} ATTRIBUTE_PACKED GetEdgeCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetEdgeCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED SetEdgeCountConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeCountConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED GetEdgeCountConfig_Response;

typedef struct {
	PacketHeader header;
	uint32_t edges;
} ATTRIBUTE_PACKED SetEdgeInterrupt_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeInterrupt_Request;

typedef struct {
	PacketHeader header;
	uint32_t edges;
} ATTRIBUTE_PACKED GetEdgeInterrupt_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetEdgeCountCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEdgeCountCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetEdgeCountCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EdgeInterrupt_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
	uint8_t value;
} ATTRIBUTE_PACKED EdgeInterrupt_Response;

typedef struct {
	PacketHeader header;
	uint32_t count;
	uint8_t value;
} ATTRIBUTE_PACKED EdgeCount_Callback;

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

static void hall_effect_callback_wrapper_edge_count(DevicePrivate *device_p, Packet *packet) {
	EdgeCount_CallbackFunction callback_function;
	void *user_data;
	EdgeCount_Callback *callback;
	bool unpacked_value;

	if (packet->header.length != sizeof(EdgeCount_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (EdgeCount_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_CALLBACK_EDGE_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_CALLBACK_EDGE_COUNT];
	callback = (EdgeCount_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_uint32_from(callback->count);
	unpacked_value = callback->value != 0;

	callback_function(callback->count, unpacked_value, user_data);
}

void hall_effect_create(HallEffect *hall_effect, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(hall_effect, uid, ipcon_p, 2, 0, 0, HALL_EFFECT_DEVICE_IDENTIFIER);

	device_p = hall_effect->p;

	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_EDGE_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[HALL_EFFECT_CALLBACK_EDGE_COUNT] = hall_effect_callback_wrapper_edge_count;

	ipcon_add_device(ipcon_p, device_p);
}

void hall_effect_destroy(HallEffect *hall_effect) {
	device_release(hall_effect->p);
}

int hall_effect_get_response_expected(HallEffect *hall_effect, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(hall_effect->p, function_id, ret_response_expected);
}

int hall_effect_set_response_expected(HallEffect *hall_effect, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(hall_effect->p, function_id, response_expected);
}

int hall_effect_set_response_expected_all(HallEffect *hall_effect, bool response_expected) {
	return device_set_response_expected_all(hall_effect->p, response_expected);
}

void hall_effect_register_callback(HallEffect *hall_effect, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(hall_effect->p, callback_id, function, user_data);
}

int hall_effect_get_api_version(HallEffect *hall_effect, uint8_t ret_api_version[3]) {
	return device_get_api_version(hall_effect->p, ret_api_version);
}

int hall_effect_get_value(HallEffect *hall_effect, bool *ret_value) {
	DevicePrivate *device_p = hall_effect->p;
	GetValue_Request request;
	GetValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = response.value != 0;

	return ret;
}

int hall_effect_get_edge_count(HallEffect *hall_effect, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCount_Request request;
	GetEdgeCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.reset_counter = reset_counter ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);

	return ret;
}

int hall_effect_set_edge_count_config(HallEffect *hall_effect, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeCountConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_get_edge_count_config(HallEffect *hall_effect, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCountConfig_Request request;
	GetEdgeCountConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_edge_type = response.edge_type;
	*ret_debounce = response.debounce;

	return ret;
}

int hall_effect_set_edge_interrupt(HallEffect *hall_effect, uint32_t edges) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeInterrupt_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.edges = leconvert_uint32_to(edges);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_get_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_edges) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeInterrupt_Request request;
	GetEdgeInterrupt_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_edges = leconvert_uint32_from(response.edges);

	return ret;
}

int hall_effect_set_edge_count_callback_period(HallEffect *hall_effect, uint32_t period) {
	DevicePrivate *device_p = hall_effect->p;
	SetEdgeCountCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_SET_EDGE_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_get_edge_count_callback_period(HallEffect *hall_effect, uint32_t *ret_period) {
	DevicePrivate *device_p = hall_effect->p;
	GetEdgeCountCallbackPeriod_Request request;
	GetEdgeCountCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_EDGE_COUNT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int hall_effect_edge_interrupt(HallEffect *hall_effect, uint32_t *ret_count, bool *ret_value) {
	DevicePrivate *device_p = hall_effect->p;
	EdgeInterrupt_Request request;
	EdgeInterrupt_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_EDGE_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);
	*ret_value = response.value != 0;

	return ret;
}

int hall_effect_get_identity(HallEffect *hall_effect, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = hall_effect->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
