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

#include "bricklet_e_paper_296x128.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*DrawStatus_CallbackFunction)(uint8_t draw_status, void *user_data);

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
} ATTRIBUTE_PACKED Draw_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDrawStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t draw_status;
} ATTRIBUTE_PACKED GetDrawStatus_Response;

typedef struct {
	PacketHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[54];
} ATTRIBUTE_PACKED WriteBlackWhiteLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
} ATTRIBUTE_PACKED ReadBlackWhiteLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[58];
} ATTRIBUTE_PACKED ReadBlackWhiteLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[54];
} ATTRIBUTE_PACKED WriteColorLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
} ATTRIBUTE_PACKED ReadColorLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[58];
} ATTRIBUTE_PACKED ReadColorLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t color;
} ATTRIBUTE_PACKED FillDisplay_Request;

typedef struct {
	PacketHeader header;
	uint16_t position_x;
	uint8_t position_y;
	uint8_t font;
	uint8_t color;
	uint8_t orientation;
	char text[50];
} ATTRIBUTE_PACKED DrawText_Request;

typedef struct {
	PacketHeader header;
	uint16_t position_x_start;
	uint8_t position_y_start;
	uint16_t position_x_end;
	uint8_t position_y_end;
	uint8_t color;
} ATTRIBUTE_PACKED DrawLine_Request;

typedef struct {
	PacketHeader header;
	uint16_t position_x_start;
	uint8_t position_y_start;
	uint16_t position_x_end;
	uint8_t position_y_end;
	uint8_t fill;
	uint8_t color;
} ATTRIBUTE_PACKED DrawBox_Request;

typedef struct {
	PacketHeader header;
	uint8_t draw_status;
} ATTRIBUTE_PACKED DrawStatus_Callback;

typedef struct {
	PacketHeader header;
	uint8_t update_mode;
} ATTRIBUTE_PACKED SetUpdateMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUpdateMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t update_mode;
} ATTRIBUTE_PACKED GetUpdateMode_Response;

typedef struct {
	PacketHeader header;
	uint8_t display_type;
} ATTRIBUTE_PACKED SetDisplayType_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayType_Request;

typedef struct {
	PacketHeader header;
	uint8_t display_type;
} ATTRIBUTE_PACKED GetDisplayType_Response;

typedef struct {
	PacketHeader header;
	uint8_t display_driver;
} ATTRIBUTE_PACKED SetDisplayDriver_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayDriver_Request;

typedef struct {
	PacketHeader header;
	uint8_t display_driver;
} ATTRIBUTE_PACKED GetDisplayDriver_Response;

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

