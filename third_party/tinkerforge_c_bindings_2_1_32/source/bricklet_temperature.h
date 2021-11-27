/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_TEMPERATURE_H
#define BRICKLET_TEMPERATURE_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletTemperature Temperature Bricklet
 */

/**
 * \ingroup BrickletTemperature
 *
 * Measures ambient temperature with 0.5°C accuracy
 */
typedef Device Temperature;

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_TEMPERATURE 1

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_PERIOD 2

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_SET_TEMPERATURE_CALLBACK_THRESHOLD 4

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_TEMPERATURE_CALLBACK_THRESHOLD 5

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_SET_DEBOUNCE_PERIOD 6

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_DEBOUNCE_PERIOD 7

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_SET_I2C_MODE 10

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_I2C_MODE 11

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletTemperature
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link temperature_set_temperature_callback_period}. The parameter is the
 * temperature of the sensor.
 * 
 * The {@link TEMPERATURE_CALLBACK_TEMPERATURE} callback is only triggered if the temperature has changed
 * since the last triggering.
 */
#define TEMPERATURE_CALLBACK_TEMPERATURE 8

/**
 * \ingroup BrickletTemperature
 *
 * Signature: \code void callback(int16_t temperature, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link temperature_set_temperature_callback_threshold} is reached.
 * The parameter is the temperature of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link temperature_set_debounce_period}.
 */
#define TEMPERATURE_CALLBACK_TEMPERATURE_REACHED 9


/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_I2C_MODE_FAST 0

/**
 * \ingroup BrickletTemperature
 */
#define TEMPERATURE_I2C_MODE_SLOW 1

/**
 * \ingroup BrickletTemperature
 *
 * This constant is used to identify a Temperature Bricklet.
 *
 * The {@link temperature_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define TEMPERATURE_DEVICE_IDENTIFIER 216

/**
 * \ingroup BrickletTemperature
 *
 * This constant represents the display name of a Temperature Bricklet.
 */
#define TEMPERATURE_DEVICE_DISPLAY_NAME "Temperature Bricklet"

/**
 * \ingroup BrickletTemperature
 *
 * Creates the device object \c temperature with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void temperature_create(Temperature *temperature, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletTemperature
 *
 * Removes the device object \c temperature from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void temperature_destroy(Temperature *temperature);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the temperature_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int temperature_get_response_expected(Temperature *temperature, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletTemperature
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
int temperature_set_response_expected(Temperature *temperature, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletTemperature
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int temperature_set_response_expected_all(Temperature *temperature, bool response_expected);

/**
 * \ingroup BrickletTemperature
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void temperature_register_callback(Temperature *temperature, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int temperature_get_api_version(Temperature *temperature, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the temperature of the sensor.
 * 
 * If you want to get the temperature periodically, it is recommended
 * to use the {@link TEMPERATURE_CALLBACK_TEMPERATURE} callback and set the period with
 * {@link temperature_set_temperature_callback_period}.
 */
int temperature_get_temperature(Temperature *temperature, int16_t *ret_temperature);

/**
 * \ingroup BrickletTemperature
 *
 * Sets the period with which the {@link TEMPERATURE_CALLBACK_TEMPERATURE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link TEMPERATURE_CALLBACK_TEMPERATURE} callback is only triggered if the temperature has changed
 * since the last triggering.
 */
int temperature_set_temperature_callback_period(Temperature *temperature, uint32_t period);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the period as set by {@link temperature_set_temperature_callback_period}.
 */
int temperature_get_temperature_callback_period(Temperature *temperature, uint32_t *ret_period);

/**
 * \ingroup BrickletTemperature
 *
 * Sets the thresholds for the {@link TEMPERATURE_CALLBACK_TEMPERATURE_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the temperature is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the temperature is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the temperature is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the temperature is greater than the min value (max is ignored)"
 * \endverbatim
 */
int temperature_set_temperature_callback_threshold(Temperature *temperature, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the threshold as set by {@link temperature_set_temperature_callback_threshold}.
 */
int temperature_get_temperature_callback_threshold(Temperature *temperature, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletTemperature
 *
 * Sets the period with which the threshold callback
 * 
 * * {@link TEMPERATURE_CALLBACK_TEMPERATURE_REACHED}
 * 
 * is triggered, if the threshold
 * 
 * * {@link temperature_set_temperature_callback_threshold}
 * 
 * keeps being reached.
 */
int temperature_set_debounce_period(Temperature *temperature, uint32_t debounce);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the debounce period as set by {@link temperature_set_debounce_period}.
 */
int temperature_get_debounce_period(Temperature *temperature, uint32_t *ret_debounce);

/**
 * \ingroup BrickletTemperature
 *
 * Sets the I2C mode. Possible modes are:
 * 
 * * 0: Fast (400kHz)
 * * 1: Slow (100kHz)
 * 
 * If you have problems with obvious outliers in the
 * Temperature Bricklet measurements, they may be caused by EMI issues.
 * In this case it may be helpful to lower the I2C speed.
 * 
 * It is however not recommended to lower the I2C speed in applications where
 * a high throughput needs to be achieved.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int temperature_set_i2c_mode(Temperature *temperature, uint8_t mode);

/**
 * \ingroup BrickletTemperature
 *
 * Returns the I2C mode as set by {@link temperature_set_i2c_mode}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int temperature_get_i2c_mode(Temperature *temperature, uint8_t *ret_mode);

/**
 * \ingroup BrickletTemperature
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
int temperature_get_identity(Temperature *temperature, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
