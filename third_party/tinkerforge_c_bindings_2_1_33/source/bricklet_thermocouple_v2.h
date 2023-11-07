/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_THERMOCOUPLE_V2_H
#define BRICKLET_THERMOCOUPLE_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletThermocoupleV2 Thermocouple Bricklet 2.0
 */

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Measures temperature with thermocouples
 */
typedef Device ThermocoupleV2;

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_TEMPERATURE 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION 3

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_SET_CONFIGURATION 5

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_CONFIGURATION 6

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_ERROR_STATE 7

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Signature: \code void callback(int32_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link thermocouple_v2_set_temperature_callback_configuration}.
 * 
 * The parameter is the same as {@link thermocouple_v2_get_temperature}.
 */
#define THERMOCOUPLE_V2_CALLBACK_TEMPERATURE 4

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Signature: \code void callback(bool over_under, bool open_circuit, void *user_data) \endcode
 * 
 * This Callback is triggered every time the error state changes
 * (see {@link thermocouple_v2_get_error_state}).
 */
#define THERMOCOUPLE_V2_CALLBACK_ERROR_STATE 8


/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_AVERAGING_1 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_AVERAGING_2 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_AVERAGING_4 4

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_AVERAGING_8 8

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_AVERAGING_16 16

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_B 0

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_E 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_J 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_K 3

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_N 4

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_R 5

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_S 6

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_T 7

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_G8 8

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_TYPE_G32 9

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FILTER_OPTION_50HZ 0

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_FILTER_OPTION_60HZ 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletThermocoupleV2
 */
