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

#include "bricklet_silent_stepper_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*UnderVoltage_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*PositionReached_CallbackFunction)(int32_t position, void *user_data);

typedef void (*AllData_CallbackFunction)(uint16_t current_velocity, int32_t current_position, int32_t remaining_steps, uint16_t input_voltage, uint16_t current_consumption, void *user_data);

typedef void (*NewState_CallbackFunction)(uint8_t state_new, uint8_t state_previous, void *user_data);

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
	uint16_t velocity;
} ATTRIBUTE_PACKED SetMaxVelocity_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMaxVelocity_Request;

typedef struct {
	PacketHeader header;
	uint16_t velocity;
} ATTRIBUTE_PACKED GetMaxVelocity_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentVelocity_Request;

typedef struct {
	PacketHeader header;
	uint16_t velocity;
} ATTRIBUTE_PACKED GetCurrentVelocity_Response;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
	uint16_t deacceleration;
} ATTRIBUTE_PACKED SetSpeedRamping_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSpeedRamping_Request;

typedef struct {
	PacketHeader header;
	uint16_t acceleration;
	uint16_t deacceleration;
} ATTRIBUTE_PACKED GetSpeedRamping_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED FullBrake_Request;

typedef struct {
	PacketHeader header;
	int32_t position;
} ATTRIBUTE_PACKED SetCurrentPosition_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentPosition_Request;

typedef struct {
	PacketHeader header;
	int32_t position;
} ATTRIBUTE_PACKED GetCurrentPosition_Response;

typedef struct {
	PacketHeader header;
	int32_t position;
} ATTRIBUTE_PACKED SetTargetPosition_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTargetPosition_Request;

typedef struct {
	PacketHeader header;
	int32_t position;
} ATTRIBUTE_PACKED GetTargetPosition_Response;

typedef struct {
	PacketHeader header;
	int32_t steps;
} ATTRIBUTE_PACKED SetSteps_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSteps_Request;

typedef struct {
	PacketHeader header;
	int32_t steps;
} ATTRIBUTE_PACKED GetSteps_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRemainingSteps_Request;

typedef struct {
	PacketHeader header;
	int32_t steps;
} ATTRIBUTE_PACKED GetRemainingSteps_Response;

typedef struct {
	PacketHeader header;
	uint8_t step_resolution;
	uint8_t interpolation;
} ATTRIBUTE_PACKED SetStepConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStepConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t step_resolution;
	uint8_t interpolation;
} ATTRIBUTE_PACKED GetStepConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DriveForward_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DriveBackward_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Stop_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInputVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetInputVoltage_Response;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED SetMotorCurrent_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMotorCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetMotorCurrent_Response;

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
	uint16_t standstill_current;
	uint16_t motor_run_current;
	uint16_t standstill_delay_time;
	uint16_t power_down_time;
	uint16_t stealth_threshold;
	uint16_t coolstep_threshold;
	uint16_t classic_threshold;
	uint8_t high_velocity_chopper_mode;
} ATTRIBUTE_PACKED SetBasicConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBasicConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t standstill_current;
	uint16_t motor_run_current;
	uint16_t standstill_delay_time;
	uint16_t power_down_time;
	uint16_t stealth_threshold;
	uint16_t coolstep_threshold;
	uint16_t classic_threshold;
	uint8_t high_velocity_chopper_mode;
} ATTRIBUTE_PACKED GetBasicConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t slow_decay_duration;
	uint8_t enable_random_slow_decay;
	uint8_t fast_decay_duration;
	uint8_t hysteresis_start_value;
	int8_t hysteresis_end_value;
	int8_t sine_wave_offset;
	uint8_t chopper_mode;
	uint8_t comparator_blank_time;
	uint8_t fast_decay_without_comparator;
} ATTRIBUTE_PACKED SetSpreadcycleConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSpreadcycleConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t slow_decay_duration;
	uint8_t enable_random_slow_decay;
	uint8_t fast_decay_duration;
	uint8_t hysteresis_start_value;
	int8_t hysteresis_end_value;
	int8_t sine_wave_offset;
	uint8_t chopper_mode;
	uint8_t comparator_blank_time;
	uint8_t fast_decay_without_comparator;
} ATTRIBUTE_PACKED GetSpreadcycleConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_stealth;
	uint8_t amplitude;
	uint8_t gradient;
	uint8_t enable_autoscale;
	uint8_t force_symmetric;
	uint8_t freewheel_mode;
} ATTRIBUTE_PACKED SetStealthConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStealthConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_stealth;
	uint8_t amplitude;
	uint8_t gradient;
	uint8_t enable_autoscale;
	uint8_t force_symmetric;
	uint8_t freewheel_mode;
} ATTRIBUTE_PACKED GetStealthConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t minimum_stallguard_value;
	uint8_t maximum_stallguard_value;
	uint8_t current_up_step_width;
	uint8_t current_down_step_width;
	uint8_t minimum_current;
	int8_t stallguard_threshold_value;
	uint8_t stallguard_mode;
} ATTRIBUTE_PACKED SetCoolstepConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCoolstepConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t minimum_stallguard_value;
	uint8_t maximum_stallguard_value;
	uint8_t current_up_step_width;
	uint8_t current_down_step_width;
	uint8_t minimum_current;
	int8_t stallguard_threshold_value;
	uint8_t stallguard_mode;
} ATTRIBUTE_PACKED GetCoolstepConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t disable_short_to_ground_protection;
	uint8_t synchronize_phase_frequency;
} ATTRIBUTE_PACKED SetMiscConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMiscConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t disable_short_to_ground_protection;
	uint8_t synchronize_phase_frequency;
} ATTRIBUTE_PACKED GetMiscConfiguration_Response;

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
} ATTRIBUTE_PACKED GetDriverStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t open_load;
	uint8_t short_to_ground;
	uint8_t over_temperature;
	uint8_t motor_stalled;
	uint8_t actual_motor_current;
	uint8_t full_step_active;
	uint8_t stallguard_result;
	uint8_t stealth_voltage_amplitude;
} ATTRIBUTE_PACKED GetDriverStatus_Response;

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
	int32_t position;
} ATTRIBUTE_PACKED PositionReached_Callback;

