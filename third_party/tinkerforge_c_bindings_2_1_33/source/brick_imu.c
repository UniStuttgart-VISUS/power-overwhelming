/* ***********************************************************
 * This file was automatically generated on 2022-05-11.      *
 *                                                           *
 * C/C++ Bindings Version 2.1.33                             *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#define IPCON_EXPOSE_INTERNALS

#include "brick_imu.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Acceleration_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*MagneticField_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*AngularVelocity_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*AllData_CallbackFunction)(int16_t acc_x, int16_t acc_y, int16_t acc_z, int16_t mag_x, int16_t mag_y, int16_t mag_z, int16_t ang_x, int16_t ang_y, int16_t ang_z, int16_t temperature, void *user_data);

typedef void (*Orientation_CallbackFunction)(int16_t roll, int16_t pitch, int16_t yaw, void *user_data);

typedef void (*Quaternion_CallbackFunction)(float x, float y, float z, float w, void *user_data);

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(push)
	#pragma pack(1)
	#define ATTRIBUTE_PACKED
#elif defined __GNUC__
	#ifdef _WIN32
		// workaround struct packing bug in GCC 4.7 on Windows
		// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52991
		#define ATTRIBUTE_PACKED __attribute__((gcc_struct, packed))
	#else
		#define ATTRIBUTE_PACKED __attribute__((packed))
	#endif
#else
	#error unknown compiler, do not know how to enable struct packing
#endif

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAcceleration_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAcceleration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticField_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetMagneticField_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAngularVelocity_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetAngularVelocity_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllData_Request;

typedef struct {
	PacketHeader header;
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	int16_t ang_x;
	int16_t ang_y;
	int16_t ang_z;
	int16_t temperature;
} ATTRIBUTE_PACKED GetAllData_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientation_Request;

typedef struct {
	PacketHeader header;
	int16_t roll;
	int16_t pitch;
	int16_t yaw;
} ATTRIBUTE_PACKED GetOrientation_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternion_Request;

typedef struct {
	PacketHeader header;
	float x;
	float y;
	float z;
	float w;
} ATTRIBUTE_PACKED GetQuaternion_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIMUTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetIMUTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LedsOn_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED LedsOff_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED AreLedsOn_Request;

typedef struct {
	PacketHeader header;
	uint8_t leds;
} ATTRIBUTE_PACKED AreLedsOn_Response;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED SetAccelerationRange_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationRange_Request;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED GetAccelerationRange_Response;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED SetMagnetometerRange_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagnetometerRange_Request;

typedef struct {
	PacketHeader header;
	uint8_t range;
} ATTRIBUTE_PACKED GetMagnetometerRange_Response;

typedef struct {
	PacketHeader header;
	uint16_t speed;
} ATTRIBUTE_PACKED SetConvergenceSpeed_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetConvergenceSpeed_Request;

typedef struct {
	PacketHeader header;
	uint16_t speed;
} ATTRIBUTE_PACKED GetConvergenceSpeed_Response;

typedef struct {
	PacketHeader header;
	uint8_t typ;
	int16_t data[10];
} ATTRIBUTE_PACKED SetCalibration_Request;

typedef struct {
	PacketHeader header;
	uint8_t typ;
} ATTRIBUTE_PACKED GetCalibration_Request;

typedef struct {
	PacketHeader header;
	int16_t data[10];
} ATTRIBUTE_PACKED GetCalibration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAccelerationPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAccelerationPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetMagneticFieldPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticFieldPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetMagneticFieldPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAngularVelocityPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAngularVelocityPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAngularVelocityPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetAllDataPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllDataPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetAllDataPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetOrientationPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientationPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetOrientationPeriod_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED SetQuaternionPeriod_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternionPeriod_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
} ATTRIBUTE_PACKED GetQuaternionPeriod_Response;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED Acceleration_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED MagneticField_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED AngularVelocity_Callback;

typedef struct {
	PacketHeader header;
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	int16_t ang_x;
	int16_t ang_y;
	int16_t ang_z;
	int16_t temperature;
} ATTRIBUTE_PACKED AllData_Callback;

typedef struct {
	PacketHeader header;
	int16_t roll;
	int16_t pitch;
	int16_t yaw;
} ATTRIBUTE_PACKED Orientation_Callback;

typedef struct {
	PacketHeader header;
	float x;
	float y;
	float z;
	float w;
} ATTRIBUTE_PACKED Quaternion_Callback;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED OrientationCalculationOn_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED OrientationCalculationOff_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsOrientationCalculationOn_Request;

typedef struct {
	PacketHeader header;
	uint8_t orientation_calculation_on;
} ATTRIBUTE_PACKED IsOrientationCalculationOn_Response;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrateConfig_Response;

typedef struct {
	PacketHeader header;
	uint8_t communication_method;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t timeout_count;
} ATTRIBUTE_PACKED GetSendTimeoutCount_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
	uint32_t baudrate;
} ATTRIBUTE_PACKED SetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	char bricklet_port;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Request;

typedef struct {
	PacketHeader header;
	uint32_t baudrate;
} ATTRIBUTE_PACKED GetSPITFPBaudrate_Response;

typedef struct {
	PacketHeader header;
	char bricklet_port;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Request;

typedef struct {
	PacketHeader header;
	uint32_t error_count_ack_checksum;
	uint32_t error_count_message_checksum;
	uint32_t error_count_frame;
	uint32_t error_count_overflow;
} ATTRIBUTE_PACKED GetSPITFPErrorCount_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED EnableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED DisableStatusLED_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Request;

typedef struct {
	PacketHeader header;
	uint8_t enabled;
} ATTRIBUTE_PACKED IsStatusLEDEnabled_Response;

typedef struct {
	PacketHeader header;
	char port;
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Request;

typedef struct {
	PacketHeader header;
	uint8_t protocol_version;
	uint8_t firmware_version[3];
	char name[40];
} ATTRIBUTE_PACKED GetProtocol1BrickletName_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetChipTemperature_Request;

typedef struct {
	PacketHeader header;
	int16_t temperature;
} ATTRIBUTE_PACKED GetChipTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED Reset_Request;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t offset;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED WriteBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	char port;
	uint8_t offset;
} ATTRIBUTE_PACKED ReadBrickletPlugin_Request;

typedef struct {
	PacketHeader header;
	uint8_t chunk[32];
} ATTRIBUTE_PACKED ReadBrickletPlugin_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetIdentity_Request;

typedef struct {
	PacketHeader header;
	char uid[8];
	char connected_uid[8];
	char position;
	uint8_t hardware_version[3];
	uint8_t firmware_version[3];
	uint16_t device_identifier;
} ATTRIBUTE_PACKED GetIdentity_Response;

#if defined _MSC_VER || defined __BORLANDC__
	#pragma pack(pop)
#endif
#undef ATTRIBUTE_PACKED

static void imu_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	Acceleration_CallbackFunction callback_function;
	void *user_data;
	Acceleration_Callback *callback;

	if (packet->header.length != sizeof(Acceleration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Acceleration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ACCELERATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ACCELERATION];
	callback = (Acceleration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_callback_wrapper_magnetic_field(DevicePrivate *device_p, Packet *packet) {
	MagneticField_CallbackFunction callback_function;
	void *user_data;
	MagneticField_Callback *callback;

	if (packet->header.length != sizeof(MagneticField_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (MagneticField_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_MAGNETIC_FIELD];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_MAGNETIC_FIELD];
	callback = (MagneticField_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_callback_wrapper_angular_velocity(DevicePrivate *device_p, Packet *packet) {
	AngularVelocity_CallbackFunction callback_function;
	void *user_data;
	AngularVelocity_Callback *callback;

	if (packet->header.length != sizeof(AngularVelocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AngularVelocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ANGULAR_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ANGULAR_VELOCITY];
	callback = (AngularVelocity_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_callback_wrapper_all_data(DevicePrivate *device_p, Packet *packet) {
	AllData_CallbackFunction callback_function;
	void *user_data;
	AllData_Callback *callback;

	if (packet->header.length != sizeof(AllData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ALL_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ALL_DATA];
	callback = (AllData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->acc_x = leconvert_int16_from(callback->acc_x);
	callback->acc_y = leconvert_int16_from(callback->acc_y);
	callback->acc_z = leconvert_int16_from(callback->acc_z);
	callback->mag_x = leconvert_int16_from(callback->mag_x);
	callback->mag_y = leconvert_int16_from(callback->mag_y);
	callback->mag_z = leconvert_int16_from(callback->mag_z);
	callback->ang_x = leconvert_int16_from(callback->ang_x);
	callback->ang_y = leconvert_int16_from(callback->ang_y);
	callback->ang_z = leconvert_int16_from(callback->ang_z);
	callback->temperature = leconvert_int16_from(callback->temperature);

	callback_function(callback->acc_x, callback->acc_y, callback->acc_z, callback->mag_x, callback->mag_y, callback->mag_z, callback->ang_x, callback->ang_y, callback->ang_z, callback->temperature, user_data);
}

static void imu_callback_wrapper_orientation(DevicePrivate *device_p, Packet *packet) {
	Orientation_CallbackFunction callback_function;
	void *user_data;
	Orientation_Callback *callback;

	if (packet->header.length != sizeof(Orientation_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Orientation_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ORIENTATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_ORIENTATION];
	callback = (Orientation_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->roll = leconvert_int16_from(callback->roll);
	callback->pitch = leconvert_int16_from(callback->pitch);
	callback->yaw = leconvert_int16_from(callback->yaw);

	callback_function(callback->roll, callback->pitch, callback->yaw, user_data);
}

static void imu_callback_wrapper_quaternion(DevicePrivate *device_p, Packet *packet) {
	Quaternion_CallbackFunction callback_function;
	void *user_data;
	Quaternion_Callback *callback;

	if (packet->header.length != sizeof(Quaternion_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Quaternion_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_QUATERNION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_CALLBACK_QUATERNION];
	callback = (Quaternion_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_float_from(callback->x);
	callback->y = leconvert_float_from(callback->y);
	callback->z = leconvert_float_from(callback->z);
	callback->w = leconvert_float_from(callback->w);

	callback_function(callback->x, callback->y, callback->z, callback->w, user_data);
}

void imu_create(IMU *imu, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(imu, uid, ipcon_p, 2, 0, 4, IMU_DEVICE_IDENTIFIER);

	device_p = imu->p;

	device_p->response_expected[IMU_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_MAGNETIC_FIELD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ANGULAR_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ALL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ORIENTATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_QUATERNION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_IMU_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_LEDS_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_LEDS_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_ARE_LEDS_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_ACCELERATION_RANGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_ACCELERATION_RANGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_MAGNETOMETER_RANGE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_MAGNETOMETER_RANGE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_CONVERGENCE_SPEED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_CONVERGENCE_SPEED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ACCELERATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_MAGNETIC_FIELD_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_MAGNETIC_FIELD_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_ALL_DATA_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ALL_DATA_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_ORIENTATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_ORIENTATION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_QUATERNION_PERIOD] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_QUATERNION_PERIOD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_ORIENTATION_CALCULATION_ON] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_ORIENTATION_CALCULATION_OFF] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_IS_ORIENTATION_CALCULATION_ON] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_SEND_TIMEOUT_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_SET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_GET_SPITFP_BAUDRATE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_ENABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_DISABLE_STATUS_LED] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_IS_STATUS_LED_ENABLED] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_WRITE_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_FUNCTION_READ_BRICKLET_PLUGIN] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IMU_CALLBACK_ACCELERATION] = imu_callback_wrapper_acceleration;
	device_p->callback_wrappers[IMU_CALLBACK_MAGNETIC_FIELD] = imu_callback_wrapper_magnetic_field;
	device_p->callback_wrappers[IMU_CALLBACK_ANGULAR_VELOCITY] = imu_callback_wrapper_angular_velocity;
	device_p->callback_wrappers[IMU_CALLBACK_ALL_DATA] = imu_callback_wrapper_all_data;
	device_p->callback_wrappers[IMU_CALLBACK_ORIENTATION] = imu_callback_wrapper_orientation;
	device_p->callback_wrappers[IMU_CALLBACK_QUATERNION] = imu_callback_wrapper_quaternion;

	ipcon_add_device(ipcon_p, device_p);
}

void imu_destroy(IMU *imu) {
	device_release(imu->p);
}

int imu_get_response_expected(IMU *imu, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(imu->p, function_id, ret_response_expected);
}

int imu_set_response_expected(IMU *imu, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(imu->p, function_id, response_expected);
}

int imu_set_response_expected_all(IMU *imu, bool response_expected) {
	return device_set_response_expected_all(imu->p, response_expected);
}

void imu_register_callback(IMU *imu, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(imu->p, callback_id, function, user_data);
}

int imu_get_api_version(IMU *imu, uint8_t ret_api_version[3]) {
	return device_get_api_version(imu->p, ret_api_version);
}

int imu_get_acceleration(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu->p;
	GetAcceleration_Request request;
	GetAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);

	return ret;
}

int imu_get_magnetic_field(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu->p;
	GetMagneticField_Request request;
	GetMagneticField_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_MAGNETIC_FIELD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);

	return ret;
}

int imu_get_angular_velocity(IMU *imu, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu->p;
	GetAngularVelocity_Request request;
	GetAngularVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ANGULAR_VELOCITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);

	return ret;
}

int imu_get_all_data(IMU *imu, int16_t *ret_acc_x, int16_t *ret_acc_y, int16_t *ret_acc_z, int16_t *ret_mag_x, int16_t *ret_mag_y, int16_t *ret_mag_z, int16_t *ret_ang_x, int16_t *ret_ang_y, int16_t *ret_ang_z, int16_t *ret_temperature) {
	DevicePrivate *device_p = imu->p;
	GetAllData_Request request;
	GetAllData_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ALL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_acc_x = leconvert_int16_from(response.acc_x);
	*ret_acc_y = leconvert_int16_from(response.acc_y);
	*ret_acc_z = leconvert_int16_from(response.acc_z);
	*ret_mag_x = leconvert_int16_from(response.mag_x);
	*ret_mag_y = leconvert_int16_from(response.mag_y);
	*ret_mag_z = leconvert_int16_from(response.mag_z);
	*ret_ang_x = leconvert_int16_from(response.ang_x);
	*ret_ang_y = leconvert_int16_from(response.ang_y);
	*ret_ang_z = leconvert_int16_from(response.ang_z);
	*ret_temperature = leconvert_int16_from(response.temperature);

	return ret;
}

int imu_get_orientation(IMU *imu, int16_t *ret_roll, int16_t *ret_pitch, int16_t *ret_yaw) {
	DevicePrivate *device_p = imu->p;
	GetOrientation_Request request;
	GetOrientation_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ORIENTATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_roll = leconvert_int16_from(response.roll);
	*ret_pitch = leconvert_int16_from(response.pitch);
	*ret_yaw = leconvert_int16_from(response.yaw);

	return ret;
}

int imu_get_quaternion(IMU *imu, float *ret_x, float *ret_y, float *ret_z, float *ret_w) {
	DevicePrivate *device_p = imu->p;
	GetQuaternion_Request request;
	GetQuaternion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_QUATERNION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_x = leconvert_float_from(response.x);
	*ret_y = leconvert_float_from(response.y);
	*ret_z = leconvert_float_from(response.z);
	*ret_w = leconvert_float_from(response.w);

	return ret;
}

int imu_get_imu_temperature(IMU *imu, int16_t *ret_temperature) {
	DevicePrivate *device_p = imu->p;
	GetIMUTemperature_Request request;
	GetIMUTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_IMU_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int16_from(response.temperature);

	return ret;
}

int imu_leds_on(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	LedsOn_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_LEDS_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_leds_off(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	LedsOff_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_LEDS_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_are_leds_on(IMU *imu, bool *ret_leds) {
	DevicePrivate *device_p = imu->p;
	AreLedsOn_Request request;
	AreLedsOn_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_ARE_LEDS_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_leds = response.leds != 0;

	return ret;
}

int imu_set_acceleration_range(IMU *imu, uint8_t range) {
	DevicePrivate *device_p = imu->p;
	SetAccelerationRange_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_ACCELERATION_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.range = range;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_acceleration_range(IMU *imu, uint8_t *ret_range) {
	DevicePrivate *device_p = imu->p;
	GetAccelerationRange_Request request;
	GetAccelerationRange_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ACCELERATION_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_range = response.range;

	return ret;
}

int imu_set_magnetometer_range(IMU *imu, uint8_t range) {
	DevicePrivate *device_p = imu->p;
	SetMagnetometerRange_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_MAGNETOMETER_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.range = range;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_magnetometer_range(IMU *imu, uint8_t *ret_range) {
	DevicePrivate *device_p = imu->p;
	GetMagnetometerRange_Request request;
	GetMagnetometerRange_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_MAGNETOMETER_RANGE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_range = response.range;

	return ret;
}

int imu_set_convergence_speed(IMU *imu, uint16_t speed) {
	DevicePrivate *device_p = imu->p;
	SetConvergenceSpeed_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_CONVERGENCE_SPEED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.speed = leconvert_uint16_to(speed);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_convergence_speed(IMU *imu, uint16_t *ret_speed) {
	DevicePrivate *device_p = imu->p;
	GetConvergenceSpeed_Request request;
	GetConvergenceSpeed_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_CONVERGENCE_SPEED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_speed = leconvert_uint16_from(response.speed);

	return ret;
}

int imu_set_calibration(IMU *imu, uint8_t typ, int16_t data[10]) {
	DevicePrivate *device_p = imu->p;
	SetCalibration_Request request;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.typ = typ;
	for (i = 0; i < 10; i++) request.data[i] = leconvert_int16_to(data[i]);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_calibration(IMU *imu, uint8_t typ, int16_t ret_data[10]) {
	DevicePrivate *device_p = imu->p;
	GetCalibration_Request request;
	GetCalibration_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.typ = typ;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 10; i++) ret_data[i] = leconvert_int16_from(response.data[i]);

	return ret;
}

int imu_set_acceleration_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetAccelerationPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_acceleration_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetAccelerationPeriod_Request request;
	GetAccelerationPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ACCELERATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_set_magnetic_field_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetMagneticFieldPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_MAGNETIC_FIELD_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_magnetic_field_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetMagneticFieldPeriod_Request request;
	GetMagneticFieldPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_MAGNETIC_FIELD_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_set_angular_velocity_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetAngularVelocityPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_ANGULAR_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_angular_velocity_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetAngularVelocityPeriod_Request request;
	GetAngularVelocityPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ANGULAR_VELOCITY_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_set_all_data_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetAllDataPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_ALL_DATA_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_all_data_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetAllDataPeriod_Request request;
	GetAllDataPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ALL_DATA_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_set_orientation_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetOrientationPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_ORIENTATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_orientation_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetOrientationPeriod_Request request;
	GetOrientationPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_ORIENTATION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_set_quaternion_period(IMU *imu, uint32_t period) {
	DevicePrivate *device_p = imu->p;
	SetQuaternionPeriod_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_QUATERNION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_quaternion_period(IMU *imu, uint32_t *ret_period) {
	DevicePrivate *device_p = imu->p;
	GetQuaternionPeriod_Request request;
	GetQuaternionPeriod_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_QUATERNION_PERIOD, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);

	return ret;
}

int imu_orientation_calculation_on(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	OrientationCalculationOn_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_ORIENTATION_CALCULATION_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_orientation_calculation_off(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	OrientationCalculationOff_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_ORIENTATION_CALCULATION_OFF, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_is_orientation_calculation_on(IMU *imu, bool *ret_orientation_calculation_on) {
	DevicePrivate *device_p = imu->p;
	IsOrientationCalculationOn_Request request;
	IsOrientationCalculationOn_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_IS_ORIENTATION_CALCULATION_ON, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_orientation_calculation_on = response.orientation_calculation_on != 0;

	return ret;
}

int imu_set_spitfp_baudrate_config(IMU *imu, bool enable_dynamic_baudrate, uint32_t minimum_dynamic_baudrate) {
	DevicePrivate *device_p = imu->p;
	SetSPITFPBaudrateConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.enable_dynamic_baudrate = enable_dynamic_baudrate ? 1 : 0;
	request.minimum_dynamic_baudrate = leconvert_uint32_to(minimum_dynamic_baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_spitfp_baudrate_config(IMU *imu, bool *ret_enable_dynamic_baudrate, uint32_t *ret_minimum_dynamic_baudrate) {
	DevicePrivate *device_p = imu->p;
	GetSPITFPBaudrateConfig_Request request;
	GetSPITFPBaudrateConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_SPITFP_BAUDRATE_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enable_dynamic_baudrate = response.enable_dynamic_baudrate != 0;
	*ret_minimum_dynamic_baudrate = leconvert_uint32_from(response.minimum_dynamic_baudrate);

	return ret;
}

int imu_get_send_timeout_count(IMU *imu, uint8_t communication_method, uint32_t *ret_timeout_count) {
	DevicePrivate *device_p = imu->p;
	GetSendTimeoutCount_Request request;
	GetSendTimeoutCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_SEND_TIMEOUT_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.communication_method = communication_method;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_timeout_count = leconvert_uint32_from(response.timeout_count);

	return ret;
}

int imu_set_spitfp_baudrate(IMU *imu, char bricklet_port, uint32_t baudrate) {
	DevicePrivate *device_p = imu->p;
	SetSPITFPBaudrate_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_SET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;
	request.baudrate = leconvert_uint32_to(baudrate);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_get_spitfp_baudrate(IMU *imu, char bricklet_port, uint32_t *ret_baudrate) {
	DevicePrivate *device_p = imu->p;
	GetSPITFPBaudrate_Request request;
	GetSPITFPBaudrate_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_SPITFP_BAUDRATE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_baudrate = leconvert_uint32_from(response.baudrate);

	return ret;
}

int imu_get_spitfp_error_count(IMU *imu, char bricklet_port, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = imu->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.bricklet_port = bricklet_port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_error_count_ack_checksum = leconvert_uint32_from(response.error_count_ack_checksum);
	*ret_error_count_message_checksum = leconvert_uint32_from(response.error_count_message_checksum);
	*ret_error_count_frame = leconvert_uint32_from(response.error_count_frame);
	*ret_error_count_overflow = leconvert_uint32_from(response.error_count_overflow);

	return ret;
}

int imu_enable_status_led(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	EnableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_ENABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_disable_status_led(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	DisableStatusLED_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_DISABLE_STATUS_LED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_is_status_led_enabled(IMU *imu, bool *ret_enabled) {
	DevicePrivate *device_p = imu->p;
	IsStatusLEDEnabled_Request request;
	IsStatusLEDEnabled_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_IS_STATUS_LED_ENABLED, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_enabled = response.enabled != 0;

	return ret;
}

int imu_get_protocol1_bricklet_name(IMU *imu, char port, uint8_t *ret_protocol_version, uint8_t ret_firmware_version[3], char ret_name[40]) {
	DevicePrivate *device_p = imu->p;
	GetProtocol1BrickletName_Request request;
	GetProtocol1BrickletName_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_PROTOCOL1_BRICKLET_NAME, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_protocol_version = response.protocol_version;
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	memcpy(ret_name, response.name, 40);

	return ret;
}

int imu_get_chip_temperature(IMU *imu, int16_t *ret_temperature) {
	DevicePrivate *device_p = imu->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = leconvert_int16_from(response.temperature);

	return ret;
}

int imu_reset(IMU *imu) {
	DevicePrivate *device_p = imu->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_write_bricklet_plugin(IMU *imu, char port, uint8_t offset, uint8_t chunk[32]) {
	DevicePrivate *device_p = imu->p;
	WriteBrickletPlugin_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_WRITE_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;
	memcpy(request.chunk, chunk, 32 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_read_bricklet_plugin(IMU *imu, char port, uint8_t offset, uint8_t ret_chunk[32]) {
	DevicePrivate *device_p = imu->p;
	ReadBrickletPlugin_Request request;
	ReadBrickletPlugin_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_READ_BRICKLET_PLUGIN, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.port = port;
	request.offset = offset;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_chunk, response.chunk, 32 * sizeof(uint8_t));

	return ret;
}

int imu_get_identity(IMU *imu, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = imu->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	memcpy(ret_uid, response.uid, 8);
	memcpy(ret_connected_uid, response.connected_uid, 8);
	*ret_position = response.position;
	memcpy(ret_hardware_version, response.hardware_version, 3 * sizeof(uint8_t));
	memcpy(ret_firmware_version, response.firmware_version, 3 * sizeof(uint8_t));
	*ret_device_identifier = leconvert_uint16_from(response.device_identifier);

	return ret;
}

#ifdef __cplusplus
}
#endif
