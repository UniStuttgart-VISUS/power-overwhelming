/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "bricklet_io16_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*InputValue_CallbackFunction)(uint8_t channel, bool changed, bool value, void *user_data);

typedef void (*AllInputValue_CallbackFunction)(bool changed[16], bool value[16], void *user_data);

typedef void (*MonoflopDone_CallbackFunction)(uint8_t channel, bool value, void *user_data);

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
	uint8_t value[2];
} ATTRIBUTE_PACKED SetValue_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t value[2];
} ATTRIBUTE_PACKED GetValue_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t value;
} ATTRIBUTE_PACKED SetSelectedValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	char direction;
	uint8_t value;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	char direction;
	uint8_t value;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetInputValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetInputValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetInputValueCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllInputValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllInputValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllInputValueCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t value;
	uint32_t time;
} ATTRIBUTE_PACKED SetMonoflop_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetMonoflop_Request;

typedef struct {
	PacketHeader header;
	uint8_t value;
	uint32_t time;
	uint32_t time_remaining;
} ATTRIBUTE_PACKED GetMonoflop_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t reset_counter;
} ATTRIBUTE_PACKED GetEdgeCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetEdgeCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED SetEdgeCountConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetEdgeCountConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED GetEdgeCountConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t changed;
	uint8_t value;
} ATTRIBUTE_PACKED InputValue_Callback;

typedef struct {
	PacketHeader header;
	uint8_t changed[2];
	uint8_t value[2];
} ATTRIBUTE_PACKED AllInputValue_Callback;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t value;
} ATTRIBUTE_PACKED MonoflopDone_Callback;

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

