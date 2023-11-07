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

#include "bricklet_one_wire.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



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
} ATTRIBUTE_PACKED SearchBusLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t identifier_length;
	uint16_t identifier_chunk_offset;
	uint64_t identifier_chunk_data[7];
	uint8_t status;
} ATTRIBUTE_PACKED SearchBusLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ResetBus_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED ResetBus_Response;

typedef struct {
	PacketHeader header;
	uint8_t data;
} ATTRIBUTE_PACKED Write_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED Write_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Read_Request;

typedef struct {
	PacketHeader header;
	uint8_t data;
	uint8_t status;
} ATTRIBUTE_PACKED Read_Response;

typedef struct {
	PacketHeader header;
	uint64_t identifier;
	uint8_t command;
} ATTRIBUTE_PACKED WriteCommand_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED WriteCommand_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetCommunicationLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetCommunicationLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetCommunicationLEDConfig_Response;

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

void one_wire_create(OneWire *one_wire, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(one_wire, uid, ipcon_p, 2, 0, 0, ONE_WIRE_DEVICE_IDENTIFIER);

	device_p = one_wire->p;

	device_p->response_expected[ONE_WIRE_FUNCTION_SEARCH_BUS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_RESET_BUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_WRITE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_READ] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_WRITE_COMMAND] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_SET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ONE_WIRE_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ONE_WIRE_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[ONE_WIRE_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[ONE_WIRE_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	ipcon_add_device(ipcon_p, device_p);
}

void one_wire_destroy(OneWire *one_wire) {
	device_release(one_wire->p);
}

int one_wire_get_response_expected(OneWire *one_wire, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(one_wire->p, function_id, ret_response_expected);
}

int one_wire_set_response_expected(OneWire *one_wire, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(one_wire->p, function_id, response_expected);
}

int one_wire_set_response_expected_all(OneWire *one_wire, bool response_expected) {
	return device_set_response_expected_all(one_wire->p, response_expected);
}


int one_wire_get_api_version(OneWire *one_wire, uint8_t ret_api_version[3]) {
	return device_get_api_version(one_wire->p, ret_api_version);
}

int one_wire_search_bus_low_level(OneWire *one_wire, uint16_t *ret_identifier_length, uint16_t *ret_identifier_chunk_offset, uint64_t ret_identifier_chunk_data[7], uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	SearchBusLowLevel_Request request;
	SearchBusLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_SEARCH_BUS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_identifier_length = leconvert_uint16_from(response.identifier_length);
	*ret_identifier_chunk_offset = leconvert_uint16_from(response.identifier_chunk_offset);
	for (i = 0; i < 7; i++) ret_identifier_chunk_data[i] = leconvert_uint64_from(response.identifier_chunk_data[i]);
	*ret_status = response.status;

	return ret;
}

int one_wire_reset_bus(OneWire *one_wire, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	ResetBus_Request request;
	ResetBus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_RESET_BUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int one_wire_write(OneWire *one_wire, uint8_t data, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	Write_Request request;
	Write_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_WRITE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.data = data;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int one_wire_read(OneWire *one_wire, uint8_t *ret_data, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	Read_Request request;
	Read_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_READ, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_data = response.data;
	*ret_status = response.status;

	return ret;
}

int one_wire_write_command(OneWire *one_wire, uint64_t identifier, uint8_t command, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	WriteCommand_Request request;
	WriteCommand_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_WRITE_COMMAND, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.identifier = leconvert_uint64_to(identifier);
	request.command = command;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int one_wire_set_communication_led_config(OneWire *one_wire, uint8_t config) {
	DevicePrivate *device_p = one_wire->p;
	SetCommunicationLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_SET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int one_wire_get_communication_led_config(OneWire *one_wire, uint8_t *ret_config) {
	DevicePrivate *device_p = one_wire->p;
	GetCommunicationLEDConfig_Request request;
	GetCommunicationLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

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

int one_wire_get_spitfp_error_count(OneWire *one_wire, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = one_wire->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int one_wire_set_bootloader_mode(OneWire *one_wire, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int one_wire_get_bootloader_mode(OneWire *one_wire, uint8_t *ret_mode) {
	DevicePrivate *device_p = one_wire->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int one_wire_set_write_firmware_pointer(OneWire *one_wire, uint32_t pointer) {
	DevicePrivate *device_p = one_wire->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int one_wire_write_firmware(OneWire *one_wire, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int one_wire_set_status_led_config(OneWire *one_wire, uint8_t config) {
	DevicePrivate *device_p = one_wire->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int one_wire_get_status_led_config(OneWire *one_wire, uint8_t *ret_config) {
	DevicePrivate *device_p = one_wire->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int one_wire_get_chip_temperature(OneWire *one_wire, int16_t *ret_temperature) {
	DevicePrivate *device_p = one_wire->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int one_wire_reset(OneWire *one_wire) {
	DevicePrivate *device_p = one_wire->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int one_wire_write_uid(OneWire *one_wire, uint32_t uid) {
	DevicePrivate *device_p = one_wire->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int one_wire_read_uid(OneWire *one_wire, uint32_t *ret_uid) {
	DevicePrivate *device_p = one_wire->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int one_wire_get_identity(OneWire *one_wire, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = one_wire->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), ONE_WIRE_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int one_wire_search_bus(OneWire *one_wire, uint64_t *ret_identifier, uint16_t *ret_identifier_length, uint8_t *ret_status) {
	DevicePrivate *device_p = one_wire->p;
	int ret = 0;
	uint16_t identifier_length = 0;
	uint16_t identifier_chunk_offset;
	uint64_t identifier_chunk_data[7];
	bool identifier_out_of_sync;
	uint16_t identifier_chunk_length;

	*ret_identifier_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = one_wire_search_bus_low_level(one_wire, &identifier_length, &identifier_chunk_offset, identifier_chunk_data, ret_status);

	if (ret < 0) {
		goto unlock;
	}

	identifier_out_of_sync = identifier_chunk_offset != 0;

	if (!identifier_out_of_sync) {
		identifier_chunk_length = identifier_length - identifier_chunk_offset;

		if (identifier_chunk_length > 7) {
			identifier_chunk_length = 7;
		}

		memcpy(ret_identifier, identifier_chunk_data, sizeof(uint64_t) * identifier_chunk_length);
		*ret_identifier_length = identifier_chunk_length;

		while (*ret_identifier_length < identifier_length) {
			ret = one_wire_search_bus_low_level(one_wire, &identifier_length, &identifier_chunk_offset, identifier_chunk_data, ret_status);

			if (ret < 0) {
				goto unlock;
			}

			identifier_out_of_sync = identifier_chunk_offset != *ret_identifier_length;

			if (identifier_out_of_sync) {
				break;
			}

			identifier_chunk_length = identifier_length - identifier_chunk_offset;

			if (identifier_chunk_length > 7) {
				identifier_chunk_length = 7;
			}

			memcpy(&ret_identifier[*ret_identifier_length], identifier_chunk_data, sizeof(uint64_t) * identifier_chunk_length);
			*ret_identifier_length += identifier_chunk_length;
		}
	}

	if (identifier_out_of_sync) {
		*ret_identifier_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (identifier_chunk_offset + 7 < identifier_length) {
			ret = one_wire_search_bus_low_level(one_wire, &identifier_length, &identifier_chunk_offset, identifier_chunk_data, ret_status);

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

#ifdef __cplusplus
}
#endif