typedef struct {
	PacketHeader header;
	uint32_t time_base;
} ATTRIBUTE_PACKED SetTimeBase_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTimeBase_Request;

typedef struct {
	PacketHeader header;
	uint32_t time_base;
} ATTRIBUTE_PACKED GetTimeBase_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllData_Request;

typedef struct {
	PacketHeader header;
	uint16_t current_velocity;
	int32_t current_position;
	int32_t remaining_steps;
	uint16_t input_voltage;
	uint16_t current_consumption;
} ATTRIBUTE_PACKED GetAllData_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAllCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllDataCallbackConfiguraton_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAllDataCallbackConfiguraton_Response;

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
	uint16_t current_velocity;
	int32_t current_position;
	int32_t remaining_steps;
	uint16_t input_voltage;
	uint16_t current_consumption;
} ATTRIBUTE_PACKED AllData_Callback;

typedef struct {
	PacketHeader header;
	uint8_t state_new;
	uint8_t state_previous;
} ATTRIBUTE_PACKED NewState_Callback;

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

static void silent_stepper_v2_callback_wrapper_under_voltage(DevicePrivate *device_p, Packet *packet) {
	UnderVoltage_CallbackFunction callback_function;
	void *user_data;
	UnderVoltage_Callback *callback;

	if (packet->header.length != sizeof(UnderVoltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (UnderVoltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_UNDER_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_UNDER_VOLTAGE];
	callback = (UnderVoltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void silent_stepper_v2_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReached_CallbackFunction callback_function;
	void *user_data;
	PositionReached_Callback *callback;

	if (packet->header.length != sizeof(PositionReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PositionReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_POSITION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_POSITION_REACHED];
	callback = (PositionReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->position = leconvert_int32_from(callback->position);

	callback_function(callback->position, user_data);
}

static void silent_stepper_v2_callback_wrapper_all_data(DevicePrivate *device_p, Packet *packet) {
	AllData_CallbackFunction callback_function;
	void *user_data;
	AllData_Callback *callback;

	if (packet->header.length != sizeof(AllData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_ALL_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_ALL_DATA];
	callback = (AllData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current_velocity = leconvert_uint16_from(callback->current_velocity);
	callback->current_position = leconvert_int32_from(callback->current_position);
	callback->remaining_steps = leconvert_int32_from(callback->remaining_steps);
	callback->input_voltage = leconvert_uint16_from(callback->input_voltage);
	callback->current_consumption = leconvert_uint16_from(callback->current_consumption);

	callback_function(callback->current_velocity, callback->current_position, callback->remaining_steps, callback->input_voltage, callback->current_consumption, user_data);
}

static void silent_stepper_v2_callback_wrapper_new_state(DevicePrivate *device_p, Packet *packet) {
	NewState_CallbackFunction callback_function;
	void *user_data;
	NewState_Callback *callback;

	if (packet->header.length != sizeof(NewState_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (NewState_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_NEW_STATE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_NEW_STATE];
	callback = (NewState_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state_new, callback->state_previous, user_data);
}

static void silent_stepper_v2_callback_wrapper_gpio_state(DevicePrivate *device_p, Packet *packet) {
	GPIOState_CallbackFunction callback_function;
	void *user_data;
	GPIOState_Callback *callback;
	int i;
	bool unpacked_gpio_state[2];

	if (packet->header.length != sizeof(GPIOState_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GPIOState_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_GPIO_STATE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SILENT_STEPPER_V2_CALLBACK_GPIO_STATE];
	callback = (GPIOState_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	for (i = 0; i < 2; i++) unpacked_gpio_state[i] = (callback->gpio_state[i / 8] & (1 << (i % 8))) != 0;

	callback_function(unpacked_gpio_state, user_data);
}

void silent_stepper_v2_create(SilentStepperV2 *silent_stepper_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(silent_stepper_v2, uid, ipcon_p, 2, 0, 0, SILENT_STEPPER_V2_DEVICE_IDENTIFIER);

	device_p = silent_stepper_v2->p;

	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_MAX_VELOCITY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_MAX_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_CURRENT_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_SPEED_RAMPING] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_SPEED_RAMPING] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_FULL_BRAKE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_CURRENT_POSITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_CURRENT_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_TARGET_POSITION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_TARGET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_STEPS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_STEPS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_REMAINING_STEPS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_STEP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_STEP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_DRIVE_FORWARD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_DRIVE_BACKWARD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_STOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_INPUT_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_MOTOR_CURRENT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_MOTOR_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_ENABLED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_BASIC_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_BASIC_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_SPREADCYCLE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_SPREADCYCLE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_STEALTH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_STEALTH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_COOLSTEP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_COOLSTEP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_MISC_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_MISC_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_DRIVER_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_MINIMUM_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_TIME_BASE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_TIME_BASE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_ALL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_ALL_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_ALL_DATA_CALLBACK_CONFIGURATON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_GPIO_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_GPIO_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_GPIO_ACTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_GPIO_ACTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_GPIO_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SILENT_STEPPER_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SILENT_STEPPER_V2_CALLBACK_UNDER_VOLTAGE] = silent_stepper_v2_callback_wrapper_under_voltage;
	device_p->callback_wrappers[SILENT_STEPPER_V2_CALLBACK_POSITION_REACHED] = silent_stepper_v2_callback_wrapper_position_reached;
	device_p->callback_wrappers[SILENT_STEPPER_V2_CALLBACK_ALL_DATA] = silent_stepper_v2_callback_wrapper_all_data;
	device_p->callback_wrappers[SILENT_STEPPER_V2_CALLBACK_NEW_STATE] = silent_stepper_v2_callback_wrapper_new_state;
	device_p->callback_wrappers[SILENT_STEPPER_V2_CALLBACK_GPIO_STATE] = silent_stepper_v2_callback_wrapper_gpio_state;

	ipcon_add_device(ipcon_p, device_p);
}

void silent_stepper_v2_destroy(SilentStepperV2 *silent_stepper_v2) {
	device_release(silent_stepper_v2->p);
}

int silent_stepper_v2_get_response_expected(SilentStepperV2 *silent_stepper_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(silent_stepper_v2->p, function_id, ret_response_expected);
}

int silent_stepper_v2_set_response_expected(SilentStepperV2 *silent_stepper_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(silent_stepper_v2->p, function_id, response_expected);
}

int silent_stepper_v2_set_response_expected_all(SilentStepperV2 *silent_stepper_v2, bool response_expected) {
	return device_set_response_expected_all(silent_stepper_v2->p, response_expected);
}

void silent_stepper_v2_register_callback(SilentStepperV2 *silent_stepper_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(silent_stepper_v2->p, callback_id, function, user_data);
}

int silent_stepper_v2_get_api_version(SilentStepperV2 *silent_stepper_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(silent_stepper_v2->p, ret_api_version);
}

int silent_stepper_v2_set_max_velocity(SilentStepperV2 *silent_stepper_v2, uint16_t velocity) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetMaxVelocity_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_MAX_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.velocity = leconvert_uint16_to(velocity);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_max_velocity(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_velocity) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetMaxVelocity_Request request;
	GetMaxVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_MAX_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint16_from(response.velocity);

	return ret;
}

int silent_stepper_v2_get_current_velocity(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_velocity) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetCurrentVelocity_Request request;
	GetCurrentVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_CURRENT_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_velocity = leconvert_uint16_from(response.velocity);

	return ret;
}

int silent_stepper_v2_set_speed_ramping(SilentStepperV2 *silent_stepper_v2, uint16_t acceleration, uint16_t deacceleration) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetSpeedRamping_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_SPEED_RAMPING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.acceleration = leconvert_uint16_to(acceleration);
	request.deacceleration = leconvert_uint16_to(deacceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_speed_ramping(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_acceleration, uint16_t *ret_deacceleration) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetSpeedRamping_Request request;
	GetSpeedRamping_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_SPEED_RAMPING, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_acceleration = leconvert_uint16_from(response.acceleration);
	*ret_deacceleration = leconvert_uint16_from(response.deacceleration);

	return ret;
}

int silent_stepper_v2_full_brake(SilentStepperV2 *silent_stepper_v2) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	FullBrake_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_FULL_BRAKE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_set_current_position(SilentStepperV2 *silent_stepper_v2, int32_t position) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetCurrentPosition_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_CURRENT_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position = leconvert_int32_to(position);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_current_position(SilentStepperV2 *silent_stepper_v2, int32_t *ret_position) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetCurrentPosition_Request request;
	GetCurrentPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_CURRENT_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int32_from(response.position);

	return ret;
}

int silent_stepper_v2_set_target_position(SilentStepperV2 *silent_stepper_v2, int32_t position) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetTargetPosition_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_TARGET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position = leconvert_int32_to(position);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_target_position(SilentStepperV2 *silent_stepper_v2, int32_t *ret_position) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetTargetPosition_Request request;
	GetTargetPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_TARGET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_position = leconvert_int32_from(response.position);

	return ret;
}

int silent_stepper_v2_set_steps(SilentStepperV2 *silent_stepper_v2, int32_t steps) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetSteps_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_STEPS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.steps = leconvert_int32_to(steps);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_steps(SilentStepperV2 *silent_stepper_v2, int32_t *ret_steps) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetSteps_Request request;
	GetSteps_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_STEPS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_steps = leconvert_int32_from(response.steps);

	return ret;
}

int silent_stepper_v2_get_remaining_steps(SilentStepperV2 *silent_stepper_v2, int32_t *ret_steps) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetRemainingSteps_Request request;
	GetRemainingSteps_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_REMAINING_STEPS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_steps = leconvert_int32_from(response.steps);

	return ret;
}

int silent_stepper_v2_set_step_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t step_resolution, bool interpolation) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetStepConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_STEP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.step_resolution = step_resolution;
	request.interpolation = interpolation ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_step_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_step_resolution, bool *ret_interpolation) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetStepConfiguration_Request request;
	GetStepConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_STEP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_step_resolution = response.step_resolution;
	*ret_interpolation = response.interpolation != 0;

	return ret;
}

