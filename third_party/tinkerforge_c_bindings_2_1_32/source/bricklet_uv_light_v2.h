/* ***********************************************************
 * This file was automatically generated on 2021-05-06.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.32                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/

#ifndef BRICKLET_UV_LIGHT_V2_H
#define BRICKLET_UV_LIGHT_V2_H

#include "ip_connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup BrickletUVLightV2 UV Light Bricklet 2.0
 */

/**
 * \ingroup BrickletUVLightV2
 *
 * Measures UV-A, UV-B and UV index
 */
typedef Device UVLightV2;

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVA 1

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_UVA_CALLBACK_CONFIGURATION 2

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVA_CALLBACK_CONFIGURATION 3

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVB 5

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_UVB_CALLBACK_CONFIGURATION 6

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVB_CALLBACK_CONFIGURATION 7

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVI 9

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_UVI_CALLBACK_CONFIGURATION 10

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_UVI_CALLBACK_CONFIGURATION 11

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_CONFIGURATION 13

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_CONFIGURATION 14

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_SPITFP_ERROR_COUNT 234

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_BOOTLOADER_MODE 235

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_BOOTLOADER_MODE 236

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER 237

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_WRITE_FIRMWARE 238

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_SET_STATUS_LED_CONFIG 239

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_STATUS_LED_CONFIG 240

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_CHIP_TEMPERATURE 242

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_RESET 243

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_WRITE_UID 248

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_READ_UID 249

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_FUNCTION_GET_IDENTITY 255

/**
 * \ingroup BrickletUVLightV2
 *
 * Signature: \code void callback(int32_t uva, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link uv_light_v2_set_uva_callback_configuration}.
 * 
 * The parameter is the same as {@link uv_light_v2_get_uva}.
 */
#define UV_LIGHT_V2_CALLBACK_UVA 4

/**
 * \ingroup BrickletUVLightV2
 *
 * Signature: \code void callback(int32_t uvb, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link uv_light_v2_set_uvb_callback_configuration}.
 * 
 * The parameter is the same as {@link uv_light_v2_get_uvb}.
 */
#define UV_LIGHT_V2_CALLBACK_UVB 8

/**
 * \ingroup BrickletUVLightV2
 *
 * Signature: \code void callback(int32_t uvi, void *user_data) \endcode
 * 
 * This callback is triggered periodically according to the configuration set by
 * {@link uv_light_v2_set_uvi_callback_configuration}.
 * 
 * The parameter is the same as {@link uv_light_v2_get_uvi}.
 */
#define UV_LIGHT_V2_CALLBACK_UVI 12


/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_THRESHOLD_OPTION_OFF 'x'

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_THRESHOLD_OPTION_OUTSIDE 'o'

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_THRESHOLD_OPTION_INSIDE 'i'

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_THRESHOLD_OPTION_SMALLER '<'

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_THRESHOLD_OPTION_GREATER '>'

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_INTEGRATION_TIME_50MS 0

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_INTEGRATION_TIME_100MS 1

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_INTEGRATION_TIME_200MS 2

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_INTEGRATION_TIME_400MS 3

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_INTEGRATION_TIME_800MS 4

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_MODE_BOOTLOADER 0

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_MODE_FIRMWARE 1

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_OK 0

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_INVALID_MODE 1

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_NO_CHANGE 2

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_STATUS_LED_CONFIG_OFF 0

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_STATUS_LED_CONFIG_ON 1

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2

/**
 * \ingroup BrickletUVLightV2
 */
#define UV_LIGHT_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

/**
 * \ingroup BrickletUVLightV2
 *
 * This constant is used to identify a UV Light Bricklet 2.0.
 *
 * The {@link uv_light_v2_get_identity} function and the
 * {@link IPCON_CALLBACK_ENUMERATE} callback of the IP Connection have a
 * \c device_identifier parameter to specify the Brick's or Bricklet's type.
 */
#define UV_LIGHT_V2_DEVICE_IDENTIFIER 2118

/**
 * \ingroup BrickletUVLightV2
 *
 * This constant represents the display name of a UV Light Bricklet 2.0.
 */
#define UV_LIGHT_V2_DEVICE_DISPLAY_NAME "UV Light Bricklet 2.0"

