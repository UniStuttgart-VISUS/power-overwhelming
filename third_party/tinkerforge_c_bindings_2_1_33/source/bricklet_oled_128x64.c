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

#include "bricklet_oled_128x64.h"

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
	uint8_t data[64];
} ATTRIBUTE_PACKED Write_Request;

typedef struct {
	PacketHeader header;
	uint8_t column_from;
	uint8_t column_to;
	uint8_t row_from;
	uint8_t row_to;
} ATTRIBUTE_PACKED NewWindow_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ClearDisplay_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t invert;
} ATTRIBUTE_PACKED SetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t contrast;
	uint8_t invert;
} ATTRIBUTE_PACKED GetDisplayConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t line;
	uint8_t position;
	char text[26];
} ATTRIBUTE_PACKED WriteLine_Request;

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

void oled_128x64_create(OLED128x64 *oled_128x64, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(oled_128x64, uid, ipcon_p, 2, 0, 0, OLED_128X64_DEVICE_IDENTIFIER);

	device_p = oled_128x64->p;

	device_p->response_expected[OLED_128X64_FUNCTION_WRITE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_NEW_WINDOW] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_CLEAR_DISPLAY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[OLED_128X64_FUNCTION_WRITE_LINE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[OLED_128X64_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	ipcon_add_device(ipcon_p, device_p);
}

void oled_128x64_destroy(OLED128x64 *oled_128x64) {
	device_release(oled_128x64->p);
}

int oled_128x64_get_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(oled_128x64->p, function_id, ret_response_expected);
}

int oled_128x64_set_response_expected(OLED128x64 *oled_128x64, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(oled_128x64->p, function_id, response_expected);
}

int oled_128x64_set_response_expected_all(OLED128x64 *oled_128x64, bool response_expected) {
	return device_set_response_expected_all(oled_128x64->p, response_expected);
}


int oled_128x64_get_api_version(OLED128x64 *oled_128x64, uint8_t ret_api_version[3]) {
	return device_get_api_version(oled_128x64->p, ret_api_version);
}

int oled_128x64_write(OLED128x64 *oled_128x64, uint8_t data[64]) {
	DevicePrivate *device_p = oled_128x64->p;
	Write_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_WRITE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_new_window(OLED128x64 *oled_128x64, uint8_t column_from, uint8_t column_to, uint8_t row_from, uint8_t row_to) {
	DevicePrivate *device_p = oled_128x64->p;
	NewWindow_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_NEW_WINDOW, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.column_from = column_from;
	request.column_to = column_to;
	request.row_from = row_from;
	request.row_to = row_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_clear_display(OLED128x64 *oled_128x64) {
	DevicePrivate *device_p = oled_128x64->p;
	ClearDisplay_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_CLEAR_DISPLAY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_set_display_configuration(OLED128x64 *oled_128x64, uint8_t contrast, bool invert) {
	DevicePrivate *device_p = oled_128x64->p;
	SetDisplayConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_SET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.contrast = contrast;
	request.invert = invert ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_get_display_configuration(OLED128x64 *oled_128x64, uint8_t *ret_contrast, bool *ret_invert) {
	DevicePrivate *device_p = oled_128x64->p;
	GetDisplayConfiguration_Request request;
	GetDisplayConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_GET_DISPLAY_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_contrast = response.contrast;
	*ret_invert = response.invert != 0;

	return ret;
}

int oled_128x64_write_line(OLED128x64 *oled_128x64, uint8_t line, uint8_t position, const char *text) {
	DevicePrivate *device_p = oled_128x64->p;
	WriteLine_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_WRITE_LINE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.line = line;
	request.position = position;
	string_copy(request.text, text, 26);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int oled_128x64_get_identity(OLED128x64 *oled_128x64, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = oled_128x64->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), OLED_128X64_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
