/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_DMX_H
#define BRICKLET_DMX_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDMX DMX Bricklet
 */

/**
 * \ingroup BrickletDMX
 *
 * DMX master and slave
 */
typedef Device DMX;

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_DMX_MODE 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_DMX_MODE 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_WRITE_FRAME_LOW_LEVEL 3

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_READ_FRAME_LOW_LEVEL 4

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_FRAME_DURATION 5

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_FRAME_DURATION 6

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_FRAME_ERROR_COUNT 7

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_COMMUNICATION_LED_CONFIG 8

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_COMMUNICATION_LED_CONFIG 9

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_ERROR_LED_CONFIG 10

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_ERROR_LED_CONFIG 11

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_FRAME_CALLBACK_CONFIG 12

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_FRAME_CALLBACK_CONFIG 13

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_RESET 243

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletDMX
 */
#define DMX_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDMX
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered as soon as a new frame write is started.
 * You should send the data for the next frame directly after this callback
 * was triggered.
 * 
 * For an explanation of the general approach see {@link dmx_write_frame}.
 * 
 * This callback can be enabled via {@link dmx_set_frame_callback_config}.
 * 
 * This callback can only be triggered in master mode.
 */
#define DMX_CALLBACK_FRAME_STARTED 14

/**
 * \ingroup BrickletDMX
 *
 * Signature: \code void callback(uint32_t frame_number, void *user_data) \endcode
 * 
 * This callback is triggered in slave mode when a new frame was received from the DMX master
 * and it can be read out. You have to read the frame before the master has written
 * the next frame, see {@link dmx_read_frame} for more details.
 * 
 * The parameter is the frame number, it is increased by one with each received frame.
 * 
 * This callback can be enabled via {@link dmx_set_frame_callback_config}.
 * 
 * This callback can only be triggered in slave mode.
 */
#define DMX_CALLBACK_FRAME_AVAILABLE 15

/**
 * \ingroup BrickletDMX
 *
 * See DMX_CALLBACK_FRAME
 */
#define DMX_CALLBACK_FRAME_LOW_LEVEL 16

/**
 * \ingroup BrickletDMX
 *
 * Signature: \code void callback(uint32_t overrun_error_count, uint32_t framing_error_count, void *user_data) \endcode
 * 
 * This callback is called if a new error occurs. It returns
 * the current overrun and framing error count.
 */
#define DMX_CALLBACK_FRAME_ERROR_COUNT 17

/**
 * \ingroup BrickletDMX
 *
 * Signature: \code void callback(uint8_t *frame, uint16_t frame_length, uint32_t frame_number, void *user_data) \endcode
 * 
 * This callback is called as soon as a new frame is available
 * (written by the DMX master).
 * 
 * The size of the array is equivalent to the number of channels in
 * the frame. Each byte represents one channel.
 * 
 * This callback can be enabled via {@link dmx_set_frame_callback_config}.
 * 
 * This callback can only be triggered in slave mode.
 * 
 * \note
 *  If reconstructing the value fails, the callback is triggered with NULL for frame.
 */
#define DMX_CALLBACK_FRAME (-16)


/**
 * \ingroup BrickletDMX
 */
#define DMX_DMX_MODE_MASTER 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_DMX_MODE_SLAVE 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_COMMUNICATION_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_COMMUNICATION_LED_CONFIG_ON 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_COMMUNICATION_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_COMMUNICATION_LED_CONFIG_SHOW_COMMUNICATION 3

/**
 * \ingroup BrickletDMX
 */
#define DMX_ERROR_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_ERROR_LED_CONFIG_ON 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_ERROR_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_ERROR_LED_CONFIG_SHOW_ERROR 3

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletDMX
 */
#define DMX_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletDMX
 */
#define DMX_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletDMX
 */
#define DMX_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletDMX
 */
#define DMX_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletDMX
 */
