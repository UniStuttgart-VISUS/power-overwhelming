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

#include "bricklet_co2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*CO2Concentration_CallbackFunction)(uint16_t co2_concentration, void *user_data);

typedef void (*CO2ConcentrationReached_CallbackFunction)(uint16_t co2_concentration, void *user_data);

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
} ATTRIBUTE_PACKED GetCO2Concentration_Request;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED GetCO2Concentration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetCO2ConcentrationCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetCO2ConcentrationCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetCO2ConcentrationCallbackThreshold_Response;

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
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED CO2Concentration_Callback;

typedef struct {
	PacketHeader header;
	uint16_t co2_concentration;
} ATTRIBUTE_PACKED CO2ConcentrationReached_Callback;

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

static void co2_callback_wrapper_co2_concentration(DevicePrivate *device_p, Packet *packet) {
	CO2Concentration_CallbackFunction callback_function;
	void *user_data;
	CO2Concentration_Callback *callback;

	if (packet->header.length != sizeof(CO2Concentration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CO2Concentration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_CALLBACK_CO2_CONCENTRATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_CALLBACK_CO2_CONCENTRATION];
	callback = (CO2Concentration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);

	callback_function(callback->co2_concentration, user_data);
}

static void co2_callback_wrapper_co2_concentration_reached(DevicePrivate *device_p, Packet *packet) {
	CO2ConcentrationReached_CallbackFunction callback_function;
	void *user_data;
	CO2ConcentrationReached_Callback *callback;

	if (packet->header.length != sizeof(CO2ConcentrationReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CO2ConcentrationReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + CO2_CALLBACK_CO2_CONCENTRATION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + CO2_CALLBACK_CO2_CONCENTRATION_REACHED];
	callback = (CO2ConcentrationReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->co2_concentration = leconvert_uint16_from(callback->co2_concentration);

	callback_function(callback->co2_concentration, user_data);
}

void co2_create(CO2 *co2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(co2, uid, ipcon_p, 2, 0, 0, CO2_DEVICE_IDENTIFIER);

	device_p = co2->p;

	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[CO2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[CO2_CALLBACK_CO2_CONCENTRATION] = co2_callback_wrapper_co2_concentration;
	device_p->callback_wrappers[CO2_CALLBACK_CO2_CONCENTRATION_REACHED] = co2_callback_wrapper_co2_concentration_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void co2_destroy(CO2 *co2) {
	device_release(co2->p);
}

int co2_get_response_expected(CO2 *co2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(co2->p, function_id, ret_response_expected);
}

int co2_set_response_expected(CO2 *co2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(co2->p, function_id, response_expected);
}

int co2_set_response_expected_all(CO2 *co2, bool response_expected) {
	return device_set_response_expected_all(co2->p, response_expected);
}

void co2_register_callback(CO2 *co2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(co2->p, callback_id, function, user_data);
}

int co2_get_api_version(CO2 *co2, uint8_t ret_api_version[3]) {
	return device_get_api_version(co2->p, ret_api_version);
}

int co2_get_co2_concentration(CO2 *co2, uint16_t *ret_co2_concentration) {
	DevicePrivate *device_p = co2->p;
	GetCO2Concentration_Request request;
	GetCO2Concentration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_co2_concentration = leconvert_uint16_from(response.co2_concentration);

	return ret;
}

int co2_set_co2_concentration_callback_period(CO2 *co2, uint32_t period) {
	DevicePrivate *device_p = co2->p;
	SetCO2ConcentrationCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_get_co2_concentration_callback_period(CO2 *co2, uint32_t *ret_period) {
	DevicePrivate *device_p = co2->p;
	GetCO2ConcentrationCallbackPeriod_Request request;
	GetCO2ConcentrationCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int co2_set_co2_concentration_callback_threshold(CO2 *co2, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = co2->p;
	SetCO2ConcentrationCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_CO2_CONCENTRATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_get_co2_concentration_callback_threshold(CO2 *co2, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = co2->p;
	GetCO2ConcentrationCallbackThreshold_Request request;
	GetCO2ConcentrationCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_CO2_CONCENTRATION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int co2_set_debounce_period(CO2 *co2, uint32_t debounce) {
	DevicePrivate *device_p = co2->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int co2_get_debounce_period(CO2 *co2, uint32_t *ret_debounce) {
	DevicePrivate *device_p = co2->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int co2_get_identity(CO2 *co2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = co2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), CO2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