int silent_stepper_v2_drive_forward(SilentStepperV2 *silent_stepper_v2) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	DriveForward_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_DRIVE_FORWARD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_drive_backward(SilentStepperV2 *silent_stepper_v2) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	DriveBackward_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_DRIVE_BACKWARD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_stop(SilentStepperV2 *silent_stepper_v2) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	Stop_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_STOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_input_voltage(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetInputVoltage_Request request;
	GetInputVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_INPUT_VOLTAGE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_motor_current(SilentStepperV2 *silent_stepper_v2, uint16_t current) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetMotorCurrent_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_MOTOR_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.current = leconvert_uint16_to(current);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_motor_current(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_current) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetMotorCurrent_Request request;
	GetMotorCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_MOTOR_CURRENT, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_enabled(SilentStepperV2 *silent_stepper_v2, bool enabled) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetEnabled_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_enabled(SilentStepperV2 *silent_stepper_v2, bool *ret_enabled) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetEnabled_Request request;
	GetEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_ENABLED, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_basic_configuration(SilentStepperV2 *silent_stepper_v2, uint16_t standstill_current, uint16_t motor_run_current, uint16_t standstill_delay_time, uint16_t power_down_time, uint16_t stealth_threshold, uint16_t coolstep_threshold, uint16_t classic_threshold, bool high_velocity_chopper_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetBasicConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_BASIC_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.standstill_current = leconvert_uint16_to(standstill_current);
	request.motor_run_current = leconvert_uint16_to(motor_run_current);
	request.standstill_delay_time = leconvert_uint16_to(standstill_delay_time);
	request.power_down_time = leconvert_uint16_to(power_down_time);
	request.stealth_threshold = leconvert_uint16_to(stealth_threshold);
	request.coolstep_threshold = leconvert_uint16_to(coolstep_threshold);
	request.classic_threshold = leconvert_uint16_to(classic_threshold);
	request.high_velocity_chopper_mode = high_velocity_chopper_mode ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_basic_configuration(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_standstill_current, uint16_t *ret_motor_run_current, uint16_t *ret_standstill_delay_time, uint16_t *ret_power_down_time, uint16_t *ret_stealth_threshold, uint16_t *ret_coolstep_threshold, uint16_t *ret_classic_threshold, bool *ret_high_velocity_chopper_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetBasicConfiguration_Request request;
	GetBasicConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_BASIC_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_standstill_current = leconvert_uint16_from(response.standstill_current);
	*ret_motor_run_current = leconvert_uint16_from(response.motor_run_current);
	*ret_standstill_delay_time = leconvert_uint16_from(response.standstill_delay_time);
	*ret_power_down_time = leconvert_uint16_from(response.power_down_time);
	*ret_stealth_threshold = leconvert_uint16_from(response.stealth_threshold);
	*ret_coolstep_threshold = leconvert_uint16_from(response.coolstep_threshold);
	*ret_classic_threshold = leconvert_uint16_from(response.classic_threshold);
	*ret_high_velocity_chopper_mode = response.high_velocity_chopper_mode != 0;

	return ret;
}

int silent_stepper_v2_set_spreadcycle_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t slow_decay_duration, bool enable_random_slow_decay, uint8_t fast_decay_duration, uint8_t hysteresis_start_value, int8_t hysteresis_end_value, int8_t sine_wave_offset, uint8_t chopper_mode, uint8_t comparator_blank_time, bool fast_decay_without_comparator) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetSpreadcycleConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_SPREADCYCLE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slow_decay_duration = slow_decay_duration;
	request.enable_random_slow_decay = enable_random_slow_decay ? 1 : 0;
	request.fast_decay_duration = fast_decay_duration;
	request.hysteresis_start_value = hysteresis_start_value;
	request.hysteresis_end_value = hysteresis_end_value;
	request.sine_wave_offset = sine_wave_offset;
	request.chopper_mode = chopper_mode;
	request.comparator_blank_time = comparator_blank_time;
	request.fast_decay_without_comparator = fast_decay_without_comparator ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_spreadcycle_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_slow_decay_duration, bool *ret_enable_random_slow_decay, uint8_t *ret_fast_decay_duration, uint8_t *ret_hysteresis_start_value, int8_t *ret_hysteresis_end_value, int8_t *ret_sine_wave_offset, uint8_t *ret_chopper_mode, uint8_t *ret_comparator_blank_time, bool *ret_fast_decay_without_comparator) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetSpreadcycleConfiguration_Request request;
	GetSpreadcycleConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_SPREADCYCLE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_slow_decay_duration = response.slow_decay_duration;
	*ret_enable_random_slow_decay = response.enable_random_slow_decay != 0;
	*ret_fast_decay_duration = response.fast_decay_duration;
	*ret_hysteresis_start_value = response.hysteresis_start_value;
	*ret_hysteresis_end_value = response.hysteresis_end_value;
	*ret_sine_wave_offset = response.sine_wave_offset;
	*ret_chopper_mode = response.chopper_mode;
	*ret_comparator_blank_time = response.comparator_blank_time;
	*ret_fast_decay_without_comparator = response.fast_decay_without_comparator != 0;

	return ret;
}

