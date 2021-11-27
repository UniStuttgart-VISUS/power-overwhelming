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

#include "bricklet_ptc_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Temperature_CallbackFunction)(int32_t temperature, void *user_data);

typedef void (*Resistance_CallbackFunction)(int32_t resistance, void *user_data);

typedef void (*SensorConnected_CallbackFunction)(bool connected, void *user_data);

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
} ATTRIBUTE_PACKED GetTemperature_Request;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED GetTemperature_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t temperature;
} ATTRIBUTE_PACKED Temperature_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistance_Request;

typedef struct {
	PacketHeader header;
	int32_t resistance;
} ATTRIBUTE_PACKED GetResistance_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetResistanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResistanceCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetResistanceCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t resistance;
} ATTRIBUTE_PACKED Resistance_Callback;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED SetNoiseRejectionFilter_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetNoiseRejectionFilter_Request;

typedef struct {
	PacketHeader header;
	uint8_t filter;
} ATTRIBUTE_PACKED GetNoiseRejectionFilter_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsSensorConnected_Request;

typedef struct {
	PacketHeader header;
	uint8_t connected;
} ATTRIBUTE_PACKED IsSensorConnected_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetWireMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWireMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetWireMode_Response;

typedef struct {
	PacketHeader header;
	uint16_t moving_average_length_resistance;
	uint16_t moving_average_length_temperature;
} ATTRIBUTE_PACKED SetMovingAverageConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMovingAverageConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t moving_average_length_resistance;
	uint16_t moving_average_length_temperature;
} ATTRIBUTE_PACKED GetMovingAverageConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetSensorConnectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorConnectedCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetSensorConnectedCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t connected;
} ATTRIBUTE_PACKED SensorConnected_Callback;

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

