/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICK_SILENT_STEPPER_H
#define BRICK_SILENT_STEPPER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickSilentStepper Silent Stepper Brick
 */

/**
 * \ingroup BrickSilentStepper
 *
 * Silently drives one bipolar stepper motor with up to 46V and 1.6A per phase
 */
typedef Device SilentStepper;

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_MAX_VELOCITY 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_MAX_VELOCITY 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_CURRENT_VELOCITY 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_SPEED_RAMPING 4

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SPEED_RAMPING 5

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_FULL_BRAKE 6

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_CURRENT_POSITION 7

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_CURRENT_POSITION 8

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_TARGET_POSITION 9

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_TARGET_POSITION 10

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_STEPS 11

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_STEPS 12

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_REMAINING_STEPS 13

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_STEP_CONFIGURATION 14

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_STEP_CONFIGURATION 15

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_DRIVE_FORWARD 16

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_DRIVE_BACKWARD 17

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_STOP 18

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_STACK_INPUT_VOLTAGE 19

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_EXTERNAL_INPUT_VOLTAGE 20

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_MOTOR_CURRENT 22

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_MOTOR_CURRENT 23

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_ENABLE 24

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_DISABLE 25

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_IS_ENABLED 26

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_BASIC_CONFIGURATION 27

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_BASIC_CONFIGURATION 28

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_SPREADCYCLE_CONFIGURATION 29

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SPREADCYCLE_CONFIGURATION 30

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_STEALTH_CONFIGURATION 31

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_STEALTH_CONFIGURATION 32

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_COOLSTEP_CONFIGURATION 33

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_COOLSTEP_CONFIGURATION 34

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_MISC_CONFIGURATION 35

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_MISC_CONFIGURATION 36

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_DRIVER_STATUS 37

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_MINIMUM_VOLTAGE 38

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_MINIMUM_VOLTAGE 39

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_TIME_BASE 42

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_TIME_BASE 43

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_ALL_DATA 44

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_ALL_DATA_PERIOD 45

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_ALL_DATA_PERIOD 46

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG 231

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG 232

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SEND_TIMEOUT_COUNT 233

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_SET_SPITFP_BAUDRATE 234

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SPITFP_BAUDRATE 235

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_SPITFP_ERROR_COUNT 237

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_ENABLE_STATUS_LED 238

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_DISABLE_STATUS_LED 239

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_IS_STATUS_LED_ENABLED 240

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME 241

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_RESET 243

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_WRITE_BRICKLET_PLUGIN 246

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_READ_BRICKLET_PLUGIN 247

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickSilentStepper
 *
 * Signature: \code void callback(uint16_t voltage, void *user_data) \endcode
 * 
 * This callback is triggered when the input voltage drops below the value set by
 * {@link silent_stepper_set_minimum_voltage}. The parameter is the current voltage.
 */
#define SILENT_STEPPER_CALLBACK_UNDER_VOLTAGE 40

/**
 * \ingroup BrickSilentStepper
 *
 * Signature: \code void callback(int32_t position, void *user_data) \endcode
 * 
 * This callback is triggered when a position set by {@link silent_stepper_set_steps} or
 * {@link silent_stepper_set_target_position} is reached.
 * 
 * \note
 *  Since we can't get any feedback from the stepper motor, this only works if the
 *  acceleration (see {@link silent_stepper_set_speed_ramping}) is set smaller or equal to the
 *  maximum acceleration of the motor. Otherwise the motor will lag behind the
 *  control value and the callback will be triggered too early.
 */
#define SILENT_STEPPER_CALLBACK_POSITION_REACHED 41

/**
 * \ingroup BrickSilentStepper
 *
 * Signature: \code void callback(uint16_t current_velocity, int32_t current_position, int32_t remaining_steps, uint16_t stack_voltage, uint16_t external_voltage, uint16_t current_consumption, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link silent_stepper_set_all_data_period}. The parameters are: the current velocity,
 * the current position, the remaining steps, the stack voltage, the external
 * voltage and the current consumption of the stepper motor.
 */
#define SILENT_STEPPER_CALLBACK_ALL_DATA 47

/**
 * \ingroup BrickSilentStepper
 *
 * Signature: \code void callback(uint8_t state_new, uint8_t state_previous, void *user_data) \endcode
 * 
 * This callback is triggered whenever the Silent Stepper Brick enters a new state.
 * It returns the new state as well as the previous state.
 */
#define SILENT_STEPPER_CALLBACK_NEW_STATE 48


