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

#include "bricklet_sound_pressure_level.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Decibel_CallbackFunction)(uint16_t decibel, void *user_data);

typedef void (*SpectrumLowLevel_CallbackFunction)(uint16_t spectrum_length, uint16_t spectrum_chunk_offset, uint16_t spectrum_chunk_data[30], void *user_data);

typedef void (*Spectrum_CallbackFunction)(uint16_t *spectrum, uint16_t spectrum_length, void *user_data);

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
} ATTRIBUTE_PACKED GetDecibel_Request;

typedef struct {
	PacketHeader header;
	uint16_t decibel;
} ATTRIBUTE_PACKED GetDecibel_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetDecibelCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDecibelCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetDecibelCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t decibel;
} ATTRIBUTE_PACKED Decibel_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSpectrumLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t spectrum_length;
	uint16_t spectrum_chunk_offset;
	uint16_t spectrum_chunk_data[30];
} ATTRIBUTE_PACKED GetSpectrumLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetSpectrumCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSpectrumCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetSpectrumCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t spectrum_length;
	uint16_t spectrum_chunk_offset;
	uint16_t spectrum_chunk_data[30];
} ATTRIBUTE_PACKED SpectrumLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t fft_size;
	uint8_t weighting;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t fft_size;
	uint8_t weighting;
} ATTRIBUTE_PACKED GetConfiguration_Response;

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

