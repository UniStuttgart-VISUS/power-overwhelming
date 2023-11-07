/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_IO4_V2_H
#define BRICKLET_IO4_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIO4V2 IO-4 Bricklet 2.0
 */

/**
 * \ingroup BrickletIO4V2
 *
 * 4-channel digital input/output
 */
typedef Device IO4V2;

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_VALUE 1

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_VALUE 2

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_SELECTED_VALUE 3

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_CONFIGURATION 4

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_CONFIGURATION 5

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_INPUT_VALUE_CALLBACK_CONFIGURATION 6

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_INPUT_VALUE_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION 8

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_ALL_INPUT_VALUE_CALLBACK_CONFIGURATION 9

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_MONOFLOP 10

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_MONOFLOP 11

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_EDGE_COUNT 12

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_EDGE_COUNT_CONFIGURATION 13

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_EDGE_COUNT_CONFIGURATION 14

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_PWM_CONFIGURATION 15

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_PWM_CONFIGURATION 16

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIO4V2
 *
 * Signature: \code void callback(uint8_t channel, bool changed, bool value, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link io4_v2_set_input_value_callback_configuration}.
 * 
 * The parameters are the channel, a value-changed indicator and the actual value
 * for the channel. The `changed` parameter is true if the value has changed since
 * the last callback.
 */
#define IO4_V2_CALLBACK_INPUT_VALUE 17

/**
 * \ingroup BrickletIO4V2
 *
 * Signature: \code void callback(bool changed[4], bool value[4], void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link io4_v2_set_all_input_value_callback_configuration}.
 * 
 * The parameters are the same as {@link io4_v2_get_value}. Additional the
 * `changed` parameter is true if the value has changed since
 * the last callback.
 */
#define IO4_V2_CALLBACK_ALL_INPUT_VALUE 18

/**
 * \ingroup BrickletIO4V2
 *
 * Signature: \code void callback(uint8_t channel, bool value, void *user_data) \endcode
 * 
 * This callback is triggered whenever a monoflop timer reaches 0. The
 * parameters contain the channel and the current value of the channel
 * (the value after the monoflop).
 */
#define IO4_V2_CALLBACK_MONOFLOP_DONE 19


/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_DIRECTION_IN 'i'

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_DIRECTION_OUT 'o'

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_EDGE_TYPE_RISING 0

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_EDGE_TYPE_FALLING 1

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_EDGE_TYPE_BOTH 2

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIO4V2
 */
