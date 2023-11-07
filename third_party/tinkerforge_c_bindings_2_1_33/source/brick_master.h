/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_MASTER_H
#define BRICK_MASTER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickMaster Master Brick
 */

/**
 * \ingroup BrickMaster
 *
 * Basis to build stacks and has 4 Bricklet ports
 */
typedef Device Master;

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_EXTENSION_TYPE 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_EXTENSION_TYPE 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_CHIBI_PRESENT 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_ADDRESS 6

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_ADDRESS 7

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_MASTER_ADDRESS 8

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_MASTER_ADDRESS 9

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_SLAVE_ADDRESS 10

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_SLAVE_ADDRESS 11

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_SIGNAL_STRENGTH 12

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_ERROR_LOG 13

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_FREQUENCY 14

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_FREQUENCY 15

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_CHIBI_CHANNEL 16

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIBI_CHANNEL 17

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_RS485_PRESENT 18

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_ADDRESS 19

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_ADDRESS 20

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_SLAVE_ADDRESS 21

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_SLAVE_ADDRESS 22

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_ERROR_LOG 23

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_RS485_CONFIGURATION 24

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_RS485_CONFIGURATION 25

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_WIFI_PRESENT 26

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_CONFIGURATION 27

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_CONFIGURATION 28

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_ENCRYPTION 29

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_ENCRYPTION 30

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_STATUS 31

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_REFRESH_WIFI_STATUS 32

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_CERTIFICATE 33

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_CERTIFICATE 34

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_POWER_MODE 35

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_POWER_MODE 36

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_BUFFER_INFO 37

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_REGULATORY_DOMAIN 38

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_REGULATORY_DOMAIN 39

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE 40

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_LONG_WIFI_KEY 41

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_LONG_WIFI_KEY 42

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_HOSTNAME 43

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_HOSTNAME 44

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_PERIOD 45

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_PERIOD 46

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_PERIOD 47

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_PERIOD 48

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_PERIOD 49

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_PERIOD 50

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_CURRENT_CALLBACK_THRESHOLD 51

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_CURRENT_CALLBACK_THRESHOLD 52

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_STACK_VOLTAGE_CALLBACK_THRESHOLD 53

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_STACK_VOLTAGE_CALLBACK_THRESHOLD 54

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_USB_VOLTAGE_CALLBACK_THRESHOLD 55

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_USB_VOLTAGE_CALLBACK_THRESHOLD 56

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_DEBOUNCE_PERIOD 57

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_DEBOUNCE_PERIOD 58

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_ETHERNET_PRESENT 65

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_CONFIGURATION 66

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_CONFIGURATION 67

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_STATUS 68

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_HOSTNAME 69

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_MAC_ADDRESS 70

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_WEBSOCKET_CONFIGURATION 71

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_WEBSOCKET_CONFIGURATION 72

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_ETHERNET_AUTHENTICATION_SECRET 73

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_ETHERNET_AUTHENTICATION_SECRET 74

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI_AUTHENTICATION_SECRET 75

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI_AUTHENTICATION_SECRET 76

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CONNECTION_TYPE 77

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_WIFI2_PRESENT 78

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_START_WIFI2_BOOTLOADER 79

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_WRITE_WIFI2_SERIAL_PORT 80

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_READ_WIFI2_SERIAL_PORT 81

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_AUTHENTICATION_SECRET 82

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_AUTHENTICATION_SECRET 83

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_CONFIGURATION 84

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_CONFIGURATION 85

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_STATUS 86

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_CLIENT_CONFIGURATION 87

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_CLIENT_CONFIGURATION 88

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_CLIENT_HOSTNAME 89

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_CLIENT_HOSTNAME 90

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_CLIENT_PASSWORD 91

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_CLIENT_PASSWORD 92

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_AP_CONFIGURATION 93

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_AP_CONFIGURATION 94

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_AP_PASSWORD 95

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_AP_PASSWORD 96

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SAVE_WIFI2_CONFIGURATION 97

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_FIRMWARE_VERSION 98

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_ENABLE_WIFI2_STATUS_LED 99

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_DISABLE_WIFI2_STATUS_LED 100

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_WIFI2_STATUS_LED_ENABLED 101

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_MESH_CONFIGURATION 102

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_CONFIGURATION 103

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_SSID 104

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_SSID 105

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_WIFI2_MESH_ROUTER_PASSWORD 106

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_ROUTER_PASSWORD 107

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_COMMON_STATUS 108

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_CLIENT_STATUS 109

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_WIFI2_MESH_AP_STATUS 110

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_CONFIG 111

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_BRICKLET_XMC_FLASH_DATA 112

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_BRICKLETS_ENABLED 113

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_BRICKLETS_ENABLED 114

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG 231

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG 232

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_SEND_TIMEOUT_COUNT 233

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_SET_SPITFP_BAUDRATE 234

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_SPITFP_BAUDRATE 235

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_SPITFP_ERROR_COUNT 237

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_ENABLE_STATUS_LED 238

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_DISABLE_STATUS_LED 239

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_IS_STATUS_LED_ENABLED 240

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME 241

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_RESET 243

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_WRITE_BRICKLET_PLUGIN 246

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_READ_BRICKLET_PLUGIN 247

/**
 * \ingroup BrickMaster
 */
#define MASTER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t current, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_stack_current_callback_period}. The parameter is the current
 * of the sensor.
 * 
 * The {@link MASTER_CALLBACK_STACK_CURRENT} callback is only triggered if the current has changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_STACK_CURRENT 59

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_stack_voltage_callback_period}. The parameter is the voltage
 * of the sensor.
 * 
 * The {@link MASTER_CALLBACK_STACK_VOLTAGE} callback is only triggered if the voltage has changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_STACK_VOLTAGE 60

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link master_set_usb_voltage_callback_period}. The parameter is the USB
 * voltage.
 * 
 * The {@link MASTER_CALLBACK_USB_VOLTAGE} callback is only triggered if the USB voltage has changed
 * since the last triggering.
 * 
 * Does not work with hardware version 2.1 or newer.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_USB_VOLTAGE 61

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t current, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_stack_current_callback_threshold} is reached.
 * The parameter is the stack current.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_STACK_CURRENT_REACHED 62

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_stack_voltage_callback_threshold} is reached.
 * The parameter is the stack voltage.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_STACK_VOLTAGE_REACHED 63

/**
 * \ingroup BrickMaster
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link master_set_usb_voltage_callback_threshold} is reached.
 * The parameter is the voltage of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
#define MASTER_CALLBACK_USB_VOLTAGE_REACHED 64


/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_CHIBI 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_RS485 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_WIFI 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_ETHERNET 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_EXTENSION_TYPE_WIFI2 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_868_MHZ 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_915_MHZ 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_OQPSK_780_MHZ 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_CHIBI_FREQUENCY_BPSK40_915_MHZ 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_NONE 'n'

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_EVEN 'e'

/**
 * \ingroup BrickMaster
 */
