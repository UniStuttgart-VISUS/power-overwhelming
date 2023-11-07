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

#include "bricklet_accelerometer.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Acceleration_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*AccelerationReached_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

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
} ATTRIBUTE_PACKED GetAcceleration_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAcceleration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAccelerationCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAccelerationCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
	int16_t min_z;
	int16_t max_z;
} ATTRIBUTE_PACKED SetAccelerationCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
	int16_t min_z;
	int16_t max_z;
} ATTRIBUTE_PACKED GetAccelerationCallbackThreshold_Response;

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
} ATTRIBUTE_PACKED GetTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetTemperature_Response;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
	uint8_t filter_bandwidth;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
	uint8_t filter_bandwidth;
} ATTRIBUTE_PACKED GetConfiguration_Response;

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
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED Acceleration_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AccelerationReached_Callback;

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

static void accelerometer_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	Acceleration_CallbackFunction callback_function;
	void *user_data;
	Acceleration_Callback *callback;

	if (packet->header.length != sizeof(Acceleration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Acceleration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_CALLBACK_ACCELERATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_CALLBACK_ACCELERATION];
	callback = (Acceleration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void accelerometer_callback_wrapper_acceleration_reached(DevicePrivate *device_p, Packet *packet) {
	AccelerationReached_CallbackFunction callback_function;
	void *user_data;
	AccelerationReached_Callback *callback;

	if (packet->header.length != sizeof(AccelerationReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AccelerationReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_CALLBACK_ACCELERATION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_CALLBACK_ACCELERATION_REACHED];
	callback = (AccelerationReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

void accelerometer_create(Accelerometer *accelerometer, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(accelerometer, uid, ipcon_p, 2, 0, 1, ACCELEROMETER_DEVICE_IDENTIFIER);

	device_p = accelerometer->p;

	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_LED_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_LED_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_IS_LED_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ACCELEROMETER_CALLBACK_ACCELERATION] = accelerometer_callback_wrapper_acceleration;
	device_p->callback_wrappers[ACCELEROMETER_CALLBACK_ACCELERATION_REACHED] = accelerometer_callback_wrapper_acceleration_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void accelerometer_destroy(Accelerometer *accelerometer) {
	device_release(accelerometer->p);
}

int accelerometer_get_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(accelerometer->p, function_id, ret_response_expected);
}

int accelerometer_set_response_expected(Accelerometer *accelerometer, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(accelerometer->p, function_id, response_expected);
}

int accelerometer_set_response_expected_all(Accelerometer *accelerometer, bool response_expected) {
	return device_set_response_expected_all(accelerometer->p, response_expected);
}

void accelerometer_register_callback(Accelerometer *accelerometer, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(accelerometer->p, callback_id, function, user_data);
}

int accelerometer_get_api_version(Accelerometer *accelerometer, uint8_t ret_api_version[3]) {
	return device_get_api_version(accelerometer->p, ret_api_version);
}

int accelerometer_get_acceleration(Accelerometer *accelerometer, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = accelerometer->p;
	GetAcceleration_Request request;
	GetAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);

	return ret;
}

int accelerometer_set_acceleration_callback_period(Accelerometer *accelerometer, uint32_t period) {
	DevicePrivate *device_p = accelerometer->p;
	SetAccelerationCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_get_acceleration_callback_period(Accelerometer *accelerometer, uint32_t *ret_period) {
	DevicePrivate *device_p = accelerometer->p;
	GetAccelerationCallbackPeriod_Request request;
	GetAccelerationCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int accelerometer_set_acceleration_callback_threshold(Accelerometer *accelerometer, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y, int16_t min_z, int16_t max_z) {
	DevicePrivate *device_p = accelerometer->p;
	SetAccelerationCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_ACCELERATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_int16_to(min_x);
	request.max_x = leconvert_int16_to(max_x);
	request.min_y = leconvert_int16_to(min_y);
	request.max_y = leconvert_int16_to(max_y);
	request.min_z = leconvert_int16_to(min_z);
	request.max_z = leconvert_int16_to(max_z);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_get_acceleration_callback_threshold(Accelerometer *accelerometer, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y, int16_t *ret_min_z, int16_t *ret_max_z) {
	DevicePrivate *device_p = accelerometer->p;
	GetAccelerationCallbackThreshold_Request request;
	GetAccelerationCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_ACCELERATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min_x = leconvert_int16_from(response.min_x);
	*ret_max_x = leconvert_int16_from(response.max_x);
	*ret_min_y = leconvert_int16_from(response.min_y);
	*ret_max_y = leconvert_int16_from(response.max_y);
	*ret_min_z = leconvert_int16_from(response.min_z);
	*ret_max_z = leconvert_int16_from(response.max_z);

	return ret;
}

int accelerometer_set_debounce_period(Accelerometer *accelerometer, uint32_t debounce) {
	DevicePrivate *device_p = accelerometer->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_get_debounce_period(Accelerometer *accelerometer, uint32_t *ret_debounce) {
	DevicePrivate *device_p = accelerometer->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int accelerometer_get_temperature(Accelerometer *accelerometer, int16_t *ret_temperature) {
	DevicePrivate *device_p = accelerometer->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

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

int accelerometer_set_configuration(Accelerometer *accelerometer, uint8_t data_rate, uint8_t full_scale, uint8_t filter_bandwidth) {
	DevicePrivate *device_p = accelerometer->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.data_rate = data_rate;
	request.full_scale = full_scale;
	request.filter_bandwidth = filter_bandwidth;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_get_configuration(Accelerometer *accelerometer, uint8_t *ret_data_rate, uint8_t *ret_full_scale, uint8_t *ret_filter_bandwidth) {
	DevicePrivate *device_p = accelerometer->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_data_rate = response.data_rate;
	*ret_full_scale = response.full_scale;
	*ret_filter_bandwidth = response.filter_bandwidth;

	return ret;
}

int accelerometer_led_on(Accelerometer *accelerometer) {
	DevicePrivate *device_p = accelerometer->p;
	LEDOn_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_LED_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_led_off(Accelerometer *accelerometer) {
	DevicePrivate *device_p = accelerometer->p;
	LEDOff_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_LED_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_is_led_on(Accelerometer *accelerometer, bool *ret_on) {
	DevicePrivate *device_p = accelerometer->p;
	IsLEDOn_Request request;
	IsLEDOn_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_IS_LED_ON, device_p->ipcon_p, device_p);

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

int accelerometer_get_identity(Accelerometer *accelerometer, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = accelerometer->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
