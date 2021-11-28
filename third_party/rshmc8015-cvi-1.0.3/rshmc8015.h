/****************************************************************************
 *
 *  Rohde & Schwarz HMC 8015 Power Analyzer Driver
 *
 ****************************************************************************/

#ifndef __RSHMC8015_HEADER
#define __RSHMC8015_HEADER

#include "rsidr_core.h"
#include "rshmc8015_attributes.h"
#include "rshmc8015_utility.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Useful Macros & Constants -----------------------------------------------*
 *****************************************************************************/
#define RSHMC8015_SIMULATION_ID_QUERY      "Rohde&Schwarz,HMC8015,012345678,00.011"  /* Default definition of ID Query Response for simulation */
#define RSHMC8015_VALID_ID_RESPONSE_STRING "Rohde&Schwarz"      /* Valid response for identification query */
#define RSHMC8015_SIMULATION_OPT_QUERY     ""      /* Simulated response for *OPT? command */

#define RSHMC8015_IO_BUFFER_SIZE           1024L   /* I/O buffer size */
#define RSHMC8015_OPC_TIMEOUT              5000L   /* Maximum time to wait for OPC in milliseconds */
#define IEEE_488_2_ERROR_MASK              0x4    /* 488.2 STB Bits */   
#define IEEE_488_2_ESE_MASK                0x3D   /* 488.2 Event Status Register (ESE) Bits */
#define IEEE_488_2_SRE_MASK                0x24   /* 488.2 Event Status Register (ESR) Bits */
#define RSHMC8015_NAN                 9.91e+37
#define RSHMC8015_NAN_VI_INT32             0x80000000
#define RSHMC8015_NAN_VI_INT64             0x8000000000000000     
/****************************************************************************
 *----------------- Instrument Driver Revision Information -----------------*
 ****************************************************************************/

/* Class Driver Identification */

#define RSHMC8015_CLASS_DRIVER_DESCRIPTION           ""
#define RSHMC8015_CLASS_DRIVER_PREFIX                ""
#define RSHMC8015_CLASS_DRIVER_VENDOR                ""
#define RSHMC8015_CLASS_DRIVER_REVISION              ""
#define RSHMC8015_CLASS_SPEC_MAJOR_VERSION           1L    /* Class specification major version */
#define RSHMC8015_CLASS_SPEC_MINOR_VERSION           0L    /* Class specification minor version */

/* Driver Identification */

#define RSHMC8015_SPECIFIC_DRIVER_DESCRIPTION        ""
#define RSHMC8015_SPECIFIC_DRIVER_PREFIX             "RSHMC8015"
#define RSHMC8015_SPECIFIC_DRIVER_LOCATOR            ""
#define RSHMC8015_SPECIFIC_DRIVER_VENDOR             ""
#define RSHMC8015_MAJOR_VERSION                      1L    /* Instrument driver major version          */
#define RSHMC8015_MINOR_VERSION                      0L    /* Instrument driver minor version          */
#define RSHMC8015_MINOR_MINOR_VERSION                3L    /* Instrument driver minor minor version    */

/* Driver Capabilities */          

#define RSHMC8015_SUPPORTED_INSTRUMENT_MODELS        ""    /* Instrument driver supported model(s)     */
#define RSHMC8015_GROUP_CAPABILITIES                 ""
#define RSHMC8015_FUNCTION_CAPABILITIES              ""

/****************************************************************************
 *---------------------------- Attribute Defines ---------------------------*
 ****************************************************************************/

    /*- Inherent Instrument Specific Attributes ----------------------------*/

        /* User Options */

#define RSHMC8015_ATTR_RANGE_CHECK                                           RS_ATTR_RANGE_CHECK                                     /* ViBoolean */
#define RSHMC8015_ATTR_QUERY_INSTRUMENT_STATUS                               RS_ATTR_QUERY_INSTRUMENT_STATUS                         /* ViBoolean */
#define RSHMC8015_ATTR_CACHE                                                 RS_ATTR_CACHE                                           /* ViBoolean */
#define RSHMC8015_ATTR_SIMULATE                                              RS_ATTR_SIMULATE                                        /* ViBoolean */
#define RSHMC8015_ATTR_RECORD_COERCIONS                                      RS_ATTR_RECORD_COERCIONS                                /* ViBoolean */
#define RSHMC8015_ATTR_INTERCHANGE_CHECK                                     RS_ATTR_INTERCHANGE_CHECK                               /* ViBoolean */
#define RSHMC8015_ATTR_SPY                                                   RS_ATTR_SPY                                             /* ViBoolean */
#define RSHMC8015_ATTR_USE_SPECIFIC_SIMULATION                               RS_ATTR_USE_SPECIFIC_SIMULATION                         /* ViBoolean */

        /* Class Driver Identification */

