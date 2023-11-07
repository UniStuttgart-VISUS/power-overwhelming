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

#include "brick_servo.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*UnderVoltage_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*PositionReached_CallbackFunction)(uint8_t servo_num, int16_t position, void *user_data);

typedef void (*VelocityReached_CallbackFunction)(uint8_t servo_num, int16_t velocity, void *user_data);

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
	uint8_t servo_num;
} ATTRIBUTE_PACKED Enable_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED Disable_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED IsEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	int16_t position;
} ATTRIBUTE_PACKED SetPosition_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetPosition_Request;

typedef struct {
	PacketHeader header;
	int16_t position;
} ATTRIBUTE_PACKED GetPosition_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetCurrentPosition_Request;

typedef struct {
	PacketHeader header;
	int16_t position;
} ATTRIBUTE_PACKED GetCurrentPosition_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	uint16_t velocity;
} ATTRIBUTE_PACKED SetVelocity_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetVelocity_Request;

typedef struct {
	PacketHeader header;
	uint16_t velocity;
} ATTRIBUTE_PACKED GetVelocity_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetCurrentVelocity_Request;

typedef struct {
	PacketHeader header;
	uint16_t velocity;
} ATTRIBUTE_PACKED GetCurrentVelocity_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	uint16_t acceleration;
} ATTRIBUTE_PACKED SetAcceleration_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetAcceleration_Request;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
} ATTRIBUTE_PACKED GetAcceleration_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED SetOutputVoltage_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOutputVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetOutputVoltage_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetPulseWidth_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetPulseWidth_Request;

typedef struct {
	PacketHeader header;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetPulseWidth_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetDegree_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetDegree_Request;

typedef struct {
	PacketHeader header;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetDegree_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	uint16_t period;
} ATTRIBUTE_PACKED SetPeriod_Request;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetPeriod_Request;

typedef struct {
	PacketHeader header;
	uint16_t period;
} ATTRIBUTE_PACKED GetPeriod_Response;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
} ATTRIBUTE_PACKED GetServoCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetServoCurrent_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOverallCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetOverallCurrent_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackInputVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetStackInputVoltage_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetExternalInputVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetExternalInputVoltage_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED SetMinimumVoltage_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMinimumVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetMinimumVoltage_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED UnderVoltage_Callback;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	int16_t position;
} ATTRIBUTE_PACKED PositionReached_Callback;

typedef struct {
	PacketHeader header;
	uint8_t servo_num;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnablePositionReachedCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisablePositionReachedCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsPositionReachedCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsPositionReachedCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableVelocityReachedCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableVelocityReachedCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsVelocityReachedCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsVelocityReachedCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t communication_method;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t timeout_count;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
	uint32_t baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	char bricklet_port;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
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
} ATTRIBUTE_PACKED EnableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Response;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Request;

typedef struct {
	PacketHeader header;
	uint8_t protocol_version;
	uint8_t firmware_version[3];
	char name[40];
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Response;

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
	char port;
	uint8_t offset;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED WriteBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t offset;
} ATTRIBUTE_PACKED ReadBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED ReadBrickletPlugin_Response;

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

