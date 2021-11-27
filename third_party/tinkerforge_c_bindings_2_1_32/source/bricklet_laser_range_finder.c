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

#include "bricklet_laser_range_finder.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Distance_CallbackFunction)(uint16_t distance, void *user_data);

typedef void (*Velocity_CallbackFunction)(int16_t velocity, void *user_data);

typedef void (*DistanceReached_CallbackFunction)(uint16_t distance, void *user_data);

typedef void (*VelocityReached_CallbackFunction)(int16_t velocity, void *user_data);

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
} ATTRIBUTE_PACKED GetDistance_Request;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED GetDistance_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocity_Request;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetVelocity_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetDistanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetDistanceCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetVelocityCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetVelocityCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetDistanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetDistanceCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetVelocityCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetVelocityCallbackThreshold_Response;

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
	uint8_t distance_average_length;
	uint8_t velocity_average_length;
} ATTRIBUTE_PACKED SetMovingAverage_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverage_Request;

typedef struct {
	PacketHeader header;
	uint8_t distance_average_length;
	uint8_t velocity_average_length;
} ATTRIBUTE_PACKED GetMovingAverage_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableLaser_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableLaser_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsLaserEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t laser_enabled;
} ATTRIBUTE_PACKED IsLaserEnabled_Response;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED Distance_Callback;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED Velocity_Callback;

typedef struct {
	PacketHeader header;
	uint16_t distance;
} ATTRIBUTE_PACKED DistanceReached_Callback;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorHardwareVersion_Request;

typedef struct {
	PacketHeader header;
	uint8_t version;
} ATTRIBUTE_PACKED GetSensorHardwareVersion_Response;

typedef struct {
	PacketHeader header;
	uint8_t acquisition_count;
	uint8_t enable_quick_termination;
	uint8_t threshold_value;
	uint16_t measurement_frequency;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t acquisition_count;
	uint8_t enable_quick_termination;
	uint8_t threshold_value;
	uint16_t measurement_frequency;
} ATTRIBUTE_PACKED GetConfiguration_Response;

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