/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_1 8

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_2 7

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_4 6

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_8 5

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_16 4

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_32 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_64 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_128 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STEP_RESOLUTION_256 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CHOPPER_MODE_SPREAD_CYCLE 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CHOPPER_MODE_FAST_DECAY 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FREEWHEEL_MODE_NORMAL 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FREEWHEEL_MODE_FREEWHEELING 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FREEWHEEL_MODE_COIL_SHORT_LS 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_FREEWHEEL_MODE_COIL_SHORT_HS 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_UP_STEP_INCREMENT_1 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_UP_STEP_INCREMENT_2 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_UP_STEP_INCREMENT_4 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_UP_STEP_INCREMENT_8 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_DOWN_STEP_DECREMENT_1 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_DOWN_STEP_DECREMENT_2 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_DOWN_STEP_DECREMENT_8 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_CURRENT_DOWN_STEP_DECREMENT_32 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_MINIMUM_CURRENT_HALF 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_MINIMUM_CURRENT_QUARTER 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STALLGUARD_MODE_STANDARD 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STALLGUARD_MODE_FILTERED 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OPEN_LOAD_NONE 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OPEN_LOAD_PHASE_A 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OPEN_LOAD_PHASE_B 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OPEN_LOAD_PHASE_AB 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_SHORT_TO_GROUND_NONE 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_SHORT_TO_GROUND_PHASE_A 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_SHORT_TO_GROUND_PHASE_B 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_SHORT_TO_GROUND_PHASE_AB 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OVER_TEMPERATURE_NONE 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OVER_TEMPERATURE_WARNING 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_OVER_TEMPERATURE_LIMIT 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_STOP 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_ACCELERATION 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_RUN 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_DEACCELERATION 4

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_DIRECTION_CHANGE_TO_FORWARD 5

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_STATE_DIRECTION_CHANGE_TO_BACKWARD 6

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_NONE 0

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_USB 1

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_SPI_STACK 2

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_CHIBI 3

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_RS485 4

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_WIFI 5

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_ETHERNET 6

/**
 * \ingroup BrickSilentStepper
 */
#define SILENT_STEPPER_COMMUNICATION_METHOD_WIFI_V2 7

/**
 * \ingroup BrickSilentStepper
 *
 * This constant is used to identify a Silent Stepper Brick.
 *
 * The {@link silent_stepper_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define SILENT_STEPPER_DEVICE_IDENTIFIER 19

/**
 * \ingroup BrickSilentStepper
 *
 * This constant represents the display name of a Silent Stepper Brick.
 */
#define SILENT_STEPPER_DEVICE_DISPLAY_NAME "Silent Stepper Brick"

/**
 * \ingroup BrickSilentStepper
 *
 * Creates the device object \c silent_stepper with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void silent_stepper_create(SilentStepper *silent_stepper, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickSilentStepper
 *
 * Removes the device object \c silent_stepper from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void silent_stepper_destroy(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the silent_stepper_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int silent_stepper_get_response_expected(SilentStepper *silent_stepper, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickSilentStepper
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
int silent_stepper_set_response_expected(SilentStepper *silent_stepper, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickSilentStepper
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int silent_stepper_set_response_expected_all(SilentStepper *silent_stepper, bool response_expected);

/**
 * \ingroup BrickSilentStepper
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void silent_stepper_register_callback(SilentStepper *silent_stepper, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int silent_stepper_get_api_version(SilentStepper *silent_stepper, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the maximum velocity of the stepper motor.
 * This function does *not* start the motor, it merely sets the maximum
 * velocity the stepper motor is accelerated to. To get the motor running use
 * either {@link silent_stepper_set_target_position}, {@link silent_stepper_set_steps}, {@link silent_stepper_drive_forward} or
 * {@link silent_stepper_drive_backward}.
 */
int silent_stepper_set_max_velocity(SilentStepper *silent_stepper, uint16_t velocity);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the velocity as set by {@link silent_stepper_set_max_velocity}.
 */
int silent_stepper_get_max_velocity(SilentStepper *silent_stepper, uint16_t *ret_velocity);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the *current* velocity of the stepper motor.
 */
int silent_stepper_get_current_velocity(SilentStepper *silent_stepper, uint16_t *ret_velocity);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the acceleration and deacceleration of the stepper motor.
 * An acceleration of 1000 means, that
 * every second the velocity is increased by 1000 *steps/s*.
 * 
 * For example: If the current velocity is 0 and you want to accelerate to a
 * velocity of 8000 *steps/s* in 10 seconds, you should set an acceleration
 * of 800 *steps/s²*.
 * 
 * An acceleration/deacceleration of 0 means instantaneous
 * acceleration/deacceleration (not recommended)
 */
int silent_stepper_set_speed_ramping(SilentStepper *silent_stepper, uint16_t acceleration, uint16_t deacceleration);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the acceleration and deacceleration as set by
 * {@link silent_stepper_set_speed_ramping}.
 */
