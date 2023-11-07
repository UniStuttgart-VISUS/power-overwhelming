/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_REAL_TIME_CLOCK_H
#define BRICKLET_REAL_TIME_CLOCK_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletRealTimeClock Real-Time Clock Bricklet
 */

/**
 * \ingroup BrickletRealTimeClock
 *
 * Battery-backed real-time clock
 */
typedef Device RealTimeClock;

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME 1

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME 2

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_TIMESTAMP 3

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_OFFSET 4

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_OFFSET 5

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_DATE_TIME_CALLBACK_PERIOD 6

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_DATE_TIME_CALLBACK_PERIOD 7

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_SET_ALARM 8

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_ALARM 9

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletRealTimeClock
 *
 * Signature: \code void callback(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday, int64_t timestamp, void *user_data) \endcode
 * 
 * This callback is triggered periodically with the period that is set by
 * {@link real_time_clock_set_date_time_callback_period}. The parameters are the same
 * as for {@link real_time_clock_get_date_time} and {@link real_time_clock_get_timestamp} combined.
 * 
 * The {@link REAL_TIME_CLOCK_CALLBACK_DATE_TIME} callback is only triggered if the date or time changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define REAL_TIME_CLOCK_CALLBACK_DATE_TIME 10

/**
 * \ingroup BrickletRealTimeClock
 *
 * Signature: \code void callback(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday, int64_t timestamp, void *user_data) \endcode
 * 
 * This callback is triggered every time the current date and time matches the
 * configured alarm (see {@link real_time_clock_set_alarm}). The parameters are the same
 * as for {@link real_time_clock_get_date_time} and {@link real_time_clock_get_timestamp} combined.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
#define REAL_TIME_CLOCK_CALLBACK_ALARM 11


/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_MONDAY 1

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_TUESDAY 2

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_WEDNESDAY 3

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_THURSDAY 4

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_FRIDAY 5

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_SATURDAY 6

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_WEEKDAY_SUNDAY 7

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_ALARM_MATCH_DISABLED -1

/**
 * \ingroup BrickletRealTimeClock
 */
#define REAL_TIME_CLOCK_ALARM_INTERVAL_DISABLED -1

/**
 * \ingroup BrickletRealTimeClock
 *
 * This constant is used to identify a Real-Time Clock Bricklet.
 *
 * The {@link real_time_clock_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define REAL_TIME_CLOCK_DEVICE_IDENTIFIER 268

/**
 * \ingroup BrickletRealTimeClock
 *
 * This constant represents the display name of a Real-Time Clock Bricklet.
 */
#define REAL_TIME_CLOCK_DEVICE_DISPLAY_NAME "Real-Time Clock Bricklet"

/**
 * \ingroup BrickletRealTimeClock
 *
 * Creates the device object \c real_time_clock with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void real_time_clock_create(RealTimeClock *real_time_clock, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Removes the device object \c real_time_clock from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void real_time_clock_destroy(RealTimeClock *real_time_clock);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the real_time_clock_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int real_time_clock_get_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletRealTimeClock
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
int real_time_clock_set_response_expected(RealTimeClock *real_time_clock, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int real_time_clock_set_response_expected_all(RealTimeClock *real_time_clock, bool response_expected);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void real_time_clock_register_callback(RealTimeClock *real_time_clock, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int real_time_clock_get_api_version(RealTimeClock *real_time_clock, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Sets the current date (including weekday) and the current time.
 * 
 * If the backup battery is installed then the real-time clock keeps date and
 * time even if the Bricklet is not powered by a Brick.
 * 
 * The real-time clock handles leap year and inserts the 29th of February
 * accordingly. But leap seconds, time zones and daylight saving time are not
 * handled.
 */
int real_time_clock_set_date_time(RealTimeClock *real_time_clock, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t centisecond, uint8_t weekday);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the current date (including weekday) and the current time of the
 * real-time clock.
 */
int real_time_clock_get_date_time(RealTimeClock *real_time_clock, uint16_t *ret_year, uint8_t *ret_month, uint8_t *ret_day, uint8_t *ret_hour, uint8_t *ret_minute, uint8_t *ret_second, uint8_t *ret_centisecond, uint8_t *ret_weekday);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the current date and the time of the real-time clock.
 * The timestamp has an effective resolution of hundredths of a
 * second and is an offset to 2000-01-01 00:00:00.000.
 */
