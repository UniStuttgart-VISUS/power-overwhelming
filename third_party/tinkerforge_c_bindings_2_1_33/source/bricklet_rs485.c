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

#include "bricklet_rs485.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*ReadLowLevel_CallbackFunction)(uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60], void *user_data);

typedef void (*ErrorCount_CallbackFunction)(uint32_t overrun_error_count, uint32_t parity_error_count, void *user_data);

typedef void (*ModbusSlaveReadCoilsRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t count, void *user_data);

typedef void (*ModbusMasterReadCoilsResponseLowLevel_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[464], void *user_data);

typedef void (*ModbusSlaveReadHoldingRegistersRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t count, void *user_data);

typedef void (*ModbusMasterReadHoldingRegistersResponseLowLevel_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t holding_registers_length, uint16_t holding_registers_chunk_offset, uint16_t holding_registers_chunk_data[29], void *user_data);

typedef void (*ModbusSlaveWriteSingleCoilRequest_CallbackFunction)(uint8_t request_id, uint32_t coil_address, bool coil_value, void *user_data);

typedef void (*ModbusMasterWriteSingleCoilResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, void *user_data);

typedef void (*ModbusSlaveWriteSingleRegisterRequest_CallbackFunction)(uint8_t request_id, uint32_t register_address, uint16_t register_value, void *user_data);

typedef void (*ModbusMasterWriteSingleRegisterResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, void *user_data);

typedef void (*ModbusSlaveWriteMultipleCoilsRequestLowLevel_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[440], void *user_data);

typedef void (*ModbusMasterWriteMultipleCoilsResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, void *user_data);

typedef void (*ModbusSlaveWriteMultipleRegistersRequestLowLevel_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t registers_length, uint16_t registers_chunk_offset, uint16_t registers_chunk_data[27], void *user_data);

typedef void (*ModbusMasterWriteMultipleRegistersResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, void *user_data);

typedef void (*ModbusSlaveReadDiscreteInputsRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t count, void *user_data);

typedef void (*ModbusMasterReadDiscreteInputsResponseLowLevel_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t discrete_inputs_length, uint16_t discrete_inputs_chunk_offset, bool discrete_inputs_chunk_data[464], void *user_data);

typedef void (*ModbusSlaveReadInputRegistersRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t count, void *user_data);

typedef void (*ModbusMasterReadInputRegistersResponseLowLevel_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t input_registers_length, uint16_t input_registers_chunk_offset, uint16_t input_registers_chunk_data[29], void *user_data);

typedef void (*FrameReadable_CallbackFunction)(uint16_t frame_count, void *user_data);

typedef void (*Read_CallbackFunction)(char *message, uint16_t message_length, void *user_data);

typedef void (*ModbusMasterReadCoilsResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, bool *coils, uint16_t coils_length, void *user_data);

typedef void (*ModbusMasterReadHoldingRegistersResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t *holding_registers, uint16_t holding_registers_length, void *user_data);

typedef void (*ModbusSlaveWriteMultipleCoilsRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, bool *coils, uint16_t coils_length, void *user_data);

typedef void (*ModbusSlaveWriteMultipleRegistersRequest_CallbackFunction)(uint8_t request_id, uint32_t starting_address, uint16_t *registers, uint16_t registers_length, void *user_data);

typedef void (*ModbusMasterReadDiscreteInputsResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, bool *discrete_inputs, uint16_t discrete_inputs_length, void *user_data);

typedef void (*ModbusMasterReadInputRegistersResponse_CallbackFunction)(uint8_t request_id, int8_t exception_code, uint16_t *input_registers, uint16_t input_registers_length, void *user_data);

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
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED WriteLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t message_chunk_written;
} ATTRIBUTE_PACKED WriteLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint16_t length;
} ATTRIBUTE_PACKED ReadLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED ReadLowLevel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableReadCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsReadCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsReadCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t duplex;
} ATTRIBUTE_PACKED SetRS485Configuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485Configuration_Request;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stopbits;
	uint8_t wordlength;
	uint8_t duplex;
} ATTRIBUTE_PACKED GetRS485Configuration_Response;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t master_request_timeout;
} ATTRIBUTE_PACKED SetModbusConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetModbusConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t master_request_timeout;
} ATTRIBUTE_PACKED GetModbusConfiguration_Response;

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
	uint8_t config;
} ATTRIBUTE_PACKED SetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetErrorLEDConfig_Response;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_size;
	uint16_t receive_buffer_size;
} ATTRIBUTE_PACKED SetBufferConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBufferConfig_Request;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_size;
	uint16_t receive_buffer_size;
} ATTRIBUTE_PACKED GetBufferConfig_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBufferStatus_Request;

typedef struct {
	PacketHeader header;
	uint16_t send_buffer_used;
	uint16_t receive_buffer_used;
} ATTRIBUTE_PACKED GetBufferStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableErrorCountCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableErrorCountCallback_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsErrorCountCallbackEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsErrorCountCallbackEnabled_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t overrun_error_count;
	uint32_t parity_error_count;
} ATTRIBUTE_PACKED GetErrorCount_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetModbusCommonErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t timeout_error_count;
	uint32_t checksum_error_count;
	uint32_t frame_too_big_error_count;
	uint32_t illegal_function_error_count;
	uint32_t illegal_data_address_error_count;
	uint32_t illegal_data_value_error_count;
	uint32_t slave_device_failure_error_count;
} ATTRIBUTE_PACKED GetModbusCommonErrorCount_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
} ATTRIBUTE_PACKED ModbusSlaveReportException_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint16_t coils_length;
	uint16_t coils_chunk_offset;
	uint8_t coils_chunk_data[59];
} ATTRIBUTE_PACKED ModbusSlaveAnswerReadCoilsRequestLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusMasterReadCoils_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterReadCoils_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint16_t holding_registers_length;
	uint16_t holding_registers_chunk_offset;
	uint16_t holding_registers_chunk_data[29];
} ATTRIBUTE_PACKED ModbusSlaveAnswerReadHoldingRegistersRequestLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusMasterReadHoldingRegisters_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterReadHoldingRegisters_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusSlaveAnswerWriteSingleCoilRequest_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t coil_address;
	uint8_t coil_value;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleCoil_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleCoil_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusSlaveAnswerWriteSingleRegisterRequest_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t register_address;
	uint16_t register_value;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleRegister_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleRegister_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusSlaveAnswerWriteMultipleCoilsRequest_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t coils_length;
	uint16_t coils_chunk_offset;
	uint8_t coils_chunk_data[55];
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleCoilsLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleCoilsLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusSlaveAnswerWriteMultipleRegistersRequest_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t registers_length;
	uint16_t registers_chunk_offset;
	uint16_t registers_chunk_data[27];
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleRegistersLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleRegistersLowLevel_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint16_t discrete_inputs_length;
	uint16_t discrete_inputs_chunk_offset;
	uint8_t discrete_inputs_chunk_data[59];
} ATTRIBUTE_PACKED ModbusSlaveAnswerReadDiscreteInputsRequestLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusMasterReadDiscreteInputs_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterReadDiscreteInputs_Response;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint16_t input_registers_length;
	uint16_t input_registers_chunk_offset;
	uint16_t input_registers_chunk_data[29];
} ATTRIBUTE_PACKED ModbusSlaveAnswerReadInputRegistersRequestLowLevel_Request;

typedef struct {
	PacketHeader header;
	uint8_t slave_address;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusMasterReadInputRegisters_Request;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
} ATTRIBUTE_PACKED ModbusMasterReadInputRegisters_Response;