int silent_stepper_v2_set_stealth_configuration(SilentStepperV2 *silent_stepper_v2, bool enable_stealth, uint8_t amplitude, uint8_t gradient, bool enable_autoscale, bool force_symmetric, uint8_t freewheel_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetStealthConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_STEALTH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_stealth = enable_stealth ? 1 : 0;
	request.amplitude = amplitude;
	request.gradient = gradient;
	request.enable_autoscale = enable_autoscale ? 1 : 0;
	request.force_symmetric = force_symmetric ? 1 : 0;
	request.freewheel_mode = freewheel_mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_stealth_configuration(SilentStepperV2 *silent_stepper_v2, bool *ret_enable_stealth, uint8_t *ret_amplitude, uint8_t *ret_gradient, bool *ret_enable_autoscale, bool *ret_force_symmetric, uint8_t *ret_freewheel_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetStealthConfiguration_Request request;
	GetStealthConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_STEALTH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_stealth = response.enable_stealth != 0;
	*ret_amplitude = response.amplitude;
	*ret_gradient = response.gradient;
	*ret_enable_autoscale = response.enable_autoscale != 0;
	*ret_force_symmetric = response.force_symmetric != 0;
	*ret_freewheel_mode = response.freewheel_mode;

	return ret;
}

int silent_stepper_v2_set_coolstep_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t minimum_stallguard_value, uint8_t maximum_stallguard_value, uint8_t current_up_step_width, uint8_t current_down_step_width, uint8_t minimum_current, int8_t stallguard_threshold_value, uint8_t stallguard_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetCoolstepConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_COOLSTEP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.minimum_stallguard_value = minimum_stallguard_value;
	request.maximum_stallguard_value = maximum_stallguard_value;
	request.current_up_step_width = current_up_step_width;
	request.current_down_step_width = current_down_step_width;
	request.minimum_current = minimum_current;
	request.stallguard_threshold_value = stallguard_threshold_value;
	request.stallguard_mode = stallguard_mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_coolstep_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_minimum_stallguard_value, uint8_t *ret_maximum_stallguard_value, uint8_t *ret_current_up_step_width, uint8_t *ret_current_down_step_width, uint8_t *ret_minimum_current, int8_t *ret_stallguard_threshold_value, uint8_t *ret_stallguard_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetCoolstepConfiguration_Request request;
	GetCoolstepConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_COOLSTEP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_minimum_stallguard_value = response.minimum_stallguard_value;
	*ret_maximum_stallguard_value = response.maximum_stallguard_value;
	*ret_current_up_step_width = response.current_up_step_width;
	*ret_current_down_step_width = response.current_down_step_width;
	*ret_minimum_current = response.minimum_current;
	*ret_stallguard_threshold_value = response.stallguard_threshold_value;
	*ret_stallguard_mode = response.stallguard_mode;

	return ret;
}

