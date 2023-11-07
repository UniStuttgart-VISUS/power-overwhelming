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

#include "bricklet_segment_display_4x7_v2.h"

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
	uint8_t digit0[1];
	uint8_t digit1[1];
	uint8_t digit2[1];
	uint8_t digit3[1];
	uint8_t colon[1];
	uint8_t tick;
} ATTRIBUTE_PACKED SetSegments_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSegments_Request;

typedef struct {
	PacketHeader header;
	uint8_t digit0[1];
	uint8_t digit1[1];
	uint8_t digit2[1];
	uint8_t digit3[1];
	uint8_t colon[1];
	uint8_t tick;
} ATTRIBUTE_PACKED GetSegments_Response;

typedef struct {
	PacketHeader header;
	uint8_t brightness;
} ATTRIBUTE_PACKED SetBrightness_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBrightness_Request;

typedef struct {
	PacketHeader header;
	uint8_t brightness;
} ATTRIBUTE_PACKED GetBrightness_Response;

typedef struct {
	PacketHeader header;
	int8_t value[4];
} ATTRIBUTE_PACKED SetNumericValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t segment;
	uint8_t value;
} ATTRIBUTE_PACKED SetSelectedSegment_Request;

typedef struct {
	PacketHeader header;
	uint8_t segment;
} ATTRIBUTE_PACKED GetSelectedSegment_Request;

typedef struct {
	PacketHeader header;
	uint8_t value;
} ATTRIBUTE_PACKED GetSelectedSegment_Response;

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

static void segment_display_4x7_v2_callback_wrapper_counter_finished(DevicePrivate *device_p, Packet *packet) {
	CounterFinished_CallbackFunction callback_function;
	void *user_data;
	CounterFinished_Callback *callback;

	if (packet->header.length != sizeof(CounterFinished_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CounterFinished_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + SEGMENT_DISPLAY_4X7_V2_CALLBACK_COUNTER_FINISHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + SEGMENT_DISPLAY_4X7_V2_CALLBACK_COUNTER_FINISHED];
	callback = (CounterFinished_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void segment_display_4x7_v2_create(SegmentDisplay4x7V2 *segment_display_4x7_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(segment_display_4x7_v2, uid, ipcon_p, 2, 0, 0, SEGMENT_DISPLAY_4X7_V2_DEVICE_IDENTIFIER);

	device_p = segment_display_4x7_v2->p;

	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_SEGMENTS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SEGMENTS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_BRIGHTNESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_BRIGHTNESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_NUMERIC_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_SELECTED_SEGMENT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SELECTED_SEGMENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_START_COUNTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_COUNTER_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[SEGMENT_DISPLAY_4X7_V2_CALLBACK_COUNTER_FINISHED] = segment_display_4x7_v2_callback_wrapper_counter_finished;

	ipcon_add_device(ipcon_p, device_p);
}

void segment_display_4x7_v2_destroy(SegmentDisplay4x7V2 *segment_display_4x7_v2) {
	device_release(segment_display_4x7_v2->p);
}

int segment_display_4x7_v2_get_response_expected(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(segment_display_4x7_v2->p, function_id, ret_response_expected);
}

int segment_display_4x7_v2_set_response_expected(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(segment_display_4x7_v2->p, function_id, response_expected);
}

int segment_display_4x7_v2_set_response_expected_all(SegmentDisplay4x7V2 *segment_display_4x7_v2, bool response_expected) {
	return device_set_response_expected_all(segment_display_4x7_v2->p, response_expected);
}

void segment_display_4x7_v2_register_callback(SegmentDisplay4x7V2 *segment_display_4x7_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(segment_display_4x7_v2->p, callback_id, function, user_data);
}

int segment_display_4x7_v2_get_api_version(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(segment_display_4x7_v2->p, ret_api_version);
}

int segment_display_4x7_v2_set_segments(SegmentDisplay4x7V2 *segment_display_4x7_v2, bool digit0[8], bool digit1[8], bool digit2[8], bool digit3[8], bool colon[2], bool tick) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetSegments_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_SEGMENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memset(request.digit0, 0, 1); for (i = 0; i < 8; i++) request.digit0[i / 8] |= (digit0[i] ? 1 : 0) << (i % 8);
	memset(request.digit1, 0, 1); for (i = 0; i < 8; i++) request.digit1[i / 8] |= (digit1[i] ? 1 : 0) << (i % 8);
	memset(request.digit2, 0, 1); for (i = 0; i < 8; i++) request.digit2[i / 8] |= (digit2[i] ? 1 : 0) << (i % 8);
	memset(request.digit3, 0, 1); for (i = 0; i < 8; i++) request.digit3[i / 8] |= (digit3[i] ? 1 : 0) << (i % 8);
	memset(request.colon, 0, 1); for (i = 0; i < 2; i++) request.colon[i / 8] |= (colon[i] ? 1 : 0) << (i % 8);
	request.tick = tick ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_get_segments(SegmentDisplay4x7V2 *segment_display_4x7_v2, bool ret_digit0[8], bool ret_digit1[8], bool ret_digit2[8], bool ret_digit3[8], bool ret_colon[2], bool *ret_tick) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetSegments_Request request;
	GetSegments_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SEGMENTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 8; i++) ret_digit0[i] = (response.digit0[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 8; i++) ret_digit1[i] = (response.digit1[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 8; i++) ret_digit2[i] = (response.digit2[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 8; i++) ret_digit3[i] = (response.digit3[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 2; i++) ret_colon[i] = (response.colon[i / 8] & (1 << (i % 8))) != 0;
	*ret_tick = response.tick != 0;

	return ret;
}

int segment_display_4x7_v2_set_brightness(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t brightness) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetBrightness_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_BRIGHTNESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.brightness = brightness;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_get_brightness(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t *ret_brightness) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetBrightness_Request request;
	GetBrightness_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_BRIGHTNESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_brightness = response.brightness;

	return ret;
}

int segment_display_4x7_v2_set_numeric_value(SegmentDisplay4x7V2 *segment_display_4x7_v2, int8_t value[4]) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetNumericValue_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_NUMERIC_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.value, value, 4 * sizeof(int8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_set_selected_segment(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t segment, bool value) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetSelectedSegment_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_SELECTED_SEGMENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.segment = segment;
	request.value = value ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_get_selected_segment(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t segment, bool *ret_value) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetSelectedSegment_Request request;
	GetSelectedSegment_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SELECTED_SEGMENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.segment = segment;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = response.value != 0;

	return ret;
}

int segment_display_4x7_v2_start_counter(SegmentDisplay4x7V2 *segment_display_4x7_v2, int16_t value_from, int16_t value_to, int16_t increment, uint32_t length) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	StartCounter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_START_COUNTER, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_get_counter_value(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint16_t *ret_value) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetCounterValue_Request request;
	GetCounterValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_COUNTER_VALUE, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_get_spitfp_error_count(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_set_bootloader_mode(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_get_bootloader_mode(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_set_write_firmware_pointer(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint32_t pointer) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_write_firmware(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_set_status_led_config(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t config) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_get_status_led_config(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_get_chip_temperature(SegmentDisplay4x7V2 *segment_display_4x7_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_reset(SegmentDisplay4x7V2 *segment_display_4x7_v2) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_write_uid(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint32_t uid) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int segment_display_4x7_v2_read_uid(SegmentDisplay4x7V2 *segment_display_4x7_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int segment_display_4x7_v2_get_identity(SegmentDisplay4x7V2 *segment_display_4x7_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = segment_display_4x7_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), SEGMENT_DISPLAY_4X7_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