int silent_stepper_get_speed_ramping(SilentStepper *silent_stepper, uint16_t *ret_acceleration, uint16_t *ret_deacceleration);

/**
 * \ingroup BrickSilentStepper
 *
 * Executes an active full brake.
 * 
 * \warning
 *  This function is for emergency purposes,
 *  where an immediate brake is necessary. Depending on the current velocity and
 *  the strength of the motor, a full brake can be quite violent.
 * 
 * Call {@link silent_stepper_stop} if you just want to stop the motor.
 */
int silent_stepper_full_brake(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the current steps of the internal step counter. This can be used to
 * set the current position to 0 when some kind of starting position
 * is reached (e.g. when a CNC machine reaches a corner).
 */
int silent_stepper_set_current_position(SilentStepper *silent_stepper, int32_t position);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the current position of the stepper motor in steps. On startup
 * the position is 0. The steps are counted with all possible driving
 * functions ({@link silent_stepper_set_target_position}, {@link silent_stepper_set_steps}, {@link silent_stepper_drive_forward} or
 * {@link silent_stepper_drive_backward}). It also is possible to reset the steps to 0 or
 * set them to any other desired value with {@link silent_stepper_set_current_position}.
 */
int silent_stepper_get_current_position(SilentStepper *silent_stepper, int32_t *ret_position);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the target position of the stepper motor in steps. For example,
 * if the current position of the motor is 500 and {@link silent_stepper_set_target_position} is
 * called with 1000, the stepper motor will drive 500 steps forward. It will
 * use the velocity, acceleration and deacceleration as set by
 * {@link silent_stepper_set_max_velocity} and {@link silent_stepper_set_speed_ramping}.
 * 
 * A call of {@link silent_stepper_set_target_position} with the parameter *x* is equivalent to
 * a call of {@link silent_stepper_set_steps} with the parameter
 * (*x* - {@link silent_stepper_get_current_position}).
 */
int silent_stepper_set_target_position(SilentStepper *silent_stepper, int32_t position);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the last target position as set by {@link silent_stepper_set_target_position}.
 */
int silent_stepper_get_target_position(SilentStepper *silent_stepper, int32_t *ret_position);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the number of steps the stepper motor should run. Positive values
 * will drive the motor forward and negative values backward.
 * The velocity, acceleration and deacceleration as set by
 * {@link silent_stepper_set_max_velocity} and {@link silent_stepper_set_speed_ramping} will be used.
 */
int silent_stepper_set_steps(SilentStepper *silent_stepper, int32_t steps);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the last steps as set by {@link silent_stepper_set_steps}.
 */
int silent_stepper_get_steps(SilentStepper *silent_stepper, int32_t *ret_steps);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the remaining steps of the last call of {@link silent_stepper_set_steps}.
 * For example, if {@link silent_stepper_set_steps} is called with 2000 and
 * {@link silent_stepper_get_remaining_steps} is called after the motor has run for 500 steps,
 * it will return 1500.
 */
int silent_stepper_get_remaining_steps(SilentStepper *silent_stepper, int32_t *ret_steps);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the step resolution from full-step up to 1/256-step.
 * 
 * If interpolation is turned on, the Silent Stepper Brick will always interpolate
 * your step inputs as 1/256-step. If you use full-step mode with interpolation, each
 * step will generate 256 1/256 steps.
 * 
 * For maximum torque use full-step without interpolation. For maximum resolution use
 * 1/256-step. Turn interpolation on to make the Stepper driving less noisy.
 * 
 * If you often change the speed with high acceleration you should turn the
 * interpolation off.
 */
int silent_stepper_set_step_configuration(SilentStepper *silent_stepper, uint8_t step_resolution, bool interpolation);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the step mode as set by {@link silent_stepper_set_step_configuration}.
 */
int silent_stepper_get_step_configuration(SilentStepper *silent_stepper, uint8_t *ret_step_resolution, bool *ret_interpolation);

/**
 * \ingroup BrickSilentStepper
 *
 * Drives the stepper motor forward until {@link silent_stepper_drive_backward} or
 * {@link silent_stepper_stop} is called. The velocity, acceleration and deacceleration as
 * set by {@link silent_stepper_set_max_velocity} and {@link silent_stepper_set_speed_ramping} will be used.
 */
int silent_stepper_drive_forward(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Drives the stepper motor backward until {@link silent_stepper_drive_forward} or
 * {@link silent_stepper_stop} is triggered. The velocity, acceleration and deacceleration as
 * set by {@link silent_stepper_set_max_velocity} and {@link silent_stepper_set_speed_ramping} will be used.
 */
int silent_stepper_drive_backward(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Stops the stepper motor with the deacceleration as set by
 * {@link silent_stepper_set_speed_ramping}.
 */
int silent_stepper_stop(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the stack input voltage. The stack input voltage is the
 * voltage that is supplied via the stack, i.e. it is given by a
 * Step-Down or Step-Up Power Supply.
 */
int silent_stepper_get_stack_input_voltage(SilentStepper *silent_stepper, uint16_t *ret_voltage);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the external input voltage. The external input voltage is
 * given via the black power input connector on the Silent Stepper Brick.
 * 
 * If there is an external input voltage and a stack input voltage, the motor
 * will be driven by the external input voltage. If there is only a stack
 * voltage present, the motor will be driven by this voltage.
 * 
 * \warning
 *  This means, if you have a high stack voltage and a low external voltage,
 *  the motor will be driven with the low external voltage. If you then remove
 *  the external connection, it will immediately be driven by the high
 *  stack voltage
 */
int silent_stepper_get_external_input_voltage(SilentStepper *silent_stepper, uint16_t *ret_voltage);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the current with which the motor will be driven.
 * 
 * \warning
 *  Do not set this value above the specifications of your stepper motor.
 *  Otherwise it may damage your motor.
 */
int silent_stepper_set_motor_current(SilentStepper *silent_stepper, uint16_t current);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the current as set by {@link silent_stepper_set_motor_current}.
 */
int silent_stepper_get_motor_current(SilentStepper *silent_stepper, uint16_t *ret_current);

/**
 * \ingroup BrickSilentStepper
 *
 * Enables the driver chip. The driver parameters can be configured (maximum velocity,
 * acceleration, etc) before it is enabled.
 */
int silent_stepper_enable(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Disables the driver chip. The configurations are kept (maximum velocity,
 * acceleration, etc) but the motor is not driven until it is enabled again.
 * 
 * \warning
 *  Disabling the driver chip while the motor is still turning can damage the
 *  driver chip. The motor should be stopped calling {@link silent_stepper_stop} function
 *  before disabling the motor power. The {@link silent_stepper_stop} function will **not**
 *  wait until the motor is actually stopped. You have to explicitly wait for the
 *  appropriate time after calling the {@link silent_stepper_stop} function before calling
 *  the {@link silent_stepper_disable} function.
 */
int silent_stepper_disable(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns *true* if the driver chip is enabled, *false* otherwise.
 */
int silent_stepper_is_enabled(SilentStepper *silent_stepper, bool *ret_enabled);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the basic configuration parameters for the different modes (Stealth, Coolstep, Classic).
 * 
 * * Standstill Current: This value can be used to lower the current during stand still. This might
 *   be reasonable to reduce the heating of the motor and the Brick. When the motor is in standstill
 *   the configured motor phase current will be driven until the configured
 *   Power Down Time is elapsed. After that the phase current will be reduced to the standstill
 *   current. The elapsed time for this reduction can be configured with the Standstill Delay Time.
 *   The maximum allowed value is the configured maximum motor current
 *   (see {@link silent_stepper_set_motor_current}).
 * 
 * * Motor Run Current: The value sets the motor current when the motor is running.
 *   Use a value of at least one half of the global maximum motor current for a good
 *   microstep performance. The maximum allowed value is the current
 *   motor current. The API maps the entered value to 1/32 ... 32/32 of the maximum
 *   motor current. This value should be used to change the motor current during motor movement,
 *   whereas the global maximum motor current should not be changed while the motor is moving
 *   (see {@link silent_stepper_set_motor_current}).
 * 
 * * Standstill Delay Time: Controls the duration for motor power down after a motion
 *   as soon as standstill is detected and the Power Down Time is expired. A high Standstill Delay
 *   Time results in a smooth transition that avoids motor jerk during power down.
 * 
 * * Power Down Time: Sets the delay time after a stand still.
 * 
 * * Stealth Threshold: Sets the upper threshold for Stealth mode.
 *   If the velocity of the motor goes above this value, Stealth mode is turned
 *   off. Otherwise it is turned on. In Stealth mode the torque declines with high speed.
 * 
 * * Coolstep Threshold: Sets the lower threshold for Coolstep mode.
 *   The Coolstep Threshold needs to be above the Stealth Threshold.
 * 
 * * Classic Threshold: Sets the lower threshold for classic mode.
 *   In classic mode the stepper becomes more noisy, but the torque is maximized.
 * 
 * * High Velocity Chopper Mode: If High Velocity Chopper Mode is enabled, the stepper control
 *   is optimized to run the stepper motors at high velocities.
 * 
 * If you want to use all three thresholds make sure that
 * Stealth Threshold < Coolstep Threshold < Classic Threshold.
 */
int silent_stepper_set_basic_configuration(SilentStepper *silent_stepper, uint16_t standstill_current, uint16_t motor_run_current, uint16_t standstill_delay_time, uint16_t power_down_time, uint16_t stealth_threshold, uint16_t coolstep_threshold, uint16_t classic_threshold, bool high_velocity_chopper_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the configuration as set by {@link silent_stepper_set_basic_configuration}.
 */
int silent_stepper_get_basic_configuration(SilentStepper *silent_stepper, uint16_t *ret_standstill_current, uint16_t *ret_motor_run_current, uint16_t *ret_standstill_delay_time, uint16_t *ret_power_down_time, uint16_t *ret_stealth_threshold, uint16_t *ret_coolstep_threshold, uint16_t *ret_classic_threshold, bool *ret_high_velocity_chopper_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Note: If you don't know what any of this means you can very likely keep all of
 * the values as default!
 * 
 * Sets the Spreadcycle configuration parameters. Spreadcycle is a chopper algorithm which actively
 * controls the motor current flow. More information can be found in the TMC2130 datasheet on page
 * 47 (7 spreadCycle and Classic Chopper).
 * 
 * * Slow Decay Duration: Controls duration of off time setting of slow decay phase.
 *   0 = driver disabled, all bridges off. Use 1 only with Comparator Blank time >= 2.
 * 
 * * Enable Random Slow Decay: Set to false to fix chopper off time as set by Slow Decay Duration.
 *   If you set it to true, Decay Duration is randomly modulated.
 * 
 * * Fast Decay Duration: Sets the fast decay duration. This parameters is
 *   only used if the Chopper Mode is set to Fast Decay.
 * 
 * * Hysteresis Start Value: Sets the hysteresis start value. This parameter is
 *   only used if the Chopper Mode is set to Spread Cycle.
 * 
 * * Hysteresis End Value: Sets the hysteresis end value. This parameter is
 *   only used if the Chopper Mode is set to Spread Cycle.
 * 
 * * Sine Wave Offset: Sets the sine wave offset. This parameters is
 *   only used if the Chopper Mode is set to Fast Decay. 1/512 of the value becomes added to the absolute
 *   value of the sine wave.
 * 
 * * Chopper Mode: 0 = Spread Cycle, 1 = Fast Decay.
 * 
 * * Comparator Blank Time: Sets the blank time of the comparator. Available values are
 * 
 *   * 0 = 16 clocks,
 *   * 1 = 24 clocks,
 *   * 2 = 36 clocks and
 *   * 3 = 54 clocks.
 * 
 *   A value of 1 or 2 is recommended for most applications.
 * 
 * * Fast Decay Without Comparator: If set to true the current comparator usage for termination of the
 *   fast decay cycle is disabled.
 */
int silent_stepper_set_spreadcycle_configuration(SilentStepper *silent_stepper, uint8_t slow_decay_duration, bool enable_random_slow_decay, uint8_t fast_decay_duration, uint8_t hysteresis_start_value, int8_t hysteresis_end_value, int8_t sine_wave_offset, uint8_t chopper_mode, uint8_t comparator_blank_time, bool fast_decay_without_comparator);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the configuration as set by {@link silent_stepper_set_basic_configuration}.
 */
int silent_stepper_get_spreadcycle_configuration(SilentStepper *silent_stepper, uint8_t *ret_slow_decay_duration, bool *ret_enable_random_slow_decay, uint8_t *ret_fast_decay_duration, uint8_t *ret_hysteresis_start_value, int8_t *ret_hysteresis_end_value, int8_t *ret_sine_wave_offset, uint8_t *ret_chopper_mode, uint8_t *ret_comparator_blank_time, bool *ret_fast_decay_without_comparator);

/**
 * \ingroup BrickSilentStepper
 *
 * Note: If you don't know what any of this means you can very likely keep all of
 * the values as default!
 * 
 * Sets the configuration relevant for Stealth mode.
 * 
 * * Enable Stealth: If set to true the stealth mode is enabled, if set to false the
 *   stealth mode is disabled, even if the speed is below the threshold set in {@link silent_stepper_set_basic_configuration}.
 * 
 * * Amplitude: If autoscale is disabled, the PWM amplitude is scaled by this value. If autoscale is enabled,
 *   this value defines the maximum PWM amplitude change per half wave.
 * 
 * * Gradient: If autoscale is disabled, the PWM gradient is scaled by this value. If autoscale is enabled,
 *   this value defines the maximum PWM gradient. With autoscale a value above 64 is recommended,
 *   otherwise the regulation might not be able to measure the current.
 * 
 * * Enable Autoscale: If set to true, automatic current control is used. Otherwise the user defined
 *   amplitude and gradient are used.
 * 
 * * Force Symmetric: If true, A symmetric PWM cycle is enforced. Otherwise the PWM value may change within each
 *   PWM cycle.
 * 
 * * Freewheel Mode: The freewheel mode defines the behavior in stand still if the Standstill Current
 *   (see {@link silent_stepper_set_basic_configuration}) is set to 0.
 */
int silent_stepper_set_stealth_configuration(SilentStepper *silent_stepper, bool enable_stealth, uint8_t amplitude, uint8_t gradient, bool enable_autoscale, bool force_symmetric, uint8_t freewheel_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the configuration as set by {@link silent_stepper_set_stealth_configuration}.
 */
int silent_stepper_get_stealth_configuration(SilentStepper *silent_stepper, bool *ret_enable_stealth, uint8_t *ret_amplitude, uint8_t *ret_gradient, bool *ret_enable_autoscale, bool *ret_force_symmetric, uint8_t *ret_freewheel_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Note: If you don't know what any of this means you can very likely keep all of
 * the values as default!
 * 
 * Sets the configuration relevant for Coolstep.
 * 
 * * Minimum Stallguard Value: If the Stallguard result falls below this value*32, the motor current
 *   is increased to reduce motor load angle. A value of 0 turns Coolstep off.
 * 
 * * Maximum Stallguard Value: If the Stallguard result goes above
 *   (Min Stallguard Value + Max Stallguard Value + 1) * 32, the motor current is decreased to save
 *   energy.
 * 
 * * Current Up Step Width: Sets the up step increment per Stallguard value. The value range is 0-3,
 *   corresponding to the increments 1, 2, 4 and 8.
 * 
 * * Current Down Step Width: Sets the down step decrement per Stallguard value. The value range is 0-3,
 *   corresponding to the decrements 1, 2, 8 and 16.
 * 
 * * Minimum Current: Sets the minimum current for Coolstep current control. You can choose between
 *   half and quarter of the run current.
 * 
 * * Stallguard Threshold Value: Sets the level for stall output (see {@link silent_stepper_get_driver_status}).
 *   A lower value gives a higher sensitivity. You have to find a suitable value for your
 *   motor by trial and error, 0 works for most motors.
 * 
 * * Stallguard Mode: Set to 0 for standard resolution or 1 for filtered mode. In filtered mode the Stallguard
 *   signal will be updated every four full-steps.
 */
int silent_stepper_set_coolstep_configuration(SilentStepper *silent_stepper, uint8_t minimum_stallguard_value, uint8_t maximum_stallguard_value, uint8_t current_up_step_width, uint8_t current_down_step_width, uint8_t minimum_current, int8_t stallguard_threshold_value, uint8_t stallguard_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the configuration as set by {@link silent_stepper_set_coolstep_configuration}.
 */
int silent_stepper_get_coolstep_configuration(SilentStepper *silent_stepper, uint8_t *ret_minimum_stallguard_value, uint8_t *ret_maximum_stallguard_value, uint8_t *ret_current_up_step_width, uint8_t *ret_current_down_step_width, uint8_t *ret_minimum_current, int8_t *ret_stallguard_threshold_value, uint8_t *ret_stallguard_mode);

/**
 * \ingroup BrickSilentStepper
 *
 * Note: If you don't know what any of this means you can very likely keep all of
 * the values as default!
 * 
 * Sets miscellaneous configuration parameters.
 * 
 * * Disable Short To Ground Protection: Set to false to enable short to ground protection, otherwise
 *   it is disabled.
 * 
 * * Synchronize Phase Frequency: With this parameter you can synchronize the chopper for both phases
 *   of a two phase motor to avoid the occurrence of a beat. The value range is 0-15. If set to 0,
 *   the synchronization is turned off. Otherwise the synchronization is done through the formula
 *   f_sync = f_clk/(value*64). In Classic Mode the synchronization is automatically switched off.
 *   f_clk is 12.8MHz.
 */
int silent_stepper_set_misc_configuration(SilentStepper *silent_stepper, bool disable_short_to_ground_protection, uint8_t synchronize_phase_frequency);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the configuration as set by {@link silent_stepper_set_misc_configuration}.
 */
int silent_stepper_get_misc_configuration(SilentStepper *silent_stepper, bool *ret_disable_short_to_ground_protection, uint8_t *ret_synchronize_phase_frequency);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the current driver status.
 * 
 * * Open Load: Indicates if an open load is present on phase A, B or both. This could mean that there is a problem
 *   with the wiring of the motor. False detection can occur in fast motion as well as during stand still.
 * 
 * * Short To Ground: Indicates if a short to ground is present on phase A, B or both. If this is detected the driver
 *   automatically becomes disabled and stays disabled until it is enabled again manually.
 * 
 * * Over Temperature: The over temperature indicator switches to "Warning" if the driver IC warms up. The warning flag
 *   is expected during long duration stepper uses. If the temperature limit is reached the indicator switches
 *   to "Limit". In this case the driver becomes disabled until it cools down again.
 * 
 * * Motor Stalled: Is true if a motor stall was detected.
 * 
 * * Actual Motor Current: Indicates the actual current control scaling as used in Coolstep mode.
 *   It represents a multiplier of 1/32 to 32/32 of the
 *   ``Motor Run Current`` as set by {@link silent_stepper_set_basic_configuration}. Example: If a ``Motor Run Current``
 *   of 1000mA was set and the returned value is 15, the ``Actual Motor Current`` is 16/32*1000mA = 500mA.
 * 
 * * Stallguard Result: Indicates the load of the motor. A lower value signals a higher load. Per trial and error
 *   you can find out which value corresponds to a suitable torque for the velocity used in your application.
 *   After that you can use this threshold value to find out if a motor stall becomes probable and react on it (e.g.
 *   decrease velocity).
 *   During stand still this value can not be used for stall detection, it shows the chopper on-time for motor coil A.
 * 
 * * Stealth Voltage Amplitude: Shows the actual PWM scaling. In Stealth mode it can be used to detect motor load and
 *   stall if autoscale is enabled (see {@link silent_stepper_set_stealth_configuration}).
 */
int silent_stepper_get_driver_status(SilentStepper *silent_stepper, uint8_t *ret_open_load, uint8_t *ret_short_to_ground, uint8_t *ret_over_temperature, bool *ret_motor_stalled, uint8_t *ret_actual_motor_current, bool *ret_full_step_active, uint8_t *ret_stallguard_result, uint8_t *ret_stealth_voltage_amplitude);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the minimum voltage, below which the {@link SILENT_STEPPER_CALLBACK_UNDER_VOLTAGE} callback
 * is triggered. The minimum possible value that works with the Silent Stepper
 * Brick is 8V.
 * You can use this function to detect the discharge of a battery that is used
 * to drive the stepper motor. If you have a fixed power supply, you likely do
 * not need this functionality.
 */
int silent_stepper_set_minimum_voltage(SilentStepper *silent_stepper, uint16_t voltage);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the minimum voltage as set by {@link silent_stepper_set_minimum_voltage}.
 */
int silent_stepper_get_minimum_voltage(SilentStepper *silent_stepper, uint16_t *ret_voltage);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the time base of the velocity and the acceleration of the Silent Stepper
 * Brick.
 * 
 * For example, if you want to make one step every 1.5 seconds, you can set
 * the time base to 15 and the velocity to 10. Now the velocity is
 * 10steps/15s = 1steps/1.5s.
 */
int silent_stepper_set_time_base(SilentStepper *silent_stepper, uint32_t time_base);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the time base as set by {@link silent_stepper_set_time_base}.
 */
int silent_stepper_get_time_base(SilentStepper *silent_stepper, uint32_t *ret_time_base);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the following parameters: The current velocity,
 * the current position, the remaining steps, the stack voltage, the external
 * voltage and the current consumption of the stepper motor.
 * 
 * The current consumption is calculated by multiplying the ``Actual Motor Current``
 * value (see {@link silent_stepper_set_basic_configuration}) with the ``Motor Run Current``
 * (see {@link silent_stepper_get_driver_status}). This is an internal calculation of the
 * driver, not an independent external measurement.
 * 
 * The current consumption calculation was broken up to firmware 2.0.1, it is fixed
 * since firmware 2.0.2.
 * 
 * There is also a callback for this function, see {@link SILENT_STEPPER_CALLBACK_ALL_DATA} callback.
 */
int silent_stepper_get_all_data(SilentStepper *silent_stepper, uint16_t *ret_current_velocity, int32_t *ret_current_position, int32_t *ret_remaining_steps, uint16_t *ret_stack_voltage, uint16_t *ret_external_voltage, uint16_t *ret_current_consumption);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the period with which the {@link SILENT_STEPPER_CALLBACK_ALL_DATA} callback is triggered
 * periodically. A value of 0 turns the callback off.
 */
int silent_stepper_set_all_data_period(SilentStepper *silent_stepper, uint32_t period);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the period as set by {@link silent_stepper_set_all_data_period}.
 */
int silent_stepper_get_all_data_period(SilentStepper *silent_stepper, uint32_t *ret_period);

/**
 * \ingroup BrickSilentStepper
 *
 * The SPITF protocol can be used with a dynamic baudrate. If the dynamic baudrate is
 * enabled, the Brick will try to adapt the baudrate for the communication
 * between Bricks and Bricklets according to the amount of data that is transferred.
 * 
 * The baudrate will be increased exponentially if lots of data is sent/received and
 * decreased linearly if little data is sent/received.
 * 
 * This lowers the baudrate in applications where little data is transferred (e.g.
 * a weather station) and increases the robustness. If there is lots of data to transfer
 * (e.g. Thermal Imaging Bricklet) it automatically increases the baudrate as needed.
 * 
 * In cases where some data has to transferred as fast as possible every few seconds
 * (e.g. RS485 Bricklet with a high baudrate but small payload) you may want to turn
 * the dynamic baudrate off to get the highest possible performance.
 * 
 * The maximum value of the baudrate can be set per port with the function
 * {@link silent_stepper_set_spitfp_baudrate}. If the dynamic baudrate is disabled, the baudrate
 * as set by {@link silent_stepper_set_spitfp_baudrate} will be used statically.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Firmware)
 */
int silent_stepper_set_spitfp_baudrate_config(SilentStepper *silent_stepper, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the baudrate config, see {@link silent_stepper_set_spitfp_baudrate_config}.
 * 
 * .. versionadded:: 2.0.4$nbsp;(Firmware)
 */
int silent_stepper_get_spitfp_baudrate_config(SilentStepper *silent_stepper, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the timeout count for the different communication methods.
 * 
 * The methods 0-2 are available for all Bricks, 3-7 only for Master Bricks.
 * 
 * This function is mostly used for debugging during development, in normal operation
 * the counters should nearly always stay at 0.
 */
int silent_stepper_get_send_timeout_count(SilentStepper *silent_stepper, uint8_t communication_method, uint32_t *ret_timeout_count);

/**
 * \ingroup BrickSilentStepper
 *
 * Sets the baudrate for a specific Bricklet port.
 * 
 * If you want to increase the throughput of Bricklets you can increase
 * the baudrate. If you get a high error count because of high
 * interference (see {@link silent_stepper_get_spitfp_error_count}) you can decrease the
 * baudrate.
 * 
 * If the dynamic baudrate feature is enabled, the baudrate set by this
 * function corresponds to the maximum baudrate (see {@link silent_stepper_set_spitfp_baudrate_config}).
 * 
 * Regulatory testing is done with the default baudrate. If CE compatibility
 * or similar is necessary in your applications we recommend to not change
 * the baudrate.
 */
int silent_stepper_set_spitfp_baudrate(SilentStepper *silent_stepper, char bricklet_port, uint32_t baudrate);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the baudrate for a given Bricklet port, see {@link silent_stepper_set_spitfp_baudrate}.
 */
int silent_stepper_get_spitfp_baudrate(SilentStepper *silent_stepper, char bricklet_port, uint32_t *ret_baudrate);

/**
 * \ingroup BrickSilentStepper
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
 * The errors counts are for errors that occur on the Brick side. All
 * Bricklets have a similar function that returns the errors on the Bricklet side.
 */
int silent_stepper_get_spitfp_error_count(SilentStepper *silent_stepper, char bricklet_port, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickSilentStepper
 *
 * Enables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 */
int silent_stepper_enable_status_led(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Disables the status LED.
 * 
 * The status LED is the blue LED next to the USB connector. If enabled is is
 * on and it flickers if data is transfered. If disabled it is always off.
 * 
 * The default state is enabled.
 */
int silent_stepper_disable_status_led(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns *true* if the status LED is enabled, *false* otherwise.
 */
int silent_stepper_is_status_led_enabled(SilentStepper *silent_stepper, bool *ret_enabled);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the firmware and protocol version and the name of the Bricklet for a
 * given port.
 * 
 * This functions sole purpose is to allow automatic flashing of v1.x.y Bricklet
 * plugins.
 */
int silent_stepper_get_protocol1_bricklet_name(SilentStepper *silent_stepper, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]);

/**
 * \ingroup BrickSilentStepper
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has an
 * accuracy of ±15%. Practically it is only useful as an indicator for
 * temperature changes.
 */
int silent_stepper_get_chip_temperature(SilentStepper *silent_stepper, int16_t *ret_temperature);

/**
 * \ingroup BrickSilentStepper
 *
 * Calling this function will reset the Brick. Calling this function
 * on a Brick inside of a stack will reset the whole stack.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int silent_stepper_reset(SilentStepper *silent_stepper);

/**
 * \ingroup BrickSilentStepper
 *
 * Writes 32 bytes of firmware to the bricklet attached at the given port.
 * The bytes are written to the position offset * 32.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int silent_stepper_write_bricklet_plugin(SilentStepper *silent_stepper, char port, uint8_t offset, uint8_t chunk[32]);

/**
 * \ingroup BrickSilentStepper
 *
 * Reads 32 bytes of firmware from the bricklet attached at the given port.
 * The bytes are read starting at the position offset * 32.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int silent_stepper_read_bricklet_plugin(SilentStepper *silent_stepper, char port, uint8_t offset, uint8_t ret_chunk[32]);

/**
 * \ingroup BrickSilentStepper
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
int silent_stepper_get_identity(SilentStepper *silent_stepper, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
