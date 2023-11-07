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

#include "bricklet_barometer.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AirPressure_CallbackFunction)(int32_t air_pressure, void *user_data);

typedef void (*Altitude_CallbackFunction)(int32_t altitude, void *user_data);

typedef void (*AirPressureReached_CallbackFunction)(int32_t air_pressure, void *user_data);

typedef void (*AltitudeReached_CallbackFunction)(int32_t altitude, void *user_data);

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
} ATTRIBUTE_PACKED GetAirPressure_Request;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetAirPressure_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitude_Request;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED GetAltitude_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAirPressureCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressureCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAirPressureCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAltitudeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetAirPressureCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressureCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetAirPressureCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetAltitudeCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitudeCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetAltitudeCallbackThreshold_Response;

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
	int32_t air_pressure;
} ATTRIBUTE_PACKED SetReferenceAirPressure_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperature_Response;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AirPressure_Callback;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED Altitude_Callback;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AirPressureReached_Callback;

typedef struct {
	PacketHeader header;
	int32_t altitude;
} ATTRIBUTE_PACKED AltitudeReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReferenceAirPressure_Request;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetReferenceAirPressure_Response;

typedef struct {
	PacketHeader header;
	uint8_t moving_average_pressure;
	uint8_t average_pressure;
	uint8_t average_temperature;
} ATTRIBUTE_PACKED SetAveraging_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAveraging_Request;

typedef struct {
	PacketHeader header;
	uint8_t moving_average_pressure;
	uint8_t average_pressure;
	uint8_t average_temperature;
} ATTRIBUTE_PACKED GetAveraging_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetI2CMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetI2CMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetI2CMode_Response;

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

