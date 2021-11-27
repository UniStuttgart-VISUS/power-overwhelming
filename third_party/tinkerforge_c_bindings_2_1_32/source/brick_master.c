/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "brick_master.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*StackCurrent_CallbackFunction)(uint16_t current, void *user_data);

typedef void (*StackVoltage_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*USBVoltage_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*StackCurrentReached_CallbackFunction)(uint16_t current, void *user_data);

typedef void (*StackVoltageReached_CallbackFunction)(uint16_t voltage, void *user_data);

typedef void (*USBVoltageReached_CallbackFunction)(uint16_t voltage, void *user_data);

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
} ATTRIBUTE_PACKED GetStackVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetStackVoltage_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrent_Request;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED GetStackCurrent_Response;

typedef struct {
	PacketHeader header;
	uint8_t extension;
	uint32_t exttype;
} ATTRIBUTE_PACKED SetExtensionType_Request;

typedef struct {
	PacketHeader header;
	uint8_t extension;
} ATTRIBUTE_PACKED GetExtensionType_Request;

typedef struct {
	PacketHeader header;
	uint32_t exttype;
} ATTRIBUTE_PACKED GetExtensionType_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsChibiPresent_Request;

typedef struct {
	PacketHeader header;
	uint8_t present;
} ATTRIBUTE_PACKED IsChibiPresent_Response;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiAddress_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiAddress_Response;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiMasterAddress_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiMasterAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiMasterAddress_Response;

typedef struct {
	PacketHeader header;
	uint8_t num;
	uint8_t address;
} ATTRIBUTE_PACKED SetChibiSlaveAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t num;
} ATTRIBUTE_PACKED GetChibiSlaveAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetChibiSlaveAddress_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiSignalStrength_Request;

typedef struct {
	PacketHeader header;
	uint8_t signal_strength;
} ATTRIBUTE_PACKED GetChibiSignalStrength_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiErrorLog_Request;

typedef struct {
	PacketHeader header;
	uint16_t underrun;
	uint16_t crc_error;
	uint16_t no_ack;
	uint16_t overflow;
} ATTRIBUTE_PACKED GetChibiErrorLog_Response;

typedef struct {
	PacketHeader header;
	uint8_t frequency;
} ATTRIBUTE_PACKED SetChibiFrequency_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiFrequency_Request;

typedef struct {
	PacketHeader header;
	uint8_t frequency;
} ATTRIBUTE_PACKED GetChibiFrequency_Response;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED SetChibiChannel_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChibiChannel_Request;

typedef struct {
	PacketHeader header;
	uint8_t channel;
} ATTRIBUTE_PACKED GetChibiChannel_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsRS485Present_Request;

typedef struct {
	PacketHeader header;
	uint8_t present;
} ATTRIBUTE_PACKED IsRS485Present_Response;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED SetRS485Address_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485Address_Request;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetRS485Address_Response;

typedef struct {
	PacketHeader header;
	uint8_t num;
	uint8_t address;
} ATTRIBUTE_PACKED SetRS485SlaveAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t num;
} ATTRIBUTE_PACKED GetRS485SlaveAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t address;
} ATTRIBUTE_PACKED GetRS485SlaveAddress_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485ErrorLog_Request;

typedef struct {
	PacketHeader header;
	uint16_t crc_error;
} ATTRIBUTE_PACKED GetRS485ErrorLog_Response;

typedef struct {
	PacketHeader header;
	uint32_t speed;
	char parity;
	uint8_t stopbits;
} ATTRIBUTE_PACKED SetRS485Configuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetRS485Configuration_Request;

typedef struct {
	PacketHeader header;
	uint32_t speed;
	char parity;
	uint8_t stopbits;
} ATTRIBUTE_PACKED GetRS485Configuration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsWifiPresent_Request;

typedef struct {
	PacketHeader header;
	uint8_t present;
} ATTRIBUTE_PACKED IsWifiPresent_Response;

typedef struct {
	PacketHeader header;
	char ssid[32];
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED SetWifiConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiConfiguration_Request;

typedef struct {
	PacketHeader header;
	char ssid[32];
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED GetWifiConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t encryption;
	char key[50];
	uint8_t key_index;
	uint8_t eap_options;
	uint16_t ca_certificate_length;
	uint16_t client_certificate_length;
	uint16_t private_key_length;
} ATTRIBUTE_PACKED SetWifiEncryption_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiEncryption_Request;

typedef struct {
	PacketHeader header;
	uint8_t encryption;
	char key[50];
	uint8_t key_index;
	uint8_t eap_options;
	uint16_t ca_certificate_length;
	uint16_t client_certificate_length;
	uint16_t private_key_length;
} ATTRIBUTE_PACKED GetWifiEncryption_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
	uint8_t bssid[6];
	uint8_t channel;
	int16_t rssi;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint32_t rx_count;
	uint32_t tx_count;
	uint8_t state;
} ATTRIBUTE_PACKED GetWifiStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED RefreshWifiStatus_Request;

typedef struct {
	PacketHeader header;
	uint16_t index;
	uint8_t data[32];
	uint8_t data_length;
} ATTRIBUTE_PACKED SetWifiCertificate_Request;

typedef struct {
	PacketHeader header;
	uint16_t index;
} ATTRIBUTE_PACKED GetWifiCertificate_Request;

typedef struct {
	PacketHeader header;
	uint8_t data[32];
	uint8_t data_length;
} ATTRIBUTE_PACKED GetWifiCertificate_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetWifiPowerMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiPowerMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetWifiPowerMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiBufferInfo_Request;

typedef struct {
	PacketHeader header;
	uint32_t overflow;
	uint16_t low_watermark;
	uint16_t used;
} ATTRIBUTE_PACKED GetWifiBufferInfo_Response;

typedef struct {
	PacketHeader header;
	uint8_t domain;
} ATTRIBUTE_PACKED SetWifiRegulatoryDomain_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiRegulatoryDomain_Request;

typedef struct {
	PacketHeader header;
	uint8_t domain;
} ATTRIBUTE_PACKED GetWifiRegulatoryDomain_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltage_Request;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED GetUSBVoltage_Response;

typedef struct {
	PacketHeader header;
	char key[64];
} ATTRIBUTE_PACKED SetLongWifiKey_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLongWifiKey_Request;

typedef struct {
	PacketHeader header;
	char key[64];
} ATTRIBUTE_PACKED GetLongWifiKey_Response;

typedef struct {
	PacketHeader header;
	char hostname[16];
} ATTRIBUTE_PACKED SetWifiHostname_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiHostname_Request;

typedef struct {
	PacketHeader header;
	char hostname[16];
} ATTRIBUTE_PACKED GetWifiHostname_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetStackCurrentCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrentCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetStackCurrentCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetStackVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetStackVoltageCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetUSBVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackPeriod_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetStackCurrentCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackCurrentCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetStackCurrentCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetStackVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStackVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetStackVoltageCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED SetUSBVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackThreshold_Request;

typedef struct {
	PacketHeader header;
	char option;
	uint16_t min;
	uint16_t max;
} ATTRIBUTE_PACKED GetUSBVoltageCallbackThreshold_Response;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED SetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetDebouncePeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t debounce;
} ATTRIBUTE_PACKED GetDebouncePeriod_Response;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED StackCurrent_Callback;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED StackVoltage_Callback;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED USBVoltage_Callback;

