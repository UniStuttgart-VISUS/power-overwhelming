/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_CAN_H
#define BRICKLET_CAN_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletCAN CAN Bricklet
 */

/**
 * \ingroup BrickletCAN
 *
 * Communicates with CAN bus devices
 */
typedef Device CAN;

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_WRITE_FRAME 1

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_READ_FRAME 2

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_ENABLE_FRAME_READ_CALLBACK 3

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_DISABLE_FRAME_READ_CALLBACK 4

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_IS_FRAME_READ_CALLBACK_ENABLED 5

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_SET_CONFIGURATION 6

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_GET_CONFIGURATION 7

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_SET_READ_FILTER 8

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_GET_READ_FILTER 9

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_GET_ERROR_LOG 10

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_SET_FRAME_READABLE_CALLBACK_CONFIGURATION 12

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_GET_FRAME_READABLE_CALLBACK_CONFIGURATION 13

/**
 * \ingroup BrickletCAN
 */
#define CAN_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletCAN
 *
 * Signature: \code void callback(uint8_t frame_type, uint32_t identifier, uint8_t data[8], uint8_t length, void *user_data) \endcode
 * 
 * This callback is triggered if a data or remote frame was received by the CAN
 * transceiver.
 * 
 * The ``identifier`` return value follows the identifier format described for
 * {@link can_write_frame}.
 * 
 * For remote frames the ``data`` return value always contains invalid values.
 * 
 * A configurable read filter can be used to define which frames should be
 * received by the CAN transceiver at all (see {@link can_set_read_filter}).
 * 
 * To enable this callback, use {@link can_enable_frame_read_callback}.
 */
#define CAN_CALLBACK_FRAME_READ 11

/**
 * \ingroup BrickletCAN
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if a data or remote frame was received by the CAN
 * transceiver. The received frame can be read with {@link can_read_frame}.
 * If additional frames are received, but {@link can_read_frame} was not called yet, the callback
 * will not trigger again.
 * 
 * A configurable read filter can be used to define which frames should be
 * received by the CAN transceiver and put into the read queue (see
 * {@link can_set_read_filter}).
 * 
 * To enable this callback, use {@link can_set_frame_readable_callback_configuration}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define CAN_CALLBACK_FRAME_READABLE 14


/**
 * \ingroup BrickletCAN
 */
#define CAN_FRAME_TYPE_STANDARD_DATA 0

/**
 * \ingroup BrickletCAN
 */
#define CAN_FRAME_TYPE_STANDARD_REMOTE 1

/**
 * \ingroup BrickletCAN
 */
#define CAN_FRAME_TYPE_EXTENDED_DATA 2

/**
 * \ingroup BrickletCAN
 */
#define CAN_FRAME_TYPE_EXTENDED_REMOTE 3

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_10KBPS 0

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_20KBPS 1

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_50KBPS 2

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_125KBPS 3

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_250KBPS 4

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_500KBPS 5

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_800KBPS 6

/**
 * \ingroup BrickletCAN
 */
#define CAN_BAUD_RATE_1000KBPS 7

/**
 * \ingroup BrickletCAN
 */
#define CAN_TRANSCEIVER_MODE_NORMAL 0

/**
 * \ingroup BrickletCAN
 */
#define CAN_TRANSCEIVER_MODE_LOOPBACK 1

/**
 * \ingroup BrickletCAN
 */
#define CAN_TRANSCEIVER_MODE_READ_ONLY 2

/**
 * \ingroup BrickletCAN
 */
#define CAN_FILTER_MODE_DISABLED 0

/**
 * \ingroup BrickletCAN
 */
#define CAN_FILTER_MODE_ACCEPT_ALL 1

/**
 * \ingroup BrickletCAN
 */
#define CAN_FILTER_MODE_MATCH_STANDARD 2

/**
 * \ingroup BrickletCAN
 */
#define CAN_FILTER_MODE_MATCH_STANDARD_AND_DATA 3

/**
 * \ingroup BrickletCAN
 */