#define MASTER_RS485_PARITY_ODD 'o'

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_DHCP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_STATIC_IP 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_ACCESS_POINT_DHCP 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_ACCESS_POINT_STATIC_IP 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_AD_HOC_DHCP 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_CONNECTION_AD_HOC_STATIC_IP 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WPA_WPA2 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WPA_ENTERPRISE 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_WEP 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_ENCRYPTION_NO_ENCRYPTION 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_FAST 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_TLS 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_TTLS 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_OUTER_AUTH_EAP_PEAP 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_INNER_AUTH_EAP_MSCHAP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_INNER_AUTH_EAP_GTC 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_CA_CERT 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_CLIENT_CERT 8

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_EAP_OPTION_CERT_TYPE_PRIVATE_KEY 16

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_DISASSOCIATED 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ASSOCIATED 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ASSOCIATING 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_ERROR 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_STATE_NOT_INITIALIZED_YET 255

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_POWER_MODE_FULL_SPEED 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_POWER_MODE_LOW_POWER 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO11 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO13 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI_DOMAIN_CHANNEL_1TO14 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickMaster
 */
#define MASTER_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickMaster
 */
#define MASTER_ETHERNET_CONNECTION_DHCP 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_ETHERNET_CONNECTION_STATIC_IP 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_NONE 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_USB 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_SPI_STACK 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_CHIBI 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_RS485 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_WIFI 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_ETHERNET 6

/**
 * \ingroup BrickMaster
 */
#define MASTER_CONNECTION_TYPE_WIFI2 7

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_PHY_MODE_B 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_PHY_MODE_G 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_PHY_MODE_N 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_IDLE 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_CONNECTING 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_WRONG_PASSWORD 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_NO_AP_FOUND 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_CONNECT_FAILED 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_GOT_IP 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_CLIENT_STATUS_UNKNOWN 255

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_AP_ENCRYPTION_OPEN 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_AP_ENCRYPTION_WEP 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_AP_ENCRYPTION_WPA_PSK 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_AP_ENCRYPTION_WPA2_PSK 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_AP_ENCRYPTION_WPA_WPA2_PSK 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_DISABLED 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_WIFI_CONNECTING 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_GOT_IP 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_MESH_LOCAL 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_MESH_ONLINE 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_AP_AVAILABLE 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_AP_SETUP 6

/**
 * \ingroup BrickMaster
 */
#define MASTER_WIFI2_MESH_STATUS_LEAF_AVAILABLE 7

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_NONE 0

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_USB 1

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_SPI_STACK 2

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_CHIBI 3

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_RS485 4

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_WIFI 5

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_ETHERNET 6

/**
 * \ingroup BrickMaster
 */
#define MASTER_COMMUNICATION_METHOD_WIFI_V2 7

/**
 * \ingroup BrickMaster
 *
 * This constant is used to identify a Master Brick.
 *
 * The {@link master_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define MASTER_DEVICE_IDENTIFIER 13

/**
 * \ingroup BrickMaster
 *
 * This constant represents the display name of a Master Brick.
 */
#define MASTER_DEVICE_DISPLAY_NAME "Master Brick"

/**
 * \ingroup BrickMaster
 *
 * Creates the device object \c master with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void master_create(Master *master, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickMaster
 *
 * Removes the device object \c master from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void master_destroy(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the master_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int master_get_response_expected(Master *master, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickMaster
 *
 * Changes the response expected flag of the function specified by the
 * \c function_id parameter. This flag can only be changed for setter
 * (default value: *false*) and callback configuration functions
 * (default value: *true*). For getter functions it is always enabled.
 *
 * Enabling the response expected flag for a setter function allows to detect
 * timeouts and other error conditions calls of this setter as well. The device
 * will then send a response for this purpose. If this flag is disabled for a
 * setter function then no response is sent and errors are silently ignored,
 * because they cannot be detected.
 */
int master_set_response_expected(Master *master, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickMaster
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int master_set_response_expected_all(Master *master, bool response_expected);

/**
 * \ingroup BrickMaster
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void master_register_callback(Master *master, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickMaster
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int master_get_api_version(Master *master, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickMaster
 *
 * Returns the stack voltage. The stack voltage is the
 * voltage that is supplied via the stack, i.e. it is given by a
 * Step-Down or Step-Up Power Supply.
 * 
 * \note
 *  It is not possible to measure voltages supplied per PoE or USB with this function.
 */
int master_get_stack_voltage(Master *master, uint16_t *ret_voltage);

/**
 * \ingroup BrickMaster
 *
 * Returns the stack current. The stack current is the
 * current that is drawn via the stack, i.e. it is given by a
 * Step-Down or Step-Up Power Supply.
 * 
 * \note
 *  It is not possible to measure the current drawn via PoE or USB with this function.
 */
int master_get_stack_current(Master *master, uint16_t *ret_current);

/**
 * \ingroup BrickMaster
 *
 * Writes the extension type to the EEPROM of a specified extension.
 * The extension is either 0 or 1 (0 is the lower one, 1 is the upper one,
 * if only one extension is present use 0).
 * 
 * Possible extension types:
 * 
 * \verbatim
 *  "Type", "Description"
 * 
 *  "1",    "Chibi"
 *  "2",    "RS485"
 *  "3",    "WIFI"
 *  "4",    "Ethernet"
 *  "5",    "WIFI 2.0"
 * \endverbatim
 * 
 * The extension type is already set when bought and it can be set with the
 * Brick Viewer, it is unlikely that you need this function.
 */
int master_set_extension_type(Master *master, uint8_t extension, uint32_t exttype);

/**
 * \ingroup BrickMaster
 *
 * Returns the type for a given extension as set by {@link master_set_extension_type}.
 */
int master_get_extension_type(Master *master, uint8_t extension, uint32_t *ret_exttype);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Master Brick is at position 0 in the stack and a Chibi
 * Extension is available.
 */
int master_is_chibi_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the address belonging to the Chibi Extension.
 * 
 * It is possible to set the address with the Brick Viewer and it will be
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 */
int master_set_chibi_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_chibi_address}.
 */
int master_get_chibi_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets the address of the Chibi Master. This address is used if the
 * Chibi Extension is used as slave (i.e. it does not have a USB connection).
 * 
 * It is possible to set the address with the Brick Viewer and it will be
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 */
int master_set_chibi_master_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_chibi_master_address}.
 */
int master_get_chibi_master_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets up to 254 slave addresses. 0 has a
 * special meaning, it is used as list terminator and not allowed as normal slave
 * address. The address numeration (via \c num parameter) has to be used
 * ascending from 0. For example: If you use the Chibi Extension in Master mode
 * (i.e. the stack has an USB connection) and you want to talk to three other
 * Chibi stacks with the slave addresses 17, 23, and 42, you should call with
 * ``(0, 17)``, ``(1, 23)``, ``(2, 42)`` and ``(3, 0)``. The last call with
 * ``(3, 0)`` is a list terminator and indicates that the Chibi slave address
 * list contains 3 addresses in this case.
 * 
 * It is possible to set the addresses with the Brick Viewer, that will take care
 * of correct address numeration and list termination.
 * 
 * The slave addresses will be saved in the EEPROM of the Chibi Extension, they
 * don't have to be set on every startup.
 */
