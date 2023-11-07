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

#include "bricklet_gps.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Coordinates_CallbackFunction)(uint32_t latitude, char ns, uint32_t longitude, char ew, uint16_t pdop, uint16_t hdop, uint16_t vdop, uint16_t epe, void *user_data);

typedef void (*Status_CallbackFunction)(uint8_t fix, uint8_t satellites_view, uint8_t satellites_used, void *user_data);

typedef void (*Altitude_CallbackFunction)(int32_t altitude, int32_t geoidal_separation, void *user_data);

typedef void (*Motion_CallbackFunction)(uint32_t course, uint32_t speed, void *user_data);

typedef void (*DateTime_CallbackFunction)(uint32_t date, uint32_t time, void *user_data);

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
} ATTRIBUTE_PACKED GetCoordinates_Request;

typedef struct {
	PacketHeader header;
	uint32_t latitude;
	char ns;
	uint32_t longitude;
	char ew;
	uint16_t pdop;
	uint16_t hdop;
	uint16_t vdop;
	uint16_t epe;
} ATTRIBUTE_PACKED GetCoordinates_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t fix;
	uint8_t satellites_view;
	uint8_t satellites_used;
} ATTRIBUTE_PACKED GetStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitude_Request;

typedef struct {
	PacketHeader header;
	int32_t altitude;
	int32_t geoidal_separation;
} ATTRIBUTE_PACKED GetAltitude_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMotion_Request;

typedef struct {
	PacketHeader header;
	uint32_t course;
	uint32_t speed;
} ATTRIBUTE_PACKED GetMotion_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDateTime_Request;

typedef struct {
	PacketHeader header;
	uint32_t date;
	uint32_t time;
} ATTRIBUTE_PACKED GetDateTime_Response;

typedef struct {
	PacketHeader header;
	uint8_t restart_type;
} ATTRIBUTE_PACKED Restart_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetCoordinatesCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCoordinatesCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetCoordinatesCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetStatusCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatusCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetStatusCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAltitudeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAltitudeCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetMotionCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMotionCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetMotionCallbackPeriod_Response;

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
	uint32_t latitude;
	char ns;
	uint32_t longitude;
	char ew;
	uint16_t pdop;
	uint16_t hdop;
	uint16_t vdop;
	uint16_t epe;
} ATTRIBUTE_PACKED Coordinates_Callback;

typedef struct {
	PacketHeader header;
	uint8_t fix;
	uint8_t satellites_view;
	uint8_t satellites_used;
} ATTRIBUTE_PACKED Status_Callback;

typedef struct {
	PacketHeader header;
	int32_t altitude;
	int32_t geoidal_separation;
} ATTRIBUTE_PACKED Altitude_Callback;

typedef struct {
	PacketHeader header;
	uint32_t course;
	uint32_t speed;
} ATTRIBUTE_PACKED Motion_Callback;

typedef struct {
	PacketHeader header;
	uint32_t date;
	uint32_t time;
} ATTRIBUTE_PACKED DateTime_Callback;

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

