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

#include "bricklet_piezo_speaker_v2.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*BeepFinished_CallbackFunction)(void *user_data);

typedef void (*AlarmFinished_CallbackFunction)(void *user_data);

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
	uint16_t frequency;
	uint8_t volume;
	uint32_t duration;
} ATTRIBUTE_PACKED SetBeep_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBeep_Request;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
	uint8_t volume;
	uint32_t duration;
	uint32_t duration_remaining;
} ATTRIBUTE_PACKED GetBeep_Response;

typedef struct {
	PacketHeader header;
	uint16_t start_frequency;
	uint16_t end_frequency;
	uint16_t step_size;
	uint16_t step_delay;
	uint8_t volume;
	uint32_t duration;
} ATTRIBUTE_PACKED SetAlarm_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAlarm_Request;

typedef struct {
	PacketHeader header;
	uint16_t start_frequency;
	uint16_t end_frequency;
	uint16_t step_size;
	uint16_t step_delay;
	uint8_t volume;
	uint32_t duration;
	uint32_t duration_remaining;
	uint16_t current_frequency;
} ATTRIBUTE_PACKED GetAlarm_Response;

typedef struct {
	PacketHeader header;
	uint8_t volume;
} ATTRIBUTE_PACKED UpdateVolume_Request;

typedef struct {
	PacketHeader header;
	uint16_t frequency;
} ATTRIBUTE_PACKED UpdateFrequency_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED BeepFinished_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED AlarmFinished_Callback;

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

