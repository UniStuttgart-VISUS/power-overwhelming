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

#include "bricklet_joystick.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Position_CallbackFunction)(int16_t x, int16_t y, void *user_data);

typedef void (*AnalogValue_CallbackFunction)(uint16_t x, uint16_t y, void *user_data);

typedef void (*PositionReached_CallbackFunction)(int16_t x, int16_t y, void *user_data);

typedef void (*AnalogValueReached_CallbackFunction)(uint16_t x, uint16_t y, void *user_data);

typedef void (*Pressed_CallbackFunction)(void *user_data);

typedef void (*Released_CallbackFunction)(void *user_data);

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
} ATTRIBUTE_PACKED GetPosition_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED GetPosition_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsPressed_Request;

typedef struct {
	PacketHeader header;
	uint8_t pressed;
} ATTRIBUTE_PACKED IsPressed_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValue_Request;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED GetAnalogValue_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Calibrate_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetPositionCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetPositionCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAnalogValueCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAnalogValueCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
} ATTRIBUTE_PACKED SetPositionCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetPositionCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	int16_t min_x;
	int16_t max_x;
	int16_t min_y;
	int16_t max_y;
} ATTRIBUTE_PACKED GetPositionCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_x;
	uint16_t max_x;
	uint16_t min_y;
	uint16_t max_y;
} ATTRIBUTE_PACKED SetAnalogValueCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min_x;
	uint16_t max_x;
	uint16_t min_y;
	uint16_t max_y;
} ATTRIBUTE_PACKED GetAnalogValueCallbackThreshold_Response;

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
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED Position_Callback;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED AnalogValue_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
} ATTRIBUTE_PACKED PositionReached_Callback;

typedef struct {
	PacketHeader header;
	uint16_t x;
	uint16_t y;
} ATTRIBUTE_PACKED AnalogValueReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Pressed_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Released_Callback;

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