#define CAN_FILTER_MODE_MATCH_EXTENDED 4

/**
 * \ingroup BrickletCAN
 *
 * This constant is used to identify a CAN Bricklet.
 *
 * The {@link can_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define CAN_DEVICE_IDENTIFIER 270

/**
 * \ingroup BrickletCAN
 *
 * This constant represents the display name of a CAN Bricklet.
 */
#define CAN_DEVICE_DISPLAY_NAME "CAN Bricklet"

/**
 * \ingroup BrickletCAN
 *
 * Creates the device object \c can with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void can_create(CAN *can, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletCAN
 *
 * Removes the device object \c can from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void can_destroy(CAN *can);

/**
 * \ingroup BrickletCAN
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the can_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int can_get_response_expected(CAN *can, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletCAN
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
int can_set_response_expected(CAN *can, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletCAN
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int can_set_response_expected_all(CAN *can, bool response_expected);

/**
 * \ingroup BrickletCAN
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void can_register_callback(CAN *can, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletCAN
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int can_get_api_version(CAN *can, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletCAN
 *
 * Writes a data or remote frame to the write buffer to be transmitted over the
 * CAN transceiver.
 * 
 * The Bricklet supports the standard 11-bit (CAN 2.0A) and the additional extended
 * 18-bit (CAN 2.0B) identifiers. For standard frames the Bricklet uses bit 0 to 10
 * from the ``identifier`` parameter as standard 11-bit identifier. For extended
 * frames the Bricklet additionally uses bit 11 to 28 from the ``identifier``
 * parameter as extended 18-bit identifier.
 * 
 * For remote frames the ``data`` parameter is ignored.
 * 
 * Returns *true* if the frame was successfully added to the write buffer. Returns
 * *false* if the frame could not be added because write buffer is already full.
 * 
 * The write buffer can overflow if frames are written to it at a higher rate
 * than the Bricklet can transmitted them over the CAN transceiver. This may
 * happen if the CAN transceiver is configured as read-only or is using a low baud
 * rate (see {@link can_set_configuration}). It can also happen if the CAN bus is
 * congested and the frame cannot be transmitted because it constantly loses
 * arbitration or because the CAN transceiver is currently disabled due to a high
 * write error level (see {@link can_get_error_log}).
 */
int can_write_frame(CAN *can, uint8_t frame_type, uint32_t identifier, uint8_t data[8], uint8_t length, bool *ret_success);

/**
 * \ingroup BrickletCAN
 *
 * Tries to read the next data or remote frame from the read buffer and return it.
 * If a frame was successfully read, then the ``success`` return value is set to
 * *true* and the other return values contain the frame. If the read buffer is
 * empty and no frame could be read, then the ``success`` return value is set to
 * *false* and the other return values contain invalid data.
 * 
 * The ``identifier`` return value follows the identifier format described for
 * {@link can_write_frame}.
 * 
 * For remote frames the ``data`` return value always contains invalid data.
 * 
 * A configurable read filter can be used to define which frames should be
 * received by the CAN transceiver and put into the read buffer (see
 * {@link can_set_read_filter}).
 * 
 * Instead of polling with this function, you can also use callbacks. See the
 * {@link can_enable_frame_read_callback} function and the {@link CAN_CALLBACK_FRAME_READ} callback.
 */
int can_read_frame(CAN *can, bool *ret_success, uint8_t *ret_frame_type, uint32_t *ret_identifier, uint8_t ret_data[8], uint8_t *ret_length);

/**
 * \ingroup BrickletCAN
 *
 * Enables the {@link CAN_CALLBACK_FRAME_READ} callback.
 * 
 * By default the callback is disabled. Enabling this callback will disable the {@link CAN_CALLBACK_FRAME_READABLE} callback.
 */
int can_enable_frame_read_callback(CAN *can);

/**
 * \ingroup BrickletCAN
 *
 * Disables the {@link CAN_CALLBACK_FRAME_READ} callback.
 * 
 * By default the callback is disabled.
 */
