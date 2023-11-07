/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_REMOTE_SWITCH_V2_H
#define BRICKLET_REMOTE_SWITCH_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRemoteSwitchV2 Remote Switch Bricklet 2.0
 */

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Controls remote mains switches and receives signals from remotes
 */
typedef Device RemoteSwitchV2;

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_SWITCHING_STATE 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SET_REPEATS 3

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_REPEATS 4

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_A 5

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_B 6

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_DIM_SOCKET_B 7

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SWITCH_SOCKET_C 8

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SET_REMOTE_CONFIGURATION 9

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_CONFIGURATION 10

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_A 11

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_B 12

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_REMOTE_STATUS_C 13

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered whenever the switching state changes
 * from busy to ready, see {@link remote_switch_v2_get_switching_state}.
 */
#define REMOTE_SWITCH_V2_CALLBACK_SWITCHING_DONE 2

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Signature: \code void callback(uint8_t house_code, uint8_t receiver_code, uint8_t switch_to, uint16_t repeats, void *user_data) \endcode
 * 
 * Returns the house code, receiver code, switch state (on/off) and number of repeats for
 * remote type A.
 * 
 * The repeats are the number of received identical data packets. The longer the button is pressed,
 * the higher the repeat number. The callback is triggered with every repeat.
 * 
 * You have to enable the callback with {@link remote_switch_v2_set_remote_configuration}. The number
 * of repeats that you can set in the configuration is the minimum number of repeats that have
 * to be seen before the callback is triggered for the first time.
 */
#define REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A 14

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Signature: \code void callback(uint32_t address, uint8_t unit, uint8_t switch_to, uint8_t dim_value, uint16_t repeats, void *user_data) \endcode
 * 
 * Returns the address (unique per remote), unit (button number), switch state (on/off) and number of repeats for
 * remote type B.
 * 
 * If the remote supports dimming the dim value is used instead of the switch state.
 * 
 * The repeats are the number of received identical data packets. The longer the button is pressed,
 * the higher the repeat number. The callback is triggered with every repeat.
 * 
 * You have to enable the callback with {@link remote_switch_v2_set_remote_configuration}. The number
 * of repeats that you can set in the configuration is the minimum number of repeats that have
 * to be seen before the callback is triggered for the first time.
 */
#define REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B 15

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Signature: \code void callback(char system_code, uint8_t device_code, uint8_t switch_to, uint16_t repeats, void *user_data) \endcode
 * 
 * Returns the system code, device code, switch state (on/off) and number of repeats for
 * remote type C.
 * 
 * The repeats are the number of received identical data packets. The longer the button is pressed,
 * the higher the repeat number. The callback is triggered with every repeat.
 * 
 * You have to enable the callback with {@link remote_switch_v2_set_remote_configuration}. The number
 * of repeats that you can set in the configuration is the minimum number of repeats that have
 * to be seen before the callback is triggered for the first time.
 */
#define REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C 16


/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_SWITCHING_STATE_READY 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_SWITCHING_STATE_BUSY 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_SWITCH_TO_OFF 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_SWITCH_TO_ON 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_REMOTE_TYPE_A 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_REMOTE_TYPE_B 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_REMOTE_TYPE_C 2

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletRemoteSwitchV2
 */
