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

#include "bricklet_particulate_matter.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*PMConcentration_CallbackFunction)(uint16_t pm10, uint16_t pm25, uint16_t pm100, void *user_data);

typedef void (*PMCount_CallbackFunction)(uint16_t greater03um, uint16_t greater05um, uint16_t greater10um, uint16_t greater25um, uint16_t greater50um, uint16_t greater100um, void *user_data);

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
} ATTRIBUTE_PACKED GetPMConcentration_Request;

typedef struct {
	PacketHeader header;
	uint16_t pm10;
	uint16_t pm25;
	uint16_t pm100;
} ATTRIBUTE_PACKED GetPMConcentration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPMCount_Request;

typedef struct {
	PacketHeader header;
	uint16_t greater03um;
	uint16_t greater05um;
	uint16_t greater10um;
	uint16_t greater25um;
	uint16_t greater50um;
	uint16_t greater100um;
} ATTRIBUTE_PACKED GetPMCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED SetEnable_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEnable_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED GetEnable_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorInfo_Request;

typedef struct {
	PacketHeader header;
	uint8_t sensor_version;
	uint8_t last_error_code;
	uint8_t framing_error_count;
	uint8_t checksum_error_count;
} ATTRIBUTE_PACKED GetSensorInfo_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetPMConcentrationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPMConcentrationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetPMConcentrationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetPMCountCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPMCountCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetPMCountCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t pm10;
	uint16_t pm25;
	uint16_t pm100;
} ATTRIBUTE_PACKED PMConcentration_Callback;

typedef struct {
	PacketHeader header;
	uint16_t greater03um;
	uint16_t greater05um;
	uint16_t greater10um;
	uint16_t greater25um;
	uint16_t greater50um;
	uint16_t greater100um;
} ATTRIBUTE_PACKED PMCount_Callback;

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