static void barometer_callback_wrapper_air_pressure(DevicePrivate *device_p, Packet *packet) {
	AirPressure_CallbackFunction callback_function;
	void *user_data;
	AirPressure_Callback *callback;

	if (packet->header.length != sizeof(AirPressure_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AirPressure_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_AIR_PRESSURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_AIR_PRESSURE];
	callback = (AirPressure_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->air_pressure, user_data);
}

static void barometer_callback_wrapper_altitude(DevicePrivate *device_p, Packet *packet) {
	Altitude_CallbackFunction callback_function;
	void *user_data;
	Altitude_Callback *callback;

	if (packet->header.length != sizeof(Altitude_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Altitude_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_ALTITUDE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_ALTITUDE];
	callback = (Altitude_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->altitude = leconvert_int32_from(callback->altitude);

	callback_function(callback->altitude, user_data);
}

static void barometer_callback_wrapper_air_pressure_reached(DevicePrivate *device_p, Packet *packet) {
	AirPressureReached_CallbackFunction callback_function;
	void *user_data;
	AirPressureReached_Callback *callback;

	if (packet->header.length != sizeof(AirPressureReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AirPressureReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_AIR_PRESSURE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_AIR_PRESSURE_REACHED];
	callback = (AirPressureReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->air_pressure, user_data);
}

static void barometer_callback_wrapper_altitude_reached(DevicePrivate *device_p, Packet *packet) {
	AltitudeReached_CallbackFunction callback_function;
	void *user_data;
	AltitudeReached_Callback *callback;

	if (packet->header.length != sizeof(AltitudeReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AltitudeReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_ALTITUDE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + BAROMETER_CALLBACK_ALTITUDE_REACHED];
	callback = (AltitudeReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->altitude = leconvert_int32_from(callback->altitude);

	callback_function(callback->altitude, user_data);
}

void barometer_create(Barometer *barometer, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(barometer, uid, ipcon_p, 2, 0, 2, BAROMETER_DEVICE_IDENTIFIER);

	device_p = barometer->p;

	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_REFERENCE_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_REFERENCE_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_AVERAGING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_SET_I2C_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_I2C_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[BAROMETER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[BAROMETER_CALLBACK_AIR_PRESSURE] = barometer_callback_wrapper_air_pressure;
	device_p->callback_wrappers[BAROMETER_CALLBACK_ALTITUDE] = barometer_callback_wrapper_altitude;
	device_p->callback_wrappers[BAROMETER_CALLBACK_AIR_PRESSURE_REACHED] = barometer_callback_wrapper_air_pressure_reached;
	device_p->callback_wrappers[BAROMETER_CALLBACK_ALTITUDE_REACHED] = barometer_callback_wrapper_altitude_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void barometer_destroy(Barometer *barometer) {
	device_release(barometer->p);
}

int barometer_get_response_expected(Barometer *barometer, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(barometer->p, function_id, ret_response_expected);
}

int barometer_set_response_expected(Barometer *barometer, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(barometer->p, function_id, response_expected);
}

int barometer_set_response_expected_all(Barometer *barometer, bool response_expected) {
	return device_set_response_expected_all(barometer->p, response_expected);
}

void barometer_register_callback(Barometer *barometer, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(barometer->p, callback_id, function, user_data);
}

int barometer_get_api_version(Barometer *barometer, uint8_t ret_api_version[3]) {
	return device_get_api_version(barometer->p, ret_api_version);
}

int barometer_get_air_pressure(Barometer *barometer, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressure_Request request;
	GetAirPressure_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_air_pressure = leconvert_int32_from(response.air_pressure);

	return ret;
}

int barometer_get_altitude(Barometer *barometer, int32_t *ret_altitude) {
	DevicePrivate *device_p = barometer->p;
	GetAltitude_Request request;
	GetAltitude_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_altitude = leconvert_int32_from(response.altitude);

	return ret;
}

int barometer_set_air_pressure_callback_period(Barometer *barometer, uint32_t period) {
	DevicePrivate *device_p = barometer->p;
	SetAirPressureCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_air_pressure_callback_period(Barometer *barometer, uint32_t *ret_period) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressureCallbackPeriod_Request request;
	GetAirPressureCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_altitude_callback_period(Barometer *barometer, uint32_t period) {
	DevicePrivate *device_p = barometer->p;
	SetAltitudeCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_altitude_callback_period(Barometer *barometer, uint32_t *ret_period) {
	DevicePrivate *device_p = barometer->p;
	GetAltitudeCallbackPeriod_Request request;
	GetAltitudeCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_air_pressure_callback_threshold(Barometer *barometer, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = barometer->p;
	SetAirPressureCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AIR_PRESSURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_air_pressure_callback_threshold(Barometer *barometer, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = barometer->p;
	GetAirPressureCallbackThreshold_Request request;
	GetAirPressureCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AIR_PRESSURE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int barometer_set_altitude_callback_threshold(Barometer *barometer, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = barometer->p;
	SetAltitudeCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_ALTITUDE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_altitude_callback_threshold(Barometer *barometer, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = barometer->p;
	GetAltitudeCallbackThreshold_Request request;
	GetAltitudeCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_ALTITUDE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int barometer_set_debounce_period(Barometer *barometer, uint32_t debounce) {
	DevicePrivate *device_p = barometer->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_debounce_period(Barometer *barometer, uint32_t *ret_debounce) {
	DevicePrivate *device_p = barometer->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int barometer_set_reference_air_pressure(Barometer *barometer, int32_t air_pressure) {
	DevicePrivate *device_p = barometer->p;
	SetReferenceAirPressure_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_REFERENCE_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.air_pressure = leconvert_int32_to(air_pressure);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_chip_temperature(Barometer *barometer, int16_t *ret_temperature) {
	DevicePrivate *device_p = barometer->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int barometer_get_reference_air_pressure(Barometer *barometer, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = barometer->p;
	GetReferenceAirPressure_Request request;
	GetReferenceAirPressure_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_REFERENCE_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_air_pressure = leconvert_int32_from(response.air_pressure);

	return ret;
}

int barometer_set_averaging(Barometer *barometer, uint8_t moving_average_pressure, uint8_t average_pressure, uint8_t average_temperature) {
	DevicePrivate *device_p = barometer->p;
	SetAveraging_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.moving_average_pressure = moving_average_pressure;
	request.average_pressure = average_pressure;
	request.average_temperature = average_temperature;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_averaging(Barometer *barometer, uint8_t *ret_moving_average_pressure, uint8_t *ret_average_pressure, uint8_t *ret_average_temperature) {
	DevicePrivate *device_p = barometer->p;
	GetAveraging_Request request;
	GetAveraging_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_AVERAGING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_moving_average_pressure = response.moving_average_pressure;
	*ret_average_pressure = response.average_pressure;
	*ret_average_temperature = response.average_temperature;

	return ret;
}

int barometer_set_i2c_mode(Barometer *barometer, uint8_t mode) {
	DevicePrivate *device_p = barometer->p;
	SetI2CMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_SET_I2C_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int barometer_get_i2c_mode(Barometer *barometer, uint8_t *ret_mode) {
	DevicePrivate *device_p = barometer->p;
	GetI2CMode_Request request;
	GetI2CMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_I2C_MODE, device_p->ipcon_p, device_p);

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

int barometer_get_identity(Barometer *barometer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = barometer->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), BAROMETER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