static void joystick_callback_wrapper_position(DevicePrivate *device_p, Packet *packet) {
	Position_CallbackFunction callback_function;
	void *user_data;
	Position_Callback *callback;

	if (packet->header.length != sizeof(Position_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Position_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_POSITION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_POSITION];
	callback = (Position_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_analog_value(DevicePrivate *device_p, Packet *packet) {
	AnalogValue_CallbackFunction callback_function;
	void *user_data;
	AnalogValue_Callback *callback;

	if (packet->header.length != sizeof(AnalogValue_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValue_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_ANALOG_VALUE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_ANALOG_VALUE];
	callback = (AnalogValue_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_uint16_from(callback->x);
	callback->y = leconvert_uint16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_position_reached(DevicePrivate *device_p, Packet *packet) {
	PositionReached_CallbackFunction callback_function;
	void *user_data;
	PositionReached_Callback *callback;

	if (packet->header.length != sizeof(PositionReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (PositionReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_POSITION_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_POSITION_REACHED];
	callback = (PositionReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_analog_value_reached(DevicePrivate *device_p, Packet *packet) {
	AnalogValueReached_CallbackFunction callback_function;
	void *user_data;
	AnalogValueReached_Callback *callback;

	if (packet->header.length != sizeof(AnalogValueReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AnalogValueReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED];
	callback = (AnalogValueReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_uint16_from(callback->x);
	callback->y = leconvert_uint16_from(callback->y);

	callback_function(callback->x, callback->y, user_data);
}

static void joystick_callback_wrapper_pressed(DevicePrivate *device_p, Packet *packet) {
	Pressed_CallbackFunction callback_function;
	void *user_data;
	Pressed_Callback *callback;

	if (packet->header.length != sizeof(Pressed_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Pressed_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_PRESSED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_PRESSED];
	callback = (Pressed_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void joystick_callback_wrapper_released(DevicePrivate *device_p, Packet *packet) {
	Released_CallbackFunction callback_function;
	void *user_data;
	Released_Callback *callback;

	if (packet->header.length != sizeof(Released_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Released_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_RELEASED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + JOYSTICK_CALLBACK_RELEASED];
	callback = (Released_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void joystick_create(Joystick *joystick, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(joystick, uid, ipcon_p, 2, 0, 0, JOYSTICK_DEVICE_IDENTIFIER);

	device_p = joystick->p;

	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_IS_PRESSED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_CALIBRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[JOYSTICK_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[JOYSTICK_CALLBACK_POSITION] = joystick_callback_wrapper_position;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_ANALOG_VALUE] = joystick_callback_wrapper_analog_value;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_POSITION_REACHED] = joystick_callback_wrapper_position_reached;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_ANALOG_VALUE_REACHED] = joystick_callback_wrapper_analog_value_reached;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_PRESSED] = joystick_callback_wrapper_pressed;
	device_p->callback_wrappers[JOYSTICK_CALLBACK_RELEASED] = joystick_callback_wrapper_released;

	ipcon_add_device(ipcon_p, device_p);
}

void joystick_destroy(Joystick *joystick) {
	device_release(joystick->p);
}

int joystick_get_response_expected(Joystick *joystick, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(joystick->p, function_id, ret_response_expected);
}

int joystick_set_response_expected(Joystick *joystick, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(joystick->p, function_id, response_expected);
}

int joystick_set_response_expected_all(Joystick *joystick, bool response_expected) {
	return device_set_response_expected_all(joystick->p, response_expected);
}

void joystick_register_callback(Joystick *joystick, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(joystick->p, callback_id, function, user_data);
}

int joystick_get_api_version(Joystick *joystick, uint8_t ret_api_version[3]) {
	return device_get_api_version(joystick->p, ret_api_version);
}

int joystick_get_position(Joystick *joystick, int16_t *ret_x, int16_t *ret_y) {
	DevicePrivate *device_p = joystick->p;
	GetPosition_Request request;
	GetPosition_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);

	return ret;
}

int joystick_is_pressed(Joystick *joystick, bool *ret_pressed) {
	DevicePrivate *device_p = joystick->p;
	IsPressed_Request request;
	IsPressed_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_IS_PRESSED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_pressed = response.pressed != 0;

	return ret;
}

int joystick_get_analog_value(Joystick *joystick, uint16_t *ret_x, uint16_t *ret_y) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValue_Request request;
	GetAnalogValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_uint16_from(response.x);
	*ret_y = leconvert_uint16_from(response.y);

	return ret;
}

int joystick_calibrate(Joystick *joystick) {
	DevicePrivate *device_p = joystick->p;
	Calibrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_CALIBRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_set_position_callback_period(Joystick *joystick, uint32_t period) {
	DevicePrivate *device_p = joystick->p;
	SetPositionCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_get_position_callback_period(Joystick *joystick, uint32_t *ret_period) {
	DevicePrivate *device_p = joystick->p;
	GetPositionCallbackPeriod_Request request;
	GetPositionCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_set_analog_value_callback_period(Joystick *joystick, uint32_t period) {
	DevicePrivate *device_p = joystick->p;
	SetAnalogValueCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_get_analog_value_callback_period(Joystick *joystick, uint32_t *ret_period) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValueCallbackPeriod_Request request;
	GetAnalogValueCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_set_position_callback_threshold(Joystick *joystick, char option, int16_t min_x, int16_t max_x, int16_t min_y, int16_t max_y) {
	DevicePrivate *device_p = joystick->p;
	SetPositionCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_int16_to(min_x);
	request.max_x = leconvert_int16_to(max_x);
	request.min_y = leconvert_int16_to(min_y);
	request.max_y = leconvert_int16_to(max_y);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_get_position_callback_threshold(Joystick *joystick, char *ret_option, int16_t *ret_min_x, int16_t *ret_max_x, int16_t *ret_min_y, int16_t *ret_max_y) {
	DevicePrivate *device_p = joystick->p;
	GetPositionCallbackThreshold_Request request;
	GetPositionCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_POSITION_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min_x = leconvert_int16_from(response.min_x);
	*ret_max_x = leconvert_int16_from(response.max_x);
	*ret_min_y = leconvert_int16_from(response.min_y);
	*ret_max_y = leconvert_int16_from(response.max_y);

	return ret;
}

int joystick_set_analog_value_callback_threshold(Joystick *joystick, char option, uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y) {
	DevicePrivate *device_p = joystick->p;
	SetAnalogValueCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min_x = leconvert_uint16_to(min_x);
	request.max_x = leconvert_uint16_to(max_x);
	request.min_y = leconvert_uint16_to(min_y);
	request.max_y = leconvert_uint16_to(max_y);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_get_analog_value_callback_threshold(Joystick *joystick, char *ret_option, uint16_t *ret_min_x, uint16_t *ret_max_x, uint16_t *ret_min_y, uint16_t *ret_max_y) {
	DevicePrivate *device_p = joystick->p;
	GetAnalogValueCallbackThreshold_Request request;
	GetAnalogValueCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_ANALOG_VALUE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min_x = leconvert_uint16_from(response.min_x);
	*ret_max_x = leconvert_uint16_from(response.max_x);
	*ret_min_y = leconvert_uint16_from(response.min_y);
	*ret_max_y = leconvert_uint16_from(response.max_y);

	return ret;
}

int joystick_set_debounce_period(Joystick *joystick, uint32_t debounce) {
	DevicePrivate *device_p = joystick->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int joystick_get_debounce_period(Joystick *joystick, uint32_t *ret_debounce) {
	DevicePrivate *device_p = joystick->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

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

int joystick_get_identity(Joystick *joystick, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = joystick->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), JOYSTICK_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
