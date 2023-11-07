/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_DC_V2_H
#define BRICKLET_DC_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletDCV2 DC Bricklet 2.0
 */

/**
 * \ingroup BrickletDCV2
 *
 * Drives one brushed DC motor with up to 28V and 5A (peak)
 */
typedef Device DCV2;

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_ENABLED 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_ENABLED 2

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_VELOCITY 3

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_VELOCITY 4

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_CURRENT_VELOCITY 5

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_MOTION 6

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_MOTION 7

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_FULL_BRAKE 8

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_DRIVE_MODE 9

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_DRIVE_MODE 10

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_PWM_FREQUENCY 11

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_PWM_FREQUENCY 12

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_POWER_STATISTICS 13

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_ERROR_LED_CONFIG 14

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_ERROR_LED_CONFIG 15

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION 16

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION 17

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION 18

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION 19

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION 20

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION 21

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletDCV2
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if either the current consumption
 * is too high (above 5A) or the temperature of the driver chip is too high
 * (above 175°C). These two possibilities are essentially the same, since the
 * temperature will reach this threshold immediately if the motor consumes too
 * much current. In case of a voltage below 3.3V (external or stack) this
 * callback is triggered as well.
 * 
 * If this callback is triggered, the driver chip gets disabled at the same time.
 * That means, {@link dc_v2_set_enabled} has to be called to drive the motor again.
 * 
 * \note
 *  This callback only works in Drive/Brake mode (see {@link dc_v2_set_drive_mode}). In
 *  Drive/Coast mode it is unfortunately impossible to reliably read the
 *  overcurrent/overtemperature signal from the driver chip.
 */
#define DC_V2_CALLBACK_EMERGENCY_SHUTDOWN 22

/**
 * \ingroup BrickletDCV2
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered whenever a set velocity is reached. For example:
 * If a velocity of 0 is present, acceleration is set to 5000 and velocity
 * to 10000, the {@link DC_V2_CALLBACK_VELOCITY_REACHED} callback will be triggered after about
 * 2 seconds, when the set velocity is actually reached.
 * 
 * \note
 *  Since we can't get any feedback from the DC motor, this only works if the
 *  acceleration (see {@link dc_v2_set_motion}) is set smaller or equal to the
 *  maximum acceleration of the motor. Otherwise the motor will lag behind the
 *  control value and the callback will be triggered too early.
 */
#define DC_V2_CALLBACK_VELOCITY_REACHED 23

/**
 * \ingroup BrickletDCV2
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered with the period that is set by
 * {@link dc_v2_set_current_velocity_callback_configuration}. The parameter is the *current*
 * velocity used by the motor.
 * 
 * The {@link DC_V2_CALLBACK_CURRENT_VELOCITY} callback is only triggered after the set period
 * if there is a change in the velocity.
 */
#define DC_V2_CALLBACK_CURRENT_VELOCITY 24


/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_DRIVE_MODE_DRIVE_BRAKE 0

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_DRIVE_MODE_DRIVE_COAST 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_ERROR_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_ERROR_LED_CONFIG_ON 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_ERROR_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_ERROR_LED_CONFIG_SHOW_ERROR 3

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletDCV2
 */
