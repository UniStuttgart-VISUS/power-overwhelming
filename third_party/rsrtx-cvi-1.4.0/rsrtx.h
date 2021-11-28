/****************************************************************************
 *
 *  Rohde & Schwarz RTM Oscilloscope instrument driver include file
 *
 ****************************************************************************/

#ifndef __RSRTX_HEADER
#define __RSRTX_HEADER

#include "rscore.h"
#include "rsrtx_attributes.h"
#include "rsrtx_utility.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Useful Macros & Constants -----------------------------------------------*
 *****************************************************************************/
#define RSRTX_SIMULATION_ID_QUERY      "Rohde&Schwarz,RTB2000,123456/789,1.23"  /* Default definition of ID Query Response for simulation */
#define RSRTX_VALID_ID_RESPONSE_STRING "Rohde&Schwarz"      /* Valid response for identification query */
#define RSRTX_SIMULATION_OPT_QUERY     "K0"      /* Simulated response for *OPT? command */
#define RSRTX_OPC_TIMEOUT              30000L    /* Timeout to wait for OPC in milliseconds */

/****************************************************************************
 *----------------- Instrument Driver Revision Information -----------------*
 ****************************************************************************/

/* Class Driver Identification */

#define RSRTX_CLASS_DRIVER_DESCRIPTION           ""
#define RSRTX_CLASS_DRIVER_PREFIX                ""
#define RSRTX_CLASS_DRIVER_VENDOR                ""
#define RSRTX_CLASS_DRIVER_REVISION              ""
#define RSRTX_CLASS_SPEC_MAJOR_VERSION           1L    /* Class specification major version */
#define RSRTX_CLASS_SPEC_MINOR_VERSION           0L    /* Class specification minor version */

/* Driver Identification */

#define RSRTX_SPECIFIC_DRIVER_DESCRIPTION        ""
#define RSRTX_SPECIFIC_DRIVER_PREFIX             "RSRTX"
#define RSRTX_SPECIFIC_DRIVER_LOCATOR            ""
#define RSRTX_SPECIFIC_DRIVER_VENDOR             ""
#define RSRTX_MAJOR_VERSION                      1L    /* Instrument driver major version          */
#define RSRTX_MINOR_VERSION                      4L    /* Instrument driver minor version          */
#define RSRTX_MINOR_MINOR_VERSION                0L    /* Instrument driver minor minor version    */

/* Driver Capabilities */

#define RSRTX_SUPPORTED_INSTRUMENT_MODELS        ""    /* Instrument driver supported model(s)     */
#define RSRTX_GROUP_CAPABILITIES                 ""
#define RSRTX_FUNCTION_CAPABILITIES              ""

/****************************************************************************
 *------------------------ Error And Completion Codes ----------------------*
 ****************************************************************************/

#define RSRTX_WARN_MEASURE_UNCALIBRATED    (RS_CLASS_WARN_BASE + 0x0001L)
#define RSRTX_WARN_OVER_RANGE              (RS_CLASS_WARN_BASE + 0x0002L)

#define RSRTX_ERROR_MARKER_NOT_ENABLED     (RS_CLASS_ERROR_BASE + 0x0003L)
#define RSRTX_ERROR_NOT_DELTA_MARKER       (RS_CLASS_ERROR_BASE + 0x0002L)
#define RSRTX_ERROR_MAX_TIME_EXCEEDED      (RS_CLASS_ERROR_BASE + 0x0001L)

#define RSRTX_WARNMSG_MEASURE_UNCALIBRATED "Uncalibrated measurement"
#define RSRTX_WARNMSG_OVER_RANGE           "Measurement overrange"

#define RSRTX_ERRMSG_MARKER_NOT_ENABLED    "Marker Not Enabled"
#define RSRTX_ERRMSG_NOT_DELTA_MARKER      "Not Delta Marker"
#define RSRTX_ERRMSG_MAX_TIME_EXCEEDED     "Max Time Exceeded"

#define RSRTX_ERROR_CODES_AND_MSGS \
    {RSRTX_WARN_MEASURE_UNCALIBRATED,  RSRTX_WARNMSG_MEASURE_UNCALIBRATED},\
    {RSRTX_WARN_OVER_RANGE,            RSRTX_WARNMSG_OVER_RANGE},\
    {RSRTX_ERROR_MARKER_NOT_ENABLED,   RSRTX_ERRMSG_MARKER_NOT_ENABLED},\
    {RSRTX_ERROR_NOT_DELTA_MARKER,     RSRTX_ERRMSG_NOT_DELTA_MARKER},\
    {RSRTX_ERROR_MAX_TIME_EXCEEDED,    RSRTX_ERRMSG_MAX_TIME_EXCEEDED}

/****************************************************************************
 *---------------------------- Attribute Defines ---------------------------*
 ****************************************************************************/

    /*- Inherent Instrument Specific Attributes ----------------------------*/

        /* User Options */

#define RSRTX_ATTR_RANGE_CHECK                                           RS_ATTR_RANGE_CHECK                                     /* ViBoolean */
#define RSRTX_ATTR_QUERY_INSTRUMENT_STATUS                               RS_ATTR_QUERY_INSTRUMENT_STATUS                         /* ViBoolean */
#define RSRTX_ATTR_CACHE                                                 RS_ATTR_CACHE                                           /* ViBoolean */
#define RSRTX_ATTR_SIMULATE                                              RS_ATTR_SIMULATE                                        /* ViBoolean */
#define RSRTX_ATTR_RECORD_COERCIONS                                      RS_ATTR_RECORD_COERCIONS                                /* ViBoolean */
#define RSRTX_ATTR_INTERCHANGE_CHECK                                     RS_ATTR_INTERCHANGE_CHECK                               /* ViBoolean */
#define RSRTX_ATTR_SPY                                                   RS_ATTR_SPY                                             /* ViBoolean */
#define RSRTX_ATTR_USE_SPECIFIC_SIMULATION                               RS_ATTR_USE_SPECIFIC_SIMULATION                         /* ViBoolean */

        /* Class Driver Identification */

#define RSRTX_ATTR_CLASS_DRIVER_DESCRIPTION                              RS_ATTR_CLASS_DRIVER_DESCRIPTION                        /* ViString, read-only */
#define RSRTX_ATTR_CLASS_DRIVER_PREFIX                                   RS_ATTR_CLASS_DRIVER_PREFIX                             /* ViString, read-only */
#define RSRTX_ATTR_CLASS_DRIVER_VENDOR                                   RS_ATTR_CLASS_DRIVER_VENDOR                             /* ViString, read-only */
#define RSRTX_ATTR_CLASS_DRIVER_REVISION                                 RS_ATTR_CLASS_DRIVER_REVISION                           /* ViString, read-only */
#define RSRTX_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION           /* ViInt32,  read-only */
#define RSRTX_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION                 RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION           /* ViInt32,  read-only */

        /* Driver Identification */

#define RSRTX_ATTR_SPECIFIC_DRIVER_DESCRIPTION                           RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION                     /* ViString, read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_PREFIX                                RS_ATTR_SPECIFIC_DRIVER_PREFIX                          /* ViString, read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_LOCATOR                               RS_ATTR_SPECIFIC_DRIVER_LOCATOR                         /* ViString, read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_VENDOR                                RS_ATTR_SPECIFIC_DRIVER_VENDOR                          /* ViString, read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_REVISION                              RS_ATTR_SPECIFIC_DRIVER_REVISION                        /* ViString, read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION        /* ViInt32,  read-only */
#define RSRTX_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION        /* ViInt32,  read-only */

        /* Driver Capabilities */

#define RSRTX_ATTR_SUPPORTED_INSTRUMENT_MODELS                           RS_ATTR_SUPPORTED_INSTRUMENT_MODELS                     /* ViString, read-only */
#define RSRTX_ATTR_GROUP_CAPABILITIES                                    RS_ATTR_GROUP_CAPABILITIES                              /* ViString, read-only */
#define RSRTX_ATTR_FUNCTION_CAPABILITIES                                 RS_ATTR_FUNCTION_CAPABILITIES                           /* ViString, read-only */
#define RSRTX_ATTR_CHANNEL_COUNT                                         RS_ATTR_CHANNEL_COUNT                                   /* ViInt32,  read-only */

        /* Driver Setup */

#define RSRTX_ATTR_DRIVER_SETUP                                          RS_ATTR_DRIVER_SETUP                                    /* ViString            */

        /* Instrument Identification */

#define RSRTX_ATTR_INSTRUMENT_MANUFACTURER                               RS_ATTR_INSTRUMENT_MANUFACTURER                         /* ViString, read-only */
#define RSRTX_ATTR_INSTRUMENT_MODEL                                      RS_ATTR_INSTRUMENT_MODEL                                /* ViString, read-only */
#define RSRTX_ATTR_INSTRUMENT_FIRMWARE_REVISION                          RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                    /* ViString, read-only */

        /* Advanced Session Information */

#define RSRTX_ATTR_IO_RESOURCE_DESCRIPTOR                                RS_ATTR_IO_RESOURCE_DESCRIPTOR                          /* ViString, read-only */
#define RSRTX_ATTR_LOGICAL_NAME                                          RS_ATTR_LOGICAL_NAME

/* ViString, read-only */

    /*- Instrument-Specific Attributes -------------------------------------*/

//#define RSRTX_ATTR_ID_QUERY_RESPONSE                                     (RS_SPECIFIC_PUBLIC_ATTR_BASE + 1L)                     /* ViString (Read Only)              */