typedef struct {
	PacketHeader header;
	uint16_t message_length;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
} ATTRIBUTE_PACKED ReadLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint32_t overrun_error_count;
	uint32_t parity_error_count;
} ATTRIBUTE_PACKED ErrorCount_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusSlaveReadCoilsRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
	uint16_t coils_length;
	uint16_t coils_chunk_offset;
	uint8_t coils_chunk_data[58];
} ATTRIBUTE_PACKED ModbusMasterReadCoilsResponseLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusSlaveReadHoldingRegistersRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
	uint16_t holding_registers_length;
	uint16_t holding_registers_chunk_offset;
	uint16_t holding_registers_chunk_data[29];
} ATTRIBUTE_PACKED ModbusMasterReadHoldingRegistersResponseLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t coil_address;
	uint8_t coil_value;
} ATTRIBUTE_PACKED ModbusSlaveWriteSingleCoilRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleCoilResponse_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t register_address;
	uint16_t register_value;
} ATTRIBUTE_PACKED ModbusSlaveWriteSingleRegisterRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
} ATTRIBUTE_PACKED ModbusMasterWriteSingleRegisterResponse_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t coils_length;
	uint16_t coils_chunk_offset;
	uint8_t coils_chunk_data[55];
} ATTRIBUTE_PACKED ModbusSlaveWriteMultipleCoilsRequestLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleCoilsResponse_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t registers_length;
	uint16_t registers_chunk_offset;
	uint16_t registers_chunk_data[27];
} ATTRIBUTE_PACKED ModbusSlaveWriteMultipleRegistersRequestLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
} ATTRIBUTE_PACKED ModbusMasterWriteMultipleRegistersResponse_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusSlaveReadDiscreteInputsRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
	uint16_t discrete_inputs_length;
	uint16_t discrete_inputs_chunk_offset;
	uint8_t discrete_inputs_chunk_data[58];
} ATTRIBUTE_PACKED ModbusMasterReadDiscreteInputsResponseLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	uint32_t starting_address;
	uint16_t count;
} ATTRIBUTE_PACKED ModbusSlaveReadInputRegistersRequest_Callback;

typedef struct {
	PacketHeader header;
	uint8_t request_id;
	int8_t exception_code;
	uint16_t input_registers_length;
	uint16_t input_registers_chunk_offset;
	uint16_t input_registers_chunk_data[29];
} ATTRIBUTE_PACKED ModbusMasterReadInputRegistersResponseLowLevel_Callback;

typedef struct {
	PacketHeader header;
	uint16_t frame_size;
} ATTRIBUTE_PACKED SetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint16_t frame_size;
} ATTRIBUTE_PACKED GetFrameReadableCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint16_t frame_count;
} ATTRIBUTE_PACKED FrameReadable_Callback;

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