#define DMX_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletDMX
 *
 * This constant is used to identify a DMX Bricklet.
 *
 * The {@link dmx_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DMX_DEVICE_IDENTIFIER 285

/**
 * \ingroup BrickletDMX
 *
 * This constant represents the display name of a DMX Bricklet.
 */
#define DMX_DEVICE_DISPLAY_NAME "DMX Bricklet"

/**
 * \ingroup BrickletDMX
 *
 * Creates the device object \c dmx with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void dmx_create(DMX *dmx, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDMX
 *
 * Removes the device object \c dmx from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void dmx_destroy(DMX *dmx);

/**
 * \ingroup BrickletDMX
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the dmx_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int dmx_get_response_expected(DMX *dmx, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDMX
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
int dmx_set_response_expected(DMX *dmx, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDMX
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int dmx_set_response_expected_all(DMX *dmx, bool response_expected);

/**
 * \ingroup BrickletDMX
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void dmx_register_callback(DMX *dmx, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletDMX
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int dmx_get_api_version(DMX *dmx, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDMX
 *
 * Sets the DMX mode to either master or slave.
 * 
 * Calling this function sets frame number to 0.
 */
int dmx_set_dmx_mode(DMX *dmx, uint8_t dmx_mode);

/**
 * \ingroup BrickletDMX
 *
 * Returns the DMX mode, as set by {@link dmx_set_dmx_mode}.
 */
int dmx_get_dmx_mode(DMX *dmx, uint8_t *ret_dmx_mode);

/**
 * \ingroup BrickletDMX
 *
 * Writes a DMX frame. The maximum frame size is 512 byte. Each byte represents one channel.
 * 
 * The next frame can be written after the {@link DMX_CALLBACK_FRAME_STARTED} callback was called. The frame
 * is double buffered, so a new frame can be written as soon as the writing of the prior frame
 * starts.
 * 
 * The data will be transfered when the next frame duration ends, see {@link dmx_set_frame_duration}.
 * 
 * Generic approach:
 * 
 * * Set the frame duration to a value that represents the number of frames per second you want to achieve.
 * * Set channels for first frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_STARTED} callback.
 * * Set channels for next frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_STARTED} callback.
 * * and so on.
 * 
 * This approach ensures that you can set new DMX data with a fixed frame rate.
 * 
 * This function can only be called in master mode.
 */
int dmx_write_frame_low_level(DMX *dmx, uint16_t frame_length, uint16_t frame_chunk_offset, uint8_t frame_chunk_data[60]);

/**
 * \ingroup BrickletDMX
 *
 * Returns the last frame that was written by the DMX master. The size of the array
 * is equivalent to the number of channels in the frame. Each byte represents one channel.
 * 
 * The next frame is available after the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback was called.
 * 
 * Generic approach:
 * 
 * * Call {@link dmx_read_frame} to get first frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback.
 * * Call {@link dmx_read_frame} to get second frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback.
 * * and so on.
 * 
 * Instead of polling this function you can also use the {@link DMX_CALLBACK_FRAME} callback.
 * You can enable it with {@link dmx_set_frame_callback_config}.
 * 
 * The frame number starts at 0 and it is increased by one with each received frame.
 * 
 * This function can only be called in slave mode.
 */
int dmx_read_frame_low_level(DMX *dmx, uint16_t *ret_frame_length, uint16_t *ret_frame_chunk_offset, uint8_t ret_frame_chunk_data[56], uint32_t *ret_frame_number);

/**
 * \ingroup BrickletDMX
 *
 * Sets the duration of a frame.
 * 
 * Example: If you want to achieve 20 frames per second, you should
 * set the frame duration to 50ms (50ms * 20 = 1 second).
 * 
 * If you always want to send a frame as fast as possible you can set
 * this value to 0.
 * 
 * This setting is only used in master mode.
 */
int dmx_set_frame_duration(DMX *dmx, uint16_t frame_duration);

/**
 * \ingroup BrickletDMX
 *
 * Returns the frame duration as set by {@link dmx_set_frame_duration}.
 */
int dmx_get_frame_duration(DMX *dmx, uint16_t *ret_frame_duration);

/**
 * \ingroup BrickletDMX
 *
 * Returns the current number of overrun and framing errors.
 */
int dmx_get_frame_error_count(DMX *dmx, uint32_t *ret_overrun_error_count, uint32_t *ret_framing_error_count);

/**
 * \ingroup BrickletDMX
 *
 * Sets the communication LED configuration. By default the LED shows
 * communication traffic, it flickers once for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is off.
 */
int dmx_set_communication_led_config(DMX *dmx, uint8_t config);

/**
 * \ingroup BrickletDMX
 *
 * Returns the configuration as set by {@link dmx_set_communication_led_config}
 */
int dmx_get_communication_led_config(DMX *dmx, uint8_t *ret_config);

/**
 * \ingroup BrickletDMX
 *
 * Sets the error LED configuration.
 * 
 * By default the error LED turns on if there is any error (see {@link DMX_CALLBACK_FRAME_ERROR_COUNT}
 * callback). If you call this function with the Show-Error option again, the LED
 * will turn off until the next error occurs.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is off.
 */
int dmx_set_error_led_config(DMX *dmx, uint8_t config);

/**
 * \ingroup BrickletDMX
 *
 * Returns the configuration as set by {@link dmx_set_error_led_config}.
 */
int dmx_get_error_led_config(DMX *dmx, uint8_t *ret_config);

/**
 * \ingroup BrickletDMX
 *
 * Enables/Disables the different callbacks. By default the
 * {@link DMX_CALLBACK_FRAME_STARTED} callback and {@link DMX_CALLBACK_FRAME_AVAILABLE} callback are enabled while
 * the {@link DMX_CALLBACK_FRAME} callback and {@link DMX_CALLBACK_FRAME_ERROR_COUNT} callback are disabled.
 * 
 * If you want to use the {@link DMX_CALLBACK_FRAME} callback you can enable it and disable
 * the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback at the same time. It becomes redundant in
 * this case.
 */
int dmx_set_frame_callback_config(DMX *dmx, bool frame_started_callback_enabled, bool frame_available_callback_enabled, bool frame_callback_enabled, bool frame_error_count_callback_enabled);

/**
 * \ingroup BrickletDMX
 *
 * Returns the frame callback config as set by {@link dmx_set_frame_callback_config}.
 */
int dmx_get_frame_callback_config(DMX *dmx, bool *ret_frame_started_callback_enabled, bool *ret_frame_available_callback_enabled, bool *ret_frame_callback_enabled, bool *ret_frame_error_count_callback_enabled);

/**
 * \ingroup BrickletDMX
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
int dmx_get_spitfp_error_count(DMX *dmx, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletDMX
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
int dmx_set_bootloader_mode(DMX *dmx, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletDMX
 *
 * Returns the current bootloader mode, see {@link dmx_set_bootloader_mode}.
 */
int dmx_get_bootloader_mode(DMX *dmx, uint8_t *ret_mode);

/**
 * \ingroup BrickletDMX
 *
 * Sets the firmware pointer for {@link dmx_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int dmx_set_write_firmware_pointer(DMX *dmx, uint32_t pointer);

/**
 * \ingroup BrickletDMX
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link dmx_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int dmx_write_firmware(DMX *dmx, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletDMX
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int dmx_set_status_led_config(DMX *dmx, uint8_t config);

/**
 * \ingroup BrickletDMX
 *
 * Returns the configuration as set by {@link dmx_set_status_led_config}
 */
int dmx_get_status_led_config(DMX *dmx, uint8_t *ret_config);

/**
 * \ingroup BrickletDMX
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int dmx_get_chip_temperature(DMX *dmx, int16_t *ret_temperature);

/**
 * \ingroup BrickletDMX
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int dmx_reset(DMX *dmx);

/**
 * \ingroup BrickletDMX
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int dmx_write_uid(DMX *dmx, uint32_t uid);

/**
 * \ingroup BrickletDMX
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int dmx_read_uid(DMX *dmx, uint32_t *ret_uid);

/**
 * \ingroup BrickletDMX
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
int dmx_get_identity(DMX *dmx, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

/**
 * \ingroup BrickletDMX
 *
 * Writes a DMX frame. The maximum frame size is 512 byte. Each byte represents one channel.
 * 
 * The next frame can be written after the {@link DMX_CALLBACK_FRAME_STARTED} callback was called. The frame
 * is double buffered, so a new frame can be written as soon as the writing of the prior frame
 * starts.
 * 
 * The data will be transfered when the next frame duration ends, see {@link dmx_set_frame_duration}.
 * 
 * Generic approach:
 * 
 * * Set the frame duration to a value that represents the number of frames per second you want to achieve.
 * * Set channels for first frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_STARTED} callback.
 * * Set channels for next frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_STARTED} callback.
 * * and so on.
 * 
 * This approach ensures that you can set new DMX data with a fixed frame rate.
 * 
 * This function can only be called in master mode.
 */
int dmx_write_frame(DMX *dmx, uint8_t *frame, uint16_t frame_length);

/**
 * \ingroup BrickletDMX
 *
 * Returns the last frame that was written by the DMX master. The size of the array
 * is equivalent to the number of channels in the frame. Each byte represents one channel.
 * 
 * The next frame is available after the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback was called.
 * 
 * Generic approach:
 * 
 * * Call {@link dmx_read_frame} to get first frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback.
 * * Call {@link dmx_read_frame} to get second frame.
 * * Wait for the {@link DMX_CALLBACK_FRAME_AVAILABLE} callback.
 * * and so on.
 * 
 * Instead of polling this function you can also use the {@link DMX_CALLBACK_FRAME} callback.
 * You can enable it with {@link dmx_set_frame_callback_config}.
 * 
 * The frame number starts at 0 and it is increased by one with each received frame.
 * 
 * This function can only be called in slave mode.
 */
int dmx_read_frame(DMX *dmx, uint8_t *ret_frame, uint16_t *ret_frame_length, uint32_t *ret_frame_number);

#ifdef __cplusplus
}
#endif

#endif
