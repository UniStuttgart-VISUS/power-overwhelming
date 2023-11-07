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

#include "brick_hat.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Voltages_CallbackFunction)(uint16_t voltage_usb, uint16_t voltage_dc, void *user_data);

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
	uint32_t power_off_delay;
	uint32_t power_off_duration;
	uint8_t raspberry_pi_off;
	uint8_t bricklets_off;
	uint8_t enable_sleep_indicator;
} ATTRIBUTE_PACKED SetSleepMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSleepMode_Request;

typedef struct {
	PacketHeader header;
	uint32_t power_off_delay;
	uint32_t power_off_duration;
	uint8_t raspberry_pi_off;
	uint8_t bricklets_off;
	uint8_t enable_sleep_indicator;
} ATTRIBUTE_PACKED GetSleepMode_Response;

typedef struct {
	PacketHeader header;
	uint8_t bricklet_power;
} ATTRIBUTE_PACKED SetBrickletPower_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBrickletPower_Request;

typedef struct {
	PacketHeader header;
	uint8_t bricklet_power;
} ATTRIBUTE_PACKED GetBrickletPower_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltages_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage_usb;
	uint16_t voltage_dc;
} ATTRIBUTE_PACKED GetVoltages_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetVoltagesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetVoltagesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetVoltagesCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t voltage_usb;
	uint16_t voltage_dc;
} ATTRIBUTE_PACKED Voltages_Callback;

typedef struct {
	PacketHeader header;
	uint8_t rtc_driver;
} ATTRIBUTE_PACKED SetRTCDriver_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRTCDriver_Request;

typedef struct {
	PacketHeader header;
	uint8_t rtc_driver;
} ATTRIBUTE_PACKED GetRTCDriver_Response;

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

