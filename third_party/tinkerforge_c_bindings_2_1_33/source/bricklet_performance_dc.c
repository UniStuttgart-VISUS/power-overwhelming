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

#include "bricklet_performance_dc.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*EmergencyShutdown_CallbackFunction)(void *user_data);

typedef void (*VelocityReached_CallbackFunction)(int16_t velocity, void *user_data);

typedef void (*CurrentVelocity_CallbackFunction)(int16_t velocity, void *user_data);

typedef void (*GPIOState_CallbackFunction)(bool gpio_state[2], void *user_data);

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
	int16_t temperature;
} ATTRIBUTE_PACKED GetPowerStatistics_Response;

typedef struct {
	PacketHeader header;
	uint8_t temperature;
} ATTRIBUTE_PACKED SetThermalShutdown_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetThermalShutdown_Request;

typedef struct {
	PacketHeader header;
	uint8_t temperature;
} ATTRIBUTE_PACKED GetThermalShutdown_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint16_t debounce;
	uint16_t stop_deceleration;
} ATTRIBUTE_PACKED SetGPIOConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetGPIOConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t debounce;
	uint16_t stop_deceleration;
} ATTRIBUTE_PACKED GetGPIOConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint32_t action;
} ATTRIBUTE_PACKED SetGPIOAction_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetGPIOAction_Request;

typedef struct {
	PacketHeader header;
	uint32_t action;
} ATTRIBUTE_PACKED GetGPIOAction_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGPIOState_Request;

typedef struct {
	PacketHeader header;
	uint8_t gpio_state[1];
} ATTRIBUTE_PACKED GetGPIOState_Response;

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
	uint8_t config;
} ATTRIBUTE_PACKED SetCWLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCWLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetCWLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetCCWLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCCWLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetCCWLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t config;
} ATTRIBUTE_PACKED SetGPIOLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetGPIOLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetGPIOLEDConfig_Response;

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
	uint8_t gpio_state[1];
} ATTRIBUTE_PACKED GPIOState_Callback;

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