/**
 * \ingroup BrickletUVLightV2
 *
 * Creates the device object \c uv_light_v2 with the unique device ID \c uid and adds
 * it to the IPConnection \c ipcon.
 */
void uv_light_v2_create(UVLightV2 *uv_light_v2, const char *uid, IPConnection *ipcon);

/**
 * \ingroup BrickletUVLightV2
 *
 * Removes the device object \c uv_light_v2 from its IPConnection and destroys it.
 * The device object cannot be used anymore afterwards.
 */
void uv_light_v2_destroy(UVLightV2 *uv_light_v2);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the response expected flag for the function specified by the
 * \c function_id parameter. It is *true* if the function is expected to
 * send a response, *false* otherwise.
 *
 * For getter functions this is enabled by default and cannot be disabled,
 * because those functions will always send a response. For callback
 * configuration functions it is enabled by default too, but can be disabled
 * via the uv_light_v2_set_response_expected function. For setter functions it is
 * disabled by default and can be enabled.
 *
 * Enabling the response expected flag for a setter function allows to
 * detect timeouts and other error conditions calls of this setter as well.
 * The device will then send a response for this purpose. If this flag is
 * disabled for a setter function then no response is sent and errors are
 * silently ignored, because they cannot be detected.
 */
int uv_light_v2_get_response_expected(UVLightV2 *uv_light_v2, uint8_t function_id, bool *ret_response_expected);

/**
 * \ingroup BrickletUVLightV2
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
int uv_light_v2_set_response_expected(UVLightV2 *uv_light_v2, uint8_t function_id, bool response_expected);

/**
 * \ingroup BrickletUVLightV2
 *
 * Changes the response expected flag for all setter and callback configuration
 * functions of this device at once.
 */
int uv_light_v2_set_response_expected_all(UVLightV2 *uv_light_v2, bool response_expected);

/**
 * \ingroup BrickletUVLightV2
 *
 * Registers the given \c function with the given \c callback_id. The
 * \c user_data will be passed as the last parameter to the \c function.
 */
void uv_light_v2_register_callback(UVLightV2 *uv_light_v2, int16_t callback_id, void (*function)(void), void *user_data);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the API version (major, minor, release) of the bindings for this
 * device.
 */
int uv_light_v2_get_api_version(UVLightV2 *uv_light_v2, uint8_t ret_api_version[3]);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the UVA intensity of the sensor.
 * The sensor has not weighted the intensity with the erythemal
 * action spectrum to get the skin-affecting irradiation. Therefore, you cannot
 * just divide the value by 250 to get the UVA index. To get the UV index use
 * {@link uv_light_v2_get_uvi}.
 * 
 * If the sensor is saturated, then -1 is returned, see {@link uv_light_v2_set_configuration}.
 * 
 * If you want to get the intensity periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVA} callback and set the period with
 * {@link uv_light_v2_set_uva_callback_configuration}.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVA} callback. You can set the callback configuration
 * with {@link uv_light_v2_set_uva_callback_configuration}.
 */
int uv_light_v2_get_uva(UVLightV2 *uv_light_v2, int32_t *ret_uva);

/**
 * \ingroup BrickletUVLightV2
 *
 * The period is the period with which the {@link UV_LIGHT_V2_CALLBACK_UVA} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change
 * within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * It is furthermore possible to constrain the callback with thresholds.
 * 
 * The `option`-parameter together with min/max sets a threshold for the {@link UV_LIGHT_V2_CALLBACK_UVA} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Threshold is turned off"
 *  "'o'",    "Threshold is triggered when the value is *outside* the min and max values"
 *  "'i'",    "Threshold is triggered when the value is *inside* or equal to the min and max values"
 *  "'<'",    "Threshold is triggered when the value is smaller than the min value (max is ignored)"
 *  "'>'",    "Threshold is triggered when the value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * If the option is set to 'x' (threshold turned off) the callback is triggered with the fixed period.
 */
int uv_light_v2_set_uva_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the callback configuration as set by {@link uv_light_v2_set_uva_callback_configuration}.
 */