int real_time_clock_get_timestamp(RealTimeClock *real_time_clock, int64_t *ret_timestamp);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Sets the offset the real-time clock should compensate for in 2.17 ppm steps
 * between -277.76 ppm (-128) and +275.59 ppm (127).
 * 
 * The real-time clock time can deviate from the actual time due to the frequency
 * deviation of its 32.768 kHz crystal. Even without compensation (factory
 * default) the resulting time deviation should be at most ±20 ppm (±52.6
 * seconds per month).
 * 
 * This deviation can be calculated by comparing the same duration measured by the
 * real-time clock (``rtc_duration``) an accurate reference clock
 * (``ref_duration``).
 * 
 * For best results the configured offset should be set to 0 ppm first and then a
 * duration of at least 6 hours should be measured.
 * 
 * The new offset (``new_offset``) can be calculated from the currently configured
 * offset (``current_offset``) and the measured durations as follow::
 * 
 *   new_offset = current_offset - round(1000000 * (rtc_duration - ref_duration) / rtc_duration / 2.17)
 * 
 * If you want to calculate the offset, then we recommend using the calibration
 * dialog in Brick Viewer, instead of doing it manually.
 * 
 * The offset is saved in the EEPROM of the Bricklet and only needs to be
 * configured once.
 */
int real_time_clock_set_offset(RealTimeClock *real_time_clock, int8_t offset);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the offset as set by {@link real_time_clock_set_offset}.
 */
int real_time_clock_get_offset(RealTimeClock *real_time_clock, int8_t *ret_offset);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Sets the period with which the {@link REAL_TIME_CLOCK_CALLBACK_DATE_TIME} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * The {@link REAL_TIME_CLOCK_CALLBACK_DATE_TIME} Callback is only triggered if the date or time changed
 * since the last triggering.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int real_time_clock_set_date_time_callback_period(RealTimeClock *real_time_clock, uint32_t period);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the period as set by {@link real_time_clock_set_date_time_callback_period}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int real_time_clock_get_date_time_callback_period(RealTimeClock *real_time_clock, uint32_t *ret_period);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Configures a repeatable alarm. The {@link REAL_TIME_CLOCK_CALLBACK_ALARM} callback is triggered if the
 * current date and time matches the configured alarm.
 * 
 * Setting a parameter to -1 means that it should be disabled and doesn't take part
 * in the match. Setting all parameters to -1 disables the alarm completely.
 * 
 * For example, to make the alarm trigger every day at 7:30 AM it can be
 * configured as (-1, -1, 7, 30, -1, -1, -1). The hour is set to match 7 and the
 * minute is set to match 30. The alarm is triggered if all enabled parameters
 * match.
 * 
 * The interval has a special role. It allows to make the alarm reconfigure itself.
 * This is useful if you need a repeated alarm that cannot be expressed by matching
 * the current date and time. For example, to make the alarm trigger every 23
 * seconds it can be configured as (-1, -1, -1, -1, -1, -1, 23). Internally the
 * Bricklet will take the current date and time, add 23 seconds to it and set the
 * result as its alarm. The first alarm will be triggered 23 seconds after the
 * call. Because the interval is not -1, the Bricklet will do the same again
 * internally, take the current date and time, add 23 seconds to it and set that
 * as its alarm. This results in a repeated alarm that triggers every 23 seconds.
 * 
 * The interval can also be used in combination with the other parameters. For
 * example, configuring the alarm as (-1, -1, 7, 30, -1, -1, 300) results in an
 * alarm that triggers every day at 7:30 AM and is then repeated every 5 minutes.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int real_time_clock_set_alarm(RealTimeClock *real_time_clock, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second, int8_t weekday, int32_t interval);

/**
 * \ingroup BrickletRealTimeClock
 *
 * Returns the alarm configuration as set by {@link real_time_clock_set_alarm}.
 * 
 * .. versionadded:: 2.0.1$nbsp;(Plugin)
 */
int real_time_clock_get_alarm(RealTimeClock *real_time_clock, int8_t *ret_month, int8_t *ret_day, int8_t *ret_hour, int8_t *ret_minute, int8_t *ret_second, int8_t *ret_weekday, int32_t *ret_interval);

/**
 * \ingroup BrickletRealTimeClock
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
int real_time_clock_get_identity(RealTimeClock *real_time_clock, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