static void particulate_matter_callback_wrapper_pm_concentration(DevicePrivate *device_p, Packet *packet) {
	PMConcentration_CallbackFunction callback_function;
	void *user_data;
	PMConcentration_Callback *callback;

	if (packet->header.length != sizeof(PMConcentration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PMConcentration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PARTICULATE_MATTER_CALLBACK_PM_CONCENTRATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PARTICULATE_MATTER_CALLBACK_PM_CONCENTRATION];
	callback = (PMConcentration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->pm10 = leconvert_uint16_from(callback->pm10);
	callback->pm25 = leconvert_uint16_from(callback->pm25);
	callback->pm100 = leconvert_uint16_from(callback->pm100);

	callback_function(callback->pm10, callback->pm25, callback->pm100, user_data);
}

static void particulate_matter_callback_wrapper_pm_count(DevicePrivate *device_p, Packet *packet) {
	PMCount_CallbackFunction callback_function;
	void *user_data;
	PMCount_Callback *callback;

	if (packet->header.length != sizeof(PMCount_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PMCount_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PARTICULATE_MATTER_CALLBACK_PM_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PARTICULATE_MATTER_CALLBACK_PM_COUNT];
	callback = (PMCount_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->greater03um = leconvert_uint16_from(callback->greater03um);
	callback->greater05um = leconvert_uint16_from(callback->greater05um);
	callback->greater10um = leconvert_uint16_from(callback->greater10um);
	callback->greater25um = leconvert_uint16_from(callback->greater25um);
	callback->greater50um = leconvert_uint16_from(callback->greater50um);
	callback->greater100um = leconvert_uint16_from(callback->greater100um);

	callback_function(callback->greater03um, callback->greater05um, callback->greater10um, callback->greater25um, callback->greater50um, callback->greater100um, user_data);
}

void particulate_matter_create(ParticulateMatter *particulate_matter, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(particulate_matter, uid, ipcon_p, 2, 0, 0, PARTICULATE_MATTER_DEVICE_IDENTIFIER);

	device_p = particulate_matter->p;

	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_PM_CONCENTRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_PM_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_ENABLE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_ENABLE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_SENSOR_INFO] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_PM_CONCENTRATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_PM_CONCENTRATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_PM_COUNT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_PM_COUNT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PARTICULATE_MATTER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PARTICULATE_MATTER_CALLBACK_PM_CONCENTRATION] = particulate_matter_callback_wrapper_pm_concentration;
	device_p->callback_wrappers[PARTICULATE_MATTER_CALLBACK_PM_COUNT] = particulate_matter_callback_wrapper_pm_count;

	ipcon_add_device(ipcon_p, device_p);
}

void particulate_matter_destroy(ParticulateMatter *particulate_matter) {
	device_release(particulate_matter->p);
}

int particulate_matter_get_response_expected(ParticulateMatter *particulate_matter, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(particulate_matter->p, function_id, ret_response_expected);
}

int particulate_matter_set_response_expected(ParticulateMatter *particulate_matter, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(particulate_matter->p, function_id, response_expected);
}

int particulate_matter_set_response_expected_all(ParticulateMatter *particulate_matter, bool response_expected) {
	return device_set_response_expected_all(particulate_matter->p, response_expected);
}

void particulate_matter_register_callback(ParticulateMatter *particulate_matter, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(particulate_matter->p, callback_id, function, user_data);
}

int particulate_matter_get_api_version(ParticulateMatter *particulate_matter, uint8_t ret_api_version[3]) {
	return device_get_api_version(particulate_matter->p, ret_api_version);
}

int particulate_matter_get_pm_concentration(ParticulateMatter *particulate_matter, uint16_t *ret_pm10, uint16_t *ret_pm25, uint16_t *ret_pm100) {
	DevicePrivate *device_p = particulate_matter->p;
	GetPMConcentration_Request request;
	GetPMConcentration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_PM_CONCENTRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pm10 = leconvert_uint16_from(response.pm10);
	*ret_pm25 = leconvert_uint16_from(response.pm25);
	*ret_pm100 = leconvert_uint16_from(response.pm100);

	return ret;
}

int particulate_matter_get_pm_count(ParticulateMatter *particulate_matter, uint16_t *ret_greater03um, uint16_t *ret_greater05um, uint16_t *ret_greater10um, uint16_t *ret_greater25um, uint16_t *ret_greater50um, uint16_t *ret_greater100um) {
	DevicePrivate *device_p = particulate_matter->p;
	GetPMCount_Request request;
	GetPMCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_PM_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_greater03um = leconvert_uint16_from(response.greater03um);
	*ret_greater05um = leconvert_uint16_from(response.greater05um);
	*ret_greater10um = leconvert_uint16_from(response.greater10um);
	*ret_greater25um = leconvert_uint16_from(response.greater25um);
	*ret_greater50um = leconvert_uint16_from(response.greater50um);
	*ret_greater100um = leconvert_uint16_from(response.greater100um);

	return ret;
}

int particulate_matter_set_enable(ParticulateMatter *particulate_matter, bool enable) {
	DevicePrivate *device_p = particulate_matter->p;
	SetEnable_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable = enable ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_get_enable(ParticulateMatter *particulate_matter, bool *ret_enable) {
	DevicePrivate *device_p = particulate_matter->p;
	GetEnable_Request request;
	GetEnable_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_ENABLE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;

	return ret;
}

int particulate_matter_get_sensor_info(ParticulateMatter *particulate_matter, uint8_t *ret_sensor_version, uint8_t *ret_last_error_code, uint8_t *ret_framing_error_count, uint8_t *ret_checksum_error_count) {
	DevicePrivate *device_p = particulate_matter->p;
	GetSensorInfo_Request request;
	GetSensorInfo_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_SENSOR_INFO, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_sensor_version = response.sensor_version;
	*ret_last_error_code = response.last_error_code;
	*ret_framing_error_count = response.framing_error_count;
	*ret_checksum_error_count = response.checksum_error_count;

	return ret;
}

int particulate_matter_set_pm_concentration_callback_configuration(ParticulateMatter *particulate_matter, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = particulate_matter->p;
	SetPMConcentrationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_PM_CONCENTRATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_get_pm_concentration_callback_configuration(ParticulateMatter *particulate_matter, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = particulate_matter->p;
	GetPMConcentrationCallbackConfiguration_Request request;
	GetPMConcentrationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_PM_CONCENTRATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int particulate_matter_set_pm_count_callback_configuration(ParticulateMatter *particulate_matter, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = particulate_matter->p;
	SetPMCountCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_PM_COUNT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_get_pm_count_callback_configuration(ParticulateMatter *particulate_matter, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = particulate_matter->p;
	GetPMCountCallbackConfiguration_Request request;
	GetPMCountCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_PM_COUNT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int particulate_matter_get_spitfp_error_count(ParticulateMatter *particulate_matter, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = particulate_matter->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int particulate_matter_set_bootloader_mode(ParticulateMatter *particulate_matter, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = particulate_matter->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int particulate_matter_get_bootloader_mode(ParticulateMatter *particulate_matter, uint8_t *ret_mode) {
	DevicePrivate *device_p = particulate_matter->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int particulate_matter_set_write_firmware_pointer(ParticulateMatter *particulate_matter, uint32_t pointer) {
	DevicePrivate *device_p = particulate_matter->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_write_firmware(ParticulateMatter *particulate_matter, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = particulate_matter->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int particulate_matter_set_status_led_config(ParticulateMatter *particulate_matter, uint8_t config) {
	DevicePrivate *device_p = particulate_matter->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_get_status_led_config(ParticulateMatter *particulate_matter, uint8_t *ret_config) {
	DevicePrivate *device_p = particulate_matter->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int particulate_matter_get_chip_temperature(ParticulateMatter *particulate_matter, int16_t *ret_temperature) {
	DevicePrivate *device_p = particulate_matter->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int particulate_matter_reset(ParticulateMatter *particulate_matter) {
	DevicePrivate *device_p = particulate_matter->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_write_uid(ParticulateMatter *particulate_matter, uint32_t uid) {
	DevicePrivate *device_p = particulate_matter->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int particulate_matter_read_uid(ParticulateMatter *particulate_matter, uint32_t *ret_uid) {
	DevicePrivate *device_p = particulate_matter->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int particulate_matter_get_identity(ParticulateMatter *particulate_matter, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = particulate_matter->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PARTICULATE_MATTER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