int can_disable_frame_read_callback(CAN *can);

/**
 * \ingroup BrickletCAN
 *
 * Returns *true* if the {@link CAN_CALLBACK_FRAME_READ} callback is enabled, *false* otherwise.
 */
int can_is_frame_read_callback_enabled(CAN *can, bool *ret_enabled);

/**
 * \ingroup BrickletCAN
 *
 * Sets the configuration for the CAN bus communication.
 * 
 * The baud rate can be configured in steps between 10 and 1000 kbit/s.
 * 
 * The CAN transceiver has three different modes:
 * 
 * * Normal: Reads from and writes to the CAN bus and performs active bus
 *   error detection and acknowledgement.
 * * Loopback: All reads and writes are performed internally. The transceiver
 *   is disconnected from the actual CAN bus.
 * * Read-Only: Only reads from the CAN bus, but does neither active bus error
 *   detection nor acknowledgement. Only the receiving part of the transceiver
 *   is connected to the CAN bus.
 * 
 * The write timeout has three different modes that define how a failed frame
 * transmission should be handled:
 * 
 * * One-Shot (= -1): Only one transmission attempt will be made. If the
 *   transmission fails then the frame is discarded.
 * * Infinite (= 0): Infinite transmission attempts will be made. The frame will
 *   never be discarded.
 * * Milliseconds (> 0): A limited number of transmission attempts will be made.
 *   If the frame could not be transmitted successfully after the configured
 *   number of milliseconds then the frame is discarded.
 */
int can_set_configuration(CAN *can, uint8_t baud_rate, uint8_t transceiver_mode, int32_t write_timeout);

/**
 * \ingroup BrickletCAN
 *
 * Returns the configuration as set by {@link can_set_configuration}.
 */
int can_get_configuration(CAN *can, uint8_t *ret_baud_rate, uint8_t *ret_transceiver_mode, int32_t *ret_write_timeout);

/**
 * \ingroup BrickletCAN
 *
 * Set the read filter configuration. This can be used to define which frames
 * should be received by the CAN transceiver and put into the read buffer.
 * 
 * The read filter has five different modes that define if and how the mask and
 * the two filters are applied:
 * 
 * * Disabled: No filtering is applied at all. All frames are received even
 *   incomplete and defective frames. This mode should be used for debugging only.
 * * Accept-All: All complete and error-free frames are received.
 * * Match-Standard: Only standard frames with a matching identifier are received.
 * * Match-Standard-and-Data: Only standard frames with matching identifier and
 *   data bytes are received.
 * * Match-Extended: Only extended frames with a matching identifier are received.
 * 
 * The mask and filters are used as bit masks. Their usage depends on the mode:
 * 
 * * Disabled: Mask and filters are ignored.
 * * Accept-All: Mask and filters are ignored.
 * * Match-Standard: Bit 0 to 10 (11 bits) of mask and filters are used to match
 *   the 11-bit identifier of standard frames.
 * * Match-Standard-and-Data: Bit 0 to 10 (11 bits) of mask and filters are used
 *   to match the 11-bit identifier of standard frames. Bit 11 to 18 (8 bits) and
 *   bit 19 to 26 (8 bits) of mask and filters are used to match the first and
 *   second data byte (if present) of standard frames.
 * * Match-Extended: Bit 0 to 10 (11 bits) of mask and filters are used
 *   to match the standard 11-bit identifier part of extended frames. Bit 11 to 28
 *   (18 bits) of mask and filters are used to match the extended 18-bit identifier
 *   part of extended frames.
 * 
 * The mask and filters are applied in this way: The mask is used to select the
 * identifier and data bits that should be compared to the corresponding filter
 * bits. All unselected bits are automatically accepted. All selected bits have
 * to match one of the filters to be accepted. If all bits for the selected mode
 * are accepted then the frame is accepted and is added to the read buffer.
 * 
 * \verbatim
 *  "Mask Bit", "Filter Bit", "Identifier/Data Bit", "Result"
 * 
 *  0, X, X, Accept
 *  1, 0, 0, Accept
 *  1, 0, 1, Reject
 *  1, 1, 0, Reject
 *  1, 1, 1, Accept
 * \endverbatim
 * 
 * For example, to receive standard frames with identifier 0x123 only the mode can
 * be set to Match-Standard with 0x7FF as mask and 0x123 as filter 1 and filter 2.
 * The mask of 0x7FF selects all 11 identifier bits for matching so that the
 * identifier has to be exactly 0x123 to be accepted.
 * 
 * To accept identifier 0x123 and identifier 0x456 at the same time, just set
 * filter 2 to 0x456 and keep mask and filter 1 unchanged.
 */
