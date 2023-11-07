/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_LASER_RANGE_FINDER_H
#define BRICKLET_LASER_RANGE_FINDER_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletLaserRangeFinder Laser Range Finder Bricklet
 */

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Measures distance up to 40m with laser light
 */
typedef Device LaserRangeFinder;

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE 1

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY 2

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_PERIOD 3

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_PERIOD 4

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_PERIOD 5

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_DISTANCE_CALLBACK_THRESHOLD 7

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_DISTANCE_CALLBACK_THRESHOLD 8

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_VELOCITY_CALLBACK_THRESHOLD 9

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_VELOCITY_CALLBACK_THRESHOLD 10

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_DEBOUNCE_PERIOD 11

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_DEBOUNCE_PERIOD 12

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_MOVING_AVERAGE 13

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_MOVING_AVERAGE 14

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_MODE 15

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_MODE 16

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_ENABLE_LASER 17

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_DISABLE_LASER 18

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_IS_LASER_ENABLED 19

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_SENSOR_HARDWARE_VERSION 24

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_SET_CONFIGURATION 25

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_CONFIGURATION 26

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Signature: \code void callback(uint16_t distance, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link laser_range_finder_set_distance_callback_period}. The parameter is the distance
 * value of the sensor.
 * 
 * The {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE} callback is only triggered if the distance value has changed
 * since the last triggering.
 */
#define LASER_RANGE_FINDER_CALLBACK_DISTANCE 20

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link laser_range_finder_set_velocity_callback_period}. The parameter is the velocity
 * value of the sensor.
 * 
 * The {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY} callback is only triggered if the velocity has changed since
 * the last triggering.
 */
#define LASER_RANGE_FINDER_CALLBACK_VELOCITY 21

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Signature: \code void callback(uint16_t distance, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link laser_range_finder_set_distance_callback_threshold} is reached.
 * The parameter is the distance value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link laser_range_finder_set_debounce_period}.
 */
#define LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED 22

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Signature: \code void callback(int16_t velocity, void *user_data) \endcode
 * 
 * This callback is triggered when the threshold as set by
 * {@link laser_range_finder_set_velocity_callback_threshold} is reached.
 * The parameter is the velocity value of the sensor.
 * 
 * If the threshold keeps being reached, the callback is triggered periodically
 * with the period as set by {@link laser_range_finder_set_debounce_period}.
 */
#define LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED 23


/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_MODE_DISTANCE 0

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_MODE_VELOCITY_MAX_13MS 1

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_MODE_VELOCITY_MAX_32MS 2

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_MODE_VELOCITY_MAX_64MS 3

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_MODE_VELOCITY_MAX_127MS 4

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_VERSION_1 1

/**
 * \ingroup BrickletLaserRangeFinder
 */