int silent_stepper_v2_set_misc_configuration(SilentStepperV2 *silent_stepper_v2, bool disable_short_to_ground_protection, uint8_t synchronize_phase_frequency) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetMiscConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_MISC_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.disable_short_to_ground_protection = disable_short_to_ground_protection ? 1 : 0;
	request.synchronize_phase_frequency = synchronize_phase_frequency;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_misc_configuration(SilentStepperV2 *silent_stepper_v2, bool *ret_disable_short_to_ground_protection, uint8_t *ret_synchronize_phase_frequency) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetMiscConfiguration_Request request;
	GetMiscConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_MISC_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_disable_short_to_ground_protection = response.disable_short_to_ground_protection != 0;
	*ret_synchronize_phase_frequency = response.synchronize_phase_frequency;

	return ret;
}

int silent_stepper_v2_set_error_led_config(SilentStepperV2 *silent_stepper_v2, uint8_t config) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_error_led_config(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_driver_status(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_open_load, uint8_t *ret_short_to_ground, uint8_t *ret_over_temperature, bool *ret_motor_stalled, uint8_t *ret_actual_motor_current, bool *ret_full_step_active, uint8_t *ret_stallguard_result, uint8_t *ret_stealth_voltage_amplitude) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetDriverStatus_Request request;
	GetDriverStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_DRIVER_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_open_load = response.open_load;
	*ret_short_to_ground = response.short_to_ground;
	*ret_over_temperature = response.over_temperature;
	*ret_motor_stalled = response.motor_stalled != 0;
	*ret_actual_motor_current = response.actual_motor_current;
	*ret_full_step_active = response.full_step_active != 0;
	*ret_stallguard_result = response.stallguard_result;
	*ret_stealth_voltage_amplitude = response.stealth_voltage_amplitude;

	return ret;
}

