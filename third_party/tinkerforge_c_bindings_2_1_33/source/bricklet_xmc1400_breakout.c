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

#include "bricklet_xmc1400_breakout.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ADCValues_CallbackFunction)(uint16_t values[8], void *user_data);

typedef void (*Count_CallbackFunction)(uint32_t count, void *user_data);

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
	uint8_t port;
	uint8_t pin;
	uint8_t mode;
	uint8_t input_hysteresis;
	uint8_t output_level;
} ATTRIBUTE_PACKED SetGPIOConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t port;
	uint8_t pin;
} ATTRIBUTE_PACKED GetGPIOInput_Request;

typedef struct {
	PacketHeader header;
	uint8_t value;
} ATTRIBUTE_PACKED GetGPIOInput_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t enable;
} ATTRIBUTE_PACKED SetADCChannelConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetADCChannelConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
} ATTRIBUTE_PACKED GetADCChannelConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetADCChannelValue_Request;

typedef struct {
	PacketHeader header;
	uint16_t value;
} ATTRIBUTE_PACKED GetADCChannelValue_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetADCValues_Request;

typedef struct {
	PacketHeader header;
	uint16_t values[8];
} ATTRIBUTE_PACKED GetADCValues_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetADCValuesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetADCValuesCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetADCValuesCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t values[8];
} ATTRIBUTE_PACKED ADCValues_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED GetCount_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED SetCountCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCountCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
	char option;
	uint32_t min;
	uint32_t max;
} ATTRIBUTE_PACKED GetCountCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t count;
} ATTRIBUTE_PACKED Count_Callback;

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

static void xmc1400_breakout_callback_wrapper_adc_values(DevicePrivate *device_p, Packet *packet) {
	ADCValues_CallbackFunction callback_function;
	void *user_data;
	ADCValues_Callback *callback;
	int i;
	uint16_t aligned_values[8];


	if (packet->header.length != sizeof(ADCValues_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ADCValues_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + XMC1400_BREAKOUT_CALLBACK_ADC_VALUES];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + XMC1400_BREAKOUT_CALLBACK_ADC_VALUES];
	callback = (ADCValues_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 8; i++) aligned_values[i] = leconvert_uint16_from(callback->values[i]);

	callback_function(aligned_values, user_data);
}

static void xmc1400_breakout_callback_wrapper_count(DevicePrivate *device_p, Packet *packet) {
	Count_CallbackFunction callback_function;
	void *user_data;
	Count_Callback *callback;

	if (packet->header.length != sizeof(Count_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Count_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + XMC1400_BREAKOUT_CALLBACK_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + XMC1400_BREAKOUT_CALLBACK_COUNT];
	callback = (Count_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->count = leconvert_uint32_from(callback->count);

	callback_function(callback->count, user_data);
}

void xmc1400_breakout_create(XMC1400Breakout *xmc1400_breakout, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(xmc1400_breakout, uid, ipcon_p, 2, 0, 0, XMC1400_BREAKOUT_DEVICE_IDENTIFIER);

	device_p = xmc1400_breakout->p;

	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_GPIO_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_GPIO_INPUT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_ADC_CHANNEL_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_ADC_CHANNEL_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_ADC_CHANNEL_VALUE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_ADC_VALUES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_ADC_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_ADC_VALUES_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_COUNT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_COUNT_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[XMC1400_BREAKOUT_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[XMC1400_BREAKOUT_CALLBACK_ADC_VALUES] = xmc1400_breakout_callback_wrapper_adc_values;
	device_p->callback_wrappers[XMC1400_BREAKOUT_CALLBACK_COUNT] = xmc1400_breakout_callback_wrapper_count;

	ipcon_add_device(ipcon_p, device_p);
}

void xmc1400_breakout_destroy(XMC1400Breakout *xmc1400_breakout) {
	device_release(xmc1400_breakout->p);
}

int xmc1400_breakout_get_response_expected(XMC1400Breakout *xmc1400_breakout, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(xmc1400_breakout->p, function_id, ret_response_expected);
}

int xmc1400_breakout_set_response_expected(XMC1400Breakout *xmc1400_breakout, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(xmc1400_breakout->p, function_id, response_expected);
}

int xmc1400_breakout_set_response_expected_all(XMC1400Breakout *xmc1400_breakout, bool response_expected) {
	return device_set_response_expected_all(xmc1400_breakout->p, response_expected);
}

void xmc1400_breakout_register_callback(XMC1400Breakout *xmc1400_breakout, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(xmc1400_breakout->p, callback_id, function, user_data);
}

int xmc1400_breakout_get_api_version(XMC1400Breakout *xmc1400_breakout, uint8_t ret_api_version[3]) {
	return device_get_api_version(xmc1400_breakout->p, ret_api_version);
}

int xmc1400_breakout_set_gpio_config(XMC1400Breakout *xmc1400_breakout, uint8_t port, uint8_t pin, uint8_t mode, uint8_t input_hysteresis, bool output_level) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetGPIOConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_GPIO_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.pin = pin;
	request.mode = mode;
	request.input_hysteresis = input_hysteresis;
	request.output_level = output_level ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_get_gpio_input(XMC1400Breakout *xmc1400_breakout, uint8_t port, uint8_t pin, bool *ret_value) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetGPIOInput_Request request;
	GetGPIOInput_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_GPIO_INPUT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.pin = pin;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = response.value != 0;

	return ret;
}

int xmc1400_breakout_set_adc_channel_config(XMC1400Breakout *xmc1400_breakout, uint8_t channel, bool enable) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetADCChannelConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_ADC_CHANNEL_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.enable = enable ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_get_adc_channel_config(XMC1400Breakout *xmc1400_breakout, uint8_t channel, bool *ret_enable) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetADCChannelConfig_Request request;
	GetADCChannelConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_ADC_CHANNEL_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;

	return ret;
}

int xmc1400_breakout_get_adc_channel_value(XMC1400Breakout *xmc1400_breakout, uint8_t channel, uint16_t *ret_value) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetADCChannelValue_Request request;
	GetADCChannelValue_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_ADC_CHANNEL_VALUE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_value = leconvert_uint16_from(response.value);

	return ret;
}

