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

#include "bricklet_remote_switch.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*SwitchingDone_CallbackFunction)(void *user_data);

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
	uint8_t house_code;
	uint8_t receiver_code;
	uint8_t switch_to;
} ATTRIBUTE_PACKED SwitchSocket_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSwitchingState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
} ATTRIBUTE_PACKED GetSwitchingState_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED SwitchingDone_Callback;

typedef struct {
	PacketHeader header;
	uint8_t repeats;
} ATTRIBUTE_PACKED SetRepeats_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRepeats_Request;

typedef struct {
	PacketHeader header;
	uint8_t repeats;
} ATTRIBUTE_PACKED GetRepeats_Response;

typedef struct {
	PacketHeader header;
	uint8_t house_code;
	uint8_t receiver_code;
	uint8_t switch_to;
} ATTRIBUTE_PACKED SwitchSocketA_Request;

typedef struct {
	PacketHeader header;
	uint32_t address;
	uint8_t unit;
	uint8_t switch_to;
} ATTRIBUTE_PACKED SwitchSocketB_Request;

typedef struct {
	PacketHeader header;
	uint32_t address;
	uint8_t unit;
	uint8_t dim_value;
} ATTRIBUTE_PACKED DimSocketB_Request;

typedef struct {
	PacketHeader header;
	char system_code;
	uint8_t device_code;
	uint8_t switch_to;
} ATTRIBUTE_PACKED SwitchSocketC_Request;

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

static void remote_switch_callback_wrapper_switching_done(DevicePrivate *device_p, Packet *packet) {
	SwitchingDone_CallbackFunction callback_function;
	void *user_data;
	SwitchingDone_Callback *callback;

	if (packet->header.length != sizeof(SwitchingDone_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SwitchingDone_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_CALLBACK_SWITCHING_DONE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_CALLBACK_SWITCHING_DONE];
	callback = (SwitchingDone_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void remote_switch_create(RemoteSwitch *remote_switch, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(remote_switch, uid, ipcon_p, 2, 0, 1, REMOTE_SWITCH_DEVICE_IDENTIFIER);

	device_p = remote_switch->p;

	device_p->response_expected[REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_GET_SWITCHING_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_SET_REPEATS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_GET_REPEATS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_A] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_B] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_DIM_SOCKET_B] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_C] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[REMOTE_SWITCH_CALLBACK_SWITCHING_DONE] = remote_switch_callback_wrapper_switching_done;

	ipcon_add_device(ipcon_p, device_p);
}

void remote_switch_destroy(RemoteSwitch *remote_switch) {
	device_release(remote_switch->p);
}

int remote_switch_get_response_expected(RemoteSwitch *remote_switch, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(remote_switch->p, function_id, ret_response_expected);
}

int remote_switch_set_response_expected(RemoteSwitch *remote_switch, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(remote_switch->p, function_id, response_expected);
}

int remote_switch_set_response_expected_all(RemoteSwitch *remote_switch, bool response_expected) {
	return device_set_response_expected_all(remote_switch->p, response_expected);
}

void remote_switch_register_callback(RemoteSwitch *remote_switch, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(remote_switch->p, callback_id, function, user_data);
}

int remote_switch_get_api_version(RemoteSwitch *remote_switch, uint8_t ret_api_version[3]) {
	return device_get_api_version(remote_switch->p, ret_api_version);
}

int remote_switch_switch_socket(RemoteSwitch *remote_switch, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch->p;
	SwitchSocket_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.house_code = house_code;
	request.receiver_code = receiver_code;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_get_switching_state(RemoteSwitch *remote_switch, uint8_t *ret_state) {
	DevicePrivate *device_p = remote_switch->p;
	GetSwitchingState_Request request;
	GetSwitchingState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_GET_SWITCHING_STATE, device_p->ipcon_p, device_p);

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

int remote_switch_set_repeats(RemoteSwitch *remote_switch, uint8_t repeats) {
	DevicePrivate *device_p = remote_switch->p;
	SetRepeats_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_SET_REPEATS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.repeats = repeats;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_get_repeats(RemoteSwitch *remote_switch, uint8_t *ret_repeats) {
	DevicePrivate *device_p = remote_switch->p;
	GetRepeats_Request request;
	GetRepeats_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_GET_REPEATS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_repeats = response.repeats;

	return ret;
}

int remote_switch_switch_socket_a(RemoteSwitch *remote_switch, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch->p;
	SwitchSocketA_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_A, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.house_code = house_code;
	request.receiver_code = receiver_code;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_switch_socket_b(RemoteSwitch *remote_switch, uint32_t address, uint8_t unit, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch->p;
	SwitchSocketB_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_B, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = leconvert_uint32_to(address);
	request.unit = unit;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_dim_socket_b(RemoteSwitch *remote_switch, uint32_t address, uint8_t unit, uint8_t dim_value) {
	DevicePrivate *device_p = remote_switch->p;
	DimSocketB_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_DIM_SOCKET_B, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = leconvert_uint32_to(address);
	request.unit = unit;
	request.dim_value = dim_value;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_switch_socket_c(RemoteSwitch *remote_switch, char system_code, uint8_t device_code, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch->p;
	SwitchSocketC_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_SWITCH_SOCKET_C, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.system_code = system_code;
	request.device_code = device_code;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_get_identity(RemoteSwitch *remote_switch, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = remote_switch->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
