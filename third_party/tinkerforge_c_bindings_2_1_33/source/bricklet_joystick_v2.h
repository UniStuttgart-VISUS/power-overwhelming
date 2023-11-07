/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_JOYSTICK_V2_H
#define BRICKLET_JOYSTICK_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletJoystickV2 Joystick Bricklet 2.0
 */

/**
 * \ingroup BrickletJoystickV2
 *
 * 2-axis joystick with push-button
 */
typedef Device JoystickV2;

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_POSITION 1

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_IS_PRESSED 2

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_CALIBRATE 3

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_SET_POSITION_CALLBACK_CONFIGURATION 4

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_POSITION_CALLBACK_CONFIGURATION 5

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_SET_PRESSED_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_PRESSED_CALLBACK_CONFIGURATION 8

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletJoystickV2
 *
 * Signature: \code void callback(int16_t x, int16_t y, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link joystick_v2_set_position_callback_configuration}.
 * 
 * The parameters are the same as with {@link joystick_v2_get_position}.
 */
#define JOYSTICK_V2_CALLBACK_POSITION 6

/**
 * \ingroup BrickletJoystickV2
 *
 * Signature: \code void callback(bool pressed, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link joystick_v2_set_pressed_callback_configuration}.
 * 
 * The parameters are the same as with {@link joystick_v2_is_pressed}.
 */
#define JOYSTICK_V2_CALLBACK_PRESSED 9


/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletJoystickV2
 */
#define JOYSTICK_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletJoystickV2
 *
 * This constant is used to identify a Joystick Bricklet 2.0.
 *
 * The {@link joystick_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define JOYSTICK_V2_DEVICE_IDENTIFIER 2138

/**
 * \ingroup BrickletJoystickV2
 *
 * This constant represents the display name of a Joystick Bricklet 2.0.
 */
#define JOYSTICK_V2_DEVICE_DISPLAY_NAME "Joystick Bricklet 2.0"

/**
 * \ingroup BrickletJoystickV2
 *
 * Creates the device object \c joystick_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void joystick_v2_create(JoystickV2 *joystick_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletJoystickV2
 *
 * Removes the device object \c joystick_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void joystick_v2_destroy(JoystickV2 *joystick_v2);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the joystick_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int joystick_v2_get_response_expected(JoystickV2 *joystick_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletJoystickV2
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
int joystick_v2_set_response_expected(JoystickV2 *joystick_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletJoystickV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int joystick_v2_set_response_expected_all(JoystickV2 *joystick_v2, bool response_expected);

/**
 * \ingroup BrickletJoystickV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void joystick_v2_register_callback(JoystickV2 *joystick_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int joystick_v2_get_api_version(JoystickV2 *joystick_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the position of the joystick. The middle position of the joystick is x=0, y=0.
 * The returned values are averaged and calibrated (see {@link joystick_v2_calibrate}).
 * 
 * If you want to get the position periodically, it is recommended to use the
 * {@link JOYSTICK_V2_CALLBACK_POSITION} callback and set the period with
 * {@link joystick_v2_set_position_callback_configuration}.
 */
int joystick_v2_get_position(JoystickV2 *joystick_v2, int16_t *ret_x, int16_t *ret_y);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns *true* if the button is pressed and *false* otherwise.
 * 
 * If you want to get the press-state periodically, it is recommended to use the
 * {@link JOYSTICK_V2_CALLBACK_PRESSED} callback and set the period with
 * {@link joystick_v2_set_pressed_callback_configuration}.
 */
int joystick_v2_is_pressed(JoystickV2 *joystick_v2, bool *ret_pressed);

/**
 * \ingroup BrickletJoystickV2
 *
 * Calibrates the middle position of the joystick. If your Joystick Bricklet 2.0
 * does not return x=0 and y=0 in the middle position, call this function
 * while the joystick is standing still in the middle position.
 * 
 * The resulting calibration will be saved in non-volatile memory,
 * thus you only have to calibrate it once.
 */
int joystick_v2_calibrate(JoystickV2 *joystick_v2);

/**
 * \ingroup BrickletJoystickV2
 *
 * The period is the period with which the {@link JOYSTICK_V2_CALLBACK_POSITION}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after at least one of the values has changed. If the values didn't
 * change within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int joystick_v2_set_position_callback_configuration(JoystickV2 *joystick_v2, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the callback configuration as set by
 * {@link joystick_v2_set_position_callback_configuration}.
 */
int joystick_v2_get_position_callback_configuration(JoystickV2 *joystick_v2, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletJoystickV2
 *
 * The period is the period with which the {@link JOYSTICK_V2_CALLBACK_PRESSED}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after at least one of the values has changed. If the values didn't
 * change within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int joystick_v2_set_pressed_callback_configuration(JoystickV2 *joystick_v2, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the callback configuration as set by
 * {@link joystick_v2_set_pressed_callback_configuration}.
 */
int joystick_v2_get_pressed_callback_configuration(JoystickV2 *joystick_v2, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletJoystickV2
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
int joystick_v2_get_spitfp_error_count(JoystickV2 *joystick_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletJoystickV2
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
int joystick_v2_set_bootloader_mode(JoystickV2 *joystick_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the current bootloader mode, see {@link joystick_v2_set_bootloader_mode}.
 */
int joystick_v2_get_bootloader_mode(JoystickV2 *joystick_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletJoystickV2
 *
 * Sets the firmware pointer for {@link joystick_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int joystick_v2_set_write_firmware_pointer(JoystickV2 *joystick_v2, uint32_t pointer);

/**
 * \ingroup BrickletJoystickV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link joystick_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int joystick_v2_write_firmware(JoystickV2 *joystick_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletJoystickV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int joystick_v2_set_status_led_config(JoystickV2 *joystick_v2, uint8_t config);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the configuration as set by {@link joystick_v2_set_status_led_config}
 */
int joystick_v2_get_status_led_config(JoystickV2 *joystick_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int joystick_v2_get_chip_temperature(JoystickV2 *joystick_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletJoystickV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int joystick_v2_reset(JoystickV2 *joystick_v2);

/**
 * \ingroup BrickletJoystickV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int joystick_v2_write_uid(JoystickV2 *joystick_v2, uint32_t uid);

/**
 * \ingroup BrickletJoystickV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int joystick_v2_read_uid(JoystickV2 *joystick_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletJoystickV2
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
int joystick_v2_get_identity(JoystickV2 *joystick_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
