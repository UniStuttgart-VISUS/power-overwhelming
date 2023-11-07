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

#include "bricklet_thermal_imaging.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*HighContrastImageLowLevel_CallbackFunction)(uint16_t image_chunk_offset, uint8_t image_chunk_data[62], void *user_data);

typedef void (*TemperatureImageLowLevel_CallbackFunction)(uint16_t image_chunk_offset, uint16_t image_chunk_data[31], void *user_data);

typedef void (*HighContrastImage_CallbackFunction)(uint8_t *image, uint16_t image_length, void *user_data);

typedef void (*TemperatureImage_CallbackFunction)(uint16_t *image, uint16_t image_length, void *user_data);

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
} ATTRIBUTE_PACKED GetHighContrastImageLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t image_chunk_offset;
	uint8_t image_chunk_data[62];
} ATTRIBUTE_PACKED GetHighContrastImageLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureImageLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t image_chunk_offset;
	uint16_t image_chunk_data[31];
} ATTRIBUTE_PACKED GetTemperatureImageLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatistics_Request;

typedef struct {
	PacketHeader header;
	uint16_t spotmeter_statistics[4];
	uint16_t temperatures[4];
	uint8_t resolution;
	uint8_t ffc_status;
	uint8_t temperature_warning[1];
} ATTRIBUTE_PACKED GetStatistics_Response;

typedef struct {
	PacketHeader header;
	uint8_t resolution;
} ATTRIBUTE_PACKED SetResolution_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetResolution_Request;

typedef struct {
	PacketHeader header;
	uint8_t resolution;
} ATTRIBUTE_PACKED GetResolution_Response;

typedef struct {
	PacketHeader header;
	uint8_t region_of_interest[4];
} ATTRIBUTE_PACKED SetSpotmeterConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSpotmeterConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t region_of_interest[4];
} ATTRIBUTE_PACKED GetSpotmeterConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t region_of_interest[4];
	uint16_t dampening_factor;
	uint16_t clip_limit[2];
	uint16_t empty_counts;
} ATTRIBUTE_PACKED SetHighContrastConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetHighContrastConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t region_of_interest[4];
	uint16_t dampening_factor;
	uint16_t clip_limit[2];
	uint16_t empty_counts;
} ATTRIBUTE_PACKED GetHighContrastConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetImageTransferConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetImageTransferConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetImageTransferConfig_Response;

typedef struct {
	PacketHeader header;
	uint16_t image_chunk_offset;
	uint8_t image_chunk_data[62];
} ATTRIBUTE_PACKED HighContrastImageLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint16_t image_chunk_offset;
	uint16_t image_chunk_data[31];
} ATTRIBUTE_PACKED TemperatureImageLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint16_t scene_emissivity;
	uint16_t temperature_background;
	uint16_t tau_window;
	uint16_t temperatur_window;
	uint16_t tau_atmosphere;
	uint16_t temperature_atmosphere;
	uint16_t reflection_window;
	uint16_t temperature_reflection;
} ATTRIBUTE_PACKED SetFluxLinearParameters_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFluxLinearParameters_Request;

typedef struct {
	PacketHeader header;
	uint16_t scene_emissivity;
	uint16_t temperature_background;
	uint16_t tau_window;
	uint16_t temperatur_window;
	uint16_t tau_atmosphere;
	uint16_t temperature_atmosphere;
	uint16_t reflection_window;
	uint16_t temperature_reflection;
} ATTRIBUTE_PACKED GetFluxLinearParameters_Response;

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

