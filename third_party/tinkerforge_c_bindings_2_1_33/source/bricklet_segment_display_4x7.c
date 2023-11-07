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

#include "bricklet_segment_display_4x7.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*CounterFinished_CallbackFunction)(void *user_data);

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
	uint8_t segments[4];
	uint8_t brightness;
	uint8_t colon;
} ATTRIBUTE_PACKED SetSegments_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSegments_Request;

typedef struct {
	PacketHeader header;
	uint8_t segments[4];
	uint8_t brightness;
	uint8_t colon;
} ATTRIBUTE_PACKED GetSegments_Response;

typedef struct {
	PacketHeader header;
	int16_t value_from;
	int16_t value_to;
	int16_t increment;
	uint32_t length;
} ATTRIBUTE_PACKED StartCounter_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCounterValue_Request;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED GetCounterValue_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED CounterFinished_Callback;

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

static void segment_display_4x7_callback_wrapper_counter_finished(DevicePrivate *device_p, Packet *packet) {
	CounterFinished_CallbackFunction callback_function;
	void *user_data;
	CounterFinished_Callback *callback;

	if (packet->header.length != sizeof(CounterFinished_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CounterFinished_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SEGMENT_DISPLAY_4X7_CALLBACK_COUNTER_FINISHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SEGMENT_DISPLAY_4X7_CALLBACK_COUNTER_FINISHED];
	callback = (CounterFinished_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void segment_display_4x7_create(SegmentDisplay4x7 *segment_display_4x7, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(segment_display_4x7, uid, ipcon_p, 2, 0, 0, SEGMENT_DISPLAY_4X7_DEVICE_IDENTIFIER);

	device_p = segment_display_4x7->p;

	device_p->response_expected[SEGMENT_DISPLAY_4X7_FUNCTION_SET_SEGMENTS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_FUNCTION_GET_SEGMENTS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_FUNCTION_START_COUNTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_FUNCTION_GET_COUNTER_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SEGMENT_DISPLAY_4X7_CALLBACK_COUNTER_FINISHED] = segment_display_4x7_callback_wrapper_counter_finished;

	ipcon_add_device(ipcon_p, device_p);
}

void segment_display_4x7_destroy(SegmentDisplay4x7 *segment_display_4x7) {
	device_release(segment_display_4x7->p);
}

int segment_display_4x7_get_response_expected(SegmentDisplay4x7 *segment_display_4x7, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(segment_display_4x7->p, function_id, ret_response_expected);
}

int segment_display_4x7_set_response_expected(SegmentDisplay4x7 *segment_display_4x7, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(segment_display_4x7->p, function_id, response_expected);
}

int segment_display_4x7_set_response_expected_all(SegmentDisplay4x7 *segment_display_4x7, bool response_expected) {
	return device_set_response_expected_all(segment_display_4x7->p, response_expected);
}

void segment_display_4x7_register_callback(SegmentDisplay4x7 *segment_display_4x7, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(segment_display_4x7->p, callback_id, function, user_data);
}

int segment_display_4x7_get_api_version(SegmentDisplay4x7 *segment_display_4x7, uint8_t ret_api_version[3]) {
	return device_get_api_version(segment_display_4x7->p, ret_api_version);
}

int segment_display_4x7_set_segments(SegmentDisplay4x7 *segment_display_4x7, uint8_t segments[4], uint8_t brightness, bool colon) {
	DevicePrivate *device_p = segment_display_4x7->p;
	SetSegments_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_FUNCTION_SET_SEGMENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.segments, segments, 4 * sizeof(uint8_t));
	request.brightness = brightness;
	request.colon = colon ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_get_segments(SegmentDisplay4x7 *segment_display_4x7, uint8_t ret_segments[4], uint8_t *ret_brightness, bool *ret_colon) {
	DevicePrivate *device_p = segment_display_4x7->p;
	GetSegments_Request request;
	GetSegments_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_FUNCTION_GET_SEGMENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_segments, response.segments, 4 * sizeof(uint8_t));
	*ret_brightness = response.brightness;
	*ret_colon = response.colon != 0;

	return ret;
}

int segment_display_4x7_start_counter(SegmentDisplay4x7 *segment_display_4x7, int16_t value_from, int16_t value_to, int16_t increment, uint32_t length) {
	DevicePrivate *device_p = segment_display_4x7->p;
	StartCounter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_FUNCTION_START_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.value_from = leconvert_int16_to(value_from);
	request.value_to = leconvert_int16_to(value_to);
	request.increment = leconvert_int16_to(increment);
	request.length = leconvert_uint32_to(length);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_get_counter_value(SegmentDisplay4x7 *segment_display_4x7, uint16_t *ret_value) {
	DevicePrivate *device_p = segment_display_4x7->p;
	GetCounterValue_Request request;
	GetCounterValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_FUNCTION_GET_COUNTER_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = leconvert_uint16_from(response.value);

	return ret;
}

int segment_display_4x7_get_identity(SegmentDisplay4x7 *segment_display_4x7, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = segment_display_4x7->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