int silent_stepper_v2_set_minimum_voltage(SilentStepperV2 *silent_stepper_v2, uint16_t voltage) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetMinimumVoltage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage = leconvert_uint16_to(voltage);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_minimum_voltage(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_voltage) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetMinimumVoltage_Request request;
	GetMinimumVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_MINIMUM_VOLTAGE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_time_base(SilentStepperV2 *silent_stepper_v2, uint32_t time_base) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetTimeBase_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_TIME_BASE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.time_base = leconvert_uint32_to(time_base);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_time_base(SilentStepperV2 *silent_stepper_v2, uint32_t *ret_time_base) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetTimeBase_Request request;
	GetTimeBase_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_TIME_BASE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_time_base = leconvert_uint32_from(response.time_base);

	return ret;
}

int silent_stepper_v2_get_all_data(SilentStepperV2 *silent_stepper_v2, uint16_t *ret_current_velocity, int32_t *ret_current_position, int32_t *ret_remaining_steps, uint16_t *ret_input_voltage, uint16_t *ret_current_consumption) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetAllData_Request request;
	GetAllData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_ALL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current_velocity = leconvert_uint16_from(response.current_velocity);
	*ret_current_position = leconvert_int32_from(response.current_position);
	*ret_remaining_steps = leconvert_int32_from(response.remaining_steps);
	*ret_input_voltage = leconvert_uint16_from(response.input_voltage);
	*ret_current_consumption = leconvert_uint16_from(response.current_consumption);

	return ret;
}

