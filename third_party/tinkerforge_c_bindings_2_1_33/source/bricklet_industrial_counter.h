/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_COUNTER_H
#define BRICKLET_INDUSTRIAL_COUNTER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialCounter Industrial Counter Bricklet
 */

/**
 * \ingroup BrickletIndustrialCounter
 *
 * 4 channel counter up to 4MHz
 */
typedef Device IndustrialCounter;

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER 4

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_SIGNAL_DATA 5

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA 6

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_ACTIVE 7

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_ACTIVE 8

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_ACTIVE 9

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_ACTIVE 10

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_COUNTER_CONFIGURATION 11

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_COUNTER_CONFIGURATION 12

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_COUNTER_CALLBACK_CONFIGURATION 13

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_COUNTER_CALLBACK_CONFIGURATION 14

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION 15

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_ALL_SIGNAL_DATA_CALLBACK_CONFIGURATION 16

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_CHANNEL_LED_CONFIG 17

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_CHANNEL_LED_CONFIG 18

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_RESET 243

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Signature: \code void callback(int64_t counter[4], void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link industrial_counter_set_all_counter_callback_configuration}.
 * 
 * The parameters are the same as {@link industrial_counter_get_all_counter}.
 */
#define INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER 19

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Signature: \code void callback(uint16_t duty_cycle[4], uint64_t period[4], uint32_t frequency[4], bool value[4], void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link industrial_counter_set_all_signal_data_callback_configuration}.
 * 
 * The parameters are the same as {@link industrial_counter_get_all_signal_data}.
 */
#define INDUSTRIAL_COUNTER_CALLBACK_ALL_SIGNAL_DATA 20


/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_0 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_1 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_2 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_3 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_EDGE_RISING 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_EDGE_FALLING 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_EDGE_BOTH 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_DIRECTION_UP 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_DIRECTION_DOWN 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_DIRECTION_EXTERNAL_UP 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_COUNT_DIRECTION_EXTERNAL_DOWN 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_1 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_2 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_4 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_8 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_16 4

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_32 5

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_64 6

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_128 7

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_256 8

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_512 9

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_1024 10

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_2048 11

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_4096 12

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_8192 13

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_16384 14

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_DUTY_CYCLE_PRESCALER_32768 15

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_128_MS 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_256_MS 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_512_MS 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_1024_MS 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_2048_MS 4

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_4096_MS 5

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_8192_MS 6

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_16384_MS 7

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_FREQUENCY_INTEGRATION_TIME_32768_MS 8

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_CHANNEL_LED_CONFIG_SHOW_CHANNEL_STATUS 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIndustrialCounter
 */
