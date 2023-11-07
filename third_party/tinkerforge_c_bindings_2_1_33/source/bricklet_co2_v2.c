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

#include "bricklet_co2_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AllValues_CallbackFunction)(uint16_t co2_concentration, int16_t temperature, uint16_t humidity, void *user_data);

typedef void (*CO2Concentration_CallbackFunction)(uint16_t co2_concentration, void *user_data);

typedef void (*Temperature_CallbackFunction)(int16_t temperature, void *user_data);

typedef void (*Humidity_CallbackFunction)(uint16_t humidity, void *user_data);

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
	uint16_t co2_concentration;
	int16_t temperature;
	uint16_t humidity;
} ATTRIBUTE_PACKED GetAllValues_Response;

typedef struct {
	PacketHeader header;
	uint16_t air_pressure;
} ATTRIBUTE_PACKED SetAirPressure_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAirPressure_Request;

typedef struct {
	PacketHeader header;
	uint16_t air_pressure;
} ATTRIBUTE_PACKED GetAirPressure_Response;

typedef struct {
	PacketHeader header;
	uint16_t offset;
} ATTRIBUTE_PACKED SetTemperatureOffset_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureOffset_Request;

typedef struct {
	PacketHeader header;
	uint16_t offset;
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
	uint16_t co2_concentration;
	int16_t temperature;
	uint16_t humidity;
} ATTRIBUTE_PACKED AllValues_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2Concentration_Request;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED GetCO2Concentration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetCO2ConcentrationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED CO2Concentration_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetTemperature_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED Temperature_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetHumidity_Request;

typedef struct {
	PacketHeader header;
	uint16_t humidity;
} ATTRIBUTE_PACKED GetHumidity_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetHumidityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetHumidityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetHumidityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t humidity;
} ATTRIBUTE_PACKED Humidity_Callback;

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

static void co2_v2_callback_wrapper_all_values(DevicePrivate *device_p, Packet *packet) {
	AllValues_CallbackFunction callback_function;
	void *user_data;
	AllValues_Callback *callback;

	if (packet->header.length != sizeof(AllValues_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllValues_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_ALL_VALUES];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_ALL_VALUES];
	callback = (AllValues_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);
	callback->temperature = leconvert_int16_from(callback->temperature);
	callback->humidity = leconvert_uint16_from(callback->humidity);

	callback_function(callback->co2_concentration, callback->temperature, callback->humidity, user_data);
}