int xmc1400_breakout_get_adc_values(XMC1400Breakout *xmc1400_breakout, uint16_t ret_values[8]) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetADCValues_Request request;
	GetADCValues_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_ADC_VALUES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 8; i++) ret_values[i] = leconvert_uint16_from(response.values[i]);

	return ret;
}

int xmc1400_breakout_set_adc_values_callback_configuration(XMC1400Breakout *xmc1400_breakout, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetADCValuesCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_ADC_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_get_adc_values_callback_configuration(XMC1400Breakout *xmc1400_breakout, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetADCValuesCallbackConfiguration_Request request;
	GetADCValuesCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_ADC_VALUES_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_get_count(XMC1400Breakout *xmc1400_breakout, uint32_t *ret_count) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetCount_Request request;
	GetCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count = leconvert_uint32_from(response.count);

	return ret;
}

int xmc1400_breakout_set_count_callback_configuration(XMC1400Breakout *xmc1400_breakout, uint32_t period, bool value_has_to_change, char option, uint32_t min, uint32_t max) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetCountCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_COUNT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;
	request.option = option;
	request.min = leconvert_uint32_to(min);
	request.max = leconvert_uint32_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_get_count_callback_configuration(XMC1400Breakout *xmc1400_breakout, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint32_t *ret_min, uint32_t *ret_max) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetCountCallbackConfiguration_Request request;
	GetCountCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_COUNT_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;
	*ret_option = response.option;
	*ret_min = leconvert_uint32_from(response.min);
	*ret_max = leconvert_uint32_from(response.max);

	return ret;
}

int xmc1400_breakout_get_spitfp_error_count(XMC1400Breakout *xmc1400_breakout, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_set_bootloader_mode(XMC1400Breakout *xmc1400_breakout, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_get_bootloader_mode(XMC1400Breakout *xmc1400_breakout, uint8_t *ret_mode) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_set_write_firmware_pointer(XMC1400Breakout *xmc1400_breakout, uint32_t pointer) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_write_firmware(XMC1400Breakout *xmc1400_breakout, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_set_status_led_config(XMC1400Breakout *xmc1400_breakout, uint8_t config) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_get_status_led_config(XMC1400Breakout *xmc1400_breakout, uint8_t *ret_config) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_get_chip_temperature(XMC1400Breakout *xmc1400_breakout, int16_t *ret_temperature) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_reset(XMC1400Breakout *xmc1400_breakout) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_write_uid(XMC1400Breakout *xmc1400_breakout, uint32_t uid) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int xmc1400_breakout_read_uid(XMC1400Breakout *xmc1400_breakout, uint32_t *ret_uid) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int xmc1400_breakout_get_identity(XMC1400Breakout *xmc1400_breakout, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = xmc1400_breakout->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), XMC1400_BREAKOUT_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
