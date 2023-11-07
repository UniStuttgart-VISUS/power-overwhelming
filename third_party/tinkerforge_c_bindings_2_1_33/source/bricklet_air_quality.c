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

#include "bricklet_air_quality.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AllValues_CallbackFunction)(int32_t iaq_index, uint8_t iaq_index_accuracy, int32_t temperature, int32_t humidity, int32_t air_pressure, void *user_data);

typedef void (*IAQIndex_CallbackFunction)(int32_t iaq_index, uint8_t iaq_index_accuracy, void *user_data);

typedef void (*Temperature_CallbackFunction)(int32_t temperature, void *user_data);

typedef void (*Humidity_CallbackFunction)(int32_t humidity, void *user_data);

typedef void (*AirPressure_CallbackFunction)(int32_t air_pressure, void *user_data);

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
} ATTRIBUTE_PACKED GetAllValues_Request;

typedef struct {
	PacketHeader header;
	int32_t iaq_index;
	uint8_t iaq_index_accuracy;
	int32_t temperature;
	int32_t humidity;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetAllValues_Response;

typedef struct {
	PacketHeader header;
	int32_t offset;
} ATTRIBUTE_PACKED SetTemperatureOffset_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureOffset_Request;

typedef struct {
	PacketHeader header;
	int32_t offset;
} ATTRIBUTE_PACKED GetTemperatureOffset_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllValuesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllValuesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllValuesCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t iaq_index;
	uint8_t iaq_index_accuracy;
	int32_t temperature;
	int32_t humidity;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AllValues_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIAQIndex_Request;

typedef struct {
	PacketHeader header;
	int32_t iaq_index;
	uint8_t iaq_index_accuracy;
} ATTRIBUTE_PACKED GetIAQIndex_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetIAQIndexCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIAQIndexCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetIAQIndexCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t iaq_index;
	uint8_t iaq_index_accuracy;
} ATTRIBUTE_PACKED IAQIndex_Callback;

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
} ATTRIBUTE_PACKED GetHumidity_Request;

typedef struct {
	PacketHeader header;
	int32_t humidity;
} ATTRIBUTE_PACKED GetHumidity_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetHumidityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetHumidityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetHumidityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t humidity;
} ATTRIBUTE_PACKED Humidity_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressure_Request;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED GetAirPressure_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED SetAirPressureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int32_t min;
	int32_t max;
} ATTRIBUTE_PACKED GetAirPressureCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t air_pressure;
} ATTRIBUTE_PACKED AirPressure_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED RemoveCalibration_Request;

typedef struct {
	PacketHeader header;
	uint8_t duration;
} ATTRIBUTE_PACKED SetBackgroundCalibrationDuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBackgroundCalibrationDuration_Request;

typedef struct {
	PacketHeader header;
	uint8_t duration;
} ATTRIBUTE_PACKED GetBackgroundCalibrationDuration_Response;

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

static void air_quality_callback_wrapper_all_values(DevicePrivate *device_p, Packet *packet) {
	AllValues_CallbackFunction callback_function;
	void *user_data;
	AllValues_Callback *callback;

	if (packet->header.length != sizeof(AllValues_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllValues_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_ALL_VALUES];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_ALL_VALUES];
	callback = (AllValues_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->iaq_index = leconvert_int32_from(callback->iaq_index);
	callback->temperature = leconvert_int32_from(callback->temperature);
	callback->humidity = leconvert_int32_from(callback->humidity);
	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->iaq_index, callback->iaq_index_accuracy, callback->temperature, callback->humidity, callback->air_pressure, user_data);
}

