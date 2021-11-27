/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_HUMIDITY_V2_H
#define BRICKLET_HUMIDITY_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletHumidityV2 Humidity Bricklet 2.0
 */

/**
 * \ingroup BrickletHumidityV2
 *
 * Measures relative humidity
 */
typedef Device HumidityV2;

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_HUMIDITY 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_HUMIDITY_CALLBACK_CONFIGURATION 2

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_HUMIDITY_CALLBACK_CONFIGURATION 3

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_TEMPERATURE 5

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION 6

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_HEATER_CONFIGURATION 9

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_HEATER_CONFIGURATION 10

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_MOVING_AVERAGE_CONFIGURATION 11

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_MOVING_AVERAGE_CONFIGURATION 12

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_SAMPLES_PER_SECOND 13

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_SAMPLES_PER_SECOND 14

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletHumidityV2
 *
 * Signature: \code void callback(uint16_t humidity, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link humidity_v2_set_humidity_callback_configuration}.
 * 
 * The parameter is the same as {@link humidity_v2_get_humidity}.
 */
#define HUMIDITY_V2_CALLBACK_HUMIDITY 4

/**
 * \ingroup BrickletHumidityV2
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link humidity_v2_set_temperature_callback_configuration}.
 * 
 * The parameter is the same as {@link humidity_v2_get_temperature}.
 */
#define HUMIDITY_V2_CALLBACK_TEMPERATURE 8


/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_HEATER_CONFIG_DISABLED 0

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_HEATER_CONFIG_ENABLED 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_20 0

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_10 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_5 2

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_1 3

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_02 4

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_SPS_01 5

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletHumidityV2
 */