#define RSHMC8015_ATTR_CLASS_DRIVER_DESCRIPTION                              RS_ATTR_CLASS_DRIVER_DESCRIPTION                        /* ViString, read-only */
#define RSHMC8015_ATTR_CLASS_DRIVER_PREFIX                                   RS_ATTR_CLASS_DRIVER_PREFIX                             /* ViString, read-only */
#define RSHMC8015_ATTR_CLASS_DRIVER_VENDOR                                   RS_ATTR_CLASS_DRIVER_VENDOR                             /* ViString, read-only */
#define RSHMC8015_ATTR_CLASS_DRIVER_REVISION                                 RS_ATTR_CLASS_DRIVER_REVISION                           /* ViString, read-only */
#define RSHMC8015_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION           /* ViInt32,  read-only */
#define RSHMC8015_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION           /* ViInt32,  read-only */

        /* Driver Identification */

#define RSHMC8015_ATTR_SPECIFIC_DRIVER_DESCRIPTION                           RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION                     /* ViString, read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_PREFIX                                RS_ATTR_SPECIFIC_DRIVER_PREFIX                          /* ViString, read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_LOCATOR                               RS_ATTR_SPECIFIC_DRIVER_LOCATOR                         /* ViString, read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_VENDOR                                RS_ATTR_SPECIFIC_DRIVER_VENDOR                          /* ViString, read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_REVISION                              RS_ATTR_SPECIFIC_DRIVER_REVISION                        /* ViString, read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION        /* ViInt32,  read-only */
#define RSHMC8015_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION        /* ViInt32,  read-only */

        /* Driver Capabilities */

#define RSHMC8015_ATTR_SUPPORTED_INSTRUMENT_MODELS                           RS_ATTR_SUPPORTED_INSTRUMENT_MODELS                     /* ViString, read-only */
#define RSHMC8015_ATTR_GROUP_CAPABILITIES                                    RS_ATTR_GROUP_CAPABILITIES                              /* ViString, read-only */
#define RSHMC8015_ATTR_FUNCTION_CAPABILITIES                                 RS_ATTR_FUNCTION_CAPABILITIES                           /* ViString, read-only */
#define RSHMC8015_ATTR_CHANNEL_COUNT                                         RS_ATTR_CHANNEL_COUNT                                   /* ViInt32,  read-only */

        /* Driver Setup */

#define RSHMC8015_ATTR_DRIVER_SETUP                                          RS_ATTR_DRIVER_SETUP                                    /* ViString            */

        /* Instrument Identification */

#define RSHMC8015_ATTR_INSTRUMENT_MANUFACTURER                               RS_ATTR_INSTRUMENT_MANUFACTURER                         /* ViString, read-only */
#define RSHMC8015_ATTR_INSTRUMENT_MODEL                                      RS_ATTR_INSTRUMENT_MODEL                                /* ViString, read-only */
#define RSHMC8015_ATTR_INSTRUMENT_FIRMWARE_REVISION                          RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                    /* ViString, read-only */

        /* Advanced Session Information */

#define RSHMC8015_ATTR_IO_RESOURCE_DESCRIPTOR                                RS_ATTR_IO_RESOURCE_DESCRIPTOR                          /* ViString, read-only */
#define RSHMC8015_ATTR_LOGICAL_NAME                                          RS_ATTR_LOGICAL_NAME

/* ViString, read-only */

    /*- Instrument-Specific Attributes -------------------------------------*/

//#define RSHMC8015_ATTR_ID_QUERY_RESPONSE                                     (RS_SPECIFIC_PUBLIC_ATTR_BASE + 1L)                     /* ViString (Read Only)              */

