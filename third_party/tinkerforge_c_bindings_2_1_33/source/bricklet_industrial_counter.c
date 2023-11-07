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

#include "bricklet_industrial_counter.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*AllCounter_CallbackFunction)(int64_t counter[4], void *user_data);

typedef void (*AllSignalData_CallbackFunction)(uint16_t duty_cycle[4], uint64_t period[4], uint32_t frequency[4], bool value[4], void *user_data);

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
	uint8_t channel;
} ATTRIBUTE_PACKED GetCounter_Request;

typedef struct {
	PacketHeader header;
	int64_t counter;
} ATTRIBUTE_PACKED GetCounter_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllCounter_Request;

typedef struct {
	PacketHeader header;
	int64_t counter[4];
} ATTRIBUTE_PACKED GetAllCounter_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	int64_t counter;
} ATTRIBUTE_PACKED SetCounter_Request;

typedef struct {
	PacketHeader header;
	int64_t counter[4];
} ATTRIBUTE_PACKED SetAllCounter_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetSignalData_Request;

typedef struct {
	PacketHeader header;
	uint16_t duty_cycle;
	uint64_t period;
	uint32_t frequency;
	uint8_t value;
} ATTRIBUTE_PACKED GetSignalData_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllSignalData_Request;

typedef struct {
	PacketHeader header;
	uint16_t duty_cycle[4];
	uint64_t period[4];
	uint32_t frequency[4];
	uint8_t value[1];
} ATTRIBUTE_PACKED GetAllSignalData_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t active;
} ATTRIBUTE_PACKED SetCounterActive_Request;

typedef struct {
	PacketHeader header;
	uint8_t active[1];
} ATTRIBUTE_PACKED SetAllCounterActive_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetCounterActive_Request;

typedef struct {
	PacketHeader header;
	uint8_t active;
} ATTRIBUTE_PACKED GetCounterActive_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllCounterActive_Request;

typedef struct {
	PacketHeader header;
	uint8_t active[1];
} ATTRIBUTE_PACKED GetAllCounterActive_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
	uint8_t count_edge;
	uint8_t count_direction;
	uint8_t duty_cycle_prescaler;
	uint8_t frequency_integration_time;
} ATTRIBUTE_PACKED SetCounterConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetCounterConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t count_edge;
	uint8_t count_direction;
	uint8_t duty_cycle_prescaler;
	uint8_t frequency_integration_time;
} ATTRIBUTE_PACKED GetCounterConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllCounterCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllCounterCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllCounterCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllSignalDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllSignalDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllSignalDataCallbackConfiguration_Response;

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
	int64_t counter[4];
} ATTRIBUTE_PACKED AllCounter_Callback;

typedef struct {
	PacketHeader header;
	uint16_t duty_cycle[4];
	uint64_t period[4];
	uint32_t frequency[4];
	uint8_t value[1];
} ATTRIBUTE_PACKED AllSignalData_Callback;

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