static void piezo_speaker_v2_callback_wrapper_beep_finished(DevicePrivate *device_p, Packet *packet) {
	BeepFinished_CallbackFunction callback_function;
	void *user_data;
	BeepFinished_Callback *callback;

	if (packet->header.length != sizeof(BeepFinished_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (BeepFinished_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PIEZO_SPEAKER_V2_CALLBACK_BEEP_FINISHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PIEZO_SPEAKER_V2_CALLBACK_BEEP_FINISHED];
	callback = (BeepFinished_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

static void piezo_speaker_v2_callback_wrapper_alarm_finished(DevicePrivate *device_p, Packet *packet) {
	AlarmFinished_CallbackFunction callback_function;
	void *user_data;
	AlarmFinished_Callback *callback;

	if (packet->header.length != sizeof(AlarmFinished_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AlarmFinished_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + PIEZO_SPEAKER_V2_CALLBACK_ALARM_FINISHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + PIEZO_SPEAKER_V2_CALLBACK_ALARM_FINISHED];
	callback = (AlarmFinished_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(user_data);
}

void piezo_speaker_v2_create(PiezoSpeakerV2 *piezo_speaker_v2, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(piezo_speaker_v2, uid, ipcon_p, 2, 0, 0, PIEZO_SPEAKER_V2_DEVICE_IDENTIFIER);

	device_p = piezo_speaker_v2->p;

	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_BEEP] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_ALARM] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[PIEZO_SPEAKER_V2_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[PIEZO_SPEAKER_V2_CALLBACK_BEEP_FINISHED] = piezo_speaker_v2_callback_wrapper_beep_finished;
	device_p->callback_wrappers[PIEZO_SPEAKER_V2_CALLBACK_ALARM_FINISHED] = piezo_speaker_v2_callback_wrapper_alarm_finished;

	ipcon_add_device(ipcon_p, device_p);
}

void piezo_speaker_v2_destroy(PiezoSpeakerV2 *piezo_speaker_v2) {
	device_release(piezo_speaker_v2->p);
}

int piezo_speaker_v2_get_response_expected(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(piezo_speaker_v2->p, function_id, ret_response_expected);
}

int piezo_speaker_v2_set_response_expected(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(piezo_speaker_v2->p, function_id, response_expected);
}

int piezo_speaker_v2_set_response_expected_all(PiezoSpeakerV2 *piezo_speaker_v2, bool response_expected) {
	return device_set_response_expected_all(piezo_speaker_v2->p, response_expected);
}

void piezo_speaker_v2_register_callback(PiezoSpeakerV2 *piezo_speaker_v2, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(piezo_speaker_v2->p, callback_id, function, user_data);
}

int piezo_speaker_v2_get_api_version(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t ret_api_version[3]) {
	return device_get_api_version(piezo_speaker_v2->p, ret_api_version);
}

int piezo_speaker_v2_set_beep(PiezoSpeakerV2 *piezo_speaker_v2, uint16_t frequency, uint8_t volume, uint32_t duration) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	SetBeep_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = leconvert_uint16_to(frequency);
	request.volume = volume;
	request.duration = leconvert_uint32_to(duration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_get_beep(PiezoSpeakerV2 *piezo_speaker_v2, uint16_t *ret_frequency, uint8_t *ret_volume, uint32_t *ret_duration, uint32_t *ret_duration_remaining) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetBeep_Request request;
	GetBeep_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_BEEP, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frequency = leconvert_uint16_from(response.frequency);
	*ret_volume = response.volume;
	*ret_duration = leconvert_uint32_from(response.duration);
	*ret_duration_remaining = leconvert_uint32_from(response.duration_remaining);

	return ret;
}

int piezo_speaker_v2_set_alarm(PiezoSpeakerV2 *piezo_speaker_v2, uint16_t start_frequency, uint16_t end_frequency, uint16_t step_size, uint16_t step_delay, uint8_t volume, uint32_t duration) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	SetAlarm_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.start_frequency = leconvert_uint16_to(start_frequency);
	request.end_frequency = leconvert_uint16_to(end_frequency);
	request.step_size = leconvert_uint16_to(step_size);
	request.step_delay = leconvert_uint16_to(step_delay);
	request.volume = volume;
	request.duration = leconvert_uint32_to(duration);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_get_alarm(PiezoSpeakerV2 *piezo_speaker_v2, uint16_t *ret_start_frequency, uint16_t *ret_end_frequency, uint16_t *ret_step_size, uint16_t *ret_step_delay, uint8_t *ret_volume, uint32_t *ret_duration, uint32_t *ret_duration_remaining, uint16_t *ret_current_frequency) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetAlarm_Request request;
	GetAlarm_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_ALARM, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_start_frequency = leconvert_uint16_from(response.start_frequency);
	*ret_end_frequency = leconvert_uint16_from(response.end_frequency);
	*ret_step_size = leconvert_uint16_from(response.step_size);
	*ret_step_delay = leconvert_uint16_from(response.step_delay);
	*ret_volume = response.volume;
	*ret_duration = leconvert_uint32_from(response.duration);
	*ret_duration_remaining = leconvert_uint32_from(response.duration_remaining);
	*ret_current_frequency = leconvert_uint16_from(response.current_frequency);

	return ret;
}

int piezo_speaker_v2_update_volume(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t volume) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	UpdateVolume_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.volume = volume;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_update_frequency(PiezoSpeakerV2 *piezo_speaker_v2, uint16_t frequency) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	UpdateFrequency_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = leconvert_uint16_to(frequency);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_get_spitfp_error_count(PiezoSpeakerV2 *piezo_speaker_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_set_bootloader_mode(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_get_bootloader_mode(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t *ret_mode) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_set_write_firmware_pointer(PiezoSpeakerV2 *piezo_speaker_v2, uint32_t pointer) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_write_firmware(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_set_status_led_config(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t config) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_get_status_led_config(PiezoSpeakerV2 *piezo_speaker_v2, uint8_t *ret_config) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_get_chip_temperature(PiezoSpeakerV2 *piezo_speaker_v2, int16_t *ret_temperature) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_reset(PiezoSpeakerV2 *piezo_speaker_v2) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_write_uid(PiezoSpeakerV2 *piezo_speaker_v2, uint32_t uid) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int piezo_speaker_v2_read_uid(PiezoSpeakerV2 *piezo_speaker_v2, uint32_t *ret_uid) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int piezo_speaker_v2_get_identity(PiezoSpeakerV2 *piezo_speaker_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = piezo_speaker_v2->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), PIEZO_SPEAKER_V2_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