static void air_quality_callback_wrapper_iaq_index(DevicePrivate *device_p, Packet *packet) {
	IAQIndex_CallbackFunction callback_function;
	void *user_data;
	IAQIndex_Callback *callback;

	if (packet->header.length != sizeof(IAQIndex_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (IAQIndex_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_IAQ_INDEX];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_IAQ_INDEX];
	callback = (IAQIndex_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->iaq_index = leconvert_int32_from(callback->iaq_index);

	callback_function(callback->iaq_index, callback->iaq_index_accuracy, user_data);
}

static void air_quality_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	Temperature_CallbackFunction callback_function;
	void *user_data;
	Temperature_Callback *callback;

	if (packet->header.length != sizeof(Temperature_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Temperature_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_TEMPERATURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_TEMPERATURE];
	callback = (Temperature_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int32_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void air_quality_callback_wrapper_humidity(DevicePrivate *device_p, Packet *packet) {
	Humidity_CallbackFunction callback_function;
	void *user_data;
	Humidity_Callback *callback;

	if (packet->header.length != sizeof(Humidity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Humidity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_HUMIDITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_HUMIDITY];
	callback = (Humidity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->humidity = leconvert_int32_from(callback->humidity);

	callback_function(callback->humidity, user_data);
}

static void air_quality_callback_wrapper_air_pressure(DevicePrivate *device_p, Packet *packet) {
	AirPressure_CallbackFunction callback_function;
	void *user_data;
	AirPressure_Callback *callback;

	if (packet->header.length != sizeof(AirPressure_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AirPressure_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_AIR_PRESSURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + AIR_QUALITY_CALLBACK_AIR_PRESSURE];
	callback = (AirPressure_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->air_pressure = leconvert_int32_from(callback->air_pressure);

	callback_function(callback->air_pressure, user_data);
}

void air_quality_create(AirQuality *air_quality, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(air_quality, uid, ipcon_p, 2, 0, 1, AIR_QUALITY_DEVICE_IDENTIFIER);

	device_p = air_quality->p;

	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_ALL_VALUES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_TEMPERATURE_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_TEMPERATURE_OFFSET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_ALL_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_ALL_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_IAQ_INDEX] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_IAQ_INDEX_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_IAQ_INDEX_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_HUMIDITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_HUMIDITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_HUMIDITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_AIR_PRESSURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_AIR_PRESSURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_REMOVE_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_BACKGROUND_CALIBRATION_DURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_BACKGROUND_CALIBRATION_DURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[AIR_QUALITY_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[AIR_QUALITY_CALLBACK_ALL_VALUES] = air_quality_callback_wrapper_all_values;
	device_p->callback_wrappers[AIR_QUALITY_CALLBACK_IAQ_INDEX] = air_quality_callback_wrapper_iaq_index;
	device_p->callback_wrappers[AIR_QUALITY_CALLBACK_TEMPERATURE] = air_quality_callback_wrapper_temperature;
	device_p->callback_wrappers[AIR_QUALITY_CALLBACK_HUMIDITY] = air_quality_callback_wrapper_humidity;
	device_p->callback_wrappers[AIR_QUALITY_CALLBACK_AIR_PRESSURE] = air_quality_callback_wrapper_air_pressure;

	ipcon_add_device(ipcon_p, device_p);
}

void air_quality_destroy(AirQuality *air_quality) {
	device_release(air_quality->p);
}

int air_quality_get_response_expected(AirQuality *air_quality, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(air_quality->p, function_id, ret_response_expected);
}

int air_quality_set_response_expected(AirQuality *air_quality, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(air_quality->p, function_id, response_expected);
}

int air_quality_set_response_expected_all(AirQuality *air_quality, bool response_expected) {
	return device_set_response_expected_all(air_quality->p, response_expected);
}

void air_quality_register_callback(AirQuality *air_quality, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(air_quality->p, callback_id, function, user_data);
}

int air_quality_get_api_version(AirQuality *air_quality, uint8_t ret_api_version[3]) {
	return device_get_api_version(air_quality->p, ret_api_version);
}

int air_quality_get_all_values(AirQuality *air_quality, int32_t *ret_iaq_index, uint8_t *ret_iaq_index_accuracy, int32_t *ret_temperature, int32_t *ret_humidity, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = air_quality->p;
	GetAllValues_Request request;
	GetAllValues_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_ALL_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_iaq_index = leconvert_int32_from(response.iaq_index);
	*ret_iaq_index_accuracy = response.iaq_index_accuracy;
	*ret_temperature = leconvert_int32_from(response.temperature);
	*ret_humidity = leconvert_int32_from(response.humidity);
	*ret_air_pressure = leconvert_int32_from(response.air_pressure);

	return ret;
}

int air_quality_set_temperature_offset(AirQuality *air_quality, int32_t offset) {
	DevicePrivate *device_p = air_quality->p;
	SetTemperatureOffset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_TEMPERATURE_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = leconvert_int32_to(offset);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_get_temperature_offset(AirQuality *air_quality, int32_t *ret_offset) {
	DevicePrivate *device_p = air_quality->p;
	GetTemperatureOffset_Request request;
	GetTemperatureOffset_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_TEMPERATURE_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_offset = leconvert_int32_from(response.offset);

	return ret;
}

int air_quality_set_all_values_callback_configuration(AirQuality *air_quality, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = air_quality->p;
	SetAllValuesCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_ALL_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_get_all_values_callback_configuration(AirQuality *air_quality, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = air_quality->p;
	GetAllValuesCallbackConfiguration_Request request;
	GetAllValuesCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_ALL_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_iaq_index(AirQuality *air_quality, int32_t *ret_iaq_index, uint8_t *ret_iaq_index_accuracy) {
	DevicePrivate *device_p = air_quality->p;
	GetIAQIndex_Request request;
	GetIAQIndex_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_IAQ_INDEX, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_iaq_index = leconvert_int32_from(response.iaq_index);
	*ret_iaq_index_accuracy = response.iaq_index_accuracy;

	return ret;
}

int air_quality_set_iaq_index_callback_configuration(AirQuality *air_quality, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = air_quality->p;
	SetIAQIndexCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_IAQ_INDEX_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_get_iaq_index_callback_configuration(AirQuality *air_quality, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = air_quality->p;
	GetIAQIndexCallbackConfiguration_Request request;
	GetIAQIndexCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_IAQ_INDEX_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_temperature(AirQuality *air_quality, int32_t *ret_temperature) {
	DevicePrivate *device_p = air_quality->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

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

int air_quality_set_temperature_callback_configuration(AirQuality *air_quality, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = air_quality->p;
	SetTemperatureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_temperature_callback_configuration(AirQuality *air_quality, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = air_quality->p;
	GetTemperatureCallbackConfiguration_Request request;
	GetTemperatureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_humidity(AirQuality *air_quality, int32_t *ret_humidity) {
	DevicePrivate *device_p = air_quality->p;
	GetHumidity_Request request;
	GetHumidity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_HUMIDITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_humidity = leconvert_int32_from(response.humidity);

	return ret;
}

int air_quality_set_humidity_callback_configuration(AirQuality *air_quality, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = air_quality->p;
	SetHumidityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_HUMIDITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_humidity_callback_configuration(AirQuality *air_quality, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = air_quality->p;
	GetHumidityCallbackConfiguration_Request request;
	GetHumidityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_HUMIDITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_air_pressure(AirQuality *air_quality, int32_t *ret_air_pressure) {
	DevicePrivate *device_p = air_quality->p;
	GetAirPressure_Request request;
	GetAirPressure_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_air_pressure = leconvert_int32_from(response.air_pressure);

	return ret;
}

int air_quality_set_air_pressure_callback_configuration(AirQuality *air_quality, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max) {
	DevicePrivate *device_p = air_quality->p;
	SetAirPressureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_AIR_PRESSURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_get_air_pressure_callback_configuration(AirQuality *air_quality, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max) {
	DevicePrivate *device_p = air_quality->p;
	GetAirPressureCallbackConfiguration_Request request;
	GetAirPressureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_AIR_PRESSURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int air_quality_remove_calibration(AirQuality *air_quality) {
	DevicePrivate *device_p = air_quality->p;
	RemoveCalibration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_REMOVE_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_set_background_calibration_duration(AirQuality *air_quality, uint8_t duration) {
	DevicePrivate *device_p = air_quality->p;
	SetBackgroundCalibrationDuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_BACKGROUND_CALIBRATION_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.duration = duration;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_get_background_calibration_duration(AirQuality *air_quality, uint8_t *ret_duration) {
	DevicePrivate *device_p = air_quality->p;
	GetBackgroundCalibrationDuration_Request request;
	GetBackgroundCalibrationDuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_BACKGROUND_CALIBRATION_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_duration = response.duration;

	return ret;
}

int air_quality_get_spitfp_error_count(AirQuality *air_quality, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = air_quality->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int air_quality_set_bootloader_mode(AirQuality *air_quality, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = air_quality->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int air_quality_get_bootloader_mode(AirQuality *air_quality, uint8_t *ret_mode) {
	DevicePrivate *device_p = air_quality->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int air_quality_set_write_firmware_pointer(AirQuality *air_quality, uint32_t pointer) {
	DevicePrivate *device_p = air_quality->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_write_firmware(AirQuality *air_quality, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = air_quality->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int air_quality_set_status_led_config(AirQuality *air_quality, uint8_t config) {
	DevicePrivate *device_p = air_quality->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_get_status_led_config(AirQuality *air_quality, uint8_t *ret_config) {
	DevicePrivate *device_p = air_quality->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int air_quality_get_chip_temperature(AirQuality *air_quality, int16_t *ret_temperature) {
	DevicePrivate *device_p = air_quality->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int air_quality_reset(AirQuality *air_quality) {
	DevicePrivate *device_p = air_quality->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_write_uid(AirQuality *air_quality, uint32_t uid) {
	DevicePrivate *device_p = air_quality->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int air_quality_read_uid(AirQuality *air_quality, uint32_t *ret_uid) {
	DevicePrivate *device_p = air_quality->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int air_quality_get_identity(AirQuality *air_quality, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = air_quality->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), AIR_QUALITY_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