static void laser_range_finder_callback_wrapper_distance(DevicePrivate *device_p, Packet *packet) {
	Distance_CallbackFunction callback_function;
	void *user_data;
	Distance_Callback *callback;

	if (packet->header.length != sizeof(Distance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Distance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_DISTANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_DISTANCE];
	callback = (Distance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void laser_range_finder_callback_wrapper_velocity(DevicePrivate *device_p, Packet *packet) {
	Velocity_CallbackFunction callback_function;
	void *user_data;
	Velocity_Callback *callback;

	if (packet->header.length != sizeof(Velocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Velocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_VELOCITY];
	callback = (Velocity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void laser_range_finder_callback_wrapper_distance_reached(DevicePrivate *device_p, Packet *packet) {
	DistanceReached_CallbackFunction callback_function;
	void *user_data;
	DistanceReached_Callback *callback;

	if (packet->header.length != sizeof(DistanceReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (DistanceReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED];
	callback = (DistanceReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_uint16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void laser_range_finder_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReached_CallbackFunction callback_function;
	void *user_data;
	VelocityReached_Callback *callback;

	if (packet->header.length != sizeof(VelocityReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (VelocityReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED];
	callback = (VelocityReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

void laser_range_finder_create(LaserRangeFinder *laser_range_finder, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(laser_range_finder, uid, ipcon_p, 2, 0, 1, LASER_RANGE_FINDER_DEVICE_IDENTIFIER);

	device_p = laser_range_finder->p;

	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_ENABLE_LASER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_DISABLE_LASER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_IS_LASER_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_SENSOR_HARDWARE_VERSION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_DISTANCE] = laser_range_finder_callback_wrapper_distance;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_VELOCITY] = laser_range_finder_callback_wrapper_velocity;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED] = laser_range_finder_callback_wrapper_distance_reached;
	device_p->callback_wrappers[LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED] = laser_range_finder_callback_wrapper_velocity_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void laser_range_finder_destroy(LaserRangeFinder *laser_range_finder) {
	device_release(laser_range_finder->p);
}

int laser_range_finder_get_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(laser_range_finder->p, function_id, ret_response_expected);
}

int laser_range_finder_set_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(laser_range_finder->p, function_id, response_expected);
}

int laser_range_finder_set_response_expected_all(LaserRangeFinder *laser_range_finder, bool response_expected) {
	return device_set_response_expected_all(laser_range_finder->p, response_expected);
}

void laser_range_finder_register_callback(LaserRangeFinder *laser_range_finder, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(laser_range_finder->p, callback_id, function, user_data);
}

int laser_range_finder_get_api_version(LaserRangeFinder *laser_range_finder, uint8_t ret_api_version[3]) {
	return device_get_api_version(laser_range_finder->p, ret_api_version);
}

int laser_range_finder_get_distance(LaserRangeFinder *laser_range_finder, uint16_t *ret_distance) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistance_Request request;
	GetDistance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_distance = leconvert_uint16_from(response.distance);

	return ret;
}

int laser_range_finder_get_velocity(LaserRangeFinder *laser_range_finder, int16_t *ret_velocity) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocity_Request request;
	GetVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_int16_from(response.velocity);

	return ret;
}

int laser_range_finder_set_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDistanceCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistanceCallbackPeriod_Request request;
	GetDistanceCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetVelocityCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocityCallbackPeriod_Request request;
	GetVelocityCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDistanceCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDistanceCallbackThreshold_Request request;
	GetDistanceCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetVelocityCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetVelocityCallbackThreshold_Request request;
	GetVelocityCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t debounce) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_debounce) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int laser_range_finder_set_moving_average(LaserRangeFinder *laser_range_finder, uint8_t distance_average_length, uint8_t velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetMovingAverage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.distance_average_length = distance_average_length;
	request.velocity_average_length = velocity_average_length;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_moving_average(LaserRangeFinder *laser_range_finder, uint8_t *ret_distance_average_length, uint8_t *ret_velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetMovingAverage_Request request;
	GetMovingAverage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_distance_average_length = response.distance_average_length;
	*ret_velocity_average_length = response.velocity_average_length;

	return ret;
}

int laser_range_finder_set_mode(LaserRangeFinder *laser_range_finder, uint8_t mode) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_mode(LaserRangeFinder *laser_range_finder, uint8_t *ret_mode) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetMode_Request request;
	GetMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_MODE, device_p->ipcon_p, device_p);

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

int laser_range_finder_enable_laser(LaserRangeFinder *laser_range_finder) {
	DevicePrivate *device_p = laser_range_finder->p;
	EnableLaser_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_ENABLE_LASER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_disable_laser(LaserRangeFinder *laser_range_finder) {
	DevicePrivate *device_p = laser_range_finder->p;
	DisableLaser_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_DISABLE_LASER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_is_laser_enabled(LaserRangeFinder *laser_range_finder, bool *ret_laser_enabled) {
	DevicePrivate *device_p = laser_range_finder->p;
	IsLaserEnabled_Request request;
	IsLaserEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_IS_LASER_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_laser_enabled = response.laser_enabled != 0;

	return ret;
}

int laser_range_finder_get_sensor_hardware_version(LaserRangeFinder *laser_range_finder, uint8_t *ret_version) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetSensorHardwareVersion_Request request;
	GetSensorHardwareVersion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_SENSOR_HARDWARE_VERSION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_version = response.version;

	return ret;
}

int laser_range_finder_set_configuration(LaserRangeFinder *laser_range_finder, uint8_t acquisition_count, bool enable_quick_termination, uint8_t threshold_value, uint16_t measurement_frequency) {
	DevicePrivate *device_p = laser_range_finder->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.acquisition_count = acquisition_count;
	request.enable_quick_termination = enable_quick_termination ? 1 : 0;
	request.threshold_value = threshold_value;
	request.measurement_frequency = leconvert_uint16_to(measurement_frequency);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_get_configuration(LaserRangeFinder *laser_range_finder, uint8_t *ret_acquisition_count, bool *ret_enable_quick_termination, uint8_t *ret_threshold_value, uint16_t *ret_measurement_frequency) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_acquisition_count = response.acquisition_count;
	*ret_enable_quick_termination = response.enable_quick_termination != 0;
	*ret_threshold_value = response.threshold_value;
	*ret_measurement_frequency = leconvert_uint16_from(response.measurement_frequency);

	return ret;
}

int laser_range_finder_get_identity(LaserRangeFinder *laser_range_finder, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = laser_range_finder->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
