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

#include "bricklet_dc_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*EmergencyShutdown_CallbackFunction)(void *user_data);

typedef void (*VelocityReached_CallbackFunction)(int16_t velocity, void *user_data);

typedef void (*CurrentVelocity_CallbackFunction)(int16_t velocity, void *user_data);

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
	uint8_t enabled;
} ATTRIBUTE_PACKED SetEnabled_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetEnabled_Response;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED SetVelocity_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocity_Request;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetVelocity_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentVelocity_Request;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED GetCurrentVelocity_Response;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
	uint16_t deceleration;
} ATTRIBUTE_PACKED SetMotion_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMotion_Request;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
	uint16_t deceleration;
} ATTRIBUTE_PACKED GetMotion_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED FullBrake_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetDriveMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDriveMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetDriveMode_Response;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
} ATTRIBUTE_PACKED SetPWMFrequency_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPWMFrequency_Request;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
} ATTRIBUTE_PACKED GetPWMFrequency_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPowerStatistics_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
	uint16_t current;
} ATTRIBUTE_PACKED GetPowerStatistics_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetEmergencyShutdownCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEmergencyShutdownCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetEmergencyShutdownCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetVelocityReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVelocityReachedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetVelocityReachedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetCurrentVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetCurrentVelocityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EmergencyShutdown_Callback;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED VelocityReached_Callback;

typedef struct {
	PacketHeader header;
	int16_t velocity;
} ATTRIBUTE_PACKED CurrentVelocity_Callback;

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