int uv_light_v2_get_uva_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the UVB intensity of the sensor.
 * The sensor has not weighted the intensity with the erythemal
 * action spectrum to get the skin-affecting irradiation. Therefore, you cannot
 * just divide the value by 250 to get the UVB index. To get the UV index use
 * {@link uv_light_v2_get_uvi}.
 * 
 * If the sensor is saturated, then -1 is returned, see {@link uv_light_v2_set_configuration}.
 * 
 * If you want to get the intensity periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVB} callback and set the period with
 * {@link uv_light_v2_set_uvb_callback_configuration}.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVB} callback. You can set the callback configuration
 * with {@link uv_light_v2_set_uvb_callback_configuration}.
 */
int uv_light_v2_get_uvb(UVLightV2 *uv_light_v2, int32_t *ret_uvb);

/**
 * \ingroup BrickletUVLightV2
 *
 * The period is the period with which the {@link UV_LIGHT_V2_CALLBACK_UVB} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change
 * within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * It is furthermore possible to constrain the callback with thresholds.
 * 
 * The `option`-parameter together with min/max sets a threshold for the {@link UV_LIGHT_V2_CALLBACK_UVB} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Threshold is turned off"
 *  "'o'",    "Threshold is triggered when the value is *outside* the min and max values"
 *  "'i'",    "Threshold is triggered when the value is *inside* or equal to the min and max values"
 *  "'<'",    "Threshold is triggered when the value is smaller than the min value (max is ignored)"
 *  "'>'",    "Threshold is triggered when the value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * If the option is set to 'x' (threshold turned off) the callback is triggered with the fixed period.
 */
int uv_light_v2_set_uvb_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the callback configuration as set by {@link uv_light_v2_set_uvb_callback_configuration}.
 */
int uv_light_v2_get_uvb_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the UV index of the sensor, the index is given in 1/10.
 * 
 * If the sensor is saturated, then -1 is returned, see {@link uv_light_v2_set_configuration}.
 * 
 * If you want to get the intensity periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVI} callback and set the period with
 * {@link uv_light_v2_set_uvi_callback_configuration}.
 * 
 * 
 * If you want to get the value periodically, it is recommended to use the
 * {@link UV_LIGHT_V2_CALLBACK_UVI} callback. You can set the callback configuration
 * with {@link uv_light_v2_set_uvi_callback_configuration}.
 */
int uv_light_v2_get_uvi(UVLightV2 *uv_light_v2, int32_t *ret_uvi);

/**
 * \ingroup BrickletUVLightV2
 *
 * The period is the period with which the {@link UV_LIGHT_V2_CALLBACK_UVI} callback is triggered
 * periodically. A value of 0 turns the callback off.
 * 
 * If the `value has to change`-parameter is set to true, the callback is only
 * triggered after the value has changed. If the value didn't change
 * within the period, the callback is triggered immediately on change.
 * 
 * If it is set to false, the callback is continuously triggered with the period,
 * independent of the value.
 * 
 * It is furthermore possible to constrain the callback with thresholds.
 * 
 * The `option`-parameter together with min/max sets a threshold for the {@link UV_LIGHT_V2_CALLBACK_UVI} callback.
 * 
 * The following options are possible:
 * 
 * \verbatim
 *  "Option", "Description"
 * 
 *  "'x'",    "Threshold is turned off"
 *  "'o'",    "Threshold is triggered when the value is *outside* the min and max values"
 *  "'i'",    "Threshold is triggered when the value is *inside* or equal to the min and max values"
 *  "'<'",    "Threshold is triggered when the value is smaller than the min value (max is ignored)"
 *  "'>'",    "Threshold is triggered when the value is greater than the min value (max is ignored)"
 * \endverbatim
 * 
 * If the option is set to 'x' (threshold turned off) the callback is triggered with the fixed period.
 */