int silent_stepper_v2_set_all_callback_configuration(SilentStepperV2 *silent_stepper_v2, uint32_t period) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetAllCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_ALL_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_all_data_callback_configuraton(SilentStepperV2 *silent_stepper_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetAllDataCallbackConfiguraton_Request request;
	GetAllDataCallbackConfiguraton_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_ALL_DATA_CALLBACK_CONFIGURATON, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_gpio_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t channel, uint16_t debounce, uint16_t stop_deceleration) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetGPIOConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_GPIO_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.debounce = leconvert_uint16_to(debounce);
	request.stop_deceleration = leconvert_uint16_to(stop_deceleration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_gpio_configuration(SilentStepperV2 *silent_stepper_v2, uint8_t channel, uint16_t *ret_debounce, uint16_t *ret_stop_deceleration) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetGPIOConfiguration_Request request;
	GetGPIOConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_GPIO_CONFIGURATION, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_gpio_action(SilentStepperV2 *silent_stepper_v2, uint8_t channel, uint32_t action) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetGPIOAction_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_GPIO_ACTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.action = leconvert_uint32_to(action);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_gpio_action(SilentStepperV2 *silent_stepper_v2, uint8_t channel, uint32_t *ret_action) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetGPIOAction_Request request;
	GetGPIOAction_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_GPIO_ACTION, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_gpio_state(SilentStepperV2 *silent_stepper_v2, bool ret_gpio_state[2]) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetGPIOState_Request request;
	GetGPIOState_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_GPIO_STATE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_spitfp_error_count(SilentStepperV2 *silent_stepper_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_bootloader_mode(SilentStepperV2 *silent_stepper_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_bootloader_mode(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_write_firmware_pointer(SilentStepperV2 *silent_stepper_v2, uint32_t pointer) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_write_firmware(SilentStepperV2 *silent_stepper_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_set_status_led_config(SilentStepperV2 *silent_stepper_v2, uint8_t config) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_get_status_led_config(SilentStepperV2 *silent_stepper_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_chip_temperature(SilentStepperV2 *silent_stepper_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_reset(SilentStepperV2 *silent_stepper_v2) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_write_uid(SilentStepperV2 *silent_stepper_v2, uint32_t uid) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int silent_stepper_v2_read_uid(SilentStepperV2 *silent_stepper_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int silent_stepper_v2_get_identity(SilentStepperV2 *silent_stepper_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = silent_stepper_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SILENT_STEPPER_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
