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

#include "bricklet_outdoor_weather.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*StationData_CallbackFunction)(uint8_t identifier, int16_t temperature, uint8_t humidity, uint32_t wind_speed, uint32_t gust_speed, uint32_t rain, uint8_t wind_direction, bool battery_low, void *user_data);

typedef void (*SensorData_CallbackFunction)(uint8_t identifier, int16_t temperature, uint8_t humidity, void *user_data);

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
} ATTRIBUTE_PACKED GetStationIdentifiersLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t identifiers_length;
	uint16_t identifiers_chunk_offset;
	uint8_t identifiers_chunk_data[60];
} ATTRIBUTE_PACKED GetStationIdentifiersLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorIdentifiersLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t identifiers_length;
	uint16_t identifiers_chunk_offset;
	uint8_t identifiers_chunk_data[60];
} ATTRIBUTE_PACKED GetSensorIdentifiersLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t identifier;
} ATTRIBUTE_PACKED GetStationData_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
	uint8_t humidity;
	uint32_t wind_speed;
	uint32_t gust_speed;
	uint32_t rain;
	uint8_t wind_direction;
	uint8_t battery_low;
	uint16_t last_change;
} ATTRIBUTE_PACKED GetStationData_Response;

typedef struct {
	PacketHeader header;
	uint8_t identifier;
} ATTRIBUTE_PACKED GetSensorData_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
	uint8_t humidity;
	uint16_t last_change;
} ATTRIBUTE_PACKED GetSensorData_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_callback;
} ATTRIBUTE_PACKED SetStationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_callback;
} ATTRIBUTE_PACKED GetStationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_callback;
} ATTRIBUTE_PACKED SetSensorCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_callback;
} ATTRIBUTE_PACKED GetSensorCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t identifier;
	int16_t temperature;
	uint8_t humidity;
	uint32_t wind_speed;
	uint32_t gust_speed;
	uint32_t rain;
	uint8_t wind_direction;
	uint8_t battery_low;
} ATTRIBUTE_PACKED StationData_Callback;

typedef struct {
	PacketHeader header;
	uint8_t identifier;
	int16_t temperature;
	uint8_t humidity;
} ATTRIBUTE_PACKED SensorData_Callback;

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

