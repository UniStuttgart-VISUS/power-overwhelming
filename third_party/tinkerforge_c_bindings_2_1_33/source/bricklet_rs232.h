/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_RS232_H
#define BRICKLET_RS232_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRS232 RS232 Bricklet
 */

/**
 * \ingroup BrickletRS232
 *
 * Communicates with RS232 devices
 */
typedef Device RS232;

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_WRITE 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_READ 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_ENABLE_READ_CALLBACK 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_DISABLE_READ_CALLBACK 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_IS_READ_CALLBACK_ENABLED 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_SET_CONFIGURATION 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_GET_CONFIGURATION 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_SET_BREAK_CONDITION 10

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION 11

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION 12

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_READ_FRAME 14

/**
 * \ingroup BrickletRS232
 */
#define RS232_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(char message[60], uint8_t length, void *user_data) \endcode
 * 
 * This callback is called if new data is available. The message has
 * a maximum size of 60 characters. The actual length of the message
 * is given in addition.
 * 
 * To enable this callback, use {@link rs232_enable_read_callback}.
 */
#define RS232_CALLBACK_READ 8

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(uint8_t error, void *user_data) \endcode
 * 
 * This callback is called if an error occurs.
 * Possible errors are overrun, parity or framing error.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define RS232_CALLBACK_ERROR 9

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(uint8_t frame_count, void *user_data) \endcode
 * 
 * This callback is called if at least one frame of data is readable. The frame size is configured with {@link rs232_set_frame_readable_callback_configuration}.
 * The frame count parameter is the number of frames that can be read.
 * This callback is triggered only once until {@link rs232_read} or {@link rs232_read_frame} is called. This means, that if you have configured a frame size of X bytes,
 * you can read exactly X bytes using the {@link rs232_read_frame} function, every time the callback triggers without checking the frame count parameter.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Plugin)
 */
#define RS232_CALLBACK_FRAME_READABLE 13

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(char ret_message[60], uint8_t length, void *user_data) \endcode
 *
 * This callback is called if new data is available. The message has
 * a maximum size of 60 characters. The actual length of the message
 * is given in addition.
 *
 * To enable this callback, use {@link rs232_enable_read_callback}.
 */
#define RS232_CALLBACK_READ_CALLBACK RS232_CALLBACK_READ // for backward compatibility

/**
 * \ingroup BrickletRS232
 *
 * Signature: \code void callback(uint8_t error, void *user_data) \endcode
 *
 * This callback is called if an error occurs.
 * Possible errors are overrun, parity or framing error.
 *
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define RS232_CALLBACK_ERROR_CALLBACK RS232_CALLBACK_ERROR // for backward compatibility


/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_300 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_600 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_1200 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_2400 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_4800 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_9600 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_14400 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_19200 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_28800 8

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_38400 9

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_57600 10

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_115200 11

/**
 * \ingroup BrickletRS232
 */
#define RS232_BAUDRATE_230400 12

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_NONE 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_ODD 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_EVEN 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_FORCED_PARITY_1 3

/**
 * \ingroup BrickletRS232
 */
#define RS232_PARITY_FORCED_PARITY_0 4

/**
 * \ingroup BrickletRS232
 */
#define RS232_STOPBITS_1 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_STOPBITS_2 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_5 5

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_6 6

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_7 7

/**
 * \ingroup BrickletRS232
 */
#define RS232_WORDLENGTH_8 8

/**
 * \ingroup BrickletRS232
 */
#define RS232_HARDWARE_FLOWCONTROL_OFF 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_HARDWARE_FLOWCONTROL_ON 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_SOFTWARE_FLOWCONTROL_OFF 0

/**
 * \ingroup BrickletRS232
 */
#define RS232_SOFTWARE_FLOWCONTROL_ON 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_OVERRUN 1

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_PARITY 2

/**
 * \ingroup BrickletRS232
 */
#define RS232_ERROR_FRAMING 4

/**
 * \ingroup BrickletRS232
 *
 * This constant is used to identify a RS232 Bricklet.
 *
 * The {@link rs232_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define RS232_DEVICE_IDENTIFIER 254

/**
 * \ingroup BrickletRS232
 *
 * This constant represents the display name of a RS232 Bricklet.
 */
#define RS232_DEVICE_DISPLAY_NAME "RS232 Bricklet"