int uv_light_v2_set_uvi_callback_configuration(UVLightV2 *uv_light_v2, uint32_t period, bool value_has_to_change, char option, int32_t min, int32_t max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the callback configuration as set by {@link uv_light_v2_set_uvi_callback_configuration}.
 */
int uv_light_v2_get_uvi_callback_configuration(UVLightV2 *uv_light_v2, uint32_t *ret_period, bool *ret_value_has_to_change, char *ret_option, int32_t *ret_min, int32_t *ret_max);

/**
 * \ingroup BrickletUVLightV2
 *
 * Sets the configuration of the sensor. The integration time can be configured
 * between 50 and 800 ms. With a shorter integration time the sensor reading updates
 * more often but contains more noise. With a longer integration the sensor reading
 * contains less noise but updates less often.
 * 
 * With a longer integration time (especially 800 ms) and a higher UV intensity the
 * sensor can be saturated. If this happens the UVA/UVB/UVI readings are all -1.
 * In this case you need to choose a shorter integration time.
 */
int uv_light_v2_set_configuration(UVLightV2 *uv_light_v2, uint8_t integration_time);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the configuration as set by {@link uv_light_v2_set_configuration}.
 */
int uv_light_v2_get_configuration(UVLightV2 *uv_light_v2, uint8_t *ret_integration_time);

/**
 * \ingroup BrickletUVLightV2
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
int uv_light_v2_get_spitfp_error_count(UVLightV2 *uv_light_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow);

/**
 * \ingroup BrickletUVLightV2
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
int uv_light_v2_set_bootloader_mode(UVLightV2 *uv_light_v2, uint8_t mode, uint8_t *ret_status);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the current bootloader mode, see {@link uv_light_v2_set_bootloader_mode}.
 */
int uv_light_v2_get_bootloader_mode(UVLightV2 *uv_light_v2, uint8_t *ret_mode);

/**
 * \ingroup BrickletUVLightV2
 *
 * Sets the firmware pointer for {@link uv_light_v2_write_firmware}. The pointer has
 * to be increased by chunks of size 64. The data is written to flash
 * every 4 chunks (which equals to one page of size 256).
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int uv_light_v2_set_write_firmware_pointer(UVLightV2 *uv_light_v2, uint32_t pointer);

/**
 * \ingroup BrickletUVLightV2
 *
 * Writes 64 Bytes of firmware at the position as written by
 * {@link uv_light_v2_set_write_firmware_pointer} before. The firmware is written
 * to flash every 4 chunks.
 * 
 * You can only write firmware in bootloader mode.
 * 
 * This function is used by Brick Viewer during flashing. It should not be
 * necessary to call it in a normal user program.
 */
int uv_light_v2_write_firmware(UVLightV2 *uv_light_v2, uint8_t data[64], uint8_t *ret_status);

/**
 * \ingroup BrickletUVLightV2
 *
 * Sets the status LED configuration. By default the LED shows
 * communication traffic between Brick and Bricklet, it flickers once
 * for every 10 received data packets.
 * 
 * You can also turn the LED permanently on/off or show a heartbeat.
 * 
 * If the Bricklet is in bootloader mode, the LED is will show heartbeat by default.
 */
int uv_light_v2_set_status_led_config(UVLightV2 *uv_light_v2, uint8_t config);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the configuration as set by {@link uv_light_v2_set_status_led_config}
 */
int uv_light_v2_get_status_led_config(UVLightV2 *uv_light_v2, uint8_t *ret_config);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the temperature as measured inside the microcontroller. The
 * value returned is not the ambient temperature!
 * 
 * The temperature is only proportional to the real temperature and it has bad
 * accuracy. Practically it is only useful as an indicator for
 * temperature changes.
 */
int uv_light_v2_get_chip_temperature(UVLightV2 *uv_light_v2, int16_t *ret_temperature);

/**
 * \ingroup BrickletUVLightV2
 *
 * Calling this function will reset the Bricklet. All configurations
 * will be lost.
 * 
 * After a reset you have to create new device objects,
 * calling functions on the existing ones will result in
 * undefined behavior!
 */
int uv_light_v2_reset(UVLightV2 *uv_light_v2);

/**
 * \ingroup BrickletUVLightV2
 *
 * Writes a new UID into flash. If you want to set a new UID
 * you have to decode the Base58 encoded UID string into an
 * integer first.
 * 
 * We recommend that you use Brick Viewer to change the UID.
 */
int uv_light_v2_write_uid(UVLightV2 *uv_light_v2, uint32_t uid);

/**
 * \ingroup BrickletUVLightV2
 *
 * Returns the current UID as an integer. Encode as
 * Base58 to get the usual string version.
 */
int uv_light_v2_read_uid(UVLightV2 *uv_light_v2, uint32_t *ret_uid);

/**
 * \ingroup BrickletUVLightV2
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
int uv_light_v2_get_identity(UVLightV2 *uv_light_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier);

#ifdef __cplusplus
}
#endif

#endif
