/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_INDUSTRIAL_ANALOG_OUT_V2_H
#define BRICKLET_INDUSTRIAL_ANALOG_OUT_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletIndustrialAnalogOutV2 Industrial Analog Out Bricklet 2.0
 */

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Generates configurable DC voltage and current, 0V to 10V and 4mA to 20mA
 */
typedef Device IndustrialAnalogOutV2;

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_ENABLED 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_ENABLED 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_VOLTAGE 3

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_VOLTAGE 4

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_CURRENT 5

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_CURRENT 6

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_CONFIGURATION 7

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_CONFIGURATION 8

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_OUT_LED_CONFIG 9

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_OUT_LED_CONFIG 10

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_OUT_LED_STATUS_CONFIG 11

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_OUT_LED_STATUS_CONFIG 12

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_VOLTAGE_RANGE_0_TO_5V 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_VOLTAGE_RANGE_0_TO_10V 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_CURRENT_RANGE_4_TO_20MA 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_CURRENT_RANGE_0_TO_20MA 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_CURRENT_RANGE_0_TO_24MA 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_CONFIG_SHOW_OUT_STATUS 3

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_STATUS_CONFIG_THRESHOLD 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_OUT_LED_STATUS_CONFIG_INTENSITY 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 */
#define INDUSTRIAL_ANALOG_OUT_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * This constant is used to identify a Industrial Analog Out Bricklet 2.0.
 *
 * The {@link industrial_analog_out_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define INDUSTRIAL_ANALOG_OUT_V2_DEVICE_IDENTIFIER 2116

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * This constant represents the display name of a Industrial Analog Out Bricklet 2.0.
 */
#define INDUSTRIAL_ANALOG_OUT_V2_DEVICE_DISPLAY_NAME "Industrial Analog Out Bricklet 2.0"

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Creates the device object \c industrial_analog_out_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void industrial_analog_out_v2_create(IndustrialAnalogOutV2 *industrial_analog_out_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Removes the device object \c industrial_analog_out_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void industrial_analog_out_v2_destroy(IndustrialAnalogOutV2 *industrial_analog_out_v2);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the industrial_analog_out_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int industrial_analog_out_v2_get_response_expected(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
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
int industrial_analog_out_v2_set_response_expected(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int industrial_analog_out_v2_set_response_expected_all(IndustrialAnalogOutV2 *industrial_analog_out_v2, bool response_expected);


/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int industrial_analog_out_v2_get_api_version(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Enables/disables the output of voltage and current.
 */
int industrial_analog_out_v2_set_enabled(IndustrialAnalogOutV2 *industrial_analog_out_v2, bool enabled);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns *true* if output of voltage and current is enabled, *false* otherwise.
 */
int industrial_analog_out_v2_get_enabled(IndustrialAnalogOutV2 *industrial_analog_out_v2, bool *ret_enabled);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Sets the output voltage.
 * 
 * The output voltage and output current are linked. Changing the output voltage
 * also changes the output current.
 */
int industrial_analog_out_v2_set_voltage(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t voltage);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the voltage as set by {@link industrial_analog_out_v2_set_voltage}.
 */
int industrial_analog_out_v2_get_voltage(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t *ret_voltage);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Sets the output current.
 * 
 * The output current and output voltage are linked. Changing the output current
 * also changes the output voltage.
 */
int industrial_analog_out_v2_set_current(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t current);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the current as set by {@link industrial_analog_out_v2_set_current}.
 */
int industrial_analog_out_v2_get_current(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t *ret_current);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Configures the voltage and current range.
 * 
 * Possible voltage ranges are:
 * 
 * * 0V to 5V
 * * 0V to 10V
 * 
 * Possible current ranges are:
 * 
 * * 4mA to 20mA
 * * 0mA to 20mA
 * * 0mA to 24mA
 * 
 * The resolution will always be 12 bit. This means, that the
 * precision is higher with a smaller range.
 */
int industrial_analog_out_v2_set_configuration(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t voltage_range, uint8_t current_range);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the configuration as set by {@link industrial_analog_out_v2_set_configuration}.
 */
int industrial_analog_out_v2_get_configuration(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t *ret_voltage_range, uint8_t *ret_current_range);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * You can turn the Out LED off, on or show a
 * heartbeat. You can also set the LED to "Out Status". In this mode the
 * LED can either be turned on with a pre-defined threshold or the intensity
 * of the LED can change with the output value (voltage or current).
 * 
 * You can configure the channel status behavior with {@link industrial_analog_out_v2_set_out_led_status_config}.
 */
int industrial_analog_out_v2_set_out_led_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the Out LED configuration as set by {@link industrial_analog_out_v2_set_out_led_config}
 */
int industrial_analog_out_v2_get_out_led_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Sets the Out LED status config. This config is used if the Out LED is
 * configured as "Out Status", see {@link industrial_analog_out_v2_set_out_led_config}.
 * 
 * For each channel you can choose between threshold and intensity mode.
 * 
 * In threshold mode you can define a positive or a negative threshold.
 * For a positive threshold set the "min" parameter to the threshold value in mV or
 * µA above which the LED should turn on and set the "max" parameter to 0. Example:
 * If you set a positive threshold of 5V, the LED will turn on as soon as the
 * output value exceeds 5V and turn off again if it goes below 5V.
 * For a negative threshold set the "max" parameter to the threshold value in mV or
 * µA below which the LED should turn on and set the "min" parameter to 0. Example:
 * If you set a negative threshold of 5V, the LED will turn on as soon as the
 * output value goes below 5V and the LED will turn off when the output value
 * exceeds 5V.
 * 
 * In intensity mode you can define a range mV or µA that is used to scale the brightness
 * of the LED. Example with min=2V, max=8V: The LED is off at 2V and below, on at
 * 8V and above and the brightness is linearly scaled between the values 2V and 8V.
 * If the min value is greater than the max value, the LED brightness is scaled the
 * other way around.
 */
int industrial_analog_out_v2_set_out_led_status_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t min, uint16_t max, uint8_t config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the Out LED status configuration as set by {@link industrial_analog_out_v2_set_out_led_status_config}.
 */
int industrial_analog_out_v2_get_out_led_status_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint16_t *ret_min, uint16_t *ret_max, uint8_t *ret_config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
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
int industrial_analog_out_v2_get_spitfp_error_count(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
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
int industrial_analog_out_v2_set_bootloader_mode(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the current bootloader mode, see {@link industrial_analog_out_v2_set_bootloader_mode}.
 */
int industrial_analog_out_v2_get_bootloader_mode(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Sets the firmware pointer for {@link industrial_analog_out_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int industrial_analog_out_v2_set_write_firmware_pointer(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint32_t pointer);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link industrial_analog_out_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int industrial_analog_out_v2_write_firmware(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int industrial_analog_out_v2_set_status_led_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the configuration as set by {@link industrial_analog_out_v2_set_status_led_config}
 */
int industrial_analog_out_v2_get_status_led_config(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int industrial_analog_out_v2_get_chip_temperature(IndustrialAnalogOutV2 *industrial_analog_out_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int industrial_analog_out_v2_reset(IndustrialAnalogOutV2 *industrial_analog_out_v2);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int industrial_analog_out_v2_write_uid(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint32_t uid);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int industrial_analog_out_v2_read_uid(IndustrialAnalogOutV2 *industrial_analog_out_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletIndustrialAnalogOutV2
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
int industrial_analog_out_v2_get_identity(IndustrialAnalogOutV2 *industrial_analog_out_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