static void industrial_counter_callback_wrapper_all_counter(DevicePrivate *device_p, Packet *packet) {
	AllCounter_CallbackFunction callback_function;
	void *user_data;
	AllCounter_Callback *callback;
	int i;
	int64_t aligned_counter[4];


	if (packet->header.length != sizeof(AllCounter_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllCounter_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER];
	callback = (AllCounter_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 4; i++) aligned_counter[i] = leconvert_int64_from(callback->counter[i]);

	callback_function(aligned_counter, user_data);
}

static void industrial_counter_callback_wrapper_all_signal_data(DevicePrivate *device_p, Packet *packet) {
	AllSignalData_CallbackFunction callback_function;
	void *user_data;
	AllSignalData_Callback *callback;
	int i;
	bool unpacked_value[4];
	uint16_t aligned_duty_cycle[4];
	uint64_t aligned_period[4];
	uint32_t aligned_frequency[4];


	if (packet->header.length != sizeof(AllSignalData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllSignalData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_COUNTER_CALLBACK_ALL_SIGNAL_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + INDUSTRIAL_COUNTER_CALLBACK_ALL_SIGNAL_DATA];
	callback = (AllSignalData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 4; i++) aligned_duty_cycle[i] = leconvert_uint16_from(callback->duty_cycle[i]);
	for (i = 0; i < 4; i++) aligned_period[i] = leconvert_uint64_from(callback->period[i]);
	for (i = 0; i < 4; i++) aligned_frequency[i] = leconvert_uint32_from(callback->frequency[i]);
	for (i = 0; i < 4; i++) unpacked_value[i] = (callback->value[i / 8] & (1 << (i % 8))) != 0;

	callback_function(aligned_duty_cycle, aligned_period, aligned_frequency, unpacked_value, user_data);
}

void industrial_counter_create(IndustrialCounter *industrial_counter, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(industrial_counter, uid, ipcon_p, 2, 0, 0, INDUSTRIAL_COUNTER_DEVICE_IDENTIFIER);

	device_p = industrial_counter->p;

	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_SIGNAL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_ACTIVE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_ACTIVE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_ACTIVE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_ACTIVE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_CHANNEL_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_CHANNEL_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[INDUSTRIAL_COUNTER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER] = industrial_counter_callback_wrapper_all_counter;
	device_p->callback_wrappers[INDUSTRIAL_COUNTER_CALLBACK_ALL_SIGNAL_DATA] = industrial_counter_callback_wrapper_all_signal_data;

	ipcon_add_device(ipcon_p, device_p);
}

void industrial_counter_destroy(IndustrialCounter *industrial_counter) {
	device_release(industrial_counter->p);
}

int industrial_counter_get_response_expected(IndustrialCounter *industrial_counter, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(industrial_counter->p, function_id, ret_response_expected);
}

int industrial_counter_set_response_expected(IndustrialCounter *industrial_counter, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(industrial_counter->p, function_id, response_expected);
}

int industrial_counter_set_response_expected_all(IndustrialCounter *industrial_counter, bool response_expected) {
	return device_set_response_expected_all(industrial_counter->p, response_expected);
}

void industrial_counter_register_callback(IndustrialCounter *industrial_counter, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(industrial_counter->p, callback_id, function, user_data);
}

int industrial_counter_get_api_version(IndustrialCounter *industrial_counter, uint8_t ret_api_version[3]) {
	return device_get_api_version(industrial_counter->p, ret_api_version);
}

int industrial_counter_get_counter(IndustrialCounter *industrial_counter, uint8_t channel, int64_t *ret_counter) {
	DevicePrivate *device_p = industrial_counter->p;
	GetCounter_Request request;
	GetCounter_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_counter = leconvert_int64_from(response.counter);

	return ret;
}

int industrial_counter_get_all_counter(IndustrialCounter *industrial_counter, int64_t ret_counter[4]) {
	DevicePrivate *device_p = industrial_counter->p;
	GetAllCounter_Request request;
	GetAllCounter_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) ret_counter[i] = leconvert_int64_from(response.counter[i]);

	return ret;
}

int industrial_counter_set_counter(IndustrialCounter *industrial_counter, uint8_t channel, int64_t counter) {
	DevicePrivate *device_p = industrial_counter->p;
	SetCounter_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.counter = leconvert_int64_to(counter);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_set_all_counter(IndustrialCounter *industrial_counter, int64_t counter[4]) {
	DevicePrivate *device_p = industrial_counter->p;
	SetAllCounter_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) request.counter[i] = leconvert_int64_to(counter[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_signal_data(IndustrialCounter *industrial_counter, uint8_t channel, uint16_t *ret_duty_cycle, uint64_t *ret_period, uint32_t *ret_frequency, bool *ret_value) {
	DevicePrivate *device_p = industrial_counter->p;
	GetSignalData_Request request;
	GetSignalData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_SIGNAL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_duty_cycle = leconvert_uint16_from(response.duty_cycle);
	*ret_period = leconvert_uint64_from(response.period);
	*ret_frequency = leconvert_uint32_from(response.frequency);
	*ret_value = response.value != 0;

	return ret;
}

int industrial_counter_get_all_signal_data(IndustrialCounter *industrial_counter, uint16_t ret_duty_cycle[4], uint64_t ret_period[4], uint32_t ret_frequency[4], bool ret_value[4]) {
	DevicePrivate *device_p = industrial_counter->p;
	GetAllSignalData_Request request;
	GetAllSignalData_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) ret_duty_cycle[i] = leconvert_uint16_from(response.duty_cycle[i]);
	for (i = 0; i < 4; i++) ret_period[i] = leconvert_uint64_from(response.period[i]);
	for (i = 0; i < 4; i++) ret_frequency[i] = leconvert_uint32_from(response.frequency[i]);
	for (i = 0; i < 4; i++) ret_value[i] = (response.value[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int industrial_counter_set_counter_active(IndustrialCounter *industrial_counter, uint8_t channel, bool active) {
	DevicePrivate *device_p = industrial_counter->p;
	SetCounterActive_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_ACTIVE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.active = active ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_set_all_counter_active(IndustrialCounter *industrial_counter, bool active[4]) {
	DevicePrivate *device_p = industrial_counter->p;
	SetAllCounterActive_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_ACTIVE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memset(request.active, 0, 1); for (i = 0; i < 4; i++) request.active[i / 8] |= (active[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_counter_active(IndustrialCounter *industrial_counter, uint8_t channel, bool *ret_active) {
	DevicePrivate *device_p = industrial_counter->p;
	GetCounterActive_Request request;
	GetCounterActive_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_ACTIVE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_active = response.active != 0;

	return ret;
}

int industrial_counter_get_all_counter_active(IndustrialCounter *industrial_counter, bool ret_active[4]) {
	DevicePrivate *device_p = industrial_counter->p;
	GetAllCounterActive_Request request;
	GetAllCounterActive_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_ACTIVE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 4; i++) ret_active[i] = (response.active[i / 8] & (1 << (i % 8))) != 0;

	return ret;
}

int industrial_counter_set_counter_configuration(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t count_edge, uint8_t count_direction, uint8_t duty_cycle_prescaler, uint8_t frequency_integration_time) {
	DevicePrivate *device_p = industrial_counter->p;
	SetCounterConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.count_edge = count_edge;
	request.count_direction = count_direction;
	request.duty_cycle_prescaler = duty_cycle_prescaler;
	request.frequency_integration_time = frequency_integration_time;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_counter_configuration(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t *ret_count_edge, uint8_t *ret_count_direction, uint8_t *ret_duty_cycle_prescaler, uint8_t *ret_frequency_integration_time) {
	DevicePrivate *device_p = industrial_counter->p;
	GetCounterConfiguration_Request request;
	GetCounterConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_count_edge = response.count_edge;
	*ret_count_direction = response.count_direction;
	*ret_duty_cycle_prescaler = response.duty_cycle_prescaler;
	*ret_frequency_integration_time = response.frequency_integration_time;

	return ret;
}

int industrial_counter_set_all_counter_callback_configuration(IndustrialCounter *industrial_counter, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = industrial_counter->p;
	SetAllCounterCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_all_counter_callback_configuration(IndustrialCounter *industrial_counter, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = industrial_counter->p;
	GetAllCounterCallbackConfiguration_Request request;
	GetAllCounterCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int industrial_counter_set_all_signal_data_callback_configuration(IndustrialCounter *industrial_counter, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = industrial_counter->p;
	SetAllSignalDataCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_all_signal_data_callback_configuration(IndustrialCounter *industrial_counter, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = industrial_counter->p;
	GetAllSignalDataCallbackConfiguration_Request request;
	GetAllSignalDataCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int industrial_counter_set_channel_led_config(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t config) {
	DevicePrivate *device_p = industrial_counter->p;
	SetChannelLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_CHANNEL_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;
	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_channel_led_config(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t *ret_config) {
	DevicePrivate *device_p = industrial_counter->p;
	GetChannelLEDConfig_Request request;
	GetChannelLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_CHANNEL_LED_CONFIG, device_p->ipcon_p, device_p);

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

int industrial_counter_get_spitfp_error_count(IndustrialCounter *industrial_counter, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = industrial_counter->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int industrial_counter_set_bootloader_mode(IndustrialCounter *industrial_counter, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = industrial_counter->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int industrial_counter_get_bootloader_mode(IndustrialCounter *industrial_counter, uint8_t *ret_mode) {
	DevicePrivate *device_p = industrial_counter->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int industrial_counter_set_write_firmware_pointer(IndustrialCounter *industrial_counter, uint32_t pointer) {
	DevicePrivate *device_p = industrial_counter->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_write_firmware(IndustrialCounter *industrial_counter, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = industrial_counter->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int industrial_counter_set_status_led_config(IndustrialCounter *industrial_counter, uint8_t config) {
	DevicePrivate *device_p = industrial_counter->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_get_status_led_config(IndustrialCounter *industrial_counter, uint8_t *ret_config) {
	DevicePrivate *device_p = industrial_counter->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int industrial_counter_get_chip_temperature(IndustrialCounter *industrial_counter, int16_t *ret_temperature) {
	DevicePrivate *device_p = industrial_counter->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int industrial_counter_reset(IndustrialCounter *industrial_counter) {
	DevicePrivate *device_p = industrial_counter->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_write_uid(IndustrialCounter *industrial_counter, uint32_t uid) {
	DevicePrivate *device_p = industrial_counter->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int industrial_counter_read_uid(IndustrialCounter *industrial_counter, uint32_t *ret_uid) {
	DevicePrivate *device_p = industrial_counter->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int industrial_counter_get_identity(IndustrialCounter *industrial_counter, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = industrial_counter->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), INDUSTRIAL_COUNTER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
