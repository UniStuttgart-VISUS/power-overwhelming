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

#include "bricklet_motorized_linear_poti.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Position_CallbackFunction)(uint16_t position, void *user_data);

typedef void (*PositionReached_CallbackFunction)(uint16_t position, void *user_data);

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
} ATTRIBUTE_PACKED GetPosition_Request;

typedef struct {
	PacketHeader header;
	uint16_t position;
} ATTRIBUTE_PACKED GetPosition_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetPositionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetPositionCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t position;
} ATTRIBUTE_PACKED Position_Callback;

typedef struct {
	PacketHeader header;
	uint16_t position;
	uint8_t drive_mode;
	uint8_t hold_position;
} ATTRIBUTE_PACKED SetMotorPosition_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMotorPosition_Request;

typedef struct {
	PacketHeader header;
	uint16_t position;
	uint8_t drive_mode;
	uint8_t hold_position;
	uint8_t position_reached;
} ATTRIBUTE_PACKED GetMotorPosition_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Calibrate_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetPositionReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetPositionReachedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t position;
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

static void motorized_linear_poti_callback_wrapper_position(DevicePrivate *device_p, Packet *packet) {
	Position_CallbackFunction callback_function;
	void *user_data;
	Position_Callback *callback;

	if (packet->header.length != sizeof(Position_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Position_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MOTORIZED_LINEAR_POTI_CALLBACK_POSITION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MOTORIZED_LINEAR_POTI_CALLBACK_POSITION];
	callback = (Position_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_uint16_from(callback->position);

	callback_function(callback->position, user_data);
}

static void motorized_linear_poti_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReached_CallbackFunction callback_function;
	void *user_data;
	PositionReached_Callback *callback;

	if (packet->header.length != sizeof(PositionReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PositionReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MOTORIZED_LINEAR_POTI_CALLBACK_POSITION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MOTORIZED_LINEAR_POTI_CALLBACK_POSITION_REACHED];
	callback = (PositionReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_uint16_from(callback->position);

	callback_function(callback->position, user_data);
}

void motorized_linear_poti_create(MotorizedLinearPoti *motorized_linear_poti, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(motorized_linear_poti, uid, ipcon_p, 2, 0, 0, MOTORIZED_LINEAR_POTI_DEVICE_IDENTIFIER);

	device_p = motorized_linear_poti->p;

	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_MOTOR_POSITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_MOTOR_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_POSITION_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MOTORIZED_LINEAR_POTI_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[MOTORIZED_LINEAR_POTI_CALLBACK_POSITION] = motorized_linear_poti_callback_wrapper_position;
	device_p->callback_wrappers[MOTORIZED_LINEAR_POTI_CALLBACK_POSITION_REACHED] = motorized_linear_poti_callback_wrapper_position_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void motorized_linear_poti_destroy(MotorizedLinearPoti *motorized_linear_poti) {
	device_release(motorized_linear_poti->p);
}

int motorized_linear_poti_get_response_expected(MotorizedLinearPoti *motorized_linear_poti, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(motorized_linear_poti->p, function_id, ret_response_expected);
}

int motorized_linear_poti_set_response_expected(MotorizedLinearPoti *motorized_linear_poti, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(motorized_linear_poti->p, function_id, response_expected);
}

int motorized_linear_poti_set_response_expected_all(MotorizedLinearPoti *motorized_linear_poti, bool response_expected) {
	return device_set_response_expected_all(motorized_linear_poti->p, response_expected);
}

void motorized_linear_poti_register_callback(MotorizedLinearPoti *motorized_linear_poti, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(motorized_linear_poti->p, callback_id, function, user_data);
}

int motorized_linear_poti_get_api_version(MotorizedLinearPoti *motorized_linear_poti, uint8_t ret_api_version[3]) {
	return device_get_api_version(motorized_linear_poti->p, ret_api_version);
}

int motorized_linear_poti_get_position(MotorizedLinearPoti *motorized_linear_poti, uint16_t *ret_position) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetPosition_Request request;
	GetPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_uint16_from(response.position);

	return ret;
}

int motorized_linear_poti_set_position_callback_configuration(MotorizedLinearPoti *motorized_linear_poti, uint32_t period, bool value_has_to_change, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetPositionCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_POSITION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_get_position_callback_configuration(MotorizedLinearPoti *motorized_linear_poti, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetPositionCallbackConfiguration_Request request;
	GetPositionCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int motorized_linear_poti_set_motor_position(MotorizedLinearPoti *motorized_linear_poti, uint16_t position, uint8_t drive_mode, bool hold_position) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetMotorPosition_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_MOTOR_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position = leconvert_uint16_to(position);
	request.drive_mode = drive_mode;
	request.hold_position = hold_position ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_get_motor_position(MotorizedLinearPoti *motorized_linear_poti, uint16_t *ret_position, uint8_t *ret_drive_mode, bool *ret_hold_position, bool *ret_position_reached) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetMotorPosition_Request request;
	GetMotorPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_MOTOR_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_uint16_from(response.position);
	*ret_drive_mode = response.drive_mode;
	*ret_hold_position = response.hold_position != 0;
	*ret_position_reached = response.position_reached != 0;

	return ret;
}

int motorized_linear_poti_calibrate(MotorizedLinearPoti *motorized_linear_poti) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	Calibrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_set_position_reached_callback_configuration(MotorizedLinearPoti *motorized_linear_poti, bool enabled) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetPositionReachedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_POSITION_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_get_position_reached_callback_configuration(MotorizedLinearPoti *motorized_linear_poti, bool *ret_enabled) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetPositionReachedCallbackConfiguration_Request request;
	GetPositionReachedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_POSITION_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_get_spitfp_error_count(MotorizedLinearPoti *motorized_linear_poti, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_set_bootloader_mode(MotorizedLinearPoti *motorized_linear_poti, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_get_bootloader_mode(MotorizedLinearPoti *motorized_linear_poti, uint8_t *ret_mode) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_set_write_firmware_pointer(MotorizedLinearPoti *motorized_linear_poti, uint32_t pointer) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_write_firmware(MotorizedLinearPoti *motorized_linear_poti, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_set_status_led_config(MotorizedLinearPoti *motorized_linear_poti, uint8_t config) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_get_status_led_config(MotorizedLinearPoti *motorized_linear_poti, uint8_t *ret_config) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_get_chip_temperature(MotorizedLinearPoti *motorized_linear_poti, int16_t *ret_temperature) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_reset(MotorizedLinearPoti *motorized_linear_poti) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_write_uid(MotorizedLinearPoti *motorized_linear_poti, uint32_t uid) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int motorized_linear_poti_read_uid(MotorizedLinearPoti *motorized_linear_poti, uint32_t *ret_uid) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int motorized_linear_poti_get_identity(MotorizedLinearPoti *motorized_linear_poti, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = motorized_linear_poti->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MOTORIZED_LINEAR_POTI_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
