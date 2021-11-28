/*****************************************************************************
 *  Rohde&Schwarz Instrument Driver Specific Attribute callbacks include file
 *
 *  WARNING: Do not add to, delete from, or otherwise modify the contents
 *           of this include file. It is generated from DrBase repository.
 *
 *  Built on: 2016-03-22 12:47:52Z
 *****************************************************************************/

#ifndef __RSHMC8015_ATTRIBUTES_HEADER
#define __RSHMC8015_ATTRIBUTES_HEADER

#include "rsidr_core.h"

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Read Callbacks ----------------------------------------------------------*
 *****************************************************************************/
ViStatus rshmc8015_parseNAN_ReadCallback (ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 bufSize, void *value);

/*****************************************************************************
 *- Write Callbacks ---------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Check Callbacks ---------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Check Status Callbacks ---------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Coerce Callbacks --------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Range Table Callbacks ---------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- User Callbacks ----------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Range Tables ------------------------------------------------------------*
 *****************************************************************************/
extern RsRangeTable rshmc8015_rngViewMode;
extern RsRangeTable rshmc8015_rngNormalViewFunction;
extern RsRangeTable rshmc8015_rngViewNormalPageSize;
extern RsRangeTable rshmc8015_rngHarmonicsView;
extern RsRangeTable rshmc8015_rngHarmonicsSource;
extern RsRangeTable rshmc8015_rngHarmonicsNumber;
extern RsRangeTable rshmc8015_rngHarmonicsScaling;
extern RsRangeTable rshmc8015_rngHarmonicsSubset;
extern RsRangeTable rshmc8015_rngActivePage;
extern RsRangeTable rshmc8015_rngIntegratorMode;
extern RsRangeTable rshmc8015_rngIntegratorDuration;
extern RsRangeTable rshmc8015_rngLoggingMode;
extern RsRangeTable rshmc8015_rngLoggingTime;
extern RsRangeTable rshmc8015_rngLoggingCount;
extern RsRangeTable rshmc8015_rngLimitSource;
extern RsRangeTable rshmc8015_rngAcquisitionMode;
extern RsRangeTable rshmc8015_rngAcquisitionVoltageRange;
extern RsRangeTable rshmc8015_rngAcquisitionCrestFactor;
extern RsRangeTable rshmc8015_rngAcquisitionCurrentRange;
extern RsRangeTable rshmc8015_rngPLLSource;
extern RsRangeTable rshmc8015_rngImageFormat;
extern RsRangeTable rshmc8015_rngAnalogOutputMode;
extern RsRangeTable rshmc8015_rngDigitalInputMode;
extern RsRangeTable rshmc8015_rngDigitalOutputMode;
extern RsRangeTable rshmc8015_rngSensorMode;
extern RsRangeTable rshmc8015_rngShuntResistance;
extern RsRangeTable rshmc8015_rngClampRatio;
extern RsRangeTable rshmc8015_rngStatusRegisterOperation;
extern RsRangeTable rshmc8015_rngStatusRegisterQuery;
extern RsRangeTable rshmc8015_rngDevice;

/*****************************************************************************
 *- Attributes --------------------------------------------------------------*
 *****************************************************************************/
extern RsAttrProperties g_RSHMC8015_RS_ATTR_RANGE_CHECK;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_QUERY_INSTRUMENT_STATUS;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CACHE;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SIMULATE;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_RECORD_COERCIONS;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_INTERCHANGE_CHECK;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPY;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_USE_SPECIFIC_SIMULATION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_DESCRIPTION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_PREFIX;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_VENDOR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_REVISION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_PREFIX;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_LOCATOR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_VENDOR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_REVISION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_GROUP_CAPABILITIES;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_FUNCTION_CAPABILITIES;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CHANNEL_COUNT;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_DRIVER_SETUP;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_INSTRUMENT_MANUFACTURER;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_INSTRUMENT_MODEL;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_OPTIONS_LIST;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_IO_RESOURCE_DESCRIPTOR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_LOGICAL_NAME;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_PRIMARY_ERROR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SECONDARY_ERROR;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_ERROR_ELABORATION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_VISA_RM_SESSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_IO_SESSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_IO_SESSION_TYPE;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_ENGINE_MAJOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_ENGINE_MINOR_VERSION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_ENGINE_REVISION;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_OPC_CALLBACK;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_CHECK_STATUS_CALLBACK;
extern RsAttrProperties g_RSHMC8015_RS_ATTR_OPC_TIMEOUT;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_PLL_SOURCE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_DIGITAL_FILTER;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_BWL;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_CURRENT_RANGE;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_CURRENT_INVERT;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_OCP;
extern RsAttrProperties g_RSHMC8015_ATTR_ACQ_OCP_RESET;
extern RsAttrProperties g_RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_SOURCE;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_HIGH;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_LOW;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_CHECK_RESULT;
extern RsAttrProperties g_RSHMC8015_ATTR_LIMIT_PERCENT;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_AINPUT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_AOUTPUT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_AOUTPUT_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DINPUT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DINPUT_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DINPUT_INVERT;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DOUTPUT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DOUTPUT_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_DOUTPUT_INVERT;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_SENSOR_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_SENSOR_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO;
extern RsAttrProperties g_RSHMC8015_ATTR_EXT_SENSOR_RANGE;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_NORM_FUNCTION;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_HARM_SELECT;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_HARM_SOURCE;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_HARM_NUMBER;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_HARM_SCALING;
extern RsAttrProperties g_RSHMC8015_ATTR_VIEW_HARM_SUBSET;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_DURATION;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_RESET;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_START;
extern RsAttrProperties g_RSHMC8015_ATTR_INTEGRATOR_STOP;
extern RsAttrProperties g_RSHMC8015_ATTR_LOGGING_STATE;
extern RsAttrProperties g_RSHMC8015_ATTR_LOGGING_PAGE;
extern RsAttrProperties g_RSHMC8015_ATTR_LOGGING_MODE;
extern RsAttrProperties g_RSHMC8015_ATTR_LOGGING_TIME;
extern RsAttrProperties g_RSHMC8015_ATTR_LOGGING_COUNT;
extern RsAttrProperties g_RSHMC8015_ATTR_ID_QUERY_RESPONSE;
extern RsAttrProperties g_RSHMC8015_ATTR_DISPLAY_CLEAR;
extern RsAttrProperties g_RSHMC8015_ATTR_DISPLAY_TEXT;
extern RsAttrProperties g_RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT;
extern RsAttrProperties g_RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH;
extern RsAttrProperties g_RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_START_BEEP;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_NAME;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_ERROR;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_LOCAL;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_REMOTE;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_RWLOCK;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_VERSION;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_DEVICE;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_SHUTDOWN;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_SOFTWARE;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_HARDWARE;
extern RsAttrProperties g_RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER;
extern RsAttrProperties g_RSHMC8015_ATTR_STATUS_PRESET;

/*****************************************************************************
 *- Repeated Capabilities Table --------------------------------------------------------------*
 *****************************************************************************/
extern RsRepCap rshmc8015_RsRepCapTable[];

/*****************************************************************************
 *- Attributes List ---------------------------------------------------------*
 *****************************************************************************/
extern RsAttrPropertiesPtr rshmc8015_RsAttrPropertiesList[];

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __RSHMC8015_ATTRIBUTES_HEADER */
