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

#include "bricklet_energy_monitor.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*EnergyData_CallbackFunction)(int32_t voltage, int32_t current, int32_t energy, int32_t real_power, int32_t apparent_power, int32_t reactive_power, uint16_t power_factor, uint16_t frequency, void *user_data);

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
} ATTRIBUTE_PACKED GetEnergyData_Request;

typedef struct {
	PacketHeader header;
	int32_t voltage;
	int32_t current;
	int32_t energy;
	int32_t real_power;
	int32_t apparent_power;
	int32_t reactive_power;
	uint16_t power_factor;
	uint16_t frequency;
} ATTRIBUTE_PACKED GetEnergyData_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ResetEnergy_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWaveformLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t waveform_chunk_offset;
	int16_t waveform_chunk_data[30];
} ATTRIBUTE_PACKED GetWaveformLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTransformerStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t voltage_transformer_connected;
	uint8_t current_transformer_connected;
} ATTRIBUTE_PACKED GetTransformerStatus_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage_ratio;
	uint16_t current_ratio;
	int16_t phase_shift;
} ATTRIBUTE_PACKED SetTransformerCalibration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTransformerCalibration_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage_ratio;
	uint16_t current_ratio;
	int16_t phase_shift;
} ATTRIBUTE_PACKED GetTransformerCalibration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED CalibrateOffset_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetEnergyDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEnergyDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetEnergyDataCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int32_t voltage;
	int32_t current;
	int32_t energy;
	int32_t real_power;
	int32_t apparent_power;
	int32_t reactive_power;
	uint16_t power_factor;
	uint16_t frequency;
} ATTRIBUTE_PACKED EnergyData_Callback;

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