#define INDUSTRIAL_COUNTER_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletIndustrialCounter
 *
 * This constant is used to identify a Industrial Counter Bricklet.
 *
 * The {@link industrial_counter_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_COUNTER_DEVICE_IDENTIFIER 293

/**
 * \ingroup BrickletIndustrialCounter
 *
 * This constant represents the display name of a Industrial Counter Bricklet.
 */
#define INDUSTRIAL_COUNTER_DEVICE_DISPLAY_NAME "Industrial Counter Bricklet"

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Creates the device object \c industrial_counter with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_counter_create(IndustrialCounter *industrial_counter, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Removes the device object \c industrial_counter from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_counter_destroy(IndustrialCounter *industrial_counter);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_counter_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_counter_get_response_expected(IndustrialCounter *industrial_counter, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialCounter
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
int industrial_counter_set_response_expected(IndustrialCounter *industrial_counter, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_counter_set_response_expected_all(IndustrialCounter *industrial_counter, bool response_expected);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void industrial_counter_register_callback(IndustrialCounter *industrial_counter, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_counter_get_api_version(IndustrialCounter *industrial_counter, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the current counter value for the given channel.
 */
int industrial_counter_get_counter(IndustrialCounter *industrial_counter, uint8_t channel, int64_t *ret_counter);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the current counter values for all four channels.
 */
int industrial_counter_get_all_counter(IndustrialCounter *industrial_counter, int64_t ret_counter[4]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Sets the counter value for the given channel.
 * 
 * The default value for the counters on startup is 0.
 */
int industrial_counter_set_counter(IndustrialCounter *industrial_counter, uint8_t channel, int64_t counter);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Sets the counter values for all four channels.
 * 
 * The default value for the counters on startup is 0.
 */
int industrial_counter_set_all_counter(IndustrialCounter *industrial_counter, int64_t counter[4]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the signal data (duty cycle, period, frequency and value) for the
 * given channel.
 */
int industrial_counter_get_signal_data(IndustrialCounter *industrial_counter, uint8_t channel, uint16_t *ret_duty_cycle, uint64_t *ret_period, uint32_t *ret_frequency, bool *ret_value);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the signal data (duty cycle, period, frequency and value) for all four
 * channels.
 */
int industrial_counter_get_all_signal_data(IndustrialCounter *industrial_counter, uint16_t ret_duty_cycle[4], uint64_t ret_period[4], uint32_t ret_frequency[4], bool ret_value[4]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Activates/deactivates the counter of the given channel.
 * 
 * true = activate, false = deactivate.
 * 
 * By default all channels are activated.
 */
int industrial_counter_set_counter_active(IndustrialCounter *industrial_counter, uint8_t channel, bool active);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Activates/deactivates the counter of all four channels.
 * 
 * true = activate, false = deactivate.
 * 
 * By default all channels are activated.
 */
int industrial_counter_set_all_counter_active(IndustrialCounter *industrial_counter, bool active[4]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the activation state of the given channel.
 * 
 * true = activated, false = deactivated.
 */
int industrial_counter_get_counter_active(IndustrialCounter *industrial_counter, uint8_t channel, bool *ret_active);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the activation state of all four channels.
 * 
 * true = activated, false = deactivated.
 */
int industrial_counter_get_all_counter_active(IndustrialCounter *industrial_counter, bool ret_active[4]);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Sets the counter configuration for the given channel.
 * 
 * * Count Edge: Counter can count on rising, falling or both edges.
 * * Count Direction: Counter can count up or down. You can also use
 *   another channel as direction input, see
 *   `here <https://www.tinkerforge.com/en/doc/Hardware/Bricklets/Industrial_Counter.html#external-count-direction>`__
 *   for details.
 * * Duty Cycle Prescaler: Sets a divider for the internal clock. See
 *   `here <https://www.tinkerforge.com/en/doc/Hardware/Bricklets/Industrial_Counter.html#duty-cycle-prescaler-and-frequency-integration-time>`__
 *   for details.
 * * Frequency Integration Time: Sets the integration time for the
 *   frequency measurement. See
 *   `here <https://www.tinkerforge.com/en/doc/Hardware/Bricklets/Industrial_Counter.html#duty-cycle-prescaler-and-frequency-integration-time>`__
 *   for details.
 */
int industrial_counter_set_counter_configuration(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t count_edge, uint8_t count_direction, uint8_t duty_cycle_prescaler, uint8_t frequency_integration_time);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the counter configuration as set by {@link industrial_counter_set_counter_configuration}.
 */
int industrial_counter_get_counter_configuration(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t *ret_count_edge, uint8_t *ret_count_direction, uint8_t *ret_duty_cycle_prescaler, uint8_t *ret_frequency_integration_time);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * The period is the period with which the {@link INDUSTRIAL_COUNTER_CALLBACK_ALL_COUNTER}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int industrial_counter_set_all_counter_callback_configuration(IndustrialCounter *industrial_counter, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the callback configuration as set by
 * {@link industrial_counter_set_all_counter_callback_configuration}.
 */
int industrial_counter_get_all_counter_callback_configuration(IndustrialCounter *industrial_counter, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * The period is the period with which the {@link INDUSTRIAL_COUNTER_CALLBACK_ALL_SIGNAL_DATA}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int industrial_counter_set_all_signal_data_callback_configuration(IndustrialCounter *industrial_counter, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the callback configuration as set by
 * {@link industrial_counter_set_all_signal_data_callback_configuration}.
 */
int industrial_counter_get_all_signal_data_callback_configuration(IndustrialCounter *industrial_counter, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Each channel has a corresponding LED. You can turn the LED off, on or show a
 * heartbeat. You can also set the LED to "Channel Status". In this mode the
 * LED is on if the channel is high and off otherwise.
 */
int industrial_counter_set_channel_led_config(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t config);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the channel LED configuration as set by {@link industrial_counter_set_channel_led_config}
 */
int industrial_counter_get_channel_led_config(IndustrialCounter *industrial_counter, uint8_t channel, uint8_t *ret_config);

/**
 * \ingroup BrickletIndustrialCounter
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
int industrial_counter_get_spitfp_error_count(IndustrialCounter *industrial_counter, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletIndustrialCounter
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
int industrial_counter_set_bootloader_mode(IndustrialCounter *industrial_counter, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the current bootloader mode, see {@link industrial_counter_set_bootloader_mode}.
 */
int industrial_counter_get_bootloader_mode(IndustrialCounter *industrial_counter, uint8_t *ret_mode);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Sets the firmware pointer for {@link industrial_counter_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int industrial_counter_set_write_firmware_pointer(IndustrialCounter *industrial_counter, uint32_t pointer);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link industrial_counter_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int industrial_counter_write_firmware(IndustrialCounter *industrial_counter, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int industrial_counter_set_status_led_config(IndustrialCounter *industrial_counter, uint8_t config);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the configuration as set by {@link industrial_counter_set_status_led_config}
 */
int industrial_counter_get_status_led_config(IndustrialCounter *industrial_counter, uint8_t *ret_config);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int industrial_counter_get_chip_temperature(IndustrialCounter *industrial_counter, int16_t *ret_temperature);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int industrial_counter_reset(IndustrialCounter *industrial_counter);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int industrial_counter_write_uid(IndustrialCounter *industrial_counter, uint32_t uid);

/**
 * \ingroup BrickletIndustrialCounter
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int industrial_counter_read_uid(IndustrialCounter *industrial_counter, uint32_t *ret_uid);

/**
 * \ingroup BrickletIndustrialCounter
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
int industrial_counter_get_identity(IndustrialCounter *industrial_counter, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
