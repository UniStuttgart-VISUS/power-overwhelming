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

#include "bricklet_analog_in_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Voltage_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*AnalogValue_CallbackFunction)(uint16_t value, void *user_data);

typedef void (*VoltageReached_CallbackFunction)(uint16_t voltage, void *user_data);

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
} ATTRIBUTE_PACKED GetVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetVoltage_Response;

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
} ATTRIBUTE_PACKED SetVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVoltageCallbackPeriod_Response;

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
} ATTRIBUTE_PACKED SetVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetVoltageCallbackThreshold_Response;

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
	uint8_t average;
} ATTRIBUTE_PACKED SetMovingAverage_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverage_Request;

typedef struct {
	PacketHeader header;
	uint8_t average;
} ATTRIBUTE_PACKED GetMovingAverage_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED Voltage_Callback;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED AnalogValue_Callback;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED VoltageReached_Callback;

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

static void analog_in_v2_callback_wrapper_voltage(DevicePrivate *device_p, Packet *packet) {
	Voltage_CallbackFunction callback_function;
	void *user_data;
	Voltage_Callback *callback;

	if (packet->header.length != sizeof(Voltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Voltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_VOLTAGE];
	callback = (Voltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void analog_in_v2_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValue_CallbackFunction callback_function;
	void *user_data;
	AnalogValue_Callback *callback;

	if (packet->header.length != sizeof(AnalogValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_ANALOG_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_ANALOG_VALUE];
	callback = (AnalogValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

static void analog_in_v2_callback_wrapper_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	VoltageReached_CallbackFunction callback_function;
	void *user_data;
	VoltageReached_Callback *callback;

	if (packet->header.length != sizeof(VoltageReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (VoltageReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED];
	callback = (VoltageReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void analog_in_v2_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReached_CallbackFunction callback_function;
	void *user_data;
	AnalogValueReached_Callback *callback;

	if (packet->header.length != sizeof(AnalogValueReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValueReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED];
	callback = (AnalogValueReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->value = leconvert_uint16_from(callback->value);

	callback_function(callback->value, user_data);
}

void analog_in_v2_create(AnalogInV2 *analog_in_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(analog_in_v2, uid, ipcon_p, 2, 0, 1, ANALOG_IN_V2_DEVICE_IDENTIFIER);

	device_p = analog_in_v2->p;

	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ANALOG_IN_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ANALOG_IN_V2_CALLBACK_VOLTAGE] = analog_in_v2_callback_wrapper_voltage;
	device_p->callback_wrappers[ANALOG_IN_V2_CALLBACK_ANALOG_VALUE] = analog_in_v2_callback_wrapper_analog_value;
	device_p->callback_wrappers[ANALOG_IN_V2_CALLBACK_VOLTAGE_REACHED] = analog_in_v2_callback_wrapper_voltage_reached;
	device_p->callback_wrappers[ANALOG_IN_V2_CALLBACK_ANALOG_VALUE_REACHED] = analog_in_v2_callback_wrapper_analog_value_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void analog_in_v2_destroy(AnalogInV2 *analog_in_v2) {
	device_release(analog_in_v2->p);
}

int analog_in_v2_get_response_expected(AnalogInV2 *analog_in_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(analog_in_v2->p, function_id, ret_response_expected);
}

int analog_in_v2_set_response_expected(AnalogInV2 *analog_in_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(analog_in_v2->p, function_id, response_expected);
}

int analog_in_v2_set_response_expected_all(AnalogInV2 *analog_in_v2, bool response_expected) {
	return device_set_response_expected_all(analog_in_v2->p, response_expected);
}

void analog_in_v2_register_callback(AnalogInV2 *analog_in_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(analog_in_v2->p, callback_id, function, user_data);
}

int analog_in_v2_get_api_version(AnalogInV2 *analog_in_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(analog_in_v2->p, ret_api_version);
}

int analog_in_v2_get_voltage(AnalogInV2 *analog_in_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetVoltage_Request request;
	GetVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

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

int analog_in_v2_get_analog_value(AnalogInV2 *analog_in_v2, uint16_t *ret_value) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetAnalogValue_Request request;
	GetAnalogValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_voltage_callback_period(AnalogInV2 *analog_in_v2, uint32_t period) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetVoltageCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_voltage_callback_period(AnalogInV2 *analog_in_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetVoltageCallbackPeriod_Request request;
	GetVoltageCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_analog_value_callback_period(AnalogInV2 *analog_in_v2, uint32_t period) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetAnalogValueCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_analog_value_callback_period(AnalogInV2 *analog_in_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetAnalogValueCallbackPeriod_Request request;
	GetAnalogValueCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_voltage_callback_threshold(AnalogInV2 *analog_in_v2, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetVoltageCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_voltage_callback_threshold(AnalogInV2 *analog_in_v2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetVoltageCallbackThreshold_Request request;
	GetVoltageCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_analog_value_callback_threshold(AnalogInV2 *analog_in_v2, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetAnalogValueCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_analog_value_callback_threshold(AnalogInV2 *analog_in_v2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetAnalogValueCallbackThreshold_Request request;
	GetAnalogValueCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_debounce_period(AnalogInV2 *analog_in_v2, uint32_t debounce) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_debounce_period(AnalogInV2 *analog_in_v2, uint32_t *ret_debounce) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int analog_in_v2_set_moving_average(AnalogInV2 *analog_in_v2, uint8_t average) {
	DevicePrivate *device_p = analog_in_v2->p;
	SetMovingAverage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int analog_in_v2_get_moving_average(AnalogInV2 *analog_in_v2, uint8_t *ret_average) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetMovingAverage_Request request;
	GetMovingAverage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_average = response.average;

	return ret;
}

int analog_in_v2_get_identity(AnalogInV2 *analog_in_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = analog_in_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ANALOG_IN_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
