/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_PERFORMANCE_DC_H
#define BRICKLET_PERFORMANCE_DC_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletPerformanceDC Performance DC Bricklet
 */

/**
 * \ingroup BrickletPerformanceDC
 *
 * Drives one brushed DC motor with up to 36V and 10A
 */
typedef Device PerformanceDC;

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_ENABLED 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_ENABLED 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_VELOCITY 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_VELOCITY 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY 5

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_MOTION 6

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_MOTION 7

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_FULL_BRAKE 8

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_DRIVE_MODE 9

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_DRIVE_MODE 10

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_PWM_FREQUENCY 11

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_PWM_FREQUENCY 12

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_POWER_STATISTICS 13

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_THERMAL_SHUTDOWN 14

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_THERMAL_SHUTDOWN 15

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_GPIO_CONFIGURATION 16

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_GPIO_CONFIGURATION 17

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_GPIO_ACTION 18

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_GPIO_ACTION 19

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_GPIO_STATE 20

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_ERROR_LED_CONFIG 21

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_ERROR_LED_CONFIG 22

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_CW_LED_CONFIG 23

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_CW_LED_CONFIG 24

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_CCW_LED_CONFIG 25

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_CCW_LED_CONFIG 26

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_GPIO_LED_CONFIG 27

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_GPIO_LED_CONFIG 28

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION 29

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_EMERGENCY_SHUTDOWN_CALLBACK_CONFIGURATION 30

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_VELOCITY_REACHED_CALLBACK_CONFIGURATION 31

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_VELOCITY_REACHED_CALLBACK_CONFIGURATION 32

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION 33

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_CURRENT_VELOCITY_CALLBACK_CONFIGURATION 34

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_RESET 243

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletPerformanceDC
 *
 * Signature: \code void callback(void *user_data) \endcode
 * 
 * This callback is triggered if either the current consumption
 * is too high or the temperature of the driver chip is too high
 * (above 150°C) or the user defined thermal shutdown is triggered (see {@link performance_dc_set_thermal_shutdown}).
 * n case of a voltage below 6V (input voltage) this
 * callback is triggered as well.
 * 
 * If this callback is triggered, the driver chip gets disabled at the same time.
 * That means, {@link performance_dc_set_enabled} has to be called to drive the motor again.
 */
#define PERFORMANCE_DC_CALLBACK_EMERGENCY_SHUTDOWN 35

/**
 * \ingroup BrickletPerformanceDC
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered whenever a set velocity is reached. For example:
 * If a velocity of 0 is present, acceleration is set to 5000 and velocity
 * to 10000, the {@link PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED} callback will be triggered after about
 * 2 seconds, when the set velocity is actually reached.
 * 
 * \note
 *  Since we can't get any feedback from the DC motor, this only works if the
 *  acceleration (see {@link performance_dc_set_motion}) is set smaller or equal to the
 *  maximum acceleration of the motor. Otherwise the motor will lag behind the
 *  control value and the callback will be triggered too early.
 */
#define PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED 36

/**
 * \ingroup BrickletPerformanceDC
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered with the period that is set by
 * {@link performance_dc_set_current_velocity_callback_configuration}. The parameter is the *current*
 * velocity used by the motor.
 * 
 * The {@link PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY} callback is only triggered after the set period
 * if there is a change in the velocity.
 */
#define PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY 37

