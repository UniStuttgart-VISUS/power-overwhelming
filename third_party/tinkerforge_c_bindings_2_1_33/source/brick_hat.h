/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_HAT_H
#define BRICK_HAT_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickHAT HAT Brick
 */

/**
 * \ingroup BrickHAT
 *
 * HAT for Raspberry Pi with 8 Bricklets ports and real-time clock
 */
typedef Device HAT;

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_SLEEP_MODE 1

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_SLEEP_MODE 2

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_BRICKLET_POWER 3

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_BRICKLET_POWER 4

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_VOLTAGES 5

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_VOLTAGES_CALLBACK_CONFIGURATION 6

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_VOLTAGES_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_RTC_DRIVER 9

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_RTC_DRIVER 10

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_RESET 243

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_READ_UID 249

/**
 * \ingroup BrickHAT
 */
#define HAT_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickHAT
 *
 * Signature: \code void callback(uint16_t voltage_usb, uint16_t voltage_dc, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link hat_set_voltages_callback_configuration}.
 * 
 * The parameters are the same as {@link hat_get_voltages}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Firmware)
 */
#define HAT_CALLBACK_VOLTAGES 8


/**
 * \ingroup BrickHAT
 */
#define HAT_RTC_DRIVER_PCF8523 0

/**
 * \ingroup BrickHAT
 */
#define HAT_RTC_DRIVER_DS1338 1

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickHAT
 */
#define HAT_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickHAT
 */
#define HAT_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickHAT
 */
#define HAT_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickHAT
 */
#define HAT_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickHAT
 */