/* BEGIN GENERATE */
#define RSHMC8015_ATTR_ACQ_MODE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 327954
#define RSHMC8015_ATTR_ACQ_PLL_SOURCE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 327955
#define RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 327956
#define RSHMC8015_ATTR_ACQ_DIGITAL_FILTER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 327957
#define RSHMC8015_ATTR_ACQ_BWL                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 327958
#define RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 327959
#define RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 327960
#define RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 327961
#define RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 327962
#define RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 327963
#define RSHMC8015_ATTR_ACQ_CURRENT_RANGE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 327964
#define RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 327965
#define RSHMC8015_ATTR_ACQ_CURRENT_INVERT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 327966
#define RSHMC8015_ATTR_ACQ_OCP                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 327967
#define RSHMC8015_ATTR_ACQ_OCP_RESET                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 327968
#define RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 327998
#define RSHMC8015_ATTR_LIMIT_STATE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 328000
#define RSHMC8015_ATTR_LIMIT_SOURCE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 328001
#define RSHMC8015_ATTR_LIMIT_HIGH                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 328002
#define RSHMC8015_ATTR_LIMIT_LOW                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 328003
#define RSHMC8015_ATTR_LIMIT_CHECK_RESULT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 328004
#define RSHMC8015_ATTR_LIMIT_PERCENT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 328005
#define RSHMC8015_ATTR_EXT_AINPUT_STATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328006
#define RSHMC8015_ATTR_EXT_AOUTPUT_STATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328007
#define RSHMC8015_ATTR_EXT_AOUTPUT_MODE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328008
#define RSHMC8015_ATTR_EXT_DINPUT_STATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328009
#define RSHMC8015_ATTR_EXT_DINPUT_MODE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 328010
#define RSHMC8015_ATTR_EXT_DINPUT_INVERT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328011
#define RSHMC8015_ATTR_EXT_DOUTPUT_STATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328012
#define RSHMC8015_ATTR_EXT_DOUTPUT_MODE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328013
#define RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 328014
#define RSHMC8015_ATTR_EXT_DOUTPUT_INVERT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 328015
#define RSHMC8015_ATTR_EXT_SENSOR_STATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328016
#define RSHMC8015_ATTR_EXT_SENSOR_MODE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 328017
#define RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 328018
#define RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 328019
#define RSHMC8015_ATTR_EXT_SENSOR_RANGE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 328020
#define RSHMC8015_ATTR_VIEW_MODE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 327972
#define RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 327973
#define RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 327974
#define RSHMC8015_ATTR_VIEW_NORM_FUNCTION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 327975
#define RSHMC8015_ATTR_VIEW_HARM_SELECT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327976
#define RSHMC8015_ATTR_VIEW_HARM_SOURCE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327977
#define RSHMC8015_ATTR_VIEW_HARM_NUMBER                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327978
#define RSHMC8015_ATTR_VIEW_HARM_SCALING                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 327979
#define RSHMC8015_ATTR_VIEW_HARM_SUBSET                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327980
#define RSHMC8015_ATTR_INTEGRATOR_STATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327981
#define RSHMC8015_ATTR_INTEGRATOR_MODE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 327982
#define RSHMC8015_ATTR_INTEGRATOR_DURATION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 327983
#define RSHMC8015_ATTR_INTEGRATOR_RESET                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327984
#define RSHMC8015_ATTR_INTEGRATOR_START                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 327985
#define RSHMC8015_ATTR_INTEGRATOR_STOP                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 327986
#define RSHMC8015_ATTR_LOGGING_STATE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 327988
#define RSHMC8015_ATTR_LOGGING_PAGE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 327989
#define RSHMC8015_ATTR_LOGGING_MODE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 327990
#define RSHMC8015_ATTR_LOGGING_TIME                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 327991
#define RSHMC8015_ATTR_LOGGING_COUNT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 327992
#define RSHMC8015_ATTR_ID_QUERY_RESPONSE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328021
#define RSHMC8015_ATTR_DISPLAY_CLEAR                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 327970
#define RSHMC8015_ATTR_DISPLAY_TEXT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 327971
#define RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 328023
#define RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328024
#define RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 328025
#define RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 328028
#define RSHMC8015_ATTR_SYSTEM_START_BEEP                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 328029
#define RSHMC8015_ATTR_SYSTEM_NAME                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 328030
#define RSHMC8015_ATTR_SYSTEM_ERROR                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 328031
#define RSHMC8015_ATTR_SYSTEM_LOCAL                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 328032
#define RSHMC8015_ATTR_SYSTEM_REMOTE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 328033
#define RSHMC8015_ATTR_SYSTEM_RWLOCK                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 328034
#define RSHMC8015_ATTR_SYSTEM_VERSION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 328035
#define RSHMC8015_ATTR_SYSTEM_DEVICE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 328036
#define RSHMC8015_ATTR_SYSTEM_SHUTDOWN                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 328037
#define RSHMC8015_ATTR_SYSTEM_SOFTWARE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 328038
#define RSHMC8015_ATTR_SYSTEM_HARDWARE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 328039
#define RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 328040
#define RSHMC8015_ATTR_STATUS_PRESET                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 328043

// rshmc8015_rngViewMode
#define RSHMC8015_VAL_VIEW_MODE_NORMAL                                      0
#define RSHMC8015_VAL_VIEW_MODE_HARMONICS                                   1
#define RSHMC8015_VAL_VIEW_MODE_TRENDCHART                                  2
#define RSHMC8015_VAL_VIEW_MODE_SIGNALS                                     3
#define RSHMC8015_VAL_VIEW_MODE_STANDARDS                                   4
#define RSHMC8015_VAL_VIEW_MODE_INRUSH                                      5

// rshmc8015_rngNormalViewFunction
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_EMPTY                                0
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_P                                    1
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_S                                    2
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_Q                                    3
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_PF                                   4
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_PHI                                  5
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_FU                                   6
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_FI                                   7
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_UPP                                  8
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_UMP                                  9
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_IPP                                  10
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_IMP                                  11
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_PPP                                  12
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_PMP                                  13
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_URMS                                 14
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_UAVG                                 15
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRMS                                 16
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_IAVG                                 17
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_UTHD                                 18
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_ITHD                                 19
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_DIN                                  20
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_AIN                                  21
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_TIME                                 22
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_WH                                   23
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHP                                  24
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHM                                  25
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_AH                                   26
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHP                                  27
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHM                                  28
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_TEMP                                 29
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM1                                 30
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM2                                 31
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM3                                 32
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM4                                 33
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM5                                 34
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM6                                 35
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_URANGE                               36
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRANGE                               37
#define RSHMC8015_VAL_NORMAL_VIEW_FUNC_FPLL                                 38