static void gps_callback_wrapper_coordinates(DevicePrivate *device_p, Packet *packet) {
	Coordinates_CallbackFunction callback_function;
	void *user_data;
	Coordinates_Callback *callback;

	if (packet->header.length != sizeof(Coordinates_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Coordinates_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_COORDINATES];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_COORDINATES];
	callback = (Coordinates_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->latitude = leconvert_uint32_from(callback->latitude);
	callback->longitude = leconvert_uint32_from(callback->longitude);
	callback->pdop = leconvert_uint16_from(callback->pdop);
	callback->hdop = leconvert_uint16_from(callback->hdop);
	callback->vdop = leconvert_uint16_from(callback->vdop);
	callback->epe = leconvert_uint16_from(callback->epe);

	callback_function(callback->latitude, callback->ns, callback->longitude, callback->ew, callback->pdop, callback->hdop, callback->vdop, callback->epe, user_data);
}

static void gps_callback_wrapper_status(DevicePrivate *device_p, Packet *packet) {
	Status_CallbackFunction callback_function;
	void *user_data;
	Status_Callback *callback;

	if (packet->header.length != sizeof(Status_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Status_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_STATUS];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_STATUS];
	callback = (Status_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->fix, callback->satellites_view, callback->satellites_used, user_data);
}

static void gps_callback_wrapper_altitude(DevicePrivate *device_p, Packet *packet) {
	Altitude_CallbackFunction callback_function;
	void *user_data;
	Altitude_Callback *callback;

	if (packet->header.length != sizeof(Altitude_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Altitude_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_ALTITUDE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_ALTITUDE];
	callback = (Altitude_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->altitude = leconvert_int32_from(callback->altitude);
	callback->geoidal_separation = leconvert_int32_from(callback->geoidal_separation);

	callback_function(callback->altitude, callback->geoidal_separation, user_data);
}

static void gps_callback_wrapper_motion(DevicePrivate *device_p, Packet *packet) {
	Motion_CallbackFunction callback_function;
	void *user_data;
	Motion_Callback *callback;

	if (packet->header.length != sizeof(Motion_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Motion_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_MOTION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_MOTION];
	callback = (Motion_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->course = leconvert_uint32_from(callback->course);
	callback->speed = leconvert_uint32_from(callback->speed);

	callback_function(callback->course, callback->speed, user_data);
}

static void gps_callback_wrapper_date_time(DevicePrivate *device_p, Packet *packet) {
	DateTime_CallbackFunction callback_function;
	void *user_data;
	DateTime_Callback *callback;

	if (packet->header.length != sizeof(DateTime_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (DateTime_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_DATE_TIME];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + GPS_CALLBACK_DATE_TIME];
	callback = (DateTime_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->date = leconvert_uint32_from(callback->date);
	callback->time = leconvert_uint32_from(callback->time);

	callback_function(callback->date, callback->time, user_data);
}

void gps_create(GPS *gps, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(gps, uid, ipcon_p, 2, 0, 1, GPS_DEVICE_IDENTIFIER);

	device_p = gps->p;

	device_p->response_expected[GPS_FUNCTION_GET_COORDINATES] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_ALTITUDE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_MOTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_DATE_TIME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_RESTART] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[GPS_FUNCTION_SET_COORDINATES_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_COORDINATES_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_SET_STATUS_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_STATUS_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_SET_MOTION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_MOTION_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[GPS_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[GPS_CALLBACK_COORDINATES] = gps_callback_wrapper_coordinates;
	device_p->callback_wrappers[GPS_CALLBACK_STATUS] = gps_callback_wrapper_status;
	device_p->callback_wrappers[GPS_CALLBACK_ALTITUDE] = gps_callback_wrapper_altitude;
	device_p->callback_wrappers[GPS_CALLBACK_MOTION] = gps_callback_wrapper_motion;
	device_p->callback_wrappers[GPS_CALLBACK_DATE_TIME] = gps_callback_wrapper_date_time;

	ipcon_add_device(ipcon_p, device_p);
}

void gps_destroy(GPS *gps) {
	device_release(gps->p);
}

int gps_get_response_expected(GPS *gps, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(gps->p, function_id, ret_response_expected);
}

int gps_set_response_expected(GPS *gps, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(gps->p, function_id, response_expected);
}

int gps_set_response_expected_all(GPS *gps, bool response_expected) {
	return device_set_response_expected_all(gps->p, response_expected);
}

void gps_register_callback(GPS *gps, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(gps->p, callback_id, function, user_data);
}

int gps_get_api_version(GPS *gps, uint8_t ret_api_version[3]) {
	return device_get_api_version(gps->p, ret_api_version);
}

int gps_get_coordinates(GPS *gps, uint32_t *ret_latitude, char *ret_ns, uint32_t *ret_longitude, char *ret_ew, uint16_t *ret_pdop, uint16_t *ret_hdop, uint16_t *ret_vdop, uint16_t *ret_epe) {
	DevicePrivate *device_p = gps->p;
	GetCoordinates_Request request;
	GetCoordinates_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_COORDINATES, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_latitude = leconvert_uint32_from(response.latitude);
	*ret_ns = response.ns;
	*ret_longitude = leconvert_uint32_from(response.longitude);
	*ret_ew = response.ew;
	*ret_pdop = leconvert_uint16_from(response.pdop);
	*ret_hdop = leconvert_uint16_from(response.hdop);
	*ret_vdop = leconvert_uint16_from(response.vdop);
	*ret_epe = leconvert_uint16_from(response.epe);

	return ret;
}

int gps_get_status(GPS *gps, uint8_t *ret_fix, uint8_t *ret_satellites_view, uint8_t *ret_satellites_used) {
	DevicePrivate *device_p = gps->p;
	GetStatus_Request request;
	GetStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_fix = response.fix;
	*ret_satellites_view = response.satellites_view;
	*ret_satellites_used = response.satellites_used;

	return ret;
}

int gps_get_altitude(GPS *gps, int32_t *ret_altitude, int32_t *ret_geoidal_separation) {
	DevicePrivate *device_p = gps->p;
	GetAltitude_Request request;
	GetAltitude_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_ALTITUDE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_altitude = leconvert_int32_from(response.altitude);
	*ret_geoidal_separation = leconvert_int32_from(response.geoidal_separation);

	return ret;
}

int gps_get_motion(GPS *gps, uint32_t *ret_course, uint32_t *ret_speed) {
	DevicePrivate *device_p = gps->p;
	GetMotion_Request request;
	GetMotion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_MOTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_course = leconvert_uint32_from(response.course);
	*ret_speed = leconvert_uint32_from(response.speed);

	return ret;
}

int gps_get_date_time(GPS *gps, uint32_t *ret_date, uint32_t *ret_time) {
	DevicePrivate *device_p = gps->p;
	GetDateTime_Request request;
	GetDateTime_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_DATE_TIME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_date = leconvert_uint32_from(response.date);
	*ret_time = leconvert_uint32_from(response.time);

	return ret;
}

int gps_restart(GPS *gps, uint8_t restart_type) {
	DevicePrivate *device_p = gps->p;
	Restart_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_RESTART, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.restart_type = restart_type;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_set_coordinates_callback_period(GPS *gps, uint32_t period) {
	DevicePrivate *device_p = gps->p;
	SetCoordinatesCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_SET_COORDINATES_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_get_coordinates_callback_period(GPS *gps, uint32_t *ret_period) {
	DevicePrivate *device_p = gps->p;
	GetCoordinatesCallbackPeriod_Request request;
	GetCoordinatesCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_COORDINATES_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int gps_set_status_callback_period(GPS *gps, uint32_t period) {
	DevicePrivate *device_p = gps->p;
	SetStatusCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_SET_STATUS_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_get_status_callback_period(GPS *gps, uint32_t *ret_period) {
	DevicePrivate *device_p = gps->p;
	GetStatusCallbackPeriod_Request request;
	GetStatusCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_STATUS_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int gps_set_altitude_callback_period(GPS *gps, uint32_t period) {
	DevicePrivate *device_p = gps->p;
	SetAltitudeCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_SET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_get_altitude_callback_period(GPS *gps, uint32_t *ret_period) {
	DevicePrivate *device_p = gps->p;
	GetAltitudeCallbackPeriod_Request request;
	GetAltitudeCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_ALTITUDE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int gps_set_motion_callback_period(GPS *gps, uint32_t period) {
	DevicePrivate *device_p = gps->p;
	SetMotionCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_SET_MOTION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_get_motion_callback_period(GPS *gps, uint32_t *ret_period) {
	DevicePrivate *device_p = gps->p;
	GetMotionCallbackPeriod_Request request;
	GetMotionCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_MOTION_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int gps_set_date_time_callback_period(GPS *gps, uint32_t period) {
	DevicePrivate *device_p = gps->p;
	SetDateTimeCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int gps_get_date_time_callback_period(GPS *gps, uint32_t *ret_period) {
	DevicePrivate *device_p = gps->p;
	GetDateTimeCallbackPeriod_Request request;
	GetDateTimeCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int gps_get_identity(GPS *gps, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = gps->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), GPS_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