#define LASER_RANGE_FINDER_VERSION_3 3

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * This constant is used to identify a Laser Range Finder Bricklet.
 *
 * The {@link laser_range_finder_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define LASER_RANGE_FINDER_DEVICE_IDENTIFIER 255

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * This constant represents the display name of a Laser Range Finder Bricklet.
 */
#define LASER_RANGE_FINDER_DEVICE_DISPLAY_NAME "Laser Range Finder Bricklet"

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Creates the device object \c laser_range_finder with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void laser_range_finder_create(LaserRangeFinder *laser_range_finder, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Removes the device object \c laser_range_finder from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void laser_range_finder_destroy(LaserRangeFinder *laser_range_finder);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the laser_range_finder_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int laser_range_finder_get_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletLaserRangeFinder
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
int laser_range_finder_set_response_expected(LaserRangeFinder *laser_range_finder, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int laser_range_finder_set_response_expected_all(LaserRangeFinder *laser_range_finder, bool response_expected);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void laser_range_finder_register_callback(LaserRangeFinder *laser_range_finder, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int laser_range_finder_get_api_version(LaserRangeFinder *laser_range_finder, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the measured distance.
 * 
 * Sensor hardware version 1 (see {@link laser_range_finder_get_sensor_hardware_version}) cannot
 * measure distance and velocity at the same time. Therefore, the distance mode
 * has to be enabled using {@link laser_range_finder_set_mode}.
 * Sensor hardware version 3 can measure distance and velocity at the same
 * time. Also the laser has to be enabled, see {@link laser_range_finder_enable_laser}.
 * 
 * If you want to get the distance periodically, it is recommended to
 * use the {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE} callback and set the period with
 * {@link laser_range_finder_set_distance_callback_period}.
 */
int laser_range_finder_get_distance(LaserRangeFinder *laser_range_finder, uint16_t *ret_distance);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the measured velocity.
 * 
 * Sensor hardware version 1 (see {@link laser_range_finder_get_sensor_hardware_version}) cannot
 * measure distance and velocity at the same time. Therefore, the velocity mode
 * has to be enabled using {@link laser_range_finder_set_mode}.
 * Sensor hardware version 3 can measure distance and velocity at the same
 * time, but the velocity measurement only produces stables results if a fixed
 * measurement rate (see {@link laser_range_finder_set_configuration}) is configured. Also the laser
 * has to be enabled, see {@link laser_range_finder_enable_laser}.
 * 
 * If you want to get the velocity periodically, it is recommended to
 * use the {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY} callback and set the period with
 * {@link laser_range_finder_set_velocity_callback_period}.
 */
int laser_range_finder_get_velocity(LaserRangeFinder *laser_range_finder, int16_t *ret_velocity);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the period with which the {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE} callback is only triggered if the distance value has
 * changed since the last triggering.
 */
int laser_range_finder_set_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the period as set by {@link laser_range_finder_set_distance_callback_period}.
 */
int laser_range_finder_get_distance_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the period with which the {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY} callback is only triggered if the velocity value has
 * changed since the last triggering.
 */
int laser_range_finder_set_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t period);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the period as set by {@link laser_range_finder_set_velocity_callback_period}.
 */
int laser_range_finder_get_velocity_callback_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_period);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the thresholds for the {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the distance value is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the distance value is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the distance value is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the distance value is greater than the min value (max is ignored)"
 * \endverbatim
 */
int laser_range_finder_set_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char option, uint16_t min, uint16_t max);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the threshold as set by {@link laser_range_finder_set_distance_callback_threshold}.
 */
int laser_range_finder_get_distance_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, uint16_t *ret_min, uint16_t *ret_max);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the thresholds for the {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Callback is turned off"
 *  "'o'",    "Callback is triggered when the velocity is *outside* the min and max values"
 *  "'i'",    "Callback is triggered when the velocity is *inside* the min and max values"
 *  "'<'",    "Callback is triggered when the velocity is smaller than the min value (max is ignored)"
 *  "'>'",    "Callback is triggered when the velocity is greater than the min value (max is ignored)"
 * \endverbatim
 */
int laser_range_finder_set_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char option, int16_t min, int16_t max);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the threshold as set by {@link laser_range_finder_set_velocity_callback_threshold}.
 */
int laser_range_finder_get_velocity_callback_threshold(LaserRangeFinder *laser_range_finder, char *ret_option, int16_t *ret_min, int16_t *ret_max);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the period with which the threshold callbacks
 * 
 * * {@link LASER_RANGE_FINDER_CALLBACK_DISTANCE_REACHED},
 * * {@link LASER_RANGE_FINDER_CALLBACK_VELOCITY_REACHED},
 * 
 * are triggered, if the thresholds
 * 
 * * {@link laser_range_finder_set_distance_callback_threshold},
 * * {@link laser_range_finder_set_velocity_callback_threshold},
 * 
 * keep being reached.
 */
int laser_range_finder_set_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t debounce);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the debounce period as set by {@link laser_range_finder_set_debounce_period}.
 */
int laser_range_finder_get_debounce_period(LaserRangeFinder *laser_range_finder, uint32_t *ret_debounce);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Sets the length of a `moving averaging <https://en.wikipedia.org/wiki/Moving_average>`__
 * for the distance and velocity.
 * 
 * Setting the length to 0 will turn the averaging completely off. With less
 * averaging, there is more noise on the data.
 */
int laser_range_finder_set_moving_average(LaserRangeFinder *laser_range_finder, uint8_t distance_average_length, uint8_t velocity_average_length);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the length moving average as set by {@link laser_range_finder_set_moving_average}.
 */
int laser_range_finder_get_moving_average(LaserRangeFinder *laser_range_finder, uint8_t *ret_distance_average_length, uint8_t *ret_velocity_average_length);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * \note
 *  This function is only available if you have a LIDAR-Lite sensor with hardware
 *  version 1. Use {@link laser_range_finder_set_configuration} for hardware version 3. You can check
 *  the sensor hardware version using {@link laser_range_finder_get_sensor_hardware_version}.
 * 
 * The LIDAR-Lite sensor (hardware version 1) has five different modes. One mode is
 * for distance measurements and four modes are for velocity measurements with
 * different ranges.
 * 
 * The following modes are available:
 * 
 * * 0: Distance is measured with resolution 1.0 cm and range 0-4000 cm
 * * 1: Velocity is measured with resolution 0.1 m/s and range is 0-12.7 m/s
 * * 2: Velocity is measured with resolution 0.25 m/s and range is 0-31.75 m/s
 * * 3: Velocity is measured with resolution 0.5 m/s and range is 0-63.5 m/s
 * * 4: Velocity is measured with resolution 1.0 m/s and range is 0-127 m/s
 */
int laser_range_finder_set_mode(LaserRangeFinder *laser_range_finder, uint8_t mode);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the mode as set by {@link laser_range_finder_set_mode}.
 */
int laser_range_finder_get_mode(LaserRangeFinder *laser_range_finder, uint8_t *ret_mode);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Activates the laser of the LIDAR.
 * 
 * We recommend that you wait 250ms after enabling the laser before
 * the first call of {@link laser_range_finder_get_distance} to ensure stable measurements.
 */
int laser_range_finder_enable_laser(LaserRangeFinder *laser_range_finder);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Deactivates the laser of the LIDAR.
 */
int laser_range_finder_disable_laser(LaserRangeFinder *laser_range_finder);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns *true* if the laser is enabled, *false* otherwise.
 */
int laser_range_finder_is_laser_enabled(LaserRangeFinder *laser_range_finder, bool *ret_laser_enabled);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the LIDAR-Lite hardware version.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Plugin)
 */
