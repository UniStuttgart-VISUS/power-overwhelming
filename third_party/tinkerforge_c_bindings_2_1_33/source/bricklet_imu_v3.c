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

#include "bricklet_imu_v3.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef void (*Acceleration_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*MagneticField_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*AngularVelocity_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*Temperature_CallbackFunction)(int8_t temperature, void *user_data);

typedef void (*LinearAcceleration_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*GravityVector_CallbackFunction)(int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*Orientation_CallbackFunction)(int16_t heading, int16_t roll, int16_t pitch, void *user_data);

typedef void (*Quaternion_CallbackFunction)(int16_t w, int16_t x, int16_t y, int16_t z, void *user_data);

typedef void (*AllData_CallbackFunction)(int16_t acceleration[3], int16_t magnetic_field[3], int16_t angular_velocity[3], int16_t euler_angle[3], int16_t quaternion[4], int16_t linear_acceleration[3], int16_t gravity_vector[3], int8_t temperature, uint8_t calibration_status, void *user_data);

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
} ATTRIBUTE_PACKED GetTemperature_Request;

typedef struct {
	PacketHeader header;
	int8_t temperature;
} ATTRIBUTE_PACKED GetTemperature_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientation_Request;

typedef struct {
	PacketHeader header;
	int16_t heading;
	int16_t roll;
	int16_t pitch;
} ATTRIBUTE_PACKED GetOrientation_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLinearAcceleration_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetLinearAcceleration_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGravityVector_Request;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetGravityVector_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternion_Request;

typedef struct {
	PacketHeader header;
	int16_t w;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GetQuaternion_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllData_Request;

typedef struct {
	PacketHeader header;
	int16_t acceleration[3];
	int16_t magnetic_field[3];
	int16_t angular_velocity[3];
	int16_t euler_angle[3];
	int16_t quaternion[4];
	int16_t linear_acceleration[3];
	int16_t gravity_vector[3];
	int8_t temperature;
	uint8_t calibration_status;
} ATTRIBUTE_PACKED GetAllData_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED SaveCalibration_Request;

typedef struct {
	PacketHeader header;
	uint8_t calibration_done;
} ATTRIBUTE_PACKED SaveCalibration_Response;

typedef struct {
	PacketHeader header;
	uint8_t magnetometer_rate;
	uint8_t gyroscope_range;
	uint8_t gyroscope_bandwidth;
	uint8_t accelerometer_range;
	uint8_t accelerometer_bandwidth;
} ATTRIBUTE_PACKED SetSensorConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint8_t magnetometer_rate;
	uint8_t gyroscope_range;
	uint8_t gyroscope_bandwidth;
	uint8_t accelerometer_range;
	uint8_t accelerometer_bandwidth;
} ATTRIBUTE_PACKED GetSensorConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED SetSensorFusionMode_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetSensorFusionMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetSensorFusionMode_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAccelerationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetMagneticFieldCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetMagneticFieldCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetMagneticFieldCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAngularVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAngularVelocityCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAngularVelocityCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetTemperatureCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetOrientationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetOrientationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetOrientationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetLinearAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetLinearAccelerationCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetLinearAccelerationCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetGravityVectorCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetGravityVectorCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetGravityVectorCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetQuaternionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetQuaternionCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetQuaternionCallbackConfiguration_Response;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED SetAllDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetAllDataCallbackConfiguration_Request;

typedef struct {
	PacketHeader header;
	uint32_t period;
	uint8_t value_has_to_change;
} ATTRIBUTE_PACKED GetAllDataCallbackConfiguration_Response;

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
	int8_t temperature;
} ATTRIBUTE_PACKED Temperature_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED LinearAcceleration_Callback;

