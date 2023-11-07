/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_ESP32_H
#define BRICK_ESP32_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickESP32 ESP32 Brick
 */

/**
 * \ingroup BrickESP32
 *
 * ESP32 microcontroller based Brick with 6 Bricklet ports
 */
typedef Device ESP32;

/**
 * \ingroup BrickESP32
 */
#define ESP32_FUNCTION_GET_IDENTITY 255


/**
 * \ingroup BrickESP32
 *
 * This constant is used to identify a ESP32 Brick.
 *
 * The {@link esp32_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define ESP32_DEVICE_IDENTIFIER 113

/**
 * \ingroup BrickESP32
 *
 * This constant represents the display name of a ESP32 Brick.
 */
#define ESP32_DEVICE_DISPLAY_NAME "ESP32 Brick"

/**
 * \ingroup BrickESP32
 *
 * Creates the device object \c esp32 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void esp32_create(ESP32 *esp32, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickESP32
 *
 * Removes the device object \c esp32 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void esp32_destroy(ESP32 *esp32);

/**
 * \ingroup BrickESP32
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the esp32_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int esp32_get_response_expected(ESP32 *esp32, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickESP32
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
int esp32_set_response_expected(ESP32 *esp32, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickESP32
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int esp32_set_response_expected_all(ESP32 *esp32, bool response_expected);


/**
 * \ingroup BrickESP32
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int esp32_get_api_version(ESP32 *esp32, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickESP32
 *
 * Returns the UID, the UID where the Brick is connected to,
 * the position, the hardware and firmware version as well as the
 * device identifier.
 * 
 * The position is the position in the stack from '0' (bottom) to '8' (top).
 * 
 * The device identifier numbers can be found :ref:`here <device_identifier>`.
 * |device_identifier_constant|
 */
int esp32_get_identity(ESP32 *esp32, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