// rshmc8015_rngViewNormalPageSize
#define RSHMC8015_VAL_VIEW_PAGE_SIZE_6                                      0
#define RSHMC8015_VAL_VIEW_PAGE_SIZE_10                                     1

// rshmc8015_rngHarmonicsView
#define RSHMC8015_VAL_VIEW_HARM_VIEW_BAR                                    0
#define RSHMC8015_VAL_VIEW_HARM_VIEW_TAB                                    1

// rshmc8015_rngHarmonicsSource
#define RSHMC8015_VAL_VIEW_HARM_SOURCE_VOLTAGE                              0
#define RSHMC8015_VAL_VIEW_HARM_SOURCE_CURRENT                              1
#define RSHMC8015_VAL_VIEW_HARM_SOURCE_BOTH                                 2

// rshmc8015_rngHarmonicsScaling
#define RSHMC8015_VAL_VIEW_HARM_SCALING_ABSOLUTE                            0
#define RSHMC8015_VAL_VIEW_HARM_SCALING_PERCENT                             1

// rshmc8015_rngHarmonicsSubset
#define RSHMC8015_VAL_VIEW_HARM_SUBSET_EVEN                                 0
#define RSHMC8015_VAL_VIEW_HARM_SUBSET_ODD                                  1

// rshmc8015_rngIntegratorMode
#define RSHMC8015_VAL_INTEGRATOR_MODE_MANUAL                                0
#define RSHMC8015_VAL_INTEGRATOR_MODE_DURATION                              1
#define RSHMC8015_VAL_INTEGRATOR_MODE_SPAN                                  2
#define RSHMC8015_VAL_INTEGRATOR_MODE_EXTERN                                3

// rshmc8015_rngLoggingMode
#define RSHMC8015_VAL_LOGGING_MODE_UNLIMITED                                0
#define RSHMC8015_VAL_LOGGING_MODE_COUNT                                    1
#define RSHMC8015_VAL_LOGGING_MODE_TIME                                     2
#define RSHMC8015_VAL_LOGGING_MODE_SPAN                                     3

// rshmc8015_rngLimitSource
#define RSHMC8015_VAL_LIMIT_SOURCE_URMS                                     0
#define RSHMC8015_VAL_LIMIT_SOURCE_UAVG                                     1
#define RSHMC8015_VAL_LIMIT_SOURCE_FU                                       2
#define RSHMC8015_VAL_LIMIT_SOURCE_IRMS                                     3
#define RSHMC8015_VAL_LIMIT_SOURCE_IAVG                                     4
#define RSHMC8015_VAL_LIMIT_SOURCE_FI                                       5
#define RSHMC8015_VAL_LIMIT_SOURCE_P                                        6
#define RSHMC8015_VAL_LIMIT_SOURCE_S                                        7
#define RSHMC8015_VAL_LIMIT_SOURCE_Q                                        8
#define RSHMC8015_VAL_LIMIT_SOURCE_PF                                       9
#define RSHMC8015_VAL_LIMIT_SOURCE_PHI                                      10
#define RSHMC8015_VAL_LIMIT_SOURCE_FPLL                                     11
#define RSHMC8015_VAL_LIMIT_SOURCE_UTHD                                     12
#define RSHMC8015_VAL_LIMIT_SOURCE_ITHD                                     13

// rshmc8015_rngAcquisitionMode
#define RSHMC8015_VAL_ACQ_MODE_AC                                           0
#define RSHMC8015_VAL_ACQ_MODE_DC                                           1
#define RSHMC8015_VAL_ACQ_MODE_EXTERN                                       2

// rshmc8015_rngAcquisitionCrestFactor
#define RSHMC8015_VAL_CREST_FACTOR_3                                        0
#define RSHMC8015_VAL_CREST_FACTOR_6                                        1

// rshmc8015_rngPLLSource
#define RSHMC8015_VAL_PLL_SOURCE_VOLTAGE                                    0
#define RSHMC8015_VAL_PLL_SOURCE_CURRENT                                    1

// rshmc8015_rngImageFormat
#define RSHMC8015_VAL_IMAGE_FORMAT_BMP                                      0
#define RSHMC8015_VAL_IMAGE_FORMAT_PNG                                      1

// rshmc8015_rngAnalogOutputMode
#define RSHMC8015_VAL_AOUT_MODE_VOLTAGE                                     0
#define RSHMC8015_VAL_AOUT_MODE_CURRENT                                     1
#define RSHMC8015_VAL_AOUT_MODE_POWER                                       2
#define RSHMC8015_VAL_AOUT_MODE_LIM1                                        3
#define RSHMC8015_VAL_AOUT_MODE_LIM2                                        4
#define RSHMC8015_VAL_AOUT_MODE_LIM3                                        5
#define RSHMC8015_VAL_AOUT_MODE_LIM4                                        6
#define RSHMC8015_VAL_AOUT_MODE_LIM5                                        7
#define RSHMC8015_VAL_AOUT_MODE_LIM6                                        8

