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

#include "bricklet_hall_effect_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*MagneticFluxDensity_CallbackFunction)(int16_t magnetic_flux_density, void *user_data);

typedef void (*Counter_CallbackFunction)(uint32_t count, void *user_data);

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
} ATTRIBUTE_PACKED GetMagneticFluxDensity_Request;

typedef struct {
	PacketHeader header;
	int16_t magnetic_flux_density;
} ATTRIBUTE_PACKED GetMagneticFluxDensity_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED SetMagneticFluxDensityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticFluxDensityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	int16_t min;
	int16_t max;
} ATTRIBUTE_PACKED GetMagneticFluxDensityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int16_t magnetic_flux_density;
} ATTRIBUTE_PACKED MagneticFluxDensity_Callback;

typedef struct {
	PacketHeader header;
	uint8_t reset_counter;
} ATTRIBUTE_PACKED GetCounter_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetCounter_Response;

typedef struct {
	PacketHeader header;
	int16_t high_threshold;
	int16_t low_threshold;
	uint32_t debounce;
} ATTRIBUTE_PACKED SetCounterConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCounterConfig_Request;

typedef struct {
	PacketHeader header;
	int16_t high_threshold;
	int16_t low_threshold;
	uint32_t debounce;
} ATTRIBUTE_PACKED GetCounterConfig_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetCounterCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCounterCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetCounterCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED Counter_Callback;

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

static void hall_effect_v2_callback_wrapper_magnetic_flux_density(DevicePrivate *device_p, Packet *packet) {
	MagneticFluxDensity_CallbackFunction callback_function;
	void *user_data;
	MagneticFluxDensity_Callback *callback;

	if (packet->header.length != sizeof(MagneticFluxDensity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (MagneticFluxDensity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_V2_CALLBACK_MAGNETIC_FLUX_DENSITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_V2_CALLBACK_MAGNETIC_FLUX_DENSITY];
	callback = (MagneticFluxDensity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->magnetic_flux_density = leconvert_int16_from(callback->magnetic_flux_density);

	callback_function(callback->magnetic_flux_density, user_data);
}

static void hall_effect_v2_callback_wrapper_counter(DevicePrivate *device_p, Packet *packet) {
	Counter_CallbackFunction callback_function;
	void *user_data;
	Counter_Callback *callback;

	if (packet->header.length != sizeof(Counter_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Counter_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_V2_CALLBACK_COUNTER];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + HALL_EFFECT_V2_CALLBACK_COUNTER];
	callback = (Counter_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_uint32_from(callback->count);

	callback_function(callback->count, user_data);
}

void hall_effect_v2_create(HallEffectV2 *hall_effect_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(hall_effect_v2, uid, ipcon_p, 2, 0, 0, HALL_EFFECT_V2_DEVICE_IDENTIFIER);

	device_p = hall_effect_v2->p;

	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_MAGNETIC_FLUX_DENSITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_COUNTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_COUNTER_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_COUNTER_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_COUNTER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_COUNTER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[HALL_EFFECT_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[HALL_EFFECT_V2_CALLBACK_MAGNETIC_FLUX_DENSITY] = hall_effect_v2_callback_wrapper_magnetic_flux_density;
	device_p->callback_wrappers[HALL_EFFECT_V2_CALLBACK_COUNTER] = hall_effect_v2_callback_wrapper_counter;

	ipcon_add_device(ipcon_p, device_p);
}

void hall_effect_v2_destroy(HallEffectV2 *hall_effect_v2) {
	device_release(hall_effect_v2->p);
}

int hall_effect_v2_get_response_expected(HallEffectV2 *hall_effect_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(hall_effect_v2->p, function_id, ret_response_expected);
}

int hall_effect_v2_set_response_expected(HallEffectV2 *hall_effect_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(hall_effect_v2->p, function_id, response_expected);
}

int hall_effect_v2_set_response_expected_all(HallEffectV2 *hall_effect_v2, bool response_expected) {
	return device_set_response_expected_all(hall_effect_v2->p, response_expected);
}

void hall_effect_v2_register_callback(HallEffectV2 *hall_effect_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(hall_effect_v2->p, callback_id, function, user_data);
}

int hall_effect_v2_get_api_version(HallEffectV2 *hall_effect_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(hall_effect_v2->p, ret_api_version);
}

int hall_effect_v2_get_magnetic_flux_density(HallEffectV2 *hall_effect_v2, int16_t *ret_magnetic_flux_density) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetMagneticFluxDensity_Request request;
	GetMagneticFluxDensity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_MAGNETIC_FLUX_DENSITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_magnetic_flux_density = leconvert_int16_from(response.magnetic_flux_density);

	return ret;
}

int hall_effect_v2_set_magnetic_flux_density_callback_configuration(HallEffectV2 *hall_effect_v2, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetMagneticFluxDensityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_magnetic_flux_density_callback_configuration(HallEffectV2 *hall_effect_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetMagneticFluxDensityCallbackConfiguration_Request request;
	GetMagneticFluxDensityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_counter(HallEffectV2 *hall_effect_v2, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetCounter_Request request;
	GetCounter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.reset_counter = reset_counter ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);

	return ret;
}

int hall_effect_v2_set_counter_config(HallEffectV2 *hall_effect_v2, int16_t high_threshold, int16_t low_threshold, uint32_t debounce) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetCounterConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_COUNTER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.high_threshold = leconvert_int16_to(high_threshold);
	request.low_threshold = leconvert_int16_to(low_threshold);
	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_get_counter_config(HallEffectV2 *hall_effect_v2, int16_t *ret_high_threshold, int16_t *ret_low_threshold, uint32_t *ret_debounce) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetCounterConfig_Request request;
	GetCounterConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_COUNTER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_high_threshold = leconvert_int16_from(response.high_threshold);
	*ret_low_threshold = leconvert_int16_from(response.low_threshold);
	*ret_debounce = leconvert_uint32_from(response.debounce);

	return ret;
}

int hall_effect_v2_set_counter_callback_configuration(HallEffectV2 *hall_effect_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetCounterCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_COUNTER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_get_counter_callback_configuration(HallEffectV2 *hall_effect_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetCounterCallbackConfiguration_Request request;
	GetCounterCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_COUNTER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_spitfp_error_count(HallEffectV2 *hall_effect_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int hall_effect_v2_set_bootloader_mode(HallEffectV2 *hall_effect_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_bootloader_mode(HallEffectV2 *hall_effect_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int hall_effect_v2_set_write_firmware_pointer(HallEffectV2 *hall_effect_v2, uint32_t pointer) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_write_firmware(HallEffectV2 *hall_effect_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = hall_effect_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int hall_effect_v2_set_status_led_config(HallEffectV2 *hall_effect_v2, uint8_t config) {
	DevicePrivate *device_p = hall_effect_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_get_status_led_config(HallEffectV2 *hall_effect_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_chip_temperature(HallEffectV2 *hall_effect_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int hall_effect_v2_reset(HallEffectV2 *hall_effect_v2) {
	DevicePrivate *device_p = hall_effect_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_write_uid(HallEffectV2 *hall_effect_v2, uint32_t uid) {
	DevicePrivate *device_p = hall_effect_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int hall_effect_v2_read_uid(HallEffectV2 *hall_effect_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = hall_effect_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int hall_effect_v2_get_identity(HallEffectV2 *hall_effect_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = hall_effect_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), HALL_EFFECT_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
