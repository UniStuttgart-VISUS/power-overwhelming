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

#include "bricklet_rs232_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ReadLowLevel_CallbackFunction)(uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60], void *user_data);

typedef void (*ErrorCount_CallbackFunction)(uint32_t error_count_overrun, uint32_t error_count_parity, void *user_data);

typedef void (*FrameReadable_CallbackFunction)(uint16_t frame_count, void *user_data);

typedef void (*Read_CallbackFunction)(char *message, uint16_t message_length, void *user_data);

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
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED WriteLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t message_chunk_written;
} ATTRIBUTE_PACKED WriteLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint16_t length;
} ATTRIBUTE_PACKED ReadLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED ReadLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsReadCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsReadCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t flowcontrol;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t flowcontrol;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_size;
	uint16_t receive_buffer_size;
} ATTRIBUTE_PACKED SetBufferConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBufferConfig_Request;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_size;
	uint16_t receive_buffer_size;
} ATTRIBUTE_PACKED GetBufferConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBufferStatus_Request;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_used;
	uint16_t receive_buffer_used;
} ATTRIBUTE_PACKED GetBufferStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t error_count_overrun;
	uint32_t error_count_parity;
} ATTRIBUTE_PACKED GetErrorCount_Response;

typedef struct {
	PacketHeader header;
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED ReadLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint32_t error_count_overrun;
	uint32_t error_count_parity;
} ATTRIBUTE_PACKED ErrorCount_Callback;

typedef struct {
	PacketHeader header;
	uint16_t frame_size;
} ATTRIBUTE_PACKED SetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t frame_size;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t frame_count;
} ATTRIBUTE_PACKED FrameReadable_Callback;

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