static void io16_v2_callback_wrapper_input_value(DevicePrivate *device_p, Packet *packet) {
	InputValue_CallbackFunction callback_function;
	void *user_data;
	InputValue_Callback *callback;
	bool unpacked_changed;
	bool unpacked_value;

	if (packet->header.length != sizeof(InputValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (InputValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_INPUT_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_INPUT_VALUE];
	callback = (InputValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_changed = callback->changed != 0;
	unpacked_value = callback->value != 0;

	callback_function(callback->channel, unpacked_changed, unpacked_value, user_data);
}

static void io16_v2_callback_wrapper_all_input_value(DevicePrivate *device_p, Packet *packet) {
	AllInputValue_CallbackFunction callback_function;
	void *user_data;
	AllInputValue_Callback *callback;
	int i;
	bool unpacked_changed[16];
	bool unpacked_value[16];

	if (packet->header.length != sizeof(AllInputValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllInputValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_ALL_INPUT_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_ALL_INPUT_VALUE];
	callback = (AllInputValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	for (i = 0; i < 16; i++) unpacked_changed[i] = (callback->changed[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 16; i++) unpacked_value[i] = (callback->value[i / 8] & (1 << (i % 8))) != 0;

	callback_function(unpacked_changed, unpacked_value, user_data);
}

static void io16_v2_callback_wrapper_monoflop_done(DevicePrivate *device_p, Packet *packet) {
	MonoflopDone_CallbackFunction callback_function;
	void *user_data;
	MonoflopDone_Callback *callback;
	bool unpacked_value;

	if (packet->header.length != sizeof(MonoflopDone_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (MonoflopDone_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_MONOFLOP_DONE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IO16_V2_CALLBACK_MONOFLOP_DONE];
	callback = (MonoflopDone_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_value = callback->value != 0;

	callback_function(callback->channel, unpacked_value, user_data);
}

void io16_v2_create(IO16V2 *io16_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(io16_v2, uid, ipcon_p, 2, 0, 0, IO16_V2_DEVICE_IDENTIFIER);

	device_p = io16_v2->p;

	device_p->response_expected[IO16_V2_FUNCTION_SET_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_SELECTED_VALUE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_INPUT_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_INPUT_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_MONOFLOP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_EDGE_COUNT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_EDGE_COUNT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IO16_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IO16_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IO16_V2_CALLBACK_INPUT_VALUE] = io16_v2_callback_wrapper_input_value;
	device_p->callback_wrappers[IO16_V2_CALLBACK_ALL_INPUT_VALUE] = io16_v2_callback_wrapper_all_input_value;
	device_p->callback_wrappers[IO16_V2_CALLBACK_MONOFLOP_DONE] = io16_v2_callback_wrapper_monoflop_done;

	ipcon_add_device(ipcon_p, device_p);
}

void io16_v2_destroy(IO16V2 *io16_v2) {
	device_release(io16_v2->p);
}

int io16_v2_get_response_expected(IO16V2 *io16_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(io16_v2->p, function_id, ret_response_expected);
}

int io16_v2_set_response_expected(IO16V2 *io16_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(io16_v2->p, function_id, response_expected);
}

int io16_v2_set_response_expected_all(IO16V2 *io16_v2, bool response_expected) {
	return device_set_response_expected_all(io16_v2->p, response_expected);
}

void io16_v2_register_callback(IO16V2 *io16_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(io16_v2->p, callback_id, function, user_data);
}

int io16_v2_get_api_version(IO16V2 *io16_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(io16_v2->p, ret_api_version);
}

int io16_v2_set_value(IO16V2 *io16_v2, bool value[16]) {
	DevicePrivate *device_p = io16_v2->p;
	SetValue_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memset(request.value, 0, 2); for (i = 0; i < 16; i++) request.value[i / 8] |= (value[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_value(IO16V2 *io16_v2, bool ret_value[16]) {
	DevicePrivate *device_p = io16_v2->p;
	GetValue_Request request;
	GetValue_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 16; i++) ret_value[i] = (response.value[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int io16_v2_set_selected_value(IO16V2 *io16_v2, uint8_t channel, bool value) {
	DevicePrivate *device_p = io16_v2->p;
	SetSelectedValue_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_SELECTED_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.value = value ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_set_configuration(IO16V2 *io16_v2, uint8_t channel, char direction, bool value) {
	DevicePrivate *device_p = io16_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.direction = direction;
	request.value = value ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_configuration(IO16V2 *io16_v2, uint8_t channel, char *ret_direction, bool *ret_value) {
	DevicePrivate *device_p = io16_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_direction = response.direction;
	*ret_value = response.value != 0;

	return ret;
}

int io16_v2_set_input_value_callback_configuration(IO16V2 *io16_v2, uint8_t channel, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = io16_v2->p;
	SetInputValueCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_INPUT_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_input_value_callback_configuration(IO16V2 *io16_v2, uint8_t channel, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = io16_v2->p;
	GetInputValueCallbackConfiguration_Request request;
	GetInputValueCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_INPUT_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int io16_v2_set_all_input_value_callback_configuration(IO16V2 *io16_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = io16_v2->p;
	SetAllInputValueCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_all_input_value_callback_configuration(IO16V2 *io16_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = io16_v2->p;
	GetAllInputValueCallbackConfiguration_Request request;
	GetAllInputValueCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int io16_v2_set_monoflop(IO16V2 *io16_v2, uint8_t channel, bool value, uint32_t time) {
	DevicePrivate *device_p = io16_v2->p;
	SetMonoflop_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.value = value ? 1 : 0;
	request.time = leconvert_uint32_to(time);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_monoflop(IO16V2 *io16_v2, uint8_t channel, bool *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining) {
	DevicePrivate *device_p = io16_v2->p;
	GetMonoflop_Request request;
	GetMonoflop_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_MONOFLOP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = response.value != 0;
	*ret_time = leconvert_uint32_from(response.time);
	*ret_time_remaining = leconvert_uint32_from(response.time_remaining);

	return ret;
}

int io16_v2_get_edge_count(IO16V2 *io16_v2, uint8_t channel, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = io16_v2->p;
	GetEdgeCount_Request request;
	GetEdgeCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.reset_counter = reset_counter ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);

	return ret;
}

int io16_v2_set_edge_count_configuration(IO16V2 *io16_v2, uint8_t channel, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = io16_v2->p;
	SetEdgeCountConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_EDGE_COUNT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_edge_count_configuration(IO16V2 *io16_v2, uint8_t channel, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = io16_v2->p;
	GetEdgeCountConfiguration_Request request;
	GetEdgeCountConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_EDGE_COUNT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_edge_type = response.edge_type;
	*ret_debounce = response.debounce;

	return ret;
}

int io16_v2_get_spitfp_error_count(IO16V2 *io16_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = io16_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int io16_v2_set_bootloader_mode(IO16V2 *io16_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = io16_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int io16_v2_get_bootloader_mode(IO16V2 *io16_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = io16_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int io16_v2_set_write_firmware_pointer(IO16V2 *io16_v2, uint32_t pointer) {
	DevicePrivate *device_p = io16_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_write_firmware(IO16V2 *io16_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = io16_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int io16_v2_set_status_led_config(IO16V2 *io16_v2, uint8_t config) {
	DevicePrivate *device_p = io16_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_get_status_led_config(IO16V2 *io16_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = io16_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int io16_v2_get_chip_temperature(IO16V2 *io16_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = io16_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int io16_v2_reset(IO16V2 *io16_v2) {
	DevicePrivate *device_p = io16_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_write_uid(IO16V2 *io16_v2, uint32_t uid) {
	DevicePrivate *device_p = io16_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int io16_v2_read_uid(IO16V2 *io16_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = io16_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int io16_v2_get_identity(IO16V2 *io16_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = io16_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IO16_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