static void performance_dc_callback_wrapper_emergency_shutdown(DevicePrivate *device_p, Packet *packet) {
	EmergencyShutdown_CallbackFunction callback_function;
	void *user_data;
	EmergencyShutdown_Callback *callback;

	if (packet->header.length != sizeof(EmergencyShutdown_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (EmergencyShutdown_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_EMERGENCY_SHUTDOWN];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_EMERGENCY_SHUTDOWN];
	callback = (EmergencyShutdown_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void performance_dc_callback_wrapper_velocity_reached(DevicePrivate *device_p, Packet *packet) {
	VelocityReached_CallbackFunction callback_function;
	void *user_data;
	VelocityReached_Callback *callback;

	if (packet->header.length != sizeof(VelocityReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (VelocityReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED];
	callback = (VelocityReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void performance_dc_callback_wrapper_current_velocity(DevicePrivate *device_p, Packet *packet) {
	CurrentVelocity_CallbackFunction callback_function;
	void *user_data;
	CurrentVelocity_Callback *callback;

	if (packet->header.length != sizeof(CurrentVelocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CurrentVelocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY];
	callback = (CurrentVelocity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->velocity = leconvert_int16_from(callback->velocity);

	callback_function(callback->velocity, user_data);
}

static void performance_dc_callback_wrapper_gpio_state(DevicePrivate *device_p, Packet *packet) {
	GPIOState_CallbackFunction callback_function;
	void *user_data;
	GPIOState_Callback *callback;
	int i;
	bool unpacked_gpio_state[2];

	if (packet->header.length != sizeof(GPIOState_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GPIOState_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_GPIO_STATE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PERFORMANCE_DC_CALLBACK_GPIO_STATE];
	callback = (GPIOState_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	for (i = 0; i < 2; i++) unpacked_gpio_state[i] = (callback->gpio_state[i / 8] & (1 << (i % 8))) != 0;

	callback_function(unpacked_gpio_state, user_data);
}

void performance_dc_create(PerformanceDC *performance_dc, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(performance_dc, uid, ipcon_p, 2, 0, 1, PERFORMANCE_DC_DEVICE_IDENTIFIER);

	device_p = performance_dc->p;

	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_ENABLED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_MOTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_MOTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_FULL_BRAKE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_DRIVE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_PWM_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_POWER_STATISTICS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_THERMAL_SHUTDOWN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_THERMAL_SHUTDOWN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_GPIO_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_GPIO_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_GPIO_ACTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_GPIO_ACTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_GPIO_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_CW_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_CW_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_CCW_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_CCW_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_GPIO_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_GPIO_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PERFORMANCE_DC_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PERFORMANCE_DC_CALLBACK_EMERGENCY_SHUTDOWN] = performance_dc_callback_wrapper_emergency_shutdown;
	device_p->callback_wrappers[PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED] = performance_dc_callback_wrapper_velocity_reached;
	device_p->callback_wrappers[PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY] = performance_dc_callback_wrapper_current_velocity;
	device_p->callback_wrappers[PERFORMANCE_DC_CALLBACK_GPIO_STATE] = performance_dc_callback_wrapper_gpio_state;

	ipcon_add_device(ipcon_p, device_p);
}

void performance_dc_destroy(PerformanceDC *performance_dc) {
	device_release(performance_dc->p);
}

int performance_dc_get_response_expected(PerformanceDC *performance_dc, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(performance_dc->p, function_id, ret_response_expected);
}

int performance_dc_set_response_expected(PerformanceDC *performance_dc, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(performance_dc->p, function_id, response_expected);
}

int performance_dc_set_response_expected_all(PerformanceDC *performance_dc, bool response_expected) {
	return device_set_response_expected_all(performance_dc->p, response_expected);
}

void performance_dc_register_callback(PerformanceDC *performance_dc, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(performance_dc->p, callback_id, function, user_data);
}

int performance_dc_get_api_version(PerformanceDC *performance_dc, uint8_t ret_api_version[3]) {
	return device_get_api_version(performance_dc->p, ret_api_version);
}

int performance_dc_set_enabled(PerformanceDC *performance_dc, bool enabled) {
	DevicePrivate *device_p = performance_dc->p;
	SetEnabled_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_enabled(PerformanceDC *performance_dc, bool *ret_enabled) {
	DevicePrivate *device_p = performance_dc->p;
	GetEnabled_Request request;
	GetEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_ENABLED, device_p->ipcon_p, device_p);

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

int performance_dc_set_velocity(PerformanceDC *performance_dc, int16_t velocity) {
	DevicePrivate *device_p = performance_dc->p;
	SetVelocity_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.velocity = leconvert_int16_to(velocity);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_velocity(PerformanceDC *performance_dc, int16_t *ret_velocity) {
	DevicePrivate *device_p = performance_dc->p;
	GetVelocity_Request request;
	GetVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_VELOCITY, device_p->ipcon_p, device_p);

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

int performance_dc_get_current_velocity(PerformanceDC *performance_dc, int16_t *ret_velocity) {
	DevicePrivate *device_p = performance_dc->p;
	GetCurrentVelocity_Request request;
	GetCurrentVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

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

int performance_dc_set_motion(PerformanceDC *performance_dc, uint16_t acceleration, uint16_t deceleration) {
	DevicePrivate *device_p = performance_dc->p;
	SetMotion_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_MOTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.acceleration = leconvert_uint16_to(acceleration);
	request.deceleration = leconvert_uint16_to(deceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_motion(PerformanceDC *performance_dc, uint16_t *ret_acceleration, uint16_t *ret_deceleration) {
	DevicePrivate *device_p = performance_dc->p;
	GetMotion_Request request;
	GetMotion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_MOTION, device_p->ipcon_p, device_p);

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

int performance_dc_full_brake(PerformanceDC *performance_dc) {
	DevicePrivate *device_p = performance_dc->p;
	FullBrake_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_FULL_BRAKE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_set_drive_mode(PerformanceDC *performance_dc, uint8_t mode) {
	DevicePrivate *device_p = performance_dc->p;
	SetDriveMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_DRIVE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_drive_mode(PerformanceDC *performance_dc, uint8_t *ret_mode) {
	DevicePrivate *device_p = performance_dc->p;
	GetDriveMode_Request request;
	GetDriveMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_DRIVE_MODE, device_p->ipcon_p, device_p);

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

int performance_dc_set_pwm_frequency(PerformanceDC *performance_dc, uint16_t frequency) {
	DevicePrivate *device_p = performance_dc->p;
	SetPWMFrequency_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = leconvert_uint16_to(frequency);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_pwm_frequency(PerformanceDC *performance_dc, uint16_t *ret_frequency) {
	DevicePrivate *device_p = performance_dc->p;
	GetPWMFrequency_Request request;
	GetPWMFrequency_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_PWM_FREQUENCY, device_p->ipcon_p, device_p);

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

int performance_dc_get_power_statistics(PerformanceDC *performance_dc, uint16_t *ret_voltage, uint16_t *ret_current, int16_t *ret_temperature) {
	DevicePrivate *device_p = performance_dc->p;
	GetPowerStatistics_Request request;
	GetPowerStatistics_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_POWER_STATISTICS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_uint16_from(response.voltage);
	*ret_current = leconvert_uint16_from(response.current);
	*ret_temperature = leconvert_int16_from(response.temperature);

	return ret;
}

int performance_dc_set_thermal_shutdown(PerformanceDC *performance_dc, uint8_t temperature) {
	DevicePrivate *device_p = performance_dc->p;
	SetThermalShutdown_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_THERMAL_SHUTDOWN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.temperature = temperature;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_thermal_shutdown(PerformanceDC *performance_dc, uint8_t *ret_temperature) {
	DevicePrivate *device_p = performance_dc->p;
	GetThermalShutdown_Request request;
	GetThermalShutdown_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_THERMAL_SHUTDOWN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = response.temperature;

	return ret;
}

int performance_dc_set_gpio_configuration(PerformanceDC *performance_dc, uint8_t channel, uint16_t debounce, uint16_t stop_deceleration) {
	DevicePrivate *device_p = performance_dc->p;
	SetGPIOConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_GPIO_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.debounce = leconvert_uint16_to(debounce);
	request.stop_deceleration = leconvert_uint16_to(stop_deceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_gpio_configuration(PerformanceDC *performance_dc, uint8_t channel, uint16_t *ret_debounce, uint16_t *ret_stop_deceleration) {
	DevicePrivate *device_p = performance_dc->p;
	GetGPIOConfiguration_Request request;
	GetGPIOConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_GPIO_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_debounce = leconvert_uint16_from(response.debounce);
	*ret_stop_deceleration = leconvert_uint16_from(response.stop_deceleration);

	return ret;
}

int performance_dc_set_gpio_action(PerformanceDC *performance_dc, uint8_t channel, uint32_t action) {
	DevicePrivate *device_p = performance_dc->p;
	SetGPIOAction_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_GPIO_ACTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.action = leconvert_uint32_to(action);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_gpio_action(PerformanceDC *performance_dc, uint8_t channel, uint32_t *ret_action) {
	DevicePrivate *device_p = performance_dc->p;
	GetGPIOAction_Request request;
	GetGPIOAction_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_GPIO_ACTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_action = leconvert_uint32_from(response.action);

	return ret;
}

int performance_dc_get_gpio_state(PerformanceDC *performance_dc, bool ret_gpio_state[2]) {
	DevicePrivate *device_p = performance_dc->p;
	GetGPIOState_Request request;
	GetGPIOState_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_GPIO_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 2; i++) ret_gpio_state[i] = (response.gpio_state[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int performance_dc_set_error_led_config(PerformanceDC *performance_dc, uint8_t config) {
	DevicePrivate *device_p = performance_dc->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_error_led_config(PerformanceDC *performance_dc, uint8_t *ret_config) {
	DevicePrivate *device_p = performance_dc->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int performance_dc_set_cw_led_config(PerformanceDC *performance_dc, uint8_t config) {
	DevicePrivate *device_p = performance_dc->p;
	SetCWLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_CW_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_cw_led_config(PerformanceDC *performance_dc, uint8_t *ret_config) {
	DevicePrivate *device_p = performance_dc->p;
	GetCWLEDConfig_Request request;
	GetCWLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_CW_LED_CONFIG, device_p->ipcon_p, device_p);

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

int performance_dc_set_ccw_led_config(PerformanceDC *performance_dc, uint8_t config) {
	DevicePrivate *device_p = performance_dc->p;
	SetCCWLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_CCW_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_ccw_led_config(PerformanceDC *performance_dc, uint8_t *ret_config) {
	DevicePrivate *device_p = performance_dc->p;
	GetCCWLEDConfig_Request request;
	GetCCWLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_CCW_LED_CONFIG, device_p->ipcon_p, device_p);

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

int performance_dc_set_gpio_led_config(PerformanceDC *performance_dc, uint8_t channel, uint8_t config) {
	DevicePrivate *device_p = performance_dc->p;
	SetGPIOLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_GPIO_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_gpio_led_config(PerformanceDC *performance_dc, uint8_t channel, uint8_t *ret_config) {
	DevicePrivate *device_p = performance_dc->p;
	GetGPIOLEDConfig_Request request;
	GetGPIOLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_GPIO_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int performance_dc_set_emergency_shutdown_callback_configuration(PerformanceDC *performance_dc, bool enabled) {
	DevicePrivate *device_p = performance_dc->p;
	SetEmergencyShutdownCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_emergency_shutdown_callback_configuration(PerformanceDC *performance_dc, bool *ret_enabled) {
	DevicePrivate *device_p = performance_dc->p;
	GetEmergencyShutdownCallbackConfiguration_Request request;
	GetEmergencyShutdownCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int performance_dc_set_velocity_reached_callback_configuration(PerformanceDC *performance_dc, bool enabled) {
	DevicePrivate *device_p = performance_dc->p;
	SetVelocityReachedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_velocity_reached_callback_configuration(PerformanceDC *performance_dc, bool *ret_enabled) {
	DevicePrivate *device_p = performance_dc->p;
	GetVelocityReachedCallbackConfiguration_Request request;
	GetVelocityReachedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int performance_dc_set_current_velocity_callback_configuration(PerformanceDC *performance_dc, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = performance_dc->p;
	SetCurrentVelocityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_current_velocity_callback_configuration(PerformanceDC *performance_dc, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = performance_dc->p;
	GetCurrentVelocityCallbackConfiguration_Request request;
	GetCurrentVelocityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int performance_dc_get_spitfp_error_count(PerformanceDC *performance_dc, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = performance_dc->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int performance_dc_set_bootloader_mode(PerformanceDC *performance_dc, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = performance_dc->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int performance_dc_get_bootloader_mode(PerformanceDC *performance_dc, uint8_t *ret_mode) {
	DevicePrivate *device_p = performance_dc->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int performance_dc_set_write_firmware_pointer(PerformanceDC *performance_dc, uint32_t pointer) {
	DevicePrivate *device_p = performance_dc->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_write_firmware(PerformanceDC *performance_dc, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = performance_dc->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int performance_dc_set_status_led_config(PerformanceDC *performance_dc, uint8_t config) {
	DevicePrivate *device_p = performance_dc->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_get_status_led_config(PerformanceDC *performance_dc, uint8_t *ret_config) {
	DevicePrivate *device_p = performance_dc->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int performance_dc_get_chip_temperature(PerformanceDC *performance_dc, int16_t *ret_temperature) {
	DevicePrivate *device_p = performance_dc->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int performance_dc_reset(PerformanceDC *performance_dc) {
	DevicePrivate *device_p = performance_dc->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_write_uid(PerformanceDC *performance_dc, uint32_t uid) {
	DevicePrivate *device_p = performance_dc->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int performance_dc_read_uid(PerformanceDC *performance_dc, uint32_t *ret_uid) {
	DevicePrivate *device_p = performance_dc->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int performance_dc_get_identity(PerformanceDC *performance_dc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = performance_dc->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PERFORMANCE_DC_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
