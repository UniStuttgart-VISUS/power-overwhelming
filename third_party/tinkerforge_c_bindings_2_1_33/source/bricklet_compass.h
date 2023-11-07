/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_COMPASS_H
#define BRICKLET_COMPASS_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletCompass Compass Bricklet
 */

/**
 * \ingroup BrickletCompass
 *
 * 3-axis compass with 10 nanotesla and 0.1° resolution
 */
typedef Device Compass;

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_HEADING 1

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_HEADING_CALLBACK_CONFIGURATION 2

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_HEADING_CALLBACK_CONFIGURATION 3

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_MAGNETIC_FLUX_DENSITY 5

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION 6

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_MAGNETIC_FLUX_DENSITY_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_CONFIGURATION 9

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_CONFIGURATION 10

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_CALIBRATION 11

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_CALIBRATION 12

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_RESET 243

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletCompass
 *
 * Signature: \code void callback(int16_t heading, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link compass_set_heading_callback_configuration}.
 * 
 * The parameter is the same as {@link compass_get_heading}.
 */
#define COMPASS_CALLBACK_HEADING 4

/**
 * \ingroup BrickletCompass
 *
 * Signature: \code void callback(int32_t x, int32_t y, int32_t z, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link compass_set_magnetic_flux_density_callback_configuration}.
 * 
 * The parameters are the same as {@link compass_get_magnetic_flux_density}.
 */
#define COMPASS_CALLBACK_MAGNETIC_FLUX_DENSITY 8


/**
 * \ingroup BrickletCompass
 */
#define COMPASS_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_DATA_RATE_100HZ 0

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_DATA_RATE_200HZ 1

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_DATA_RATE_400HZ 2

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_DATA_RATE_600HZ 3

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletCompass
 */