/**
 * \ingroup BrickletRS232
 *
 * Creates the device object \c rs232 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void rs232_create(RS232 *rs232, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRS232
 *
 * Removes the device object \c rs232 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void rs232_destroy(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the rs232_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int rs232_get_response_expected(RS232 *rs232, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRS232
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
int rs232_set_response_expected(RS232 *rs232, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRS232
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int rs232_set_response_expected_all(RS232 *rs232, bool response_expected);

/**
 * \ingroup BrickletRS232
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void rs232_register_callback(RS232 *rs232, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletRS232
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int rs232_get_api_version(RS232 *rs232, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRS232
 *
 * Writes a string of up to 60 characters to the RS232 interface. The string
 * can be binary data, ASCII or similar is not necessary.
 * 
 * The length of the string has to be given as an additional parameter.
 * 
 * The return value is the number of bytes that could be written.
 * 
 * See {@link rs232_set_configuration} for configuration possibilities
 * regarding baudrate, parity and so on.
 */
int rs232_write(RS232 *rs232, char message[60], uint8_t length, uint8_t *ret_written);

/**
 * \ingroup BrickletRS232
 *
 * Returns the currently buffered message. The maximum length
 * of message is 60. If the returned length is 0, no new data was available.
 * 
 * Instead of polling with this function, you can also use
 * callbacks. See {@link rs232_enable_read_callback} and {@link RS232_CALLBACK_READ} callback.
 */
int rs232_read(RS232 *rs232, char ret_message[60], uint8_t *ret_length);

/**
 * \ingroup BrickletRS232
 *
 * Enables the {@link RS232_CALLBACK_READ} callback. This will disable the {@link RS232_CALLBACK_FRAME_READABLE} callback.
 * 
 * By default the callback is disabled.
 */
int rs232_enable_read_callback(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Disables the {@link RS232_CALLBACK_READ} callback.
 * 
 * By default the callback is disabled.
 */
int rs232_disable_read_callback(RS232 *rs232);

/**
 * \ingroup BrickletRS232
 *
 * Returns *true* if the {@link RS232_CALLBACK_READ} callback is enabled,
 * *false* otherwise.
 */
int rs232_is_read_callback_enabled(RS232 *rs232, bool *ret_enabled);

/**
 * \ingroup BrickletRS232
 *
 * Sets the configuration for the RS232 communication.
 * 
 * Hard-/Software flow control can either be on or off but not both simultaneously on.
 */
int rs232_set_configuration(RS232 *rs232, uint8_t baudrate, uint8_t parity, uint8_t stopbits, uint8_t wordlength, uint8_t hardware_flowcontrol, uint8_t software_flowcontrol);

/**
 * \ingroup BrickletRS232
 *
 * Returns the configuration as set by {@link rs232_set_configuration}.
 */
int rs232_get_configuration(RS232 *rs232, uint8_t *ret_baudrate, uint8_t *ret_parity, uint8_t *ret_stopbits, uint8_t *ret_wordlength, uint8_t *ret_hardware_flowcontrol, uint8_t *ret_software_flowcontrol);

/**
 * \ingroup BrickletRS232
 *
 * Sets a break condition (the TX output is forced to a logic 0 state).
 * The parameter sets the hold-time of the break condition.
 * 
 * .. versionadded:: 2.0.2$nbsp;(Plugin)
 */
int rs232_set_break_condition(RS232 *rs232, uint16_t break_time);

/**
 * \ingroup BrickletRS232
 *
 * Configures the {@link RS232_CALLBACK_FRAME_READABLE} callback. The frame size is the number of bytes, that have to be readable to trigger the callback.
 * A frame size of 0 disables the callback. A frame size greater than 0 enables the callback and disables the {@link RS232_CALLBACK_READ} callback.
 * 
 * By default the callback is disabled.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Plugin)
 */
int rs232_set_frame_readable_callback_configuration(RS232 *rs232, uint8_t frame_size);

/**
 * \ingroup BrickletRS232
 *
 * Returns the callback configuration as set by {@link rs232_set_frame_readable_callback_configuration}.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Plugin)
 */
int rs232_get_frame_readable_callback_configuration(RS232 *rs232, uint8_t *ret_frame_size);

/**
 * \ingroup BrickletRS232
 *
 * Returns up to one frame of bytes from the read buffer.
 * The frame size is configured with {@link rs232_set_frame_readable_callback_configuration}.
 * If the returned length is 0, no new data was available.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Plugin)
 */
int rs232_read_frame(RS232 *rs232, char ret_message[60], uint8_t *ret_length);

/**
 * \ingroup BrickletRS232
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
int rs232_get_identity(RS232 *rs232, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