static void outdoor_weather_callback_wrapper_station_data(DevicePrivate *device_p, Packet *packet) {
	StationData_CallbackFunction callback_function;
	void *user_data;
	StationData_Callback *callback;
	bool unpacked_battery_low;

	if (packet->header.length != sizeof(StationData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StationData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + OUTDOOR_WEATHER_CALLBACK_STATION_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + OUTDOOR_WEATHER_CALLBACK_STATION_DATA];
	callback = (StationData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int16_from(callback->temperature);
	callback->wind_speed = leconvert_uint32_from(callback->wind_speed);
	callback->gust_speed = leconvert_uint32_from(callback->gust_speed);
	callback->rain = leconvert_uint32_from(callback->rain);
	unpacked_battery_low = callback->battery_low != 0;

	callback_function(callback->identifier, callback->temperature, callback->humidity, callback->wind_speed, callback->gust_speed, callback->rain, callback->wind_direction, unpacked_battery_low, user_data);
}

static void outdoor_weather_callback_wrapper_sensor_data(DevicePrivate *device_p, Packet *packet) {
	SensorData_CallbackFunction callback_function;
	void *user_data;
	SensorData_Callback *callback;

	if (packet->header.length != sizeof(SensorData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SensorData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + OUTDOOR_WEATHER_CALLBACK_SENSOR_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + OUTDOOR_WEATHER_CALLBACK_SENSOR_DATA];
	callback = (SensorData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->temperature = leconvert_int16_from(callback->temperature);

	callback_function(callback->identifier, callback->temperature, callback->humidity, user_data);
}

void outdoor_weather_create(OutdoorWeather *outdoor_weather, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(outdoor_weather, uid, ipcon_p, 2, 0, 0, OUTDOOR_WEATHER_DEVICE_IDENTIFIER);

	device_p = outdoor_weather->p;

	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_STATION_IDENTIFIERS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_IDENTIFIERS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_STATION_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_SET_STATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_STATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_SET_SENSOR_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OUTDOOR_WEATHER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[OUTDOOR_WEATHER_CALLBACK_STATION_DATA] = outdoor_weather_callback_wrapper_station_data;
	device_p->callback_wrappers[OUTDOOR_WEATHER_CALLBACK_SENSOR_DATA] = outdoor_weather_callback_wrapper_sensor_data;

	ipcon_add_device(ipcon_p, device_p);
}

void outdoor_weather_destroy(OutdoorWeather *outdoor_weather) {
	device_release(outdoor_weather->p);
}

int outdoor_weather_get_response_expected(OutdoorWeather *outdoor_weather, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(outdoor_weather->p, function_id, ret_response_expected);
}

int outdoor_weather_set_response_expected(OutdoorWeather *outdoor_weather, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(outdoor_weather->p, function_id, response_expected);
}

int outdoor_weather_set_response_expected_all(OutdoorWeather *outdoor_weather, bool response_expected) {
	return device_set_response_expected_all(outdoor_weather->p, response_expected);
}

void outdoor_weather_register_callback(OutdoorWeather *outdoor_weather, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(outdoor_weather->p, callback_id, function, user_data);
}

int outdoor_weather_get_api_version(OutdoorWeather *outdoor_weather, uint8_t ret_api_version[3]) {
	return device_get_api_version(outdoor_weather->p, ret_api_version);
}

int outdoor_weather_get_station_identifiers_low_level(OutdoorWeather *outdoor_weather, uint16_t *ret_identifiers_length, uint16_t *ret_identifiers_chunk_offset, uint8_t ret_identifiers_chunk_data[60]) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetStationIdentifiersLowLevel_Request request;
	GetStationIdentifiersLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_STATION_IDENTIFIERS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_identifiers_length = leconvert_uint16_from(response.identifiers_length);
	*ret_identifiers_chunk_offset = leconvert_uint16_from(response.identifiers_chunk_offset);
	memcpy(ret_identifiers_chunk_data, response.identifiers_chunk_data, 60 * sizeof(uint8_t));

	return ret;
}

int outdoor_weather_get_sensor_identifiers_low_level(OutdoorWeather *outdoor_weather, uint16_t *ret_identifiers_length, uint16_t *ret_identifiers_chunk_offset, uint8_t ret_identifiers_chunk_data[60]) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetSensorIdentifiersLowLevel_Request request;
	GetSensorIdentifiersLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_IDENTIFIERS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_identifiers_length = leconvert_uint16_from(response.identifiers_length);
	*ret_identifiers_chunk_offset = leconvert_uint16_from(response.identifiers_chunk_offset);
	memcpy(ret_identifiers_chunk_data, response.identifiers_chunk_data, 60 * sizeof(uint8_t));

	return ret;
}

int outdoor_weather_get_station_data(OutdoorWeather *outdoor_weather, uint8_t identifier, int16_t *ret_temperature, uint8_t *ret_humidity, uint32_t *ret_wind_speed, uint32_t *ret_gust_speed, uint32_t *ret_rain, uint8_t *ret_wind_direction, bool *ret_battery_low, uint16_t *ret_last_change) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetStationData_Request request;
	GetStationData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_STATION_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.identifier = identifier;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int16_from(response.temperature);
	*ret_humidity = response.humidity;
	*ret_wind_speed = leconvert_uint32_from(response.wind_speed);
	*ret_gust_speed = leconvert_uint32_from(response.gust_speed);
	*ret_rain = leconvert_uint32_from(response.rain);
	*ret_wind_direction = response.wind_direction;
	*ret_battery_low = response.battery_low != 0;
	*ret_last_change = leconvert_uint16_from(response.last_change);

	return ret;
}

int outdoor_weather_get_sensor_data(OutdoorWeather *outdoor_weather, uint8_t identifier, int16_t *ret_temperature, uint8_t *ret_humidity, uint16_t *ret_last_change) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetSensorData_Request request;
	GetSensorData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.identifier = identifier;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int16_from(response.temperature);
	*ret_humidity = response.humidity;
	*ret_last_change = leconvert_uint16_from(response.last_change);

	return ret;
}

int outdoor_weather_set_station_callback_configuration(OutdoorWeather *outdoor_weather, bool enable_callback) {
	DevicePrivate *device_p = outdoor_weather->p;
	SetStationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_SET_STATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_callback = enable_callback ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_get_station_callback_configuration(OutdoorWeather *outdoor_weather, bool *ret_enable_callback) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetStationCallbackConfiguration_Request request;
	GetStationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_STATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_callback = response.enable_callback != 0;

	return ret;
}

int outdoor_weather_set_sensor_callback_configuration(OutdoorWeather *outdoor_weather, bool enable_callback) {
	DevicePrivate *device_p = outdoor_weather->p;
	SetSensorCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_SET_SENSOR_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_callback = enable_callback ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_get_sensor_callback_configuration(OutdoorWeather *outdoor_weather, bool *ret_enable_callback) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetSensorCallbackConfiguration_Request request;
	GetSensorCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_SENSOR_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_callback = response.enable_callback != 0;

	return ret;
}

