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

#include "bricklet_industrial_digital_in_4.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Interrupt_CallbackFunction)(uint16_t interrupt_mask, uint16_t value_mask, void *user_data);

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
	uint16_t value_mask;
} ATTRIBUTE_PACKED GetValue_Response;

typedef struct {
	PacketHeader header;
	char group[4];
} ATTRIBUTE_PACKED SetGroup_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGroup_Request;

typedef struct {
	PacketHeader header;
	char group[4];
} ATTRIBUTE_PACKED GetGroup_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAvailableForGroup_Request;

typedef struct {
	PacketHeader header;
	uint8_t available;
} ATTRIBUTE_PACKED GetAvailableForGroup_Response;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED SetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED GetDebouncePeriod_Response;

typedef struct {
	PacketHeader header;
	uint16_t interrupt_mask;
} ATTRIBUTE_PACKED SetInterrupt_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInterrupt_Request;

typedef struct {
	PacketHeader header;
	uint16_t interrupt_mask;
} ATTRIBUTE_PACKED GetInterrupt_Response;

typedef struct {
	PacketHeader header;
	uint16_t interrupt_mask;
	uint16_t value_mask;
} ATTRIBUTE_PACKED Interrupt_Callback;

typedef struct {
	PacketHeader header;
	uint8_t pin;
	uint8_t reset_counter;
} ATTRIBUTE_PACKED GetEdgeCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetEdgeCount_Response;

typedef struct {
	PacketHeader header;
	uint16_t selection_mask;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED SetEdgeCountConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t pin;
} ATTRIBUTE_PACKED GetEdgeCountConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} ATTRIBUTE_PACKED GetEdgeCountConfig_Response;

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

static void industrial_digital_in_4_callback_wrapper_interrupt(DevicePrivate *device_p, Packet *packet) {
	Interrupt_CallbackFunction callback_function;
	void *user_data;
	Interrupt_Callback *callback;

	if (packet->header.length != sizeof(Interrupt_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Interrupt_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT];
	callback = (Interrupt_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->interrupt_mask = leconvert_uint16_from(callback->interrupt_mask);
	callback->value_mask = leconvert_uint16_from(callback->value_mask);

	callback_function(callback->interrupt_mask, callback->value_mask, user_data);
}

void industrial_digital_in_4_create(IndustrialDigitalIn4 *industrial_digital_in_4, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(industrial_digital_in_4, uid, ipcon_p, 2, 0, 1, INDUSTRIAL_DIGITAL_IN_4_DEVICE_IDENTIFIER);

	device_p = industrial_digital_in_4->p;

	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_GROUP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_GROUP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_AVAILABLE_FOR_GROUP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_INTERRUPT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[INDUSTRIAL_DIGITAL_IN_4_CALLBACK_INTERRUPT] = industrial_digital_in_4_callback_wrapper_interrupt;

	ipcon_add_device(ipcon_p, device_p);
}

void industrial_digital_in_4_destroy(IndustrialDigitalIn4 *industrial_digital_in_4) {
	device_release(industrial_digital_in_4->p);
}

int industrial_digital_in_4_get_response_expected(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_digital_in_4->p, function_id, ret_response_expected);
}

int industrial_digital_in_4_set_response_expected(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_digital_in_4->p, function_id, response_expected);
}

int industrial_digital_in_4_set_response_expected_all(IndustrialDigitalIn4 *industrial_digital_in_4, bool response_expected) {
	return device_set_response_expected_all(industrial_digital_in_4->p, response_expected);
}

void industrial_digital_in_4_register_callback(IndustrialDigitalIn4 *industrial_digital_in_4, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(industrial_digital_in_4->p, callback_id, function, user_data);
}

int industrial_digital_in_4_get_api_version(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_digital_in_4->p, ret_api_version);
}

int industrial_digital_in_4_get_value(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t *ret_value_mask) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetValue_Request request;
	GetValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value_mask = leconvert_uint16_from(response.value_mask);

	return ret;
}

int industrial_digital_in_4_set_group(IndustrialDigitalIn4 *industrial_digital_in_4, char group[4]) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	SetGroup_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.group, group, 4 * sizeof(char));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_get_group(IndustrialDigitalIn4 *industrial_digital_in_4, char ret_group[4]) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetGroup_Request request;
	GetGroup_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_group, response.group, 4 * sizeof(char));

	return ret;
}

int industrial_digital_in_4_get_available_for_group(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t *ret_available) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetAvailableForGroup_Request request;
	GetAvailableForGroup_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_AVAILABLE_FOR_GROUP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_available = response.available;

	return ret;
}

int industrial_digital_in_4_set_debounce_period(IndustrialDigitalIn4 *industrial_digital_in_4, uint32_t debounce) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_get_debounce_period(IndustrialDigitalIn4 *industrial_digital_in_4, uint32_t *ret_debounce) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_debounce = leconvert_uint32_from(response.debounce);

	return ret;
}

int industrial_digital_in_4_set_interrupt(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t interrupt_mask) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	SetInterrupt_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.interrupt_mask = leconvert_uint16_to(interrupt_mask);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_get_interrupt(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t *ret_interrupt_mask) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetInterrupt_Request request;
	GetInterrupt_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_INTERRUPT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_interrupt_mask = leconvert_uint16_from(response.interrupt_mask);

	return ret;
}

int industrial_digital_in_4_get_edge_count(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t pin, bool reset_counter, uint32_t *ret_count) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetEdgeCount_Request request;
	GetEdgeCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;
	request.reset_counter = reset_counter ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);

	return ret;
}

int industrial_digital_in_4_set_edge_count_config(IndustrialDigitalIn4 *industrial_digital_in_4, uint16_t selection_mask, uint8_t edge_type, uint8_t debounce) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	SetEdgeCountConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_SET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.selection_mask = leconvert_uint16_to(selection_mask);
	request.edge_type = edge_type;
	request.debounce = debounce;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_digital_in_4_get_edge_count_config(IndustrialDigitalIn4 *industrial_digital_in_4, uint8_t pin, uint8_t *ret_edge_type, uint8_t *ret_debounce) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetEdgeCountConfig_Request request;
	GetEdgeCountConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_EDGE_COUNT_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pin = pin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_edge_type = response.edge_type;
	*ret_debounce = response.debounce;

	return ret;
}

int industrial_digital_in_4_get_identity(IndustrialDigitalIn4 *industrial_digital_in_4, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_digital_in_4->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_DIGITAL_IN_4_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
