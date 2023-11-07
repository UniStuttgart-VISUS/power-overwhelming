#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rs485.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RS485 Bricklet

// Callback function for Modbus slave write single register request callback
void cb_modbus_slave_write_single_register_request(uint8_t request_id,
                                                   uint32_t register_address,
                                                   uint16_t register_value,
                                                   void *user_data) {
	RS485 *rs485 = (RS485 *)user_data;

	printf("Request ID: %d\n", request_id);
	printf("Register Address: %d\n", register_address);
	printf("Register Value: %d\n", register_value);

	if (register_address != 42) {
		printf("Error: Invalid register address\n");
		rs485_modbus_slave_report_exception(rs485, request_id, RS485_EXCEPTION_CODE_ILLEGAL_DATA_ADDRESS);
	} else {
		rs485_modbus_slave_answer_write_single_register_request(rs485, request_id);
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RS485 rs485;
	rs485_create(&rs485, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Set operating mode to Modbus RTU slave
	rs485_set_mode(&rs485, RS485_MODE_MODBUS_SLAVE_RTU);

	// Modbus specific configuration:
	// - slave address = 17
	// - master request timeout = 0ms (unused in slave mode)
	rs485_set_modbus_configuration(&rs485, 17, 0);

	// Register Modbus slave write single register request callback to function
	// cb_modbus_slave_write_single_register_request
	rs485_register_callback(&rs485,
	                        RS485_CALLBACK_MODBUS_SLAVE_WRITE_SINGLE_REGISTER_REQUEST,
	                        (void (*)(void))cb_modbus_slave_write_single_register_request,
	                        (void *)&rs485);

	printf("Press key to exit\n");
	getchar();
	rs485_destroy(&rs485);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