int outdoor_weather_get_spitfp_error_count(OutdoorWeather *outdoor_weather, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int outdoor_weather_set_bootloader_mode(OutdoorWeather *outdoor_weather, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = outdoor_weather->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int outdoor_weather_get_bootloader_mode(OutdoorWeather *outdoor_weather, uint8_t *ret_mode) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int outdoor_weather_set_write_firmware_pointer(OutdoorWeather *outdoor_weather, uint32_t pointer) {
	DevicePrivate *device_p = outdoor_weather->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_write_firmware(OutdoorWeather *outdoor_weather, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = outdoor_weather->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int outdoor_weather_set_status_led_config(OutdoorWeather *outdoor_weather, uint8_t config) {
	DevicePrivate *device_p = outdoor_weather->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_get_status_led_config(OutdoorWeather *outdoor_weather, uint8_t *ret_config) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int outdoor_weather_get_chip_temperature(OutdoorWeather *outdoor_weather, int16_t *ret_temperature) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int outdoor_weather_reset(OutdoorWeather *outdoor_weather) {
	DevicePrivate *device_p = outdoor_weather->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_write_uid(OutdoorWeather *outdoor_weather, uint32_t uid) {
	DevicePrivate *device_p = outdoor_weather->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int outdoor_weather_read_uid(OutdoorWeather *outdoor_weather, uint32_t *ret_uid) {
	DevicePrivate *device_p = outdoor_weather->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int outdoor_weather_get_identity(OutdoorWeather *outdoor_weather, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = outdoor_weather->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OUTDOOR_WEATHER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int outdoor_weather_get_station_identifiers(OutdoorWeather *outdoor_weather, uint8_t *ret_identifiers, uint16_t *ret_identifiers_length) {
	DevicePrivate *device_p = outdoor_weather->p;
	int ret = 0;
	uint16_t identifiers_length = 0;
	uint16_t identifiers_chunk_offset;
	uint8_t identifiers_chunk_data[60];
	bool identifiers_out_of_sync;
	uint16_t identifiers_chunk_length;

	*ret_identifiers_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = outdoor_weather_get_station_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	identifiers_out_of_sync = identifiers_chunk_offset != 0;

	if (!identifiers_out_of_sync) {
		identifiers_chunk_length = identifiers_length - identifiers_chunk_offset;

		if (identifiers_chunk_length > 60) {
			identifiers_chunk_length = 60;
		}

		memcpy(ret_identifiers, identifiers_chunk_data, sizeof(uint8_t) * identifiers_chunk_length);
		*ret_identifiers_length = identifiers_chunk_length;

		while (*ret_identifiers_length < identifiers_length) {
			ret = outdoor_weather_get_station_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			identifiers_out_of_sync = identifiers_chunk_offset != *ret_identifiers_length;

			if (identifiers_out_of_sync) {
				break;
			}

			identifiers_chunk_length = identifiers_length - identifiers_chunk_offset;

			if (identifiers_chunk_length > 60) {
				identifiers_chunk_length = 60;
			}

			memcpy(&ret_identifiers[*ret_identifiers_length], identifiers_chunk_data, sizeof(uint8_t) * identifiers_chunk_length);
			*ret_identifiers_length += identifiers_chunk_length;
		}
	}

	if (identifiers_out_of_sync) {
		*ret_identifiers_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (identifiers_chunk_offset + 60 < identifiers_length) {
			ret = outdoor_weather_get_station_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

int outdoor_weather_get_sensor_identifiers(OutdoorWeather *outdoor_weather, uint8_t *ret_identifiers, uint16_t *ret_identifiers_length) {
	DevicePrivate *device_p = outdoor_weather->p;
	int ret = 0;
	uint16_t identifiers_length = 0;
	uint16_t identifiers_chunk_offset;
	uint8_t identifiers_chunk_data[60];
	bool identifiers_out_of_sync;
	uint16_t identifiers_chunk_length;

	*ret_identifiers_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = outdoor_weather_get_sensor_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	identifiers_out_of_sync = identifiers_chunk_offset != 0;

	if (!identifiers_out_of_sync) {
		identifiers_chunk_length = identifiers_length - identifiers_chunk_offset;

		if (identifiers_chunk_length > 60) {
			identifiers_chunk_length = 60;
		}

		memcpy(ret_identifiers, identifiers_chunk_data, sizeof(uint8_t) * identifiers_chunk_length);
		*ret_identifiers_length = identifiers_chunk_length;

		while (*ret_identifiers_length < identifiers_length) {
			ret = outdoor_weather_get_sensor_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			identifiers_out_of_sync = identifiers_chunk_offset != *ret_identifiers_length;

			if (identifiers_out_of_sync) {
				break;
			}

			identifiers_chunk_length = identifiers_length - identifiers_chunk_offset;

			if (identifiers_chunk_length > 60) {
				identifiers_chunk_length = 60;
			}

			memcpy(&ret_identifiers[*ret_identifiers_length], identifiers_chunk_data, sizeof(uint8_t) * identifiers_chunk_length);
			*ret_identifiers_length += identifiers_chunk_length;
		}
	}

	if (identifiers_out_of_sync) {
		*ret_identifiers_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (identifiers_chunk_offset + 60 < identifiers_length) {
			ret = outdoor_weather_get_sensor_identifiers_low_level(outdoor_weather, &identifiers_length, &identifiers_chunk_offset, identifiers_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

#ifdef __cplusplus
}
#endif