/* BEGIN GENERATE */
#define RSRTX_ATTR_RECORD_LENGTH_AUTOMATIC                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1695
#define RSRTX_ATTR_RECORD_LENGTH                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1696
#define RSRTX_ATTR_ACQUIRE_MODE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1697
#define RSRTX_ATTR_PEAK_DETECT                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1698
#define RSRTX_ATTR_HIGH_RESOLUTION                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1699
#define RSRTX_ATTR_INTERPOLATION                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 3
#define RSRTX_ATTR_NUM_AVERAGES                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 4
#define RSRTX_ATTR_NUM_AVERAGES_CURRENT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1935
#define RSRTX_ATTR_NUM_AVERAGES_RESET                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1700
#define RSRTX_ATTR_MEMORY_MODE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1936
#define RSRTX_ATTR_AVERAGING_STATUS                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1428
#define RSRTX_ATTR_NUMBER_OF_WAVEFORMS                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 614
#define RSRTX_ATTR_SAMPLE_MODE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 5
#define RSRTX_ATTR_WAVEFORM_RATE_MAXIMUM                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1933
#define RSRTX_ATTR_HORZ_TIME_PER_RECORD                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 7
#define RSRTX_ATTR_HORZ_SCALE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 9
#define RSRTX_ATTR_ROLL_MODE_AUTOMATIC                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1937
#define RSRTX_ATTR_ROLL_MODE_MINIMUM_TIME_BASE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1938
#define RSRTX_ATTR_ACQUSITION_START_TIME                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 10
#define RSRTX_ATTR_ACQUISITION_TIME                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 12
#define RSRTX_ATTR_HORZ_ADC_SAMPLE_RATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 14
#define RSRTX_ATTR_HORZ_SAMPLE_RATE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 610
#define RSRTX_ATTR_AUTOSCALE                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 15
#define RSRTX_ATTR_HORZ_DIVISIONS                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 16
#define RSRTX_ATTR_HORZ_REFERENCE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 17
#define RSRTX_ATTR_ROLL_MODE                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 612
#define RSRTX_ATTR_TIMESTAMPS_FILENAME                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1571
#define RSRTX_ATTR_TIMESTAMPS_SAVE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1572
#define RSRTX_ATTR_ACQUISITION_TYPE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1023
#define RSRTX_ATTR_WAVEFORM_ACQUISITION_TYPE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2
#define RSRTX_ATTR_HORZ_RECORD_LENGTH                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 667
#define RSRTX_ATTR_GET_HORZ_RECORD_LENGTH                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1198
#define RSRTX_ATTR_PROBE_TYPE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 313
#define RSRTX_ATTR_PROBE_NAME                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 314
#define RSRTX_ATTR_PROBE_INPUT_IMPEDANCE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 315
#define RSRTX_ATTR_PROBE_INPUT_CAPACITANCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 316
#define RSRTX_ATTR_PROBE_DEGAUSS                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1939
#define RSRTX_ATTR_PROBE_ATTENUATION                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 23
#define RSRTX_ATTR_PROBE_GAIN                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1940
#define RSRTX_ATTR_PROBE_BANDWIDTH                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 24
#define RSRTX_ATTR_PROBE_DC_OFFSET                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 471
#define RSRTX_ATTR_PROBE_CM_OFFSET                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1843
#define RSRTX_ATTR_PROBE_ADDITIONAL_OFFSET                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 472
#define RSRTX_ATTR_PROBE_VOLTMETER_ENABLED                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 473
#define RSRTX_ATTR_PROBE_ATTENUATION_UNIT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 645
#define RSRTX_ATTR_PROBE_ATTENUATION_MANUAL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 646
#define RSRTX_ATTR_PROBE_GAIN_UNIT                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1941
#define RSRTX_ATTR_PROBE_GAIN_MANUAL                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1942
#define RSRTX_ATTR_PROBE_MICRO_BUTTON_ACTION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 319
#define RSRTX_ATTR_PROBE_SOFTWARE_VERSION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 320
#define RSRTX_ATTR_PROBE_PRODUCTION_DATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 321
#define RSRTX_ATTR_PROBE_PART_NUMBER                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 322
#define RSRTX_ATTR_PROBE_BUILD_NUMBER                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 474
#define RSRTX_ATTR_PROBE_SERIAL_NUMBER                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 323
#define RSRTX_ATTR_PROBE_COPY_TO_OFFSET                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 2129
#define RSRTX_ATTR_PROBE_ATTENUATOR_RT_ZA15_ENABLED                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2130
#define RSRTX_ATTR_PROBE_ZERO_ADJUST                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2131
#define RSRTX_ATTR_PROBE_SAVE_ZERO_ADJUST                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2132
#define RSRTX_ATTR_PROBE_INPUT_VOLTAGE_RANGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2133
#define RSRTX_ATTR_PROBE_BANDWIDTH_LIMIT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2134
#define RSRTX_ATTR_PROBE_AUDIBLE_OVERRANGE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2135
#define RSRTX_ATTR_PROBE_MEAS_MODE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2136
#define RSRTX_ATTR_PROBE_AC_COUPLING                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2137
#define RSRTX_ATTR_PROBE_METER_VISIBILITY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2138
#define RSRTX_ATTR_PROBE_METER_RESULT_SINGLE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2139
#define RSRTX_ATTR_PROBE_METER_RESULT_COMMON                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2140
#define RSRTX_ATTR_PROBE_METER_RESULT_DIFFERENTIAL                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2141
#define RSRTX_ATTR_PROBE_METER_RESULT_NEGATIVE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2142
#define RSRTX_ATTR_PROBE_METER_RESULT_POSITIVE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2143
#define RSRTX_ATTR_LABEL_ENABLED                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 687
#define RSRTX_ATTR_LABEL_NAME                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 688
#define RSRTX_ATTR_BUS_LABEL_ENABLED                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1573
#define RSRTX_ATTR_BUS_LABEL_NAME                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1574
#define RSRTX_ATTR_CHANNEL_ENABLED                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 25
#define RSRTX_ATTR_VERTICAL_RANGE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 26
#define RSRTX_ATTR_VERTICAL_COUPLING                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 28
#define RSRTX_ATTR_VERTICAL_SCALE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 29
#define RSRTX_ATTR_CHANNEL_OFFSET                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 30
#define RSRTX_ATTR_CHANNEL_ZERO_OFFSET                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1943
#define RSRTX_ATTR_CHANNEL_BANDWIDTH_LIMIT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 31
#define RSRTX_ATTR_CHANNEL_POLARITY                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 615
#define RSRTX_ATTR_CHANNEL_OVERLOAD                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 32
#define RSRTX_ATTR_CHANNEL_SKEW                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 33
#define RSRTX_ATTR_CHANNEL_THRESHOLD                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 34
#define RSRTX_ATTR_CHANNEL_THRESHOLD_HYSTERESIS                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1320
#define RSRTX_ATTR_CHANNEL_POSITION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1944
#define RSRTX_ATTR_CHANNEL_WAVEFORM_COLOR                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1945
#define RSRTX_ATTR_PROTOCOL_FIND_LEVEL                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 693
#define RSRTX_ATTR_CHANNEL_ALL_OFF                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1575
#define RSRTX_ATTR_CHANNEL_ALL_ON                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1576
#define RSRTX_ATTR_DIGITAL_ENABLED                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 822
#define RSRTX_ATTR_DIGITAL_DESKEW                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1162
#define RSRTX_ATTR_DIGITAL_THRESHOLD                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 823
#define RSRTX_ATTR_DIGITAL_TECHNOLOGY                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 824
#define RSRTX_ATTR_DIGITAL_HYSTERESIS                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 825
#define RSRTX_ATTR_DIGITAL_APPLY                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 826
#define RSRTX_ATTR_DIGITAL_LABEL                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 827
#define RSRTX_ATTR_DIGITAL_LABEL_ENABLED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 828
#define RSRTX_ATTR_DIGITAL_VERTICAL_CHANNEL_SIZE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 829
#define RSRTX_ATTR_DIGITAL_VERTICAL_POSITION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 830
#define RSRTX_ATTR_DIGITAL_CURRENT_STATUS_MAXIMUM                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1558
#define RSRTX_ATTR_DIGITAL_CURRENT_STATUS_MINIMUM                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1559
#define RSRTX_ATTR_DIGITAL_PROBE_ENABLED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1701
#define RSRTX_ATTR_DIGITAL_POINT_SELECTION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1844
#define RSRTX_ATTR_LOGIC_STATE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1702
#define RSRTX_ATTR_LOGIC_TYPE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1703
#define RSRTX_ATTR_LOGIC_THRESHOLD                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1704
#define RSRTX_ATTR_LOGIC_THRESHOLD_USER_LEVEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1705
#define RSRTX_ATTR_LOGIC_HYSTERESIS                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1706
#define RSRTX_ATTR_LOGIC_ARITHMETICS                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1707
#define RSRTX_ATTR_LOGIC_PROBE_CONNECTED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1946
#define RSRTX_ATTR_LOGIC_CURRENT_MAXIMUM                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1708
#define RSRTX_ATTR_LOGIC_CURRENT_MINIMUM                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1709
#define RSRTX_ATTR_LOGIC_POINT_SELECTION                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1947
#define RSRTX_ATTR_LOGIC_WAVEFORM_DATA_POINTS                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1948
#define RSRTX_ATTR_TRIGGER_TYPE_A                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 37
#define RSRTX_ATTR_TRIGGER_SOURCE_A                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 38
#define RSRTX_ATTR_TRIGGER_SOURCE_B                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 768
#define RSRTX_ATTR_EXTERNAL_TRIGGER_COUPLING                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 616
#define RSRTX_ATTR_EXTERNAL_TRIGGER_TERMINATION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1577
#define RSRTX_ATTR_EXTERNAL_TRIGGER_OVERLOAD                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1578
#define RSRTX_ATTR_TRIGGER_HOLDOFF_TIME                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 689
#define RSRTX_ATTR_TRIGGER_HOLDOFF_MODE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 831
#define RSRTX_ATTR_TRIGGER_HYSTERESIS_A                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 493
#define RSRTX_ATTR_TRIGGER_HYSTERESIS_A_LEVEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1579
#define RSRTX_ATTR_TRIGGER_HYSTERESIS_B                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 769
#define RSRTX_ATTR_TRIGGER_HYSTERESIS_B_LEVEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1580
#define RSRTX_ATTR_TRIGGER_ENABLED                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 482
#define RSRTX_ATTR_TRIGGER_MODIFIER_A                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 40
#define RSRTX_ATTR_TRIGGER_MODIFIER_B                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 770
#define RSRTX_ATTR_TRIGGER_EVENT_COUNT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 489
#define RSRTX_ATTR_TRIGGER_LEVEL_AUTO_FIND_A                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 41
#define RSRTX_ATTR_TRIGGER_LEVEL_AUTO_FIND_B                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 771
#define RSRTX_ATTR_TRIGGER_LEVEL_LOWER                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 832
#define RSRTX_ATTR_TRIGGER_LEVEL_UPPER                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 833
#define RSRTX_ATTR_TRIGGER_DELAY                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 488
#define RSRTX_ATTR_TRIGGER_LEVEL_A                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 39
#define RSRTX_ATTR_TRIGGER_LEVEL_B                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 772
#define RSRTX_ATTR_TRIGGER_SLOPE_A                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 45
#define RSRTX_ATTR_TRIGGER_SLOPE_B                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 773
#define RSRTX_ATTR_TRIGGER_COUPLING                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 490
#define RSRTX_ATTR_TRIGGER_FILTER_HIGH                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 774
#define RSRTX_ATTR_TRIGGER_FILTER_HF_REJECT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1845
#define RSRTX_ATTR_TV_TRIGGER_EVENT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 51
#define RSRTX_ATTR_TV_TRIGGER_LINE_NUMBER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 52
#define RSRTX_ATTR_TV_TRIGGER_POLARITY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 53
#define RSRTX_ATTR_TV_STANDARD                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 477
#define RSRTX_ATTR_WIDTH                                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 481
#define RSRTX_ATTR_WIDTH_DELTA                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 480
#define RSRTX_ATTR_WIDTH_POLARITY                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 478
#define RSRTX_ATTR_WIDTH_CONDITION                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 479
#define RSRTX_ATTR_TRIGGER_PATTERN_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 494
#define RSRTX_ATTR_TRIGGER_PATTERN_FUNCTION                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 495
#define RSRTX_ATTR_TRIGGER_PATTERN_POINT_ENABLED                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 496
#define RSRTX_ATTR_TRIGGER_PATTERN_MODE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 834
#define RSRTX_ATTR_TRIGGER_PATTERN_WIDTH                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 835
#define RSRTX_ATTR_TRIGGER_PATTERN_WIDTH_DELTA                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 836
#define RSRTX_ATTR_TRIGGER_PATTERN_WIDTH_CONDITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 837
#define RSRTX_ATTR_TRIGGER_WINDOW_RANGE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1921
#define RSRTX_ATTR_TRIGGER_WINDOW_WIDTH                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1922
#define RSRTX_ATTR_TRIGGER_WINDOW_TIME_RANGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1923
#define RSRTX_ATTR_TRIGGER_TIME_POLARITY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 838
#define RSRTX_ATTR_TRIGGER_TIME_CONDITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 839
#define RSRTX_ATTR_TRIGGER_TIME                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 840
#define RSRTX_ATTR_TRIGGER_TIME_DELTA                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 841
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2144
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_SOUND                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2145
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_SCREENSHOT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 2146
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_SAVE_WAVEFORM                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2147
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_REFERENCES                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 2148
#define RSRTX_ATTR_ACTIONS_ON_TRIGGER_PULSE_OUT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2149
#define RSRTX_ATTR_TRIGGER_OUT_MODE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 842
#define RSRTX_ATTR_TRIGGER_OUT_POLARITY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 843
#define RSRTX_ATTR_TRIGGER_OUT_PULSE_WIDTH                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 844
#define RSRTX_ATTR_RUNT_TRIGGER_POLARITY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1336
#define RSRTX_ATTR_RUNT_TRIGGER_WIDTH                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1846
#define RSRTX_ATTR_RUNT_TRIGGER_DELTA                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1847
#define RSRTX_ATTR_RUNT_TRIGGER_RANGE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1848
#define RSRTX_ATTR_RUNT_TRIGGER_LOWER_LEVEL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1337
#define RSRTX_ATTR_RUNT_TRIGGER_UPPER_LEVEL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1338
#define RSRTX_ATTR_TIMEOUT_TRIGGER_TIME                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1849
#define RSRTX_ATTR_TIMEOUT_TRIGGER_RANGE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1850
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_ACCESS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 529
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS_TYPE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 531
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_ADDRESS                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 530
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_MODE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 532
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_CONDITION_LENGTH                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 534
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_BIT_PATTERN                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 533
#define RSRTX_ATTR_PROTOCOL_I2C_TRIGGER_FIRST_BYTE_OFFSET                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 535
#define RSRTX_ATTR_PROTOCOL_SPI_TRIGGER_MODE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 537
#define RSRTX_ATTR_PROTOCOL_SPI_TRIGGER_SOURCE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1924
#define RSRTX_ATTR_PROTOCOL_SPI_TRIGGER_OFFSET                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 388
#define RSRTX_ATTR_PROTOCOL_SPI_BIT_PATTERN_LENGTH                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 539
#define RSRTX_ATTR_PROTOCOL_SPI_BIT_PATTERN                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 536
#define RSRTX_ATTR_PROTOCOL_UART_TRIGGER_MODE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 540
#define RSRTX_ATTR_PROTOCOL_UART_TRIGGER_SOURCE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1925
#define RSRTX_ATTR_PROTOCOL_UART_TRIGGER_DATA_PATTERN                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 541
#define RSRTX_ATTR_PROTOCOL_UART_TRIGGER_DATA_POSITION_INDEX_MIN            RS_SPECIFIC_PUBLIC_ATTR_BASE + 542
#define RSRTX_ATTR_PROTOCOL_UART_TRIGGER_CONDITION_LENGTH                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 543
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_MODE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 705
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_CONDITION_ID                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 706
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_CONDITION_DATA                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 805
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_ID_PATTERN                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 707
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_DATA_LENGTH                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 708
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_DATA_PATTERN                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 709
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_ERROR_CHECKSUM                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 710
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_ERROR_PARITY                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 806
#define RSRTX_ATTR_PROTOCOL_LIN_TRIGGER_ERROR_SYNC                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 807
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_MODE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 723
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_FRAME_TYPE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 724
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_CONDITION_ID                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 725
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_CONDITION_DATA                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 811
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ID_TYPE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 726
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ID_PATTERN                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 727
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_DATA_LENGTH                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 728
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_DATA_PATTERN                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 729
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ERROR_CRC                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 730
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ERROR_STUFFING                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 812
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ERROR_FORM                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 813
#define RSRTX_ATTR_PROTOCOL_CAN_TRIGGER_ERROR_ACK                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 814
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_TYPE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1143
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_WINDOW_LENGTH                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1144
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_WORD_SELECT_SLOPE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1145
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_RIGHT_CONDITION                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1163
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_RIGHT_MINIMUM                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1164
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_RIGHT_MAXIMUM                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1165
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_LEFT_CONDITION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1166
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_LEFT_MINIMUM                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1167
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_LEFT_MAXIMUM                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1168
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_COMBINATION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1169
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_CHANNEL_CONDITION                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1170
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_CHANNEL_MINIMUM                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1171
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRIGGER_CHANNEL_MAXIMUM                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1172
#define RSRTX_ATTR_MILSTD_TRIGGER_TYPE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1230
#define RSRTX_ATTR_MILSTD_TRIGGER_MODE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1851
#define RSRTX_ATTR_MILSTD_TRIGGER_SYNCHRONIZATION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1231
#define RSRTX_ATTR_MILSTD_TRIGGER_WORD                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1232
#define RSRTX_ATTR_MILSTD_TRIGGER_TRANSMISSION_TYPE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1424
#define RSRTX_ATTR_MILSTD_TRIGGER_FRAME                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1852
#define RSRTX_ATTR_MILSTD_TRIGGER_SYNCHRONIZATION_ERROR                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1233
#define RSRTX_ATTR_MILSTD_TRIGGER_TIMEOUT_ERROR                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1234
#define RSRTX_ATTR_MILSTD_TRIGGER_PARITY_ERROR                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1235
#define RSRTX_ATTR_MILSTD_TRIGGER_MANCHESTER_ERROR                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1236
#define RSRTX_ATTR_MILSTD_TRIGGER_COMMAND_TYPE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1237
#define RSRTX_ATTR_MILSTD_TRIGGER_COMMAND_DATA_DIRECTION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1238
#define RSRTX_ATTR_MILSTD_TRIGGER_RT_ADDRESS_CONDITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1239
#define RSRTX_ATTR_MILSTD_TRIGGER_RT_ADDRESS_MINIMUM                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1240
#define RSRTX_ATTR_MILSTD_TRIGGER_RT_ADDRESS_MAXIMUM                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1241
#define RSRTX_ATTR_MILSTD_TRIGGER_SUB_ADDRESS_CONDITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1242
#define RSRTX_ATTR_MILSTD_TRIGGER_SUB_ADDRESS_MINIMUM                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1243
#define RSRTX_ATTR_MILSTD_TRIGGER_SUB_ADDRESS_MAXIMUM                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1244
#define RSRTX_ATTR_MILSTD_TRIGGER_SUB_ADDRESS                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1245
#define RSRTX_ATTR_MILSTD_TRIGGER_WORD_CONDITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1246
#define RSRTX_ATTR_MILSTD_WORD_ADDRESS_MINIMUM                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1247
#define RSRTX_ATTR_MILSTD_WORD_ADDRESS_MAXIMUM                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1248
#define RSRTX_ATTR_MILSTD_TRIGGER_COMMAND_MODE_CODE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1249
#define RSRTX_ATTR_MILSTD_TRIGGER_COMMAND_MODE_VALUE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1250
#define RSRTX_ATTR_MILSTD_TRIGGER_RECEIVED_BIT_STATUS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1251
#define RSRTX_ATTR_MILSTD_TRIGGER_BUSY_BIT_STATUS                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1252
#define RSRTX_ATTR_MILSTD_TRIGGER_BUS_CONTROL_BIT_STATUS                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1253
#define RSRTX_ATTR_MILSTD_TRIGGER_INSTRUMENTATION_BIT_STATUS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1254
#define RSRTX_ATTR_MILSTD_TRIGGER_MESSAGE_ERROR_BIT_STATUS                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1255
#define RSRTX_ATTR_MILSTD_TRIGGER_SERVICE_REQUEST_BIT_STATUS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1256
#define RSRTX_ATTR_MILSTD_TRIGGER_SUBSYSTEM_BIT_STATUS                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1257
#define RSRTX_ATTR_MILSTD_TRIGGER_TERMINAL_BIT_STATUS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1258
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_CONDITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1259
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_MINIMUM                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1260
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_MAXIMUM                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1261
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_OFFSET_CONDITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1262
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_OFFSET                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1263
#define RSRTX_ATTR_MILSTD_TRIGGER_DATA_OFFSET_WORDS                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1264
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_TYPE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1389
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_WORD_TYPE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1390
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_ERROR_CODING_ERROR             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1367
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_ERROR_PARITY_ERROR             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1368
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_ERROR_GAP_ERROR                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1391
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_DATA_SDI                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1359
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_DATA_SSM                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1360
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_DATA_FORMAT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1392
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_PATTERN_CONDITION        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1361
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_PATTERN_MIN              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1362
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_LABEL_PATTERN_MAX              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1363
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_DATA_PATTERN_CONDITION         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1393
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_DATA_PATTERN_MIN               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1365
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_DATA_PATTERN_MAX               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1366
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_DATA_OFFSET                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1394
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_DATA_SIZE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1395
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_TIMING_CONDITION               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1364
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_TIMING_MIN                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1396
#define RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_TIMING_MAX                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1397
#define RSRTX_ATTR_RUN_SINGLE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 130
#define RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1563
#define RSRTX_ATTR_RUN_CONTINUOUS                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 131
#define RSRTX_ATTR_STOP                                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 132
#define RSRTX_ATTR_SEND_SW_TRIGGER                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 134
#define RSRTX_ATTR_ACQUISITION_STATE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1710
#define RSRTX_ATTR_WAVEFROM_EXPORT_NAME                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1853
#define RSRTX_ATTR_WAVEFORM_EXPORT_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1854
#define RSRTX_ATTR_WAVEFORM_EXPORT_SAVE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1855
#define RSRTX_ATTR_WAVEFORM_SAMPLES                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 500
#define RSRTX_ATTR_WAVEFORM_CONVERSION_X_START                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 744
#define RSRTX_ATTR_WAVEFORM_CONVERSION_X_INCREMENT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 745
#define RSRTX_ATTR_WAVEFORM_CONVERSION_Y_START                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 746
#define RSRTX_ATTR_WAVEFORM_CONVERSION_Y_INCREMENT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 747
#define RSRTX_ATTR_WAVEFORM_CONVERSION_Y_RESOLUTION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 748
#define RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_X_START                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 749
#define RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_X_INCREMENT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 750
#define RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_START                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 751
#define RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_INCREMENT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 752
#define RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_RESOLUTION                RS_SPECIFIC_PUBLIC_ATTR_BASE + 753
#define RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_X_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 754
#define RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_X_INCREMENT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 755
#define RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 756
#define RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_INCREMENT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 757
#define RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_RESOLUTION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 758
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_X_START                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1714
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_X_INCREMENT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1715
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_START                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1716
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_INCREMENT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1717
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_RESOLUTION             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1718
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_X_START                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 759
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_X_INCREMENT                RS_SPECIFIC_PUBLIC_ATTR_BASE + 760
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_START                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 761
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_INCREMENT                RS_SPECIFIC_PUBLIC_ATTR_BASE + 762
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_RESOLUTION               RS_SPECIFIC_PUBLIC_ATTR_BASE + 763
#define RSRTX_ATTR_MASK_DATA_CONVERSION_X_START                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1331
#define RSRTX_ATTR_MASK_DATA_CONVERSION_X_INCREMENT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1332
#define RSRTX_ATTR_MASK_DATA_CONVERSION_Y_START                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1333
#define RSRTX_ATTR_MASK_DATA_CONVERSION_Y_INCREMENT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1334
#define RSRTX_ATTR_MASK_DATA_CONVERSION_Y_RESOLUTION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1335
#define RSRTX_ATTR_LOGIC_DATA_CONVERSION_X_START                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1767
#define RSRTX_ATTR_LOGIC_DATA_CONVERSION_X_INCREMENT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1768
#define RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_START                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1769
#define RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_INCREMENT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1770
#define RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_RESOLUTION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1771
#define RSRTX_ATTR_DIGITAL_WAVEFORM_SAMPLES                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1949
#define RSRTX_ATTR_DIGITAL_DATA_CONVERSION_X_START                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1926
#define RSRTX_ATTR_DIGITAL_DATA_CONVERSION_X_INCREMENT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1927
#define RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_START                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1928
#define RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_INCREMENT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1929
#define RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_RESOLUTION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1930
#define RSRTX_ATTR_SPECTRUM_WAVEFORM_SAMPLES                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1950
#define RSRTX_ATTR_SPECTRUM_MINIMUM_WAVEFORM_SAMPLES                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1953
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_WAVEFORM_SAMPLES                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1956
#define RSRTX_ATTR_SPECTRUM_AVERAGE_WAVEFORM_SAMPLES                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1959
#define RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_X_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1962
#define RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_X_INCREMENT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1963
#define RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1964
#define RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_INCREMENT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1965
#define RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_RESOLUTION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1966
#define RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_X_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1967
#define RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_X_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1968
#define RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1969
#define RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1970
#define RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_RESOLUTION            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1971
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_X_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1972
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_X_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1973
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1974
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1975
#define RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_RESOLUTION            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1976
#define RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_X_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1977
#define RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_X_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1978
#define RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_Y_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1979
#define RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_Y_INCREMENT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1980
#define RSRTX_ATTR_SPECTRUM_AVERAVE_DATA_CONVERSION_Y_RESOLUTION            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1981
#define RSRTX_ATTR_CURSOR_ENABLED                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 173
#define RSRTX_ATTR_ALL_CURSORS_OFF                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 174
#define RSRTX_ATTR_CURSOR_MEASUREMENT_TYPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 175
#define RSRTX_ATTR_CURSOR_SOURCE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 176
#define RSRTX_ATTR_CURSOR_SECOND_SOURCE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1982
#define RSRTX_ATTR_CURSOR_SECOND_SOURCE_ENABLE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1983
#define RSRTX_ATTR_CURSOR_TRACKING                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 177
#define RSRTX_ATTR_CURSOR_X_POSITION_COUPLING                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 179
#define RSRTX_ATTR_CURSOR_Y_POSITION_COUPLING                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 181
#define RSRTX_ATTR_CURSOR_ADJUSTMENT                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 507
#define RSRTX_ATTR_CURSOR_X_RATIO_MEASUREMENT_UNIT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 187
#define RSRTX_ATTR_CURSOR_Y_RATIO_MEASUREMENT_UNIT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 189
#define RSRTX_ATTR_CURSOR_X_RATIO_MEASUREMENT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 188
#define RSRTX_ATTR_CURSOR_Y_RATIO_MEASUREMENT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 190
#define RSRTX_ATTR_CURSOR_DISTANCE_HORIZONTAL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 183
#define RSRTX_ATTR_CURSOR_DISTANCE_VERTICAL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 779
#define RSRTX_ATTR_CURSOR_INVERSE_DISTANCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 184
#define RSRTX_ATTR_CURSOR_VOLTAGE_INVERSE_DISTANCE_VERTICAL                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 780
#define RSRTX_ATTR_CURSOR_POSITION                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 506
#define RSRTX_ATTR_CURSOR_AUTOSET                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 647
#define RSRTX_ATTR_CURSOR_RESET                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 648
#define RSRTX_ATTR_CURSOR_PEAK_NEXT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 649
#define RSRTX_ATTR_CURSOR_PEAK_PREVIOUS                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 650
#define RSRTX_ATTR_CURSOR_X1_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 178
#define RSRTX_ATTR_CURSOR_X2_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 781
#define RSRTX_ATTR_CURSOR_X3_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 782
#define RSRTX_ATTR_CURSOR_Y1_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 180
#define RSRTX_ATTR_CURSOR_Y2_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 783
#define RSRTX_ATTR_CURSOR_Y3_POSITION                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 784
#define RSRTX_ATTR_CURSOR_LINE_NEXT_PEAK                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1719
#define RSRTX_ATTR_CURSOR_LINE_PREVIOUS_PEAK                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1720
#define RSRTX_ATTR_MEAS_RELATIVE_MODE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 619
#define RSRTX_ATTR_MEAS_RELATIVE_LOWER_LEVEL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 620
#define RSRTX_ATTR_MEAS_RELATIVE_UPPER_LEVEL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 621
#define RSRTX_ATTR_MEAS_RELATIVE_MIDDLE_LEVEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 622
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FREQUENCY                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 979
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PERIOD                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 980
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PEAK                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 981
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MAXIMUM_PEAK                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 982
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MINIMUM_PEAK                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 983
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_PULSES                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 984
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_PULSES                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 985
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RISING_EDGES                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 986
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FALLING_EDGES                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 987
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_HIGH_LEVEL                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 988
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_LOW_LEVEL                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 989
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_AMPLITUDE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 990
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MEAN                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 991
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RMS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 992
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RISE_TIME                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 993
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FALLING_TIME                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 994
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_CYCLE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1005
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_CYCLE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1006
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_WIDTH_POSITIVE_PULSE             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1007
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_WIDTH_NEGATIVE_PULSE             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1008
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MEAN_VALUE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1009
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RMS_VALUE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1010
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_STANDARD_DEVIATIONS              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1011
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_STANDARD_DEVIATION_VALUE         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1012
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_DELAY                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1015
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PHASE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1016
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_BURST_WIDTH                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1017
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_OVERSHOOT               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1018
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_OVERSHOOT               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1019
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_AVERAGE_VALUE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 508
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_STANDARD_DEVIATION               RS_SPECIFIC_PUBLIC_ATTR_BASE + 775
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_PEAK                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 776
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_PEAK                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 777
#define RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_WAVEFORM_COUNT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 778
#define RSRTX_ATTR_AMPT_MAIN_MEASUREMENT                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 147
#define RSRTX_ATTR_MEASUREMENT_DELAY_MARKER_VISIBLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2150
#define RSRTX_ATTR_MEASUREMENT_ENABLED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 136
#define RSRTX_ATTR_MEASUREMENT_CATEGORY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 138
#define RSRTX_ATTR_QUICK_MEASUREMENTS_ENABLE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 139
#define RSRTX_ATTR_QUICK_MEASUREMENTS_DISABLE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 140
#define RSRTX_ATTR_QUICK_MEASUREMENTS_ENABLE_WITH_STATUS_BIT                RS_SPECIFIC_PUBLIC_ATTR_BASE + 668
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_ENABLED                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 651
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_NUMBER_OF_WAVEFORMS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 652
#define RSRTX_ATTR_RESET_AUTOMATIC_MEASUREMENT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 653
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_NUMBER_OF_MEASURED_WAVEFORMS       RS_SPECIFIC_PUBLIC_ATTR_BASE + 666
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT_AUTO                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2152
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 2153
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_AVERAGE_VALUE               RS_SPECIFIC_PUBLIC_ATTR_BASE + 654
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_STANDARD_DEVIATION          RS_SPECIFIC_PUBLIC_ATTR_BASE + 785
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_NEGATIVE_PEAK               RS_SPECIFIC_PUBLIC_ATTR_BASE + 786
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_POSITIVE_PEAK               RS_SPECIFIC_PUBLIC_ATTR_BASE + 787
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_INDEX                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 764
#define RSRTX_ATTR_AUTOMATIC_MEASUREMENT_SINGLE_STATISTICAL_VALUE           RS_SPECIFIC_PUBLIC_ATTR_BASE + 765
#define RSRTX_ATTR_EXPORT_AUTOMATIC_MEASUREMENTS_NAME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1582
#define RSRTX_ATTR_EXPORT_AUTOMATIC_MEASUREMENT_SAVE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1583
#define RSRTX_ATTR_EXPORT_AUTOMATIC_MEASUREMENTS_ALL_NAME                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1584
#define RSRTX_ATTR_EXPORT_AUTOMATIC_MEASUREMENT_ALL_SAVE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1585
#define RSRTX_ATTR_MEASUREMENT_GATE_ENABLE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1984
#define RSRTX_ATTR_MEASUREMENT_GATE_MODE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1985
#define RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_START                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1986
#define RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_END                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1987
#define RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_START                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1988
#define RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_END                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1989
#define RSRTX_ATTR_MATH_WAVEFORM_HEADER                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 337
#define RSRTX_ATTR_MATH_WAVEFORM_DATA_POINTS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1586
#define RSRTX_ATTR_MATH_WAVEFORM_ENABLED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 235
#define RSRTX_ATTR_MATH_WAVEFORM_POSITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 623
#define RSRTX_ATTR_MATH_VERTICAL_SCALE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 624
#define RSRTX_ATTR_MATH_ACQUISITION_TYPE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 236
#define RSRTX_ATTR_MATH_EXPRESSION                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 237
#define RSRTX_ATTR_MATH_WAVEFORM_LABEL                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1990
#define RSRTX_ATTR_MATH_WAVEFORM_LABEL_STATE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1991
#define RSRTX_ATTR_MATH_WAVEFORM_COLOR                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1992
#define RSRTX_ATTR_FFT_CENTER_FREQUENCY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 241
#define RSRTX_ATTR_FFT_FREQUENCY_SPAN                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 242
#define RSRTX_ATTR_FFT_FULL_SPAN                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 243
#define RSRTX_ATTR_FFT_START_FREQUENCY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 244
#define RSRTX_ATTR_FFT_STOP_FREQUENCY                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 245
#define RSRTX_ATTR_FFT_AVERAGING                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 509
#define RSRTX_ATTR_FFT_AVERAGING_STATUS                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1560
#define RSRTX_ATTR_FFT_WINDOW_TYPE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 246
#define RSRTX_ATTR_FFT_RESOLUTION_BANDWIDTH                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 254
#define RSRTX_ATTR_FFT_RESOLUTION_BANDWIDTH_COUPLING_ENABLED                RS_SPECIFIC_PUBLIC_ATTR_BASE + 255
#define RSRTX_ATTR_FFT_RESOLUTION_BANDWIDTH_RATIO                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 256
#define RSRTX_ATTR_FFT_EFFECTIVE_RESOLUTION_BANDWIDTH                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 257
#define RSRTX_ATTR_FFT_SCALING_UNIT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 625
#define RSRTX_ATTR_FFT_SAMPLE_RATE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 655
#define RSRTX_ATTR_FFT_YT_WINDOW_POSITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 669
#define RSRTX_ATTR_FFT_YT_WINDOW_WIDTH                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 670
#define RSRTX_ATTR_MATH_TRACK_EDGE_POLARITY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1993
#define RSRTX_ATTR_MATH_TRACK_DOUBLE_PULSE_ENABLE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1994
#define RSRTX_ATTR_MATH_TRACK_THRESHOLD_HYSTERESIS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1995
#define RSRTX_ATTR_MATH_TRACK_THRESHOLD_LOWER                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1996
#define RSRTX_ATTR_MATH_TRACK_THRESHOLD_UPPER                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1997
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_ENABLED                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1721
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_POSITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1722
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_VERTICAL_SCALE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1723
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_OPERATION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1724
#define RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_SOURCE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1725
#define RSRTX_ATTR_REFERENCE_WAVEFORM_HEADER                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 511
#define RSRTX_ATTR_REFERENCE_WAVEFORM_DATA_POINTS                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1587
#define RSRTX_ATTR_REFERENCE_WAVEFORM_LABEL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1998
#define RSRTX_ATTR_REFERENCE_WAVEFORM_COLOR                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1999
#define RSRTX_ATTR_REFERENCE_WAVEFORM_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 270
#define RSRTX_ATTR_REFERENCE_WAVEFORM_UPDATE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 276
#define RSRTX_ATTR_REFERENCE_WAVEFORM_DISPLAY_ENABLED                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 271
#define RSRTX_ATTR_REFERENCE_WAVEFORM_LOAD_FROM_FILE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 512
#define RSRTX_ATTR_REFERENCE_WAVEFORM_LOAD_CONFIGURATION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 513
#define RSRTX_ATTR_REFERENCE_WAVEFORM_SAVE_TO_FILE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 514
#define RSRTX_ATTR_REFERENCE_WAVEFORM_CATALOG                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 515
#define RSRTX_ATTR_REFERENCE_WAVEFORM_VERTICAL_SCALE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 281
#define RSRTX_ATTR_REFERENCE_WAVEFORM_VERTICAL_POSITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 282
#define RSRTX_ATTR_REFERENCE_WAVEFORM_HORIZONTAL_SCALE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 516
#define RSRTX_ATTR_REFERENCE_WAVEFORM_HORIZONTAL_POSITION                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 611
#define RSRTX_ATTR_MASK_ENABLED                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 517
#define RSRTX_ATTR_MASK_SOURCE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 525
#define RSRTX_ATTR_MASK_TEST                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 526
#define RSRTX_ATTR_MASK_COPY_CHANNEL                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 518
#define RSRTX_ATTR_MASK_HIT_COUNT                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 522
#define RSRTX_ATTR_MASK_COUNT                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 521
#define RSRTX_ATTR_MASK_SEGMENT_CAPTURE_MODE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2000
#define RSRTX_ATTR_MASK_STORE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 524
#define RSRTX_ATTR_MASK_LOAD                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 523
#define RSRTX_ATTR_MASK_TEST_ACTION_BEEP                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 671
#define RSRTX_ATTR_MASK_TEST_ACTION_STOP                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 788
#define RSRTX_ATTR_MASK_TEST_ACTION_SCREENSHOT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 789
#define RSRTX_ATTR_MASK_TEST_ACTION_SCREENSHOT_DESTINATION                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1859
#define RSRTX_ATTR_MASK_TEST_ACTION_SAVES_WAVEFORM                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 791
#define RSRTX_ATTR_MASK_TEST_ACTION_SAVES_WAVEFORM_DESTINATION              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1860
#define RSRTX_ATTR_MASK_TEST_ACTION_PULSE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1173
#define RSRTX_ATTR_MASK_TEST_ACTION_AUX_OUTPUT_ENABLED                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1861
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_BEEP                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 672
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_STOP                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 792
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_SCREENSHOT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 793
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_PRINT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 794
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_SAVES_WAVEFORM                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 795
#define RSRTX_ATTR_MASK_TEST_VIOLATION_COUNT_PULSE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1174
#define RSRTX_ATTR_MASK_TEST_VIOLATION_PULSE_LENGTH                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1175
#define RSRTX_ATTR_MASK_TEST_VIOLATION_PULSE_POLARITY                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1176
#define RSRTX_ATTR_MASK_RESET_TEST_COUNTER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 673
#define RSRTX_ATTR_MASK_VERTICAL_OFFSET                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 519
#define RSRTX_ATTR_MASK_VERTICAL_SCALING                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 520
#define RSRTX_ATTR_MASK_VERTICAL_WIDTH                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 528
#define RSRTX_ATTR_MASK_HORIZONTAL_WIDTH                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 527
#define RSRTX_ATTR_SEARCH_ENABLED                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 626
#define RSRTX_ATTR_SEARCH_CONDITION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 627
#define RSRTX_ATTR_SEARCH_SOURCE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 628
#define RSRTX_ATTR_SEARCH_TRIGGER_EDGE_SLOPE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 629
#define RSRTX_ATTR_SEARCH_TRIGGER_EDGE_LEVEL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 630
#define RSRTX_ATTR_SEARCH_TRIGGER_EDGE_HYSTERSIS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 631
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_LEVEL                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 632
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_HYSTERSIS                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 633
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_WIDTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 634
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_DELTA                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 635
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_POLARITY                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 636
#define RSRTX_ATTR_SEARCH_TRIGGER_WIDTH_RANGE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 637
#define RSRTX_ATTR_SEARCH_TRIGGER_PEAK_POLARITY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 638
#define RSRTX_ATTR_SEARCH_TRIGGER_PEAK_LIMIT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 639
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_POLARITY                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 656
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_LEVEL_LOWER                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 657
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_LEVEL_UPPER                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 796
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_RANGE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 658
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_REFERENCE_TIME                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 659
#define RSRTX_ATTR_SEARCH_TRIGGER_RISE_TIME_DELTA_TIME                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 660
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_POLARITY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 661
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_LEVEL_LOWER                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 662
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_LEVEL_UPPER                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 797
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_RANGE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 663
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_WIDTH                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 664
#define RSRTX_ATTR_SEARCH_TRIGGER_RUNT_DELTA_WIDTH                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 665
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_CLOCK_SOURCE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 674
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_CLOCK_LEVEL                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 675
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_DATA_LEVEL                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 798
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_CLOCK_HYSTERESIS                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 676
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_DATA_HYSTERESIS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 799
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_POLARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 677
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_SETUP_TIME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 678
#define RSRTX_ATTR_SEARCH_TRIGGER_D2C_HOLD_TIME                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 679
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 680
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_COMBINATION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 681
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_COMPARISON                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 682
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_WIDTH                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 683
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_WIDTH_DELTA                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 684
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_LEVEL_LOWER                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1862
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_LEVEL_UPPER                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1863
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_DELTA                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1864
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_POLARITY                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1865
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_RANGE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1866
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_TIME_RANGE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1867
#define RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_WIDTH                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1868
#define RSRTX_ATTR_SEARCH_GATE_MODE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 690
#define RSRTX_ATTR_SEARCH_GATE_START                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 691
#define RSRTX_ATTR_SEARCH_GATE_STOP                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 692
#define RSRTX_ATTR_SEARCH_SHOW_RESULT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 640
#define RSRTX_ATTR_SEARCH_NUMBER_OF_RESULTS                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 641
#define RSRTX_ATTR_SEARCH_MAXIMUM_NUMBER_OF_RESULTS                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1425
#define RSRTX_ATTR_SEARCH_EXPORT_NAME                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1869
#define RSRTX_ATTR_SEARCH_EXPORT_SAVE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1870
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_LEVEL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 685
#define RSRTX_ATTR_SEARCH_TRIGGER_PATTERN_HYSTERESIS                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 686
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_EVENT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 712
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_FRAME_SETUP                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 713
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_CONDITION_ID                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 714
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_CONDITION_DATA                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 808
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_ID_PATTERN                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 715
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_DATA_LENGTH                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 716
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_DATA_PATTERN                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 717
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_ERROR_CHECKSUM                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 718
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_ERROR_PARITY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 809
#define RSRTX_ATTR_PROTOCOL_LIN_SEARCH_ERROR_SYNC                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 810
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_EVENT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 732
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_FRAME_SETUP                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 733
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_FRAME_TYPE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 734
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ID_TYPE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 735
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_CONDITION_ID                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 736
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_CONDITION_DATA                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 815
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ID_PATTERN                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 737
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_DATA_LENGTH                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 738
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_DATA_PATTERN                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 739
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ERROR_CRC                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 740
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ERROR_STUFFING                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 816
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ERROR_FORM                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 817
#define RSRTX_ATTR_PROTOCOL_CAN_SEARCH_ERROR_ACK                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 818
#define RSRTX_ATTR_MILSTD_SEARCH_CONDITION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1290
#define RSRTX_ATTR_MILSTD_SEARCH_WORD_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1426
#define RSRTX_ATTR_MILSTD_SEARCH_ERROR                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1291
#define RSRTX_ATTR_MILSTD_SEARCH_TRANSMISSION_TYPE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1427
#define RSRTX_ATTR_MILSTD_SEARCH_COMMAND_DATA_DIRECTION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1265
#define RSRTX_ATTR_MILSTD_SEARCH_RT_ADDRESS_CONDITION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1266
#define RSRTX_ATTR_MILSTD_SEARCH_RT_ADDRESS_MINIMUM                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1267
#define RSRTX_ATTR_MILSTD_SEARCH_RT_ADDRESS_MAXIMUM                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1268
#define RSRTX_ATTR_MILSTD_SEARCH_SUB_ADDRESS_CONDITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1269
#define RSRTX_ATTR_MILSTD_SEARCH_SUB_ADDRESS_MINIMUM                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1270
#define RSRTX_ATTR_MILSTD_SEARCH_SUB_ADDRESS_MAXIMUM                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1271
#define RSRTX_ATTR_MILSTD_SEARCH_SUB_ADDRESS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1272
#define RSRTX_ATTR_MILSTD_SEARCH_WORD_CONDITION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1273
#define RSRTX_ATTR_MILSTD_SEARCH_WORD_MINIMUM                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1274
#define RSRTX_ATTR_MILSTD_SEARCH_WORD_MAXIMUM                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1275
#define RSRTX_ATTR_MILSTD_SEARCH_COMMAND_MODE_CODE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1276
#define RSRTX_ATTR_MILSTD_SEARCH_RECEIVED_BIT_STATUS                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1277
#define RSRTX_ATTR_MILSTD_SEARCH_BUSY_BIT_STATUS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1278
#define RSRTX_ATTR_MILSTD_SEARCH_BUS_CONTROL_BIT_STATUS                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1279
#define RSRTX_ATTR_MILSTD_SEARCH_INSTRUMENTATION_BIT_STATUS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1280
#define RSRTX_ATTR_MILSTD_SEARCHMESSAGE_ERROR_BIT_STATUS                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1281
#define RSRTX_ATTR_MILSTD_SEARCH_SERVICE_REQUEST_BIT_STATUS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1282
#define RSRTX_ATTR_MILSTD_SEARCH_SUBSYSTEM_BIT_STATUS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1283
#define RSRTX_ATTR_MILSTD_SEARCH_TERMINAL_BIT_STATUS                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1284
#define RSRTX_ATTR_MILSTD_SEARCH_DATA_CONDITION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1285
#define RSRTX_ATTR_MILSTD_SEARCH_DATA_MINIMUM                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1286
#define RSRTX_ATTR_MILSTD_SEARCH_DATA_MAXIMUM                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1287
#define RSRTX_ATTR_MILSTD_SEARCH_DATA_OFFSET                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1288
#define RSRTX_ATTR_MILSTD_SEARCH_DATA_OFFSET_WORDS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1289
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_TYPE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1398
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_WORD_TYPE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1399
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_ERROR                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1400
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_LABEL_PATTERN_CONDITION         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1401
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_LABEL_PATTERN_MIN               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1402
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_LABEL_PATTERN_MAX               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1403
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_PATTERN_CONDITION          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1404
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_PATTERN_MIN                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1405
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_PATTERN_MAX                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1406
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_OFFSET                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1407
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_SIZE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1408
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_DATA_FORMAT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1409
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_SDI                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1410
#define RSRTX_ATTR_PROTOCOL_ARINC429_SEARCH_SSM                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1411
#define RSRTX_ATTR_PROTOCOL_ENABLED                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 577
#define RSRTX_ATTR_PROTOCOL_TYPE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 578
#define RSRTX_ATTR_BUS_SAVE_DECODED_DATA                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 695
#define RSRTX_ATTR_PROTOCOL_CONTENT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 867
#define RSRTX_ATTR_PROTOCOL_DISPLAY_FORMAT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 579
#define RSRTX_ATTR_PROTOCOL_DISPLAY_HEIGHT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 580
#define RSRTX_ATTR_PROTOCOL_DISPLAY_LINES                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 581
#define RSRTX_ATTR_PROTOCOL_DISPLAY_VERTICAL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 582
#define RSRTX_ATTR_PROTOCOL_DISPLAY_RESULTS                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 868
#define RSRTX_ATTR_PROTOCOL_I2C_CLOCK_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 350
#define RSRTX_ATTR_PROTOCOL_I2C_DATA_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 800
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 696
#define RSRTX_ATTR_PROTOCOL_I2C_SELECTED_FRAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 869
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_DATA                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 870
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_STATUS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 871
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 872
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 873
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_TRANSFER_DIRECTION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 874
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_ACKNOWLEDGE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 875
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_ENABLED                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 876
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_START_ACK_BIT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 877
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 878
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_WITHOUT_BIT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 879
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_LENGTH                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 880
#define RSRTX_ATTR_PROTOCOL_I2C_FRAME_ADDRESS_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 881
#define RSRTX_ATTR_PROTOCOL_I2C_SELECTED_BYTE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 882
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_COUNT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 883
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_ACK_BIT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 884
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_ACK_BIT_START                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 885
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_ENABLED                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 886
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_START                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 887
#define RSRTX_ATTR_PROTOCOL_I2C_BYTE_VALUE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 888
#define RSRTX_ATTR_PROTOCOL_SPI_CLOCK_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 382
#define RSRTX_ATTR_PROTOCOL_SPI_DATA_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 819
#define RSRTX_ATTR_PROTOCOL_SPI_MISO_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2001
#define RSRTX_ATTR_PROTOCOL_SPI_CLOCK_POLARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 383
#define RSRTX_ATTR_PROTOCOL_SPI_CS_POLARITY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1726
#define RSRTX_ATTR_PROTOCOL_SPI_CS_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2002
#define RSRTX_ATTR_PROTOCOL_SPI_DATA_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 820
#define RSRTX_ATTR_PROTOCOL_SPI_BIT_ORDER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 380
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_LENGTH                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 381
#define RSRTX_ATTR_PROTOCOL_SPI_MOSI_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2003
#define RSRTX_ATTR_PROTOCOL_SPI_MISO_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2004
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 698
#define RSRTX_ATTR_PROTOCOL_SPI_SELECTED_FRAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 889
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_STATUS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 890
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 891
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 892
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_DATA_MOSI                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 893
#define RSRTX_ATTR_PROTOCOL_SPI_FRAME_DATA_MISO                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 894
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_COUNT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 895
#define RSRTX_ATTR_PROTOCOL_SPI_SELECTED_WORD                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 896
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_START                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 897
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_END                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 898
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_MOSI                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 899
#define RSRTX_ATTR_PROTOCOL_SPI_WORD_MISO                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 900
#define RSRTX_ATTR_PROTOCOL_SSPI_CLOCK_SOURCE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 609
#define RSRTX_ATTR_PROTOCOL_SSPI_DATA_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 801
#define RSRTX_ATTR_PROTOCOL_SSPI_MISO_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2005
#define RSRTX_ATTR_PROTOCOL_SSPI_CLOCK_POLARITY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 594
#define RSRTX_ATTR_PROTOCOL_SSPI_DATA_POLARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 802
#define RSRTX_ATTR_PROTOCOL_SSPI_INTERFRAME_TIME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 597
#define RSRTX_ATTR_PROTOCOL_SSPI_BIT_ORDER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 598
#define RSRTX_ATTR_PROTOCOL_SSPI_WORD_LENGTH                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 599
#define RSRTX_ATTR_PROTOCOL_SSPI_MOSI_POLARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2006
#define RSRTX_ATTR_PROTOCOL_SSPI_MISO_POLARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2007
#define RSRTX_ATTR_PROTOCOL_UART_SOURCE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 600
#define RSRTX_ATTR_PROTOCOL_UART_RX_SOURCE_LINE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 699
#define RSRTX_ATTR_PROTOCOL_UART_TX_SOURCE_LINE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 804
#define RSRTX_ATTR_PROTOCOL_UART_POLARITY                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 601
#define RSRTX_ATTR_PROTOCOL_UART_IDLE_STATE_POLARITY                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2008
#define RSRTX_ATTR_PROTOCOL_UART_INTERFRAME_TIME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 605
#define RSRTX_ATTR_PROTOCOL_UART_WORD_LENGTH                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 606
#define RSRTX_ATTR_PROTOCOL_UART_BIT_RATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 604
#define RSRTX_ATTR_PROTOCOL_UART_PARITY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 405
#define RSRTX_ATTR_PROTOCOL_UART_STOP_BITS                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 603
#define RSRTX_ATTR_PROTOCOL_UART_FRAME_COUNT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1727
#define RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_COUNT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 701
#define RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_COUNT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 803
#define RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 901
#define RSRTX_ATTR_PROTOCOL_UART_FRAME_STATE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2009
#define RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_STATE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2010
#define RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_STATE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2011
#define RSRTX_ATTR_PROTOCOL_UART_FRAME_START                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2012
#define RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_START                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2013
#define RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_START                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2014
#define RSRTX_ATTR_PROTOCOL_UART_FRAME_END                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2015
#define RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_END                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2016
#define RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_END                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2017
#define RSRTX_ATTR_PROTOCOL_UART_WORD_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1728
#define RSRTX_ATTR_PROTOCOL_UART_RX_WORD_COUNT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 902
#define RSRTX_ATTR_PROTOCOL_UART_TX_WORD_COUNT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 903
#define RSRTX_ATTR_PROTOCOL_UART_SELECTED_WORD                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 904
#define RSRTX_ATTR_PROTOCOL_UART_WORD_VALUE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1729
#define RSRTX_ATTR_PROTOCOL_UART_RX_WORD_VALUE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 921
#define RSRTX_ATTR_PROTOCOL_UART_TX_WORD_VALUE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 922
#define RSRTX_ATTR_PROTOCOL_UART_WORD_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1730
#define RSRTX_ATTR_PROTOCOL_UART_RX_WORD_START                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 923
#define RSRTX_ATTR_PROTOCOL_UART_TX_WORD_START                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 924
#define RSRTX_ATTR_PROTOCOL_UART_WORD_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1731
#define RSRTX_ATTR_PROTOCOL_UART_RX_WORD_END                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 925
#define RSRTX_ATTR_PROTOCOL_UART_TX_WORD_END                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 926
#define RSRTX_ATTR_PROTOCOL_UART_WORD_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1732
#define RSRTX_ATTR_PROTOCOL_UART_RX_WORD_ENABLED                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 927
#define RSRTX_ATTR_PROTOCOL_UART_TX_WORD_ENABLED                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 928
#define RSRTX_ATTR_PROTOCOL_UART_WORD_SOURCE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1733
#define RSRTX_ATTR_PROTOCOL_LIN_SOURCE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 702
#define RSRTX_ATTR_PROTOCOL_LIN_POLARITY                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 741
#define RSRTX_ATTR_PROTOCOL_LIN_STANDARD                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 703
#define RSRTX_ATTR_PROTOCOL_LIN_BIT_RATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 704
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 711
#define RSRTX_ATTR_PROTOCOL_LIN_SELECTED_FRAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 905
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_DATA                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 906
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_STATUS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 907
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 908
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 909
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_CHECKSUM_ENABLED                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 910
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_CHECKSUM_VALUE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 911
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_PARITY_ENABLED                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 912
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_PARITY_VALUE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 913
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_ID_VALUE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 914
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_SYNC_ENABLED                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 915
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_SYNC_VALUE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 916
#define RSRTX_ATTR_PROTOCOL_LIN_FRAME_VERSION                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 917
#define RSRTX_ATTR_PROTOCOL_LIN_BYTE_COUNT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 918
#define RSRTX_ATTR_PROTOCOL_LIN_SELECTED_BYTE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1022
#define RSRTX_ATTR_PROTOCOL_LIN_BYTE_ENABLED                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 919
#define RSRTX_ATTR_PROTOCOL_LIN_BYTE_VALUE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 920
#define RSRTX_ATTR_PROTOCOL_CAN_LINE_TYPE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 719
#define RSRTX_ATTR_PROTOCOL_CAN_SOURCE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 720
#define RSRTX_ATTR_PROTOCOL_CAN_BIT_RATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 721
#define RSRTX_ATTR_PROTOCOL_CAN_SAMPLE_POINT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 722
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 731
#define RSRTX_ATTR_PROTOCOL_CAN_SELECTED_FRAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 929
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_TYPE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 930
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_STATUS                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 931
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 932
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 933
#define RSRTX_ATTR_PROTOCOL_CAN_FRAME_DATA                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 934
#define RSRTX_ATTR_PROTOCOL_CAN_ACK_STATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 935
#define RSRTX_ATTR_PROTOCOL_CAN_ACK_VALUE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 936
#define RSRTX_ATTR_PROTOCOL_CAN_CHECKSUM_STATE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 937
#define RSRTX_ATTR_PROTOCOL_CAN_CHECKSUM_VALUE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 938
#define RSRTX_ATTR_PROTOCOL_CAN_DATA_LENGTH_STATE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 939
#define RSRTX_ATTR_PROTOCOL_CAN_DATA_LENGTH_VALUE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 940
#define RSRTX_ATTR_PROTOCOL_CAN_ID_STATE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 941
#define RSRTX_ATTR_PROTOCOL_CAN_ID_VALUE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 942
#define RSRTX_ATTR_PROTOCOL_CAN_ID_TYPE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 943
#define RSRTX_ATTR_PROTOCOL_CAN_BSE_POSITION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 944
#define RSRTX_ATTR_PROTOCOL_CAN_BYTE_COUNT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 945
#define RSRTX_ATTR_PROTOCOL_CAN_SELECTED_BYTE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 946
#define RSRTX_ATTR_PROTOCOL_CAN_BYTE_STATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 947
#define RSRTX_ATTR_PROTOCOL_CAN_BYTE_VALUE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 948
#define RSRTX_ATTR_PARALLEL_BUS_ANALYZED_LINES                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 608
#define RSRTX_ATTR_PARALLEL_BUS_FRAME_COUNT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 846
#define RSRTX_ATTR_PARALLEL_BUS_SELECTED_FRAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 857
#define RSRTX_ATTR_PARALLEL_BUS_FRAME_DATA                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 858
#define RSRTX_ATTR_PARALLEL_BUS_FRAME_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 859
#define RSRTX_ATTR_PARALLEL_BUS_FRAME_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 860
#define RSRTX_ATTR_PARALLEL_BUS_FRAME_END                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 861
#define RSRTX_ATTR_PARALLEL_BUS_BIT_SOURCE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2018
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_ANALYZED_LINES                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 847
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_FRAME_COUNT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 848
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_SLOPE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 849
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_CS_POLARITY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 850
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_SELECTED_FRAME                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 862
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_FRAME_DATA                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 863
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_FRAME_ENABLED                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 864
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_FRAME_START                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 865
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_FRAME_END                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 866
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_SOURCE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1588
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_CHIP_SELECT_ENABLED                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1589
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_CHIP_SELECT_SOURCE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1590
#define RSRTX_ATTR_PARALLEL_BUS_CLOCKED_BIT_SOURCE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2019
#define RSRTX_ATTR_PROTOCOL_AUDIO_VARIANT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1111
#define RSRTX_ATTR_PROTOCOL_AUDIO_WORD_LENGTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1113
#define RSRTX_ATTR_PROTOCOL_AUDIO_CHANNEL_ORDER                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1114
#define RSRTX_ATTR_PROTOCOL_AUDIO_BIT_ORDER                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1115
#define RSRTX_ATTR_PROTOCOL_AUDIO_CHANNEL_OFFSET                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1116
#define RSRTX_ATTR_PROTOCOL_AUDIO_CHANNEL_LENGTH                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1117
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_OFFSET                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1118
#define RSRTX_ATTR_PROTOCOL_AUDIO_TDM_CHANNELS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1119
#define RSRTX_ATTR_PROTOCOL_AUDIO_SELECTED_FRAME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1120
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1121
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_STATUS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1122
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_START                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1123
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_STOP                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1124
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_LEFT_CHANNEL_STATUS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1125
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_RIGHT_CHANNEL_STATUS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1126
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_LEFT_CHANNEL_VALUE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1127
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_RIGHT_CHANNEL_VALUE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1128
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_TDM_STATUS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1131
#define RSRTX_ATTR_PROTOCOL_AUDIO_FRAME_TDM_VALUE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1132
#define RSRTX_ATTR_PROTOCOL_AUDIO_CLOCK_SOURCE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1133
#define RSRTX_ATTR_PROTOCOL_AUDIO_CLOCK_THRESHOLD                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1134
#define RSRTX_ATTR_PROTOCOL_AUDIO_CLOCK_POLARITY                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1135
#define RSRTX_ATTR_PROTOCOL_AUDIO_WS_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1136
#define RSRTX_ATTR_PROTOCOL_AUDIO_WS_THRESHOLD                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1137
#define RSRTX_ATTR_PROTOCOL_AUDIO_WS_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1138
#define RSRTX_ATTR_PROTOCOL_AUDIO_DATA_SOURCE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1139
#define RSRTX_ATTR_PROTOCOL_AUDIO_DATA_THRESHOLD                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1140
#define RSRTX_ATTR_PROTOCOL_AUDIO_DATA_POLARITY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1141
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_DISPLAY_MODE               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1151
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_LEFT_POSITION              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1152
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_LEFT_SCALE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1153
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_RIGHT_POSITION             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1154
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_RIGHT_SCALE                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1155
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_DEFAULT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1159
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_SCREEN              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1161
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_CHANNEL_ENABLED            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1156
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_CHANNEL_POSITION           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1142
#define RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_CHANNEL_SCALE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1157
#define RSRTX_ATTR_PROTOCOL_MILSTD_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1200
#define RSRTX_ATTR_PROTOCOL_MILSTD_POLARITY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1201
#define RSRTX_ATTR_PROTOCOL_MILSTD_TRESHOLD_HIGH                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1202
#define RSRTX_ATTR_PROTOCOL_MILSTD_TRESHOLD_HLOW                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1203
#define RSRTX_ATTR_PROTOCOL_MILSTD_TIMING                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1204
#define RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_INFINITE          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1734
#define RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_MINIMUM           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1735
#define RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_MAXIMUM           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1736
#define RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_INFINITE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1737
#define RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_MINIMUM                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1738
#define RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_MAXIMUM                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1739
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_COUNT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1205
#define RSRTX_ATTR_PROTOCOL_MILSTD_SELECTED_WORD                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1206
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_START                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1207
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_STOP                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1208
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_STATUS                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1209
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_TRANSMISSION_DIRECTION              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1210
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_TYPE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1211
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_PARITY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1219
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_RESPONSE_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1212
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_VALUE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1217
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_INTERMESSAGE_GATE_TIME              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1218
#define RSRTX_ATTR_PROTOCOL_MILSTD_COMMAND_WORD_COUNT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1229
#define RSRTX_ATTR_PROTOCOL_MILSTD_COMMAND_WORD_MODE_CODE_TYPE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1213
#define RSRTX_ATTR_PROTOCOL_MILSTD_COMMAND_WORD_MODE_CODE_VALUE             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1214
#define RSRTX_ATTR_PROTOCOL_MILSTD_COMMAND_WORD_RT_ADDRESS                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1215
#define RSRTX_ATTR_PROTOCOL_MILSTD_COMMAND_WORD_SUB_ADDRESS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1216
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_RECEIVED_BIT_STATUS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1220
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_BUSY_BIT_STATUS                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1221
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_BUS_CONTROL_BIT_STATUS              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1222
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_INSTRUMENTATION_BIT_STATUS          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1223
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_MESSAGE_ERROR_BIT_STATUS            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1224
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_STATUS_RT_ADDRESS                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1225
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_SUBSYSTEM_BIT_STATUS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1226
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_TERMINAL_BIT_STATUS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1227
#define RSRTX_ATTR_PROTOCOL_MILSTD_WORD_SERVICE_REQUEST_BIT_STATUS          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2020
#define RSRTX_ATTR_PROTOCOL_ARINC429_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1387
#define RSRTX_ATTR_PROTOCOL_ARINC429_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1339
#define RSRTX_ATTR_PROTOCOL_ARINC429_BIT_RATE_MODE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1340
#define RSRTX_ATTR_PROTOCOL_ARINC429_BIT_RATE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1341
#define RSRTX_ATTR_PROTOCOL_ARINC429_THRESHOLD_HIGH                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1342
#define RSRTX_ATTR_PROTOCOL_ARINC429_THRESHOLD_LOW                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1343
#define RSRTX_ATTR_PROTOCOL_ARINC429_DATA_FORMAT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1388
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_COUNT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1349
#define RSRTX_ATTR_PROTOCOL_ARINC429_SELECTED_WORD                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1444
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_STATUS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1412
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_START                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1413
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_STOP                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1414
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_SDI                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1415
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_SSM                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1416
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_LABEL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1417
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_LABEL_VALUE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1418
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_PATTERN                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1419
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_PARITY                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1420
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_FORMAT                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1421
#define RSRTX_ATTR_PROTOCOL_ARINC429_WORD_DATA                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1423
#define RSRTX_ATTR_POWER_ANALYSIS_ENABLED                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1197
#define RSRTX_ATTR_POWER_ANALYSIS_TYPE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1024
#define RSRTX_ATTR_POWER_ANALYSIS_RESULT_TABLE_ENABLED                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1025
#define RSRTX_ATTR_POWER_ANALYSIS_RESET_STATISTICS                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1027
#define RSRTX_ATTR_POWER_ANALYSIS_STATISTICS_VISIBLE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1028
#define RSRTX_ATTR_POWER_ANALYSIS_START_DESKEW                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1030
#define RSRTX_ATTR_POWER_ANALYSIS_ZERO_OFFSET                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1073
#define RSRTX_ATTR_POWER_ANALYSIS_AUTOSET                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1871
#define RSRTX_ATTR_POWER_ANALYSIS_AUTOSET_CURRENT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1872
#define RSRTX_ATTR_POWER_ANALYSIS_AUTOSET_VOLTAGE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1873
#define RSRTX_ATTR_POWER_ANALYSIS_VOLTAGE_SOURCE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1074
#define RSRTX_ATTR_POWER_ANALYSIS_CURRENT_SOURCE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1075
#define RSRTX_ATTR_POWER_ANALYSIS_ADD_REPORT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1506
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_DUT                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1507
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_USER                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1508
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_SITE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1509
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_TEMPERATURE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1510
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_DESCRIPTION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1511
#define RSRTX_ATTR_POWER_ANALYSIS_REPORT_OUTPUT_FOLDER                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1512
#define RSRTX_ATTR_START_POWER_QUALITY_MEASUREMENT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1032
#define RSRTX_ATTR_POWER_QUALITY_MEASUREMENT_ADD_REPORT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1513
#define RSRTX_ATTR_START_POWER_CONSUMPTION_MEASUREMENT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1037
#define RSRTX_ATTR_RESTART_POWER_CONSUMPTION_MEASUREMENT                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1039
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ADD_REPORT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1514
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_DURATION_RESULT            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1179
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ENERGY_RESULT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1180
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ACTIVE_RESULT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1181
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_APPARENT_POWER_RESULT      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1874
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_POWER_FACTOR_RESULT        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1875
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_PHASE_RESULT               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1876
#define RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_REACTIVE_POWER_RESULT      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1877
#define RSRTX_ATTR_START_POWER_CURRENT_HARMONICS_MEASUREMENT                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1042
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_STANDARD             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1043
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FUNDAMENTAL          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1044
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FUNDAMENTAL_MIL      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1456
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FUNDAMENTAL_RTC      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1457
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_NUMBER_OF_MEASURED_HARMONICS     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1458
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_ADD_REPORT           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1515
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_DURATION             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1878
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_LIMIT_CHECK_RESULT   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1046
#define RSRTX_ATTR_RESET_POWER_CURRENT_HARMONICS_MEASUREMENT_RESULTS        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1047
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FREQUENCY_CURRENT    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1459
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FREQUENCY_AVERAGE    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1460
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FREQUENCY_MAXIMUM    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1461
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FREQUENCY_MINIMUM    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1462
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_FREQUENCY_STANDARD_DEVIATION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1463
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_REAL_POWER_CURRENT   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1879
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_TOTAL_HARMONIC_DISTORTION_CURRENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1464
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_TOTAL_HARMONIC_DISTORTION_AVERAGE RS_SPECIFIC_PUBLIC_ATTR_BASE + 1465
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_TOTAL_HARMONIC_DISTORTION_MAXIMUM RS_SPECIFIC_PUBLIC_ATTR_BASE + 1466
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_TOTAL_HARMONIC_DISTORTION_MINIMUM RS_SPECIFIC_PUBLIC_ATTR_BASE + 1467
#define RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_TOTAL_HARMONIC_DISTORTION_STANDARD_DEVIATION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1468
#define RSRTX_ATTR_CURRENT_HARMONICS_EXPORT_NAME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1591
#define RSRTX_ATTR_CURRENT_HARMONICS_EXPORT_SAVE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1592
#define RSRTX_ATTR_START_POWER_INRUSH_CURRENT_MEASUREMENT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1049
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_GATE_COUNT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1050
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_ADD_REPORT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1516
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_GATE_START              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1051
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_GATE_STOP               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1052
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_AREA_RESULT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1053
#define RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_MAXIMUM_RESULT          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1054
#define RSRTX_ATTR_START_POWER_RIPPLE_MEASUREMENT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1056
#define RSRTX_ATTR_POWER_RIPPLE_MEASUREMENT_ADD_REPORT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1517
#define RSRTX_ATTR_START_POWER_SPECTRUM_MEASUREMENT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1059
#define RSRTX_ATTR_POWER_SPECTRUM_MEASUREMENT_FREQUENCY                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1060
#define RSRTX_ATTR_POWER_SPECTRUM_MEASUREMENT_ADD_REPORT                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1518
#define RSRTX_ATTR_RESET_POWER_SPECTRUM_MEASUREMENT_RESULTS                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1062
#define RSRTX_ATTR_START_POWER_SLEW_RATE_MEASUREMENT                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1063
#define RSRTX_ATTR_POWER_SLEW_RATE_MEASUREMENT_DELTA_SAMPLE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1065
#define RSRTX_ATTR_POWER_SLEW_RATE_MEASUREMENT_DELTA_TIME                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1066
#define RSRTX_ATTR_POWER_SLEW_RATE_MEASUREMENT_ADD_REPORT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1519
#define RSRTX_ATTR_START_POWER_MODULATION_MEASUREMENT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1069
#define RSRTX_ATTR_POWER_MODULATION_MEASUREMENT_TYPE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1070
#define RSRTX_ATTR_POWER_MODULATION_MEASUREMENT_ADD_REPORT                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1520
#define RSRTX_ATTR_POWER_MODULATION_THRESHOLD_UPPER                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2021
#define RSRTX_ATTR_POWER_MODULATION_THRESHOLD_LOWER                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2022
#define RSRTX_ATTR_POWER_MODULATION_THRESHOLD_HYSTERESIS                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2023
#define RSRTX_ATTR_START_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1077
#define RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_ADD_REPORT       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1521
#define RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_GATE_START       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1078
#define RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_GATE_STOP        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1079
#define RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_RESULT           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1080
#define RSRTX_ATTR_START_POWER_EFFICIENCY_MEASUREMENT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1082
#define RSRTX_ATTR_POWER_EFFICIENCY_MEASUREMENT_ADD_REPORT                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1522
#define RSRTX_ATTR_START_POWER_SWITCHINGLOSS_MEASUREMENT                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1085
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TYPE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1086
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_ADD_REPORT               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1523
#define RSRTX_ATTR_SET_POWER_SWITSCHINGLOSS_MEASUREMENT_GATE_TO_WAVEFORM    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1088
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_CONDUCTION_START    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1089
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_CONDUCTION_STOP     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1090
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_NO_CONDUCTION_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1091
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_NO_CONDUCTION_STOP  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1092
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_TURN_ON_START       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1093
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_TURN_ON_STOP        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1094
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_TURN_OFF_START      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1095
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_GATE_TURN_OFF_STOP       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1096
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_CONDUCTION_ENERGY_RESULT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1097
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_CONDUCTION_POWER_RESULT  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1098
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_NO_CONDUCTION_ENERGY_RESULT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1099
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_NO_CONDUCTION_POWER_RESULT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1100
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_ON_ENERGY_RESULT    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1101
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_ON_POWER_RESULT     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1102
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_OFF_ENERGY_RESULT   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1103
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_OFF_POWER_RESULT    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1104
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TOTAL_ENERGY_RESULT      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1105
#define RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TOTAL_POWER_RESULT       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1106
#define RSRTX_ATTR_START_POWER_ON_OFF_MEASUREMENT                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1108
#define RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_TYPE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1109
#define RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_ADD_REPORT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1524
#define RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_RESULT                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1110
#define RSRTX_ATTR_START_POWER_SAFE_OPERATING_AREA_MEASUREMENT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1429
#define RSRTX_ATTR_RESTART_POWER_SAFE_OPERATING_AREA_MEASUREMENT            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1445
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_ADD_REPORT                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1525
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SCALE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1446
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_MASK_SCALE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1447
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_DISPLAY_SCALE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1448
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LIN_ADD                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1432
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_INSERT                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1433
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_REMOVE                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1434
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_COUNT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1435
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_ADD                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1436
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_INSERT             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1437
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_REMOVE             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1438
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_COUNT              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1439
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1449
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_VOLTAGE           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1450
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1880
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT_MIN       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1451
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT_MAX       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1452
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_VOLTAGE      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1453
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1881
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT_MIN  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1454
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT_MAX  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1455
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_TOLERANCE   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1469
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_PASSED_RESULTS RS_SPECIFIC_PUBLIC_ATTR_BASE + 1470
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_FAILED_RESULTS RS_SPECIFIC_PUBLIC_ATTR_BASE + 1471
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_FAILED_RATE RS_SPECIFIC_PUBLIC_ATTR_BASE + 1472
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_NUMBER_OF_POINTS RS_SPECIFIC_PUBLIC_ATTR_BASE + 1473
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_STATUS      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1474
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION_COUNT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1475
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2024
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION_CURRENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1476
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION_VOLTAGE RS_SPECIFIC_PUBLIC_ATTR_BASE + 1477
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1885
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1886
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1887
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1888
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_RESOLUTION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1889
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1893
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1894
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1895
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1896
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_RESOLUTION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1897
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_TOLERANCE         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1478
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_PASSED_RESULTS    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1479
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_FAILED_RESULTS    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1480
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_FAILED_RATE       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1481
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_NUMBER_OF_ACQUISITIONS RS_SPECIFIC_PUBLIC_ATTR_BASE + 1482
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_STATUS            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1483
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION_COUNT   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1484
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_PASSED_SAMPLES    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1485
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_FAILED_SAMPLES    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1486
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_NUMBER_OF_SAMPLES RS_SPECIFIC_PUBLIC_ATTR_BASE + 1487
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2026
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION_CURRENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1488
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION_VOLTAGE RS_SPECIFIC_PUBLIC_ATTR_BASE + 1489
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1493
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1494
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1495
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1496
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_RESOLUTION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1497
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1501
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1502
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_START RS_SPECIFIC_PUBLIC_ATTR_BASE + 1503
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_INCREMENT RS_SPECIFIC_PUBLIC_ATTR_BASE + 1504
#define RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_RESOLUTION RS_SPECIFIC_PUBLIC_ATTR_BASE + 1505
#define RSRTX_ATTR_START_POWER_TRANSIENT_RESPONSE_MEASUREMENT               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1526
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SIGNAL_HIGH                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1532
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SIGNAL_LOW                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1533
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_ADD_REPORT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1536
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_START_TIME                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1538
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_STOP_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1539
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_DELAY_TIME                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1540
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_OVERSHOOT                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1541
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_PEAK_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1542
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_PEAK_VALUE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1543
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_RISE_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1544
#define RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SETTLING_TIME                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1545
#define RSRTX_ATTR_SPECTRUM_ANALYSIS_ENABLE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1593
#define RSRTX_ATTR_SPECTRUM_ANALYSIS_MODE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1898
#define RSRTX_ATTR_SPECTRUM_ANALYSIS_SOURCE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1594
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_AVERAGE_COMPLETE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1595
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_AVERAGE_COUNT                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1596
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_MAGNITUDE_SCALE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1597
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_POSITION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1598
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_RESET                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1599
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_SCALE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1600
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_WINDOW_POSITION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2028
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_WINDOW_TYPE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1601
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_START                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1602
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_STOP                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1603
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_CENTER                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1604
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_SPAN                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1605
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_FULL_SPAN                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2029
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_BANDWIDTH_AUTO                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1606
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_BANDWIDTH_RATIO                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1607
#define RSRTX_ATTR_SPECTRUM_FREQUENCY_BANDWIDTH_RESOLUTION                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1608
#define RSRTX_ATTR_SPECTRUM_SPECTROGRAM_RESET                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1609
#define RSRTX_ATTR_SPECTRUM_SPECTROGRAM_SCALE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1610
#define RSRTX_ATTR_SPECTRUM_SPECTROGRAM_WINDOW_POSITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 2030
#define RSRTX_ATTR_SPECTRUM_MARKER_ENABLE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1611
#define RSRTX_ATTR_SPECTRUM_MARKER_SOURCE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1612
#define RSRTX_ATTR_SPECTRUM_MARKER_DISPLAY                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1613
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_DISTANCE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1614
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_EXCURSION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1615
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_MINIMUM_LEVEL                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1616
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_DETECTION_MODE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1617
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_MAXIMUM_WIDTH                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1618
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_CENTER_SCREEN                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1899
#define RSRTX_ATTR_SPECTRUM_MARKER_SETUP_RANGE_TO_PEAK                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1900
#define RSRTX_ATTR_SPECTRUM_MARKER_REFERENCE_MODE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1619
#define RSRTX_ATTR_SPECTRUM_MARKER_REFERENCE_FREQUENCY                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1620
#define RSRTX_ATTR_SPECTRUM_MARKER_REFERENCE_SPAN                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1621
#define RSRTX_ATTR_SPECTRUM_MARKER_REFERENCE_INDEX                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1622
#define RSRTX_ATTR_SPECTRUM_MARKER_TABLE_ENABLE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1623
#define RSRTX_ATTR_SPECTRUM_MARKER_TABLE_DETECTED_PEAKS                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1624
#define RSRTX_ATTR_SPECTRUM_MARKER_TABLE_RESULT_MODE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1625
#define RSRTX_ATTR_SPECTRUM_MARKER_TABLE_POSITION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1626
#define RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_FREQUENCY                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 2031
#define RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_LEVEL                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2032
#define RSRTX_ATTR_SPECTRUM_DISPLAY_MAGNITUDE_MODE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1627
#define RSRTX_ATTR_SPECTRUM_DISPLAY_MAXIMUM_LEVEL                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1628
#define RSRTX_ATTR_SPECTRUM_DISPLAY_MINIMUM_LEVEL                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1629
#define RSRTX_ATTR_SPECTRUM_DISPLAY_COLOR_SCHEME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1630
#define RSRTX_ATTR_SPECTRUM_DISPLAY_SPECTROGRAM_COLOR_SCHEME                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1631
#define RSRTX_ATTR_SPECTRUM_DISPLAY_FREQUENCY_DOMAIN_ENABLE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1632
#define RSRTX_ATTR_SPECTRUM_DISPLAY_SPECTROGRAM_ENABLE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1633
#define RSRTX_ATTR_SPECTRUM_DISPLAY_TIME_DOMAIN_ENABLE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1634
#define RSRTX_ATTR_SPECTRUM_WAVEFORM_ENABLE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1635
#define RSRTX_ATTR_SPECTRUM_WAVEFORM_MINIMUM_ENABLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1636
#define RSRTX_ATTR_SPECTRUM_WAVEFORM_MAXIMUM_ENABLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1637
#define RSRTX_ATTR_SPECTRUM_WAVEFORM_AVERAGE_ENABLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1638
#define RSRTX_ATTR_SPECTRUM_TIME_DOMAIN_POSITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1639
#define RSRTX_ATTR_SPECTRUM_TIME_DOMAIN_RANGE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1640
#define RSRTX_ATTR_DVM_ENABLE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1641
#define RSRTX_ATTR_DVM_SOURCE                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1642
#define RSRTX_ATTR_DVM_TYPE                                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1643
#define RSRTX_ATTR_DVM_POSITION                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1644
#define RSRTX_ATTR_DVM_RESULT                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1645
#define RSRTX_ATTR_DVM_RESULT_STATUS                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1646
#define RSRTX_ATTR_COUNTER_ENABLE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1647
#define RSRTX_ATTR_COUNTER_FREQUENCY                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1648
#define RSRTX_ATTR_COUNTER_PERIOD                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1649
#define RSRTX_ATTR_COUNTER_SOURCE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 2037
#define RSRTX_ATTR_BODE_PLOT_ENABLE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2038
#define RSRTX_ATTR_BODE_PLOT_START_FREQUENCY                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2039
#define RSRTX_ATTR_BODE_PLOT_STOP_FREQUENCY                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2040
#define RSRTX_ATTR_BODE_PLOT_INPUT_CHANNEL                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2041
#define RSRTX_ATTR_BODE_PLOT_OUTPUT_CHANNEL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2042
#define RSRTX_ATTR_BODE_PLOT_GAIN_ENABLE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2043
#define RSRTX_ATTR_BODE_PLOT_GAIN_POSITION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2044
#define RSRTX_ATTR_BODE_PLOT_GAIN_SCALE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 2045
#define RSRTX_ATTR_BODE_PLOT_PHASE_ENABLE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2046
#define RSRTX_ATTR_BODE_PLOT_PHASE_POSITION                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2047
#define RSRTX_ATTR_BODE_PLOT_PHASE_SCALE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2048
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_ENABLE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2049
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_POSITION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2050
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_SCALE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2051
#define RSRTX_ATTR_START_BODE_PLOT_MEASUREMENT                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2052
#define RSRTX_ATTR_STOP_BODE_PLOT_MEASUREMENT                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2053
#define RSRTX_ATTR_BODE_PLOT_MEASUREMENT_STATE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2054
#define RSRTX_ATTR_BODE_PLOT_REPEATED_MEASUREMENT_ENABLE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2055
#define RSRTX_ATTR_BODE_PLOT_RESET                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2056
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_MODE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2057
#define RSRTX_ATTR_BODE_PLOT_POINTS_PER_DECADE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2058
#define RSRTX_ATTR_BODE_PLOT_MEASUREMENT_POINTS_DISPLAY_ENABLE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2059
#define RSRTX_ATTR_BODE_PLOT_MEASUREMENT_DELAY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2060
#define RSRTX_ATTR_BODE_PLOT_EXPORT_NAME                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2061
#define RSRTX_ATTR_BODE_PLOT_EXPORT_SAVE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2062
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINTS                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2063
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_AMPLITUDE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2064
#define RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_FREQUENCY              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2065
#define RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2066
#define RSRTX_ATTR_BODE_PLOT_MARKER_GAIN                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2067
#define RSRTX_ATTR_BODE_PLOT_MARKER_PHASE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2068
#define RSRTX_ATTR_BODE_PLOT_MARKER_INDEX                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2069
#define RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY_DIFFERENCE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2070
#define RSRTX_ATTR_BODE_PLOT_MARKER_GAIN_DIFFERENCE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2071
#define RSRTX_ATTR_BODE_PLOT_MARKER_PHASE_DIFFERENCE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2072
#define RSRTX_ATTR_RESET_BODE_PLOT_MARKERS                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2073
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FUNCTION_TYPE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1773
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FREQUENCY                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1774
#define RSRTX_ATTR_WAVEFORM_GENERATOR_PULSE_DUTY_CYCLE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1775
#define RSRTX_ATTR_WAVEFORM_GENERATOR_PULSE_EDGE_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1776
#define RSRTX_ATTR_WAVEFORM_GENERATOR_RAMP_POLARITY                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1777
#define RSRTX_ATTR_WAVEFORM_GENERATOR_EXPONENTIAL_POLARITY                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1778
#define RSRTX_ATTR_WAVEFORM_GENERATOR_TRIANGLE_SYMMETRY                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 2077
#define RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_ENABLED                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1779
#define RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_TYPE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1780
#define RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_FUNCTION_TYPE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1781
#define RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_RAMP_POLARITY              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1782
#define RSRTX_ATTR_WAVEFORM_GENERATOR_AM_MODULATION_FREQUENCY               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1783
#define RSRTX_ATTR_WAVEFORM_GENERATOR_AM_MODULATION_DEPTH                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1784
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FM_MODULATION_FREQUENCY               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1785
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FM_MODULATION_FREQUENCY_DEVIATION     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1786
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ASK_MODULATION_FREQUENCY              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1787
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ASK_MODULATION_DEPTH                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1788
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FSK_MODULATION_HOPPING_FREQUENCY      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1789
#define RSRTX_ATTR_WAVEFORM_GENERATOR_FSK_MODULATION_RATE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1790
#define RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_ENABLED                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1791
#define RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_TYPE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1792
#define RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_START_FREQUENCY                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1793
#define RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_STOP_FREQUENCY                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1794
#define RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_TIME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1795
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_FILE_NAME                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1796
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_OPEN_FILE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1797
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_SOURCE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1798
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_UPDATE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1799
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_START                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2078
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_END                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2079
#define RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_DISPLAY_ENABLE              RS_SPECIFIC_PUBLIC_ATTR_BASE + 2080
#define RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_ENABLED                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1800
#define RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_AMPLITUDE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1801
#define RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_OFFSET                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1802
#define RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_USER_LOAD                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1803
#define RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_DESTINATION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1804
#define RSRTX_ATTR_WAVEFORM_GENERATOR_NOISE_LEVEL_PERCENT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1805
#define RSRTX_ATTR_WAVEFORM_GENERATOR_NOISE_ABSOLUTE_LEVEL                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1806
#define RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_ENABLE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2081
#define RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_CYCLES                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2082
#define RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_IDLE_TIME                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2083
#define RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_PHASE_OFFSET                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2084
#define RSRTX_ATTR_PATTERN_GENERATOR_ENABLED                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1807
#define RSRTX_ATTR_PATTERN_GENERATOR_FUNCTION_TYPE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1808
#define RSRTX_ATTR_PATTERN_GENERATOR_FREQUENCY                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1809
#define RSRTX_ATTR_PATTERN_GENERATOR_PERIOD                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1810
#define RSRTX_ATTR_PATTERN_GENERATOR_POLARITY                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1811
#define RSRTX_ATTR_PATTERN_GENERATOR_DUTY_CYCLE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1812
#define RSRTX_ATTR_PATTERN_GENERATOR_SAMPLE_TIME                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1813
#define RSRTX_ATTR_PATTERN_GENERATOR_COUNTER_DIRECTION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1814
#define RSRTX_ATTR_PATTERN_GENERATOR_COUNTER_FREQUENCY                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1815
#define RSRTX_ATTR_PATTERN_GENERATOR_BURST_ENABLED                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1816
#define RSRTX_ATTR_PATTERN_GENERATOR_BURST_CYCLES                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1817
#define RSRTX_ATTR_PATTERN_GENERATOR_IDLE_TIME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1818
#define RSRTX_ATTR_PATTERN_GENERATOR_TRIGGER_MODE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1819
#define RSRTX_ATTR_PATTERN_GENERATOR_TRIGGER_RUN_SINGLE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1820
#define RSRTX_ATTR_PATTERN_GENERATOR_EXTERNAL_TRIGGER_SLOPE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2085
#define RSRTX_ATTR_PATTERN_GENERATOR_ARB_PATTERN_LENGTH                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1821
#define RSRTX_ATTR_PATTERN_GENERATOR_ARB_INDEX                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1822
#define RSRTX_ATTR_PATTERN_GENERATOR_MANUAL_STATE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1827
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_ENABLE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2086
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_DIRECTION                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2087
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_DUTY_CYCLE                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2088
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 2089
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_BLUE                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 2090
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_GREEN                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2091
#define RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_RED                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 2092
#define RSRTX_ATTR_COLOR_AND_BRIGHTNESS                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 547
#define RSRTX_ATTR_SIGNAL_STYLE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 427
#define RSRTX_ATTR_DIAGRAM_GRID_STYLE                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 550
#define RSRTX_ATTR_DIAGRAM_ANNOTATION_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1740
#define RSRTX_ATTR_DIAGRAM_ANNOTATION_TRACK                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1741
#define RSRTX_ATTR_WAVEFORM_INTENSITY                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 573
#define RSRTX_ATTR_BACKGROUND_INTENSITY                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 545
#define RSRTX_ATTR_GRID_INTENSITY                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 546
#define RSRTX_ATTR_DISPLAY_LANGUAGE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 549
#define RSRTX_ATTR_DISPLAY_DATE_AND_TIME                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2093
#define RSRTX_ATTR_DIAGRAM_MODE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 548
#define RSRTX_ATTR_DISPLAY_SEND_MESSAGE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1561
#define RSRTX_ATTR_DISPLAY_CLOSE_DIALOG                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1321
#define RSRTX_ATTR_DIALOG_TRANSPARENCY                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1650
#define RSRTX_ATTR_DISPLAY_CLEAR_SCREEN                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1742
#define RSRTX_ATTR_PERSISTENCE_ENABLED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 422
#define RSRTX_ATTR_PERSISTENCE_TYPE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1743
#define RSRTX_ATTR_INFINITE_PERSISTENCE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 423
#define RSRTX_ATTR_PERSISTENCE_TIME                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 424
#define RSRTX_ATTR_PERSISTENCE_CLEAR                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 572
#define RSRTX_ATTR_XY_X_SOURCE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 551
#define RSRTX_ATTR_XY_Y_SOURCE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 552
#define RSRTX_ATTR_XY_Y2_SOURCE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 554
#define RSRTX_ATTR_XY_Z_SOURCE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 553
#define RSRTX_ATTR_XY_Z_TRESHOLD                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 556
#define RSRTX_ATTR_XY_INTENSITY_CONTROL                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 555
#define RSRTX_ATTR_ZOOM_WINDOW_ENABLED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 557
#define RSRTX_ATTR_ZOOM_DIAGRAM_TIMEBASE                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 558
#define RSRTX_ATTR_ZOOM_OFFSET_OF_TRIGGER_POINT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 559
#define RSRTX_ATTR_ZOOM_REFERENCE_POINT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 560
#define RSRTX_ATTR_ZOOM_WINDOW_POSITION                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 2094
#define RSRTX_ATTR_ZOOM_SAMPLE_RATE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1322
#define RSRTX_ATTR_MARKER_SET                                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 561
#define RSRTX_ATTR_MARKER_CLEAR                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 562
#define RSRTX_ATTR_MARKER_CLEAR_ALL                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 563
#define RSRTX_ATTR_MARKER_NEXT                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 564
#define RSRTX_ATTR_MARKER_PREVIOUS                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 565
#define RSRTX_ATTR_VIRTUAL_SCREEN_ENABLED                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 851
#define RSRTX_ATTR_VIRTUAL_SCREEN_POSITION                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 852
#define RSRTX_ATTR_HISTORY_CHANNEL_CURRENT_ACQUISITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1292
#define RSRTX_ATTR_HISTORY_CHANNEL_PLAYER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1293
#define RSRTX_ATTR_HISTORY_CHANNEL_START_ACQUISITION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1294
#define RSRTX_ATTR_HISTORY_CHANNEL_STOP_ACQUISITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1295
#define RSRTX_ATTR_HISTORY_CHANNEL_PLAY_ALL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1296
#define RSRTX_ATTR_HISTORY_CHANNEL_SPEED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1297
#define RSRTX_ATTR_HISTORY_CHANNEL_REPEAT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1298
#define RSRTX_ATTR_HISTORY_CHANNEL_ACQUISITON_RELATIVE_TIME                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1546
#define RSRTX_ATTR_HISTORY_CHANNEL_ALL_DATES                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1651
#define RSRTX_ATTR_HISTORY_CHANNEL_ALL_TIME_DIFFERENCES                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1652
#define RSRTX_ATTR_HISTORY_CHANNEL_ALL_DAYTIMES                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1653
#define RSRTX_ATTR_HISTORY_CHANNEL_PLAYER_CONTROL_ENABLE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2095
#define RSRTX_ATTR_HISTORY_CHANNEL_TABLE_MODE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1744
#define RSRTX_ATTR_HISTORY_CHANNEL_TIME_TABLE_ENABLE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2096
#define RSRTX_ATTR_HISTORY_CHANNEL_EXPORT_NAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1745
#define RSRTX_ATTR_HISTORY_CHANNEL_EXPORT_SAVE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1746
#define RSRTX_ATTR_HISTORY_DIGITAL_CURRENT_ACQUISITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1299
#define RSRTX_ATTR_HISTORY_DIGITAL_PLAYER                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1300
#define RSRTX_ATTR_HISTORY_DIGITAL_START_ACQUISITION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1301
#define RSRTX_ATTR_HISTORY_DIGITAL_STOP_ACQUISITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1302
#define RSRTX_ATTR_HISTORY_DIGITAL_PLAY_ALL                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1303
#define RSRTX_ATTR_HISTORY_DIGITAL_SPEED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1304
#define RSRTX_ATTR_HISTORY_DIGITAL_REPEAT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1305
#define RSRTX_ATTR_HISTORY_DIGITAL_ACQUISITON_RELATIVE_TIME                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1549
#define RSRTX_ATTR_HISTORY_DIGITAL_ALL_DATES                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1654
#define RSRTX_ATTR_HISTORY_DIGITAL_ALL_TIME_DIFFERENCES                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1655
#define RSRTX_ATTR_HISTORY_DIGITAL_ALL_DAYTIMES                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1656
#define RSRTX_ATTR_HISTORY_DIGITAL_PLAYER_CONTROL_ENABLE                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2097
#define RSRTX_ATTR_HISTORY_DIGITAL_TIME_TABLE_ENABLE                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 2098
#define RSRTX_ATTR_DIGITAL_HISTORY_EXPORT_NAME                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1747
#define RSRTX_ATTR_DIGITAL_HISTORY_EXPORT_SAVE                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1748
#define RSRTX_ATTR_HISTORY_MATH_CURRENT_ACQUISITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1306
#define RSRTX_ATTR_HISTORY_MATH_PLAYER                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1307
#define RSRTX_ATTR_HISTORY_MATH_START_ACQUISITION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1308
#define RSRTX_ATTR_HISTORY_MATH_STOP_ACQUISITION                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1309
#define RSRTX_ATTR_HISTORY_MATH_PLAY_ALL                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1310
#define RSRTX_ATTR_HISTORY_MATH_SPEED                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1311
#define RSRTX_ATTR_HISTORY_MATH_REPEAT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1312
#define RSRTX_ATTR_HISTORY_MATH_ACQUISITON_RELATIVE_TIME                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1552
#define RSRTX_ATTR_HISTORY_MATH_ALL_DATES                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1657
#define RSRTX_ATTR_HISTORY_MATH_ALL_TIME_DIFFERENCES                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1658
#define RSRTX_ATTR_HISTORY_MATH_ALL_DAYTIMES                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1659
#define RSRTX_ATTR_HISTORY_MATH_PLAYER_CONTROL_ENABLE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2099
#define RSRTX_ATTR_HISTORY_MATH_TIME_TABLE_ENABLE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 2100
#define RSRTX_ATTR_HISTORY_MATH_EXPORT_NAME                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1906
#define RSRTX_ATTR_HISTORY_MATH_EXPORT_SAVE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 1907
#define RSRTX_ATTR_HISTORY_PROTOCOL_CURRENT_ACQUISITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1313
#define RSRTX_ATTR_HISTORY_PROTOCOL_PLAYER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1314
#define RSRTX_ATTR_HISTORY_PROTOCOL_START_ACQUISITION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1315
#define RSRTX_ATTR_HISTORY_PROTOCOL_STOP_ACQUISITION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1316
#define RSRTX_ATTR_HISTORY_PROTOCOL_PLAY_ALL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1317
#define RSRTX_ATTR_HISTORY_PROTOCOL_SPEED                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1318
#define RSRTX_ATTR_HISTORY_PROTOCOL_REPEAT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1319
#define RSRTX_ATTR_HISTORY_PROTOCOL_ACQUISITON_RELATIVE_TIME                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1555
#define RSRTX_ATTR_HISTORY_PROTOCOL_ALL_DATES                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1660
#define RSRTX_ATTR_HISTORY_PROTOCOL_ALL_TIME_DIFFERENCES                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 1661
#define RSRTX_ATTR_HISTORY_PROTOCOL_ALL_DAYTIMES                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1662
#define RSRTX_ATTR_HISTORY_PROTOCOL_PLAYER_CONTROL_ENABLE                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2101
#define RSRTX_ATTR_HISTORY_PROTOCOL_TIME_TABLE_ENABLE                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2102
#define RSRTX_ATTR_HISTORY_PROTOCOL_EXPORT_NAME                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1749
#define RSRTX_ATTR_HISTORY_PROTOCOL_EXPORT_SAVE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1750
#define RSRTX_ATTR_HISTORY_SPECTRUM_CURRENT_ACQUISITION                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1663
#define RSRTX_ATTR_HISTORY_SPECTRUM_PLAYER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1664
#define RSRTX_ATTR_HISTORY_SPECTRUM_START_ACQUISITION                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1665
#define RSRTX_ATTR_HISTORY_SPECTRUM_STOP_ACQUISITION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1666
#define RSRTX_ATTR_HISTORY_SPECTRUM_PLAY_ALL                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1667
#define RSRTX_ATTR_HISTORY_SPECTRUM_SPEED                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1668
#define RSRTX_ATTR_HISTORY_SPECTRUM_REPEAT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1669
#define RSRTX_ATTR_HISTORY_SPECTRUM_ACQUISITION_RELATIVE_TIME               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2103
#define RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DATES                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 2104
#define RSRTX_ATTR_HISTORY_SPECTRUM_ALL_TIME_DIFFERENCES                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 2105
#define RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DAYTIMES                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 2106
#define RSRTX_ATTR_HISTORY_SPECTRUM_EXPORT_NAME                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1670
#define RSRTX_ATTR_HISTORY_SPECTRUM_EXPORT_SAVE                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 1671
#define RSRTX_ATTR_HISTORY_LOGIC_CURRENT_ACQUISITION                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1828
#define RSRTX_ATTR_HISTORY_LOGIC_PLAYER                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1829
#define RSRTX_ATTR_HISTORY_LOGIC_START_ACQUISITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 1830
#define RSRTX_ATTR_HISTORY_LOGIC_STOP_ACQUISITION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1831
#define RSRTX_ATTR_HISTORY_LOGIC_PLAY_ALL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1832
#define RSRTX_ATTR_HISTORY_LOGIC_SPEED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1833
#define RSRTX_ATTR_HISTORY_LOGIC_REPEAT                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1834
#define RSRTX_ATTR_HISTORY_LOGIC_ACQUISITON_RELATIVE_TIME                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1835
#define RSRTX_ATTR_HISTORY_LOGIC_ALL_DATES                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1836
#define RSRTX_ATTR_HISTORY_LOGIC_ALL_TIME_DIFFERENCES                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 1837
#define RSRTX_ATTR_HISTORY_LOGIC_ALL_DAYTIMES                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1838
#define RSRTX_ATTR_HISTORY_LOGIC_PLAYER_CONTROL_ENABLE                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 2109
#define RSRTX_ATTR_HISTORY_LOGIC_TIME_TABLE_ENABLE                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 2110
#define RSRTX_ATTR_HISTORY_LOGIC_EXPORT_NAME                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1839
#define RSRTX_ATTR_HISTORY_LOGIC_EXPORT_SAVE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1840
#define RSRTX_ATTR_SEGMENTATION_RECORD_LENGTH                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1323
#define RSRTX_ATTR_ULTRA_SEGMENTATION_ENABLED                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 1324
#define RSRTX_ATTR_SEGMENTATION_RECORD_MAXIMUM_SEGMENTS                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1908
#define RSRTX_ATTR_SEGMENTATION_NX_SINGLE_MAXIMUM                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1325
#define RSRTX_ATTR_SEGMENTATION_MAXIMUM_NUMBER_OF_SEGMENTS                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1326
#define RSRTX_ATTR_SEGMENTATION_NUMBER_OF_AVAILABLE_SEGMENTS                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1327
#define RSRTX_ATTR_DRIVES                                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 297
#define RSRTX_ATTR_CHANGE_DRIVE                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 298
#define RSRTX_ATTR_CURRENT_DIRECTORY                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 299
#define RSRTX_ATTR_CREATE_DIRECTORY                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 300
#define RSRTX_ATTR_REMOVE_DIRECTORY                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 301
#define RSRTX_ATTR_DELETE_FILE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 302
#define RSRTX_ATTR_HARDCOPY_FILE_NAME                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 303
#define RSRTX_ATTR_HARDCOPY_DEVICE_DESTINATION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 455
#define RSRTX_ATTR_HARDCOPY_COLOR_SCHEME                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 571
#define RSRTX_ATTR_HARDCOPY_COMMAND_SET                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1443
#define RSRTX_ATTR_HARDCOPY_CLOSE_DIALOGS                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 2113
#define RSRTX_ATTR_HARDCOPY_DEVICE_LANGUAGE_OUTPUT_FORMAT                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 456
#define RSRTX_ATTR_HARDCOPY_OUTPUT_FORMAT                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 1759
#define RSRTX_ATTR_HARDCOPY_DEVICE_ORIENTATION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 457
#define RSRTX_ATTR_HARDCOPY_PAGE_SIZE_X                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1761
#define RSRTX_ATTR_HARDCOPY_PAGE_SIZE_Y                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1762
#define RSRTX_ATTR_HARDCOPY_PRINT                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 458
#define RSRTX_ATTR_HARDCOPY_SELECT_PRINTER                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 459
#define RSRTX_ATTR_HARDCOPY_GET_FIRST_PRINTER                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 460
#define RSRTX_ATTR_HARDCOPY_GET_NEXT_PRINTER                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 461
#define RSRTX_ATTR_DEVICE_MODE                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 1763
#define RSRTX_ATTR_INTERFACE_SELECT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1909
#define RSRTX_ATTR_USB_CLASS                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1910
#define RSRTX_ATTR_ETHERNET_DHCP                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1911
#define RSRTX_ATTR_ETHERNET_IP_PORT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1912
#define RSRTX_ATTR_ETHERNET_VXI11_PORT                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 1913
#define RSRTX_ATTR_ETHERNET_HTTP_PORT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 2114
#define RSRTX_ATTR_ETHERNET_TRANSFER                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 1914
#define RSRTX_ATTR_ETHERNET_MAC_ADDRESS                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1915
#define RSRTX_ATTR_PRESET_EDUCATION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1919
#define RSRTX_ATTR_DEVICE_FOOTPRINT                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 1920
#define RSRTX_ATTR_ID_QUERY_RESPONSE                                        RS_SPECIFIC_PUBLIC_ATTR_BASE + 304
#define RSRTX_ATTR_SYSTEM_PRESET                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1690
#define RSRTX_ATTR_LOGGING                                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 1691
#define RSRTX_ATTR_CALIBRATION                                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 305
#define RSRTX_ATTR_SELF_TEST_QUERY                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 306
#define RSRTX_ATTR_SYSTEM_ERROR                                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 307
#define RSRTX_ATTR_SYST_ERR_LIST                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 642
#define RSRTX_ATTR_INSTRUMENT_NAME                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 568
#define RSRTX_ATTR_RESET_STATUS_REGISTER                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 643
#define RSRTX_ATTR_SELF_ALIGNMENT                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1177
#define RSRTX_ATTR_SELF_ALIGNMENT_STATE                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 1178
#define RSRTX_ATTR_QUERY_OPC                                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 1565
#define RSRTX_ATTR_PROCESS_ALL_PREVIOUS_COMMANDS                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 1567
#define RSRTX_ATTR_SOUND_ENABLED                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 853
#define RSRTX_ATTR_SOUND_ERROR_ENABLED                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 854
#define RSRTX_ATTR_SOUND_TRIGGER_ENABLED                                    RS_SPECIFIC_PUBLIC_ATTR_BASE + 855
#define RSRTX_ATTR_SOUND_GENERATE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 856
#define RSRTX_ATTR_OPERATION_CONDITION                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 953
#define RSRTX_ATTR_OPERATION_ENABLE                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 954
#define RSRTX_ATTR_OPERATION_N_TRANSITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 955
#define RSRTX_ATTR_OPERATION_P_TRANSITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 956
#define RSRTX_ATTR_OPERATION_EVENT                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 957
#define RSRTX_ATTR_QUESTIONABLE_CONDITION                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 958
#define RSRTX_ATTR_QUESTIONABLE_ENABLE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 959
#define RSRTX_ATTR_QUESTIONABLE_N_TRANSITION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 960
#define RSRTX_ATTR_QUESTIONABLE_P_TRANSITION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 961
#define RSRTX_ATTR_QUESTIONABLE_EVENT                                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 962
#define RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_CONDITION                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 963
#define RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_ENABLE                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 964
#define RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_N_TRANSITION               RS_SPECIFIC_PUBLIC_ATTR_BASE + 965
#define RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_P_TRANSITION               RS_SPECIFIC_PUBLIC_ATTR_BASE + 966
#define RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_EVENT                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 967
#define RSRTX_ATTR_QUESTIONABLE_LIMIT_CONDITION                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 968
#define RSRTX_ATTR_QUESTIONABLE_LIMIT_ENABLE                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 969
#define RSRTX_ATTR_QUESTIONABLE_LIMIT_N_TRANSITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 970
#define RSRTX_ATTR_QUESTIONABLE_LIMIT_P_TRANSITION                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 971
#define RSRTX_ATTR_QUESTIONABLE_LIMIT_EVENT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 972
#define RSRTX_ATTR_QUESTIONABLE_MASK_CONDITION                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 973
#define RSRTX_ATTR_QUESTIONABLE_MASK_ENABLE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 974
#define RSRTX_ATTR_QUESTIONABLE_MASK_N_TRANSITION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 975
#define RSRTX_ATTR_QUESTIONABLE_MASK_P_TRANSITION                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 976
#define RSRTX_ATTR_QUESTIONABLE_MASK_EVENT                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 977
#define RSRTX_ATTR_QUESTIONABLE_ADC_STATE_CONDITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 2115
#define RSRTX_ATTR_QUESTIONABLE_ADC_STATE_ENABLE                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 2116
#define RSRTX_ATTR_QUESTIONABLE_ADC_STATE_N_TRANSITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 2117
#define RSRTX_ATTR_QUESTIONABLE_ADC_STATE_P_TRANSITION                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 2118
#define RSRTX_ATTR_QUESTIONABLE_ADC_STATE_EVENT                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 2119