static void rs232_v2_callback_wrapper_read(DevicePrivate *device_p, uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60]) {
	Read_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_READ];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS232_V2_CALLBACK_READ];
	uint16_t message_chunk_length = message_length - message_chunk_offset;

	callback_function = (Read_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_READ];

	if (message_chunk_length > 60) {
		message_chunk_length = 60;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (message_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(char) * message_length);
			high_level_callback->length = message_chunk_length;

			memcpy(high_level_callback->data, message_chunk_data, sizeof(char) * message_chunk_length);

			if (high_level_callback->length >= message_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (message_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((char *)high_level_callback->data)[high_level_callback->length], message_chunk_data, sizeof(char) * message_chunk_length);
			high_level_callback->length += message_chunk_length;

			if (high_level_callback->length >= message_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs232_v2_callback_wrapper_read_low_level(DevicePrivate *device_p, Packet *packet) {
	ReadLowLevel_CallbackFunction callback_function;
	void *user_data;
	ReadLowLevel_Callback *callback;

	if (packet->header.length != sizeof(ReadLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ReadLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_READ_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_READ_LOW_LEVEL];
	callback = (ReadLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->message_length = leconvert_uint16_from(callback->message_length);
	callback->message_chunk_offset = leconvert_uint16_from(callback->message_chunk_offset);

	rs232_v2_callback_wrapper_read(device_p, callback->message_length, callback->message_chunk_offset, callback->message_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->message_length, callback->message_chunk_offset, callback->message_chunk_data, user_data);
	}
}

static void rs232_v2_callback_wrapper_error_count(DevicePrivate *device_p, Packet *packet) {
	ErrorCount_CallbackFunction callback_function;
	void *user_data;
	ErrorCount_Callback *callback;

	if (packet->header.length != sizeof(ErrorCount_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ErrorCount_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_ERROR_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_ERROR_COUNT];
	callback = (ErrorCount_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->error_count_overrun = leconvert_uint32_from(callback->error_count_overrun);
	callback->error_count_parity = leconvert_uint32_from(callback->error_count_parity);

	callback_function(callback->error_count_overrun, callback->error_count_parity, user_data);
}

static void rs232_v2_callback_wrapper_frame_readable(DevicePrivate *device_p, Packet *packet) {
	FrameReadable_CallbackFunction callback_function;
	void *user_data;
	FrameReadable_Callback *callback;

	if (packet->header.length != sizeof(FrameReadable_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameReadable_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_FRAME_READABLE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS232_V2_CALLBACK_FRAME_READABLE];
	callback = (FrameReadable_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->frame_count = leconvert_uint16_from(callback->frame_count);

	callback_function(callback->frame_count, user_data);
}

void rs232_v2_create(RS232V2 *rs232_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(rs232_v2, uid, ipcon_p, 2, 0, 1, RS232_V2_DEVICE_IDENTIFIER);

	device_p = rs232_v2->p;

	device_p->response_expected[RS232_V2_FUNCTION_WRITE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_READ_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_ENABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_DISABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_IS_READ_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_BUFFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_BUFFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_BUFFER_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS232_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS232_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RS232_V2_CALLBACK_READ_LOW_LEVEL] = rs232_v2_callback_wrapper_read_low_level;
	device_p->callback_wrappers[RS232_V2_CALLBACK_ERROR_COUNT] = rs232_v2_callback_wrapper_error_count;
	device_p->callback_wrappers[RS232_V2_CALLBACK_FRAME_READABLE] = rs232_v2_callback_wrapper_frame_readable;

	device_p->high_level_callbacks[-RS232_V2_CALLBACK_READ].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void rs232_v2_destroy(RS232V2 *rs232_v2) {
	device_release(rs232_v2->p);
}

int rs232_v2_get_response_expected(RS232V2 *rs232_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rs232_v2->p, function_id, ret_response_expected);
}

int rs232_v2_set_response_expected(RS232V2 *rs232_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rs232_v2->p, function_id, response_expected);
}

int rs232_v2_set_response_expected_all(RS232V2 *rs232_v2, bool response_expected) {
	return device_set_response_expected_all(rs232_v2->p, response_expected);
}

void rs232_v2_register_callback(RS232V2 *rs232_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(rs232_v2->p, callback_id, function, user_data);
}

int rs232_v2_get_api_version(RS232V2 *rs232_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(rs232_v2->p, ret_api_version);
}

int rs232_v2_write_low_level(RS232V2 *rs232_v2, uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60], uint8_t *ret_message_chunk_written) {
	DevicePrivate *device_p = rs232_v2->p;
	WriteLowLevel_Request request;
	WriteLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_WRITE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.message_length = leconvert_uint16_to(message_length);
	request.message_chunk_offset = leconvert_uint16_to(message_chunk_offset);
	memcpy(request.message_chunk_data, message_chunk_data, 60 * sizeof(char));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_message_chunk_written = response.message_chunk_written;

	return ret;
}

int rs232_v2_read_low_level(RS232V2 *rs232_v2, uint16_t length, uint16_t *ret_message_length, uint16_t *ret_message_chunk_offset, char ret_message_chunk_data[60]) {
	DevicePrivate *device_p = rs232_v2->p;
	ReadLowLevel_Request request;
	ReadLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_READ_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.length = leconvert_uint16_to(length);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_message_length = leconvert_uint16_from(response.message_length);
	*ret_message_chunk_offset = leconvert_uint16_from(response.message_chunk_offset);
	memcpy(ret_message_chunk_data, response.message_chunk_data, 60 * sizeof(char));

	return ret;
}

int rs232_v2_enable_read_callback(RS232V2 *rs232_v2) {
	DevicePrivate *device_p = rs232_v2->p;
	EnableReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_ENABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_disable_read_callback(RS232V2 *rs232_v2) {
	DevicePrivate *device_p = rs232_v2->p;
	DisableReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_DISABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_is_read_callback_enabled(RS232V2 *rs232_v2, bool *ret_enabled) {
	DevicePrivate *device_p = rs232_v2->p;
	IsReadCallbackEnabled_Request request;
	IsReadCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_IS_READ_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int rs232_v2_set_configuration(RS232V2 *rs232_v2, uint32_t baudrate, uint8_t parity, uint8_t stopbits, uint8_t wordlength, uint8_t flowcontrol) {
	DevicePrivate *device_p = rs232_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.baudrate = leconvert_uint32_to(baudrate);
	request.parity = parity;
	request.stopbits = stopbits;
	request.wordlength = wordlength;
	request.flowcontrol = flowcontrol;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_get_configuration(RS232V2 *rs232_v2, uint32_t *ret_baudrate, uint8_t *ret_parity, uint8_t *ret_stopbits, uint8_t *ret_wordlength, uint8_t *ret_flowcontrol) {
	DevicePrivate *device_p = rs232_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baudrate = leconvert_uint32_from(response.baudrate);
	*ret_parity = response.parity;
	*ret_stopbits = response.stopbits;
	*ret_wordlength = response.wordlength;
	*ret_flowcontrol = response.flowcontrol;

	return ret;
}

int rs232_v2_set_buffer_config(RS232V2 *rs232_v2, uint16_t send_buffer_size, uint16_t receive_buffer_size) {
	DevicePrivate *device_p = rs232_v2->p;
	SetBufferConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_BUFFER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.send_buffer_size = leconvert_uint16_to(send_buffer_size);
	request.receive_buffer_size = leconvert_uint16_to(receive_buffer_size);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_get_buffer_config(RS232V2 *rs232_v2, uint16_t *ret_send_buffer_size, uint16_t *ret_receive_buffer_size) {
	DevicePrivate *device_p = rs232_v2->p;
	GetBufferConfig_Request request;
	GetBufferConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_BUFFER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_send_buffer_size = leconvert_uint16_from(response.send_buffer_size);
	*ret_receive_buffer_size = leconvert_uint16_from(response.receive_buffer_size);

	return ret;
}

int rs232_v2_get_buffer_status(RS232V2 *rs232_v2, uint16_t *ret_send_buffer_used, uint16_t *ret_receive_buffer_used) {
	DevicePrivate *device_p = rs232_v2->p;
	GetBufferStatus_Request request;
	GetBufferStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_BUFFER_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_send_buffer_used = leconvert_uint16_from(response.send_buffer_used);
	*ret_receive_buffer_used = leconvert_uint16_from(response.receive_buffer_used);

	return ret;
}

int rs232_v2_get_error_count(RS232V2 *rs232_v2, uint32_t *ret_error_count_overrun, uint32_t *ret_error_count_parity) {
	DevicePrivate *device_p = rs232_v2->p;
	GetErrorCount_Request request;
	GetErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_error_count_overrun = leconvert_uint32_from(response.error_count_overrun);
	*ret_error_count_parity = leconvert_uint32_from(response.error_count_parity);

	return ret;
}

int rs232_v2_set_frame_readable_callback_configuration(RS232V2 *rs232_v2, uint16_t frame_size) {
	DevicePrivate *device_p = rs232_v2->p;
	SetFrameReadableCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_size = leconvert_uint16_to(frame_size);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_get_frame_readable_callback_configuration(RS232V2 *rs232_v2, uint16_t *ret_frame_size) {
	DevicePrivate *device_p = rs232_v2->p;
	GetFrameReadableCallbackConfiguration_Request request;
	GetFrameReadableCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_size = leconvert_uint16_from(response.frame_size);

	return ret;
}

int rs232_v2_get_spitfp_error_count(RS232V2 *rs232_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = rs232_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int rs232_v2_set_bootloader_mode(RS232V2 *rs232_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = rs232_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rs232_v2_get_bootloader_mode(RS232V2 *rs232_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = rs232_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rs232_v2_set_write_firmware_pointer(RS232V2 *rs232_v2, uint32_t pointer) {
	DevicePrivate *device_p = rs232_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_write_firmware(RS232V2 *rs232_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = rs232_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int rs232_v2_set_status_led_config(RS232V2 *rs232_v2, uint8_t config) {
	DevicePrivate *device_p = rs232_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_get_status_led_config(RS232V2 *rs232_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = rs232_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rs232_v2_get_chip_temperature(RS232V2 *rs232_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = rs232_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int rs232_v2_reset(RS232V2 *rs232_v2) {
	DevicePrivate *device_p = rs232_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_write_uid(RS232V2 *rs232_v2, uint32_t uid) {
	DevicePrivate *device_p = rs232_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs232_v2_read_uid(RS232V2 *rs232_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = rs232_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int rs232_v2_get_identity(RS232V2 *rs232_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rs232_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS232_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int rs232_v2_write(RS232V2 *rs232_v2, const char *message, uint16_t message_length, uint16_t *ret_message_written) {
	DevicePrivate *device_p = rs232_v2->p;
	int ret = 0;
	uint16_t message_chunk_offset = 0;
	char message_chunk_data[60];
	uint16_t message_chunk_length;
	uint8_t message_chunk_written;

	*ret_message_written = 0;

	if (message_length == 0) {
		memset(&message_chunk_data, 0, sizeof(char) * 60);

		ret = rs232_v2_write_low_level(rs232_v2, message_length, message_chunk_offset, message_chunk_data, &message_chunk_written);

		if (ret < 0) {
			return ret;
		}

		*ret_message_written = message_chunk_written;
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (message_chunk_offset < message_length) {
			message_chunk_length = message_length - message_chunk_offset;

			if (message_chunk_length > 60) {
				message_chunk_length = 60;
			}

			memcpy(message_chunk_data, &message[message_chunk_offset], sizeof(char) * message_chunk_length);
			memset(&message_chunk_data[message_chunk_length], 0, sizeof(char) * (60 - message_chunk_length));

			ret = rs232_v2_write_low_level(rs232_v2, message_length, message_chunk_offset, message_chunk_data, &message_chunk_written);

			if (ret < 0) {
				*ret_message_written = 0;

				break;
			}

			*ret_message_written += message_chunk_written;

			if (message_chunk_written < 60) {
				break; // either last chunk or short write
			}

			message_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs232_v2_read(RS232V2 *rs232_v2, uint16_t length, char *ret_message, uint16_t *ret_message_length) {
	DevicePrivate *device_p = rs232_v2->p;
	int ret = 0;
	uint16_t message_length = 0;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
	bool message_out_of_sync;
	uint16_t message_chunk_length;

	*ret_message_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = rs232_v2_read_low_level(rs232_v2, length, &message_length, &message_chunk_offset, message_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	message_out_of_sync = message_chunk_offset != 0;

	if (!message_out_of_sync) {
		message_chunk_length = message_length - message_chunk_offset;

		if (message_chunk_length > 60) {
			message_chunk_length = 60;
		}

		memcpy(ret_message, message_chunk_data, sizeof(char) * message_chunk_length);
		*ret_message_length = message_chunk_length;

		while (*ret_message_length < message_length) {
			ret = rs232_v2_read_low_level(rs232_v2, length, &message_length, &message_chunk_offset, message_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			message_out_of_sync = message_chunk_offset != *ret_message_length;

			if (message_out_of_sync) {
				break;
			}

			message_chunk_length = message_length - message_chunk_offset;

			if (message_chunk_length > 60) {
				message_chunk_length = 60;
			}

			memcpy(&ret_message[*ret_message_length], message_chunk_data, sizeof(char) * message_chunk_length);
			*ret_message_length += message_chunk_length;
		}
	}

	if (message_out_of_sync) {
		*ret_message_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (message_chunk_offset + 60 < message_length) {
			ret = rs232_v2_read_low_level(rs232_v2, length, &message_length, &message_chunk_offset, message_chunk_data);

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
