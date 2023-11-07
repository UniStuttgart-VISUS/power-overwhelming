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

#include "bricklet_rgb_led.h"

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
	uint8_t r;
	uint8_t g;
	uint8_t b;
} ATTRIBUTE_PACKED SetRGBValue_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRGBValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t r;
	uint8_t g;
	uint8_t b;
} ATTRIBUTE_PACKED GetRGBValue_Response;

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

void rgb_led_create(RGBLED *rgb_led, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(rgb_led, uid, ipcon_p, 2, 0, 0, RGB_LED_DEVICE_IDENTIFIER);

	device_p = rgb_led->p;

	device_p->response_expected[RGB_LED_FUNCTION_SET_RGB_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RGB_LED_FUNCTION_GET_RGB_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RGB_LED_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	ipcon_add_device(ipcon_p, device_p);
}

void rgb_led_destroy(RGBLED *rgb_led) {
	device_release(rgb_led->p);
}

int rgb_led_get_response_expected(RGBLED *rgb_led, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rgb_led->p, function_id, ret_response_expected);
}

int rgb_led_set_response_expected(RGBLED *rgb_led, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rgb_led->p, function_id, response_expected);
}

int rgb_led_set_response_expected_all(RGBLED *rgb_led, bool response_expected) {
	return device_set_response_expected_all(rgb_led->p, response_expected);
}


int rgb_led_get_api_version(RGBLED *rgb_led, uint8_t ret_api_version[3]) {
	return device_get_api_version(rgb_led->p, ret_api_version);
}

int rgb_led_set_rgb_value(RGBLED *rgb_led, uint8_t r, uint8_t g, uint8_t b) {
	DevicePrivate *device_p = rgb_led->p;
	SetRGBValue_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_FUNCTION_SET_RGB_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.r = r;
	request.g = g;
	request.b = b;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rgb_led_get_rgb_value(RGBLED *rgb_led, uint8_t *ret_r, uint8_t *ret_g, uint8_t *ret_b) {
	DevicePrivate *device_p = rgb_led->p;
	GetRGBValue_Request request;
	GetRGBValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_FUNCTION_GET_RGB_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_r = response.r;
	*ret_g = response.g;
	*ret_b = response.b;

	return ret;
}

int rgb_led_get_identity(RGBLED *rgb_led, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rgb_led->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RGB_LED_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
