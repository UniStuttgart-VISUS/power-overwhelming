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

#include "bricklet_load_cell.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Weight_CallbackFunction)(int32_t weight, void *user_data);

typedef void (*WeightReached_CallbackFunction)(int32_t weight, void *user_data);

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
} ATTRIBUTE_PACKED GetWeight_Request;

typedef struct {
	PacketHeader header;
	int32_t weight;
} ATTRIBUTE_PACKED GetWeight_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetWeightCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWeightCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetWeightCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetWeightCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWeightCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetWeightCallbackThreshold_Response;

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
} ATTRIBUTE_PACKED LEDOn_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LEDOff_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsLEDOn_Request;

typedef struct {
	PacketHeader header;
	uint8_t on;
} ATTRIBUTE_PACKED IsLEDOn_Response;

typedef struct {
	PacketHeader header;
	uint32_t weight;
} ATTRIBUTE_PACKED Calibrate_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Tare_Request;

typedef struct {
	PacketHeader header;
	uint8_t rate;
	uint8_t gain;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t rate;
	uint8_t gain;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t weight;
} ATTRIBUTE_PACKED Weight_Callback;

typedef struct {
	PacketHeader header;
	int32_t weight;
} ATTRIBUTE_PACKED WeightReached_Callback;

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

static void load_cell_callback_wrapper_weight(DevicePrivate *device_p, Packet *packet) {
	Weight_CallbackFunction callback_function;
	void *user_data;
	Weight_Callback *callback;

	if (packet->header.length != sizeof(Weight_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Weight_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LOAD_CELL_CALLBACK_WEIGHT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LOAD_CELL_CALLBACK_WEIGHT];
	callback = (Weight_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->weight = leconvert_int32_from(callback->weight);

	callback_function(callback->weight, user_data);
}

static void load_cell_callback_wrapper_weight_reached(DevicePrivate *device_p, Packet *packet) {
	WeightReached_CallbackFunction callback_function;
	void *user_data;
	WeightReached_Callback *callback;

	if (packet->header.length != sizeof(WeightReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (WeightReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LOAD_CELL_CALLBACK_WEIGHT_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LOAD_CELL_CALLBACK_WEIGHT_REACHED];
	callback = (WeightReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->weight = leconvert_int32_from(callback->weight);

	callback_function(callback->weight, user_data);
}

void load_cell_create(LoadCell *load_cell, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(load_cell, uid, ipcon_p, 2, 0, 0, LOAD_CELL_DEVICE_IDENTIFIER);

	device_p = load_cell->p;

	device_p->response_expected[LOAD_CELL_FUNCTION_GET_WEIGHT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_LED_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_LED_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_IS_LED_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_TARE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LOAD_CELL_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LOAD_CELL_CALLBACK_WEIGHT] = load_cell_callback_wrapper_weight;
	device_p->callback_wrappers[LOAD_CELL_CALLBACK_WEIGHT_REACHED] = load_cell_callback_wrapper_weight_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void load_cell_destroy(LoadCell *load_cell) {
	device_release(load_cell->p);
}

int load_cell_get_response_expected(LoadCell *load_cell, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(load_cell->p, function_id, ret_response_expected);
}

int load_cell_set_response_expected(LoadCell *load_cell, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(load_cell->p, function_id, response_expected);
}

int load_cell_set_response_expected_all(LoadCell *load_cell, bool response_expected) {
	return device_set_response_expected_all(load_cell->p, response_expected);
}

void load_cell_register_callback(LoadCell *load_cell, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(load_cell->p, callback_id, function, user_data);
}

int load_cell_get_api_version(LoadCell *load_cell, uint8_t ret_api_version[3]) {
	return device_get_api_version(load_cell->p, ret_api_version);
}

int load_cell_get_weight(LoadCell *load_cell, int32_t *ret_weight) {
	DevicePrivate *device_p = load_cell->p;
	GetWeight_Request request;
	GetWeight_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_WEIGHT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_weight = leconvert_int32_from(response.weight);

	return ret;
}

int load_cell_set_weight_callback_period(LoadCell *load_cell, uint32_t period) {
	DevicePrivate *device_p = load_cell->p;
	SetWeightCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_get_weight_callback_period(LoadCell *load_cell, uint32_t *ret_period) {
	DevicePrivate *device_p = load_cell->p;
	GetWeightCallbackPeriod_Request request;
	GetWeightCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int load_cell_set_weight_callback_threshold(LoadCell *load_cell, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = load_cell->p;
	SetWeightCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_SET_WEIGHT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_get_weight_callback_threshold(LoadCell *load_cell, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = load_cell->p;
	GetWeightCallbackThreshold_Request request;
	GetWeightCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_WEIGHT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int load_cell_set_debounce_period(LoadCell *load_cell, uint32_t debounce) {
	DevicePrivate *device_p = load_cell->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_get_debounce_period(LoadCell *load_cell, uint32_t *ret_debounce) {
	DevicePrivate *device_p = load_cell->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int load_cell_set_moving_average(LoadCell *load_cell, uint8_t average) {
	DevicePrivate *device_p = load_cell->p;
	SetMovingAverage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.average = average;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_get_moving_average(LoadCell *load_cell, uint8_t *ret_average) {
	DevicePrivate *device_p = load_cell->p;
	GetMovingAverage_Request request;
	GetMovingAverage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

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

int load_cell_led_on(LoadCell *load_cell) {
	DevicePrivate *device_p = load_cell->p;
	LEDOn_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_LED_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_led_off(LoadCell *load_cell) {
	DevicePrivate *device_p = load_cell->p;
	LEDOff_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_LED_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_is_led_on(LoadCell *load_cell, bool *ret_on) {
	DevicePrivate *device_p = load_cell->p;
	IsLEDOn_Request request;
	IsLEDOn_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_IS_LED_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_on = response.on != 0;

	return ret;
}

int load_cell_calibrate(LoadCell *load_cell, uint32_t weight) {
	DevicePrivate *device_p = load_cell->p;
	Calibrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.weight = leconvert_uint32_to(weight);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_tare(LoadCell *load_cell) {
	DevicePrivate *device_p = load_cell->p;
	Tare_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_TARE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_set_configuration(LoadCell *load_cell, uint8_t rate, uint8_t gain) {
	DevicePrivate *device_p = load_cell->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.rate = rate;
	request.gain = gain;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int load_cell_get_configuration(LoadCell *load_cell, uint8_t *ret_rate, uint8_t *ret_gain) {
	DevicePrivate *device_p = load_cell->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_rate = response.rate;
	*ret_gain = response.gain;

	return ret;
}

int load_cell_get_identity(LoadCell *load_cell, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = load_cell->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LOAD_CELL_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