static void rs485_callback_wrapper_read(DevicePrivate *device_p, uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60]) {
	Read_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_READ];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_READ];
	uint16_t message_chunk_length = message_length - message_chunk_offset;

	callback_function = (Read_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_READ];

	if (message_chunk_length > 60) {
		message_chunk_length = 60;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (message_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(char) * message_length);
			high_level_callback->length = message_chunk_length;

			memcpy(high_level_callback->data, message_chunk_data, sizeof(char) * message_chunk_length);

			if (high_level_callback->length >= message_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (message_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((char *)high_level_callback->data)[high_level_callback->length], message_chunk_data, sizeof(char) * message_chunk_length);
			high_level_callback->length += message_chunk_length;

			if (high_level_callback->length >= message_length) { // stream complete
				if (callback_function != NULL) {
					callback_function((char *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_master_read_coils_response(DevicePrivate *device_p, uint8_t request_id, int8_t exception_code, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[464]) {
	ModbusMasterReadCoilsResponse_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE];
	uint16_t coils_chunk_length = coils_length - coils_chunk_offset;

	callback_function = (ModbusMasterReadCoilsResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE];

	if (coils_chunk_length > 464) {
		coils_chunk_length = 464;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (coils_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(bool) * coils_length);
			high_level_callback->length = coils_chunk_length;

			memcpy(high_level_callback->data, coils_chunk_data, sizeof(bool) * coils_chunk_length);

			if (high_level_callback->length >= coils_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (coils_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((bool *)high_level_callback->data)[high_level_callback->length], coils_chunk_data, sizeof(bool) * coils_chunk_length);
			high_level_callback->length += coils_chunk_length;

			if (high_level_callback->length >= coils_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_master_read_holding_registers_response(DevicePrivate *device_p, uint8_t request_id, int8_t exception_code, uint16_t holding_registers_length, uint16_t holding_registers_chunk_offset, uint16_t holding_registers_chunk_data[29]) {
	ModbusMasterReadHoldingRegistersResponse_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE];
	uint16_t holding_registers_chunk_length = holding_registers_length - holding_registers_chunk_offset;

	callback_function = (ModbusMasterReadHoldingRegistersResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE];

	if (holding_registers_chunk_length > 29) {
		holding_registers_chunk_length = 29;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (holding_registers_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint16_t) * holding_registers_length);
			high_level_callback->length = holding_registers_chunk_length;

			memcpy(high_level_callback->data, holding_registers_chunk_data, sizeof(uint16_t) * holding_registers_chunk_length);

			if (high_level_callback->length >= holding_registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (holding_registers_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint16_t *)high_level_callback->data)[high_level_callback->length], holding_registers_chunk_data, sizeof(uint16_t) * holding_registers_chunk_length);
			high_level_callback->length += holding_registers_chunk_length;

			if (high_level_callback->length >= holding_registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_slave_write_multiple_coils_request(DevicePrivate *device_p, uint8_t request_id, uint32_t starting_address, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[440]) {
	ModbusSlaveWriteMultipleCoilsRequest_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST];
	uint16_t coils_chunk_length = coils_length - coils_chunk_offset;

	callback_function = (ModbusSlaveWriteMultipleCoilsRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST];

	if (coils_chunk_length > 440) {
		coils_chunk_length = 440;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (coils_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(bool) * coils_length);
			high_level_callback->length = coils_chunk_length;

			memcpy(high_level_callback->data, coils_chunk_data, sizeof(bool) * coils_chunk_length);

			if (high_level_callback->length >= coils_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, starting_address, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (coils_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, starting_address, (bool *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((bool *)high_level_callback->data)[high_level_callback->length], coils_chunk_data, sizeof(bool) * coils_chunk_length);
			high_level_callback->length += coils_chunk_length;

			if (high_level_callback->length >= coils_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, starting_address, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_slave_write_multiple_registers_request(DevicePrivate *device_p, uint8_t request_id, uint32_t starting_address, uint16_t registers_length, uint16_t registers_chunk_offset, uint16_t registers_chunk_data[27]) {
	ModbusSlaveWriteMultipleRegistersRequest_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST];
	uint16_t registers_chunk_length = registers_length - registers_chunk_offset;

	callback_function = (ModbusSlaveWriteMultipleRegistersRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST];

	if (registers_chunk_length > 27) {
		registers_chunk_length = 27;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (registers_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint16_t) * registers_length);
			high_level_callback->length = registers_chunk_length;

			memcpy(high_level_callback->data, registers_chunk_data, sizeof(uint16_t) * registers_chunk_length);

			if (high_level_callback->length >= registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, starting_address, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (registers_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, starting_address, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint16_t *)high_level_callback->data)[high_level_callback->length], registers_chunk_data, sizeof(uint16_t) * registers_chunk_length);
			high_level_callback->length += registers_chunk_length;

			if (high_level_callback->length >= registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, starting_address, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_master_read_discrete_inputs_response(DevicePrivate *device_p, uint8_t request_id, int8_t exception_code, uint16_t discrete_inputs_length, uint16_t discrete_inputs_chunk_offset, bool discrete_inputs_chunk_data[464]) {
	ModbusMasterReadDiscreteInputsResponse_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE];
	uint16_t discrete_inputs_chunk_length = discrete_inputs_length - discrete_inputs_chunk_offset;

	callback_function = (ModbusMasterReadDiscreteInputsResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE];

	if (discrete_inputs_chunk_length > 464) {
		discrete_inputs_chunk_length = 464;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (discrete_inputs_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(bool) * discrete_inputs_length);
			high_level_callback->length = discrete_inputs_chunk_length;

			memcpy(high_level_callback->data, discrete_inputs_chunk_data, sizeof(bool) * discrete_inputs_chunk_length);

			if (high_level_callback->length >= discrete_inputs_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (discrete_inputs_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((bool *)high_level_callback->data)[high_level_callback->length], discrete_inputs_chunk_data, sizeof(bool) * discrete_inputs_chunk_length);
			high_level_callback->length += discrete_inputs_chunk_length;

			if (high_level_callback->length >= discrete_inputs_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (bool *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_modbus_master_read_input_registers_response(DevicePrivate *device_p, uint8_t request_id, int8_t exception_code, uint16_t input_registers_length, uint16_t input_registers_chunk_offset, uint16_t input_registers_chunk_data[29]) {
	ModbusMasterReadInputRegistersResponse_CallbackFunction callback_function;
	void *user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE];
	HighLevelCallback *high_level_callback = &device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE];
	uint16_t input_registers_chunk_length = input_registers_length - input_registers_chunk_offset;

	callback_function = (ModbusMasterReadInputRegistersResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE];

	if (input_registers_chunk_length > 29) {
		input_registers_chunk_length = 29;
	}

	if (high_level_callback->data == NULL) { // no stream in-progress
		if (input_registers_chunk_offset == 0) { // stream starts
			high_level_callback->data = malloc(sizeof(uint16_t) * input_registers_length);
			high_level_callback->length = input_registers_chunk_length;

			memcpy(high_level_callback->data, input_registers_chunk_data, sizeof(uint16_t) * input_registers_chunk_length);

			if (high_level_callback->length >= input_registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		} else { // ignore tail of current stream, wait for next stream start
		}
	} else { // stream in-progress
		if (input_registers_chunk_offset != high_level_callback->length) { // stream out-of-sync
			free(high_level_callback->data);
			high_level_callback->data = NULL;
			high_level_callback->length = 0;

			if (callback_function != NULL) {
				callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
			}
		} else { // stream in-sync
			memcpy(&((uint16_t *)high_level_callback->data)[high_level_callback->length], input_registers_chunk_data, sizeof(uint16_t) * input_registers_chunk_length);
			high_level_callback->length += input_registers_chunk_length;

			if (high_level_callback->length >= input_registers_length) { // stream complete
				if (callback_function != NULL) {
					callback_function(request_id, exception_code, (uint16_t *)high_level_callback->data, high_level_callback->length, user_data);
				}

				free(high_level_callback->data);
				high_level_callback->data = NULL;
				high_level_callback->length = 0;
			}
		}
	}
}

static void rs485_callback_wrapper_read_low_level(DevicePrivate *device_p, Packet *packet) {
	ReadLowLevel_CallbackFunction callback_function;
	void *user_data;
	ReadLowLevel_Callback *callback;

	if (packet->header.length != sizeof(ReadLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ReadLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_READ_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_READ_LOW_LEVEL];
	callback = (ReadLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->message_length = leconvert_uint16_from(callback->message_length);
	callback->message_chunk_offset = leconvert_uint16_from(callback->message_chunk_offset);

	rs485_callback_wrapper_read(device_p, callback->message_length, callback->message_chunk_offset, callback->message_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->message_length, callback->message_chunk_offset, callback->message_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_error_count(DevicePrivate *device_p, Packet *packet) {
	ErrorCount_CallbackFunction callback_function;
	void *user_data;
	ErrorCount_Callback *callback;

	if (packet->header.length != sizeof(ErrorCount_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ErrorCount_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_ERROR_COUNT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_ERROR_COUNT];
	callback = (ErrorCount_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->overrun_error_count = leconvert_uint32_from(callback->overrun_error_count);
	callback->parity_error_count = leconvert_uint32_from(callback->parity_error_count);

	callback_function(callback->overrun_error_count, callback->parity_error_count, user_data);
}

static void rs485_callback_wrapper_modbus_slave_read_coils_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveReadCoilsRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveReadCoilsRequest_Callback *callback;

	if (packet->header.length != sizeof(ModbusSlaveReadCoilsRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveReadCoilsRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_COILS_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_COILS_REQUEST];
	callback = (ModbusSlaveReadCoilsRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->count = leconvert_uint16_from(callback->count);

	callback_function(callback->request_id, callback->starting_address, callback->count, user_data);
}

static void rs485_callback_wrapper_modbus_master_read_coils_response_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterReadCoilsResponseLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterReadCoilsResponseLowLevel_Callback *callback;
	int i;
	bool unpacked_coils_chunk_data[464];

	if (packet->header.length != sizeof(ModbusMasterReadCoilsResponseLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterReadCoilsResponseLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE_LOW_LEVEL];
	callback = (ModbusMasterReadCoilsResponseLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->coils_length = leconvert_uint16_from(callback->coils_length);
	callback->coils_chunk_offset = leconvert_uint16_from(callback->coils_chunk_offset);
	for (i = 0; i < 464; i++) unpacked_coils_chunk_data[i] = (callback->coils_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	rs485_callback_wrapper_modbus_master_read_coils_response(device_p, callback->request_id, callback->exception_code, callback->coils_length, callback->coils_chunk_offset, unpacked_coils_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->exception_code, callback->coils_length, callback->coils_chunk_offset, unpacked_coils_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_modbus_slave_read_holding_registers_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveReadHoldingRegistersRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveReadHoldingRegistersRequest_Callback *callback;

	if (packet->header.length != sizeof(ModbusSlaveReadHoldingRegistersRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveReadHoldingRegistersRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_HOLDING_REGISTERS_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_HOLDING_REGISTERS_REQUEST];
	callback = (ModbusSlaveReadHoldingRegistersRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->count = leconvert_uint16_from(callback->count);

	callback_function(callback->request_id, callback->starting_address, callback->count, user_data);
}

static void rs485_callback_wrapper_modbus_master_read_holding_registers_response_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterReadHoldingRegistersResponseLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterReadHoldingRegistersResponseLowLevel_Callback *callback;
	int i;
	uint16_t aligned_holding_registers_chunk_data[29];


	if (packet->header.length != sizeof(ModbusMasterReadHoldingRegistersResponseLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterReadHoldingRegistersResponseLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE_LOW_LEVEL];
	callback = (ModbusMasterReadHoldingRegistersResponseLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->holding_registers_length = leconvert_uint16_from(callback->holding_registers_length);
	callback->holding_registers_chunk_offset = leconvert_uint16_from(callback->holding_registers_chunk_offset);
	for (i = 0; i < 29; i++) aligned_holding_registers_chunk_data[i] = leconvert_uint16_from(callback->holding_registers_chunk_data[i]);

	rs485_callback_wrapper_modbus_master_read_holding_registers_response(device_p, callback->request_id, callback->exception_code, callback->holding_registers_length, callback->holding_registers_chunk_offset, aligned_holding_registers_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->exception_code, callback->holding_registers_length, callback->holding_registers_chunk_offset, aligned_holding_registers_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_modbus_slave_write_single_coil_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveWriteSingleCoilRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveWriteSingleCoilRequest_Callback *callback;
	bool unpacked_coil_value;

	if (packet->header.length != sizeof(ModbusSlaveWriteSingleCoilRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveWriteSingleCoilRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_COIL_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_COIL_REQUEST];
	callback = (ModbusSlaveWriteSingleCoilRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->coil_address = leconvert_uint32_from(callback->coil_address);
	unpacked_coil_value = callback->coil_value != 0;

	callback_function(callback->request_id, callback->coil_address, unpacked_coil_value, user_data);
}

static void rs485_callback_wrapper_modbus_master_write_single_coil_response(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterWriteSingleCoilResponse_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterWriteSingleCoilResponse_Callback *callback;

	if (packet->header.length != sizeof(ModbusMasterWriteSingleCoilResponse_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterWriteSingleCoilResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_COIL_RESPONSE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_COIL_RESPONSE];
	callback = (ModbusMasterWriteSingleCoilResponse_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->request_id, callback->exception_code, user_data);
}

static void rs485_callback_wrapper_modbus_slave_write_single_register_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveWriteSingleRegisterRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveWriteSingleRegisterRequest_Callback *callback;

	if (packet->header.length != sizeof(ModbusSlaveWriteSingleRegisterRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveWriteSingleRegisterRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_REGISTER_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_REGISTER_REQUEST];
	callback = (ModbusSlaveWriteSingleRegisterRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->register_address = leconvert_uint32_from(callback->register_address);
	callback->register_value = leconvert_uint16_from(callback->register_value);

	callback_function(callback->request_id, callback->register_address, callback->register_value, user_data);
}

static void rs485_callback_wrapper_modbus_master_write_single_register_response(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterWriteSingleRegisterResponse_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterWriteSingleRegisterResponse_Callback *callback;

	if (packet->header.length != sizeof(ModbusMasterWriteSingleRegisterResponse_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterWriteSingleRegisterResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_REGISTER_RESPONSE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_REGISTER_RESPONSE];
	callback = (ModbusMasterWriteSingleRegisterResponse_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->request_id, callback->exception_code, user_data);
}

static void rs485_callback_wrapper_modbus_slave_write_multiple_coils_request_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveWriteMultipleCoilsRequestLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveWriteMultipleCoilsRequestLowLevel_Callback *callback;
	int i;
	bool unpacked_coils_chunk_data[440];

	if (packet->header.length != sizeof(ModbusSlaveWriteMultipleCoilsRequestLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveWriteMultipleCoilsRequestLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST_LOW_LEVEL];
	callback = (ModbusSlaveWriteMultipleCoilsRequestLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->coils_length = leconvert_uint16_from(callback->coils_length);
	callback->coils_chunk_offset = leconvert_uint16_from(callback->coils_chunk_offset);
	for (i = 0; i < 440; i++) unpacked_coils_chunk_data[i] = (callback->coils_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	rs485_callback_wrapper_modbus_slave_write_multiple_coils_request(device_p, callback->request_id, callback->starting_address, callback->coils_length, callback->coils_chunk_offset, unpacked_coils_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->starting_address, callback->coils_length, callback->coils_chunk_offset, unpacked_coils_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_modbus_master_write_multiple_coils_response(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterWriteMultipleCoilsResponse_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterWriteMultipleCoilsResponse_Callback *callback;

	if (packet->header.length != sizeof(ModbusMasterWriteMultipleCoilsResponse_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterWriteMultipleCoilsResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_COILS_RESPONSE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_COILS_RESPONSE];
	callback = (ModbusMasterWriteMultipleCoilsResponse_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->request_id, callback->exception_code, user_data);
}

static void rs485_callback_wrapper_modbus_slave_write_multiple_registers_request_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveWriteMultipleRegistersRequestLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveWriteMultipleRegistersRequestLowLevel_Callback *callback;
	int i;
	uint16_t aligned_registers_chunk_data[27];


	if (packet->header.length != sizeof(ModbusSlaveWriteMultipleRegistersRequestLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveWriteMultipleRegistersRequestLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST_LOW_LEVEL];
	callback = (ModbusSlaveWriteMultipleRegistersRequestLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->registers_length = leconvert_uint16_from(callback->registers_length);
	callback->registers_chunk_offset = leconvert_uint16_from(callback->registers_chunk_offset);
	for (i = 0; i < 27; i++) aligned_registers_chunk_data[i] = leconvert_uint16_from(callback->registers_chunk_data[i]);

	rs485_callback_wrapper_modbus_slave_write_multiple_registers_request(device_p, callback->request_id, callback->starting_address, callback->registers_length, callback->registers_chunk_offset, aligned_registers_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->starting_address, callback->registers_length, callback->registers_chunk_offset, aligned_registers_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_modbus_master_write_multiple_registers_response(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterWriteMultipleRegistersResponse_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterWriteMultipleRegistersResponse_Callback *callback;

	if (packet->header.length != sizeof(ModbusMasterWriteMultipleRegistersResponse_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterWriteMultipleRegistersResponse_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_REGISTERS_RESPONSE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_REGISTERS_RESPONSE];
	callback = (ModbusMasterWriteMultipleRegistersResponse_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->request_id, callback->exception_code, user_data);
}

static void rs485_callback_wrapper_modbus_slave_read_discrete_inputs_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveReadDiscreteInputsRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveReadDiscreteInputsRequest_Callback *callback;

	if (packet->header.length != sizeof(ModbusSlaveReadDiscreteInputsRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveReadDiscreteInputsRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_DISCRETE_INPUTS_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_DISCRETE_INPUTS_REQUEST];
	callback = (ModbusSlaveReadDiscreteInputsRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->count = leconvert_uint16_from(callback->count);

	callback_function(callback->request_id, callback->starting_address, callback->count, user_data);
}

static void rs485_callback_wrapper_modbus_master_read_discrete_inputs_response_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterReadDiscreteInputsResponseLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterReadDiscreteInputsResponseLowLevel_Callback *callback;
	int i;
	bool unpacked_discrete_inputs_chunk_data[464];

	if (packet->header.length != sizeof(ModbusMasterReadDiscreteInputsResponseLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterReadDiscreteInputsResponseLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE_LOW_LEVEL];
	callback = (ModbusMasterReadDiscreteInputsResponseLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->discrete_inputs_length = leconvert_uint16_from(callback->discrete_inputs_length);
	callback->discrete_inputs_chunk_offset = leconvert_uint16_from(callback->discrete_inputs_chunk_offset);
	for (i = 0; i < 464; i++) unpacked_discrete_inputs_chunk_data[i] = (callback->discrete_inputs_chunk_data[i / 8] & (1 << (i % 8))) != 0;

	rs485_callback_wrapper_modbus_master_read_discrete_inputs_response(device_p, callback->request_id, callback->exception_code, callback->discrete_inputs_length, callback->discrete_inputs_chunk_offset, unpacked_discrete_inputs_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->exception_code, callback->discrete_inputs_length, callback->discrete_inputs_chunk_offset, unpacked_discrete_inputs_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_modbus_slave_read_input_registers_request(DevicePrivate *device_p, Packet *packet) {
	ModbusSlaveReadInputRegistersRequest_CallbackFunction callback_function;
	void *user_data;
	ModbusSlaveReadInputRegistersRequest_Callback *callback;

	if (packet->header.length != sizeof(ModbusSlaveReadInputRegistersRequest_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusSlaveReadInputRegistersRequest_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_INPUT_REGISTERS_REQUEST];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_SLAVE_READ_INPUT_REGISTERS_REQUEST];
	callback = (ModbusSlaveReadInputRegistersRequest_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->starting_address = leconvert_uint32_from(callback->starting_address);
	callback->count = leconvert_uint16_from(callback->count);

	callback_function(callback->request_id, callback->starting_address, callback->count, user_data);
}

static void rs485_callback_wrapper_modbus_master_read_input_registers_response_low_level(DevicePrivate *device_p, Packet *packet) {
	ModbusMasterReadInputRegistersResponseLowLevel_CallbackFunction callback_function;
	void *user_data;
	ModbusMasterReadInputRegistersResponseLowLevel_Callback *callback;
	int i;
	uint16_t aligned_input_registers_chunk_data[29];


	if (packet->header.length != sizeof(ModbusMasterReadInputRegistersResponseLowLevel_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (ModbusMasterReadInputRegistersResponseLowLevel_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE_LOW_LEVEL];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE_LOW_LEVEL];
	callback = (ModbusMasterReadInputRegistersResponseLowLevel_Callback *)packet;
	(void)callback; // avoid unused variable warning


	callback->input_registers_length = leconvert_uint16_from(callback->input_registers_length);
	callback->input_registers_chunk_offset = leconvert_uint16_from(callback->input_registers_chunk_offset);
	for (i = 0; i < 29; i++) aligned_input_registers_chunk_data[i] = leconvert_uint16_from(callback->input_registers_chunk_data[i]);

	rs485_callback_wrapper_modbus_master_read_input_registers_response(device_p, callback->request_id, callback->exception_code, callback->input_registers_length, callback->input_registers_chunk_offset, aligned_input_registers_chunk_data);

	if (callback_function != NULL) {
		callback_function(callback->request_id, callback->exception_code, callback->input_registers_length, callback->input_registers_chunk_offset, aligned_input_registers_chunk_data, user_data);
	}
}

static void rs485_callback_wrapper_frame_readable(DevicePrivate *device_p, Packet *packet) {
	FrameReadable_CallbackFunction callback_function;
	void *user_data;
	FrameReadable_Callback *callback;

	if (packet->header.length != sizeof(FrameReadable_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (FrameReadable_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_FRAME_READABLE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + RS485_CALLBACK_FRAME_READABLE];
	callback = (FrameReadable_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->frame_count = leconvert_uint16_from(callback->frame_count);

	callback_function(callback->frame_count, user_data);
}

void rs485_create(RS485 *rs485, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(rs485, uid, ipcon_p, 2, 0, 1, RS485_DEVICE_IDENTIFIER);

	device_p = rs485->p;

	device_p->response_expected[RS485_FUNCTION_WRITE_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_READ_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_ENABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_DISABLE_READ_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_IS_READ_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_MODBUS_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_MODBUS_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_COMMUNICATION_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_ERROR_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_BUFFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_BUFFER_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_BUFFER_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_ENABLE_ERROR_COUNT_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_DISABLE_ERROR_COUNT_CALLBACK] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_IS_ERROR_COUNT_CALLBACK_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_MODBUS_COMMON_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_REPORT_EXCEPTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_COILS_REQUEST_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_READ_COILS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_HOLDING_REGISTERS_REQUEST_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_READ_HOLDING_REGISTERS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_SINGLE_COIL_REQUEST] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_WRITE_SINGLE_COIL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_SINGLE_REGISTER_REQUEST] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_WRITE_SINGLE_REGISTER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_MULTIPLE_COILS_REQUEST] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_WRITE_MULTIPLE_COILS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_MULTIPLE_REGISTERS_REQUEST] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_WRITE_MULTIPLE_REGISTERS_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_DISCRETE_INPUTS_REQUEST_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_READ_DISCRETE_INPUTS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_INPUT_REGISTERS_REQUEST_LOW_LEVEL] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_MODBUS_MASTER_READ_INPUT_REGISTERS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[RS485_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[RS485_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[RS485_CALLBACK_READ_LOW_LEVEL] = rs485_callback_wrapper_read_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_ERROR_COUNT] = rs485_callback_wrapper_error_count;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_READ_COILS_REQUEST] = rs485_callback_wrapper_modbus_slave_read_coils_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE_LOW_LEVEL] = rs485_callback_wrapper_modbus_master_read_coils_response_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_READ_HOLDING_REGISTERS_REQUEST] = rs485_callback_wrapper_modbus_slave_read_holding_registers_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE_LOW_LEVEL] = rs485_callback_wrapper_modbus_master_read_holding_registers_response_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_COIL_REQUEST] = rs485_callback_wrapper_modbus_slave_write_single_coil_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_COIL_RESPONSE] = rs485_callback_wrapper_modbus_master_write_single_coil_response;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_REGISTER_REQUEST] = rs485_callback_wrapper_modbus_slave_write_single_register_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_REGISTER_RESPONSE] = rs485_callback_wrapper_modbus_master_write_single_register_response;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST_LOW_LEVEL] = rs485_callback_wrapper_modbus_slave_write_multiple_coils_request_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_COILS_RESPONSE] = rs485_callback_wrapper_modbus_master_write_multiple_coils_response;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST_LOW_LEVEL] = rs485_callback_wrapper_modbus_slave_write_multiple_registers_request_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_WRITE_MULTIPLE_REGISTERS_RESPONSE] = rs485_callback_wrapper_modbus_master_write_multiple_registers_response;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_READ_DISCRETE_INPUTS_REQUEST] = rs485_callback_wrapper_modbus_slave_read_discrete_inputs_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE_LOW_LEVEL] = rs485_callback_wrapper_modbus_master_read_discrete_inputs_response_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_SLAVE_READ_INPUT_REGISTERS_REQUEST] = rs485_callback_wrapper_modbus_slave_read_input_registers_request;
	device_p->callback_wrappers[RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE_LOW_LEVEL] = rs485_callback_wrapper_modbus_master_read_input_registers_response_low_level;
	device_p->callback_wrappers[RS485_CALLBACK_FRAME_READABLE] = rs485_callback_wrapper_frame_readable;

	device_p->high_level_callbacks[-RS485_CALLBACK_READ].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_COILS_RESPONSE].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_HOLDING_REGISTERS_RESPONSE].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_COILS_REQUEST].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_SLAVE_WRITE_MULTIPLE_REGISTERS_REQUEST].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_DISCRETE_INPUTS_RESPONSE].exists = true;
	device_p->high_level_callbacks[-RS485_CALLBACK_MODBUS_MASTER_READ_INPUT_REGISTERS_RESPONSE].exists = true;
	ipcon_add_device(ipcon_p, device_p);
}

void rs485_destroy(RS485 *rs485) {
	device_release(rs485->p);
}

int rs485_get_response_expected(RS485 *rs485, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(rs485->p, function_id, ret_response_expected);
}

int rs485_set_response_expected(RS485 *rs485, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(rs485->p, function_id, response_expected);
}

int rs485_set_response_expected_all(RS485 *rs485, bool response_expected) {
	return device_set_response_expected_all(rs485->p, response_expected);
}

void rs485_register_callback(RS485 *rs485, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(rs485->p, callback_id, function, user_data);
}

int rs485_get_api_version(RS485 *rs485, uint8_t ret_api_version[3]) {
	return device_get_api_version(rs485->p, ret_api_version);
}

int rs485_write_low_level(RS485 *rs485, uint16_t message_length, uint16_t message_chunk_offset, char message_chunk_data[60], uint8_t *ret_message_chunk_written) {
	DevicePrivate *device_p = rs485->p;
	WriteLowLevel_Request request;
	WriteLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_WRITE_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.message_length = leconvert_uint16_to(message_length);
	request.message_chunk_offset = leconvert_uint16_to(message_chunk_offset);
	memcpy(request.message_chunk_data, message_chunk_data, 60 * sizeof(char));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_message_chunk_written = response.message_chunk_written;

	return ret;
}

int rs485_read_low_level(RS485 *rs485, uint16_t length, uint16_t *ret_message_length, uint16_t *ret_message_chunk_offset, char ret_message_chunk_data[60]) {
	DevicePrivate *device_p = rs485->p;
	ReadLowLevel_Request request;
	ReadLowLevel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_READ_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.length = leconvert_uint16_to(length);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_message_length = leconvert_uint16_from(response.message_length);
	*ret_message_chunk_offset = leconvert_uint16_from(response.message_chunk_offset);
	memcpy(ret_message_chunk_data, response.message_chunk_data, 60 * sizeof(char));

	return ret;
}

int rs485_enable_read_callback(RS485 *rs485) {
	DevicePrivate *device_p = rs485->p;
	EnableReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_ENABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_disable_read_callback(RS485 *rs485) {
	DevicePrivate *device_p = rs485->p;
	DisableReadCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_DISABLE_READ_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_is_read_callback_enabled(RS485 *rs485, bool *ret_enabled) {
	DevicePrivate *device_p = rs485->p;
	IsReadCallbackEnabled_Request request;
	IsReadCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_IS_READ_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int rs485_set_rs485_configuration(RS485 *rs485, uint32_t baudrate, uint8_t parity, uint8_t stopbits, uint8_t wordlength, uint8_t duplex) {
	DevicePrivate *device_p = rs485->p;
	SetRS485Configuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.baudrate = leconvert_uint32_to(baudrate);
	request.parity = parity;
	request.stopbits = stopbits;
	request.wordlength = wordlength;
	request.duplex = duplex;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_rs485_configuration(RS485 *rs485, uint32_t *ret_baudrate, uint8_t *ret_parity, uint8_t *ret_stopbits, uint8_t *ret_wordlength, uint8_t *ret_duplex) {
	DevicePrivate *device_p = rs485->p;
	GetRS485Configuration_Request request;
	GetRS485Configuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baudrate = leconvert_uint32_from(response.baudrate);
	*ret_parity = response.parity;
	*ret_stopbits = response.stopbits;
	*ret_wordlength = response.wordlength;
	*ret_duplex = response.duplex;

	return ret;
}

int rs485_set_modbus_configuration(RS485 *rs485, uint8_t slave_address, uint32_t master_request_timeout) {
	DevicePrivate *device_p = rs485->p;
	SetModbusConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_MODBUS_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.master_request_timeout = leconvert_uint32_to(master_request_timeout);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_modbus_configuration(RS485 *rs485, uint8_t *ret_slave_address, uint32_t *ret_master_request_timeout) {
	DevicePrivate *device_p = rs485->p;
	GetModbusConfiguration_Request request;
	GetModbusConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_MODBUS_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_slave_address = response.slave_address;
	*ret_master_request_timeout = leconvert_uint32_from(response.master_request_timeout);

	return ret;
}

int rs485_set_mode(RS485 *rs485, uint8_t mode) {
	DevicePrivate *device_p = rs485->p;
	SetMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_mode(RS485 *rs485, uint8_t *ret_mode) {
	DevicePrivate *device_p = rs485->p;
	GetMode_Request request;
	GetMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_MODE, device_p->ipcon_p, device_p);

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

int rs485_set_communication_led_config(RS485 *rs485, uint8_t config) {
	DevicePrivate *device_p = rs485->p;
	SetCommunicationLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_communication_led_config(RS485 *rs485, uint8_t *ret_config) {
	DevicePrivate *device_p = rs485->p;
	GetCommunicationLEDConfig_Request request;
	GetCommunicationLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_COMMUNICATION_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rs485_set_error_led_config(RS485 *rs485, uint8_t config) {
	DevicePrivate *device_p = rs485->p;
	SetErrorLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_error_led_config(RS485 *rs485, uint8_t *ret_config) {
	DevicePrivate *device_p = rs485->p;
	GetErrorLEDConfig_Request request;
	GetErrorLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_ERROR_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rs485_set_buffer_config(RS485 *rs485, uint16_t send_buffer_size, uint16_t receive_buffer_size) {
	DevicePrivate *device_p = rs485->p;
	SetBufferConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_BUFFER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.send_buffer_size = leconvert_uint16_to(send_buffer_size);
	request.receive_buffer_size = leconvert_uint16_to(receive_buffer_size);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_buffer_config(RS485 *rs485, uint16_t *ret_send_buffer_size, uint16_t *ret_receive_buffer_size) {
	DevicePrivate *device_p = rs485->p;
	GetBufferConfig_Request request;
	GetBufferConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_BUFFER_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_send_buffer_size = leconvert_uint16_from(response.send_buffer_size);
	*ret_receive_buffer_size = leconvert_uint16_from(response.receive_buffer_size);

	return ret;
}

int rs485_get_buffer_status(RS485 *rs485, uint16_t *ret_send_buffer_used, uint16_t *ret_receive_buffer_used) {
	DevicePrivate *device_p = rs485->p;
	GetBufferStatus_Request request;
	GetBufferStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_BUFFER_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_send_buffer_used = leconvert_uint16_from(response.send_buffer_used);
	*ret_receive_buffer_used = leconvert_uint16_from(response.receive_buffer_used);

	return ret;
}

int rs485_enable_error_count_callback(RS485 *rs485) {
	DevicePrivate *device_p = rs485->p;
	EnableErrorCountCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_ENABLE_ERROR_COUNT_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_disable_error_count_callback(RS485 *rs485) {
	DevicePrivate *device_p = rs485->p;
	DisableErrorCountCallback_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_DISABLE_ERROR_COUNT_CALLBACK, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_is_error_count_callback_enabled(RS485 *rs485, bool *ret_enabled) {
	DevicePrivate *device_p = rs485->p;
	IsErrorCountCallbackEnabled_Request request;
	IsErrorCountCallbackEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_IS_ERROR_COUNT_CALLBACK_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int rs485_get_error_count(RS485 *rs485, uint32_t *ret_overrun_error_count, uint32_t *ret_parity_error_count) {
	DevicePrivate *device_p = rs485->p;
	GetErrorCount_Request request;
	GetErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_overrun_error_count = leconvert_uint32_from(response.overrun_error_count);
	*ret_parity_error_count = leconvert_uint32_from(response.parity_error_count);

	return ret;
}

int rs485_get_modbus_common_error_count(RS485 *rs485, uint32_t *ret_timeout_error_count, uint32_t *ret_checksum_error_count, uint32_t *ret_frame_too_big_error_count, uint32_t *ret_illegal_function_error_count, uint32_t *ret_illegal_data_address_error_count, uint32_t *ret_illegal_data_value_error_count, uint32_t *ret_slave_device_failure_error_count) {
	DevicePrivate *device_p = rs485->p;
	GetModbusCommonErrorCount_Request request;
	GetModbusCommonErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_MODBUS_COMMON_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timeout_error_count = leconvert_uint32_from(response.timeout_error_count);
	*ret_checksum_error_count = leconvert_uint32_from(response.checksum_error_count);
	*ret_frame_too_big_error_count = leconvert_uint32_from(response.frame_too_big_error_count);
	*ret_illegal_function_error_count = leconvert_uint32_from(response.illegal_function_error_count);
	*ret_illegal_data_address_error_count = leconvert_uint32_from(response.illegal_data_address_error_count);
	*ret_illegal_data_value_error_count = leconvert_uint32_from(response.illegal_data_value_error_count);
	*ret_slave_device_failure_error_count = leconvert_uint32_from(response.slave_device_failure_error_count);

	return ret;
}

int rs485_modbus_slave_report_exception(RS485 *rs485, uint8_t request_id, int8_t exception_code) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveReportException_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_REPORT_EXCEPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;
	request.exception_code = exception_code;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_slave_answer_read_coils_request_low_level(RS485 *rs485, uint8_t request_id, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[472]) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerReadCoilsRequestLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_COILS_REQUEST_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;
	request.coils_length = leconvert_uint16_to(coils_length);
	request.coils_chunk_offset = leconvert_uint16_to(coils_chunk_offset);
	memset(request.coils_chunk_data, 0, 59); for (i = 0; i < 472; i++) request.coils_chunk_data[i / 8] |= (coils_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_read_coils(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t count, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterReadCoils_Request request;
	ModbusMasterReadCoils_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_READ_COILS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.count = leconvert_uint16_to(count);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_read_holding_registers_request_low_level(RS485 *rs485, uint8_t request_id, uint16_t holding_registers_length, uint16_t holding_registers_chunk_offset, uint16_t holding_registers_chunk_data[29]) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerReadHoldingRegistersRequestLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_HOLDING_REGISTERS_REQUEST_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;
	request.holding_registers_length = leconvert_uint16_to(holding_registers_length);
	request.holding_registers_chunk_offset = leconvert_uint16_to(holding_registers_chunk_offset);
	for (i = 0; i < 29; i++) request.holding_registers_chunk_data[i] = leconvert_uint16_to(holding_registers_chunk_data[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_read_holding_registers(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t count, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterReadHoldingRegisters_Request request;
	ModbusMasterReadHoldingRegisters_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_READ_HOLDING_REGISTERS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.count = leconvert_uint16_to(count);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_write_single_coil_request(RS485 *rs485, uint8_t request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerWriteSingleCoilRequest_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_SINGLE_COIL_REQUEST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_write_single_coil(RS485 *rs485, uint8_t slave_address, uint32_t coil_address, bool coil_value, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterWriteSingleCoil_Request request;
	ModbusMasterWriteSingleCoil_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_WRITE_SINGLE_COIL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.coil_address = leconvert_uint32_to(coil_address);
	request.coil_value = coil_value ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_write_single_register_request(RS485 *rs485, uint8_t request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerWriteSingleRegisterRequest_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_SINGLE_REGISTER_REQUEST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_write_single_register(RS485 *rs485, uint8_t slave_address, uint32_t register_address, uint16_t register_value, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterWriteSingleRegister_Request request;
	ModbusMasterWriteSingleRegister_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_WRITE_SINGLE_REGISTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.register_address = leconvert_uint32_to(register_address);
	request.register_value = leconvert_uint16_to(register_value);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_write_multiple_coils_request(RS485 *rs485, uint8_t request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerWriteMultipleCoilsRequest_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_MULTIPLE_COILS_REQUEST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_write_multiple_coils_low_level(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t coils_length, uint16_t coils_chunk_offset, bool coils_chunk_data[440], uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterWriteMultipleCoilsLowLevel_Request request;
	ModbusMasterWriteMultipleCoilsLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_WRITE_MULTIPLE_COILS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.coils_length = leconvert_uint16_to(coils_length);
	request.coils_chunk_offset = leconvert_uint16_to(coils_chunk_offset);
	memset(request.coils_chunk_data, 0, 55); for (i = 0; i < 440; i++) request.coils_chunk_data[i / 8] |= (coils_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_write_multiple_registers_request(RS485 *rs485, uint8_t request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerWriteMultipleRegistersRequest_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_WRITE_MULTIPLE_REGISTERS_REQUEST, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_write_multiple_registers_low_level(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t registers_length, uint16_t registers_chunk_offset, uint16_t registers_chunk_data[27], uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterWriteMultipleRegistersLowLevel_Request request;
	ModbusMasterWriteMultipleRegistersLowLevel_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_WRITE_MULTIPLE_REGISTERS_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.registers_length = leconvert_uint16_to(registers_length);
	request.registers_chunk_offset = leconvert_uint16_to(registers_chunk_offset);
	for (i = 0; i < 27; i++) request.registers_chunk_data[i] = leconvert_uint16_to(registers_chunk_data[i]);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_read_discrete_inputs_request_low_level(RS485 *rs485, uint8_t request_id, uint16_t discrete_inputs_length, uint16_t discrete_inputs_chunk_offset, bool discrete_inputs_chunk_data[472]) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerReadDiscreteInputsRequestLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_DISCRETE_INPUTS_REQUEST_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;
	request.discrete_inputs_length = leconvert_uint16_to(discrete_inputs_length);
	request.discrete_inputs_chunk_offset = leconvert_uint16_to(discrete_inputs_chunk_offset);
	memset(request.discrete_inputs_chunk_data, 0, 59); for (i = 0; i < 472; i++) request.discrete_inputs_chunk_data[i / 8] |= (discrete_inputs_chunk_data[i] ? 1 : 0) << (i % 8);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_read_discrete_inputs(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t count, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterReadDiscreteInputs_Request request;
	ModbusMasterReadDiscreteInputs_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_READ_DISCRETE_INPUTS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.count = leconvert_uint16_to(count);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_modbus_slave_answer_read_input_registers_request_low_level(RS485 *rs485, uint8_t request_id, uint16_t input_registers_length, uint16_t input_registers_chunk_offset, uint16_t input_registers_chunk_data[29]) {
	DevicePrivate *device_p = rs485->p;
	ModbusSlaveAnswerReadInputRegistersRequestLowLevel_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_SLAVE_ANSWER_READ_INPUT_REGISTERS_REQUEST_LOW_LEVEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.request_id = request_id;
	request.input_registers_length = leconvert_uint16_to(input_registers_length);
	request.input_registers_chunk_offset = leconvert_uint16_to(input_registers_chunk_offset);
	for (i = 0; i < 29; i++) request.input_registers_chunk_data[i] = leconvert_uint16_to(input_registers_chunk_data[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_modbus_master_read_input_registers(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t count, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	ModbusMasterReadInputRegisters_Request request;
	ModbusMasterReadInputRegisters_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_MODBUS_MASTER_READ_INPUT_REGISTERS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.slave_address = slave_address;
	request.starting_address = leconvert_uint32_to(starting_address);
	request.count = leconvert_uint16_to(count);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_request_id = response.request_id;

	return ret;
}

int rs485_set_frame_readable_callback_configuration(RS485 *rs485, uint16_t frame_size) {
	DevicePrivate *device_p = rs485->p;
	SetFrameReadableCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frame_size = leconvert_uint16_to(frame_size);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_frame_readable_callback_configuration(RS485 *rs485, uint16_t *ret_frame_size) {
	DevicePrivate *device_p = rs485->p;
	GetFrameReadableCallbackConfiguration_Request request;
	GetFrameReadableCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frame_size = leconvert_uint16_from(response.frame_size);

	return ret;
}

int rs485_get_spitfp_error_count(RS485 *rs485, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = rs485->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

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

int rs485_set_bootloader_mode(RS485 *rs485, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = rs485->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rs485_get_bootloader_mode(RS485 *rs485, uint8_t *ret_mode) {
	DevicePrivate *device_p = rs485->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

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

int rs485_set_write_firmware_pointer(RS485 *rs485, uint32_t pointer) {
	DevicePrivate *device_p = rs485->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_write_firmware(RS485 *rs485, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = rs485->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

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

int rs485_set_status_led_config(RS485 *rs485, uint8_t config) {
	DevicePrivate *device_p = rs485->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_get_status_led_config(RS485 *rs485, uint8_t *ret_config) {
	DevicePrivate *device_p = rs485->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

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

int rs485_get_chip_temperature(RS485 *rs485, int16_t *ret_temperature) {
	DevicePrivate *device_p = rs485->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int rs485_reset(RS485 *rs485) {
	DevicePrivate *device_p = rs485->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_write_uid(RS485 *rs485, uint32_t uid) {
	DevicePrivate *device_p = rs485->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int rs485_read_uid(RS485 *rs485, uint32_t *ret_uid) {
	DevicePrivate *device_p = rs485->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

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

int rs485_get_identity(RS485 *rs485, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = rs485->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), RS485_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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

int rs485_write(RS485 *rs485, const char *message, uint16_t message_length, uint16_t *ret_message_written) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t message_chunk_offset = 0;
	char message_chunk_data[60];
	uint16_t message_chunk_length;
	uint8_t message_chunk_written;

	*ret_message_written = 0;

	if (message_length == 0) {
		memset(&message_chunk_data, 0, sizeof(char) * 60);

		ret = rs485_write_low_level(rs485, message_length, message_chunk_offset, message_chunk_data, &message_chunk_written);

		if (ret < 0) {
			return ret;
		}

		*ret_message_written = message_chunk_written;
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (message_chunk_offset < message_length) {
			message_chunk_length = message_length - message_chunk_offset;

			if (message_chunk_length > 60) {
				message_chunk_length = 60;
			}

			memcpy(message_chunk_data, &message[message_chunk_offset], sizeof(char) * message_chunk_length);
			memset(&message_chunk_data[message_chunk_length], 0, sizeof(char) * (60 - message_chunk_length));

			ret = rs485_write_low_level(rs485, message_length, message_chunk_offset, message_chunk_data, &message_chunk_written);

			if (ret < 0) {
				*ret_message_written = 0;

				break;
			}

			*ret_message_written += message_chunk_written;

			if (message_chunk_written < 60) {
				break; // either last chunk or short write
			}

			message_chunk_offset += 60;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_read(RS485 *rs485, uint16_t length, char *ret_message, uint16_t *ret_message_length) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t message_length = 0;
	uint16_t message_chunk_offset;
	char message_chunk_data[60];
	bool message_out_of_sync;
	uint16_t message_chunk_length;

	*ret_message_length = 0;

	mutex_lock(&device_p->stream_mutex);

	ret = rs485_read_low_level(rs485, length, &message_length, &message_chunk_offset, message_chunk_data);

	if (ret < 0) {
		goto unlock;
	}

	message_out_of_sync = message_chunk_offset != 0;

	if (!message_out_of_sync) {
		message_chunk_length = message_length - message_chunk_offset;

		if (message_chunk_length > 60) {
			message_chunk_length = 60;
		}

		memcpy(ret_message, message_chunk_data, sizeof(char) * message_chunk_length);
		*ret_message_length = message_chunk_length;

		while (*ret_message_length < message_length) {
			ret = rs485_read_low_level(rs485, length, &message_length, &message_chunk_offset, message_chunk_data);

			if (ret < 0) {
				goto unlock;
			}

			message_out_of_sync = message_chunk_offset != *ret_message_length;

			if (message_out_of_sync) {
				break;
			}

			message_chunk_length = message_length - message_chunk_offset;

			if (message_chunk_length > 60) {
				message_chunk_length = 60;
			}

			memcpy(&ret_message[*ret_message_length], message_chunk_data, sizeof(char) * message_chunk_length);
			*ret_message_length += message_chunk_length;
		}
	}

	if (message_out_of_sync) {
		*ret_message_length = 0; // return empty array

		// discard remaining stream to bring it back in-sync
		while (message_chunk_offset + 60 < message_length) {
			ret = rs485_read_low_level(rs485, length, &message_length, &message_chunk_offset, message_chunk_data);

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

int rs485_modbus_slave_answer_read_coils_request(RS485 *rs485, uint8_t request_id, bool *coils, uint16_t coils_length) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t coils_chunk_offset = 0;
	bool coils_chunk_data[472];
	uint16_t coils_chunk_length;

	if (coils_length == 0) {
		memset(&coils_chunk_data, 0, sizeof(bool) * 472);

		ret = rs485_modbus_slave_answer_read_coils_request_low_level(rs485, request_id, coils_length, coils_chunk_offset, coils_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (coils_chunk_offset < coils_length) {
			coils_chunk_length = coils_length - coils_chunk_offset;

			if (coils_chunk_length > 472) {
				coils_chunk_length = 472;
			}

			memcpy(coils_chunk_data, &coils[coils_chunk_offset], sizeof(bool) * coils_chunk_length);
			memset(&coils_chunk_data[coils_chunk_length], 0, sizeof(bool) * (472 - coils_chunk_length));

			ret = rs485_modbus_slave_answer_read_coils_request_low_level(rs485, request_id, coils_length, coils_chunk_offset, coils_chunk_data);

			if (ret < 0) {
				break;
			}

			coils_chunk_offset += 472;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_modbus_slave_answer_read_holding_registers_request(RS485 *rs485, uint8_t request_id, uint16_t *holding_registers, uint16_t holding_registers_length) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t holding_registers_chunk_offset = 0;
	uint16_t holding_registers_chunk_data[29];
	uint16_t holding_registers_chunk_length;

	if (holding_registers_length == 0) {
		memset(&holding_registers_chunk_data, 0, sizeof(uint16_t) * 29);

		ret = rs485_modbus_slave_answer_read_holding_registers_request_low_level(rs485, request_id, holding_registers_length, holding_registers_chunk_offset, holding_registers_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (holding_registers_chunk_offset < holding_registers_length) {
			holding_registers_chunk_length = holding_registers_length - holding_registers_chunk_offset;

			if (holding_registers_chunk_length > 29) {
				holding_registers_chunk_length = 29;
			}

			memcpy(holding_registers_chunk_data, &holding_registers[holding_registers_chunk_offset], sizeof(uint16_t) * holding_registers_chunk_length);
			memset(&holding_registers_chunk_data[holding_registers_chunk_length], 0, sizeof(uint16_t) * (29 - holding_registers_chunk_length));

			ret = rs485_modbus_slave_answer_read_holding_registers_request_low_level(rs485, request_id, holding_registers_length, holding_registers_chunk_offset, holding_registers_chunk_data);

			if (ret < 0) {
				break;
			}

			holding_registers_chunk_offset += 29;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_modbus_master_write_multiple_coils(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, bool *coils, uint16_t coils_length, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t coils_chunk_offset = 0;
	bool coils_chunk_data[440];
	uint16_t coils_chunk_length;

	if (coils_length == 0) {
		memset(&coils_chunk_data, 0, sizeof(bool) * 440);

		ret = rs485_modbus_master_write_multiple_coils_low_level(rs485, slave_address, starting_address, coils_length, coils_chunk_offset, coils_chunk_data, ret_request_id);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (coils_chunk_offset < coils_length) {
			coils_chunk_length = coils_length - coils_chunk_offset;

			if (coils_chunk_length > 440) {
				coils_chunk_length = 440;
			}

			memcpy(coils_chunk_data, &coils[coils_chunk_offset], sizeof(bool) * coils_chunk_length);
			memset(&coils_chunk_data[coils_chunk_length], 0, sizeof(bool) * (440 - coils_chunk_length));

			ret = rs485_modbus_master_write_multiple_coils_low_level(rs485, slave_address, starting_address, coils_length, coils_chunk_offset, coils_chunk_data, ret_request_id);

			if (ret < 0) {
				break;
			}

			coils_chunk_offset += 440;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_modbus_master_write_multiple_registers(RS485 *rs485, uint8_t slave_address, uint32_t starting_address, uint16_t *registers, uint16_t registers_length, uint8_t *ret_request_id) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t registers_chunk_offset = 0;
	uint16_t registers_chunk_data[27];
	uint16_t registers_chunk_length;

	if (registers_length == 0) {
		memset(&registers_chunk_data, 0, sizeof(uint16_t) * 27);

		ret = rs485_modbus_master_write_multiple_registers_low_level(rs485, slave_address, starting_address, registers_length, registers_chunk_offset, registers_chunk_data, ret_request_id);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (registers_chunk_offset < registers_length) {
			registers_chunk_length = registers_length - registers_chunk_offset;

			if (registers_chunk_length > 27) {
				registers_chunk_length = 27;
			}

			memcpy(registers_chunk_data, &registers[registers_chunk_offset], sizeof(uint16_t) * registers_chunk_length);
			memset(&registers_chunk_data[registers_chunk_length], 0, sizeof(uint16_t) * (27 - registers_chunk_length));

			ret = rs485_modbus_master_write_multiple_registers_low_level(rs485, slave_address, starting_address, registers_length, registers_chunk_offset, registers_chunk_data, ret_request_id);

			if (ret < 0) {
				break;
			}

			registers_chunk_offset += 27;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_modbus_slave_answer_read_discrete_inputs_request(RS485 *rs485, uint8_t request_id, bool *discrete_inputs, uint16_t discrete_inputs_length) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t discrete_inputs_chunk_offset = 0;
	bool discrete_inputs_chunk_data[472];
	uint16_t discrete_inputs_chunk_length;

	if (discrete_inputs_length == 0) {
		memset(&discrete_inputs_chunk_data, 0, sizeof(bool) * 472);

		ret = rs485_modbus_slave_answer_read_discrete_inputs_request_low_level(rs485, request_id, discrete_inputs_length, discrete_inputs_chunk_offset, discrete_inputs_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (discrete_inputs_chunk_offset < discrete_inputs_length) {
			discrete_inputs_chunk_length = discrete_inputs_length - discrete_inputs_chunk_offset;

			if (discrete_inputs_chunk_length > 472) {
				discrete_inputs_chunk_length = 472;
			}

			memcpy(discrete_inputs_chunk_data, &discrete_inputs[discrete_inputs_chunk_offset], sizeof(bool) * discrete_inputs_chunk_length);
			memset(&discrete_inputs_chunk_data[discrete_inputs_chunk_length], 0, sizeof(bool) * (472 - discrete_inputs_chunk_length));

			ret = rs485_modbus_slave_answer_read_discrete_inputs_request_low_level(rs485, request_id, discrete_inputs_length, discrete_inputs_chunk_offset, discrete_inputs_chunk_data);

			if (ret < 0) {
				break;
			}

			discrete_inputs_chunk_offset += 472;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

int rs485_modbus_slave_answer_read_input_registers_request(RS485 *rs485, uint8_t request_id, uint16_t *input_registers, uint16_t input_registers_length) {
	DevicePrivate *device_p = rs485->p;
	int ret = 0;
	uint16_t input_registers_chunk_offset = 0;
	uint16_t input_registers_chunk_data[29];
	uint16_t input_registers_chunk_length;

	if (input_registers_length == 0) {
		memset(&input_registers_chunk_data, 0, sizeof(uint16_t) * 29);

		ret = rs485_modbus_slave_answer_read_input_registers_request_low_level(rs485, request_id, input_registers_length, input_registers_chunk_offset, input_registers_chunk_data);
	} else {
		mutex_lock(&device_p->stream_mutex);

		while (input_registers_chunk_offset < input_registers_length) {
			input_registers_chunk_length = input_registers_length - input_registers_chunk_offset;

			if (input_registers_chunk_length > 29) {
				input_registers_chunk_length = 29;
			}

			memcpy(input_registers_chunk_data, &input_registers[input_registers_chunk_offset], sizeof(uint16_t) * input_registers_chunk_length);
			memset(&input_registers_chunk_data[input_registers_chunk_length], 0, sizeof(uint16_t) * (29 - input_registers_chunk_length));

			ret = rs485_modbus_slave_answer_read_input_registers_request_low_level(rs485, request_id, input_registers_length, input_registers_chunk_offset, input_registers_chunk_data);

			if (ret < 0) {
				break;
			}

			input_registers_chunk_offset += 29;
		}

		mutex_unlock(&device_p->stream_mutex);
	}

	return ret;
}

#ifdef __cplusplus
}
#endif
