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

#include "bricklet_nfc.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ReaderStateChanged_CallbackFunction)(uint8_t state, bool idle, void *user_data);

typedef void (*CardemuStateChanged_CallbackFunction)(uint8_t state, bool idle, void *user_data);

typedef void (*P2PStateChanged_CallbackFunction)(uint8_t state, bool idle, void *user_data);

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
	uint8_t mode;
} ATTRIBUTE_PACKED SetMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderRequestTagID_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderGetTagIDLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t tag_type;
	uint8_t tag_id_length;
	uint8_t tag_id_data[32];
} ATTRIBUTE_PACKED ReaderGetTagIDLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderGetState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED ReaderGetState_Response;

typedef struct {
	PacketHeader header;
	uint16_t ndef_length;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
} ATTRIBUTE_PACKED ReaderWriteNDEFLowLevel_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderRequestNDEF_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderReadNDEFLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t ndef_length;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
} ATTRIBUTE_PACKED ReaderReadNDEFLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint16_t page;
	uint8_t key_number;
	uint8_t key[6];
} ATTRIBUTE_PACKED ReaderAuthenticateMifareClassicPage_Request;

typedef struct {
	PacketHeader header;
	uint16_t page;
	uint16_t data_length;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[58];
} ATTRIBUTE_PACKED ReaderWritePageLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t page;
	uint16_t length;
} ATTRIBUTE_PACKED ReaderRequestPage_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReaderReadPageLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t data_length;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[60];
} ATTRIBUTE_PACKED ReaderReadPageLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED ReaderStateChanged_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED CardemuGetState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED CardemuGetState_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED CardemuStartDiscovery_Request;

typedef struct {
	PacketHeader header;
	uint16_t ndef_length;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
} ATTRIBUTE_PACKED CardemuWriteNDEFLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t transfer;
} ATTRIBUTE_PACKED CardemuStartTransfer_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED CardemuStateChanged_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED P2PGetState_Request;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED P2PGetState_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED P2PStartDiscovery_Request;

typedef struct {
	PacketHeader header;
	uint16_t ndef_length;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
} ATTRIBUTE_PACKED P2PWriteNDEFLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t transfer;
} ATTRIBUTE_PACKED P2PStartTransfer_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED P2PReadNDEFLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t ndef_length;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
} ATTRIBUTE_PACKED P2PReadNDEFLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t state;
	uint8_t idle;
} ATTRIBUTE_PACKED P2PStateChanged_Callback;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetDetectionLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDetectionLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetDetectionLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint16_t timeout;
} ATTRIBUTE_PACKED SetMaximumTimeout_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMaximumTimeout_Request;

typedef struct {
	PacketHeader header;
	uint16_t timeout;
} ATTRIBUTE_PACKED GetMaximumTimeout_Response;

typedef struct {
	PacketHeader header;
	uint8_t index;
} ATTRIBUTE_PACKED SimpleGetTagIDLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t tag_type;
	uint8_t tag_id_length;
	uint8_t tag_id_data[10];
	uint32_t last_seen;
} ATTRIBUTE_PACKED SimpleGetTagIDLowLevel_Response;

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