// rsrtx_rngSampleMode
#define RSRTX_VAL_REAL_TIME                                                 0
#define RSRTX_VAL_EQUIVALENT_TIME                                           1

// rsrtx_rngWaveformArithmetics
#define RSRTX_VAL_OFF                                                       0
#define RSRTX_VAL_ENVELOPE                                                  1
#define RSRTX_VAL_AVERAGE                                                   2
#define RSRTX_VAL_SMOOTH                                                    3
#define RSRTX_VAL_FILTER                                                    4

// rsrtx_rngVerticalCoupling
#define RSRTX_VAL_AC                                                        0
#define RSRTX_VAL_DC                                                        1
#define RSRTX_VAL_DC_LIMIT                                                  2
#define RSRTX_VAL_AC_LIMIT                                                  3
#define RSRTX_VAL_GND                                                       4

// rsrtx_rngChannelBWLimit
#define RSRTX_VAL_BW_FULL                                                   0
#define RSRTX_VAL_BW_400                                                    1
#define RSRTX_VAL_BW_200                                                    2
#define RSRTX_VAL_BW_20                                                     3

// rsrtx_rngTriggerSource
#define RSRTX_VAL_CHANNEL1                                                  1
#define RSRTX_VAL_CHANNEL2                                                  2
#define RSRTX_VAL_CHANNEL3                                                  3
#define RSRTX_VAL_CHANNEL4                                                  4
#define RSRTX_VAL_EXTERNAL                                                  5
#define RSRTX_VAL_LINE                                                      6
#define RSRTX_VAL_SBUS1                                                     7
#define RSRTX_VAL_SBUS2                                                     8
#define RSRTX_VAL_SBUS3                                                     9
#define RSRTX_VAL_SBUS4                                                     10
#define RSRTX_VAL_D0                                                        11
#define RSRTX_VAL_D1                                                        12
#define RSRTX_VAL_D2                                                        13
#define RSRTX_VAL_D3                                                        14
#define RSRTX_VAL_D4                                                        15
#define RSRTX_VAL_D5                                                        16
#define RSRTX_VAL_D6                                                        17
#define RSRTX_VAL_D7                                                        18
#define RSRTX_VAL_D8                                                        19
#define RSRTX_VAL_D9                                                        20
#define RSRTX_VAL_D10                                                       21
#define RSRTX_VAL_D11                                                       22
#define RSRTX_VAL_D12                                                       23
#define RSRTX_VAL_D13                                                       24
#define RSRTX_VAL_D14                                                       25
#define RSRTX_VAL_D15                                                       26

