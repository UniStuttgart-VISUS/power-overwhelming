/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_ISOLATOR_H
#define BRICKLET_ISOLATOR_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIsolator Isolator Bricklet
 */

/**
 * \ingroup BrickletIsolator
 *
 * Galvanically isolates any Bricklet from any Brick
 */
typedef Device Isolator;

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_STATISTICS 1

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG 2

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG 3

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_SPITFP_BAUDRATE 4

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_SPITFP_BAUDRATE 5

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_ISOLATOR_SPITFP_ERROR_COUNT 6

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_STATISTICS_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_STATISTICS_CALLBACK_CONFIGURATION 8

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_RESET 243

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIsolator
 *
 * Signature: \code void callback(uint32_t messages_from_brick, uint32_t messages_from_bricklet, uint16_t connected_bricklet_device_identifier, char connected_bricklet_uid[8], void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link isolator_set_statistics_callback_configuration}.
 * 
 * The parameters are the same as {@link isolator_get_statistics}.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 */
#define ISOLATOR_CALLBACK_STATISTICS 9


/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIsolator
 */
#define ISOLATOR_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletIsolator
 *
 * This constant is used to identify a Isolator Bricklet.
 *
 * The {@link isolator_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ISOLATOR_DEVICE_IDENTIFIER 2122

/**
 * \ingroup BrickletIsolator
 *
 * This constant represents the display name of a Isolator Bricklet.
 */
#define ISOLATOR_DEVICE_DISPLAY_NAME "Isolator Bricklet"

/**
 * \ingroup BrickletIsolator
 *
 * Creates the device object \c isolator with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void isolator_create(Isolator *isolator, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIsolator
 *
 * Removes the device object \c isolator from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void isolator_destroy(Isolator *isolator);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the isolator_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int isolator_get_response_expected(Isolator *isolator, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIsolator
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
int isolator_set_response_expected(Isolator *isolator, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIsolator
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int isolator_set_response_expected_all(Isolator *isolator, bool response_expected);

/**
 * \ingroup BrickletIsolator
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void isolator_register_callback(Isolator *isolator, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int isolator_get_api_version(Isolator *isolator, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIsolator
 *
 * Returns statistics for the Isolator Bricklet.
 */
int isolator_get_statistics(Isolator *isolator, uint32_t *ret_messages_from_brick, uint32_t *ret_messages_from_bricklet, uint16_t *ret_connected_bricklet_device_identifier, char ret_connected_bricklet_uid[8]);

/**
 * \ingroup BrickletIsolator
 *
 * The SPITF protocol can be used with a dynamic baudrate. If the dynamic baudrate is
 * enabled, the Isolator Bricklet will try to adapt the baudrate for the communication
 * between Bricks and Bricklets according to the amount of data that is transferred.
 * 
 * The baudrate for communication config between
 * Brick and Isolator Bricklet can be set through the API of the Brick.
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
 * {@link isolator_set_spitfp_baudrate}. If the dynamic baudrate is disabled, the baudrate
 * as set by {@link isolator_set_spitfp_baudrate} will be used statically.
 */
int isolator_set_spitfp_baudrate_config(Isolator *isolator, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the baudrate config, see {@link isolator_set_spitfp_baudrate_config}.
 */
int isolator_get_spitfp_baudrate_config(Isolator *isolator, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate);

/**
 * \ingroup BrickletIsolator
 *
 * Sets the baudrate for a the communication between Isolator Bricklet
 * and the connected Bricklet. The baudrate for communication between
 * Brick and Isolator Bricklet can be set through the API of the Brick.
 * 
 * If you want to increase the throughput of Bricklets you can increase
 * the baudrate. If you get a high error count because of high
 * interference (see {@link isolator_get_spitfp_error_count}) you can decrease the
 * baudrate.
 * 
 * If the dynamic baudrate feature is enabled, the baudrate set by this
 * function corresponds to the maximum baudrate (see {@link isolator_set_spitfp_baudrate_config}).
 * 
 * Regulatory testing is done with the default baudrate. If CE compatibility
 * or similar is necessary in your applications we recommend to not change
 * the baudrate.
 */
int isolator_set_spitfp_baudrate(Isolator *isolator, uint32_t baudrate);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the baudrate, see {@link isolator_set_spitfp_baudrate}.
 */
int isolator_get_spitfp_baudrate(Isolator *isolator, uint32_t *ret_baudrate);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the error count for the communication between Isolator Bricklet and
 * the connected Bricklet. Call {@link isolator_get_spitfp_error_count} to get the
 * error count between Isolator Bricklet and Brick.
 * 
 * The errors are divided into
 * 
 * * ACK checksum errors,
 * * message checksum errors,
 * * framing errors and
 * * overflow errors.
 */
int isolator_get_isolator_spitfp_error_count(Isolator *isolator, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletIsolator
 *
 * The period is the period with which the {@link ISOLATOR_CALLBACK_STATISTICS}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 */
int isolator_set_statistics_callback_configuration(Isolator *isolator, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the callback configuration as set by
 * {@link isolator_set_statistics_callback_configuration}.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 */
int isolator_get_statistics_callback_configuration(Isolator *isolator, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletIsolator
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
int isolator_get_spitfp_error_count(Isolator *isolator, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletIsolator
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
int isolator_set_bootloader_mode(Isolator *isolator, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the current bootloader mode, see {@link isolator_set_bootloader_mode}.
 */
int isolator_get_bootloader_mode(Isolator *isolator, uint8_t *ret_mode);

/**
 * \ingroup BrickletIsolator
 *
 * Sets the firmware pointer for {@link isolator_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int isolator_set_write_firmware_pointer(Isolator *isolator, uint32_t pointer);

/**
 * \ingroup BrickletIsolator
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link isolator_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int isolator_write_firmware(Isolator *isolator, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletIsolator
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int isolator_set_status_led_config(Isolator *isolator, uint8_t config);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the configuration as set by {@link isolator_set_status_led_config}
 */
int isolator_get_status_led_config(Isolator *isolator, uint8_t *ret_config);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int isolator_get_chip_temperature(Isolator *isolator, int16_t *ret_temperature);

/**
 * \ingroup BrickletIsolator
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int isolator_reset(Isolator *isolator);

/**
 * \ingroup BrickletIsolator
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int isolator_write_uid(Isolator *isolator, uint32_t uid);

/**
 * \ingroup BrickletIsolator
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int isolator_read_uid(Isolator *isolator, uint32_t *ret_uid);

/**
 * \ingroup BrickletIsolator
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
int isolator_get_identity(Isolator *isolator, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