// rshmc8015_rngDigitalInputMode
#define RSHMC8015_VAL_DINP_MODE_FREQUENCY                                   0
#define RSHMC8015_VAL_DINP_MODE_PWM                                         1
#define RSHMC8015_VAL_DINP_MODE_STATE                                       2
#define RSHMC8015_VAL_DINP_MODE_COMM                                        3
#define RSHMC8015_VAL_DINP_MODE_INT                                         4

// rshmc8015_rngDigitalOutputMode
#define RSHMC8015_VAL_DOUT_MODE_FPLL                                        0
#define RSHMC8015_VAL_DOUT_MODE_COMM                                        1
#define RSHMC8015_VAL_DOUT_MODE_LIM1                                        2
#define RSHMC8015_VAL_DOUT_MODE_LIM2                                        3
#define RSHMC8015_VAL_DOUT_MODE_LIM3                                        4
#define RSHMC8015_VAL_DOUT_MODE_LIM4                                        5
#define RSHMC8015_VAL_DOUT_MODE_LIM5                                        6
#define RSHMC8015_VAL_DOUT_MODE_LIM6                                        7

// rshmc8015_rngSensorMode
#define RSHMC8015_VAL_SENSOR_MODE_SHUNT                                     0
#define RSHMC8015_VAL_SENSOR_MODE_CLAMP                                     1

// rshmc8015_rngStatusRegisterOperation
#define RSHMC8015_VAL_STAT_REG_QUESTIONABLE                                 1
#define RSHMC8015_VAL_STAT_REG_OPERATION                                    2

// rshmc8015_rngStatusRegisterQuery
#define RSHMC8015_VAL_STAT_REG_QUERY_COND                                   0
#define RSHMC8015_VAL_STAT_REG_QUERY_EVENT                                  1
#define RSHMC8015_VAL_STAT_REG_QUERY_ENABLE                                 2
#define RSHMC8015_VAL_STAT_REG_QUERY_PTRANSITION                            3
#define RSHMC8015_VAL_STAT_REG_QUERY_NTRANSITION                            4

// rshmc8015_rngDevice
#define RSHMC8015_VAL_DEVICE_INT                                            0
#define RSHMC8015_VAL_DEVICE_EXT                                            1
#define RSHMC8015_VAL_DEVICE_DEF                                            2
/* END GENERATE */

/*****************************************************************************
 *- Hidden Attribute Declarations -------------------------------------------*
 *****************************************************************************/

#define RSHMC8015_ATTR_OPC_TIMEOUT               (RS_ATTR_OPC_TIMEOUT)           /* ViInt32 */
#define RSHMC8015_ATTR_IO_SESSION                (RS_ATTR_IO_SESSION)            /* ViSession */
#define RSHMC8015_ATTR_OPC_CALLBACK              (RS_ATTR_OPC_CALLBACK)          /* ViAddr */
#define RSHMC8015_ATTR_CHECK_STATUS_CALLBACK     (RS_ATTR_CHECK_STATUS_CALLBACK) /* ViAddr */

/****************************************************************************
 *---------------- Constant definition  ------------------------------------*
 ****************************************************************************/

#define RSHMC8015_VAL_INTEGRATOR_OPERATION_START  0
#define RSHMC8015_VAL_INTEGRATOR_OPERATION_STOP   1
#define RSHMC8015_VAL_INTEGRATOR_OPERATION_RESET  2
	
