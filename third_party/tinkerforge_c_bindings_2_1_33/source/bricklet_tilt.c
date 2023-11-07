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

#include "bricklet_tilt.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*TiltState_CallbackFunction)(uint8_t state, void *user_data);

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
} ATTRIBUTE_PACKED GetTiltState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED GetTiltState_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableTiltStateCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableTiltStateCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsTiltStateCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsTiltStateCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED TiltState_Callback;

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

static void tilt_callback_wrapper_tilt_state(DevicePrivate *device_p, Packet *packet) {
	TiltState_CallbackFunction callback_function;
	void *user_data;
	TiltState_Callback *callback;

	if (packet->header.length != sizeof(TiltState_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (TiltState_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + TILT_CALLBACK_TILT_STATE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + TILT_CALLBACK_TILT_STATE];
	callback = (TiltState_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->state, user_data);
}

void tilt_create(Tilt *tilt, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(tilt, uid, ipcon_p, 2, 0, 0, TILT_DEVICE_IDENTIFIER);

	device_p = tilt->p;

	device_p->response_expected[TILT_FUNCTION_GET_TILT_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TILT_FUNCTION_ENABLE_TILT_STATE_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TILT_FUNCTION_DISABLE_TILT_STATE_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[TILT_FUNCTION_IS_TILT_STATE_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[TILT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[TILT_CALLBACK_TILT_STATE] = tilt_callback_wrapper_tilt_state;

	ipcon_add_device(ipcon_p, device_p);
}

void tilt_destroy(Tilt *tilt) {
	device_release(tilt->p);
}

int tilt_get_response_expected(Tilt *tilt, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(tilt->p, function_id, ret_response_expected);
}

int tilt_set_response_expected(Tilt *tilt, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(tilt->p, function_id, response_expected);
}

int tilt_set_response_expected_all(Tilt *tilt, bool response_expected) {
	return device_set_response_expected_all(tilt->p, response_expected);
}

void tilt_register_callback(Tilt *tilt, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(tilt->p, callback_id, function, user_data);
}

int tilt_get_api_version(Tilt *tilt, uint8_t ret_api_version[3]) {
	return device_get_api_version(tilt->p, ret_api_version);
}

int tilt_get_tilt_state(Tilt *tilt, uint8_t *ret_state) {
	DevicePrivate *device_p = tilt->p;
	GetTiltState_Request request;
	GetTiltState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_GET_TILT_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_state = response.state;

	return ret;
}

int tilt_enable_tilt_state_callback(Tilt *tilt) {
	DevicePrivate *device_p = tilt->p;
	EnableTiltStateCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_ENABLE_TILT_STATE_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int tilt_disable_tilt_state_callback(Tilt *tilt) {
	DevicePrivate *device_p = tilt->p;
	DisableTiltStateCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_DISABLE_TILT_STATE_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int tilt_is_tilt_state_callback_enabled(Tilt *tilt, bool *ret_enabled) {
	DevicePrivate *device_p = tilt->p;
	IsTiltStateCallbackEnabled_Request request;
	IsTiltStateCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_IS_TILT_STATE_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

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

int tilt_get_identity(Tilt *tilt, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = tilt->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), TILT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