#define THERMOCOUPLE_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletThermocoupleV2
 *
 * This constant is used to identify a Thermocouple Bricklet 2.0.
 *
 * The {@link thermocouple_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define THERMOCOUPLE_V2_DEVICE_IDENTIFIER 2109

/**
 * \ingroup BrickletThermocoupleV2
 *
 * This constant represents the display name of a Thermocouple Bricklet 2.0.
 */
#define THERMOCOUPLE_V2_DEVICE_DISPLAY_NAME "Thermocouple Bricklet 2.0"

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Creates the device object \c thermocouple_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void thermocouple_v2_create(ThermocoupleV2 *thermocouple_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Removes the device object \c thermocouple_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void thermocouple_v2_destroy(ThermocoupleV2 *thermocouple_v2);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the thermocouple_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int thermocouple_v2_get_response_expected(ThermocoupleV2 *thermocouple_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletThermocoupleV2
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
int thermocouple_v2_set_response_expected(ThermocoupleV2 *thermocouple_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int thermocouple_v2_set_response_expected_all(ThermocoupleV2 *thermocouple_v2, bool response_expected);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void thermocouple_v2_register_callback(ThermocoupleV2 *thermocouple_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int thermocouple_v2_get_api_version(ThermocoupleV2 *thermocouple_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the temperature of the thermocouple. The value is given in °C/100,
 * e.g. a value of 4223 means that a temperature of 42.23 °C is measured.
 * 
 * If you want to get the temperature periodically, it is recommended
 * to use the {@link THERMOCOUPLE_V2_CALLBACK_TEMPERATURE} callback and set the period with
 * {@link thermocouple_v2_set_temperature_callback_configuration}.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link THERMOCOUPLE_V2_CALLBACK_TEMPERATURE} callback. You can set the callback configuration
 * with {@link thermocouple_v2_set_temperature_callback_configuration}.
 */
int thermocouple_v2_get_temperature(ThermocoupleV2 *thermocouple_v2, int32_t *ret_temperature);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * The period is the period with which the {@link THERMOCOUPLE_V2_CALLBACK_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change
 * within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * It is furthermore possible to constrain the callback with thresholds.
 * 
 * The `option`-parameter together with min/max sets a threshold for the {@link THERMOCOUPLE_V2_CALLBACK_TEMPERATURE} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Threshold is turned off"
 *  "'o'",    "Threshold is triggered when the value is *outside* the min and max values"
 *  "'i'",    "Threshold is triggered when the value is *inside* or equal to the min and max values"
 *  "'<'",    "Threshold is triggered when the value is smaller than the min value (max is ignored)"
 *  "'>'",    "Threshold is triggered when the value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * If the option is set to 'x' (threshold turned off) the callback is triggered with the fixed period.
 */
int thermocouple_v2_set_temperature_callback_configuration(ThermocoupleV2 *thermocouple_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the callback configuration as set by {@link thermocouple_v2_set_temperature_callback_configuration}.
 */
int thermocouple_v2_get_temperature_callback_configuration(ThermocoupleV2 *thermocouple_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * You can configure averaging size, thermocouple type and frequency
 * filtering.
 * 
 * Available averaging sizes are 1, 2, 4, 8 and 16 samples.
 * 
 * As thermocouple type you can use B, E, J, K, N, R, S and T. If you have a
 * different thermocouple or a custom thermocouple you can also use
 * G8 and G32. With these types the returned value will not be in °C/100,
 * it will be calculated by the following formulas:
 * 
 * * G8: ``value = 8 * 1.6 * 2^17 * Vin``
 * * G32: ``value = 32 * 1.6 * 2^17 * Vin``
 * 
 * where Vin is the thermocouple input voltage.
 * 
 * The frequency filter can be either configured to 50Hz or to 60Hz. You should
 * configure it according to your utility frequency.
 * 
 * The conversion time depends on the averaging and filter configuration, it can
 * be calculated as follows:
 * 
 * * 60Hz: ``time = 82 + (samples - 1) * 16.67``
 * * 50Hz: ``time = 98 + (samples - 1) * 20``
 */
int thermocouple_v2_set_configuration(ThermocoupleV2 *thermocouple_v2, uint8_t averaging, uint8_t thermocouple_type, uint8_t filter);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the configuration as set by {@link thermocouple_v2_set_configuration}.
 */
int thermocouple_v2_get_configuration(ThermocoupleV2 *thermocouple_v2, uint8_t *ret_averaging, uint8_t *ret_thermocouple_type, uint8_t *ret_filter);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the current error state. There are two possible errors:
 * 
 * * Over/Under Voltage and
 * * Open Circuit.
 * 
 * Over/Under Voltage happens for voltages below 0V or above 3.3V. In this case
 * it is very likely that your thermocouple is defective. An Open Circuit error
 * indicates that there is no thermocouple connected.
 * 
 * You can use the {@link THERMOCOUPLE_V2_CALLBACK_ERROR_STATE} callback to automatically get triggered
 * when the error state changes.
 */
int thermocouple_v2_get_error_state(ThermocoupleV2 *thermocouple_v2, bool *ret_over_under, bool *ret_open_circuit);

/**
 * \ingroup BrickletThermocoupleV2
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
 * The errors counts are for errors that occur on the Bricklet side. All
 * Bricks have a similar function that returns the errors on the Brick side.
 */
int thermocouple_v2_get_spitfp_error_count(ThermocoupleV2 *thermocouple_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Sets the bootloader mode and returns the status after the requested
 * mode change was instigated.
 * 
 * You can change from bootloader mode to firmware mode and vice versa. A change
 * from bootloader mode to firmware mode will only take place if the entry function,
 * device identifier and CRC are present and correct.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int thermocouple_v2_set_bootloader_mode(ThermocoupleV2 *thermocouple_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the current bootloader mode, see {@link thermocouple_v2_set_bootloader_mode}.
 */
int thermocouple_v2_get_bootloader_mode(ThermocoupleV2 *thermocouple_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Sets the firmware pointer for {@link thermocouple_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int thermocouple_v2_set_write_firmware_pointer(ThermocoupleV2 *thermocouple_v2, uint32_t pointer);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link thermocouple_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int thermocouple_v2_write_firmware(ThermocoupleV2 *thermocouple_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int thermocouple_v2_set_status_led_config(ThermocoupleV2 *thermocouple_v2, uint8_t config);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the configuration as set by {@link thermocouple_v2_set_status_led_config}
 */
int thermocouple_v2_get_status_led_config(ThermocoupleV2 *thermocouple_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int thermocouple_v2_get_chip_temperature(ThermocoupleV2 *thermocouple_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int thermocouple_v2_reset(ThermocoupleV2 *thermocouple_v2);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int thermocouple_v2_write_uid(ThermocoupleV2 *thermocouple_v2, uint32_t uid);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int thermocouple_v2_read_uid(ThermocoupleV2 *thermocouple_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletThermocoupleV2
 *
 * Returns the UID, the UID where the Bricklet is connected to,
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position can be 'a', 'b', 'c', 'd', 'e', 'f', 'g' or 'h' (Bricklet Port).
 * A Bricklet connected to an :ref:`Isolator Bricklet <isolator_bricklet>` is always at
 * position 'z'.
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int thermocouple_v2_get_identity(ThermocoupleV2 *thermocouple_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