static void servo_callback_wrapper_under_voltage(DevicePrivate *device_p, Packet *packet) {
	UnderVoltage_CallbackFunction callback_function;
	void *user_data;
	UnderVoltage_Callback *callback;

	if (packet->header.length != sizeof(UnderVoltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UnderVoltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_UNDER_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_UNDER_VOLTAGE];
	callback = (UnderVoltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void servo_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReached_CallbackFunction callback_function;
	void *user_data;
	PositionReached_Callback *callback;

	if (packet->header.length != sizeof(PositionReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PositionReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_POSITION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_POSITION_REACHED];
	callback = (PositionReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_int16_from(callback->position);

	callback_function(callback->servo_num, callback->position, user_data);
}

static void servo_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReached_CallbackFunction callback_function;
	void *user_data;
	VelocityReached_Callback *callback;

	if (packet->header.length != sizeof(VelocityReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (VelocityReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_VELOCITY_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SERVO_CALLBACK_VELOCITY_REACHED];
	callback = (VelocityReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->servo_num, callback->velocity, user_data);
}

void servo_create(Servo *servo, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(servo, uid, ipcon_p, 2, 0, 4, SERVO_DEVICE_IDENTIFIER);

	device_p = servo->p;

	device_p->response_expected[SERVO_FUNCTION_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_DISABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_IS_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_POSITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_CURRENT_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_OUTPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_OUTPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_PULSE_WIDTH] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_PULSE_WIDTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_DEGREE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_DEGREE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_PERIOD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_SERVO_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_OVERALL_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_STACK_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_EXTERNAL_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_ENABLE_POSITION_REACHED_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_FUNCTION_DISABLE_POSITION_REACHED_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_FUNCTION_IS_POSITION_REACHED_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_ENABLE_VELOCITY_REACHED_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_FUNCTION_DISABLE_VELOCITY_REACHED_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SERVO_FUNCTION_IS_VELOCITY_REACHED_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_SEND_TIMEOUT_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_SET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_GET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_ENABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_DISABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_IS_STATUS_LED_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_WRITE_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SERVO_FUNCTION_READ_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SERVO_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SERVO_CALLBACK_UNDER_VOLTAGE] = servo_callback_wrapper_under_voltage;
	device_p->callback_wrappers[SERVO_CALLBACK_POSITION_REACHED] = servo_callback_wrapper_position_reached;
	device_p->callback_wrappers[SERVO_CALLBACK_VELOCITY_REACHED] = servo_callback_wrapper_velocity_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void servo_destroy(Servo *servo) {
	device_release(servo->p);
}

int servo_get_response_expected(Servo *servo, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(servo->p, function_id, ret_response_expected);
}

int servo_set_response_expected(Servo *servo, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(servo->p, function_id, response_expected);
}

int servo_set_response_expected_all(Servo *servo, bool response_expected) {
	return device_set_response_expected_all(servo->p, response_expected);
}

void servo_register_callback(Servo *servo, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(servo->p, callback_id, function, user_data);
}

int servo_get_api_version(Servo *servo, uint8_t ret_api_version[3]) {
	return device_get_api_version(servo->p, ret_api_version);
}

int servo_enable(Servo *servo, uint8_t servo_num) {
	DevicePrivate *device_p = servo->p;
	Enable_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_disable(Servo *servo, uint8_t servo_num) {
	DevicePrivate *device_p = servo->p;
	Disable_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_DISABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_is_enabled(Servo *servo, uint8_t servo_num, bool *ret_enabled) {
	DevicePrivate *device_p = servo->p;
	IsEnabled_Request request;
	IsEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_IS_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int servo_set_position(Servo *servo, uint8_t servo_num, int16_t position) {
	DevicePrivate *device_p = servo->p;
	SetPosition_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.position = leconvert_int16_to(position);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_position(Servo *servo, uint8_t servo_num, int16_t *ret_position) {
	DevicePrivate *device_p = servo->p;
	GetPosition_Request request;
	GetPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int16_from(response.position);

	return ret;
}

int servo_get_current_position(Servo *servo, uint8_t servo_num, int16_t *ret_position) {
	DevicePrivate *device_p = servo->p;
	GetCurrentPosition_Request request;
	GetCurrentPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_CURRENT_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int16_from(response.position);

	return ret;
}

int servo_set_velocity(Servo *servo, uint8_t servo_num, uint16_t velocity) {
	DevicePrivate *device_p = servo->p;
	SetVelocity_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.velocity = leconvert_uint16_to(velocity);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity) {
	DevicePrivate *device_p = servo->p;
	GetVelocity_Request request;
	GetVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint16_from(response.velocity);

	return ret;
}

int servo_get_current_velocity(Servo *servo, uint8_t servo_num, uint16_t *ret_velocity) {
	DevicePrivate *device_p = servo->p;
	GetCurrentVelocity_Request request;
	GetCurrentVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint16_from(response.velocity);

	return ret;
}

int servo_set_acceleration(Servo *servo, uint8_t servo_num, uint16_t acceleration) {
	DevicePrivate *device_p = servo->p;
	SetAcceleration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.acceleration = leconvert_uint16_to(acceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_acceleration(Servo *servo, uint8_t servo_num, uint16_t *ret_acceleration) {
	DevicePrivate *device_p = servo->p;
	GetAcceleration_Request request;
	GetAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_acceleration = leconvert_uint16_from(response.acceleration);

	return ret;
}

int servo_set_output_voltage(Servo *servo, uint16_t voltage) {
	DevicePrivate *device_p = servo->p;
	SetOutputVoltage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_OUTPUT_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_output_voltage(Servo *servo, uint16_t *ret_voltage) {
	DevicePrivate *device_p = servo->p;
	GetOutputVoltage_Request request;
	GetOutputVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_OUTPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int servo_set_pulse_width(Servo *servo, uint8_t servo_num, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = servo->p;
	SetPulseWidth_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_PULSE_WIDTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_pulse_width(Servo *servo, uint8_t servo_num, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = servo->p;
	GetPulseWidth_Request request;
	GetPulseWidth_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_PULSE_WIDTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int servo_set_degree(Servo *servo, uint8_t servo_num, int16_t min, int16_t max) {
	DevicePrivate *device_p = servo->p;
	SetDegree_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_DEGREE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.min = leconvert_int16_to(min);
	request.max = leconvert_int16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_degree(Servo *servo, uint8_t servo_num, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = servo->p;
	GetDegree_Request request;
	GetDegree_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_DEGREE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_min = leconvert_int16_from(response.min);
	*ret_max = leconvert_int16_from(response.max);

	return ret;
}

int servo_set_period(Servo *servo, uint8_t servo_num, uint16_t period) {
	DevicePrivate *device_p = servo->p;
	SetPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;
	request.period = leconvert_uint16_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_period(Servo *servo, uint8_t servo_num, uint16_t *ret_period) {
	DevicePrivate *device_p = servo->p;
	GetPeriod_Request request;
	GetPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint16_from(response.period);

	return ret;
}

int servo_get_servo_current(Servo *servo, uint8_t servo_num, uint16_t *ret_current) {
	DevicePrivate *device_p = servo->p;
	GetServoCurrent_Request request;
	GetServoCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_SERVO_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.servo_num = servo_num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_uint16_from(response.current);

	return ret;
}

int servo_get_overall_current(Servo *servo, uint16_t *ret_current) {
	DevicePrivate *device_p = servo->p;
	GetOverallCurrent_Request request;
	GetOverallCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_OVERALL_CURRENT, device_p->ipcon_p, device_p);

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

int servo_get_stack_input_voltage(Servo *servo, uint16_t *ret_voltage) {
	DevicePrivate *device_p = servo->p;
	GetStackInputVoltage_Request request;
	GetStackInputVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_STACK_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int servo_get_external_input_voltage(Servo *servo, uint16_t *ret_voltage) {
	DevicePrivate *device_p = servo->p;
	GetExternalInputVoltage_Request request;
	GetExternalInputVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_EXTERNAL_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int servo_set_minimum_voltage(Servo *servo, uint16_t voltage) {
	DevicePrivate *device_p = servo->p;
	SetMinimumVoltage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_minimum_voltage(Servo *servo, uint16_t *ret_voltage) {
	DevicePrivate *device_p = servo->p;
	GetMinimumVoltage_Request request;
	GetMinimumVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

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

int servo_enable_position_reached_callback(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	EnablePositionReachedCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_ENABLE_POSITION_REACHED_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_disable_position_reached_callback(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	DisablePositionReachedCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_DISABLE_POSITION_REACHED_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_is_position_reached_callback_enabled(Servo *servo, bool *ret_enabled) {
	DevicePrivate *device_p = servo->p;
	IsPositionReachedCallbackEnabled_Request request;
	IsPositionReachedCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_IS_POSITION_REACHED_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int servo_enable_velocity_reached_callback(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	EnableVelocityReachedCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_ENABLE_VELOCITY_REACHED_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_disable_velocity_reached_callback(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	DisableVelocityReachedCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_DISABLE_VELOCITY_REACHED_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_is_velocity_reached_callback_enabled(Servo *servo, bool *ret_enabled) {
	DevicePrivate *device_p = servo->p;
	IsVelocityReachedCallbackEnabled_Request request;
	IsVelocityReachedCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_IS_VELOCITY_REACHED_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int servo_set_spitfp_baudrate_config(Servo *servo, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate) {
	DevicePrivate *device_p = servo->p;
	SetSPITFPBaudrateConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_dynamic_baudrate = enable_dynamic_baudrate ? 1 : 0;
	request.minimum_dynamic_baudrate = leconvert_uint32_to(minimum_dynamic_baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_spitfp_baudrate_config(Servo *servo, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate) {
	DevicePrivate *device_p = servo->p;
	GetSPITFPBaudrateConfig_Request request;
	GetSPITFPBaudrateConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_dynamic_baudrate = response.enable_dynamic_baudrate != 0;
	*ret_minimum_dynamic_baudrate = leconvert_uint32_from(response.minimum_dynamic_baudrate);

	return ret;
}

int servo_get_send_timeout_count(Servo *servo, uint8_t communication_method, uint32_t *ret_timeout_count) {
	DevicePrivate *device_p = servo->p;
	GetSendTimeoutCount_Request request;
	GetSendTimeoutCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_SEND_TIMEOUT_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.communication_method = communication_method;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timeout_count = leconvert_uint32_from(response.timeout_count);

	return ret;
}

int servo_set_spitfp_baudrate(Servo *servo, char bricklet_port, uint32_t baudrate) {
	DevicePrivate *device_p = servo->p;
	SetSPITFPBaudrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_SET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;
	request.baudrate = leconvert_uint32_to(baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_get_spitfp_baudrate(Servo *servo, char bricklet_port, uint32_t *ret_baudrate) {
	DevicePrivate *device_p = servo->p;
	GetSPITFPBaudrate_Request request;
	GetSPITFPBaudrate_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baudrate = leconvert_uint32_from(response.baudrate);

	return ret;
}

int servo_get_spitfp_error_count(Servo *servo, char bricklet_port, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = servo->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

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

int servo_enable_status_led(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	EnableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_ENABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_disable_status_led(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	DisableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_DISABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_is_status_led_enabled(Servo *servo, bool *ret_enabled) {
	DevicePrivate *device_p = servo->p;
	IsStatusLEDEnabled_Request request;
	IsStatusLEDEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_IS_STATUS_LED_ENABLED, device_p->ipcon_p, device_p);

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

int servo_get_protocol1_bricklet_name(Servo *servo, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = servo->p;
	GetProtocol1BrickletName_Request request;
	GetProtocol1BrickletName_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_protocol_version = response.protocol_version;
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	memcpy(ret_name, response.name, 40);

	return ret;
}

int servo_get_chip_temperature(Servo *servo, int16_t *ret_temperature) {
	DevicePrivate *device_p = servo->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int servo_reset(Servo *servo) {
	DevicePrivate *device_p = servo->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_write_bricklet_plugin(Servo *servo, char port, uint8_t offset, uint8_t chunk[32]) {
	DevicePrivate *device_p = servo->p;
	WriteBrickletPlugin_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_WRITE_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;
	memcpy(request.chunk, chunk, 32 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int servo_read_bricklet_plugin(Servo *servo, char port, uint8_t offset, uint8_t ret_chunk[32]) {
	DevicePrivate *device_p = servo->p;
	ReadBrickletPlugin_Request request;
	ReadBrickletPlugin_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_READ_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_chunk, response.chunk, 32 * sizeof(uint8_t));

	return ret;
}

int servo_get_identity(Servo *servo, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = servo->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SERVO_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