typedef struct {
	PacketHeader header;
	uint16_t current;
} ATTRIBUTE_PACKED StackCurrentReached_Callback;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED StackVoltageReached_Callback;

typedef struct {
	PacketHeader header;
	uint16_t voltage;
} ATTRIBUTE_PACKED USBVoltageReached_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsEthernetPresent_Request;

typedef struct {
	PacketHeader header;
	uint8_t present;
} ATTRIBUTE_PACKED IsEthernetPresent_Response;

typedef struct {
	PacketHeader header;
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED SetEthernetConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t connection;
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint16_t port;
} ATTRIBUTE_PACKED GetEthernetConfiguration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint32_t rx_count;
	uint32_t tx_count;
	char hostname[32];
} ATTRIBUTE_PACKED GetEthernetStatus_Response;

typedef struct {
	PacketHeader header;
	char hostname[32];
} ATTRIBUTE_PACKED SetEthernetHostname_Request;

typedef struct {
	PacketHeader header;
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED SetEthernetMACAddress_Request;

typedef struct {
	PacketHeader header;
	uint8_t sockets;
	uint16_t port;
} ATTRIBUTE_PACKED SetEthernetWebsocketConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetWebsocketConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t sockets;
	uint16_t port;
} ATTRIBUTE_PACKED GetEthernetWebsocketConfiguration_Response;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED SetEthernetAuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetEthernetAuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED GetEthernetAuthenticationSecret_Response;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED SetWifiAuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifiAuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED GetWifiAuthenticationSecret_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConnectionType_Request;

typedef struct {
	PacketHeader header;
	uint8_t connection_type;
} ATTRIBUTE_PACKED GetConnectionType_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsWifi2Present_Request;

typedef struct {
	PacketHeader header;
	uint8_t present;
} ATTRIBUTE_PACKED IsWifi2Present_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED StartWifi2Bootloader_Request;

typedef struct {
	PacketHeader header;
	int8_t result;
} ATTRIBUTE_PACKED StartWifi2Bootloader_Response;

typedef struct {
	PacketHeader header;
	uint8_t data[60];
	uint8_t length;
} ATTRIBUTE_PACKED WriteWifi2SerialPort_Request;

typedef struct {
	PacketHeader header;
	int8_t result;
} ATTRIBUTE_PACKED WriteWifi2SerialPort_Response;

typedef struct {
	PacketHeader header;
	uint8_t length;
} ATTRIBUTE_PACKED ReadWifi2SerialPort_Request;

typedef struct {
	PacketHeader header;
	uint8_t data[60];
	uint8_t result;
} ATTRIBUTE_PACKED ReadWifi2SerialPort_Response;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED SetWifi2AuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2AuthenticationSecret_Request;

typedef struct {
	PacketHeader header;
	char secret[64];
} ATTRIBUTE_PACKED GetWifi2AuthenticationSecret_Response;

typedef struct {
	PacketHeader header;
	uint16_t port;
	uint16_t websocket_port;
	uint16_t website_port;
	uint8_t phy_mode;
	uint8_t sleep_mode;
	uint8_t website;
} ATTRIBUTE_PACKED SetWifi2Configuration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2Configuration_Request;

typedef struct {
	PacketHeader header;
	uint16_t port;
	uint16_t websocket_port;
	uint16_t website_port;
	uint8_t phy_mode;
	uint8_t sleep_mode;
	uint8_t website;
} ATTRIBUTE_PACKED GetWifi2Configuration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2Status_Request;

typedef struct {
	PacketHeader header;
	uint8_t client_enabled;
	uint8_t client_status;
	uint8_t client_ip[4];
	uint8_t client_subnet_mask[4];
	uint8_t client_gateway[4];
	uint8_t client_mac_address[6];
	uint32_t client_rx_count;
	uint32_t client_tx_count;
	int8_t client_rssi;
	uint8_t ap_enabled;
	uint8_t ap_ip[4];
	uint8_t ap_subnet_mask[4];
	uint8_t ap_gateway[4];
	uint8_t ap_mac_address[6];
	uint32_t ap_rx_count;
	uint32_t ap_tx_count;
	uint8_t ap_connected_count;
} ATTRIBUTE_PACKED GetWifi2Status_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	char ssid[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t mac_address[6];
	uint8_t bssid[6];
} ATTRIBUTE_PACKED SetWifi2ClientConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2ClientConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	char ssid[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t mac_address[6];
	uint8_t bssid[6];
} ATTRIBUTE_PACKED GetWifi2ClientConfiguration_Response;

typedef struct {
	PacketHeader header;
	char hostname[32];
} ATTRIBUTE_PACKED SetWifi2ClientHostname_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2ClientHostname_Request;

typedef struct {
	PacketHeader header;
	char hostname[32];
} ATTRIBUTE_PACKED GetWifi2ClientHostname_Response;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED SetWifi2ClientPassword_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2ClientPassword_Request;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED GetWifi2ClientPassword_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	char ssid[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t encryption;
	uint8_t hidden;
	uint8_t channel;
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED SetWifi2APConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2APConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	char ssid[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t encryption;
	uint8_t hidden;
	uint8_t channel;
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED GetWifi2APConfiguration_Response;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED SetWifi2APPassword_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2APPassword_Request;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED GetWifi2APPassword_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED SaveWifi2Configuration_Request;

typedef struct {
	PacketHeader header;
	uint8_t result;
} ATTRIBUTE_PACKED SaveWifi2Configuration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2FirmwareVersion_Request;

typedef struct {
	PacketHeader header;
	uint8_t firmware_version[3];
} ATTRIBUTE_PACKED GetWifi2FirmwareVersion_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableWifi2StatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableWifi2StatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsWifi2StatusLEDEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsWifi2StatusLEDEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	uint8_t root_ip[4];
	uint8_t root_subnet_mask[4];
	uint8_t root_gateway[4];
	uint8_t router_bssid[6];
	uint8_t group_id[6];
	char group_ssid_prefix[16];
	uint8_t gateway_ip[4];
	uint16_t gateway_port;
} ATTRIBUTE_PACKED SetWifi2MeshConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable;
	uint8_t root_ip[4];
	uint8_t root_subnet_mask[4];
	uint8_t root_gateway[4];
	uint8_t router_bssid[6];
	uint8_t group_id[6];
	char group_ssid_prefix[16];
	uint8_t gateway_ip[4];
	uint16_t gateway_port;
} ATTRIBUTE_PACKED GetWifi2MeshConfiguration_Response;

typedef struct {
	PacketHeader header;
	char ssid[32];
} ATTRIBUTE_PACKED SetWifi2MeshRouterSSID_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshRouterSSID_Request;

typedef struct {
	PacketHeader header;
	char ssid[32];
} ATTRIBUTE_PACKED GetWifi2MeshRouterSSID_Response;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED SetWifi2MeshRouterPassword_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshRouterPassword_Request;

typedef struct {
	PacketHeader header;
	char password[64];
} ATTRIBUTE_PACKED GetWifi2MeshRouterPassword_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshCommonStatus_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
	uint8_t root_node;
	uint8_t root_candidate;
	uint16_t connected_nodes;
	uint32_t rx_count;
	uint32_t tx_count;
} ATTRIBUTE_PACKED GetWifi2MeshCommonStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshClientStatus_Request;

