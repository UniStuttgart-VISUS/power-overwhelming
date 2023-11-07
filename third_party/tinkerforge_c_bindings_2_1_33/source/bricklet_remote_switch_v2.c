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

#include "bricklet_remote_switch_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*SwitchingDone_CallbackFunction)(void *user_data);

typedef void (*RemoteStatusA_CallbackFunction)(uint8_t house_code, uint8_t receiver_code, uint8_t switch_to, uint16_t repeats, void *user_data);

typedef void (*RemoteStatusB_CallbackFunction)(uint32_t address, uint8_t unit, uint8_t switch_to, uint8_t dim_value, uint16_t repeats, void *user_data);

typedef void (*RemoteStatusC_CallbackFunction)(char system_code, uint8_t device_code, uint8_t switch_to, uint16_t repeats, void *user_data);

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
	uint8_t remote_type;
	uint16_t minimum_repeats;
	uint8_t callback_enabled;
} ATTRIBUTE_PACKED SetRemoteConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRemoteConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t remote_type;
	uint16_t minimum_repeats;
	uint8_t callback_enabled;
} ATTRIBUTE_PACKED GetRemoteConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRemoteStatusA_Request;

typedef struct {
	PacketHeader header;
	uint8_t house_code;
	uint8_t receiver_code;
	uint8_t switch_to;
	uint16_t repeats;
} ATTRIBUTE_PACKED GetRemoteStatusA_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRemoteStatusB_Request;

typedef struct {
	PacketHeader header;
	uint32_t address;
	uint8_t unit;
	uint8_t switch_to;
	uint8_t dim_value;
	uint16_t repeats;
} ATTRIBUTE_PACKED GetRemoteStatusB_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRemoteStatusC_Request;

typedef struct {
	PacketHeader header;
	char system_code;
	uint8_t device_code;
	uint8_t switch_to;
	uint16_t repeats;
} ATTRIBUTE_PACKED GetRemoteStatusC_Response;

typedef struct {
	PacketHeader header;
	uint8_t house_code;
	uint8_t receiver_code;
	uint8_t switch_to;
	uint16_t repeats;
} ATTRIBUTE_PACKED RemoteStatusA_Callback;

typedef struct {
	PacketHeader header;
	uint32_t address;
	uint8_t unit;
	uint8_t switch_to;
	uint8_t dim_value;
	uint16_t repeats;
} ATTRIBUTE_PACKED RemoteStatusB_Callback;

typedef struct {
	PacketHeader header;
	char system_code;
	uint8_t device_code;
	uint8_t switch_to;
	uint16_t repeats;
} ATTRIBUTE_PACKED RemoteStatusC_Callback;

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

