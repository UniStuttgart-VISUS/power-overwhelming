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

#include "bricklet_can_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*FrameReadLowLevel_CallbackFunction)(uint8_t frame_type, uint32_t identifier, uint8_t data_length, uint8_t data_data[15], void *user_data);

typedef void (*FrameReadable_CallbackFunction)(void *user_data);

typedef void (*ErrorOccurred_CallbackFunction)(void *user_data);

typedef void (*FrameRead_CallbackFunction)(uint8_t frame_type, uint32_t identifier, uint8_t *data, uint8_t data_length, void *user_data);

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
	uint8_t frame_type;
	uint32_t identifier;
	uint8_t data_length;
	uint8_t data_data[15];
} ATTRIBUTE_PACKED WriteFrameLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t success;
} ATTRIBUTE_PACKED WriteFrameLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadFrameLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t success;
	uint8_t frame_type;
	uint32_t identifier;
	uint8_t data_length;
	uint8_t data_data[15];
} ATTRIBUTE_PACKED ReadFrameLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetFrameReadCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameReadCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetFrameReadCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t baud_rate;
	uint16_t sample_point;
	uint8_t transceiver_mode;
} ATTRIBUTE_PACKED SetTransceiverConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTransceiverConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t baud_rate;
	uint16_t sample_point;
	uint8_t transceiver_mode;
} ATTRIBUTE_PACKED GetTransceiverConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t write_buffer_size;
	int32_t write_buffer_timeout;
	uint16_t write_backlog_size;
	uint8_t read_buffer_sizes_length;
	int8_t read_buffer_sizes_data[32];
	uint16_t read_backlog_size;
} ATTRIBUTE_PACKED SetQueueConfigurationLowLevel_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQueueConfigurationLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t write_buffer_size;
	int32_t write_buffer_timeout;
	uint16_t write_backlog_size;
	uint8_t read_buffer_sizes_length;
	int8_t read_buffer_sizes_data[32];
	uint16_t read_backlog_size;
} ATTRIBUTE_PACKED GetQueueConfigurationLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t buffer_index;
	uint8_t filter_mode;
	uint32_t filter_mask;
	uint32_t filter_identifier;
} ATTRIBUTE_PACKED SetReadFilterConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t buffer_index;
} ATTRIBUTE_PACKED GetReadFilterConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t filter_mode;
	uint32_t filter_mask;
	uint32_t filter_identifier;
} ATTRIBUTE_PACKED GetReadFilterConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorLogLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t transceiver_state;
	uint8_t transceiver_write_error_level;
	uint8_t transceiver_read_error_level;
	uint32_t transceiver_stuffing_error_count;
	uint32_t transceiver_format_error_count;
	uint32_t transceiver_ack_error_count;
	uint32_t transceiver_bit1_error_count;
	uint32_t transceiver_bit0_error_count;
	uint32_t transceiver_crc_error_count;
	uint32_t write_buffer_timeout_error_count;
	uint32_t read_buffer_overflow_error_count;
	uint8_t read_buffer_overflow_error_occurred_length;
	uint8_t read_buffer_overflow_error_occurred_data[4];
	uint32_t read_backlog_overflow_error_count;
} ATTRIBUTE_PACKED GetErrorLogLowLevel_Response;

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
	uint8_t frame_type;
	uint32_t identifier;
	uint8_t data_length;
	uint8_t data_data[15];
} ATTRIBUTE_PACKED FrameReadLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED FrameReadable_Callback;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED SetErrorOccurredCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorOccurredCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED GetErrorOccurredCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ErrorOccurred_Callback;

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

static void can_v2_callback_wrapper_frame_read(DevicePrivate *device_p, uint8_t frame_type, uint32_t identifier, uint8_t data_length, uint8_t data_data[15]) {
	FrameRead_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READ];

	callback_function = (FrameRead_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READ];

	if (callback_function != NULL) {
		callback_function(frame_type, identifier, data_data, data_length, user_data);
	}
}