#define COMPASS_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletCompass
 *
 * This constant is used to identify a Compass Bricklet.
 *
 * The {@link compass_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define COMPASS_DEVICE_IDENTIFIER 2153

/**
 * \ingroup BrickletCompass
 *
 * This constant represents the display name of a Compass Bricklet.
 */
#define COMPASS_DEVICE_DISPLAY_NAME "Compass Bricklet"

/**
 * \ingroup BrickletCompass
 *
 * Creates the device object \c compass with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void compass_create(Compass *compass, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletCompass
 *
 * Removes the device object \c compass from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void compass_destroy(Compass *compass);

/**
 * \ingroup BrickletCompass
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the compass_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int compass_get_response_expected(Compass *compass, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletCompass
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
int compass_set_response_expected(Compass *compass, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletCompass
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int compass_set_response_expected_all(Compass *compass, bool response_expected);

/**
 * \ingroup BrickletCompass
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void compass_register_callback(Compass *compass, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletCompass
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int compass_get_api_version(Compass *compass, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletCompass
 *
 * Returns the heading (north = 0 degree, east = 90 degree).
 * 
 * Alternatively you can use {@link compass_get_magnetic_flux_density} and calculate the
 * heading with ``heading = atan2(y, x) * 180 / PI``.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link COMPASS_CALLBACK_HEADING} callback. You can set the callback configuration
 * with {@link compass_set_heading_callback_configuration}.
 */
int compass_get_heading(Compass *compass, int16_t *ret_heading);

/**
 * \ingroup BrickletCompass
 *
 * The period is the period with which the {@link COMPASS_CALLBACK_HEADING} callback is triggered
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
 * The `option`-parameter together with min/max sets a threshold for the {@link COMPASS_CALLBACK_HEADING} callback.
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
int compass_set_heading_callback_configuration(Compass *compass, uint32_t period, bool value_has_to_change, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletCompass
 *
 * Returns the callback configuration as set by {@link compass_set_heading_callback_configuration}.
 */
int compass_get_heading_callback_configuration(Compass *compass, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletCompass
 *
 * Returns the `magnetic flux density (magnetic induction) <https://en.wikipedia.org/wiki/Magnetic_flux>`__
 * for all three axis.
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link COMPASS_CALLBACK_MAGNETIC_FLUX_DENSITY} callback. You can set the callback configuration
 * with {@link compass_set_magnetic_flux_density_callback_configuration}.
 */
int compass_get_magnetic_flux_density(Compass *compass, int32_t *ret_x, int32_t *ret_y, int32_t *ret_z);

/**
 * \ingroup BrickletCompass
 *
 * The period is the period with which the {@link COMPASS_CALLBACK_MAGNETIC_FLUX_DENSITY} callback
 * is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int compass_set_magnetic_flux_density_callback_configuration(Compass *compass, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletCompass
 *
 * Returns the callback configuration as set by
 * {@link compass_set_magnetic_flux_density_callback_configuration}.
 */
int compass_get_magnetic_flux_density_callback_configuration(Compass *compass, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletCompass
 *
 * Configures the data rate and background calibration.
 * 
 * * Data Rate: Sets the data rate that is used by the magnetometer.
 *   The lower the data rate, the lower is the noise on the data.
 * * Background Calibration: Set to *true* to enable the background
 *   calibration and *false* to turn it off. If the background calibration
 *   is enabled the sensing polarity is flipped once per second to automatically
 *   calculate and remove offset that is caused by temperature changes.
 *   This polarity flipping takes about 20ms. This means that once a second
 *   you will not get new data for a period of 20ms. We highly recommend that
 *   you keep the background calibration enabled and only disable it if the 20ms
 *   off-time is a problem in your application.
 */
int compass_set_configuration(Compass *compass, uint8_t data_rate, bool background_calibration);

/**
 * \ingroup BrickletCompass
 *
 * Returns the configuration as set by {@link compass_set_configuration}.
 */
int compass_get_configuration(Compass *compass, uint8_t *ret_data_rate, bool *ret_background_calibration);

/**
 * \ingroup BrickletCompass
 *
 * Sets offset and gain for each of the three axes.
 * 
 * The Bricklet is factory calibrated. If you want to re-calibrate the
 * Bricklet we recommend that you do the calibration through Brick Viewer.
 * 
 * The calibration is saved in non-volatile memory and only has to be
 * done once.
 */
int compass_set_calibration(Compass *compass, int16_t offset[3], int16_t gain[3]);

/**
 * \ingroup BrickletCompass
 *
 * Returns the calibration parameters as set by {@link compass_set_calibration}.
 */
int compass_get_calibration(Compass *compass, int16_t ret_offset[3], int16_t ret_gain[3]);

/**
 * \ingroup BrickletCompass
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
int compass_get_spitfp_error_count(Compass *compass, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletCompass
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
int compass_set_bootloader_mode(Compass *compass, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletCompass
 *
 * Returns the current bootloader mode, see {@link compass_set_bootloader_mode}.
 */
int compass_get_bootloader_mode(Compass *compass, uint8_t *ret_mode);

/**
 * \ingroup BrickletCompass
 *
 * Sets the firmware pointer for {@link compass_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int compass_set_write_firmware_pointer(Compass *compass, uint32_t pointer);

/**
 * \ingroup BrickletCompass
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link compass_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int compass_write_firmware(Compass *compass, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletCompass
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int compass_set_status_led_config(Compass *compass, uint8_t config);

/**
 * \ingroup BrickletCompass
 *
 * Returns the configuration as set by {@link compass_set_status_led_config}
 */
int compass_get_status_led_config(Compass *compass, uint8_t *ret_config);

/**
 * \ingroup BrickletCompass
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int compass_get_chip_temperature(Compass *compass, int16_t *ret_temperature);

/**
 * \ingroup BrickletCompass
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int compass_reset(Compass *compass);

/**
 * \ingroup BrickletCompass
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int compass_write_uid(Compass *compass, uint32_t uid);

/**
 * \ingroup BrickletCompass
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int compass_read_uid(Compass *compass, uint32_t *ret_uid);

/**
 * \ingroup BrickletCompass
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
int compass_get_identity(Compass *compass, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
