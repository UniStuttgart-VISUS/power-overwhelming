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

#include "bricklet_dmx.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*FrameStarted_CallbackFunction)(void *user_data);

typedef void (*FrameAvailable_CallbackFunction)(uint32_t frame_number, void *user_data);

typedef void (*FrameLowLevel_CallbackFunction)(uint16_t frame_length, uint16_t frame_chunk_offset, uint8_t frame_chunk_data[56], uint32_t frame_number, void *user_data);

typedef void (*FrameErrorCount_CallbackFunction)(uint32_t overrun_error_count, uint32_t framing_error_count, void *user_data);

typedef void (*Frame_CallbackFunction)(uint8_t *frame, uint16_t frame_length, uint32_t frame_number, void *user_data);

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
	uint8_t dmx_mode;
} ATTRIBUTE_PACKED SetDMXMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDMXMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t dmx_mode;
} ATTRIBUTE_PACKED GetDMXMode_Response;

typedef struct {
	PacketHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[60];
} ATTRIBUTE_PACKED WriteFrameLowLevel_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadFrameLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[56];
	uint32_t frame_number;
} ATTRIBUTE_PACKED ReadFrameLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint16_t frame_duration;
} ATTRIBUTE_PACKED SetFrameDuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameDuration_Request;

typedef struct {
	PacketHeader header;
	uint16_t frame_duration;
} ATTRIBUTE_PACKED GetFrameDuration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t overrun_error_count;
	uint32_t framing_error_count;
} ATTRIBUTE_PACKED GetFrameErrorCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetCommunicationLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCommunicationLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetCommunicationLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t frame_started_callback_enabled;
	uint8_t frame_available_callback_enabled;
	uint8_t frame_callback_enabled;
	uint8_t frame_error_count_callback_enabled;
} ATTRIBUTE_PACKED SetFrameCallbackConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameCallbackConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t frame_started_callback_enabled;
	uint8_t frame_available_callback_enabled;
	uint8_t frame_callback_enabled;
	uint8_t frame_error_count_callback_enabled;
} ATTRIBUTE_PACKED GetFrameCallbackConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED FrameStarted_Callback;

typedef struct {
	PacketHeader header;
	uint32_t frame_number;
} ATTRIBUTE_PACKED FrameAvailable_Callback;

typedef struct {
	PacketHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[56];
	uint32_t frame_number;
} ATTRIBUTE_PACKED FrameLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint32_t overrun_error_count;
	uint32_t framing_error_count;
} ATTRIBUTE_PACKED FrameErrorCount_Callback;

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

