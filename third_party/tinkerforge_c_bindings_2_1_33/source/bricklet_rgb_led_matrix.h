/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_RGB_LED_MATRIX_H
#define BRICKLET_RGB_LED_MATRIX_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRGBLEDMatrix RGB LED Matrix Bricklet
 */

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * RGB LED Matrix with 8x8 pixel
 */
typedef Device RGBLEDMatrix;

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_RED 1

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_RED 2

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_GREEN 3

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_GREEN 4

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_BLUE 5

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_BLUE 6

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_FRAME_DURATION 7

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_FRAME_DURATION 8

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_DRAW_FRAME 9

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_SUPPLY_VOLTAGE 10

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_RESET 243

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Signature: \code void callback(uint32_t frame_number, void *user_data) \endcode
 * 
 * This callback is triggered as soon as a new frame write is started.
 * The LED values are double buffered, so you can send the LED values
 * for the next frame directly after this callback is triggered.
 */
#define RGB_LED_MATRIX_CALLBACK_FRAME_STARTED 11


/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletRGBLEDMatrix
 */
#define RGB_LED_MATRIX_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * This constant is used to identify a RGB LED Matrix Bricklet.
 *
 * The {@link rgb_led_matrix_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define RGB_LED_MATRIX_DEVICE_IDENTIFIER 272

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * This constant represents the display name of a RGB LED Matrix Bricklet.
 */
#define RGB_LED_MATRIX_DEVICE_DISPLAY_NAME "RGB LED Matrix Bricklet"

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Creates the device object \c rgb_led_matrix with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void rgb_led_matrix_create(RGBLEDMatrix *rgb_led_matrix, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Removes the device object \c rgb_led_matrix from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void rgb_led_matrix_destroy(RGBLEDMatrix *rgb_led_matrix);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the rgb_led_matrix_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int rgb_led_matrix_get_response_expected(RGBLEDMatrix *rgb_led_matrix, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRGBLEDMatrix
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
int rgb_led_matrix_set_response_expected(RGBLEDMatrix *rgb_led_matrix, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int rgb_led_matrix_set_response_expected_all(RGBLEDMatrix *rgb_led_matrix, bool response_expected);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void rgb_led_matrix_register_callback(RGBLEDMatrix *rgb_led_matrix, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int rgb_led_matrix_get_api_version(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the 64 red LED values of the matrix.
 */
int rgb_led_matrix_set_red(RGBLEDMatrix *rgb_led_matrix, uint8_t red[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the red LED values as set by {@link rgb_led_matrix_set_red}.
 */
int rgb_led_matrix_get_red(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_red[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the 64 green LED values of the matrix.
 */
int rgb_led_matrix_set_green(RGBLEDMatrix *rgb_led_matrix, uint8_t green[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the green LED values as set by {@link rgb_led_matrix_set_green}.
 */
int rgb_led_matrix_get_green(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_green[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the 64 blue LED values of the matrix.
 */
int rgb_led_matrix_set_blue(RGBLEDMatrix *rgb_led_matrix, uint8_t blue[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the blue LED values as set by {@link rgb_led_matrix_set_blue}.
 */
int rgb_led_matrix_get_blue(RGBLEDMatrix *rgb_led_matrix, uint8_t ret_blue[64]);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the frame duration.
 * 
 * Example: If you want to achieve 20 frames per second, you should
 * set the frame duration to 50ms (50ms * 20 = 1 second).
 * 
 * Set this value to 0 to turn the automatic frame write mechanism off.
 * 
 * Approach:
 * 
 * * Call {@link rgb_led_matrix_set_frame_duration} with value > 0.
 * * Set LED values for first frame with {@link rgb_led_matrix_set_red}, {@link rgb_led_matrix_set_green}, {@link rgb_led_matrix_set_blue}.
 * * Wait for {@link RGB_LED_MATRIX_CALLBACK_FRAME_STARTED} callback.
 * * Set LED values for second frame with {@link rgb_led_matrix_set_red}, {@link rgb_led_matrix_set_green}, {@link rgb_led_matrix_set_blue}.
 * * Wait for {@link RGB_LED_MATRIX_CALLBACK_FRAME_STARTED} callback.
 * * and so on.
 * 
 * For frame duration of 0 see {@link rgb_led_matrix_draw_frame}.
 */
int rgb_led_matrix_set_frame_duration(RGBLEDMatrix *rgb_led_matrix, uint16_t frame_duration);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the frame duration as set by {@link rgb_led_matrix_set_frame_duration}.
 */
int rgb_led_matrix_get_frame_duration(RGBLEDMatrix *rgb_led_matrix, uint16_t *ret_frame_duration);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * If you set the frame duration to 0 (see {@link rgb_led_matrix_set_frame_duration}), you can use this
 * function to transfer the frame to the matrix.
 * 
 * Approach:
 * 
 * * Call {@link rgb_led_matrix_set_frame_duration} with 0.
 * * Set LED values for first frame with {@link rgb_led_matrix_set_red}, {@link rgb_led_matrix_set_green}, {@link rgb_led_matrix_set_blue}.
 * * Call {@link rgb_led_matrix_draw_frame}.
 * * Wait for {@link RGB_LED_MATRIX_CALLBACK_FRAME_STARTED} callback.
 * * Set LED values for second frame with {@link rgb_led_matrix_set_red}, {@link rgb_led_matrix_set_green}, {@link rgb_led_matrix_set_blue}.
 * * Call {@link rgb_led_matrix_draw_frame}.
 * * Wait for {@link RGB_LED_MATRIX_CALLBACK_FRAME_STARTED} callback.
 * * and so on.
 */
int rgb_led_matrix_draw_frame(RGBLEDMatrix *rgb_led_matrix);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the current supply voltage of the Bricklet.
 */
int rgb_led_matrix_get_supply_voltage(RGBLEDMatrix *rgb_led_matrix, uint16_t *ret_voltage);

/**
 * \ingroup BrickletRGBLEDMatrix
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
int rgb_led_matrix_get_spitfp_error_count(RGBLEDMatrix *rgb_led_matrix, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletRGBLEDMatrix
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
int rgb_led_matrix_set_bootloader_mode(RGBLEDMatrix *rgb_led_matrix, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the current bootloader mode, see {@link rgb_led_matrix_set_bootloader_mode}.
 */
int rgb_led_matrix_get_bootloader_mode(RGBLEDMatrix *rgb_led_matrix, uint8_t *ret_mode);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the firmware pointer for {@link rgb_led_matrix_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int rgb_led_matrix_set_write_firmware_pointer(RGBLEDMatrix *rgb_led_matrix, uint32_t pointer);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link rgb_led_matrix_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int rgb_led_matrix_write_firmware(RGBLEDMatrix *rgb_led_matrix, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int rgb_led_matrix_set_status_led_config(RGBLEDMatrix *rgb_led_matrix, uint8_t config);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the configuration as set by {@link rgb_led_matrix_set_status_led_config}
 */
int rgb_led_matrix_get_status_led_config(RGBLEDMatrix *rgb_led_matrix, uint8_t *ret_config);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int rgb_led_matrix_get_chip_temperature(RGBLEDMatrix *rgb_led_matrix, int16_t *ret_temperature);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int rgb_led_matrix_reset(RGBLEDMatrix *rgb_led_matrix);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int rgb_led_matrix_write_uid(RGBLEDMatrix *rgb_led_matrix, uint32_t uid);

/**
 * \ingroup BrickletRGBLEDMatrix
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int rgb_led_matrix_read_uid(RGBLEDMatrix *rgb_led_matrix, uint32_t *ret_uid);

/**
 * \ingroup BrickletRGBLEDMatrix
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
int rgb_led_matrix_get_identity(RGBLEDMatrix *rgb_led_matrix, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