typedef struct {
	PacketHeader header;
	char hostname[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED GetWifi2MeshClientStatus_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetWifi2MeshAPStatus_Request;

typedef struct {
	PacketHeader header;
	char ssid[32];
	uint8_t ip[4];
	uint8_t subnet_mask[4];
	uint8_t gateway[4];
	uint8_t mac_address[6];
} ATTRIBUTE_PACKED GetWifi2MeshAPStatus_Response;

typedef struct {
	PacketHeader header;
	uint32_t config;
	uint32_t parameter1;
	uint32_t parameter2;
	uint8_t data[52];
} ATTRIBUTE_PACKED SetBrickletXMCFlashConfig_Request;

typedef struct {
	PacketHeader header;
	uint32_t return_value;
	uint8_t return_data[60];
} ATTRIBUTE_PACKED SetBrickletXMCFlashConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t data[64];
} ATTRIBUTE_PACKED SetBrickletXMCFlashData_Request;

typedef struct {
	PacketHeader header;
	uint32_t return_data;
} ATTRIBUTE_PACKED SetBrickletXMCFlashData_Response;

typedef struct {
	PacketHeader header;
	uint8_t bricklets_enabled;
} ATTRIBUTE_PACKED SetBrickletsEnabled_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBrickletsEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t bricklets_enabled;
} ATTRIBUTE_PACKED GetBrickletsEnabled_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t communication_method;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t timeout_count;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
	uint32_t baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	char bricklet_port;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
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
} ATTRIBUTE_PACKED EnableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Response;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Request;

typedef struct {
	PacketHeader header;
	uint8_t protocol_version;
	uint8_t firmware_version[3];
	char name[40];
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Response;

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
	char port;
	uint8_t offset;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED WriteBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t offset;
} ATTRIBUTE_PACKED ReadBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED ReadBrickletPlugin_Response;

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

