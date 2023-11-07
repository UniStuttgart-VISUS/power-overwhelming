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

#include "bricklet_servo_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*PositionReached_CallbackFunction)(uint16_t servo_channel, int16_t position, void *user_data);

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
} ATTRIBUTE_PACKED GetStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled[2];
	int16_t current_position[10];
	int16_t current_velocity[10];
	uint16_t current[10];
	uint16_t input_voltage;
} ATTRIBUTE_PACKED GetStatus_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint8_t enable;
} ATTRIBUTE_PACKED SetEnable_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED GetEnabled_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	int16_t position;
} ATTRIBUTE_PACKED SetPosition_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetPosition_Request;

typedef struct {
	PacketHeader header;
	int16_t position;
} ATTRIBUTE_PACKED GetPosition_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetCurrentPosition_Request;

typedef struct {
	PacketHeader header;
	int16_t position;
} ATTRIBUTE_PACKED GetCurrentPosition_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetCurrentVelocity_Request;

typedef struct {
	PacketHeader header;
	uint16_t velocity;
} ATTRIBUTE_PACKED GetCurrentVelocity_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint32_t velocity;
	uint32_t acceleration;
	uint32_t deceleration;
} ATTRIBUTE_PACKED SetMotionConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetMotionConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t velocity;
	uint32_t acceleration;
	uint32_t deceleration;
} ATTRIBUTE_PACKED GetMotionConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED SetPulseWidth_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetPulseWidth_Request;

typedef struct {
	PacketHeader header;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED GetPulseWidth_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetDegree_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetDegree_Request;

typedef struct {
	PacketHeader header;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetDegree_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint32_t period;
} ATTRIBUTE_PACKED SetPeriod_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetPeriod_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetServoCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetServoCurrent_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint8_t averaging_duration;
} ATTRIBUTE_PACKED SetServoCurrentConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetServoCurrentConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t averaging_duration;
} ATTRIBUTE_PACKED GetServoCurrentConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t averaging_duration;
} ATTRIBUTE_PACKED SetInputVoltageConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInputVoltageConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t averaging_duration;
} ATTRIBUTE_PACKED GetInputVoltageConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOverallCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetOverallCurrent_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInputVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetInputVoltage_Response;

typedef struct {
	PacketHeader header;
	int16_t offset[10];
} ATTRIBUTE_PACKED SetCurrentCalibration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCalibration_Request;

typedef struct {
	PacketHeader header;
	int16_t offset[10];
} ATTRIBUTE_PACKED GetCurrentCalibration_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetPositionReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
} ATTRIBUTE_PACKED GetPositionReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetPositionReachedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t servo_channel;
	int16_t position;
} ATTRIBUTE_PACKED PositionReached_Callback;

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