static void thermal_imaging_callback_wrapper_high_contrast_image(DevicePrivate *device_p, uint16_t image_chunk_offset, uint8_t image_chunk_data[62]) {
	HighContrastImage_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE];
	uint16_t image_chunk_length = 4800 - image_chunk_offset;

	callback_function = (HighContrastImage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE];

	if (image_chunk_length > 62) {
		image_chunk_length = 62;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (image_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint8_t) * 4800);
			high_level_callback->length = image_chunk_length;

			memcpy(high_level_callback->data, image_chunk_data, sizeof(uint8_t) * image_chunk_length);

			if (high_level_callback->length >= 4800) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (image_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint8_t *)high_level_callback->data)[high_level_callback->length], image_chunk_data, sizeof(uint8_t) * image_chunk_length);
			high_level_callback->length += image_chunk_length;

			if (high_level_callback->length >= 4800) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void thermal_imaging_callback_wrapper_temperature_image(DevicePrivate *device_p, uint16_t image_chunk_offset, uint16_t image_chunk_data[31]) {
	TemperatureImage_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE];
	uint16_t image_chunk_length = 4800 - image_chunk_offset;

	callback_function = (TemperatureImage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE];

	if (image_chunk_length > 31) {
		image_chunk_length = 31;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (image_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint16_t) * 4800);
			high_level_callback->length = image_chunk_length;

			memcpy(high_level_callback->data, image_chunk_data, sizeof(uint16_t) * image_chunk_length);

			if (high_level_callback->length >= 4800) { // stream complete
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
		if (image_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint16_t *)high_level_callback->data)[high_level_callback->length], image_chunk_data, sizeof(uint16_t) * image_chunk_length);
			high_level_callback->length += image_chunk_length;

			if (high_level_callback->length >= 4800) { // stream complete
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

static void thermal_imaging_callback_wrapper_high_contrast_image_low_level(DevicePrivate *device_p, Packet *packet) {
	HighContrastImageLowLevel_CallbackFunction callback_function;
	void *user_data;
	HighContrastImageLowLevel_Callback *callback;

	if (packet->header.length != sizeof(HighContrastImageLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (HighContrastImageLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE_LOW_LEVEL];
	callback = (HighContrastImageLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->image_chunk_offset = leconvert_uint16_from(callback->image_chunk_offset);

	thermal_imaging_callback_wrapper_high_contrast_image(device_p, callback->image_chunk_offset, callback->image_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->image_chunk_offset, callback->image_chunk_data, user_data);
	}
}

static void thermal_imaging_callback_wrapper_temperature_image_low_level(DevicePrivate *device_p, Packet *packet) {
	TemperatureImageLowLevel_CallbackFunction callback_function;
	void *user_data;
	TemperatureImageLowLevel_Callback *callback;
	int i;
	uint16_t aligned_image_chunk_data[31];


	if (packet->header.length != sizeof(TemperatureImageLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (TemperatureImageLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE_LOW_LEVEL];
	callback = (TemperatureImageLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->image_chunk_offset = leconvert_uint16_from(callback->image_chunk_offset);
	for (i = 0; i < 31; i++) aligned_image_chunk_data[i] = leconvert_uint16_from(callback->image_chunk_data[i]);

	thermal_imaging_callback_wrapper_temperature_image(device_p, callback->image_chunk_offset, aligned_image_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->image_chunk_offset, aligned_image_chunk_data, user_data);
	}
}

void thermal_imaging_create(ThermalImaging *thermal_imaging, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(thermal_imaging, uid, ipcon_p, 2, 0, 1, THERMAL_IMAGING_DEVICE_IDENTIFIER);

	device_p = thermal_imaging->p;

	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_HIGH_CONTRAST_IMAGE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_TEMPERATURE_IMAGE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_STATISTICS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_RESOLUTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_RESOLUTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_SPOTMETER_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_SPOTMETER_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_HIGH_CONTRAST_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_HIGH_CONTRAST_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_IMAGE_TRANSFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_IMAGE_TRANSFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_FLUX_LINEAR_PARAMETERS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_FLUX_LINEAR_PARAMETERS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[THERMAL_IMAGING_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE_LOW_LEVEL] = thermal_imaging_callback_wrapper_high_contrast_image_low_level;
	device_p->callback_wrappers[THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE_LOW_LEVEL] = thermal_imaging_callback_wrapper_temperature_image_low_level;

	device_p->high_level_callbacks[-THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE].exists = true;
	device_p->high_level_callbacks[-THERMAL_IMAGING_CALLBACK_TEMPERATURE_IMAGE].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void thermal_imaging_destroy(ThermalImaging *thermal_imaging) {
	device_release(thermal_imaging->p);
}

int thermal_imaging_get_response_expected(ThermalImaging *thermal_imaging, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(thermal_imaging->p, function_id, ret_response_expected);
}

int thermal_imaging_set_response_expected(ThermalImaging *thermal_imaging, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(thermal_imaging->p, function_id, response_expected);
}

int thermal_imaging_set_response_expected_all(ThermalImaging *thermal_imaging, bool response_expected) {
	return device_set_response_expected_all(thermal_imaging->p, response_expected);
}

void thermal_imaging_register_callback(ThermalImaging *thermal_imaging, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(thermal_imaging->p, callback_id, function, user_data);
}

int thermal_imaging_get_api_version(ThermalImaging *thermal_imaging, uint8_t ret_api_version[3]) {
	return device_get_api_version(thermal_imaging->p, ret_api_version);
}

int thermal_imaging_get_high_contrast_image_low_level(ThermalImaging *thermal_imaging, uint16_t *ret_image_chunk_offset, uint8_t ret_image_chunk_data[62]) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetHighContrastImageLowLevel_Request request;
	GetHighContrastImageLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_HIGH_CONTRAST_IMAGE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_image_chunk_offset = leconvert_uint16_from(response.image_chunk_offset);
	memcpy(ret_image_chunk_data, response.image_chunk_data, 62 * sizeof(uint8_t));

	return ret;
}

int thermal_imaging_get_temperature_image_low_level(ThermalImaging *thermal_imaging, uint16_t *ret_image_chunk_offset, uint16_t ret_image_chunk_data[31]) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetTemperatureImageLowLevel_Request request;
	GetTemperatureImageLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_TEMPERATURE_IMAGE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_image_chunk_offset = leconvert_uint16_from(response.image_chunk_offset);
	for (i = 0; i < 31; i++) ret_image_chunk_data[i] = leconvert_uint16_from(response.image_chunk_data[i]);

	return ret;
}

int thermal_imaging_get_statistics(ThermalImaging *thermal_imaging, uint16_t ret_spotmeter_statistics[4], uint16_t ret_temperatures[4], uint8_t *ret_resolution, uint8_t *ret_ffc_status, bool ret_temperature_warning[2]) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetStatistics_Request request;
	GetStatistics_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_STATISTICS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) ret_spotmeter_statistics[i] = leconvert_uint16_from(response.spotmeter_statistics[i]);
	for (i = 0; i < 4; i++) ret_temperatures[i] = leconvert_uint16_from(response.temperatures[i]);
	*ret_resolution = response.resolution;
	*ret_ffc_status = response.ffc_status;
	for (i = 0; i < 2; i++) ret_temperature_warning[i] = (response.temperature_warning[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int thermal_imaging_set_resolution(ThermalImaging *thermal_imaging, uint8_t resolution) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetResolution_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_RESOLUTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.resolution = resolution;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_resolution(ThermalImaging *thermal_imaging, uint8_t *ret_resolution) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetResolution_Request request;
	GetResolution_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_RESOLUTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_resolution = response.resolution;

	return ret;
}

int thermal_imaging_set_spotmeter_config(ThermalImaging *thermal_imaging, uint8_t region_of_interest[4]) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetSpotmeterConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_SPOTMETER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.region_of_interest, region_of_interest, 4 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_spotmeter_config(ThermalImaging *thermal_imaging, uint8_t ret_region_of_interest[4]) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetSpotmeterConfig_Request request;
	GetSpotmeterConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_SPOTMETER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_region_of_interest, response.region_of_interest, 4 * sizeof(uint8_t));

	return ret;
}

int thermal_imaging_set_high_contrast_config(ThermalImaging *thermal_imaging, uint8_t region_of_interest[4], uint16_t dampening_factor, uint16_t clip_limit[2], uint16_t empty_counts) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetHighContrastConfig_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_HIGH_CONTRAST_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.region_of_interest, region_of_interest, 4 * sizeof(uint8_t));
	request.dampening_factor = leconvert_uint16_to(dampening_factor);
	for (i = 0; i < 2; i++) request.clip_limit[i] = leconvert_uint16_to(clip_limit[i]);
	request.empty_counts = leconvert_uint16_to(empty_counts);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_high_contrast_config(ThermalImaging *thermal_imaging, uint8_t ret_region_of_interest[4], uint16_t *ret_dampening_factor, uint16_t ret_clip_limit[2], uint16_t *ret_empty_counts) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetHighContrastConfig_Request request;
	GetHighContrastConfig_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_HIGH_CONTRAST_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_region_of_interest, response.region_of_interest, 4 * sizeof(uint8_t));
	*ret_dampening_factor = leconvert_uint16_from(response.dampening_factor);
	for (i = 0; i < 2; i++) ret_clip_limit[i] = leconvert_uint16_from(response.clip_limit[i]);
	*ret_empty_counts = leconvert_uint16_from(response.empty_counts);

	return ret;
}

