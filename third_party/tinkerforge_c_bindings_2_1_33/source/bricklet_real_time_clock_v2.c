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

#include "bricklet_real_time_clock_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*DateTime_CallbackFunction)(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday, int64_t timestamp, void *user_data);

typedef void (*Alarm_CallbackFunction)(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday, int64_t timestamp, void *user_data);

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
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
} ATTRIBUTE_PACKED SetDateTime_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDateTime_Request;

typedef struct {
	PacketHeader header;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
	int64_t timestamp;
} ATTRIBUTE_PACKED GetDateTime_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTimestamp_Request;

typedef struct {
	PacketHeader header;
	int64_t timestamp;
} ATTRIBUTE_PACKED GetTimestamp_Response;

typedef struct {
	PacketHeader header;
	int8_t offset;
} ATTRIBUTE_PACKED SetOffset_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOffset_Request;

typedef struct {
	PacketHeader header;
	int8_t offset;
} ATTRIBUTE_PACKED GetOffset_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetDateTimeCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDateTimeCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetDateTimeCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
	int8_t second;
	int8_t weekday;
	int32_t interval;
} ATTRIBUTE_PACKED SetAlarm_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAlarm_Request;

typedef struct {
	PacketHeader header;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minute;
	int8_t second;
	int8_t weekday;
	int32_t interval;
} ATTRIBUTE_PACKED GetAlarm_Response;

typedef struct {
	PacketHeader header;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
	int64_t timestamp;
} ATTRIBUTE_PACKED DateTime_Callback;

typedef struct {
	PacketHeader header;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t centisecond;
	uint8_t weekday;
	int64_t timestamp;
} ATTRIBUTE_PACKED Alarm_Callback;

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

static void real_time_clock_v2_callback_wrapper_date_time(DevicePrivate *device_p, Packet *packet) {
	DateTime_CallbackFunction callback_function;
	void *user_data;
	DateTime_Callback *callback;

	if (packet->header.length != sizeof(DateTime_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (DateTime_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_V2_CALLBACK_DATE_TIME];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_V2_CALLBACK_DATE_TIME];
	callback = (DateTime_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->year = leconvert_uint16_from(callback->year);
	callback->timestamp = leconvert_int64_from(callback->timestamp);

	callback_function(callback->year, callback->month, callback->day, callback->hour, callback->minute, callback->second, callback->centisecond, callback->weekday, callback->timestamp, user_data);
}

static void real_time_clock_v2_callback_wrapper_alarm(DevicePrivate *device_p, Packet *packet) {
	Alarm_CallbackFunction callback_function;
	void *user_data;
	Alarm_Callback *callback;

	if (packet->header.length != sizeof(Alarm_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Alarm_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_V2_CALLBACK_ALARM];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_V2_CALLBACK_ALARM];
	callback = (Alarm_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->year = leconvert_uint16_from(callback->year);
	callback->timestamp = leconvert_int64_from(callback->timestamp);

	callback_function(callback->year, callback->month, callback->day, callback->hour, callback->minute, callback->second, callback->centisecond, callback->weekday, callback->timestamp, user_data);
}

void real_time_clock_v2_create(RealTimeClockV2 *real_time_clock_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(real_time_clock_v2, uid, ipcon_p, 2, 0, 0, REAL_TIME_CLOCK_V2_DEVICE_IDENTIFIER);

	device_p = real_time_clock_v2->p;

	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_TIMESTAMP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_OFFSET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_DATE_TIME_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_DATE_TIME_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_ALARM] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_ALARM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[REAL_TIME_CLOCK_V2_CALLBACK_DATE_TIME] = real_time_clock_v2_callback_wrapper_date_time;
	device_p->callback_wrappers[REAL_TIME_CLOCK_V2_CALLBACK_ALARM] = real_time_clock_v2_callback_wrapper_alarm;

	ipcon_add_device(ipcon_p, device_p);
}

void real_time_clock_v2_destroy(RealTimeClockV2 *real_time_clock_v2) {
	device_release(real_time_clock_v2->p);
}

int real_time_clock_v2_get_response_expected(RealTimeClockV2 *real_time_clock_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(real_time_clock_v2->p, function_id, ret_response_expected);
}

int real_time_clock_v2_set_response_expected(RealTimeClockV2 *real_time_clock_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(real_time_clock_v2->p, function_id, response_expected);
}

int real_time_clock_v2_set_response_expected_all(RealTimeClockV2 *real_time_clock_v2, bool response_expected) {
	return device_set_response_expected_all(real_time_clock_v2->p, response_expected);
}

void real_time_clock_v2_register_callback(RealTimeClockV2 *real_time_clock_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(real_time_clock_v2->p, callback_id, function, user_data);
}

int real_time_clock_v2_get_api_version(RealTimeClockV2 *real_time_clock_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(real_time_clock_v2->p, ret_api_version);
}

int real_time_clock_v2_set_date_time(RealTimeClockV2 *real_time_clock_v2, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetDateTime_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_DATE_TIME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.year = leconvert_uint16_to(year);
	request.month = month;
	request.day = day;
	request.hour = hour;
	request.minute = minute;
	request.second = second;
	request.centisecond = centisecond;
	request.weekday = weekday;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_get_date_time(RealTimeClockV2 *real_time_clock_v2, uint16_t *ret_year, uint8_t *ret_month, uint8_t *ret_day, uint8_t *ret_hour, uint8_t *ret_minute, uint8_t *ret_second, uint8_t *ret_centisecond, uint8_t *ret_weekday, int64_t *ret_timestamp) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetDateTime_Request request;
	GetDateTime_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_DATE_TIME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_year = leconvert_uint16_from(response.year);
	*ret_month = response.month;
	*ret_day = response.day;
	*ret_hour = response.hour;
	*ret_minute = response.minute;
	*ret_second = response.second;
	*ret_centisecond = response.centisecond;
	*ret_weekday = response.weekday;
	*ret_timestamp = leconvert_int64_from(response.timestamp);

	return ret;
}

int real_time_clock_v2_get_timestamp(RealTimeClockV2 *real_time_clock_v2, int64_t *ret_timestamp) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetTimestamp_Request request;
	GetTimestamp_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_TIMESTAMP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timestamp = leconvert_int64_from(response.timestamp);

	return ret;
}

int real_time_clock_v2_set_offset(RealTimeClockV2 *real_time_clock_v2, int8_t offset) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetOffset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_get_offset(RealTimeClockV2 *real_time_clock_v2, int8_t *ret_offset) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetOffset_Request request;
	GetOffset_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_offset = response.offset;

	return ret;
}