static void e_paper_296x128_callback_wrapper_draw_status(DevicePrivate *device_p, Packet *packet) {
	DrawStatus_CallbackFunction callback_function;
	void *user_data;
	DrawStatus_Callback *callback;

	if (packet->header.length != sizeof(DrawStatus_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (DrawStatus_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + E_PAPER_296X128_CALLBACK_DRAW_STATUS];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + E_PAPER_296X128_CALLBACK_DRAW_STATUS];
	callback = (DrawStatus_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->draw_status, user_data);
}

void e_paper_296x128_create(EPaper296x128 *e_paper_296x128, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(e_paper_296x128, uid, ipcon_p, 2, 0, 1, E_PAPER_296X128_DEVICE_IDENTIFIER);

	device_p = e_paper_296x128->p;

	device_p->response_expected[E_PAPER_296X128_FUNCTION_DRAW] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_DRAW_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_WRITE_BLACK_WHITE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_READ_BLACK_WHITE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_WRITE_COLOR_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_READ_COLOR_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_FILL_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_DRAW_TEXT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_DRAW_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_DRAW_BOX] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_UPDATE_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_UPDATE_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_DISPLAY_TYPE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_DISPLAY_TYPE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_DISPLAY_DRIVER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_DISPLAY_DRIVER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[E_PAPER_296X128_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[E_PAPER_296X128_CALLBACK_DRAW_STATUS] = e_paper_296x128_callback_wrapper_draw_status;

	ipcon_add_device(ipcon_p, device_p);
}

void e_paper_296x128_destroy(EPaper296x128 *e_paper_296x128) {
	device_release(e_paper_296x128->p);
}

int e_paper_296x128_get_response_expected(EPaper296x128 *e_paper_296x128, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(e_paper_296x128->p, function_id, ret_response_expected);
}

int e_paper_296x128_set_response_expected(EPaper296x128 *e_paper_296x128, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(e_paper_296x128->p, function_id, response_expected);
}

int e_paper_296x128_set_response_expected_all(EPaper296x128 *e_paper_296x128, bool response_expected) {
	return device_set_response_expected_all(e_paper_296x128->p, response_expected);
}

void e_paper_296x128_register_callback(EPaper296x128 *e_paper_296x128, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(e_paper_296x128->p, callback_id, function, user_data);
}

int e_paper_296x128_get_api_version(EPaper296x128 *e_paper_296x128, uint8_t ret_api_version[3]) {
	return device_get_api_version(e_paper_296x128->p, ret_api_version);
}

int e_paper_296x128_draw(EPaper296x128 *e_paper_296x128) {
	DevicePrivate *device_p = e_paper_296x128->p;
	Draw_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_DRAW, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_get_draw_status(EPaper296x128 *e_paper_296x128, uint8_t *ret_draw_status) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetDrawStatus_Request request;
	GetDrawStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_DRAW_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_draw_status = response.draw_status;

	return ret;
}

int e_paper_296x128_write_black_white_low_level(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, uint16_t pixels_length, uint16_t pixels_chunk_offset, bool pixels_chunk_data[432]) {
	DevicePrivate *device_p = e_paper_296x128->p;
	WriteBlackWhiteLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_WRITE_BLACK_WHITE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = leconvert_uint16_to(x_start);
	request.y_start = y_start;
	request.x_end = leconvert_uint16_to(x_end);
	request.y_end = y_end;
	request.pixels_length = leconvert_uint16_to(pixels_length);
	request.pixels_chunk_offset = leconvert_uint16_to(pixels_chunk_offset);
	memset(request.pixels_chunk_data, 0, 54); for (i = 0; i < 432; i++) request.pixels_chunk_data[i / 8] |= (pixels_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_read_black_white_low_level(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, uint16_t *ret_pixels_length, uint16_t *ret_pixels_chunk_offset, bool ret_pixels_chunk_data[464]) {
	DevicePrivate *device_p = e_paper_296x128->p;
	ReadBlackWhiteLowLevel_Request request;
	ReadBlackWhiteLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_READ_BLACK_WHITE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = leconvert_uint16_to(x_start);
	request.y_start = y_start;
	request.x_end = leconvert_uint16_to(x_end);
	request.y_end = y_end;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pixels_length = leconvert_uint16_from(response.pixels_length);
	*ret_pixels_chunk_offset = leconvert_uint16_from(response.pixels_chunk_offset);
	for (i = 0; i < 464; i++) ret_pixels_chunk_data[i] = (response.pixels_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int e_paper_296x128_write_color_low_level(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, uint16_t pixels_length, uint16_t pixels_chunk_offset, bool pixels_chunk_data[432]) {
	DevicePrivate *device_p = e_paper_296x128->p;
	WriteColorLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_WRITE_COLOR_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = leconvert_uint16_to(x_start);
	request.y_start = y_start;
	request.x_end = leconvert_uint16_to(x_end);
	request.y_end = y_end;
	request.pixels_length = leconvert_uint16_to(pixels_length);
	request.pixels_chunk_offset = leconvert_uint16_to(pixels_chunk_offset);
	memset(request.pixels_chunk_data, 0, 54); for (i = 0; i < 432; i++) request.pixels_chunk_data[i / 8] |= (pixels_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_read_color_low_level(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, uint16_t *ret_pixels_length, uint16_t *ret_pixels_chunk_offset, bool ret_pixels_chunk_data[464]) {
	DevicePrivate *device_p = e_paper_296x128->p;
	ReadColorLowLevel_Request request;
	ReadColorLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_READ_COLOR_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.x_start = leconvert_uint16_to(x_start);
	request.y_start = y_start;
	request.x_end = leconvert_uint16_to(x_end);
	request.y_end = y_end;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pixels_length = leconvert_uint16_from(response.pixels_length);
	*ret_pixels_chunk_offset = leconvert_uint16_from(response.pixels_chunk_offset);
	for (i = 0; i < 464; i++) ret_pixels_chunk_data[i] = (response.pixels_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int e_paper_296x128_fill_display(EPaper296x128 *e_paper_296x128, uint8_t color) {
	DevicePrivate *device_p = e_paper_296x128->p;
	FillDisplay_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_FILL_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.color = color;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_draw_text(EPaper296x128 *e_paper_296x128, uint16_t position_x, uint8_t position_y, uint8_t font, uint8_t color, uint8_t orientation, const char *text) {
	DevicePrivate *device_p = e_paper_296x128->p;
	DrawText_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_DRAW_TEXT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x = leconvert_uint16_to(position_x);
	request.position_y = position_y;
	request.font = font;
	request.color = color;
	request.orientation = orientation;
	string_copy(request.text, text, 50);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_draw_line(EPaper296x128 *e_paper_296x128, uint16_t position_x_start, uint8_t position_y_start, uint16_t position_x_end, uint8_t position_y_end, uint8_t color) {
	DevicePrivate *device_p = e_paper_296x128->p;
	DrawLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_DRAW_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x_start = leconvert_uint16_to(position_x_start);
	request.position_y_start = position_y_start;
	request.position_x_end = leconvert_uint16_to(position_x_end);
	request.position_y_end = position_y_end;
	request.color = color;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_draw_box(EPaper296x128 *e_paper_296x128, uint16_t position_x_start, uint8_t position_y_start, uint16_t position_x_end, uint8_t position_y_end, bool fill, uint8_t color) {
	DevicePrivate *device_p = e_paper_296x128->p;
	DrawBox_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_DRAW_BOX, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.position_x_start = leconvert_uint16_to(position_x_start);
	request.position_y_start = position_y_start;
	request.position_x_end = leconvert_uint16_to(position_x_end);
	request.position_y_end = position_y_end;
	request.fill = fill ? 1 : 0;
	request.color = color;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_set_update_mode(EPaper296x128 *e_paper_296x128, uint8_t update_mode) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetUpdateMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_UPDATE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.update_mode = update_mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_get_update_mode(EPaper296x128 *e_paper_296x128, uint8_t *ret_update_mode) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetUpdateMode_Request request;
	GetUpdateMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_UPDATE_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_update_mode = response.update_mode;

	return ret;
}

int e_paper_296x128_set_display_type(EPaper296x128 *e_paper_296x128, uint8_t display_type) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetDisplayType_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_DISPLAY_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.display_type = display_type;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_get_display_type(EPaper296x128 *e_paper_296x128, uint8_t *ret_display_type) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetDisplayType_Request request;
	GetDisplayType_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_DISPLAY_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_display_type = response.display_type;

	return ret;
}

int e_paper_296x128_set_display_driver(EPaper296x128 *e_paper_296x128, uint8_t display_driver) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetDisplayDriver_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_DISPLAY_DRIVER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.display_driver = display_driver;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_get_display_driver(EPaper296x128 *e_paper_296x128, uint8_t *ret_display_driver) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetDisplayDriver_Request request;
	GetDisplayDriver_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_DISPLAY_DRIVER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_display_driver = response.display_driver;

	return ret;
}

int e_paper_296x128_get_spitfp_error_count(EPaper296x128 *e_paper_296x128, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int e_paper_296x128_set_bootloader_mode(EPaper296x128 *e_paper_296x128, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int e_paper_296x128_get_bootloader_mode(EPaper296x128 *e_paper_296x128, uint8_t *ret_mode) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int e_paper_296x128_set_write_firmware_pointer(EPaper296x128 *e_paper_296x128, uint32_t pointer) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_write_firmware(EPaper296x128 *e_paper_296x128, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = e_paper_296x128->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int e_paper_296x128_set_status_led_config(EPaper296x128 *e_paper_296x128, uint8_t config) {
	DevicePrivate *device_p = e_paper_296x128->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_get_status_led_config(EPaper296x128 *e_paper_296x128, uint8_t *ret_config) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int e_paper_296x128_get_chip_temperature(EPaper296x128 *e_paper_296x128, int16_t *ret_temperature) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int e_paper_296x128_reset(EPaper296x128 *e_paper_296x128) {
	DevicePrivate *device_p = e_paper_296x128->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_write_uid(EPaper296x128 *e_paper_296x128, uint32_t uid) {
	DevicePrivate *device_p = e_paper_296x128->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int e_paper_296x128_read_uid(EPaper296x128 *e_paper_296x128, uint32_t *ret_uid) {
	DevicePrivate *device_p = e_paper_296x128->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int e_paper_296x128_get_identity(EPaper296x128 *e_paper_296x128, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = e_paper_296x128->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), E_PAPER_296X128_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int e_paper_296x128_write_black_white(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, bool *pixels, uint16_t pixels_length) {
	DevicePrivate *device_p = e_paper_296x128->p;
	int ret = 0;
	uint16_t pixels_chunk_offset = 0;
	bool pixels_chunk_data[432];
	uint16_t pixels_chunk_length;

	if (pixels_length == 0) {
		memset(&pixels_chunk_data, 0, sizeof(bool) * 432);

		ret = e_paper_296x128_write_black_white_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (pixels_chunk_offset < pixels_length) {
			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 432) {
				pixels_chunk_length = 432;
			}

			memcpy(pixels_chunk_data, &pixels[pixels_chunk_offset], sizeof(bool) * pixels_chunk_length);
			memset(&pixels_chunk_data[pixels_chunk_length], 0, sizeof(bool) * (432 - pixels_chunk_length));

			ret = e_paper_296x128_write_black_white_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				break;
			}

			pixels_chunk_offset += 432;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int e_paper_296x128_read_black_white(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, bool *ret_pixels, uint16_t *ret_pixels_length) {
	DevicePrivate *device_p = e_paper_296x128->p;
	int ret = 0;
	uint16_t pixels_length = 0;
	uint16_t pixels_chunk_offset;
	bool pixels_chunk_data[464];
	bool pixels_out_of_sync;
	uint16_t pixels_chunk_length;

	*ret_pixels_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = e_paper_296x128_read_black_white_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	pixels_out_of_sync = pixels_chunk_offset != 0;

	if (!pixels_out_of_sync) {
		pixels_chunk_length = pixels_length - pixels_chunk_offset;

		if (pixels_chunk_length > 464) {
			pixels_chunk_length = 464;
		}

		memcpy(ret_pixels, pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
		*ret_pixels_length = pixels_chunk_length;

		while (*ret_pixels_length < pixels_length) {
			ret = e_paper_296x128_read_black_white_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			pixels_out_of_sync = pixels_chunk_offset != *ret_pixels_length;

			if (pixels_out_of_sync) {
				break;
			}

			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 464) {
				pixels_chunk_length = 464;
			}

			memcpy(&ret_pixels[*ret_pixels_length], pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
			*ret_pixels_length += pixels_chunk_length;
		}
	}

	if (pixels_out_of_sync) {
		*ret_pixels_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (pixels_chunk_offset + 464 < pixels_length) {
			ret = e_paper_296x128_read_black_white_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

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

int e_paper_296x128_write_color(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, bool *pixels, uint16_t pixels_length) {
	DevicePrivate *device_p = e_paper_296x128->p;
	int ret = 0;
	uint16_t pixels_chunk_offset = 0;
	bool pixels_chunk_data[432];
	uint16_t pixels_chunk_length;

	if (pixels_length == 0) {
		memset(&pixels_chunk_data, 0, sizeof(bool) * 432);

		ret = e_paper_296x128_write_color_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (pixels_chunk_offset < pixels_length) {
			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 432) {
				pixels_chunk_length = 432;
			}

			memcpy(pixels_chunk_data, &pixels[pixels_chunk_offset], sizeof(bool) * pixels_chunk_length);
			memset(&pixels_chunk_data[pixels_chunk_length], 0, sizeof(bool) * (432 - pixels_chunk_length));

			ret = e_paper_296x128_write_color_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, pixels_length, pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				break;
			}

			pixels_chunk_offset += 432;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int e_paper_296x128_read_color(EPaper296x128 *e_paper_296x128, uint16_t x_start, uint8_t y_start, uint16_t x_end, uint8_t y_end, bool *ret_pixels, uint16_t *ret_pixels_length) {
	DevicePrivate *device_p = e_paper_296x128->p;
	int ret = 0;
	uint16_t pixels_length = 0;
	uint16_t pixels_chunk_offset;
	bool pixels_chunk_data[464];
	bool pixels_out_of_sync;
	uint16_t pixels_chunk_length;

	*ret_pixels_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = e_paper_296x128_read_color_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	pixels_out_of_sync = pixels_chunk_offset != 0;

	if (!pixels_out_of_sync) {
		pixels_chunk_length = pixels_length - pixels_chunk_offset;

		if (pixels_chunk_length > 464) {
			pixels_chunk_length = 464;
		}

		memcpy(ret_pixels, pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
		*ret_pixels_length = pixels_chunk_length;

		while (*ret_pixels_length < pixels_length) {
			ret = e_paper_296x128_read_color_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			pixels_out_of_sync = pixels_chunk_offset != *ret_pixels_length;

			if (pixels_out_of_sync) {
				break;
			}

			pixels_chunk_length = pixels_length - pixels_chunk_offset;

			if (pixels_chunk_length > 464) {
				pixels_chunk_length = 464;
			}

			memcpy(&ret_pixels[*ret_pixels_length], pixels_chunk_data, sizeof(bool) * pixels_chunk_length);
			*ret_pixels_length += pixels_chunk_length;
		}
	}

	if (pixels_out_of_sync) {
		*ret_pixels_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (pixels_chunk_offset + 464 < pixels_length) {
			ret = e_paper_296x128_read_color_low_level(e_paper_296x128, x_start, y_start, x_end, y_end, &pixels_length, &pixels_chunk_offset, pixels_chunk_data);

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