static void sound_pressure_level_callback_wrapper_spectrum(DevicePrivate *device_p, uint16_t spectrum_length, uint16_t spectrum_chunk_offset, uint16_t spectrum_chunk_data[30]) {
	Spectrum_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM];
	uint16_t spectrum_chunk_length = spectrum_length - spectrum_chunk_offset;

	callback_function = (Spectrum_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM];

	if (spectrum_chunk_length > 30) {
		spectrum_chunk_length = 30;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (spectrum_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint16_t) * spectrum_length);
			high_level_callback->length = spectrum_chunk_length;

			memcpy(high_level_callback->data, spectrum_chunk_data, sizeof(uint16_t) * spectrum_chunk_length);

			if (high_level_callback->length >= spectrum_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (spectrum_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint16_t *)high_level_callback->data)[high_level_callback->length], spectrum_chunk_data, sizeof(uint16_t) * spectrum_chunk_length);
			high_level_callback->length += spectrum_chunk_length;

			if (high_level_callback->length >= spectrum_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void sound_pressure_level_callback_wrapper_decibel(DevicePrivate *device_p, Packet *packet) {
	Decibel_CallbackFunction callback_function;
	void *user_data;
	Decibel_Callback *callback;

	if (packet->header.length != sizeof(Decibel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Decibel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_DECIBEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_DECIBEL];
	callback = (Decibel_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->decibel = leconvert_uint16_from(callback->decibel);

	callback_function(callback->decibel, user_data);
}

static void sound_pressure_level_callback_wrapper_spectrum_low_level(DevicePrivate *device_p, Packet *packet) {
	SpectrumLowLevel_CallbackFunction callback_function;
	void *user_data;
	SpectrumLowLevel_Callback *callback;
	int i;
	uint16_t aligned_spectrum_chunk_data[30];


	if (packet->header.length != sizeof(SpectrumLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SpectrumLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM_LOW_LEVEL];
	callback = (SpectrumLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->spectrum_length = leconvert_uint16_from(callback->spectrum_length);
	callback->spectrum_chunk_offset = leconvert_uint16_from(callback->spectrum_chunk_offset);
	for (i = 0; i < 30; i++) aligned_spectrum_chunk_data[i] = leconvert_uint16_from(callback->spectrum_chunk_data[i]);

	sound_pressure_level_callback_wrapper_spectrum(device_p, callback->spectrum_length, callback->spectrum_chunk_offset, aligned_spectrum_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->spectrum_length, callback->spectrum_chunk_offset, aligned_spectrum_chunk_data, user_data);
	}
}

void sound_pressure_level_create(SoundPressureLevel *sound_pressure_level, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(sound_pressure_level, uid, ipcon_p, 2, 0, 0, SOUND_PRESSURE_LEVEL_DEVICE_IDENTIFIER);

	device_p = sound_pressure_level->p;

	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_DECIBEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_DECIBEL_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_DECIBEL_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPECTRUM_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_SPECTRUM_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPECTRUM_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SOUND_PRESSURE_LEVEL_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SOUND_PRESSURE_LEVEL_CALLBACK_DECIBEL] = sound_pressure_level_callback_wrapper_decibel;
	device_p->callback_wrappers[SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM_LOW_LEVEL] = sound_pressure_level_callback_wrapper_spectrum_low_level;

	device_p->high_level_callbacks[-SOUND_PRESSURE_LEVEL_CALLBACK_SPECTRUM].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void sound_pressure_level_destroy(SoundPressureLevel *sound_pressure_level) {
	device_release(sound_pressure_level->p);
}

int sound_pressure_level_get_response_expected(SoundPressureLevel *sound_pressure_level, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(sound_pressure_level->p, function_id, ret_response_expected);
}

int sound_pressure_level_set_response_expected(SoundPressureLevel *sound_pressure_level, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(sound_pressure_level->p, function_id, response_expected);
}

int sound_pressure_level_set_response_expected_all(SoundPressureLevel *sound_pressure_level, bool response_expected) {
	return device_set_response_expected_all(sound_pressure_level->p, response_expected);
}

void sound_pressure_level_register_callback(SoundPressureLevel *sound_pressure_level, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(sound_pressure_level->p, callback_id, function, user_data);
}

int sound_pressure_level_get_api_version(SoundPressureLevel *sound_pressure_level, uint8_t ret_api_version[3]) {
	return device_get_api_version(sound_pressure_level->p, ret_api_version);
}

int sound_pressure_level_get_decibel(SoundPressureLevel *sound_pressure_level, uint16_t *ret_decibel) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetDecibel_Request request;
	GetDecibel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_DECIBEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_decibel = leconvert_uint16_from(response.decibel);

	return ret;
}

int sound_pressure_level_set_decibel_callback_configuration(SoundPressureLevel *sound_pressure_level, uint32_t period, bool value_has_to_change, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetDecibelCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_DECIBEL_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_decibel_callback_configuration(SoundPressureLevel *sound_pressure_level, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetDecibelCallbackConfiguration_Request request;
	GetDecibelCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_DECIBEL_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_spectrum_low_level(SoundPressureLevel *sound_pressure_level, uint16_t *ret_spectrum_length, uint16_t *ret_spectrum_chunk_offset, uint16_t ret_spectrum_chunk_data[30]) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetSpectrumLowLevel_Request request;
	GetSpectrumLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPECTRUM_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_spectrum_length = leconvert_uint16_from(response.spectrum_length);
	*ret_spectrum_chunk_offset = leconvert_uint16_from(response.spectrum_chunk_offset);
	for (i = 0; i < 30; i++) ret_spectrum_chunk_data[i] = leconvert_uint16_from(response.spectrum_chunk_data[i]);

	return ret;
}

int sound_pressure_level_set_spectrum_callback_configuration(SoundPressureLevel *sound_pressure_level, uint32_t period) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetSpectrumCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_SPECTRUM_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_get_spectrum_callback_configuration(SoundPressureLevel *sound_pressure_level, uint32_t *ret_period) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetSpectrumCallbackConfiguration_Request request;
	GetSpectrumCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPECTRUM_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int sound_pressure_level_set_configuration(SoundPressureLevel *sound_pressure_level, uint8_t fft_size, uint8_t weighting) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.fft_size = fft_size;
	request.weighting = weighting;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_get_configuration(SoundPressureLevel *sound_pressure_level, uint8_t *ret_fft_size, uint8_t *ret_weighting) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_fft_size = response.fft_size;
	*ret_weighting = response.weighting;

	return ret;
}

int sound_pressure_level_get_spitfp_error_count(SoundPressureLevel *sound_pressure_level, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int sound_pressure_level_set_bootloader_mode(SoundPressureLevel *sound_pressure_level, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_bootloader_mode(SoundPressureLevel *sound_pressure_level, uint8_t *ret_mode) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int sound_pressure_level_set_write_firmware_pointer(SoundPressureLevel *sound_pressure_level, uint32_t pointer) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_write_firmware(SoundPressureLevel *sound_pressure_level, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = sound_pressure_level->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int sound_pressure_level_set_status_led_config(SoundPressureLevel *sound_pressure_level, uint8_t config) {
	DevicePrivate *device_p = sound_pressure_level->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_get_status_led_config(SoundPressureLevel *sound_pressure_level, uint8_t *ret_config) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_chip_temperature(SoundPressureLevel *sound_pressure_level, int16_t *ret_temperature) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int sound_pressure_level_reset(SoundPressureLevel *sound_pressure_level) {
	DevicePrivate *device_p = sound_pressure_level->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_write_uid(SoundPressureLevel *sound_pressure_level, uint32_t uid) {
	DevicePrivate *device_p = sound_pressure_level->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int sound_pressure_level_read_uid(SoundPressureLevel *sound_pressure_level, uint32_t *ret_uid) {
	DevicePrivate *device_p = sound_pressure_level->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_identity(SoundPressureLevel *sound_pressure_level, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = sound_pressure_level->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SOUND_PRESSURE_LEVEL_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int sound_pressure_level_get_spectrum(SoundPressureLevel *sound_pressure_level, uint16_t *ret_spectrum, uint16_t *ret_spectrum_length) {
	DevicePrivate *device_p = sound_pressure_level->p;
	int ret = 0;
	uint16_t spectrum_length = 0;
	uint16_t spectrum_chunk_offset;
	uint16_t spectrum_chunk_data[30];
	bool spectrum_out_of_sync;
	uint16_t spectrum_chunk_length;

	*ret_spectrum_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = sound_pressure_level_get_spectrum_low_level(sound_pressure_level, &spectrum_length, &spectrum_chunk_offset, spectrum_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	spectrum_out_of_sync = spectrum_chunk_offset != 0;

	if (!spectrum_out_of_sync) {
		spectrum_chunk_length = spectrum_length - spectrum_chunk_offset;

		if (spectrum_chunk_length > 30) {
			spectrum_chunk_length = 30;
		}

		memcpy(ret_spectrum, spectrum_chunk_data, sizeof(uint16_t) * spectrum_chunk_length);
		*ret_spectrum_length = spectrum_chunk_length;

		while (*ret_spectrum_length < spectrum_length) {
			ret = sound_pressure_level_get_spectrum_low_level(sound_pressure_level, &spectrum_length, &spectrum_chunk_offset, spectrum_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			spectrum_out_of_sync = spectrum_chunk_offset != *ret_spectrum_length;

			if (spectrum_out_of_sync) {
				break;
			}

			spectrum_chunk_length = spectrum_length - spectrum_chunk_offset;

			if (spectrum_chunk_length > 30) {
				spectrum_chunk_length = 30;
			}

			memcpy(&ret_spectrum[*ret_spectrum_length], spectrum_chunk_data, sizeof(uint16_t) * spectrum_chunk_length);
			*ret_spectrum_length += spectrum_chunk_length;
		}
	}

	if (spectrum_out_of_sync) {
		*ret_spectrum_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (spectrum_chunk_offset + 30 < spectrum_length) {
			ret = sound_pressure_level_get_spectrum_low_level(sound_pressure_level, &spectrum_length, &spectrum_chunk_offset, spectrum_chunk_data);

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