#define REMOTE_SWITCH_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * This constant is used to identify a Remote Switch Bricklet 2.0.
 *
 * The {@link remote_switch_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define REMOTE_SWITCH_V2_DEVICE_IDENTIFIER 289

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * This constant represents the display name of a Remote Switch Bricklet 2.0.
 */
#define REMOTE_SWITCH_V2_DEVICE_DISPLAY_NAME "Remote Switch Bricklet 2.0"

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Creates the device object \c remote_switch_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void remote_switch_v2_create(RemoteSwitchV2 *remote_switch_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Removes the device object \c remote_switch_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void remote_switch_v2_destroy(RemoteSwitchV2 *remote_switch_v2);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the remote_switch_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int remote_switch_v2_get_response_expected(RemoteSwitchV2 *remote_switch_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRemoteSwitchV2
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
int remote_switch_v2_set_response_expected(RemoteSwitchV2 *remote_switch_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int remote_switch_v2_set_response_expected_all(RemoteSwitchV2 *remote_switch_v2, bool response_expected);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void remote_switch_v2_register_callback(RemoteSwitchV2 *remote_switch_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int remote_switch_v2_get_api_version(RemoteSwitchV2 *remote_switch_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the current switching state. If the current state is busy, the
 * Bricklet is currently sending a code to switch a socket. It will not
 * accept any calls of switch socket functions until the state changes to ready.
 * 
 * How long the switching takes is dependent on the number of repeats, see
 * {@link remote_switch_v2_set_repeats}.
 */
int remote_switch_v2_get_switching_state(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_state);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Sets the number of times the code is sent when one of the Switch Socket
 * functions is called. The repeats basically correspond to the amount of time
 * that a button of the remote is pressed.
 * 
 * Some dimmers are controlled by the length of a button pressed,
 * this can be simulated by increasing the repeats.
 */
int remote_switch_v2_set_repeats(RemoteSwitchV2 *remote_switch_v2, uint8_t repeats);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the number of repeats as set by {@link remote_switch_v2_set_repeats}.
 */
int remote_switch_v2_get_repeats(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_repeats);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * To switch a type A socket you have to give the house code, receiver code and the
 * state (on or off) you want to switch to.
 * 
 * A detailed description on how you can figure out the house and receiver code
 * can be found :ref:`here <remote_switch_bricklet_type_a_house_and_receiver_code>`.
 */
int remote_switch_v2_switch_socket_a(RemoteSwitchV2 *remote_switch_v2, uint8_t house_code, uint8_t receiver_code, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * To switch a type B socket you have to give the address, unit and the state
 * (on or off) you want to switch to.
 * 
 * To switch all devices with the same address use 255 for the unit.
 * 
 * A detailed description on how you can teach a socket the address and unit can
 * be found :ref:`here <remote_switch_bricklet_type_b_address_and_unit>`.
 */
int remote_switch_v2_switch_socket_b(RemoteSwitchV2 *remote_switch_v2, uint32_t address, uint8_t unit, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * To control a type B dimmer you have to give the address, unit and the
 * dim value you want to set the dimmer to.
 * 
 * A detailed description on how you can teach a dimmer the address and unit can
 * be found :ref:`here <remote_switch_bricklet_type_b_address_and_unit>`.
 */
int remote_switch_v2_dim_socket_b(RemoteSwitchV2 *remote_switch_v2, uint32_t address, uint8_t unit, uint8_t dim_value);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * To switch a type C socket you have to give the system code, device code and the
 * state (on or off) you want to switch to.
 * 
 * A detailed description on how you can figure out the system and device code
 * can be found :ref:`here <remote_switch_bricklet_type_c_system_and_device_code>`.
 */
int remote_switch_v2_switch_socket_c(RemoteSwitchV2 *remote_switch_v2, char system_code, uint8_t device_code, uint8_t switch_to);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Sets the configuration for **receiving** data from a remote of type A, B or C.
 * 
 * * Remote Type: A, B or C depending on the type of remote you want to receive.
 * * Minimum Repeats: The minimum number of repeated data packets until the callback
 *   is triggered (if enabled).
 * * Callback Enabled: Enable or disable callback (see {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A} callback,
 *   {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B} callback and {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C} callback).
 */
int remote_switch_v2_set_remote_configuration(RemoteSwitchV2 *remote_switch_v2, uint8_t remote_type, uint16_t minimum_repeats, bool callback_enabled);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the remote configuration as set by {@link remote_switch_v2_set_remote_configuration}
 */
int remote_switch_v2_get_remote_configuration(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_remote_type, uint16_t *ret_minimum_repeats, bool *ret_callback_enabled);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the house code, receiver code, switch state (on/off) and number of
 * repeats for remote type A.
 * 
 * Repeats == 0 means there was no button press. Repeats >= 1 means there
 * was a button press with the specified house/receiver code. The repeats are the
 * number of received identical data packets. The longer the button is pressed,
 * the higher the repeat number.
 * 
 * Use the callback to get this data automatically when a button is pressed,
 * see {@link remote_switch_v2_set_remote_configuration} and {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_A} callback.
 */
int remote_switch_v2_get_remote_status_a(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_house_code, uint8_t *ret_receiver_code, uint8_t *ret_switch_to, uint16_t *ret_repeats);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the address (unique per remote), unit (button number), switch state
 * (on/off) and number of repeats for remote type B.
 * 
 * If the remote supports dimming the dim value is used instead of the switch state.
 * 
 * If repeats=0 there was no button press. If repeats >= 1 there
 * was a button press with the specified address/unit. The repeats are the number of received
 * identical data packets. The longer the button is pressed, the higher the repeat number.
 * 
 * Use the callback to get this data automatically when a button is pressed,
 * see {@link remote_switch_v2_set_remote_configuration} and {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_B} callback.
 */
int remote_switch_v2_get_remote_status_b(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_address, uint8_t *ret_unit, uint8_t *ret_switch_to, uint8_t *ret_dim_value, uint16_t *ret_repeats);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the system code, device code, switch state (on/off) and number of repeats for
 * remote type C.
 * 
 * If repeats=0 there was no button press. If repeats >= 1 there
 * was a button press with the specified system/device code. The repeats are the number of received
 * identical data packets. The longer the button is pressed, the higher the repeat number.
 * 
 * Use the callback to get this data automatically when a button is pressed,
 * see {@link remote_switch_v2_set_remote_configuration} and {@link REMOTE_SWITCH_V2_CALLBACK_REMOTE_STATUS_C} callback.
 */
int remote_switch_v2_get_remote_status_c(RemoteSwitchV2 *remote_switch_v2, char *ret_system_code, uint8_t *ret_device_code, uint8_t *ret_switch_to, uint16_t *ret_repeats);

/**
 * \ingroup BrickletRemoteSwitchV2
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
int remote_switch_v2_get_spitfp_error_count(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletRemoteSwitchV2
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
int remote_switch_v2_set_bootloader_mode(RemoteSwitchV2 *remote_switch_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the current bootloader mode, see {@link remote_switch_v2_set_bootloader_mode}.
 */
int remote_switch_v2_get_bootloader_mode(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Sets the firmware pointer for {@link remote_switch_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int remote_switch_v2_set_write_firmware_pointer(RemoteSwitchV2 *remote_switch_v2, uint32_t pointer);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link remote_switch_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int remote_switch_v2_write_firmware(RemoteSwitchV2 *remote_switch_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int remote_switch_v2_set_status_led_config(RemoteSwitchV2 *remote_switch_v2, uint8_t config);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the configuration as set by {@link remote_switch_v2_set_status_led_config}
 */
int remote_switch_v2_get_status_led_config(RemoteSwitchV2 *remote_switch_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int remote_switch_v2_get_chip_temperature(RemoteSwitchV2 *remote_switch_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int remote_switch_v2_reset(RemoteSwitchV2 *remote_switch_v2);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int remote_switch_v2_write_uid(RemoteSwitchV2 *remote_switch_v2, uint32_t uid);

/**
 * \ingroup BrickletRemoteSwitchV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int remote_switch_v2_read_uid(RemoteSwitchV2 *remote_switch_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletRemoteSwitchV2
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
int remote_switch_v2_get_identity(RemoteSwitchV2 *remote_switch_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
