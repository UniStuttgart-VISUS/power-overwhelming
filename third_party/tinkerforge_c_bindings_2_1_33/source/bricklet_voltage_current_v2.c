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

#include "bricklet_voltage_current_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Current_CallbackFunction)(int32_t current, void *user_data);

typedef void (*Voltage_CallbackFunction)(int32_t voltage, void *user_data);

typedef void (*Power_CallbackFunction)(int32_t power, void *user_data);

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
} ATTRIBUTE_PACKED GetCurrent_Request;

typedef struct {
	PacketHeader header;
	int32_t current;
} ATTRIBUTE_PACKED GetCurrent_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetCurrentCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCurrentCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetCurrentCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t current;
} ATTRIBUTE_PACKED Current_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltage_Request;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED GetVoltage_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetVoltageCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltageCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetVoltageCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t voltage;
} ATTRIBUTE_PACKED Voltage_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPower_Request;

typedef struct {
	PacketHeader header;
	int32_t power;
} ATTRIBUTE_PACKED GetPower_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetPowerCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPowerCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetPowerCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t power;
} ATTRIBUTE_PACKED Power_Callback;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t voltage_conversion_time;
	uint8_t current_conversion_time;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t averaging;
	uint8_t voltage_conversion_time;
	uint8_t current_conversion_time;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage_multiplier;
	uint16_t voltage_divisor;
	uint16_t current_multiplier;
	uint16_t current_divisor;
} ATTRIBUTE_PACKED SetCalibration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCalibration_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage_multiplier;
	uint16_t voltage_divisor;
	uint16_t current_multiplier;
	uint16_t current_divisor;
} ATTRIBUTE_PACKED GetCalibration_Response;

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