static void master_callback_wrapper_stack_current(DevicePrivate *device_p, Packet *packet) {
	StackCurrent_CallbackFunction callback_function;
	void *user_data;
	StackCurrent_Callback *callback;

	if (packet->header.length != sizeof(StackCurrent_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StackCurrent_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_CURRENT];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_CURRENT];
	callback = (StackCurrent_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_uint16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void master_callback_wrapper_stack_voltage(DevicePrivate *device_p, Packet *packet) {
	StackVoltage_CallbackFunction callback_function;
	void *user_data;
	StackVoltage_Callback *callback;

	if (packet->header.length != sizeof(StackVoltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StackVoltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_VOLTAGE];
	callback = (StackVoltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_usb_voltage(DevicePrivate *device_p, Packet *packet) {
	USBVoltage_CallbackFunction callback_function;
	void *user_data;
	USBVoltage_Callback *callback;

	if (packet->header.length != sizeof(USBVoltage_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (USBVoltage_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_USB_VOLTAGE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_USB_VOLTAGE];
	callback = (USBVoltage_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_stack_current_reached(DevicePrivate *device_p, Packet *packet) {
	StackCurrentReached_CallbackFunction callback_function;
	void *user_data;
	StackCurrentReached_Callback *callback;

	if (packet->header.length != sizeof(StackCurrentReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StackCurrentReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_CURRENT_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_CURRENT_REACHED];
	callback = (StackCurrentReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->current = leconvert_uint16_from(callback->current);

	callback_function(callback->current, user_data);
}

static void master_callback_wrapper_stack_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	StackVoltageReached_CallbackFunction callback_function;
	void *user_data;
	StackVoltageReached_Callback *callback;

	if (packet->header.length != sizeof(StackVoltageReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (StackVoltageReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_VOLTAGE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_STACK_VOLTAGE_REACHED];
	callback = (StackVoltageReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

static void master_callback_wrapper_usb_voltage_reached(DevicePrivate *device_p, Packet *packet) {
	USBVoltageReached_CallbackFunction callback_function;
	void *user_data;
	USBVoltageReached_Callback *callback;

	if (packet->header.length != sizeof(USBVoltageReached_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (USBVoltageReached_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_USB_VOLTAGE_REACHED];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + MASTER_CALLBACK_USB_VOLTAGE_REACHED];
	callback = (USBVoltageReached_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->voltage = leconvert_uint16_from(callback->voltage);

	callback_function(callback->voltage, user_data);
}

void master_create(Master *master, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(master, uid, ipcon_p, 2, 0, 10, MASTER_DEVICE_IDENTIFIER);

	device_p = master->p;

	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_EXTENSION_TYPE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_EXTENSION_TYPE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_CHIBI_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_ERROR_LOG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_FREQUENCY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_CHIBI_CHANNEL] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIBI_CHANNEL] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_RS485_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_ERROR_LOG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_RS485_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_WIFI_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_ENCRYPTION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_ENCRYPTION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_REFRESH_WIFI_STATUS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_CERTIFICATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_CERTIFICATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_POWER_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_POWER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_BUFFER_INFO] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_LONG_WIFI_KEY] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_LONG_WIFI_KEY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_DEBOUNCE_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_ETHERNET_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_WEBSOCKET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_WEBSOCKET_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_ETHERNET_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_ETHERNET_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CONNECTION_TYPE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_IS_WIFI2_PRESENT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_START_WIFI2_BOOTLOADER] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_WRITE_WIFI2_SERIAL_PORT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_READ_WIFI2_SERIAL_PORT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_AUTHENTICATION_SECRET] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_CLIENT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_CLIENT_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_CLIENT_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_CLIENT_HOSTNAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_CLIENT_PASSWORD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_CLIENT_PASSWORD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_AP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_AP_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_AP_PASSWORD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_AP_PASSWORD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SAVE_WIFI2_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_FIRMWARE_VERSION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_ENABLE_WIFI2_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_DISABLE_WIFI2_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_IS_WIFI2_STATUS_LED_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_MESH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_SSID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_SSID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_PASSWORD] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_PASSWORD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_COMMON_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_CLIENT_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_WIFI2_MESH_AP_STATUS] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_BRICKLETS_ENABLED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_BRICKLETS_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_SEND_TIMEOUT_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_SET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_GET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_ENABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_DISABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_IS_STATUS_LED_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_WRITE_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[MASTER_FUNCTION_READ_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[MASTER_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[MASTER_CALLBACK_STACK_CURRENT] = master_callback_wrapper_stack_current;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_VOLTAGE] = master_callback_wrapper_stack_voltage;
	device_p->callback_wrappers[MASTER_CALLBACK_USB_VOLTAGE] = master_callback_wrapper_usb_voltage;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_CURRENT_REACHED] = master_callback_wrapper_stack_current_reached;
	device_p->callback_wrappers[MASTER_CALLBACK_STACK_VOLTAGE_REACHED] = master_callback_wrapper_stack_voltage_reached;
	device_p->callback_wrappers[MASTER_CALLBACK_USB_VOLTAGE_REACHED] = master_callback_wrapper_usb_voltage_reached;

	ipcon_add_device(ipcon_p, device_p);
}

void master_destroy(Master *master) {
	device_release(master->p);
}

int master_get_response_expected(Master *master, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(master->p, function_id, ret_response_expected);
}

int master_set_response_expected(Master *master, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(master->p, function_id, response_expected);
}

int master_set_response_expected_all(Master *master, bool response_expected) {
	return device_set_response_expected_all(master->p, response_expected);
}

void master_register_callback(Master *master, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(master->p, callback_id, function, user_data);
}

int master_get_api_version(Master *master, uint8_t ret_api_version[3]) {
	return device_get_api_version(master->p, ret_api_version);
}

int master_get_stack_voltage(Master *master, uint16_t *ret_voltage) {
	DevicePrivate *device_p = master->p;
	GetStackVoltage_Request request;
	GetStackVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_uint16_from(response.voltage);

	return ret;
}

int master_get_stack_current(Master *master, uint16_t *ret_current) {
	DevicePrivate *device_p = master->p;
	GetStackCurrent_Request request;
	GetStackCurrent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_current = leconvert_uint16_from(response.current);

	return ret;
}

int master_set_extension_type(Master *master, uint8_t extension, uint32_t exttype) {
	DevicePrivate *device_p = master->p;
	SetExtensionType_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_EXTENSION_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.extension = extension;
	request.exttype = leconvert_uint32_to(exttype);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_extension_type(Master *master, uint8_t extension, uint32_t *ret_exttype) {
	DevicePrivate *device_p = master->p;
	GetExtensionType_Request request;
	GetExtensionType_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_EXTENSION_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.extension = extension;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_exttype = leconvert_uint32_from(response.exttype);

	return ret;
}

int master_is_chibi_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsChibiPresent_Request request;
	IsChibiPresent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_CHIBI_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_present = response.present != 0;

	return ret;
}

int master_set_chibi_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiAddress_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_chibi_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiAddress_Request request;
	GetChibiAddress_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = response.address;

	return ret;
}

int master_set_chibi_master_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiMasterAddress_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_chibi_master_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiMasterAddress_Request request;
	GetChibiMasterAddress_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = response.address;

	return ret;
}

int master_set_chibi_slave_address(Master *master, uint8_t num, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetChibiSlaveAddress_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;
	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_chibi_slave_address(Master *master, uint8_t num, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetChibiSlaveAddress_Request request;
	GetChibiSlaveAddress_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = response.address;

	return ret;
}

int master_get_chibi_signal_strength(Master *master, uint8_t *ret_signal_strength) {
	DevicePrivate *device_p = master->p;
	GetChibiSignalStrength_Request request;
	GetChibiSignalStrength_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_signal_strength = response.signal_strength;

	return ret;
}

int master_get_chibi_error_log(Master *master, uint16_t *ret_underrun, uint16_t *ret_crc_error, uint16_t *ret_no_ack, uint16_t *ret_overflow) {
	DevicePrivate *device_p = master->p;
	GetChibiErrorLog_Request request;
	GetChibiErrorLog_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_ERROR_LOG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_underrun = leconvert_uint16_from(response.underrun);
	*ret_crc_error = leconvert_uint16_from(response.crc_error);
	*ret_no_ack = leconvert_uint16_from(response.no_ack);
	*ret_overflow = leconvert_uint16_from(response.overflow);

	return ret;
}

int master_set_chibi_frequency(Master *master, uint8_t frequency) {
	DevicePrivate *device_p = master->p;
	SetChibiFrequency_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.frequency = frequency;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_chibi_frequency(Master *master, uint8_t *ret_frequency) {
	DevicePrivate *device_p = master->p;
	GetChibiFrequency_Request request;
	GetChibiFrequency_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_FREQUENCY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_frequency = response.frequency;

	return ret;
}

int master_set_chibi_channel(Master *master, uint8_t channel) {
	DevicePrivate *device_p = master->p;
	SetChibiChannel_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_CHIBI_CHANNEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.channel = channel;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_chibi_channel(Master *master, uint8_t *ret_channel) {
	DevicePrivate *device_p = master->p;
	GetChibiChannel_Request request;
	GetChibiChannel_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIBI_CHANNEL, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_channel = response.channel;

	return ret;
}

int master_is_rs485_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsRS485Present_Request request;
	IsRS485Present_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_RS485_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_present = response.present != 0;

	return ret;
}

int master_set_rs485_address(Master *master, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetRS485Address_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_rs485_address(Master *master, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetRS485Address_Request request;
	GetRS485Address_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = response.address;

	return ret;
}

int master_set_rs485_slave_address(Master *master, uint8_t num, uint8_t address) {
	DevicePrivate *device_p = master->p;
	SetRS485SlaveAddress_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;
	request.address = address;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_rs485_slave_address(Master *master, uint8_t num, uint8_t *ret_address) {
	DevicePrivate *device_p = master->p;
	GetRS485SlaveAddress_Request request;
	GetRS485SlaveAddress_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.num = num;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_address = response.address;

	return ret;
}

int master_get_rs485_error_log(Master *master, uint16_t *ret_crc_error) {
	DevicePrivate *device_p = master->p;
	GetRS485ErrorLog_Request request;
	GetRS485ErrorLog_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_ERROR_LOG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_crc_error = leconvert_uint16_from(response.crc_error);

	return ret;
}

int master_set_rs485_configuration(Master *master, uint32_t speed, char parity, uint8_t stopbits) {
	DevicePrivate *device_p = master->p;
	SetRS485Configuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.speed = leconvert_uint32_to(speed);
	request.parity = parity;
	request.stopbits = stopbits;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_rs485_configuration(Master *master, uint32_t *ret_speed, char *ret_parity, uint8_t *ret_stopbits) {
	DevicePrivate *device_p = master->p;
	GetRS485Configuration_Request request;
	GetRS485Configuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_RS485_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_speed = leconvert_uint32_from(response.speed);
	*ret_parity = response.parity;
	*ret_stopbits = response.stopbits;

	return ret;
}

int master_is_wifi_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsWifiPresent_Request request;
	IsWifiPresent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_WIFI_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_present = response.present != 0;

	return ret;
}

int master_set_wifi_configuration(Master *master, const char ssid[32], uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port) {
	DevicePrivate *device_p = master->p;
	SetWifiConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.ssid, ssid, 32);

	request.connection = connection;
	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	request.port = leconvert_uint16_to(port);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_configuration(Master *master, char ret_ssid[32], uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port) {
	DevicePrivate *device_p = master->p;
	GetWifiConfiguration_Request request;
	GetWifiConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_ssid, response.ssid, 32);
	*ret_connection = response.connection;
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_port = leconvert_uint16_from(response.port);

	return ret;
}

int master_set_wifi_encryption(Master *master, uint8_t encryption, const char key[50], uint8_t key_index, uint8_t eap_options, uint16_t ca_certificate_length, uint16_t client_certificate_length, uint16_t private_key_length) {
	DevicePrivate *device_p = master->p;
	SetWifiEncryption_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_ENCRYPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.encryption = encryption;
	memcpy(request.key, key, 50);

	request.key_index = key_index;
	request.eap_options = eap_options;
	request.ca_certificate_length = leconvert_uint16_to(ca_certificate_length);
	request.client_certificate_length = leconvert_uint16_to(client_certificate_length);
	request.private_key_length = leconvert_uint16_to(private_key_length);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_encryption(Master *master, uint8_t *ret_encryption, char ret_key[50], uint8_t *ret_key_index, uint8_t *ret_eap_options, uint16_t *ret_ca_certificate_length, uint16_t *ret_client_certificate_length, uint16_t *ret_private_key_length) {
	DevicePrivate *device_p = master->p;
	GetWifiEncryption_Request request;
	GetWifiEncryption_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_ENCRYPTION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_encryption = response.encryption;
	memcpy(ret_key, response.key, 50);
	*ret_key_index = response.key_index;
	*ret_eap_options = response.eap_options;
	*ret_ca_certificate_length = leconvert_uint16_from(response.ca_certificate_length);
	*ret_client_certificate_length = leconvert_uint16_from(response.client_certificate_length);
	*ret_private_key_length = leconvert_uint16_from(response.private_key_length);

	return ret;
}

int master_get_wifi_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_bssid[6], uint8_t *ret_channel, int16_t *ret_rssi, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, uint8_t *ret_state) {
	DevicePrivate *device_p = master->p;
	GetWifiStatus_Request request;
	GetWifiStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));
	memcpy(ret_bssid, response.bssid, 6 * sizeof(uint8_t));
	*ret_channel = response.channel;
	*ret_rssi = leconvert_int16_from(response.rssi);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_rx_count = leconvert_uint32_from(response.rx_count);
	*ret_tx_count = leconvert_uint32_from(response.tx_count);
	*ret_state = response.state;

	return ret;
}

int master_refresh_wifi_status(Master *master) {
	DevicePrivate *device_p = master->p;
	RefreshWifiStatus_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_REFRESH_WIFI_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_set_wifi_certificate(Master *master, uint16_t index, uint8_t data[32], uint8_t data_length) {
	DevicePrivate *device_p = master->p;
	SetWifiCertificate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_CERTIFICATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = leconvert_uint16_to(index);
	memcpy(request.data, data, 32 * sizeof(uint8_t));
	request.data_length = data_length;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_certificate(Master *master, uint16_t index, uint8_t ret_data[32], uint8_t *ret_data_length) {
	DevicePrivate *device_p = master->p;
	GetWifiCertificate_Request request;
	GetWifiCertificate_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_CERTIFICATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.index = leconvert_uint16_to(index);

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_data, response.data, 32 * sizeof(uint8_t));
	*ret_data_length = response.data_length;

	return ret;
}

int master_set_wifi_power_mode(Master *master, uint8_t mode) {
	DevicePrivate *device_p = master->p;
	SetWifiPowerMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_POWER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_power_mode(Master *master, uint8_t *ret_mode) {
	DevicePrivate *device_p = master->p;
	GetWifiPowerMode_Request request;
	GetWifiPowerMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_POWER_MODE, device_p->ipcon_p, device_p);

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

int master_get_wifi_buffer_info(Master *master, uint32_t *ret_overflow, uint16_t *ret_low_watermark, uint16_t *ret_used) {
	DevicePrivate *device_p = master->p;
	GetWifiBufferInfo_Request request;
	GetWifiBufferInfo_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_BUFFER_INFO, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_overflow = leconvert_uint32_from(response.overflow);
	*ret_low_watermark = leconvert_uint16_from(response.low_watermark);
	*ret_used = leconvert_uint16_from(response.used);

	return ret;
}

int master_set_wifi_regulatory_domain(Master *master, uint8_t domain) {
	DevicePrivate *device_p = master->p;
	SetWifiRegulatoryDomain_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.domain = domain;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_regulatory_domain(Master *master, uint8_t *ret_domain) {
	DevicePrivate *device_p = master->p;
	GetWifiRegulatoryDomain_Request request;
	GetWifiRegulatoryDomain_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_domain = response.domain;

	return ret;
}

int master_get_usb_voltage(Master *master, uint16_t *ret_voltage) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltage_Request request;
	GetUSBVoltage_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_voltage = leconvert_uint16_from(response.voltage);

	return ret;
}

int master_set_long_wifi_key(Master *master, const char key[64]) {
	DevicePrivate *device_p = master->p;
	SetLongWifiKey_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_LONG_WIFI_KEY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.key, key, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_long_wifi_key(Master *master, char ret_key[64]) {
	DevicePrivate *device_p = master->p;
	GetLongWifiKey_Request request;
	GetLongWifiKey_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_LONG_WIFI_KEY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_key, response.key, 64);

	return ret;
}

int master_set_wifi_hostname(Master *master, const char hostname[16]) {
	DevicePrivate *device_p = master->p;
	SetWifiHostname_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.hostname, hostname, 16);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_hostname(Master *master, char ret_hostname[16]) {
	DevicePrivate *device_p = master->p;
	GetWifiHostname_Request request;
	GetWifiHostname_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_hostname, response.hostname, 16);

	return ret;
}

int master_set_stack_current_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetStackCurrentCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_stack_current_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetStackCurrentCallbackPeriod_Request request;
	GetStackCurrentCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_stack_voltage_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetStackVoltageCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_stack_voltage_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetStackVoltageCallbackPeriod_Request request;
	GetStackVoltageCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_usb_voltage_callback_period(Master *master, uint32_t period) {
	DevicePrivate *device_p = master->p;
	SetUSBVoltageCallbackPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_usb_voltage_callback_period(Master *master, uint32_t *ret_period) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltageCallbackPeriod_Request request;
	GetUSBVoltageCallbackPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD, device_p->ipcon_p, device_p);

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

int master_set_stack_current_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetStackCurrentCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_stack_current_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetStackCurrentCallbackThreshold_Request request;
	GetStackCurrentCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int master_set_stack_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetStackVoltageCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_stack_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetStackVoltageCallbackThreshold_Request request;
	GetStackVoltageCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int master_set_usb_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max) {
	DevicePrivate *device_p = master->p;
	SetUSBVoltageCallbackThreshold_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.option = option;
	request.min = leconvert_uint16_to(min);
	request.max = leconvert_uint16_to(max);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_usb_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max) {
	DevicePrivate *device_p = master->p;
	GetUSBVoltageCallbackThreshold_Request request;
	GetUSBVoltageCallbackThreshold_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_option = response.option;
	*ret_min = leconvert_uint16_from(response.min);
	*ret_max = leconvert_uint16_from(response.max);

	return ret;
}

int master_set_debounce_period(Master *master, uint32_t debounce) {
	DevicePrivate *device_p = master->p;
	SetDebouncePeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.debounce = leconvert_uint32_to(debounce);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_debounce_period(Master *master, uint32_t *ret_debounce) {
	DevicePrivate *device_p = master->p;
	GetDebouncePeriod_Request request;
	GetDebouncePeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_DEBOUNCE_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_debounce = leconvert_uint32_from(response.debounce);

	return ret;
}

int master_is_ethernet_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsEthernetPresent_Request request;
	IsEthernetPresent_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_ETHERNET_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_present = response.present != 0;

	return ret;
}

int master_set_ethernet_configuration(Master *master, uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port) {
	DevicePrivate *device_p = master->p;
	SetEthernetConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.connection = connection;
	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	request.port = leconvert_uint16_to(port);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_ethernet_configuration(Master *master, uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port) {
	DevicePrivate *device_p = master->p;
	GetEthernetConfiguration_Request request;
	GetEthernetConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_connection = response.connection;
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_port = leconvert_uint16_from(response.port);

	return ret;
}

int master_get_ethernet_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, char ret_hostname[32]) {
	DevicePrivate *device_p = master->p;
	GetEthernetStatus_Request request;
	GetEthernetStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_rx_count = leconvert_uint32_from(response.rx_count);
	*ret_tx_count = leconvert_uint32_from(response.tx_count);
	memcpy(ret_hostname, response.hostname, 32);

	return ret;
}

int master_set_ethernet_hostname(Master *master, const char hostname[32]) {
	DevicePrivate *device_p = master->p;
	SetEthernetHostname_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.hostname, hostname, 32);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_set_ethernet_mac_address(Master *master, uint8_t mac_address[6]) {
	DevicePrivate *device_p = master->p;
	SetEthernetMACAddress_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.mac_address, mac_address, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_set_ethernet_websocket_configuration(Master *master, uint8_t sockets, uint16_t port) {
	DevicePrivate *device_p = master->p;
	SetEthernetWebsocketConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_WEBSOCKET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.sockets = sockets;
	request.port = leconvert_uint16_to(port);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_ethernet_websocket_configuration(Master *master, uint8_t *ret_sockets, uint16_t *ret_port) {
	DevicePrivate *device_p = master->p;
	GetEthernetWebsocketConfiguration_Request request;
	GetEthernetWebsocketConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_WEBSOCKET_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_sockets = response.sockets;
	*ret_port = leconvert_uint16_from(response.port);

	return ret;
}

int master_set_ethernet_authentication_secret(Master *master, const char secret[64]) {
	DevicePrivate *device_p = master->p;
	SetEthernetAuthenticationSecret_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_ETHERNET_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.secret, secret, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_ethernet_authentication_secret(Master *master, char ret_secret[64]) {
	DevicePrivate *device_p = master->p;
	GetEthernetAuthenticationSecret_Request request;
	GetEthernetAuthenticationSecret_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_ETHERNET_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_secret, response.secret, 64);

	return ret;
}

int master_set_wifi_authentication_secret(Master *master, const char secret[64]) {
	DevicePrivate *device_p = master->p;
	SetWifiAuthenticationSecret_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.secret, secret, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi_authentication_secret(Master *master, char ret_secret[64]) {
	DevicePrivate *device_p = master->p;
	GetWifiAuthenticationSecret_Request request;
	GetWifiAuthenticationSecret_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_secret, response.secret, 64);

	return ret;
}

int master_get_connection_type(Master *master, uint8_t *ret_connection_type) {
	DevicePrivate *device_p = master->p;
	GetConnectionType_Request request;
	GetConnectionType_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CONNECTION_TYPE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_connection_type = response.connection_type;

	return ret;
}

int master_is_wifi2_present(Master *master, bool *ret_present) {
	DevicePrivate *device_p = master->p;
	IsWifi2Present_Request request;
	IsWifi2Present_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_WIFI2_PRESENT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_present = response.present != 0;

	return ret;
}

int master_start_wifi2_bootloader(Master *master, int8_t *ret_result) {
	DevicePrivate *device_p = master->p;
	StartWifi2Bootloader_Request request;
	StartWifi2Bootloader_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_START_WIFI2_BOOTLOADER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_result = response.result;

	return ret;
}

int master_write_wifi2_serial_port(Master *master, uint8_t data[60], uint8_t length, int8_t *ret_result) {
	DevicePrivate *device_p = master->p;
	WriteWifi2SerialPort_Request request;
	WriteWifi2SerialPort_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_WRITE_WIFI2_SERIAL_PORT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 60 * sizeof(uint8_t));
	request.length = length;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_result = response.result;

	return ret;
}

int master_read_wifi2_serial_port(Master *master, uint8_t length, uint8_t ret_data[60], uint8_t *ret_result) {
	DevicePrivate *device_p = master->p;
	ReadWifi2SerialPort_Request request;
	ReadWifi2SerialPort_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_READ_WIFI2_SERIAL_PORT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.length = length;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_data, response.data, 60 * sizeof(uint8_t));
	*ret_result = response.result;

	return ret;
}

int master_set_wifi2_authentication_secret(Master *master, const char secret[64]) {
	DevicePrivate *device_p = master->p;
	SetWifi2AuthenticationSecret_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.secret, secret, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_authentication_secret(Master *master, char ret_secret[64]) {
	DevicePrivate *device_p = master->p;
	GetWifi2AuthenticationSecret_Request request;
	GetWifi2AuthenticationSecret_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_AUTHENTICATION_SECRET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_secret, response.secret, 64);

	return ret;
}

int master_set_wifi2_configuration(Master *master, uint16_t port, uint16_t websocket_port, uint16_t website_port, uint8_t phy_mode, uint8_t sleep_mode, uint8_t website) {
	DevicePrivate *device_p = master->p;
	SetWifi2Configuration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = leconvert_uint16_to(port);
	request.websocket_port = leconvert_uint16_to(websocket_port);
	request.website_port = leconvert_uint16_to(website_port);
	request.phy_mode = phy_mode;
	request.sleep_mode = sleep_mode;
	request.website = website;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_configuration(Master *master, uint16_t *ret_port, uint16_t *ret_websocket_port, uint16_t *ret_website_port, uint8_t *ret_phy_mode, uint8_t *ret_sleep_mode, uint8_t *ret_website) {
	DevicePrivate *device_p = master->p;
	GetWifi2Configuration_Request request;
	GetWifi2Configuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_port = leconvert_uint16_from(response.port);
	*ret_websocket_port = leconvert_uint16_from(response.websocket_port);
	*ret_website_port = leconvert_uint16_from(response.website_port);
	*ret_phy_mode = response.phy_mode;
	*ret_sleep_mode = response.sleep_mode;
	*ret_website = response.website;

	return ret;
}

int master_get_wifi2_status(Master *master, bool *ret_client_enabled, uint8_t *ret_client_status, uint8_t ret_client_ip[4], uint8_t ret_client_subnet_mask[4], uint8_t ret_client_gateway[4], uint8_t ret_client_mac_address[6], uint32_t *ret_client_rx_count, uint32_t *ret_client_tx_count, int8_t *ret_client_rssi, bool *ret_ap_enabled, uint8_t ret_ap_ip[4], uint8_t ret_ap_subnet_mask[4], uint8_t ret_ap_gateway[4], uint8_t ret_ap_mac_address[6], uint32_t *ret_ap_rx_count, uint32_t *ret_ap_tx_count, uint8_t *ret_ap_connected_count) {
	DevicePrivate *device_p = master->p;
	GetWifi2Status_Request request;
	GetWifi2Status_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_client_enabled = response.client_enabled != 0;
	*ret_client_status = response.client_status;
	memcpy(ret_client_ip, response.client_ip, 4 * sizeof(uint8_t));
	memcpy(ret_client_subnet_mask, response.client_subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_client_gateway, response.client_gateway, 4 * sizeof(uint8_t));
	memcpy(ret_client_mac_address, response.client_mac_address, 6 * sizeof(uint8_t));
	*ret_client_rx_count = leconvert_uint32_from(response.client_rx_count);
	*ret_client_tx_count = leconvert_uint32_from(response.client_tx_count);
	*ret_client_rssi = response.client_rssi;
	*ret_ap_enabled = response.ap_enabled != 0;
	memcpy(ret_ap_ip, response.ap_ip, 4 * sizeof(uint8_t));
	memcpy(ret_ap_subnet_mask, response.ap_subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_ap_gateway, response.ap_gateway, 4 * sizeof(uint8_t));
	memcpy(ret_ap_mac_address, response.ap_mac_address, 6 * sizeof(uint8_t));
	*ret_ap_rx_count = leconvert_uint32_from(response.ap_rx_count);
	*ret_ap_tx_count = leconvert_uint32_from(response.ap_tx_count);
	*ret_ap_connected_count = response.ap_connected_count;

	return ret;
}

int master_set_wifi2_client_configuration(Master *master, bool enable, const char ssid[32], uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint8_t mac_address[6], uint8_t bssid[6]) {
	DevicePrivate *device_p = master->p;
	SetWifi2ClientConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_CLIENT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable = enable ? 1 : 0;
	memcpy(request.ssid, ssid, 32);

	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	memcpy(request.mac_address, mac_address, 6 * sizeof(uint8_t));
	memcpy(request.bssid, bssid, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_client_configuration(Master *master, bool *ret_enable, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6], uint8_t ret_bssid[6]) {
	DevicePrivate *device_p = master->p;
	GetWifi2ClientConfiguration_Request request;
	GetWifi2ClientConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_CLIENT_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;
	memcpy(ret_ssid, response.ssid, 32);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));
	memcpy(ret_bssid, response.bssid, 6 * sizeof(uint8_t));

	return ret;
}

int master_set_wifi2_client_hostname(Master *master, const char hostname[32]) {
	DevicePrivate *device_p = master->p;
	SetWifi2ClientHostname_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_CLIENT_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.hostname, hostname, 32);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_client_hostname(Master *master, char ret_hostname[32]) {
	DevicePrivate *device_p = master->p;
	GetWifi2ClientHostname_Request request;
	GetWifi2ClientHostname_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_CLIENT_HOSTNAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_hostname, response.hostname, 32);

	return ret;
}

int master_set_wifi2_client_password(Master *master, const char password[64]) {
	DevicePrivate *device_p = master->p;
	SetWifi2ClientPassword_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_CLIENT_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.password, password, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_client_password(Master *master, char ret_password[64]) {
	DevicePrivate *device_p = master->p;
	GetWifi2ClientPassword_Request request;
	GetWifi2ClientPassword_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_CLIENT_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_password, response.password, 64);

	return ret;
}

int master_set_wifi2_ap_configuration(Master *master, bool enable, const char ssid[32], uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint8_t encryption, bool hidden, uint8_t channel, uint8_t mac_address[6]) {
	DevicePrivate *device_p = master->p;
	SetWifi2APConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_AP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable = enable ? 1 : 0;
	memcpy(request.ssid, ssid, 32);

	memcpy(request.ip, ip, 4 * sizeof(uint8_t));
	memcpy(request.subnet_mask, subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.gateway, gateway, 4 * sizeof(uint8_t));
	request.encryption = encryption;
	request.hidden = hidden ? 1 : 0;
	request.channel = channel;
	memcpy(request.mac_address, mac_address, 6 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_ap_configuration(Master *master, bool *ret_enable, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t *ret_encryption, bool *ret_hidden, uint8_t *ret_channel, uint8_t ret_mac_address[6]) {
	DevicePrivate *device_p = master->p;
	GetWifi2APConfiguration_Request request;
	GetWifi2APConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_AP_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;
	memcpy(ret_ssid, response.ssid, 32);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	*ret_encryption = response.encryption;
	*ret_hidden = response.hidden != 0;
	*ret_channel = response.channel;
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));

	return ret;
}

int master_set_wifi2_ap_password(Master *master, const char password[64]) {
	DevicePrivate *device_p = master->p;
	SetWifi2APPassword_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_AP_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.password, password, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_ap_password(Master *master, char ret_password[64]) {
	DevicePrivate *device_p = master->p;
	GetWifi2APPassword_Request request;
	GetWifi2APPassword_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_AP_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_password, response.password, 64);

	return ret;
}

int master_save_wifi2_configuration(Master *master, uint8_t *ret_result) {
	DevicePrivate *device_p = master->p;
	SaveWifi2Configuration_Request request;
	SaveWifi2Configuration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SAVE_WIFI2_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_result = response.result;

	return ret;
}

int master_get_wifi2_firmware_version(Master *master, uint8_t ret_firmware_version[3]) {
	DevicePrivate *device_p = master->p;
	GetWifi2FirmwareVersion_Request request;
	GetWifi2FirmwareVersion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_FIRMWARE_VERSION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));

	return ret;
}

int master_enable_wifi2_status_led(Master *master) {
	DevicePrivate *device_p = master->p;
	EnableWifi2StatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_ENABLE_WIFI2_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_disable_wifi2_status_led(Master *master) {
	DevicePrivate *device_p = master->p;
	DisableWifi2StatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_DISABLE_WIFI2_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_is_wifi2_status_led_enabled(Master *master, bool *ret_enabled) {
	DevicePrivate *device_p = master->p;
	IsWifi2StatusLEDEnabled_Request request;
	IsWifi2StatusLEDEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_WIFI2_STATUS_LED_ENABLED, device_p->ipcon_p, device_p);

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

int master_set_wifi2_mesh_configuration(Master *master, bool enable, uint8_t root_ip[4], uint8_t root_subnet_mask[4], uint8_t root_gateway[4], uint8_t router_bssid[6], uint8_t group_id[6], const char group_ssid_prefix[16], uint8_t gateway_ip[4], uint16_t gateway_port) {
	DevicePrivate *device_p = master->p;
	SetWifi2MeshConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_MESH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable = enable ? 1 : 0;
	memcpy(request.root_ip, root_ip, 4 * sizeof(uint8_t));
	memcpy(request.root_subnet_mask, root_subnet_mask, 4 * sizeof(uint8_t));
	memcpy(request.root_gateway, root_gateway, 4 * sizeof(uint8_t));
	memcpy(request.router_bssid, router_bssid, 6 * sizeof(uint8_t));
	memcpy(request.group_id, group_id, 6 * sizeof(uint8_t));
	memcpy(request.group_ssid_prefix, group_ssid_prefix, 16);

	memcpy(request.gateway_ip, gateway_ip, 4 * sizeof(uint8_t));
	request.gateway_port = leconvert_uint16_to(gateway_port);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_mesh_configuration(Master *master, bool *ret_enable, uint8_t ret_root_ip[4], uint8_t ret_root_subnet_mask[4], uint8_t ret_root_gateway[4], uint8_t ret_router_bssid[6], uint8_t ret_group_id[6], char ret_group_ssid_prefix[16], uint8_t ret_gateway_ip[4], uint16_t *ret_gateway_port) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshConfiguration_Request request;
	GetWifi2MeshConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable = response.enable != 0;
	memcpy(ret_root_ip, response.root_ip, 4 * sizeof(uint8_t));
	memcpy(ret_root_subnet_mask, response.root_subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_root_gateway, response.root_gateway, 4 * sizeof(uint8_t));
	memcpy(ret_router_bssid, response.router_bssid, 6 * sizeof(uint8_t));
	memcpy(ret_group_id, response.group_id, 6 * sizeof(uint8_t));
	memcpy(ret_group_ssid_prefix, response.group_ssid_prefix, 16);
	memcpy(ret_gateway_ip, response.gateway_ip, 4 * sizeof(uint8_t));
	*ret_gateway_port = leconvert_uint16_from(response.gateway_port);

	return ret;
}

int master_set_wifi2_mesh_router_ssid(Master *master, const char ssid[32]) {
	DevicePrivate *device_p = master->p;
	SetWifi2MeshRouterSSID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_SSID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.ssid, ssid, 32);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_mesh_router_ssid(Master *master, char ret_ssid[32]) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshRouterSSID_Request request;
	GetWifi2MeshRouterSSID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_SSID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_ssid, response.ssid, 32);

	return ret;
}

int master_set_wifi2_mesh_router_password(Master *master, const char password[64]) {
	DevicePrivate *device_p = master->p;
	SetWifi2MeshRouterPassword_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.password, password, 64);


	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_wifi2_mesh_router_password(Master *master, char ret_password[64]) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshRouterPassword_Request request;
	GetWifi2MeshRouterPassword_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_PASSWORD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_password, response.password, 64);

	return ret;
}

int master_get_wifi2_mesh_common_status(Master *master, uint8_t *ret_status, bool *ret_root_node, bool *ret_root_candidate, uint16_t *ret_connected_nodes, uint32_t *ret_rx_count, uint32_t *ret_tx_count) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshCommonStatus_Request request;
	GetWifi2MeshCommonStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_COMMON_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;
	*ret_root_node = response.root_node != 0;
	*ret_root_candidate = response.root_candidate != 0;
	*ret_connected_nodes = leconvert_uint16_from(response.connected_nodes);
	*ret_rx_count = leconvert_uint32_from(response.rx_count);
	*ret_tx_count = leconvert_uint32_from(response.tx_count);

	return ret;
}

int master_get_wifi2_mesh_client_status(Master *master, char ret_hostname[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6]) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshClientStatus_Request request;
	GetWifi2MeshClientStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_CLIENT_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_hostname, response.hostname, 32);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));

	return ret;
}