static void dmx_callback_wrapper_frame(DevicePrivate *device_p, uint16_t frame_length, uint16_t frame_chunk_offset, uint8_t frame_chunk_data[56], uint32_t frame_number) {
	Frame_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-DMX_CALLBACK_FRAME];
	uint16_t frame_chunk_length = frame_length - frame_chunk_offset;

	callback_function = (Frame_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME];

	if (frame_chunk_length > 56) {
		frame_chunk_length = 56;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (frame_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint8_t) * frame_length);
			high_level_callback->length = frame_chunk_length;

			memcpy(high_level_callback->data, frame_chunk_data, sizeof(uint8_t) * frame_chunk_length);

			if (high_level_callback->length >= frame_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, frame_number, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (frame_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, frame_number, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint8_t *)high_level_callback->data)[high_level_callback->length], frame_chunk_data, sizeof(uint8_t) * frame_chunk_length);
			high_level_callback->length += frame_chunk_length;

			if (high_level_callback->length >= frame_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((uint8_t *)high_level_callback->data, high_level_callback->length, frame_number, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void dmx_callback_wrapper_frame_started(DevicePrivate *device_p, Packet *packet) {
	FrameStarted_CallbackFunction callback_function;
	void *user_data;
	FrameStarted_Callback *callback;

	if (packet->header.length != sizeof(FrameStarted_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameStarted_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_STARTED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_STARTED];
	callback = (FrameStarted_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void dmx_callback_wrapper_frame_available(DevicePrivate *device_p, Packet *packet) {
	FrameAvailable_CallbackFunction callback_function;
	void *user_data;
	FrameAvailable_Callback *callback;

	if (packet->header.length != sizeof(FrameAvailable_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameAvailable_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_AVAILABLE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_AVAILABLE];
	callback = (FrameAvailable_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->frame_number = leconvert_uint32_from(callback->frame_number);

	callback_function(callback->frame_number, user_data);
}

static void dmx_callback_wrapper_frame_low_level(DevicePrivate *device_p, Packet *packet) {
	FrameLowLevel_CallbackFunction callback_function;
	void *user_data;
	FrameLowLevel_Callback *callback;

	if (packet->header.length != sizeof(FrameLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_LOW_LEVEL];
	callback = (FrameLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->frame_length = leconvert_uint16_from(callback->frame_length);
	callback->frame_chunk_offset = leconvert_uint16_from(callback->frame_chunk_offset);
	callback->frame_number = leconvert_uint32_from(callback->frame_number);

	dmx_callback_wrapper_frame(device_p, callback->frame_length, callback->frame_chunk_offset, callback->frame_chunk_data, callback->frame_number);

	if (callback_function != NULL) {
		callback_function(callback->frame_length, callback->frame_chunk_offset, callback->frame_chunk_data, callback->frame_number, user_data);
	}
}

static void dmx_callback_wrapper_frame_error_count(DevicePrivate *device_p, Packet *packet) {
	FrameErrorCount_CallbackFunction callback_function;
	void *user_data;
	FrameErrorCount_Callback *callback;

	if (packet->header.length != sizeof(FrameErrorCount_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameErrorCount_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_ERROR_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + DMX_CALLBACK_FRAME_ERROR_COUNT];
	callback = (FrameErrorCount_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->overrun_error_count = leconvert_uint32_from(callback->overrun_error_count);
	callback->framing_error_count = leconvert_uint32_from(callback->framing_error_count);

	callback_function(callback->overrun_error_count, callback->framing_error_count, user_data);
}

void dmx_create(DMX *dmx, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(dmx, uid, ipcon_p, 2, 0, 0, DMX_DEVICE_IDENTIFIER);

	device_p = dmx->p;

	device_p->response_expected[DMX_FUNCTION_SET_DMX_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_GET_DMX_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_WRITE_FRAME_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DMX_FUNCTION_READ_FRAME_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_FRAME_DURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_GET_FRAME_DURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_FRAME_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_GET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_FRAME_CALLBACK_CONFIG] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_FRAME_CALLBACK_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[DMX_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[DMX_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[DMX_CALLBACK_FRAME_STARTED] = dmx_callback_wrapper_frame_started;
	device_p->callback_wrappers[DMX_CALLBACK_FRAME_AVAILABLE] = dmx_callback_wrapper_frame_available;
	device_p->callback_wrappers[DMX_CALLBACK_FRAME_LOW_LEVEL] = dmx_callback_wrapper_frame_low_level;
	device_p->callback_wrappers[DMX_CALLBACK_FRAME_ERROR_COUNT] = dmx_callback_wrapper_frame_error_count;

	device_p->high_level_callbacks[-DMX_CALLBACK_FRAME].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void dmx_destroy(DMX *dmx) {
	device_release(dmx->p);
}

int dmx_get_response_expected(DMX *dmx, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(dmx->p, function_id, ret_response_expected);
}

int dmx_set_response_expected(DMX *dmx, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(dmx->p, function_id, response_expected);
}

int dmx_set_response_expected_all(DMX *dmx, bool response_expected) {
	return device_set_response_expected_all(dmx->p, response_expected);
}

void dmx_register_callback(DMX *dmx, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(dmx->p, callback_id, function, user_data);
}

int dmx_get_api_version(DMX *dmx, uint8_t ret_api_version[3]) {
	return device_get_api_version(dmx->p, ret_api_version);
}

int dmx_set_dmx_mode(DMX *dmx, uint8_t dmx_mode) {
	DevicePrivate *device_p = dmx->p;
	SetDMXMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_DMX_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.dmx_mode = dmx_mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_dmx_mode(DMX *dmx, uint8_t *ret_dmx_mode) {
	DevicePrivate *device_p = dmx->p;
	GetDMXMode_Request request;
	GetDMXMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_DMX_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_dmx_mode = response.dmx_mode;

	return ret;
}

int dmx_write_frame_low_level(DMX *dmx, uint16_t frame_length, uint16_t frame_chunk_offset, uint8_t frame_chunk_data[60]) {
	DevicePrivate *device_p = dmx->p;
	WriteFrameLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_WRITE_FRAME_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_length = leconvert_uint16_to(frame_length);
	request.frame_chunk_offset = leconvert_uint16_to(frame_chunk_offset);
	memcpy(request.frame_chunk_data, frame_chunk_data, 60 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_read_frame_low_level(DMX *dmx, uint16_t *ret_frame_length, uint16_t *ret_frame_chunk_offset, uint8_t ret_frame_chunk_data[56], uint32_t *ret_frame_number) {
	DevicePrivate *device_p = dmx->p;
	ReadFrameLowLevel_Request request;
	ReadFrameLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_READ_FRAME_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_length = leconvert_uint16_from(response.frame_length);
	*ret_frame_chunk_offset = leconvert_uint16_from(response.frame_chunk_offset);
	memcpy(ret_frame_chunk_data, response.frame_chunk_data, 56 * sizeof(uint8_t));
	*ret_frame_number = leconvert_uint32_from(response.frame_number);

	return ret;
}

int dmx_set_frame_duration(DMX *dmx, uint16_t frame_duration) {
	DevicePrivate *device_p = dmx->p;
	SetFrameDuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_FRAME_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_duration = leconvert_uint16_to(frame_duration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_frame_duration(DMX *dmx, uint16_t *ret_frame_duration) {
	DevicePrivate *device_p = dmx->p;
	GetFrameDuration_Request request;
	GetFrameDuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_FRAME_DURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_duration = leconvert_uint16_from(response.frame_duration);

	return ret;
}

int dmx_get_frame_error_count(DMX *dmx, uint32_t *ret_overrun_error_count, uint32_t *ret_framing_error_count) {
	DevicePrivate *device_p = dmx->p;
	GetFrameErrorCount_Request request;
	GetFrameErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_FRAME_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_overrun_error_count = leconvert_uint32_from(response.overrun_error_count);
	*ret_framing_error_count = leconvert_uint32_from(response.framing_error_count);

	return ret;
}

int dmx_set_communication_led_config(DMX *dmx, uint8_t config) {
	DevicePrivate *device_p = dmx->p;
	SetCommunicationLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_communication_led_config(DMX *dmx, uint8_t *ret_config) {
	DevicePrivate *device_p = dmx->p;
	GetCommunicationLEDConfig_Request request;
	GetCommunicationLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dmx_set_error_led_config(DMX *dmx, uint8_t config) {
	DevicePrivate *device_p = dmx->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_error_led_config(DMX *dmx, uint8_t *ret_config) {
	DevicePrivate *device_p = dmx->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dmx_set_frame_callback_config(DMX *dmx, bool frame_started_callback_enabled, bool frame_available_callback_enabled, bool frame_callback_enabled, bool frame_error_count_callback_enabled) {
	DevicePrivate *device_p = dmx->p;
	SetFrameCallbackConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_FRAME_CALLBACK_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_started_callback_enabled = frame_started_callback_enabled ? 1 : 0;
	request.frame_available_callback_enabled = frame_available_callback_enabled ? 1 : 0;
	request.frame_callback_enabled = frame_callback_enabled ? 1 : 0;
	request.frame_error_count_callback_enabled = frame_error_count_callback_enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_frame_callback_config(DMX *dmx, bool *ret_frame_started_callback_enabled, bool *ret_frame_available_callback_enabled, bool *ret_frame_callback_enabled, bool *ret_frame_error_count_callback_enabled) {
	DevicePrivate *device_p = dmx->p;
	GetFrameCallbackConfig_Request request;
	GetFrameCallbackConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_FRAME_CALLBACK_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_started_callback_enabled = response.frame_started_callback_enabled != 0;
	*ret_frame_available_callback_enabled = response.frame_available_callback_enabled != 0;
	*ret_frame_callback_enabled = response.frame_callback_enabled != 0;
	*ret_frame_error_count_callback_enabled = response.frame_error_count_callback_enabled != 0;

	return ret;
}

int dmx_get_spitfp_error_count(DMX *dmx, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = dmx->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int dmx_set_bootloader_mode(DMX *dmx, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = dmx->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dmx_get_bootloader_mode(DMX *dmx, uint8_t *ret_mode) {
	DevicePrivate *device_p = dmx->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int dmx_set_write_firmware_pointer(DMX *dmx, uint32_t pointer) {
	DevicePrivate *device_p = dmx->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_write_firmware(DMX *dmx, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = dmx->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int dmx_set_status_led_config(DMX *dmx, uint8_t config) {
	DevicePrivate *device_p = dmx->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_get_status_led_config(DMX *dmx, uint8_t *ret_config) {
	DevicePrivate *device_p = dmx->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int dmx_get_chip_temperature(DMX *dmx, int16_t *ret_temperature) {
	DevicePrivate *device_p = dmx->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int dmx_reset(DMX *dmx) {
	DevicePrivate *device_p = dmx->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_write_uid(DMX *dmx, uint32_t uid) {
	DevicePrivate *device_p = dmx->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int dmx_read_uid(DMX *dmx, uint32_t *ret_uid) {
	DevicePrivate *device_p = dmx->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int dmx_get_identity(DMX *dmx, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = dmx->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), DMX_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int dmx_write_frame(DMX *dmx, uint8_t *frame, uint16_t frame_length) {
	DevicePrivate *device_p = dmx->p;
	int ret = 0;
	uint16_t frame_chunk_offset = 0;
	uint8_t frame_chunk_data[60];
	uint16_t frame_chunk_length;

	if (frame_length == 0) {
		memset(&frame_chunk_data, 0, sizeof(uint8_t) * 60);

		ret = dmx_write_frame_low_level(dmx, frame_length, frame_chunk_offset, frame_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (frame_chunk_offset < frame_length) {
			frame_chunk_length = frame_length - frame_chunk_offset;

			if (frame_chunk_length > 60) {
				frame_chunk_length = 60;
			}

			memcpy(frame_chunk_data, &frame[frame_chunk_offset], sizeof(uint8_t) * frame_chunk_length);
			memset(&frame_chunk_data[frame_chunk_length], 0, sizeof(uint8_t) * (60 - frame_chunk_length));

			ret = dmx_write_frame_low_level(dmx, frame_length, frame_chunk_offset, frame_chunk_data);

			if (ret < 0) {
				break;
			}

			frame_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int dmx_read_frame(DMX *dmx, uint8_t *ret_frame, uint16_t *ret_frame_length, uint32_t *ret_frame_number) {
	DevicePrivate *device_p = dmx->p;
	int ret = 0;
	uint16_t frame_length = 0;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[56];
	bool frame_out_of_sync;
	uint16_t frame_chunk_length;

	*ret_frame_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = dmx_read_frame_low_level(dmx, &frame_length, &frame_chunk_offset, frame_chunk_data, ret_frame_number);

	if (ret < 0) {
		goto unlock;
	}

	frame_out_of_sync = frame_chunk_offset != 0;

	if (!frame_out_of_sync) {
		frame_chunk_length = frame_length - frame_chunk_offset;

		if (frame_chunk_length > 56) {
			frame_chunk_length = 56;
		}

		memcpy(ret_frame, frame_chunk_data, sizeof(uint8_t) * frame_chunk_length);
		*ret_frame_length = frame_chunk_length;

		while (*ret_frame_length < frame_length) {
			ret = dmx_read_frame_low_level(dmx, &frame_length, &frame_chunk_offset, frame_chunk_data, ret_frame_number);

			if (ret < 0) {
				goto unlock;
			}

			frame_out_of_sync = frame_chunk_offset != *ret_frame_length;

			if (frame_out_of_sync) {
				break;
			}

			frame_chunk_length = frame_length - frame_chunk_offset;

			if (frame_chunk_length > 56) {
				frame_chunk_length = 56;
			}

			memcpy(&ret_frame[*ret_frame_length], frame_chunk_data, sizeof(uint8_t) * frame_chunk_length);
			*ret_frame_length += frame_chunk_length;
		}
	}

	if (frame_out_of_sync) {
		*ret_frame_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (frame_chunk_offset + 56 < frame_length) {
			ret = dmx_read_frame_low_level(dmx, &frame_length, &frame_chunk_offset, frame_chunk_data, ret_frame_number);

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