/**
 * \ingroup BrickletPerformanceDC
 *
 * Signature: \code void callback(bool gpio_state[2], void *user_data) \endcode
 * 
 * This callback is triggered by GPIO changes if it is activated through {@link performance_dc_set_gpio_action}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define PERFORMANCE_DC_CALLBACK_GPIO_STATE 38


/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_DRIVE_MODE_DRIVE_BRAKE 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_DRIVE_MODE_DRIVE_COAST 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_NONE 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_NORMAL_STOP_RISING_EDGE 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_NORMAL_STOP_FALLING_EDGE 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_FULL_BRAKE_RISING_EDGE 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_FULL_BRAKE_FALLING_EDGE 8

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_CALLBACK_RISING_EDGE 16

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_ACTION_CALLBACK_FALLING_EDGE 32

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_ERROR_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_ERROR_LED_CONFIG_ON 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_ERROR_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_ERROR_LED_CONFIG_SHOW_ERROR 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CW_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CW_LED_CONFIG_ON 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CW_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CW_LED_CONFIG_SHOW_CW_AS_FORWARD 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CW_LED_CONFIG_SHOW_CW_AS_BACKWARD 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CCW_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CCW_LED_CONFIG_ON 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_CCW_AS_FORWARD 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_CCW_AS_BACKWARD 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_LED_CONFIG_ON 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_HIGH 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_LOW 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletPerformanceDC
 */