// rsrtx_rngTriggerSlope
#define RSRTX_VAL_POSITIVE                                                  0
#define RSRTX_VAL_NEGATIVE                                                  1
#define RSRTX_VAL_EITHER                                                    2

// rsrtx_rngPolarity
#define RSRTX_VAL_POLARITY_NEGATIVE                                         0
#define RSRTX_VAL_POLARITY_POSITIVE                                         1

// rsrtx_rngWidthCondition
#define RSRTX_VAL_SHORTER                                                   0
#define RSRTX_VAL_LONGER                                                    1
#define RSRTX_VAL_WITHIN                                                    2
#define RSRTX_VAL_OUTSIDE                                                   3

// rsrtx_rngTVTriggerEvent
#define RSRTX_VAL_TV_EVENT_EVEN                                             0
#define RSRTX_VAL_TV_EVENT_ODD                                              1
#define RSRTX_VAL_TV_EVENT_ANY_FIELD                                        2
#define RSRTX_VAL_TV_EVENT_LINE                                             3
#define RSRTX_VAL_TV_EVENT_ANY_LINE                                         4

// rsrtx_rngCursorFunction
#define RSRTX_VAL_CURSOR_HORIZONTAL                                         0
#define RSRTX_VAL_CURSOR_VERTICAL                                           1
#define RSRTX_VAL_CURSOR_PAIRED                                             2
#define RSRTX_VAL_CURSOR_HRAT                                               3
#define RSRTX_VAL_CURSOR_VRAT                                               4
#define RSRTX_VAL_CURSOR_PPC                                                5
#define RSRTX_VAL_CURSOR_NPC                                                6
#define RSRTX_VAL_CURSOR_REC                                                7
#define RSRTX_VAL_CURSOR_FEC                                                8
#define RSRTX_VAL_CURSOR_MEAN                                               9
#define RSRTX_VAL_CURSOR_RMS                                                10
#define RSRTX_VAL_CURSOR_RTIM                                               11
#define RSRTX_VAL_CURSOR_FTIM                                               12
#define RSRTX_VAL_CURSOR_PEAK                                               13
#define RSRTX_VAL_CURSOR_UPE                                                14
#define RSRTX_VAL_CURSOR_LPE                                                15
#define RSRTX_VAL_CURSOR_BWIDTH                                             16
#define RSRTX_VAL_CURSOR_HVER                                               17

// rsrtx_rngXRatioMeasurementUnit
#define RSRTX_VAL_UNIT_RATIO                                                0
#define RSRTX_VAL_UNIT_PCT                                                  1
#define RSRTX_VAL_UNIT_DEGREE                                               2
#define RSRTX_VAL_UNIT_RAD                                                  3

// rsrtx_rngInterpolation
#define RSRTX_VAL_SINE_X                                                    0
#define RSRTX_VAL_LINEAR                                                    1
#define RSRTX_VAL_SAMPLE_HOLD                                               2

// rsrtx_rngMeasurementCategory
#define RSRTX_VAL_AMPTIME                                                   0

// rsrtx_rngFFTWindowType
#define RSRTX_VAL_RECTANGULAR                                               0
#define RSRTX_VAL_HAMMING                                                   1
#define RSRTX_VAL_HANN                                                      2
#define RSRTX_VAL_BLACKMAN                                                  3
#define RSRTX_VAL_FLAT                                                      4

// rsrtx_rngProtocolI2CFrameState
#define RSRTX_VAL_FRAME_STATE_OK                                            0
#define RSRTX_VAL_FRAME_STATE_INCOMPLETE                                    1
#define RSRTX_VAL_FRAME_STATE_UNEXPSTOP                                     2
#define RSRTX_VAL_FRAME_STATE_INSUFFICIENT                                  3
#define RSRTX_VAL_FRAME_STATE_ADDIFFERENT                                   4

// rsrtx_rngProtocolAckBit
#define RSRTX_VAL_I2C_EITHER                                                0
#define RSRTX_VAL_I2C_ACK                                                   1
#define RSRTX_VAL_I2C_NACK                                                  2
#define RSRTX_VAL_I2C_INCOMPLETE                                            3

// rsrtx_rngProtocolSPIBitOrder
#define RSRTX_VAL_SPI_MSBF                                                  0
#define RSRTX_VAL_SPI_LSBF                                                  1

// rsrtx_rngAudioSource
#define RSRTX_VAL_AUDIO_SOURCE_CH1                                          1
#define RSRTX_VAL_AUDIO_SOURCE_CH2                                          2
#define RSRTX_VAL_AUDIO_SOURCE_CH3                                          3
#define RSRTX_VAL_AUDIO_SOURCE_CH4                                          4
#define RSRTX_VAL_AUDIO_SOURCE_D0                                           5
#define RSRTX_VAL_AUDIO_SOURCE_D1                                           6
#define RSRTX_VAL_AUDIO_SOURCE_D2                                           7
#define RSRTX_VAL_AUDIO_SOURCE_D3                                           8
#define RSRTX_VAL_AUDIO_SOURCE_D4                                           9
#define RSRTX_VAL_AUDIO_SOURCE_D5                                           10
#define RSRTX_VAL_AUDIO_SOURCE_D6                                           11
#define RSRTX_VAL_AUDIO_SOURCE_D7                                           12
#define RSRTX_VAL_AUDIO_SOURCE_D8                                           13
#define RSRTX_VAL_AUDIO_SOURCE_D9                                           14
#define RSRTX_VAL_AUDIO_SOURCE_D10                                          15
#define RSRTX_VAL_AUDIO_SOURCE_D11                                          16
#define RSRTX_VAL_AUDIO_SOURCE_D12                                          17
#define RSRTX_VAL_AUDIO_SOURCE_D13                                          18
#define RSRTX_VAL_AUDIO_SOURCE_D14                                          19
#define RSRTX_VAL_AUDIO_SOURCE_D15                                          20

// rsrtx_rngSPIChipSelectSource
#define RSRTX_VAL_SPI_CS_SOURCE_CH1                                         1
#define RSRTX_VAL_SPI_CS_SOURCE_CH2                                         2
#define RSRTX_VAL_SPI_CS_SOURCE_CH3                                         3
#define RSRTX_VAL_SPI_CS_SOURCE_CH4                                         4
#define RSRTX_VAL_SPI_CS_SOURCE_D0                                          5
#define RSRTX_VAL_SPI_CS_SOURCE_D1                                          6
#define RSRTX_VAL_SPI_CS_SOURCE_D2                                          7
#define RSRTX_VAL_SPI_CS_SOURCE_D3                                          8
#define RSRTX_VAL_SPI_CS_SOURCE_D4                                          9
#define RSRTX_VAL_SPI_CS_SOURCE_D5                                          10
#define RSRTX_VAL_SPI_CS_SOURCE_D6                                          11
#define RSRTX_VAL_SPI_CS_SOURCE_D7                                          12
#define RSRTX_VAL_SPI_CS_SOURCE_D8                                          13
#define RSRTX_VAL_SPI_CS_SOURCE_D9                                          14
#define RSRTX_VAL_SPI_CS_SOURCE_D10                                         15
#define RSRTX_VAL_SPI_CS_SOURCE_D11                                         16
#define RSRTX_VAL_SPI_CS_SOURCE_D12                                         17
#define RSRTX_VAL_SPI_CS_SOURCE_D13                                         18
#define RSRTX_VAL_SPI_CS_SOURCE_D14                                         19
#define RSRTX_VAL_SPI_CS_SOURCE_D15                                         20

// rsrtx_rngMOSISource
#define RSRTX_VAL_MOSI_SOURCE_CH1                                           1
#define RSRTX_VAL_MOSI_SOURCE_CH2                                           2
#define RSRTX_VAL_MOSI_SOURCE_CH3                                           3
#define RSRTX_VAL_MOSI_SOURCE_CH4                                           4
#define RSRTX_VAL_MOSI_SOURCE_D0                                            5
#define RSRTX_VAL_MOSI_SOURCE_D1                                            6
#define RSRTX_VAL_MOSI_SOURCE_D2                                            7
#define RSRTX_VAL_MOSI_SOURCE_D3                                            8
#define RSRTX_VAL_MOSI_SOURCE_D4                                            9
#define RSRTX_VAL_MOSI_SOURCE_D5                                            10
#define RSRTX_VAL_MOSI_SOURCE_D6                                            11
#define RSRTX_VAL_MOSI_SOURCE_D7                                            12
#define RSRTX_VAL_MOSI_SOURCE_D8                                            13
#define RSRTX_VAL_MOSI_SOURCE_D9                                            14
#define RSRTX_VAL_MOSI_SOURCE_D10                                           15
#define RSRTX_VAL_MOSI_SOURCE_D11                                           16
#define RSRTX_VAL_MOSI_SOURCE_D12                                           17
#define RSRTX_VAL_MOSI_SOURCE_D13                                           18
#define RSRTX_VAL_MOSI_SOURCE_D14                                           19
#define RSRTX_VAL_MOSI_SOURCE_D15                                           20

// rsrtx_rngMISOSource
#define RSRTX_VAL_MISO_SOURCE_NONE                                          0
#define RSRTX_VAL_MISO_SOURCE_CH1                                           1
#define RSRTX_VAL_MISO_SOURCE_CH2                                           2
#define RSRTX_VAL_MISO_SOURCE_CH3                                           3
#define RSRTX_VAL_MISO_SOURCE_CH4                                           4
#define RSRTX_VAL_MISO_SOURCE_D0                                            5
#define RSRTX_VAL_MISO_SOURCE_D1                                            6
#define RSRTX_VAL_MISO_SOURCE_D2                                            7
#define RSRTX_VAL_MISO_SOURCE_D3                                            8
#define RSRTX_VAL_MISO_SOURCE_D4                                            9
#define RSRTX_VAL_MISO_SOURCE_D5                                            10
#define RSRTX_VAL_MISO_SOURCE_D6                                            11
#define RSRTX_VAL_MISO_SOURCE_D7                                            12
#define RSRTX_VAL_MISO_SOURCE_D8                                            13
#define RSRTX_VAL_MISO_SOURCE_D9                                            14
#define RSRTX_VAL_MISO_SOURCE_D10                                           15
#define RSRTX_VAL_MISO_SOURCE_D11                                           16
#define RSRTX_VAL_MISO_SOURCE_D12                                           17
#define RSRTX_VAL_MISO_SOURCE_D13                                           18
#define RSRTX_VAL_MISO_SOURCE_D14                                           19
#define RSRTX_VAL_MISO_SOURCE_D15                                           20

// rsrtx_rngProtocolSPIPolarity
#define RSRTX_VAL_ACTLOW                                                    0
#define RSRTX_VAL_ACTHIGH                                                   1

// rsrtx_rngProtocolSPIFrameState
#define RSRTX_VAL_FRAME_STATE_INCFIRST                                      1
#define RSRTX_VAL_FRAME_STATE_INCLAST                                       2
#define RSRTX_VAL_FRAME_STATE_VOID                                          4

// rsrtx_rngUARTSource
#define RSRTX_VAL_UART_SOURCE_CH1                                           1
#define RSRTX_VAL_UART_SOURCE_CH2                                           2
#define RSRTX_VAL_UART_SOURCE_CH3                                           3
#define RSRTX_VAL_UART_SOURCE_CH4                                           4
#define RSRTX_VAL_UART_SOURCE_D0                                            5
#define RSRTX_VAL_UART_SOURCE_D1                                            6
#define RSRTX_VAL_UART_SOURCE_D2                                            7
#define RSRTX_VAL_UART_SOURCE_D3                                            8
#define RSRTX_VAL_UART_SOURCE_D4                                            9
#define RSRTX_VAL_UART_SOURCE_D5                                            10
#define RSRTX_VAL_UART_SOURCE_D6                                            11
#define RSRTX_VAL_UART_SOURCE_D7                                            12
#define RSRTX_VAL_UART_SOURCE_D8                                            13
#define RSRTX_VAL_UART_SOURCE_D9                                            14
#define RSRTX_VAL_UART_SOURCE_D10                                           15
#define RSRTX_VAL_UART_SOURCE_D11                                           16
#define RSRTX_VAL_UART_SOURCE_D12                                           17
#define RSRTX_VAL_UART_SOURCE_D13                                           18
#define RSRTX_VAL_UART_SOURCE_D14                                           19
#define RSRTX_VAL_UART_SOURCE_D15                                           20

// rsrtx_rngUARTTxSource
#define RSRTX_VAL_UART_SOURCE_NONE                                          01

// rsrtx_rngProtocolUARTParity
#define RSRTX_VAL_UART_NONE                                                 0
#define RSRTX_VAL_UART_ODD                                                  1
#define RSRTX_VAL_UART_EVEN                                                 2

// rsrtx_rngProtocolUARTStopBits
#define RSRTX_VAL_UART_B1                                                   0
#define RSRTX_VAL_UART_B1_5                                                 1
#define RSRTX_VAL_UART_B2                                                   2

// rsrtx_rngProtocolUARTTriggerType
#define RSRTX_VAL_UART_TRIGGER_BURSTSTART                                   0
#define RSRTX_VAL_UART_TRIGGER_SBIT                                         1
#define RSRTX_VAL_UART_TRIGGER_NTHS                                         2
#define RSRTX_VAL_UART_TRIGGER_SYMB                                         3
#define RSRTX_VAL_UART_TRIGGER_PATT                                         4
#define RSRTX_VAL_UART_TRIGGER_PERR                                         5
#define RSRTX_VAL_UART_TRIGGER_SPER                                         6
#define RSRTX_VAL_UART_TRIGGER_BRE                                          7

// rsrtx_rngSignalStyle
#define RSRTX_VAL_SIGNAL_STYLE_VECTORS                                      0
#define RSRTX_VAL_SIGNAL_STYLE_DOTS                                         1

// rsrtx_rngHardcopyDeviceOrientation
#define RSRTX_VAL_HARDCOPY_ORIENTATION_PORTRAIT                             0
#define RSRTX_VAL_HARDCOPY_ORIENTATION_LANDSCAPE                            1

// rsrtx_rngWaveformParameter
#define RSRTX_VAL_WAV_CH1                                                   1
#define RSRTX_VAL_WAV_CH2                                                   2
#define RSRTX_VAL_WAV_CH3                                                   3
#define RSRTX_VAL_WAV_CH4                                                   4
#define RSRTX_VAL_WAV_M1                                                    5
#define RSRTX_VAL_WAV_M2                                                    6
#define RSRTX_VAL_WAV_M3                                                    7
#define RSRTX_VAL_WAV_M4                                                    8
#define RSRTX_VAL_WAV_M5                                                    9
#define RSRTX_VAL_WAV_R1                                                    10
#define RSRTX_VAL_WAV_R2                                                    11
#define RSRTX_VAL_WAV_R3                                                    12
#define RSRTX_VAL_WAV_R4                                                    13
#define RSRTX_VAL_WAV_D0                                                    14
#define RSRTX_VAL_WAV_D1                                                    15
#define RSRTX_VAL_WAV_D2                                                    16
#define RSRTX_VAL_WAV_D3                                                    17
#define RSRTX_VAL_WAV_D4                                                    18
#define RSRTX_VAL_WAV_D5                                                    19
#define RSRTX_VAL_WAV_D6                                                    20
#define RSRTX_VAL_WAV_D7                                                    21
#define RSRTX_VAL_WAV_D8                                                    22
#define RSRTX_VAL_WAV_D9                                                    23
#define RSRTX_VAL_WAV_D10                                                   24
#define RSRTX_VAL_WAV_D11                                                   25
#define RSRTX_VAL_WAV_D12                                                   26
#define RSRTX_VAL_WAV_D13                                                   27
#define RSRTX_VAL_WAV_D14                                                   28
#define RSRTX_VAL_WAV_D15                                                   29
#define RSRTX_VAL_WAV_D70                                                   30
#define RSRTX_VAL_WAV_D158                                                  31
#define RSRTX_VAL_WAV_SPEC                                                  32
#define RSRTX_VAL_WAV_XY2                                                   33
#define RSRTX_VAL_WAV_MINH                                                  34
#define RSRTX_VAL_WAV_MAXH                                                  35
#define RSRTX_VAL_WAV_AVER                                                  36
#define RSRTX_VAL_WAV_QMA                                                   37
#define RSRTX_VAL_WAV_XY1                                                   38

// rsrtx_rngColorBrightness
#define RSRTX_VAL_COLOR_NORM                                                0
#define RSRTX_VAL_COLOR_INVERSE                                             1
#define RSRTX_VAL_COLOR_FCOLOR                                              2
#define RSRTX_VAL_COLOR_INVCOLOR                                            3

// rsrtx_rngDiagramMode
#define RSRTX_VAL_DISPLAY_YT                                                0
#define RSRTX_VAL_DISPLAY_XY                                                1

// rsrtx_rngLanguage
#define RSRTX_VAL_DISPLAY_ENGLISH                                           0
#define RSRTX_VAL_DISPLAY_GERMAN                                            1
#define RSRTX_VAL_DISPLAY_FRENCH                                            2
#define RSRTX_VAL_DISPLAY_SPANISH                                           3
#define RSRTX_VAL_DISPLAY_RUSSIAN                                           4
#define RSRTX_VAL_DISPLAY_SCHIN                                             5
#define RSRTX_VAL_DISPLAY_TCHIN                                             6
#define RSRTX_VAL_DISPLAY_JAPAN                                             7
#define RSRTX_VAL_DISPLAY_KOREAN                                            8
#define RSRTX_VAL_DISPLAY_ITALIAN                                           9
#define RSRTX_VAL_DISPLAY_PORTUGUESE                                        10
#define RSRTX_VAL_DISPLAY_CZECH                                             11
#define RSRTX_VAL_DISPLAY_POLISH                                            12

// rsrtx_rngGridStyle
#define RSRTX_VAL_GRID_LINES                                                0
#define RSRTX_VAL_GRID_CROSS                                                1
#define RSRTX_VAL_GRID_NONE                                                 2

// rsrtx_rngSource
#define RSRTX_VAL_SOURCE_CH1                                                1
#define RSRTX_VAL_SOURCE_CH2                                                2
#define RSRTX_VAL_SOURCE_CH3                                                3
#define RSRTX_VAL_SOURCE_CH4                                                4

// rsrtx_rngXY2Source
#define RSRTX_VAL_SOURCE_NONE                                               0

// rsrtx_rngIntensityMode
#define RSRTX_VAL_ZMODE_ANALOG                                              0
#define RSRTX_VAL_ZMODE_DIGITAL                                             1
#define RSRTX_VAL_ZMODE_OFF                                                 2

// rsrtx_rngHardcopyDevice
#define RSRTX_VAL_HARDCOPY_DEVICE_MEM                                       0
#define RSRTX_VAL_HARDCOPY_DEVICE_PRINT                                     1

// rsrtx_rngHardcopyDeviceLang
#define RSRTX_VAL_HARDCOPY_DEVICE_LANG_BMP                                  1
#define RSRTX_VAL_HARDCOPY_DEVICE_LANG_PNG                                  0
#define RSRTX_VAL_HARDCOPY_DEVICE_LANG_GDI                                  2
#define RSRTX_VAL_HARDCOPY_DEVICE_LANG_GIF                                  3

// rsrtx_rngPageSize
#define RSRTX_VAL_PAGE_A4                                                   0
#define RSRTX_VAL_PAGE_A5                                                   1
#define RSRTX_VAL_PAGE_B5                                                   2
#define RSRTX_VAL_PAGE_B6                                                   3
#define RSRTX_VAL_PAGE_EX                                                   4
#define RSRTX_VAL_PAGE_LEGAL                                                5
#define RSRTX_VAL_PAGE_LETTER                                               6

// rsrtx_rngMaskCondition
#define RSRTX_VAL_MASKCOND_RUN                                              0
#define RSRTX_VAL_MASKCOND_STOP                                             1
#define RSRTX_VAL_MASKCOND_PAUSE                                            2

// rsrtx_rngProbeButtonAction
#define RSRTX_VAL_PROBE_BUTTON_NO_ACTION                                    0
#define RSRTX_VAL_PROBE_BUTTON_RUN_CONTINUOUS                               1
#define RSRTX_VAL_PROBE_BUTTON_RUN_SINGLE                                   2
#define RSRTX_VAL_PROBE_BUTTON_AUTOSET                                      3

// rsrtx_rngTriggerCoupling
#define RSRTX_VAL_COUPLING_DIRECT                                           0
#define RSRTX_VAL_COUPLING_ALTERNATING                                      1
#define RSRTX_VAL_COUPLING_HIGHFREQ                                         2

// rsrtx_rngProtocolI2CAccessBit
#define RSRTX_VAL_I2C_TRIGGER_READ                                          1
#define RSRTX_VAL_I2C_TRIGGER_WRITE                                         2

// rsrtx_rngAddressLength
#define RSRTX_VAL_LENGTH_NORMAL                                             0
#define RSRTX_VAL_LENGTH_EXTENDED                                           1

// rsrtx_rngProtocolI2CTriggerType
#define RSRTX_VAL_TRIGGER_MODE_START                                        0
#define RSRTX_VAL_TRIGGER_MODE_RESTART                                      1
#define RSRTX_VAL_TRIGGER_MODE_STOP                                         2
#define RSRTX_VAL_TRIGGER_MODE_MISSING                                      3
#define RSRTX_VAL_TRIGGER_MODE_PATT                                         4

// rsrtx_rngHysteresisMode
#define RSRTX_VAL_HYSTERESIS_AUTO                                           0
#define RSRTX_VAL_HYSTERESIS_SMALL                                          1
#define RSRTX_VAL_HYSTERESIS_MEDIUM                                         2
#define RSRTX_VAL_HYSTERESIS_LARGE                                          3
#define RSRTX_VAL_HYSTERESIS_MANUAL                                         4

// rsrtx_rngTriggerMode
#define RSRTX_VAL_TRIGGER_AUTO                                              0
#define RSRTX_VAL_TRIGGER_NORMAL                                            1
#define RSRTX_VAL_TRIGGER_DELAY                                             2
#define RSRTX_VAL_TRIGGER_EVENTS                                            3

// rsrtx_rngTriggerPatternFunction
#define RSRTX_VAL_TRG_PATTERN_AND                                           0
#define RSRTX_VAL_TRG_PATTERN_OR                                            1

// rsrtx_rngProtocolSPITriggerType
#define RSRTX_VAL_SPI_MODE_BURSTSTART                                       0
#define RSRTX_VAL_SPI_MODE_BURSTEND                                         1
#define RSRTX_VAL_SPI_MODE_BIT                                              2
#define RSRTX_VAL_SPI_MODE_PATTERN                                          3

// rsrtx_rngTriggerType
#define RSRTX_VAL_EDGE_TRIGGER                                              0
#define RSRTX_VAL_WIDTH_TRIGGER                                             1
#define RSRTX_VAL_VIDEO_TRIGGER                                             2
#define RSRTX_VAL_PATTERN_TRIGGER                                           3
#define RSRTX_VAL_BUS_TRIGGER                                               4
#define RSRTX_VAL_RISE_TIME_TRIGGER                                         5
#define RSRTX_VAL_RUNT_TRIGGER                                              6
#define RSRTX_VAL_LINE_TRIGGER                                              7

// rsrtx_rngTVStandard
#define RSRTX_VAL_TV_STANDART_PAL                                           0
#define RSRTX_VAL_TV_STANDART_NTSC                                          1
#define RSRTX_VAL_TV_STANDART_SECAM                                         2
#define RSRTX_VAL_TV_STANDART_PALM                                          3
#define RSRTX_VAL_TV_STANDART_I576                                          4
#define RSRTX_VAL_TV_STANDART_P720                                          5
#define RSRTX_VAL_TV_STANDART_P1080                                         6
#define RSRTX_VAL_TV_STANDART_I1080                                         7

// rsrtx_rngColorScheme
#define RSRTX_VAL_SCHEME_COLOR                                              0
#define RSRTX_VAL_SCHEME_GRAY                                               1
#define RSRTX_VAL_SCHEME_INVERTED                                           2

// rsrtx_rngAcquisitionType
#define RSRTX_VAL_SAMPLE                                                    0
#define RSRTX_VAL_PEAK_DETECT                                               1
#define RSRTX_VAL_HI_RES                                                    2

// rsrtx_rngAmplitudeTimeMeasurementType
#define RSRTX_VAL_MEAS_FREQUENCY                                            1
#define RSRTX_VAL_MEAS_PERIOD                                               2
#define RSRTX_VAL_MEAS_PEAK                                                 3
#define RSRTX_VAL_MEAS_UPEAK                                                4
#define RSRTX_VAL_MEAS_LPEAK                                                5
#define RSRTX_VAL_MEAS_PPC                                                  6
#define RSRTX_VAL_MEAS_NPC                                                  7
#define RSRTX_VAL_MEAS_REC                                                  8
#define RSRTX_VAL_MEAS_FEC                                                  9
#define RSRTX_VAL_MEAS_HIGH                                                 10
#define RSRTX_VAL_MEAS_LOW                                                  11
#define RSRTX_VAL_MEAS_AMP                                                  12
#define RSRTX_VAL_MEAS_MEAN                                                 13
#define RSRTX_VAL_MEAS_RMS                                                  14
#define RSRTX_VAL_MEAS_RTM                                                  15
#define RSRTX_VAL_MEAS_FTIM                                                 16
#define RSRTX_VAL_MEAS_PDCY                                                 17
#define RSRTX_VAL_MEAS_NDCY                                                 18
#define RSRTX_VAL_MEAS_PPW                                                  19
#define RSRTX_VAL_MEAS_NPW                                                  20
#define RSRTX_VAL_MEAS_CYCM                                                 21
#define RSRTX_VAL_MEAS_CYCR                                                 22
#define RSRTX_VAL_MEAS_SSTDD                                                23
#define RSRTX_VAL_MEAS_TFR                                                  24
#define RSRTX_VAL_MEAS_TPER                                                 25
#define RSRTX_VAL_MEAS_DEL                                                  26
#define RSRTX_VAL_MEAS_PHA                                                  27
#define RSRTX_VAL_MEAS_BWID                                                 28
#define RSRTX_VAL_MEAS_CYCS                                                 29
#define RSRTX_VAL_MEAS_POV                                                  30
#define RSRTX_VAL_MEAS_NOV                                                  31
#define RSRTX_VAL_MEAS_TBFR                                                 32
#define RSRTX_VAL_MEAS_TBP                                                  33
#define RSRTX_VAL_MEAS_SRR                                                  34
#define RSRTX_VAL_MEAS_SRF                                                  35
#define RSRTX_VAL_MEAS_DTOT                                                 36

// rsrtx_rngProtocolType
#define RSRTX_VAL_PTYPE_PARALLEL                                            0
#define RSRTX_VAL_PTYPE_CPARALLEL                                           1
#define RSRTX_VAL_PTYPE_I2C                                                 2
#define RSRTX_VAL_PTYPE_SPI                                                 3
#define RSRTX_VAL_PTYPE_SSPI                                                4
#define RSRTX_VAL_PTYPE_UART                                                5
#define RSRTX_VAL_PTYPE_CAN                                                 6
#define RSRTX_VAL_PTYPE_LIN                                                 7
#define RSRTX_VAL_PTYPE_AUDIO                                               8
#define RSRTX_VAL_PTYPE_MILSTD                                              9
#define RSRTX_VAL_PTYPE_ARINC                                               10

// rsrtx_rngProtocolFormat
#define RSRTX_VAL_PFORMAT_ASCI                                              0
#define RSRTX_VAL_PFORMAT_HEX                                               1
#define RSRTX_VAL_PFORMAT_BIN                                               2
#define RSRTX_VAL_PFORMAT_DEC                                               3
#define RSRTX_VAL_PFORMAT_OCT                                               4

// rsrtx_rngProtocolHeight
#define RSRTX_VAL_PHEIGHT_SMALL                                             0
#define RSRTX_VAL_PHEIGHT_MEDIUM                                            1
#define RSRTX_VAL_PHEIGHT_LARGE                                             2
#define RSRTX_VAL_PHEIGHT_DIV1                                              3
#define RSRTX_VAL_PHEIGHT_DIV2                                              4
#define RSRTX_VAL_PHEIGHT_DIV4                                              5
#define RSRTX_VAL_PHEIGHT_DIV8                                              6

// rsrtx_rngRelativeMode
#define RSRTX_VAL_MEAS_RELATIVE_TEN                                         0
#define RSRTX_VAL_MEAS_RELATIVE_TWENTY                                      1
#define RSRTX_VAL_MEAS_RELATIVE_FIVE                                        2
#define RSRTX_VAL_MEAS_RELATIVE_USER                                        3

// rsrtx_rngChannelPolarity
#define RSRTX_VAL_POLARITY_NORM                                             0
#define RSRTX_VAL_POLARITY_INV                                              1

// rsrtx_rngExternalTriggerCoupling
#define RSRTX_VAL_COUPLING_AC                                               0
#define RSRTX_VAL_COUPLING_DC                                               1

// rsrtx_rngSearchCondition
#define RSRTX_VAL_SEARCHCOND_EDGE                                           0
#define RSRTX_VAL_SEARCHCOND_WIDTH                                          1
#define RSRTX_VAL_SEARCHCOND_PEAK                                           2
#define RSRTX_VAL_SEARCHCOND_RUNT                                           3
#define RSRTX_VAL_SEARCHCOND_RTIME                                          4
#define RSRTX_VAL_SEARCHCOND_D2C                                            5
#define RSRTX_VAL_SEARCHCOND_PATTERN                                        6
#define RSRTX_VAL_SEARCHCOND_PROTOCOL                                       7
#define RSRTX_VAL_SEARCHCOND_WINDOW                                         8

// rsrtx_rngSearchSource
#define RSRTX_VAL_MEASUREMENT_SOURCE_C1                                     0
#define RSRTX_VAL_MEASUREMENT_SOURCE_C2                                     1
#define RSRTX_VAL_MEASUREMENT_SOURCE_C3                                     2
#define RSRTX_VAL_MEASUREMENT_SOURCE_C4                                     3
#define RSRTX_VAL_MEASUREMENT_SOURCE_MA1                                    4
#define RSRTX_VAL_MEASUREMENT_SOURCE_MA2                                    5
#define RSRTX_VAL_MEASUREMENT_SOURCE_MA3                                    6
#define RSRTX_VAL_MEASUREMENT_SOURCE_MA4                                    7
#define RSRTX_VAL_MEASUREMENT_SOURCE_RE1                                    8
#define RSRTX_VAL_MEASUREMENT_SOURCE_RE2                                    9
#define RSRTX_VAL_MEASUREMENT_SOURCE_RE3                                    10
#define RSRTX_VAL_MEASUREMENT_SOURCE_RE4                                    11
#define RSRTX_VAL_MEASUREMENT_SOURCE_SBUS1                                  12
#define RSRTX_VAL_MEASUREMENT_SOURCE_SBUS2                                  13
#define RSRTX_VAL_MEASUREMENT_SOURCE_SBUS3                                  14
#define RSRTX_VAL_MEASUREMENT_SOURCE_SBUS4                                  15
#define RSRTX_VAL_MEASUREMENT_SOURCE_QMA                                    37

// rsrtx_rngScalingUnit
#define RSRTX_VAL_FFT_LIN                                                   0
#define RSRTX_VAL_FFT_DBM                                                   1
#define RSRTX_VAL_FFT_DBV                                                   2

// rsrtx_rngProbeUnit
#define RSRTX_VAL_PROBE_UNIT_V                                              0
#define RSRTX_VAL_PROBE_UNIT_A                                              1

// rsrtx_rngWaveformSamplesRange
#define RSRTX_VAL_WAVEFORM_SAMPLES_DEFAULT                                  0
#define RSRTX_VAL_WAVEFORM_SAMPLES_MAXIMUM                                  1
#define RSRTX_VAL_WAVEFORM_SAMPLES_DISPLAY_MAXIMUM                          2

// rsrtx_rngMaskTestActionExecution
#define RSRTX_VAL_MASK_ACTION_EXECUTION_OFF                                 0
#define RSRTX_VAL_MASK_ACTION_EXECUTION_EACH                                1
#define RSRTX_VAL_MASK_ACTION_EXECUTION_SINGLE                              2
#define RSRTX_VAL_MASK_ACTION_EXECUTION_CYCLIC                              3

// rsrtx_rngSearchTriggerPatternCombination
#define RSRTX_VAL_PATTERN_COMBINATION_AND                                   0
#define RSRTX_VAL_PATTERN_COMBINATION_OR                                    1
#define RSRTX_VAL_PATTERN_COMBINATION_NAND                                  2
#define RSRTX_VAL_PATTERN_COMBINATION_NOR                                   3

// rsrtx_rngSearchGateMode
#define RSRTX_VAL_SEARCH_GATE_ALL                                           0
#define RSRTX_VAL_SEARCH_GATE_DISPLAY                                       1
#define RSRTX_VAL_SEARCH_GATE_USER                                          2

// rsrtx_rngProtocolSPITriggerSource
#define RSRTX_VAL_SPI_MISO                                                  3
#define RSRTX_VAL_SPI_MOSI                                                  4

// rsrtx_rngProtocolLINStandard
#define RSRTX_VAL_LIN_STANDARD_AUTO                                         0
#define RSRTX_VAL_LIN_STANDARD_1X                                           1
#define RSRTX_VAL_LIN_STANDARD_2X                                           2
#define RSRTX_VAL_LIN_STANDARD_J2602                                        3

// rsrtx_rngProtocolLINTriggerMode
#define RSRTX_VAL_LIN_FRAME_START                                           0
#define RSRTX_VAL_LIN_FRAME_ID                                              1
#define RSRTX_VAL_LIN_FRAME_ID_DATA                                         2
#define RSRTX_VAL_LIN_FRAME_WAKEUP                                          3
#define RSRTX_VAL_LIN_ERR_COND                                              4

// rsrtx_rngProtocolCondition
#define RSRTX_VAL_COND_NQ                                                   0
#define RSRTX_VAL_COND_EQ                                                   1
#define RSRTX_VAL_COND_LT                                                   2
#define RSRTX_VAL_COND_GT                                                   3

// rsrtx_rngProtocolSearchEvent
#define RSRTX_VAL_SEARCH_EVENT_FRAME                                        0
#define RSRTX_VAL_SEARCH_EVENT_ERROR                                        1
#define RSRTX_VAL_SEARCH_EVENT_ID                                           2
#define RSRTX_VAL_SEARCH_EVENT_IDDT                                         3
#define RSRTX_VAL_SEARCH_EVENT_IDERR                                        4

// rsrtx_rngProtocolLINSearchFrameSetup
#define RSRTX_VAL_LIN_SEARCH_FRAME_SOF                                      0
#define RSRTX_VAL_LIN_SEARCH_FRAME_WAKEUP                                   1

// rsrtx_rngProtocolCANLineType
#define RSRTX_VAL_CAN_LOW                                                   0
#define RSRTX_VAL_CAN_HIGH                                                  1

