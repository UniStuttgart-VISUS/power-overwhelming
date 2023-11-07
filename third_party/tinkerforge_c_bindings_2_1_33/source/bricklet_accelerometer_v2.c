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

#include "bricklet_accelerometer_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Acceleration_CallbackFunction)(int32_t x, int32_t y, int32_t z, void *user_data);

typedef void (*ContinuousAcceleration16Bit_CallbackFunction)(int16_t acceleration[30], void *user_data);

typedef void (*ContinuousAcceleration8Bit_CallbackFunction)(int8_t acceleration[60], void *user_data);

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
} ATTRIBUTE_PACKED GetAcceleration_Request;

typedef struct {
	PacketHeader header;
	int32_t x;
	int32_t y;
	int32_t z;
} ATTRIBUTE_PACKED GetAcceleration_Response;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
} ATTRIBUTE_PACKED SetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t data_rate;
	uint8_t full_scale;
} ATTRIBUTE_PACKED GetConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAccelerationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetInfoLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetInfoLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetInfoLEDConfig_Response;

typedef struct {
	PacketHeader header;
	int32_t x;
	int32_t y;
	int32_t z;
} ATTRIBUTE_PACKED Acceleration_Callback;

typedef struct {
	PacketHeader header;
	uint8_t enable_x;
	uint8_t enable_y;
	uint8_t enable_z;
	uint8_t resolution;
} ATTRIBUTE_PACKED SetContinuousAccelerationConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetContinuousAccelerationConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_x;
	uint8_t enable_y;
	uint8_t enable_z;
	uint8_t resolution;
} ATTRIBUTE_PACKED GetContinuousAccelerationConfiguration_Response;

typedef struct {
	PacketHeader header;
	int16_t acceleration[30];
} ATTRIBUTE_PACKED ContinuousAcceleration16Bit_Callback;

typedef struct {
	PacketHeader header;
	int8_t acceleration[60];
} ATTRIBUTE_PACKED ContinuousAcceleration8Bit_Callback;

typedef struct {
	PacketHeader header;
	uint8_t iir_bypass;
	uint8_t low_pass_filter;
} ATTRIBUTE_PACKED SetFilterConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFilterConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t iir_bypass;
	uint8_t low_pass_filter;
} ATTRIBUTE_PACKED GetFilterConfiguration_Response;

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