int master_get_wifi2_mesh_ap_status(Master *master, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6]) {
	DevicePrivate *device_p = master->p;
	GetWifi2MeshAPStatus_Request request;
	GetWifi2MeshAPStatus_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_WIFI2_MESH_AP_STATUS, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_ssid, response.ssid, 32);
	memcpy(ret_ip, response.ip, 4 * sizeof(uint8_t));
	memcpy(ret_subnet_mask, response.subnet_mask, 4 * sizeof(uint8_t));
	memcpy(ret_gateway, response.gateway, 4 * sizeof(uint8_t));
	memcpy(ret_mac_address, response.mac_address, 6 * sizeof(uint8_t));

	return ret;
}

int master_set_bricklet_xmc_flash_config(Master *master, uint32_t config, uint32_t parameter1, uint32_t parameter2, uint8_t data[52], uint32_t *ret_return_value, uint8_t ret_return_data[60]) {
	DevicePrivate *device_p = master->p;
	SetBrickletXMCFlashConfig_Request request;
	SetBrickletXMCFlashConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = leconvert_uint32_to(config);
	request.parameter1 = leconvert_uint32_to(parameter1);
	request.parameter2 = leconvert_uint32_to(parameter2);
	memcpy(request.data, data, 52 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_return_value = leconvert_uint32_from(response.return_value);
	memcpy(ret_return_data, response.return_data, 60 * sizeof(uint8_t));

	return ret;
}

int master_set_bricklet_xmc_flash_data(Master *master, uint8_t data[64], uint32_t *ret_return_data) {
	DevicePrivate *device_p = master->p;
	SetBrickletXMCFlashData_Request request;
	SetBrickletXMCFlashData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_return_data = leconvert_uint32_from(response.return_data);

	return ret;
}

int master_set_bricklets_enabled(Master *master, bool bricklets_enabled) {
	DevicePrivate *device_p = master->p;
	SetBrickletsEnabled_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_BRICKLETS_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklets_enabled = bricklets_enabled ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_bricklets_enabled(Master *master, bool *ret_bricklets_enabled) {
	DevicePrivate *device_p = master->p;
	GetBrickletsEnabled_Request request;
	GetBrickletsEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_BRICKLETS_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_bricklets_enabled = response.bricklets_enabled != 0;

	return ret;
}

int master_set_spitfp_baudrate_config(Master *master, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate) {
	DevicePrivate *device_p = master->p;
	SetSPITFPBaudrateConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_dynamic_baudrate = enable_dynamic_baudrate ? 1 : 0;
	request.minimum_dynamic_baudrate = leconvert_uint32_to(minimum_dynamic_baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_spitfp_baudrate_config(Master *master, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate) {
	DevicePrivate *device_p = master->p;
	GetSPITFPBaudrateConfig_Request request;
	GetSPITFPBaudrateConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_dynamic_baudrate = response.enable_dynamic_baudrate != 0;
	*ret_minimum_dynamic_baudrate = leconvert_uint32_from(response.minimum_dynamic_baudrate);

	return ret;
}

int master_get_send_timeout_count(Master *master, uint8_t communication_method, uint32_t *ret_timeout_count) {
	DevicePrivate *device_p = master->p;
	GetSendTimeoutCount_Request request;
	GetSendTimeoutCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_SEND_TIMEOUT_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.communication_method = communication_method;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timeout_count = leconvert_uint32_from(response.timeout_count);

	return ret;
}

int master_set_spitfp_baudrate(Master *master, char bricklet_port, uint32_t baudrate) {
	DevicePrivate *device_p = master->p;
	SetSPITFPBaudrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_SET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;
	request.baudrate = leconvert_uint32_to(baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_get_spitfp_baudrate(Master *master, char bricklet_port, uint32_t *ret_baudrate) {
	DevicePrivate *device_p = master->p;
	GetSPITFPBaudrate_Request request;
	GetSPITFPBaudrate_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baudrate = leconvert_uint32_from(response.baudrate);

	return ret;
}

int master_get_spitfp_error_count(Master *master, char bricklet_port, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = master->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

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

int master_enable_status_led(Master *master) {
	DevicePrivate *device_p = master->p;
	EnableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_ENABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_disable_status_led(Master *master) {
	DevicePrivate *device_p = master->p;
	DisableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_DISABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_is_status_led_enabled(Master *master, bool *ret_enabled) {
	DevicePrivate *device_p = master->p;
	IsStatusLEDEnabled_Request request;
	IsStatusLEDEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_IS_STATUS_LED_ENABLED, device_p->ipcon_p, device_p);

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

int master_get_protocol1_bricklet_name(Master *master, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = master->p;
	GetProtocol1BrickletName_Request request;
	GetProtocol1BrickletName_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_protocol_version = response.protocol_version;
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	memcpy(ret_name, response.name, 40);

	return ret;
}

int master_get_chip_temperature(Master *master, int16_t *ret_temperature) {
	DevicePrivate *device_p = master->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int master_reset(Master *master) {
	DevicePrivate *device_p = master->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_write_bricklet_plugin(Master *master, char port, uint8_t offset, uint8_t chunk[32]) {
	DevicePrivate *device_p = master->p;
	WriteBrickletPlugin_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_WRITE_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;
	memcpy(request.chunk, chunk, 32 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int master_read_bricklet_plugin(Master *master, char port, uint8_t offset, uint8_t ret_chunk[32]) {
	DevicePrivate *device_p = master->p;
	ReadBrickletPlugin_Request request;
	ReadBrickletPlugin_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_READ_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_chunk, response.chunk, 32 * sizeof(uint8_t));

	return ret;
}

int master_get_identity(Master *master, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = master->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), MASTER_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