static void servo_v2_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReached_CallbackFunction callback_function;
	void *user_data;
	PositionReached_Callback *callback;

	if (packet->header.length != sizeof(PositionReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PositionReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SERVO_V2_CALLBACK_POSITION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SERVO_V2_CALLBACK_POSITION_REACHED];
	callback = (PositionReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->servo_channel = leconvert_uint16_from(callback->servo_channel);
	callback->position = leconvert_int16_from(callback->position);

	callback_function(callback->servo_channel, callback->position, user_data);
}

void servo_v2_create(ServoV2 *servo_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(servo_v2, uid, ipcon_p, 2, 0, 0, SERVO_V2_DEVICE_IDENTIFIER);

	device_p = servo_v2->p;

	device_p->response_expected[SERVO_V2_FUNCTION_GET_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_POSITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_CURRENT_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_MOTION_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_MOTION_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_PULSE_WIDTH] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_PULSE_WIDTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_DEGREE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_DEGREE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_PERIOD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_SERVO_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_SERVO_CURRENT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_SERVO_CURRENT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_INPUT_VOLTAGE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_INPUT_VOLTAGE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_OVERALL_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_CURRENT_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_CURRENT_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_POSITION_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_POSITION_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SERVO_V2_CALLBACK_POSITION_REACHED] = servo_v2_callback_wrapper_position_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void servo_v2_destroy(ServoV2 *servo_v2) {
	device_release(servo_v2->p);
}

int servo_v2_get_response_expected(ServoV2 *servo_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(servo_v2->p, function_id, ret_response_expected);
}

int servo_v2_set_response_expected(ServoV2 *servo_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(servo_v2->p, function_id, response_expected);
}

int servo_v2_set_response_expected_all(ServoV2 *servo_v2, bool response_expected) {
	return device_set_response_expected_all(servo_v2->p, response_expected);
}

void servo_v2_register_callback(ServoV2 *servo_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(servo_v2->p, callback_id, function, user_data);
}

int servo_v2_get_api_version(ServoV2 *servo_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(servo_v2->p, ret_api_version);
}

int servo_v2_get_status(ServoV2 *servo_v2, bool ret_enabled[10], int16_t ret_current_position[10], int16_t ret_current_velocity[10], uint16_t ret_current[10], uint16_t *ret_input_voltage) {
	DevicePrivate *device_p = servo_v2->p;
	GetStatus_Request request;
	GetStatus_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 10; i++) ret_enabled[i] = (response.enabled[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 10; i++) ret_current_position[i] = leconvert_int16_from(response.current_position[i]);
	for (i = 0; i < 10; i++) ret_current_velocity[i] = leconvert_int16_from(response.current_velocity[i]);
	for (i = 0; i < 10; i++) ret_current[i] = leconvert_uint16_from(response.current[i]);
	*ret_input_voltage = leconvert_uint16_from(response.input_voltage);

	return ret;
}

int servo_v2_set_enable(ServoV2 *servo_v2, uint16_t servo_channel, bool enable) {
	DevicePrivate *device_p = servo_v2->p;
	SetEnable_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.enable = enable ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_enabled(ServoV2 *servo_v2, uint16_t servo_channel, bool *ret_enable) {
	DevicePrivate *device_p = servo_v2->p;
	GetEnabled_Request request;
	GetEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;

	return ret;
}

int servo_v2_set_position(ServoV2 *servo_v2, uint16_t servo_channel, int16_t position) {
	DevicePrivate *device_p = servo_v2->p;
	SetPosition_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.position = leconvert_int16_to(position);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_position(ServoV2 *servo_v2, uint16_t servo_channel, int16_t *ret_position) {
	DevicePrivate *device_p = servo_v2->p;
	GetPosition_Request request;
	GetPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int16_from(response.position);

	return ret;
}

int servo_v2_get_current_position(ServoV2 *servo_v2, uint16_t servo_channel, int16_t *ret_position) {
	DevicePrivate *device_p = servo_v2->p;
	GetCurrentPosition_Request request;
	GetCurrentPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_CURRENT_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int16_from(response.position);

	return ret;
}

int servo_v2_get_current_velocity(ServoV2 *servo_v2, uint16_t servo_channel, uint16_t *ret_velocity) {
	DevicePrivate *device_p = servo_v2->p;
	GetCurrentVelocity_Request request;
	GetCurrentVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint16_from(response.velocity);

	return ret;
}

int servo_v2_set_motion_configuration(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t velocity, uint32_t acceleration, uint32_t deceleration) {
	DevicePrivate *device_p = servo_v2->p;
	SetMotionConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_MOTION_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.velocity = leconvert_uint32_to(velocity);
	request.acceleration = leconvert_uint32_to(acceleration);
	request.deceleration = leconvert_uint32_to(deceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_motion_configuration(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t *ret_velocity, uint32_t *ret_acceleration, uint32_t *ret_deceleration) {
	DevicePrivate *device_p = servo_v2->p;
	GetMotionConfiguration_Request request;
	GetMotionConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_MOTION_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint32_from(response.velocity);
	*ret_acceleration = leconvert_uint32_from(response.acceleration);
	*ret_deceleration = leconvert_uint32_from(response.deceleration);

	return ret;
}

int servo_v2_set_pulse_width(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t min, uint32_t max) {
	DevicePrivate *device_p = servo_v2->p;
	SetPulseWidth_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_PULSE_WIDTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.min = leconvert_uint32_to(min);
	request.max = leconvert_uint32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_pulse_width(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t *ret_min, uint32_t *ret_max) {
	DevicePrivate *device_p = servo_v2->p;
	GetPulseWidth_Request request;
	GetPulseWidth_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_PULSE_WIDTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_min = leconvert_uint32_from(response.min);
	*ret_max = leconvert_uint32_from(response.max);

	return ret;
}

int servo_v2_set_degree(ServoV2 *servo_v2, uint16_t servo_channel, int16_t min, int16_t max) {
	DevicePrivate *device_p = servo_v2->p;
	SetDegree_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_DEGREE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_degree(ServoV2 *servo_v2, uint16_t servo_channel, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = servo_v2->p;
	GetDegree_Request request;
	GetDegree_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_DEGREE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);

	return ret;
}

int servo_v2_set_period(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t period) {
	DevicePrivate *device_p = servo_v2->p;
	SetPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_period(ServoV2 *servo_v2, uint16_t servo_channel, uint32_t *ret_period) {
	DevicePrivate *device_p = servo_v2->p;
	GetPeriod_Request request;
	GetPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int servo_v2_get_servo_current(ServoV2 *servo_v2, uint16_t servo_channel, uint16_t *ret_current) {
	DevicePrivate *device_p = servo_v2->p;
	GetServoCurrent_Request request;
	GetServoCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_SERVO_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_uint16_from(response.current);

	return ret;
}

int servo_v2_set_servo_current_configuration(ServoV2 *servo_v2, uint16_t servo_channel, uint8_t averaging_duration) {
	DevicePrivate *device_p = servo_v2->p;
	SetServoCurrentConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_SERVO_CURRENT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.averaging_duration = averaging_duration;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_servo_current_configuration(ServoV2 *servo_v2, uint16_t servo_channel, uint8_t *ret_averaging_duration) {
	DevicePrivate *device_p = servo_v2->p;
	GetServoCurrentConfiguration_Request request;
	GetServoCurrentConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_SERVO_CURRENT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_averaging_duration = response.averaging_duration;

	return ret;
}

int servo_v2_set_input_voltage_configuration(ServoV2 *servo_v2, uint8_t averaging_duration) {
	DevicePrivate *device_p = servo_v2->p;
	SetInputVoltageConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_INPUT_VOLTAGE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.averaging_duration = averaging_duration;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_input_voltage_configuration(ServoV2 *servo_v2, uint8_t *ret_averaging_duration) {
	DevicePrivate *device_p = servo_v2->p;
	GetInputVoltageConfiguration_Request request;
	GetInputVoltageConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_INPUT_VOLTAGE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_averaging_duration = response.averaging_duration;

	return ret;
}

int servo_v2_get_overall_current(ServoV2 *servo_v2, uint16_t *ret_current) {
	DevicePrivate *device_p = servo_v2->p;
	GetOverallCurrent_Request request;
	GetOverallCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_OVERALL_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_uint16_from(response.current);

	return ret;
}

int servo_v2_get_input_voltage(ServoV2 *servo_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = servo_v2->p;
	GetInputVoltage_Request request;
	GetInputVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int servo_v2_set_current_calibration(ServoV2 *servo_v2, int16_t offset[10]) {
	DevicePrivate *device_p = servo_v2->p;
	SetCurrentCalibration_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_CURRENT_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 10; i++) request.offset[i] = leconvert_int16_to(offset[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_current_calibration(ServoV2 *servo_v2, int16_t ret_offset[10]) {
	DevicePrivate *device_p = servo_v2->p;
	GetCurrentCalibration_Request request;
	GetCurrentCalibration_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_CURRENT_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 10; i++) ret_offset[i] = leconvert_int16_from(response.offset[i]);

	return ret;
}

int servo_v2_set_position_reached_callback_configuration(ServoV2 *servo_v2, uint16_t servo_channel, bool enabled) {
	DevicePrivate *device_p = servo_v2->p;
	SetPositionReachedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_POSITION_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);
	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_position_reached_callback_configuration(ServoV2 *servo_v2, uint16_t servo_channel, bool *ret_enabled) {
	DevicePrivate *device_p = servo_v2->p;
	GetPositionReachedCallbackConfiguration_Request request;
	GetPositionReachedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_POSITION_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_channel = leconvert_uint16_to(servo_channel);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int servo_v2_get_spitfp_error_count(ServoV2 *servo_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = servo_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int servo_v2_set_bootloader_mode(ServoV2 *servo_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = servo_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int servo_v2_get_bootloader_mode(ServoV2 *servo_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = servo_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int servo_v2_set_write_firmware_pointer(ServoV2 *servo_v2, uint32_t pointer) {
	DevicePrivate *device_p = servo_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_write_firmware(ServoV2 *servo_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = servo_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int servo_v2_set_status_led_config(ServoV2 *servo_v2, uint8_t config) {
	DevicePrivate *device_p = servo_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_get_status_led_config(ServoV2 *servo_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = servo_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int servo_v2_get_chip_temperature(ServoV2 *servo_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = servo_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int servo_v2_reset(ServoV2 *servo_v2) {
	DevicePrivate *device_p = servo_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_write_uid(ServoV2 *servo_v2, uint32_t uid) {
	DevicePrivate *device_p = servo_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_v2_read_uid(ServoV2 *servo_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = servo_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int servo_v2_get_identity(ServoV2 *servo_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = servo_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SERVO_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