static void accelerometer_v2_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	Acceleration_CallbackFunction callback_function;
	void *user_data;
	Acceleration_Callback *callback;

	if (packet->header.length != sizeof(Acceleration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Acceleration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_ACCELERATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_ACCELERATION];
	callback = (Acceleration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int32_from(callback->x);
	callback->y = leconvert_int32_from(callback->y);
	callback->z = leconvert_int32_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void accelerometer_v2_callback_wrapper_continuous_acceleration_16_bit(DevicePrivate *device_p, Packet *packet) {
	ContinuousAcceleration16Bit_CallbackFunction callback_function;
	void *user_data;
	ContinuousAcceleration16Bit_Callback *callback;
	int i;
	int16_t aligned_acceleration[30];


	if (packet->header.length != sizeof(ContinuousAcceleration16Bit_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ContinuousAcceleration16Bit_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_16_BIT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_16_BIT];
	callback = (ContinuousAcceleration16Bit_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 30; i++) aligned_acceleration[i] = leconvert_int16_from(callback->acceleration[i]);

	callback_function(aligned_acceleration, user_data);
}

static void accelerometer_v2_callback_wrapper_continuous_acceleration_8_bit(DevicePrivate *device_p, Packet *packet) {
	ContinuousAcceleration8Bit_CallbackFunction callback_function;
	void *user_data;
	ContinuousAcceleration8Bit_Callback *callback;

	if (packet->header.length != sizeof(ContinuousAcceleration8Bit_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ContinuousAcceleration8Bit_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_8_BIT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_8_BIT];
	callback = (ContinuousAcceleration8Bit_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->acceleration, user_data);
}

void accelerometer_v2_create(AccelerometerV2 *accelerometer_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(accelerometer_v2, uid, ipcon_p, 2, 0, 1, ACCELEROMETER_V2_DEVICE_IDENTIFIER);

	device_p = accelerometer_v2->p;

	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_INFO_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_INFO_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_CONTINUOUS_ACCELERATION_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_CONTINUOUS_ACCELERATION_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_FILTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_FILTER_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ACCELEROMETER_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[ACCELEROMETER_V2_CALLBACK_ACCELERATION] = accelerometer_v2_callback_wrapper_acceleration;
	device_p->callback_wrappers[ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_16_BIT] = accelerometer_v2_callback_wrapper_continuous_acceleration_16_bit;
	device_p->callback_wrappers[ACCELEROMETER_V2_CALLBACK_CONTINUOUS_ACCELERATION_8_BIT] = accelerometer_v2_callback_wrapper_continuous_acceleration_8_bit;

	ipcon_add_device(ipcon_p, device_p);
}

void accelerometer_v2_destroy(AccelerometerV2 *accelerometer_v2) {
	device_release(accelerometer_v2->p);
}

int accelerometer_v2_get_response_expected(AccelerometerV2 *accelerometer_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(accelerometer_v2->p, function_id, ret_response_expected);
}

int accelerometer_v2_set_response_expected(AccelerometerV2 *accelerometer_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(accelerometer_v2->p, function_id, response_expected);
}

int accelerometer_v2_set_response_expected_all(AccelerometerV2 *accelerometer_v2, bool response_expected) {
	return device_set_response_expected_all(accelerometer_v2->p, response_expected);
}

void accelerometer_v2_register_callback(AccelerometerV2 *accelerometer_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(accelerometer_v2->p, callback_id, function, user_data);
}

int accelerometer_v2_get_api_version(AccelerometerV2 *accelerometer_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(accelerometer_v2->p, ret_api_version);
}

int accelerometer_v2_get_acceleration(AccelerometerV2 *accelerometer_v2, int32_t *ret_x, int32_t *ret_y, int32_t *ret_z) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetAcceleration_Request request;
	GetAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int32_from(response.x);
	*ret_y = leconvert_int32_from(response.y);
	*ret_z = leconvert_int32_from(response.z);

	return ret;
}

int accelerometer_v2_set_configuration(AccelerometerV2 *accelerometer_v2, uint8_t data_rate, uint8_t full_scale) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.data_rate = data_rate;
	request.full_scale = full_scale;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_configuration(AccelerometerV2 *accelerometer_v2, uint8_t *ret_data_rate, uint8_t *ret_full_scale) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetConfiguration_Request request;
	GetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_data_rate = response.data_rate;
	*ret_full_scale = response.full_scale;

	return ret;
}

int accelerometer_v2_set_acceleration_callback_configuration(AccelerometerV2 *accelerometer_v2, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetAccelerationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_acceleration_callback_configuration(AccelerometerV2 *accelerometer_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetAccelerationCallbackConfiguration_Request request;
	GetAccelerationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int accelerometer_v2_set_info_led_config(AccelerometerV2 *accelerometer_v2, uint8_t config) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetInfoLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_INFO_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_info_led_config(AccelerometerV2 *accelerometer_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetInfoLEDConfig_Request request;
	GetInfoLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_INFO_LED_CONFIG, device_p->ipcon_p, device_p);

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

int accelerometer_v2_set_continuous_acceleration_configuration(AccelerometerV2 *accelerometer_v2, bool enable_x, bool enable_y, bool enable_z, uint8_t resolution) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetContinuousAccelerationConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_CONTINUOUS_ACCELERATION_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_x = enable_x ? 1 : 0;
	request.enable_y = enable_y ? 1 : 0;
	request.enable_z = enable_z ? 1 : 0;
	request.resolution = resolution;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_continuous_acceleration_configuration(AccelerometerV2 *accelerometer_v2, bool *ret_enable_x, bool *ret_enable_y, bool *ret_enable_z, uint8_t *ret_resolution) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetContinuousAccelerationConfiguration_Request request;
	GetContinuousAccelerationConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_CONTINUOUS_ACCELERATION_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_x = response.enable_x != 0;
	*ret_enable_y = response.enable_y != 0;
	*ret_enable_z = response.enable_z != 0;
	*ret_resolution = response.resolution;

	return ret;
}

int accelerometer_v2_set_filter_configuration(AccelerometerV2 *accelerometer_v2, uint8_t iir_bypass, uint8_t low_pass_filter) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetFilterConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_FILTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.iir_bypass = iir_bypass;
	request.low_pass_filter = low_pass_filter;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_filter_configuration(AccelerometerV2 *accelerometer_v2, uint8_t *ret_iir_bypass, uint8_t *ret_low_pass_filter) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetFilterConfiguration_Request request;
	GetFilterConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_FILTER_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_iir_bypass = response.iir_bypass;
	*ret_low_pass_filter = response.low_pass_filter;

	return ret;
}

int accelerometer_v2_get_spitfp_error_count(AccelerometerV2 *accelerometer_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int accelerometer_v2_set_bootloader_mode(AccelerometerV2 *accelerometer_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int accelerometer_v2_get_bootloader_mode(AccelerometerV2 *accelerometer_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int accelerometer_v2_set_write_firmware_pointer(AccelerometerV2 *accelerometer_v2, uint32_t pointer) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_write_firmware(AccelerometerV2 *accelerometer_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = accelerometer_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int accelerometer_v2_set_status_led_config(AccelerometerV2 *accelerometer_v2, uint8_t config) {
	DevicePrivate *device_p = accelerometer_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_get_status_led_config(AccelerometerV2 *accelerometer_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int accelerometer_v2_get_chip_temperature(AccelerometerV2 *accelerometer_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int accelerometer_v2_reset(AccelerometerV2 *accelerometer_v2) {
	DevicePrivate *device_p = accelerometer_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_write_uid(AccelerometerV2 *accelerometer_v2, uint32_t uid) {
	DevicePrivate *device_p = accelerometer_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int accelerometer_v2_read_uid(AccelerometerV2 *accelerometer_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = accelerometer_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int accelerometer_v2_get_identity(AccelerometerV2 *accelerometer_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = accelerometer_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ACCELEROMETER_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