static void nfc_callback_wrapper_reader_state_changed(DevicePrivate *device_p, Packet *packet) {
	ReaderStateChanged_CallbackFunction callback_function;
	void *user_data;
	ReaderStateChanged_Callback *callback;
	bool unpacked_idle;

	if (packet->header.length != sizeof(ReaderStateChanged_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ReaderStateChanged_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_READER_STATE_CHANGED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_READER_STATE_CHANGED];
	callback = (ReaderStateChanged_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_idle = callback->idle != 0;

	callback_function(callback->state, unpacked_idle, user_data);
}

static void nfc_callback_wrapper_cardemu_state_changed(DevicePrivate *device_p, Packet *packet) {
	CardemuStateChanged_CallbackFunction callback_function;
	void *user_data;
	CardemuStateChanged_Callback *callback;
	bool unpacked_idle;

	if (packet->header.length != sizeof(CardemuStateChanged_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (CardemuStateChanged_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_CARDEMU_STATE_CHANGED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_CARDEMU_STATE_CHANGED];
	callback = (CardemuStateChanged_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_idle = callback->idle != 0;

	callback_function(callback->state, unpacked_idle, user_data);
}

static void nfc_callback_wrapper_p2p_state_changed(DevicePrivate *device_p, Packet *packet) {
	P2PStateChanged_CallbackFunction callback_function;
	void *user_data;
	P2PStateChanged_Callback *callback;
	bool unpacked_idle;

	if (packet->header.length != sizeof(P2PStateChanged_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (P2PStateChanged_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_P2P_STATE_CHANGED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + NFC_CALLBACK_P2P_STATE_CHANGED];
	callback = (P2PStateChanged_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}
	unpacked_idle = callback->idle != 0;

	callback_function(callback->state, unpacked_idle, user_data);
}

void nfc_create(NFC *nfc, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(nfc, uid, ipcon_p, 2, 0, 2, NFC_DEVICE_IDENTIFIER);

	device_p = nfc->p;

	device_p->response_expected[NFC_FUNCTION_SET_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_GET_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_REQUEST_TAG_ID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_READER_GET_TAG_ID_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_WRITE_NDEF_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_REQUEST_NDEF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_READER_READ_NDEF_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_AUTHENTICATE_MIFARE_CLASSIC_PAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_READER_WRITE_PAGE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[NFC_FUNCTION_READER_REQUEST_PAGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_READER_READ_PAGE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_CARDEMU_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_CARDEMU_START_DISCOVERY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_CARDEMU_WRITE_NDEF_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[NFC_FUNCTION_CARDEMU_START_TRANSFER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_P2P_GET_STATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_P2P_START_DISCOVERY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_P2P_WRITE_NDEF_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[NFC_FUNCTION_P2P_START_TRANSFER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_P2P_READ_NDEF_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SET_DETECTION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_GET_DETECTION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SET_MAXIMUM_TIMEOUT] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_GET_MAXIMUM_TIMEOUT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SIMPLE_GET_TAG_ID_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[NFC_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[NFC_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[NFC_CALLBACK_READER_STATE_CHANGED] = nfc_callback_wrapper_reader_state_changed;
	device_p->callback_wrappers[NFC_CALLBACK_CARDEMU_STATE_CHANGED] = nfc_callback_wrapper_cardemu_state_changed;
	device_p->callback_wrappers[NFC_CALLBACK_P2P_STATE_CHANGED] = nfc_callback_wrapper_p2p_state_changed;

	ipcon_add_device(ipcon_p, device_p);
}

void nfc_destroy(NFC *nfc) {
	device_release(nfc->p);
}

int nfc_get_response_expected(NFC *nfc, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(nfc->p, function_id, ret_response_expected);
}

int nfc_set_response_expected(NFC *nfc, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(nfc->p, function_id, response_expected);
}

int nfc_set_response_expected_all(NFC *nfc, bool response_expected) {
	return device_set_response_expected_all(nfc->p, response_expected);
}

void nfc_register_callback(NFC *nfc, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(nfc->p, callback_id, function, user_data);
}

int nfc_get_api_version(NFC *nfc, uint8_t ret_api_version[3]) {
	return device_get_api_version(nfc->p, ret_api_version);
}

int nfc_set_mode(NFC *nfc, uint8_t mode) {
	DevicePrivate *device_p = nfc->p;
	SetMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_get_mode(NFC *nfc, uint8_t *ret_mode) {
	DevicePrivate *device_p = nfc->p;
	GetMode_Request request;
	GetMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_MODE, device_p->ipcon_p, device_p);

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

int nfc_reader_request_tag_id(NFC *nfc) {
	DevicePrivate *device_p = nfc->p;
	ReaderRequestTagID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_REQUEST_TAG_ID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_get_tag_id_low_level(NFC *nfc, uint8_t *ret_tag_type, uint8_t *ret_tag_id_length, uint8_t ret_tag_id_data[32]) {
	DevicePrivate *device_p = nfc->p;
	ReaderGetTagIDLowLevel_Request request;
	ReaderGetTagIDLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_GET_TAG_ID_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_tag_type = response.tag_type;
	*ret_tag_id_length = response.tag_id_length;
	memcpy(ret_tag_id_data, response.tag_id_data, 32 * sizeof(uint8_t));

	return ret;
}

int nfc_reader_get_state(NFC *nfc, uint8_t *ret_state, bool *ret_idle) {
	DevicePrivate *device_p = nfc->p;
	ReaderGetState_Request request;
	ReaderGetState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_GET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_state = response.state;
	*ret_idle = response.idle != 0;

	return ret;
}

int nfc_reader_write_ndef_low_level(NFC *nfc, uint16_t ndef_length, uint16_t ndef_chunk_offset, uint8_t ndef_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	ReaderWriteNDEFLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_WRITE_NDEF_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.ndef_length = leconvert_uint16_to(ndef_length);
	request.ndef_chunk_offset = leconvert_uint16_to(ndef_chunk_offset);
	memcpy(request.ndef_chunk_data, ndef_chunk_data, 60 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_request_ndef(NFC *nfc) {
	DevicePrivate *device_p = nfc->p;
	ReaderRequestNDEF_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_REQUEST_NDEF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_read_ndef_low_level(NFC *nfc, uint16_t *ret_ndef_length, uint16_t *ret_ndef_chunk_offset, uint8_t ret_ndef_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	ReaderReadNDEFLowLevel_Request request;
	ReaderReadNDEFLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_READ_NDEF_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_ndef_length = leconvert_uint16_from(response.ndef_length);
	*ret_ndef_chunk_offset = leconvert_uint16_from(response.ndef_chunk_offset);
	memcpy(ret_ndef_chunk_data, response.ndef_chunk_data, 60 * sizeof(uint8_t));

	return ret;
}

int nfc_reader_authenticate_mifare_classic_page(NFC *nfc, uint16_t page, uint8_t key_number, uint8_t key[6]) {
	DevicePrivate *device_p = nfc->p;
	ReaderAuthenticateMifareClassicPage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_AUTHENTICATE_MIFARE_CLASSIC_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);
	request.key_number = key_number;
	memcpy(request.key, key, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_write_page_low_level(NFC *nfc, uint16_t page, uint16_t data_length, uint16_t data_chunk_offset, uint8_t data_chunk_data[58]) {
	DevicePrivate *device_p = nfc->p;
	ReaderWritePageLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_WRITE_PAGE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);
	request.data_length = leconvert_uint16_to(data_length);
	request.data_chunk_offset = leconvert_uint16_to(data_chunk_offset);
	memcpy(request.data_chunk_data, data_chunk_data, 58 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_request_page(NFC *nfc, uint16_t page, uint16_t length) {
	DevicePrivate *device_p = nfc->p;
	ReaderRequestPage_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_REQUEST_PAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.page = leconvert_uint16_to(page);
	request.length = leconvert_uint16_to(length);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_reader_read_page_low_level(NFC *nfc, uint16_t *ret_data_length, uint16_t *ret_data_chunk_offset, uint8_t ret_data_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	ReaderReadPageLowLevel_Request request;
	ReaderReadPageLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READER_READ_PAGE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_data_length = leconvert_uint16_from(response.data_length);
	*ret_data_chunk_offset = leconvert_uint16_from(response.data_chunk_offset);
	memcpy(ret_data_chunk_data, response.data_chunk_data, 60 * sizeof(uint8_t));

	return ret;
}

int nfc_cardemu_get_state(NFC *nfc, uint8_t *ret_state, bool *ret_idle) {
	DevicePrivate *device_p = nfc->p;
	CardemuGetState_Request request;
	CardemuGetState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_CARDEMU_GET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_state = response.state;
	*ret_idle = response.idle != 0;

	return ret;
}

int nfc_cardemu_start_discovery(NFC *nfc) {
	DevicePrivate *device_p = nfc->p;
	CardemuStartDiscovery_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_CARDEMU_START_DISCOVERY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_cardemu_write_ndef_low_level(NFC *nfc, uint16_t ndef_length, uint16_t ndef_chunk_offset, uint8_t ndef_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	CardemuWriteNDEFLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_CARDEMU_WRITE_NDEF_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.ndef_length = leconvert_uint16_to(ndef_length);
	request.ndef_chunk_offset = leconvert_uint16_to(ndef_chunk_offset);
	memcpy(request.ndef_chunk_data, ndef_chunk_data, 60 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_cardemu_start_transfer(NFC *nfc, uint8_t transfer) {
	DevicePrivate *device_p = nfc->p;
	CardemuStartTransfer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_CARDEMU_START_TRANSFER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.transfer = transfer;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_p2p_get_state(NFC *nfc, uint8_t *ret_state, bool *ret_idle) {
	DevicePrivate *device_p = nfc->p;
	P2PGetState_Request request;
	P2PGetState_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_P2P_GET_STATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_state = response.state;
	*ret_idle = response.idle != 0;

	return ret;
}

int nfc_p2p_start_discovery(NFC *nfc) {
	DevicePrivate *device_p = nfc->p;
	P2PStartDiscovery_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_P2P_START_DISCOVERY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_p2p_write_ndef_low_level(NFC *nfc, uint16_t ndef_length, uint16_t ndef_chunk_offset, uint8_t ndef_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	P2PWriteNDEFLowLevel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_P2P_WRITE_NDEF_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.ndef_length = leconvert_uint16_to(ndef_length);
	request.ndef_chunk_offset = leconvert_uint16_to(ndef_chunk_offset);
	memcpy(request.ndef_chunk_data, ndef_chunk_data, 60 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_p2p_start_transfer(NFC *nfc, uint8_t transfer) {
	DevicePrivate *device_p = nfc->p;
	P2PStartTransfer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_P2P_START_TRANSFER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.transfer = transfer;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_p2p_read_ndef_low_level(NFC *nfc, uint16_t *ret_ndef_length, uint16_t *ret_ndef_chunk_offset, uint8_t ret_ndef_chunk_data[60]) {
	DevicePrivate *device_p = nfc->p;
	P2PReadNDEFLowLevel_Request request;
	P2PReadNDEFLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_P2P_READ_NDEF_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_ndef_length = leconvert_uint16_from(response.ndef_length);
	*ret_ndef_chunk_offset = leconvert_uint16_from(response.ndef_chunk_offset);
	memcpy(ret_ndef_chunk_data, response.ndef_chunk_data, 60 * sizeof(uint8_t));

	return ret;
}

int nfc_set_detection_led_config(NFC *nfc, uint8_t config) {
	DevicePrivate *device_p = nfc->p;
	SetDetectionLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_DETECTION_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_get_detection_led_config(NFC *nfc, uint8_t *ret_config) {
	DevicePrivate *device_p = nfc->p;
	GetDetectionLEDConfig_Request request;
	GetDetectionLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_DETECTION_LED_CONFIG, device_p->ipcon_p, device_p);

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

int nfc_set_maximum_timeout(NFC *nfc, uint16_t timeout) {
	DevicePrivate *device_p = nfc->p;
	SetMaximumTimeout_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_MAXIMUM_TIMEOUT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.timeout = leconvert_uint16_to(timeout);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_get_maximum_timeout(NFC *nfc, uint16_t *ret_timeout) {
	DevicePrivate *device_p = nfc->p;
	GetMaximumTimeout_Request request;
	GetMaximumTimeout_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_MAXIMUM_TIMEOUT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timeout = leconvert_uint16_from(response.timeout);

	return ret;
}

int nfc_simple_get_tag_id_low_level(NFC *nfc, uint8_t index, uint8_t *ret_tag_type, uint8_t *ret_tag_id_length, uint8_t ret_tag_id_data[10], uint32_t *ret_last_seen) {
	DevicePrivate *device_p = nfc->p;
	SimpleGetTagIDLowLevel_Request request;
	SimpleGetTagIDLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SIMPLE_GET_TAG_ID_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = index;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_tag_type = response.tag_type;
	*ret_tag_id_length = response.tag_id_length;
	memcpy(ret_tag_id_data, response.tag_id_data, 10 * sizeof(uint8_t));
	*ret_last_seen = leconvert_uint32_from(response.last_seen);

	return ret;
}

int nfc_get_spitfp_error_count(NFC *nfc, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = nfc->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int nfc_set_bootloader_mode(NFC *nfc, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = nfc->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int nfc_get_bootloader_mode(NFC *nfc, uint8_t *ret_mode) {
	DevicePrivate *device_p = nfc->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int nfc_set_write_firmware_pointer(NFC *nfc, uint32_t pointer) {
	DevicePrivate *device_p = nfc->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_write_firmware(NFC *nfc, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = nfc->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int nfc_set_status_led_config(NFC *nfc, uint8_t config) {
	DevicePrivate *device_p = nfc->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_get_status_led_config(NFC *nfc, uint8_t *ret_config) {
	DevicePrivate *device_p = nfc->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int nfc_get_chip_temperature(NFC *nfc, int16_t *ret_temperature) {
	DevicePrivate *device_p = nfc->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int nfc_reset(NFC *nfc) {
	DevicePrivate *device_p = nfc->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_write_uid(NFC *nfc, uint32_t uid) {
	DevicePrivate *device_p = nfc->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int nfc_read_uid(NFC *nfc, uint32_t *ret_uid) {
	DevicePrivate *device_p = nfc->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int nfc_get_identity(NFC *nfc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = nfc->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), NFC_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int nfc_reader_get_tag_id(NFC *nfc, uint8_t *ret_tag_type, uint8_t *ret_tag_id, uint8_t *ret_tag_id_length) {
	int ret = 0;
	uint8_t tag_id_length;
	uint8_t tag_id_data[32];

	*ret_tag_id_length = 0;

	ret = nfc_reader_get_tag_id_low_level(nfc, ret_tag_type, &tag_id_length, tag_id_data);

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_tag_id, tag_id_data, sizeof(uint8_t) * tag_id_length);
	memset(&ret_tag_id[tag_id_length], 0, sizeof(uint8_t) * (32 - tag_id_length));

	*ret_tag_id_length = tag_id_length;

	return ret;
}

int nfc_reader_write_ndef(NFC *nfc, uint8_t *ndef, uint16_t ndef_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t ndef_chunk_offset = 0;
	uint8_t ndef_chunk_data[60];
	uint16_t ndef_chunk_length;

	if (ndef_length == 0) {
		memset(&ndef_chunk_data, 0, sizeof(uint8_t) * 60);

		ret = nfc_reader_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (ndef_chunk_offset < ndef_length) {
			ndef_chunk_length = ndef_length - ndef_chunk_offset;

			if (ndef_chunk_length > 60) {
				ndef_chunk_length = 60;
			}

			memcpy(ndef_chunk_data, &ndef[ndef_chunk_offset], sizeof(uint8_t) * ndef_chunk_length);
			memset(&ndef_chunk_data[ndef_chunk_length], 0, sizeof(uint8_t) * (60 - ndef_chunk_length));

			ret = nfc_reader_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				break;
			}

			ndef_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int nfc_reader_read_ndef(NFC *nfc, uint8_t *ret_ndef, uint16_t *ret_ndef_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t ndef_length = 0;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
	bool ndef_out_of_sync;
	uint16_t ndef_chunk_length;

	*ret_ndef_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = nfc_reader_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	ndef_out_of_sync = ndef_chunk_offset != 0;

	if (!ndef_out_of_sync) {
		ndef_chunk_length = ndef_length - ndef_chunk_offset;

		if (ndef_chunk_length > 60) {
			ndef_chunk_length = 60;
		}

		memcpy(ret_ndef, ndef_chunk_data, sizeof(uint8_t) * ndef_chunk_length);
		*ret_ndef_length = ndef_chunk_length;

		while (*ret_ndef_length < ndef_length) {
			ret = nfc_reader_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			ndef_out_of_sync = ndef_chunk_offset != *ret_ndef_length;

			if (ndef_out_of_sync) {
				break;
			}

			ndef_chunk_length = ndef_length - ndef_chunk_offset;

			if (ndef_chunk_length > 60) {
				ndef_chunk_length = 60;
			}

			memcpy(&ret_ndef[*ret_ndef_length], ndef_chunk_data, sizeof(uint8_t) * ndef_chunk_length);
			*ret_ndef_length += ndef_chunk_length;
		}
	}

	if (ndef_out_of_sync) {
		*ret_ndef_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (ndef_chunk_offset + 60 < ndef_length) {
			ret = nfc_reader_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

int nfc_reader_write_page(NFC *nfc, uint16_t page, uint8_t *data, uint16_t data_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t data_chunk_offset = 0;
	uint8_t data_chunk_data[58];
	uint16_t data_chunk_length;

	if (data_length == 0) {
		memset(&data_chunk_data, 0, sizeof(uint8_t) * 58);

		ret = nfc_reader_write_page_low_level(nfc, page, data_length, data_chunk_offset, data_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (data_chunk_offset < data_length) {
			data_chunk_length = data_length - data_chunk_offset;

			if (data_chunk_length > 58) {
				data_chunk_length = 58;
			}

			memcpy(data_chunk_data, &data[data_chunk_offset], sizeof(uint8_t) * data_chunk_length);
			memset(&data_chunk_data[data_chunk_length], 0, sizeof(uint8_t) * (58 - data_chunk_length));

			ret = nfc_reader_write_page_low_level(nfc, page, data_length, data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				break;
			}

			data_chunk_offset += 58;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int nfc_reader_read_page(NFC *nfc, uint8_t *ret_data, uint16_t *ret_data_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t data_length = 0;
	uint16_t data_chunk_offset;
	uint8_t data_chunk_data[60];
	bool data_out_of_sync;
	uint16_t data_chunk_length;

	*ret_data_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = nfc_reader_read_page_low_level(nfc, &data_length, &data_chunk_offset, data_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	data_out_of_sync = data_chunk_offset != 0;

	if (!data_out_of_sync) {
		data_chunk_length = data_length - data_chunk_offset;

		if (data_chunk_length > 60) {
			data_chunk_length = 60;
		}

		memcpy(ret_data, data_chunk_data, sizeof(uint8_t) * data_chunk_length);
		*ret_data_length = data_chunk_length;

		while (*ret_data_length < data_length) {
			ret = nfc_reader_read_page_low_level(nfc, &data_length, &data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			data_out_of_sync = data_chunk_offset != *ret_data_length;

			if (data_out_of_sync) {
				break;
			}

			data_chunk_length = data_length - data_chunk_offset;

			if (data_chunk_length > 60) {
				data_chunk_length = 60;
			}

			memcpy(&ret_data[*ret_data_length], data_chunk_data, sizeof(uint8_t) * data_chunk_length);
			*ret_data_length += data_chunk_length;
		}
	}

	if (data_out_of_sync) {
		*ret_data_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (data_chunk_offset + 60 < data_length) {
			ret = nfc_reader_read_page_low_level(nfc, &data_length, &data_chunk_offset, data_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

int nfc_cardemu_write_ndef(NFC *nfc, uint8_t *ndef, uint16_t ndef_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t ndef_chunk_offset = 0;
	uint8_t ndef_chunk_data[60];
	uint16_t ndef_chunk_length;

	if (ndef_length == 0) {
		memset(&ndef_chunk_data, 0, sizeof(uint8_t) * 60);

		ret = nfc_cardemu_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (ndef_chunk_offset < ndef_length) {
			ndef_chunk_length = ndef_length - ndef_chunk_offset;

			if (ndef_chunk_length > 60) {
				ndef_chunk_length = 60;
			}

			memcpy(ndef_chunk_data, &ndef[ndef_chunk_offset], sizeof(uint8_t) * ndef_chunk_length);
			memset(&ndef_chunk_data[ndef_chunk_length], 0, sizeof(uint8_t) * (60 - ndef_chunk_length));

			ret = nfc_cardemu_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				break;
			}

			ndef_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int nfc_p2p_write_ndef(NFC *nfc, uint8_t *ndef, uint16_t ndef_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t ndef_chunk_offset = 0;
	uint8_t ndef_chunk_data[60];
	uint16_t ndef_chunk_length;

	if (ndef_length == 0) {
		memset(&ndef_chunk_data, 0, sizeof(uint8_t) * 60);

		ret = nfc_p2p_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (ndef_chunk_offset < ndef_length) {
			ndef_chunk_length = ndef_length - ndef_chunk_offset;

			if (ndef_chunk_length > 60) {
				ndef_chunk_length = 60;
			}

			memcpy(ndef_chunk_data, &ndef[ndef_chunk_offset], sizeof(uint8_t) * ndef_chunk_length);
			memset(&ndef_chunk_data[ndef_chunk_length], 0, sizeof(uint8_t) * (60 - ndef_chunk_length));

			ret = nfc_p2p_write_ndef_low_level(nfc, ndef_length, ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				break;
			}

			ndef_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int nfc_p2p_read_ndef(NFC *nfc, uint8_t *ret_ndef, uint16_t *ret_ndef_length) {
	DevicePrivate *device_p = nfc->p;
	int ret = 0;
	uint16_t ndef_length = 0;
	uint16_t ndef_chunk_offset;
	uint8_t ndef_chunk_data[60];
	bool ndef_out_of_sync;
	uint16_t ndef_chunk_length;

	*ret_ndef_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = nfc_p2p_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	ndef_out_of_sync = ndef_chunk_offset != 0;

	if (!ndef_out_of_sync) {
		ndef_chunk_length = ndef_length - ndef_chunk_offset;

		if (ndef_chunk_length > 60) {
			ndef_chunk_length = 60;
		}

		memcpy(ret_ndef, ndef_chunk_data, sizeof(uint8_t) * ndef_chunk_length);
		*ret_ndef_length = ndef_chunk_length;

		while (*ret_ndef_length < ndef_length) {
			ret = nfc_p2p_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			ndef_out_of_sync = ndef_chunk_offset != *ret_ndef_length;

			if (ndef_out_of_sync) {
				break;
			}

			ndef_chunk_length = ndef_length - ndef_chunk_offset;

			if (ndef_chunk_length > 60) {
				ndef_chunk_length = 60;
			}

			memcpy(&ret_ndef[*ret_ndef_length], ndef_chunk_data, sizeof(uint8_t) * ndef_chunk_length);
			*ret_ndef_length += ndef_chunk_length;
		}
	}

	if (ndef_out_of_sync) {
		*ret_ndef_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (ndef_chunk_offset + 60 < ndef_length) {
			ret = nfc_p2p_read_ndef_low_level(nfc, &ndef_length, &ndef_chunk_offset, ndef_chunk_data);

			if (ret < 0) {
				goto unlock;
			}
		}

		ret = E_STREAM_OUT_OF_SYNC;
	}

unlock:
	mutex_unlock(&device_p->stream_mutex);

	return ret;
}

int nfc_simple_get_tag_id(NFC *nfc, uint8_t index, uint8_t *ret_tag_type, uint8_t *ret_tag_id, uint8_t *ret_tag_id_length, uint32_t *ret_last_seen) {
	int ret = 0;
	uint8_t tag_id_length;
	uint8_t tag_id_data[10];

	*ret_tag_id_length = 0;

	ret = nfc_simple_get_tag_id_low_level(nfc, index, ret_tag_type, &tag_id_length, tag_id_data, ret_last_seen);

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_tag_id, tag_id_data, sizeof(uint8_t) * tag_id_length);
	memset(&ret_tag_id[tag_id_length], 0, sizeof(uint8_t) * (10 - tag_id_length));

	*ret_tag_id_length = tag_id_length;

	return ret;
}

#ifdef __cplusplus
}
#endif
