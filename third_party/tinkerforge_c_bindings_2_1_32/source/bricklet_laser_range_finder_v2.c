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

#include "bricklet_laser_range_finder_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Distance_CallbackFunction)(int16_t distance, void *user_data);

typedef void (*Velocity_CallbackFunction)(int16_t velocity, void *user_data);

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
	int16_t distance;
} ATTRIBUTE_PACKED GetDistance_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetDistanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetDistanceCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int16_t distance;
} ATTRIBUTE_PACKED Distance_Callback;

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
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetVelocityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED Velocity_Callback;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED SetEnable_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEnable_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED GetEnable_Response;

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
	int16_t offset;
} ATTRIBUTE_PACKED SetOffsetCalibration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOffsetCalibration_Request;

typedef struct {
	PacketHeader header;
	int16_t offset;
} ATTRIBUTE_PACKED GetOffsetCalibration_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetDistanceLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDistanceLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetDistanceLEDConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t error_count_ack_checksum;
	uint32_t error_count_message_checksum;
	uint32_t error_count_frame;
	uint32_t error_count_overflow;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED SetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
	uint32_t pointer;
} ATTRIBUTE_PACKED SetWriteFirmwarePointer_Request;

typedef struct {
	PacketHeader header;
	uint8_t data[64];
} ATTRIBUTE_PACKED WriteFirmware_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED WriteFirmware_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Reset_Request;

typedef struct {
	PacketHeader header;
	uint32_t uid;
} ATTRIBUTE_PACKED WriteUID_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadUID_Request;

typedef struct {
	PacketHeader header;
	uint32_t uid;
} ATTRIBUTE_PACKED ReadUID_Response;

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

static void laser_range_finder_v2_callback_wrapper_distance(DevicePrivate *device_p, Packet *packet) {
	Distance_CallbackFunction callback_function;
	void *user_data;
	Distance_Callback *callback;

	if (packet->header.length != sizeof(Distance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Distance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_V2_CALLBACK_DISTANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_V2_CALLBACK_DISTANCE];
	callback = (Distance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->distance = leconvert_int16_from(callback->distance);

	callback_function(callback->distance, user_data);
}

static void laser_range_finder_v2_callback_wrapper_velocity(DevicePrivate *device_p, Packet *packet) {
	Velocity_CallbackFunction callback_function;
	void *user_data;
	Velocity_Callback *callback;

	if (packet->header.length != sizeof(Velocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Velocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_V2_CALLBACK_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + LASER_RANGE_FINDER_V2_CALLBACK_VELOCITY];
	callback = (Velocity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

void laser_range_finder_v2_create(LaserRangeFinderV2 *laser_range_finder_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(laser_range_finder_v2, uid, ipcon_p, 2, 0, 0, LASER_RANGE_FINDER_V2_DEVICE_IDENTIFIER);

	device_p = laser_range_finder_v2->p;

	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_DISTANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_ENABLE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_MOVING_AVERAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_OFFSET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_OFFSET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_DISTANCE_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[LASER_RANGE_FINDER_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[LASER_RANGE_FINDER_V2_CALLBACK_DISTANCE] = laser_range_finder_v2_callback_wrapper_distance;
	device_p->callback_wrappers[LASER_RANGE_FINDER_V2_CALLBACK_VELOCITY] = laser_range_finder_v2_callback_wrapper_velocity;

	ipcon_add_device(ipcon_p, device_p);
}

void laser_range_finder_v2_destroy(LaserRangeFinderV2 *laser_range_finder_v2) {
	device_release(laser_range_finder_v2->p);
}

int laser_range_finder_v2_get_response_expected(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(laser_range_finder_v2->p, function_id, ret_response_expected);
}

int laser_range_finder_v2_set_response_expected(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(laser_range_finder_v2->p, function_id, response_expected);
}

int laser_range_finder_v2_set_response_expected_all(LaserRangeFinderV2 *laser_range_finder_v2, bool response_expected) {
	return device_set_response_expected_all(laser_range_finder_v2->p, response_expected);
}

void laser_range_finder_v2_register_callback(LaserRangeFinderV2 *laser_range_finder_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(laser_range_finder_v2->p, callback_id, function, user_data);
}

int laser_range_finder_v2_get_api_version(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(laser_range_finder_v2->p, ret_api_version);
}

int laser_range_finder_v2_get_distance(LaserRangeFinderV2 *laser_range_finder_v2, int16_t *ret_distance) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetDistance_Request request;
	GetDistance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_distance = leconvert_int16_from(response.distance);

	return ret;
}

int laser_range_finder_v2_set_distance_callback_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetDistanceCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_DISTANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_distance_callback_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetDistanceCallbackConfiguration_Request request;
	GetDistanceCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;
	*ret_option = response.option;
	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);

	return ret;
}

int laser_range_finder_v2_get_velocity(LaserRangeFinderV2 *laser_range_finder_v2, int16_t *ret_velocity) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetVelocity_Request request;
	GetVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_set_velocity_callback_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetVelocityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_velocity_callback_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetVelocityCallbackConfiguration_Request request;
	GetVelocityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;
	*ret_option = response.option;
	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);

	return ret;
}

int laser_range_finder_v2_set_enable(LaserRangeFinderV2 *laser_range_finder_v2, bool enable) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetEnable_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable = enable ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_enable(LaserRangeFinderV2 *laser_range_finder_v2, bool *ret_enable) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetEnable_Request request;
	GetEnable_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;

	return ret;
}