static void hat_callback_wrapper_voltages(DevicePrivate *device_p, Packet *packet) {
	Voltages_CallbackFunction callback_function;
	void *user_data;
	Voltages_Callback *callback;

	if (packet->header.length != sizeof(Voltages_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Voltages_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + HAT_CALLBACK_VOLTAGES];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + HAT_CALLBACK_VOLTAGES];
	callback = (Voltages_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage_usb = leconvert_uint16_from(callback->voltage_usb);
	callback->voltage_dc = leconvert_uint16_from(callback->voltage_dc);

	callback_function(callback->voltage_usb, callback->voltage_dc, user_data);
}

void hat_create(HAT *hat, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(hat, uid, ipcon_p, 2, 0, 2, HAT_DEVICE_IDENTIFIER);

	device_p = hat->p;

	device_p->response_expected[HAT_FUNCTION_SET_SLEEP_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_GET_SLEEP_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_BRICKLET_POWER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_GET_BRICKLET_POWER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_VOLTAGES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_VOLTAGES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_VOLTAGES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_RTC_DRIVER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_GET_RTC_DRIVER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HAT_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HAT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[HAT_CALLBACK_VOLTAGES] = hat_callback_wrapper_voltages;

	ipcon_add_device(ipcon_p, device_p);
}

void hat_destroy(HAT *hat) {
	device_release(hat->p);
}

int hat_get_response_expected(HAT *hat, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(hat->p, function_id, ret_response_expected);
}

int hat_set_response_expected(HAT *hat, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(hat->p, function_id, response_expected);
}

int hat_set_response_expected_all(HAT *hat, bool response_expected) {
	return device_set_response_expected_all(hat->p, response_expected);
}

void hat_register_callback(HAT *hat, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(hat->p, callback_id, function, user_data);
}

int hat_get_api_version(HAT *hat, uint8_t ret_api_version[3]) {
	return device_get_api_version(hat->p, ret_api_version);
}

int hat_set_sleep_mode(HAT *hat, uint32_t power_off_delay, uint32_t power_off_duration, bool raspberry_pi_off, bool bricklets_off, bool enable_sleep_indicator) {
	DevicePrivate *device_p = hat->p;
	SetSleepMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_SLEEP_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.power_off_delay = leconvert_uint32_to(power_off_delay);
	request.power_off_duration = leconvert_uint32_to(power_off_duration);
	request.raspberry_pi_off = raspberry_pi_off ? 1 : 0;
	request.bricklets_off = bricklets_off ? 1 : 0;
	request.enable_sleep_indicator = enable_sleep_indicator ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_get_sleep_mode(HAT *hat, uint32_t *ret_power_off_delay, uint32_t *ret_power_off_duration, bool *ret_raspberry_pi_off, bool *ret_bricklets_off, bool *ret_enable_sleep_indicator) {
	DevicePrivate *device_p = hat->p;
	GetSleepMode_Request request;
	GetSleepMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_SLEEP_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_power_off_delay = leconvert_uint32_from(response.power_off_delay);
	*ret_power_off_duration = leconvert_uint32_from(response.power_off_duration);
	*ret_raspberry_pi_off = response.raspberry_pi_off != 0;
	*ret_bricklets_off = response.bricklets_off != 0;
	*ret_enable_sleep_indicator = response.enable_sleep_indicator != 0;

	return ret;
}

int hat_set_bricklet_power(HAT *hat, bool bricklet_power) {
	DevicePrivate *device_p = hat->p;
	SetBrickletPower_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_BRICKLET_POWER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_power = bricklet_power ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_get_bricklet_power(HAT *hat, bool *ret_bricklet_power) {
	DevicePrivate *device_p = hat->p;
	GetBrickletPower_Request request;
	GetBrickletPower_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_BRICKLET_POWER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_bricklet_power = response.bricklet_power != 0;

	return ret;
}

int hat_get_voltages(HAT *hat, uint16_t *ret_voltage_usb, uint16_t *ret_voltage_dc) {
	DevicePrivate *device_p = hat->p;
	GetVoltages_Request request;
	GetVoltages_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_VOLTAGES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage_usb = leconvert_uint16_from(response.voltage_usb);
	*ret_voltage_dc = leconvert_uint16_from(response.voltage_dc);

	return ret;
}

int hat_set_voltages_callback_configuration(HAT *hat, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = hat->p;
	SetVoltagesCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_VOLTAGES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_get_voltages_callback_configuration(HAT *hat, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = hat->p;
	GetVoltagesCallbackConfiguration_Request request;
	GetVoltagesCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_VOLTAGES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int hat_set_rtc_driver(HAT *hat, uint8_t rtc_driver) {
	DevicePrivate *device_p = hat->p;
	SetRTCDriver_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_RTC_DRIVER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.rtc_driver = rtc_driver;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_get_rtc_driver(HAT *hat, uint8_t *ret_rtc_driver) {
	DevicePrivate *device_p = hat->p;
	GetRTCDriver_Request request;
	GetRTCDriver_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_RTC_DRIVER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_rtc_driver = response.rtc_driver;

	return ret;
}

int hat_get_spitfp_error_count(HAT *hat, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = hat->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int hat_set_bootloader_mode(HAT *hat, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = hat->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int hat_get_bootloader_mode(HAT *hat, uint8_t *ret_mode) {
	DevicePrivate *device_p = hat->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int hat_set_write_firmware_pointer(HAT *hat, uint32_t pointer) {
	DevicePrivate *device_p = hat->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_write_firmware(HAT *hat, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = hat->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int hat_set_status_led_config(HAT *hat, uint8_t config) {
	DevicePrivate *device_p = hat->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_get_status_led_config(HAT *hat, uint8_t *ret_config) {
	DevicePrivate *device_p = hat->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int hat_get_chip_temperature(HAT *hat, int16_t *ret_temperature) {
	DevicePrivate *device_p = hat->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int hat_reset(HAT *hat) {
	DevicePrivate *device_p = hat->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_write_uid(HAT *hat, uint32_t uid) {
	DevicePrivate *device_p = hat->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hat_read_uid(HAT *hat, uint32_t *ret_uid) {
	DevicePrivate *device_p = hat->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int hat_get_identity(HAT *hat, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = hat->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HAT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