static void co2_v2_callback_wrapper_co2_concentration(DevicePrivate *device_p, Packet *packet) {
	CO2Concentration_CallbackFunction callback_function;
	void *user_data;
	CO2Concentration_Callback *callback;

	if (packet->header.length != sizeof(CO2Concentration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CO2Concentration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_CO2_CONCENTRATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_CO2_CONCENTRATION];
	callback = (CO2Concentration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);

	callback_function(callback->co2_concentration, user_data);
}

static void co2_v2_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	Temperature_CallbackFunction callback_function;
	void *user_data;
	Temperature_Callback *callback;

	if (packet->header.length != sizeof(Temperature_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Temperature_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_TEMPERATURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_TEMPERATURE];
	callback = (Temperature_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int16_from(callback->temperature);

	callback_function(callback->temperature, user_data);
}

static void co2_v2_callback_wrapper_humidity(DevicePrivate *device_p, Packet *packet) {
	Humidity_CallbackFunction callback_function;
	void *user_data;
	Humidity_Callback *callback;

	if (packet->header.length != sizeof(Humidity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Humidity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_HUMIDITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_V2_CALLBACK_HUMIDITY];
	callback = (Humidity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->humidity = leconvert_uint16_from(callback->humidity);

	callback_function(callback->humidity, user_data);
}

void co2_v2_create(CO2V2 *co2_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(co2_v2, uid, ipcon_p, 2, 0, 0, CO2_V2_DEVICE_IDENTIFIER);

	device_p = co2_v2->p;

	device_p->response_expected[CO2_V2_FUNCTION_GET_ALL_VALUES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_AIR_PRESSURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_TEMPERATURE_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_TEMPERATURE_OFFSET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_ALL_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_ALL_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_CO2_CONCENTRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_HUMIDITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_HUMIDITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_HUMIDITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CO2_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CO2_V2_CALLBACK_ALL_VALUES] = co2_v2_callback_wrapper_all_values;
	device_p->callback_wrappers[CO2_V2_CALLBACK_CO2_CONCENTRATION] = co2_v2_callback_wrapper_co2_concentration;
	device_p->callback_wrappers[CO2_V2_CALLBACK_TEMPERATURE] = co2_v2_callback_wrapper_temperature;
	device_p->callback_wrappers[CO2_V2_CALLBACK_HUMIDITY] = co2_v2_callback_wrapper_humidity;

	ipcon_add_device(ipcon_p, device_p);
}

void co2_v2_destroy(CO2V2 *co2_v2) {
	device_release(co2_v2->p);
}

int co2_v2_get_response_expected(CO2V2 *co2_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(co2_v2->p, function_id, ret_response_expected);
}

int co2_v2_set_response_expected(CO2V2 *co2_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(co2_v2->p, function_id, response_expected);
}

int co2_v2_set_response_expected_all(CO2V2 *co2_v2, bool response_expected) {
	return device_set_response_expected_all(co2_v2->p, response_expected);
}

void co2_v2_register_callback(CO2V2 *co2_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(co2_v2->p, callback_id, function, user_data);
}

int co2_v2_get_api_version(CO2V2 *co2_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(co2_v2->p, ret_api_version);
}

int co2_v2_get_all_values(CO2V2 *co2_v2, uint16_t *ret_co2_concentration, int16_t *ret_temperature, uint16_t *ret_humidity) {
	DevicePrivate *device_p = co2_v2->p;
	GetAllValues_Request request;
	GetAllValues_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_ALL_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_co2_concentration = leconvert_uint16_from(response.co2_concentration);
	*ret_temperature = leconvert_int16_from(response.temperature);
	*ret_humidity = leconvert_uint16_from(response.humidity);

	return ret;
}

int co2_v2_set_air_pressure(CO2V2 *co2_v2, uint16_t air_pressure) {
	DevicePrivate *device_p = co2_v2->p;
	SetAirPressure_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.air_pressure = leconvert_uint16_to(air_pressure);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_get_air_pressure(CO2V2 *co2_v2, uint16_t *ret_air_pressure) {
	DevicePrivate *device_p = co2_v2->p;
	GetAirPressure_Request request;
	GetAirPressure_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_AIR_PRESSURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_air_pressure = leconvert_uint16_from(response.air_pressure);

	return ret;
}

int co2_v2_set_temperature_offset(CO2V2 *co2_v2, uint16_t offset) {
	DevicePrivate *device_p = co2_v2->p;
	SetTemperatureOffset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_TEMPERATURE_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = leconvert_uint16_to(offset);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_get_temperature_offset(CO2V2 *co2_v2, uint16_t *ret_offset) {
	DevicePrivate *device_p = co2_v2->p;
	GetTemperatureOffset_Request request;
	GetTemperatureOffset_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_TEMPERATURE_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_offset = leconvert_uint16_from(response.offset);

	return ret;
}

int co2_v2_set_all_values_callback_configuration(CO2V2 *co2_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = co2_v2->p;
	SetAllValuesCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_ALL_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_get_all_values_callback_configuration(CO2V2 *co2_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = co2_v2->p;
	GetAllValuesCallbackConfiguration_Request request;
	GetAllValuesCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_ALL_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_co2_concentration(CO2V2 *co2_v2, uint16_t *ret_co2_concentration) {
	DevicePrivate *device_p = co2_v2->p;
	GetCO2Concentration_Request request;
	GetCO2Concentration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_CO2_CONCENTRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_co2_concentration = leconvert_uint16_from(response.co2_concentration);

	return ret;
}

int co2_v2_set_co2_concentration_callback_configuration(CO2V2 *co2_v2, uint32_t period, bool value_has_to_change, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = co2_v2->p;
	SetCO2ConcentrationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_co2_concentration_callback_configuration(CO2V2 *co2_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = co2_v2->p;
	GetCO2ConcentrationCallbackConfiguration_Request request;
	GetCO2ConcentrationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_temperature(CO2V2 *co2_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = co2_v2->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

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

int co2_v2_set_temperature_callback_configuration(CO2V2 *co2_v2, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = co2_v2->p;
	SetTemperatureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_temperature_callback_configuration(CO2V2 *co2_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = co2_v2->p;
	GetTemperatureCallbackConfiguration_Request request;
	GetTemperatureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_humidity(CO2V2 *co2_v2, uint16_t *ret_humidity) {
	DevicePrivate *device_p = co2_v2->p;
	GetHumidity_Request request;
	GetHumidity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_HUMIDITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_humidity = leconvert_uint16_from(response.humidity);

	return ret;
}

int co2_v2_set_humidity_callback_configuration(CO2V2 *co2_v2, uint32_t period, bool value_has_to_change, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = co2_v2->p;
	SetHumidityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_HUMIDITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_humidity_callback_configuration(CO2V2 *co2_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = co2_v2->p;
	GetHumidityCallbackConfiguration_Request request;
	GetHumidityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_HUMIDITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int co2_v2_get_spitfp_error_count(CO2V2 *co2_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = co2_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int co2_v2_set_bootloader_mode(CO2V2 *co2_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = co2_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int co2_v2_get_bootloader_mode(CO2V2 *co2_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = co2_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int co2_v2_set_write_firmware_pointer(CO2V2 *co2_v2, uint32_t pointer) {
	DevicePrivate *device_p = co2_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_write_firmware(CO2V2 *co2_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = co2_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int co2_v2_set_status_led_config(CO2V2 *co2_v2, uint8_t config) {
	DevicePrivate *device_p = co2_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_get_status_led_config(CO2V2 *co2_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = co2_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int co2_v2_get_chip_temperature(CO2V2 *co2_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = co2_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int co2_v2_reset(CO2V2 *co2_v2) {
	DevicePrivate *device_p = co2_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_write_uid(CO2V2 *co2_v2, uint32_t uid) {
	DevicePrivate *device_p = co2_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_v2_read_uid(CO2V2 *co2_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = co2_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int co2_v2_get_identity(CO2V2 *co2_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = co2_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