int master_set_chibi_slave_address(Master *master, uint8_t num, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the slave address for a given \c num as set by
 * {@link master_set_chibi_slave_address}.
 */
int master_get_chibi_slave_address(Master *master, uint8_t num, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Returns the signal strength in dBm. The signal strength updates every time a
 * packet is received.
 */
int master_get_chibi_signal_strength(Master *master, uint8_t *ret_signal_strength);

/**
 * \ingroup BrickMaster
 *
 * Returns underrun, CRC error, no ACK and overflow error counts of the Chibi
 * communication. If these errors start rising, it is likely that either the
 * distance between two Chibi stacks is becoming too big or there are
 * interferences.
 */
int master_get_chibi_error_log(Master *master, uint16_t *ret_underrun, uint16_t *ret_crc_error, uint16_t *ret_no_ack, uint16_t *ret_overflow);

/**
 * \ingroup BrickMaster
 *
 * Sets the Chibi frequency range for the Chibi Extension. Possible values are:
 * 
 * \verbatim
 *  "Type", "Description"
 * 
 *  "0",    "OQPSK 868MHz (Europe)"
 *  "1",    "OQPSK 915MHz (US)"
 *  "2",    "OQPSK 780MHz (China)"
 *  "3",    "BPSK40 915MHz"
 * \endverbatim
 * 
 * It is possible to set the frequency with the Brick Viewer and it will be
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 */
int master_set_chibi_frequency(Master *master, uint8_t frequency);

/**
 * \ingroup BrickMaster
 *
 * Returns the frequency value as set by {@link master_set_chibi_frequency}.
 */
int master_get_chibi_frequency(Master *master, uint8_t *ret_frequency);

/**
 * \ingroup BrickMaster
 *
 * Sets the channel used by the Chibi Extension. Possible channels are
 * different for different frequencies:
 * 
 * \verbatim
 *  "Frequency", "Possible Channels"
 * 
 *  "OQPSK 868MHz (Europe)", "0"
 *  "OQPSK 915MHz (US)",     "1, 2, 3, 4, 5, 6, 7, 8, 9, 10"
 *  "OQPSK 780MHz (China)",  "0, 1, 2, 3"
 *  "BPSK40 915MHz",         "1, 2, 3, 4, 5, 6, 7, 8, 9, 10"
 * \endverbatim
 * 
 * It is possible to set the channel with the Brick Viewer and it will be
 * saved in the EEPROM of the Chibi Extension, it does not
 * have to be set on every startup.
 */
int master_set_chibi_channel(Master *master, uint8_t channel);

/**
 * \ingroup BrickMaster
 *
 * Returns the channel as set by {@link master_set_chibi_channel}.
 */
int master_get_chibi_channel(Master *master, uint8_t *ret_channel);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Master Brick is at position 0 in the stack and a RS485
 * Extension is available.
 */
int master_is_rs485_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the address (0-255) belonging to the RS485 Extension.
 * 
 * Set to 0 if the RS485 Extension should be the RS485 Master (i.e.
 * connected to a PC via USB).
 * 
 * It is possible to set the address with the Brick Viewer and it will be
 * saved in the EEPROM of the RS485 Extension, it does not
 * have to be set on every startup.
 */
int master_set_rs485_address(Master *master, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the address as set by {@link master_set_rs485_address}.
 */
int master_get_rs485_address(Master *master, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Sets up to 255 slave addresses. Valid addresses are in range 1-255. 0 has a
 * special meaning, it is used as list terminator and not allowed as normal slave
 * address. The address numeration (via ``num`` parameter) has to be used
 * ascending from 0. For example: If you use the RS485 Extension in Master mode
 * (i.e. the stack has an USB connection) and you want to talk to three other
 * RS485 stacks with the addresses 17, 23, and 42, you should call with
 * ``(0, 17)``, ``(1, 23)``, ``(2, 42)`` and ``(3, 0)``. The last call with
 * ``(3, 0)`` is a list terminator and indicates that the RS485 slave address list
 * contains 3 addresses in this case.
 * 
 * It is possible to set the addresses with the Brick Viewer, that will take care
 * of correct address numeration and list termination.
 * 
 * The slave addresses will be saved in the EEPROM of the Chibi Extension, they
 * don't have to be set on every startup.
 */
int master_set_rs485_slave_address(Master *master, uint8_t num, uint8_t address);

/**
 * \ingroup BrickMaster
 *
 * Returns the slave address for a given ``num`` as set by
 * {@link master_set_rs485_slave_address}.
 */
int master_get_rs485_slave_address(Master *master, uint8_t num, uint8_t *ret_address);

/**
 * \ingroup BrickMaster
 *
 * Returns CRC error counts of the RS485 communication.
 * If this counter starts rising, it is likely that the distance
 * between the RS485 nodes is too big or there is some kind of
 * interference.
 */
int master_get_rs485_error_log(Master *master, uint16_t *ret_crc_error);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the RS485 Extension. The
 * Master Brick will try to match the given baud rate as exactly as possible.
 * The maximum recommended baud rate is 2000000 (2MBd).
 * Possible values for parity are 'n' (none), 'e' (even) and 'o' (odd).
 * 
 * If your RS485 is unstable (lost messages etc.), the first thing you should
 * try is to decrease the speed. On very large bus (e.g. 1km), you probably
 * should use a value in the range of 100000 (100kBd).
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 */
int master_set_rs485_configuration(Master *master, uint32_t speed, char parity, uint8_t stopbits);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_rs485_configuration}.
 */
int master_get_rs485_configuration(Master *master, uint32_t *ret_speed, char *ret_parity, uint8_t *ret_stopbits);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Master Brick is at position 0 in the stack and a WIFI
 * Extension is available.
 */
int master_is_wifi_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the WIFI Extension. The ``ssid`` can have a max length
 * of 32 characters. Possible values for ``connection`` are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "DHCP"
 *  "1", "Static IP"
 *  "2", "Access Point: DHCP"
 *  "3", "Access Point: Static IP"
 *  "4", "Ad Hoc: DHCP"
 *  "5", "Ad Hoc: Static IP"
 * \endverbatim
 * 
 * If you set ``connection`` to one of the static IP options then you have to
 * supply ``ip``, ``subnet_mask`` and ``gateway`` as an array of size 4 (first
 * element of the array is the least significant byte of the address). If
 * ``connection`` is set to one of the DHCP options then ``ip``, ``subnet_mask``
 * and ``gateway`` are ignored, you can set them to 0.
 * 
 * The last parameter is the port that your program will connect to.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the WIFI configuration.
 */
int master_set_wifi_configuration(Master *master, const char *ssid, uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_wifi_configuration}.
 */
int master_get_wifi_configuration(Master *master, char ret_ssid[32], uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port);

/**
 * \ingroup BrickMaster
 *
 * Sets the encryption of the WIFI Extension. The first parameter is the
 * type of the encryption. Possible values are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "WPA/WPA2"
 *  "1", "WPA Enterprise (EAP-FAST, EAP-TLS, EAP-TTLS, PEAP)"
 *  "2", "WEP"
 *  "3", "No Encryption"
 * \endverbatim
 * 
 * The ``key`` has a max length of 50 characters and is used if ``encryption``
 * is set to 0 or 2 (WPA/WPA2 or WEP). Otherwise the value is ignored.
 * 
 * For WPA/WPA2 the key has to be at least 8 characters long. If you want to set
 * a key with more than 50 characters, see {@link master_set_long_wifi_key}.
 * 
 * For WEP the key has to be either 10 or 26 hexadecimal digits long. It is
 * possible to set the WEP ``key_index`` (1-4). If you don't know your
 * ``key_index``, it is likely 1.
 * 
 * If you choose WPA Enterprise as encryption, you have to set ``eap_options`` and
 * the length of the certificates (for other encryption types these parameters
 * are ignored). The certificates
 * themselves can be set with {@link master_set_wifi_certificate}. ``eap_options`` consist
 * of the outer authentication (bits 1-2), inner authentication (bit 3) and
 * certificate type (bits 4-5):
 * 
 * \verbatim
 *  "Option", "Bits", "Description"
 * 
 *  "outer authentication", "1-2", "0=EAP-FAST, 1=EAP-TLS, 2=EAP-TTLS, 3=EAP-PEAP"
 *  "inner authentication", "3", "0=EAP-MSCHAP, 1=EAP-GTC"
 *  "certificate type", "4-5", "0=CA Certificate, 1=Client Certificate, 2=Private Key"
 * \endverbatim
 * 
 * Example for EAP-TTLS + EAP-GTC + Private Key: ``option = 2 | (1 << 2) | (2 << 3)``.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the Wi-Fi encryption.
 */
int master_set_wifi_encryption(Master *master, uint8_t encryption, const char *key, uint8_t key_index, uint8_t eap_options, uint16_t ca_certificate_length, uint16_t client_certificate_length, uint16_t private_key_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the encryption as set by {@link master_set_wifi_encryption}.
 * 
 * \note
 *  Since Master Brick Firmware version 2.4.4 the key is not returned anymore.
 */
int master_get_wifi_encryption(Master *master, uint8_t *ret_encryption, char ret_key[50], uint8_t *ret_key_index, uint8_t *ret_eap_options, uint16_t *ret_ca_certificate_length, uint16_t *ret_client_certificate_length, uint16_t *ret_private_key_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the status of the WIFI Extension. The ``state`` is updated automatically,
 * all of the other parameters are updated on startup and every time
 * {@link master_refresh_wifi_status} is called.
 * 
 * Possible states are:
 * 
 * \verbatim
 *  "State", "Description"
 * 
 *  "0", "Disassociated"
 *  "1", "Associated"
 *  "2", "Associating"
 *  "3", "Error"
 *  "255", "Not initialized yet"
 * \endverbatim
 */
int master_get_wifi_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_bssid[6], uint8_t *ret_channel, int16_t *ret_rssi, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, uint8_t *ret_state);

/**
 * \ingroup BrickMaster
 *
 * Refreshes the Wi-Fi status (see {@link master_get_wifi_status}). To read the status
 * of the Wi-Fi module, the Master Brick has to change from data mode to
 * command mode and back. This transaction and the readout itself is
 * unfortunately time consuming. This means, that it might take some ms
 * until the stack with attached WIFI Extension reacts again after this
 * function is called.
 */
int master_refresh_wifi_status(Master *master);

/**
 * \ingroup BrickMaster
 *
 * This function is used to set the certificate as well as password and username
 * for WPA Enterprise. To set the username use index 0xFFFF,
 * to set the password use index 0xFFFE. The max length of username and
 * password is 32.
 * 
 * The certificate is written in chunks of size 32 and the index is used as
 * the index of the chunk. ``data_length`` should nearly always be 32. Only
 * the last chunk can have a length that is not equal to 32.
 * 
 * The starting index of the CA Certificate is 0, of the Client Certificate
 * 10000 and for the Private Key 20000. Maximum sizes are 1312, 1312 and
 * 4320 byte respectively.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after uploading the certificate.
 * 
 * It is recommended to use the Brick Viewer to set the certificate, username
 * and password.
 */
int master_set_wifi_certificate(Master *master, uint16_t index, uint8_t data[32], uint8_t data_length);

/**
 * \ingroup BrickMaster
 *
 * Returns the certificate for a given index as set by {@link master_set_wifi_certificate}.
 */
int master_get_wifi_certificate(Master *master, uint16_t index, uint8_t ret_data[32], uint8_t *ret_data_length);

/**
 * \ingroup BrickMaster
 *
 * Sets the power mode of the WIFI Extension. Possible modes are:
 * 
 * \verbatim
 *  "Mode", "Description"
 * 
 *  "0", "Full Speed (high power consumption, high throughput)"
 *  "1", "Low Power (low power consumption, low throughput)"
 * \endverbatim
 */
int master_set_wifi_power_mode(Master *master, uint8_t mode);

/**
 * \ingroup BrickMaster
 *
 * Returns the power mode as set by {@link master_set_wifi_power_mode}.
 */
int master_get_wifi_power_mode(Master *master, uint8_t *ret_mode);

/**
 * \ingroup BrickMaster
 *
 * Returns informations about the Wi-Fi receive buffer. The Wi-Fi
 * receive buffer has a max size of 1500 byte and if data is transfered
 * too fast, it might overflow.
 * 
 * The return values are the number of overflows, the low watermark
 * (i.e. the smallest number of bytes that were free in the buffer) and
 * the bytes that are currently used.
 * 
 * You should always try to keep the buffer empty, otherwise you will
 * have a permanent latency. A good rule of thumb is, that you can transfer
 * 1000 messages per second without problems.
 * 
 * Try to not send more then 50 messages at a time without any kind of
 * break between them.
 */
int master_get_wifi_buffer_info(Master *master, uint32_t *ret_overflow, uint16_t *ret_low_watermark, uint16_t *ret_used);

/**
 * \ingroup BrickMaster
 *
 * Sets the regulatory domain of the WIFI Extension. Possible domains are:
 * 
 * \verbatim
 *  "Domain", "Description"
 * 
 *  "0", "FCC: Channel 1-11 (N/S America, Australia, New Zealand)"
 *  "1", "ETSI: Channel 1-13 (Europe, Middle East, Africa)"
 *  "2", "TELEC: Channel 1-14 (Japan)"
 * \endverbatim
 */
int master_set_wifi_regulatory_domain(Master *master, uint8_t domain);

/**
 * \ingroup BrickMaster
 *
 * Returns the regulatory domain as set by {@link master_set_wifi_regulatory_domain}.
 */
int master_get_wifi_regulatory_domain(Master *master, uint8_t *ret_domain);

/**
 * \ingroup BrickMaster
 *
 * Returns the USB voltage. Does not work with hardware version 2.1 or newer.
 */
int master_get_usb_voltage(Master *master, uint16_t *ret_voltage);

/**
 * \ingroup BrickMaster
 *
 * Sets a long Wi-Fi key (up to 63 chars, at least 8 chars) for WPA encryption.
 * This key will be used
 * if the key in {@link master_set_wifi_encryption} is set to "-". In the old protocol,
 * a payload of size 63 was not possible, so the maximum key length was 50 chars.
 * 
 * With the new protocol this is possible, since we didn't want to break API,
 * this function was added additionally.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Firmware)
 */
int master_set_long_wifi_key(Master *master, const char *key);

/**
 * \ingroup BrickMaster
 *
 * Returns the encryption key as set by {@link master_set_long_wifi_key}.
 * 
 * \note
 *  Since Master Brick firmware version 2.4.4 the key is not returned anymore.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Firmware)
 */
int master_get_long_wifi_key(Master *master, char ret_key[64]);

/**
 * \ingroup BrickMaster
 *
 * Sets the hostname of the WIFI Extension. The hostname will be displayed
 * by access points as the hostname in the DHCP clients table.
 * 
 * Setting an empty String will restore the default hostname.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_wifi_hostname(Master *master, const char *hostname);

/**
 * \ingroup BrickMaster
 *
 * Returns the hostname as set by {@link master_set_wifi_hostname}.
 * 
 * An empty String means, that the default hostname is used.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_wifi_hostname(Master *master, char ret_hostname[16]);

/**
 * \ingroup BrickMaster
 *
 * Sets the period with which the {@link MASTER_CALLBACK_STACK_CURRENT} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link MASTER_CALLBACK_STACK_CURRENT} callback is only triggered if the current has changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_stack_current_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by {@link master_set_stack_current_callback_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_stack_current_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the period with which the {@link MASTER_CALLBACK_STACK_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link MASTER_CALLBACK_STACK_VOLTAGE} callback is only triggered if the voltage has changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_stack_voltage_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by {@link master_set_stack_voltage_callback_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_stack_voltage_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the period with which the {@link MASTER_CALLBACK_USB_VOLTAGE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link MASTER_CALLBACK_USB_VOLTAGE} callback is only triggered if the voltage has changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_usb_voltage_callback_period(Master *master, uint32_t period);

/**
 * \ingroup BrickMaster
 *
 * Returns the period as set by {@link master_set_usb_voltage_callback_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_usb_voltage_callback_period(Master *master, uint32_t *ret_period);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the {@link MASTER_CALLBACK_STACK_CURRENT_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the current is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the current is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the current is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the current is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_stack_current_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_stack_current_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_stack_current_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the {@link MASTER_CALLBACK_STACK_VOLTAGE_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the voltage is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the voltage is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the voltage is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the voltage is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_stack_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_stack_voltage_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_stack_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the thresholds for the {@link MASTER_CALLBACK_USB_VOLTAGE_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the voltage is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the voltage is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the voltage is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the voltage is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_usb_voltage_callback_threshold(Master *master, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickMaster
 *
 * Returns the threshold as set by {@link master_set_usb_voltage_callback_threshold}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_usb_voltage_callback_threshold(Master *master, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickMaster
 *
 * Sets the period with which the threshold callbacks
 * 
 * * {@link MASTER_CALLBACK_STACK_CURRENT_REACHED},
 * * {@link MASTER_CALLBACK_STACK_VOLTAGE_REACHED},
 * * {@link MASTER_CALLBACK_USB_VOLTAGE_REACHED}
 * 
 * are triggered, if the thresholds
 * 
 * * {@link master_set_stack_current_callback_threshold},
 * * {@link master_set_stack_voltage_callback_threshold},
 * * {@link master_set_usb_voltage_callback_threshold}
 * 
 * keep being reached.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_set_debounce_period(Master *master, uint32_t debounce);

/**
 * \ingroup BrickMaster
 *
 * Returns the debounce period as set by {@link master_set_debounce_period}.
 * 
 * .. versionadded:: 2.0.5$nbsp;(Firmware)
 */
int master_get_debounce_period(Master *master, uint32_t *ret_debounce);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Master Brick is at position 0 in the stack and an Ethernet
 * Extension is available.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_is_ethernet_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Sets the configuration of the Ethernet Extension. Possible values for
 * ``connection`` are:
 * 
 * \verbatim
 *  "Value", "Description"
 * 
 *  "0", "DHCP"
 *  "1", "Static IP"
 * \endverbatim
 * 
 * If you set ``connection`` to static IP options then you have to supply ``ip``,
 * ``subnet_mask`` and ``gateway`` as an array of size 4 (first element of the
 * array is the least significant byte of the address). If ``connection`` is set
 * to the DHCP options then ``ip``, ``subnet_mask`` and ``gateway`` are ignored,
 * you can set them to 0.
 * 
 * The last parameter is the port that your program will connect to.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the Ethernet configuration.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_set_ethernet_configuration(Master *master, uint8_t connection, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint16_t port);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_ethernet_configuration}.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_get_ethernet_configuration(Master *master, uint8_t *ret_connection, uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint16_t *ret_port);

/**
 * \ingroup BrickMaster
 *
 * Returns the status of the Ethernet Extension.
 * 
 * ``mac_address``, ``ip``, ``subnet_mask`` and ``gateway`` are given as an array.
 * The first element of the array is the least significant byte of the address.
 * 
 * ``rx_count`` and ``tx_count`` are the number of bytes that have been
 * received/send since last restart.
 * 
 * ``hostname`` is the currently used hostname.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_get_ethernet_status(Master *master, uint8_t ret_mac_address[6], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint32_t *ret_rx_count, uint32_t *ret_tx_count, char ret_hostname[32]);

/**
 * \ingroup BrickMaster
 *
 * Sets the hostname of the Ethernet Extension. The hostname will be displayed
 * by access points as the hostname in the DHCP clients table.
 * 
 * Setting an empty String will restore the default hostname.
 * 
 * The current hostname can be discovered with {@link master_get_ethernet_status}.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_set_ethernet_hostname(Master *master, const char *hostname);

/**
 * \ingroup BrickMaster
 *
 * Sets the MAC address of the Ethernet Extension. The Ethernet Extension should
 * come configured with a valid MAC address, that is also written on a
 * sticker of the extension itself.
 * 
 * The MAC address can be read out again with {@link master_get_ethernet_status}.
 * 
 * .. versionadded:: 2.1.0$nbsp;(Firmware)
 */
int master_set_ethernet_mac_address(Master *master, uint8_t mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * Sets the Ethernet WebSocket configuration. The first parameter sets the number of socket
 * connections that are reserved for WebSockets. The range is 0-7. The connections
 * are shared with the plain sockets. Example: If you set the connections to 3,
 * there will be 3 WebSocket and 4 plain socket connections available.
 * 
 * The second parameter is the port for the WebSocket connections. The port can
 * not be the same as the port for the plain socket connections.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the Ethernet configuration.
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_set_ethernet_websocket_configuration(Master *master, uint8_t sockets, uint16_t port);

/**
 * \ingroup BrickMaster
 *
 * Returns the configuration as set by {@link master_set_ethernet_configuration}.
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_get_ethernet_websocket_configuration(Master *master, uint8_t *ret_sockets, uint16_t *ret_port);

/**
 * \ingroup BrickMaster
 *
 * Sets the Ethernet authentication secret. The secret can be a string of up to 64
 * characters. An empty string disables the authentication.
 * 
 * See the :ref:`authentication tutorial <tutorial_authentication>` for more
 * information.
 * 
 * The secret is stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the Ethernet authentication secret.
 * 
 * The default value is an empty string (authentication disabled).
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_set_ethernet_authentication_secret(Master *master, const char *secret);

/**
 * \ingroup BrickMaster
 *
 * Returns the authentication secret as set by
 * {@link master_set_ethernet_authentication_secret}.
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_get_ethernet_authentication_secret(Master *master, char ret_secret[64]);

/**
 * \ingroup BrickMaster
 *
 * Sets the WIFI authentication secret. The secret can be a string of up to 64
 * characters. An empty string disables the authentication.
 * 
 * See the :ref:`authentication tutorial <tutorial_authentication>` for more
 * information.
 * 
 * The secret is stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * It is recommended to use the Brick Viewer to set the WIFI authentication secret.
 * 
 * The default value is an empty string (authentication disabled).
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_set_wifi_authentication_secret(Master *master, const char *secret);

/**
 * \ingroup BrickMaster
 *
 * Returns the authentication secret as set by
 * {@link master_set_wifi_authentication_secret}.
 * 
 * .. versionadded:: 2.2.0$nbsp;(Firmware)
 */
int master_get_wifi_authentication_secret(Master *master, char ret_secret[64]);

/**
 * \ingroup BrickMaster
 *
 * Returns the type of the connection over which this function was called.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_connection_type(Master *master, uint8_t *ret_connection_type);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Master Brick is at position 0 in the stack and a WIFI
 * Extension 2.0 is available.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_is_wifi2_present(Master *master, bool *ret_present);

/**
 * \ingroup BrickMaster
 *
 * Starts the bootloader of the WIFI Extension 2.0. Returns 0 on success.
 * Afterwards the {@link master_write_wifi2_serial_port} and {@link master_read_wifi2_serial_port}
 * functions can be used to communicate with the bootloader to flash a new
 * firmware.
 * 
 * The bootloader should only be started over a USB connection. It cannot be
 * started over a WIFI2 connection, see the {@link master_get_connection_type} function.
 * 
 * It is recommended to use the Brick Viewer to update the firmware of the WIFI
 * Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_start_wifi2_bootloader(Master *master, int8_t *ret_result);

/**
 * \ingroup BrickMaster
 *
 * Writes up to 60 bytes (number of bytes to be written specified by ``length``)
 * to the serial port of the bootloader of the WIFI Extension 2.0. Returns 0 on
 * success.
 * 
 * Before this function can be used the bootloader has to be started using the
 * {@link master_start_wifi2_bootloader} function.
 * 
 * It is recommended to use the Brick Viewer to update the firmware of the WIFI
 * Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_write_wifi2_serial_port(Master *master, uint8_t data[60], uint8_t length, int8_t *ret_result);

/**
 * \ingroup BrickMaster
 *
 * Reads up to 60 bytes (number of bytes to be read specified by ``length``)
 * from the serial port of the bootloader of the WIFI Extension 2.0.
 * Returns the number of actually read bytes.
 * 
 * Before this function can be used the bootloader has to be started using the
 * {@link master_start_wifi2_bootloader} function.
 * 
 * It is recommended to use the Brick Viewer to update the firmware of the WIFI
 * Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_read_wifi2_serial_port(Master *master, uint8_t length, uint8_t ret_data[60], uint8_t *ret_result);

/**
 * \ingroup BrickMaster
 *
 * Sets the WIFI authentication secret. The secret can be a string of up to 64
 * characters. An empty string disables the authentication. The default value is
 * an empty string (authentication disabled).
 * 
 * See the :ref:`authentication tutorial <tutorial_authentication>` for more
 * information.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_authentication_secret(Master *master, const char *secret);

/**
 * \ingroup BrickMaster
 *
 * Returns the WIFI authentication secret as set by
 * {@link master_set_wifi2_authentication_secret}.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_authentication_secret(Master *master, char ret_secret[64]);

/**
 * \ingroup BrickMaster
 *
 * Sets the general configuration of the WIFI Extension 2.0.
 * 
 * The ``port`` parameter sets the port number that your programm will connect
 * to.
 * 
 * The ``websocket_port`` parameter sets the WebSocket port number that your
 * JavaScript programm will connect to.
 * 
 * The ``website_port`` parameter sets the port number for the website of the
 * WIFI Extension 2.0.
 * 
 * The ``phy_mode`` parameter sets the specific wireless network mode to be used.
 * Possible values are B, G and N.
 * 
 * The ``sleep_mode`` parameter is currently unused.
 * 
 * The ``website`` parameter is used to enable or disable the web interface of
 * the WIFI Extension 2.0, which is available from firmware version 2.0.1. Note
 * that, for firmware version 2.0.3 and older, to disable the the web interface
 * the ``website_port`` parameter must be set to 1 and greater than 1 to enable
 * the web interface. For firmware version 2.0.4 and later, setting this parameter
 * to 1 will enable the web interface and setting it to 0 will disable the web
 * interface.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_configuration(Master *master, uint16_t port, uint16_t websocket_port, uint16_t website_port, uint8_t phy_mode, uint8_t sleep_mode, uint8_t website);

/**
 * \ingroup BrickMaster
 *
 * Returns the general configuration as set by {@link master_set_wifi2_configuration}.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_configuration(Master *master, uint16_t *ret_port, uint16_t *ret_websocket_port, uint16_t *ret_website_port, uint8_t *ret_phy_mode, uint8_t *ret_sleep_mode, uint8_t *ret_website);

/**
 * \ingroup BrickMaster
 *
 * Returns the client and access point status of the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_status(Master *master, bool *ret_client_enabled, uint8_t *ret_client_status, uint8_t ret_client_ip[4], uint8_t ret_client_subnet_mask[4], uint8_t ret_client_gateway[4], uint8_t ret_client_mac_address[6], uint32_t *ret_client_rx_count, uint32_t *ret_client_tx_count, int8_t *ret_client_rssi, bool *ret_ap_enabled, uint8_t ret_ap_ip[4], uint8_t ret_ap_subnet_mask[4], uint8_t ret_ap_gateway[4], uint8_t ret_ap_mac_address[6], uint32_t *ret_ap_rx_count, uint32_t *ret_ap_tx_count, uint8_t *ret_ap_connected_count);

/**
 * \ingroup BrickMaster
 *
 * Sets the client specific configuration of the WIFI Extension 2.0.
 * 
 * The ``enable`` parameter enables or disables the client part of the
 * WIFI Extension 2.0.
 * 
 * The ``ssid`` parameter sets the SSID (up to 32 characters) of the access point
 * to connect to.
 * 
 * If the ``ip`` parameter is set to all zero then ``subnet_mask`` and ``gateway``
 * parameters are also set to all zero and DHCP is used for IP address configuration.
 * Otherwise those three parameters can be used to configure a static IP address.
 * The default configuration is DHCP.
 * 
 * If the ``mac_address`` parameter is set to all zero then the factory MAC
 * address is used. Otherwise this parameter can be used to set a custom MAC
 * address.
 * 
 * If the ``bssid`` parameter is set to all zero then WIFI Extension 2.0 will
 * connect to any access point that matches the configured SSID. Otherwise this
 * parameter can be used to make the WIFI Extension 2.0 only connect to an
 * access point if SSID and BSSID match.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_client_configuration(Master *master, bool enable, const char *ssid, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint8_t mac_address[6], uint8_t bssid[6]);

/**
 * \ingroup BrickMaster
 *
 * Returns the client configuration as set by {@link master_set_wifi2_client_configuration}.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_client_configuration(Master *master, bool *ret_enable, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6], uint8_t ret_bssid[6]);

/**
 * \ingroup BrickMaster
 *
 * Sets the client hostname (up to 32 characters) of the WIFI Extension 2.0. The
 * hostname will be displayed by access points as the hostname in the DHCP clients
 * table.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_client_hostname(Master *master, const char *hostname);

/**
 * \ingroup BrickMaster
 *
 * Returns the client hostname as set by {@link master_set_wifi2_client_hostname}.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_client_hostname(Master *master, char ret_hostname[32]);

/**
 * \ingroup BrickMaster
 *
 * Sets the client password (up to 63 chars) for WPA/WPA2 encryption.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_client_password(Master *master, const char *password);

/**
 * \ingroup BrickMaster
 *
 * Returns the client password as set by {@link master_set_wifi2_client_password}.
 * 
 * \note
 *  Since WIFI Extension 2.0 firmware version 2.1.3 the password is not
 *  returned anymore.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_client_password(Master *master, char ret_password[64]);

/**
 * \ingroup BrickMaster
 *
 * Sets the access point specific configuration of the WIFI Extension 2.0.
 * 
 * The ``enable`` parameter enables or disables the access point part of the
 * WIFI Extension 2.0.
 * 
 * The ``ssid`` parameter sets the SSID (up to 32 characters) of the access point.
 * 
 * If the ``ip`` parameter is set to all zero then ``subnet_mask`` and ``gateway``
 * parameters are also set to all zero and DHCP is used for IP address configuration.
 * Otherwise those three parameters can be used to configure a static IP address.
 * The default configuration is DHCP.
 * 
 * The ``encryption`` parameter sets the encryption mode to be used. Possible
 * values are Open (no encryption), WEP or WPA/WPA2 PSK.
 * Use the {@link master_set_wifi2_ap_password} function to set the encryption
 * password.
 * 
 * The ``hidden`` parameter makes the access point hide or show its SSID.
 * 
 * The ``channel`` parameter sets the channel (1 to 13) of the access point.
 * 
 * If the ``mac_address`` parameter is set to all zero then the factory MAC
 * address is used. Otherwise this parameter can be used to set a custom MAC
 * address.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_ap_configuration(Master *master, bool enable, const char *ssid, uint8_t ip[4], uint8_t subnet_mask[4], uint8_t gateway[4], uint8_t encryption, bool hidden, uint8_t channel, uint8_t mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * Returns the access point configuration as set by {@link master_set_wifi2_ap_configuration}.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_ap_configuration(Master *master, bool *ret_enable, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t *ret_encryption, bool *ret_hidden, uint8_t *ret_channel, uint8_t ret_mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * Sets the access point password (at least 8 and up to 63 chars) for the configured encryption
 * mode, see {@link master_set_wifi2_ap_configuration}.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_set_wifi2_ap_password(Master *master, const char *password);

/**
 * \ingroup BrickMaster
 *
 * Returns the access point password as set by {@link master_set_wifi2_ap_password}.
 * 
 * \note
 *  Since WIFI Extension 2.0 firmware version 2.1.3 the password is not
 *  returned anymore.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_ap_password(Master *master, char ret_password[64]);

/**
 * \ingroup BrickMaster
 *
 * All configuration functions for the WIFI Extension 2.0 do not change the
 * values permanently. After configuration this function has to be called to
 * permanently store the values.
 * 
 * The values are stored in the EEPROM and only applied on startup. That means
 * you have to restart the Master Brick after configuration.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_save_wifi2_configuration(Master *master, uint8_t *ret_result);

/**
 * \ingroup BrickMaster
 *
 * Returns the current version of the WIFI Extension 2.0 firmware.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_get_wifi2_firmware_version(Master *master, uint8_t ret_firmware_version[3]);

/**
 * \ingroup BrickMaster
 *
 * Turns the green status LED of the WIFI Extension 2.0 on.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_enable_wifi2_status_led(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Turns the green status LED of the WIFI Extension 2.0 off.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_disable_wifi2_status_led(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the green status LED of the WIFI Extension 2.0 is turned on.
 * 
 * .. versionadded:: 2.4.0$nbsp;(Firmware)
 */
int master_is_wifi2_status_led_enabled(Master *master, bool *ret_enabled);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Sets the mesh specific configuration of the WIFI Extension 2.0.
 * 
 * The ``enable`` parameter enables or disables the mesh part of the
 * WIFI Extension 2.0. The mesh part cannot be
 * enabled together with the client and access-point part.
 * 
 * If the ``root_ip`` parameter is set to all zero then ``root_subnet_mask``
 * and ``root_gateway`` parameters are also set to all zero and DHCP is used for
 * IP address configuration. Otherwise those three parameters can be used to
 * configure a static IP address. The default configuration is DHCP.
 * 
 * If the ``router_bssid`` parameter is set to all zero then the information is
 * taken from Wi-Fi scan when connecting the SSID as set by
 * {@link master_set_wifi2_mesh_router_ssid}. This only works if the the SSID is not hidden.
 * In case the router has hidden SSID this parameter must be specified, otherwise
 * the node will not be able to reach the mesh router.
 * 
 * The ``group_id`` and the ``group_ssid_prefix`` parameters identifies a
 * particular mesh network and nodes configured with same ``group_id`` and the
 * ``group_ssid_prefix`` are considered to be in the same mesh network.
 * 
 * The ``gateway_ip`` and the ``gateway_port`` parameters specifies the location
 * of the brickd that supports mesh feature.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_set_wifi2_mesh_configuration(Master *master, bool enable, uint8_t root_ip[4], uint8_t root_subnet_mask[4], uint8_t root_gateway[4], uint8_t router_bssid[6], uint8_t group_id[6], const char *group_ssid_prefix, uint8_t gateway_ip[4], uint16_t gateway_port);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the mesh configuration as set by {@link master_set_wifi2_mesh_configuration}.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_configuration(Master *master, bool *ret_enable, uint8_t ret_root_ip[4], uint8_t ret_root_subnet_mask[4], uint8_t ret_root_gateway[4], uint8_t ret_router_bssid[6], uint8_t ret_group_id[6], char ret_group_ssid_prefix[16], uint8_t ret_gateway_ip[4], uint16_t *ret_gateway_port);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Sets the mesh router SSID of the WIFI Extension 2.0.
 * It is used to specify the mesh router to connect to.
 * 
 * Note that even though in the argument of this function a 32 characters long SSID
 * is allowed, in practice valid SSID should have a maximum of 31 characters. This
 * is due to a bug in the mesh library that we use in the firmware of the extension.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_set_wifi2_mesh_router_ssid(Master *master, const char *ssid);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the mesh router SSID as set by {@link master_set_wifi2_mesh_router_ssid}.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_router_ssid(Master *master, char ret_ssid[32]);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Sets the mesh router password (up to 64 characters) for WPA/WPA2 encryption.
 * The password will be used to connect to the mesh router.
 * 
 * To apply configuration changes to the WIFI Extension 2.0 the
 * {@link master_save_wifi2_configuration} function has to be called and the Master Brick
 * has to be restarted afterwards.
 * 
 * It is recommended to use the Brick Viewer to configure the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_set_wifi2_mesh_router_password(Master *master, const char *password);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the mesh router password as set by {@link master_set_wifi2_mesh_router_password}.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_router_password(Master *master, char ret_password[64]);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the common mesh status of the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_common_status(Master *master, uint8_t *ret_status, bool *ret_root_node, bool *ret_root_candidate, uint16_t *ret_connected_nodes, uint32_t *ret_rx_count, uint32_t *ret_tx_count);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the mesh client status of the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_client_status(Master *master, char ret_hostname[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * Requires WIFI Extension 2.0 firmware 2.1.0.
 * 
 * Returns the mesh AP status of the WIFI Extension 2.0.
 * 
 * .. versionadded:: 2.4.2$nbsp;(Firmware)
 */
int master_get_wifi2_mesh_ap_status(Master *master, char ret_ssid[32], uint8_t ret_ip[4], uint8_t ret_subnet_mask[4], uint8_t ret_gateway[4], uint8_t ret_mac_address[6]);

/**
 * \ingroup BrickMaster
 *
 * This function is for internal use to flash the initial
 * bootstrapper and bootloader to the Bricklets.
 * 
 * If you need to flash a boostrapper/bootloader (for exmaple
 * because you made your own Bricklet from scratch) please
 * take a look at our open source flash and test tool at
 * `https://github.com/Tinkerforge/flash-test <https://github.com/Tinkerforge/flash-test>`__
 * 
 * Don't use this function directly.
 * 
 * .. versionadded:: 2.5.0$nbsp;(Firmware)
 */
int master_set_bricklet_xmc_flash_config(Master *master, uint32_t config, uint32_t parameter1, uint32_t parameter2, uint8_t data[52], uint32_t *ret_return_value, uint8_t ret_return_data[60]);

/**
 * \ingroup BrickMaster
 *
 * This function is for internal use to flash the initial
 * bootstrapper and bootloader to the Bricklets.
 * 
 * If you need to flash a boostrapper/bootloader (for exmaple
 * because you made your own Bricklet from scratch) please
 * take a look at our open source flash and test tool at
 * `https://github.com/Tinkerforge/flash-test <https://github.com/Tinkerforge/flash-test>`__
 * 
 * Don't use this function directly.
 * 
 * .. versionadded:: 2.5.0$nbsp;(Firmware)
 */
int master_set_bricklet_xmc_flash_data(Master *master, uint8_t data[64], uint32_t *ret_return_data);

/**
 * \ingroup BrickMaster
 *
 * This function is only available in Master Brick hardware version >= 3.0.
 * 
 * Enables/disables all four Bricklets if set to true/false.
 * 
 * If you disable the Bricklets the power supply to the Bricklets will be disconnected.
 * The Bricklets will lose all configurations if disabled.
 * 
 * .. versionadded:: 2.5.0$nbsp;(Firmware)
 */
int master_set_bricklets_enabled(Master *master, bool bricklets_enabled);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the Bricklets are enabled, *false* otherwise.
 * 
 * .. versionadded:: 2.5.0$nbsp;(Firmware)
 */
int master_get_bricklets_enabled(Master *master, bool *ret_bricklets_enabled);

/**
 * \ingroup BrickMaster
 *
 * The SPITF protocol can be used with a dynamic baudrate. If the dynamic baudrate is
 * enabled, the Brick will try to adapt the baudrate for the communication
 * between Bricks and Bricklets according to the amount of data that is transferred.
 * 
 * The baudrate will be increased exponentially if lots of data is sent/received and
 * decreased linearly if little data is sent/received.
 * 
 * This lowers the baudrate in applications where little data is transferred (e.g.
 * a weather station) and increases the robustness. If there is lots of data to transfer
 * (e.g. Thermal Imaging Bricklet) it automatically increases the baudrate as needed.
 * 
 * In cases where some data has to transferred as fast as possible every few seconds
 * (e.g. RS485 Bricklet with a high baudrate but small payload) you may want to turn
 * the dynamic baudrate off to get the highest possible performance.
 * 
 * The maximum value of the baudrate can be set per port with the function
 * {@link master_set_spitfp_baudrate}. If the dynamic baudrate is disabled, the baudrate
 * as set by {@link master_set_spitfp_baudrate} will be used statically.
 * 
 * .. versionadded:: 2.4.6$nbsp;(Firmware)
 */
int master_set_spitfp_baudrate_config(Master *master, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate);

/**
 * \ingroup BrickMaster
 *
 * Returns the baudrate config, see {@link master_set_spitfp_baudrate_config}.
 * 
 * .. versionadded:: 2.4.6$nbsp;(Firmware)
 */
int master_get_spitfp_baudrate_config(Master *master, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate);

/**
 * \ingroup BrickMaster
 *
 * Returns the timeout count for the different communication methods.
 * 
 * The methods 0-2 are available for all Bricks, 3-7 only for Master Bricks.
 * 
 * This function is mostly used for debugging during development, in normal operation
 * the counters should nearly always stay at 0.
 * 
 * .. versionadded:: 2.4.3$nbsp;(Firmware)
 */
int master_get_send_timeout_count(Master *master, uint8_t communication_method, uint32_t *ret_timeout_count);

/**
 * \ingroup BrickMaster
 *
 * Sets the baudrate for a specific Bricklet port.
 * 
 * If you want to increase the throughput of Bricklets you can increase
 * the baudrate. If you get a high error count because of high
 * interference (see {@link master_get_spitfp_error_count}) you can decrease the
 * baudrate.
 * 
 * If the dynamic baudrate feature is enabled, the baudrate set by this
 * function corresponds to the maximum baudrate (see {@link master_set_spitfp_baudrate_config}).
 * 
 * Regulatory testing is done with the default baudrate. If CE compatibility
 * or similar is necessary in your applications we recommend to not change
 * the baudrate.
 * 
 * .. versionadded:: 2.4.3$nbsp;(Firmware)
 */
int master_set_spitfp_baudrate(Master *master, char bricklet_port, uint32_t baudrate);

/**
 * \ingroup BrickMaster
 *
 * Returns the baudrate for a given Bricklet port, see {@link master_set_spitfp_baudrate}.
 * 
 * .. versionadded:: 2.4.3$nbsp;(Firmware)
 */
int master_get_spitfp_baudrate(Master *master, char bricklet_port, uint32_t *ret_baudrate);

/**
 * \ingroup BrickMaster
 *
 * Returns the error count for the communication between Brick and Bricklet.
 * 
 * The errors are divided into
 * 
 * * ACK checksum errors,
 * * message checksum errors,
 * * framing errors and
 * * overflow errors.
 * 
 * The errors counts are for errors that occur on the Brick side. All
 * Bricklets have a similar function that returns the errors on the Bricklet side.
 * 
 * .. versionadded:: 2.4.3$nbsp;(Firmware)
 */
int master_get_spitfp_error_count(Master *master, char bricklet_port, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickMaster
 *
 * Enables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 * 
 * .. versionadded:: 2.3.2$nbsp;(Firmware)
 */
int master_enable_status_led(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Disables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 * 
 * .. versionadded:: 2.3.2$nbsp;(Firmware)
 */
int master_disable_status_led(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Returns *true* if the status LED is enabled, *false* otherwise.
 * 
 * .. versionadded:: 2.3.2$nbsp;(Firmware)
 */
int master_is_status_led_enabled(Master *master, bool *ret_enabled);

/**
 * \ingroup BrickMaster
 *
 * Returns the firmware and protocol version and the name of the Bricklet for a
 * given port.
 * 
 * This functions sole purpose is to allow automatic flashing of v1.x.y Bricklet
 * plugins.
 */
int master_get_protocol1_bricklet_name(Master *master, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]);

/**
 * \ingroup BrickMaster
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has an
 * accuracy of ±15%. Practically it is only useful as an indicator for
 * temperature changes.
 */
int master_get_chip_temperature(Master *master, int16_t *ret_temperature);

/**
 * \ingroup BrickMaster
 *
 * Calling this function will reset the Brick. Calling this function
 * on a Brick inside of a stack will reset the whole stack.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int master_reset(Master *master);

/**
 * \ingroup BrickMaster
 *
 * Writes 32 bytes of firmware to the bricklet attached at the given port.
 * The bytes are written to the position offset * 32.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int master_write_bricklet_plugin(Master *master, char port, uint8_t offset, uint8_t chunk[32]);

/**
 * \ingroup BrickMaster
 *
 * Reads 32 bytes of firmware from the bricklet attached at the given port.
 * The bytes are read starting at the position offset * 32.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int master_read_bricklet_plugin(Master *master, char port, uint8_t offset, uint8_t ret_chunk[32]);

/**
 * \ingroup BrickMaster
 *
 * Returns the UID, the UID where the Brick is connected to,
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position is the position in the stack from '0' (bottom) to '8' (top).
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int master_get_identity(Master *master, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
