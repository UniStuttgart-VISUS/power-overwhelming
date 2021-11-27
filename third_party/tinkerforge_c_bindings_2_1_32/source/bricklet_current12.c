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

#include "bricklet_current12.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Current_CallbackFunction)(int16_t current, void *user_data);

typedef void (*AnalogValue_CallbackFunction)(uint16_t value, void *user_data);

typedef void (*CurrentReached_CallbackFunction)(int16_t current, void *user_data);

typedef void (*AnalogValueReached_CallbackFunction)(uint16_t value, void *user_data);

typedef void (*OverCurrent_CallbackFunction)(void *user_data);

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
} ATTRIBUTE_PACKED GetCurrent_Request;

typedef struct {
	PacketHeader header;
	int16_t current;
} ATTRIBUTE_PACKED GetCurrent_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Calibrate_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsOverCurrent_Request;

typedef struct {
	PacketHeader header;
	uint8_t over;
} ATTRIBUTE_PACKED IsOverCurrent_Response;

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
} ATTRIBUTE_PACKED SetCurrentCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCurrentCallbackPeriod_Response;

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
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetCurrentCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetCurrentCallbackThreshold_Response;

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
	int16_t current;
} ATTRIBUTE_PACKED Current_Callback;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValue_Callback;

typedef struct {
	PacketHeader header;
	int16_t current;
} ATTRIBUTE_PACKED CurrentReached_Callback;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValueReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED OverCurrent_Callback;

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

static void current12_callback_wrapper_current(DevicePrivate *device_p, Packet *packet) {
	Current_CallbackFunction callback_function;
	void *user_data;
	Current_Callback *callback;

	if (packet->header.length != sizeof(Current_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Current_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_CURRENT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_CURRENT];
	callback = (Current_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void current12_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValue_CallbackFunction callback_function;
	void *user_data;
	AnalogValue_Callback *callback;

	if (packet->header.length != sizeof(AnalogValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_ANALOG_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_ANALOG_VALUE];
	callback = (AnalogValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void current12_callback_wrapper_current_reached(DevicePrivate *device_p, Packet *packet) {
	CurrentReached_CallbackFunction callback_function;
	void *user_data;
	CurrentReached_Callback *callback;

	if (packet->header.length != sizeof(CurrentReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CurrentReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_CURRENT_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_CURRENT_REACHED];
	callback = (CurrentReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void current12_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReached_CallbackFunction callback_function;
	void *user_data;
	AnalogValueReached_Callback *callback;

	if (packet->header.length != sizeof(AnalogValueReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValueReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_ANALOG_VALUE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_ANALOG_VALUE_REACHED];
	callback = (AnalogValueReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void current12_callback_wrapper_over_current(DevicePrivate *device_p, Packet *packet) {
	OverCurrent_CallbackFunction callback_function;
	void *user_data;
	OverCurrent_Callback *callback;

	if (packet->header.length != sizeof(OverCurrent_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (OverCurrent_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_OVER_CURRENT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CURRENT12_CALLBACK_OVER_CURRENT];
	callback = (OverCurrent_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void current12_create(Current12 *current12, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(current12, uid, ipcon_p, 2, 0, 0, CURRENT12_DEVICE_IDENTIFIER);

	device_p = current12->p;

	device_p->response_expected[CURRENT12_FUNCTION_GET_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CURRENT12_FUNCTION_IS_OVER_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CURRENT12_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CURRENT12_CALLBACK_CURRENT] = current12_callback_wrapper_current;
	device_p->callback_wrappers[CURRENT12_CALLBACK_ANALOG_VALUE] = current12_callback_wrapper_analog_value;
	device_p->callback_wrappers[CURRENT12_CALLBACK_CURRENT_REACHED] = current12_callback_wrapper_current_reached;
	device_p->callback_wrappers[CURRENT12_CALLBACK_ANALOG_VALUE_REACHED] = current12_callback_wrapper_analog_value_reached;
	device_p->callback_wrappers[CURRENT12_CALLBACK_OVER_CURRENT] = current12_callback_wrapper_over_current;

	ipcon_add_device(ipcon_p, device_p);
}

void current12_destroy(Current12 *current12) {
	device_release(current12->p);
}

int current12_get_response_expected(Current12 *current12, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(current12->p, function_id, ret_response_expected);
}

int current12_set_response_expected(Current12 *current12, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(current12->p, function_id, response_expected);
}

int current12_set_response_expected_all(Current12 *current12, bool response_expected) {
	return device_set_response_expected_all(current12->p, response_expected);
}

void current12_register_callback(Current12 *current12, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(current12->p, callback_id, function, user_data);
}

int current12_get_api_version(Current12 *current12, uint8_t ret_api_version[3]) {
	return device_get_api_version(current12->p, ret_api_version);
}

int current12_get_current(Current12 *current12, int16_t *ret_current) {
	DevicePrivate *device_p = current12->p;
	GetCurrent_Request request;
	GetCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_int16_from(response.current);

	return ret;
}

int current12_calibrate(Current12 *current12) {
	DevicePrivate *device_p = current12->p;
	Calibrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_is_over_current(Current12 *current12, bool *ret_over) {
	DevicePrivate *device_p = current12->p;
	IsOverCurrent_Request request;
	IsOverCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_IS_OVER_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_over = response.over != 0;

	return ret;
}

int current12_get_analog_value(Current12 *current12, uint16_t *ret_value) {
	DevicePrivate *device_p = current12->p;
	GetAnalogValue_Request request;
	GetAnalogValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

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

int current12_set_current_callback_period(Current12 *current12, uint32_t period) {
	DevicePrivate *device_p = current12->p;
	SetCurrentCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_get_current_callback_period(Current12 *current12, uint32_t *ret_period) {
	DevicePrivate *device_p = current12->p;
	GetCurrentCallbackPeriod_Request request;
	GetCurrentCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int current12_set_analog_value_callback_period(Current12 *current12, uint32_t period) {
	DevicePrivate *device_p = current12->p;
	SetAnalogValueCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_get_analog_value_callback_period(Current12 *current12, uint32_t *ret_period) {
	DevicePrivate *device_p = current12->p;
	GetAnalogValueCallbackPeriod_Request request;
	GetAnalogValueCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int current12_set_current_callback_threshold(Current12 *current12, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = current12->p;
	SetCurrentCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_SET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_get_current_callback_threshold(Current12 *current12, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = current12->p;
	GetCurrentCallbackThreshold_Request request;
	GetCurrentCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);

	return ret;
}

int current12_set_analog_value_callback_threshold(Current12 *current12, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = current12->p;
	SetAnalogValueCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_get_analog_value_callback_threshold(Current12 *current12, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = current12->p;
	GetAnalogValueCallbackThreshold_Request request;
	GetAnalogValueCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int current12_set_debounce_period(Current12 *current12, uint32_t debounce) {
	DevicePrivate *device_p = current12->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int current12_get_debounce_period(Current12 *current12, uint32_t *ret_debounce) {
	DevicePrivate *device_p = current12->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int current12_get_identity(Current12 *current12, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = current12->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CURRENT12_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