#define IO4_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletIO4V2
 *
 * This constant is used to identify a IO-4 Bricklet 2.0.
 *
 * The {@link io4_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define IO4_V2_DEVICE_IDENTIFIER 2111

/**
 * \ingroup BrickletIO4V2
 *
 * This constant represents the display name of a IO-4 Bricklet 2.0.
 */
#define IO4_V2_DEVICE_DISPLAY_NAME "IO-4 Bricklet 2.0"

/**
 * \ingroup BrickletIO4V2
 *
 * Creates the device object \c io4_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void io4_v2_create(IO4V2 *io4_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIO4V2
 *
 * Removes the device object \c io4_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void io4_v2_destroy(IO4V2 *io4_v2);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the io4_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int io4_v2_get_response_expected(IO4V2 *io4_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIO4V2
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
int io4_v2_set_response_expected(IO4V2 *io4_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIO4V2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int io4_v2_set_response_expected_all(IO4V2 *io4_v2, bool response_expected);

/**
 * \ingroup BrickletIO4V2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void io4_v2_register_callback(IO4V2 *io4_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int io4_v2_get_api_version(IO4V2 *io4_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIO4V2
 *
 * Sets the output value of all four channels. A value of *true* or *false* outputs
 * logic 1 or logic 0 respectively on the corresponding channel.
 * 
 * Use {@link io4_v2_set_selected_value} to change only one output channel state.
 * 
 * For example: (True, True, False, False) will turn the channels 0-1 high and the
 * channels 2-3 low.
 * 
 * All running monoflop timers and PWMs will be aborted if this function is called.
 * 
 * \note
 *  This function does nothing for channels that are configured as input. Pull-up
 *  resistors can be switched on with {@link io4_v2_set_configuration}.
 */
int io4_v2_set_value(IO4V2 *io4_v2, bool value[4]);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the logic levels that are currently measured on the channels.
 * This function works if the channel is configured as input as well as if it is
 * configured as output.
 */
int io4_v2_get_value(IO4V2 *io4_v2, bool ret_value[4]);

/**
 * \ingroup BrickletIO4V2
 *
 * Sets the output value of a specific channel without affecting the other channels.
 * 
 * A running monoflop timer or PWM for the specific channel will be aborted if this
 * function is called.
 * 
 * \note
 *  This function does nothing for channels that are configured as input. Pull-up
 *  resistors can be switched on with {@link io4_v2_set_configuration}.
 */
int io4_v2_set_selected_value(IO4V2 *io4_v2, uint8_t channel, bool value);

/**
 * \ingroup BrickletIO4V2
 *
 * Configures the value and direction of a specific channel. Possible directions
 * are 'i' and 'o' for input and output.
 * 
 * If the direction is configured as output, the value is either high or low
 * (set as *true* or *false*).
 * 
 * If the direction is configured as input, the value is either pull-up or
 * default (set as *true* or *false*).
 * 
 * For example:
 * 
 * * (0, 'i', true) will set channel 0 as input pull-up.
 * * (1, 'i', false) will set channel 1 as input default (floating if nothing is connected).
 * * (2, 'o', true) will set channel 2 as output high.
 * * (3, 'o', false) will set channel 3 as output low.
 * 
 * A running monoflop timer or PWM for the specific channel will be aborted if this
 * function is called.
 */
int io4_v2_set_configuration(IO4V2 *io4_v2, uint8_t channel, char direction, bool value);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the channel configuration as set by {@link io4_v2_set_configuration}.
 */
int io4_v2_get_configuration(IO4V2 *io4_v2, uint8_t channel, char *ret_direction, bool *ret_value);

/**
 * \ingroup BrickletIO4V2
 *
 * This callback can be configured per channel.
 * 
 * The period is the period with which the {@link IO4_V2_CALLBACK_INPUT_VALUE}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int io4_v2_set_input_value_callback_configuration(IO4V2 *io4_v2, uint8_t channel, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the callback configuration for the given channel as set by
 * {@link io4_v2_set_input_value_callback_configuration}.
 */
int io4_v2_get_input_value_callback_configuration(IO4V2 *io4_v2, uint8_t channel, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletIO4V2
 *
 * The period is the period with which the {@link IO4_V2_CALLBACK_ALL_INPUT_VALUE}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int io4_v2_set_all_input_value_callback_configuration(IO4V2 *io4_v2, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the callback configuration as set by
 * {@link io4_v2_set_all_input_value_callback_configuration}.
 */
int io4_v2_get_all_input_value_callback_configuration(IO4V2 *io4_v2, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletIO4V2
 *
 * The first parameter is the desired state of the channel (*true* means output *high*
 * and *false* means output *low*). The second parameter indicates the time that
 * the channel should hold the state.
 * 
 * If this function is called with the parameters (true, 1500):
 * The channel will turn on and in 1.5s it will turn off again.
 * 
 * A PWM for the selected channel will be aborted if this function is called.
 * 
 * A monoflop can be used as a failsafe mechanism. For example: Lets assume you
 * have a RS485 bus and a IO-4 Bricklet 2.0 is connected to one of the slave
 * stacks. You can now call this function every second, with a time parameter
 * of two seconds. The channel will be *high* all the time. If now the RS485
 * connection is lost, the channel will turn *low* in at most two seconds.
 */
int io4_v2_set_monoflop(IO4V2 *io4_v2, uint8_t channel, bool value, uint32_t time);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns (for the given channel) the current value and the time as set by
 * {@link io4_v2_set_monoflop} as well as the remaining time until the value flips.
 * 
 * If the timer is not running currently, the remaining time will be returned
 * as 0.
 */
int io4_v2_get_monoflop(IO4V2 *io4_v2, uint8_t channel, bool *ret_value, uint32_t *ret_time, uint32_t *ret_time_remaining);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the current value of the edge counter for the selected channel. You can
 * configure the edges that are counted with {@link io4_v2_set_edge_count_configuration}.
 * 
 * If you set the reset counter to *true*, the count is set back to 0
 * directly after it is read.
 * 
 * \note
 *  Calling this function is only allowed for channels configured as input.
 */
int io4_v2_get_edge_count(IO4V2 *io4_v2, uint8_t channel, bool reset_counter, uint32_t *ret_count);

/**
 * \ingroup BrickletIO4V2
 *
 * Configures the edge counter for a specific channel.
 * 
 * The edge type parameter configures if rising edges, falling edges or
 * both are counted if the channel is configured for input. Possible edge types are:
 * 
 * * 0 = rising
 * * 1 = falling
 * * 2 = both
 * 
 * Configuring an edge counter resets its value to 0.
 * 
 * If you don't know what any of this means, just leave it at default. The
 * default configuration is very likely OK for you.
 * 
 * \note
 *  Calling this function is only allowed for channels configured as input.
 */
int io4_v2_set_edge_count_configuration(IO4V2 *io4_v2, uint8_t channel, uint8_t edge_type, uint8_t debounce);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the edge type and debounce time for the selected channel as set by
 * {@link io4_v2_set_edge_count_configuration}.
 * 
 * \note
 *  Calling this function is only allowed for channels configured as input.
 */
int io4_v2_get_edge_count_configuration(IO4V2 *io4_v2, uint8_t channel, uint8_t *ret_edge_type, uint8_t *ret_debounce);

/**
 * \ingroup BrickletIO4V2
 *
 * Activates a PWM for the given channel.
 * 
 * You need to set the channel to output before you call this function, otherwise it will
 * report an invalid parameter error. To turn the PWM off again, you can set the frequency to 0 or any other
 * function that changes a value of the channel (e.g. {@link io4_v2_set_selected_value}).
 * 
 * A running monoflop timer for the given channel will be aborted if this function
 * is called.
 */
int io4_v2_set_pwm_configuration(IO4V2 *io4_v2, uint8_t channel, uint32_t frequency, uint16_t duty_cycle);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the PWM configuration as set by {@link io4_v2_set_pwm_configuration}.
 */
int io4_v2_get_pwm_configuration(IO4V2 *io4_v2, uint8_t channel, uint32_t *ret_frequency, uint16_t *ret_duty_cycle);

/**
 * \ingroup BrickletIO4V2
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
int io4_v2_get_spitfp_error_count(IO4V2 *io4_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletIO4V2
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
int io4_v2_set_bootloader_mode(IO4V2 *io4_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the current bootloader mode, see {@link io4_v2_set_bootloader_mode}.
 */
int io4_v2_get_bootloader_mode(IO4V2 *io4_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletIO4V2
 *
 * Sets the firmware pointer for {@link io4_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int io4_v2_set_write_firmware_pointer(IO4V2 *io4_v2, uint32_t pointer);

/**
 * \ingroup BrickletIO4V2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link io4_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int io4_v2_write_firmware(IO4V2 *io4_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletIO4V2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int io4_v2_set_status_led_config(IO4V2 *io4_v2, uint8_t config);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the configuration as set by {@link io4_v2_set_status_led_config}
 */
int io4_v2_get_status_led_config(IO4V2 *io4_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int io4_v2_get_chip_temperature(IO4V2 *io4_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletIO4V2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int io4_v2_reset(IO4V2 *io4_v2);

/**
 * \ingroup BrickletIO4V2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int io4_v2_write_uid(IO4V2 *io4_v2, uint32_t uid);

/**
 * \ingroup BrickletIO4V2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int io4_v2_read_uid(IO4V2 *io4_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletIO4V2
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
int io4_v2_get_identity(IO4V2 *io4_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