int real_time_clock_v2_set_date_time_callback_configuration(RealTimeClockV2 *real_time_clock_v2, uint32_t period) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetDateTimeCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_DATE_TIME_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_get_date_time_callback_configuration(RealTimeClockV2 *real_time_clock_v2, uint32_t *ret_period) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetDateTimeCallbackConfiguration_Request request;
	GetDateTimeCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_DATE_TIME_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_set_alarm(RealTimeClockV2 *real_time_clock_v2, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second, int8_t weekday, int32_t interval) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetAlarm_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_ALARM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.month = month;
	request.day = day;
	request.hour = hour;
	request.minute = minute;
	request.second = second;
	request.weekday = weekday;
	request.interval = leconvert_int32_to(interval);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_get_alarm(RealTimeClockV2 *real_time_clock_v2, int8_t *ret_month, int8_t *ret_day, int8_t *ret_hour, int8_t *ret_minute, int8_t *ret_second, int8_t *ret_weekday, int32_t *ret_interval) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetAlarm_Request request;
	GetAlarm_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_ALARM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_month = response.month;
	*ret_day = response.day;
	*ret_hour = response.hour;
	*ret_minute = response.minute;
	*ret_second = response.second;
	*ret_weekday = response.weekday;
	*ret_interval = leconvert_int32_from(response.interval);

	return ret;
}

int real_time_clock_v2_get_spitfp_error_count(RealTimeClockV2 *real_time_clock_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_set_bootloader_mode(RealTimeClockV2 *real_time_clock_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_get_bootloader_mode(RealTimeClockV2 *real_time_clock_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_set_write_firmware_pointer(RealTimeClockV2 *real_time_clock_v2, uint32_t pointer) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_write_firmware(RealTimeClockV2 *real_time_clock_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_set_status_led_config(RealTimeClockV2 *real_time_clock_v2, uint8_t config) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_get_status_led_config(RealTimeClockV2 *real_time_clock_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_get_chip_temperature(RealTimeClockV2 *real_time_clock_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_reset(RealTimeClockV2 *real_time_clock_v2) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_write_uid(RealTimeClockV2 *real_time_clock_v2, uint32_t uid) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_v2_read_uid(RealTimeClockV2 *real_time_clock_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int real_time_clock_v2_get_identity(RealTimeClockV2 *real_time_clock_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = real_time_clock_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
