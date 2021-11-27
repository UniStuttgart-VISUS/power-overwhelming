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

#include "bricklet_ambient_light.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Illuminance_CallbackFunction)(uint16_t illuminance, void *user_data);

typedef void (*AnalogValue_CallbackFunction)(uint16_t value, void *user_data);

typedef void (*IlluminanceReached_CallbackFunction)(uint16_t illuminance, void *user_data);

typedef void (*AnalogValueReached_CallbackFunction)(uint16_t value, void *user_data);

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
	uint16_t illuminance;
} ATTRIBUTE_PACKED GetIlluminance_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValue_Request;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED GetAnalogValue_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetIlluminanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetIlluminanceCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAnalogValueCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetIlluminanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIlluminanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetIlluminanceCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetAnalogValueCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_Response;

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
	uint16_t illuminance;
} ATTRIBUTE_PACKED Illuminance_Callback;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValue_Callback;

typedef struct {
	PacketHeader header;
	uint16_t illuminance;
} ATTRIBUTE_PACKED IlluminanceReached_Callback;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueReached_Callback;

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

static void ambient_light_callback_wrapper_illuminance(DevicePrivate *device_p, Packet *packet) {
	Illuminance_CallbackFunction callback_function;
	void *user_data;
	Illuminance_Callback *callback;

	if (packet->header.length != sizeof(Illuminance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Illuminance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ILLUMINANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ILLUMINANCE];
	callback = (Illuminance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint16_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

static void ambient_light_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValue_CallbackFunction callback_function;
	void *user_data;
	AnalogValue_Callback *callback;

	if (packet->header.length != sizeof(AnalogValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE];
	callback = (AnalogValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void ambient_light_callback_wrapper_illuminance_reached(DevicePrivate *device_p, Packet *packet) {
	IlluminanceReached_CallbackFunction callback_function;
	void *user_data;
	IlluminanceReached_Callback *callback;

	if (packet->header.length != sizeof(IlluminanceReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (IlluminanceReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ILLUMINANCE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ILLUMINANCE_REACHED];
	callback = (IlluminanceReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->illuminance = leconvert_uint16_from(callback->illuminance);

	callback_function(callback->illuminance, user_data);
}

static void ambient_light_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReached_CallbackFunction callback_function;
	void *user_data;
	AnalogValueReached_Callback *callback;

	if (packet->header.length != sizeof(AnalogValueReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValueReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE_REACHED];
	callback = (AnalogValueReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

void ambient_light_create(AmbientLight *ambient_light, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(ambient_light, uid, ipcon_p, 2, 0, 1, AMBIENT_LIGHT_DEVICE_IDENTIFIER);

	device_p = ambient_light->p;

	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_SET_ILLUMINANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AMBIENT_LIGHT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[AMBIENT_LIGHT_CALLBACK_ILLUMINANCE] = ambient_light_callback_wrapper_illuminance;
	device_p->callback_wrappers[AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE] = ambient_light_callback_wrapper_analog_value;
	device_p->callback_wrappers[AMBIENT_LIGHT_CALLBACK_ILLUMINANCE_REACHED] = ambient_light_callback_wrapper_illuminance_reached;
	device_p->callback_wrappers[AMBIENT_LIGHT_CALLBACK_ANALOG_VALUE_REACHED] = ambient_light_callback_wrapper_analog_value_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void ambient_light_destroy(AmbientLight *ambient_light) {
	device_release(ambient_light->p);
}

int ambient_light_get_response_expected(AmbientLight *ambient_light, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ambient_light->p, function_id, ret_response_expected);
}

int ambient_light_set_response_expected(AmbientLight *ambient_light, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ambient_light->p, function_id, response_expected);
}

int ambient_light_set_response_expected_all(AmbientLight *ambient_light, bool response_expected) {
	return device_set_response_expected_all(ambient_light->p, response_expected);
}

void ambient_light_register_callback(AmbientLight *ambient_light, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(ambient_light->p, callback_id, function, user_data);
}

int ambient_light_get_api_version(AmbientLight *ambient_light, uint8_t ret_api_version[3]) {
	return device_get_api_version(ambient_light->p, ret_api_version);
}

int ambient_light_get_illuminance(AmbientLight *ambient_light, uint16_t *ret_illuminance) {
	DevicePrivate *device_p = ambient_light->p;
	GetIlluminance_Request request;
	GetIlluminance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_illuminance = leconvert_uint16_from(response.illuminance);

	return ret;
}

int ambient_light_get_analog_value(AmbientLight *ambient_light, uint16_t *ret_value) {
	DevicePrivate *device_p = ambient_light->p;
	GetAnalogValue_Request request;
	GetAnalogValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = leconvert_uint16_from(response.value);

	return ret;
}

int ambient_light_set_illuminance_callback_period(AmbientLight *ambient_light, uint32_t period) {
	DevicePrivate *device_p = ambient_light->p;
	SetIlluminanceCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_SET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_get_illuminance_callback_period(AmbientLight *ambient_light, uint32_t *ret_period) {
	DevicePrivate *device_p = ambient_light->p;
	GetIlluminanceCallbackPeriod_Request request;
	GetIlluminanceCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ambient_light_set_analog_value_callback_period(AmbientLight *ambient_light, uint32_t period) {
	DevicePrivate *device_p = ambient_light->p;
	SetAnalogValueCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_get_analog_value_callback_period(AmbientLight *ambient_light, uint32_t *ret_period) {
	DevicePrivate *device_p = ambient_light->p;
	GetAnalogValueCallbackPeriod_Request request;
	GetAnalogValueCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ambient_light_set_illuminance_callback_threshold(AmbientLight *ambient_light, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = ambient_light->p;
	SetIlluminanceCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_SET_ILLUMINANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_get_illuminance_callback_threshold(AmbientLight *ambient_light, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = ambient_light->p;
	GetIlluminanceCallbackThreshold_Request request;
	GetIlluminanceCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ILLUMINANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int ambient_light_set_analog_value_callback_threshold(AmbientLight *ambient_light, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = ambient_light->p;
	SetAnalogValueCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_get_analog_value_callback_threshold(AmbientLight *ambient_light, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = ambient_light->p;
	GetAnalogValueCallbackThreshold_Request request;
	GetAnalogValueCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int ambient_light_set_debounce_period(AmbientLight *ambient_light, uint32_t debounce) {
	DevicePrivate *device_p = ambient_light->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ambient_light_get_debounce_period(AmbientLight *ambient_light, uint32_t *ret_debounce) {
	DevicePrivate *device_p = ambient_light->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int ambient_light_get_identity(AmbientLight *ambient_light, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ambient_light->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AMBIENT_LIGHT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
