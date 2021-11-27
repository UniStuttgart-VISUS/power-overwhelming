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

#include "bricklet_industrial_digital_in_4_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Value_CallbackFunction)(uint8_t channel, bool changed, bool value, void *user_data);

typedef void (*AllValue_CallbackFunction)(bool changed[4], bool value[4], void *user_data);

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
} ATTRIBUTE_PACKED GetValue_Request;

typedef struct {
	PacketHeader header;
	uint8_t value[1];
} ATTRIBUTE_PACKED GetValue_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetValueCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllValueCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllValueCallbackConfiguration_Response;

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
	uint8_t config;
} ATTRIBUTE_PACKED SetChannelLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetChannelLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetChannelLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t changed;
	uint8_t value;
} ATTRIBUTE_PACKED Value_Callback;

typedef struct {
	PacketHeader header;
	uint8_t changed[1];
	uint8_t value[1];
} ATTRIBUTE_PACKED AllValue_Callback;

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

static void industrial_digital_in_4_v2_callback_wrapper_value(DevicePrivate *device_p, Packet *packet) {
	Value_CallbackFunction callback_function;
	void *user_data;
	Value_Callback *callback;
	bool unpacked_changed;
	bool unpacked_value;

	if (packet->header.length != sizeof(Value_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Value_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_VALUE];
	callback = (Value_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_changed = callback->changed != 0;
	unpacked_value = callback->value != 0;

	callback_function(callback->channel, unpacked_changed, unpacked_value, user_data);
}

static void industrial_digital_in_4_v2_callback_wrapper_all_value(DevicePrivate *device_p, Packet *packet) {
	AllValue_CallbackFunction callback_function;
	void *user_data;
	AllValue_Callback *callback;
	int i;
	bool unpacked_changed[4];
	bool unpacked_value[4];

	if (packet->header.length != sizeof(AllValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_ALL_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_ALL_VALUE];
	callback = (AllValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	for (i = 0; i < 4; i++) unpacked_changed[i] = (callback->changed[i / 8] & (1 << (i % 8))) != 0;
	for (i = 0; i < 4; i++) unpacked_value[i] = (callback->value[i / 8] & (1 << (i % 8))) != 0;

	callback_function(unpacked_changed, unpacked_value, user_data);
}

void industrial_digital_in_4_v2_create(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(industrial_digital_in_4_v2, uid, ipcon_p, 2, 0, 0, INDUSTRIAL_DIGITAL_IN_4_V2_DEVICE_IDENTIFIER);

	device_p = industrial_digital_in_4_v2->p;

	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_ALL_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_ALL_VALUE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_EDGE_COUNT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_EDGE_COUNT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_CHANNEL_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_CHANNEL_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_VALUE] = industrial_digital_in_4_v2_callback_wrapper_value;
	device_p->callback_wrappers[INDUSTRIAL_DIGITAL_IN_4_V2_CALLBACK_ALL_VALUE] = industrial_digital_in_4_v2_callback_wrapper_all_value;

	ipcon_add_device(ipcon_p, device_p);
}

void industrial_digital_in_4_v2_destroy(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2) {
	device_release(industrial_digital_in_4_v2->p);
}

int industrial_digital_in_4_v2_get_response_expected(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_digital_in_4_v2->p, function_id, ret_response_expected);
}

int industrial_digital_in_4_v2_set_response_expected(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_digital_in_4_v2->p, function_id, response_expected);
}

int industrial_digital_in_4_v2_set_response_expected_all(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, bool response_expected) {
	return device_set_response_expected_all(industrial_digital_in_4_v2->p, response_expected);
}

void industrial_digital_in_4_v2_register_callback(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(industrial_digital_in_4_v2->p, callback_id, function, user_data);
}

int industrial_digital_in_4_v2_get_api_version(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_digital_in_4_v2->p, ret_api_version);
}

int industrial_digital_in_4_v2_get_value(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, bool ret_value[4]) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetValue_Request request;
	GetValue_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) ret_value[i] = (response.value[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int industrial_digital_in_4_v2_set_value_callback_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetValueCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_get_value_callback_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetValueCallbackConfiguration_Request request;
	GetValueCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_all_value_callback_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetAllValueCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_ALL_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_get_all_value_callback_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetAllValueCallbackConfiguration_Request request;
	GetAllValueCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_ALL_VALUE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_get_edge_count(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetEdgeCount_Request request;
	GetEdgeCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_edge_count_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetEdgeCountConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_EDGE_COUNT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_get_edge_count_configuration(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetEdgeCountConfiguration_Request request;
	GetEdgeCountConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_EDGE_COUNT_CONFIGURATION, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_channel_led_config(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint8_t config) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetChannelLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_CHANNEL_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_get_channel_led_config(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t channel, uint8_t *ret_config) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetChannelLEDConfig_Request request;
	GetChannelLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_CHANNEL_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int industrial_digital_in_4_v2_get_spitfp_error_count(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_bootloader_mode(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_get_bootloader_mode(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_write_firmware_pointer(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t pointer) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_write_firmware(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_set_status_led_config(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t config) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_get_status_led_config(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_get_chip_temperature(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_reset(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_write_uid(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t uid) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_v2_read_uid(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int industrial_digital_in_4_v2_get_identity(IndustrialDigitalIn4V2 *industrial_digital_in_4_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_digital_in_4_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