int thermal_imaging_set_image_transfer_config(ThermalImaging *thermal_imaging, uint8_t config) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetImageTransferConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_IMAGE_TRANSFER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_image_transfer_config(ThermalImaging *thermal_imaging, uint8_t *ret_config) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetImageTransferConfig_Request request;
	GetImageTransferConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_IMAGE_TRANSFER_CONFIG, device_p->ipcon_p, device_p);

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

int thermal_imaging_set_flux_linear_parameters(ThermalImaging *thermal_imaging, uint16_t scene_emissivity, uint16_t temperature_background, uint16_t tau_window, uint16_t temperatur_window, uint16_t tau_atmosphere, uint16_t temperature_atmosphere, uint16_t reflection_window, uint16_t temperature_reflection) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetFluxLinearParameters_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_FLUX_LINEAR_PARAMETERS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.scene_emissivity = leconvert_uint16_to(scene_emissivity);
	request.temperature_background = leconvert_uint16_to(temperature_background);
	request.tau_window = leconvert_uint16_to(tau_window);
	request.temperatur_window = leconvert_uint16_to(temperatur_window);
	request.tau_atmosphere = leconvert_uint16_to(tau_atmosphere);
	request.temperature_atmosphere = leconvert_uint16_to(temperature_atmosphere);
	request.reflection_window = leconvert_uint16_to(reflection_window);
	request.temperature_reflection = leconvert_uint16_to(temperature_reflection);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_flux_linear_parameters(ThermalImaging *thermal_imaging, uint16_t *ret_scene_emissivity, uint16_t *ret_temperature_background, uint16_t *ret_tau_window, uint16_t *ret_temperatur_window, uint16_t *ret_tau_atmosphere, uint16_t *ret_temperature_atmosphere, uint16_t *ret_reflection_window, uint16_t *ret_temperature_reflection) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetFluxLinearParameters_Request request;
	GetFluxLinearParameters_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_FLUX_LINEAR_PARAMETERS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_scene_emissivity = leconvert_uint16_from(response.scene_emissivity);
	*ret_temperature_background = leconvert_uint16_from(response.temperature_background);
	*ret_tau_window = leconvert_uint16_from(response.tau_window);
	*ret_temperatur_window = leconvert_uint16_from(response.temperatur_window);
	*ret_tau_atmosphere = leconvert_uint16_from(response.tau_atmosphere);
	*ret_temperature_atmosphere = leconvert_uint16_from(response.temperature_atmosphere);
	*ret_reflection_window = leconvert_uint16_from(response.reflection_window);
	*ret_temperature_reflection = leconvert_uint16_from(response.temperature_reflection);

	return ret;
}