#define HUMIDITY_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletHumidityV2
 *
 * This constant is used to identify a Humidity Bricklet 2.0.
 *
 * The {@link humidity_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define HUMIDITY_V2_DEVICE_IDENTIFIER 283

/**
 * \ingroup BrickletHumidityV2
 *
 * This constant represents the display name of a Humidity Bricklet 2.0.
 */
#define HUMIDITY_V2_DEVICE_DISPLAY_NAME "Humidity Bricklet 2.0"

/**
 * \ingroup BrickletHumidityV2
 *
 * Creates the device object \c humidity_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void humidity_v2_create(HumidityV2 *humidity_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletHumidityV2
 *
 * Removes the device object \c humidity_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void humidity_v2_destroy(HumidityV2 *humidity_v2);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the humidity_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int humidity_v2_get_response_expected(HumidityV2 *humidity_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletHumidityV2
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
int humidity_v2_set_response_expected(HumidityV2 *humidity_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletHumidityV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int humidity_v2_set_response_expected_all(HumidityV2 *humidity_v2, bool response_expected);

/**
 * \ingroup BrickletHumidityV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void humidity_v2_register_callback(HumidityV2 *humidity_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int humidity_v2_get_api_version(HumidityV2 *humidity_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the humidity measured by the sensor.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link HUMIDITY_V2_CALLBACK_HUMIDITY} callback. You can set the callback configuration
 * with {@link humidity_v2_set_humidity_callback_configuration}.
 */
int humidity_v2_get_humidity(HumidityV2 *humidity_v2, uint16_t *ret_humidity);

/**
 * \ingroup BrickletHumidityV2
 *
 * The period is the period with which the {@link HUMIDITY_V2_CALLBACK_HUMIDITY} callback is triggered
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
 * The `option`-parameter together with min/max sets a threshold for the {@link HUMIDITY_V2_CALLBACK_HUMIDITY} callback.
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
int humidity_v2_set_humidity_callback_configuration(HumidityV2 *humidity_v2, uint32_t period, bool value_has_to_change, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the callback configuration as set by {@link humidity_v2_set_humidity_callback_configuration}.
 */
int humidity_v2_get_humidity_callback_configuration(HumidityV2 *humidity_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the temperature measured by the sensor.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link HUMIDITY_V2_CALLBACK_TEMPERATURE} callback. You can set the callback configuration
 * with {@link humidity_v2_set_temperature_callback_configuration}.
 */
int humidity_v2_get_temperature(HumidityV2 *humidity_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletHumidityV2
 *
 * The period is the period with which the {@link HUMIDITY_V2_CALLBACK_TEMPERATURE} callback is triggered
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
 * The `option`-parameter together with min/max sets a threshold for the {@link HUMIDITY_V2_CALLBACK_TEMPERATURE} callback.
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
int humidity_v2_set_temperature_callback_configuration(HumidityV2 *humidity_v2, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the callback configuration as set by {@link humidity_v2_set_temperature_callback_configuration}.
 */
int humidity_v2_get_temperature_callback_configuration(HumidityV2 *humidity_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletHumidityV2
 *
 * Enables/disables the heater. The heater can be used to dry the sensor in
 * extremely wet conditions.
 */
int humidity_v2_set_heater_configuration(HumidityV2 *humidity_v2, uint8_t heater_config);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the heater configuration as set by {@link humidity_v2_set_heater_configuration}.
 */
int humidity_v2_get_heater_configuration(HumidityV2 *humidity_v2, uint8_t *ret_heater_config);

/**
 * \ingroup BrickletHumidityV2
 *
 * Sets the length of a `moving averaging <https://en.wikipedia.org/wiki/Moving_average>`__
 * for the humidity and temperature.
 * 
 * Setting the length to 1 will turn the averaging off. With less
 * averaging, there is more noise on the data.
 * 
 * New data is gathered every 50ms*. With a moving average of length 1000 the resulting
 * averaging window has a length of 50s. If you want to do long term measurements the longest
 * moving average will give the cleanest results.
 * 
 * \* In firmware version 2.0.3 we added the {@link humidity_v2_set_samples_per_second} function. It
 * configures the measurement frequency. Since high frequencies can result in self-heating
 * of th IC, changed the default value from 20 samples per second to 1. With 1 sample per second
 * a moving average length of 1000 would result in an averaging window of 1000 seconds!
 */
int humidity_v2_set_moving_average_configuration(HumidityV2 *humidity_v2, uint16_t moving_average_length_humidity, uint16_t moving_average_length_temperature);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the moving average configuration as set by {@link humidity_v2_set_moving_average_configuration}.
 */
int humidity_v2_get_moving_average_configuration(HumidityV2 *humidity_v2, uint16_t *ret_moving_average_length_humidity, uint16_t *ret_moving_average_length_temperature);

/**
 * \ingroup BrickletHumidityV2
 *
 * Sets the samples per second that are gathered by the humidity/temperature sensor HDC1080.
 * 
 * We added this function since we found out that a high measurement frequency can lead to
 * self-heating of the sensor. Which can distort the temperature measurement.
 * 
 * If you don't need a lot of measurements, you can use the lowest available measurement
 * frequency of 0.1 samples per second for the least amount of self-heating.
 * 
 * Before version 2.0.3 the default was 20 samples per second. The new default is 1 sample per second.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Plugin)
 */
int humidity_v2_set_samples_per_second(HumidityV2 *humidity_v2, uint8_t sps);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returnes the samples per second, as set by {@link humidity_v2_set_samples_per_second}.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Plugin)
 */
int humidity_v2_get_samples_per_second(HumidityV2 *humidity_v2, uint8_t *ret_sps);

/**
 * \ingroup BrickletHumidityV2
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
int humidity_v2_get_spitfp_error_count(HumidityV2 *humidity_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletHumidityV2
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
int humidity_v2_set_bootloader_mode(HumidityV2 *humidity_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the current bootloader mode, see {@link humidity_v2_set_bootloader_mode}.
 */
int humidity_v2_get_bootloader_mode(HumidityV2 *humidity_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletHumidityV2
 *
 * Sets the firmware pointer for {@link humidity_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int humidity_v2_set_write_firmware_pointer(HumidityV2 *humidity_v2, uint32_t pointer);

/**
 * \ingroup BrickletHumidityV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link humidity_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int humidity_v2_write_firmware(HumidityV2 *humidity_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletHumidityV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int humidity_v2_set_status_led_config(HumidityV2 *humidity_v2, uint8_t config);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the configuration as set by {@link humidity_v2_set_status_led_config}
 */
int humidity_v2_get_status_led_config(HumidityV2 *humidity_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int humidity_v2_get_chip_temperature(HumidityV2 *humidity_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletHumidityV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int humidity_v2_reset(HumidityV2 *humidity_v2);

/**
 * \ingroup BrickletHumidityV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int humidity_v2_write_uid(HumidityV2 *humidity_v2, uint32_t uid);

/**
 * \ingroup BrickletHumidityV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int humidity_v2_read_uid(HumidityV2 *humidity_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletHumidityV2
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
int humidity_v2_get_identity(HumidityV2 *humidity_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
