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

#include "bricklet_can.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*FrameRead_CallbackFunction)(uint8_t frame_type, uint32_t identifier, uint8_t data[8], uint8_t length, void *user_data);

typedef void (*FrameReadable_CallbackFunction)(void *user_data);

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
	uint8_t data[8];
	uint8_t length;
} ATTRIBUTE_PACKED WriteFrame_Request;

typedef struct {
	PacketHeader header;
	uint8_t success;
} ATTRIBUTE_PACKED WriteFrame_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadFrame_Request;

typedef struct {
	PacketHeader header;
	uint8_t success;
	uint8_t frame_type;
	uint32_t identifier;
	uint8_t data[8];
	uint8_t length;
} ATTRIBUTE_PACKED ReadFrame_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableFrameReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableFrameReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsFrameReadCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsFrameReadCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t baud_rate;
	uint8_t transceiver_mode;
	int32_t write_timeout;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t baud_rate;
	uint8_t transceiver_mode;
	int32_t write_timeout;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
	uint32_t mask;
	uint32_t filter1;
	uint32_t filter2;
} ATTRIBUTE_PACKED SetReadFilter_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetReadFilter_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
	uint32_t mask;
	uint32_t filter1;
	uint32_t filter2;
} ATTRIBUTE_PACKED GetReadFilter_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorLog_Request;

typedef struct {
	PacketHeader header;
	uint8_t write_error_level;
	uint8_t read_error_level;
	uint8_t transceiver_disabled;
	uint32_t write_timeout_count;
	uint32_t read_register_overflow_count;
	uint32_t read_buffer_overflow_count;
} ATTRIBUTE_PACKED GetErrorLog_Response;

typedef struct {
	PacketHeader header;
	uint8_t frame_type;
	uint32_t identifier;
	uint8_t data[8];
	uint8_t length;
} ATTRIBUTE_PACKED FrameRead_Callback;

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