// rsrtx_rngProtocolCANTriggerMode
#define RSRTX_VAL_CAN_FRAME_START                                           0
#define RSRTX_VAL_CAN_FRAME_END                                             1
#define RSRTX_VAL_CAN_MSG_ID                                                2
#define RSRTX_VAL_CAN_MSG_IDDT                                              3
#define RSRTX_VAL_CAN_FRAME_TYPE                                            4
#define RSRTX_VAL_CAN_ERROR_COND                                            5

// rsrtx_rngProtocolCANTriggerFrameType
#define RSRTX_VAL_CAN_FRAME_TYPE_DATA                                       0
#define RSRTX_VAL_CAN_FRAME_TYPE_REMOTE                                     1
#define RSRTX_VAL_CAN_FRAME_TYPE_ERROR                                      2
#define RSRTX_VAL_CAN_FRAME_TYPE_OVER_LOAD                                  3
#define RSRTX_VAL_CAN_FRAME_TYPE_ANY                                        4

// rsrtx_rngProtocolCANIDType
#define RSRTX_VAL_CAN_ID_TYPE_B11                                           0
#define RSRTX_VAL_CAN_ID_TYPE_B29                                           1
#define RSRTX_VAL_CAN_ID_TYPE_ANY                                           2

// rsrtx_rngProtocolCANSearchFrameSetup
#define RSRTX_VAL_CAN_SEARCH_FRAME_SOF                                      0
#define RSRTX_VAL_CAN_SEARCH_FRAME_EOF                                      1
#define RSRTX_VAL_CAN_SEARCH_FRAME_OVER                                     2
#define RSRTX_VAL_CAN_SEARCH_FRAME_ERR                                      3
#define RSRTX_VAL_CAN_SEARCH_FRAME_DTA11                                    4
#define RSRTX_VAL_CAN_SEARCH_FRAME_DTA29                                    5
#define RSRTX_VAL_CAN_SEARCH_FRAME_REM11                                    6
#define RSRTX_VAL_CAN_SEARCH_FRAME_REM29                                    7

// rsrtx_rngProtocolCANSearchFrameType
#define RSRTX_VAL_CAN_SEARCH_FRAME_TYPE_DATA                                0
#define RSRTX_VAL_CAN_SEARCH_FRAME_TYPE_REMOTE                              1
#define RSRTX_VAL_CAN_SEARCH_FRAME_TYPE_ANY                                 2

// rsrtx_rngProtocolLINPolarity
#define RSRTX_VAL_LIN_ACTLOW                                                0
#define RSRTX_VAL_LIN_ACTHIGH                                               1

// rsrtx_rngDigitalHysteresis
#define RSRTX_VAL_DIGITAL_HYSTERESIS_SMALL                                  0
#define RSRTX_VAL_DIGITAL_HYSTERESIS_MEDIUM                                 1
#define RSRTX_VAL_DIGITAL_HYSTERESIS_LARGE                                  2

// rsrtx_rngTriggerHoldoffMode
#define RSRTX_VAL_HOLDOFF_MODE_TIME                                         0
#define RSRTX_VAL_HOLDOFF_MODE_OFF                                          1

// rsrtx_rngTriggerPatternMode
#define RSRTX_VAL_PATTERN_MODE_OFF                                          0
#define RSRTX_VAL_PATTERN_MODE_TIMEOUT                                      1
#define RSRTX_VAL_PATTERN_MODE_WIDTH                                        2

// rsrtx_rngTriggerOutMode
#define RSRTX_VAL_TRIGGER_OUT_MODE_OFF                                      0
#define RSRTX_VAL_TRIGGER_OUT_MODE_TRIG                                     1
#define RSRTX_VAL_TRIGGER_OUT_MODE_MASK                                     2
#define RSRTX_VAL_TRIGGER_OUT_MODE_REF                                      3
#define RSRTX_VAL_TRIGGER_OUT_MODE_GEN                                      4

// rsrtx_rngDigitalTechnology
#define RSRTX_VAL_DIGITAL_TECHNOLOGY_TTL                                    0
#define RSRTX_VAL_DIGITAL_TECHNOLOGY_ECL                                    1
#define RSRTX_VAL_DIGITAL_TECHNOLOGY_CMOS                                   2
#define RSRTX_VAL_DIGITAL_TECHNOLOGY_MANUAL                                 3

// rsrtx_rngParallelBusFrameEnabled
#define RSRTX_PARALLEL_BUS_ENABLED_OK                                       0
#define RSRTX_PARALLEL_BUS_ENABLED_ERROR                                    1
#define RSRTX_PARALLEL_BUS_ENABLED_INS                                      2

// rsrtx_rngI2CFrameTransferDirection
#define RSRTX_VAL_TRANSFER_DIRECTION_INC                                    0
#define RSRTX_VAL_TRANSFER_DIRECTION_READ                                   1
#define RSRTX_VAL_TRANSFER_DIRECTION_WRITE                                  2
#define RSRTX_VAL_TRANSFER_DIRECTION_EITH                                   3
#define RSRTX_VAL_TRANSFER_DIRECTION_UNDF                                   4

// rsrtx_rngFrameAddressLength
#define RSRTX_VAL_FRAME_ADDRESS_LENGTH_BIT7                                 0
#define RSRTX_VAL_FRAME_ADDRESS_LENGTH_BIT10                                1

// rsrtx_rngLINFrameStatus
#define RSRTX_VAL_LIN_FRAME_STATUS_OK                                       0
#define RSRTX_VAL_LIN_FRAME_STATUS_UART                                     1
#define RSRTX_VAL_LIN_FRAME_STATUS_CHCK                                     2
#define RSRTX_VAL_LIN_FRAME_STATUS_PRER                                     3
#define RSRTX_VAL_LIN_FRAME_STATUS_SYER                                     4
#define RSRTX_VAL_LIN_FRAME_STATUS_WAK                                      5
#define RSRTX_VAL_LIN_FRAME_STATUS_INS                                      6
#define RSRTX_VAL_LIN_FRAME_STATUS_ERR                                      7
#define RSRTX_VAL_LIN_FRAME_STATUS_LEN                                      8

// rsrtx_rngLINChecksum
#define RSRTX_VAL_LIN_CHECKSUM_OK                                           0
#define RSRTX_VAL_LIN_CHECKSUM_ERR                                          1
#define RSRTX_VAL_LIN_CHECKSUM_UNDF                                         2

// rsrtx_rngLINParity
#define RSRTX_VAL_LIN_PARITY_OK                                             0
#define RSRTX_VAL_LIN_PARITY_PRER                                           1
#define RSRTX_VAL_LIN_PARITY_UVAL                                           2
#define RSRTX_VAL_LIN_PARITY_INS                                            3

// rsrtx_rngLINFrameVersion
#define RSRTX_VAL_FRAME_VERSION_V1X                                         0
#define RSRTX_VAL_FRAME_VERSION_V2X                                         1
#define RSRTX_VAL_FRAME_VERSION_UNK                                         2

// rsrtx_rngLINByteEnabled
#define RSRTX_VAL_LIN_BYTE_ENABLED_OK                                       0
#define RSRTX_VAL_LIN_BYTE_ENABLED_INS                                      1
#define RSRTX_VAL_LIN_BYTE_ENABLED_UART                                     2

// rsrtx_rngUARTWordEnabled
#define RSRTX_VAL_UART_STATE_OK                                             0
#define RSRTX_VAL_UART_STATE_FRST                                           1
#define RSRTX_VAL_UART_STATE_FREN                                           2
#define RSRTX_VAL_UART_STATE_FRME                                           3
#define RSRTX_VAL_UART_STATE_STER                                           4
#define RSRTX_VAL_UART_STATE_SPER                                           5
#define RSRTX_VAL_UART_STATE_PRER                                           6
#define RSRTX_VAL_UART_STATE_INS                                            7
#define RSRTX_VAL_UART_STATE_BRE                                            8

// rsrtx_rngCANFrameType
#define RSRTX_VAL_CAN_FRAME_TYPE_REM                                        1
#define RSRTX_VAL_CAN_FRAME_TYPE_ERR                                        2
#define RSRTX_VAL_CAN_FRAME_TYPE_OVLD                                       3

// rsrtx_rngCANFrameStatus
#define RSRTX_VAL_CAN_FRAME_STATUS_OK                                       0
#define RSRTX_VAL_CAN_FRAME_STATUS_BTST                                     1
#define RSRTX_VAL_CAN_FRAME_STATUS_CRCD                                     2
#define RSRTX_VAL_CAN_FRAME_STATUS_ACKD                                     3
#define RSRTX_VAL_CAN_FRAME_STATUS_CRC                                      4
#define RSRTX_VAL_CAN_FRAME_STATUS_EOFD                                     5
#define RSRTX_VAL_CAN_FRAME_STATUS_NOAC                                     6
#define RSRTX_VAL_CAN_FRAME_STATUS_INS                                      7

// rsrtx_rngCANAckState
#define RSRTX_VAL_CAN_ACK_OK                                                0
#define RSRTX_VAL_CAN_ACK_UNDF                                              1

// rsrtx_rngMeasurementSource
#define RSRTX_VAL_MEASUREMENT_SOURCE_NONE                                   0
#define RSRTX_VAL_MEASUREMENT_SOURCE_CH1                                    1
#define RSRTX_VAL_MEASUREMENT_SOURCE_CH2                                    2
#define RSRTX_VAL_MEASUREMENT_SOURCE_CH3                                    3
#define RSRTX_VAL_MEASUREMENT_SOURCE_CH4                                    4
#define RSRTX_VAL_MEASUREMENT_SOURCE_M1                                     5
#define RSRTX_VAL_MEASUREMENT_SOURCE_M2                                     6
#define RSRTX_VAL_MEASUREMENT_SOURCE_M3                                     7
#define RSRTX_VAL_MEASUREMENT_SOURCE_M4                                     8
#define RSRTX_VAL_MEASUREMENT_SOURCE_M5                                     9
#define RSRTX_VAL_MEASUREMENT_SOURCE_R1                                     10
#define RSRTX_VAL_MEASUREMENT_SOURCE_R2                                     11
#define RSRTX_VAL_MEASUREMENT_SOURCE_R3                                     12
#define RSRTX_VAL_MEASUREMENT_SOURCE_R4                                     13
#define RSRTX_VAL_MEASUREMENT_SOURCE_TRIG                                   14
#define RSRTX_VAL_MEASUREMENT_SOURCE_D1                                     15
#define RSRTX_VAL_MEASUREMENT_SOURCE_D2                                     16
#define RSRTX_VAL_MEASUREMENT_SOURCE_D3                                     17
#define RSRTX_VAL_MEASUREMENT_SOURCE_D4                                     18
#define RSRTX_VAL_MEASUREMENT_SOURCE_D5                                     19
#define RSRTX_VAL_MEASUREMENT_SOURCE_D6                                     20
#define RSRTX_VAL_MEASUREMENT_SOURCE_D7                                     21
#define RSRTX_VAL_MEASUREMENT_SOURCE_D8                                     22
#define RSRTX_VAL_MEASUREMENT_SOURCE_D9                                     23
#define RSRTX_VAL_MEASUREMENT_SOURCE_D10                                    24
#define RSRTX_VAL_MEASUREMENT_SOURCE_D11                                    25
#define RSRTX_VAL_MEASUREMENT_SOURCE_D12                                    26
#define RSRTX_VAL_MEASUREMENT_SOURCE_D13                                    27
#define RSRTX_VAL_MEASUREMENT_SOURCE_D14                                    28
#define RSRTX_VAL_MEASUREMENT_SOURCE_D15                                    29
#define RSRTX_VAL_MEASUREMENT_SOURCE_D70                                    30
#define RSRTX_VAL_MEASUREMENT_SOURCE_D158                                   31
#define RSRTX_VAL_MEASUREMENT_SOURCE_D0                                     32
#define RSRTX_VAL_MEASUREMENT_SOURCE_SPEC                                   33
#define RSRTX_VAL_MEASUREMENT_SOURCE_MINH                                   34
#define RSRTX_VAL_MEASUREMENT_SOURCE_MAXH                                   35
#define RSRTX_VAL_MEASUREMENT_SOURCE_AVER                                   36

// rsrtx_rngPowerAnalysisType
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_OFF                                   0
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_QUAL                                  1
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_CONS                                  2
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_HARM                                  3
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_RIPP                                  4
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_SPEC                                  5
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_SLEW                                  6
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_DONR                                  7
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_EFFS                                  8
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_TURN                                  9
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_TRAN                                  10
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_SWITC                                 11
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_MOD                                   12
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_INR                                   13
#define RSRTX_VAL_POWER_ANALYSIS_TYPE_SOA                                   14

// rsrtx_rngStatistics
#define RSRTX_VAL_STATISTICS_ACT                                            0
#define RSRTX_VAL_STATISTICS_AVG                                            1
#define RSRTX_VAL_STATISTICS_STDD                                           2
#define RSRTX_VAL_STATISTICS_NPE                                            3
#define RSRTX_VAL_STATISTICS_PPE                                            4
#define RSRTX_VAL_STATISTICS_WFMC                                           5

// rsrtx_rngQualityType
#define RSRTX_VAL_QUALITY_TYPE_RMS                                          0
#define RSRTX_VAL_QUALITY_TYPE_FREQ                                         1
#define RSRTX_VAL_QUALITY_TYPE_CRES                                         2

// rsrtx_rngQualityTypePower
#define RSRTX_VAL_QUALITY_TYPE_POWER_REAL                                   0
#define RSRTX_VAL_QUALITY_TYPE_POWER_REAC                                   1
#define RSRTX_VAL_QUALITY_TYPE_POWER_APP                                    2
#define RSRTX_VAL_QUALITY_TYPE_POWER_PFAC                                   3
#define RSRTX_VAL_QUALITY_TYPE_POWER_PHAS                                   4

// rsrtx_rngHarmonicsStandard
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_ENA                            0
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_ENB                            1
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_ENC                            2
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_END                            3
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_MIL                            4
#define RSRTX_VAL_CURRENT_HARMONICS_STANDARD_RTC                            5

// rsrtx_rngHarmonicsType
#define RSRTX_VAL_HARMONICS_TYPE_VIOLENT_COUNT                              0
#define RSRTX_VAL_HARMONICS_TYPE_FREQUENCY                                  1
#define RSRTX_VAL_HARMONICS_TYPE_LEVEL                                      2
#define RSRTX_VAL_HARMONICS_TYPE_MINIMUM                                    3
#define RSRTX_VAL_HARMONICS_TYPE_MAXIMUM                                    4
#define RSRTX_VAL_HARMONICS_TYPE_AVERAGE                                    5
#define RSRTX_VAL_HARMONICS_TYPE_LIMIT                                      6
#define RSRTX_VAL_HARMONICS_TYPE_WFMC                                       7

// rsrtx_rngLimitCheck
#define RSRTX_VAL_FAIL                                                      0
#define RSRTX_VAL_PASS                                                      1

// rsrtx_rngRippleType
#define RSRTX_VAL_RIPPLE_TYPE_FREQUENCY                                     0
#define RSRTX_VAL_RIPPLE_TYPE_PEAK                                          1
#define RSRTX_VAL_RIPPLE_TYPE_STD_DEV                                       2
#define RSRTX_VAL_RIPPLE_TYPE_UPEAK                                         3
#define RSRTX_VAL_RIPPLE_TYPE_LPEAK                                         4
#define RSRTX_VAL_RIPPLE_TYPE_MEAN                                          5
#define RSRTX_VAL_RIPPLE_TYPE_PERIOD                                        6
#define RSRTX_VAL_RIPPLE_TYPE_PDCYCLE                                       7
#define RSRTX_VAL_RIPPLE_TYPE_NDCYCLE                                       8

// rsrtx_rngSpectrumType
#define RSRTX_VAL_SPECTRUM_TYPE_FREQUENCY                                   0
#define RSRTX_VAL_SPECTRUM_TYPE_LEVEL                                       1
#define RSRTX_VAL_SPECTRUM_TYPE_MINIMUM                                     2
#define RSRTX_VAL_SPECTRUM_TYPE_MAXIMUM                                     3
#define RSRTX_VAL_SPECTRUM_TYPE_AVERAGE                                     4
#define RSRTX_VAL_SPECTRUM_TYPE_WFMC                                        5

// rsrtx_rngHarmonicsFundamental
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_AUTO                                0
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_F60                                 1
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_F50                                 2

// rsrtx_rngSlewRateType
#define RSRTX_VAL_SLEW_RATE_TYPE_UPEAK                                      1
#define RSRTX_VAL_SLEW_RATE_TYPE_LPEAK                                      0

// rsrtx_rngModulationType
#define RSRTX_VAL_MODULATION_TYPE_PER                                       0
#define RSRTX_VAL_MODULATION_TYPE_FREQ                                      1
#define RSRTX_VAL_MODULATION_TYPE_PDCY                                      2
#define RSRTX_VAL_MODULATION_TYPE_NDCY                                      3
#define RSRTX_VAL_MODULATION_TYPE_PPW                                       4
#define RSRTX_VAL_MODULATION_TYPE_NPW                                       5

// rsrtx_rngModulationResultType
#define RSRTX_VAL_MODULATION_RESULT_TYPE_LPE                                0
#define RSRTX_VAL_MODULATION_RESULT_TYPE_UPE                                1
#define RSRTX_VAL_MODULATION_RESULT_TYPE_MEAN                               2
#define RSRTX_VAL_MODULATION_RESULT_TYPE_RMS                                3
#define RSRTX_VAL_MODULATION_RESULT_TYPE_STDD                               4

// rsrtx_rngEfficiencyType
#define RSRTX_VAL_EFFICIENCY_TYPE_EFFICIENCY                                0
#define RSRTX_VAL_EFFICIENCY_TYPE_INPUT                                     1
#define RSRTX_VAL_EFFICIENCY_TYPE_OUTPUT                                    2

// rsrtx_rngSwitchinglossType
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_ENERGY                                 0
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_POWER                                  1

// rsrtx_rngOnOffType
#define RSRTX_VAL_ON_OFF_TYPE_ON                                            1
#define RSRTX_VAL_ON_OFF_TYPE_OFF                                           0

// rsrtx_rngPowerAnalysisSource
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_CH1                                 1
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_CH2                                 2
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_CH3                                 3
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_CH4                                 4
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_RE1                                 5
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_RE2                                 6
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_RE3                                 7
#define RSRTX_VAL_POWER_ANALYSIS_SOURCE_RE4                                 8

// rsrtx_rngAudioVariant
#define RSRTX_VAL_AUDIO_VARIANT_I2S                                         0
#define RSRTX_VAL_AUDIO_VARIANT_LJ                                          1
#define RSRTX_VAL_AUDIO_VARIANT_RJ                                          2
#define RSRTX_VAL_AUDIO_VARIANT_TDM                                         3

// rsrtx_rngAudioClockPolarity
#define RSRTX_VAL_FALLING                                                   0
#define RSRTX_VAL_RISING                                                    1

// rsrtx_rngAudioWSPolarity
#define RSRTX_VAL_NORMAL                                                    0
#define RSRTX_VAL_INVERT                                                    1

// rsrtx_rngAudioChannelOrder
#define RSRTX_VAL_AUDIO_ORDER_LEFT                                          0
#define RSRTX_VAL_AUDIO_ORDER_RIGHT                                         1

// rsrtx_rngProtocolAudioBitOrder
#define RSRTX_VAL_AUDIO_MSBF                                                0
#define RSRTX_VAL_AUDIO_LSBF                                                1

// rsrtx_rngAudioTriggerType
#define RSRTX_VAL_AUDIO_TRIGGER_DATA                                        0
#define RSRTX_VAL_AUDIO_TRIGGER_WINDOW                                      1
#define RSRTX_VAL_AUDIO_TRIGGER_WSEL                                        2
#define RSRTX_VAL_AUDIO_TRIGGER_ECON                                        3

// rsrtx_rngAudioFrameStatus
#define RSRTX_VAL_AUDIO_FRAME_STATE_OK                                      0
#define RSRTX_VAL_AUDIO_FRAME_STATE_ERR                                     1
#define RSRTX_VAL_AUDIO_FRAME_STATE_INS                                     2

// rsrtx_rngTrackDisplayMode
#define RSRTX_VAL_TRACK_DISPLAY_MODE_SEQ                                    0
#define RSRTX_VAL_TRACK_DISPLAY_MODE_PAR                                    1
#define RSRTX_VAL_TRACK_DISPLAY_MODE_STR                                    2
#define RSRTX_VAL_TRACK_DISPLAY_MODE_PTR                                    3
#define RSRTX_VAL_TRACK_DISPLAY_MODE_TRAC                                   4
#define RSRTX_VAL_TRACK_DISPLAY_MODE_SDS                                    5

// rsrtx_rngAudioTriggerCondition
#define RSRTX_VAL_AUDIO_CONDITION_OFF                                       0
#define RSRTX_VAL_AUDIO_CONDITION_EQU                                       1
#define RSRTX_VAL_AUDIO_CONDITION_NEQ                                       2
#define RSRTX_VAL_AUDIO_CONDITION_GTH                                       3
#define RSRTX_VAL_AUDIO_CONDITION_LTH                                       4
#define RSRTX_VAL_AUDIO_CONDITION_INR                                       5
#define RSRTX_VAL_AUDIO_CONDITION_OOR                                       6

// rsrtx_rngAudioTriggerCombination
#define RSRTX_VAL_AUDIO_COMBINATION_AND                                     0
#define RSRTX_VAL_AUDIO_COMBINATION_OR                                      1

// rsrtx_rngSelfAlignmentState
#define RSRTX_VAL_SELF_ALIGNMENT_NO_ALIGNMENT                               0
#define RSRTX_VAL_SELF_ALIGNMENT_RUN                                        1
#define RSRTX_VAL_SELF_ALIGNMENT_ERROR                                      2
#define RSRTX_VAL_SELF_ALIGNMENT_OK                                         3
#define RSRTX_VAL_SELF_ALIGNMENT_ABORT                                      4

// rsrtx_rngMILSTDCodeType
#define RSRTX_VAL_MILSTD_CODE_TYPE_DBC                                      0
#define RSRTX_VAL_MILSTD_CODE_TYPE_TSYN                                     1
#define RSRTX_VAL_MILSTD_CODE_TYPE_TST                                      2
#define RSRTX_VAL_MILSTD_CODE_TYPE_SEL                                      3
#define RSRTX_VAL_MILSTD_CODE_TYPE_TSH                                      4
#define RSRTX_VAL_MILSTD_CODE_TYPE_OTSH                                     5
#define RSRTX_VAL_MILSTD_CODE_TYPE_ITER                                     6
#define RSRTX_VAL_MILSTD_CODE_TYPE_OIT                                      7
#define RSRTX_VAL_MILSTD_CODE_TYPE_RES                                      8
#define RSRTX_VAL_MILSTD_CODE_TYPE_VECT                                     9
#define RSRTX_VAL_MILSTD_CODE_TYPE_RSYN                                     10
#define RSRTX_VAL_MILSTD_CODE_TYPE_TLAS                                     11
#define RSRTX_VAL_MILSTD_CODE_TYPE_BITW                                     12
#define RSRTX_VAL_MILSTD_CODE_TYPE_STSH                                     13
#define RSRTX_VAL_MILSTD_CODE_TYPE_OSTS                                     14
#define RSRTX_VAL_MILSTD_CODE_TYPE_ANY                                      15

// rsrtx_rngMILSTDStatus
#define RSRTX_VAL_MILSTD_STATUS_OK                                          0
#define RSRTX_VAL_MILSTD_STATUS_INS                                         1
#define RSRTX_VAL_MILSTD_STATUS_PERR                                        2
#define RSRTX_VAL_MILSTD_STATUS_MERR                                        3
#define RSRTX_VAL_MILSTD_STATUS_TERR                                        4
#define RSRTX_VAL_MILSTD_STATUS_SERR                                        5

// rsrtx_rngMILSTDDirection
#define RSRTX_VAL_MILSTD_DIRECTION_TRANSMIT                                 0
#define RSRTX_VAL_MILSTD_DIRECTION_RECEIVE                                  1
#define RSRTX_VAL_MILSTD_DIRECTION_EITHER                                   2

// rsrtx_rngMILSTDType
#define RSRTX_VAL_MILSTD_TYPE_COMMAND                                       0
#define RSRTX_VAL_MILSTD_TYPE_STATUS                                        1
#define RSRTX_VAL_MILSTD_TYPE_DATA                                          2
#define RSRTX_VAL_MILSTD_TYPE_CMCMODE                                       3

// rsrtx_rngMILSTDTriggerType
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_SYNC                                  0
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_FRAME                                 1
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_ERROR                                 2
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_STATUS                                3
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_DATA                                  4
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_COMMAND                               5
#define RSRTX_VAL_MILSTD_TRIGGER_TYPE_CDATA                                 6

// rsrtx_rngMILSTDTriggerSync
#define RSRTX_VAL_MILSTD_TRIGGER_SYNC_CST                                   0
#define RSRTX_VAL_MILSTD_TRIGGER_SYNC_DATA                                  1
#define RSRTX_VAL_MILSTD_TRIGGER_SYNC_ALL                                   2

// rsrtx_rngMILSTDTriggerWord
#define RSRTX_VAL_MILSTD_TRIGGER_WORD_COMMAND                               0
#define RSRTX_VAL_MILSTD_TRIGGER_WORD_STATUS                                1
#define RSRTX_VAL_MILSTD_TRIGGER_WORD_DATA                                  2
#define RSRTX_VAL_MILSTD_TRIGGER_WORD_ALL                                   3

// rsrtx_rngMILSTDTriggerCommandType
#define RSRTX_VAL_MILSTD_TRIGGER_COMMAND_AWORD                              0
#define RSRTX_VAL_MILSTD_TRIGGER_COMMAND_MCODE                              1

// rsrtx_rngMILSTDCondition
#define RSRTX_VAL_MILSTD_CONDITION_OFF                                      0
#define RSRTX_VAL_MILSTD_CONDITION_EQU                                      1
#define RSRTX_VAL_MILSTD_CONDITION_NEQ                                      2
#define RSRTX_VAL_MILSTD_CONDITION_GTH                                      3
#define RSRTX_VAL_MILSTD_CONDITION_GEQ                                      4
#define RSRTX_VAL_MILSTD_CONDITION_LEQ                                      5
#define RSRTX_VAL_MILSTD_CONDITION_LTH                                      6
#define RSRTX_VAL_MILSTD_CONDITION_WITH                                     7
#define RSRTX_VAL_MILSTD_CONDITION_OUTS                                     8

// rsrtx_rngMILSTDSubAddress
#define RSRTX_VAL_MILSTD_TRIGGER_SUB_ADDRESS_A0                             0
#define RSRTX_VAL_MILSTD_TRIGGER_SUB_ADDRESS_A31                            1
#define RSRTX_VAL_MILSTD_TRIGGER_SUB_ADDRESS_EITH                           2

// rsrtx_rngMILSTDSearchCondition
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_WORD_START                        0
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_ERROR                             1
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_STATUS                            2
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_DATA                              3
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_COMMAND                           4
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_MODE_CODE                         5
#define RSRTX_VAL_MILSTD_SEARCH_CONDITION_COMMAND_DATA                      6

// rsrtx_rngMILSTDSearchError
#define RSRTX_VAL_MILSTD_SEARCH_ERROR_SYNCHRONIZATION                       0
#define RSRTX_VAL_MILSTD_SEARCH_ERROR_PARITY                                1
#define RSRTX_VAL_MILSTD_SEARCH_ERROR_TIMEOUT                               2
#define RSRTX_VAL_MILSTD_SEARCH_ERROR_MANCHESTER                            3
#define RSRTX_VAL_MILSTD_SEARCH_ERROR_ANY                                   4

// rsrtx_rngHistoryPlayer
#define RSRTX_VAL_HISTORY_PLAYER_RUN                                        1
#define RSRTX_VAL_HISTORY_PLAYER_STOP                                       0

// rsrtx_rngHistorySpeed
#define RSRTX_VAL_HISTORY_SPEED_SLOW                                        0
#define RSRTX_VAL_HISTORY_SPEED_MEDIUM                                      1
#define RSRTX_VAL_HISTORY_SPEED_FAST                                        2
#define RSRTX_VAL_HISTORY_SPEED_AUTO                                        3

// rsrtx_rngThresholdHysteresis
#define RSRTX_VAL_TRESHOLD_HYSTERESIS_SMALL                                 0
#define RSRTX_VAL_TRESHOLD_HYSTERESIS_MEDIUM                                1
#define RSRTX_VAL_TRESHOLD_HYSTERESIS_LARGE                                 2

// rsrtx_rngStatus
#define RSRTX_VAL_STATUS_0                                                  0
#define RSRTX_VAL_STATUS_1                                                  1
#define RSRTX_VAL_STATUS_X                                                  2

// rsrtx_rngProtocolARINC429Polarity
#define RSRTX_VAL_ARINC429_POLARITY_ALEG                                    0
#define RSRTX_VAL_ARINC429_POLARITY_BLEG                                    1
#define RSRTX_VAL_ARINC429_POLARITY_NORM                                    2
#define RSRTX_VAL_ARINC429_POLARITY_INV                                     3

// rsrtx_rngProtocolARINC429BitRateMode
#define RSRTX_VAL_ARINC429_BIT_RATE_MODE_LOW                                0
#define RSRTX_VAL_ARINC429_BIT_RATE_MODE_HIGH                               1
#define RSRTX_VAL_ARINC429_BIT_RATE_MODE_USER                               2

// rsrtx_rngARINC429WordStatus
#define RSRTX_VAL_ARINC_WORD_STATUS_OK                                      0
#define RSRTX_VAL_ARINC_WORD_STATUS_CERR                                    1
#define RSRTX_VAL_ARINC_WORD_STATUS_GERR                                    2
#define RSRTX_VAL_ARINC_WORD_STATUS_PRER                                    3
#define RSRTX_VAL_ARINC_WORD_STATUS_INS                                     4
#define RSRTX_VAL_ARINC_WORD_STATUS_INC                                     5

// rsrtx_rngProtocolARINC429DataFormat
#define RSRTX_VAL_ARINC429_DATA_FORMAT_DATA                                 0
#define RSRTX_VAL_ARINC429_DATA_FORMAT_DSSM                                 1
#define RSRTX_VAL_ARINC429_DATA_FORMAT_DSDI                                 2
#define RSRTX_VAL_ARINC429_DATA_FORMAT_DSSS                                 3

// rsrtx_rngProtocolARINC429Operator
#define RSRTX_VAL_ARINC_COND_NQ                                             0
#define RSRTX_VAL_ARINC_COND_EQ                                             1
#define RSRTX_VAL_ARINC_COND_LT                                             2
#define RSRTX_VAL_ARINC_COND_LE                                             3
#define RSRTX_VAL_ARINC_COND_GT                                             4
#define RSRTX_VAL_ARINC_COND_GE                                             5
#define RSRTX_VAL_ARINC_COND_WITH                                           6
#define RSRTX_VAL_ARINC_COND_OUTS                                           7

// rsrtx_rngARINCSsmSdi
#define RSRTX_VAL_ARINC_SSM_SDI_ANY                                         0
#define RSRTX_VAL_ARINC_SSM_SDI_S00                                         1
#define RSRTX_VAL_ARINC_SSM_SDI_S01                                         2
#define RSRTX_VAL_ARINC_SSM_SDI_S10                                         3
#define RSRTX_VAL_ARINC_SSM_SDI_S11                                         4

// rsrtx_rngARINC429TimingCondition
#define RSRTX_VAL_ARINC_CONDITION_TIMING_GTH                                0
#define RSRTX_VAL_ARINC_CONDITION_TIMING_LTH                                1
#define RSRTX_VAL_ARINC_CONDITION_TIMING_WITH                               2
#define RSRTX_VAL_ARINC_CONDITION_TIMING_OUTS                               3

// rsrtx_rngARINC429WordType
#define RSRTX_VAL_ARINC_WORD_TYPE_START                                     0
#define RSRTX_VAL_ARINC_WORD_TYPE_STOP                                      1

// rsrtx_rngARINC429Type
#define RSRTX_VAL_TRIGGER_ARINC_TYPE_WORD                                   0
#define RSRTX_VAL_TRIGGER_ARINC_TYPE_ERROR                                  1
#define RSRTX_VAL_TRIGGER_ARINC_TYPE_LABEL                                  2
#define RSRTX_VAL_TRIGGER_ARINC_TYPE_LDATA                                  3
#define RSRTX_VAL_TRIGGER_ARINC_TYPE_TTIME                                  4

// rsrtx_rngARINC429Error
#define RSRTX_VAL_ARINC_ERROR_ANY                                           0
#define RSRTX_VAL_ARINC_ERROR_PARITY                                        1
#define RSRTX_VAL_ARINC_ERROR_GAP                                           2
#define RSRTX_VAL_ARINC_ERROR_CODING                                        3

// rsrtx_rngMILSTDTransmissionType
#define RSRTX_MILSTD_TRANSMISSION_TYPE_BCRT                                 0
#define RSRTX_MILSTD_TRANSMISSION_TYPE_RTBC                                 1
#define RSRTX_MILSTD_TRANSMISSION_TYPE_RTRT                                 2
#define RSRTX_MILSTD_TRANSMISSION_TYPE_MCD                                  3

// rsrtx_rngMILSTDSearchWordStart
#define RSRTX_VAL_MILSTD_WORD_START_STATUS                                  0
#define RSRTX_VAL_MILSTD_WORD_START_DATA                                    1
#define RSRTX_VAL_MILSTD_WORD_START_COMMAND                                 2

// rsrtx_rngHardcopyCommandSet
#define RSRTX_VAL_COMMAND_SET_PCL5                                          0
#define RSRTX_VAL_COMMAND_SET_PCLXI                                         1
#define RSRTX_VAL_COMMAND_SET_PS                                            2
#define RSRTX_VAL_COMMAND_SET_DESK                                          3

// rsrtx_rngScaleLinLog
#define RSRTX_VAL_SCALE_LIN                                                 0
#define RSRTX_VAL_SCALE_LOG                                                 1

// rsrtx_rngHarmonicsFundamentalMIL
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_MIL_F60                             0
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_MIL_F400                            1

// rsrtx_rngHarmonicsFundamentalRTC
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_RTC_F400                            0
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_RTC_NVF                             1
#define RSRTX_VAL_HARMONICS_FUNDAMENTAL_RTC_WVF                             2

// rsrtx_rngProbeInputImpedance
#define RSRTX_VAL_UNKNOWN                                                   0
#define RSRTX_VAL_50OHM                                                     1
#define RSRTX_VAL_1MOHM                                                     2

// RsRtx_rngClockedSource
#define RSRTX_VAL_CLOCKED_SOURCE_D0                                         0
#define RSRTX_VAL_CLOCKED_SOURCE_D1                                         1
#define RSRTX_VAL_CLOCKED_SOURCE_D2                                         2
#define RSRTX_VAL_CLOCKED_SOURCE_D3                                         3
#define RSRTX_VAL_CLOCKED_SOURCE_D4                                         4
#define RSRTX_VAL_CLOCKED_SOURCE_D5                                         5
#define RSRTX_VAL_CLOCKED_SOURCE_D6                                         6
#define RSRTX_VAL_CLOCKED_SOURCE_D7                                         7
#define RSRTX_VAL_CLOCKED_SOURCE_D8                                         8
#define RSRTX_VAL_CLOCKED_SOURCE_D9                                         9
#define RSRTX_VAL_CLOCKED_SOURCE_D10                                        10
#define RSRTX_VAL_CLOCKED_SOURCE_D11                                        11
#define RSRTX_VAL_CLOCKED_SOURCE_D12                                        12
#define RSRTX_VAL_CLOCKED_SOURCE_D13                                        13
#define RSRTX_VAL_CLOCKED_SOURCE_D14                                        14
#define RSRTX_VAL_CLOCKED_SOURCE_D15                                        15

// RsRtx_rngParallelBitSource
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D0                                    0
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D1                                    1
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D2                                    2
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D3                                    3
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D4                                    4
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D5                                    5
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D6                                    6
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D7                                    7
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D8                                    8
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D9                                    9
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D10                                   10
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D11                                   11
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D12                                   12
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D13                                   13
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D14                                   14
#define RSRTX_VAL_PARALLEL_BIT_SOURCE_D15                                   15

// RsRtx_rngDVMType
#define RSRTX_VAL_DVM_TYPE_DC                                               0
#define RSRTX_VAL_DVM_TYPE_ACDC                                             1
#define RSRTX_VAL_DVM_TYPE_ACRM                                             2
#define RSRTX_VAL_DVM_TYPE_UPE                                              3
#define RSRTX_VAL_DVM_TYPE_LPE                                              4
#define RSRTX_VAL_DVM_TYPE_PEAK                                             5
#define RSRTX_VAL_DVM_TYPE_CRES                                             6
#define RSRTX_VAL_DVM_TYPE_OFF                                              7

// RsRtx_rngDVMPosition
#define RSRTX_VAL_DVM_POSITION_TLEFT                                        0
#define RSRTX_VAL_DVM_POSITION_TRIGHT                                       1
#define RSRTX_VAL_DVM_POSITION_BLEFT                                        2
#define RSRTX_VAL_DVM_POSITION_BRIGHT                                       3

// RsRtx_rngMagnitudeScale
#define RSRTX_VAL_MAGNITUDE_SCALE_LIN                                       0
#define RSRTX_VAL_MAGNITUDE_SCALE_DBM                                       1
#define RSRTX_VAL_MAGNITUDE_SCALE_DBC                                       2
#define RSRTX_VAL_MAGNITUDE_SCALE_DBUV                                      3

// RsRtx_rngSpectrumFrequencyWindowType
#define RSRTX_VAL_SPECTRUM_FREQ_WINDOW_TYPE_RECT                            0
#define RSRTX_VAL_SPECTRUM_FREQ_WINDOW_TYPE_HAMM                            1
#define RSRTX_VAL_SPECTRUM_FREQ_WINDOW_TYPE_HANN                            2
#define RSRTX_VAL_SPECTRUM_FREQ_WINDOW_TYPE_BLAC                            3
#define RSRTX_VAL_SPECTRUM_FREQ_WINDOW_TYPE_FLAT                            4

// RsRtx_rngSpectrumMarkerDisplay
#define RSRTX_VAL_SPECTRUM_MARKER_OFF                                       0
#define RSRTX_VAL_SPECTRUM_MARKER_INDEX                                     1
#define RSRTX_VAL_SPECTRUM_MARKER_RESULT                                    2