typedef struct {
	PacketHeader header;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED GravityVector_Callback;

typedef struct {
	PacketHeader header;
	int16_t heading;
	int16_t roll;
	int16_t pitch;
} ATTRIBUTE_PACKED Orientation_Callback;

typedef struct {
	PacketHeader header;
	int16_t w;
	int16_t x;
	int16_t y;
	int16_t z;
} ATTRIBUTE_PACKED Quaternion_Callback;

typedef struct {
	PacketHeader header;
	int16_t acceleration[3];
	int16_t magnetic_field[3];
	int16_t angular_velocity[3];
	int16_t euler_angle[3];
	int16_t quaternion[4];
	int16_t linear_acceleration[3];
	int16_t gravity_vector[3];
	int8_t temperature;
	uint8_t calibration_status;
} ATTRIBUTE_PACKED AllData_Callback;

typedef struct {
	PacketHeader header;
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
	uint8_t mode;
} ATTRIBUTE_PACKED SetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED SetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetBootloaderMode_Request;

typedef struct {
	PacketHeader header;
	uint8_t mode;
} ATTRIBUTE_PACKED GetBootloaderMode_Response;

typedef struct {
	PacketHeader header;
	uint32_t pointer;
} ATTRIBUTE_PACKED SetWriteFirmwarePointer_Request;

typedef struct {
	PacketHeader header;
	uint8_t data[64];
} ATTRIBUTE_PACKED WriteFirmware_Request;

typedef struct {
	PacketHeader header;
	uint8_t status;
} ATTRIBUTE_PACKED WriteFirmware_Response;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED SetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Request;

typedef struct {
	PacketHeader header;
	uint8_t config;
} ATTRIBUTE_PACKED GetStatusLEDConfig_Response;

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
	uint32_t uid;
} ATTRIBUTE_PACKED WriteUID_Request;

typedef struct {
	PacketHeader header;
} ATTRIBUTE_PACKED ReadUID_Request;

typedef struct {
	PacketHeader header;
	uint32_t uid;
} ATTRIBUTE_PACKED ReadUID_Response;

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