/****************************************************************************
*---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/

ViStatus _VI_FUNC rshmc8015_init (ViRsrc resourceName, ViBoolean IDQuery,
                                  ViBoolean resetDevice,
                                  ViSession* instrumentHandle);
ViStatus _VI_FUNC rshmc8015_InitWithOptions (ViRsrc resourceName, ViBoolean IDQuery,
                                             ViBoolean resetDevice,
                                             ViString optionString,
                                             ViSession* instrumentHandle);
ViStatus _VI_FUNC rshmc8015_ConfigureAcquisitionMode (ViSession instrumentHandle,
                                                      ViInt32 channel,
                                                      ViInt32 acquisitionMode);
ViStatus _VI_FUNC rshmc8015_ConfigureACAcquisition (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViInt32 PLLSource,
                                                    ViBoolean frequencyFilter,
                                                    ViBoolean digitalFilter,
                                                    ViBoolean BWL);
ViStatus _VI_FUNC rshmc8015_ConfigureVoltageAcquisition (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViBoolean autorange,
                                                         ViReal64 range,
                                                         ViInt32 crestFactor,
                                                         ViBoolean invert);
ViStatus _VI_FUNC rshmc8015_ConfigureCurrentAcquisition (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViBoolean autorange,
                                                         ViReal64 range,
                                                         ViInt32 crestFactor,
                                                         ViBoolean invert);
ViStatus _VI_FUNC rshmc8015_QueryOCP (ViSession instrumentHandle, ViInt32 channel,
                                      ViBoolean* OCP);
ViStatus _VI_FUNC rshmc8015_ResetOCP (ViSession instrumentHandle, ViInt32 channel);
ViStatus _VI_FUNC rshmc8015_ShowMessageBox (ViSession instrumentHandle,
                                            ViString text);
ViStatus _VI_FUNC rshmc8015_ClearMessageBox (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_ConfigureViewMode (ViSession instrumentHandle,
                                               ViInt32 viewMode);
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewPageSize (ViSession instrumentHandle,
                                                         ViInt32 page,
                                                         ViInt32 size);
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewActivePage
             (ViSession instrumentHandle, ViInt32 activePage);
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewFunction (ViSession instrumentHandle,
                                                         ViInt32 page, ViInt32 cell,
                                                         ViInt32 function);
ViStatus _VI_FUNC rshmc8015_ConfigureHarmonicsView (ViSession instrumentHandle,
                                                    ViInt32 select, ViInt32 source,
                                                    ViInt32 number, ViInt32 scaling,
                                                    ViInt32 subset);
ViStatus _VI_FUNC rshmc8015_QueryData (ViSession instrumentHandle, ViInt32 channel,
                                       ViInt32 arrayLength, ViReal64 _VI_FAR data[],
                                       ViInt32* actualDataLength);
ViStatus _VI_FUNC rshmc8015_WriteFunctionList (ViSession instrumentHandle,
                                               ViInt32 channel,
                                               ViString functionList);
ViStatus _VI_FUNC rshmc8015_QueryFunctionList (ViSession instrumentHandle,
                                               ViInt32 channel, ViInt32 bufferSize,
                                               ViChar _VI_FAR functionList[]);
ViStatus _VI_FUNC rshmc8015_QueryFunctionListLength (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32* length);
ViStatus _VI_FUNC rshmc8015_ConfigureIntegrator (ViSession instrumentHandle,
                                                 ViBoolean enabled, ViInt32 mode,
                                                 ViReal64 duration);
ViStatus _VI_FUNC rshmc8015_IntegratorOperation (ViSession instrumentHandle,
                                                 ViInt32 operation);
ViStatus _VI_FUNC rshmc8015_ConfigureIntegratorStartTime (ViSession instrumentHandle,
                                                          ViInt32 year,
                                                          ViInt32 month,
                                                          ViInt32 day, ViInt32 hour,
                                                          ViInt32 minute,
                                                          ViInt32 second);
ViStatus _VI_FUNC rshmc8015_ConfigureLoggingFile (ViSession instrumentHandle,
                                                  ViString filename,
                                                  ViInt32 device);
ViStatus _VI_FUNC rshmc8015_ConfigureLogging (ViSession instrumentHandle,
                                              ViBoolean enabled, ViInt32 mode,
                                              ViInt32 count, ViReal64 time);
ViStatus _VI_FUNC rshmc8015_ConfigureLoggingStartTime (ViSession instrumentHandle,
                                                       ViInt32 year, ViInt32 month,
                                                       ViInt32 day, ViInt32 hour,
                                                       ViInt32 minute,
                                                       ViInt32 second);
ViStatus _VI_FUNC rshmc8015_QueryLimitCheckResult (ViSession instrumentHandle,
                                                   ViInt32 channel, ViInt32 limit,
                                                   ViBoolean* limitCheckResult);
ViStatus _VI_FUNC rshmc8015_QueryLimitPercent (ViSession instrumentHandle,
                                               ViInt32 channel, ViInt32 limit,
                                               ViReal64* limitPercent);
ViStatus _VI_FUNC rshmc8015_ConfigureMeasurementLimit (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViInt32 limit,
                                                       ViBoolean state,
                                                       ViInt32 source,
                                                       ViReal64 high, ViReal64 low);
ViStatus _VI_FUNC rshmc8015_ConfigureExtAnalogIn (ViSession instrumentHandle,
                                                  ViInt32 channel, ViBoolean state);
ViStatus _VI_FUNC rshmc8015_ConfigureExtAnalogOut (ViSession instrumentHandle,
                                                   ViInt32 channel, ViBoolean state,
                                                   ViInt32 mode);
ViStatus _VI_FUNC rshmc8015_ConfigureExtDigitalIn (ViSession instrumentHandle,
                                                   ViInt32 channel, ViBoolean state,
                                                   ViInt32 mode, ViBoolean invert);
ViStatus _VI_FUNC rshmc8015_ConfigureExtDigitalOut (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViBoolean state, ViInt32 mode,
                                                    ViBoolean invert,
                                                    ViBoolean outputState);
ViStatus _VI_FUNC rshmc8015_ConfigureExtSensor (ViSession instrumentHandle,
                                                ViInt32 channel, ViBoolean state,
                                                ViInt32 mode, ViReal64 resistance,
                                                ViReal64 ratio, ViReal64 range);
ViStatus _VI_FUNC rshmc8015_SetAttributeViInt32 (ViSession instrumentHandle,
                                                 ViString repeatedCapabilityName,
                                                 ViAttr attributeID,
                                                 ViInt32 attributeValue);
ViStatus _VI_FUNC rshmc8015_SetAttributeViInt64 (ViSession instrumentHandle,
                                                 ViString repeatedCapabilityName,
                                                 ViAttr attributeID,
                                                 ViInt64 attributeValue);
ViStatus _VI_FUNC rshmc8015_SetAttributeViReal64 (ViSession instrumentHandle,
                                                  ViString repeatedCapabilityName,
                                                  ViAttr attributeID,
                                                  ViReal64 attributeValue);
ViStatus _VI_FUNC rshmc8015_SetAttributeViString (ViSession instrumentHandle,
                                                  ViString repeatedCapabilityName,
                                                  ViAttr attributeID,
                                                  ViString attributeValue);
ViStatus _VI_FUNC rshmc8015_SetAttributeViBoolean (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViBoolean attributeValue);
ViStatus _VI_FUNC rshmc8015_SetAttributeViSession (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViSession attributeValue);
ViStatus _VI_FUNC rshmc8015_GetAttributeRepeatedCapabilityIds
             (ViSession instrumentHandle, ViAttr attributeID, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityId_s[]);
ViStatus _VI_FUNC rshmc8015_GetAttributeRepeatedCapabilityIdNames
             (ViSession instrumentHandle, ViAttr attributeID,
              ViString repeatedCapabilityId, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityIdName_s[]);
ViStatus _VI_FUNC rshmc8015_GetAttributeViInt32 (ViSession instrumentHandle,
                                                 ViString repeatedCapabilityName,
                                                 ViAttr attributeID,
                                                 ViInt32* attributeValue);
ViStatus _VI_FUNC rshmc8015_GetAttributeViInt64 (ViSession instrumentHandle,
                                                 ViString repeatedCapabilityName,
                                                 ViAttr attributeID,
                                                 ViInt64* attributeValue);
ViStatus _VI_FUNC rshmc8015_GetAttributeViReal64 (ViSession instrumentHandle,
                                                  ViString repeatedCapabilityName,
                                                  ViAttr attributeID,
                                                  ViReal64* attributeValue);
ViStatus _VI_FUNC rshmc8015_GetAttributeViString (ViSession instrumentHandle,
                                                  ViString repeatedCapabilityName,
                                                  ViAttr attributeID,
                                                  ViInt32 bufferSize,
                                                  ViChar _VI_FAR attributeValue[]);
ViStatus _VI_FUNC rshmc8015_GetAttributeViBoolean (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViBoolean* attributeValue);
ViStatus _VI_FUNC rshmc8015_GetAttributeViSession (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViSession* attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViInt32 (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViInt32 attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViInt64 (ViSession instrumentHandle,
                                                   ViString repeatedCapabilityName,
                                                   ViAttr attributeID,
                                                   ViInt64 attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViReal64 (ViSession instrumentHandle,
                                                    ViString repeatedCapabilityName,
                                                    ViAttr attributeID,
                                                    ViReal64 attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViString (ViSession instrumentHandle,
                                                    ViString repeatedCapabilityName,
                                                    ViAttr attributeID,
                                                    ViString attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViBoolean (ViSession instrumentHandle,
                                                     ViString repeatedCapabilityName,
                                                     ViAttr attributeID,
                                                     ViBoolean attributeValue);
ViStatus _VI_FUNC rshmc8015_CheckAttributeViSession (ViSession instrumentHandle,
                                                     ViString repeatedCapabilityName,
                                                     ViAttr attributeID,
                                                     ViSession attributeValue);
ViStatus _VI_FUNC rshmc8015_reset (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_self_test (ViSession instrumentHandle,
                                       ViInt16* selfTestResult,
                                       ViChar _VI_FAR selfTestMessage[]);
ViStatus _VI_FUNC rshmc8015_revision_query (ViSession instrumentHandle,
                                            ViChar _VI_FAR instrumentDriverRevision[],
                                            ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC rshmc8015_BeeperState (ViSession instrumentHandle,
                                         ViBoolean beeperState);
ViStatus _VI_FUNC rshmc8015_StartBeep (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_SystemName (ViSession instrumentHandle, ViString name);
ViStatus _VI_FUNC rshmc8015_SystemLocal (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_SystemRemote (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_SystemRWLock (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_SystemVersion (ViSession instrumentHandle,
                                           ViInt32 length,
                                           ViChar _VI_FAR systemVersion[]);
ViStatus _VI_FUNC rshmc8015_SystemDevice (ViSession instrumentHandle,
                                          ViInt32 length,
                                          ViChar _VI_FAR systemDevice[]);
ViStatus _VI_FUNC rshmc8015_SystemShutdown (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_SystemSoftware (ViSession instrumentHandle,
                                            ViInt32 length,
                                            ViChar _VI_FAR systemSoftware[]);
ViStatus _VI_FUNC rshmc8015_SystemHardware (ViSession instrumentHandle,
                                            ViInt32 length,
                                            ViChar _VI_FAR systemHardware[]);
ViStatus _VI_FUNC rshmc8015_SystemSerialNumber (ViSession instrumentHandle,
                                                ViInt32 length,
                                                ViChar _VI_FAR systemSerialNumber[]);
ViStatus _VI_FUNC rshmc8015_error_query (ViSession instrumentHandle,
                                         ViInt32* errorCode,
                                         ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rshmc8015_error_message (ViSession instrumentHandle,
                                           ViStatus errorCode,
                                           ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rshmc8015_SetStatusRegister (ViSession instrumentHandle,
                                               ViInt32 registerOperation,
                                               ViInt32 enable, ViInt32 PTransition,
                                               ViInt32 NTransition);
ViStatus _VI_FUNC rshmc8015_GetStatusRegister (ViSession instrumentHandle,
                                               ViInt32 registerOperation,
                                               ViInt32 statusRegisterQuery,
                                               ViInt32* registerValue);
ViStatus _VI_FUNC rshmc8015_StatusPreset (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_GetError (ViSession instrumentHandle, ViStatus* code,
                                      ViInt32 bufferSize,
                                      ViChar _VI_FAR description[]);
ViStatus _VI_FUNC rshmc8015_ClearError (ViSession instrumentHandle);
ViStatus _VI_FUNC rshmc8015_WriteInstrData (ViSession instrumentHandle,
                                            ViString writeBuffer);
ViStatus _VI_FUNC rshmc8015_ReadInstrData (ViSession instrumentHandle,
                                           ViInt32 numberOfBytesToRead,
                                           ViChar _VI_FAR readBuffer[],
                                           ViUInt32* numBytesRead);
ViStatus _VI_FUNC rshmc8015_QueryViBoolean (ViSession instrumentHandle,
                                            ViString command, ViBoolean* value);
ViStatus _VI_FUNC rshmc8015_QueryViInt32 (ViSession instrumentHandle,
                                          ViString command, ViInt32* value);
ViStatus _VI_FUNC rshmc8015_QueryViReal64 (ViSession instrumentHandle,
                                           ViString command, ViReal64* value);
ViStatus _VI_FUNC rshmc8015_QueryViString (ViSession instrumentHandle,
                                           ViString command, ViInt32 bufferSize,
                                           ViChar _VI_FAR value[]);
ViStatus _VI_FUNC rshmc8015_ImageSnapshot (ViSession instrumentHandle,
                                           ViString destination);
ViStatus _VI_FUNC rshmc8015_ConfigureImageFormat (ViSession instrumentHandle,
                                                  ViInt32 imageFormat);
ViStatus _VI_FUNC rshmc8015_QueryImageSize (ViSession instrumentHandle,
                                            ViInt32* imageWidth,
                                            ViInt32* imageHeight);
ViStatus _VI_FUNC rshmc8015_close (ViSession instrumentHandle);

/****************************************************************************
 *------------------------ Error And Completion Codes ----------------------*
 ****************************************************************************/

