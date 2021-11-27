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

#include "bricklet_ptc.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Temperature_CallbackFunction)(int32_t temperature, void *user_data);

typedef void (*TemperatureReached_CallbackFunction)(int32_t temperature, void *user_data);

typedef void (*Resistance_CallbackFunction)(int32_t resistance, void *user_data);

typedef void (*ResistanceReached_CallbackFunction)(int32_t resistance, void *user_data);

typedef void (*SensorConnected_CallbackFunction)(bool connected, void *user_data);

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
} ATTRIBUTE_PACKED GetTemperature_Request;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED GetTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistance_Request;

typedef struct {
	PacketHeader header;
	int32_t resistance;
} ATTRIBUTE_PACKED GetResistance_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetTemperatureCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetTemperatureCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetResistanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetResistanceCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetTemperatureCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetResistanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetResistanceCallbackThreshold_Response;

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
	int32_t temperature;
} ATTRIBUTE_PACKED Temperature_Callback;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED TemperatureReached_Callback;

typedef struct {
	PacketHeader header;
	int32_t resistance;
} ATTRIBUTE_PACKED Resistance_Callback;

typedef struct {
	PacketHeader header;
	int32_t resistance;
} ATTRIBUTE_PACKED ResistanceReached_Callback;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED SetNoiseRejectionFilter_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetNoiseRejectionFilter_Request;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED GetNoiseRejectionFilter_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsSensorConnected_Request;

typedef struct {
	PacketHeader header;
	uint8_t connected;
} ATTRIBUTE_PACKED IsSensorConnected_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetWireMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWireMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetWireMode_Response;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetSensorConnectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorConnectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetSensorConnectedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t connected;
} ATTRIBUTE_PACKED SensorConnected_Callback;

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