static void dc_v2_callback_wrapper_emergency_shutdown(DevicePrivate *device_p, Packet *packet) {
	EmergencyShutdown_CallbackFunction callback_function;
	void *user_data;
	EmergencyShutdown_Callback *callback;

	if (packet->header.length != sizeof(EmergencyShutdown_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (EmergencyShutdown_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_EMERGENCY_SHUTDOWN];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_EMERGENCY_SHUTDOWN];
	callback = (EmergencyShutdown_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void dc_v2_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReached_CallbackFunction callback_function;
	void *user_data;
	VelocityReached_Callback *callback;

	if (packet->header.length != sizeof(VelocityReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (VelocityReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_VELOCITY_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_VELOCITY_REACHED];
	callback = (VelocityReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void dc_v2_callback_wrapper_current_velocity(DevicePrivate *device_p, Packet *packet) {
	CurrentVelocity_CallbackFunction callback_function;
	void *user_data;
	CurrentVelocity_Callback *callback;

	if (packet->header.length != sizeof(CurrentVelocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CurrentVelocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_CURRENT_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DC_V2_CALLBACK_CURRENT_VELOCITY];
	callback = (CurrentVelocity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

void dc_v2_create(DCV2 *dc_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(dc_v2, uid, ipcon_p, 2, 0, 0, DC_V2_DEVICE_IDENTIFIER);

	device_p = dc_v2->p;

	device_p->response_expected[DC_V2_FUNCTION_SET_ENABLED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_MOTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_MOTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_FULL_BRAKE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_SET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_POWER_STATISTICS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DC_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DC_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DC_V2_CALLBACK_EMERGENCY_SHUTDOWN] = dc_v2_callback_wrapper_emergency_shutdown;
	device_p->callback_wrappers[DC_V2_CALLBACK_VELOCITY_REACHED] = dc_v2_callback_wrapper_velocity_reached;
	device_p->callback_wrappers[DC_V2_CALLBACK_CURRENT_VELOCITY] = dc_v2_callback_wrapper_current_velocity;

	ipcon_add_device(ipcon_p, device_p);
}

void dc_v2_destroy(DCV2 *dc_v2) {
	device_release(dc_v2->p);
}

int dc_v2_get_response_expected(DCV2 *dc_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dc_v2->p, function_id, ret_response_expected);
}

int dc_v2_set_response_expected(DCV2 *dc_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dc_v2->p, function_id, response_expected);
}

int dc_v2_set_response_expected_all(DCV2 *dc_v2, bool response_expected) {
	return device_set_response_expected_all(dc_v2->p, response_expected);
}

void dc_v2_register_callback(DCV2 *dc_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(dc_v2->p, callback_id, function, user_data);
}

int dc_v2_get_api_version(DCV2 *dc_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(dc_v2->p, ret_api_version);
}

int dc_v2_set_enabled(DCV2 *dc_v2, bool enabled) {
	DevicePrivate *device_p = dc_v2->p;
	SetEnabled_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_enabled(DCV2 *dc_v2, bool *ret_enabled) {
	DevicePrivate *device_p = dc_v2->p;
	GetEnabled_Request request;
	GetEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_ENABLED, device_p->ipcon_p, device_p);

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

int dc_v2_set_velocity(DCV2 *dc_v2, int16_t velocity) {
	DevicePrivate *device_p = dc_v2->p;
	SetVelocity_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.velocity = leconvert_int16_to(velocity);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_velocity(DCV2 *dc_v2, int16_t *ret_velocity) {
	DevicePrivate *device_p = dc_v2->p;
	GetVelocity_Request request;
	GetVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

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

int dc_v2_get_current_velocity(DCV2 *dc_v2, int16_t *ret_velocity) {
	DevicePrivate *device_p = dc_v2->p;
	GetCurrentVelocity_Request request;
	GetCurrentVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

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

int dc_v2_set_motion(DCV2 *dc_v2, uint16_t acceleration, uint16_t deceleration) {
	DevicePrivate *device_p = dc_v2->p;
	SetMotion_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_MOTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.acceleration = leconvert_uint16_to(acceleration);
	request.deceleration = leconvert_uint16_to(deceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_motion(DCV2 *dc_v2, uint16_t *ret_acceleration, uint16_t *ret_deceleration) {
	DevicePrivate *device_p = dc_v2->p;
	GetMotion_Request request;
	GetMotion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_MOTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_acceleration = leconvert_uint16_from(response.acceleration);
	*ret_deceleration = leconvert_uint16_from(response.deceleration);

	return ret;
}

int dc_v2_full_brake(DCV2 *dc_v2) {
	DevicePrivate *device_p = dc_v2->p;
	FullBrake_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_FULL_BRAKE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_set_drive_mode(DCV2 *dc_v2, uint8_t mode) {
	DevicePrivate *device_p = dc_v2->p;
	SetDriveMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_DRIVE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_drive_mode(DCV2 *dc_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = dc_v2->p;
	GetDriveMode_Request request;
	GetDriveMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_DRIVE_MODE, device_p->ipcon_p, device_p);

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

int dc_v2_set_pwm_frequency(DCV2 *dc_v2, uint16_t frequency) {
	DevicePrivate *device_p = dc_v2->p;
	SetPWMFrequency_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = leconvert_uint16_to(frequency);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_pwm_frequency(DCV2 *dc_v2, uint16_t *ret_frequency) {
	DevicePrivate *device_p = dc_v2->p;
	GetPWMFrequency_Request request;
	GetPWMFrequency_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frequency = leconvert_uint16_from(response.frequency);

	return ret;
}

int dc_v2_get_power_statistics(DCV2 *dc_v2, uint16_t *ret_voltage, uint16_t *ret_current) {
	DevicePrivate *device_p = dc_v2->p;
	GetPowerStatistics_Request request;
	GetPowerStatistics_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_POWER_STATISTICS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_uint16_from(response.voltage);
	*ret_current = leconvert_uint16_from(response.current);

	return ret;
}

int dc_v2_set_error_led_config(DCV2 *dc_v2, uint8_t config) {
	DevicePrivate *device_p = dc_v2->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_error_led_config(DCV2 *dc_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = dc_v2->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dc_v2_set_emergency_shutdown_callback_configuration(DCV2 *dc_v2, bool enabled) {
	DevicePrivate *device_p = dc_v2->p;
	SetEmergencyShutdownCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_emergency_shutdown_callback_configuration(DCV2 *dc_v2, bool *ret_enabled) {
	DevicePrivate *device_p = dc_v2->p;
	GetEmergencyShutdownCallbackConfiguration_Request request;
	GetEmergencyShutdownCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int dc_v2_set_velocity_reached_callback_configuration(DCV2 *dc_v2, bool enabled) {
	DevicePrivate *device_p = dc_v2->p;
	SetVelocityReachedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_velocity_reached_callback_configuration(DCV2 *dc_v2, bool *ret_enabled) {
	DevicePrivate *device_p = dc_v2->p;
	GetVelocityReachedCallbackConfiguration_Request request;
	GetVelocityReachedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int dc_v2_set_current_velocity_callback_configuration(DCV2 *dc_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = dc_v2->p;
	SetCurrentVelocityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_current_velocity_callback_configuration(DCV2 *dc_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = dc_v2->p;
	GetCurrentVelocityCallbackConfiguration_Request request;
	GetCurrentVelocityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int dc_v2_get_spitfp_error_count(DCV2 *dc_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = dc_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int dc_v2_set_bootloader_mode(DCV2 *dc_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = dc_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dc_v2_get_bootloader_mode(DCV2 *dc_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = dc_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dc_v2_set_write_firmware_pointer(DCV2 *dc_v2, uint32_t pointer) {
	DevicePrivate *device_p = dc_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_write_firmware(DCV2 *dc_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = dc_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int dc_v2_set_status_led_config(DCV2 *dc_v2, uint8_t config) {
	DevicePrivate *device_p = dc_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_get_status_led_config(DCV2 *dc_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = dc_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dc_v2_get_chip_temperature(DCV2 *dc_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = dc_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int dc_v2_reset(DCV2 *dc_v2) {
	DevicePrivate *device_p = dc_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_write_uid(DCV2 *dc_v2, uint32_t uid) {
	DevicePrivate *device_p = dc_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dc_v2_read_uid(DCV2 *dc_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = dc_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int dc_v2_get_identity(DCV2 *dc_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dc_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DC_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
