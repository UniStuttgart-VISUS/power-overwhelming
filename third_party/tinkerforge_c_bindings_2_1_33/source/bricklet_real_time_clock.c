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

#include "bricklet_real_time_clock.h"

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
} ATTRIBUTE_PACKED SetDateTimeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDateTimeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetDateTimeCallbackPeriod_Response;

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

static void real_time_clock_callback_wrapper_date_time(DevicePrivate *device_p, Packet *packet) {
	DateTime_CallbackFunction callback_function;
	void *user_data;
	DateTime_Callback *callback;

	if (packet->header.length != sizeof(DateTime_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (DateTime_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_CALLBACK_DATE_TIME];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_CALLBACK_DATE_TIME];
	callback = (DateTime_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->year = leconvert_uint16_from(callback->year);
	callback->timestamp = leconvert_int64_from(callback->timestamp);

	callback_function(callback->year, callback->month, callback->day, callback->hour, callback->minute, callback->second, callback->centisecond, callback->weekday, callback->timestamp, user_data);
}

static void real_time_clock_callback_wrapper_alarm(DevicePrivate *device_p, Packet *packet) {
	Alarm_CallbackFunction callback_function;
	void *user_data;
	Alarm_Callback *callback;

	if (packet->header.length != sizeof(Alarm_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Alarm_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_CALLBACK_ALARM];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + REAL_TIME_CLOCK_CALLBACK_ALARM];
	callback = (Alarm_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->year = leconvert_uint16_from(callback->year);
	callback->timestamp = leconvert_int64_from(callback->timestamp);

	callback_function(callback->year, callback->month, callback->day, callback->hour, callback->minute, callback->second, callback->centisecond, callback->weekday, callback->timestamp, user_data);
}

void real_time_clock_create(RealTimeClock *real_time_clock, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(real_time_clock, uid, ipcon_p, 2, 0, 1, REAL_TIME_CLOCK_DEVICE_IDENTIFIER);

	device_p = real_time_clock->p;

	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_OFFSET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_OFFSET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_SET_ALARM] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_ALARM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[REAL_TIME_CLOCK_CALLBACK_DATE_TIME] = real_time_clock_callback_wrapper_date_time;
	device_p->callback_wrappers[REAL_TIME_CLOCK_CALLBACK_ALARM] = real_time_clock_callback_wrapper_alarm;

	ipcon_add_device(ipcon_p, device_p);
}

void real_time_clock_destroy(RealTimeClock *real_time_clock) {
	device_release(real_time_clock->p);
}

int real_time_clock_get_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(real_time_clock->p, function_id, ret_response_expected);
}

int real_time_clock_set_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(real_time_clock->p, function_id, response_expected);
}

int real_time_clock_set_response_expected_all(RealTimeClock *real_time_clock, bool response_expected) {
	return device_set_response_expected_all(real_time_clock->p, response_expected);
}

void real_time_clock_register_callback(RealTimeClock *real_time_clock, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(real_time_clock->p, callback_id, function, user_data);
}

int real_time_clock_get_api_version(RealTimeClock *real_time_clock, uint8_t ret_api_version[3]) {
	return device_get_api_version(real_time_clock->p, ret_api_version);
}

int real_time_clock_set_date_time(RealTimeClock *real_time_clock, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday) {
	DevicePrivate *device_p = real_time_clock->p;
	SetDateTime_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME, device_p->ipcon_p, device_p);

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

int real_time_clock_get_date_time(RealTimeClock *real_time_clock, uint16_t *ret_year, uint8_t *ret_month, uint8_t *ret_day, uint8_t *ret_hour, uint8_t *ret_minute, uint8_t *ret_second, uint8_t *ret_centisecond, uint8_t *ret_weekday) {
	DevicePrivate *device_p = real_time_clock->p;
	GetDateTime_Request request;
	GetDateTime_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME, device_p->ipcon_p, device_p);

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

	return ret;
}

int real_time_clock_get_timestamp(RealTimeClock *real_time_clock, int64_t *ret_timestamp) {
	DevicePrivate *device_p = real_time_clock->p;
	GetTimestamp_Request request;
	GetTimestamp_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP, device_p->ipcon_p, device_p);

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

int real_time_clock_set_offset(RealTimeClock *real_time_clock, int8_t offset) {
	DevicePrivate *device_p = real_time_clock->p;
	SetOffset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_OFFSET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_get_offset(RealTimeClock *real_time_clock, int8_t *ret_offset) {
	DevicePrivate *device_p = real_time_clock->p;
	GetOffset_Request request;
	GetOffset_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_OFFSET, device_p->ipcon_p, device_p);

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

int real_time_clock_set_date_time_callback_period(RealTimeClock *real_time_clock, uint32_t period) {
	DevicePrivate *device_p = real_time_clock->p;
	SetDateTimeCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int real_time_clock_get_date_time_callback_period(RealTimeClock *real_time_clock, uint32_t *ret_period) {
	DevicePrivate *device_p = real_time_clock->p;
	GetDateTimeCallbackPeriod_Request request;
	GetDateTimeCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int real_time_clock_set_alarm(RealTimeClock *real_time_clock, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second, int8_t weekday, int32_t interval) {
	DevicePrivate *device_p = real_time_clock->p;
	SetAlarm_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_SET_ALARM, device_p->ipcon_p, device_p);

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

int real_time_clock_get_alarm(RealTimeClock *real_time_clock, int8_t *ret_month, int8_t *ret_day, int8_t *ret_hour, int8_t *ret_minute, int8_t *ret_second, int8_t *ret_weekday, int32_t *ret_interval) {
	DevicePrivate *device_p = real_time_clock->p;
	GetAlarm_Request request;
	GetAlarm_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_ALARM, device_p->ipcon_p, device_p);

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

int real_time_clock_get_identity(RealTimeClock *real_time_clock, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = real_time_clock->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