#define DC_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletDCV2
 *
 * This constant is used to identify a DC Bricklet 2.0.
 *
 * The {@link dc_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define DC_V2_DEVICE_IDENTIFIER 2165

/**
 * \ingroup BrickletDCV2
 *
 * This constant represents the display name of a DC Bricklet 2.0.
 */
#define DC_V2_DEVICE_DISPLAY_NAME "DC Bricklet 2.0"

/**
 * \ingroup BrickletDCV2
 *
 * Creates the device object \c dc_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void dc_v2_create(DCV2 *dc_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletDCV2
 *
 * Removes the device object \c dc_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void dc_v2_destroy(DCV2 *dc_v2);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the dc_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int dc_v2_get_response_expected(DCV2 *dc_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletDCV2
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
int dc_v2_set_response_expected(DCV2 *dc_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletDCV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int dc_v2_set_response_expected_all(DCV2 *dc_v2, bool response_expected);

/**
 * \ingroup BrickletDCV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void dc_v2_register_callback(DCV2 *dc_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int dc_v2_get_api_version(DCV2 *dc_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletDCV2
 *
 * Enables/Disables the driver chip. The driver parameters can be configured
 * (velocity, acceleration, etc) before it is enabled.
 */
int dc_v2_set_enabled(DCV2 *dc_v2, bool enabled);

/**
 * \ingroup BrickletDCV2
 *
 * Returns *true* if the driver chip is enabled, *false* otherwise.
 */
int dc_v2_get_enabled(DCV2 *dc_v2, bool *ret_enabled);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the velocity of the motor. Whereas -32767 is full speed backward,
 * 0 is stop and 32767 is full speed forward. Depending on the
 * acceleration (see {@link dc_v2_set_motion}), the motor is not immediately
 * brought to the velocity but smoothly accelerated.
 * 
 * The velocity describes the duty cycle of the PWM with which the motor is
 * controlled, e.g. a velocity of 3277 sets a PWM with a 10% duty cycle.
 * You can not only control the duty cycle of the PWM but also the frequency,
 * see {@link dc_v2_set_pwm_frequency}.
 */
int dc_v2_set_velocity(DCV2 *dc_v2, int16_t velocity);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the velocity as set by {@link dc_v2_set_velocity}.
 */
int dc_v2_get_velocity(DCV2 *dc_v2, int16_t *ret_velocity);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the *current* velocity of the motor. This value is different
 * from {@link dc_v2_get_velocity} whenever the motor is currently accelerating
 * to a goal set by {@link dc_v2_set_velocity}.
 */
int dc_v2_get_current_velocity(DCV2 *dc_v2, int16_t *ret_velocity);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the acceleration and deceleration of the motor. It is given in *velocity/s*.
 * An acceleration of 10000 means, that every second the velocity is increased
 * by 10000 (or about 30% duty cycle).
 * 
 * For example: If the current velocity is 0 and you want to accelerate to a
 * velocity of 16000 (about 50% duty cycle) in 10 seconds, you should set
 * an acceleration of 1600.
 * 
 * If acceleration and deceleration is set to 0, there is no speed ramping, i.e. a
 * new velocity is immediately given to the motor.
 */
int dc_v2_set_motion(DCV2 *dc_v2, uint16_t acceleration, uint16_t deceleration);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the acceleration/deceleration as set by {@link dc_v2_set_motion}.
 */
int dc_v2_get_motion(DCV2 *dc_v2, uint16_t *ret_acceleration, uint16_t *ret_deceleration);

/**
 * \ingroup BrickletDCV2
 *
 * Executes an active full brake.
 * 
 * \warning
 *  This function is for emergency purposes,
 *  where an immediate brake is necessary. Depending on the current velocity and
 *  the strength of the motor, a full brake can be quite violent.
 * 
 * Call {@link dc_v2_set_velocity} with 0 if you just want to stop the motor.
 */
int dc_v2_full_brake(DCV2 *dc_v2);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the drive mode. Possible modes are:
 * 
 * * 0 = Drive/Brake
 * * 1 = Drive/Coast
 * 
 * These modes are different kinds of motor controls.
 * 
 * In Drive/Brake mode, the motor is always either driving or braking. There
 * is no freewheeling. Advantages are: A more linear correlation between
 * PWM and velocity, more exact accelerations and the possibility to drive
 * with slower velocities.
 * 
 * In Drive/Coast mode, the motor is always either driving or freewheeling.
 * Advantages are: Less current consumption and less demands on the motor and
 * driver chip.
 */
int dc_v2_set_drive_mode(DCV2 *dc_v2, uint8_t mode);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the drive mode, as set by {@link dc_v2_set_drive_mode}.
 */
int dc_v2_get_drive_mode(DCV2 *dc_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the frequency of the PWM with which the motor is driven.
 * Often a high frequency
 * is less noisy and the motor runs smoother. However, with a low frequency
 * there are less switches and therefore fewer switching losses. Also with
 * most motors lower frequencies enable higher torque.
 * 
 * If you have no idea what all this means, just ignore this function and use
 * the default frequency, it will very likely work fine.
 */
int dc_v2_set_pwm_frequency(DCV2 *dc_v2, uint16_t frequency);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the PWM frequency as set by {@link dc_v2_set_pwm_frequency}.
 */
int dc_v2_get_pwm_frequency(DCV2 *dc_v2, uint16_t *ret_frequency);

/**
 * \ingroup BrickletDCV2
 *
 * Returns input voltage and current usage of the driver.
 */
int dc_v2_get_power_statistics(DCV2 *dc_v2, uint16_t *ret_voltage, uint16_t *ret_current);

/**
 * \ingroup BrickletDCV2
 *
 * Configures the error LED to be either turned off, turned on, blink in
 * heartbeat mode or show an error.
 * 
 * If the LED is configured to show errors it has three different states:
 * 
 * * Off: No error present.
 * * 1s interval blinking: Input voltage too low (below 6V).
 * * 250ms interval blinking: Overtemperature or overcurrent.
 */
int dc_v2_set_error_led_config(DCV2 *dc_v2, uint8_t config);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the LED configuration as set by {@link dc_v2_set_error_led_config}
 */
int dc_v2_get_error_led_config(DCV2 *dc_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletDCV2
 *
 * Enable/Disable {@link DC_V2_CALLBACK_EMERGENCY_SHUTDOWN} callback.
 */
int dc_v2_set_emergency_shutdown_callback_configuration(DCV2 *dc_v2, bool enabled);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the callback configuration as set by
 * {@link dc_v2_set_emergency_shutdown_callback_configuration}.
 */
int dc_v2_get_emergency_shutdown_callback_configuration(DCV2 *dc_v2, bool *ret_enabled);

/**
 * \ingroup BrickletDCV2
 *
 * Enable/Disable {@link DC_V2_CALLBACK_VELOCITY_REACHED} callback.
 */
int dc_v2_set_velocity_reached_callback_configuration(DCV2 *dc_v2, bool enabled);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the callback configuration as set by
 * {@link dc_v2_set_velocity_reached_callback_configuration}.
 */
int dc_v2_get_velocity_reached_callback_configuration(DCV2 *dc_v2, bool *ret_enabled);

/**
 * \ingroup BrickletDCV2
 *
 * The period is the period with which the {@link DC_V2_CALLBACK_CURRENT_VELOCITY}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int dc_v2_set_current_velocity_callback_configuration(DCV2 *dc_v2, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the callback configuration as set by
 * {@link dc_v2_set_current_velocity_callback_configuration}.
 */
int dc_v2_get_current_velocity_callback_configuration(DCV2 *dc_v2, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletDCV2
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
int dc_v2_get_spitfp_error_count(DCV2 *dc_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletDCV2
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
int dc_v2_set_bootloader_mode(DCV2 *dc_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the current bootloader mode, see {@link dc_v2_set_bootloader_mode}.
 */
int dc_v2_get_bootloader_mode(DCV2 *dc_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the firmware pointer for {@link dc_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int dc_v2_set_write_firmware_pointer(DCV2 *dc_v2, uint32_t pointer);

/**
 * \ingroup BrickletDCV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link dc_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int dc_v2_write_firmware(DCV2 *dc_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletDCV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int dc_v2_set_status_led_config(DCV2 *dc_v2, uint8_t config);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the configuration as set by {@link dc_v2_set_status_led_config}
 */
int dc_v2_get_status_led_config(DCV2 *dc_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int dc_v2_get_chip_temperature(DCV2 *dc_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletDCV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int dc_v2_reset(DCV2 *dc_v2);

/**
 * \ingroup BrickletDCV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int dc_v2_write_uid(DCV2 *dc_v2, uint32_t uid);

/**
 * \ingroup BrickletDCV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int dc_v2_read_uid(DCV2 *dc_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletDCV2
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
int dc_v2_get_identity(DCV2 *dc_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
