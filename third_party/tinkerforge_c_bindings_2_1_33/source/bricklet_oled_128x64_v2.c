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

#include "bricklet_oled_128x64_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



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
	uint8_t x_start;
	uint8_t y_start;
	uint8_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[56];
} ATTRIBUTE_PACKED WritePixelsLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t x_start;
	uint8_t y_start;
	uint8_t x_end;
	uint8_t y_end;
} ATTRIBUTE_PACKED ReadPixelsLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[60];
} ATTRIBUTE_PACKED ReadPixelsLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ClearDisplay_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t invert;
	uint8_t automatic_draw;
} ATTRIBUTE_PACKED SetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t invert;
	uint8_t automatic_draw;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t line;
	uint8_t position;
	char text[22];
} ATTRIBUTE_PACKED WriteLine_Request;

typedef struct {
	PacketHeader header;
	uint8_t force_complete_redraw;
} ATTRIBUTE_PACKED DrawBufferedFrame_Request;

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

void oled_128x64_v2_create(OLED128x64V2 *oled_128x64_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(oled_128x64_v2, uid, ipcon_p, 2, 0, 0, OLED_128X64_V2_DEVICE_IDENTIFIER);

	device_p = oled_128x64_v2->p;

	device_p->response_expected[OLED_128X64_V2_FUNCTION_WRITE_PIXELS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_READ_PIXELS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_CLEAR_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_SET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_WRITE_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_DRAW_BUFFERED_FRAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	ipcon_add_device(ipcon_p, device_p);
}

void oled_128x64_v2_destroy(OLED128x64V2 *oled_128x64_v2) {
	device_release(oled_128x64_v2->p);
}

int oled_128x64_v2_get_response_expected(OLED128x64V2 *oled_128x64_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(oled_128x64_v2->p, function_id, ret_response_expected);
}

int oled_128x64_v2_set_response_expected(OLED128x64V2 *oled_128x64_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(oled_128x64_v2->p, function_id, response_expected);
}

int oled_128x64_v2_set_response_expected_all(OLED128x64V2 *oled_128x64_v2, bool response_expected) {
	return device_set_response_expected_all(oled_128x64_v2->p, response_expected);
}


int oled_128x64_v2_get_api_version(OLED128x64V2 *oled_128x64_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(oled_128x64_v2->p, ret_api_version);
}

int oled_128x64_v2_write_pixels_low_level(OLED128x64V2 *oled_128x64_v2, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint16_t pixels_length, uint16_t pixels_chunk_offset, bool pixels_chunk_data[448]) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	WritePixelsLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_WRITE_PIXELS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = x_start;
	request.y_start = y_start;
	request.x_end = x_end;
	request.y_end = y_end;
	request.pixels_length = leconvert_uint16_to(pixels_length);
	request.pixels_chunk_offset = leconvert_uint16_to(pixels_chunk_offset);
	memset(request.pixels_chunk_data, 0, 56); for (i = 0; i < 448; i++) request.pixels_chunk_data[i / 8] |= (pixels_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_read_pixels_low_level(OLED128x64V2 *oled_128x64_v2, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint16_t *ret_pixels_length, uint16_t *ret_pixels_chunk_offset, bool ret_pixels_chunk_data[480]) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	ReadPixelsLowLevel_Request request;
	ReadPixelsLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_READ_PIXELS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = x_start;
	request.y_start = y_start;
	request.x_end = x_end;
	request.y_end = y_end;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pixels_length = leconvert_uint16_from(response.pixels_length);
	*ret_pixels_chunk_offset = leconvert_uint16_from(response.pixels_chunk_offset);
	for (i = 0; i < 480; i++) ret_pixels_chunk_data[i] = (response.pixels_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int oled_128x64_v2_clear_display(OLED128x64V2 *oled_128x64_v2) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	ClearDisplay_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_CLEAR_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_set_display_configuration(OLED128x64V2 *oled_128x64_v2, uint8_t contrast, bool invert, bool automatic_draw) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	SetDisplayConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_SET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.contrast = contrast;
	request.invert = invert ? 1 : 0;
	request.automatic_draw = automatic_draw ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_get_display_configuration(OLED128x64V2 *oled_128x64_v2, uint8_t *ret_contrast, bool *ret_invert, bool *ret_automatic_draw) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetDisplayConfiguration_Request request;
	GetDisplayConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_contrast = response.contrast;
	*ret_invert = response.invert != 0;
	*ret_automatic_draw = response.automatic_draw != 0;

	return ret;
}

int oled_128x64_v2_write_line(OLED128x64V2 *oled_128x64_v2, uint8_t line, uint8_t position, const char *text) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	WriteLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_WRITE_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.line = line;
	request.position = position;
	string_copy(request.text, text, 22);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_draw_buffered_frame(OLED128x64V2 *oled_128x64_v2, bool force_complete_redraw) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	DrawBufferedFrame_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_DRAW_BUFFERED_FRAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.force_complete_redraw = force_complete_redraw ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_get_spitfp_error_count(OLED128x64V2 *oled_128x64_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_set_bootloader_mode(OLED128x64V2 *oled_128x64_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_get_bootloader_mode(OLED128x64V2 *oled_128x64_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_set_write_firmware_pointer(OLED128x64V2 *oled_128x64_v2, uint32_t pointer) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_write_firmware(OLED128x64V2 *oled_128x64_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_set_status_led_config(OLED128x64V2 *oled_128x64_v2, uint8_t config) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_get_status_led_config(OLED128x64V2 *oled_128x64_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_get_chip_temperature(OLED128x64V2 *oled_128x64_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_reset(OLED128x64V2 *oled_128x64_v2) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_write_uid(OLED128x64V2 *oled_128x64_v2, uint32_t uid) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_v2_read_uid(OLED128x64V2 *oled_128x64_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_get_identity(OLED128x64V2 *oled_128x64_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int oled_128x64_v2_write_pixels(OLED128x64V2 *oled_128x64_v2, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, bool *pixels, uint16_t pixels_length) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	int ret = 0;
	uint16_t pixels_chunk_offset = 0;
	bool pixels_chunk_data[448];
	uint16_t pixels_chunk_length;

	if (pixels_length == 0) {
		memset(&pixels_chunk_data, 0, sizeof(bool) * 448);

		ret = oled_128x64_v2_write_pixels_low_level(oled_128x64_v2, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (pixels_chunk_offset < pixels_length) {
			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 448) {
				pixels_chunk_length = 448;
			}

			memcpy(pixels_chunk_data, &pixels[pixels_chunk_offset], sizeof(bool) * pixels_chunk_length);
			memset(&pixels_chunk_data[pixels_chunk_length], 0, sizeof(bool) * (448 - pixels_chunk_length));

			ret = oled_128x64_v2_write_pixels_low_level(oled_128x64_v2, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				break;
			}

			pixels_chunk_offset += 448;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int oled_128x64_v2_read_pixels(OLED128x64V2 *oled_128x64_v2, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, bool *ret_pixels, uint16_t *ret_pixels_length) {
	DevicePrivate *device_p = oled_128x64_v2->p;
	int ret = 0;
	uint16_t pixels_length = 0;
	uint16_t pixels_chunk_offset;
	bool pixels_chunk_data[480];
	bool pixels_out_of_sync;
	uint16_t pixels_chunk_length;

	*ret_pixels_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = oled_128x64_v2_read_pixels_low_level(oled_128x64_v2, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	pixels_out_of_sync = pixels_chunk_offset != 0;

	if (!pixels_out_of_sync) {
		pixels_chunk_length = pixels_length - pixels_chunk_offset;

		if (pixels_chunk_length > 480) {
			pixels_chunk_length = 480;
		}

		memcpy(ret_pixels, pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
		*ret_pixels_length = pixels_chunk_length;

		while (*ret_pixels_length < pixels_length) {
			ret = oled_128x64_v2_read_pixels_low_level(oled_128x64_v2, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			pixels_out_of_sync = pixels_chunk_offset != *ret_pixels_length;

			if (pixels_out_of_sync) {
				break;
			}

			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 480) {
				pixels_chunk_length = 480;
			}

			memcpy(&ret_pixels[*ret_pixels_length], pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
			*ret_pixels_length += pixels_chunk_length;
		}
	}

	if (pixels_out_of_sync) {
		*ret_pixels_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (pixels_chunk_offset + 480 < pixels_length) {
			ret = oled_128x64_v2_read_pixels_low_level(oled_128x64_v2, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

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