static void ptc_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	Temperature_CallbackFunction callback_function;
	void *user_data;
	Temperature_Callback *callback;

	if (packet->header.length != sizeof(Temperature_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Temperature_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_TEMPERATURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_TEMPERATURE];
	callback = (Temperature_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void ptc_callback_wrapper_temperature_reached(DevicePrivate *device_p, Packet *packet) {
	TemperatureReached_CallbackFunction callback_function;
	void *user_data;
	TemperatureReached_Callback *callback;

	if (packet->header.length != sizeof(TemperatureReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (TemperatureReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_TEMPERATURE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_TEMPERATURE_REACHED];
	callback = (TemperatureReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void ptc_callback_wrapper_resistance(DevicePrivate *device_p, Packet *packet) {
	Resistance_CallbackFunction callback_function;
	void *user_data;
	Resistance_Callback *callback;

	if (packet->header.length != sizeof(Resistance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Resistance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_RESISTANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_RESISTANCE];
	callback = (Resistance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->resistance = leconvert_int32_from(callback->resistance);

	callback_function(callback->resistance, user_data);
}

static void ptc_callback_wrapper_resistance_reached(DevicePrivate *device_p, Packet *packet) {
	ResistanceReached_CallbackFunction callback_function;
	void *user_data;
	ResistanceReached_Callback *callback;

	if (packet->header.length != sizeof(ResistanceReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ResistanceReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_RESISTANCE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_RESISTANCE_REACHED];
	callback = (ResistanceReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->resistance = leconvert_int32_from(callback->resistance);

	callback_function(callback->resistance, user_data);
}

static void ptc_callback_wrapper_sensor_connected(DevicePrivate *device_p, Packet *packet) {
	SensorConnected_CallbackFunction callback_function;
	void *user_data;
	SensorConnected_Callback *callback;
	bool unpacked_connected;

	if (packet->header.length != sizeof(SensorConnected_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SensorConnected_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_SENSOR_CONNECTED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_CALLBACK_SENSOR_CONNECTED];
	callback = (SensorConnected_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_connected = callback->connected != 0;

	callback_function(unpacked_connected, user_data);
}

void ptc_create(PTC *ptc, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(ptc, uid, ipcon_p, 2, 0, 1, PTC_DEVICE_IDENTIFIER);

	device_p = ptc->p;

	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_RESISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_RESISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_RESISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_FUNCTION_GET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_IS_SENSOR_CONNECTED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_FUNCTION_GET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_SET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PTC_CALLBACK_TEMPERATURE] = ptc_callback_wrapper_temperature;
	device_p->callback_wrappers[PTC_CALLBACK_TEMPERATURE_REACHED] = ptc_callback_wrapper_temperature_reached;
	device_p->callback_wrappers[PTC_CALLBACK_RESISTANCE] = ptc_callback_wrapper_resistance;
	device_p->callback_wrappers[PTC_CALLBACK_RESISTANCE_REACHED] = ptc_callback_wrapper_resistance_reached;
	device_p->callback_wrappers[PTC_CALLBACK_SENSOR_CONNECTED] = ptc_callback_wrapper_sensor_connected;

	ipcon_add_device(ipcon_p, device_p);
}

void ptc_destroy(PTC *ptc) {
	device_release(ptc->p);
}

int ptc_get_response_expected(PTC *ptc, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ptc->p, function_id, ret_response_expected);
}

int ptc_set_response_expected(PTC *ptc, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ptc->p, function_id, response_expected);
}

int ptc_set_response_expected_all(PTC *ptc, bool response_expected) {
	return device_set_response_expected_all(ptc->p, response_expected);
}

void ptc_register_callback(PTC *ptc, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(ptc->p, callback_id, function, user_data);
}

int ptc_get_api_version(PTC *ptc, uint8_t ret_api_version[3]) {
	return device_get_api_version(ptc->p, ret_api_version);
}

int ptc_get_temperature(PTC *ptc, int32_t *ret_temperature) {
	DevicePrivate *device_p = ptc->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int32_from(response.temperature);

	return ret;
}

int ptc_get_resistance(PTC *ptc, int32_t *ret_resistance) {
	DevicePrivate *device_p = ptc->p;
	GetResistance_Request request;
	GetResistance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_resistance = leconvert_int32_from(response.resistance);

	return ret;
}

int ptc_set_temperature_callback_period(PTC *ptc, uint32_t period) {
	DevicePrivate *device_p = ptc->p;
	SetTemperatureCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_temperature_callback_period(PTC *ptc, uint32_t *ret_period) {
	DevicePrivate *device_p = ptc->p;
	GetTemperatureCallbackPeriod_Request request;
	GetTemperatureCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_resistance_callback_period(PTC *ptc, uint32_t period) {
	DevicePrivate *device_p = ptc->p;
	SetResistanceCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_RESISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_resistance_callback_period(PTC *ptc, uint32_t *ret_period) {
	DevicePrivate *device_p = ptc->p;
	GetResistanceCallbackPeriod_Request request;
	GetResistanceCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_temperature_callback_threshold(PTC *ptc, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = ptc->p;
	SetTemperatureCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_temperature_callback_threshold(PTC *ptc, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = ptc->p;
	GetTemperatureCallbackThreshold_Request request;
	GetTemperatureCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int ptc_set_resistance_callback_threshold(PTC *ptc, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = ptc->p;
	SetResistanceCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_RESISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_resistance_callback_threshold(PTC *ptc, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = ptc->p;
	GetResistanceCallbackThreshold_Request request;
	GetResistanceCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_RESISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int ptc_set_debounce_period(PTC *ptc, uint32_t debounce) {
	DevicePrivate *device_p = ptc->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_debounce_period(PTC *ptc, uint32_t *ret_debounce) {
	DevicePrivate *device_p = ptc->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int ptc_set_noise_rejection_filter(PTC *ptc, uint8_t filter) {
	DevicePrivate *device_p = ptc->p;
	SetNoiseRejectionFilter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.filter = filter;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_noise_rejection_filter(PTC *ptc, uint8_t *ret_filter) {
	DevicePrivate *device_p = ptc->p;
	GetNoiseRejectionFilter_Request request;
	GetNoiseRejectionFilter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_filter = response.filter;

	return ret;
}

int ptc_is_sensor_connected(PTC *ptc, bool *ret_connected) {
	DevicePrivate *device_p = ptc->p;
	IsSensorConnected_Request request;
	IsSensorConnected_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_IS_SENSOR_CONNECTED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_connected = response.connected != 0;

	return ret;
}

int ptc_set_wire_mode(PTC *ptc, uint8_t mode) {
	DevicePrivate *device_p = ptc->p;
	SetWireMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_WIRE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_wire_mode(PTC *ptc, uint8_t *ret_mode) {
	DevicePrivate *device_p = ptc->p;
	GetWireMode_Request request;
	GetWireMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_WIRE_MODE, device_p->ipcon_p, device_p);

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

int ptc_set_sensor_connected_callback_configuration(PTC *ptc, bool enabled) {
	DevicePrivate *device_p = ptc->p;
	SetSensorConnectedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_SET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_get_sensor_connected_callback_configuration(PTC *ptc, bool *ret_enabled) {
	DevicePrivate *device_p = ptc->p;
	GetSensorConnectedCallbackConfiguration_Request request;
	GetSensorConnectedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_get_identity(PTC *ptc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ptc->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