// RsRtx_rngSpectrumMarkerSource
#define RSRTX_VAL_SPECTRUM_MARKER_SOURCE_SPEC                               0
#define RSRTX_VAL_SPECTRUM_MARKER_SOURCE_MINH                               1
#define RSRTX_VAL_SPECTRUM_MARKER_SOURCE_MAXH                               2
#define RSRTX_VAL_SPECTRUM_MARKER_SOURCE_AVER                               3

// RsRtx_rngSpectrumMarkerSetupDetectionMode
#define RSRTX_VAL_SPECTRUM_MARKER_DETECTION_LEVEL                           0
#define RSRTX_VAL_SPECTRUM_MARKER_DETECTION_ADVANCED                        1

// RsRtx_rngSpectrumMarkerReferenceMode
#define RSRTX_VAL_SPECTRUM_MARKER_REF_MODE_OFF                              0
#define RSRTX_VAL_SPECTRUM_MARKER_REF_MODE_INDICATED                        1
#define RSRTX_VAL_SPECTRUM_MARKER_REF_MODE_RANGE                            2

// RsRtx_rngSpectrumMarkerResultMode
#define RSRTX_VAL_SPECTRUM_MARKER_RESULT_MODE_ABSOLUTE                      0
#define RSRTX_VAL_SPECTRUM_MARKER_RESULT_MODE_FREQUENCY                     1
#define RSRTX_VAL_SPECTRUM_MARKER_RESULT_MODE_LEVEL                         2
#define RSRTX_VAL_SPECTRUM_MARKER_RESULT_MODE_FLEVEL                        3

// RsRtx_rngSpectrumMarkerTablePosition
#define RSRTX_VAL_SPECTRUM_MARKER_TABLE_POSITION_TOP                        0
#define RSRTX_VAL_SPECTRUM_MARKER_TABLE_POSITION_BOTTOM                     1
#define RSRTX_VAL_SPECTRUM_MARKER_TABLE_POSITION_FULL                       2

// RsRtx_rngSpectrumDisplayColorScheme
#define RSRTX_VAL_SPECTRUM_COLOR_SCHEME_MONOCHROM                           0
#define RSRTX_VAL_SPECTRUM_COLOR_SCHEME_TEMPERATURE                         1
#define RSRTX_VAL_SPECTRUM_COLOR_SCHEME_RAINBOW                             2

// RsRtx_rngContentFormat
#define RSRTX_VAL_CONTENT_FORMAT_ALL                                        0
#define RSRTX_VAL_CONTENT_FORMAT_WTIME                                      1

// RsRtx_rngAcquisitionMode
#define RSRTX_VAL_ACQUISTION_MODE_REFRESH                                   0
#define RSRTX_VAL_ACQUISTION_MODE_AVERAGE                                   1
#define RSRTX_VAL_ACQUISTION_MODE_ENVELOPE                                  2

// RsRtx_rngAcquisitionState
#define RSRTX_VAL_ACQ_STATE_RUN                                             0
#define RSRTX_VAL_ACQ_STATE_STOP                                            1
#define RSRTX_VAL_ACQ_STATE_COMPLETE                                        2
#define RSRTX_VAL_ACQ_STATE_BREAK                                           3

// RsRtx_rngMathOperation
#define RSRTX_VAL_MATH_OPERATION_ADD                                        0
#define RSRTX_VAL_MATH_OPERATION_SUB                                        1
#define RSRTX_VAL_MATH_OPERATION_MUL                                        2
#define RSRTX_VAL_MATH_OPERATION_DIV                                        3

// RsRtx_rngAbsoluteRelative
#define RSRTX_VAL_ABS                                                       0
#define RSRTX_VAL_REL                                                       1

// RsRtx_rngDeviceMode
#define RSRTX_VAL_DEVICE_MODE_YT                                            0
#define RSRTX_VAL_DEVICE_MODE_ZOOM                                          1
#define RSRTX_VAL_DEVICE_MODE_XY                                            2
#define RSRTX_VAL_DEVICE_MODE_QMEAS                                         3
#define RSRTX_VAL_DEVICE_MODE_UPDATE                                        4
#define RSRTX_VAL_DEVICE_MODE_AUTOSET                                       5
#define RSRTX_VAL_DEVICE_MODE_MASKTEST                                      6
#define RSRTX_VAL_DEVICE_MODE_FFT                                           7

// RsRtx_rngPersistenceType
#define RSRTX_VAL_PERSISTENCE_OFF                                           0
#define RSRTX_VAL_PERSISTENCE_TIME                                          1
#define RSRTX_VAL_PERSISTENCE_INFINITE                                      2

// rsrtx_rngHardcopyFormat
#define RSRTX_VAL_HARDCOPY_FORMAT_BMP                                       1
#define RSRTX_VAL_HARDCOPY_FORMAT_PNG                                       0

// RsRtx_rngLogicThreshold
#define RSRTX_VAL_LOGIC_THRESHOLD_TTL                                       0
#define RSRTX_VAL_LOGIC_THRESHOLD_ECL                                       1
#define RSRTX_VAL_LOGIC_THRESHOLD_CMOS                                      2
#define RSRTX_VAL_LOGIC_THRESHOLD_USER                                      3

// RsRtx_rngLogicType
#define RSRTX_VAL_LOGIC_TYPE_SAMPLE                                         0
#define RSRTX_VAL_LOGIC_TYPE_PEAKDETECT                                     1

// RsRtx_rngWaveformGeneratorFunctionType
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_SIN                                0
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_SQU                                1
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_RAMP                               2
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_DC                                 3
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_PULS                               4
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_SINC                               5
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_TRI                                6
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_EXP                                7
#define RSRTX_VAL_WAVE_GEN_FUNCTION_TYPE_ARB                                8

// RsRtx_rngWaveformGeneratorModulationType
#define RSRTX_VAL_WAVE_GEN_MODULATION_TYPE_AM                               0
#define RSRTX_VAL_WAVE_GEN_MODULATION_TYPE_FM                               1
#define RSRTX_VAL_WAVE_GEN_MODULATION_TYPE_ASK                              2
#define RSRTX_VAL_WAVE_GEN_MODULATION_TYPE_FSK                              3

// RsRtx_rngWaveformGeneratorArbitrarySource
#define RSRTX_VAL_WAVE_GEN_CH1                                              1
#define RSRTX_VAL_WAVE_GEN_CH2                                              2
#define RSRTX_VAL_WAVE_GEN_CH3                                              3
#define RSRTX_VAL_WAVE_GEN_CH4                                              4

// RsRtx_rngWaveformGeneratorLoad
#define RSRTX_ATTR_WAVE_GEN_OUTPUT_LOAD_FIFTYOHM                            0
#define RSRTX_ATTR_WAVE_GEN_OUTPUT_LOAD_HIGHZ                               1

// RsRtx_rngWaveformGeneratorModulationFunctionType
#define RSRTX_VAL_WAVE_GEN_MOD_FUNCTION_TYPE_SIN                            0
#define RSRTX_VAL_WAVE_GEN_MOD_FUNCTION_TYPE_SQU                            1
#define RSRTX_VAL_WAVE_GEN_MOD_FUNCTION_TYPE_RAMP                           2
#define RSRTX_VAL_WAVE_GEN_MOD_FUNCTION_TYPE_TRI                            3

// RsRtx_rngWaveformGeneratorOutputDestination
#define RSRTX_VAL_WAVE_GEN_OUTPUT_DESTINATION_BNC                           0
#define RSRTX_VAL_WAVE_GEN_OUTPUT_DESTINATION_P3                            1

// RsRtx_rngPatternGeneratorFunctionType
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_SQUARE                             0
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_COUNTER                            1
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_ARB                                2
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_SPI                                3
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_I2C                                4
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_UART                               5
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_CAN                                6
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_LIN                                7
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_MANUAL                             8
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_AUDIO_I2S                          9
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_AUDIO_TDM                          10
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_TEST_PWM                           11
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_PWM                                12
#define RSRTX_VAL_PATT_GEN_FUNCTION_TYPE_LED_PWM                            13

// RsRtx_rngPatternGeneratorCounterDirection
#define RSRTX_VAL_PATT_GEN_DIRECTION_DOWN                                   0
#define RSRTX_VAL_PATT_GEN_DIRECTION_UP                                     1

// RsRtx_rngPatternGeneratorTriggerMode
#define RSRTX_VAL_PATT_GEN_TRIGGER_MODE_CONT                                0
#define RSRTX_VAL_PATT_GEN_TRIGGER_MODE_SING                                1

// rsrtx_rngWindowRange
#define RSRTX_VAL_RANGE_ENTER                                               0
#define RSRTX_VAL_RANGE_EXIT                                                1
#define RSRTX_VAL_RANGE_WITHIN                                              2
#define RSRTX_VAL_RANGE_OUTSIDE                                             3
#define RSRTX_VAL_RANGE_PASS                                                4
#define RSRTX_VAL_RANGE_NPASS                                               5

// RsRtx_rngSpectrumAnalysisMode
#define RSRTX_VAL_SPECTRUM_MODE_SPECTRUM                                    0
#define RSRTX_VAL_SPECTRUM_MODE_FFT                                         1

// RsRtx_rngInterface
#define RSRTX_VAL_INTERFACE_ETH                                             0
#define RSRTX_VAL_INTERFACE_USB                                             1

// RsRtx_rngUSBClass
#define RSRTX_VAL_USB_CLASS_TMC                                             0
#define RSRTX_VAL_USB_CLASS_VCP                                             1
#define RSRTX_VAL_USB_CLASS_MTP                                             2

// RsRtx_rngEthernetTransfer
#define RSRTX_VAL_ETHERNET_TRANSFER_AUTO                                    0
#define RSRTX_VAL_ETHERNET_TRANSFER_FD10                                    1
#define RSRTX_VAL_ETHERNET_TRANSFER_FD100                                   2
#define RSRTX_VAL_ETHERNET_TRANSFER_HD10                                    3
#define RSRTX_VAL_ETHERNET_TRANSFER_HD100                                   4

// RsRtx_rngTimeoutRange
#define RSRTX_VAL_TIMEOUT_RANGE_LOW                                         0
#define RSRTX_VAL_TIMEOUT_RANGE_HIGH                                        1
#define RSRTX_VAL_TIMEOUT_RANGE_EITHER                                      2

// RsRtx_rngMILSTDTriggerFrame
#define RSRTX_MILSTD_FRAME_COMMAND                                          0
#define RSRTX_MILSTD_FRAME_STATUS                                           1
#define RSRTX_MILSTD_FRAME_DATA                                             2
#define RSRTX_MILSTD_FRAME_ALL                                              3

// RsRtx_rngPointSelection
#define RSRTX_VAL_POINT_SELECTION_DEFAULT                                   0
#define RSRTX_VAL_POINT_SELECTION_MAX                                       1
#define RSRTX_VAL_POINT_SELECTION_DMAX                                      2

// RsRtx_rngUARTTriggerSource
#define RSRTX_VAL_UART_TRIGGER_SOURCE_RX                                    0
#define RSRTX_VAL_UART_TRIGGER_SOURCE_TX                                    1

// RsRtx_rngUARTFrameSource
#define RSRTX_VAL_UART_FRAME_SOURCE_RX                                      0
#define RSRTX_VAL_UART_FRAME_SOURCE_TX                                      1

// RsRtx_rngMemoryMode
#define RSRTX_VAL_MEMORY_MODE_AUTOMATIC                                     0
#define RSRTX_VAL_MEMORY_MODE_PREDEFINED                                    1
#define RSRTX_VAL_MEMORY_MODE_MANUAL                                        2

// RsRtx_rngBodeAmplitudeMode
#define RSRTX_VAL_BODE_CONSTANT                                             0
#define RSRTX_VAL_BODE_PROFILE                                              1

// RsRtx_rngBodeSourceChannel
#define RSRTX_VAL_BODE_SOURCE_CHANNEL1                                      0
#define RSRTX_VAL_BODE_SOURCE_CHANNEL2                                      1
#define RSRTX_VAL_BODE_SOURCE_CHANNEL3                                      2
#define RSRTX_VAL_BODE_SOURCE_CHANNEL4                                      3

// RsRtx_rngBodePlotMeasurementState
#define RSRTX_VAL_BODE_MEASUREMENT_STOP                                     0
#define RSRTX_VAL_BODE_MEASUREMENT_RUN                                      1

// RsRtx_rngUARTFrameState
#define RSRTX_VAL_UART_FRAME_OK                                             0
#define RSRTX_VAL_UART_FRAME_START_ERROR                                    1
#define RSRTX_VAL_UART_FRAME_STOP_ERROR                                     2
#define RSRTX_VAL_UART_FRAME_PARITY_ERROR                                   3
#define RSRTX_VAL_UART_FRAME_BREAK                                          4
#define RSRTX_VAL_UART_FRAME_INCOMPLETE                                     5

// RsRtx_rngIdleStatePolarity
#define RSRTX_VAL_UART_POLARITY_IDLE_HIGH                                   0
#define RSRTX_VAL_UART_POLARITY_IDLE_LOW                                    1

// RsRtx_rngMathWaveformColor
#define RSRTX_VALUE_WAVEFORM_COLOR_DEFAULT                                  0
#define RSRTX_VALUE_WAVEFORM_COLOR_TEMPERATURE                              1
#define RSRTX_VALUE_WAVEFORM_COLOR_RAINBOW                                  2
#define RSRTX_VALUE_WAVEFORM_COLOR_FIRE                                     3
#define RSRTX_VALUE_WAVEFORM_COLOR_YELLOW                                   4
#define RSRTX_VALUE_WAVEFORM_COLOR_GREEN                                    5
#define RSRTX_VALUE_WAVEFORM_COLOR_ORANGE                                   6
#define RSRTX_VALUE_WAVEFORM_COLOR_BLUE                                     7
#define RSRTX_VALUE_WAVEFORM_COLOR_LIGHT_BLUE                               8
#define RSRTX_VALUE_WAVEFORM_COLOR_WHITE                                    9
#define RSRTX_VALUE_WAVEFORM_COLOR_CYAN                                     10
#define RSRTX_VALUE_WAVEFORM_COLOR_PINK                                     11
#define RSRTX_VALUE_WAVEFORM_COLOR_RED                                      12

// RsRtx_rngMaskCaptureMode
#define RSRTX_VAL_MASK_CAPTURE_ALL                                          0
#define RSRTX_VAL_MASK_CAPTURE_FAILED                                       1

// RsRtx_rngCounterSource
#define RSRTX_VAL_COUNTER_SOURCE_TRIGGER                                    0
#define RSRTX_VAL_COUNTER_SOURCE_CHANNEL1                                   1
#define RSRTX_VAL_COUNTER_SOURCE_CHANNEL2                                   2
#define RSRTX_VAL_COUNTER_SOURCE_CHANNEL3                                   3
#define RSRTX_VAL_COUNTER_SOURCE_CHANNEL4                                   4

// RsRtx_rngProbeInputVoltageRange
#define RSRTX_VAL_PROBE_INPUT_VOLTAGE_AUTO                                  0
#define RSRTX_VAL_PROBE_INPUT_VOLTAGE_HIGH                                  1
#define RSRTX_VAL_PROBE_INPUT_VOLTAGE_LOW                                   2

// RsRtx_rngProbeMeasMode
#define RSRTX_VAL_PROBE_MEAS_MODE_DIFFERENTIAL                              0
#define RSRTX_VAL_PROBE_MEAS_MODE_COMMON                                    1
#define RSRTX_VAL_PROBE_MEAS_MODE_POSITIVE                                  2
#define RSRTX_VAL_PROBE_MEAS_MODE_NEGATIVE                                  3

// RsRtx_rngMeasurementDelayDirection
#define RSRTX_VAL_MEAS_DELAY_DIRECTION_NEAR                                 0
#define RSRTX_VAL_MEAS_DELAY_DIRECTION_FRFI                                 1
#define RSRTX_VAL_MEAS_DELAY_DIRECTION_FRLA                                 2

//repcap Measurement
#define RSRTX_REPCAP_MEASUREMENT_M1                                         1
#define RSRTX_REPCAP_MEASUREMENT_M2                                         2
#define RSRTX_REPCAP_MEASUREMENT_M3                                         3
#define RSRTX_REPCAP_MEASUREMENT_M4                                         4
#define RSRTX_REPCAP_MEASUREMENT_M5                                         5
#define RSRTX_REPCAP_MEASUREMENT_M6                                         6
#define RSRTX_REPCAP_MEASUREMENT_M7                                         7
#define RSRTX_REPCAP_MEASUREMENT_M8                                         8

//repcap Math
#define RSRTX_REPCAP_MATH_MA1                                               1
#define RSRTX_REPCAP_MATH_MA2                                               2
#define RSRTX_REPCAP_MATH_MA3                                               3
#define RSRTX_REPCAP_MATH_MA4                                               4
#define RSRTX_REPCAP_MATH_MA5                                               5

//repcap ReferenceWfm
#define RSRTX_REPCAP_REFERENCEWFM_RW1                                       1
#define RSRTX_REPCAP_REFERENCEWFM_RW2                                       2
#define RSRTX_REPCAP_REFERENCEWFM_RW3                                       3
#define RSRTX_REPCAP_REFERENCEWFM_RW4                                       4

//repcap SerialBus
#define RSRTX_REPCAP_SERIALBUS_SB1                                          1
#define RSRTX_REPCAP_SERIALBUS_SB2                                          2
#define RSRTX_REPCAP_SERIALBUS_SB3                                          3
#define RSRTX_REPCAP_SERIALBUS_SB4                                          4

//repcap Cursor
#define RSRTX_REPCAP_CURSOR_CUR1                                            1
#define RSRTX_REPCAP_CURSOR_CUR2                                            2
#define RSRTX_REPCAP_CURSOR_CUR3                                            3

//repcap ResultNumber
#define RSRTX_REPCAP_RESULTNUMBER_RES1                                      1
#define RSRTX_REPCAP_RESULTNUMBER_RES2                                      2
#define RSRTX_REPCAP_RESULTNUMBER_RES3                                      3
#define RSRTX_REPCAP_RESULTNUMBER_RES4                                      4
#define RSRTX_REPCAP_RESULTNUMBER_RES5                                      5
#define RSRTX_REPCAP_RESULTNUMBER_RES6                                      6
#define RSRTX_REPCAP_RESULTNUMBER_RES7                                      7
#define RSRTX_REPCAP_RESULTNUMBER_RES8                                      8
#define RSRTX_REPCAP_RESULTNUMBER_RES9                                      9
#define RSRTX_REPCAP_RESULTNUMBER_RES10                                     10
#define RSRTX_REPCAP_RESULTNUMBER_RES11                                     11
#define RSRTX_REPCAP_RESULTNUMBER_RES12                                     12
#define RSRTX_REPCAP_RESULTNUMBER_RES13                                     13
#define RSRTX_REPCAP_RESULTNUMBER_RES14                                     14
#define RSRTX_REPCAP_RESULTNUMBER_RES15                                     15
#define RSRTX_REPCAP_RESULTNUMBER_RES16                                     16
#define RSRTX_REPCAP_RESULTNUMBER_RES17                                     17
#define RSRTX_REPCAP_RESULTNUMBER_RES18                                     18
#define RSRTX_REPCAP_RESULTNUMBER_RES19                                     19
#define RSRTX_REPCAP_RESULTNUMBER_RES20                                     20
#define RSRTX_REPCAP_RESULTNUMBER_RES21                                     21
#define RSRTX_REPCAP_RESULTNUMBER_RES22                                     22
#define RSRTX_REPCAP_RESULTNUMBER_RES23                                     23
#define RSRTX_REPCAP_RESULTNUMBER_RES24                                     24
#define RSRTX_REPCAP_RESULTNUMBER_RES25                                     25
#define RSRTX_REPCAP_RESULTNUMBER_RES26                                     26
#define RSRTX_REPCAP_RESULTNUMBER_RES27                                     27
#define RSRTX_REPCAP_RESULTNUMBER_RES28                                     28
#define RSRTX_REPCAP_RESULTNUMBER_RES29                                     29
#define RSRTX_REPCAP_RESULTNUMBER_RES30                                     30
#define RSRTX_REPCAP_RESULTNUMBER_RES31                                     31
#define RSRTX_REPCAP_RESULTNUMBER_RES32                                     32
#define RSRTX_REPCAP_RESULTNUMBER_RES33                                     33
#define RSRTX_REPCAP_RESULTNUMBER_RES34                                     34
#define RSRTX_REPCAP_RESULTNUMBER_RES35                                     35
#define RSRTX_REPCAP_RESULTNUMBER_RES36                                     36
#define RSRTX_REPCAP_RESULTNUMBER_RES37                                     37
#define RSRTX_REPCAP_RESULTNUMBER_RES38                                     38
#define RSRTX_REPCAP_RESULTNUMBER_RES39                                     39
#define RSRTX_REPCAP_RESULTNUMBER_RES40                                     40

//repcap Gate
#define RSRTX_REPCAP_GATE_GATE1                                             1
#define RSRTX_REPCAP_GATE_GATE2                                             2
#define RSRTX_REPCAP_GATE_GATE3                                             3

//repcap OnOffResult
#define RSRTX_REPCAP_ONOFFRESULT_OOR1                                       1
#define RSRTX_REPCAP_ONOFFRESULT_OOR2                                       2
#define RSRTX_REPCAP_ONOFFRESULT_OOR3                                       3

//repcap SourceNumber
#define RSRTX_REPCAP_SOURCENUMBER_S1                                        1
#define RSRTX_REPCAP_SOURCENUMBER_S2                                        2
#define RSRTX_REPCAP_SOURCENUMBER_S3                                        3
#define RSRTX_REPCAP_SOURCENUMBER_S4                                        4

//repcap Digital
#define RSRTX_REPCAP_DIGITAL_D0                                             0
#define RSRTX_REPCAP_DIGITAL_D1                                             1
#define RSRTX_REPCAP_DIGITAL_D2                                             2
#define RSRTX_REPCAP_DIGITAL_D3                                             3
#define RSRTX_REPCAP_DIGITAL_D4                                             4
#define RSRTX_REPCAP_DIGITAL_D5                                             5
#define RSRTX_REPCAP_DIGITAL_D6                                             6
#define RSRTX_REPCAP_DIGITAL_D7                                             7
#define RSRTX_REPCAP_DIGITAL_D8                                             8
#define RSRTX_REPCAP_DIGITAL_D9                                             9
#define RSRTX_REPCAP_DIGITAL_D10                                            10
#define RSRTX_REPCAP_DIGITAL_D11                                            11
#define RSRTX_REPCAP_DIGITAL_D12                                            12
#define RSRTX_REPCAP_DIGITAL_D13                                            13
#define RSRTX_REPCAP_DIGITAL_D14                                            14
#define RSRTX_REPCAP_DIGITAL_D15                                            15

//repcap DigitalVoltmeter
#define RSRTX_REPCAP_DIGITALVOLTMETER_DVM1                                  1
#define RSRTX_REPCAP_DIGITALVOLTMETER_DVM2                                  2
#define RSRTX_REPCAP_DIGITALVOLTMETER_DVM3                                  3
#define RSRTX_REPCAP_DIGITALVOLTMETER_DVM4                                  4

//repcap CursorLine
#define RSRTX_REPCAP_CURSORLINE_CURSORLINE1                                 1
#define RSRTX_REPCAP_CURSORLINE_CURSORLINE2                                 2

//repcap Logic
#define RSRTX_REPCAP_LOGIC_LOGIC1                                           1
#define RSRTX_REPCAP_LOGIC_LOGIC2                                           2

//repcap OutputPin
#define RSRTX_REPCAP_OUTPUTPIN_P0                                           0
#define RSRTX_REPCAP_OUTPUTPIN_P1                                           1
#define RSRTX_REPCAP_OUTPUTPIN_P2                                           2
#define RSRTX_REPCAP_OUTPUTPIN_P3                                           3

//repcap ProfilePoint
#define RSRTX_REPCAP_PROFILEPOINT_POINT1                                    1
#define RSRTX_REPCAP_PROFILEPOINT_POINT2                                    2
#define RSRTX_REPCAP_PROFILEPOINT_POINT3                                    3
#define RSRTX_REPCAP_PROFILEPOINT_POINT4                                    4
#define RSRTX_REPCAP_PROFILEPOINT_POINT5                                    5
#define RSRTX_REPCAP_PROFILEPOINT_POINT6                                    6
#define RSRTX_REPCAP_PROFILEPOINT_POINT7                                    7
#define RSRTX_REPCAP_PROFILEPOINT_POINT8                                    8
#define RSRTX_REPCAP_PROFILEPOINT_POINT9                                    9
#define RSRTX_REPCAP_PROFILEPOINT_POINT10                                   10
#define RSRTX_REPCAP_PROFILEPOINT_POINT11                                   11
#define RSRTX_REPCAP_PROFILEPOINT_POINT12                                   12
#define RSRTX_REPCAP_PROFILEPOINT_POINT13                                   13
#define RSRTX_REPCAP_PROFILEPOINT_POINT14                                   14
#define RSRTX_REPCAP_PROFILEPOINT_POINT15                                   15
#define RSRTX_REPCAP_PROFILEPOINT_POINT16                                   16

//repcap BodeMarker
#define RSRTX_REPCAP_BODEMARKER_BODEMARK1                                   1
#define RSRTX_REPCAP_BODEMARKER_BODEMARK2                                   2

//repcap ParallelLine
#define RSRTX_REPCAP_PARALLELLINE_BIT0                                      0
#define RSRTX_REPCAP_PARALLELLINE_BIT1                                      1
#define RSRTX_REPCAP_PARALLELLINE_BIT2                                      2
#define RSRTX_REPCAP_PARALLELLINE_BIT3                                      3
#define RSRTX_REPCAP_PARALLELLINE_BIT4                                      4
#define RSRTX_REPCAP_PARALLELLINE_BIT5                                      5
#define RSRTX_REPCAP_PARALLELLINE_BIT6                                      6
#define RSRTX_REPCAP_PARALLELLINE_BIT7                                      7
#define RSRTX_REPCAP_PARALLELLINE_BIT8                                      8
#define RSRTX_REPCAP_PARALLELLINE_BIT9                                      9
#define RSRTX_REPCAP_PARALLELLINE_BIT10                                     10
#define RSRTX_REPCAP_PARALLELLINE_BIT11                                     11
#define RSRTX_REPCAP_PARALLELLINE_BIT12                                     12
#define RSRTX_REPCAP_PARALLELLINE_BIT13                                     13
#define RSRTX_REPCAP_PARALLELLINE_BIT14                                     14
#define RSRTX_REPCAP_PARALLELLINE_BIT15                                     15
/* END GENERATE */

/*****************************************************************************
 *- Hidden Attribute Declarations -------------------------------------------*
 *****************************************************************************/

#define RSRTX_ATTR_OPC_TIMEOUT               (RS_ATTR_OPC_TIMEOUT)           /* ViInt32 */
#define RSRTX_ATTR_IO_SESSION                (RS_ATTR_IO_SESSION)            /* ViSession */
#define RSRTX_ATTR_OPC_CALLBACK              (RS_ATTR_OPC_CALLBACK)          /* ViAddr */
#define RSRTX_ATTR_CHECK_STATUS_CALLBACK     (RS_ATTR_CHECK_STATUS_CALLBACK) /* ViAddr */

/****************************************************************************
 *---------------- Constant definition  ------------------------------------*
 ****************************************************************************/
#define RSRTX_VAL_CHANNEL_1   1
#define RSRTX_VAL_CHANNEL_2   2
#define RSRTX_VAL_CHANNEL_3   3
#define RSRTX_VAL_CHANNEL_4   4
#define RSRTX_VAL_CHANNEL_EXT 5

#define RSRTX_VAL_SERIAL_BUS_1  1
#define RSRTX_VAL_SERIAL_BUS_2  2
#define RSRTX_VAL_SERIAL_BUS_3  3
#define RSRTX_VAL_SERIAL_BUS_4  4

#define RSRTX_VAL_TRIGGER_A 1
#define RSRTX_VAL_TRIGGER_B 2

#define RSRTX_VAL_TRIGGER_FILTER_LOW  0
#define RSRTX_VAL_TRIGGER_FILTER_HIGH 1
#define RSRTX_VAL_TRIGGER_FILTER_HF   2

#define RSRTX_VAL_DISPLAY_BACKGROUND 0
#define RSRTX_VAL_DISPLAY_GRID       1
#define RSRTX_VAL_DISPLAY_WAVEFORM   2

#define RSRTX_VAL_MARKER_ACTION_SET    0
#define RSRTX_VAL_MARKER_ACTION_NEXT   1
#define RSRTX_VAL_MARKER_ACTION_PREV   2
#define RSRTX_VAL_MARKER_ACTION_CLEAR  3
#define RSRTX_VAL_MARKER_ACTION_ACLEAR 4

#define RSRTX_VAL_MEASUREMENT_1 1
#define RSRTX_VAL_MEASUREMENT_2 2
#define RSRTX_VAL_MEASUREMENT_3 3
#define RSRTX_VAL_MEASUREMENT_4 4
#define RSRTX_VAL_MEASUREMENT_5 5
#define RSRTX_VAL_MEASUREMENT_6 6
#define RSRTX_VAL_MEASUREMENT_7 7
#define RSRTX_VAL_MEASUREMENT_8 8

#define RSRTX_VAL_CURSOR_1 1
#define RSRTX_VAL_CURSOR_2 2
#define RSRTX_VAL_CURSOR_3 3

#define RSRTX_VAL_I2C_SCL       0
#define RSRTX_VAL_I2C_SDA       1

#define RSRTX_VAL_SPI_CLOCK  0
#define RSRTX_VAL_SPI_DATA   1
#define RSRTX_VAL_SPI_CSEL   2

#define RSRTX_VAL_PARALLEL_BIT0 0
#define RSRTX_VAL_PARALLEL_BIT1 1
#define RSRTX_VAL_PARALLEL_BIT2 2
#define RSRTX_VAL_PARALLEL_BIT3 3

#define RSRTX_VAL_WAV_LOAD      0
#define RSRTX_VAL_WAV_LOAD_CFG  1
#define RSRTX_VAL_WAV_SAVE      2

#define RSRTX_VAL_REF_WAVEFORM_1 1
#define RSRTX_VAL_REF_WAVEFORM_2 2
#define RSRTX_VAL_REF_WAVEFORM_3 3
#define RSRTX_VAL_REF_WAVEFORM_4 4

#define RSRTX_VAL_INIT_SINGLE     0
#define RSRTX_VAL_INIT_CONTINUOUS 1

#define RSRTX_VAL_FILE_COPY    0
#define RSRTX_VAL_FILE_MOVE    1
#define RSRTX_VAL_FILE_DELETE  2
#define RSRTX_VAL_FILE_NEW_DIR 3
#define RSRTX_VAL_FILE_CDIR    4
#define RSRTX_VAL_FILE_RDIR    5
#define RSRTX_VAL_FILE_CDRIVE  6

#define RSRTX_VAL_REG_OPER 0
#define RSRTX_VAL_REG_QUES 1

#define RSRTX_VAL_REG_NONE     0
#define RSRTX_VAL_REG_COV      1
#define RSRTX_VAL_REG_LIM      2
#define RSRTX_VAL_REG_MASK     3
#define RSRTX_VAL_REG_ADC      4

#define RSRTX_VAL_REG_COND   0
#define RSRTX_VAL_REG_ENABLE 1
#define RSRTX_VAL_REG_EVENT  2
#define RSRTX_VAL_REG_NTR    3
#define RSRTX_VAL_REG_PTR    4

#define RSRTX_VAL_MEM_SAVE    0
#define RSRTX_VAL_MEM_RECALL  1

#define RSRTX_VAL_MEAS_SLOPE_POS 0
#define RSRTX_VAL_MEAS_SLOPE_NEG 1

#define RSRTX_VAL_CURSOR_POSITION_AUTOSET  0
#define RSRTX_VAL_CURSOR_POSITION_RESET    1

#define RSRTX_VAL_CURSOR_PEAK_NEXT		   0
#define RSRTX_VAL_CURSOR_PEAK_PREVIOUS	   1

#define RSRTX_VAL_AUTOMATIC_MEASUREMENT_AVERAGE      0
#define RSRTX_VAL_AUTOMATIC_MEASUREMENT_DEVIATION    1
#define RSRTX_VAL_AUTOMATIC_MEASUREMENT_MINIMUM      2
#define RSRTX_VAL_AUTOMATIC_MEASUREMENT_MAXIMUM      3

#define RSRTX_VAL_MASK_ACTION_SOUND    0
#define RSRTX_VAL_MASK_ACTION_STOP     1
#define RSRTX_VAL_MASK_ACTION_SCREEN   2
#define RSRTX_VAL_MASK_ACTION_PRINT    3
#define RSRTX_VAL_MASK_ACTION_WAVEFORM 4

#define RSRTX_VAL_SEARCH_D2C_CLOCK 0
#define RSRTX_VAL_SEARCH_D2C_DATA  1

#define RSRTX_VAL_LIN_FIELD_SYNC   0
#define RSRTX_VAL_LIN_FIELD_CHKSUM 1

#define RSRTX_VAL_CAN_FIELD_DLC 0
#define RSRTX_VAL_CAN_FIELD_CRC 1
#define RSRTX_VAL_CAN_FIELD_ACK 2

#define RSRTX_VAL_CAN_FIELD_ACK 2

#define RSSCOPE_VAL_SERIAL_BUS_1 1
#define RSSCOPE_VAL_SERIAL_BUS_2 2
#define RSSCOPE_VAL_SERIAL_BUS_3 3
#define RSSCOPE_VAL_SERIAL_BUS_4 4

#define RSRTX_VAL_CONSUMPTION_TYPE_DURATION       0
#define RSRTX_VAL_CONSUMPTION_TYPE_ENERGY         1
#define RSRTX_VAL_CONSUMPTION_TYPE_ACTIVE         2
#define RSRTX_VAL_CONSUMPTION_TYPE_APPARENT_POWER 3
#define RSRTX_VAL_CONSUMPTION_TYPE_POWER_FACTOR   4
#define RSRTX_VAL_CONSUMPTION_TYPE_PHASE		  5
#define RSRTX_VAL_CONSUMPTION_TYPE_REACTIVE_POWER 6

#define RSRTX_VAL_INRUSH_CURRENT_TYPE_AREA      0
#define RSRTX_VAL_INRUSH_CURRENT_TYPE_MAXIMUM   1

#define RSRTX_VAL_SWITCHINGLOSS_TYPE_CONDUCTION 0
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_NO_COND    1
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_ON    2
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_OFF   3
#define RSRTX_VAL_SWITCHINGLOSS_TYPE_TOTAL      4

#define RSRTX_VAL_POWER_TRANSIENT_MEAS_OVERSHOOT    0
#define RSRTX_VAL_POWER_TRANSIENT_MEAS_RISE_TIME    1
#define RSRTX_VAL_POWER_TRANSIENT_MEAS_DELAY_TIME   2
#define RSRTX_VAL_POWER_TRANSIENT_MEAS_PEAK_TIME    3
#define RSRTX_VAL_POWER_TRANSIENT_MEAS_PEAK_VALUE   4
#define RSRTX_VAL_POWER_TRANSIENT_MEAS_SETTLING     5

#define RSRTX_VAL_ADD     0
#define RSRTX_VAL_REMOVE  1
#define RSRTX_VAL_INSERT  2

#define RSRTX_VAL_POWER_SOURCE_CURRENT_MIN  0
#define RSRTX_VAL_POWER_SOURCE_CURRENT_MAX  1
#define RSRTX_VAL_POWER_SOURCE_VOLTAGE      2
#define RSRTX_VAL_POWER_SOURCE_CURRENT      3

#define RSRTX_VAL_POWER_SOA_TYPE_CURRENT  0
#define RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE  1

#define RSRTX_VAL_POWER_SOA_TYPE_CURRENT  0
#define RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE  1

#define RSRTX_VAL_FAST_SWEEP_NORMAL 0
#define RSRTX_VAL_FAST_SWEEP_FAST   1