static void ptc_v2_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	Temperature_CallbackFunction callback_function;
	void *user_data;
	Temperature_Callback *callback;

	if (packet->header.length != sizeof(Temperature_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Temperature_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_TEMPERATURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_TEMPERATURE];
	callback = (Temperature_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void ptc_v2_callback_wrapper_resistance(DevicePrivate *device_p, Packet *packet) {
	Resistance_CallbackFunction callback_function;
	void *user_data;
	Resistance_Callback *callback;

	if (packet->header.length != sizeof(Resistance_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Resistance_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_RESISTANCE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_RESISTANCE];
	callback = (Resistance_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->resistance = leconvert_int32_from(callback->resistance);

	callback_function(callback->resistance, user_data);
}

static void ptc_v2_callback_wrapper_sensor_connected(DevicePrivate *device_p, Packet *packet) {
	SensorConnected_CallbackFunction callback_function;
	void *user_data;
	SensorConnected_Callback *callback;
	bool unpacked_connected;

	if (packet->header.length != sizeof(SensorConnected_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SensorConnected_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_SENSOR_CONNECTED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PTC_V2_CALLBACK_SENSOR_CONNECTED];
	callback = (SensorConnected_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_connected = callback->connected != 0;

	callback_function(unpacked_connected, user_data);
}

void ptc_v2_create(PTCV2 *ptc_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(ptc_v2, uid, ipcon_p, 2, 0, 0, PTC_V2_DEVICE_IDENTIFIER);

	device_p = ptc_v2->p;

	device_p->response_expected[PTC_V2_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_RESISTANCE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_RESISTANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_RESISTANCE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_NOISE_REJECTION_FILTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_IS_SENSOR_CONNECTED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_WIRE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_MOVING_AVERAGE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_MOVING_AVERAGE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PTC_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PTC_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PTC_V2_CALLBACK_TEMPERATURE] = ptc_v2_callback_wrapper_temperature;
	device_p->callback_wrappers[PTC_V2_CALLBACK_RESISTANCE] = ptc_v2_callback_wrapper_resistance;
	device_p->callback_wrappers[PTC_V2_CALLBACK_SENSOR_CONNECTED] = ptc_v2_callback_wrapper_sensor_connected;

	ipcon_add_device(ipcon_p, device_p);
}

void ptc_v2_destroy(PTCV2 *ptc_v2) {
	device_release(ptc_v2->p);
}

int ptc_v2_get_response_expected(PTCV2 *ptc_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(ptc_v2->p, function_id, ret_response_expected);
}

int ptc_v2_set_response_expected(PTCV2 *ptc_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(ptc_v2->p, function_id, response_expected);
}

int ptc_v2_set_response_expected_all(PTCV2 *ptc_v2, bool response_expected) {
	return device_set_response_expected_all(ptc_v2->p, response_expected);
}

void ptc_v2_register_callback(PTCV2 *ptc_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(ptc_v2->p, callback_id, function, user_data);
}

int ptc_v2_get_api_version(PTCV2 *ptc_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(ptc_v2->p, ret_api_version);
}

int ptc_v2_get_temperature(PTCV2 *ptc_v2, int32_t *ret_temperature) {
	DevicePrivate *device_p = ptc_v2->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int32_from(response.temperature);

	return ret;
}

int ptc_v2_set_temperature_callback_configuration(PTCV2 *ptc_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = ptc_v2->p;
	SetTemperatureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_v2_get_temperature_callback_configuration(PTCV2 *ptc_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = ptc_v2->p;
	GetTemperatureCallbackConfiguration_Request request;
	GetTemperatureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_v2_get_resistance(PTCV2 *ptc_v2, int32_t *ret_resistance) {
	DevicePrivate *device_p = ptc_v2->p;
	GetResistance_Request request;
	GetResistance_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_RESISTANCE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_resistance = leconvert_int32_from(response.resistance);

	return ret;
}

int ptc_v2_set_resistance_callback_configuration(PTCV2 *ptc_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = ptc_v2->p;
	SetResistanceCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_RESISTANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_v2_get_resistance_callback_configuration(PTCV2 *ptc_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = ptc_v2->p;
	GetResistanceCallbackConfiguration_Request request;
	GetResistanceCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_RESISTANCE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_v2_set_noise_rejection_filter(PTCV2 *ptc_v2, uint8_t filter) {
	DevicePrivate *device_p = ptc_v2->p;
	SetNoiseRejectionFilter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.filter = filter;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_get_noise_rejection_filter(PTCV2 *ptc_v2, uint8_t *ret_filter) {
	DevicePrivate *device_p = ptc_v2->p;
	GetNoiseRejectionFilter_Request request;
	GetNoiseRejectionFilter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_NOISE_REJECTION_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_filter = response.filter;

	return ret;
}

int ptc_v2_is_sensor_connected(PTCV2 *ptc_v2, bool *ret_connected) {
	DevicePrivate *device_p = ptc_v2->p;
	IsSensorConnected_Request request;
	IsSensorConnected_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_IS_SENSOR_CONNECTED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_connected = response.connected != 0;

	return ret;
}

int ptc_v2_set_wire_mode(PTCV2 *ptc_v2, uint8_t mode) {
	DevicePrivate *device_p = ptc_v2->p;
	SetWireMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_WIRE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_get_wire_mode(PTCV2 *ptc_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = ptc_v2->p;
	GetWireMode_Request request;
	GetWireMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_WIRE_MODE, device_p->ipcon_p, device_p);

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

int ptc_v2_set_moving_average_configuration(PTCV2 *ptc_v2, uint16_t moving_average_length_resistance, uint16_t moving_average_length_temperature) {
	DevicePrivate *device_p = ptc_v2->p;
	SetMovingAverageConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_MOVING_AVERAGE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.moving_average_length_resistance = leconvert_uint16_to(moving_average_length_resistance);
	request.moving_average_length_temperature = leconvert_uint16_to(moving_average_length_temperature);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_get_moving_average_configuration(PTCV2 *ptc_v2, uint16_t *ret_moving_average_length_resistance, uint16_t *ret_moving_average_length_temperature) {
	DevicePrivate *device_p = ptc_v2->p;
	GetMovingAverageConfiguration_Request request;
	GetMovingAverageConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_MOVING_AVERAGE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_moving_average_length_resistance = leconvert_uint16_from(response.moving_average_length_resistance);
	*ret_moving_average_length_temperature = leconvert_uint16_from(response.moving_average_length_temperature);

	return ret;
}

int ptc_v2_set_sensor_connected_callback_configuration(PTCV2 *ptc_v2, bool enabled) {
	DevicePrivate *device_p = ptc_v2->p;
	SetSensorConnectedCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_get_sensor_connected_callback_configuration(PTCV2 *ptc_v2, bool *ret_enabled) {
	DevicePrivate *device_p = ptc_v2->p;
	GetSensorConnectedCallbackConfiguration_Request request;
	GetSensorConnectedCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_SENSOR_CONNECTED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int ptc_v2_get_spitfp_error_count(PTCV2 *ptc_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = ptc_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int ptc_v2_set_bootloader_mode(PTCV2 *ptc_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = ptc_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int ptc_v2_get_bootloader_mode(PTCV2 *ptc_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = ptc_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int ptc_v2_set_write_firmware_pointer(PTCV2 *ptc_v2, uint32_t pointer) {
	DevicePrivate *device_p = ptc_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_write_firmware(PTCV2 *ptc_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = ptc_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int ptc_v2_set_status_led_config(PTCV2 *ptc_v2, uint8_t config) {
	DevicePrivate *device_p = ptc_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_get_status_led_config(PTCV2 *ptc_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = ptc_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int ptc_v2_get_chip_temperature(PTCV2 *ptc_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = ptc_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int ptc_v2_reset(PTCV2 *ptc_v2) {
	DevicePrivate *device_p = ptc_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_write_uid(PTCV2 *ptc_v2, uint32_t uid) {
	DevicePrivate *device_p = ptc_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int ptc_v2_read_uid(PTCV2 *ptc_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = ptc_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int ptc_v2_get_identity(PTCV2 *ptc_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = ptc_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PTC_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