static void remote_switch_v2_callback_wrapper_switching_done(DevicePrivate *device_p, Packet *packet) {
	SwitchingDone_CallbackFunction callback_function;
	void *user_data;
	SwitchingDone_Callback *callback;

	if (packet->header.length != sizeof(SwitchingDone_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (SwitchingDone_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_SWITCHING_DONE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_SWITCHING_DONE];
	callback = (SwitchingDone_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void remote_switch_v2_callback_wrapper_remote_status_a(DevicePrivate *device_p, Packet *packet) {
	RemoteStatusA_CallbackFunction callback_function;
	void *user_data;
	RemoteStatusA_Callback *callback;

	if (packet->header.length != sizeof(RemoteStatusA_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (RemoteStatusA_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A];
	callback = (RemoteStatusA_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->repeats = leconvert_uint16_from(callback->repeats);

	callback_function(callback->house_code, callback->receiver_code, callback->switch_to, callback->repeats, user_data);
}

static void remote_switch_v2_callback_wrapper_remote_status_b(DevicePrivate *device_p, Packet *packet) {
	RemoteStatusB_CallbackFunction callback_function;
	void *user_data;
	RemoteStatusB_Callback *callback;

	if (packet->header.length != sizeof(RemoteStatusB_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (RemoteStatusB_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B];
	callback = (RemoteStatusB_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->address = leconvert_uint32_from(callback->address);
	callback->repeats = leconvert_uint16_from(callback->repeats);

	callback_function(callback->address, callback->unit, callback->switch_to, callback->dim_value, callback->repeats, user_data);
}

static void remote_switch_v2_callback_wrapper_remote_status_c(DevicePrivate *device_p, Packet *packet) {
	RemoteStatusC_CallbackFunction callback_function;
	void *user_data;
	RemoteStatusC_Callback *callback;

	if (packet->header.length != sizeof(RemoteStatusC_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (RemoteStatusC_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C];
	callback = (RemoteStatusC_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->repeats = leconvert_uint16_from(callback->repeats);

	callback_function(callback->system_code, callback->device_code, callback->switch_to, callback->repeats, user_data);
}

void remote_switch_v2_create(RemoteSwitchV2 *remote_switch_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(remote_switch_v2, uid, ipcon_p, 2, 0, 0, REMOTE_SWITCH_V2_DEVICE_IDENTIFIER);

	device_p = remote_switch_v2->p;

	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_SWITCHING_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SET_REPEATS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_REPEATS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_A] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_B] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_DIM_SOCKET_B] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_C] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SET_REMOTE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_A] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_B] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_C] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REMOTE_SWITCH_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[REMOTE_SWITCH_V2_CALLBACK_SWITCHING_DONE] = remote_switch_v2_callback_wrapper_switching_done;
	device_p->callback_wrappers[REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A] = remote_switch_v2_callback_wrapper_remote_status_a;
	device_p->callback_wrappers[REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B] = remote_switch_v2_callback_wrapper_remote_status_b;
	device_p->callback_wrappers[REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C] = remote_switch_v2_callback_wrapper_remote_status_c;

	ipcon_add_device(ipcon_p, device_p);
}

void remote_switch_v2_destroy(RemoteSwitchV2 *remote_switch_v2) {
	device_release(remote_switch_v2->p);
}

int remote_switch_v2_get_response_expected(RemoteSwitchV2 *remote_switch_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(remote_switch_v2->p, function_id, ret_response_expected);
}

int remote_switch_v2_set_response_expected(RemoteSwitchV2 *remote_switch_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(remote_switch_v2->p, function_id, response_expected);
}

int remote_switch_v2_set_response_expected_all(RemoteSwitchV2 *remote_switch_v2, bool response_expected) {
	return device_set_response_expected_all(remote_switch_v2->p, response_expected);
}

void remote_switch_v2_register_callback(RemoteSwitchV2 *remote_switch_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(remote_switch_v2->p, callback_id, function, user_data);
}

int remote_switch_v2_get_api_version(RemoteSwitchV2 *remote_switch_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(remote_switch_v2->p, ret_api_version);
}

int remote_switch_v2_get_switching_state(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_state) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetSwitchingState_Request request;
	GetSwitchingState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_SWITCHING_STATE, device_p->ipcon_p, device_p);

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

int remote_switch_v2_set_repeats(RemoteSwitchV2 *remote_switch_v2, uint8_t repeats) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SetRepeats_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SET_REPEATS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.repeats = repeats;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_get_repeats(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_repeats) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetRepeats_Request request;
	GetRepeats_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_REPEATS, device_p->ipcon_p, device_p);

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

int remote_switch_v2_switch_socket_a(RemoteSwitchV2 *remote_switch_v2, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SwitchSocketA_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_A, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.house_code = house_code;
	request.receiver_code = receiver_code;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_switch_socket_b(RemoteSwitchV2 *remote_switch_v2, uint32_t address, uint8_t unit, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SwitchSocketB_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_B, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = leconvert_uint32_to(address);
	request.unit = unit;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_dim_socket_b(RemoteSwitchV2 *remote_switch_v2, uint32_t address, uint8_t unit, uint8_t dim_value) {
	DevicePrivate *device_p = remote_switch_v2->p;
	DimSocketB_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_DIM_SOCKET_B, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = leconvert_uint32_to(address);
	request.unit = unit;
	request.dim_value = dim_value;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_switch_socket_c(RemoteSwitchV2 *remote_switch_v2, char system_code, uint8_t device_code, uint8_t switch_to) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SwitchSocketC_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_C, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.system_code = system_code;
	request.device_code = device_code;
	request.switch_to = switch_to;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_set_remote_configuration(RemoteSwitchV2 *remote_switch_v2, uint8_t remote_type, uint16_t minimum_repeats, bool callback_enabled) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SetRemoteConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SET_REMOTE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.remote_type = remote_type;
	request.minimum_repeats = leconvert_uint16_to(minimum_repeats);
	request.callback_enabled = callback_enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_get_remote_configuration(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_remote_type, uint16_t *ret_minimum_repeats, bool *ret_callback_enabled) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetRemoteConfiguration_Request request;
	GetRemoteConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_remote_type = response.remote_type;
	*ret_minimum_repeats = leconvert_uint16_from(response.minimum_repeats);
	*ret_callback_enabled = response.callback_enabled != 0;

	return ret;
}

int remote_switch_v2_get_remote_status_a(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_house_code, uint8_t *ret_receiver_code, uint8_t *ret_switch_to, uint16_t *ret_repeats) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetRemoteStatusA_Request request;
	GetRemoteStatusA_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_A, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_house_code = response.house_code;
	*ret_receiver_code = response.receiver_code;
	*ret_switch_to = response.switch_to;
	*ret_repeats = leconvert_uint16_from(response.repeats);

	return ret;
}

int remote_switch_v2_get_remote_status_b(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_address, uint8_t *ret_unit, uint8_t *ret_switch_to, uint8_t *ret_dim_value, uint16_t *ret_repeats) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetRemoteStatusB_Request request;
	GetRemoteStatusB_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_B, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = leconvert_uint32_from(response.address);
	*ret_unit = response.unit;
	*ret_switch_to = response.switch_to;
	*ret_dim_value = response.dim_value;
	*ret_repeats = leconvert_uint16_from(response.repeats);

	return ret;
}

int remote_switch_v2_get_remote_status_c(RemoteSwitchV2 *remote_switch_v2, char *ret_system_code, uint8_t *ret_device_code, uint8_t *ret_switch_to, uint16_t *ret_repeats) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetRemoteStatusC_Request request;
	GetRemoteStatusC_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_C, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_system_code = response.system_code;
	*ret_device_code = response.device_code;
	*ret_switch_to = response.switch_to;
	*ret_repeats = leconvert_uint16_from(response.repeats);

	return ret;
}

int remote_switch_v2_get_spitfp_error_count(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int remote_switch_v2_set_bootloader_mode(RemoteSwitchV2 *remote_switch_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int remote_switch_v2_get_bootloader_mode(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int remote_switch_v2_set_write_firmware_pointer(RemoteSwitchV2 *remote_switch_v2, uint32_t pointer) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_write_firmware(RemoteSwitchV2 *remote_switch_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = remote_switch_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int remote_switch_v2_set_status_led_config(RemoteSwitchV2 *remote_switch_v2, uint8_t config) {
	DevicePrivate *device_p = remote_switch_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_get_status_led_config(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int remote_switch_v2_get_chip_temperature(RemoteSwitchV2 *remote_switch_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int remote_switch_v2_reset(RemoteSwitchV2 *remote_switch_v2) {
	DevicePrivate *device_p = remote_switch_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_write_uid(RemoteSwitchV2 *remote_switch_v2, uint32_t uid) {
	DevicePrivate *device_p = remote_switch_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int remote_switch_v2_read_uid(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = remote_switch_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int remote_switch_v2_get_identity(RemoteSwitchV2 *remote_switch_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = remote_switch_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REMOTE_SWITCH_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