int can_set_read_filter(CAN *can, uint8_t mode, uint32_t mask, uint32_t filter1, uint32_t filter2);

/**
 * \ingroup BrickletCAN
 *
 * Returns the read filter as set by {@link can_set_read_filter}.
 */
int can_get_read_filter(CAN *can, uint8_t *ret_mode, uint32_t *ret_mask, uint32_t *ret_filter1, uint32_t *ret_filter2);

/**
 * \ingroup BrickletCAN
 *
 * Returns information about different kinds of errors.
 * 
 * The write and read error levels indicate the current level of checksum,
 * acknowledgement, form, bit and stuffing errors during CAN bus write and read
 * operations.
 * 
 * When the write error level exceeds 255 then the CAN transceiver gets disabled
 * and no frames can be transmitted or received anymore. The CAN transceiver will
 * automatically be activated again after the CAN bus is idle for a while.
 * 
 * The write and read error levels are not available in read-only transceiver mode
 * (see {@link can_set_configuration}) and are reset to 0 as a side effect of changing
 * the configuration or the read filter.
 * 
 * The write timeout, read register and buffer overflow counts represents the
 * number of these errors:
 * 
 * * A write timeout occurs if a frame could not be transmitted before the
 *   configured write timeout expired (see {@link can_set_configuration}).
 * * A read register overflow occurs if the read register of the CAN transceiver
 *   still contains the last received frame when the next frame arrives. In this
 *   case the newly arrived frame is lost. This happens if the CAN transceiver
 *   receives more frames than the Bricklet can handle. Using the read filter
 *   (see {@link can_set_read_filter}) can help to reduce the amount of received frames.
 *   This count is not exact, but a lower bound, because the Bricklet might not
 *   able detect all overflows if they occur in rapid succession.
 * * A read buffer overflow occurs if the read buffer of the Bricklet is already
 *   full when the next frame should be read from the read register of the CAN
 *   transceiver. In this case the frame in the read register is lost. This
 *   happens if the CAN transceiver receives more frames to be added to the read
 *   buffer than are removed from the read buffer using the {@link can_read_frame}
 *   function. Using the {@link CAN_CALLBACK_FRAME_READ} callback ensures that the read buffer
 *   can not overflow.
 */
int can_get_error_log(CAN *can, uint8_t *ret_write_error_level, uint8_t *ret_read_error_level, bool *ret_transceiver_disabled, uint32_t *ret_write_timeout_count, uint32_t *ret_read_register_overflow_count, uint32_t *ret_read_buffer_overflow_count);

/**
 * \ingroup BrickletCAN
 *
 * Enables/disables the {@link CAN_CALLBACK_FRAME_READABLE} callback.
 * 
 * By default the callback is disabled. Enabling this callback will disable the {@link CAN_CALLBACK_FRAME_READ} callback.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int can_set_frame_readable_callback_configuration(CAN *can, bool enabled);

/**
 * \ingroup BrickletCAN
 *
 * Returns *true* if the {@link CAN_CALLBACK_FRAME_READABLE} callback is enabled, *false* otherwise.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int can_get_frame_readable_callback_configuration(CAN *can, bool *ret_enabled);

/**
 * \ingroup BrickletCAN
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
int can_get_identity(CAN *can, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