static void imu_v3_callback_wrapper_acceleration(DevicePrivate *device_p, Packet *packet) {
	Acceleration_CallbackFunction callback_function;
	void *user_data;
	Acceleration_Callback *callback;

	if (packet->header.length != sizeof(Acceleration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Acceleration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ACCELERATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ACCELERATION];
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

static void imu_v3_callback_wrapper_magnetic_field(DevicePrivate *device_p, Packet *packet) {
	MagneticField_CallbackFunction callback_function;
	void *user_data;
	MagneticField_Callback *callback;

	if (packet->header.length != sizeof(MagneticField_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (MagneticField_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_MAGNETIC_FIELD];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_MAGNETIC_FIELD];
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

static void imu_v3_callback_wrapper_angular_velocity(DevicePrivate *device_p, Packet *packet) {
	AngularVelocity_CallbackFunction callback_function;
	void *user_data;
	AngularVelocity_Callback *callback;

	if (packet->header.length != sizeof(AngularVelocity_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AngularVelocity_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ANGULAR_VELOCITY];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ANGULAR_VELOCITY];
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

static void imu_v3_callback_wrapper_temperature(DevicePrivate *device_p, Packet *packet) {
	Temperature_CallbackFunction callback_function;
	void *user_data;
	Temperature_Callback *callback;

	if (packet->header.length != sizeof(Temperature_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Temperature_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_TEMPERATURE];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_TEMPERATURE];
	callback = (Temperature_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback_function(callback->temperature, user_data);
}

static void imu_v3_callback_wrapper_linear_acceleration(DevicePrivate *device_p, Packet *packet) {
	LinearAcceleration_CallbackFunction callback_function;
	void *user_data;
	LinearAcceleration_Callback *callback;

	if (packet->header.length != sizeof(LinearAcceleration_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (LinearAcceleration_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_LINEAR_ACCELERATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_LINEAR_ACCELERATION];
	callback = (LinearAcceleration_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v3_callback_wrapper_gravity_vector(DevicePrivate *device_p, Packet *packet) {
	GravityVector_CallbackFunction callback_function;
	void *user_data;
	GravityVector_Callback *callback;

	if (packet->header.length != sizeof(GravityVector_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (GravityVector_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_GRAVITY_VECTOR];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_GRAVITY_VECTOR];
	callback = (GravityVector_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->x, callback->y, callback->z, user_data);
}

static void imu_v3_callback_wrapper_orientation(DevicePrivate *device_p, Packet *packet) {
	Orientation_CallbackFunction callback_function;
	void *user_data;
	Orientation_Callback *callback;

	if (packet->header.length != sizeof(Orientation_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Orientation_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ORIENTATION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ORIENTATION];
	callback = (Orientation_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->heading = leconvert_int16_from(callback->heading);
	callback->roll = leconvert_int16_from(callback->roll);
	callback->pitch = leconvert_int16_from(callback->pitch);

	callback_function(callback->heading, callback->roll, callback->pitch, user_data);
}

static void imu_v3_callback_wrapper_quaternion(DevicePrivate *device_p, Packet *packet) {
	Quaternion_CallbackFunction callback_function;
	void *user_data;
	Quaternion_Callback *callback;

	if (packet->header.length != sizeof(Quaternion_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (Quaternion_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_QUATERNION];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_QUATERNION];
	callback = (Quaternion_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	callback->w = leconvert_int16_from(callback->w);
	callback->x = leconvert_int16_from(callback->x);
	callback->y = leconvert_int16_from(callback->y);
	callback->z = leconvert_int16_from(callback->z);

	callback_function(callback->w, callback->x, callback->y, callback->z, user_data);
}

static void imu_v3_callback_wrapper_all_data(DevicePrivate *device_p, Packet *packet) {
	AllData_CallbackFunction callback_function;
	void *user_data;
	AllData_Callback *callback;
	int i;
	int16_t aligned_acceleration[3];
	int16_t aligned_magnetic_field[3];
	int16_t aligned_angular_velocity[3];
	int16_t aligned_euler_angle[3];
	int16_t aligned_quaternion[4];
	int16_t aligned_linear_acceleration[3];
	int16_t aligned_gravity_vector[3];


	if (packet->header.length != sizeof(AllData_Callback)) {
		return; // silently ignoring callback with wrong length
	}

	callback_function = (AllData_CallbackFunction)device_p->registered_callbacks[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ALL_DATA];
	user_data = device_p->registered_callback_user_data[DEVICE_NUM_FUNCTION_IDS + IMU_V3_CALLBACK_ALL_DATA];
	callback = (AllData_Callback *)packet;
	(void)callback; // avoid unused variable warning

	if (callback_function == NULL) {
		return;
	}

	for (i = 0; i < 3; i++) aligned_acceleration[i] = leconvert_int16_from(callback->acceleration[i]);
	for (i = 0; i < 3; i++) aligned_magnetic_field[i] = leconvert_int16_from(callback->magnetic_field[i]);
	for (i = 0; i < 3; i++) aligned_angular_velocity[i] = leconvert_int16_from(callback->angular_velocity[i]);
	for (i = 0; i < 3; i++) aligned_euler_angle[i] = leconvert_int16_from(callback->euler_angle[i]);
	for (i = 0; i < 4; i++) aligned_quaternion[i] = leconvert_int16_from(callback->quaternion[i]);
	for (i = 0; i < 3; i++) aligned_linear_acceleration[i] = leconvert_int16_from(callback->linear_acceleration[i]);
	for (i = 0; i < 3; i++) aligned_gravity_vector[i] = leconvert_int16_from(callback->gravity_vector[i]);

	callback_function(aligned_acceleration, aligned_magnetic_field, aligned_angular_velocity, aligned_euler_angle, aligned_quaternion, aligned_linear_acceleration, aligned_gravity_vector, callback->temperature, callback->calibration_status, user_data);
}

void imu_v3_create(IMUV3 *imu_v3, const char *uid, IPConnection *ipcon) {
	IPConnectionPrivate *ipcon_p = ipcon->p;
	DevicePrivate *device_p;

	device_create(imu_v3, uid, ipcon_p, 2, 0, 0, IMU_V3_DEVICE_IDENTIFIER);

	device_p = imu_v3->p;

	device_p->response_expected[IMU_V3_FUNCTION_GET_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_MAGNETIC_FIELD] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ANGULAR_VELOCITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ORIENTATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_LINEAR_ACCELERATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_GRAVITY_VECTOR] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_QUATERNION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ALL_DATA] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SAVE_CALIBRATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_SENSOR_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_SENSOR_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_SENSOR_FUSION_MODE] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_SENSOR_FUSION_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_MAGNETIC_FIELD_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_MAGNETIC_FIELD_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_ANGULAR_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ANGULAR_VELOCITY_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_ORIENTATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ORIENTATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_LINEAR_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_LINEAR_ACCELERATION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_GRAVITY_VECTOR_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_GRAVITY_VECTOR_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_QUATERNION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_QUATERNION_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_ALL_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_ALL_DATA_CALLBACK_CONFIGURATION] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_SPITFP_ERROR_COUNT] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_BOOTLOADER_MODE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_WRITE_FIRMWARE_POINTER] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_WRITE_FIRMWARE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_SET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_STATUS_LED_CONFIG] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_CHIP_TEMPERATURE] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_RESET] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_WRITE_UID] = DEVICE_RESPONSE_EXPECTED_FALSE;
	device_p->response_expected[IMU_V3_FUNCTION_READ_UID] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;
	device_p->response_expected[IMU_V3_FUNCTION_GET_IDENTITY] = DEVICE_RESPONSE_EXPECTED_ALWAYS_TRUE;

	device_p->callback_wrappers[IMU_V3_CALLBACK_ACCELERATION] = imu_v3_callback_wrapper_acceleration;
	device_p->callback_wrappers[IMU_V3_CALLBACK_MAGNETIC_FIELD] = imu_v3_callback_wrapper_magnetic_field;
	device_p->callback_wrappers[IMU_V3_CALLBACK_ANGULAR_VELOCITY] = imu_v3_callback_wrapper_angular_velocity;
	device_p->callback_wrappers[IMU_V3_CALLBACK_TEMPERATURE] = imu_v3_callback_wrapper_temperature;
	device_p->callback_wrappers[IMU_V3_CALLBACK_LINEAR_ACCELERATION] = imu_v3_callback_wrapper_linear_acceleration;
	device_p->callback_wrappers[IMU_V3_CALLBACK_GRAVITY_VECTOR] = imu_v3_callback_wrapper_gravity_vector;
	device_p->callback_wrappers[IMU_V3_CALLBACK_ORIENTATION] = imu_v3_callback_wrapper_orientation;
	device_p->callback_wrappers[IMU_V3_CALLBACK_QUATERNION] = imu_v3_callback_wrapper_quaternion;
	device_p->callback_wrappers[IMU_V3_CALLBACK_ALL_DATA] = imu_v3_callback_wrapper_all_data;

	ipcon_add_device(ipcon_p, device_p);
}

void imu_v3_destroy(IMUV3 *imu_v3) {
	device_release(imu_v3->p);
}

int imu_v3_get_response_expected(IMUV3 *imu_v3, uint8_t function_id, bool *ret_response_expected) {
	return device_get_response_expected(imu_v3->p, function_id, ret_response_expected);
}

int imu_v3_set_response_expected(IMUV3 *imu_v3, uint8_t function_id, bool response_expected) {
	return device_set_response_expected(imu_v3->p, function_id, response_expected);
}

int imu_v3_set_response_expected_all(IMUV3 *imu_v3, bool response_expected) {
	return device_set_response_expected_all(imu_v3->p, response_expected);
}

void imu_v3_register_callback(IMUV3 *imu_v3, int16_t callback_id, void (*function)(void), void *user_data) {
	device_register_callback(imu_v3->p, callback_id, function, user_data);
}

int imu_v3_get_api_version(IMUV3 *imu_v3, uint8_t ret_api_version[3]) {
	return device_get_api_version(imu_v3->p, ret_api_version);
}

int imu_v3_get_acceleration(IMUV3 *imu_v3, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetAcceleration_Request request;
	GetAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ACCELERATION, device_p->ipcon_p, device_p);

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

int imu_v3_get_magnetic_field(IMUV3 *imu_v3, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetMagneticField_Request request;
	GetMagneticField_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_MAGNETIC_FIELD, device_p->ipcon_p, device_p);

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

int imu_v3_get_angular_velocity(IMUV3 *imu_v3, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetAngularVelocity_Request request;
	GetAngularVelocity_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ANGULAR_VELOCITY, device_p->ipcon_p, device_p);

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

int imu_v3_get_temperature(IMUV3 *imu_v3, int8_t *ret_temperature) {
	DevicePrivate *device_p = imu_v3->p;
	GetTemperature_Request request;
	GetTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_TEMPERATURE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_temperature = response.temperature;

	return ret;
}

int imu_v3_get_orientation(IMUV3 *imu_v3, int16_t *ret_heading, int16_t *ret_roll, int16_t *ret_pitch) {
	DevicePrivate *device_p = imu_v3->p;
	GetOrientation_Request request;
	GetOrientation_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ORIENTATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_heading = leconvert_int16_from(response.heading);
	*ret_roll = leconvert_int16_from(response.roll);
	*ret_pitch = leconvert_int16_from(response.pitch);

	return ret;
}

int imu_v3_get_linear_acceleration(IMUV3 *imu_v3, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetLinearAcceleration_Request request;
	GetLinearAcceleration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_LINEAR_ACCELERATION, device_p->ipcon_p, device_p);

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

int imu_v3_get_gravity_vector(IMUV3 *imu_v3, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetGravityVector_Request request;
	GetGravityVector_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_GRAVITY_VECTOR, device_p->ipcon_p, device_p);

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

int imu_v3_get_quaternion(IMUV3 *imu_v3, int16_t *ret_w, int16_t *ret_x, int16_t *ret_y, int16_t *ret_z) {
	DevicePrivate *device_p = imu_v3->p;
	GetQuaternion_Request request;
	GetQuaternion_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_QUATERNION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_w = leconvert_int16_from(response.w);
	*ret_x = leconvert_int16_from(response.x);
	*ret_y = leconvert_int16_from(response.y);
	*ret_z = leconvert_int16_from(response.z);

	return ret;
}

int imu_v3_get_all_data(IMUV3 *imu_v3, int16_t ret_acceleration[3], int16_t ret_magnetic_field[3], int16_t ret_angular_velocity[3], int16_t ret_euler_angle[3], int16_t ret_quaternion[4], int16_t ret_linear_acceleration[3], int16_t ret_gravity_vector[3], int8_t *ret_temperature, uint8_t *ret_calibration_status) {
	DevicePrivate *device_p = imu_v3->p;
	GetAllData_Request request;
	GetAllData_Response response;
	int ret;
	int i;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ALL_DATA, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	for (i = 0; i < 3; i++) ret_acceleration[i] = leconvert_int16_from(response.acceleration[i]);
	for (i = 0; i < 3; i++) ret_magnetic_field[i] = leconvert_int16_from(response.magnetic_field[i]);
	for (i = 0; i < 3; i++) ret_angular_velocity[i] = leconvert_int16_from(response.angular_velocity[i]);
	for (i = 0; i < 3; i++) ret_euler_angle[i] = leconvert_int16_from(response.euler_angle[i]);
	for (i = 0; i < 4; i++) ret_quaternion[i] = leconvert_int16_from(response.quaternion[i]);
	for (i = 0; i < 3; i++) ret_linear_acceleration[i] = leconvert_int16_from(response.linear_acceleration[i]);
	for (i = 0; i < 3; i++) ret_gravity_vector[i] = leconvert_int16_from(response.gravity_vector[i]);
	*ret_temperature = response.temperature;
	*ret_calibration_status = response.calibration_status;

	return ret;
}

int imu_v3_save_calibration(IMUV3 *imu_v3, bool *ret_calibration_done) {
	DevicePrivate *device_p = imu_v3->p;
	SaveCalibration_Request request;
	SaveCalibration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SAVE_CALIBRATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_calibration_done = response.calibration_done != 0;

	return ret;
}

int imu_v3_set_sensor_configuration(IMUV3 *imu_v3, uint8_t magnetometer_rate, uint8_t gyroscope_range, uint8_t gyroscope_bandwidth, uint8_t accelerometer_range, uint8_t accelerometer_bandwidth) {
	DevicePrivate *device_p = imu_v3->p;
	SetSensorConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_SENSOR_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.magnetometer_rate = magnetometer_rate;
	request.gyroscope_range = gyroscope_range;
	request.gyroscope_bandwidth = gyroscope_bandwidth;
	request.accelerometer_range = accelerometer_range;
	request.accelerometer_bandwidth = accelerometer_bandwidth;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_sensor_configuration(IMUV3 *imu_v3, uint8_t *ret_magnetometer_rate, uint8_t *ret_gyroscope_range, uint8_t *ret_gyroscope_bandwidth, uint8_t *ret_accelerometer_range, uint8_t *ret_accelerometer_bandwidth) {
	DevicePrivate *device_p = imu_v3->p;
	GetSensorConfiguration_Request request;
	GetSensorConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_SENSOR_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_magnetometer_rate = response.magnetometer_rate;
	*ret_gyroscope_range = response.gyroscope_range;
	*ret_gyroscope_bandwidth = response.gyroscope_bandwidth;
	*ret_accelerometer_range = response.accelerometer_range;
	*ret_accelerometer_bandwidth = response.accelerometer_bandwidth;

	return ret;
}

int imu_v3_set_sensor_fusion_mode(IMUV3 *imu_v3, uint8_t mode) {
	DevicePrivate *device_p = imu_v3->p;
	SetSensorFusionMode_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_SENSOR_FUSION_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_sensor_fusion_mode(IMUV3 *imu_v3, uint8_t *ret_mode) {
	DevicePrivate *device_p = imu_v3->p;
	GetSensorFusionMode_Request request;
	GetSensorFusionMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_SENSOR_FUSION_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_mode = response.mode;

	return ret;
}

int imu_v3_set_acceleration_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetAccelerationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_acceleration_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetAccelerationCallbackConfiguration_Request request;
	GetAccelerationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_magnetic_field_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetMagneticFieldCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_MAGNETIC_FIELD_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_magnetic_field_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetMagneticFieldCallbackConfiguration_Request request;
	GetMagneticFieldCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_MAGNETIC_FIELD_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_angular_velocity_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetAngularVelocityCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_ANGULAR_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_angular_velocity_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetAngularVelocityCallbackConfiguration_Request request;
	GetAngularVelocityCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ANGULAR_VELOCITY_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_temperature_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetTemperatureCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_temperature_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetTemperatureCallbackConfiguration_Request request;
	GetTemperatureCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_TEMPERATURE_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_orientation_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetOrientationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_ORIENTATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_orientation_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetOrientationCallbackConfiguration_Request request;
	GetOrientationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ORIENTATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_linear_acceleration_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetLinearAccelerationCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_LINEAR_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_linear_acceleration_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetLinearAccelerationCallbackConfiguration_Request request;
	GetLinearAccelerationCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_LINEAR_ACCELERATION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_gravity_vector_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetGravityVectorCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_GRAVITY_VECTOR_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_gravity_vector_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetGravityVectorCallbackConfiguration_Request request;
	GetGravityVectorCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_GRAVITY_VECTOR_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_quaternion_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetQuaternionCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_QUATERNION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_quaternion_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetQuaternionCallbackConfiguration_Request request;
	GetQuaternionCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_QUATERNION_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_set_all_data_callback_configuration(IMUV3 *imu_v3, uint32_t period, bool value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	SetAllDataCallbackConfiguration_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_ALL_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.period = leconvert_uint32_to(period);
	request.value_has_to_change = value_has_to_change ? 1 : 0;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_all_data_callback_configuration(IMUV3 *imu_v3, uint32_t *ret_period, bool *ret_value_has_to_change) {
	DevicePrivate *device_p = imu_v3->p;
	GetAllDataCallbackConfiguration_Request request;
	GetAllDataCallbackConfiguration_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_ALL_DATA_CALLBACK_CONFIGURATION, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_period = leconvert_uint32_from(response.period);
	*ret_value_has_to_change = response.value_has_to_change != 0;

	return ret;
}

int imu_v3_get_spitfp_error_count(IMUV3 *imu_v3, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
	DevicePrivate *device_p = imu_v3->p;
	GetSPITFPErrorCount_Request request;
	GetSPITFPErrorCount_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_SPITFP_ERROR_COUNT, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

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

int imu_v3_set_bootloader_mode(IMUV3 *imu_v3, uint8_t mode, uint8_t *ret_status) {
	DevicePrivate *device_p = imu_v3->p;
	SetBootloaderMode_Request request;
	SetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.mode = mode;

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int imu_v3_get_bootloader_mode(IMUV3 *imu_v3, uint8_t *ret_mode) {
	DevicePrivate *device_p = imu_v3->p;
	GetBootloaderMode_Request request;
	GetBootloaderMode_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_BOOTLOADER_MODE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_mode = response.mode;

	return ret;
}

int imu_v3_set_write_firmware_pointer(IMUV3 *imu_v3, uint32_t pointer) {
	DevicePrivate *device_p = imu_v3->p;
	SetWriteFirmwarePointer_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_WRITE_FIRMWARE_POINTER, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.pointer = leconvert_uint32_to(pointer);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_write_firmware(IMUV3 *imu_v3, uint8_t data[64], uint8_t *ret_status) {
	DevicePrivate *device_p = imu_v3->p;
	WriteFirmware_Request request;
	WriteFirmware_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_WRITE_FIRMWARE, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	memcpy(request.data, data, 64 * sizeof(uint8_t));

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_status = response.status;

	return ret;
}

int imu_v3_set_status_led_config(IMUV3 *imu_v3, uint8_t config) {
	DevicePrivate *device_p = imu_v3->p;
	SetStatusLEDConfig_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_SET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.config = config;

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_get_status_led_config(IMUV3 *imu_v3, uint8_t *ret_config) {
	DevicePrivate *device_p = imu_v3->p;
	GetStatusLEDConfig_Request request;
	GetStatusLEDConfig_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_STATUS_LED_CONFIG, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_config = response.config;

	return ret;
}

int imu_v3_get_chip_temperature(IMUV3 *imu_v3, int16_t *ret_temperature) {
	DevicePrivate *device_p = imu_v3->p;
	GetChipTemperature_Request request;
	GetChipTemperature_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_CHIP_TEMPERATURE, device_p->ipcon_p, device_p);

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

int imu_v3_reset(IMUV3 *imu_v3) {
	DevicePrivate *device_p = imu_v3->p;
	Reset_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_RESET, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_write_uid(IMUV3 *imu_v3, uint32_t uid) {
	DevicePrivate *device_p = imu_v3->p;
	WriteUID_Request request;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_WRITE_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	request.uid = leconvert_uint32_to(uid);

	ret = device_send_request(device_p, (Packet *)&request, NULL, 0);

	return ret;
}

int imu_v3_read_uid(IMUV3 *imu_v3, uint32_t *ret_uid) {
	DevicePrivate *device_p = imu_v3->p;
	ReadUID_Request request;
	ReadUID_Response response;
	int ret;

	ret = device_check_validity(device_p);

	if (ret < 0) {
		return ret;
	}

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_READ_UID, device_p->ipcon_p, device_p);

	if (ret < 0) {
		return ret;
	}

	ret = device_send_request(device_p, (Packet *)&request, (Packet *)&response, sizeof(response));

	if (ret < 0) {
		return ret;
	}

	*ret_uid = leconvert_uint32_from(response.uid);

	return ret;
}

int imu_v3_get_identity(IMUV3 *imu_v3, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
	DevicePrivate *device_p = imu_v3->p;
	GetIdentity_Request request;
	GetIdentity_Response response;
	int ret;

	ret = packet_header_create(&request.header, sizeof(request), IMU_V3_FUNCTION_GET_IDENTITY, device_p->ipcon_p, device_p);

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