/****************************************************************************
*---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/
ViStatus _VI_FUNC rsrtx_init (ViRsrc resourceName, ViBoolean IDQuery,
                              ViBoolean resetDevice, ViSession* instrumentHandle);
ViStatus _VI_FUNC rsrtx_InitWithOptions (ViRsrc resourceName, ViBoolean IDQuery,
                                         ViBoolean resetDevice,
                                         ViString optionString,
                                         ViSession* instrumentHandle);
ViStatus _VI_FUNC rsrtx_Autoset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionType (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViInt32 acquisitionType);
ViStatus _VI_FUNC rsrtx_ConfigureRecordLength (ViSession instrumentHandle,
                                               ViBoolean automatic,
                                               ViInt32 recordLength);
ViStatus _VI_FUNC rsrtx_ConfigureHorizontalRecordLength (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViInt32 recordLength);
ViStatus _VI_FUNC rsrtx_QueryHorizontalRecordLength (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViInt32* recordLength);
ViStatus _VI_FUNC rsrtx_ConfigureAcquireMode (ViSession instrumentHandle,
                                              ViInt32 acquireMode);
ViStatus _VI_FUNC rsrtx_ConfigurePeakDetect (ViSession instrumentHandle,
                                             ViBoolean peakDetect);
ViStatus _VI_FUNC rsrtx_ConfigureHighResolution (ViSession instrumentHandle,
                                                 ViBoolean highResolution);
ViStatus _VI_FUNC rsrtx_ConfigureMemoryMode (ViSession instrumentHandle,
                                             ViInt32 memoryMode);
ViStatus _VI_FUNC rsrtx_ConfigureRollModeAutomatic (ViSession instrumentHandle,
                                                    ViBoolean rollModeAutomatic);
ViStatus _VI_FUNC rsrtx_ConfigureRollModeMinimumTimeBase (ViSession instrumentHandle,
                                                          ViReal64 rollModeMinimumTimeBase);
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionRecord (ViSession instrumentHandle,
                                                    ViReal64 timePerRecord,
                                                    ViReal64 acquisitionStartTime_Offset);
ViStatus _VI_FUNC rsrtx_ConfigureInterpolation (ViSession instrumentHandle,
                                                ViInt32 interpolation);
ViStatus _VI_FUNC rsrtx_ConfigureNumberOfAverages (ViSession instrumentHandle,
                                                   ViInt32 numberOfAverages);
ViStatus _VI_FUNC rsrtx_QueryNumberofAveragesCurrent (ViSession instrumentHandle,
                                                      ViInt32* numberOfAverages);
ViStatus _VI_FUNC rsrtx_NumberofAveragesReset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformRateMaximum (ViSession instrumentHandle,
                                                      ViBoolean maximum);
ViStatus _VI_FUNC rsrtx_ConfigureNumberOfWaveforms (ViSession instrumentHandle,
                                                    ViInt32 numberOfWaveforms);
ViStatus _VI_FUNC rsrtx_ConfigureHorizontalReference (ViSession instrumentHandle,
                                                      ViReal64 horizontalReference);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformAcquisitionType (ViSession instrumentHandle,
                                                          ViInt32 channel,
                                                          ViInt32 acquisitionType);
ViStatus _VI_FUNC rsrtx_ConfigureChannel (ViSession instrumentHandle,
                                          ViInt32 channel, ViBoolean channelEnabled,
                                          ViReal64 verticalRange,
                                          ViReal64 verticalOffset,
                                          ViInt32 verticalCoupling,
                                          ViInt32 channelPolarity,
                                          ViReal64 channelSkew);
ViStatus _VI_FUNC rsrtx_ConfigureChannelZeroOffset (ViSession instrumentHandle,
                                                    ViInt32 channel,
                                                    ViReal64 zeroOffset);
ViStatus _VI_FUNC rsrtx_ConfigureChannelBandwidth (ViSession instrumentHandle,
                                                   ViInt32 channel,
                                                   ViInt32 bandwidth);
ViStatus _VI_FUNC rsrtx_ConfigureChannelVerticalScale (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViReal64 scale);
ViStatus _VI_FUNC rsrtx_QueryChannelOverload (ViSession instrumentHandle,
                                              ViInt32 channel,
                                              ViBoolean* channelOverload);
ViStatus _VI_FUNC rsrtx_ClearChannelOverload (ViSession instrumentHandle,
                                              ViInt32 channel);
ViStatus _VI_FUNC rsrtx_ConfigureChannelPosition (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViReal64 verticalPosition);
ViStatus _VI_FUNC rsrtx_ConfigureChannelWaveformColor (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViInt32 waveformColor);
ViStatus _VI_FUNC rsrtx_ChannelAllOff (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ChannelAllOn (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureDigitalHysteresis (ViSession instrumentHandle,
                                                    ViInt32 digitalChannel,
                                                    ViInt32 hysteresis);
ViStatus _VI_FUNC rsrtx_ConfigureDigitalVerticalChannelSize
             (ViSession instrumentHandle, ViInt32 digitalChannel,
              ViReal64 channelSize);
ViStatus _VI_FUNC rsrtx_QueryDigitalProbeState (ViSession instrumentHandle,
                                                ViInt32 digitalChannel,
                                                ViBoolean* state);
ViStatus _VI_FUNC rsrtx_ConfigureDigitalPointSelection (ViSession instrumentHandle,
                                                        ViInt32 digitalChannel,
                                                        ViInt32 pointSelection);
ViStatus _VI_FUNC rsrtx_QueryProbeCharacteristics (ViSession instrumentHandle,
                                                   ViInt32 channel,
                                                   ViInt32 bufferSize,
                                                   ViChar _VI_FAR type[],
                                                   ViChar _VI_FAR name[],
                                                   ViInt32* inputImpedance,
                                                   ViReal64* inputCapacitance,
                                                   ViReal64* attenuation,
                                                   ViReal64* bandwidth);
ViStatus _VI_FUNC rsrtx_ConfigureProbeDegauss (ViSession instrumentHandle,
                                               ViInt32 channel);
ViStatus _VI_FUNC rsrtx_ConfigureProbeAttenuationManual (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViReal64 attenuation);
ViStatus _VI_FUNC rsrtx_QueryProbeGain (ViSession instrumentHandle, ViInt32 channel,
                                        ViReal64* probeGain);
ViStatus _VI_FUNC rsrtx_ConfigureProbeCMOffset (ViSession instrumentHandle,
                                                ViInt32 channel, ViReal64 CMOffset);
ViStatus _VI_FUNC rsrtx_ConfigureProbeGainUnit (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 unit);
ViStatus _VI_FUNC rsrtx_ConfigureProbeGainManual (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViReal64 probeGain);
ViStatus _VI_FUNC rsrtx_ConfigureProbeCopyToOffset (ViSession instrumentHandle,
                                                    ViInt32 channel);
ViStatus _VI_FUNC rsrtx_ConfigureProbeAttenuatorRTZA15Enabled
             (ViSession instrumentHandle, ViInt32 channel, ViBoolean enabled);
ViStatus _VI_FUNC rsrtx_ConfigureProbeZeroAdjust (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViReal64 zeroAdjust);
ViStatus _VI_FUNC rsrtx_ConfigureProbeSaveZeroAdjust (ViSession instrumentHandle,
                                                      ViInt32 channel);
ViStatus _VI_FUNC rsrtx_ConfigureProbeInputVoltageRange (ViSession instrumentHandle,
                                                         ViInt32 channel,
                                                         ViInt32 range);
ViStatus _VI_FUNC rsrtx_ConfigureProbeBandwidthLimit (ViSession instrumentHandle,
                                                      ViInt32 channel,
                                                      ViBoolean bandwidthLimit);
ViStatus _VI_FUNC rsrtx_ConfigureProbeAudibleOverrange (ViSession instrumentHandle,
                                                        ViInt32 channel,
                                                        ViBoolean audibleOverrange);
ViStatus _VI_FUNC rsrtx_ConfigureProbeMeasMode (ViSession instrumentHandle,
                                                ViInt32 channel, ViInt32 mode);
ViStatus _VI_FUNC rsrtx_ConfigureProbeACCoupling (ViSession instrumentHandle,
                                                  ViInt32 channel,
                                                  ViBoolean ACCoupling);
ViStatus _VI_FUNC rsrtx_ConfigureProbeMeterVisibility (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViBoolean visibility);
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultSingle (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultCommon (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultDifferential
             (ViSession instrumentHandle, ViInt32 channel, ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultNegative (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultPositive (ViSession instrumentHandle,
                                                       ViInt32 channel,
                                                       ViReal64* result);
ViStatus _VI_FUNC rsrtx_ConfigureTrigger (ViSession instrumentHandle,
                                          ViInt32 trigger, ViInt32 triggerType);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerSource (ViSession instrumentHandle,
                                                ViInt32 trigger, ViInt32 channel);
ViStatus _VI_FUNC rsrtx_ConfigureExternalTriggerCoupling (ViSession instrumentHandle,
                                                          ViInt32 externalCoupling);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerHoldoffTime (ViSession instrumentHandle,
                                                     ViReal64 holdoffTime);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerBState (ViSession instrumentHandle,
                                                ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerModifier (ViSession instrumentHandle,
                                                  ViInt32 trigger,
                                                  ViInt32 triggerModifier);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerEventCount (ViSession instrumentHandle,
                                                    ViInt32 eventCount);
ViStatus _VI_FUNC rsrtx_TriggerLevelAutoFind (ViSession instrumentHandle,
                                              ViInt32 trigger);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerChannelLevel (ViSession instrumentHandle,
                                                      ViInt32 trigger,
                                                      ViInt32 channel,
                                                      ViReal64 triggerLevel);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerHysteresis (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViInt32 hysteresis);
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerSource (ViSession instrumentHandle,
                                                    ViInt32 trigger,
                                                    ViInt32 channel,
                                                    ViInt32 triggerSource,
                                                    ViReal64 triggerLevel,
                                                    ViInt32 triggerSlope);
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerCoupling (ViSession instrumentHandle,
                                                      ViInt32 coupling);
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerFilter (ViSession instrumentHandle,
                                                    ViInt32 filterType,
                                                    ViBoolean filterState);
ViStatus _VI_FUNC rsrtx_ConfigureWidthTriggerSource (ViSession instrumentHandle,
                                                     ViInt32 triggerSource,
                                                     ViReal64 triggerLevel,
                                                     ViReal64 width,
                                                     ViReal64 widthDelta,
                                                     ViInt32 widthPolarity,
                                                     ViInt32 widthCondition);
ViStatus _VI_FUNC rsrtx_ConfigurePatternTriggerSource (ViSession instrumentHandle,
                                                       ViString patternSource,
                                                       ViInt32 patternFunction,
                                                       ViBoolean patternCondition);
ViStatus _VI_FUNC rsrtx_ConfigureVideoTriggerSource (ViSession instrumentHandle,
                                                     ViInt32 standard,
                                                     ViInt32 polarity,
                                                     ViInt32 field, ViInt32 line);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerOutMode (ViSession instrumentHandle,
                                                 ViInt32 mode);
ViStatus _VI_FUNC rsrtx_ConfigureRuntTrigger (ViSession instrumentHandle,
                                              ViInt32 polarity, ViInt32 channel,
                                              ViReal64 lowerLevel,
                                              ViReal64 upperLevel);
ViStatus _VI_FUNC rsrtx_RuntTriggerRange (ViSession instrumentHandle,
                                          ViInt32 range);
ViStatus _VI_FUNC rsrtx_ConfigureRuntTriggerWidth (ViSession instrumentHandle,
                                                   ViReal64 width);
ViStatus _VI_FUNC rsrtx_ConfigureRuntTriggerDelta (ViSession instrumentHandle,
                                                   ViReal64 delta);
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerRange (ViSession instrumentHandle,
                                                     ViInt32 range);
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerWidth (ViSession instrumentHandle,
                                                     ViReal64 width);
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerTimeRange (ViSession instrumentHandle,
                                                         ViInt32 timeRange);
ViStatus _VI_FUNC rsrtx_ConfigureTriggerDelay (ViSession instrumentHandle,
                                               ViReal64 delayTime);
ViStatus _VI_FUNC rsrtx_ConfigureTimeoutTriggerTime (ViSession instrumentHandle,
                                                     ViReal64 time, ViInt32 range);
ViStatus _VI_FUNC rsrtx_ConfigureActionsOnTriggerState (ViSession instrumentHandle,
                                                        ViBoolean enabled);
ViStatus _VI_FUNC rsrtx_ConfigureActionsOnTrigger (ViSession instrumentHandle,
                                                   ViBoolean sound,
                                                   ViBoolean screenshot,
                                                   ViBoolean saveWaveform,
                                                   ViBoolean references,
                                                   ViBoolean pulseOut);
ViStatus _VI_FUNC rsrtx_DisplayAddLanguage (ViSession instrumentHandle,
                                            ViInt32 language, ViString source);
ViStatus _VI_FUNC rsrtx_ConfigureDisplayLanguage (ViSession instrumentHandle,
                                                  ViInt32 language);
ViStatus _VI_FUNC rsrtx_MarkerSearch (ViSession instrumentHandle,
                                      ViInt32 markerAction);
ViStatus _VI_FUNC rsrtx_ClearPersistence (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureDiagramAnnotationState (ViSession instrumentHandle,
                                                         ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureDiagramAnnotationTrack (ViSession instrumentHandle,
                                                         ViInt32 annotationTrack);
ViStatus _VI_FUNC rsrtx_EnableDisplayDateAndTime (ViSession instrumentHandle,
                                                  ViBoolean displayDateAndTime);
ViStatus _VI_FUNC rsrtx_DisplayClearScreen (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureDisplayPersistenceType (ViSession instrumentHandle,
                                                         ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureDisplaySegmentationRecordMaximumSegments
             (ViSession instrumentHandle, ViBoolean recordMaximumSegments);
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelTableMode (ViSession instrumentHandle,
                                                      ViInt32 channel,
                                                      ViInt32* mode);
ViStatus _VI_FUNC rsrtx_HistoryChannelExportSave (ViSession instrumentHandle,
                                                  ViInt32 channel, ViString name);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryChannelPlayerControlEnable
             (ViSession instrumentHandle, ViInt32 channel,
              ViBoolean playerControlEnable);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryChannelTimeTableEnable
             (ViSession instrumentHandle, ViInt32 channel,
              ViBoolean timeTableEnable);
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 channel, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelAcquisitionDate
             (ViSession instrumentHandle, ViInt32 channel, ViInt32* year,
              ViInt32* month, ViInt32* day);
ViStatus _VI_FUNC rsrtx_DigitalHistoryExportSave (ViSession instrumentHandle,
                                                  ViInt32 digitalChannel,
                                                  ViString name);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryDigitalPlayerControlEnable
             (ViSession instrumentHandle, ViInt32 digitalChannel,
              ViBoolean playerControlEnable);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryDigitalTimeTableEnable
             (ViSession instrumentHandle, ViInt32 digitalChannel,
              ViBoolean timeTableEnable);
ViStatus _VI_FUNC rsrtx_QueryHistoryDigitalAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 digitalChannel, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistoryDigitalAcquisitionDate
             (ViSession instrumentHandle, ViInt32 digitalChannel, ViInt32* year,
              ViInt32* month, ViInt32* day);
ViStatus _VI_FUNC rsrtx_HistoryMathExportSave (ViSession instrumentHandle,
                                               ViInt32 mathNumber, ViString name);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryMathPlayerControlEnable
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViBoolean playerControlEnable);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryMathTimeTableEnable
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViBoolean timeTableEnable);
ViStatus _VI_FUNC rsrtx_QueryHistoryMathAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 mathNumber, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistoryMathAcquisitionDate (ViSession instrumentHandle,
                                                         ViInt32 mathNumber,
                                                         ViInt32* year,
                                                         ViInt32* month,
                                                         ViInt32* day);
ViStatus _VI_FUNC rsrtx_HistoryProtocolExportSave (ViSession instrumentHandle,
                                                   ViInt32 serialBus,
                                                   ViString name);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryProtocolPlayerControlEnable
             (ViSession instrumentHandle, ViInt32 serialBus,
              ViBoolean playerControlEnable);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryProtocolTimeTableEnable
             (ViSession instrumentHandle, ViInt32 serialBus,
              ViBoolean timeTableEnable);
ViStatus _VI_FUNC rsrtx_QueryHistoryProtocolAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistoryProtocolAcquisitionDate
             (ViSession instrumentHandle, ViInt32 serialBus, ViInt32* year,
              ViInt32* month, ViInt32* day);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 segmentNumber, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionRelativeTime
             (ViSession instrumentHandle, ViInt32 segmentNumber, ViReal64* time);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionDate
             (ViSession instrumentHandle, ViInt32 segmentNumber, ViInt32* year,
              ViInt32* month, ViInt32* day);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllDates (ViSession instrumentHandle,
                                                      ViInt32 bufferSize,
                                                      ViChar _VI_FAR allDates[]);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllTimeDifferences
             (ViSession instrumentHandle, ViInt32 bufferSize,
              ViChar _VI_FAR allTimeDifferences[]);
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllDaytimes (ViSession instrumentHandle,
                                                         ViChar _VI_FAR allDaytimes[],
                                                         ViInt32 bufferSize);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicCurrentAcquisition
             (ViSession instrumentHandle, ViInt32 logic,
              ViInt32 currentAcquisition);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayer (ViSession instrumentHandle,
                                                     ViInt32 logic, ViInt32 player);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicAcquisitionStartStop
             (ViSession instrumentHandle, ViInt32 logic, ViInt32 start,
              ViInt32 stop);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayAll (ViSession instrumentHandle,
                                                      ViInt32 logic,
                                                      ViBoolean playAll);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicSpeed (ViSession instrumentHandle,
                                                    ViInt32 logic, ViInt32 speed);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicRepeat (ViSession instrumentHandle,
                                                     ViInt32 logic,
                                                     ViBoolean repeat);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitionAbsoluteTime
             (ViSession instrumentHandle, ViInt32 logic, ViInt32* hour,
              ViInt32* minute, ViReal64* second);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitonRelativeTime
             (ViSession instrumentHandle, ViInt32 logic, ViReal64* time);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitionDate (ViSession instrumentHandle,
                                                          ViInt32 logic,
                                                          ViInt32* year,
                                                          ViInt32* month,
                                                          ViInt32* day);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllDates (ViSession instrumentHandle,
                                                   ViInt32 logic,
                                                   ViInt32 bufferSize,
                                                   ViChar _VI_FAR allDates[]);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllTimeDifferences
             (ViSession instrumentHandle, ViInt32 logic, ViInt32 bufferSize,
              ViChar _VI_FAR timeDifferences[]);
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllDaytimes (ViSession instrumentHandle,
                                                      ViInt32 logic,
                                                      ViInt32 bufferSize,
                                                      ViChar _VI_FAR allDaytimes[]);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayerControlEnable
             (ViSession instrumentHandle, ViInt32 logic,
              ViBoolean playerControlEnable);
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicTimeTableEnable
             (ViSession instrumentHandle, ViInt32 logic, ViBoolean timeTableEnable);
ViStatus _VI_FUNC rsrtx_HistoryLogicExportSave (ViSession instrumentHandle,
                                                ViInt32 logic, ViString exportName);
ViStatus _VI_FUNC rsrtx_ConfigureZoomWindowEnabled (ViSession instrumentHandle,
                                                    ViBoolean zoomWindowEnabled);
ViStatus _VI_FUNC rsrtx_ConfigureZoomDiagramTimebase (ViSession instrumentHandle,
                                                      ViReal64 diagramTimebase);
ViStatus _VI_FUNC rsrtx_ConfigureZoomOffsetOfTriggerPoint
             (ViSession instrumentHandle, ViReal64 offsetOfTriggerPoint);
ViStatus _VI_FUNC rsrtx_ConfigureZoomReferencePoint (ViSession instrumentHandle,
                                                     ViReal64 referencePoint);
ViStatus _VI_FUNC rsrtx_ConfigureZoomWindowPosition (ViSession instrumentHandle,
                                                     ViInt32 zoomWindowPosition);
ViStatus _VI_FUNC rsrtx_QueryZoomSampleRate (ViSession instrumentHandle,
                                             ViReal64* sampleRate);
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementSource (ViSession instrumentHandle,
                                                    ViInt32 measurement,
                                                    ViInt32 signalSource,
                                                    ViInt32 referenceSource);
ViStatus _VI_FUNC rsrtx_ConfigureAmplitudeTimeMainMeasurement
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasurementMarkerVisible
             (ViSession instrumentHandle, ViInt32 measurement, ViBoolean visible);
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasuremenSlope (ViSession instrumentHandle,
                                                       ViInt32 measurement,
                                                       ViInt32 source1Slope,
                                                       ViInt32 source2Slope);
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasurementDirection
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 direction1,
              ViInt32 direction2);
ViStatus _VI_FUNC rsrtx_ConfigureReferenceLevelMode (ViSession instrumentHandle,
                                                     ViInt32 relativeMode);
ViStatus _VI_FUNC rsrtx_ConfigureUserReferenceLevel (ViSession instrumentHandle,
                                                     ViReal64 lowerLevel,
                                                     ViReal64 upperLevel,
                                                     ViReal64 middleLevel);
ViStatus _VI_FUNC rsrtx_AllCursorsOff (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureCursorMeasurementType (ViSession instrumentHandle,
                                                        ViInt32 cursor,
                                                        ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureCursorSource (ViSession instrumentHandle,
                                               ViInt32 cursor, ViInt32 source);
ViStatus _VI_FUNC rsrtx_ConfigureCursorSecondSourceSettings
             (ViSession instrumentHandle, ViBoolean secondSourceEnable,
              ViInt32 secondSource);
ViStatus _VI_FUNC rsrtx_SetCursorPosition (ViSession instrumentHandle,
                                           ViInt32 cursor, ViInt32 position);
ViStatus _VI_FUNC rsrtx_ConfigureCursorPosition (ViSession instrumentHandle,
                                                 ViReal64 xPosition1,
                                                 ViReal64 xPosition2,
                                                 ViReal64 yPosition1,
                                                 ViReal64 yPosition2);
ViStatus _VI_FUNC rsrtx_SetFFTAnalysisCursorToPeak (ViSession instrumentHandle,
                                                    ViInt32 cursor, ViInt32 peak);
ViStatus _VI_FUNC rsrtx_CursorLineNextPeak (ViSession instrumentHandle,
                                            ViInt32 cursor, ViInt32 cursorLine);
ViStatus _VI_FUNC rsrtx_CursorLinePreviousPeak (ViSession instrumentHandle,
                                                ViInt32 cursor, ViInt32 cursorLine);
ViStatus _VI_FUNC rsrtx_ConfigureQuickMeasurementState (ViSession instrumentHandle,
                                                        ViInt32 measurement,
                                                        ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureQuickMeasurements (ViSession instrumentHandle,
                                                    ViInt32 measurement,
                                                    ViBoolean quickMeasurementsEnabled);
ViStatus _VI_FUNC rsrtx_QueryQuickMeasurementResults (ViSession instrumentHandle,
                                                      ViInt32 measurement,
                                                      ViInt32 arraySize,
                                                      ViReal64 _VI_FAR results[]);
ViStatus _VI_FUNC rsrtx_ConfigureAutomaticMeasurementTimeoutAuto
             (ViSession instrumentHandle, ViInt32 measurement,
              ViBoolean autoTimeout);
ViStatus _VI_FUNC rsrtx_ConfigureAutomaticMeasurementTimeout
             (ViSession instrumentHandle, ViInt32 measurement, ViReal64 timeout);
ViStatus _VI_FUNC rsrtx_ResetAutomaticMeasurement (ViSession instrumentHandle,
                                                   ViInt32 measurement);
ViStatus _VI_FUNC rsrtx_QueryAutomaticMeasurementAllStatisticalValues
             (ViSession instrumentHandle, ViInt32 measurement, ViInt32 arraySize,
              ViReal64 _VI_FAR results[]);
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateEnable (ViSession instrumentHandle,
                                                        ViBoolean gateEnable,
                                                        ViInt32 mode);
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateAbsoluteTime
             (ViSession instrumentHandle, ViReal64 startTime, ViReal64 endTime);
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateRelativeValues
             (ViSession instrumentHandle, ViReal64 startValue, ViReal64 endValue);
ViStatus _VI_FUNC rsrtx_SampleMode (ViSession instrumentHandle,
                                    ViInt32* sampleMode);
ViStatus _VI_FUNC rsrtx_MaskCopyChannel (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_MaskResetTestCounter (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionScreenshotDestination
             (ViSession instrumentHandle, ViString destination);
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionSavesWaveformDestination
             (ViSession instrumentHandle, ViString destination);
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionAUXOutputState
             (ViSession instrumentHandle, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureMaskScaling (ViSession instrumentHandle,
                                              ViReal64 verticalOffset,
                                              ViReal64 verticalScaling,
                                              ViReal64 verticalWidth,
                                              ViReal64 horizontalWidth);
ViStatus _VI_FUNC rsrtx_ConfigureMaskSegmentCaptureMode (ViSession instrumentHandle,
                                                         ViInt32 captureMode);
ViStatus _VI_FUNC rsrtx_ConfigureSearchCondition (ViSession instrumentHandle,
                                                  ViInt32 condition);
ViStatus _VI_FUNC rsrtx_ConfigureSearchSource (ViSession instrumentHandle,
                                               ViInt32 source);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowLevel
             (ViSession instrumentHandle, ViReal64 lower, ViReal64 upper);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowDelta
             (ViSession instrumentHandle, ViReal64 delta);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowPolarity
             (ViSession instrumentHandle, ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowRange
             (ViSession instrumentHandle, ViInt32 range);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowTimeRange
             (ViSession instrumentHandle, ViInt32 timeRange);
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowWidth
             (ViSession instrumentHandle, ViReal64 width);
ViStatus _VI_FUNC rsrtx_SearchExportSave (ViSession instrumentHandle,
                                          ViString name);
ViStatus _VI_FUNC rsrtx_QuerySearchResult (ViSession instrumentHandle,
                                           ViInt32 resultNumber,
                                           ViReal64* xPosition, ViReal64* yPosition,
                                           ViInt32* resultType, ViInt32* polarity,
                                           ViReal64* voltageWidth);
ViStatus _VI_FUNC rsrtx_QueryAllSearchResults (ViSession instrumentHandle,
                                               ViInt32 arraySize,
                                               ViReal64 _VI_FAR xPosition[],
                                               ViReal64 _VI_FAR yPosition[],
                                               ViInt32 _VI_FAR resultType[],
                                               ViInt32 _VI_FAR polarity[],
                                               ViReal64 _VI_FAR voltageWidth[],
                                               ViInt32* numberOfResults);
ViStatus _VI_FUNC rsrtx_ProtocolFindLevel (ViSession instrumentHandle,
                                           ViInt32 channel);
ViStatus _VI_FUNC rsrtx_QueryBusDecodedData (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 bufferSize,
                                             ViChar _VI_FAR decodedData[]);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolDisplayVertical (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViReal64 vertical);
ViStatus _VI_FUNC rsrtx_QueryI2CFrameAllData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 arraySize,
                                              ViInt32 _VI_FAR data[],
                                              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPICSPolarity (ViSession instrumentHandle,
                                                        ViInt32 serialBus,
                                                        ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureSPITriggerSource (ViSession instrumentHandle,
                                                   ViInt32 triggerSource);
ViStatus _VI_FUNC rsrtx_QuerySPIFrameAllData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 line,
                                              ViInt32 frame, ViInt32 arraySize,
                                              ViInt32 _VI_FAR data[],
                                              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_QueryLINFrameAllData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 arraySize,
                                              ViInt32 _VI_FAR data[],
                                              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_QueryCANFrameAllData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 frame,
                                              ViInt32 arraySize,
                                              ViInt32 _VI_FAR data[],
                                              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_ProtocolAudioTrackWaveformSetToDefault
             (ViSession instrumentHandle, ViInt32 serialBus);
ViStatus _VI_FUNC rsrtx_ProtocolAudioTrackWaveformSetToScreen
             (ViSession instrumentHandle, ViInt32 serialBus);
ViStatus _VI_FUNC rsrtx_ConfigureUARTTriggerSource (ViSession instrumentHandle,
                                                    ViInt32 triggerSource);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolUARTIdleStatePolarity
             (ViSession instrumentHandle, ViInt32 serialBus,
              ViInt32 idleStatePolarity);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTFrameCount (ViSession instrumentHandle,
                                                     ViInt32 serialBus,
                                                     ViInt32* count);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTWordCount (ViSession instrumentHandle,
                                                    ViInt32 serialBus,
                                                    ViInt32 frame, ViInt32* count);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTFrameSettings (ViSession instrumentHandle,
                                                        ViInt32 serialBus,
                                                        ViInt32 frame,
                                                        ViInt32* frameState,
                                                        ViReal64* frameStart,
                                                        ViReal64* frameEnd);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTRxFrameSettings (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViInt32 frame,
                                                          ViInt32* rxFrameState,
                                                          ViReal64* rxFrameStart,
                                                          ViReal64* rxFrameEnd);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTTxFrameSettings (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViInt32 frame,
                                                          ViInt32* txFrameState,
                                                          ViReal64* txFrameStart,
                                                          ViReal64* txFrameEnd);
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTWordValue (ViSession instrumentHandle,
                                                    ViInt32 serialBus,
                                                    ViInt32 frame, ViInt32 word,
                                                    ViInt32* value, ViReal64* start,
                                                    ViReal64* end, ViInt32* status,
                                                    ViInt32* source);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPICSSource (ViSession instrumentHandle,
                                                      ViInt32 serialBus,
                                                      ViInt32 protocolSPICSSource);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMOSIPolarity (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViInt32 protocolSPIMOSIPolarity);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMISOSource (ViSession instrumentHandle,
                                                        ViInt32 serialBus,
                                                        ViInt32 protocolSPIMISOSource);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMISOPolarity (ViSession instrumentHandle,
                                                          ViInt32 serialBus,
                                                          ViInt32 protocolSPIMISOPolarity);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMISOSource (ViSession instrumentHandle,
                                                         ViInt32 serialBus,
                                                         ViInt32 protocolSSPIMISOSource);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMOSIPolarity
             (ViSession instrumentHandle, ViInt32 serialBus,
              ViInt32 protocolSSPIMOSIPolarity);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMISOPolarity
             (ViSession instrumentHandle, ViInt32 serialBus,
              ViInt32 protocolSSPIMISOPolarity);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDInterMessageGapTimeInfinite
             (ViSession instrumentHandle, ViInt32 serialBus, ViBoolean infinite);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDInterMessageGapTime
             (ViSession instrumentHandle, ViInt32 serialBus, ViReal64 minimum,
              ViReal64 maximum);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDResponseTimeInfinite
             (ViSession instrumentHandle, ViInt32 serialBus, ViBoolean infinite);
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDResponseTime
             (ViSession instrumentHandle, ViInt32 serialBus, ViReal64 minimum,
              ViReal64 maximum);
ViStatus _VI_FUNC rsrtx_ConfigureMILSTDTriggerMode (ViSession instrumentHandle,
                                                    ViInt32 mode);
ViStatus _VI_FUNC rsrtx_ConfigureMILSTDTriggerFrame (ViSession instrumentHandle,
                                                     ViInt32 frame);
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Source (ViSession instrumentHandle,
                                                 ViInt32 serialBus, ViInt32 source);
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Polarity (ViSession instrumentHandle,
                                                   ViInt32 serialBus,
                                                   ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureARINC429BitRate (ViSession instrumentHandle,
                                                  ViInt32 serialBus,
                                                  ViInt32 bitRateMode,
                                                  ViReal64 bitRateValue);
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Threshold (ViSession instrumentHandle,
                                                    ViInt32 serialBus,
                                                    ViReal64 thresholdHigh,
                                                    ViReal64 thresholdLow);
ViStatus _VI_FUNC rsrtx_ConfigureARINC429TriggerType (ViSession instrumentHandle,
                                                      ViInt32 type);
ViStatus _VI_FUNC rsrtx_QueryARINC429WordCount (ViSession instrumentHandle,
                                                ViInt32 serialBus, ViInt32* count);
ViStatus _VI_FUNC rsrtx_QueryARINC429Status (ViSession instrumentHandle,
                                             ViInt32 serialBus, ViInt32 word,
                                             ViInt32* status, ViReal64* start,
                                             ViReal64* stop, ViInt32* pattern,
                                             ViInt32* SDI, ViInt32* SSM);
ViStatus _VI_FUNC rsrtx_QueryARINC429AllData (ViSession instrumentHandle,
                                              ViInt32 serialBus, ViInt32 word,
                                              ViInt32 arraySize,
                                              ViInt32 _VI_FAR data[],
                                              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_ConfigureHardcopySettings (ViSession instrumentHandle,
                                                   ViString fileName,
                                                   ViInt32 deviceDestination,
                                                   ViBoolean includeMenuInScreenshot,
                                                   ViInt32 deviceLanguageOutputFormat);
ViStatus _VI_FUNC rsrtx_HardcopyPrint (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureHardcopyOutputFormat (ViSession instrumentHandle,
                                                       ViInt32 format);
ViStatus _VI_FUNC rsrtx_CloseHardcopyDialogs (ViSession instrumentHandle,
                                              ViBoolean closeDialogs);
ViStatus _VI_FUNC rsrtx_QueryHardcopyData (ViSession instrumentHandle,
                                           ViInt32 format, ViString fileName);
ViStatus _VI_FUNC rsrtx_QueryHardcopyPageSize (ViSession instrumentHandle,
                                               ViInt32* x, ViInt32* y);
ViStatus _VI_FUNC rsrtx_SetAttributeViInt32 (ViSession instrumentHandle,
                                             ViString channelName,
                                             ViAttr attributeID,
                                             ViInt32 attributeValue);
ViStatus _VI_FUNC rsrtx_SetAttributeViReal64 (ViSession instrumentHandle,
                                              ViString channelName,
                                              ViAttr attributeID,
                                              ViReal64 attributeValue);
ViStatus _VI_FUNC rsrtx_SetAttributeViString (ViSession instrumentHandle,
                                              ViString channelName,
                                              ViAttr attributeID,
                                              ViString attributeValue);
ViStatus _VI_FUNC rsrtx_SetAttributeViBoolean (ViSession instrumentHandle,
                                               ViString channelName,
                                               ViAttr attributeID,
                                               ViBoolean attributeValue);
ViStatus _VI_FUNC rsrtx_SetAttributeViSession (ViSession instrumentHandle,
                                               ViString channelName,
                                               ViAttr attributeID,
                                               ViSession attributeValue);
ViStatus _VI_FUNC rsrtx_GetAttributeViInt32 (ViSession instrumentHandle,
                                             ViString channelName,
                                             ViAttr attributeID,
                                             ViInt32* attributeValue);
ViStatus _VI_FUNC rsrtx_GetAttributeViReal64 (ViSession instrumentHandle,
                                              ViString channelName,
                                              ViAttr attributeID,
                                              ViReal64* attributeValue);
ViStatus _VI_FUNC rsrtx_GetAttributeViString (ViSession instrumentHandle,
                                              ViString channelName,
                                              ViAttr attributeID,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR attributeValue[]);
ViStatus _VI_FUNC rsrtx_GetAttributeViBoolean (ViSession instrumentHandle,
                                               ViString channelName,
                                               ViAttr attributeID,
                                               ViBoolean* attributeValue);
ViStatus _VI_FUNC rsrtx_GetAttributeViSession (ViSession instrumentHandle,
                                               ViString channelName,
                                               ViAttr attributeID,
                                               ViSession* attributeValue);
ViStatus _VI_FUNC rsrtx_CheckAttributeViInt32 (ViSession instrumentHandle,
                                               ViString channelName,
                                               ViAttr attributeID,
                                               ViInt32 attributeValue);
ViStatus _VI_FUNC rsrtx_CheckAttributeViReal64 (ViSession instrumentHandle,
                                                ViString channelName,
                                                ViAttr attributeID,
                                                ViReal64 attributeValue);
ViStatus _VI_FUNC rsrtx_CheckAttributeViString (ViSession instrumentHandle,
                                                ViString channelName,
                                                ViAttr attributeID,
                                                ViString attributeValue);
ViStatus _VI_FUNC rsrtx_CheckAttributeViBoolean (ViSession instrumentHandle,
                                                 ViString channelName,
                                                 ViAttr attributeID,
                                                 ViBoolean attributeValue);
ViStatus _VI_FUNC rsrtx_CheckAttributeViSession (ViSession instrumentHandle,
                                                 ViString channelName,
                                                 ViAttr attributeID,
                                                 ViSession attributeValue);
ViStatus _VI_FUNC rsrtx_GetAttributeRepCapName (ViSession instrumentHandle,
                                                ViUInt32 attributeID,
                                                ViString repCapNameID,
                                                ViInt32 index, ViInt32 bufferSize,
                                                ViChar _VI_FAR repCapName[]);
ViStatus _VI_FUNC rsrtx_GetAttributeRepeatedCapabilityIds
             (ViSession instrumentHandle, ViUInt32 attributeID, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityId_s[]);
ViStatus _VI_FUNC rsrtx_GetAttributeRepeatedCapabilityIdNames
             (ViSession instrumentHandle, ViUInt32 attributeID,
              ViString repeatedCapabilityId, ViInt32 bufferSize,
              ViChar _VI_FAR repeatedCapabilityIdName_s[]);
ViStatus _VI_FUNC rsrtx_ConfigureMathWaveformLabel (ViSession instrumentHandle,
                                                    ViInt32 mathNumber,
                                                    ViString waveformLabel,
                                                    ViBoolean labelState);
ViStatus _VI_FUNC rsrtx_ConfigureMathWaveformColor (ViSession instrumentHandle,
                                                    ViInt32 mathNumber,
                                                    ViInt32 mathWaveformColor);
ViStatus _VI_FUNC rsrtx_ConfigureFFTFrequencySpanFull (ViSession instrumentHandle,
                                                       ViInt32 mathNumber);
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackEdgePolarity (ViSession instrumentHandle,
                                                        ViInt32 mathNumber,
                                                        ViBoolean edgePolarity);
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackDoublePulseEnable
             (ViSession instrumentHandle, ViInt32 mathNumber,
              ViBoolean doublePulseEnable);
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackThresholdSettings
             (ViSession instrumentHandle, ViInt32 mathNumber, ViReal64 hysteresis,
              ViReal64 thresholdLower, ViReal64 thresholdUpper);
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformLabel (ViSession instrumentHandle,
                                                         ViInt32 referenceNumber,
                                                         ViString waveformLabel);
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformColor (ViSession instrumentHandle,
                                                         ViInt32 referenceNumber,
                                                         ViInt32 waveformColor);
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformSource (ViSession instrumentHandle,
                                                          ViInt32 referenceNumber,
                                                          ViInt32 source);
ViStatus _VI_FUNC rsrtx_UpdateReferenceWaveformWithSelectedSource
             (ViSession instrumentHandle, ViInt32 referenceNumber);
ViStatus _VI_FUNC rsrtx_ReferenceWaveformFileOperations (ViSession instrumentHandle,
                                                         ViInt32 referenceWfm,
                                                         ViInt32 operation,
                                                         ViString fileName);
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformState (ViSession instrumentHandle,
                                                          ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformPosition
             (ViSession instrumentHandle, ViReal64 position);
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformVerticalScale
             (ViSession instrumentHandle, ViReal64 verticalScale);
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformOperation
             (ViSession instrumentHandle, ViInt32 operation);
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformSource
             (ViSession instrumentHandle, ViInt32 source1, ViInt32 source2);
ViStatus _VI_FUNC rsrtx_ReadWaveform (ViSession instrumentHandle, ViInt32 channel,
                                      ViInt32 waveformSize, ViInt32 maximumTime,
                                      ViReal64 _VI_FAR waveformArray[],
                                      ViInt32* actualPoints, ViReal64* initialX,
                                      ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_ReadMaskData (ViSession instrumentHandle,
                                      ViInt32 waveformSize, ViInt32 maximumTime,
                                      ViReal64 _VI_FAR waveformArray[],
                                      ViInt32* actualPoints, ViReal64* initialX,
                                      ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_ReadMainWaveformMeasurement (ViSession instrumentHandle,
                                                     ViInt32 measurement,
                                                     ViInt32 measurementFunction,
                                                     ViInt32 maximumTime,
                                                     ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_InitiateAcquisition (ViSession instrumentHandle,
                                             ViInt32 action);
ViStatus _VI_FUNC rsrtx_InitiateAcquisitionAndWait (ViSession instrumentHandle,
                                                    ViInt32 maximumTime);
ViStatus _VI_FUNC rsrtx_SendSoftwareTrigger (ViSession instrumentHandle,
                                             ViInt32 maximumTime);
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionState (ViSession instrumentHandle,
                                                   ViInt32 acquisitionState);
ViStatus _VI_FUNC rsrtx_FetchWaveform (ViSession instrumentHandle, ViInt32 channel,
                                       ViInt32 waveformSize,
                                       ViReal64 _VI_FAR waveformArray[],
                                       ViInt32* actualPoints, ViReal64* initialX,
                                       ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchWaveformInteger (ViSession instrumentHandle,
                                              ViInt32 channel, ViInt32 waveformSize,
                                              ViUInt16 _VI_FAR waveformArray[],
                                              ViInt32* actualPoints,
                                              ViReal64* initialX,
                                              ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchWaveformByte (ViSession instrumentHandle,
                                           ViInt32 channel, ViInt32 waveformSize,
                                           ViByte _VI_FAR waveformArray[],
                                           ViInt32* actualPoints,
                                           ViReal64* initialX,
                                           ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchWaveformHeader (ViSession instrumentHandle,
                                             ViInt32 channel, ViReal64* xStart,
                                             ViReal64* xStop, ViInt32* recordLength,
                                             ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchWaveformConversionData (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViReal64* xStart,
                                                     ViReal64* xIncrement,
                                                     ViReal64* yStart,
                                                     ViReal64* yIncrement,
                                                     ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveform (ViSession instrumentHandle,
                                               ViInt32 channel,
                                               ViInt32 waveformSize,
                                               ViReal64 _VI_FAR waveformArray[],
                                               ViInt32* actualPoints,
                                               ViReal64* initialX,
                                               ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveformHeader (ViSession instrumentHandle,
                                                     ViInt32 channel,
                                                     ViReal64* xStart,
                                                     ViReal64* xStop,
                                                     ViInt32* recordLength,
                                                     ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveformConversionData
             (ViSession instrumentHandle, ViInt32 channel, ViReal64* xStart,
              ViReal64* xIncrement, ViReal64* yStart, ViReal64* yIncrement,
              ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchMathWaveform (ViSession instrumentHandle,
                                           ViInt32 mathNumber, ViInt32 waveformSize,
                                           ViReal64 _VI_FAR waveformArray[],
                                           ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchMathWaveformHeader (ViSession instrumentHandle,
                                                 ViInt32 mathNumber,
                                                 ViReal64* xStart, ViReal64* xStop,
                                                 ViInt32* recordLength,
                                                 ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchMathWaveformConversionData (ViSession instrumentHandle,
                                                         ViInt32 math,
                                                         ViReal64* xStart,
                                                         ViReal64* xIncrement,
                                                         ViReal64* yStart,
                                                         ViReal64* yIncrement,
                                                         ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveform (ViSession instrumentHandle,
                                                ViInt32 referenceWfm,
                                                ViInt32 waveformSize,
                                                ViReal64 _VI_FAR waveformArray[],
                                                ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveformHeader (ViSession instrumentHandle,
                                                      ViInt32 referenceWfm,
                                                      ViReal64* xStart,
                                                      ViReal64* xStop,
                                                      ViInt32* recordLength,
                                                      ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveformConversionData
             (ViSession instrumentHandle, ViInt32 channel, ViReal64* xStart,
              ViReal64* xIncrement, ViReal64* yStart, ViReal64* yIncrement,
              ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchMaskData (ViSession instrumentHandle,
                                       ViInt32 waveformSize,
                                       ViReal64 _VI_FAR waveformArray[],
                                       ViInt32* actualPoints, ViReal64* initialX,
                                       ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchMaskDataHeader (ViSession instrumentHandle,
                                             ViReal64* xStart, ViReal64* xStop,
                                             ViInt32* recordLength,
                                             ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchMaskConversionData (ViSession instrumentHandle,
                                                 ViReal64* xStart,
                                                 ViReal64* xIncrement,
                                                 ViReal64* yStart,
                                                 ViReal64* yIncrement,
                                                 ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchMainWaveformMeasurement (ViSession instrumentHandle,
                                                      ViInt32 measurement,
                                                      ViInt32 measurementFunction,
                                                      ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_Abort (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_FetchSimpleMathWaveform (ViSession instrumentHandle,
                                                 ViInt32 waveformSize,
                                                 ViReal64 _VI_FAR waveformArray[],
                                                 ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSimpleMathWaveformHeader (ViSession instrumentHandle,
                                                       ViReal64* xStart,
                                                       ViReal64* xStop,
                                                       ViInt32* recordLength,
                                                       ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QuerySimpleMathDataConversion (ViSession instrumentHandle,
                                                       ViReal64* xStart,
                                                       ViReal64* xIncrement,
                                                       ViReal64* yStart,
                                                       ViReal64* yIncrement,
                                                       ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QueryDigitalWaveformSamplesNumber
             (ViSession instrumentHandle, ViInt32 digital, ViInt32* samplesNumber);
ViStatus _VI_FUNC rsrtx_FetchDigitalWaveform (ViSession instrumentHandle,
                                              ViInt32 digital, ViInt32 waveformSize,
                                              ViReal64 _VI_FAR waveformArray[],
                                              ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchDigitalWaveformHeader (ViSession instrumentHandle,
                                                    ViInt32 digital,
                                                    ViReal64* xStart,
                                                    ViReal64* xStop,
                                                    ViInt32* recordLength,
                                                    ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QueryDigitalDataConversion (ViSession instrumentHandle,
                                                    ViInt32 digital,
                                                    ViReal64* xStart,
                                                    ViReal64* xIncrement,
                                                    ViReal64* yStart,
                                                    ViReal64* yIncrement,
                                                    ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_FetchLogicWaveform (ViSession instrumentHandle,
                                            ViInt32 logic, ViInt32 waveformSize,
                                            ViReal64 _VI_FAR waveformArray[],
                                            ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchLogicWaveformHeader (ViSession instrumentHandle,
                                                  ViInt32 logic, ViReal64* xStart,
                                                  ViReal64* xStop,
                                                  ViInt32* recordLength,
                                                  ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QueryLogicDataConversion (ViSession instrumentHandle,
                                                  ViInt32 logic, ViReal64* xStart,
                                                  ViReal64* xIncrement,
                                                  ViReal64* yStart,
                                                  ViReal64* yIncrement,
                                                  ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QuerySpectrumWaveformSamples (ViSession instrumentHandle,
                                                      ViInt32* waveformSamples);
ViStatus _VI_FUNC rsrtx_ReadSpectrumDataWaveform (ViSession instrumentHandle,
                                                  ViInt32 waveformSize,
                                                  ViInt32 maximumTime,
                                                  ViReal64 _VI_FAR waveformArray[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumDataWaveform (ViSession instrumentHandle,
                                                   ViInt32 waveformSize,
                                                   ViReal64 _VI_FAR waveformArray[],
                                                   ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumDataWaveformHeader (ViSession instrumentHandle,
                                                         ViReal64* xStart,
                                                         ViReal64* xStop,
                                                         ViInt32* recordLength,
                                                         ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QuerySpectrumDataConversion (ViSession instrumentHandle,
                                                     ViReal64* xStart,
                                                     ViReal64* xIncrement,
                                                     ViReal64* yStart,
                                                     ViReal64* yIncrement,
                                                     ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QuerySpectrumAverageWaveformSamples
             (ViSession instrumentHandle, ViInt32* averageWaveformSamples);
ViStatus _VI_FUNC rsrtx_ReadSpectrumAverageData (ViSession instrumentHandle,
                                                 ViInt32 waveformSize,
                                                 ViInt32 maximumTime,
                                                 ViReal64 _VI_FAR waveformArray[],
                                                 ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumAverageData (ViSession instrumentHandle,
                                                  ViInt32 waveformSize,
                                                  ViReal64 _VI_FAR waveformArray[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumAverageDataHeader (ViSession instrumentHandle,
                                                        ViReal64* xStart,
                                                        ViReal64* xStop,
                                                        ViInt32* recordLength,
                                                        ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QuerySpectrumAverageDataConversion
             (ViSession instrumentHandle, ViReal64* xStart, ViReal64* xIncrement,
              ViReal64* yStart, ViReal64* yIncrement, ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMaximumWaveformSamples
             (ViSession instrumentHandle, ViInt32* maximumWaveformSamples);
ViStatus _VI_FUNC rsrtx_ReadSpectrumMaximumData (ViSession instrumentHandle,
                                                 ViInt32 waveformSize,
                                                 ViInt32 maximumTime,
                                                 ViReal64 _VI_FAR waveformArray[],
                                                 ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumMaximumData (ViSession instrumentHandle,
                                                  ViInt32 waveformSize,
                                                  ViReal64 _VI_FAR waveformArray[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumMaximumDataHeader (ViSession instrumentHandle,
                                                        ViReal64* xStart,
                                                        ViReal64* xStop,
                                                        ViInt32* recordLength,
                                                        ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMaximumDataConversion
             (ViSession instrumentHandle, ViReal64* xStart, ViReal64* xIncrement,
              ViReal64* yStart, ViReal64* yIncrement, ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMinimumWaveformSamples
             (ViSession instrumentHandle, ViInt32* minimumWaveformSamples);
ViStatus _VI_FUNC rsrtx_ReadSpectrumMinimumData (ViSession instrumentHandle,
                                                 ViInt32 waveformSize,
                                                 ViInt32 maximumTime,
                                                 ViReal64 _VI_FAR waveformArray[],
                                                 ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumMinimumData (ViSession instrumentHandle,
                                                  ViInt32 waveformSize,
                                                  ViReal64 _VI_FAR waveformArray[],
                                                  ViInt32* actualPoints);
ViStatus _VI_FUNC rsrtx_FetchSpectrumMinimumDataHeader (ViSession instrumentHandle,
                                                        ViReal64* xStart,
                                                        ViReal64* xStop,
                                                        ViInt32* recordLength,
                                                        ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMinimumDataConversion
             (ViSession instrumentHandle, ViReal64* xStart, ViReal64* xIncrement,
              ViReal64* yStart, ViReal64* yIncrement, ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_WaveformExportSource (ViSession instrumentHandle,
                                              ViInt32 source);
ViStatus _VI_FUNC rsrtx_WaveformExportSave (ViSession instrumentHandle,
                                            ViString name);
ViStatus _VI_FUNC rsrtx_ConfigurePowerAnalysisState (ViSession instrumentHandle,
                                                     ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigurePowerAnalysisType (ViSession instrumentHandle,
                                                    ViInt32 type);
ViStatus _VI_FUNC rsrtx_ResetPowerAnalysisStatistics (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_StartPowerAnalysisDeskew (ViSession instrumentHandle,
                                                  ViInt32 maximumTime);
ViStatus _VI_FUNC rsrtx_SetPowerAnalysisZeroOffset (ViSession instrumentHandle,
                                                    ViInt32 maximumTime);
ViStatus _VI_FUNC rsrtx_PowerAnalysisAddReport (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutoset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutosetCurrent (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutosetVoltage (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_StartPowerQualityMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerQualityMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementVoltageResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementCurrentResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementPowerResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerConsumptionMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_RestartPowerConsumptionMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerConsumptionMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerConsumptionMeasurementResults
             (ViSession instrumentHandle, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerCurrentHarmonicsMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerCurrentHarmonicsMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementDuration
             (ViSession instrumentHandle, ViReal64* duration);
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementResult
             (ViSession instrumentHandle, ViInt32 resultNumber, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementLimitCheckResult
             (ViSession instrumentHandle, ViInt32 resultNumber,
              ViInt32* limitCheck);
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementRealPowerCurrent
             (ViSession instrumentHandle, ViReal64* current);
ViStatus _VI_FUNC rsrtx_ResetPowerCurrentHarmonicsMeasurementResults
             (ViSession instrumentHandle, ViInt32 resultNumber);
ViStatus _VI_FUNC rsrtx_StartPowerInrushCurrentMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerInrushCurrentMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerInrushCurrentMeasurementResult
             (ViSession instrumentHandle, ViInt32 gateNumber, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerRippleMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerRippleMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerRippleMeasurementResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerSpectrumMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerSpectrumMeasurementResult
             (ViSession instrumentHandle, ViInt32 resultNumber, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_PowerSpectrumMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ResetPowerSpectrumMeasurementResults
             (ViSession instrumentHandle, ViInt32 resultNumber);
ViStatus _VI_FUNC rsrtx_StartPowerSlewRateMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerSlewRateMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerSlewRateMeasurementResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerModulationMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerModulationMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerModulationMeasurementResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_ConfigurePowerModulationThresholdSettings
             (ViSession instrumentHandle, ViReal64 thresholdHysteresis,
              ViReal64 thresholdUpper, ViReal64 thresholdLower);
ViStatus _VI_FUNC rsrtx_StartPowerDynamicOnResistanceMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerDynamicOnResistanceMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerDynamicOnResistanceMeasurementResult
             (ViSession instrumentHandle, ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerEfficiencyMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerEfficiencyMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerEfficiencyMeasurementResult
             (ViSession instrumentHandle, ViInt32 type, ViInt32 statistics,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerSwitchinglossMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_SetPowerSwitschinglossMeasurementGateToWaveform
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerSwitchinglossMeasurementAddReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerSwitchinglossMeasurementEnergyResult
             (ViSession instrumentHandle, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_QueryPowerSwitchinglossMeasurementPowerResult
             (ViSession instrumentHandle, ViInt32 type,
              ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerOnOffMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerOnOffMeasurementAddReport (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerOnOffMeasurementResult (ViSession instrumentHandle,
                                                          ViInt32 resultNumber,
                                                          ViReal64* measurementResult);
ViStatus _VI_FUNC rsrtx_StartPowerSafeOperatingAreaMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_RestartPowerSafeOperatingAreaMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaAddToReport
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaScaling (ViSession instrumentHandle,
                                                       ViInt32 scale,
                                                       ViInt32 maskScale,
                                                       ViInt32 displayScale);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLinPointManagement
             (ViSession instrumentHandle, ViInt32 operation, ViInt32 pointNumber);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLinPointValue
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64 pointValue);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaLinCount
             (ViSession instrumentHandle, ViInt32* count);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLogPointManagement
             (ViSession instrumentHandle, ViInt32 operation, ViInt32 pointNumber);
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLogPointValue
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64 pointValue);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaLogCount
             (ViSession instrumentHandle, ViInt32* count);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAcquisitionPointResults
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaResultAcquisitionViolation
             (ViSession instrumentHandle, ViInt32 pointNumber, ViReal64* current,
              ViReal64* voltage);
ViStatus _VI_FUNC rsrtx_ReadPowerSafeOperatingAreaAcquisitionData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViInt32 waveformSize, ViInt32 maximumTime,
              ViReal64 _VI_FAR waveformArray[], ViInt32* actualPoints,
              ViReal64* initialX, ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViInt32 waveformSize, ViReal64 _VI_FAR waveformArray[],
              ViInt32* actualPoints, ViReal64* initialX, ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionDataHeader
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* xStart, ViReal64* xStop, ViInt32* recordLength,
              ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionConversionData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* xStart, ViReal64* xIncrement, ViReal64* yStart,
              ViReal64* yIncrement, ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingTotalPointResults
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* result);
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaResultTotalViolation
             (ViSession instrumentHandle, ViInt32 pointNumber, ViReal64* current,
              ViReal64* voltage);
ViStatus _VI_FUNC rsrtx_ReadPowerSafeOperatingAreaTotalData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViInt32 waveformSize, ViInt32 maximumTime,
              ViReal64 _VI_FAR waveformArray[], ViInt32* actualPoints,
              ViReal64* initialX, ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViInt32 waveformSize, ViReal64 _VI_FAR waveformArray[],
              ViInt32* actualPoints, ViReal64* initialX, ViReal64* xIncrement);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalDataHeader
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* xStart, ViReal64* xStop, ViInt32* recordLength,
              ViInt32* valuesPerSample);
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalConversionData
             (ViSession instrumentHandle, ViInt32 pointNumber, ViInt32 valueType,
              ViReal64* xStart, ViReal64* xIncrement, ViReal64* yStart,
              ViReal64* yIncrement, ViInt32* yResolution);
ViStatus _VI_FUNC rsrtx_StartPowerTransientResponseMeasurement
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_TransientResponseSettings (ViSession instrumentHandle,
                                                   ViReal64 signalHigh,
                                                   ViReal64 signalLow,
                                                   ViReal64 startTime,
                                                   ViReal64 stopTime);
ViStatus _VI_FUNC rsrtx_TransientResponseAddToReport (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryPowerTransientResponseResult
             (ViSession instrumentHandle, ViInt32 type, ViReal64* result);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisState (ViSession instrumentHandle,
                                                        ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMode (ViSession instrumentHandle,
                                                       ViInt32 mode);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisSource (ViSession instrumentHandle,
                                                         ViInt32 source);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisFrequency
             (ViSession instrumentHandle, ViReal64 start, ViReal64 stop);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisFrequencyCenterSpan
             (ViSession instrumentHandle, ViReal64 center, ViReal64 span);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumFrequencyFullSpan
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisWaveform
             (ViSession instrumentHandle, ViBoolean spectrum, ViBoolean minHold,
              ViBoolean maxHold, ViBoolean average);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisTimeDomain
             (ViSession instrumentHandle, ViReal64 position, ViReal64 range);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisDisplay (ViSession instrumentHandle,
                                                          ViInt32 colorScheme,
                                                          ViBoolean magnitudeMode,
                                                          ViReal64 minimum,
                                                          ViReal64 maximum);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerState
             (ViSession instrumentHandle, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerSource
             (ViSession instrumentHandle, ViInt32 source);
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerReference
             (ViSession instrumentHandle, ViInt32 reference);
ViStatus _VI_FUNC rsrtx_SpectrumMarkerSetupCenterScreen
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_SpectrumMarkerSetupRangeToPeak (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerResults
             (ViSession instrumentHandle, ViReal64* frequency, ViReal64* level);
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerFrequency
             (ViSession instrumentHandle, ViReal64* frequency);
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerLevel
             (ViSession instrumentHandle, ViReal64* markerLevel);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerResults (ViSession instrumentHandle,
                                                    ViInt32 result,
                                                    ViReal64* frequency,
                                                    ViReal64* level);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerFrequency (ViSession instrumentHandle,
                                                      ViInt32 marker,
                                                      ViReal64* frequency);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerFrequencyDelta
             (ViSession instrumentHandle, ViInt32 marker, ViReal64* deltaFrequency);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerLevel (ViSession instrumentHandle,
                                                  ViInt32 marker, ViReal64* level);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerLevelDelta (ViSession instrumentHandle,
                                                       ViInt32 marker,
                                                       ViReal64* deltaLevel);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerDeltaResults (ViSession instrumentHandle,
                                                         ViInt32 result,
                                                         ViReal64* frequency,
                                                         ViReal64* level);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerAllResults (ViSession instrumentHandle,
                                                       ViInt32 result,
                                                       ViInt32 arraySize,
                                                       ViReal64 _VI_FAR frequency[],
                                                       ViReal64 _VI_FAR level[],
                                                       ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerAllDeltaResults
             (ViSession instrumentHandle, ViInt32 result, ViInt32 arraySize,
              ViReal64 _VI_FAR frequency[], ViReal64 _VI_FAR level[],
              ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotEnable (ViSession instrumentHandle,
                                                 ViBoolean enable);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotSweepFrequencies
             (ViSession instrumentHandle, ViReal64 startFrequency,
              ViReal64 stopFrequency);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotInputChannel (ViSession instrumentHandle,
                                                       ViInt32 bodePlotInputChannel);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotOutputChannel (ViSession instrumentHandle,
                                                        ViInt32 bodePlotOutputChannel);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotGainSettings (ViSession instrumentHandle,
                                                       ViBoolean gainEnable,
                                                       ViReal64 gainPosition,
                                                       ViReal64 gainScale);
ViStatus _VI_FUNC rsrtx_QueryBodePlotPhaseSettings (ViSession instrumentHandle,
                                                    ViBoolean* phaseEnable,
                                                    ViReal64* phasePosition,
                                                    ViReal64* phaseScale);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeMode (ViSession instrumentHandle,
                                                        ViInt32 amplitudeMode);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeSettings
             (ViSession instrumentHandle, ViBoolean amplitudeEnable,
              ViReal64 amplitudePosition, ViReal64 amplitudeScale);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMeasurementState
             (ViSession instrumentHandle, ViInt32 measurementState);
ViStatus _VI_FUNC rsrtx_StartBodePlotMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_StopBodePlotMeasurement (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMeasurementDelay
             (ViSession instrumentHandle, ViReal64 measurementDelay);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotRepeatedMeasurementEnable
             (ViSession instrumentHandle, ViBoolean repeatedMeasurementEnable);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotPointsSettings (ViSession instrumentHandle,
                                                         ViInt32 pointsPerDecade,
                                                         ViBoolean pointsDisplayEnable);
ViStatus _VI_FUNC rsrtx_ExportBodePlotTimestampTable (ViSession instrumentHandle,
                                                      ViString fileName);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeProfilePoints
             (ViSession instrumentHandle, ViReal64 profilePointsNumber);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeProfilePointSettings
             (ViSession instrumentHandle, ViInt32 profilePoint, ViReal64 amplitude,
              ViReal64 frequency);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMarkerFrequency (ViSession instrumentHandle,
                                                          ViInt32 bodeMarker,
                                                          ViReal64 markerFrequency);
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMarkerIndex (ViSession instrumentHandle,
                                                      ViInt32 bodeMarker,
													  ViReal64 markerIndex);
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerGain (ViSession instrumentHandle,
                                                 ViInt32 bodeMarker,
                                                 ViReal64* markerGain);
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerPhase (ViSession instrumentHandle,
                                                  ViInt32 bodeMarker, 
												  ViReal64* markerPhase);
ViStatus _VI_FUNC rsrtx_ResetBodePlotMarkers (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerDifferences (ViSession instrumentHandle,
                                                        ViReal64* frequencyDifference,
                                                        ViReal64* gainDifference,
                                                        ViReal64* phaseDifference);
ViStatus _VI_FUNC rsrtx_ResetBodePlotResults (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryBodePlotFrequencyData (ViSession instrumentHandle,
                                                    ViInt32 arraySize,
                                                    ViReal64 _VI_FAR frequencyData[],
                                                    ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_QueryBodePlotGainData (ViSession instrumentHandle,
                                               ViInt32 arraySize,
                                               ViReal64 _VI_FAR gainData[],
                                               ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_QueryBodePlotPhaseData (ViSession instrumentHandle,
                                                ViInt32 arraySize,
                                                ViReal64 _VI_FAR phaseData[],
                                                ViInt32* returnedValues);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFunctionType
             (ViSession instrumentHandle, ViInt32 functionType);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFrequency
             (ViSession instrumentHandle, ViReal64 frequency);
ViStatus _VI_FUNC rsrtx_WaveformGeneratorPulse (ViSession instrumentHandle,
                                                ViReal64 dutyCycle,
                                                ViReal64 edgeTime);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorRampPolarity
             (ViSession instrumentHandle, ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorExponentialPolarity
             (ViSession instrumentHandle, ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputState
             (ViSession instrumentHandle, ViBoolean enabled);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputAmplitude
             (ViSession instrumentHandle, ViReal64 amplitude, ViReal64 offset);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputUserLoad
             (ViSession instrumentHandle, ViInt32 load);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputDestination
             (ViSession instrumentHandle, ViInt32 destination);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorNoiseLevelPercent
             (ViSession instrumentHandle, ViReal64 percent);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorNoiseAbsoluteLevel
             (ViSession instrumentHandle, ViReal64 level);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorBurstSettings
             (ViSession instrumentHandle, ViBoolean burstEnable,
              ViInt32 burstCycles, ViReal64 burstIdleTime,
              ViReal64 burstPhaseOffset);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationState
             (ViSession instrumentHandle, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationType
             (ViSession instrumentHandle, ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationFunctionType
             (ViSession instrumentHandle, ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationRampPolarity
             (ViSession instrumentHandle, ViInt32 polarity);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorAMModulation
             (ViSession instrumentHandle, ViReal64 frequency, ViReal64 depth);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFMModulation
             (ViSession instrumentHandle, ViReal64 frequency, ViReal64 deviation);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorASKModulation
             (ViSession instrumentHandle, ViReal64 frequency, ViReal64 depth);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFSKModulation
             (ViSession instrumentHandle, ViReal64 frequency, ViReal64 rate);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorSweep (ViSession instrumentHandle,
                                                         ViBoolean state,
                                                         ViInt32 type,
                                                         ViReal64 startFrequency,
                                                         ViReal64 stopFrequency,
                                                         ViReal64 time);
ViStatus _VI_FUNC rsrtx_WaveformGeneratorArbitraryOpenFile
             (ViSession instrumentHandle, ViString file);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitrarySource
             (ViSession instrumentHandle, ViInt32 source);
ViStatus _VI_FUNC rsrtx_WaveformGeneratorArbitraryUpdate
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitraryRange
             (ViSession instrumentHandle, ViReal64 rangeStart, ViReal64 rangeEnd);
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitraryDisplayEnable
             (ViSession instrumentHandle, ViBoolean displayWaveformEnable);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorState (ViSession instrumentHandle,
                                                        ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorFunctionType
             (ViSession instrumentHandle, ViInt32 functionType);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorFrequency
             (ViSession instrumentHandle, ViReal64 frequency);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPeriod (ViSession instrumentHandle,
                                                         ViReal64 period);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorSquareWaveform
             (ViSession instrumentHandle, ViInt32 polarity, ViReal64 dutyCycle);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorSampleTime
             (ViSession instrumentHandle, ViReal64 sampleTime);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorCounter (ViSession instrumentHandle,
                                                          ViInt32 direction,
                                                          ViReal64 frequency);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorBurst (ViSession instrumentHandle,
                                                        ViBoolean state,
                                                        ViInt32 numberOfCycles);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorIdleTime
             (ViSession instrumentHandle, ViReal64 idleTime);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorTriggerMode
             (ViSession instrumentHandle, ViInt32 mode);
ViStatus _VI_FUNC rsrtx_PatternGeneratorTriggerRunSingle
             (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorExternalTriggerSlope
             (ViSession instrumentHandle, ViInt32 externalTriggerSlope);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBPatternLength
             (ViSession instrumentHandle, ViInt32 patternLength);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBIndex
             (ViSession instrumentHandle, ViInt32 index);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataSet
             (ViSession instrumentHandle, ViInt32 arraySize,
              ViInt32 _VI_FAR data[]);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppend
             (ViSession instrumentHandle, ViInt32 arraySize,
              ViInt32 _VI_FAR data[]);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppendAND
             (ViSession instrumentHandle, ViInt32 arraySize,
              ViInt32 _VI_FAR data[]);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppendOR
             (ViSession instrumentHandle, ViInt32 arraySize,
              ViInt32 _VI_FAR data[]);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorManualState
             (ViSession instrumentHandle, ViInt32 outputPin, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMMotorSettings
             (ViSession instrumentHandle, ViBoolean motorEnable,
              ViInt32 motorDirection, ViReal64 dutyCycle);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMLEDIntensity
             (ViSession instrumentHandle, ViReal64 LEDIntensity);
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMLEDIntensityColor
             (ViSession instrumentHandle, ViReal64 blueIntensity,
              ViReal64 greenIntensity, ViReal64 redIntensity);
ViStatus _VI_FUNC rsrtx_ConfigureLogicState (ViSession instrumentHandle,
                                             ViInt32 logic, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureLogicType (ViSession instrumentHandle,
                                            ViInt32 logic, ViInt32 type);
ViStatus _VI_FUNC rsrtx_ConfigureLogicThreshold (ViSession instrumentHandle,
                                                 ViInt32 logic, ViInt32 threshold,
                                                 ViReal64 userLevel);
ViStatus _VI_FUNC rsrtx_ConfigureLogicHysteresis (ViSession instrumentHandle,
                                                  ViInt32 logic,
                                                  ViInt32 hysteresis);
ViStatus _VI_FUNC rsrtx_ConfigureLogicArithmetics (ViSession instrumentHandle,
                                                   ViInt32 logic,
                                                   ViInt32 arithmetics);
ViStatus _VI_FUNC rsrtx_QueryLogicProbeConnected (ViSession instrumentHandle,
                                                  ViInt32 logic,
                                                  ViBoolean* probeConnected);
ViStatus _VI_FUNC rsrtx_QueryLogicCurrent (ViSession instrumentHandle,
                                           ViInt32 logic, ViInt32* maximum,
                                           ViInt32* minimum);
ViStatus _VI_FUNC rsrtx_ConfigureLogicPointSelection (ViSession instrumentHandle,
                                                      ViInt32 logic,
                                                      ViInt32 logicPointSelection);
ViStatus _VI_FUNC rsrtx_QueryLogicWaveformDataPoints (ViSession instrumentHandle,
                                                      ViInt32 logic,
                                                      ViInt32* waveformDataPoints);
ViStatus _VI_FUNC rsrtx_ConfigureDVMState (ViSession instrumentHandle,
                                           ViInt32 measurementPlace,
                                           ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureDVM (ViSession instrumentHandle,
                                      ViInt32 measurementPlace, ViInt32 source,
                                      ViInt32 type, ViInt32 position);
ViStatus _VI_FUNC rsrtx_QueryDVMResult (ViSession instrumentHandle,
                                        ViInt32 measurementPlace, ViReal64* result);
ViStatus _VI_FUNC rsrtx_ConfigureCounterState (ViSession instrumentHandle,
                                               ViInt32 counter, ViBoolean state);
ViStatus _VI_FUNC rsrtx_ConfigureCounterSource (ViSession instrumentHandle,
                                                ViInt32 counterSource);
ViStatus _VI_FUNC rsrtx_QueryCounterFrequency (ViSession instrumentHandle,
                                               ViInt32 counter,
                                               ViReal64* frequency);
ViStatus _VI_FUNC rsrtx_QueryCounterPeriod (ViSession instrumentHandle,
                                            ViInt32 counter, ViReal64* period);
ViStatus _VI_FUNC rsrtx_ConfigureDeviceMode (ViSession instrumentHandle,
                                             ViInt32 deviceMode);
ViStatus _VI_FUNC rsrtx_ConfigureInterface (ViSession instrumentHandle,
                                            ViInt32 remoteControlInterface);
ViStatus _VI_FUNC rsrtx_ConfigureUSBClass (ViSession instrumentHandle,
                                           ViInt32 USBClass);
ViStatus _VI_FUNC rsrtx_ConfigureEthernetDHCP (ViSession instrumentHandle,
                                               ViBoolean DHCP);
ViStatus _VI_FUNC rsrtx_ConfigureEthernetHTTPPort (ViSession instrumentHandle,
                                                   ViInt32 HTTPPortNumber);
ViStatus _VI_FUNC rsrtx_ConfigureEthernetIPPort (ViSession instrumentHandle,
                                                 ViInt32 IPPort);
ViStatus _VI_FUNC rsrtx_ConfigureEthernetVXI11Port (ViSession instrumentHandle,
                                                    ViInt32 VXI11Port);
ViStatus _VI_FUNC rsrtx_ConfigureEthernetTransfer (ViSession instrumentHandle,
                                                   ViInt32 transfer);
ViStatus _VI_FUNC rsrtx_QueryEthernetMACAddress (ViSession instrumentHandle,
                                                 ViInt32 bufferSize,
                                                 ViChar _VI_FAR ethernetMACAddress[]);
ViStatus _VI_FUNC rsrtx_PresetEducation (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryDeviceFootprint (ViSession instrumentHandle,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR deviceFootprint[]);
ViStatus _VI_FUNC rsrtx_reset (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_ConfigureErrorChecking (ViSession instrumentHandle,
                                                ViBoolean optionChecking,
                                                ViBoolean rangeChecking,
                                                ViBoolean statusChecking);
ViStatus _VI_FUNC rsrtx_self_test (ViSession instrumentHandle,
                                   ViInt16* selfTestResult,
                                   ViChar _VI_FAR selfTestMessage[]);
ViStatus _VI_FUNC rsrtx_revision_query (ViSession instrumentHandle,
                                        ViChar _VI_FAR instrumentDriverRevision[],
                                        ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC rsrtx_error_query (ViSession instrumentHandle, ViInt32* errorCode,
                                     ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rsrtx_ErrorList (ViSession instrumentHandle, ViInt32 bufferSize,
                                   ViChar _VI_FAR errors[]);
ViStatus _VI_FUNC rsrtx_error_message (ViSession instrumentHandle,
                                       ViStatus errorCode,
                                       ViChar _VI_FAR errorMessage[]);
ViStatus _VI_FUNC rsrtx_ConfigureInstrumentName (ViSession instrumentHandle,
                                                 ViString name);
ViStatus _VI_FUNC rsrtx_ResetStatusRegisters (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_SetStatusRegister (ViSession instrumentHandle,
                                           ViInt32 registerType,
                                           ViInt32 statusRegister,
                                           ViInt32 registerPart,
                                           ViInt32 registerValue);
ViStatus _VI_FUNC rsrtx_GetStatusRegister (ViSession instrumentHandle,
                                           ViInt32 registerType,
                                           ViInt32 statusRegister,
                                           ViInt32 registerPart,
                                           ViInt32* registerValue);
ViStatus _VI_FUNC rsrtx_SetOPCTimeout (ViSession instrumentHandle,
                                       ViUInt32 OPCTimeout);
ViStatus _VI_FUNC rsrtx_GetOPCTimeout (ViSession instrumentHandle,
                                       ViInt32* timeout);
ViStatus _VI_FUNC rsrtx_SetVISATimeout (ViSession instrumentHandle,
                                        ViUInt32 VISATimeout);
ViStatus _VI_FUNC rsrtx_GetVISATimeout (ViSession instrumentHandle,
                                        ViUInt32* VISATimeout);
ViStatus _VI_FUNC rsrtx_SelfAlingment (ViSession instrumentHandle,
                                       ViInt32 maximumTime);
ViStatus _VI_FUNC rsrtx_ClearStatus (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_IDQueryResponse (ViSession instrumentHandle,
                                         ViChar _VI_FAR IDQueryResponse[]);
ViStatus _VI_FUNC rsrtx_ProcessAllPreviousCommands (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_QueryOPC (ViSession instrumentHandle, ViInt32* OPC);
ViStatus _VI_FUNC rsrtx_ConfigureAutoSystemErrQuery (ViSession instrumentHandle,
                                                     ViBoolean autoSystErrQuery);
ViStatus _VI_FUNC rsrtx_ConfigureMultiThreadLocking (ViSession instrumentHandle,
                                                     ViBoolean multiThreadLocking);
ViStatus _VI_FUNC rsrtx_GetError (ViSession instrumentHandle, ViStatus* code,
                                  ViInt32 bufferSize, ViChar _VI_FAR description[]);
ViStatus _VI_FUNC rsrtx_ClearError (ViSession instrumentHandle);
ViStatus _VI_FUNC rsrtx_WriteInstrData (ViSession instrumentHandle,
                                        ViString writeBuffer);
ViStatus _VI_FUNC rsrtx_ReadInstrData (ViSession instrumentHandle,
                                       ViInt32 numberOfBytesToRead,
                                       ViChar _VI_FAR readBuffer[],
                                       ViUInt32* numBytesRead);
ViStatus _VI_FUNC rsrtx_QueryViBoolean (ViSession instrumentHandle,
                                        ViString command, ViBoolean* value);
ViStatus _VI_FUNC rsrtx_QueryViInt32 (ViSession instrumentHandle, ViString command,
                                      ViInt32* value);
ViStatus _VI_FUNC rsrtx_QueryViReal64 (ViSession instrumentHandle, ViString command,
                                       ViReal64* value);
ViStatus _VI_FUNC rsrtx_QueryViString (ViSession instrumentHandle, ViString command,
                                       ViInt32 bufferSize, ViChar _VI_FAR value[]);
ViStatus _VI_FUNC rsrtx_WriteCommandWithOPCSync (ViSession instrumentHandle,
                                                 ViString writeBuffer,
                                                 ViUInt32 timeout);
ViStatus _VI_FUNC rsrtx_QueryWithOPCSync (ViSession instrumentHandle,
                                          ViString writeBuffer, ViUInt32 timeout,
                                          ViInt32 bufferSize,
                                          ViChar _VI_FAR readBuffer[],
                                          ViUInt32* numBytesRead);
ViStatus _VI_FUNC rsrtx_FileManagerOperations (ViSession instrumentHandle,
                                               ViInt32 operation, ViString source,
                                               ViString destination);
ViStatus _VI_FUNC rsrtx_FileCount (ViSession instrumentHandle, ViString directory,
                                   ViInt32* numberOfFilesAndFolders);
ViStatus _VI_FUNC rsrtx_FileDirectoryContent (ViSession instrumentHandle,
                                              ViString directory,
                                              ViInt32 bufferSize,
                                              ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsrtx_FileSubdirectoriesCount (ViSession instrumentHandle,
                                                 ViString directory,
                                                 ViInt32* numberOfSubdirectories);
ViStatus _VI_FUNC rsrtx_FileSubdirectories (ViSession instrumentHandle,
                                            ViString directory, ViInt32 bufferSize,
                                            ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsrtx_FileDrives (ViSession instrumentHandle, ViInt32 bufferSize,
                                    ViChar _VI_FAR output[]);
ViStatus _VI_FUNC rsrtx_ReadToFileFromInstrument (ViSession instrumentHandle,
                                                  ViString source,
                                                  ViString destination);
ViStatus _VI_FUNC rsrtx_WriteFromFileToInstrument (ViSession instrumentHandle,
                                                   ViString source,
                                                   ViString destination);
ViStatus _VI_FUNC rsrtx_DataSetFileOperations (ViSession instrumentHandle,
                                               ViInt32 operation,
                                               ViInt32 stateNumber, ViString path);
ViStatus _VI_FUNC rsrtx_SaveInstrumentSettingsToPC (ViSession instrumentHandle,
                                                    ViString path);
ViStatus _VI_FUNC rsrtx_RecallInstrumentSettingsFromPC (ViSession instrumentHandle,
                                                        ViString path);
ViStatus _VI_FUNC rsrtx_close (ViSession instrumentHandle);

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __RSRTX_HEADER */