int laser_range_finder_v2_set_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t acquisition_count, bool enable_quick_termination, uint8_t threshold_value, uint16_t measurement_frequency) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_get_configuration(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t *ret_acquisition_count, bool *ret_enable_quick_termination, uint8_t *ret_threshold_value, uint16_t *ret_measurement_frequency) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_set_moving_average(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t distance_average_length, uint8_t velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetMovingAverage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.distance_average_length = distance_average_length;
	request.velocity_average_length = velocity_average_length;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_moving_average(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t *ret_distance_average_length, uint8_t *ret_velocity_average_length) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetMovingAverage_Request request;
	GetMovingAverage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_MOVING_AVERAGE, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_set_offset_calibration(LaserRangeFinderV2 *laser_range_finder_v2, int16_t offset) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetOffsetCalibration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_OFFSET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = leconvert_int16_to(offset);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_offset_calibration(LaserRangeFinderV2 *laser_range_finder_v2, int16_t *ret_offset) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetOffsetCalibration_Request request;
	GetOffsetCalibration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_OFFSET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_offset = leconvert_int16_from(response.offset);

	return ret;
}

int laser_range_finder_v2_set_distance_led_config(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t config) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetDistanceLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_DISTANCE_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_distance_led_config(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetDistanceLEDConfig_Request request;
	GetDistanceLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_DISTANCE_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int laser_range_finder_v2_get_spitfp_error_count(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_error_count_ack_checksum = leconvert_uint32_from(response.error_count_ack_checksum);
	*ret_error_count_message_checksum = leconvert_uint32_from(response.error_count_message_checksum);
	*ret_error_count_frame = leconvert_uint32_from(response.error_count_frame);
	*ret_error_count_overflow = leconvert_uint32_from(response.error_count_overflow);

	return ret;
}

int laser_range_finder_v2_set_bootloader_mode(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int laser_range_finder_v2_get_bootloader_mode(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_set_write_firmware_pointer(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t pointer) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_write_firmware(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int laser_range_finder_v2_set_status_led_config(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t config) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_get_status_led_config(LaserRangeFinderV2 *laser_range_finder_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int laser_range_finder_v2_get_chip_temperature(LaserRangeFinderV2 *laser_range_finder_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int laser_range_finder_v2_reset(LaserRangeFinderV2 *laser_range_finder_v2) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_write_uid(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t uid) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int laser_range_finder_v2_read_uid(LaserRangeFinderV2 *laser_range_finder_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uid = leconvert_uint32_from(response.uid);

	return ret;
}

int laser_range_finder_v2_get_identity(LaserRangeFinderV2 *laser_range_finder_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = laser_range_finder_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), LASER_RANGE_FINDER_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
