#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_rs485.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your RS485 Bricklet

// Callback function for Modbus master write single register response callback
void cb_modbus_master_write_single_register_response(uint8_t request_id,
                                                     int8_t exception_code,
                                                     void *user_data) {
	uint8_t expected_request_id = *(uint8_t *)user_data;

	printf("Request ID: %u\n", request_id);
	printf("Exception Code: %d\n", exception_code);

	if (request_id != expected_request_id) {
		printf("Error: Unexpected request ID\n");
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

	// Set operating mode to Modbus RTU master
	rs485_set_mode(&rs485, RS485_MODE_MODBUS_MASTER_RTU);

	// Modbus specific configuration:
	// - slave address = 1 (unused in master mode)
	// - master request timeout = 1000ms
	rs485_set_modbus_configuration(&rs485, 1, 1000);

	// Register Modbus master write single register response callback to function
	// cb_modbus_master_write_single_register_response
	uint8_t expected_request_id = 0;
	rs485_register_callback(&rs485,
	                        RS485_CALLBACK_MODBUS_MASTER_WRITE_SINGLE_REGISTER_RESPONSE,
	                        (void (*)(void))cb_modbus_master_write_single_register_response,
	                        (void *)&expected_request_id);

	// Write 65535 to register 42 of slave 17
	rs485_modbus_master_write_single_register(&rs485, 17, 42, 65535, &expected_request_id);

	printf("Press key to exit\n");
	getchar();
	rs485_destroy(&rs485);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