int laser_range_finder_get_sensor_hardware_version(LaserRangeFinder *laser_range_finder, uint8_t *ret_version);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * \note
 *  This function is only available if you have a LIDAR-Lite sensor with hardware
 *  version 3. Use {@link laser_range_finder_set_mode} for hardware version 1. You can check
 *  the sensor hardware version using {@link laser_range_finder_get_sensor_hardware_version}.
 * 
 * The **Acquisition Count** defines the number of times the Laser Range Finder Bricklet
 * will integrate acquisitions to find a correlation record peak. With a higher count,
 * the Bricklet can measure longer distances. With a lower count, the rate increases. The
 * allowed values are 1-255.
 * 
 * If you set **Enable Quick Termination** to true, the distance measurement will be terminated
 * early if a high peak was already detected. This means that a higher measurement rate can be achieved
 * and long distances can be measured at the same time. However, the chance of false-positive
 * distance measurements increases.
 * 
 * Normally the distance is calculated with a detection algorithm that uses peak value,
 * signal strength and noise. You can however also define a fixed **Threshold Value**.
 * Set this to a low value if you want to measure the distance to something that has
 * very little reflection (e.g. glass) and set it to a high value if you want to measure
 * the distance to something with a very high reflection (e.g. mirror). Set this to 0 to
 * use the default algorithm. The other allowed values are 1-255.
 * 
 * Set the **Measurement Frequency** to force a fixed measurement rate. If set to 0,
 * the Laser Range Finder Bricklet will use the optimal frequency according to the other
 * configurations and the actual measured distance. Since the rate is not fixed in this case,
 * the velocity measurement is not stable. For a stable velocity measurement you should
 * set a fixed measurement frequency. The lower the frequency, the higher is the resolution
 * of the calculated velocity. The allowed values are 10Hz-500Hz (and 0 to turn the fixed
 * frequency off).
 * 
 * .. versionadded:: 2.0.3$nbsp;(Plugin)
 */
int laser_range_finder_set_configuration(LaserRangeFinder *laser_range_finder, uint8_t acquisition_count, bool enable_quick_termination, uint8_t threshold_value, uint16_t measurement_frequency);

/**
 * \ingroup BrickletLaserRangeFinder
 *
 * Returns the configuration as set by {@link laser_range_finder_set_configuration}.
 * 
 * .. versionadded:: 2.0.3$nbsp;(Plugin)
 */
int laser_range_finder_get_configuration(LaserRangeFinder *laser_range_finder, uint8_t *ret_acquisition_count, bool *ret_enable_quick_termination, uint8_t *ret_threshold_value, uint16_t *ret_measurement_frequency);

/**
 * \ingroup BrickletLaserRangeFinder
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
int laser_range_finder_get_identity(LaserRangeFinder *laser_range_finder, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