#define HAT_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickHAT
 *
 * This constant is used to identify a HAT Brick.
 *
 * The {@link hat_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define HAT_DEVICE_IDENTIFIER 111

/**
 * \ingroup BrickHAT
 *
 * This constant represents the display name of a HAT Brick.
 */
#define HAT_DEVICE_DISPLAY_NAME "HAT Brick"

/**
 * \ingroup BrickHAT
 *
 * Creates the device object \c hat with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void hat_create(HAT *hat, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickHAT
 *
 * Removes the device object \c hat from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void hat_destroy(HAT *hat);

/**
 * \ingroup BrickHAT
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the hat_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int hat_get_response_expected(HAT *hat, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickHAT
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
int hat_set_response_expected(HAT *hat, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickHAT
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int hat_set_response_expected_all(HAT *hat, bool response_expected);

/**
 * \ingroup BrickHAT
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void hat_register_callback(HAT *hat, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickHAT
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int hat_get_api_version(HAT *hat, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickHAT
 *
 * Sets the sleep mode.
 * 
 * \note
 *  Calling this function will cut the Raspberry Pi's power after Power Off Delay seconds.
 *  You have to shut down the operating system yourself, e.g. by calling 'sudo shutdown -h now'.
 * 
 * Parameters:
 * 
 * * Power Off Delay: Time before the RPi/Bricklets are powered off.
 * * Power Off Duration: Duration that the RPi/Bricklets stay powered off.
 * * Raspberry Pi Off: RPi is powered off if set to true.
 * * Bricklets Off: Bricklets are powered off if set to true.
 * * Enable Sleep Indicator: If set to true, the status LED will blink in a 1s interval
 *   during the whole power off duration. This will draw additional 0.3mA.
 * 
 * Example: To turn RPi and Bricklets off in 5 seconds for 10 minutes with sleep
 * indicator enabled, call (5, 60*10, true, true, true).
 * 
 * This function can also be used to implement a watchdog. To do this you can
 * write a program that calls this function once per second in a loop with
 * (10, 2, true, false, false). If the RPi crashes or gets stuck
 * the HAT will reset the RPi after 10 seconds.
 */
int hat_set_sleep_mode(HAT *hat, uint32_t power_off_delay, uint32_t power_off_duration, bool raspberry_pi_off, bool bricklets_off, bool enable_sleep_indicator);

/**
 * \ingroup BrickHAT
 *
 * Returns the sleep mode settings as set by {@link hat_set_sleep_mode}.
 */
int hat_get_sleep_mode(HAT *hat, uint32_t *ret_power_off_delay, uint32_t *ret_power_off_duration, bool *ret_raspberry_pi_off, bool *ret_bricklets_off, bool *ret_enable_sleep_indicator);

/**
 * \ingroup BrickHAT
 *
 * Set to true/false to turn the power supply of the connected Bricklets on/off.
 */
int hat_set_bricklet_power(HAT *hat, bool bricklet_power);

/**
 * \ingroup BrickHAT
 *
 * Returns the power status of the connected Bricklets as set by {@link hat_set_bricklet_power}.
 */
int hat_get_bricklet_power(HAT *hat, bool *ret_bricklet_power);

/**
 * \ingroup BrickHAT
 *
 * Returns the USB supply voltage and the DC input supply voltage.
 * 
 * There are three possible combinations:
 * 
 * * Only USB connected: The USB supply voltage will be fed back to the
 *   DC input connector. You will read the USB voltage and a slightly lower
 *   voltage on the DC input.
 * * Only DC input connected: The DC voltage will not be fed back to the
 *   USB connector. You will read the DC input voltage and the USB voltage
 *   will be 0.
 * * USB and DC input connected: You will read both voltages. In this case
 *   the USB supply will be without load, but it will work as backup if you
 *   disconnect the DC input (or if the DC input voltage falls below the
 *   USB voltage).
 */
int hat_get_voltages(HAT *hat, uint16_t *ret_voltage_usb, uint16_t *ret_voltage_dc);

/**
 * \ingroup BrickHAT
 *
 * The period is the period with which the {@link HAT_CALLBACK_VOLTAGES}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Firmware)
 */
int hat_set_voltages_callback_configuration(HAT *hat, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickHAT
 *
 * Returns the callback configuration as set by
 * {@link hat_set_voltages_callback_configuration}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Firmware)
 */
int hat_get_voltages_callback_configuration(HAT *hat, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickHAT
 *
 * Configures the RTC driver that is given to the Raspberry Pi to be used.
 * Currently there are two different RTCs used:
 * 
 * * Hardware version <= 1.5: PCF8523
 * * Hardware version 1.6: DS1338
 * 
 * The correct driver will be set during factory flashing by Tinkerforge.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Firmware)
 */
int hat_set_rtc_driver(HAT *hat, uint8_t rtc_driver);

/**
 * \ingroup BrickHAT
 *
 * Returns the RTC driver as set by {@link hat_set_rtc_driver}.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Firmware)
 */
int hat_get_rtc_driver(HAT *hat, uint8_t *ret_rtc_driver);

/**
 * \ingroup BrickHAT
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
int hat_get_spitfp_error_count(HAT *hat, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickHAT
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
int hat_set_bootloader_mode(HAT *hat, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickHAT
 *
 * Returns the current bootloader mode, see {@link hat_set_bootloader_mode}.
 */
int hat_get_bootloader_mode(HAT *hat, uint8_t *ret_mode);

/**
 * \ingroup BrickHAT
 *
 * Sets the firmware pointer for {@link hat_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int hat_set_write_firmware_pointer(HAT *hat, uint32_t pointer);

/**
 * \ingroup BrickHAT
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link hat_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int hat_write_firmware(HAT *hat, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickHAT
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int hat_set_status_led_config(HAT *hat, uint8_t config);

/**
 * \ingroup BrickHAT
 *
 * Returns the configuration as set by {@link hat_set_status_led_config}
 */
int hat_get_status_led_config(HAT *hat, uint8_t *ret_config);

/**
 * \ingroup BrickHAT
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int hat_get_chip_temperature(HAT *hat, int16_t *ret_temperature);

/**
 * \ingroup BrickHAT
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int hat_reset(HAT *hat);

/**
 * \ingroup BrickHAT
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int hat_write_uid(HAT *hat, uint32_t uid);

/**
 * \ingroup BrickHAT
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int hat_read_uid(HAT *hat, uint32_t *ret_uid);

/**
 * \ingroup BrickHAT
 *
 * Returns the UID, the UID where the HAT is connected to
 * (typically '0' as the HAT is the root device in the topology),
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The HAT (Zero) Brick is always at position 'i'.
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int hat_get_identity(HAT *hat, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
