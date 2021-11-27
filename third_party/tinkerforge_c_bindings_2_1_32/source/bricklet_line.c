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

#include "bricklet_line.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Reflectivity_CallbackFunction)(uint16_t reflectivity, void *user_data);

typedef void (*ReflectivityReached_CallbackFunction)(uint16_t reflectivity, void *user_data);

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
} ATTRIBUTE_PACKED GetReflectivity_Request;

typedef struct {
	PacketHeader header;
	uint16_t reflectivity;
} ATTRIBUTE_PACKED GetReflectivity_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetReflectivityCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReflectivityCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetReflectivityCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetReflectivityCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReflectivityCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetReflectivityCallbackThreshold_Response;

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
	uint16_t reflectivity;
} ATTRIBUTE_PACKED Reflectivity_Callback;

typedef struct {
	PacketHeader header;
	uint16_t reflectivity;
} ATTRIBUTE_PACKED ReflectivityReached_Callback;

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

static void line_callback_wrapper_reflectivity(DevicePrivate *device_p, Packet *packet) {
	Reflectivity_CallbackFunction callback_function;
	void *user_data;
	Reflectivity_Callback *callback;

	if (packet->header.length != sizeof(Reflectivity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Reflectivity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LINE_CALLBACK_REFLECTIVITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LINE_CALLBACK_REFLECTIVITY];
	callback = (Reflectivity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->reflectivity = leconvert_uint16_from(callback->reflectivity);

	callback_function(callback->reflectivity, user_data);
}

static void line_callback_wrapper_reflectivity_reached(DevicePrivate *device_p, Packet *packet) {
	ReflectivityReached_CallbackFunction callback_function;
	void *user_data;
	ReflectivityReached_Callback *callback;

	if (packet->header.length != sizeof(ReflectivityReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ReflectivityReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LINE_CALLBACK_REFLECTIVITY_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LINE_CALLBACK_REFLECTIVITY_REACHED];
	callback = (ReflectivityReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->reflectivity = leconvert_uint16_from(callback->reflectivity);

	callback_function(callback->reflectivity, user_data);
}

void line_create(Line *line, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(line, uid, ipcon_p, 2, 0, 0, LINE_DEVICE_IDENTIFIER);

	device_p = line->p;

	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LINE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LINE_CALLBACK_REFLECTIVITY] = line_callback_wrapper_reflectivity;
	device_p->callback_wrappers[LINE_CALLBACK_REFLECTIVITY_REACHED] = line_callback_wrapper_reflectivity_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void line_destroy(Line *line) {
	device_release(line->p);
}

int line_get_response_expected(Line *line, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(line->p, function_id, ret_response_expected);
}

int line_set_response_expected(Line *line, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(line->p, function_id, response_expected);
}

int line_set_response_expected_all(Line *line, bool response_expected) {
	return device_set_response_expected_all(line->p, response_expected);
}

void line_register_callback(Line *line, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(line->p, callback_id, function, user_data);
}

int line_get_api_version(Line *line, uint8_t ret_api_version[3]) {
	return device_get_api_version(line->p, ret_api_version);
}

int line_get_reflectivity(Line *line, uint16_t *ret_reflectivity) {
	DevicePrivate *device_p = line->p;
	GetReflectivity_Request request;
	GetReflectivity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_reflectivity = leconvert_uint16_from(response.reflectivity);

	return ret;
}

int line_set_reflectivity_callback_period(Line *line, uint32_t period) {
	DevicePrivate *device_p = line->p;
	SetReflectivityCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int line_get_reflectivity_callback_period(Line *line, uint32_t *ret_period) {
	DevicePrivate *device_p = line->p;
	GetReflectivityCallbackPeriod_Request request;
	GetReflectivityCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int line_set_reflectivity_callback_threshold(Line *line, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = line->p;
	SetReflectivityCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_REFLECTIVITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int line_get_reflectivity_callback_threshold(Line *line, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = line->p;
	GetReflectivityCallbackThreshold_Request request;
	GetReflectivityCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_REFLECTIVITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int line_set_debounce_period(Line *line, uint32_t debounce) {
	DevicePrivate *device_p = line->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int line_get_debounce_period(Line *line, uint32_t *ret_debounce) {
	DevicePrivate *device_p = line->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int line_get_identity(Line *line, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = line->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LINE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