#define RSHMC8015_WARN_MEASURE_UNCALIBRATED    (RS_CLASS_WARN_BASE + 0x0001L)
#define RSHMC8015_WARN_OVER_RANGE              (RS_CLASS_WARN_BASE + 0x0002L)

#define RSHMC8015_ERROR_MARKER_NOT_ENABLED     (RS_CLASS_ERROR_BASE + 0x0003L)
#define RSHMC8015_ERROR_NOT_DELTA_MARKER       (RS_CLASS_ERROR_BASE + 0x0002L)
#define RSHMC8015_ERROR_MAX_TIME_EXCEEDED      (RS_CLASS_ERROR_BASE + 0x0001L)

#define RSHMC8015_WARNMSG_MEASURE_UNCALIBRATED "Uncalibrated measurement"
#define RSHMC8015_WARNMSG_OVER_RANGE           "Measurement overrange"

#define RSHMC8015_ERRMSG_MARKER_NOT_ENABLED    "Marker Not Enabled"
#define RSHMC8015_ERRMSG_NOT_DELTA_MARKER      "Not Delta Marker"
#define RSHMC8015_ERRMSG_MAX_TIME_EXCEEDED     "Max Time Exceeded"

#define RSHMC8015_ERROR_CODES_AND_MSGS \
    {RSHMC8015_WARN_MEASURE_UNCALIBRATED,  RSHMC8015_WARNMSG_MEASURE_UNCALIBRATED},\
    {RSHMC8015_WARN_OVER_RANGE,            RSHMC8015_WARNMSG_OVER_RANGE},\
    {RSHMC8015_ERROR_MARKER_NOT_ENABLED,   RSHMC8015_ERRMSG_MARKER_NOT_ENABLED},\
    {RSHMC8015_ERROR_NOT_DELTA_MARKER,     RSHMC8015_ERRMSG_NOT_DELTA_MARKER},\
    {RSHMC8015_ERROR_MAX_TIME_EXCEEDED,    RSHMC8015_ERRMSG_MAX_TIME_EXCEEDED}

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __RSHMC8015_HEADER */