static void voltage_current_v2_callback_wrapper_current(DevicePrivate *device_p, Packet *packet) {
	Current_CallbackFunction callback_function;
	void *user_data;
	Current_Callback *callback;

	if (packet->header.length != sizeof(Current_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Current_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_CURRENT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_CURRENT];
	callback = (Current_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_int32_from(callback->current);

	callback_function(callback->current, user_data);
}

static void voltage_current_v2_callback_wrapper_voltage(DevicePrivate *device_p, Packet *packet) {
	Voltage_CallbackFunction callback_function;
	void *user_data;
	Voltage_Callback *callback;

	if (packet->header.length != sizeof(Voltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Voltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE];
	callback = (Voltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void voltage_current_v2_callback_wrapper_power(DevicePrivate *device_p, Packet *packet) {
	Power_CallbackFunction callback_function;
	void *user_data;
	Power_Callback *callback;

	if (packet->header.length != sizeof(Power_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Power_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_POWER];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + VOLTAGE_CURRENT_V2_CALLBACK_POWER];
	callback = (Power_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->power = leconvert_int32_from(callback->power);

	callback_function(callback->power, user_data);
}

void voltage_current_v2_create(VoltageCurrentV2 *voltage_current_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(voltage_current_v2, uid, ipcon_p, 2, 0, 0, VOLTAGE_CURRENT_V2_DEVICE_IDENTIFIER);

	device_p = voltage_current_v2->p;

	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_CURRENT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_CURRENT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_VOLTAGE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_VOLTAGE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_POWER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_POWER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_POWER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[VOLTAGE_CURRENT_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[VOLTAGE_CURRENT_V2_CALLBACK_CURRENT] = voltage_current_v2_callback_wrapper_current;
	device_p->callback_wrappers[VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE] = voltage_current_v2_callback_wrapper_voltage;
	device_p->callback_wrappers[VOLTAGE_CURRENT_V2_CALLBACK_POWER] = voltage_current_v2_callback_wrapper_power;

	ipcon_add_device(ipcon_p, device_p);
}

void voltage_current_v2_destroy(VoltageCurrentV2 *voltage_current_v2) {
	device_release(voltage_current_v2->p);
}

int voltage_current_v2_get_response_expected(VoltageCurrentV2 *voltage_current_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(voltage_current_v2->p, function_id, ret_response_expected);
}

int voltage_current_v2_set_response_expected(VoltageCurrentV2 *voltage_current_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(voltage_current_v2->p, function_id, response_expected);
}

int voltage_current_v2_set_response_expected_all(VoltageCurrentV2 *voltage_current_v2, bool response_expected) {
	return device_set_response_expected_all(voltage_current_v2->p, response_expected);
}

void voltage_current_v2_register_callback(VoltageCurrentV2 *voltage_current_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(voltage_current_v2->p, callback_id, function, user_data);
}

int voltage_current_v2_get_api_version(VoltageCurrentV2 *voltage_current_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(voltage_current_v2->p, ret_api_version);
}

int voltage_current_v2_get_current(VoltageCurrentV2 *voltage_current_v2, int32_t *ret_current) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetCurrent_Request request;
	GetCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_int32_from(response.current);

	return ret;
}

int voltage_current_v2_set_current_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetCurrentCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_CURRENT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_current_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetCurrentCallbackConfiguration_Request request;
	GetCurrentCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_CURRENT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int voltage_current_v2_get_voltage(VoltageCurrentV2 *voltage_current_v2, int32_t *ret_voltage) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetVoltage_Request request;
	GetVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_int32_from(response.voltage);

	return ret;
}

int voltage_current_v2_set_voltage_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetVoltageCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_VOLTAGE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_voltage_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetVoltageCallbackConfiguration_Request request;
	GetVoltageCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_VOLTAGE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int voltage_current_v2_get_power(VoltageCurrentV2 *voltage_current_v2, int32_t *ret_power) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetPower_Request request;
	GetPower_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_POWER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_power = leconvert_int32_from(response.power);

	return ret;
}

int voltage_current_v2_set_power_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetPowerCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_POWER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_int32_to(min);
	request.max = leconvert_int32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_power_callback_configuration(VoltageCurrentV2 *voltage_current_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetPowerCallbackConfiguration_Request request;
	GetPowerCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_POWER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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
	*ret_min = leconvert_int32_from(response.min);
	*ret_max = leconvert_int32_from(response.max);

	return ret;
}

int voltage_current_v2_set_configuration(VoltageCurrentV2 *voltage_current_v2, uint8_t averaging, uint8_t voltage_conversion_time, uint8_t current_conversion_time) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.averaging = averaging;
	request.voltage_conversion_time = voltage_conversion_time;
	request.current_conversion_time = current_conversion_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_configuration(VoltageCurrentV2 *voltage_current_v2, uint8_t *ret_averaging, uint8_t *ret_voltage_conversion_time, uint8_t *ret_current_conversion_time) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_averaging = response.averaging;
	*ret_voltage_conversion_time = response.voltage_conversion_time;
	*ret_current_conversion_time = response.current_conversion_time;

	return ret;
}

int voltage_current_v2_set_calibration(VoltageCurrentV2 *voltage_current_v2, uint16_t voltage_multiplier, uint16_t voltage_divisor, uint16_t current_multiplier, uint16_t current_divisor) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetCalibration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage_multiplier = leconvert_uint16_to(voltage_multiplier);
	request.voltage_divisor = leconvert_uint16_to(voltage_divisor);
	request.current_multiplier = leconvert_uint16_to(current_multiplier);
	request.current_divisor = leconvert_uint16_to(current_divisor);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_calibration(VoltageCurrentV2 *voltage_current_v2, uint16_t *ret_voltage_multiplier, uint16_t *ret_voltage_divisor, uint16_t *ret_current_multiplier, uint16_t *ret_current_divisor) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetCalibration_Request request;
	GetCalibration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage_multiplier = leconvert_uint16_from(response.voltage_multiplier);
	*ret_voltage_divisor = leconvert_uint16_from(response.voltage_divisor);
	*ret_current_multiplier = leconvert_uint16_from(response.current_multiplier);
	*ret_current_divisor = leconvert_uint16_from(response.current_divisor);

	return ret;
}

int voltage_current_v2_get_spitfp_error_count(VoltageCurrentV2 *voltage_current_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int voltage_current_v2_set_bootloader_mode(VoltageCurrentV2 *voltage_current_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int voltage_current_v2_get_bootloader_mode(VoltageCurrentV2 *voltage_current_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int voltage_current_v2_set_write_firmware_pointer(VoltageCurrentV2 *voltage_current_v2, uint32_t pointer) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_write_firmware(VoltageCurrentV2 *voltage_current_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = voltage_current_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int voltage_current_v2_set_status_led_config(VoltageCurrentV2 *voltage_current_v2, uint8_t config) {
	DevicePrivate *device_p = voltage_current_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_get_status_led_config(VoltageCurrentV2 *voltage_current_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int voltage_current_v2_get_chip_temperature(VoltageCurrentV2 *voltage_current_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int voltage_current_v2_reset(VoltageCurrentV2 *voltage_current_v2) {
	DevicePrivate *device_p = voltage_current_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_write_uid(VoltageCurrentV2 *voltage_current_v2, uint32_t uid) {
	DevicePrivate *device_p = voltage_current_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int voltage_current_v2_read_uid(VoltageCurrentV2 *voltage_current_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = voltage_current_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int voltage_current_v2_get_identity(VoltageCurrentV2 *voltage_current_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = voltage_current_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), VOLTAGE_CURRENT_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