static void energy_monitor_callback_wrapper_energy_data(DevicePrivate *device_p, Packet *packet) {
	EnergyData_CallbackFunction callback_function;
	void *user_data;
	EnergyData_Callback *callback;

	if (packet->header.length != sizeof(EnergyData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (EnergyData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ENERGY_MONITOR_CALLBACK_ENERGY_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ENERGY_MONITOR_CALLBACK_ENERGY_DATA];
	callback = (EnergyData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_int32_from(callback->voltage);
	callback->current = leconvert_int32_from(callback->current);
	callback->energy = leconvert_int32_from(callback->energy);
	callback->real_power = leconvert_int32_from(callback->real_power);
	callback->apparent_power = leconvert_int32_from(callback->apparent_power);
	callback->reactive_power = leconvert_int32_from(callback->reactive_power);
	callback->power_factor = leconvert_uint16_from(callback->power_factor);
	callback->frequency = leconvert_uint16_from(callback->frequency);

	callback_function(callback->voltage, callback->current, callback->energy, callback->real_power, callback->apparent_power, callback->reactive_power, callback->power_factor, callback->frequency, user_data);
}

void energy_monitor_create(EnergyMonitor *energy_monitor, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(energy_monitor, uid, ipcon_p, 2, 0, 0, ENERGY_MONITOR_DEVICE_IDENTIFIER);

	device_p = energy_monitor->p;

	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_ENERGY_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_RESET_ENERGY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_WAVEFORM_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_TRANSFORMER_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_SET_TRANSFORMER_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_TRANSFORMER_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_CALIBRATE_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_SET_ENERGY_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_ENERGY_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ENERGY_MONITOR_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ENERGY_MONITOR_CALLBACK_ENERGY_DATA] = energy_monitor_callback_wrapper_energy_data;

	ipcon_add_device(ipcon_p, device_p);
}

void energy_monitor_destroy(EnergyMonitor *energy_monitor) {
	device_release(energy_monitor->p);
}

int energy_monitor_get_response_expected(EnergyMonitor *energy_monitor, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(energy_monitor->p, function_id, ret_response_expected);
}

int energy_monitor_set_response_expected(EnergyMonitor *energy_monitor, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(energy_monitor->p, function_id, response_expected);
}

int energy_monitor_set_response_expected_all(EnergyMonitor *energy_monitor, bool response_expected) {
	return device_set_response_expected_all(energy_monitor->p, response_expected);
}

void energy_monitor_register_callback(EnergyMonitor *energy_monitor, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(energy_monitor->p, callback_id, function, user_data);
}

int energy_monitor_get_api_version(EnergyMonitor *energy_monitor, uint8_t ret_api_version[3]) {
	return device_get_api_version(energy_monitor->p, ret_api_version);
}

int energy_monitor_get_energy_data(EnergyMonitor *energy_monitor, int32_t *ret_voltage, int32_t *ret_current, int32_t *ret_energy, int32_t *ret_real_power, int32_t *ret_apparent_power, int32_t *ret_reactive_power, uint16_t *ret_power_factor, uint16_t *ret_frequency) {
	DevicePrivate *device_p = energy_monitor->p;
	GetEnergyData_Request request;
	GetEnergyData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_ENERGY_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_int32_from(response.voltage);
	*ret_current = leconvert_int32_from(response.current);
	*ret_energy = leconvert_int32_from(response.energy);
	*ret_real_power = leconvert_int32_from(response.real_power);
	*ret_apparent_power = leconvert_int32_from(response.apparent_power);
	*ret_reactive_power = leconvert_int32_from(response.reactive_power);
	*ret_power_factor = leconvert_uint16_from(response.power_factor);
	*ret_frequency = leconvert_uint16_from(response.frequency);

	return ret;
}

int energy_monitor_reset_energy(EnergyMonitor *energy_monitor) {
	DevicePrivate *device_p = energy_monitor->p;
	ResetEnergy_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_RESET_ENERGY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_get_waveform_low_level(EnergyMonitor *energy_monitor, uint16_t *ret_waveform_chunk_offset, int16_t ret_waveform_chunk_data[30]) {
	DevicePrivate *device_p = energy_monitor->p;
	GetWaveformLowLevel_Request request;
	GetWaveformLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_WAVEFORM_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_waveform_chunk_offset = leconvert_uint16_from(response.waveform_chunk_offset);
	for (i = 0; i < 30; i++) ret_waveform_chunk_data[i] = leconvert_int16_from(response.waveform_chunk_data[i]);

	return ret;
}

int energy_monitor_get_transformer_status(EnergyMonitor *energy_monitor, bool *ret_voltage_transformer_connected, bool *ret_current_transformer_connected) {
	DevicePrivate *device_p = energy_monitor->p;
	GetTransformerStatus_Request request;
	GetTransformerStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_TRANSFORMER_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage_transformer_connected = response.voltage_transformer_connected != 0;
	*ret_current_transformer_connected = response.current_transformer_connected != 0;

	return ret;
}

int energy_monitor_set_transformer_calibration(EnergyMonitor *energy_monitor, uint16_t voltage_ratio, uint16_t current_ratio, int16_t phase_shift) {
	DevicePrivate *device_p = energy_monitor->p;
	SetTransformerCalibration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_SET_TRANSFORMER_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.voltage_ratio = leconvert_uint16_to(voltage_ratio);
	request.current_ratio = leconvert_uint16_to(current_ratio);
	request.phase_shift = leconvert_int16_to(phase_shift);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_get_transformer_calibration(EnergyMonitor *energy_monitor, uint16_t *ret_voltage_ratio, uint16_t *ret_current_ratio, int16_t *ret_phase_shift) {
	DevicePrivate *device_p = energy_monitor->p;
	GetTransformerCalibration_Request request;
	GetTransformerCalibration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_TRANSFORMER_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage_ratio = leconvert_uint16_from(response.voltage_ratio);
	*ret_current_ratio = leconvert_uint16_from(response.current_ratio);
	*ret_phase_shift = leconvert_int16_from(response.phase_shift);

	return ret;
}

int energy_monitor_calibrate_offset(EnergyMonitor *energy_monitor) {
	DevicePrivate *device_p = energy_monitor->p;
	CalibrateOffset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_CALIBRATE_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_set_energy_data_callback_configuration(EnergyMonitor *energy_monitor, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = energy_monitor->p;
	SetEnergyDataCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_SET_ENERGY_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_get_energy_data_callback_configuration(EnergyMonitor *energy_monitor, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = energy_monitor->p;
	GetEnergyDataCallbackConfiguration_Request request;
	GetEnergyDataCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_ENERGY_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int energy_monitor_get_spitfp_error_count(EnergyMonitor *energy_monitor, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = energy_monitor->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int energy_monitor_set_bootloader_mode(EnergyMonitor *energy_monitor, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = energy_monitor->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int energy_monitor_get_bootloader_mode(EnergyMonitor *energy_monitor, uint8_t *ret_mode) {
	DevicePrivate *device_p = energy_monitor->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int energy_monitor_set_write_firmware_pointer(EnergyMonitor *energy_monitor, uint32_t pointer) {
	DevicePrivate *device_p = energy_monitor->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_write_firmware(EnergyMonitor *energy_monitor, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = energy_monitor->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int energy_monitor_set_status_led_config(EnergyMonitor *energy_monitor, uint8_t config) {
	DevicePrivate *device_p = energy_monitor->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_get_status_led_config(EnergyMonitor *energy_monitor, uint8_t *ret_config) {
	DevicePrivate *device_p = energy_monitor->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int energy_monitor_get_chip_temperature(EnergyMonitor *energy_monitor, int16_t *ret_temperature) {
	DevicePrivate *device_p = energy_monitor->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int energy_monitor_reset(EnergyMonitor *energy_monitor) {
	DevicePrivate *device_p = energy_monitor->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_write_uid(EnergyMonitor *energy_monitor, uint32_t uid) {
	DevicePrivate *device_p = energy_monitor->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int energy_monitor_read_uid(EnergyMonitor *energy_monitor, uint32_t *ret_uid) {
	DevicePrivate *device_p = energy_monitor->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int energy_monitor_get_identity(EnergyMonitor *energy_monitor, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = energy_monitor->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ENERGY_MONITOR_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int energy_monitor_get_waveform(EnergyMonitor *energy_monitor, int16_t *ret_waveform, uint16_t *ret_waveform_length) {
	DevicePrivate *device_p = energy_monitor->p;
	int ret = 0;
	uint16_t waveform_length = 1536;
	uint16_t waveform_chunk_offset;
	int16_t waveform_chunk_data[30];
	bool waveform_out_of_sync;
	uint16_t waveform_chunk_length;

	*ret_waveform_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = energy_monitor_get_waveform_low_level(energy_monitor, &waveform_chunk_offset, waveform_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	if (waveform_chunk_offset == (1 << 16) - 1) { // maximum chunk offset -> stream has no data
		goto unlock;
	}

	waveform_out_of_sync = waveform_chunk_offset != 0;

	if (!waveform_out_of_sync) {
		waveform_chunk_length = waveform_length - waveform_chunk_offset;

		if (waveform_chunk_length > 30) {
			waveform_chunk_length = 30;
		}

		memcpy(ret_waveform, waveform_chunk_data, sizeof(int16_t) * waveform_chunk_length);
		*ret_waveform_length = waveform_chunk_length;

		while (*ret_waveform_length < waveform_length) {
			ret = energy_monitor_get_waveform_low_level(energy_monitor, &waveform_chunk_offset, waveform_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			waveform_out_of_sync = waveform_chunk_offset != *ret_waveform_length;

			if (waveform_out_of_sync) {
				break;
			}

			waveform_chunk_length = waveform_length - waveform_chunk_offset;

			if (waveform_chunk_length > 30) {
				waveform_chunk_length = 30;
			}

			memcpy(&ret_waveform[*ret_waveform_length], waveform_chunk_data, sizeof(int16_t) * waveform_chunk_length);
			*ret_waveform_length += waveform_chunk_length;
		}
	}

	if (waveform_out_of_sync) {
		*ret_waveform_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (waveform_chunk_offset + 30 < waveform_length) {
			ret = energy_monitor_get_waveform_low_level(energy_monitor, &waveform_chunk_offset, waveform_chunk_data);

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
