/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_RGB_LED_H
#define BRICKLET_RGB_LED_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRGBLED RGB LED Bricklet
 */

/**
 * \ingroup BrickletRGBLED
 *
 * Controls one RGB LED
 */
typedef Device RGBLED;

/**
 * \ingroup BrickletRGBLED
 */
#define RGB_LED_FUNCTION_SET_RGB_VALUE 1

/**
 * \ingroup BrickletRGBLED
 */
#define RGB_LED_FUNCTION_GET_RGB_VALUE 2

/**
 * \ingroup BrickletRGBLED
 */
#define RGB_LED_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickletRGBLED
 *
 * This constant is used to identify a RGB LED Bricklet.
 *
 * The {@link rgb_led_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define RGB_LED_DEVICE_IDENTIFIER 271

/**
 * \ingroup BrickletRGBLED
 *
 * This constant represents the display name of a RGB LED Bricklet.
 */
#define RGB_LED_DEVICE_DISPLAY_NAME "RGB LED Bricklet"

/**
 * \ingroup BrickletRGBLED
 *
 * Creates the device object \c rgb_led with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void rgb_led_create(RGBLED *rgb_led, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRGBLED
 *
 * Removes the device object \c rgb_led from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void rgb_led_destroy(RGBLED *rgb_led);

/**
 * \ingroup BrickletRGBLED
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the rgb_led_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int rgb_led_get_response_expected(RGBLED *rgb_led, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRGBLED
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
int rgb_led_set_response_expected(RGBLED *rgb_led, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRGBLED
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int rgb_led_set_response_expected_all(RGBLED *rgb_led, bool response_expected);


/**
 * \ingroup BrickletRGBLED
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int rgb_led_get_api_version(RGBLED *rgb_led, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRGBLED
 *
 * Sets the *r*, *g* and *b* values for the LED.
 */
int rgb_led_set_rgb_value(RGBLED *rgb_led, uint8_t r, uint8_t g, uint8_t b);

/**
 * \ingroup BrickletRGBLED
 *
 * Returns the *r*, *g* and *b* values of the LED as set by {@link rgb_led_set_rgb_value}.
 */
int rgb_led_get_rgb_value(RGBLED *rgb_led, uint8_t *ret_r, uint8_t *ret_g, uint8_t *ret_b);

/**
 * \ingroup BrickletRGBLED
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
int rgb_led_get_identity(RGBLED *rgb_led, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