#define PERFORMANCE_DC_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletPerformanceDC
 *
 * This constant is used to identify a Performance DC Bricklet.
 *
 * The {@link performance_dc_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define PERFORMANCE_DC_DEVICE_IDENTIFIER 2156

/**
 * \ingroup BrickletPerformanceDC
 *
 * This constant represents the display name of a Performance DC Bricklet.
 */
#define PERFORMANCE_DC_DEVICE_DISPLAY_NAME "Performance DC Bricklet"

/**
 * \ingroup BrickletPerformanceDC
 *
 * Creates the device object \c performance_dc with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void performance_dc_create(PerformanceDC *performance_dc, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Removes the device object \c performance_dc from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void performance_dc_destroy(PerformanceDC *performance_dc);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the performance_dc_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int performance_dc_get_response_expected(PerformanceDC *performance_dc, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_response_expected(PerformanceDC *performance_dc, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int performance_dc_set_response_expected_all(PerformanceDC *performance_dc, bool response_expected);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void performance_dc_register_callback(PerformanceDC *performance_dc, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int performance_dc_get_api_version(PerformanceDC *performance_dc, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Enables/Disables the driver chip. The driver parameters can be configured
 * (velocity, acceleration, etc) before it is enabled.
 */
int performance_dc_set_enabled(PerformanceDC *performance_dc, bool enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns *true* if the driver chip is enabled, *false* otherwise.
 */
int performance_dc_get_enabled(PerformanceDC *performance_dc, bool *ret_enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets the velocity of the motor. Whereas -32767 is full speed backward,
 * 0 is stop and 32767 is full speed forward. Depending on the
 * acceleration (see {@link performance_dc_set_motion}), the motor is not immediately
 * brought to the velocity but smoothly accelerated.
 * 
 * The velocity describes the duty cycle of the PWM with which the motor is
 * controlled, e.g. a velocity of 3277 sets a PWM with a 10% duty cycle.
 * You can not only control the duty cycle of the PWM but also the frequency,
 * see {@link performance_dc_set_pwm_frequency}.
 */
int performance_dc_set_velocity(PerformanceDC *performance_dc, int16_t velocity);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the velocity as set by {@link performance_dc_set_velocity}.
 */
int performance_dc_get_velocity(PerformanceDC *performance_dc, int16_t *ret_velocity);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the *current* velocity of the motor. This value is different
 * from {@link performance_dc_get_velocity} whenever the motor is currently accelerating
 * to a goal set by {@link performance_dc_set_velocity}.
 */
int performance_dc_get_current_velocity(PerformanceDC *performance_dc, int16_t *ret_velocity);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_motion(PerformanceDC *performance_dc, uint16_t acceleration, uint16_t deceleration);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the acceleration/deceleration as set by {@link performance_dc_set_motion}.
 */
int performance_dc_get_motion(PerformanceDC *performance_dc, uint16_t *ret_acceleration, uint16_t *ret_deceleration);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Executes an active full brake.
 * 
 * \warning
 *  This function is for emergency purposes,
 *  where an immediate brake is necessary. Depending on the current velocity and
 *  the strength of the motor, a full brake can be quite violent.
 * 
 * Call {@link performance_dc_set_velocity} with 0 if you just want to stop the motor.
 */
int performance_dc_full_brake(PerformanceDC *performance_dc);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_drive_mode(PerformanceDC *performance_dc, uint8_t mode);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the drive mode, as set by {@link performance_dc_set_drive_mode}.
 */
int performance_dc_get_drive_mode(PerformanceDC *performance_dc, uint8_t *ret_mode);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_pwm_frequency(PerformanceDC *performance_dc, uint16_t frequency);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the PWM frequency as set by {@link performance_dc_set_pwm_frequency}.
 */
int performance_dc_get_pwm_frequency(PerformanceDC *performance_dc, uint16_t *ret_frequency);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns input voltage, current usage and temperature of the driver.
 */
int performance_dc_get_power_statistics(PerformanceDC *performance_dc, uint16_t *ret_voltage, uint16_t *ret_current, int16_t *ret_temperature);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets a temperature threshold that is used for thermal shutdown.
 * 
 * Additionally to this user defined threshold the driver chip will shut down at a
 * temperature of 150°C.
 * 
 * If a thermal shutdown is triggered the driver is disabled and has to be
 * explicitly re-enabled with {@link performance_dc_set_enabled}.
 */
int performance_dc_set_thermal_shutdown(PerformanceDC *performance_dc, uint8_t temperature);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the thermal shutdown temperature as set by {@link performance_dc_set_thermal_shutdown}.
 */
int performance_dc_get_thermal_shutdown(PerformanceDC *performance_dc, uint8_t *ret_temperature);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets the GPIO configuration for the given channel.
 * You can configure a debounce and the deceleration that is used if the action is
 * configured as ``normal stop``. See {@link performance_dc_set_gpio_action}.
 */
int performance_dc_set_gpio_configuration(PerformanceDC *performance_dc, uint8_t channel, uint16_t debounce, uint16_t stop_deceleration);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the GPIO configuration for a channel as set by {@link performance_dc_set_gpio_configuration}.
 */
int performance_dc_get_gpio_configuration(PerformanceDC *performance_dc, uint8_t channel, uint16_t *ret_debounce, uint16_t *ret_stop_deceleration);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets the GPIO action for the given channel.
 * 
 * The action can be a normal stop, a full brake or a callback. Each for a rising
 * edge or falling edge. The actions are a bitmask they can be used at the same time.
 * You can for example trigger a full brake and a callback at the same time or for
 * rising and falling edge.
 * 
 * The deceleration speed for the normal stop can be configured with
 * {@link performance_dc_set_gpio_configuration}.
 */
int performance_dc_set_gpio_action(PerformanceDC *performance_dc, uint8_t channel, uint32_t action);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the GPIO action for a channel as set by {@link performance_dc_set_gpio_action}.
 */
int performance_dc_get_gpio_action(PerformanceDC *performance_dc, uint8_t channel, uint32_t *ret_action);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the GPIO state for both channels. True if the state is ``high`` and
 * false if the state is ``low``.
 */
int performance_dc_get_gpio_state(PerformanceDC *performance_dc, bool ret_gpio_state[2]);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_error_led_config(PerformanceDC *performance_dc, uint8_t config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the LED configuration as set by {@link performance_dc_set_error_led_config}
 */
int performance_dc_get_error_led_config(PerformanceDC *performance_dc, uint8_t *ret_config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Configures the CW LED to be either turned off, turned on, blink in
 * heartbeat mode or if the motor turn clockwise.
 */
int performance_dc_set_cw_led_config(PerformanceDC *performance_dc, uint8_t config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the LED configuration as set by {@link performance_dc_set_cw_led_config}
 */
int performance_dc_get_cw_led_config(PerformanceDC *performance_dc, uint8_t *ret_config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Configures the CCW LED to be either turned off, turned on, blink in
 * heartbeat mode or if the motor turn counter-clockwise.
 */
int performance_dc_set_ccw_led_config(PerformanceDC *performance_dc, uint8_t config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the LED configuration as set by {@link performance_dc_set_ccw_led_config}
 */
int performance_dc_get_ccw_led_config(PerformanceDC *performance_dc, uint8_t *ret_config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Configures the GPIO LED to be either turned off, turned on, blink in
 * heartbeat mode or the GPIO state.
 * 
 * The GPIO LED can be configured for both channels.
 */
int performance_dc_set_gpio_led_config(PerformanceDC *performance_dc, uint8_t channel, uint8_t config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the LED configuration as set by {@link performance_dc_set_gpio_led_config}
 */
int performance_dc_get_gpio_led_config(PerformanceDC *performance_dc, uint8_t channel, uint8_t *ret_config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Enable/Disable {@link PERFORMANCE_DC_CALLBACK_EMERGENCY_SHUTDOWN} callback.
 */
int performance_dc_set_emergency_shutdown_callback_configuration(PerformanceDC *performance_dc, bool enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the callback configuration as set by
 * {@link performance_dc_set_emergency_shutdown_callback_configuration}.
 */
int performance_dc_get_emergency_shutdown_callback_configuration(PerformanceDC *performance_dc, bool *ret_enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Enable/Disable {@link PERFORMANCE_DC_CALLBACK_VELOCITY_REACHED} callback.
 */
int performance_dc_set_velocity_reached_callback_configuration(PerformanceDC *performance_dc, bool enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the callback configuration as set by
 * {@link performance_dc_set_velocity_reached_callback_configuration}.
 */
int performance_dc_get_velocity_reached_callback_configuration(PerformanceDC *performance_dc, bool *ret_enabled);

/**
 * \ingroup BrickletPerformanceDC
 *
 * The period is the period with which the {@link PERFORMANCE_DC_CALLBACK_CURRENT_VELOCITY}
 * callback is triggered periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change within the
 * period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 */
int performance_dc_set_current_velocity_callback_configuration(PerformanceDC *performance_dc, uint32_t period, bool value_has_to_change);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the callback configuration as set by
 * {@link performance_dc_set_current_velocity_callback_configuration}.
 */
int performance_dc_get_current_velocity_callback_configuration(PerformanceDC *performance_dc, uint32_t *ret_period, bool *ret_value_has_to_change);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_get_spitfp_error_count(PerformanceDC *performance_dc, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_set_bootloader_mode(PerformanceDC *performance_dc, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the current bootloader mode, see {@link performance_dc_set_bootloader_mode}.
 */
int performance_dc_get_bootloader_mode(PerformanceDC *performance_dc, uint8_t *ret_mode);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets the firmware pointer for {@link performance_dc_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int performance_dc_set_write_firmware_pointer(PerformanceDC *performance_dc, uint32_t pointer);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link performance_dc_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int performance_dc_write_firmware(PerformanceDC *performance_dc, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int performance_dc_set_status_led_config(PerformanceDC *performance_dc, uint8_t config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the configuration as set by {@link performance_dc_set_status_led_config}
 */
int performance_dc_get_status_led_config(PerformanceDC *performance_dc, uint8_t *ret_config);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int performance_dc_get_chip_temperature(PerformanceDC *performance_dc, int16_t *ret_temperature);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int performance_dc_reset(PerformanceDC *performance_dc);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int performance_dc_write_uid(PerformanceDC *performance_dc, uint32_t uid);

/**
 * \ingroup BrickletPerformanceDC
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int performance_dc_read_uid(PerformanceDC *performance_dc, uint32_t *ret_uid);

/**
 * \ingroup BrickletPerformanceDC
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
int performance_dc_get_identity(PerformanceDC *performance_dc, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