static void can_v2_callback_wrapper_frame_read_low_level(DevicePrivate *device_p, Packet *packet) {
	FrameReadLowLevel_CallbackFunction callback_function;
	void *user_data;
	FrameReadLowLevel_Callback *callback;

	if (packet->header.length != sizeof(FrameReadLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameReadLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READ_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READ_LOW_LEVEL];
	callback = (FrameReadLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->identifier = leconvert_uint32_from(callback->identifier);

	can_v2_callback_wrapper_frame_read(device_p, callback->frame_type, callback->identifier, callback->data_length, callback->data_data);

	if (callback_function != NULL) {
		callback_function(callback->frame_type, callback->identifier, callback->data_length, callback->data_data, user_data);
	}
}

static void can_v2_callback_wrapper_frame_readable(DevicePrivate *device_p, Packet *packet) {
	FrameReadable_CallbackFunction callback_function;
	void *user_data;
	FrameReadable_Callback *callback;

	if (packet->header.length != sizeof(FrameReadable_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameReadable_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READABLE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_FRAME_READABLE];
	callback = (FrameReadable_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void can_v2_callback_wrapper_error_occurred(DevicePrivate *device_p, Packet *packet) {
	ErrorOccurred_CallbackFunction callback_function;
	void *user_data;
	ErrorOccurred_Callback *callback;

	if (packet->header.length != sizeof(ErrorOccurred_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ErrorOccurred_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_ERROR_OCCURRED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_V2_CALLBACK_ERROR_OCCURRED];
	callback = (ErrorOccurred_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void can_v2_create(CANV2 *can_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(can_v2, uid, ipcon_p, 2, 0, 1, CAN_V2_DEVICE_IDENTIFIER);

	device_p = can_v2->p;

	device_p->response_expected[CAN_V2_FUNCTION_WRITE_FRAME_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_READ_FRAME_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_FRAME_READ_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_FRAME_READ_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_TRANSCEIVER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_TRANSCEIVER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_QUEUE_CONFIGURATION_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_QUEUE_CONFIGURATION_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_READ_FILTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_READ_FILTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_ERROR_LOG_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_ERROR_OCCURRED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_ERROR_OCCURRED_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CAN_V2_CALLBACK_FRAME_READ_LOW_LEVEL] = can_v2_callback_wrapper_frame_read_low_level;
	device_p->callback_wrappers[CAN_V2_CALLBACK_FRAME_READABLE] = can_v2_callback_wrapper_frame_readable;
	device_p->callback_wrappers[CAN_V2_CALLBACK_ERROR_OCCURRED] = can_v2_callback_wrapper_error_occurred;

	device_p->high_level_callbacks[-CAN_V2_CALLBACK_FRAME_READ].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void can_v2_destroy(CANV2 *can_v2) {
	device_release(can_v2->p);
}

int can_v2_get_response_expected(CANV2 *can_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(can_v2->p, function_id, ret_response_expected);
}

int can_v2_set_response_expected(CANV2 *can_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(can_v2->p, function_id, response_expected);
}

int can_v2_set_response_expected_all(CANV2 *can_v2, bool response_expected) {
	return device_set_response_expected_all(can_v2->p, response_expected);
}

void can_v2_register_callback(CANV2 *can_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(can_v2->p, callback_id, function, user_data);
}

int can_v2_get_api_version(CANV2 *can_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(can_v2->p, ret_api_version);
}

int can_v2_write_frame_low_level(CANV2 *can_v2, uint8_t frame_type, uint32_t identifier, uint8_t data_length, uint8_t data_data[15], bool *ret_success) {
	DevicePrivate *device_p = can_v2->p;
	WriteFrameLowLevel_Request request;
	WriteFrameLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_WRITE_FRAME_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_type = frame_type;
	request.identifier = leconvert_uint32_to(identifier);
	request.data_length = data_length;
	memcpy(request.data_data, data_data, 15 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_success = response.success != 0;

	return ret;
}

int can_v2_read_frame_low_level(CANV2 *can_v2, bool *ret_success, uint8_t *ret_frame_type, uint32_t *ret_identifier, uint8_t *ret_data_length, uint8_t ret_data_data[15]) {
	DevicePrivate *device_p = can_v2->p;
	ReadFrameLowLevel_Request request;
	ReadFrameLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_READ_FRAME_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_success = response.success != 0;
	*ret_frame_type = response.frame_type;
	*ret_identifier = leconvert_uint32_from(response.identifier);
	*ret_data_length = response.data_length;
	memcpy(ret_data_data, response.data_data, 15 * sizeof(uint8_t));

	return ret;
}

int can_v2_set_frame_read_callback_configuration(CANV2 *can_v2, bool enabled) {
	DevicePrivate *device_p = can_v2->p;
	SetFrameReadCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_FRAME_READ_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_frame_read_callback_configuration(CANV2 *can_v2, bool *ret_enabled) {
	DevicePrivate *device_p = can_v2->p;
	GetFrameReadCallbackConfiguration_Request request;
	GetFrameReadCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_FRAME_READ_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int can_v2_set_transceiver_configuration(CANV2 *can_v2, uint32_t baud_rate, uint16_t sample_point, uint8_t transceiver_mode) {
	DevicePrivate *device_p = can_v2->p;
	SetTransceiverConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_TRANSCEIVER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.baud_rate = leconvert_uint32_to(baud_rate);
	request.sample_point = leconvert_uint16_to(sample_point);
	request.transceiver_mode = transceiver_mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_transceiver_configuration(CANV2 *can_v2, uint32_t *ret_baud_rate, uint16_t *ret_sample_point, uint8_t *ret_transceiver_mode) {
	DevicePrivate *device_p = can_v2->p;
	GetTransceiverConfiguration_Request request;
	GetTransceiverConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_TRANSCEIVER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baud_rate = leconvert_uint32_from(response.baud_rate);
	*ret_sample_point = leconvert_uint16_from(response.sample_point);
	*ret_transceiver_mode = response.transceiver_mode;

	return ret;
}

int can_v2_set_queue_configuration_low_level(CANV2 *can_v2, uint8_t write_buffer_size, int32_t write_buffer_timeout, uint16_t write_backlog_size, uint8_t read_buffer_sizes_length, int8_t read_buffer_sizes_data[32], uint16_t read_backlog_size) {
	DevicePrivate *device_p = can_v2->p;
	SetQueueConfigurationLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_QUEUE_CONFIGURATION_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.write_buffer_size = write_buffer_size;
	request.write_buffer_timeout = leconvert_int32_to(write_buffer_timeout);
	request.write_backlog_size = leconvert_uint16_to(write_backlog_size);
	request.read_buffer_sizes_length = read_buffer_sizes_length;
	memcpy(request.read_buffer_sizes_data, read_buffer_sizes_data, 32 * sizeof(int8_t));
	request.read_backlog_size = leconvert_uint16_to(read_backlog_size);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_queue_configuration_low_level(CANV2 *can_v2, uint8_t *ret_write_buffer_size, int32_t *ret_write_buffer_timeout, uint16_t *ret_write_backlog_size, uint8_t *ret_read_buffer_sizes_length, int8_t ret_read_buffer_sizes_data[32], uint16_t *ret_read_backlog_size) {
	DevicePrivate *device_p = can_v2->p;
	GetQueueConfigurationLowLevel_Request request;
	GetQueueConfigurationLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_QUEUE_CONFIGURATION_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_write_buffer_size = response.write_buffer_size;
	*ret_write_buffer_timeout = leconvert_int32_from(response.write_buffer_timeout);
	*ret_write_backlog_size = leconvert_uint16_from(response.write_backlog_size);
	*ret_read_buffer_sizes_length = response.read_buffer_sizes_length;
	memcpy(ret_read_buffer_sizes_data, response.read_buffer_sizes_data, 32 * sizeof(int8_t));
	*ret_read_backlog_size = leconvert_uint16_from(response.read_backlog_size);

	return ret;
}

int can_v2_set_read_filter_configuration(CANV2 *can_v2, uint8_t buffer_index, uint8_t filter_mode, uint32_t filter_mask, uint32_t filter_identifier) {
	DevicePrivate *device_p = can_v2->p;
	SetReadFilterConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_READ_FILTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.buffer_index = buffer_index;
	request.filter_mode = filter_mode;
	request.filter_mask = leconvert_uint32_to(filter_mask);
	request.filter_identifier = leconvert_uint32_to(filter_identifier);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_read_filter_configuration(CANV2 *can_v2, uint8_t buffer_index, uint8_t *ret_filter_mode, uint32_t *ret_filter_mask, uint32_t *ret_filter_identifier) {
	DevicePrivate *device_p = can_v2->p;
	GetReadFilterConfiguration_Request request;
	GetReadFilterConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_READ_FILTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.buffer_index = buffer_index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_filter_mode = response.filter_mode;
	*ret_filter_mask = leconvert_uint32_from(response.filter_mask);
	*ret_filter_identifier = leconvert_uint32_from(response.filter_identifier);

	return ret;
}

int can_v2_get_error_log_low_level(CANV2 *can_v2, uint8_t *ret_transceiver_state, uint8_t *ret_transceiver_write_error_level, uint8_t *ret_transceiver_read_error_level, uint32_t *ret_transceiver_stuffing_error_count, uint32_t *ret_transceiver_format_error_count, uint32_t *ret_transceiver_ack_error_count, uint32_t *ret_transceiver_bit1_error_count, uint32_t *ret_transceiver_bit0_error_count, uint32_t *ret_transceiver_crc_error_count, uint32_t *ret_write_buffer_timeout_error_count, uint32_t *ret_read_buffer_overflow_error_count, uint8_t *ret_read_buffer_overflow_error_occurred_length, bool ret_read_buffer_overflow_error_occurred_data[32], uint32_t *ret_read_backlog_overflow_error_count) {
	DevicePrivate *device_p = can_v2->p;
	GetErrorLogLowLevel_Request request;
	GetErrorLogLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_ERROR_LOG_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_transceiver_state = response.transceiver_state;
	*ret_transceiver_write_error_level = response.transceiver_write_error_level;
	*ret_transceiver_read_error_level = response.transceiver_read_error_level;
	*ret_transceiver_stuffing_error_count = leconvert_uint32_from(response.transceiver_stuffing_error_count);
	*ret_transceiver_format_error_count = leconvert_uint32_from(response.transceiver_format_error_count);
	*ret_transceiver_ack_error_count = leconvert_uint32_from(response.transceiver_ack_error_count);
	*ret_transceiver_bit1_error_count = leconvert_uint32_from(response.transceiver_bit1_error_count);
	*ret_transceiver_bit0_error_count = leconvert_uint32_from(response.transceiver_bit0_error_count);
	*ret_transceiver_crc_error_count = leconvert_uint32_from(response.transceiver_crc_error_count);
	*ret_write_buffer_timeout_error_count = leconvert_uint32_from(response.write_buffer_timeout_error_count);
	*ret_read_buffer_overflow_error_count = leconvert_uint32_from(response.read_buffer_overflow_error_count);
	*ret_read_buffer_overflow_error_occurred_length = response.read_buffer_overflow_error_occurred_length;
	for (i = 0; i < 32; i++) ret_read_buffer_overflow_error_occurred_data[i] = (response.read_buffer_overflow_error_occurred_data[i / 8] & (1 << (i % 8))) != 0;
	*ret_read_backlog_overflow_error_count = leconvert_uint32_from(response.read_backlog_overflow_error_count);

	return ret;
}

int can_v2_set_communication_led_config(CANV2 *can_v2, uint8_t config) {
	DevicePrivate *device_p = can_v2->p;
	SetCommunicationLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_communication_led_config(CANV2 *can_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = can_v2->p;
	GetCommunicationLEDConfig_Request request;
	GetCommunicationLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

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

int can_v2_set_error_led_config(CANV2 *can_v2, uint8_t config) {
	DevicePrivate *device_p = can_v2->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_error_led_config(CANV2 *can_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = can_v2->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int can_v2_set_frame_readable_callback_configuration(CANV2 *can_v2, bool enabled) {
	DevicePrivate *device_p = can_v2->p;
	SetFrameReadableCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_frame_readable_callback_configuration(CANV2 *can_v2, bool *ret_enabled) {
	DevicePrivate *device_p = can_v2->p;
	GetFrameReadableCallbackConfiguration_Request request;
	GetFrameReadableCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int can_v2_set_error_occurred_callback_configuration(CANV2 *can_v2, bool enabled) {
	DevicePrivate *device_p = can_v2->p;
	SetErrorOccurredCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_ERROR_OCCURRED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_error_occurred_callback_configuration(CANV2 *can_v2, bool *ret_enabled) {
	DevicePrivate *device_p = can_v2->p;
	GetErrorOccurredCallbackConfiguration_Request request;
	GetErrorOccurredCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_ERROR_OCCURRED_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int can_v2_get_spitfp_error_count(CANV2 *can_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = can_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int can_v2_set_bootloader_mode(CANV2 *can_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = can_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int can_v2_get_bootloader_mode(CANV2 *can_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = can_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int can_v2_set_write_firmware_pointer(CANV2 *can_v2, uint32_t pointer) {
	DevicePrivate *device_p = can_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_write_firmware(CANV2 *can_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = can_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int can_v2_set_status_led_config(CANV2 *can_v2, uint8_t config) {
	DevicePrivate *device_p = can_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_get_status_led_config(CANV2 *can_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = can_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int can_v2_get_chip_temperature(CANV2 *can_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = can_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int can_v2_reset(CANV2 *can_v2) {
	DevicePrivate *device_p = can_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_write_uid(CANV2 *can_v2, uint32_t uid) {
	DevicePrivate *device_p = can_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_v2_read_uid(CANV2 *can_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = can_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int can_v2_get_identity(CANV2 *can_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = can_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CAN_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int can_v2_write_frame(CANV2 *can_v2, uint8_t frame_type, uint32_t identifier, uint8_t *data, uint8_t data_length, bool *ret_success) {
	uint8_t data_data[15];

	if (data_length > 15) {
		return E_INVALID_PARAMETER;
	}

	memcpy(data_data, data, sizeof(uint8_t) * data_length);
	memset(&data_data[data_length], 0, sizeof(uint8_t) * (15 - data_length));

	return can_v2_write_frame_low_level(can_v2, frame_type, identifier, data_length, data_data, ret_success);
}

int can_v2_read_frame(CANV2 *can_v2, bool *ret_success, uint8_t *ret_frame_type, uint32_t *ret_identifier, uint8_t *ret_data, uint8_t *ret_data_length) {
	int ret = 0;
	uint8_t data_length;
	uint8_t data_data[15];

	*ret_data_length = 0;

	ret = can_v2_read_frame_low_level(can_v2, ret_success, ret_frame_type, ret_identifier, &data_length, data_data);

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_data, data_data, sizeof(uint8_t) * data_length);
	memset(&ret_data[data_length], 0, sizeof(uint8_t) * (15 - data_length));

	*ret_data_length = data_length;

	return ret;
}

int can_v2_set_queue_configuration(CANV2 *can_v2, uint8_t write_buffer_size, int32_t write_buffer_timeout, uint16_t write_backlog_size, int8_t *read_buffer_sizes, uint8_t read_buffer_sizes_length, uint16_t read_backlog_size) {
	int8_t read_buffer_sizes_data[32];

	if (read_buffer_sizes_length > 32) {
		return E_INVALID_PARAMETER;
	}

	memcpy(read_buffer_sizes_data, read_buffer_sizes, sizeof(int8_t) * read_buffer_sizes_length);
	memset(&read_buffer_sizes_data[read_buffer_sizes_length], 0, sizeof(int8_t) * (32 - read_buffer_sizes_length));

	return can_v2_set_queue_configuration_low_level(can_v2, write_buffer_size, write_buffer_timeout, write_backlog_size, read_buffer_sizes_length, read_buffer_sizes_data, read_backlog_size);
}

int can_v2_get_queue_configuration(CANV2 *can_v2, uint8_t *ret_write_buffer_size, int32_t *ret_write_buffer_timeout, uint16_t *ret_write_backlog_size, int8_t *ret_read_buffer_sizes, uint8_t *ret_read_buffer_sizes_length, uint16_t *ret_read_backlog_size) {
	int ret = 0;
	uint8_t read_buffer_sizes_length;
	int8_t read_buffer_sizes_data[32];

	*ret_read_buffer_sizes_length = 0;

	ret = can_v2_get_queue_configuration_low_level(can_v2, ret_write_buffer_size, ret_write_buffer_timeout, ret_write_backlog_size, &read_buffer_sizes_length, read_buffer_sizes_data, ret_read_backlog_size);

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_read_buffer_sizes, read_buffer_sizes_data, sizeof(int8_t) * read_buffer_sizes_length);
	memset(&ret_read_buffer_sizes[read_buffer_sizes_length], 0, sizeof(int8_t) * (32 - read_buffer_sizes_length));

	*ret_read_buffer_sizes_length = read_buffer_sizes_length;

	return ret;
}

int can_v2_get_error_log(CANV2 *can_v2, uint8_t *ret_transceiver_state, uint8_t *ret_transceiver_write_error_level, uint8_t *ret_transceiver_read_error_level, uint32_t *ret_transceiver_stuffing_error_count, uint32_t *ret_transceiver_format_error_count, uint32_t *ret_transceiver_ack_error_count, uint32_t *ret_transceiver_bit1_error_count, uint32_t *ret_transceiver_bit0_error_count, uint32_t *ret_transceiver_crc_error_count, uint32_t *ret_write_buffer_timeout_error_count, uint32_t *ret_read_buffer_overflow_error_count, bool *ret_read_buffer_overflow_error_occurred, uint8_t *ret_read_buffer_overflow_error_occurred_length, uint32_t *ret_read_backlog_overflow_error_count) {
	int ret = 0;
	uint8_t read_buffer_overflow_error_occurred_length;
	bool read_buffer_overflow_error_occurred_data[32];

	*ret_read_buffer_overflow_error_occurred_length = 0;

	ret = can_v2_get_error_log_low_level(can_v2, ret_transceiver_state, ret_transceiver_write_error_level, ret_transceiver_read_error_level, ret_transceiver_stuffing_error_count, ret_transceiver_format_error_count, ret_transceiver_ack_error_count, ret_transceiver_bit1_error_count, ret_transceiver_bit0_error_count, ret_transceiver_crc_error_count, ret_write_buffer_timeout_error_count, ret_read_buffer_overflow_error_count, &read_buffer_overflow_error_occurred_length, read_buffer_overflow_error_occurred_data, ret_read_backlog_overflow_error_count);

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_read_buffer_overflow_error_occurred, read_buffer_overflow_error_occurred_data, sizeof(bool) * read_buffer_overflow_error_occurred_length);
	memset(&ret_read_buffer_overflow_error_occurred[read_buffer_overflow_error_occurred_length], 0, sizeof(bool) * (32 - read_buffer_overflow_error_occurred_length));

	*ret_read_buffer_overflow_error_occurred_length = read_buffer_overflow_error_occurred_length;

	return ret;
}

#ifdef __cplusplus
}
#endif