int thermal_imaging_get_spitfp_error_count(ThermalImaging *thermal_imaging, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int thermal_imaging_set_bootloader_mode(ThermalImaging *thermal_imaging, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int thermal_imaging_get_bootloader_mode(ThermalImaging *thermal_imaging, uint8_t *ret_mode) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int thermal_imaging_set_write_firmware_pointer(ThermalImaging *thermal_imaging, uint32_t pointer) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_write_firmware(ThermalImaging *thermal_imaging, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = thermal_imaging->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int thermal_imaging_set_status_led_config(ThermalImaging *thermal_imaging, uint8_t config) {
	DevicePrivate *device_p = thermal_imaging->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_get_status_led_config(ThermalImaging *thermal_imaging, uint8_t *ret_config) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int thermal_imaging_get_chip_temperature(ThermalImaging *thermal_imaging, int16_t *ret_temperature) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int thermal_imaging_reset(ThermalImaging *thermal_imaging) {
	DevicePrivate *device_p = thermal_imaging->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_write_uid(ThermalImaging *thermal_imaging, uint32_t uid) {
	DevicePrivate *device_p = thermal_imaging->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int thermal_imaging_read_uid(ThermalImaging *thermal_imaging, uint32_t *ret_uid) {
	DevicePrivate *device_p = thermal_imaging->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int thermal_imaging_get_identity(ThermalImaging *thermal_imaging, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = thermal_imaging->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), THERMAL_IMAGING_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int thermal_imaging_get_high_contrast_image(ThermalImaging *thermal_imaging, uint8_t *ret_image, uint16_t *ret_image_length) {
	DevicePrivate *device_p = thermal_imaging->p;
	int ret = 0;
	uint16_t image_length = 4800;
	uint16_t image_chunk_offset;
	uint8_t image_chunk_data[62];
	bool image_out_of_sync;
	uint16_t image_chunk_length;

	*ret_image_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = thermal_imaging_get_high_contrast_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	if (image_chunk_offset == (1 << 16) - 1) { // maximum chunk offset -> stream has no data
		goto unlock;
	}

	image_out_of_sync = image_chunk_offset != 0;

	if (!image_out_of_sync) {
		image_chunk_length = image_length - image_chunk_offset;

		if (image_chunk_length > 62) {
			image_chunk_length = 62;
		}

		memcpy(ret_image, image_chunk_data, sizeof(uint8_t) * image_chunk_length);
		*ret_image_length = image_chunk_length;

		while (*ret_image_length < image_length) {
			ret = thermal_imaging_get_high_contrast_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			image_out_of_sync = image_chunk_offset != *ret_image_length;

			if (image_out_of_sync) {
				break;
			}

			image_chunk_length = image_length - image_chunk_offset;

			if (image_chunk_length > 62) {
				image_chunk_length = 62;
			}

			memcpy(&ret_image[*ret_image_length], image_chunk_data, sizeof(uint8_t) * image_chunk_length);
			*ret_image_length += image_chunk_length;
		}
	}

	if (image_out_of_sync) {
		*ret_image_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (image_chunk_offset + 62 < image_length) {
			ret = thermal_imaging_get_high_contrast_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

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

int thermal_imaging_get_temperature_image(ThermalImaging *thermal_imaging, uint16_t *ret_image, uint16_t *ret_image_length) {
	DevicePrivate *device_p = thermal_imaging->p;
	int ret = 0;
	uint16_t image_length = 4800;
	uint16_t image_chunk_offset;
	uint16_t image_chunk_data[31];
	bool image_out_of_sync;
	uint16_t image_chunk_length;

	*ret_image_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = thermal_imaging_get_temperature_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	if (image_chunk_offset == (1 << 16) - 1) { // maximum chunk offset -> stream has no data
		goto unlock;
	}

	image_out_of_sync = image_chunk_offset != 0;

	if (!image_out_of_sync) {
		image_chunk_length = image_length - image_chunk_offset;

		if (image_chunk_length > 31) {
			image_chunk_length = 31;
		}

		memcpy(ret_image, image_chunk_data, sizeof(uint16_t) * image_chunk_length);
		*ret_image_length = image_chunk_length;

		while (*ret_image_length < image_length) {
			ret = thermal_imaging_get_temperature_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			image_out_of_sync = image_chunk_offset != *ret_image_length;

			if (image_out_of_sync) {
				break;
			}

			image_chunk_length = image_length - image_chunk_offset;

			if (image_chunk_length > 31) {
				image_chunk_length = 31;
			}

			memcpy(&ret_image[*ret_image_length], image_chunk_data, sizeof(uint16_t) * image_chunk_length);
			*ret_image_length += image_chunk_length;
		}
	}

	if (image_out_of_sync) {
		*ret_image_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (image_chunk_offset + 31 < image_length) {
			ret = thermal_imaging_get_temperature_image_low_level(thermal_imaging, &image_chunk_offset, image_chunk_data);

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