static void can_callback_wrapper_frame_read(DevicePrivate *device_p, Packet *packet) {
	FrameRead_CallbackFunction callback_function;
	void *user_data;
	FrameRead_Callback *callback;

	if (packet->header.length != sizeof(FrameRead_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameRead_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_CALLBACK_FRAME_READ];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_CALLBACK_FRAME_READ];
	callback = (FrameRead_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->identifier = leconvert_uint32_from(callback->identifier);

	callback_function(callback->frame_type, callback->identifier, callback->data, callback->length, user_data);
}

static void can_callback_wrapper_frame_readable(DevicePrivate *device_p, Packet *packet) {
	FrameReadable_CallbackFunction callback_function;
	void *user_data;
	FrameReadable_Callback *callback;

	if (packet->header.length != sizeof(FrameReadable_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameReadable_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CAN_CALLBACK_FRAME_READABLE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CAN_CALLBACK_FRAME_READABLE];
	callback = (FrameReadable_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void can_create(CAN *can, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(can, uid, ipcon_p, 2, 0, 1, CAN_DEVICE_IDENTIFIER);

	device_p = can->p;

	device_p->response_expected[CAN_FUNCTION_WRITE_FRAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_READ_FRAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_ENABLE_FRAME_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_FUNCTION_DISABLE_FRAME_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_FUNCTION_IS_FRAME_READ_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_SET_READ_FILTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[CAN_FUNCTION_GET_READ_FILTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_GET_ERROR_LOG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CAN_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CAN_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CAN_CALLBACK_FRAME_READ] = can_callback_wrapper_frame_read;
	device_p->callback_wrappers[CAN_CALLBACK_FRAME_READABLE] = can_callback_wrapper_frame_readable;

	ipcon_add_device(ipcon_p, device_p);
}

void can_destroy(CAN *can) {
	device_release(can->p);
}

int can_get_response_expected(CAN *can, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(can->p, function_id, ret_response_expected);
}

int can_set_response_expected(CAN *can, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(can->p, function_id, response_expected);
}

int can_set_response_expected_all(CAN *can, bool response_expected) {
	return device_set_response_expected_all(can->p, response_expected);
}

void can_register_callback(CAN *can, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(can->p, callback_id, function, user_data);
}

int can_get_api_version(CAN *can, uint8_t ret_api_version[3]) {
	return device_get_api_version(can->p, ret_api_version);
}

int can_write_frame(CAN *can, uint8_t frame_type, uint32_t identifier, uint8_t data[8], uint8_t length, bool *ret_success) {
	DevicePrivate *device_p = can->p;
	WriteFrame_Request request;
	WriteFrame_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_WRITE_FRAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_type = frame_type;
	request.identifier = leconvert_uint32_to(identifier);
	memcpy(request.data, data, 8 * sizeof(uint8_t));
	request.length = length;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_success = response.success != 0;

	return ret;
}

int can_read_frame(CAN *can, bool *ret_success, uint8_t *ret_frame_type, uint32_t *ret_identifier, uint8_t ret_data[8], uint8_t *ret_length) {
	DevicePrivate *device_p = can->p;
	ReadFrame_Request request;
	ReadFrame_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_READ_FRAME, device_p->ipcon_p, device_p);

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
	memcpy(ret_data, response.data, 8 * sizeof(uint8_t));
	*ret_length = response.length;

	return ret;
}

int can_enable_frame_read_callback(CAN *can) {
	DevicePrivate *device_p = can->p;
	EnableFrameReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_ENABLE_FRAME_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_disable_frame_read_callback(CAN *can) {
	DevicePrivate *device_p = can->p;
	DisableFrameReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_DISABLE_FRAME_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_is_frame_read_callback_enabled(CAN *can, bool *ret_enabled) {
	DevicePrivate *device_p = can->p;
	IsFrameReadCallbackEnabled_Request request;
	IsFrameReadCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_IS_FRAME_READ_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int can_set_configuration(CAN *can, uint8_t baud_rate, uint8_t transceiver_mode, int32_t write_timeout) {
	DevicePrivate *device_p = can->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.baud_rate = baud_rate;
	request.transceiver_mode = transceiver_mode;
	request.write_timeout = leconvert_int32_to(write_timeout);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_get_configuration(CAN *can, uint8_t *ret_baud_rate, uint8_t *ret_transceiver_mode, int32_t *ret_write_timeout) {
	DevicePrivate *device_p = can->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baud_rate = response.baud_rate;
	*ret_transceiver_mode = response.transceiver_mode;
	*ret_write_timeout = leconvert_int32_from(response.write_timeout);

	return ret;
}

int can_set_read_filter(CAN *can, uint8_t mode, uint32_t mask, uint32_t filter1, uint32_t filter2) {
	DevicePrivate *device_p = can->p;
	SetReadFilter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_SET_READ_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;
	request.mask = leconvert_uint32_to(mask);
	request.filter1 = leconvert_uint32_to(filter1);
	request.filter2 = leconvert_uint32_to(filter2);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_get_read_filter(CAN *can, uint8_t *ret_mode, uint32_t *ret_mask, uint32_t *ret_filter1, uint32_t *ret_filter2) {
	DevicePrivate *device_p = can->p;
	GetReadFilter_Request request;
	GetReadFilter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_GET_READ_FILTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_mode = response.mode;
	*ret_mask = leconvert_uint32_from(response.mask);
	*ret_filter1 = leconvert_uint32_from(response.filter1);
	*ret_filter2 = leconvert_uint32_from(response.filter2);

	return ret;
}

int can_get_error_log(CAN *can, uint8_t *ret_write_error_level, uint8_t *ret_read_error_level, bool *ret_transceiver_disabled, uint32_t *ret_write_timeout_count, uint32_t *ret_read_register_overflow_count, uint32_t *ret_read_buffer_overflow_count) {
	DevicePrivate *device_p = can->p;
	GetErrorLog_Request request;
	GetErrorLog_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_GET_ERROR_LOG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_write_error_level = response.write_error_level;
	*ret_read_error_level = response.read_error_level;
	*ret_transceiver_disabled = response.transceiver_disabled != 0;
	*ret_write_timeout_count = leconvert_uint32_from(response.write_timeout_count);
	*ret_read_register_overflow_count = leconvert_uint32_from(response.read_register_overflow_count);
	*ret_read_buffer_overflow_count = leconvert_uint32_from(response.read_buffer_overflow_count);

	return ret;
}

int can_set_frame_readable_callback_configuration(CAN *can, bool enabled) {
	DevicePrivate *device_p = can->p;
	SetFrameReadableCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enabled = enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int can_get_frame_readable_callback_configuration(CAN *can, bool *ret_enabled) {
	DevicePrivate *device_p = can->p;
	GetFrameReadableCallbackConfiguration_Request request;
	GetFrameReadableCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int can_get_identity(CAN *can, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = can->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CAN_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
