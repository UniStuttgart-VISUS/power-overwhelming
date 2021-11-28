/*****************************************************************************
 *  Rohde&Schwarz RTM Instrument Driver
 *  LabWindows/CVI Instrument Driver
 *  Original Release: 2010-12-17
 *  By: Jiri Kominek, Martin Krcmar
 *
 *  Modification History:
 *
 *       See ChangeLog
 *
 *****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rsrtx.h"
#if defined (_CVI_)
	#include <utility.h>
#endif

/*****************************************************************************
 *- Value Definition and Range Tables ---------------------------------------*
 *****************************************************************************/

 static ViString signalSourceArr[] = {"NONE","CH1","CH2","CH3","CH4","MA1","MA2","MA3","MA4","MA5",
										"R1","R2","R3","R4","TRIG","D1","D2","D3","D4",
										"D5","D6","D7","D8","D9","D10","D11","D12","D13",
										"D14","D15","D70","D158","D0","SPEC", "MINH",
										"MAXH", "AVER", "QMA", NULL};
 static ViString languageArr[] = {"ENGL","GERM","FREN","SPAN","RUSS","SCH","TCH","JAP","KOR",NULL};
 static ViString statisticsArr[] = {"ACT","AVG","STDD","NPE","PPE","WFMC",NULL};
 static ViString qualityTypeArr[] = {"RMS","FREQ","CRES",NULL};
 static ViString qualityTypePowerArr[] = {"REAL","REAC","APP","PFAC","PHAS",NULL};
 static ViString harmonicsTypeArr[] = {"VCO","FREQ","LEV","MIN","MAX","MEAN",
															"LEV:LIM","WFMC",NULL};
 static ViString rippleTypeArr[] = {"FREQ","PEAK","STDD","UPE","LPE","MEAN", "PER",
																"PDCY","NDCY",NULL};
 static ViString spectrumTypeArr[] = {"FREQ","LEV","MIN","MAX","MEAN","WFMC",NULL};
 static ViString slewRateTypeArr[] = {"LPE","UPE",NULL};
 static ViString modulationTypeArr[] = {"LPE","UPE","MEAN","RMS","STDD",NULL};
 static ViString efficiencyTypeArr[] = {"EFF","INP:REAL","OUTP:REAL",NULL};
/*****************************************************************************
 *- User-Callable Functions (Exportable Functions) --------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: rsrtx_init
 * Purpose:  VXIplug&play required function. Calls the
 *           rsrtx_InitWithOptions function.
 *****************************************************************************/
ViStatus _VI_FUNC rsrtx_init (ViRsrc resourceName, ViBoolean IDQuery,
                                 ViBoolean resetDevice, ViSession *newInstrSession)
{
	ViStatus error = VI_SUCCESS;

	if (newInstrSession == NULL)
	{
		(void)RsCore_SetErrorInfo(0, VI_FALSE, RS_ERROR_INVALID_PARAMETER,
		                          VI_ERROR_PARAMETER4, "Null address for Instrument Handle");

		checkErr(RS_ERROR_INVALID_PARAMETER);
	}

	checkErr(rsrtx_InitWithOptions (resourceName, IDQuery, resetDevice, "", newInstrSession));

Error:
	return error;
}

/*****************************************************************************
 * Function: rsrtx_InitWithOptions
 * Purpose:  This function creates a new RS session and calls the
 *           RsInit function.
 *****************************************************************************/
ViStatus _VI_FUNC rsrtx_InitWithOptions(
    ViRsrc          resourceName,
    ViBoolean       IDQuery,
    ViBoolean       resetDevice,
    ViString        optionString,
    ViSession      *newInstrSession
)
{
	ViStatus error = VI_SUCCESS;
	RsCoreAttributePtr* attrList = NULL;
	ViSession instrSession = 0;
	RsCoreSessionPtr sessionProperties = NULL;

	if (newInstrSession == NULL)
	{
		(void)RsCore_SetErrorInfo(0, VI_FALSE, RS_ERROR_INVALID_PARAMETER, VI_ERROR_PARAMETER5,
		                          "Null address for Instrument Handle");
		checkErr(RS_ERROR_INVALID_PARAMETER);
	}

	attrList = (RsCoreAttributePtr *)rsrtx_RsCoreAttributeList;

	*newInstrSession = 0;

	checkErr(RsCore_NewSpecificDriver(
        resourceName, // VISA Resource Name
        "rsrtx", // driver prefix
        optionString, // Init Options string, is applied to the session settings
        attrList, // List of all attributes from the rsxxx_AttrPropertiesList
        VI_FALSE, //idnModelFullName Model has the full *IDN? query name e.g. true: "CMW100A", VI_FALSE: "CMW" Used in CheckInstrument()
        0, // WriteDelay
        0, // ReadDelay
        100000, // IO Segment Size
        RS_VAL_OPCWAIT_STBPOLLING, // OPC Wait Mode
        RSRTX_OPC_TIMEOUT, // OPC timeout
        15000, // VISA Timeout
        600000, // Self-test timeout
        RS_VAL_BIN_FLOAT_FORMAT_SINGLE_4BYTES, // BinaryFloatNumbersFormat
        RS_VAL_BIN_INTEGER_FORMAT_INT32_4BYTES, // binaryIntegerNumbersFormat
        &instrSession));

	// Minimal allowed rscore version is 3.6.3
	checkErr(RsCore_CheckMinimalEngineVersion(instrSession, 3, 6, 3));

	checkErr(RsCore_GetRsSession(instrSession, &sessionProperties));

	// No SCPI command has been sent yet.
	// Call viClear before sending any SCPI command
	checkErr(RsCore_ViClear(instrSession));

	/* --- Here perform settings that are default for this driver,
	but can be overwritten by the optionsString settings */

	sessionProperties->autoSystErrQuery = VI_FALSE;
	sessionProperties->addTermCharToWriteBinBlock = VI_TRUE;
	sessionProperties->assureWriteWithLF = VI_TRUE;

	// Parse option string and optionally sets the initial state of the following session attributes
	checkErr(RsCore_ApplyOptionString(instrSession, optionString));
	checkErr(RsCore_BuildRepCapTable(instrSession, rsrtx_RsCoreRepCapTable));

	// Query *IDN? string, parse it and set the following attributes:
	// -RS_ATTR_INSTRUMENT_MANUFACTURER
	// - RS_ATTR_INSTRUMENT_MODEL - based on the idnModelFullName true: "CMW100A", false : "CMW"
	// - RS_ATTR_INSTRUMENT_FIRMWARE_REVISION
	checkErr(RsCore_QueryAndParseIDNstring(instrSession, RSRTX_SIMULATION_ID_QUERY, NULL));

	// Query *OPT? string, parse the options, remove the duplicates, sort them and store the result string to RS_ATTR_OPTIONS_LIST
	checkErr(RsCore_QueryAndParseOPTstring(instrSession, RSRTX_SIMULATION_OPT_QUERY, RS_VAL_OPTIONS_PARSING_AUTO));

	// Default Instrument Setup + optional *RST
	if (resetDevice == VI_TRUE)
	{
		checkErr(rsrtx_reset(instrSession));
	}
	else
	{
		checkErr(rsrtx_DefaultInstrSetup(instrSession));
	}

	if (IDQuery == VI_TRUE)
	{
		checkErr(RsCore_FitsIDNpattern(instrSession, RSRTX_VALID_ID_RESPONSE_STRING, NULL));
	}

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	if (error < VI_SUCCESS)
	{
		if (error == RS_ERROR_INSTRUMENT_STATUS && sessionProperties != NULL && sessionProperties->autoSystErrQuery == VI_FALSE)
		{
			sessionProperties->autoSystErrQuery = VI_TRUE;
			(void)rsrtx_CheckStatus(instrSession);
			sessionProperties->autoSystErrQuery = VI_FALSE;
		}

		if (instrSession != 0)
			(void)RsCore_ViClose(instrSession);
	}
	else
	{
		*newInstrSession = instrSession;
	}

	return error;
}

/// HIFN Document your function here.
/// HIFN You may use multiple lines for documentation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/Selects the measurement.
/// HIPAR arraySize/Pass the number of elements in 'Results' parameter.
/// HIPAR results/All values from the statistics buffer.
ViStatus _VI_FUNC rsrtx_QueryAutomaticMeasurementAllStatisticalValues(
							ViSession instrSession,
							ViInt32   measurement,
							ViInt32   arraySize,
							ViReal64  results[])
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, RSRTX_VAL_MEASUREMENT_1, RSRTX_VAL_MEASUREMENT_8),
    		2, "Measurement");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:STAT:VAL:ALL?", measurement);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, arraySize, results, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures the measurement gate settings.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_ENABLE
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_MODE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     MEASurement<m>:GATE
/// HIFN     MEASurement<m>:GATE:MODE
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR gateEnable/Activates or deactivates the measurement gate.
/// HIPAR mode/Defines whether the gate is defined in absolute or relative values.
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateEnable(ViSession instrSession,
                                                       ViBoolean gateEnable,
                                                       ViInt32   mode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_ENABLE, gateEnable),
    		3, "Gate Enable");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_MODE, mode),
			4, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the absolute start time for the measurement gate in seconds.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_START
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     MEASurement<m>:GATE:ABSolute:STARt
/// HIFN     MEASurement<m>:GATE:ABSolute:STOP
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR startTime/Defines the absolute start time for the measurement gate in seconds.
/// HIPAR endTime/Defines the absolute end time for the measurement gate in seconds.
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateAbsoluteTime(ViSession instrSession,
                                                             ViReal64  startTime,
                                                             ViReal64  endTime)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_START, startTime),
    		2, "Start Time");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_ABSOLUTE_END, endTime),
			3, "End Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the relative start and end value for the measurement gate in
/// HIFN  %.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_START
/// HIFN     RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     MEASurement<m>:GATE:RELative:STARt
/// HIFN     MEASurement<m>:GATE:RELative:STOP
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR startValue/Defines the relative start value for the measurement gate in %.
/// HIPAR endValue/Defines the relative end value for the measurement gate in %.
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementGateRelativeValues(
							ViSession instrSession,
							ViReal64  startValue,
							ViReal64  endValue)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_START, startValue),
    		2, "Start Value");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MEASUREMENT_GATE_RELATIVE_END, endValue),
			3, "End Value");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the sample mode the oscilloscope is currently
/// HIFN  using.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR sampleMode/Returns the method of adding waveform points to the samples of the ADC
/// HIPAR sampleMode/in order to fill the record length.
ViStatus _VI_FUNC rsrtx_SampleMode(ViSession instrSession,
                                   ViInt32*  sampleMode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SAMPLE_MODE, sampleMode),
    		2, "SampleMode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function performs an autoset process: analyzes the enabled channel signals, and obtains appropriate horizontal, vertical, and trigger settings to display stable waveforms.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
ViStatus _VI_FUNC rsrtx_Autoset(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_AUTOSCALE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures how the oscilloscope acquires data and fills the waveform record.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR acquisitionType/Specify the manner in which you want the oscilloscope to acquire data and fill the waveform record.
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionType(ViSession instrSession,
                                                 ViInt32   channel,
                                                 ViInt32   acquisitionType)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_ACQUISITION_TYPE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_ACQUISITION_TYPE, acquisitionType),
    		4, "Acquisition Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Enables the automatic record length or sets the record length
/// HIFN  automaticaly.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR automatic/Enables or disables the automatic record length. The instrument sets a
/// HIPAR automatic/value that fits to the selected timebase.
/// HIPAR recordLength/Defines a record length value, the number of recorded waveform points
/// HIPAR recordLength/in a segment.
ViStatus _VI_FUNC rsrtx_ConfigureRecordLength(ViSession instrSession,
                                              ViBoolean automatic,
                                              ViInt32   recordLength)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_RECORD_LENGTH_AUTOMATIC, automatic),
			2, "Automatic");

    if (!automatic)
	{
		viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_RECORD_LENGTH, recordLength),
				3, "Record Length");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects a range of samples that will be returned.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR recordLength/Selects a range of samples that will be returned
ViStatus _VI_FUNC rsrtx_ConfigureHorizontalRecordLength(ViSession instrSession,
                                                        ViInt32   channel,
                                                        ViInt32   recordLength)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HORZ_RECORD_LENGTH,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HORZ_RECORD_LENGTH, recordLength),
    		3, "Record Length");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the horizontal record length.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR recordLength/Returns the horizontal record length.
ViStatus _VI_FUNC rsrtx_QueryHorizontalRecordLength(ViSession instrSession,
                                                    ViInt32   channel,
                                                    ViInt32*  recordLength)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_GET_HORZ_RECORD_LENGTH,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_GET_HORZ_RECORD_LENGTH, recordLength),
    		3, "Record Length");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the type of the aquisition mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR acquireMode/Sets the type of the aquisition mode.
ViStatus _VI_FUNC rsrtx_ConfigureAcquireMode(ViSession instrSession,
                                             ViInt32   acquireMode)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ACQUIRE_MODE, acquireMode),
			2, "Acquire Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables or disables the peak detect acquisition mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR peakDetect/Enables or disables the peak detect acquisition mode.
ViStatus _VI_FUNC rsrtx_ConfigurePeakDetect(ViSession instrSession,
                                            ViBoolean peakDetect)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_PEAK_DETECT, peakDetect),
			2, "Peak Detect");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables or disables the high resolution acquisition mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR highResolution/Enables or disables the high resolution acquisition mode.
ViStatus _VI_FUNC rsrtx_ConfigureHighResolution(ViSession instrSession,
                                                ViBoolean highResolution)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_HIGH_RESOLUTION, highResolution),
			2, "High Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines how the record length is set.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MEMORY_MODE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     ACQuire:MEMory[:MODE]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR memoryMode/Defines how the record length is set.
ViStatus _VI_FUNC rsrtx_ConfigureMemoryMode(ViSession instrSession,
                                            ViInt32   memoryMode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_MEMORY_MODE, memoryMode),
    		2, "Memory Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the automatic roll mode. The instrument switches to roll mode
/// HIFN  if the timebase is equal or slower than the roll mode limit defined
/// HIFN  with RSRTX_ATTR_ROLL_MODE_MINIMUM_TIME_BASE.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ROLL_MODE_AUTOMATIC
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ROLL:AUTomatic
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR rollModeAutomatic/Enables the automatic roll mode. The instrument switches to roll mode
/// HIPAR rollModeAutomatic/if the timebase is equal or slower than the roll mode limit defined
/// HIPAR rollModeAutomatic/with RSRTX_ATTR_ROLL_MODE_MINIMUM_TIME_BASE.
ViStatus _VI_FUNC rsrtx_ConfigureRollModeAutomatic(ViSession instrSession,
                                                   ViBoolean rollModeAutomatic)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_ROLL_MODE_AUTOMATIC, rollModeAutomatic),
    		2, "Roll Mode Automatic");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  The roll mode is enabled automatically if the time base exceeds the
/// HIFN  MinTimeBase, and if RSRTX_ATTR_ROLL_MODE_AUTOMATIC is set ON.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ROLL_MODE_MINIMUM_TIME_BASE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ROLL:MTIMe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR rollModeMinimumTimeBase/The roll mode is enabled automatically if the time base exceeds the
/// HIPAR rollModeMinimumTimeBase/MinTimeBase, and if RSRTX_ATTR_ROLL_MODE_AUTOMATIC is set ON.
ViStatus _VI_FUNC rsrtx_ConfigureRollModeMinimumTimeBase(ViSession instrSession,
                                                         ViReal64  rollModeMinimumTimeBase)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_ROLL_MODE_MINIMUM_TIME_BASE, rollModeMinimumTimeBase),
    		2, "Roll Mode Minimum Time Base");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the common attributes of the acquisition subsystem.  These attributes are the time per record and acquisition start time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR timePerRecord/Pass the time in seconds that corresponds to the record length.
/// HIPAR acquisitionStartTime_Offset/Specifies the length of time from the trigger event to the first point in the waveform record.  If the value is positive, the first point in the waveform record occurs after the trigger event.  If the
///           value is negative, the first point in the waveform record occurs before the trigger event.
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionRecord(ViSession instrSession,
                                                   ViReal64  timePerRecord,
                                                   ViReal64  acquisitionStartTime_Offset)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_HORZ_TIME_PER_RECORD, timePerRecord),
    		2, "Time Per Record");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_ACQUSITION_START_TIME, acquisitionStartTime_Offset),
    		3, "Acqusition Start Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the interpolation method the oscilloscope uses when it cannot sample a voltage for a point in the waveform record.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR interpolation/Pass the interpolation method you want the oscilloscope to
ViStatus _VI_FUNC rsrtx_ConfigureInterpolation(ViSession instrSession,
                                               ViInt32   interpolation)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_INTERPOLATION, interpolation),
    		2, "Interpolation");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the number of waveforms that the oscilloscope  acquires and averages.  After the oscilloscope acquires as many waveforms as you specify, it returns to the idle state.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR numberofAverages/Pass the number of waveforms you want the oscilloscope to acquire and to average. After the oscilloscope acquires as many waveforms as you specify, it returns to the idle state.
ViStatus _VI_FUNC rsrtx_ConfigureNumberOfAverages(ViSession instrSession,
                                                  ViInt32   numberofAverages)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_NUM_AVERAGES, numberofAverages),
    		2, "Number of Averages");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the current amount of acquired waveforms that contribute to
/// HIFN  the average. The value is independent of the number of available
/// HIFN  segments, there are more waveforms in the average available than
/// HIFN  segments in history. Minimum is 2; maximum depends on the instrument
/// HIFN  settings.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_NUM_AVERAGES_CURRENT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     ACQuire:AVERage:CURRent?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR numberofAverages/Returns the current amount of acquired waveforms that contribute to
/// HIPAR numberofAverages/the average. The value is independent of the number of available
/// HIPAR numberofAverages/segments, there are more waveforms in the average available than
/// HIPAR numberofAverages/segments in history. Minimum is 2; maximum depends on the instrument
/// HIPAR numberofAverages/settings.
ViStatus _VI_FUNC rsrtx_QueryNumberofAveragesCurrent(ViSession instrSession,
                                                     ViInt32*  numberofAverages)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_NUM_AVERAGES_CURRENT, numberofAverages),
    		2, "Number Of Averages");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Deletes the waveform and restarts the average calculation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_NumberofAveragesReset(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_NUM_AVERAGES_RESET, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Enables/disables maximum waveform rate.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR maximum/Enables/disables maximum waveform rate.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformRateMaximum(ViSession instrSession,
                                                     ViBoolean maximum)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_RATE_MAXIMUM, maximum),
			2, "Maximum");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the number of waveforms acquired.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR numberOfWaveforms/Sets the number of waveforms acquired
ViStatus _VI_FUNC rsrtx_ConfigureNumberOfWaveforms(ViSession instrSession,
                                                   ViInt32   numberOfWaveforms)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_NUMBER_OF_WAVEFORMS, numberOfWaveforms),
    		2, "Number Of Waveforms");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the reference point of the time scale in % of the display. The
/// HIFN  reference point defines which part of the waveform is shown. If the
/// HIFN  Trigger offset is zero, the trigger point matches the reference point.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR horizontalReference/Sets the reference point of the time scale in % of the display. The
/// HIPAR horizontalReference/reference point defines which part of the waveform is shown. If the
/// HIPAR horizontalReference/Trigger offset is zero, the trigger point matches the reference point.
ViStatus _VI_FUNC rsrtx_ConfigureHorizontalReference(ViSession instrSession,
                                                     ViReal64  horizontalReference)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_HORZ_REFERENCE, horizontalReference),
    		2, "Horizontal Reference");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the method to reduce the data stream of the ADC to a stream of
/// HIFN  waveform points with lower sample rate.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR acquisitionType/Selects the method to reduce the data stream of the ADC to a stream of
/// HIPAR acquisitionType/waveform points with lower sample rate.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformAcquisitionType(ViSession instrSession,
                                                         ViInt32   channel,
                                                         ViInt32   acquisitionType)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_WAVEFORM_ACQUISITION_TYPE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_WAVEFORM_ACQUISITION_TYPE, acquisitionType),
    		3, "Acquisition Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the common attributes of the oscilloscope's channel subsystem for a particular channel.  These attributes are the vertical range, vertical offset, coupling, probe attenuation,
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR verticalRange/Sets the voltage range across the 10 vertical divisions of the diagram.
/// HIPAR verticalOffset/Pass the location of the center of the range that you specify with for the Vertical Range parameter. Express the value with respect to ground.
/// HIPAR verticalCoupling/Specify how you want the oscilloscope to couple the input signal for the channel.
/// HIPAR channelEnabled/Switches the channel signal on or off.
ViStatus _VI_FUNC rsrtx_ConfigureChannel(ViSession instrSession,
                                         ViInt32   channel,
                                         ViBoolean channelEnabled,
                                         ViReal64  verticalRange,
                                         ViReal64  verticalOffset,
                                         ViInt32   verticalCoupling,
                                         ViInt32   channelPolarity,
                                         ViReal64  channelSkew)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_ENABLED,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_CHANNEL_ENABLED, channelEnabled),
    		3, "Channel Enabled");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_VERTICAL_RANGE, verticalRange),
    		4, "Vertical Range");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_CHANNEL_OFFSET, verticalOffset),
    		5, "Vertical Offset");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_VERTICAL_COUPLING, verticalCoupling),
    		6, "Vertical Coupling");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_CHANNEL_POLARITY, channelPolarity),
			7, "Channel Polarity");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_CHANNEL_SKEW, channelSkew),
			8, "Channel Skew");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the zero offset. Differences in DUT and oscilloscope ground
/// HIFN  levels may cause larger zero errors affecting the waveform. If the DUT
/// HIFN  is ground-referenced, the Zero Offset corrects the zero error and sets
/// HIFN  the probe to the zero level. You can assess the zero error by measuring
/// HIFN  the mean value of a signal that should return zero.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_CHANNEL_ZERO_OFFSET
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<m>:ZOFFset[:VALue]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR zeroOffset/Sets the zero offset. Differences in DUT and oscilloscope ground
/// HIPAR zeroOffset/levels may cause larger zero errors affecting the waveform. If the DUT
/// HIPAR zeroOffset/is ground-referenced, the Zero Offset corrects the zero error and sets
/// HIPAR zeroOffset/the probe to the zero level. You can assess the zero error by measuring
/// HIPAR zeroOffset/the mean value of a signal that should return zero.
ViStatus _VI_FUNC rsrtx_ConfigureChannelZeroOffset(ViSession instrSession,
                                                   ViInt32   channel,
                                                   ViReal64  zeroOffset)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_ZERO_OFFSET,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_CHANNEL_ZERO_OFFSET, zeroOffset),
    		3, "Zero Offset");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function configures the bandwidth limit for the indicated channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR bandwidth/Selects the bandwidth limit for the indicated channel.
ViStatus _VI_FUNC rsrtx_ConfigureChannelBandwidth(ViSession instrSession,
                                                  ViInt32   channel,
                                                  ViInt32   bandwidth)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_BANDWIDTH_LIMIT,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_CHANNEL_BANDWIDTH_LIMIT, bandwidth),
    		3, "Bandwidth");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the vertical range per division.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR scale/Sets the vertical range per division.
ViStatus _VI_FUNC rsrtx_ConfigureChannelVerticalScale(ViSession instrSession,
                                                      ViInt32   channel,
                                                      ViReal64  scale)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_VERTICAL_SCALE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_VERTICAL_SCALE, scale),
    		3, "Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Retrieves the overload status of the specified channel from the status
/// HIFN  bit. When the overload problem is solved, the command resets the status
/// HIFN  bit.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR channelOverload/Retrieves the overload status of the specified channel from the status
/// HIPAR channelOverload/bit. When the overload problem is solved, the command resets the status
/// HIPAR channelOverload/bit.
ViStatus _VI_FUNC rsrtx_QueryChannelOverload(ViSession  instrSession,
                                             ViInt32    channel,
                                             ViBoolean* channelOverload)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_OVERLOAD,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_CHANNEL_OVERLOAD, channelOverload),
    		3, "Channel Overload");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Clears the channel overload status.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_ClearChannelOverload(ViSession instrSession,
                                             ViInt32   channel)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_OVERLOAD,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    checkErr(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_CHANNEL_OVERLOAD, VI_FALSE));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the vertical position of the waveform in divisions. While the
/// HIFN  offset sets a voltage, position is a graphical setting given in
/// HIFN  divisions.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_CHANNEL_POSITION
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<m>:POSition
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR verticalPosition/Sets the vertical position of the waveform in divisions. While the
/// HIPAR verticalPosition/offset sets a voltage, position is a graphical setting given in
/// HIPAR verticalPosition/divisions.
ViStatus _VI_FUNC rsrtx_ConfigureChannelPosition(ViSession instrSession,
                                                 ViInt32   channel,
                                                 ViReal64  verticalPosition)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_POSITION,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_CHANNEL_POSITION, verticalPosition),
    		3, "Vertical Position");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the color scale for the waveform color. Each scale comprises a
/// HIFN  set of colors, where each color represents a certain frequency of
/// HIFN  occurrence.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_CHANNEL_WAVEFORM_COLOR
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<m>:WCOLor
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformColor/Selects the color scale for the waveform color. Each scale comprises a
/// HIPAR waveformColor/set of colors, where each color represents a certain frequency of
/// HIPAR waveformColor/occurrence.
ViStatus _VI_FUNC rsrtx_ConfigureChannelWaveformColor(ViSession instrSession,
                                                      ViInt32   channel,
                                                      ViInt32   waveformColor)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CHANNEL_WAVEFORM_COLOR,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_CHANNEL_WAVEFORM_COLOR, waveformColor),
    		3, "Waveform Color");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Switches all analog channels off.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ChannelAllOff(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CHANNEL_ALL_OFF, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Switches all analog channels on.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ChannelAllOn(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CHANNEL_ALL_ON, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the size of the hysteresis to avoid the change of signal
/// HIFN  states due to noise. The setting applied to the channel group to which
/// HIFN  the indicated digital channel belongs.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR hysteresis/Defines the size of the hysteresis to avoid the change of signal
/// HIPAR hysteresis/states due to noise. The setting applied to the channel group to which
/// HIPAR hysteresis/the indicated digital channel belongs.
ViStatus _VI_FUNC rsrtx_ConfigureDigitalHysteresis(ViSession instrSession,
                                                   ViInt32   digitalChannel,
                                                   ViInt32   hysteresis)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_HYSTERESIS,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DIGITAL_HYSTERESIS, hysteresis),
    		3, "hysteresis");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the size of the indicated vertical channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR channelSize/Sets the size of the indicated vertical channel.
ViStatus _VI_FUNC rsrtx_ConfigureDigitalVerticalChannelSize(ViSession instrSession,
                                                            ViInt32   digitalChannel,
                                                            ViReal64  channelSize)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_VERTICAL_CHANNEL_SIZE,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DIGITAL_VERTICAL_CHANNEL_SIZE, channelSize),
    		3, "Channel Size");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the digital probe.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR state/Queries the digital probe state.
ViStatus _VI_FUNC rsrtx_QueryDigitalProbeState(ViSession  instrSession,
                                               ViInt32    digitalChannel,
                                               ViBoolean* state)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_PROBE_ENABLED,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_GetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_DIGITAL_PROBE_ENABLED, state),
    		3, "state");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects a range of samples that will be returned. Depending on the
/// HIFN  current settings, the memory can contain more data samples than the
/// HIFN  screen is able to display. In this case, you can decide which data will
/// HIFN  be saved: samples stored in the memory or only the displayed samples.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR pointSelection/Selects a range of samples that will be returned. Depending on the
/// HIPAR pointSelection/current settings, the memory can contain more data samples than the
/// HIPAR pointSelection/screen is able to display. In this case, you can decide which data will
/// HIPAR pointSelection/be saved: samples stored in the memory or only the displayed samples.
ViStatus _VI_FUNC rsrtx_ConfigureDigitalPointSelection(ViSession instrSession,
                                                       ViInt32   digitalChannel,
                                                       ViInt32   pointSelection)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_POINT_SELECTION,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DIGITAL_POINT_SELECTION, pointSelection),
    		3, "Point Selection");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the probe characteristics.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Name
/// HIPAR bufferSize/and Attenuation values.
/// HIPAR type/Queries the type of the probe.
/// HIPAR name/Queries the name of the probe.
/// HIPAR inputImpedance/Queries the termination of the probe.
/// HIPAR inputCapacitance/Queries the input capacitance of the probe.
/// HIPAR attenuation/Queries the attenuation of the probe.
/// HIPAR bandwidth/Queries the bandwidth of the probe.
ViStatus _VI_FUNC rsrtx_QueryProbeCharacteristics(ViSession instrSession,
                                                  ViInt32   channel,
                                                  ViInt32   bufferSize,
                                                  ViChar    type[],
                                                  ViChar    name[],
                                                  ViInt32*  inputImpedance,
                                                  ViReal64* inputCapacitance,
                                                  ViReal64* attenuation,
                                                  ViReal64* bandwidth)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, RSRTX_VAL_CHANNEL_1, RSRTX_VAL_CHANNEL_4),
    		2, "Channel");
    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_TYPE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROBE_TYPE,
    		bufferSize, type),
    		4, "Type");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROBE_NAME,
    		bufferSize, name),
    		5, "Name");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROBE_INPUT_IMPEDANCE, inputImpedance),
    		6, "Input Impedance");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_INPUT_CAPACITANCE, inputCapacitance),
    		7, "Input Capacitance");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_ATTENUATION, attenuation),
    		8, "Attenuation");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_BANDWIDTH, bandwidth),
    		9, "Bandwidth");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Demagnetizes the core if it has been magnetized by switching the power
/// HIFN  on and off, or by an excessive input. Always demagnetize the probe
/// HIFN  before measurement. The demagnetizing process takes about one second.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROBE_DEGAUSS
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PROBe<m>:SETup:DEGauss
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_ConfigureProbeDegauss(ViSession instrSession,
                                              ViInt32   channel)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_DEGAUSS,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROBE_DEGAUSS, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function sets the attenuation or gain of the probe if the probe was not detected by the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR attenuation/Sets the attenuation or gain of the probe if the probe was not detected by the instrument.
ViStatus _VI_FUNC rsrtx_ConfigureProbeAttenuationManual(ViSession instrSession,
                                                        ViInt32   channel,
                                                        ViReal64  attenuation)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, RSRTX_VAL_CHANNEL_1, RSRTX_VAL_CHANNEL_4),
			2, "Channel");
    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_ATTENUATION_MANUAL,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_ATTENUATION_MANUAL, attenuation),
    		3, "Attenuation");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the gain of an automatically detected probe.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROBE_GAIN
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PROBe<m>:SETup:GAIN[:AUTO]?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR probeGain/Returns the gain of an automatically detected probe.
ViStatus _VI_FUNC rsrtx_QueryProbeGain(ViSession instrSession,
                                       ViInt32   channel,
                                       ViReal64* probeGain)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_GAIN,
			"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
			2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_GAIN, probeGain),
    		3, "Probe Gain");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function turns an additional 5 kHz or 100 MHz low-pass filter in the trigger path
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR filterType/Selects the filter type.
/// HIPAR filterState/Activates or deactivates a low-pass filter in the trigger path.
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerFilter(ViSession instrSession,
                                                   ViInt32   filterType,
                                                   ViBoolean filterState)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, filterType, RSRTX_VAL_TRIGGER_FILTER_LOW, RSRTX_VAL_TRIGGER_FILTER_HF),
    		2, "Filter Type");

	switch (filterType)
    {
        case RSRTX_VAL_TRIGGER_FILTER_HIGH:
            viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_TRIGGER_FILTER_HIGH, filterState),
            		3, "Filter State");
            break;
        case RSRTX_VAL_TRIGGER_FILTER_HF:
            viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_TRIGGER_FILTER_HF_REJECT, filterState),
            		3, "Filter State");
            break;
        default:
            break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines wether and when a trigger out pulse is generated: never, on
/// HIFN  trigger event, or on mask violation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/Defines wether and when a trigger out pulse is generated: never, on
/// HIPAR mode/trigger event, or on mask violation.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerOutMode(ViSession instrSession,
                                                ViInt32   mode)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_OUT_MODE, mode),
    		2, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures selected trigger level.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Sets the polarity of the pulse.
/// HIPAR channel/Sets the trigger source for the selected trigger type.
/// HIPAR lowerLevel/Set the lower voltage threshold. The instrument triggers if the
/// HIPAR lowerLevel/amplitude crosses the first threshold twice in succession without
/// HIPAR lowerLevel/crossing the second one.
/// HIPAR upperLevel/Set the upper voltage threshold. The instrument triggers if the
/// HIPAR upperLevel/amplitude crosses the first threshold twice in succession without
/// HIPAR upperLevel/crossing the second one.
ViStatus _VI_FUNC rsrtx_ConfigureRuntTrigger(ViSession instrSession,
                                             ViInt32   polarity,
                                             ViInt32   channel,
                                             ViReal64  lowerLevel,
                                             ViReal64  upperLevel)
{
 	ViStatus error = VI_SUCCESS;
 	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_RUNT_TRIGGER_POLARITY, polarity),
			4, "Polarity");

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_RUNT_TRIGGER_LOWER_LEVEL,
			"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
			3, "Channel");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_RUNT_TRIGGER_LOWER_LEVEL, lowerLevel),
			4, "Lower Level");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_RUNT_TRIGGER_UPPER_LEVEL, upperLevel),
			4, "Upper Level");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines how the measured pulse width is compared with the given
/// HIFN  limit(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR range/Defines how the measured pulse width is compared with the given
/// HIPAR range/limit(s).
ViStatus _VI_FUNC rsrtx_RuntTriggerRange(ViSession instrSession,
                                         ViInt32   range)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_RUNT_TRIGGER_RANGE, range),
    		2, "Range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  For the ranges WITHin and OUTSide, the <Time1> defines the center of a
/// HIFN  range which is defined by the limits +-<Delta>. For the ranges SHORter
/// HIFN  and LONGer, the width defines the maximum and minimum pulse width,
/// HIFN  respectively.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR width/For the ranges WITHin and OUTSide, the <Time1> defines the center of a
/// HIPAR width/range which is defined by the limits +-<Delta>. For the ranges SHORter
/// HIPAR width/and LONGer, the width defines the maximum and minimum pulse width,
/// HIPAR width/respectively.
ViStatus _VI_FUNC rsrtx_ConfigureRuntTriggerWidth(ViSession instrSession,
                                                  ViReal64  width)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_RUNT_TRIGGER_WIDTH, width),
    		2, "Width");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines a range around the width value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR delta/Defines a range around the width value.
ViStatus _VI_FUNC rsrtx_ConfigureRuntTriggerDelta(ViSession instrSession,
                                                  ViReal64  delta)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_RUNT_TRIGGER_DELTA, delta),
    		2, "Delta");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets how the measured pulse width is compared with the given limit(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR range/Sets how the measured pulse width is compared with the given limit(s).
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerRange(ViSession instrSession,
                                                    ViInt32   range)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_WINDOW_RANGE, range),
    		2, "Range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures window trigger width.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR width/Configures window trigger width.
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerWidth(ViSession instrSession,
                                                    ViReal64  width)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_TRIGGER_WINDOW_WIDTH, width),
    		2, "Width");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the window time range.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR timeRange/Configures the window time range.
ViStatus _VI_FUNC rsrtx_ConfigureWindowTriggerTimeRange(ViSession instrSession,
                                                        ViInt32   timeRange)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_WINDOW_TIME_RANGE, timeRange),
    		2, "Time Range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the time the instrument waits after an A-event until it recognizes B-events.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR delayTime/Sets the time the instrument waits after an A-event until it recognizes B-events.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerDelay(ViSession instrSession,
                                              ViReal64  delayTime)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_TRIGGER_DELAY, delayTime),
    		2, "Delay Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/// HIFN Sets the coupling for the external trigger input.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR externalCoupling/Sets the coupling for the external trigger input.
ViStatus _VI_FUNC rsrtx_ConfigureExternalTriggerCoupling(ViSession instrSession,
                                                         ViInt32   externalCoupling)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_EXTERNAL_TRIGGER_COUPLING, externalCoupling),
    		2, "External Coupling");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function defines the holdoff time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR holdoffTime/Defines the holdoff time.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerHoldoffTime(ViSession instrSession,
                                                    ViReal64  holdoffTime)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_TRIGGER_HOLDOFF_TIME, holdoffTime),
    		2, "Holdoff Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function activates or deactivates the second trigger. The instrument triggers if both trigger event conditions (A and B) are fulfilled.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR state/This Control activates or deactivates the second trigger.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerBState(ViSession instrSession,
                                               ViBoolean state)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_TRIGGER_ENABLED, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets a number of B-trigger events that fulfill all B-trigger conditions but do not cause the trigger. The oscilloscope triggers on the n-th event (the last of the specified number of events).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR eventCount/This Control sets a number of B-trigger events.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerEventCount(ViSession instrSession,
                                                   ViInt32   eventCount)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_EVENT_COUNT, eventCount),
    		4, "Event Count");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures the CM voltage offset.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR cmOffset/Configures the CM voltage offset.
ViStatus _VI_FUNC rsrtx_ConfigureProbeCMOffset(ViSession instrSession,
                                               ViInt32   channel,
                                               ViReal64  cmOffset)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_CM_OFFSET,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_CM_OFFSET, cmOffset),
    		3, "CM Offset");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the unit that the probe can measure.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROBE_GAIN_UNIT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PROBe<m>:SETup:GAIN:UNIT
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR unit/Selects the unit that the probe can measure.
ViStatus _VI_FUNC rsrtx_ConfigureProbeGainUnit(ViSession instrSession,
                                               ViInt32   channel,
                                               ViInt32   unit)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_GAIN_UNIT,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROBE_GAIN_UNIT, unit),
    		3, "Unit");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the gain of the probe. The gain the the reciprocal of the
/// HIFN  attenuation (RSRTX_ATTR_PROBE_ATTENUATION_MANUAL).
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROBE_GAIN_MANUAL
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PROBe<m>:SETup:GAIN:MANual
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR probeGain/Sets the gain of the probe. The gain the the reciprocal of the
/// HIPAR probeGain/attenuation (RSRTX_ATTR_PROBE_ATTENUATION_MANUAL).
ViStatus _VI_FUNC rsrtx_ConfigureProbeGainManual(ViSession instrSession,
                                                 ViInt32   channel,
                                                 ViReal64  probeGain)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_GAIN_MANUAL,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_GAIN_MANUAL, probeGain),
    		3, "Probe Gain");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the measured ProbeMeter's DC mean value as offset. Make sure that 
/// HIFN  the Probe-Meter is active before you use this attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_ConfigureProbeCopyToOffset(
	ViSession	instrSession,
	ViInt32	channel
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_COPY_TO_OFFSET,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");
	
	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROBE_COPY_TO_OFFSET, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This attribute is relevant only for differential active probes R&S 
/// HIFN  RT-ZD10, R&S RT-ZD20 or R&S RT-ZD30. If you use the external attenuator 
/// HIFN  R&S RT-ZA15, enable it to include the external attenuation in the 
/// HIFN  measurements.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR enabled/This control is relevant only for differential active probes R&S 
/// HIPAR enabled/RT-ZD10, R&S RT-ZD20 or R&S RT-ZD30. If you use the external attenuator 
/// HIPAR enabled/R&S RT-ZA15, enable it to include the external attenuation in the 
/// HIPAR enabled/measurements.
ViStatus _VI_FUNC rsrtx_ConfigureProbeAttenuatorRTZA15Enabled(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	enabled
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_ATTENUATOR_RT_ZA15_ENABLED,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROBE_ATTENUATOR_RT_ZA15_ENABLED, enabled),
    		3, "Enabled");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This attribute  is relevant only for R&S RT-ZCxxB current probes. It 
/// HIFN  sets the waveform to zero position. It corrects the effect of a voltage 
/// HIFN  offset or temperature drift.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR probeZeroAdjust/This control  is relevant only for R&S RT-ZCxxB current probes. It 
/// HIPAR probeZeroAdjust/sets the waveform to zero position. It corrects the effect of a voltage 
/// HIPAR probeZeroAdjust/offset or temperature drift.
ViStatus _VI_FUNC rsrtx_ConfigureProbeZeroAdjust(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64	zeroAdjust
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_ZERO_ADJUST,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_ZERO_ADJUST, zeroAdjust),
    		3, "Zero Adjust");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This attribute is relevant only for R&S RT-ZCxxB current probes. It 
/// HIFN  saves the zero adjust value in the probe box. If you connect the probe 
/// HIFN  to another channel or to another oscilloscope with Rohde & Schwarz 
/// HIFN  probe interface, the value is read out again.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_ConfigureProbeSaveZeroAdjust(
	ViSession	instrSession,
	ViInt32	channel
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_SAVE_ZERO_ADJUST,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");
	
	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROBE_SAVE_ZERO_ADJUST, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This attribute is relevant for R&S RT-ZHD probes. It sets the voltage 
/// HIFN  range of the probe.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR range/This control is relevant for R&S RT-ZHD probes. It sets the voltage 
/// HIPAR range/range of the probe.
ViStatus _VI_FUNC rsrtx_ConfigureProbeInputVoltageRange(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	range
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_INPUT_VOLTAGE_RANGE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROBE_INPUT_VOLTAGE_RANGE, range),
    		3, "range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This attribute  is relevant for R&S RT-ZHD probes. It activates the 
/// HIFN  lowpass filter in the probe control box.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR bandwidthLimit/This control  is relevant for R&S RT-ZHD probes. It activates the 
/// HIPAR bandwidthLimit/lowpass filter in the probe control box.
ViStatus _VI_FUNC rsrtx_ConfigureProbeBandwidthLimit(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	bandwidthLimit
)
{
 	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_BANDWIDTH_LIMIT,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROBE_BANDWIDTH_LIMIT, bandwidthLimit),
    		3, "Bandwidth Limit");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;   
}


/// HIFN  This attribute is relevant for R&S RT-ZHD probes. It activates the 
/// HIFN  acoustic overrange warning in the probe control box.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR audibleOverrange/This control is relevant for R&S RT-ZHD probes. It activates the 
/// HIPAR audibleOverrange/acoustic overrange warning in the probe control box.
ViStatus _VI_FUNC rsrtx_ConfigureProbeAudibleOverrange(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	audibleOverrange
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_AUDIBLE_OVERRANGE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROBE_AUDIBLE_OVERRANGE, audibleOverrange),
    		3, "Audible Overrange");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  This command is relevant only for R&S RT-ZM probes. It sets the 
/// HIFN  measurement mode of modular probes. You can switch between singleended, 
/// HIFN  differential and common mode measurements without reconnecting or 
/// HIFN  resoldering the probe.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR mode/This command is relevant only for R&S RT-ZM probes. It sets the 
/// HIPAR mode/measurement mode of modular probes. You can switch between singleended, 
/// HIPAR mode/differential and common mode measurements without reconnecting or 
/// HIPAR mode/resoldering the probe.
ViStatus _VI_FUNC rsrtx_ConfigureProbeMeasMode(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	mode
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_MEAS_MODE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROBE_MEAS_MODE, mode),
    		3, "mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  Enables AC coupling in R&S RT-ZPR probes, which removes DC and very 
/// HIFN  low-frequency components. The R&S RT-ZPR probes requires 50   input 
/// HIFN  termination, for which the channel AC coupling is not available. The 
/// HIFN  probe setting allows AC coupling also at 50   inputs.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR acCoupling/Enables AC coupling in R&S RT-ZPR probes, which removes DC and very 
/// HIPAR acCoupling/low-frequency components. The R&S RT-ZPR probes requires 50   input 
/// HIPAR acCoupling/termination, for which the channel AC coupling is not available. The 
/// HIPAR acCoupling/probe setting allows AC coupling also at 50   inputs.
ViStatus _VI_FUNC rsrtx_ConfigureProbeACCoupling(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	acCoupling
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_AC_COUPLING,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROBE_AC_COUPLING, acCoupling),
    		3, "AC Coupling");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;     
}


/// HIFN  Switches the integrated voltmeter of a Rohde & Schwarz active probe on 
/// HIFN  or off. The attribute is only relevant if a Rohde & Schwarz active 
/// HIFN  probe with R&S ProbeMeter is used.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR visibility/Switches the integrated voltmeter of a Rohde & Schwarz active probe on 
/// HIPAR visibility/or off. The control is only relevant if a Rohde & Schwarz active probe 
/// HIPAR visibility/with R&S ProbeMeter is used.
ViStatus _VI_FUNC rsrtx_ConfigureProbeMeterVisibility(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	visibility
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_VISIBILITY,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_VISIBILITY, visibility),
    		3, "visibility");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;     
}


/// HIFN  Returns probe meter single result.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR result/Returns probe meter single result.Attribute:
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultSingle(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64*	result
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_RESULT_SINGLE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_RESULT_SINGLE, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  It returns the common mode voltage, which is the mean voltage between 
/// HIFN  the signal sockets and the ground socket.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR result/It returns the common mode voltage, which is the mean voltage between 
/// HIPAR result/the signal sockets and the ground socket.Attribute:
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultCommon(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64*	result
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_RESULT_COMMON,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_RESULT_COMMON, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  It returns the differential voltage, which is the voltage between the 
/// HIFN  positive and negative signal sockets.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR result/It returns the differential voltage, which is the voltage between the 
/// HIPAR result/positive and negative signal sockets.Attribute:
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultDifferential(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64*	result
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_RESULT_DIFFERENTIAL,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_RESULT_DIFFERENTIAL, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  It returns the voltage that is measured between the negative signal 
/// HIFN  socket and the ground.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR result/It returns the voltage that is measured between the negative signal 
/// HIPAR result/socket and the ground.Attribute:
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultNegative(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64*	result
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_RESULT_NEGATIVE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_RESULT_NEGATIVE, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  It returns the voltage that is measured between the positive signal 
/// HIFN  socket and the ground.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR result/It returns the voltage that is measured between the positive signal 
/// HIPAR result/socket and the ground.Attribute:
ViStatus _VI_FUNC rsrtx_QueryProbeMeterResultPositive(
	ViSession	instrSession,
	ViInt32	channel,
	ViReal64*	result
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROBE_METER_RESULT_POSITIVE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROBE_METER_RESULT_POSITIVE, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}

/// HIFN  This function configures the common attributes of the trigger subsystem.  These attributes are the trigger type and holdoff.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR triggerType/Sets the trigger type.
ViStatus _VI_FUNC rsrtx_ConfigureTrigger(ViSession instrSession,
                                         ViInt32   trigger,
                                         ViInt32   triggerType)
{
    ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_A),
    		2, "Trigger");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_TYPE_A, triggerType),
			4, "Trigger Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the TV trigger.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR standard/This Control sets the color television standard.
/// HIPAR polarity/This Control sets the polarity.
/// HIPAR field/Selects the frame or line.
/// HIPAR line/This Control sets an exact line number.
ViStatus _VI_FUNC rsrtx_ConfigureVideoTriggerSource(ViSession instrSession,
                                                    ViInt32   standard,
                                                    ViInt32   polarity,
                                                    ViInt32   field,
                                                    ViInt32   line)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_ConfigureTrigger(instrSession, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_VIDEO_TRIGGER));
    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TV_STANDARD, standard),
    		2, "Standard");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TV_TRIGGER_POLARITY, polarity),
    		3, "Polarity");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TV_TRIGGER_EVENT, field),
    		4, "Field");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TV_TRIGGER_LINE_NUMBER, line),
    		5, "Line");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the trigger.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR channel/This control selects the channel.
/// HIPAR triggerSource/selects the channel.
/// HIPAR triggerLevel/This control sets the trigger threshold voltage.
/// HIPAR triggerSlope/Selects the slope.
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerSource(ViSession instrSession,
                                                   ViInt32   trigger,
                                                   ViInt32   channel,
                                                   ViInt32   triggerSource,
                                                   ViReal64  triggerLevel,
                                                   ViInt32   triggerSlope)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
    		2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
    	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SOURCE_A, triggerSource),
    			4, "Trigger Source");

		viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SLOPE_A, triggerSlope),
				6, "Trigger Slope");

		viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_TRIGGER_LEVEL_A,
				"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
				2, "Channel");

	    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_TRIGGER_LEVEL_A, triggerLevel),
	    		5, "Trigger Level");
	}
	else
	{
    	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SOURCE_B, triggerSource),
    			4, "Trigger Source");

		viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SLOPE_B, triggerSlope),
				6, "Trigger Slope");

		viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_TRIGGER_LEVEL_B,
				"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
				2, "Channel");

	    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_TRIGGER_LEVEL_B, triggerLevel),
	    		5, "Trigger Level");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the trigger source for the selected trigger type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR source/Selects the source.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerSource(ViSession instrSession,
                                               ViInt32   trigger,
                                               ViInt32   source)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
    		2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SOURCE_A, source),
	    		3, "Source");
	}
	else
	{
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_SOURCE_B, source),
	    		3, "Source");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the coupling for the trigger source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR coupling/Selects coupling event for the trigger source.
ViStatus _VI_FUNC rsrtx_ConfigureEdgeTriggerCoupling(ViSession instrSession,
                                                     ViInt32   coupling)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_COUPLING, coupling),
    		2, "Coupling");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the trigger mode. The trigger mode determines the behaviour of the instrument if no trigger occurs.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR triggerModifier/Sets the trigger mode. The trigger mode determines the behaviour of the instrument if no trigger occurs.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerModifier(ViSession instrSession,
                                                 ViInt32   trigger,
                                                 ViInt32   triggerModifier)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
    		2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_MODIFIER_A, triggerModifier),
	    		3, "Trigger Modifier");
	}
	else
	{
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_TRIGGER_MODIFIER_B, triggerModifier),
	    		3, "Trigger Modifier");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the trigger level automatically. The attribute is not available for an external trigger source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
ViStatus _VI_FUNC rsrtx_TriggerLevelAutoFind(ViSession instrSession,
                                             ViInt32   trigger)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
    		2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
	    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_TRIGGER_LEVEL_AUTO_FIND_A, NULL),
	    		3, "Trigger");
	}
	else
	{
	    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_TRIGGER_LEVEL_AUTO_FIND_B, NULL),
	    		3, "Trigger");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function configures selected trigger level.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR channel/Sets the trigger source for the selected trigger type.
/// HIPAR triggerLevel/Sets the trigger level for the specified event and channel.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerChannelLevel(ViSession instrSession,
                                                     ViInt32   trigger,
                                                     ViInt32   channel,
                                                     ViReal64  triggerLevel)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
    		2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
		viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_TRIGGER_LEVEL_A,
				"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
				3, "Channel");

	    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_TRIGGER_LEVEL_A, triggerLevel),
	    		4, "Trigger Level");
	}
	else
	{
		viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_TRIGGER_LEVEL_B,
				"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
				3, "Channel");

	    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_TRIGGER_LEVEL_B, triggerLevel),
	    		4, "Trigger Level");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets a hysteresis range around the trigger level.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR trigger/Selects trigger event.
/// HIPAR hysteresis/Sets hysteresis range.
ViStatus _VI_FUNC rsrtx_ConfigureTriggerHysteresis(ViSession instrSession,
                                                   ViInt32   trigger,
                                                   ViInt32   hysteresis)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, trigger, RSRTX_VAL_TRIGGER_A, RSRTX_VAL_TRIGGER_B),
			2, "Trigger");

	if (trigger == RSRTX_VAL_TRIGGER_A)
    {
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_TRIGGER_HYSTERESIS_A, hysteresis),
	    		3, "Hysteresis");
    }
	else
	{
	    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_TRIGGER_HYSTERESIS_B, hysteresis),
	    		3, "Hysteresis");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Select the state for each digital channel. Sets the logical combination of the trigger states of the channels. Sets the trigger point depending on the result of the logical combination of the channel states.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR patternSource/This control sets the state for each digital channel.
/// HIPAR patternFunction/Sets the logical combination of the trigger states of the channels.
/// HIPAR patternCondition/This Control sets the trigger point depending on the result of the logical combination of the channel states.
ViStatus _VI_FUNC rsrtx_ConfigurePatternTriggerSource(ViSession instrSession,
                                                      ViString  patternSource,
                                                      ViInt32   patternFunction,
                                                      ViBoolean patternCondition)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_ConfigureTrigger(instrSession, RSRTX_VAL_TRIGGER_A,
                                      RSRTX_VAL_PATTERN_TRIGGER));
    viCheckParm(rsrtx_SetAttributeViString(instrSession, NULL, RSRTX_ATTR_TRIGGER_PATTERN_SOURCE, patternSource),
    		3, "Pattern Source");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_PATTERN_FUNCTION, patternFunction),
    		4, "Pattern Function");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_TRIGGER_PATTERN_POINT_ENABLED, patternCondition),
    		5, "Pattern Condition");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the width trigger.  A width trigger occurs
/// HIFN  when the oscilloscope detects a positive or negative pulse with a width
/// HIFN  between, or optionally outside, the width thresholds.  You specify the
/// HIFN  width thresholds with the Width Low Threshold and Width High Threshold
/// HIFN  parameters.  You specify whether the oscilloscope triggers on pulse
/// HIFN  widths that are within or outside the width thresholds with the Width
/// HIFN  Condition parameter.  You specify the polarity of the pulse with the
/// HIFN  Width Polarity parameter.  The trigger does not actually occur until
/// HIFN  the edge of a pulse that corresponds to the Width Low Threshold, Width
/// HIFN  High Threshold, Width Condition, and Width Polarity crosses the
/// HIFN  threshold you specify in the Trigger Level parameter.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR width/For the ranges "Within" and "Outside", the width defines the center of
/// HIPAR width/ a range which is defined by the limits "+/-Delta". For the ranges
/// HIPAR width/ "Shorter" and "Longer", the width defines the maximum and minimum pulse
/// HIPAR width/ width, respectively.
/// HIPAR widthDelta/Defines a range around the width value.
/// HIPAR widthPolarity/Sets the polarity of the pulse.
/// HIPAR triggerSource/Sets the trigger source for the selected trigger type.
/// HIPAR widthCondition/Sets how the measured pulse width is compared with the given limit(s).
ViStatus _VI_FUNC rsrtx_ConfigureWidthTriggerSource(ViSession instrSession,
                                                    ViInt32   triggerSource,
                                                    ViReal64  triggerLevel,
                                                    ViReal64  width,
                                                    ViReal64  widthDelta,
                                                    ViInt32   widthPolarity,
                                                    ViInt32   widthCondition)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_ConfigureTrigger(instrSession, RSRTX_VAL_TRIGGER_A,
                                      RSRTX_VAL_WIDTH_TRIGGER));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TRIGGER_SOURCE_A, triggerSource),
    		3, "Trigger Source");
   if (triggerSource < RSRTX_VAL_LINE) {
    	viCheckParm(rsrtx_ConfigureTriggerChannelLevel(instrSession,
                                                    RSRTX_VAL_TRIGGER_A,
                                                    triggerSource,
                                                    triggerLevel), 4, "Trigger Level");
   }
    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_WIDTH, width),
    		5, "Width");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_WIDTH_DELTA, widthDelta),
    		6, "Width Delta");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_WIDTH_POLARITY, widthPolarity),
    		7, "Width Polarity");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_WIDTH_CONDITION, widthCondition),
    		8, "Width Condition");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function removes the displayed persistent waveform from the screen.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ClearPersistence(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_PERSISTENCE_CLEAR, NULL),
    		1, "Session");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the time limit for the timeout at which the instrument triggers.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR time/Sets the time limit for the timeout at which the instrument triggers.
/// HIPAR range/Sets the relation of the signal level to the threshold.
ViStatus _VI_FUNC rsrtx_ConfigureTimeoutTriggerTime(ViSession instrSession,
                                                    ViReal64  time,
                                                    ViInt32   range)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_TIMEOUT_TRIGGER_TIME, time),
    		2, "Time");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_TIMEOUT_TRIGGER_RANGE, range),
			3, "Range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Activates the selected actions on trigger event.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR enabled/Activates the selected actions on trigger event.
ViStatus _VI_FUNC rsrtx_ConfigureActionsOnTriggerState(
	ViSession	instrSession,
	ViBoolean	enabled
)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_ENABLED, enabled),
    		2, "Enabled");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  Configures actions on trigger.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR sound/If ON, the instrument generates a beep on trigger event. The 
/// HIPAR sound/acquisition is not delayed, the sound generation runs asynchronously. 
/// HIPAR sound/The minimum time between two beeps is 1 s. If the instrument triggers 
/// HIPAR sound/faster, not all events are notified by a beep.
/// HIPAR screenshot/If ON, the instrument saves a screenshot on each trigger event. The 
/// HIPAR screenshot/screenshot is saved when the acquisition is complete. During saving, 
/// HIPAR screenshot/the acquisition stops, and restarts when saving is finished. Thus, the 
/// HIPAR screenshot/waveform update rate decreases significantly.
/// HIPAR saveWaveform/If ON, the instrument saves the data of a selected waveform on each 
/// HIPAR saveWaveform/trigger event. The waveform is saved when the acquisition is complete. 
/// HIPAR saveWaveform/During saving, the acquisition stops, and restarts when saving is 
/// HIPAR saveWaveform/finished. Thus, the waveform update rate decreases significantly.
/// HIPAR references/Saves reference waveforms of all active channels, and activates the 
/// HIPAR references/references. This action works only with single acquisition.
/// HIPAR pulseOut/If ON, the instrument generates a pulse on the Aux Out connector on 
/// HIPAR pulseOut/trigger event. The acquisition is not delayed, the pulse generation 
/// HIPAR pulseOut/runs asynchronously.
ViStatus _VI_FUNC rsrtx_ConfigureActionsOnTrigger(
	ViSession	instrSession,
	ViBoolean	sound,
	ViBoolean	screenshot,
	ViBoolean	saveWaveform,
	ViBoolean	references,
	ViBoolean	pulseOut
)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));
	
	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_SCREENSHOT, screenshot),
    		3, "Screenshot");
	
	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_SAVE_WAVEFORM, saveWaveform),
    		4, "Save Waveform");
	
	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_REFERENCES, references),
    		5, "References");
	
	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_PULSE_OUT, pulseOut),
    		6, "Pulse Out");

   viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_ACTIONS_ON_TRIGGER_SOUND, sound),
      2, "Sound");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;     
}

/// HIFN This function installs the specified language on the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR language/Selects the language.
/// HIPAR source/This control specifies the string parameter containing source path and file
ViStatus _VI_FUNC rsrtx_DisplayAddLanguage(ViSession instrSession,
                                           ViInt32   language,
                                           ViString  source)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, language, RSRTX_VAL_DISPLAY_ENGLISH, RSRTX_VAL_DISPLAY_KOREAN),
			2, "Language");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "DISP:LANG:ADD %s,\"%s\"", languageArr[language], source);
	checkErr(RsCore_Write(instrSession, cmd));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Sets the language in which the softkey labels, help and other screen
/// HIFN  information can be displayed. Supported languages are listed in the
/// HIFN  Specifications data sheet.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR language/Sets the language in which the softkey labels, help and other screen
/// HIPAR language/information can be displayed. Supported languages are listed in the
/// HIPAR language/Specifications data sheet.
ViStatus _VI_FUNC rsrtx_ConfigureDisplayLanguage(ViSession instrSession,
                                                 ViInt32   language)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_DISPLAY_LANGUAGE, language),
    		2, "Language");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the markers.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR markerAction/This Control selects the marker action.
ViStatus _VI_FUNC rsrtx_MarkerSearch(ViSession instrSession,
                                     ViInt32   markerAction)
{
    ViStatus error = VI_SUCCESS;

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, markerAction, RSRTX_VAL_MARKER_ACTION_SET, RSRTX_VAL_MARKER_ACTION_ACLEAR),
    		2, "Marker Action");


    checkErr(RsCore_LockSession(instrSession));

    switch (markerAction)
    {
        case RSRTX_VAL_MARKER_ACTION_SET:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MARKER_SET, NULL));
            break;
        case RSRTX_VAL_MARKER_ACTION_NEXT:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MARKER_NEXT, NULL));
            break;
        case RSRTX_VAL_MARKER_ACTION_PREV:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MARKER_PREVIOUS, NULL));
            break;
        case RSRTX_VAL_MARKER_ACTION_CLEAR:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MARKER_CLEAR, NULL));
            break;
        case RSRTX_VAL_MARKER_ACTION_ACLEAR:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MARKER_CLEAR_ALL, NULL));
            break;

        default:
            break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Enables grid annotation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Enables grid annotation.
ViStatus _VI_FUNC rsrtx_ConfigureDiagramAnnotationState(ViSession instrSession,
                                                        ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_DIAGRAM_ANNOTATION_ENABLED, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures diagram annotatiom track.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR annotationTrack/Configures diagram annotatiom track.
ViStatus _VI_FUNC rsrtx_ConfigureDiagramAnnotationTrack(ViSession instrSession,
                                                        ViInt32   annotationTrack)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_DIAGRAM_ANNOTATION_TRACK, annotationTrack),
    		2, "Annotation Track");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Switches the date and time display in the upper right corner of the
/// HIFN  screen on or off.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_DISPLAY_DATE_AND_TIME
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     DISPlay:DTIMe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR displayDateAndTime/Switches the date and time display in the upper right corner of the
/// HIPAR displayDateAndTime/screen on or off.
ViStatus _VI_FUNC rsrtx_EnableDisplayDateAndTime(ViSession instrSession,
                                                 ViBoolean displayDateAndTime)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_DISPLAY_DATE_AND_TIME, displayDateAndTime),
    		2, "Display Date and Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Clears the display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_DisplayClearScreen(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_DISPLAY_CLEAR_SCREEN, NULL),
    		1, "Session");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the persistence type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Configures the persistence type.
ViStatus _VI_FUNC rsrtx_ConfigureDisplayPersistenceType(ViSession instrSession,
                                                        ViInt32   type)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_PERSISTENCE_TYPE, type),
    		2, "Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Always records maximum possible number of segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR recordMaximumSegments/Always records maximum possible number of segments.
ViStatus _VI_FUNC rsrtx_ConfigureDisplaySegmentationRecordMaximumSegments(
							ViSession instrSession,
							ViBoolean recordMaximumSegments)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_SEGMENTATION_RECORD_MAXIMUM_SEGMENTS, recordMaximumSegments),
    		2, "Record Maximum Segments");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the the type of the timestamp that is shown the segment table.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/Returns the the type of the timestamp that is shown the segment table.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelTableMode(ViSession instrSession,
                                                     ViInt32   channel,
                                                     ViInt32   *mode)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_CHANNEL_TABLE_MODE,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_CHANNEL_TABLE_MODE, mode),
    		3, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Exports channel history.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR name/Configures export file name.
ViStatus _VI_FUNC rsrtx_HistoryChannelExportSave(ViSession instrSession,
                                                 ViInt32   channel,
                                                 ViString  name)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_CHANNEL_EXPORT_NAME,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_CHANNEL_EXPORT_NAME, name),
    		3, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_CHANNEL_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Displays or hides the history player on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_CHANNEL_PLAYER_CONTROL_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<m>:HISTory:CONTrol:[ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR playerControlEnable/Displays or hides the history player on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryChannelPlayerControlEnable(
							ViSession instrSession,
							ViInt32   channel,
							ViBoolean playerControlEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_CHANNEL_PLAYER_CONTROL_ENABLE,
    		"Channel", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_CHANNEL_PLAYER_CONTROL_ENABLE, playerControlEnable),
    		3, "Player Control Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Displays or hides the segment table on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_CHANNEL_TIME_TABLE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<m>:HISTory:TTABle[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR timeTableEnable/Displays or hides the segment table on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryChannelTimeTableEnable(
							ViSession instrSession,
							ViInt32   channel,
							ViBoolean timeTableEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_CHANNEL_TIME_TABLE_ENABLE,
    		"Channel", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_CHANNEL_TIME_TABLE_ENABLE, timeTableEnable),
    		3, "Time Table Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the absolute daytime of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   channel,
							ViInt32   *hour,
							ViInt32   *minute,
							ViReal64  *second)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, RSRTX_VAL_CHANNEL_1, RSRTX_VAL_CHANNEL_EXT),
    		2, "Channel");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CHAN%ld:HIST:TSAB?", channel);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the date of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistoryChannelAcquisitionDate(ViSession instrSession,
                                                           ViInt32   channel,
                                                           ViInt32   *year,
                                                           ViInt32   *month,
                                                           ViInt32   *day)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, RSRTX_VAL_CHANNEL_1, RSRTX_VAL_CHANNEL_EXT),
    		2, "Channel");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CHAN%ld:HIST:TSD?", channel);
    checkErr(RsCore_QueryTupleViInt32(instrSession, cmd, year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Exports channel history.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR name/Configures export file name.
ViStatus _VI_FUNC rsrtx_DigitalHistoryExportSave(ViSession instrSession,
                                                 ViInt32   digitalChannel,
                                                 ViString  name)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_HISTORY_EXPORT_NAME,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_DIGITAL_HISTORY_EXPORT_NAME, name),
    		3, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_DIGITAL_HISTORY_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Displays or hides the history player on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_LOGIC_PLAYER_CONTROL_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     LOGic<p>:HISTory:CONTrol[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR playerControlEnable/Displays or hides the history player on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayerControlEnable(
							ViSession instrSession,
							ViInt32   logic,
							ViBoolean playerControlEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_PLAYER_CONTROL_ENABLE,
    		"Logic", logic , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_PLAYER_CONTROL_ENABLE, playerControlEnable),
    		3, "Player Control Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Displays or hides the segment table on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_LOGIC_TIME_TABLE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     LOGic<p>:HISTory:TTABle[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR timeTableEnable/Displays or hides the segment table on the screen.
/// HIPAR logic/Selects the logic probe.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicTimeTableEnable(ViSession instrSession,
                                                             ViInt32   logic,
                                                             ViBoolean timeTableEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_TIME_TABLE_ENABLE,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_TIME_TABLE_ENABLE, timeTableEnable),
    		3, "Time Table Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Displays or hides the history player on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_DIGITAL_PLAYER_CONTROL_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     DIGital<m>:HISTory:CONTrol[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR playerControlEnable/Displays or hides the history player on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryDigitalPlayerControlEnable(
							ViSession instrSession,
							ViInt32   digitalChannel,
							ViBoolean playerControlEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_DIGITAL_PLAYER_CONTROL_ENABLE,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_DIGITAL_PLAYER_CONTROL_ENABLE, playerControlEnable),
    		3, "Player Control Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Displays or hides the segment table on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_DIGITAL_TIME_TABLE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     DIGital<m>:HISTory:TTABle[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR timeTableEnable/Displays or hides the segment table on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryDigitalTimeTableEnable(
							ViSession instrSession,
							ViInt32   digitalChannel,
							ViBoolean timeTableEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_DIGITAL_TIME_TABLE_ENABLE,
    		"Digital", digitalChannel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital Channel");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_DIGITAL_TIME_TABLE_ENABLE, timeTableEnable),
    		3, "Time Table Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the absolute daytime of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistoryDigitalAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   digitalChannel,
							ViInt32   *hour,
							ViInt32   *minute,
							ViReal64  *second)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, digitalChannel, 0, 15),
    		2, "Digital Channel");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "DIG%ld:HIST:TSAB?", digitalChannel);
    checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the date of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR digitalChannel/Selects digital channel.
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistoryDigitalAcquisitionDate(ViSession instrSession,
                                                           ViInt32   digitalChannel,
                                                           ViInt32   *year,
                                                           ViInt32   *month,
                                                           ViInt32   *day)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, digitalChannel, 0, 15),
    		2, "Digital Channel");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "DIG%ld:HIST:TSD?", digitalChannel);
	checkErr(RsCore_QueryTupleViInt32(instrSession, cmd, year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Exports history.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR name/Configures export file name.
ViStatus _VI_FUNC rsrtx_HistoryMathExportSave(ViSession instrSession,
                                              ViInt32   mathNumber,
                                              ViString  name)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_MATH_EXPORT_NAME,
    		"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_MATH_EXPORT_NAME, name),
    		3, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_MATH_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Displays or hides the history player on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_MATH_PLAYER_CONTROL_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:HISTory:CONTrol[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR playerControlEnable/Displays or hides the history player on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryMathPlayerControlEnable(
							ViSession instrSession,
							ViInt32   mathNumber,
							ViBoolean playerControlEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_MATH_PLAYER_CONTROL_ENABLE,
    		"Math", mathNumber , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_MATH_PLAYER_CONTROL_ENABLE, playerControlEnable),
    		3, "Player Control Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Displays or hides the segment table on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_MATH_TIME_TABLE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:HISTory:TTABle[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR timeTableEnable/Displays or hides the segment table on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryMathTimeTableEnable(ViSession instrSession,
                                                            ViInt32   mathNumber,
                                                            ViBoolean timeTableEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_MATH_TIME_TABLE_ENABLE,
    		"Math", mathNumber , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_MATH_TIME_TABLE_ENABLE, timeTableEnable),
    		3, "Time Table Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the absolute daytime of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistoryMathAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   mathNumber,
							ViInt32   *hour,
							ViInt32   *minute,
							ViReal64  *second)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, mathNumber, 1, 5),
			2, "Math Number");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CALC:MATH%ld:HIST:TSAB?", mathNumber);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the date of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistoryMathAcquisitionDate(ViSession instrSession,
                                                        ViInt32   mathNumber,
                                                        ViInt32   *year,
                                                        ViInt32   *month,
                                                        ViInt32   *day)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, mathNumber, 1, 5),
    		2, "Math Number");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CALC:MATH%ld:HIST:TSD?", mathNumber);
	checkErr(RsCore_QueryTupleViInt32(instrSession, cmd, year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Exports history.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR name/Configures export file name.
ViStatus _VI_FUNC rsrtx_HistoryProtocolExportSave(ViSession instrSession,
                                                  ViInt32   serialBus,
                                                  ViString  name)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_PROTOCOL_EXPORT_NAME,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_PROTOCOL_EXPORT_NAME, name),
    		3, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_PROTOCOL_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Displays or hides the history player on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_PROTOCOL_PLAYER_CONTROL_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:HISTory:CONTrol[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR playerControlEnable/Displays or hides the history player on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryProtocolPlayerControlEnable(
							ViSession instrSession,
							ViInt32   serialBus,
							ViBoolean playerControlEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_PROTOCOL_PLAYER_CONTROL_ENABLE,
    		"SerialBus", serialBus , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Serial Bus");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_PROTOCOL_PLAYER_CONTROL_ENABLE, playerControlEnable),
    		3, "Player Control Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Displays or hides the segment table on the screen.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_PROTOCOL_TIME_TABLE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:HISTory:TTABle[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR timeTableEnable/Displays or hides the segment table on the screen.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryProtocolTimeTableEnable(
							ViSession instrSession,
							ViInt32   serialBus,
							ViBoolean timeTableEnable)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_PROTOCOL_TIME_TABLE_ENABLE,
    		"SerialBus", serialBus , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Serial Bus");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_PROTOCOL_TIME_TABLE_ENABLE, timeTableEnable),
    		3, "Time Table Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the absolute daytime of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistoryProtocolAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   serialBus,
							ViInt32   *hour,
							ViInt32   *minute,
							ViReal64  *second)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, serialBus, RSRTX_VAL_SERIAL_BUS_1, RSRTX_VAL_SERIAL_BUS_4),
    		2, "Serial Bus");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:HIST:TSAB?", serialBus);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the date of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistoryProtocolAcquisitionDate(ViSession instrSession,
                                                            ViInt32   serialBus,
                                                            ViInt32   *year,
                                                            ViInt32   *month,
                                                            ViInt32   *day)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, serialBus, RSRTX_VAL_SERIAL_BUS_1, RSRTX_VAL_SERIAL_BUS_4),
    		2, "Serial Bus");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:HIST:TSD?", serialBus);
	checkErr(RsCore_QueryTupleViInt32(instrSession, cmd, year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the dates of all history segments as a list of comma-separated
/// HIFN  list of year, month, and day values. The list starts with the oldest
/// HIFN  segment, and the newest segment is the last one.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DATES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:HISTory:TSDate:ALL?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bufferSize/This control indicates the allocated memory for output array.
/// HIPAR allDates/Returns the dates of all history segments as a list of comma-separated
/// HIPAR allDates/list of year, month, and day values. The list starts with the oldest
/// HIPAR allDates/segment, and the newest segment is the last one.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllDates(ViSession instrSession,
                                                     ViInt32   bufferSize,
                                                     ViChar    allDates[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DATES,
    		bufferSize, allDates),
    		2, "All Dates");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the time differences to the newest acquisition of all history
/// HIFN  segments.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_SPECTRUM_ALL_TIME_DIFFERENCES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:HISTory:TSRelative:ALL?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bufferSize/This control indicates the allocated memory for output array.
/// HIPAR allTimeDifferences/Returns the time differences to the newest acquisition of all history
/// HIPAR allTimeDifferences/segments.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllTimeDifferences(
							ViSession instrSession,
							ViInt32   bufferSize,
							ViChar    allTimeDifferences[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DATES,
    		bufferSize, allTimeDifferences),
    		2, "All Time Diferences");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the absolute daytimes of all history segments.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DAYTIMES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:HISTory:TSABsolute:ALL?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR allDaytimes/Returns the absolute daytimes of all history segments.
/// HIPAR bufferSize/This control indicates the allocated memory for output array.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAllDaytimes(ViSession instrSession,
                                                        ViChar    allDaytimes[],
                                                        ViInt32   bufferSize)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_ALL_DAYTIMES,
    		bufferSize, allDaytimes),
    		2, "All Day Times");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the absolute daytime of the selected acquisition
/// HIFN  (RSRTX_ATTR_HISTORY_CHANNEL_CURRENT_ACQUISITION).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR segmentNumber/Selects the acquisition segment number
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   segmentNumber,
							ViInt32*  hour,
							ViInt32*  minute,
							ViReal64* second)
{
    ViStatus error = VI_SUCCESS;
    ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_CURRENT_ACQUISITION, segmentNumber),
    		2, "Segment Number");

    checkErr(RsCore_QueryTupleViReal64(instrSession, "SPEC:HIST:TSAB?", &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the time difference of the selected segment to the newest
/// HIFN  segment. To select a segment, use
/// HIFN  RSRTX_ATTR_HISTORY_CHANNEL_CURRENT_ACQUISITION. The newest segment has
/// HIFN  index 0.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR segmentNumber/Selects the acquisition segment number
/// HIPAR time/Returns the time difference of the selected segment to the newest segment.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionRelativeTime(
							ViSession instrSession,
							ViInt32   segmentNumber,
							ViReal64* time)
{
    ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_CURRENT_ACQUISITION, segmentNumber),
			2, "Segment Number");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_HISTORY_SPECTRUM_ACQUISITION_RELATIVE_TIME, time),
    		3, "Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the date of the selected acquisition
/// HIFN  (RSRTX_ATTR_HISTORY_CHANNEL_CURRENT_ACQUISITION).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR segmentNumber/Selects the acquisition segment number
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistorySpectrumAcquisitionDate(ViSession instrSession,
                                                            ViInt32   segmentNumber,
                                                            ViInt32*  year,
                                                            ViInt32*  month,
                                                            ViInt32*  day)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HISTORY_SPECTRUM_CURRENT_ACQUISITION, segmentNumber),
    		2, "Segment Number");

    checkErr(RsCore_QueryTupleViInt32(instrSession, "SPEC:HIST:TSD?", year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Accesses a particular acquisition segment in the memory to display it.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR currentAcquisition/Accesses a particular acquisition segment in the memory to display it.
/// HIPAR currentAcquisition/The query returns the index of the segment that is shown.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicCurrentAcquisition(
							ViSession instrSession,
							ViInt32   logic,
							ViInt32   currentAcquisition)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_CURRENT_ACQUISITION,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_CURRENT_ACQUISITION, currentAcquisition),
    		3, "Current Acquisition");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Starts and stops the replay of the history segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR player/Starts and stops the replay of the history segments.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayer(ViSession instrSession,
                                                    ViInt32   logic,
                                                    ViInt32   player)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_PLAYER,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_PLAYER, player),
    		3, "Player");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the index of the oldest and the latest segment to be displayed.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR start/Sets the index of the oldest segment to be displayed.
/// HIPAR stop/Sets the index of the latest segment to be displayed.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicAcquisitionStartStop(
							ViSession instrSession,
							ViInt32   logic,
							ViInt32   start,
							ViInt32   stop)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_START_ACQUISITION,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_START_ACQUISITION, start),
    		3, "start");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_STOP_ACQUISITION, stop),
			4, "stop");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the replay of all acquired segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR playAll/Enables the replay of all acquired segments.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicPlayAll(ViSession instrSession,
                                                     ViInt32   logic,
                                                     ViBoolean playAll)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_PLAY_ALL,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_PLAY_ALL, playAll),
    		3, "playAll");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the speed of the history replay.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR speed/Sets the speed of the history replay.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicSpeed(ViSession instrSession,
                                                   ViInt32   logic,
                                                   ViInt32   speed)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_SPEED,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_SPEED, speed),
    		3, "speed");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  If set to true, the replay of the selected history segments repeats
/// HIFN  automatically.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR repeat/If set to true, the replay of the selected history segments repeats
/// HIPAR repeat/automatically.
ViStatus _VI_FUNC rsrtx_ConfigureHistoryLogicRepeat(ViSession instrSession,
                                                    ViInt32   logic,
                                                    ViBoolean repeat)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_REPEAT,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_REPEAT, repeat),
    		3, "repeat");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the absolute daytime of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR hour/Returns hour.
/// HIPAR minute/Returns minute.
/// HIPAR second/Returns seconds.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitionAbsoluteTime(
							ViSession instrSession,
							ViInt32   logic,
							ViInt32*  hour,
							ViInt32*  minute,
							ViReal64* second)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, logic, 1, 2),
    		2, "Logic");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "LOG%ld:HIST:TSAB?", logic);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, &aux1, &aux2, second, NULL));
	*hour = (ViInt32)aux1;
	*minute = (ViInt32)aux2;

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the time difference of the selected segment to the newest
/// HIFN  segment.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR time/Returns the time difference of the selected segment to the newest
/// HIPAR time/segment.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitonRelativeTime(
							ViSession instrSession,
							ViInt32   logic,
							ViReal64* time)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_ACQUISITON_RELATIVE_TIME,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_ACQUISITON_RELATIVE_TIME, time),
    		3, "time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the date of the selected acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR year/Returns year.
/// HIPAR month/Returns month.
/// HIPAR day/Returns day.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAcquisitionDate(ViSession instrSession,
                                                         ViInt32   logic,
                                                         ViInt32*  year,
                                                         ViInt32*  month,
                                                         ViInt32*  day)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, logic, 1, 2),
    		2, "logic");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "LOG%ld:HIST:TSD?", logic);
	checkErr(RsCore_QueryTupleViInt32(instrSession, cmd, year, month, day, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the dates of all history segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR allDates/Returns the dates of all history segments.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllDates(ViSession instrSession,
                                                  ViInt32   logic,
                                                  ViInt32   bufferSize,
                                                  ViChar    allDates[])
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_ALL_DATES,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_ALL_DATES,
    		bufferSize, allDates),
    		3, "All Dates");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the time differences to the newest acquisition of all history
/// HIFN  segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR timeDifferences/Returns the time differences to the newest acquisition of all history
/// HIPAR timeDifferences/segments.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllTimeDifferences(ViSession instrSession,
                                                            ViInt32   logic,
                                                            ViInt32   bufferSize,
                                                            ViChar    timeDifferences[])
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_ALL_TIME_DIFFERENCES,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_ALL_TIME_DIFFERENCES,
    		bufferSize, timeDifferences),
    		3, "Time Differences");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the absolute daytimes of all history segments.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR allDaytimes/Returns the absolute daytimes of all history segments.
ViStatus _VI_FUNC rsrtx_QueryHistoryLogicAllDaytimes(ViSession instrSession,
                                                     ViInt32   logic,
                                                     ViInt32   bufferSize,
                                                     ViChar    allDaytimes[])
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_ALL_DAYTIMES,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_ALL_DAYTIMES,
    		bufferSize, allDaytimes),
    		3, "All Daytimes");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Exports history.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR exportName/History export file name.
ViStatus _VI_FUNC rsrtx_HistoryLogicExportSave(ViSession instrSession,
                                               ViInt32   logic,
                                               ViString  exportName)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_HISTORY_LOGIC_ALL_DAYTIMES,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_EXPORT_NAME, exportName),
    		3, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_HISTORY_LOGIC_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Switches the zoom window on or off.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_WINDOW_ENABLED
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ZOOM:STATe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR zoomWindowEnabled/Switches the zoom window on or off.
ViStatus _VI_FUNC rsrtx_ConfigureZoomWindowEnabled(ViSession instrSession,
                                                   ViBoolean zoomWindowEnabled)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_ZOOM_WINDOW_ENABLED, zoomWindowEnabled),
    		2, "Zoom Window Enabled");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the time base in the zoom diagram in seconds per division.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_DIAGRAM_TIMEBASE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ZOOM:SCALe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR diagramTimebase/Defines the time base in the zoom diagram in seconds per division.
ViStatus _VI_FUNC rsrtx_ConfigureZoomDiagramTimebase(ViSession instrSession,
                                                     ViReal64  diagramTimebase)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_ZOOM_DIAGRAM_TIMEBASE, diagramTimebase),
    		2, "Diagram Time Base");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the offset of the trigger point to the reference point of the
/// HIFN  zoom diagram.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_OFFSET_OF_TRIGGER_POINT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ZOOM:TIME
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR offsetOfTriggerPoint/Defines the offset of the trigger point to the reference point of the
/// HIPAR offsetOfTriggerPoint/zoom diagram.
ViStatus _VI_FUNC rsrtx_ConfigureZoomOffsetOfTriggerPoint(ViSession instrSession,
                                                          ViReal64  offsetOfTriggerPoint)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_ZOOM_OFFSET_OF_TRIGGER_POINT, offsetOfTriggerPoint),
    		2, "Offset of Trigger Point");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the position of the zoom reference point (the reference point
/// HIFN  of the zoom window) in relation to the reference point of original time
/// HIFN  base.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_REFERENCE_POINT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TIMebase:ZOOM:POSition
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referencePoint/Defines the position of the zoom reference point (the reference point
/// HIPAR referencePoint/of the zoom window) in relation to the reference point of original time
/// HIPAR referencePoint/base.
ViStatus _VI_FUNC rsrtx_ConfigureZoomReferencePoint(ViSession instrSession,
                                                    ViReal64  referencePoint)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_ZOOM_REFERENCE_POINT, referencePoint),
    		2, "Reference Point");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the position of the divide bar between normal waveform and
/// HIFN  zoom window. Sets the vertical position in pixels, measured from the
/// HIFN  top edge. The vertical display size is 800 px.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_WINDOW_POSITION
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     DISPlay:CBAR:ZOOM[:POSition]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR zoomWindowPosition/Defines the position of the divide bar between normal waveform and
/// HIPAR zoomWindowPosition/zoom window. Sets the vertical position in pixels, measured from the
/// HIPAR zoomWindowPosition/top edge. The vertical display size is 800 px.
ViStatus _VI_FUNC rsrtx_ConfigureZoomWindowPosition(ViSession instrSession,
                                                    ViInt32   zoomWindowPosition)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ZOOM_WINDOW_POSITION, zoomWindowPosition),
    		2, "Zoom Window Position");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the sample rate of the zoom window.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ZOOM_SAMPLE_RATE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     ACQuire:SRATe:ZOOM?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR sampleRate/Returns the sample rate of the zoom window.
ViStatus _VI_FUNC rsrtx_QueryZoomSampleRate(ViSession instrSession,
                                            ViReal64* sampleRate)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_ZOOM_SAMPLE_RATE, sampleRate),
    		2, "Sample Rate");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the state of the indicated measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR signalSource/Selects the source of the measurement.
/// HIPAR referenceSource/Selects the source of the reference.
ViStatus _VI_FUNC rsrtx_ConfigureMeasurementSource(ViSession instrSession,
                                                   ViInt32   measurement,
                                                   ViInt32   signalSource,
                                                   ViInt32   referenceSource)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, RSRTX_VAL_MEASUREMENT_1, RSRTX_VAL_MEASUREMENT_8),
    		2, "Measurement");
    viCheckParm(RsCore_InvalidViInt32Range(instrSession, signalSource, RSRTX_VAL_MEASUREMENT_SOURCE_NONE, RSRTX_VAL_MEASUREMENT_SOURCE_QMA),
    		3, "Signal Source");
    viCheckParm(RsCore_InvalidViInt32Range(instrSession, referenceSource, RSRTX_VAL_MEASUREMENT_SOURCE_NONE, RSRTX_VAL_MEASUREMENT_SOURCE_QMA),
    		4, "Reference Source");

	if (referenceSource != RSRTX_VAL_MEASUREMENT_SOURCE_NONE)
	{
		snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:SOUR %s,%s", measurement, signalSourceArr[signalSource], signalSourceArr[referenceSource]);
		checkErr(RsCore_Write(instrSession, cmd));
	}
	else
	{
		snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:SOUR %s", measurement, signalSourceArr[signalSource]);
		checkErr(RsCore_Write(instrSession, cmd));
	}

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Set the cursor line to the next peak, respectively. The attribute is
/// HIFN  only available for FFT waveforms.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR cursor/This control selects the cursor.
/// HIPAR cursorLine/Selects the cursor line.
ViStatus _VI_FUNC rsrtx_CursorLineNextPeak(ViSession instrSession,
                                           ViInt32   cursor,
                                           ViInt32   cursorLine)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, cursor, 1, 3),
    		2, "Cursor");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, cursorLine, 1, 2),
			2, "Cursor Line");

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "Cur%ld,CursorLine%ld", cursor, cursorLine);

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_CURSOR_LINE_NEXT_PEAK, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Set the cursor line to the previous peak, respectively. The attribute
/// HIFN  is only available for FFT waveforms.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR cursor/This control selects the cursor.
/// HIPAR cursorLine/Selects the cursor line.
ViStatus _VI_FUNC rsrtx_CursorLinePreviousPeak(ViSession instrSession,
                                               ViInt32   cursor,
                                               ViInt32   cursorLine)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, cursor, 1, 3),
    		2, "Cursor");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, cursorLine, 1, 2),
			2, "Cursor Line");

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "Cur%ld,CursorLine%ld", cursor, cursorLine);

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_CURSOR_LINE_PREVIOUS_PEAK, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Starts or stops the quick measurement and sets the status bit.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Starts or stops the quick measurement and sets the status bit.
ViStatus _VI_FUNC rsrtx_ConfigureQuickMeasurementState(ViSession instrSession,
                                                       ViInt32   measurement,
                                                       ViBoolean state)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap_measurement[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_QUICK_MEASUREMENTS_ENABLE_WITH_STATUS_BIT,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap_measurement),
    		2, "Measurement");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap_measurement, RSRTX_ATTR_QUICK_MEASUREMENTS_ENABLE_WITH_STATUS_BIT, state),
    		3, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Document your function here.
/// HIFN You may use multiple lines for documentation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR quickMeasurementsEnabled/This function enables and disables all quick measurements of the indicated measurement
ViStatus _VI_FUNC rsrtx_ConfigureQuickMeasurements(ViSession instrSession,
                                                   ViInt32   measurement,
                                                   ViBoolean quickMeasurementsEnabled)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap_measurement[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MEASUREMENT_ENABLED,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap_measurement),
    		2, "Measurement");

    if (quickMeasurementsEnabled)
    {
        viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap_measurement, RSRTX_ATTR_QUICK_MEASUREMENTS_ENABLE, NULL),
        		3, "Quick Measurements Enable");
    }
    else
    {
        viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap_measurement, RSRTX_ATTR_QUICK_MEASUREMENTS_DISABLE, NULL),
        		3, "Quick Measurements Disable");
    }

Error:
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the results of the quick measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR results/Returns the list of values.
ViStatus _VI_FUNC rsrtx_QueryQuickMeasurementResults(ViSession instrSession,
                                                     ViInt32   measurement,
                                                     ViInt32   arraySize,
                                                     ViReal64  results[])
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, RSRTX_VAL_MEASUREMENT_1, RSRTX_VAL_MEASUREMENT_8),
    		2, "Measurement");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:ARES?", measurement);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, arraySize, results, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  The waiting time is set automatically, based on the horizontal scale.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR autoTimeout/The waiting time is set automatically, based on the horizontal scale.
ViStatus _VI_FUNC rsrtx_ConfigureAutomaticMeasurementTimeoutAuto(
	ViSession	instrSession,
	ViInt32	measurement,
	ViBoolean	autoTimeout
)
{
 	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT_AUTO,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Measurement");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT_AUTO, autoTimeout),
    		3, "Auto Timeout");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;   
}


/// HIFN  Sets a waiting time, how long the instrument waits until it returns 
/// HIFN  the measurement results.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR timeout/Sets a waiting time, how long the instrument waits until it returns 
/// HIPAR timeout/the measurement results.
ViStatus _VI_FUNC rsrtx_ConfigureAutomaticMeasurementTimeout(
	ViSession	instrSession,
	ViInt32	measurement,
	ViReal64	timeout
)
{
 	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Measurement");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_AUTOMATIC_MEASUREMENT_TIMEOUT, timeout),
    		3, "Timeout");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;   
}

/// HIFN This function resets the statistical results for the selected measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR measurement/This control selects the measurement.
ViStatus _VI_FUNC rsrtx_ResetAutomaticMeasurement(ViSession instrSession,
                                                  ViInt32   measurement)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap_measurement[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_RESET_AUTOMATIC_MEASUREMENT,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap_measurement),
    		2, "Measurement");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap_measurement, RSRTX_ATTR_RESET_AUTOMATIC_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines or queries the main measurement. This measurement is the one 
/// HIFN  referred to if the measurement waveform is used as a source for math 
/// HIFN  calculations. The main measurement type must belong to the same 
/// HIFN  category as the other types assigned to the same measurement waveform, 
/// HIFN  if there are any.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR type/Defines or queries the main measurement. This measurement is the one 
/// HIPAR type/referred to if the measurement waveform is used as a source for math 
/// HIPAR type/calculations. The main measurement type must belong to the same 
/// HIPAR type/category as the other types assigned to the same measurement waveform, 
/// HIPAR type/if there are any.
ViStatus _VI_FUNC rsrtx_ConfigureAmplitudeTimeMainMeasurement(
	ViSession	instrSession,
	ViInt32	measurement,
	ViInt32	type
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_AMPT_MAIN_MEASUREMENT,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Measurement");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_AMPT_MAIN_MEASUREMENT, type),
    		3, "Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}


/// HIFN  If ON, the markers show the edge, the measured point on the edge, and 
/// HIFN  the direction in which the edge is detected.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR visible/If ON, the markers show the edge, the measured point on the edge, and 
/// HIPAR visible/the direction in which the edge is detected.
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasurementMarkerVisible(
	ViSession	instrSession,
	ViInt32	measurement,
	ViBoolean	visible
)
{
	ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MEASUREMENT_DELAY_MARKER_VISIBLE,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Measurement");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_MEASUREMENT_DELAY_MARKER_VISIBLE, visible),
    		3, "Visible");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}

/// HIFN  Sets the edges to be used for delay measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR measurement/This control selects the measurement.
/// HIPAR source1Slope/Slope of source 1 (first waveform).
/// HIPAR source2Slope/Slope of source 2 (second waveform).
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasuremenSlope(ViSession instrSession,
                                                      ViInt32   measurement,
                                                      ViInt32   source1Slope,
                                                      ViInt32   source2Slope)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViString slopeArr[] = {"POS","NEG"};

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, 1, 8),
			2, "Measurement");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, source1Slope, RSRTX_VAL_MEAS_SLOPE_POS, RSRTX_VAL_MEAS_SLOPE_NEG),
			3, "Source 1 Slope");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, source2Slope, RSRTX_VAL_MEAS_SLOPE_POS, RSRTX_VAL_MEAS_SLOPE_NEG),
			4, "Source 2 Slope");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:DEL:SLOP %s,%s", measurement, slopeArr[source1Slope], slopeArr[source2Slope]);
	checkErr(RsCore_Write(instrSession, cmd));

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the edges for delay measurement and delay to trigger 
/// HIFN  measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or 
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR measurement/Selects waveform measurement.
/// HIPAR direction1/Defines the first edge for the delay measurement.
/// HIPAR direction2/Defines the second edge for the delay measurement.
ViStatus _VI_FUNC rsrtx_ConfigureDelayMeasurementDirection(
	ViSession	instrSession,
	ViInt32	measurement,
	ViInt32	direction1,
	ViInt32	direction2
)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, 1, 8),
			2, "Measurement");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, direction1, RSRTX_VAL_MEAS_DELAY_DIRECTION_NEAR, RSRTX_VAL_MEAS_DELAY_DIRECTION_FRLA),
			3, "Direction 1");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, direction2, RSRTX_VAL_MEAS_DELAY_DIRECTION_NEAR, RSRTX_VAL_MEAS_DELAY_DIRECTION_FRLA),
			4, "Direction 2");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MEAS%ld:DEL:DIR %s,%s", measurement, 
			 RsRtx_rngMeasurementDelayDirection.rangeValues[direction1].cmdString, 
			 RsRtx_rngMeasurementDelayDirection.rangeValues[direction2].cmdString);
	
	checkErr(RsCore_Write(instrSession, cmd));

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;    
}

/// HIFN  This function sets the lower and upper reference levels.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR relativeMode/Selects the reference level.
ViStatus _VI_FUNC rsrtx_ConfigureReferenceLevelMode(ViSession instrSession,
                                                    ViInt32   relativeMode)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_MEAS_RELATIVE_MODE, relativeMode),
    		3, "Relative Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Set the lower and upper reference levels for rise and fall time mesurements,
/// HIFN  and the middle reference level used for phase and delay measurements.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR lowerLevel/Set the lower reference level for rise and fall time mesurements.
/// HIPAR upperLevel/Set the upper reference level for rise and fall time mesurements.
/// HIPAR middleLevel/Set the middle reference level used for phase and delay measurements.
ViStatus _VI_FUNC rsrtx_ConfigureUserReferenceLevel(ViSession instrSession,
                                                    ViReal64  lowerLevel,
                                                    ViReal64  upperLevel,
                                                    ViReal64  middleLevel)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_MEAS_RELATIVE_LOWER_LEVEL, lowerLevel),
    		2, "Lower Level");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_MEAS_RELATIVE_UPPER_LEVEL, upperLevel),
    		3, "Upper Level");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_MEAS_RELATIVE_MIDDLE_LEVEL, middleLevel),
    		4, "Middle Level");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function switches all cursors off.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
ViStatus _VI_FUNC rsrtx_AllCursorsOff(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_ALL_CURSORS_OFF, NULL),
    		2, "All Cursors Off");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the cursor measurement type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Defines the cursor measurement type.
ViStatus _VI_FUNC rsrtx_ConfigureCursorMeasurementType(ViSession instrSession,
                                                       ViInt32   cursor,
                                                       ViInt32   type)
{
	ViStatus error = VI_SUCCESS;
	         cursor;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_CURSOR_MEASUREMENT_TYPE, type),
			2, "type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the source of the cursor measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Defines the source of the cursor measurement.
ViStatus _VI_FUNC rsrtx_ConfigureCursorSource(ViSession instrSession,
                                              ViInt32   cursor,
                                              ViInt32   source)
{
	ViStatus error = VI_SUCCESS;
	         cursor;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_CURSOR_SOURCE, source),
			2, "source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures settings for second source.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_CURSOR_SECOND_SOURCE_ENABLE
/// HIFN     RSRTX_ATTR_CURSOR_SECOND_SOURCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CURSor<m>:SSOURce
/// HIFN     CURSor<m>:USSOURce
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR secondSourceEnable/Enables the second cursor source. To select the second source, use
/// HIPAR secondSourceEnable/RSRTX_ATTR_CURSOR_SECOND_SOURCE. If enabled, the second cursor measures
/// HIPAR secondSourceEnable/on the second source. Using a second source, you can measure
/// HIPAR secondSourceEnable/differences between two waveforms with cursors. Both sources must be in
/// HIPAR secondSourceEnable/the same domain (time domain or frequency domain).
/// HIPAR secondSource/Selects the second cursor source.
ViStatus _VI_FUNC rsrtx_ConfigureCursorSecondSourceSettings(ViSession instrSession,
                                                            ViBoolean secondSourceEnable,
                                                            ViInt32   secondSource)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_CURSOR_SECOND_SOURCE_ENABLE, secondSourceEnable),
			2, "Second Source Enable");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_CURSOR_SECOND_SOURCE, secondSource),
			3, "Second Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function resets the cursor to the initial position or sets the cursor lines to typical points of the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR cursor/This control selects the cursor.
/// HIPAR position/Selects if the cursor position resets or autosets.
ViStatus _VI_FUNC rsrtx_SetCursorPosition(ViSession instrSession,
                                          ViInt32   cursor,
                                          ViInt32   position)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, position, 0, 1),
			3, "Position");
	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CURSOR_AUTOSET,
			"Cursor", cursor , RS_REPCAP_BUF_SIZE, repCap),
			2, "Cursor");

	switch(position)
    {
        case RSRTX_VAL_CURSOR_POSITION_AUTOSET:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CURSOR_AUTOSET, NULL));

        break;

        case RSRTX_VAL_CURSOR_POSITION_RESET:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CURSOR_RESET, NULL));
        break;

        default:
        break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function configures the horizontal and vertical position of
/// HIFN selected cursor or cursor line.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR cursor/This control selects the cursor.
/// HIPAR xPosition1/Defines the position of the left vertical cursor line.
/// HIPAR xPosition2/Defines the position of the right vertical cursor line.
/// HIPAR yPosition1/Defines the position of the lower horizontal cursor line.
/// HIPAR yPosition2/Defines the position of the upper horizontal cursor line.
ViStatus _VI_FUNC rsrtx_ConfigureCursorPosition(ViSession instrSession,
                                                ViReal64  xPosition1,
                                                ViReal64  xPosition2,
                                                ViReal64  yPosition1,
                                                ViReal64  yPosition2)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_CURSOR_X1_POSITION, xPosition1),
    		2, "xPosition1");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_CURSOR_X2_POSITION, xPosition2),
    		3, "xPosition2");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_CURSOR_Y1_POSITION, yPosition1),
    		4, "yPosition1");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_CURSOR_Y2_POSITION, yPosition2),
			5, "yPosition2");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function sets the cursor to the next or the previous peak.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR instrSession/The handle identifies a particular instrument session.
/// HIPAR cursor/This control selects the cursor.
/// HIPAR peak/This control selects if the cursor is set to the next or the previous peak.
ViStatus _VI_FUNC rsrtx_SetFFTAnalysisCursorToPeak(ViSession instrSession,
                                                   ViInt32   cursor,
                                                   ViInt32   peak)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, peak, 0, 1),
			3, "Position");
	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_CURSOR_AUTOSET,
			"Cursor", cursor , RS_REPCAP_BUF_SIZE, repCap),
			2, "Cursor");

	switch(peak)
    {
        case RSRTX_VAL_CURSOR_PEAK_NEXT:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CURSOR_PEAK_NEXT, NULL));

        break;
        case RSRTX_VAL_CURSOR_PEAK_PREVIOUS:
            checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CURSOR_PEAK_PREVIOUS, NULL));
        break;
        default:
        break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Creates a mask from the envelope waveform of the test source set with MASK: SOURce.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_MaskCopyChannel(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, NULL, RSRTX_ATTR_MASK_COPY_CHANNEL, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Sets the counters of passed and failed acquisitions to Zero.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_MaskResetTestCounter(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MASK_RESET_TEST_COUNTER, NULL));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Defines the path and filename for a screenshot that will be saved on
/// HIFN  mask violation. The file format is PNG, the filename is incremented
/// HIFN  automatically.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR destination/Defines the path and filename for a screenshot that will be saved on
/// HIPAR destination/mask violation. The file format is PNG, the filename is incremented
/// HIPAR destination/automatically.
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionScreenshotDestination(
							ViSession instrSession,
							ViString  destination)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MASK_TEST_ACTION_SCREENSHOT_DESTINATION, destination),
    		2, "Destination");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Defines the path and filename for a waveform data that will be saved
/// HIFN  on mask violation. The file format is CSV, the filename is incremented
/// HIFN  automatically.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR destination/Defines the path and filename for a waveform data that will be saved
/// HIPAR destination/on mask violation. The file format is CSV, the filename is incremented
/// HIPAR destination/automatically.
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionSavesWaveformDestination(
							ViSession instrSession,
							ViString  destination)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_MASK_TEST_ACTION_SAVES_WAVEFORM_DESTINATION, destination),
    		2, "Destination");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Creates a pulse on the AUX OUT connector if the mask is violated. This
/// HIFN  selection sets the configuration of the AUX OUT connector to Mask
/// HIFN  Violation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Creates a pulse on the AUX OUT connector if the mask is violated. This
/// HIPAR state/selection sets the configuration of the AUX OUT connector to Mask
/// HIPAR state/Violation.
ViStatus _VI_FUNC rsrtx_ConfigureMaskTestActionAUXOutputState(
							ViSession instrSession,
							ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_MASK_TEST_ACTION_AUX_OUTPUT_ENABLED, state),
    		2, "State");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Moves the mask vertically within the display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR verticalOffset/Moves the mask vertically within the display.
/// HIPAR verticalScaling/Changes the vertical scaling to stretch or compress the mask in
/// HIPAR verticalScaling/y-direction.
/// HIPAR verticalWidth/Changes the width of the mask in vertical direction.
/// HIPAR horizontalWidth/Changes the width of the mask in horizontal direction.
ViStatus _VI_FUNC rsrtx_ConfigureMaskScaling(ViSession instrSession,
                                             ViReal64  verticalOffset,
                                             ViReal64  verticalScaling,
                                             ViReal64  verticalWidth,
                                             ViReal64  horizontalWidth)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_VERTICAL_OFFSET, verticalOffset),
    		2, "Vertical Offset");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_VERTICAL_SCALING, verticalScaling),
			3, "Vertical Scaling");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_VERTICAL_WIDTH, verticalWidth),
			4, "Vertical Width");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_HORIZONTAL_WIDTH, horizontalWidth),
			5, "Horizontal Width");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Only available with history. The command selects whether all
/// HIFN  acquisitions are stored in segments, or only failed acquisition. You
/// HIFN  can use the history to analyze the segments.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MASK_SEGMENT_CAPTURE_MODE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     MASK:CAPTure[:MODE]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR captureMode/Only available with history. The command selects whether all
/// HIPAR captureMode/acquisitions are stored in segments, or only failed acquisition. You
/// HIPAR captureMode/can use the history to analyze the segments.
ViStatus _VI_FUNC rsrtx_ConfigureMaskSegmentCaptureMode(ViSession instrSession,
                                                        ViInt32   captureMode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_MASK_SEGMENT_CAPTURE_MODE, captureMode),
    		2, "Capture Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the symptom you want to search for.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR condition/Selects the symptom you want to search for.
ViStatus _VI_FUNC rsrtx_ConfigureSearchCondition(ViSession instrSession,
                                                 ViInt32   condition)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SEARCH_CONDITION, condition),
    		2, "Condition");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Selects the waveform to be analyzed. One of the active channel, math,
/// HIFN  and reference waveforms can be searched.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Selects the waveform to be analyzed. One of the active channel, math,
/// HIPAR source/and reference waveforms can be searched.
ViStatus _VI_FUNC rsrtx_ConfigureSearchSource(ViSession instrSession,
                                              ViInt32   source)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SEARCH_SOURCE, source),
    		2, "Source");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Sets the voltage threshold. When the signal crosses this level, the
/// HIFN  window measurement starts or stops depending on the selected slope.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR lower/Sets the voltage threshold. When the signal crosses this level, the
/// HIPAR lower/window measurement starts or stops depending on the selected slope.
/// HIPAR upper/Sets the voltage threshold. When the signal crosses this level, the
/// HIPAR upper/window measurement starts or stops depending on the selected slope.
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowLevel(ViSession instrSession,
                                                          ViReal64  lower,
                                                          ViReal64  upper)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_LEVEL_LOWER, lower),
    		2, "lower");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_LEVEL_UPPER, upper),
			3, "upper");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Sets a range delta t.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR delta/Sets a range delta t.
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowDelta(ViSession instrSession,
                                                          ViReal64  delta)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_DELTA, delta),
    		2, "delta");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Sets the slope to be found.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Sets the slope to be found.
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowPolarity(ViSession instrSession,
                                                             ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_POLARITY, polarity),
    		2, "Polarity");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Sets how the measured pulse width is compared with the given limit(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR range/Sets how the measured pulse width is compared with the given limit(s).
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowRange(ViSession instrSession,
                                                          ViInt32   range)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_RANGE, range),
    		2, "Range");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Configures the window time range.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR timeRange/Configures the window time range.
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowTimeRange(
							ViSession instrSession,
							ViInt32   timeRange)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_TIME_RANGE, timeRange),
    		2, "Time Range");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Configures window trigger width.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR width/Configures window trigger width.
ViStatus _VI_FUNC rsrtx_ConfigureSearchTriggerWindowWidth(ViSession instrSession,
                                                          ViReal64  width)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SEARCH_TRIGGER_WINDOW_WIDTH, width),
    		2, "Width");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Saves search results of the indicated measurement place to the file.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR name/Defines the path and filename of the results file, available for
/// HIPAR name/search. The file format is CSV. If the file already exists, it will be
/// HIPAR name/overwritten.
ViStatus _VI_FUNC rsrtx_SearchExportSave(ViSession instrSession,
                                         ViString  name)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SEARCH_EXPORT_NAME, name),
    		2, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SEARCH_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the result values of the specified search result.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR resultNumber/Number of result to be read.
/// HIPAR xPosition/Returns the X-position (time) of the search result
/// HIPAR yPosition/Returns the Y-position of the search result, currently not relevant. .
/// HIPAR resultType/Returns the type of the search result (Edge, Peak, Width).
/// HIPAR polarity/Returns the slope or polarity of the search result.
/// HIPAR voltageWidth/For peak searches, the value contains the peak voltage.
ViStatus _VI_FUNC rsrtx_QuerySearchResult(ViSession instrSession,
                                          ViInt32   resultNumber,
                                          ViReal64  *xPosition,
                                          ViReal64  *yPosition,
                                          ViInt32   *resultType,
                                          ViInt32   *polarity,
                                          ViReal64  *voltageWidth)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViChar   response[RS_MAX_MESSAGE_BUF_SIZE];
	ViChar*  p2buf;
	ViString resultTypeArr[] = {"EDGE","WIDTH","PEAK","RUNT","RTIM","DATATOCLOCK", "PATTERN","PROTOCOL","WINDOW",NULL};
	ViString polarityArr[] = {"POSITIVE","NEGATIVE","EITHER",NULL};

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SEAR:RES%ld?", resultNumber);
    checkErr(RsCore_QueryViString(instrSession, cmd, response));
    checkErr(rsrtx_CheckStatus(instrSession));

    strtok (response, ",");
	p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (xPosition != NULL) *xPosition = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (yPosition != NULL) *yPosition = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (resultType != NULL) *resultType = RsCore_FindStringIndex(resultTypeArr, p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (polarity != NULL) *polarity = RsCore_FindStringIndex(polarityArr, p2buf);

	p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (voltageWidth != NULL) *voltageWidth = RsCore_Convert_String_To_ViReal64(p2buf);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/// HIFN  This function returns all result values of the search.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR arraySize/Pass the number of elements in the array parameters.
/// HIPAR xPosition/Returns the X-position (time) of the search result
/// HIPAR yPosition/Returns the Y-position of the search result, currently not relevant. .
/// HIPAR resultType/Returns the type of the search result (Edge, Peak, Width).
/// HIPAR polarity/Returns the slope or polarity of the search result.
/// HIPAR voltageWidth/For peak searches, the value contains the peak voltage.
/// HIPAR numberOfResults/Number of returned results.
ViStatus _VI_FUNC rsrtx_QueryAllSearchResults(ViSession instrSession,
                                              ViInt32   arraySize,
                                              ViReal64  xPosition[],
                                              ViReal64  yPosition[],
                                              ViInt32   resultType[],
                                              ViInt32   polarity[],
                                              ViReal64  voltageWidth[],
                                              ViInt32   *numberOfResults)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViChar*  p2buf;
	ViChar   *buf = NULL;
	ViInt32  i;
	ViString resultTypeArr[] = {"EDGE","WIDTH","PEAK","RUNT","RTIM","DATATOCLOCK",
	         "PATTERN","PROTOCOL","WINDOW",NULL};
	ViString polarityArr[] = {"POSITIVE","NEGATIVE","EITHER",NULL};

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SEAR:RES:ALL?");
    checkErr(RsCore_QueryViStringUnknownLength(instrSession, cmd, &buf));
    checkErr(rsrtx_CheckStatus(instrSession));

	strtok (buf, ",");
    for (i=0; i<arraySize; i++)
	{
		p2buf = strtok (NULL, ",");
	    if (p2buf == NULL)
	        checkErr(VI_ERROR_INV_RESPONSE);
	    xPosition[i] = RsCore_Convert_String_To_ViReal64(p2buf);

	    p2buf = strtok (NULL, ",");
	    if (p2buf == NULL)
	        checkErr(VI_ERROR_INV_RESPONSE);
	    yPosition[i] = RsCore_Convert_String_To_ViReal64(p2buf);

	    p2buf = strtok (NULL, ",");
	    if (p2buf == NULL)
	        checkErr(VI_ERROR_INV_RESPONSE);
	    resultType[i] = RsCore_FindStringIndex(resultTypeArr, p2buf);

	    p2buf = strtok (NULL, ",");
	    if (p2buf == NULL)
	        checkErr(VI_ERROR_INV_RESPONSE);
	    polarity[i] = RsCore_FindStringIndex(polarityArr, p2buf);

		p2buf = strtok (NULL, ",");
	    if (p2buf == NULL)
	        checkErr(VI_ERROR_INV_RESPONSE);
	    voltageWidth[i] = RsCore_Convert_String_To_ViReal64(p2buf);

		*numberOfResults = i;

		p2buf = strtok (NULL, ",");
		if (p2buf == NULL) break;
	}

Error:
	if (buf) free(buf);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Executes the analysis of all channels that are configured for the selected bus
/// HIFN and sets the threshold for digitization of analog signals for each channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
ViStatus _VI_FUNC rsrtx_ProtocolFindLevel(ViSession instrSession,
                                          ViInt32   channel)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_FIND_LEVEL,
    		"Channel", channel , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROTOCOL_FIND_LEVEL, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function queries the contents of the frame table in block data format.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bufferSize/This control indicates the allocated memory in Decoded Data.
/// HIPAR decodedData/Returns the contents of the frame table in block data format.
ViStatus _VI_FUNC rsrtx_QueryBusDecodedData(ViSession instrSession,
                                            ViInt32   serialBus,
                                            ViInt32   bufferSize,
                                            ViChar    decodedData[])
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViByte   *data = NULL;
	ViInt64  length;

    checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:LIST?", serialBus);
	checkErr(RsCore_QueryBinaryDataBlock(instrSession, cmd, VI_TRUE, NULL, &data, &length));
	checkErr(RsCore_CopyToUserBufferBinData((ViBuf)decodedData, bufferSize, data, length));

	error = rsrtx_CheckStatus(instrSession);

Error:
	if (data) free (data);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the vertical position of the decoded bus signal in divisions on
/// HIFN  the sreen.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR vertical/Sets the vertical position of the decoded bus signal in divisions on
/// HIPAR vertical/the sreen.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolDisplayVertical(ViSession instrSession,
                                                         ViInt32   serialBus,
                                                         ViReal64  vertical)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_DISPLAY_VERTICAL,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_DISPLAY_VERTICAL, vertical),
    		3, "vertical");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Queries the all data words of the specified frame in comma-separated list of decimal values of the data bytes.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR frame/This control selects the frame.
/// HIPAR arraySize/Pass the number of values allocated for Data result array.
/// HIPAR data/Data words of the specified frame.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryI2CFrameAllData(ViSession instrSession,
                                             ViInt32   serialBus,
                                             ViInt32   frame,
                                             ViInt32   arraySize,
                                             ViInt32   data[],
                                             ViInt32   *returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViInt32* auxData = NULL;
	ViInt32  auxDataLen;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K1"));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:I2C:FRAM%ld:DATA?", serialBus, frame);
	checkErr(RsCore_QueryIntegerArray(instrSession, cmd, &auxData, &auxDataLen));
	*returnedValues = auxData[0];
	auxDataLen--;
	checkErr(rsrtx_CheckStatus(instrSession));
	checkErr(RsCore_CopyToUserBufferViInt32Array(data, arraySize, auxData + 1, auxDataLen));

Error:
	if (auxData) free(auxData);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects wether the chip select signal is high active (high = 1) or low
/// HIFN  active (low = 1).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR polarity/Selects wether the chip select signal is high active (high = 1) or low active (low = 1)
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPICSPolarity(ViSession instrSession,
                                                       ViInt32   serialBus,
                                                       ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SPI_CS_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SPI_CS_POLARITY, polarity),
    		3, "polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the trigger source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR triggerSource/Selects the trigger source.
ViStatus _VI_FUNC rsrtx_ConfigureSPITriggerSource(ViSession instrSession,
                                                  ViInt32   triggerSource)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_SPI_TRIGGER_SOURCE, triggerSource),
    		2, "Trigger Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Queries the data words of the specified frame of the MISO or MOSI line.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or rsrtx_InitWithOptions function.
/// HIPAR line/This control selects line.
/// HIPAR frame/This control selects the frame.
/// HIPAR arraySize/Pass the number of values allocated for Data result array.
/// HIPAR data/Data words of the specified frame.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QuerySPIFrameAllData(ViSession instrSession,
                                             ViInt32   serialBus,
                                             ViInt32   line,
                                             ViInt32   frame,
                                             ViInt32   arraySize,
                                             ViInt32   data[],
                                             ViInt32   *returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViInt32* auxData = NULL;
	ViInt32  auxDataLen;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K1"));
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, line, RSRTX_VAL_SPI_MISO, RSRTX_VAL_SPI_MOSI),
			2, "Line");

	if (line == RSRTX_VAL_SPI_MISO)
    {
		snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:SPI:FRAM%ld:DATA:MISO?", serialBus, frame);
    }
	else
	{
		snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:SPI:FRAM%ld:DATA:MOSI?", serialBus, frame);

	}

	checkErr(RsCore_QueryIntegerArray(instrSession, cmd, &auxData, &auxDataLen));
	
	*returnedValues = auxData[0];
	auxDataLen--;

    checkErr(rsrtx_CheckStatus(instrSession));
	checkErr(RsCore_CopyToUserBufferViInt32Array(data, arraySize, auxData + 1, auxDataLen));

Error:
	if (auxData) free(auxData);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Queries the data bytes of the specified frame.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frame/This control selects the frame.
/// HIPAR arraySize/Pass the number of values allocated for Data result array.
/// HIPAR data/Array of decimal values of the data bytes.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryLINFrameAllData(ViSession instrSession,
                                             ViInt32   serialBus,
                                             ViInt32   frame,
                                             ViInt32   arraySize,
                                             ViInt32   data[],
                                             ViInt32   *returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViInt32* auxData = NULL;
	ViInt32  auxDataLen;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K3"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:LIN:FRAM%ld:DATA?", serialBus, frame);
	checkErr(RsCore_QueryIntegerArray(instrSession, cmd, &auxData, &auxDataLen));
	*returnedValues = auxData[0];
	auxDataLen--;

	checkErr(rsrtx_CheckStatus(instrSession));
	checkErr(RsCore_CopyToUserBufferViInt32Array(data, arraySize, auxData + 1, auxDataLen));

Error:
	if (auxData) free(auxData);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Queries the data bytes of the specified frame.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frame/This control selects the frame.
/// HIPAR arraySize/Pass the number of values allocated for Data result array.
/// HIPAR data/Array of decimal values of the data bytes.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryCANFrameAllData(ViSession instrSession,
                                             ViInt32   serialBus,
                                             ViInt32   frame,
                                             ViInt32   arraySize,
                                             ViInt32   data[],
                                             ViInt32   *returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViInt32* auxData = NULL;
	ViInt32  auxDataLen;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K3"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:CAN:FRAM%ld:DATA?", serialBus, frame);
	checkErr(RsCore_QueryIntegerArray(instrSession, cmd, &auxData, &auxDataLen));
	*returnedValues = auxData[0];
	auxDataLen--;

	checkErr(rsrtx_CheckStatus(instrSession));
	checkErr(RsCore_CopyToUserBufferViInt32Array(data, arraySize, auxData + 1, auxDataLen));

Error:
	if (auxData) free(auxData);
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Sets all selected tracks to the middle of the display and scales them
/// HIFN  to full height of the display (8 dovisions). The track waveforms
/// HIFN  overlap.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
ViStatus _VI_FUNC rsrtx_ProtocolAudioTrackWaveformSetToDefault(
							ViSession instrSession,
							ViInt32   serialBus)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_DEFAULT,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_DEFAULT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Arranges the selected tracks vertically, one above the other. The
/// HIFN  track waveforms do not overlap.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
ViStatus _VI_FUNC rsrtx_ProtocolAudioTrackWaveformSetToScreen(
							ViSession instrSession,
							ViInt32   serialBus)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_SCREEN,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_PROTOCOL_AUDIO_TRACK_WAVEFORM_SET_TO_SCREEN, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures the UART trigger source
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR triggerSource/Configures the UART trigger source
ViStatus _VI_FUNC rsrtx_ConfigureUARTTriggerSource(ViSession instrSession,
                                                   ViInt32   triggerSource)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_TRIGGER_SOURCE, triggerSource),
    		2, "Trigger Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the logic levels of the bus. The idle state corresponds to a
/// HIFN  logic 1, and the start bit to a logic 0. Alternative command for
/// HIFN  RSRTX_ATTR_PROTOCOL_UART_POLARITY
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_IDLE_STATE_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:UART:POLarity
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR idleStatePolarity/Defines the logic levels of the bus. The idle state corresponds to a
/// HIPAR idleStatePolarity/logic 1, and the start bit to a logic 0.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolUARTIdleStatePolarity(
							ViSession instrSession,
							ViInt32   serialBus,
							ViInt32   idleStatePolarity)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_IDLE_STATE_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_IDLE_STATE_POLARITY, idleStatePolarity),
			3, "Idle State Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Return the number of decoded frames on the data line.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the channel.
/// HIPAR count/Return the number of decoded frames on the data line.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTFrameCount(ViSession instrSession,
                                                    ViInt32   serialBus,
                                                    ViInt32*  count)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_FRAME_COUNT,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_FRAME_COUNT, count),
    		3, "count");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the number of words in the specified frame.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR count/Returns the number of words in the specified frame.
/// HIPAR frame/This control selects the frame.
/// HIPAR serialBus/This control selects the channel.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTWordCount(ViSession instrSession,
                                                   ViInt32   serialBus,
                                                   ViInt32   frame,
                                                   ViInt32   *count)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_WORD_COUNT,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, frame),
			3, "frame");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_COUNT, count),
    		4, "count");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the status of the specified frame.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_FRAME_STATE
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_FRAME_START
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_FRAME_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:UART:FRAMe<n>:STATe?
/// HIFN     BUS<b>:UART:FRAMe<n>:STARt?
/// HIFN     BUS<b>:UART:FRAMe<n>:STOP?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR frame/This control selects the frame.
/// HIPAR frameState/Returns the statue of the specified frame.
/// HIPAR frameStart/Return the start time of the specified frame.
/// HIPAR frameEnd/Return the end time of the specified frame.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTFrameSettings(ViSession instrSession,
                                                       ViInt32   serialBus,
                                                       ViInt32   frame,
                                                       ViInt32*  frameState,
                                                       ViReal64* frameStart,
                                                       ViReal64* frameEnd)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_FRAME_STATE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, frame),
			3, "Frame");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_FRAME_STATE, frameState),
    		4, "Frame State");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_FRAME_START, frameStart),
			5, "Frame Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_FRAME_END, frameEnd),
			6, "Frame End");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the status of the specified frame.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_STATE
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_START
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:UART:RX:FRAMe<n>:STATe?
/// HIFN     BUS<b>:UART:RX:FRAMe<n>:STARt?
/// HIFN     BUS<b>:UART:RX:FRAMe<n>:STOP?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR frame/This control selects the frame.
/// HIPAR rxFrameState/Returns the status of the specified frame.
/// HIPAR rxFrameStart/Return the start time of the specified frame.
/// HIPAR rxFrameEnd/Return the end time of the specified frame.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTRxFrameSettings(ViSession instrSession,
                                                         ViInt32   serialBus,
                                                         ViInt32   frame,
                                                         ViInt32*  rxFrameState,
                                                         ViReal64* rxFrameStart,
                                                         ViReal64* rxFrameEnd)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_STATE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, frame),
			3, "frame");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_STATE, rxFrameState),
    		4, "RX Frame State");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_START, rxFrameStart),
			5, "RX Frame Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_RX_FRAME_END, rxFrameEnd),
			6, "RX Frame End");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the status of the specified frame.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_STATE
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_START
/// HIFN     RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS:UART:TX:FRAMe:STATe?
/// HIFN     BUS:UART:TX:FRAMe:STARt?
/// HIFN     BUS:UART:TX:FRAMe:STOP?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR frame/This control selects the frame.
/// HIPAR txFrameState/Returns the status of the specified frame.
/// HIPAR txFrameStart/Return the start time of the specified frame.
/// HIPAR txFrameEnd/Return the end time of the specified frame.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTTxFrameSettings(ViSession instrSession,
                                                         ViInt32   serialBus,
                                                         ViInt32   frame,
                                                         ViInt32*  txFrameState,
                                                         ViReal64* txFrameStart,
                                                         ViReal64* txFrameEnd)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_STATE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, frame),
			3, "frame");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_STATE, txFrameState),
    		4, "TX Frame State");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_START, txFrameStart),
			5, "TX Frame Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_TX_FRAME_END, txFrameEnd),
			6, "TX Frame End");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the word values in the specified frame.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR frame/This control selects the frame.
/// HIPAR word/This control selects the word.
/// HIPAR value/Returns the value of words in the specified frame.
/// HIPAR start/Returns the start time of words in the specified frame.
/// HIPAR end/Returns the end time of words in the specified frame.
/// HIPAR status/Returns the state of words in the specified frame.
/// HIPAR source/Returns the value of words in the specified frame.
ViStatus _VI_FUNC rsrtx_QueryProtocolUARTWordValue(ViSession instrSession,
                                                   ViInt32   serialBus,
                                                   ViInt32   frame,
                                                   ViInt32   word,
                                                   ViInt32*  value,
                                                   ViReal64* start,
                                                   ViReal64* end,
                                                   ViInt32*  status,
                                                   ViInt32*  source)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_UART_WORD_COUNT,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, frame),
			3, "frame");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_SELECTED_WORD, word),
			4, "word");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_VALUE, value),
    		5, "value");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_START, start),
			6, "start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_END, end),
			7, "end");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_ENABLED, status),
			8, "status");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_UART_WORD_SOURCE, source),
			9, "source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the input channel of the chip select line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SPI_CS_SOURCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS:SPI:CS:SOURce
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSPICSSource/Selects the input channel of the chip select line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPICSSource(ViSession instrSession,
                                                     ViInt32   serialBus,
                                                     ViInt32   protocolSPICSSource)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SPI_CS_SOURCE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SPI_CS_SOURCE, protocolSPICSSource),
			2, "Protocol SPI CS Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects if transmitted data is high active (high = 1) or low active
/// HIFN  (low = 1) on the MOSI/MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SPI_MOSI_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SPI:MOSI:POLarity
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSPIMOSIPolarity/Selects if transmitted data is high active (high = 1) or low active
/// HIPAR protocolSPIMOSIPolarity/(low = 1) on the MOSI/MISO line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMOSIPolarity(ViSession instrSession,
                                                         ViInt32   serialBus,
                                                         ViInt32   protocolSPIMOSIPolarity)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SPI_MOSI_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SPI_MOSI_POLARITY, protocolSPIMOSIPolarity),
    		3, "Protocol SPI MOSI Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the input channel of the optional MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SPI_MISO_SOURCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SPI:MISO:SOURce
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSPIMISOSource/Selects the input channel of the optional MISO line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMISOSource(ViSession instrSession,
                                                       ViInt32   serialBus,
                                                       ViInt32   protocolSPIMISOSource)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SPI_MISO_SOURCE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SPI_MISO_SOURCE, protocolSPIMISOSource),
    		3, "Protocol SPI MISO Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects whether transmitted data is high active (high = 1) or low
/// HIFN  active (low = 1) on the MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SPI_MISO_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SPI:MISO:POLarity
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSPIMISOPolarity/Selects whether transmitted data is high active (high = 1) or low
/// HIPAR protocolSPIMISOPolarity/active (low = 1) on the MISO line
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSPIMISOPolarity(ViSession instrSession,
                                                         ViInt32   serialBus,
                                                         ViInt32   protocolSPIMISOPolarity)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SPI_MISO_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SPI_MISO_POLARITY, protocolSPIMISOPolarity),
    		3, "Protocol SPI MISO Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the input channel of the optional MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SSPI_MISO_SOURCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SSPI:MISO:SOURce
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSSPIMISOSource/Selects the input channel of the optional MISO line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMISOSource(ViSession instrSession,
                                                        ViInt32   serialBus,
                                                        ViInt32   protocolSSPIMISOSource)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SSPI_MISO_SOURCE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SSPI_MISO_SOURCE, protocolSSPIMISOSource),
    		3, "Protocol SSPI MISO Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects if transmitted data is high active (high = 1) or low active
/// HIFN  (low = 1) on the MOSI/MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SSPI_MOSI_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SSPI:MOSI:POLarity
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSSPIMOSIPolarity/Selects if transmitted data is high active (high = 1) or low active
/// HIPAR protocolSSPIMOSIPolarity/(low = 1) on the MOSI/MISO line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMOSIPolarity(ViSession instrSession,
                                                          ViInt32   serialBus,
                                                          ViInt32   protocolSSPIMOSIPolarity)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SSPI_MOSI_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SSPI_MOSI_POLARITY, protocolSSPIMOSIPolarity),
    		3, "Protocol SSPI MOSI Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects whether transmitted data is high active (high = 1) or low
/// HIFN  active (low = 1) on the MISO line.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PROTOCOL_SSPI_MISO_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BUS<b>:SSPI:MISO:POLarity
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR protocolSSPIMISOPolarity/Selects whether transmitted data is high active (high = 1) or low
/// HIPAR protocolSSPIMISOPolarity/active (low = 1) on the MISO line.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolSSPIMISOPolarity(ViSession instrSession,
                                                          ViInt32   serialBus,
                                                          ViInt32   protocolSSPIMISOPolarity)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_SSPI_MISO_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_SSPI_MISO_POLARITY, protocolSSPIMISOPolarity),
    		3, "Protocol SSPI MISO Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables infinite Inter Message Gap Time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR infinite/Enables infinite Inter Message Gap Time.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDInterMessageGapTimeInfinite(
							ViSession instrSession,
							ViInt32   serialBus,
							ViBoolean infinite)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_INFINITE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_INFINITE, infinite),
    		3, "infinite");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures maximum Inter Message Gap Time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR minimum/Configures minimum Inter Message Gap Time.
/// HIPAR maximum/Configures maximum Inter Message Gap Time.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDInterMessageGapTime(
							ViSession instrSession,
							ViInt32   serialBus,
							ViReal64  minimum,
							ViReal64  maximum)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_MINIMUM,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_MINIMUM, minimum),
    		3, "minimum");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_INTER_MESSAGE_GAP_TIME_MAXIMUM, maximum),
			4, "maximum");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables infinite response time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR infinite/Enables infinite response time.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDResponseTimeInfinite(
							ViSession instrSession,
							ViInt32   serialBus,
							ViBoolean infinite)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_INFINITE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_INFINITE, infinite),
    		3, "infinite");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures response time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR minimum/Configures minimum response time.
/// HIPAR maximum/Configures maximum response time.
ViStatus _VI_FUNC rsrtx_ConfigureProtocolMILSTDResponseTime(ViSession instrSession,
                                                            ViInt32   serialBus,
                                                            ViReal64  minimum,
                                                            ViReal64  maximum)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_MINIMUM,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_MINIMUM, minimum),
    		3, "minimum");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_MILSTD_RESPONSE_TIME_MAXIMUM, maximum),
			4, "maximum");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This attribute select the trigger mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/This control select the trigger mode.
ViStatus _VI_FUNC rsrtx_ConfigureMILSTDTriggerMode(ViSession instrSession,
                                                   ViInt32   mode)
{
 	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_MILSTD_TRIGGER_MODE, mode),
    		2, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures trigger frame.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frame/Configures trigger frame.
ViStatus _VI_FUNC rsrtx_ConfigureMILSTDTriggerFrame(ViSession instrSession,
                                                    ViInt32   frame)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_MILSTD_TRIGGER_FRAME, frame),
    		2, "Frame");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the channel for the signal source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR source/Sets the channel for the signal source.
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Source(ViSession instrSession,
                                                ViInt32   serialBus,
                                                ViInt32   source)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_SOURCE,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_SOURCE, source),
    		3, "Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function selects the wire on which the bus signal is measured.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR polarity/Sets the wire on which the bus signal is measured.
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Polarity(ViSession instrSession,
                                                  ViInt32   serialBus,
                                                  ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_POLARITY,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_POLARITY, polarity),
    		3, "Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the bit rate.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR bitRateMode/Sets the bit rate mode to high or low speed.
/// HIPAR bitRateValue/Sets the number of transmitted bits per second.
ViStatus _VI_FUNC rsrtx_ConfigureARINC429BitRate(ViSession instrSession,
                                                 ViInt32   serialBus,
                                                 ViInt32   bitRateMode,
                                                 ViReal64  bitRateValue)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_BIT_RATE_MODE,
			"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_BIT_RATE_MODE, bitRateMode),
			3, "Bit Rate Mode");

	if(bitRateMode == RSRTX_VAL_ARINC429_BIT_RATE_MODE_USER)
	{
		viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_BIT_RATE, bitRateValue),
				4, "Bit Rate Value");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures threshold values used for digitization of the signal.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/This control selects the serial bus.
/// HIPAR thresholdHigh/Sets the high threshold level of the signal.
/// HIPAR thresholdLow/Sets the lower threshold level of the signal.
ViStatus _VI_FUNC rsrtx_ConfigureARINC429Threshold(ViSession instrSession,
                                                   ViInt32   serialBus,
                                                   ViReal64  thresholdHigh,
                                                   ViReal64  thresholdLow)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_THRESHOLD_HIGH,
			"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_THRESHOLD_HIGH, thresholdHigh),
			3, "Threshold High");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_THRESHOLD_LOW, thresholdLow),
			4, "Threshold Low");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the trigger type for ARINC 429 analysis.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects the type of trigger.
ViStatus _VI_FUNC rsrtx_ConfigureARINC429TriggerType(ViSession instrSession,
                                                     ViInt32   type)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_PROTOCOL_ARINC429_TRIGGER_TYPE, type),
    		2, "Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of decoded words.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/Selects the serial bus.
/// HIPAR count/Returns the number of decoded words.
ViStatus _VI_FUNC rsrtx_QueryARINC429WordCount(ViSession instrSession,
                                               ViInt32   serialBus,
                                               ViInt32   *count)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_COUNT,
			"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "SerialBus");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_COUNT, count),
			3, "Count");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Queries the overall state of the word.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/Selects the serial bus.
/// HIPAR word/This control selects the word.
/// HIPAR status/Returns the status of the specified word.
/// HIPAR start/Returns the start time of the specified word.
/// HIPAR stop/Returns the start time of the specified word.
/// HIPAR pattern/Returns all 32 bits of a data word as decimal value.
/// HIPAR SDI/Returns the source/destination identifier (SDI) bits of the specified word.
/// HIPAR SSM/Returns the source/destination identifier (SSM) bits of the specified word.
ViStatus _VI_FUNC rsrtx_QueryARINC429Status(ViSession instrSession,
                                            ViInt32   serialBus,
                                            ViInt32   word,
                                            ViInt32   *status,
                                            ViReal64  *start,
                                            ViReal64  *stop,
                                            ViInt32   *pattern,
                                            ViInt32   *SDI,
                                            ViInt32   *SSM)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_STATUS,
    		"SerialBus", serialBus - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "SerialBus");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_ARINC429_SELECTED_WORD, word),
			3, "Word");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_STATUS, status),
    		4, "Status");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_START, start),
			5, "Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_STOP, stop),
			6, "Stop");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_PATTERN, pattern),
			7, "Pattern");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_SDI, SDI),
			8, "SDI");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_PROTOCOL_ARINC429_WORD_SSM, SSM),
			9, "SSM");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Return the data bytes of the specified word.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsscope_init or
/// HIPAR instrSession/rsscope_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR serialBus/Selects the serial bus.
/// HIPAR word/This control selects the word.
/// HIPAR arraySize/Returns the status of the specified word.
/// HIPAR data/Returns the start time of the specified word.
/// HIPAR returnedValues/Returns the start time of the specified word.
ViStatus _VI_FUNC rsrtx_QueryARINC429AllData(ViSession instrSession,
                                             ViInt32   serialBus,
                                             ViInt32   word,
                                             ViInt32   arraySize,
                                             ViInt32   data[],
                                             ViInt32   *returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViInt32* auxData = NULL;
	ViInt32  auxDataLen;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_ARINC429_SELECTED_WORD, word),
			3, "Word");

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "BUS%ld:ARIN:WORD%ld:DATA?", serialBus, word);
	checkErr(RsCore_QueryIntegerArray(instrSession, cmd, &auxData, &auxDataLen));
	*returnedValues = auxData[0];
	auxDataLen--;
	checkErr(rsrtx_CheckStatus(instrSession));
	checkErr(RsCore_CopyToUserBufferViInt32Array(data, arraySize, auxData + 1, auxDataLen));

Error:
	if (auxData) free(auxData);
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function prints an image of the display to the printer or saves
/// HIFN  an image to a file or the clipboard.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR fileName/Defines the file name when an image of the display is stored to
/// HIPAR fileName/a file rather than printed to a printer using the rsrtx_HardcopyPrint.
/// HIPAR deviceDestination/This control selects the printer output medium (Disk, Printer or
/// HIPAR deviceDestination/Clipboard).
/// HIPAR includeMenuInScreenshot/Includes the menu in the screenshot. If OFF (no menu), the menu
/// HIPAR includeMenuInScreenshot/is clipped off, and date and time are shown instead of the menu
/// HIPAR includeMenuInScreenshot/name.
/// HIPAR deviceLanguageOutputFormat/Defines the file format for the image of the display.
ViStatus _VI_FUNC rsrtx_ConfigureHardcopySettings(ViSession instrSession,
                                                  ViString  fileName,
                                                  ViInt32   deviceDestination,
                                                  ViBoolean includeMenuInScreenshot,
                                                  ViInt32   deviceLanguageOutputFormat)
{
	ViStatus error = VI_SUCCESS;
	         includeMenuInScreenshot;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_HARDCOPY_FILE_NAME, fileName),
    		2, "File Name");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_DEVICE_DESTINATION, deviceDestination),
			3, "Device Destination");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_DEVICE_LANGUAGE_OUTPUT_FORMAT, deviceLanguageOutputFormat),
			5, "Device Language Output Format");

Error:
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function prints an image of the display to the printer or saves
/// HIFN  an image to a file or the clipboard.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_HardcopyPrint(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, NULL, RSRTX_ATTR_HARDCOPY_PRINT, NULL),
    		1, "Session");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function defines an instrument name.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR name/Defines the name.
ViStatus _VI_FUNC rsrtx_ConfigureInstrumentName(ViSession instrSession,
                                                ViString  name)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_INSTRUMENT_NAME, name),
    		2, "Name");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the file format for the image of the display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR format/Defines the file format for the image of the display.
ViStatus _VI_FUNC rsrtx_ConfigureHardcopyOutputFormat(ViSession instrSession,
                                                      ViInt32   format)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_OUTPUT_FORMAT, format),
    		2, "format");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  If ON, open dialog boxes and menus are closed before the screenshot is
/// HIFN  saved. Thus, the waveforms and results are always visible on the
/// HIFN  screenshot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_HARDCOPY_CLOSE_DIALOGS
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     HCOPy:CWINdow
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR closeDialogs/If ON, open dialog boxes and menus are closed before the screenshot is
/// HIPAR closeDialogs/saved. Thus, the waveforms and results are always visible on the
/// HIPAR closeDialogs/screenshot.
ViStatus _VI_FUNC rsrtx_CloseHardcopyDialogs(ViSession instrSession,
                                             ViBoolean closeDialogs)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_HARDCOPY_CLOSE_DIALOGS, closeDialogs),
    		2, "Close Dialogs");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the data of the image file.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR format/Defines the file format for the image of the display.
/// HIPAR fileName/Returns the data of the image file.
ViStatus _VI_FUNC rsrtx_QueryHardcopyData(ViSession instrSession,
                                          ViInt32   format,
                                          ViString  fileName)
{
	ViStatus error = VI_SUCCESS;
	ViUInt32 old_timeout = 0;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_OUTPUT_FORMAT, format),
    		3, "Hardcopy Format");

	checkErr(RsCore_GetVisaTimeout(instrSession, &old_timeout));
	checkErr(RsCore_SetVisaTimeout(instrSession, 100000));

    viCheckParm(RsCore_InvalidNullPointer(instrSession, fileName), 3, "File Name");
    checkErr(RsCore_QueryBinaryDataBlockToFile(instrSession, "HCOPY:DATA?", fileName, RS_VAL_TRUNCATE));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	if (old_timeout > 0)
		(void)RsCore_SetVisaTimeout(instrSession, old_timeout);

	(void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Queries size of the page.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR x/Queries X size of the page.
/// HIPAR y/Queries Y size of the page.
ViStatus _VI_FUNC rsrtx_QueryHardcopyPageSize(ViSession instrSession,
                                              ViInt32*  x,
                                              ViInt32*  y)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_PAGE_SIZE_X, x),
    		2, "X");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_HARDCOPY_PAGE_SIZE_Y, y),
			3, "Y");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the value of a ViInt32 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rsrtx_SetAttributeViInt32(ViSession instrSession,
                                            ViString  channelName,
                                            ViUInt32  attributeId,
                                            ViInt32   value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_SetAttributeViInt32(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function sets the value of a ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rsrtx_SetAttributeViReal64(ViSession instrSession,
                                             ViString  channelName,
                                             ViUInt32  attributeId,
                                             ViReal64  value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_SetAttributeViReal64(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function sets the value of a ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rsrtx_SetAttributeViString(ViSession instrSession,
                                             ViString  channelName,
                                             ViUInt32  attributeId,
                                             ViString  value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_SetAttributeViString(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function sets the value of a ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rsrtx_SetAttributeViBoolean(ViSession instrSession,
                                              ViString  channelName,
                                              ViUInt32  attributeId,
                                              ViBoolean value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_SetAttributeViBoolean(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function sets the value of a ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rsrtx_SetAttributeViSession(ViSession instrSession,
                                              ViString  channelName,
                                              ViUInt32  attributeId,
                                              ViSession value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_SetAttributeViSession(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the value of a ViInt32 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a
/// HIPAR value/ViInt32 variable.
ViStatus _VI_FUNC rsrtx_GetAttributeViInt32(ViSession instrSession,
                                            ViString  channelName,
                                            ViUInt32  attributeId,
                                            ViInt32   *value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);
	error = RsCore_GetAttributeViInt32(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the value of a ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a
/// HIPAR value/ViReal64 variable.
ViStatus _VI_FUNC rsrtx_GetAttributeViReal64(ViSession instrSession,
                                             ViString  channelName,
                                             ViUInt32  attributeId,
                                             ViReal64  *value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_GetAttributeViReal64(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the value of a ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR bufSize/Pass the number of bytes in the ViChar array you specify for the
/// HIPAR bufSize/Attribute Value parameter.
/// HIPAR value/The buffer in which the function returns the current value of the
/// HIPAR value/attribute.  The buffer must be of type ViChar and have at least as many
/// HIPAR value/bytes as indicated in the Buffer Size parameter.
ViStatus _VI_FUNC rsrtx_GetAttributeViString(ViSession instrSession,
                                             ViString  channelName,
                                             ViUInt32  attributeId,
                                             ViInt32   bufSize,
                                             ViChar    value[])
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_GetAttributeViString(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, bufSize,
	                                    value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the value of a ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a
/// HIPAR value/ViBoolean variable.
ViStatus _VI_FUNC rsrtx_GetAttributeViBoolean(ViSession instrSession,
                                              ViString  channelName,
                                              ViUInt32  attributeId,
                                              ViBoolean *value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_GetAttributeViBoolean(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the value of a ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the
/// HIPAR channelName/attribute is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a
/// HIPAR value/ViSession variable.
ViStatus _VI_FUNC rsrtx_GetAttributeViSession(ViSession instrSession,
                                              ViString  channelName,
                                              ViUInt32  attributeId,
                                              ViSession *value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_GetAttributeViSession(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function checks the validity of a value you specify for a ViInt32
/// HIFN  attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute
/// HIPAR channelName/is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the
/// HIPAR value/attribute.
ViStatus _VI_FUNC rsrtx_CheckAttributeViInt32(ViSession instrSession,
                                              ViString  channelName,
                                              ViUInt32  attributeId,
                                              ViInt32   value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_CheckAttributeViInt32(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function checks the validity of a value you specify for a
/// HIFN  ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute
/// HIPAR channelName/is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the
/// HIPAR value/attribute.
ViStatus _VI_FUNC rsrtx_CheckAttributeViReal64(ViSession instrSession,
                                               ViString  channelName,
                                               ViUInt32  attributeId,
                                               ViReal64  value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_CheckAttributeViReal64(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function checks the validity of a value you specify for a
/// HIFN  ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute
/// HIPAR channelName/is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the
/// HIPAR value/attribute.
ViStatus _VI_FUNC rsrtx_CheckAttributeViString(ViSession instrSession,
                                               ViString  channelName,
                                               ViUInt32  attributeId,
                                               ViString  value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_CheckAttributeViString(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function checks the validity of a value you specify for a
/// HIFN  ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute
/// HIPAR channelName/is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the
/// HIPAR value/attribute.
ViStatus _VI_FUNC rsrtx_CheckAttributeViBoolean(ViSession instrSession,
                                                ViString  channelName,
                                                ViUInt32  attributeId,
                                                ViBoolean value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_CheckAttributeViBoolean(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function checks the validity of a value you specify for a
/// HIFN  ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute
/// HIPAR channelName/is not channel-based, then pass NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the
/// HIPAR value/attribute.
ViStatus _VI_FUNC rsrtx_CheckAttributeViSession(ViSession instrSession,
                                                ViString  channelName,
                                                ViUInt32  attributeId,
                                                ViSession value)
{
	ViStatus error = VI_SUCCESS;

	(void)RsCore_LockSession(instrSession);

	error = RsCore_CheckAttributeViSession(instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function returns the repeated capability id(s) that belongs
/// HIFN to the attribute you specify. More then one id is listed in
/// HIFN comma separated string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR attributeID/Pass the ID of an attribute.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id(s) parameter.
/// HIPAR repeatedCapabilityIds/The buffer in which the function returns the repeated capability id(s) belonging to the attribute.
ViStatus _VI_FUNC rsrtx_GetAttributeRepeatedCapabilityIds(ViSession instrSession,
                                                          ViUInt32  attributeID,
                                                          ViInt32   bufferSize,
                                                          ViChar    _VI_FAR repeatedCapabilityIds[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, bufferSize, 1, RS_MAX_SHORT_MESSAGE_BUF_SIZE),
			3, "Buffer Size");

	checkErr(RsCore_GetAttributeRepCapNameIds(instrSession, attributeID, bufferSize, repeatedCapabilityIds));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function returns the repeated capability name(s) that
/// HIFN belongs to the attribute and single repeated capability id you
/// HIFN may specify. More then one name is listed in comma separated
/// HIFN string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR attributeID/Pass the ID of an attribute.
/// HIPAR repeatedCapabilityId/If the attribute applies to a repeated capability such as a trace, this parameter defines the Id of the repeated capability on which to query repeated capability id name(s).
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id Name(s) parameter.
/// HIPAR repeatedCapabilityIdNames/The buffer in which the function returns the repeated capability id name(s) belonging to the attribute.
ViStatus _VI_FUNC rsrtx_GetAttributeRepeatedCapabilityIdNames(
							ViSession instrSession,
							ViUInt32  attributeID,
							ViString  repeatedCapabilityId,
							ViInt32   bufferSize,
							ViChar    _VI_FAR repeatedCapabilityIdNames[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, bufferSize, 1, RS_MAX_SHORT_MESSAGE_BUF_SIZE),
			4, "Buffer Size");

	checkErr(RsCore_GetAttributeRepCapNamesAll(instrSession,
        attributeID,
        repeatedCapabilityId,
        bufferSize,
        repeatedCapabilityIdNames));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}
/// HIFN Function used by Hi-level functions to obtain a repCap name from:
/// HIFN - attributeID
/// HIFN - repCapNameID
/// HIFN - 0-based index in the repCapNames
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR repCapNameId/RepCap Name ID.
/// HIPAR index/Zero based index in the repCapNames.
/// HIPAR bufferSize/Pass the number of bytes in the string you allocate for the repCapName.
/// HIPAR repCapName/String returning RepCap name
ViStatus _VI_FUNC rsrtx_GetAttributeRepCapName(ViSession instrSession,
                                               ViUInt32  attributeId,
                                               ViString  repCapNameId,
                                               ViInt32   index,
                                               ViInt32   bufferSize,
                                               ViChar    repCapName[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_GetAttributeRepCapName(instrSession, attributeId, repCapNameId, index, bufferSize, repCapName));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures settings for waveform label.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MATH_WAVEFORM_LABEL
/// HIFN     RSRTX_ATTR_MATH_WAVEFORM_LABEL_STATE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:LABel
/// HIFN     CALCulate:MATH<m>:LABel:STATe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR waveformLabel/Defines a label for the specified math waveform (equation), which is
/// HIPAR waveformLabel/shown at the waveform.
/// HIPAR labelState/Activates the diplay of the label that is defined with
/// HIPAR labelState/RSRTX_ATTR_MATH_WAVEFORM_LABEL.
ViStatus _VI_FUNC rsrtx_ConfigureMathWaveformLabel(ViSession instrSession,
                                                   ViInt32   mathNumber,
                                                   ViString  waveformLabel,
                                                   ViBoolean labelState)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, mathNumber, 1, 5),
    		2, "Math Number");
	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_WAVEFORM_LABEL,
			"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "Math Number");

    viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_LABEL, waveformLabel),
    		3, "Math Waveform Color");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_LABEL_STATE, labelState),
			4, "Label State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the color of the indicated math waveform.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MATH_WAVEFORM_COLOR
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:WCOLor
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR mathWaveformColor/Sets the color of the indicated math waveform.
ViStatus _VI_FUNC rsrtx_ConfigureMathWaveformColor(ViSession instrSession,
                                                   ViInt32   mathNumber,
                                                   ViInt32   mathWaveformColor)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, mathNumber, 1, 5),
    		2, "Math Number");
	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_WAVEFORM_COLOR,
			"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "Math Number");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_COLOR, mathWaveformColor),
    		3, "Math Waveform Color");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Performs FFT calculation for the full frequency span.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
ViStatus _VI_FUNC rsrtx_ConfigureFFTFrequencySpanFull(ViSession instrSession,
                                                      ViInt32   mathNumber)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, mathNumber, 1, 5),
    		2, "Math Number");
	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_FFT_FULL_SPAN,
			"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "Math Number");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_FFT_FULL_SPAN, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the rising or falling edge as a reference for each measurement.
/// HIFN  The setting helps to determine values in terms of the power stage
/// HIFN  switching state. For unipolar souces, the on edge is the rising edge,
/// HIFN  and the off edge is the falling edge. In the bipolar case, all
/// HIFN  transitions are inverted for the negative branch. For positive pulses,
/// HIFN  the rising edge is the on edge, and for negative pulses, the falling
/// HIFN  edge is the on edge.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MATH_TRACK_EDGE_POLARITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:TRACk:EDGE
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR edgePolarity/Sets the rising or falling edge as a reference for each measurement.
/// HIPAR edgePolarity/The setting helps to determine values in terms of the power stage
/// HIPAR edgePolarity/switching state. For unipolar souces, the on edge is the rising edge,
/// HIPAR edgePolarity/and the off edge is the falling edge. In the bipolar case, all
/// HIPAR edgePolarity/transitions are inverted for the negative branch. For positive pulses,
/// HIPAR edgePolarity/the rising edge is the on edge, and for negative pulses, the falling
/// HIPAR edgePolarity/edge is the on edge.
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackEdgePolarity(ViSession instrSession,
                                                       ViInt32   mathNumber,
                                                       ViBoolean edgePolarity)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_TRACK_EDGE_POLARITY,
    		"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_MATH_TRACK_EDGE_POLARITY, edgePolarity),
			3, "Edge Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Available for bipolar signals. Considers the effect of the double
/// HIFN  pulse, which arises due to the inversion.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MATH_TRACK_DOUBLE_PULSE_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:TRACk:DPULse[:ENABle]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR doublePulseEnable/Available for bipolar signals. Considers the effect of the double
/// HIPAR doublePulseEnable/pulse, which arises due to the inversion.
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackDoublePulseEnable(ViSession instrSession,
                                                            ViInt32   mathNumber,
                                                            ViBoolean doublePulseEnable)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_TRACK_DOUBLE_PULSE_ENABLE,
    		"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_MATH_TRACK_DOUBLE_PULSE_ENABLE, doublePulseEnable),
			3, "Double Pulse Enabled");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the track threshold settings.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_MATH_TRACK_THRESHOLD_HYSTERESIS
/// HIFN     RSRTX_ATTR_MATH_TRACK_THRESHOLD_LOWER
/// HIFN     RSRTX_ATTR_MATH_TRACK_THRESHOLD_UPPER
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     CALCulate:MATH<m>:TRACk:THReshold:HYSTeresis
/// HIFN     CALCulate:MATH<m>:TRACk:THReshold:LOWer
/// HIFN     CALCulate:MATH<m>:TRACk:THReshold[:UPPer]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR hysteresis/Sets the hysteresis for correct edge detection.
/// HIPAR thresholdLower/Sets the lower level for bipolar track sources, which determines the
/// HIPAR thresholdLower/crossing points on negative pulses.
/// HIPAR thresholdUpper/Sets the threshold for unipolar track sources, or the upper level for
/// HIPAR thresholdUpper/bipolar sources. The signal is measured at the crossing points of the
/// HIPAR thresholdUpper/signal with the threshold.
ViStatus _VI_FUNC rsrtx_ConfigureMathTrackThresholdSettings(ViSession instrSession,
                                                            ViInt32   mathNumber,
                                                            ViReal64  hysteresis,
                                                            ViReal64  thresholdLower,
                                                            ViReal64  thresholdUpper)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_TRACK_THRESHOLD_HYSTERESIS,
    		"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_TRACK_THRESHOLD_HYSTERESIS, hysteresis),
			3, "Hysteresis");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_TRACK_THRESHOLD_LOWER, thresholdLower),
			4, "Threshold Lower");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_TRACK_THRESHOLD_UPPER, thresholdUpper),
			5, "Threshold Upper");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines a label for the indicated reference waveform.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_REFERENCE_WAVEFORM_LABEL
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     REFCurve<m>:LABel
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referenceNumber/Selects the reference waveform.
/// HIPAR waveformLabel/Defines a label for the indicated reference waveform.
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformLabel(ViSession instrSession,
                                                        ViInt32   referenceNumber,
                                                        ViString  waveformLabel)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_LABEL,
    		"ReferenceWfm", referenceNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Number");

	viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_LABEL, waveformLabel),
			3, "Waveform Label");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects a color for the reference waveform. The default color is
/// HIFN  white. You can select another monochrome color, or a color scale.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_REFERENCE_WAVEFORM_COLOR
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     REFCurve<m>:WCOLor
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referenceNumber/Selects the reference waveform.
/// HIPAR waveformColor/Selects a color for the reference waveform. The default color is
/// HIPAR waveformColor/white. You can select another monochrome color, or a color scale.
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformColor(ViSession instrSession,
                                                        ViInt32   referenceNumber,
                                                        ViInt32   waveformColor)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_COLOR,
    		"ReferenceWfm", referenceNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Number");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_COLOR, waveformColor),
    		3, "Waveform Color");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects the source waveform to be used as a reference.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Selects the source waveform to be used as a reference.
ViStatus _VI_FUNC rsrtx_ConfigureReferenceWaveformSource(ViSession instrSession,
                                                         ViInt32   referenceNumber,
                                                         ViInt32   source)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_SOURCE,
    		"ReferenceWfm", referenceNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Number");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_SOURCE, source),
    		3, "source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Copies the selected source waveform with all its settings to the
/// HIFN  memory of the reference waveform
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referenceNumber/Selects the reference waveform.
ViStatus _VI_FUNC rsrtx_UpdateReferenceWaveformWithSelectedSource(
							ViSession instrSession,
							ViInt32   referenceNumber)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_UPDATE,
    		"ReferenceWfm", referenceNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Number");

    checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_UPDATE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Loads or saves the reference waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referenceWfm/Selects the reference waveform.
/// HIPAR fileName/DDefines the file name.
/// HIPAR operation/This control selects the type of waveform operation to be performed.
ViStatus _VI_FUNC rsrtx_ReferenceWaveformFileOperations(ViSession instrSession,
                                                        ViInt32   referenceWfm,
                                                        ViInt32   operation,
                                                        ViString  fileName)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_LOAD_FROM_FILE,
    		"ReferenceWfm", referenceWfm - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Number");

    switch (operation)
    {
        case RSRTX_VAL_WAV_LOAD_CFG:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_LOAD_CONFIGURATION, NULL),
            		1, "Reference Waveform");
        break;

        case RSRTX_VAL_WAV_LOAD:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_LOAD_FROM_FILE, fileName),
            		3, "File Name");
        break;

        case RSRTX_VAL_WAV_SAVE:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_SAVE_TO_FILE, fileName),
            		3, "File Name");
        break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, operation), 4, "Operation");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Activates the mathematics function and displays the resulting math
/// HIFN  waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Activates the mathematics function and displays the resulting math
/// HIPAR state/waveform.
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformState(ViSession instrSession,
                                                         ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_ENABLED, state),
    		2, "state");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the vertical position of the math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR position/Sets the vertical position of the math waveform.
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformPosition(ViSession instrSession,
                                                            ViReal64  position)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_POSITION, position),
    		2, "position");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the vertical scale of the math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR verticalScale/Sets the vertical scale of the math waveform.
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformVerticalScale(
							ViSession instrSession,
							ViReal64  verticalScale)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_VERTICAL_SCALE, verticalScale),
    		2, "Vertical Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the operation that calculates the math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR operation/Defines the operation that calculates the math waveform.
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformOperation(ViSession instrSession,
                                                             ViInt32   operation)
{
 	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_OPERATION, operation),
    		2, "Operation");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Defines the first and the second source for the mathematical operation
/// HIFN  (operands). The sources can be any active analog channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source1/Defines the first source for the mathematical operation (operands).
/// HIPAR source2/Defines the the second source for the mathematical operation
/// HIPAR source2/(operands).
ViStatus _VI_FUNC rsrtx_ConfigureSimpleMathWaveformSource(ViSession instrSession,
                                                          ViInt32   source1,
                                                          ViInt32   source2)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_SOURCE,
    		"SourceNumber", source1 - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "source1");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_SOURCE, source2),
    		2, "source2");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates an acquisition on the channels that you enable
/// HIFN  with the rsrtx_ConfigureChannel function.  It then waits for the
/// HIFN  acquisition to complete, and returns the waveform for the channel you
/// HIFN  specify.  You call the rsrtx_FetchWaveform function to obtain the
/// HIFN  waveforms for each of the remaining enabled channels without initiating
/// HIFN  another acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array.  The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_ReadWaveform(ViSession instrSession,
                                     ViInt32   channel,
                                     ViInt32   waveformSize,
                                     ViInt32   maximumTime,
                                     ViReal64  waveformArray[],
                                     ViInt32*  actualPoints,
                                     ViReal64* initialX,
                                     ViReal64* xIncrement)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchWaveform(instrSession, channel, waveformSize,
                                     waveformArray, actualPoints, initialX,
                                     xIncrement));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates measurement and returns datareturns the mask
/// HIFN  data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array.  The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_ReadMaskData(ViSession instrSession,
                                     ViInt32   waveformSize,
                                     ViInt32   maximumTime,
                                     ViReal64  waveformArray[],
                                     ViInt32   *actualPoints,
                                     ViReal64  *initialX,
                                     ViReal64  *xIncrement)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_InitiateAcquisition(instrSession, RSRTX_VAL_INIT_SINGLE));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchMaskData(instrSession, waveformSize,
                                     waveformArray, actualPoints, initialX,
                                     xIncrement));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates an acquisition on the channels that you enable
/// HIFN  with the rsrtx_ConfigureChannel function.  It then waits for the
/// HIFN  acquisition to complete, obtains a main waveform measurement on the channel
/// HIFN  you specify, and returns the measurement value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR measurement/Selects waveform measurement.
/// HIPAR measurementFunction/Defines or queries the main measurement.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR measurementResult/Returns the measured value.
ViStatus _VI_FUNC rsrtx_ReadMainWaveformMeasurement(ViSession instrSession,
                                                    ViInt32   measurement,
                                                    ViInt32   measurementFunction,
                                                    ViInt32   maximumTime,
                                                    ViReal64  *measurementResult)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurement, 1, 8),
    		2, "Measurement");

    checkErr(rsrtx_InitiateAcquisitionAndWait(instrSession, maximumTime));

    checkErr(rsrtx_FetchMainWaveformMeasurement(instrSession,
                                                    measurement,
                                                    measurementFunction,
                                                    measurementResult));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function initiates a waveform acquisition.  After you call this
/// HIFN  function, the oscilloscope leaves the Idle state and waits for a
/// HIFN  trigger.  The oscilloscope acquires a waveform for each channel you
/// HIFN  have enabled with the  rsrtx_ConfigureChannel function.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR action/Select action to be performed.
ViStatus _VI_FUNC rsrtx_InitiateAcquisition(ViSession instrSession,
                                            ViInt32   action)
{
    ViStatus error = VI_SUCCESS;
    ViUInt32 attr = RSRTX_ATTR_RUN_SINGLE;

    checkErr(RsCore_LockSession(instrSession));

    switch (action)
    {
        case RSRTX_VAL_INIT_SINGLE:
            attr = RSRTX_ATTR_RUN_SINGLE;
            break;
        case RSRTX_VAL_INIT_CONTINUOUS:
            attr = RSRTX_ATTR_RUN_CONTINUOUS;
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, action), 2, "Action");
    }

    checkErr(rsrtx_SetAttributeViString(instrSession, "", attr, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates a waveform acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the initiate
/// HIPAR maximumTime/acquisition operation to complete.
ViStatus _VI_FUNC rsrtx_InitiateAcquisitionAndWait(ViSession instrSession,
                                                   ViInt32   maximumTime)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sends software trigger and waits for operation complete.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR maximumTime/Pass the maximum length of time (in milliseconds) in which to allow
/// HIPAR maximumTime/the read waveform operation to complete.
ViStatus _VI_FUNC rsrtx_SendSoftwareTrigger(ViSession instrSession,
                                            ViInt32   maximumTime)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  timeout = 0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetAttributeViInt32(instrSession, "", RS_ATTR_OPC_TIMEOUT, &timeout));
    checkErr(rsrtx_SetAttributeViInt32(instrSession, "", RS_ATTR_OPC_TIMEOUT, maximumTime));
    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SEND_SW_TRIGGER, NULL));

Error:
	checkErr(rsrtx_SetAttributeViInt32(instrSession, "", RS_ATTR_OPC_TIMEOUT, timeout));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets or queries the acquisition state of the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR acquisitionState/Sets or queries the acquisition state of the instrument.
ViStatus _VI_FUNC rsrtx_ConfigureAcquisitionState(ViSession instrSession,
                                                  ViInt32   acquisitionState)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ACQUISITION_STATE, acquisitionState),
    		2, "Acquisition State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform the oscilloscope acquires for the
/// HIFN  channel you specify.  The waveform is from an acquisition that you
/// HIFN  previously initiated.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array. The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_FetchWaveform(ViSession instrSession,
                                      ViInt32   channel,
                                      ViInt32   waveformSize,
                                      ViReal64  waveformArray[],
                                      ViInt32*  actualPoints,
                                      ViReal64* initialX,
                                      ViReal64* xIncrement)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "CH%ld", channel);
    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_START, initialX),
    		6, "Initial X");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
    		7, "X Increment");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;CHAN%ld:DATA?", channel);
    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform the oscilloscope acquires for the
/// HIFN  channel you specify.  The waveform is from an acquisition that you
/// HIFN  previously initiated. To speed up the transmission, data are transfered as ViUInt16 array
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array. The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_FetchWaveformInteger(ViSession instrSession,
                                             ViInt32   channel,
                                             ViInt32   waveformSize,
                                             ViUInt16  waveformArray[],
                                             ViInt32   *actualPoints,
                                             ViReal64  *initialX,
                                             ViReal64  *xIncrement)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar   repCap[RS_REPCAP_BUF_SIZE];
    ViByte   *data = NULL;
    ViInt64  dataLen = 0;

    checkErr(RsCore_LockSession(instrSession));

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "CH%ld", channel);
    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_START, initialX),
    		6, "Initial X");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
    		7, "X Increment");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM UINT,16;CHAN%ld:DATA?", channel);
	checkErr(RsCore_QueryBinaryDataBlock(instrSession, cmd, VI_TRUE, NULL, &data, &dataLen));
	RsCore_CopyToUserBufferBinData((ViBuf)waveformArray, waveformSize * sizeof(ViUInt16), data, dataLen);

	if (actualPoints != NULL) *actualPoints = (ViInt32)dataLen;

Error:
    if (data) free(data);
	(void)RsCore_Write(instrSession, "FORM ASCII");
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform the oscilloscope acquires for the
/// HIFN  channel you specify.  The waveform is from an acquisition that you
/// HIFN  previously initiated. To speed up the transmission, data are transfered as byte array
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array. The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_FetchWaveformByte(ViSession instrSession,
                                          ViInt32   channel,
                                          ViInt32   waveformSize,
                                          ViByte    waveformArray[],
                                          ViInt32   *actualPoints,
                                          ViReal64  *initialX,
                                          ViReal64  *xIncrement)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar   repCap[RS_REPCAP_BUF_SIZE];
    ViByte   *data = NULL;
    ViInt64  length = 0;

    checkErr(RsCore_LockSession(instrSession));

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "CH%ld", channel);
    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_START, initialX),
    		6, "Initial X");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
    		7, "X Increment");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM UINT,8;CHAN%ld:DATA?", channel);
	checkErr(RsCore_QueryBinaryDataBlock(instrSession, cmd, VI_TRUE, NULL, &data, &length));
	checkErr(RsCore_CopyToUserBufferBinData(waveformArray, waveformSize, data, length));

	if (actualPoints != NULL)
		*actualPoints = (ViInt32)length;

Error:
	if (data)
		free(data);
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns information on the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchWaveformHeader(ViSession instrSession,
                                            ViInt32   channel,
                                            ViReal64  *xStart,
                                            ViReal64  *xStop,
                                            ViInt32   *recordLength,
                                            ViInt32   *valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CHAN%ld:DATA:HEAD?", channel);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns the waveform conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchWaveformConversionData(ViSession instrSession,
                                                    ViInt32   channel,
                                                    ViReal64  *xStart,
                                                    ViReal64  *xIncrement,
                                                    ViReal64  *yStart,
                                                    ViReal64  *yIncrement,
                                                    ViInt32   *yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_WAVEFORM_CONVERSION_X_START,
    		"Channel", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_WAVEFORM_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function returns the data of the envelope.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control selects the channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array.  The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/This control is reserved.
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveform(ViSession instrSession,
                                              ViInt32   channel,
                                              ViInt32   waveformSize,
                                              ViReal64  waveformArray[],
                                              ViInt32   *actualPoints,
                                              ViReal64  *initialX,
                                              ViReal64  *xIncrement)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
             xIncrement;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, 1, 4),
    		2, "Channel");

    checkErr(rsrtx_FetchEnvelopeWaveformHeader(instrSession, channel,
                                                 initialX, NULL,
                                                 actualPoints, NULL));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CHAN%ld:DATA:ENV?", channel);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns information on the envelope waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 2.
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveformHeader(ViSession instrSession,
                                                    ViInt32   channel,
                                                    ViReal64  *xStart,
                                                    ViReal64  *xStop,
                                                    ViInt32   *recordLength,
                                                    ViInt32   *valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CHAN%ld:DATA:ENV:HEAD?", channel);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns the envelope waveform conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchEnvelopeWaveformConversionData(ViSession instrSession,
                                                            ViInt32   channel,
                                                            ViReal64  *xStart,
                                                            ViReal64  *xIncrement,
                                                            ViReal64  *yStart,
                                                            ViReal64  *yIncrement,
                                                            ViInt32   *yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_X_START,
    		"Channel", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_ENVELOPE_WAVEFORM_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function returns the data of the math waveform points.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mathNumber/Selects the math waveform.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchMathWaveform(ViSession instrSession,
                                          ViInt32   mathNumber,
                                          ViInt32   waveformSize,
                                          ViReal64  waveformArray[],
                                          ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "CALC:MATH%ld:DATA?", mathNumber);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of math waveform data. The header contains
/// HIFN  attributes of the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchMathWaveformHeader(ViSession instrSession,
                                                ViInt32   mathNumber,
                                                ViReal64  *xStart,
                                                ViReal64  *xStop,
                                                ViInt32   *recordLength,
                                                ViInt32   *valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   response[RS_MAX_MESSAGE_BUF_SIZE];
	ViChar   repCap[RS_REPCAP_BUF_SIZE];
	ViChar*  p2buf;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_WAVEFORM_HEADER,
    		"Math", mathNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Math Number");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_HEADER,
    		RS_MAX_MESSAGE_BUF_SIZE, response),
    		3, "Math Waveform Header");

    p2buf = strtok (response, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (xStart != NULL) *xStart = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (xStop != NULL) *xStop = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (recordLength != NULL) *recordLength = RsCore_Convert_String_To_ViInt32(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (valuesPerSample != NULL) *valuesPerSample = RsCore_Convert_String_To_ViInt32(p2buf);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns the math waveform conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchMathWaveformConversionData(ViSession instrSession,
                                                        ViInt32   channel,
                                                        ViReal64  *xStart,
                                                        ViReal64  *xIncrement,
                                                        ViReal64  *yStart,
                                                        ViReal64  *yIncrement,
                                                        ViInt32   *yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_X_START,
    		"Math", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_MATH_WAVEFORM_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function returns the data of the reference waveform points.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR referenceWfm/Selects the reference waveform, the internal reference storage.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveform(ViSession instrSession,
                                               ViInt32   referenceWfm,
                                               ViInt32   waveformSize,
                                               ViReal64  waveformArray[],
                                               ViInt32   *actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, referenceWfm, RSRTX_VAL_REF_WAVEFORM_1, RSRTX_VAL_REF_WAVEFORM_4),
    		2, "Reference Wfm");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "REFC%ld:DATA?", referenceWfm);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of math waveform data. The header contains
/// HIFN  attributes of the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveformHeader(ViSession instrSession,
                                                     ViInt32   channel,
                                                     ViReal64  *xStart,
                                                     ViReal64  *xStop,
                                                     ViInt32   *recordLength,
                                                     ViInt32   *valuesPerSample)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";
    ViChar   response[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar*  p2buf;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_HEADER,
    		"ReferenceWfm", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Reference Wfm");

    viCheckParm(rsrtx_GetAttributeViString(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_HEADER,
    		RS_MAX_MESSAGE_BUF_SIZE, response),
    		3, "Reference Waveform Header");

    p2buf = strtok (response, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (xStart != NULL) *xStart = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (xStop != NULL) *xStop = RsCore_Convert_String_To_ViReal64(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (recordLength != NULL) *recordLength = RsCore_Convert_String_To_ViInt32(p2buf);

    p2buf = strtok (NULL, ",");
    if (p2buf == NULL)
        checkErr(VI_ERROR_INV_RESPONSE);
    if (valuesPerSample != NULL) *valuesPerSample = RsCore_Convert_String_To_ViInt32(p2buf);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Returns the reference waveform conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Channel number.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchReferenceWaveformConversionData(ViSession instrSession,
                                                             ViInt32   channel,
                                                             ViReal64  *xStart,
                                                             ViReal64  *xIncrement,
                                                             ViReal64  *yStart,
                                                             ViReal64  *yIncrement,
                                                             ViInt32   *yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_X_START,
    		"ReferenceWfm", channel - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Channel");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_REFERENCE_WAVEFORM_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function returns the mask data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchMaskData(ViSession instrSession,
                                      ViInt32   waveformSize,
                                      ViReal64  waveformArray[],
                                      ViInt32   *actualPoints,
                                      ViReal64  *initialX,
                                      ViReal64  *xIncrement)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MASK_DATA_CONVERSION_X_START, initialX),
    		6, "Initial X");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MASK_DATA_CONVERSION_X_INCREMENT, xIncrement),
    		7, "X Increment");

    snprintf(cmd, RS_REPCAP_BUF_SIZE, "FORM REAL,32;MASK:DATA?");
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
	(void)RsCore_Write(instrSession, "FORM ASCII");
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns information of the mask data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 2.
ViStatus _VI_FUNC rsrtx_FetchMaskDataHeader(ViSession instrSession,
                                            ViReal64* xStart,
                                            ViReal64* xStop,
                                            ViInt32*  recordLength,
                                            ViInt32*  valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

    snprintf (cmd, RS_MAX_MESSAGE_BUF_SIZE, "MASK:DATA:HEAD?");
    checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the mask conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchMaskConversionData(ViSession instrSession,
                                                ViReal64* xStart,
                                                ViReal64* xIncrement,
                                                ViReal64* yStart,
                                                ViReal64* yIncrement,
                                                ViInt32*  yResolution)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_DATA_CONVERSION_X_START, xStart),
			2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_DATA_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_DATA_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_MASK_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_MASK_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function obtains a main waveform measurement on the channel you
/// HIFN  specify, and returns the measurement value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR measurement/Selects waveform measurement.
/// HIPAR measurementFunction/Defines or queries the main measurement.
/// HIPAR measurementResult/Returns the measured value.
ViStatus _VI_FUNC rsrtx_FetchMainWaveformMeasurement(ViSession instrSession,
                                                     ViInt32   measurement,
                                                     ViInt32   measurementFunction,
                                                     ViReal64  *measurementResult)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FREQUENCY,
    		"Measurement", measurement - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Measurement");

	switch (measurementFunction)
	{
		case RSRTX_VAL_MEAS_FREQUENCY:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FREQUENCY, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PERIOD:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PERIOD, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PEAK:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PEAK, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_UPEAK:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MAXIMUM_PEAK, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_LPEAK:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MINIMUM_PEAK, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PPC:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_PULSES, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_NPC:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_PULSES, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_REC:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RISING_EDGES, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_FEC:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FALLING_EDGES, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_HIGH:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_HIGH_LEVEL, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_LOW:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_LOW_LEVEL, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_AMP:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_AMPLITUDE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_MEAN:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MEAN, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_RMS:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RMS, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_RTM:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RISE_TIME, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_FTIM:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_FALLING_TIME, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PDCY:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_CYCLE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_NDCY:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_CYCLE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PPW:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_WIDTH_POSITIVE_PULSE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_NPW:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_WIDTH_NEGATIVE_PULSE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_CYCM:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_MEAN_VALUE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_CYCR:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_RMS_VALUE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_SSTDD:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_STANDARD_DEVIATIONS, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_DEL:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_DELAY, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_PHA:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_PHASE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_BWID:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_BURST_WIDTH, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_CYCS:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_STANDARD_DEVIATION_VALUE, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_POV:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_POSITIVE_OVERSHOOT, measurementResult),
					4, "Result");
			break;
		case RSRTX_VAL_MEAS_NOV:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_MAIN_MEASUREMENT_RESULT_NEGATIVE_OVERSHOOT, measurementResult),
					4, "Result");
			break;
		default:
			viCheckParm(RsCore_InvalidViInt32Value(instrSession, measurementFunction), 3, "Measurement Function");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function aborts an acquisition and returns the oscilloscope to
/// HIFN  the Idle state.  You initiate an acquisition with the
/// HIFN  rsrtx_InitiateAcquisition function.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
ViStatus _VI_FUNC rsrtx_Abort(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_STOP, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the data of the math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchSimpleMathWaveform(ViSession instrSession,
                                                ViInt32   waveformSize,
                                                ViReal64  waveformArray[],
                                                ViInt32*  actualPoints)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;CALC:QMAT:DATA?");
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the header of math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchSimpleMathWaveformHeader(ViSession instrSession,
                                                      ViReal64* xStart,
                                                      ViReal64* xStop,
                                                      ViInt32*  recordLength,
                                                      ViInt32*  valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

    snprintf (cmd, RS_MAX_MESSAGE_BUF_SIZE, "CALC:QMAT:DATA:HEAD?");
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Return the conversion data of the simple math waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySimpleMathDataConversion(ViSession instrSession,
                                                      ViReal64* xStart,
                                                      ViReal64* xIncrement,
                                                      ViReal64* yStart,
                                                      ViReal64* yIncrement,
                                                      ViInt32*  yResolution)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_X_START, xStart),
			2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SIMPLE_MATH_WAVEFORM_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Returns the number of returned samples for the selected range.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_DIGITAL_WAVEFORM_SAMPLES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     DIGital<m>:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digital/Selects the digital channel.
/// HIPAR samplesNumber/Returns the number of returned samples for the selected range.
ViStatus _VI_FUNC rsrtx_QueryDigitalWaveformSamplesNumber(ViSession instrSession,
                                                          ViInt32   digital,
                                                          ViInt32*  samplesNumber)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_WAVEFORM_SAMPLES,
    		"Digital", digital , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DIGITAL_WAVEFORM_SAMPLES, samplesNumber),
			3, "Samples Number");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function returns the data of the digital waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digital/Selects the digital channel.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchDigitalWaveform(ViSession instrSession,
                                             ViInt32   digital,
                                             ViInt32   waveformSize,
                                             ViReal64  waveformArray[],
                                             ViInt32*  actualPoints)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "DIG%ld:DATA?", digital);
    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the header of digital waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
/// HIPAR digital/Selects the digital channel.
ViStatus _VI_FUNC rsrtx_FetchDigitalWaveformHeader(ViSession instrSession,
                                                   ViInt32   digital,
                                                   ViReal64  *xStart,
                                                   ViReal64  *xStop,
                                                   ViInt32   *recordLength,
                                                   ViInt32   *valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "DIG%ld:DATA:HEAD?", digital);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Return the conversion data of the indicated waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR digital/Selects the digital channel.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QueryDigitalDataConversion(ViSession instrSession,
                                                   ViInt32   digital,
                                                   ViReal64* xStart,
                                                   ViReal64* xIncrement,
                                                   ViReal64* yStart,
                                                   ViReal64* yIncrement,
                                                   ViInt32*  yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_X_START,
    		"Digital", digital , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Digital");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DIGITAL_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  This function returns the data of the logic waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchLogicWaveform(ViSession instrSession,
                                           ViInt32   logic,
                                           ViInt32   waveformSize,
                                           ViReal64  waveformArray[],
                                           ViInt32*  actualPoints)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

	checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "LOG%ld:DATA?", logic);
	checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the header of logic waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchLogicWaveformHeader(ViSession instrSession,
                                                 ViInt32   logic,
                                                 ViReal64* xStart,
                                                 ViReal64* xStop,
                                                 ViInt32*  recordLength,
                                                 ViInt32*  valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "LOG%ld:DATA:HEAD?", logic);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesPerSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Return the conversion data of the indicated waveform.
/// HIFN     LOGic<p>:DATA:YRESolution?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QueryLogicDataConversion(ViSession instrSession,
                                                 ViInt32   logic,
                                                 ViReal64* xStart,
                                                 ViReal64* xIncrement,
                                                 ViReal64* yStart,
                                                 ViReal64* yIncrement,
                                                 ViInt32*  yResolution)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_DATA_CONVERSION_X_START,
    		"Logic", logic - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "logic");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_LOGIC_DATA_CONVERSION_X_START, xStart),
			3, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_LOGIC_DATA_CONVERSION_X_INCREMENT, xIncrement),
			4, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_START, yStart),
			5, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			6, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_LOGIC_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			7, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Returns the number of data samples that are returned with
/// HIFN  SPECtrum:WAVeform:SPECtrum:DATA.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_WAVEFORM_SAMPLES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:WAVeform:SPECtrum:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSamples/Returns the number of data samples that are returned with
/// HIPAR waveformSamples/SPECtrum:WAVeform:SPECtrum:DATA.
ViStatus _VI_FUNC rsrtx_QuerySpectrumWaveformSamples(ViSession instrSession,
                                                     ViInt32*  waveformSamples)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_WAVEFORM_SAMPLES, waveformSamples),
    		2, "Waveform Samples");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates a measurement and returns the waveform for the
/// HIFN  channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_ReadSpectrumDataWaveform(ViSession instrSession,
                                                 ViInt32   waveformSize,
                                                 ViInt32   maximumTime,
                                                 ViReal64  waveformArray[],
                                                 ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchSpectrumDataWaveform(instrSession, waveformSize,
                                     waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform for the channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchSpectrumDataWaveform(ViSession instrSession,
                                                  ViInt32   waveformSize,
                                                  ViReal64  waveformArray[],
                                                  ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "FORM REAL,32;SPEC:WAV:SPEC:DATA?", waveformSize, waveformArray, actualPoints));

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of waveform data. The header contains attributes of
/// HIFN  the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchSpectrumDataWaveformHeader(ViSession instrSession,
                                                        ViReal64* xStart,
                                                        ViReal64* xStop,
                                                        ViInt32*  recordLength,
                                                        ViInt32*  valuesperSample)
{
    ViStatus error = VI_SUCCESS;
    ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_QueryTupleViReal64(instrSession, "SPEC:WAV:SPEC:DATA:HEAD?", xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesperSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns conversion data of the indicated waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Returns the frequency of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the level difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Returns the vertical bit resolution of the indicated waveform.
/// HIPAR yIncrement/Returns the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Returns the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumDataConversion(ViSession instrSession,
                                                    ViReal64* xStart,
                                                    ViReal64* xIncrement,
                                                    ViReal64* yStart,
                                                    ViReal64* yIncrement,
                                                    ViInt32*  yResolution)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_X_START, xStart),
    		2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of data samples that are returned with
/// HIFN  SPECtrum:WAVeform:xxx:DATA for the indicated waveform.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_AVERAGE_WAVEFORM_SAMPLES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:WAVeform:AVERage:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR averageWaveformSamples/Returns the number of data samples that are returned with
/// HIPAR averageWaveformSamples/SPECtrum:WAVeform:xxx:DATA for the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumAverageWaveformSamples(ViSession instrSession,
                                                            ViInt32*  averageWaveformSamples)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAGE_WAVEFORM_SAMPLES, averageWaveformSamples),
    		2, "Average Waveform Samples");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates a measurement and returns the waveform for the
/// HIFN  channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_ReadSpectrumAverageData(ViSession instrSession,
                                                ViInt32   waveformSize,
                                                ViInt32   maximumTime,
                                                ViReal64  waveformArray[],
                                                ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchSpectrumAverageData(instrSession, waveformSize,
                                     waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform for the channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchSpectrumAverageData(ViSession instrSession,
                                                 ViInt32   waveformSize,
                                                 ViReal64  waveformArray[],
                                                 ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "FORM REAL,32;SPEC:WAV:AVER:DATA?", waveformSize, waveformArray, actualPoints));

Error:
    (void)(RsCore_Write(instrSession, "FORM ASCII"));
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of waveform data. The header contains attributes of
/// HIFN  the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchSpectrumAverageDataHeader(ViSession instrSession,
                                                       ViReal64* xStart,
                                                       ViReal64* xStop,
                                                       ViInt32*  recordLength,
                                                       ViInt32*  valuesperSample)
{
    ViStatus error = VI_SUCCESS;
    ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_QueryTupleViReal64(instrSession, "SPEC:WAV:AVER:DATA:HEAD?", xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesperSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns conversion data of the indicated waveform average.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Returns the frequency of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the level difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Returns the vertical bit resolution of the indicated waveform.
/// HIPAR yIncrement/Returns the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Returns the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumAverageDataConversion(ViSession instrSession,
                                                           ViReal64* xStart,
                                                           ViReal64* xIncrement,
                                                           ViReal64* yStart,
                                                           ViReal64* yIncrement,
                                                           ViInt32*  yResolution)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_X_START, xStart),
    		2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAGE_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_AVERAVE_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of data samples that are returned with
/// HIFN  SPECtrum:WAVeform:xxx:DATA for the indicated waveform.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_MAXIMUM_WAVEFORM_SAMPLES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:WAVeform:MAXimum:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR maximumWaveformSamples/Returns the number of data samples that are returned with
/// HIPAR maximumWaveformSamples/SPECtrum:WAVeform:xxx:DATA for the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMaximumWaveformSamples(ViSession instrSession,
                                                            ViInt32*  maximumWaveformSamples)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_WAVEFORM_SAMPLES, maximumWaveformSamples),
    		2, "Maximum Waveform Samples");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates a mesaurement and returns the waveform for the
/// HIFN  channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_ReadSpectrumMaximumData(ViSession instrSession,
                                                ViInt32   waveformSize,
                                                ViInt32   maximumTime,
                                                ViReal64  waveformArray[],
                                                ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchSpectrumMaximumData(instrSession, waveformSize,
                                     waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform for the channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchSpectrumMaximumData(ViSession instrSession,
                                                 ViInt32   waveformSize,
                                                 ViReal64  waveformArray[],
                                                 ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "FORM REAL,32;SPEC:WAV:MAX:DATA?", waveformSize, waveformArray, actualPoints));

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of waveform data. The header contains attributes of
/// HIFN  the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchSpectrumMaximumDataHeader(ViSession instrSession,
                                                       ViReal64* xStart,
                                                       ViReal64* xStop,
                                                       ViInt32*  recordLength,
                                                       ViInt32*  valuesperSample)
{
    ViStatus error = VI_SUCCESS;
    ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_QueryTupleViReal64(instrSession, "SPEC:WAV:MAX:DATA:HEAD?", xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesperSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns conversion data of the indicated waveform maximum.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Returns the frequency of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the level difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Returns the vertical bit resolution of the indicated waveform.
/// HIPAR yIncrement/Returns the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Returns the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMaximumDataConversion(ViSession instrSession,
                                                           ViReal64* xStart,
                                                           ViReal64* xIncrement,
                                                           ViReal64* yStart,
                                                           ViReal64* yIncrement,
                                                           ViInt32*  yResolution)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_X_START, xStart),
    		2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MAXIMUM_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of data samples that are returned with
/// HIFN  SPECtrum:WAVeform:MINimum:DATA.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_MINIMUM_WAVEFORM_SAMPLES
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:WAVeform:MINimum:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR minimumWaveformSamples/Returns the number of data samples that are returned with
/// HIPAR minimumWaveformSamples/SPECtrum:WAVeform:MINimum:DATA.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMinimumWaveformSamples(ViSession instrSession,
                                                            ViInt32*  minimumWaveformSamples)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_WAVEFORM_SAMPLES, minimumWaveformSamples),
    		2, "Minimum Waveform Samples");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates a measurement and returns the waveform for the
/// HIFN  channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_ReadSpectrumMinimumData(ViSession instrSession,
                                                ViInt32   waveformSize,
                                                ViInt32   maximumTime,
                                                ViReal64  waveformArray[],
                                                ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;
    ViInt32  oldTimeout = 5;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RUN_SINGLE_WAIT_FOR_OPC, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

    checkErr(rsrtx_FetchSpectrumMinimumData(instrSession, waveformSize,
                                     waveformArray, actualPoints));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the waveform for the channel you specify.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
ViStatus _VI_FUNC rsrtx_FetchSpectrumMinimumData(ViSession instrSession,
                                                 ViInt32   waveformSize,
                                                 ViReal64  waveformArray[],
                                                 ViInt32*  actualPoints)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "FORM REAL,32;SPEC:WAV:MIN:DATA?", waveformSize, waveformArray, actualPoints));

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the header of waveform data. The header contains attributes of
/// HIFN  the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 1.
ViStatus _VI_FUNC rsrtx_FetchSpectrumMinimumDataHeader(ViSession instrSession,
                                                       ViReal64* xStart,
                                                       ViReal64* xStop,
                                                       ViInt32*  recordLength,
                                                       ViInt32*  valuesperSample)
{
    ViStatus error = VI_SUCCESS;
    ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_QueryTupleViReal64(instrSession, "SPEC:WAV:MIN:DATA:HEAD?", xStart, xStop, &aux1, &aux2));
	*recordLength = (ViInt32)aux1;
	*valuesperSample = (ViInt32)aux2;
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns conversion data of the indicated waveform minimum.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR xStart/Returns the frequency of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the level difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Returns the vertical bit resolution of the indicated waveform.
/// HIPAR yIncrement/Returns the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Returns the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMinimumDataConversion(ViSession instrSession,
                                                           ViReal64* xStart,
                                                           ViReal64* xIncrement,
                                                           ViReal64* yStart,
                                                           ViReal64* yIncrement,
                                                           ViInt32*  yResolution)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_X_START, xStart),
    		2, "X Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_X_INCREMENT, xIncrement),
			3, "X Increment");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_START, yStart),
			4, "Y Start");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_INCREMENT, yIncrement),
			5, "Y Increment");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MINIMUM_DATA_CONVERSION_Y_RESOLUTION, yResolution),
			6, "Y Resolution");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the waveform to be exported.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Defines the waveform to be exported.
ViStatus _VI_FUNC rsrtx_WaveformExportSource(ViSession instrSession,
                                             ViInt32   source)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_EXPORT_SOURCE, source),
    		2, "Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Executes saving a waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR name/Defines the path and filename for a waveform data file that will be
/// HIPAR name/saved. The file format is CSV. If the file already exists, it will be
/// HIPAR name/overwritten.
ViStatus _VI_FUNC rsrtx_WaveformExportSave(ViSession instrSession,
                                           ViString  name)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_WAVEFROM_EXPORT_NAME, name),
    		2, "Name");

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_WAVEFORM_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function enables the power analysis.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/enables the power analysis.
ViStatus _VI_FUNC rsrtx_ConfigurePowerAnalysisState(ViSession instrSession,
                                                    ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_ENABLED, state),
    		2, "state");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures power analysis type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects power analysis type.
ViStatus _VI_FUNC rsrtx_ConfigurePowerAnalysisType(ViSession instrSession,
                                                   ViInt32   type)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_TYPE, type),
    		2, "type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function resets statistics.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ResetPowerAnalysisStatistics(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_RESET_STATISTICS, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the automatic deskew procedure to align the
/// HIFN  waveforms of all visible channels. It is necessary to deskew if a
/// HIFN  current and a voltage probe is used in the measurment. Use the R&S
/// HIFN  RT-ZF20 power deskew fixture to deskew the probes.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerAnalysisDeskew(ViSession instrSession,
                                                 ViInt32   maximumTime)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  oldTimeout = 0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_START_DESKEW, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function sets zero offset.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_SetPowerAnalysisZeroOffset(ViSession instrSession,
                                                   ViInt32   maximumTime)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  oldTimeout = 0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_ZERO_OFFSET, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerAnalysisAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Starts power analysis autoset.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutoset(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_AUTOSET, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Starts power analysis current autoset.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutosetCurrent(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_AUTOSET_CURRENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Starts power analysis voltage autoset.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerAnalysisAutosetVoltage(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ANALYSIS_AUTOSET_VOLTAGE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function starts the power quality measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerQualityMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_QUALITY_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerQualityMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_QUALITY_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects quality type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementVoltageResult(
							ViSession instrSession,
							ViInt32   type,
							ViInt32   statistics,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_QUALITY_TYPE_RMS, RSRTX_VAL_QUALITY_TYPE_CRES),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:QUAL:RES:VOLT:%s:%s?", qualityTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects quality type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementCurrentResult(
							ViSession instrSession,
							ViInt32   type,
							ViInt32   statistics,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_QUALITY_TYPE_RMS, RSRTX_VAL_QUALITY_TYPE_CRES),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:QUAL:RES:CURR:%s:%s?", qualityTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects quality type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerQualityMeasurementPowerResult(
							ViSession instrSession,
							ViInt32   type,
							ViInt32   statistics,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_QUALITY_TYPE_POWER_REAL, RSRTX_VAL_QUALITY_TYPE_POWER_PHAS),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:QUAL:RES:POW:%s:%s?", qualityTypePowerArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power consumption measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerConsumptionMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_CONSUMPTION_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function restarts the power consumption measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_RestartPowerConsumptionMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RESTART_POWER_CONSUMPTION_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerConsumptionMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects consumption type.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerConsumptionMeasurementResults(
							ViSession instrSession,
							ViInt32   type,
							ViReal64* measurementResult)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    switch (type)
    {
        case RSRTX_VAL_CONSUMPTION_TYPE_DURATION:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_DURATION_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        case RSRTX_VAL_CONSUMPTION_TYPE_ENERGY:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_CONSUMPTION_TYPE_ACTIVE:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_ACTIVE_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_CONSUMPTION_TYPE_APPARENT_POWER:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_APPARENT_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_CONSUMPTION_TYPE_POWER_FACTOR:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_POWER_FACTOR_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_CONSUMPTION_TYPE_PHASE:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_PHASE_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_CONSUMPTION_TYPE_REACTIVE_POWER:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CONSUMPTION_MEASUREMENT_REACTIVE_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, type), 2, "Type");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power current harmonics measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerCurrentHarmonicsMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_CURRENT_HARMONICS_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the selected measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerCurrentHarmonicsMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the measurement duration.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR duration/Returns the measurement duration.
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementDuration(
							ViSession instrSession,
							ViReal64* duration)
{
 	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_DURATION, duration),
    		2, "duration");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the selected measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR resultNumber/Result number.
/// HIPAR type/Selects harmonics type.
/// HIPAR measurementResult/Returns the result of the selected measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementResult(
							ViSession instrSession,
							ViInt32   resultNumber,
							ViInt32   type,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, resultNumber, 1, 40),
			2, "Result Number");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_HARMONICS_TYPE_VIOLENT_COUNT, RSRTX_VAL_HARMONICS_TYPE_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:HARM:RES%ld:%s?", resultNumber, harmonicsTypeArr[type]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the limit check result.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR resultNumber/Result number.
/// HIPAR limitCheck/Returns the limit check result.
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementLimitCheckResult(
							ViSession instrSession,
							ViInt32   resultNumber,
							ViInt32*  limitCheck)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_LIMIT_CHECK_RESULT,
    		"ResultNumber", resultNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "ResultNumber");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_LIMIT_CHECK_RESULT, limitCheck),
			3, "Limit Check");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the current real power value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR current/Returns the current real power value.
ViStatus _VI_FUNC rsrtx_QueryPowerCurrentHarmonicsMeasurementRealPowerCurrent(
							ViSession instrSession,
							ViReal64* current)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_CURRENT_HARMONICS_MEASUREMENT_REAL_POWER_CURRENT, current),
    		2, "current");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function resets the results.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR resultNumber/Result number.
ViStatus _VI_FUNC rsrtx_ResetPowerCurrentHarmonicsMeasurementResults(
							ViSession instrSession,
							ViInt32   resultNumber)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_RESET_POWER_CURRENT_HARMONICS_MEASUREMENT_RESULTS,
    		"ResultNumber", resultNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "ResultNumber");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_RESET_POWER_CURRENT_HARMONICS_MEASUREMENT_RESULTS, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power inrush current measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerInrushCurrentMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_INRUSH_CURRENT_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerInrushCurrentMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the selected measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR gateNumber/Gate number.
/// HIPAR type/Selects inrush current type.
/// HIPAR measurementResult/Returns the result of the selected measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerInrushCurrentMeasurementResult(
							ViSession instrSession,
							ViInt32   gateNumber,
							ViInt32   type,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_AREA_RESULT,
    		"Gate", gateNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Gate");
    switch (type)
    {
        case RSRTX_VAL_INRUSH_CURRENT_TYPE_AREA:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_AREA_RESULT, measurementResult),
            		4, "Measurement Result");
            break;
        case RSRTX_VAL_INRUSH_CURRENT_TYPE_MAXIMUM:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_INRUSH_CURRENT_MEASUREMENT_MAXIMUM_RESULT, measurementResult),
            		4, "Measurement Result");
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, type), 3, "Type");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power ripple measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerRippleMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_RIPPLE_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerRippleMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_RIPPLE_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects ripple type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerRippleMeasurementResult(ViSession instrSession,
                                                          ViInt32   type,
                                                          ViInt32   statistics,
                                                          ViReal64* measurementResult)
{
 	ViStatus error = VI_SUCCESS;
 	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_RIPPLE_TYPE_FREQUENCY, RSRTX_VAL_RIPPLE_TYPE_NDCYCLE),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			2, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:RIPP:RES:%s:%s?", rippleTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power spectrum measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerSpectrumMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_SPECTRUM_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the result of the selected measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR resultNumber/Result number.
/// HIPAR type/Selects spectrum measurement type.
/// HIPAR measurementResult/Returns the result of the selected measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerSpectrumMeasurementResult(ViSession instrSession,
                                                            ViInt32   resultNumber,
                                                            ViInt32   type,
                                                            ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, resultNumber, 1, 40),
			2, "Result Number");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_SPECTRUM_TYPE_FREQUENCY, RSRTX_VAL_SPECTRUM_TYPE_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SPEC:RES%ld:%s?", resultNumber, spectrumTypeArr[type]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerSpectrumMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SPECTRUM_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function resets the results.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR resultNumber/Result number.
ViStatus _VI_FUNC rsrtx_ResetPowerSpectrumMeasurementResults(ViSession instrSession,
                                                             ViInt32   resultNumber)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_RESET_POWER_SPECTRUM_MEASUREMENT_RESULTS,
    		"ResultNumber", resultNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "ResultNumber");

	checkErr(rsrtx_SetAttributeViString(instrSession, repCap, RSRTX_ATTR_RESET_POWER_SPECTRUM_MEASUREMENT_RESULTS, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the slew rate measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerSlewRateMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_SLEW_RATE_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerSlewRateMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SLEW_RATE_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects slew rate measurement type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerSlewRateMeasurementResult(ViSession instrSession,
                                                            ViInt32   type,
                                                            ViInt32   statistics,
                                                            ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_SLEW_RATE_TYPE_LPEAK, RSRTX_VAL_SLEW_RATE_TYPE_UPEAK),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SLEW:RES:%s:%s?", slewRateTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power modulation measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerModulationMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_MODULATION_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerModulationMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_MODULATION_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects modulation measurement type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerModulationMeasurementResult(
							ViSession instrSession,
							ViInt32   type,
							ViInt32   statistics,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_MODULATION_RESULT_TYPE_LPE, RSRTX_VAL_MODULATION_RESULT_TYPE_STDD),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:MOD:RES:%s:%s?", modulationTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Contains the the power modulation threshold settings.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_POWER_MODULATION_THRESHOLD_HYSTERESIS
/// HIFN     RSRTX_ATTR_POWER_MODULATION_THRESHOLD_LOWER
/// HIFN     RSRTX_ATTR_POWER_MODULATION_THRESHOLD_UPPER
/// HIFN
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     POWer:MODulation:THReshold:HYSTeresis
/// HIFN     POWer:MODulation:THReshold:LOWer
/// HIFN     POWer:MODulation:THReshold[:UPPer]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR thresholdHysteresis/Sets the hysteresis for correct edge detection.
/// HIPAR thresholdUpper/Sets the threshold for unipolar sources, or the upper level for
/// HIPAR thresholdUpper/bipolar sources. The signal is measured at the crossing points of the
/// HIPAR thresholdUpper/signal with the threshold.
/// HIPAR thresholdLower/Sets the lower level for bipolar sources, which determines the
/// HIPAR thresholdLower/crossing points on negative pulses.
ViStatus _VI_FUNC rsrtx_ConfigurePowerModulationThresholdSettings(
							ViSession instrSession,
							ViReal64  thresholdHysteresis,
							ViReal64  thresholdUpper,
							ViReal64  thresholdLower)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_MODULATION_THRESHOLD_HYSTERESIS, thresholdHysteresis),
    		2, "Threshold Hysteresis");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_MODULATION_THRESHOLD_UPPER, thresholdUpper),
    		3, "Threshold Upper");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_MODULATION_THRESHOLD_LOWER, thresholdLower),
			4, "Threshold Lower");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power dynamic on resistance measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerDynamicOnResistanceMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerDynamicOnResistanceMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerDynamicOnResistanceMeasurementResult(
							ViSession instrSession,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_DYNAMIC_ON_RESISTANCE_MEASUREMENT_RESULT, measurementResult),
			2, "Measurement Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power efficiency measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerEfficiencyMeasurement(ViSession instrSession)
{
 	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_EFFICIENCY_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerEfficiencyMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_EFFICIENCY_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the statistic value of the specified measurement series.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects efficiency measurement type.
/// HIPAR statistics/Selects statistic value.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
ViStatus _VI_FUNC rsrtx_QueryPowerEfficiencyMeasurementResult(
							ViSession instrSession,
							ViInt32   type,
							ViInt32   statistics,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_CheckInstrumentOptions(instrSession, "K31"));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_EFFICIENCY_TYPE_EFFICIENCY, RSRTX_VAL_EFFICIENCY_TYPE_OUTPUT),
			2, "Type");
	viCheckParm(RsCore_InvalidViInt32Range(instrSession, statistics, RSRTX_VAL_STATISTICS_ACT, RSRTX_VAL_STATISTICS_WFMC),
			3, "Statistics");

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:EFF:RES:%s:%s?", efficiencyTypeArr[type], statisticsArr[statistics]);
    checkErr(rsrtx_QueryViReal64(instrSession, cmd, measurementResult));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function starts the power switchingloss measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerSwitchinglossMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_SWITCHINGLOSS_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function sets gate to waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_SetPowerSwitschinglossMeasurementGateToWaveform(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SET_POWER_SWITSCHINGLOSS_MEASUREMENT_GATE_TO_WAVEFORM, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerSwitchinglossMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects switchingloss measurement type.
/// HIPAR measurementResult/Returns the result of the measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerSwitchinglossMeasurementEnergyResult(
							ViSession instrSession,
							ViInt32   type,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    switch (type)
    {
        case RSRTX_VAL_SWITCHINGLOSS_TYPE_CONDUCTION:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_CONDUCTION_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        case RSRTX_VAL_SWITCHINGLOSS_TYPE_NO_COND:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_NO_CONDUCTION_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_ON:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_ON_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_OFF:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_OFF_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TOTAL:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TOTAL_ENERGY_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, type), 2, "Type");
		break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the result of the measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects switchingloss measurement type.
/// HIPAR measurementResult/Returns the result of the measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerSwitchinglossMeasurementPowerResult(
							ViSession instrSession,
							ViInt32   type,
							ViReal64* measurementResult)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    switch (type)
    {
        case RSRTX_VAL_SWITCHINGLOSS_TYPE_CONDUCTION:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_CONDUCTION_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        case RSRTX_VAL_SWITCHINGLOSS_TYPE_NO_COND:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_NO_CONDUCTION_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_ON:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_ON_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TURN_OFF:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TURN_OFF_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
		case RSRTX_VAL_SWITCHINGLOSS_TYPE_TOTAL:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_SWITCHINGLOSS_MEASUREMENT_TOTAL_POWER_RESULT, measurementResult),
            		3, "Measurement Result");
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, type), 2, "Type");
		break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function starts the power on off measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerOnOffMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_ON_OFF_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds a power report.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerOnOffMeasurementAddReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the result of the measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementResult/Returns the statistic value of the specified measurement series.
/// HIPAR resultNumber/Result number.
ViStatus _VI_FUNC rsrtx_QueryPowerOnOffMeasurementResult(ViSession instrSession,
                                                         ViInt32   resultNumber,
                                                         ViReal64  *measurementResult)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_RESULT,
    		"OnOffResult", resultNumber - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "OnOffResult");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_POWER_ON_OFF_MEASUREMENT_RESULT, measurementResult),
			3, "Measurement Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function starts the safe operating area measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerSafeOperatingAreaMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_SAFE_OPERATING_AREA_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function restarts the safe operating area measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_RestartPowerSafeOperatingAreaMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RESTART_POWER_SAFE_OPERATING_AREA_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds the result to the report list.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaAddToReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the safe operation area scaling.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR scale/Selects the scale for the result diagram.
/// HIPAR maskScale/Sets the scale for the mask, linear or logarithmic.
/// HIPAR displayScale/Sets a linear or a logarithmic scaled for the displayed results.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaScaling(ViSession instrSession,
                                                      ViInt32   scale,
                                                      ViInt32   maskScale,
                                                      ViInt32   displayScale)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SCALE, scale),
    		2, "Scale");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_MASK_SCALE, maskScale),
			3, "Mask Scale");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_DISPLAY_SCALE, displayScale),
			4, "Display Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function manages the safe operating area linear point measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR operation/Selects the operation.
/// HIPAR pointNumber/Sets the point number.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLinPointManagement(
							ViSession instrSession,
							ViInt32   operation,
							ViInt32   pointNumber)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, operation, RSRTX_VAL_ADD, RSRTX_VAL_INSERT),
			2, "Operation");

	switch (operation)
	{
		case RSRTX_VAL_ADD:

			    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LIN_ADD, NULL));
		 break;

		 case RSRTX_VAL_INSERT:

	            viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_INSERT, pointNumber),
	            		3, "Point Number");
		 break;

		 case RSRTX_VAL_REMOVE:

	            viCheckParm(rsrtx_SetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_REMOVE, pointNumber),
	            		3, "Point Number");

		 break;

		 default:
			    viCheckParm(RsCore_InvalidViInt32Value(instrSession, operation), 2, "Operation");
		 break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the voltage/current value of the SOA point
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the value type.
/// HIPAR value/Sets the point value.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLinPointValue(ViSession instrSession,
                                                            ViInt32   pointNumber,
                                                            ViInt32   valueType,
                                                            ViReal64  value)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOURCE_CURRENT_MIN, RSRTX_VAL_POWER_SOURCE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
    {
        case RSRTX_VAL_POWER_SOURCE_CURRENT_MIN:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT_MIN, value),
            		4, "Value");
            break;
        case RSRTX_VAL_POWER_SOURCE_CURRENT_MAX:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT_MAX, value),
            		4, "Value");
            break;
		case RSRTX_VAL_POWER_SOURCE_VOLTAGE:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_VOLTAGE, value),
            		4, "Value");
            break;
		case RSRTX_VAL_POWER_SOURCE_CURRENT:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_POINT_CURRENT, value),
            		4, "Value");
            default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		    break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Queries the number of points.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR count/Returns the number of points
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaLinCount(ViSession instrSession,
                                                            ViInt32   *count)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LINEAR_COUNT, count),
			2, "Count");

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function starts the safe operating area measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR operation/Selects the operation.
/// HIPAR pointNumber/Sets the point number.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLogPointManagement(
							ViSession instrSession,
							ViInt32   operation,
							ViInt32   pointNumber)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, operation, RSRTX_VAL_ADD, RSRTX_VAL_INSERT),
			2, "Operation");

	switch (operation)
	{
		case RSRTX_VAL_ADD:

			    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_ADD, NULL));
		 break;

		 case RSRTX_VAL_INSERT:

	            viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_INSERT, pointNumber),
	            		3, "Point Number");
		 break;

		 case RSRTX_VAL_REMOVE:

	            viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_REMOVE, pointNumber),
	            		3, "Point Number");

		 break;

		 default:
			    viCheckParm(RsCore_InvalidViInt32Value(instrSession, operation), 2, "Operation");
		 break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the voltage/current value of the SOA point
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the value type.
/// HIPAR value/Sets the point value.
ViStatus _VI_FUNC rsrtx_PowerSafeOperatingAreaLogPointValue(ViSession instrSession,
                                                            ViInt32   pointNumber,
                                                            ViInt32   valueType,
                                                            ViReal64  value)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOURCE_CURRENT_MIN, RSRTX_VAL_POWER_SOURCE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
    {
        case RSRTX_VAL_POWER_SOURCE_CURRENT_MIN:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT_MIN, value),
            		4, "Value");
            break;
        case RSRTX_VAL_POWER_SOURCE_CURRENT_MAX:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT_MAX, value),
            		4, "Value");
            break;
		case RSRTX_VAL_POWER_SOURCE_VOLTAGE:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_VOLTAGE, value),
            		4, "Value");
            break;
		case RSRTX_VAL_POWER_SOURCE_CURRENT:
            viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_POINT_CURRENT, value),
            		4, "Value");
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Queries the number of points.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR count/Returns the number of points.
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaLogCount(ViSession instrSession,
                                                            ViInt32   *count)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_LOGARITHMIC_COUNT, count),
    		2, "Count");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function Returns the results of the safe acquisition point measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR result/Returns the results of the safe acquisition point measurement..
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAcquisitionPointResults(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64  *result)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
    {
        case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION_CURRENT, result),
            		4, "Result");
            break;
        case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION_VOLTAGE, result),
            		4, "Result");
            break;

        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the current and voltage value for the corresponding
/// HIFN  acquisition violation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR current/Returns the current.
/// HIPAR voltage/Returns voltage.
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaResultAcquisitionViolation(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViReal64* current,
							ViReal64* voltage)
{
    ViStatus error = VI_SUCCESS;
    ViChar   response[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViChar   *p2response;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidNullPointer(instrSession, current), 3, "Current");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, voltage), 4, "Voltage");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
    		2, "Point Number");

    checkErr(rsrtx_GetAttributeViString(instrSession, NULL,
        RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VIOLATION, RS_MAX_MESSAGE_BUF_SIZE, response));

	p2response = strtok (response, ",");

	if (p2response != NULL)
		*current = RsCore_Convert_String_To_ViReal64(p2response);

	p2response = strtok (NULL, ",\n");

	if (p2response != NULL)
		*voltage = RsCore_Convert_String_To_ViReal64(p2response);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates measurement and returns returns the current or
/// HIFN  voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform
/// HIPAR maximumTime/operation to complete.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array.  The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_ReadPowerSafeOperatingAreaAcquisitionData(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViInt32   waveformSize,
							ViInt32   maximumTime,
							ViReal64  waveformArray[],
							ViInt32*  actualPoints,
							ViReal64* initialX,
							ViReal64* xIncrement)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  old_tout = 0;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &old_tout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_InitiateAcquisition(instrSession, RSRTX_VAL_INIT_SINGLE));
    checkErr(rsrtx_FetchPowerSafeOperatingAreaAcquisitionData(instrSession, pointNumber, valueType, waveformSize,
                                                                             waveformArray, actualPoints, initialX,
                                                                             xIncrement));

Error:
	(void)rsrtx_SetOPCTimeout(instrSession, old_tout);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function returns the current or voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the vertical values - voltages of recorded waveform samples,
/// HIPAR waveformArray/or magnitudes of a spectrum.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform
/// HIPAR actualPoints/Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array.  The time
/// HIPAR initialX/is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the Waveform Array.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionData(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViInt32   waveformSize,
							ViReal64  waveformArray[],
							ViInt32*  actualPoints,
							ViReal64* initialX,
							ViReal64* xIncrement)
{
 	ViStatus error = VI_SUCCESS;
 	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_START, initialX),
             		7, "Initial X");

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_INCREMENT, xIncrement),
             		8, "X Increment");

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;POW:SOA:RES:ACQ:VIOL%ld:CURR:DATA?", pointNumber);
			 checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

		break;

	    case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_START, initialX),
					7, "Initial X");

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_INCREMENT, xIncrement),
             		8, "X Increment");

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;POW:SOA:RES:ACQ:VIOL%ld:VOLT:DATA?", pointNumber);
			 checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));
		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	}

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns information of the current or voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesperSample/Number of values per sample interval, usually 2.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionDataHeader(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64* xStart,
							ViReal64* xStop,
							ViInt32*  recordLength,
							ViInt32*  valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SOA:RES:ACQ:VIOL%ld:CURR:DATA:HEAD?", pointNumber);
			 checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
			 *recordLength = (ViInt32)aux1;
			 *valuesPerSample = (ViInt32)aux2;
			 checkErr(rsrtx_CheckStatus(instrSession));
    	break;

		case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:

			snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SOA:RES:ACQ:VIOL%ld:VOLT:DATA:HEAD?", pointNumber);
			 checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
			 *recordLength = (ViInt32)aux1;
			 *valuesPerSample = (ViInt32)aux2;
			 checkErr(rsrtx_CheckStatus(instrSession));
		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the
/// HIPAR xIncrement/indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaAcquisitionConversionData(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64* xStart,
							ViReal64* xIncrement,
							ViReal64* yStart,
							ViReal64* yIncrement,
							ViInt32*  yResolution)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_START, xStart),
				4, "X Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_X_INCREMENT, xIncrement),
        		5, "X Increment");

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_START, yStart),
				6, "Y Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_INCREMENT, yIncrement),
        		7, "Y Increment");

		viCheckParm(rsrtx_GetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_CURRENT_DATA_CONVERSION_Y_RESOLUTION, yResolution),
				8, "Y Resolution");

		break;

		case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_START, xStart),
				4, "X Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_X_INCREMENT, xIncrement),
        		5, "X Increment");

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_START, yStart),
				6, "Y Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_INCREMENT, yIncrement),
        		7, "Y Increment");

		viCheckParm(rsrtx_GetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_ACQUISITION_VOLTAGE_DATA_CONVERSION_Y_RESOLUTION, yResolution),
				8, "Y Resolution");

		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the voltage/current results of the total violation of SOA point measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR result/Returns the voltage and the current of the total violation of SOA point measurement.
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingTotalPointResults(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64  *result)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
    {
        case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION_CURRENT, result),
            		4, "Result");
            break;
        case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:
            viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION_VOLTAGE, result),
            		4, "Result");
            break;

        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the current and voltage value for the corresponding total
/// HIFN  violation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR current/Returns the current.
/// HIPAR voltage/Returns voltage.
ViStatus _VI_FUNC rsrtx_QueryPowerSafeOperatingAreaResultTotalViolation(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViReal64* current,
							ViReal64* voltage)
{
    ViStatus error = VI_SUCCESS;
    ViChar   response[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViChar   *p2response;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidNullPointer(instrSession, current), 3, "Current");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, voltage), 4, "Voltage");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
    		2, "Point Number");

    checkErr(rsrtx_GetAttributeViString(instrSession, NULL,
        RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VIOLATION, RS_MAX_MESSAGE_BUF_SIZE, response));

	p2response = strtok (response, ",");

	if (p2response != NULL)
		*current = RsCore_Convert_String_To_ViReal64(p2response);

	p2response = strtok (NULL, ",\n");

	if (p2response != NULL)
		*voltage = RsCore_Convert_String_To_ViReal64(p2response);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function initiates measurement and returns returns the current or voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR maximumTime/Pass the maximum length of time in which to allow the read waveform operation to complete.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array. The time is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the WaveformArray.
ViStatus _VI_FUNC rsrtx_ReadPowerSafeOperatingAreaTotalData(ViSession instrSession,
                                                            ViInt32   pointNumber,
                                                            ViInt32   valueType,
                                                            ViInt32   waveformSize,
                                                            ViInt32   maximumTime,
                                                            ViReal64  waveformArray[],
                                                            ViInt32   *actualPoints,
                                                            ViReal64  *initialX,
                                                            ViReal64  *xIncrement)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  old_tout = 0;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &old_tout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

    checkErr(rsrtx_InitiateAcquisition(instrSession, RSRTX_VAL_INIT_SINGLE));
    checkErr(rsrtx_FetchPowerSafeOperatingAreaTotalData(instrSession, pointNumber, valueType, waveformSize,
                                                                             waveformArray, actualPoints, initialX,
                                                                             xIncrement));

Error:
	rsrtx_SetOPCTimeout(instrSession, old_tout);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the current or voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR waveformSize/Pass the number of elements in the Waveform Array parameter.
/// HIPAR waveformArray/Returns the waveform that the oscilloscope acquires.
/// HIPAR actualPoints/Indicates the number of points the function places in the Waveform Array parameter.
/// HIPAR initialX/Indicates the time of the first point in the Waveform Array. The time is relative to the trigger event.
/// HIPAR xIncrement/Indicates the length of time between points in the WaveformArray.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalData(ViSession instrSession,
                                                             ViInt32   pointNumber,
                                                             ViInt32   valueType,
                                                             ViInt32   waveformSize,
                                                             ViReal64  waveformArray[],
                                                             ViInt32   *actualPoints,
                                                             ViReal64  *initialX,
                                                             ViReal64  *xIncrement)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_START, initialX),
             		7, "Initial X");

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_INCREMENT, xIncrement),
             		8, "X Increment");

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;POW:SOA:RES:TOT:VIOL%ld:CURR:DATA?", pointNumber);
			 checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));

		break;

	    case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:
			viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_START, initialX),
					7, "Initial X");

             viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_INCREMENT, xIncrement),
             		8, "X Increment");

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "FORM REAL,32;POW:SOA:RES:TOT:VIOL%ld:VOLT:DATA?", pointNumber);
			 checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, cmd, waveformSize, waveformArray, actualPoints));
		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	}

Error:
	(void)(RsCore_Write(instrSession, "FORM ASCII"));
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns information of the current or voltage data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR xStart/X Start in seconds.
/// HIPAR xStop/X Stop in seconds.
/// HIPAR recordLength/Record length of the waveform in Samples.
/// HIPAR valuesPerSample/Number of values per sample interval, usually 2.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalDataHeader(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64  *xStart,
							ViReal64  *xStop,
							ViInt32   *recordLength,
							ViInt32   *valuesPerSample)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 aux1, aux2;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SOA:RES:TOT:VIOL%ld:CURR:DATA:HEAD?", pointNumber);
			 checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
			 *recordLength = (ViInt32)aux1;
			 *valuesPerSample = (ViInt32)aux2;
			 checkErr(rsrtx_CheckStatus(instrSession));
    	break;

		case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:

			 snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "POW:SOA:RES:TOT:VIOL%ld:VOLT:DATA:HEAD?", pointNumber);
			 checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, xStart, xStop, &aux1, &aux2));
			 *recordLength = (ViInt32)aux1;
			 *valuesPerSample = (ViInt32)aux2;
			 checkErr(rsrtx_CheckStatus(instrSession));
		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the conversion data.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointNumber/Sets the point number.
/// HIPAR valueType/Sets the result type.
/// HIPAR xStart/Return the time of the first sample of the indicated waveform.
/// HIPAR xIncrement/Return the time difference between two adjacent samples of the indicated waveform.
/// HIPAR yStart/Return the voltage value for binary value 0 of the indicated waveform.
/// HIPAR yIncrement/Return the voltage value per bit of the indicated waveform.
/// HIPAR yResolution/Return the vertical bit resolution of the indicated waveform.
ViStatus _VI_FUNC rsrtx_FetchPowerSafeOperatingAreaTotalConversionData(
							ViSession instrSession,
							ViInt32   pointNumber,
							ViInt32   valueType,
							ViReal64  *xStart,
							ViReal64  *xIncrement,
							ViReal64  *yStart,
							ViReal64  *yIncrement,
							ViInt32   *yResolution)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, valueType, RSRTX_VAL_POWER_SOA_TYPE_CURRENT, RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE),
			3, "Value Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, pointNumber),
			2, "Point Number");

	switch (valueType)
	{
		case RSRTX_VAL_POWER_SOA_TYPE_CURRENT:

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_START, xStart),
				4, "X Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_X_INCREMENT, xIncrement),
        		5, "X Increment");

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_START, yStart),
				6, "Y Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_INCREMENT, yIncrement),
        		7, "Y Increment");

		viCheckParm(rsrtx_GetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_CURRENT_DATA_CONVERSION_Y_RESOLUTION, yResolution),
				8, "Y Resolution");

		break;

		case RSRTX_VAL_POWER_SOA_TYPE_VOLTAGE:

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_START, xStart),
				4, "X Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_X_INCREMENT, xIncrement),
        		5, "X Increment");

		viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_START, yStart),
				6, "Y Start");

        viCheckParm(rsrtx_GetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_INCREMENT, yIncrement),
        		7, "Y Increment");

		viCheckParm(rsrtx_GetAttributeViInt32(instrSession, NULL, RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_RESULT_TOTAL_VOLTAGE_DATA_CONVERSION_Y_RESOLUTION, yResolution),
				8, "Y Resolution");

		break;

		default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, valueType), 3, "Value Type");
		break;
	 }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function starts the power transient response measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartPowerTransientResponseMeasurement(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_POWER_TRANSIENT_RESPONSE_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function starts the power transient response measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR signalHigh/Sets the expected signal high voltage value.
/// HIPAR signalLow/Sets the expected signal low voltage value.
/// HIPAR startTime/Sets the start time.
/// HIPAR stopTime/Sets the stop time.
ViStatus _VI_FUNC rsrtx_TransientResponseSettings(ViSession instrSession,
                                                  ViReal64  signalHigh,
                                                  ViReal64  signalLow,
                                                  ViReal64  startTime,
                                                  ViReal64  stopTime)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SIGNAL_HIGH, signalHigh),
    		2, "Signal High");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SIGNAL_LOW, signalLow),
			3, "Signal Low");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_START_TIME, startTime),
			4, "Start Time");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, NULL, RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_STOP_TIME, stopTime),
			5, "Stop Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function adds the result to the report list.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_TransientResponseAddToReport(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_ADD_REPORT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the results of the transient response measurement
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Sets the result type.
/// HIPAR result/Returns the result.
ViStatus _VI_FUNC rsrtx_QueryPowerTransientResponseResult(ViSession instrSession,
                                                          ViInt32   type,
                                                          ViReal64  *result)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, type, RSRTX_VAL_POWER_TRANSIENT_MEAS_OVERSHOOT, RSRTX_VAL_POWER_TRANSIENT_MEAS_SETTLING),
			2, "Type");
	switch (type)
	{

		case RSRTX_VAL_POWER_TRANSIENT_MEAS_OVERSHOOT:
			 viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_OVERSHOOT, result),
			 		3, "Result");
			 break;
		case RSRTX_VAL_POWER_TRANSIENT_MEAS_RISE_TIME:
			 viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_RISE_TIME, result),
			 		3, "Result");
			 break;
		case RSRTX_VAL_POWER_TRANSIENT_MEAS_DELAY_TIME:
					viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_DELAY_TIME, result),
							3, "Result");
			 break;
		case RSRTX_VAL_POWER_TRANSIENT_MEAS_PEAK_TIME:
					viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_PEAK_TIME, result),
							3, "Result");
			break;
		case RSRTX_VAL_POWER_TRANSIENT_MEAS_PEAK_VALUE:
					viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_PEAK_VALUE, result),
							3, "Result");
			break;
		case RSRTX_VAL_POWER_TRANSIENT_MEAS_SETTLING:
					viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_POWER_TRANSIENT_RESPONSE_SETTLING_TIME, result),
							3, "Result");
			break;
			default:
			viCheckParm(RsCore_InvalidViInt32Value(instrSession, type), 2, "Type");
			break;
	}

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function enables the spectrum analysis.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/This control enables the spectrum analysis.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisState(ViSession instrSession,
                                                       ViBoolean state)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_ANALYSIS_ENABLE, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures spectrum anaylsis mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/Configures spectrum anaylsis mode.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMode(ViSession instrSession,
                                                      ViInt32   mode)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_ANALYSIS_MODE, mode),
    		2, "mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function selects the source for the spectrum analysis diagrams.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Selects the source for the spectrum analysis diagrams.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisSource(ViSession instrSession,
                                                        ViInt32   source)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_ANALYSIS_SOURCE, source),
    		2, "Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function configures the spectrum analysis frequency.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR start/Defines the start frequency of the displayed frequency domain at the
/// HIPAR start/left display edge: Center - Span/2
/// HIPAR stop/Defines the stop frequency of the displayed frequency domain at the
/// HIPAR stop/right display edge: Center + Span/2
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisFrequency(ViSession instrSession,
                                                           ViReal64  start,
                                                           ViReal64  stop)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_FREQUENCY_START, start),
    		2, "Start");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "",
                                                 RSRTX_ATTR_SPECTRUM_FREQUENCY_STOP,
                                                 stop), 3, "Stop")

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the spectrum analysis frequency.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR center/Defines the position of the displayed frequency domain, which is
/// HIPAR center/(Center - Span/2) to (Center + Span/2). The width of the domain is
/// HIPAR center/defined using the command SPECtrum:FREQuency:SPAN.
/// HIPAR span/The span is specified in Hertz and defines the width of the displayed
/// HIPAR span/frequency range, which is (Center - Span/2) to (Center + Span/2).
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisFrequencyCenterSpan(
							ViSession instrSession,
							ViReal64  center,
							ViReal64  span)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_FREQUENCY_CENTER, center),
			2, "Center");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_FREQUENCY_SPAN, span),
			3, "Span");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Performs the spectrum analysis calculation for the full frequency
/// HIFN  span.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_FREQUENCY_FULL_SPAN
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:FREQuency:FULLspan
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumFrequencyFullSpan(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SPECTRUM_FREQUENCY_FULL_SPAN, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function enables the spectrum analysis.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR spectrum/Enables or diables the indicated waveform.
/// HIPAR minHold/Enables or diables the indicated waveform.
/// HIPAR maxHold/Enables or diables the indicated waveform.
/// HIPAR average/Enables or diables the indicated waveform.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisWaveform(ViSession instrSession,
                                                          ViBoolean spectrum,
                                                          ViBoolean minHold,
                                                          ViBoolean maxHold,
                                                          ViBoolean average)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_WAVEFORM_ENABLE, spectrum),
    		2, "Spectrum");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_WAVEFORM_MINIMUM_ENABLE, minHold),
			3, "Min Hold");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_WAVEFORM_MAXIMUM_ENABLE, maxHold),
			4, "Max Hold");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_WAVEFORM_AVERAGE_ENABLE, average),
			5, "Average");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function configures the spectrum analysis time domain.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR position/Sets the time position of the analyzed time range.
/// HIPAR range/Sets the time range for the time domain diagram.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisTimeDomain(ViSession instrSession,
                                                            ViReal64  position,
                                                            ViReal64  range)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_TIME_DOMAIN_POSITION, position),
    		2, "Position");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_TIME_DOMAIN_RANGE, range),
			3, "Range");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function configures the spectrum analysis display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR colorScheme/Sets the color scale for the display of the waveform in the frequency
/// HIPAR colorScheme/domain diagram.
/// HIPAR magnitudeMode/Enables the magnitude coloring of the waveform.
/// HIPAR minimum/Sets the level used as a minimum of the color scale selected with
/// HIPAR minimum/SPECtrum:DIAGram:COLor:SCHeme:FDOMain/SPECtrum:DIAGram:COLor:SCHeme:SPECtrogramm.
/// HIPAR minimum/All level values lower than the minimum will be displayed with the
/// HIPAR minimum/minimum color.
/// HIPAR maximum/Sets the level used as a maximum of the color scale selected with
/// HIPAR maximum/SPECtrum:DIAGram:COLor:SCHeme:FDOMain/SPECtrum:DIAGram:COLor:SCHeme:SPECtrogramm.
/// HIPAR maximum/All level values lower than the minimum will be displayed with the
/// HIPAR maximum/minimum color.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisDisplay(ViSession instrSession,
                                                         ViInt32   colorScheme,
                                                         ViBoolean magnitudeMode,
                                                         ViReal64  minimum,
                                                         ViReal64  maximum)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_DISPLAY_COLOR_SCHEME, colorScheme),
    		2, "Color Scheme");

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_DISPLAY_MAGNITUDE_MODE, magnitudeMode),
			3, "Magnitude Mode");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DISPLAY_MINIMUM_LEVEL, minimum),
    		4, "Minimum");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_DISPLAY_MAXIMUM_LEVEL, maximum),
			5, "Maximum");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function Enables the usage of markers.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Enables the usage of markers.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerState(ViSession instrSession,
                                                             ViBoolean state)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_SPECTRUM_MARKER_ENABLE, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function sets the source for the marker search function.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Sets the source for the marker search function.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerSource(
							ViSession instrSession,
							ViInt32   source)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MARKER_SOURCE, source),
    		2, "Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function sets the mode for the selection of the reference peak.
/// HIFN  The peak with the highest level within the selected settings is set as
/// HIFN  the reference marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR reference/Sets the mode for the selection of the reference peak. The peak with
/// HIPAR reference/the highest level within the selected settings is set as the reference
/// HIPAR reference/marker.
ViStatus _VI_FUNC rsrtx_ConfigureSpectrumAnalysisMarkerReference(
							ViSession instrSession,
							ViInt32   reference)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_SPECTRUM_MARKER_REFERENCE_MODE, reference),
    		2, "Reference");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the range to the center of the screen.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_SpectrumMarkerSetupCenterScreen(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SPECTRUM_MARKER_SETUP_CENTER_SCREEN, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the range to the highest peak.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_SpectrumMarkerSetupRangeToPeak(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SPECTRUM_MARKER_SETUP_RANGE_TO_PEAK, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the frequency and the level values of the present reference
/// HIFN  marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Returns the result frequency.
/// HIPAR level/Returns the result level.
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerResults(ViSession instrSession,
                                                            ViReal64* frequency,
                                                            ViReal64* level)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RMAR?");
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, frequency, level, NULL, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the frequency of the reference marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_FREQUENCY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:MARKer:RMARker:FREQuency?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Returns the frequency of the reference marker.
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerFrequency(
							ViSession instrSession,
							ViReal64* frequency)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_FREQUENCY, frequency),
    		2, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the level of the reference marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_LEVEL
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SPECtrum:MARKer:RMARker:LEVel?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR markerLevel/Returns the level of the reference marker.
ViStatus _VI_FUNC rsrtx_QuerySpectrumReferenceMarkerLevel(ViSession instrSession,
                                                          ViReal64* markerLevel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_SPECTRUM_REFERENCE_MARKER_LEVEL, markerLevel),
    		2, "Marker Level");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the frequency and level values of the n-th marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR result/Selects the result number.
/// HIPAR frequency/Returns the result frequency.
/// HIPAR level/Returns the result level.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerResults(ViSession instrSession,
                                                   ViInt32   result,
                                                   ViReal64* frequency,
                                                   ViReal64* level)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld?", result);
	checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, frequency, level, NULL, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the frequency of the n-th marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR marker/Selects the marker number.
/// HIPAR frequency/Returns selected marker frequency.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerFrequency(ViSession instrSession,
                                                     ViInt32   marker,
                                                     ViReal64* frequency)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:FREQ?", marker);
	checkErr(RsCore_QueryViReal64(instrSession, cmd, frequency));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the delta frequency, the difference between the frequency of
/// HIFN  the specified marker and the frequency of the reference marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR marker/Selects the marker number.
/// HIPAR deltaFrequency/Returns the delta frequency, the difference between the frequency of
/// HIPAR deltaFrequency/the specified marker and the frequency of the reference marker.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerFrequencyDelta(ViSession instrSession,
                                                          ViInt32   marker,
                                                          ViReal64* deltaFrequency)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:FREQ:DELT?", marker);
	checkErr(RsCore_QueryViReal64(instrSession, cmd, deltaFrequency));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the level of the n-th marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR marker/Selects the marker number.
/// HIPAR level/Returns the level of the n-th marker.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerLevel(ViSession instrSession,
                                                 ViInt32   marker,
                                                 ViReal64* level)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:LEV?", marker);
	checkErr(RsCore_QueryViReal64(instrSession, cmd, level));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the delta level, the difference between the level of the
/// HIFN  specified marker and the level of the reference marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR marker/Selects the marker number.
/// HIPAR deltaLevel/Returns the delta level, the difference between the level of the
/// HIPAR deltaLevel/specified marker and the level of the reference marker.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerLevelDelta(ViSession instrSession,
                                                      ViInt32   marker,
                                                      ViReal64* deltaLevel)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:LEV:DELT?", marker);
	checkErr(RsCore_QueryViReal64(instrSession, cmd, deltaLevel));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the difference in the values between the n-th marker and the
/// HIFN  reference marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR result/Selects the result number.
/// HIPAR frequency/Returns the result delta frequency.
/// HIPAR level/Returns the result delta level.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerDeltaResults(ViSession instrSession,
                                                        ViInt32   result,
                                                        ViReal64* frequency,
                                                        ViReal64* level)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:DELT?", result);
    checkErr(RsCore_QueryTupleViReal64(instrSession, cmd, frequency, level, NULL, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns a list of all marker with the corresponding frequency and
/// HIFN  level values.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR result/Selects the result number.
/// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR frequency/Returns the result frequencies.
/// HIPAR level/Returns the result levels.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerAllResults(ViSession instrSession,
                                                      ViInt32   result,
                                                      ViInt32   arraySize,
                                                      ViReal64  frequency[],
                                                      ViReal64  level[],
                                                      ViInt32*  returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 *data = NULL;
	ViInt32  dataSize;
	ViInt32  i = 0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:ALL?", result);
	checkErr(RsCore_QueryFloatArray(instrSession, cmd, &data, &dataSize));

	*returnedValues = dataSize / 2;
	for (i = 0; i < arraySize; i++)
	{
		frequency[i] = data[i * 2];
		level[i] = data[i * 2 + 1];
	}

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
	if (data) free(data);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Queries the delta frequency and delta level, the difference between
/// HIFN  the freqeuncy/level of the specified marker and the freqeuncy/level of
/// HIFN  the reference marker.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR result/Selects the result number.
/// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR frequency/Returns the result delta frequencies.
/// HIPAR level/Returns the result delta levels.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QuerySpectrumMarkerAllDeltaResults(ViSession instrSession,
                                                           ViInt32   result,
                                                           ViInt32   arraySize,
                                                           ViReal64  frequency[],
                                                           ViReal64  level[],
                                                           ViInt32*  returnedValues)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
	ViReal64 *data = NULL;
	ViInt32  dataSize;
	ViInt32  i=0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_CheckInstrumentModel(instrSession, "!RTB"));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "SPEC:MARK:RES%ld:ALL:DELT?", result);
	checkErr(RsCore_QueryFloatArray(instrSession, cmd, &data, &dataSize));

	*returnedValues = dataSize / 2;
	for (i = 0; i < arraySize; i++)
	{
		frequency[i] = data[i * 2];
		level[i] = data[i * 2 + 1];
	}

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
	if (data) free(data);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Enables the Bode plot diagram.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR enable/Enables the Bode plot diagram.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotEnable(ViSession instrSession,
                                                ViBoolean enable)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, NULL, RSRTX_ATTR_BODE_PLOT_ENABLE, enable),
    		2, "Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the data of the frequency waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR frequencyData/Returns the data of the frequency waveform.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryBodePlotFrequencyData(ViSession instrSession,
                                                   ViInt32   arraySize,
                                                   ViReal64  frequencyData[],
                                                   ViInt32*  returnedValues)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "BPL:FREQ:DATA?", arraySize, frequencyData, returnedValues));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the data of the gain waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR gainData/Returns the data of the gain waveform.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryBodePlotGainData(ViSession instrSession,
                                              ViInt32   arraySize,
                                              ViReal64  gainData[],
                                              ViInt32*  returnedValues)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "BPL:GAIN:DATA?", arraySize, gainData, returnedValues));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the data of the phase waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session./// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR arraySize/Pass the number of values allocated for result arrays.
/// HIPAR phaseData/Returns the data of the phase waveform.
/// HIPAR returnedValues/Returns number of results returned from the instrument.
ViStatus _VI_FUNC rsrtx_QueryBodePlotPhaseData(ViSession instrSession,
                                               ViInt32   arraySize,
                                               ViReal64  phaseData[],
                                               ViInt32*  returnedValues)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryFloatArrayToUserBuffer(instrSession, "BPL:PHAS:DATA?", arraySize, phaseData, returnedValues));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the type of waveform to be generated for the function generator.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR functionType/Sets the type of waveform to be generated for the function generator.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFunctionType(
							ViSession instrSession,
							ViInt32   functionType)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FUNCTION_TYPE, functionType),
    		2, "Function Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the frequency of the waveform. The available frequency range
/// HIFN  depends on the selected function type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Sets the frequency of the waveform. The available frequency range
/// HIPAR frequency/depends on the selected function type.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFrequency(ViSession instrSession,
                                                            ViReal64  frequency)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FREQUENCY, frequency),
    		2, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the start and stop frequency of the sweep for the Bode plot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_START_FREQUENCY
/// HIFN     RSRTX_ATTR_BODE_PLOT_STOP_FREQUENCY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:FREQuency:STARt
/// HIFN     BPLot:FREQuency:STOP
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR startFrequency/Sets the start frequency of the sweep for the Bode plot.
/// HIPAR stopFrequency/Sets the stop frequency of the sweep for the Bode plot.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotSweepFrequencies(ViSession instrSession,
                                                          ViReal64  startFrequency,
                                                          ViReal64  stopFrequency)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_START_FREQUENCY, startFrequency),
    		2, "Start Frequency");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_STOP_FREQUENCY, stopFrequency),
    		3, "Stop Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the channel for the input signal of the DUT.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_INPUT_CHANNEL
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:INPut[:SOURce]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodePlotInputChannel/Selects the channel for the input signal of the DUT.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotInputChannel(ViSession instrSession,
                                                      ViInt32   bodePlotInputChannel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_BODE_PLOT_INPUT_CHANNEL, bodePlotInputChannel),
    		2, "Bode Plot Input Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the channel for the output signal of the DUT.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_OUTPUT_CHANNEL
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:OUTPut[:SOURce]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodePlotOutputChannel/Selects the channel for the output signal of the DUT.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotOutputChannel(ViSession instrSession,
                                                       ViInt32   bodePlotOutputChannel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_BODE_PLOT_OUTPUT_CHANNEL, bodePlotOutputChannel),
    		2, "Bode Plot Output Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Contains settings for the gain waveform for the Bode plot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_GAIN_ENABLE
/// HIFN     RSRTX_ATTR_BODE_PLOT_GAIN_POSITION
/// HIFN     RSRTX_ATTR_BODE_PLOT_GAIN_SCALE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:GAIN:ENABle
/// HIFN     BPLot:GAIN:POSition
/// HIFN     BPLot:GAIN:SCALe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR gainEnable/Enables the gain waveform for the Bode plot.
/// HIPAR gainPosition/Sets the vertical position of the gain waveform in divisions.
/// HIPAR gainScale/Sets the vertical scale for the gain waveform.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotGainSettings(ViSession instrSession,
                                                      ViBoolean gainEnable,
                                                      ViReal64  gainPosition,
                                                      ViReal64  gainScale)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_BODE_PLOT_GAIN_ENABLE, gainEnable),
    		2, "Gain Enable");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_GAIN_POSITION, gainPosition),
			3, "Gain Position");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_GAIN_SCALE, gainScale),
			4, "Gain Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the settings for the phase waveform for the Bode plot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_PHASE_ENABLE
/// HIFN     RSRTX_ATTR_BODE_PLOT_PHASE_POSITION
/// HIFN     RSRTX_ATTR_BODE_PLOT_PHASE_SCALE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:PHASe:ENABle?
/// HIFN     BPLot:PHASe:POSition?
/// HIFN     BPLot:PHASe:SCALe?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR phaseEnable/Enables the phase waveform for the Bode plot.
/// HIPAR phasePosition/Sets the vertical position of the phase waveform in divisions.
/// HIPAR phaseScale/Sets the vertical scale for the phase waveform.
ViStatus _VI_FUNC rsrtx_QueryBodePlotPhaseSettings(ViSession  instrSession,
                                                   ViBoolean* phaseEnable,
                                                   ViReal64*  phasePosition,
                                                   ViReal64*  phaseScale)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViBoolean(instrSession, "", RSRTX_ATTR_BODE_PLOT_PHASE_ENABLE, phaseEnable),
    		2, "Phase Enable");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_PHASE_POSITION, phasePosition),
			3, "Phase Position");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_PHASE_SCALE, phaseScale),
			4, "Phase Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the amplitude mode.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_MODE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:AMPLitude:MODE
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR amplitudeMode/Sets the amplitude mode.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeMode(ViSession instrSession,
                                                       ViInt32   amplitudeMode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_BODE_PLOT_AMPLITUDE_MODE, amplitudeMode),
    		2, "Amplitude Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the amplitude waveform for the Bode plot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_ENABLE
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_POSITION
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_SCALE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:AMPLitude:ENABle
/// HIFN     BPLot:AMPLitude:POSition
/// HIFN     BPLot:AMPLitude:SCALe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR amplitudeEnable/Enables the amplitude waveform for the Bode plot.
/// HIPAR amplitudePosition/Sets the vertical position of the amplitude waveform in divisions.
/// HIPAR amplitudeScale/Sets the vertical scale for the amplitude waveform.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeSettings(ViSession instrSession,
                                                           ViBoolean amplitudeEnable,
                                                           ViReal64  amplitudePosition,
                                                           ViReal64  amplitudeScale)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_BODE_PLOT_AMPLITUDE_ENABLE, amplitudeEnable),
    		2, "Amplitude Enable");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_AMPLITUDE_POSITION, amplitudePosition),
			3, "Amplitude Position");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_AMPLITUDE_SCALE, amplitudeScale),
			4, "Amplitude Scale");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Starts or stops the Bode plot measurement.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MEASUREMENT_STATE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:STATe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementState/Starts the Bode plot measurement.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMeasurementState(ViSession instrSession,
                                                          ViInt32   measurementState)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_BODE_PLOT_MEASUREMENT_STATE, measurementState),
    		2, "Measurement State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Starts the Bode plot measurement.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_START_BODE_PLOT_MEASUREMENT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:STATe RUN
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StartBodePlotMeasurement(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_START_BODE_PLOT_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Stops the Bode plot measurement.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_STOP_BODE_PLOT_MEASUREMENT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:STATe STOP
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_StopBodePlotMeasurement(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_STOP_BODE_PLOT_MEASUREMENT, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets a time delay, that the system waits before measuring the next
/// HIFN  point of the bode plot.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MEASUREMENT_DELAY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MEASurement:DELay
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementDelay/Sets a time delay, that the system waits before measuring the next
/// HIPAR measurementDelay/point of the bode plot.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMeasurementDelay(ViSession instrSession,
                                                          ViReal64  measurementDelay)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MEASUREMENT_DELAY, measurementDelay),
    		2, "Measurement Delay");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Repeats the measurement, using the same parameters.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_REPEATED_MEASUREMENT_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:REPeat
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR repeatedMeasurementEnable/Repeats the measurement, using the same parameters.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotRepeatedMeasurementEnable(
							ViSession instrSession,
							ViBoolean repeatedMeasurementEnable)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_BODE_PLOT_REPEATED_MEASUREMENT_ENABLE, repeatedMeasurementEnable),
    		2, "Repeated Measurement Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the number of points per decade that are measured.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_POINTS_PER_DECADE
/// HIFN     RSRTX_ATTR_BODE_PLOT_MEASUREMENT_POINTS_DISPLAY_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:POINts:LOGarithmic
/// HIFN     BPLot:MEASurement:POINt[:DISPLAY]
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR pointsPerDecade/Sets the number of points per decade that are measured.
/// HIPAR pointsDisplayEnable/Enables the display of the measurement points in the bode plot.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotPointsSettings(ViSession instrSession,
                                                        ViInt32   pointsPerDecade,
                                                        ViBoolean pointsDisplayEnable)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_BODE_PLOT_POINTS_PER_DECADE, pointsPerDecade),
    		2, "Points per Decade");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_BODE_PLOT_MEASUREMENT_POINTS_DISPLAY_ENABLE, pointsDisplayEnable),
    		3, "Points Display Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects and saves acquisition timestamps table to a file.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_EXPORT_NAME
/// HIFN     RSRTX_ATTR_BODE_PLOT_EXPORT_SAVE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:EXPort:NAME
/// HIFN     BPLot:EXPort:SAVE
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR fileName/Path and file name to save Bode plot export data. File format is CSV
ViStatus _VI_FUNC rsrtx_ExportBodePlotTimestampTable(ViSession instrSession,
                                                     ViString  fileName)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_BODE_PLOT_EXPORT_NAME, fileName),
    		2, "File Name");
	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_BODE_PLOT_EXPORT_SAVE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the number of different points that you can define for the
/// HIFN  amplitude profile.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINTS
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:AMPLitude:PROFile:COUNt
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR profilePointsNumber/Sets the number of different points that you can define for the
/// HIPAR profilePointsNumber/amplitude profile.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeProfilePoints(
							ViSession instrSession,
							ViReal64  profilePointsNumber)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINTS, profilePointsNumber),
    		2, "Profile Points Number");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the amplitude and frequency of the specified point of the
/// HIFN  amplitude profile.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_AMPLITUDE
/// HIFN     RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_FREQUENCY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:AMPLitude:PROFile:POINt<n>:AMPLitude
/// HIFN     BPLot:AMPLitude:PROFile:POINt<n>:FREQuency
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR profilePoint/Selects the profile point.
/// HIPAR amplitude/Sets the amplitude of the specified point of the amplitude profile.
/// HIPAR frequency/Sets the frequency of the specified point of the amplitude profile.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotAmplitudeProfilePointSettings(
							ViSession instrSession,
							ViInt32   profilePoint,
							ViReal64  amplitude,
							ViReal64  frequency)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_AMPLITUDE,
    		"ProfilePoint", profilePoint - 1 , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Profile Point");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_AMPLITUDE, amplitude),
    		3, "Amplitude");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_BODE_PLOT_AMPLITUDE_PROFILE_POINT_FREQUENCY, frequency),
    		4, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the frequency for the specified marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:FREQuency
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodeMarker/Selects the bode marker.
/// HIPAR markerFrequency/Returns the frequency for the specified marker.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMarkerFrequency(ViSession instrSession,
                                                         ViInt32   bodeMarker,
                                                         ViReal64  markerFrequency)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY,
    		"BodeMarker", bodeMarker - 1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Bode Marker");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY, markerFrequency),
    		3, "Marker Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the index for the specified marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_INDEX
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:INDex
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodeMarker/Selects the bode marker.
/// HIPAR markerIndex/Returns the index for the specified marker.
ViStatus _VI_FUNC rsrtx_ConfigureBodePlotMarkerIndex(ViSession instrSession,
                                                     ViInt32   bodeMarker,
                                                     ViReal64  markerIndex)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_BODE_PLOT_MARKER_INDEX,
			"BodeMarker", bodeMarker - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "Bode Marker");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MARKER_INDEX, markerIndex),
    		3, "Marker Index");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Resets the markers to their initial positions. This is helpful if the
/// HIFN  markers have disappeared from the display or need to be moved for a
/// HIFN  larger distance.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_RESET_BODE_PLOT_MARKERS
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:SSCReen
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ResetBodePlotMarkers(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_RESET_BODE_PLOT_MARKERS, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the gain for the specified marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_GAIN
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:GAIN?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodeMarker/Selects the bode marker.
/// HIPAR markerGain/Returns the gain for the specified marker.
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerGain(ViSession instrSession,
                                                ViInt32   bodeMarker,
                                                ViReal64* markerGain)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_BODE_PLOT_MARKER_GAIN,
    		"BodeMarker", bodeMarker - 1 , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Bode Marker");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_BODE_PLOT_MARKER_GAIN, markerGain),
    		3, "Marker Gain");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the phase value for the specified marker.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_PHASE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:PHASe?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bodeMarker/Selects the bode marker.
/// HIPAR markerPhase/Returns the phase value for the specified marker.
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerPhase(ViSession instrSession,
                                                 ViInt32   bodeMarker,
                                                 ViReal64* markerPhase)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_BODE_PLOT_MARKER_PHASE,
			"BodeMarker", bodeMarker - 1, RS_REPCAP_BUF_SIZE, repCap),
			2, "Bode Marker");

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MARKER_PHASE, markerPhase),
    		3, "Marker Phase");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the delta value of the frequency, gain and phase between the
/// HIFN  two markers.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY_DIFFERENCE
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_GAIN_DIFFERENCE
/// HIFN     RSRTX_ATTR_BODE_PLOT_MARKER_PHASE_DIFFERENCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:MARKer<m>:DIFFerence:FREQ?
/// HIFN     BPLot:MARKer<m>:DIFFerence:GAIN?
/// HIFN     BPLot:MARKer<m>:DIFFerence:PHASe?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequencyDifference/Returns the delta value of the frequency between the two markers.
/// HIPAR gainDifference/Returns the delta value of the gain between the two markers.
/// HIPAR phaseDifference/Returns the delta value of the phase between the two markers.
ViStatus _VI_FUNC rsrtx_QueryBodePlotMarkerDifferences(ViSession instrSession,
                                                       ViReal64* frequencyDifference,
                                                       ViReal64* gainDifference,
                                                       ViReal64* phaseDifference)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MARKER_FREQUENCY_DIFFERENCE, frequencyDifference),
    		2, "Frequency Difference");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MARKER_GAIN_DIFFERENCE, gainDifference),
			3, "Gain Difference");

	viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_BODE_PLOT_MARKER_PHASE_DIFFERENCE, phaseDifference),
			4, "Phase Difference");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Deletes all test results.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_BODE_PLOT_RESET
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     BPLot:RESet
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ResetBodePlotResults(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_BODE_PLOT_RESET, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the pulse waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR dutyCycle/Sets the duty cycle for a square waveform. The duty cycle expresses
/// HIPAR dutyCycle/for what percentage of the period, the signal state is high.
/// HIPAR edgeTime/Configures pulse edge time.
ViStatus _VI_FUNC rsrtx_WaveformGeneratorPulse(ViSession instrSession,
                                               ViReal64  dutyCycle,
                                               ViReal64  edgeTime)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_PULSE_DUTY_CYCLE, dutyCycle),
    		2, "Duty Cycle");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_PULSE_EDGE_TIME, edgeTime),
			3, "Edge Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the ramp waveform polarity.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Configures the ramp waveform polarity.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorRampPolarity(
							ViSession instrSession,
							ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_RAMP_POLARITY, polarity),
    		2, "Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the exponential waveform polarity.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Configures the exponential waveform polarity.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorExponentialPolarity(
							ViSession instrSession,
							ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_EXPONENTIAL_POLARITY, polarity),
    		2, "Polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the waveform generator and outputs the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR enabled/Enables the waveform generator and outputs the waveform.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputState(
							ViSession instrSession,
							ViBoolean enabled)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_ENABLED, enabled),
    		2, "Enabled");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the amplitude, peak to peak voltage and offeset of the output
/// HIFN  waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR amplitude/Sets the amplitude, peak to peak voltage, of the output waveform. This
/// HIPAR amplitude/is defined as the voltage difference between the maximum and the
/// HIPAR amplitude/minimum voltage levels.
/// HIPAR offset/Sets a voltage offset.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputAmplitude(
							ViSession instrSession,
							ViReal64  amplitude,
							ViReal64  offset)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_AMPLITUDE, amplitude),
    		2, "Amplitude");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_OFFSET, offset),
			3, "Offset");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the load of the DUT at its connection.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR waveformGeneratorOutputUser/Sets the load of the DUT at its connection.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputUserLoad(
							ViSession instrSession,
							ViInt32   load)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_USER_LOAD, load),
    		2, "Load");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the output destination.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR destination/Configures the output destination.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorOutputDestination(
							ViSession instrSession,
							ViInt32   destination)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_OUTPUT_DESTINATION, destination),
    		2, "destination");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the noise level in percentage of the amplitude.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR percent/Sets the noise level in percentage of the amplitude.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorNoiseLevelPercent(
							ViSession instrSession,
							ViReal64  percent)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_NOISE_LEVEL_PERCENT, percent),
    		2, "percent");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the level of the noise in volts.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR level/Sets the level of the noise in volts.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorNoiseAbsoluteLevel(
							ViSession instrSession,
							ViReal64  level)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_NOISE_ABSOLUTE_LEVEL, level),
    		2, "Level");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures settings for genarator burst.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_ENABLE
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_CYCLES
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_IDLE_TIME
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_PHASE_OFFSET
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     WGENerator:BURSt[:STATe]
/// HIFN     WGENerator:BURSt:NCYCle
/// HIFN     WGENerator:BURSt:ITIMe
/// HIFN     WGENerator:BURSt:PHASe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR burstEnable/Enables or disables the burst for the generator.
/// HIPAR burstCycles/Sets the number of times the generator outputs one cycle of the
/// HIPAR burstCycles/waveform per burst.
/// HIPAR burstIdleTime/Sets the idle time between two burst cycles.
/// HIPAR burstPhaseOffset/Sets the start phase of the burst.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorBurstSettings(
							ViSession instrSession,
							ViBoolean burstEnable,
							ViInt32   burstCycles,
							ViReal64  burstIdleTime,
							ViReal64  burstPhaseOffset)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_ENABLE, burstEnable),
    		2, "Burst Enable");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_CYCLES, burstCycles),
			3, "Burst Cycles");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_IDLE_TIME, burstIdleTime),
    		4, "Burst Idle Time");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_BURST_PHASE_OFFSET, burstPhaseOffset),
			5, "Burst Phase Offset");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the waveform modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Enables the waveform modulation.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationState(
							ViSession instrSession,
							ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_ENABLED, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the modulation type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Sets the modulation type.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationType(
							ViSession instrSession,
							ViInt32   type)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_TYPE, type),
    		2, "type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the function type of modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Sets the function type of modulation.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationFunctionType(
							ViSession instrSession,
							ViInt32   type)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_FUNCTION_TYPE, type),
    		2, "type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the ramp waveform polarity.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Configures the ramp waveform polarity.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorModulationRampPolarity(
							ViSession instrSession,
							ViInt32   polarity)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_MODULATION_RAMP_POLARITY, polarity),
    		2, "polarity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the frequency a depth of the modulation waveform for amplitude
/// HIFN  modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Sets the frequency of the modulation waveform for amplitude
/// HIPAR frequency/modulation.
/// HIPAR depth/Sets the amplitude modulation depth.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorAMModulation(
							ViSession instrSession,
							ViReal64  frequency,
							ViReal64  depth)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_AM_MODULATION_FREQUENCY, frequency),
    		2, "Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_AM_MODULATION_DEPTH, depth),
			3, "Depth");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the frequency adn deviation of the modulation waveform for
/// HIFN  frequency modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Sets the frequency of the modulation waveform for frequency
/// HIPAR frequency/modulation.
/// HIPAR deviation/Sets the frequency deviation, the maximum difference between and FM
/// HIPAR deviation/modulated signal and the carrier signal.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFMModulation(
							ViSession instrSession,
							ViReal64  frequency,
							ViReal64  deviation)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FM_MODULATION_FREQUENCY, frequency),
    		2, "Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FM_MODULATION_FREQUENCY_DEVIATION, deviation),
			3, "deviation");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the ASK modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Sets the frequency of the modulation waveform for ASK modulation.
/// HIPAR depth/Sets the ASK modulation depth.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorASKModulation(
							ViSession instrSession,
							ViReal64  frequency,
							ViReal64  depth)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ASK_MODULATION_FREQUENCY, frequency),
    		2, "Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ASK_MODULATION_DEPTH, depth),
			3, "Depth");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the FSK modulation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Sets the hopping frequency.
/// HIPAR rate/Sets the hop rate, the time before a switch from the carrier frequency
/// HIPAR rate/and the modulation frequency.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorFSKModulation(
							ViSession instrSession,
							ViReal64  frequency,
							ViReal64  rate)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FSK_MODULATION_HOPPING_FREQUENCY, frequency),
    		2, "Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_FSK_MODULATION_RATE, rate),
			3, "rate");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the sweep.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Enables the sweep.
/// HIPAR type/Configures the sweep type.
/// HIPAR startFrequency/Sets the start frequency of the sweep range.
/// HIPAR stopFrequency/Sets the stop frequency of the sweep range.
/// HIPAR time/Sets the duration of the sweep.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorSweep(ViSession instrSession,
                                                        ViBoolean state,
                                                        ViInt32   type,
                                                        ViReal64  startFrequency,
                                                        ViReal64  stopFrequency,
                                                        ViReal64  time)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_ENABLED, state),
			2, "state");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_TYPE, type),
    		3, "Type");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_START_FREQUENCY, startFrequency),
			4, "Start Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_STOP_FREQUENCY, stopFrequency),
			5, "Stop Frequency");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_SWEEP_TIME, time),
			6, "Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Loads the arbitrary waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR file/Sets the file path and the file for an arbitrary waveform.
ViStatus _VI_FUNC rsrtx_WaveformGeneratorArbitraryOpenFile(ViSession instrSession,
                                                           ViString  file)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_FILE_NAME, file),
    		2, "File");

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_OPEN_FILE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the oscilloscope source, from which the arbitrary signal is
/// HIFN  loaded.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR source/Selects the oscilloscope source, from which the arbitrary signal is
/// HIPAR source/loaded.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitrarySource(
							ViSession instrSession,
							ViInt32   source)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_SOURCE, source),
    		2, "source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Loads the waveform from the selected signal source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_WaveformGeneratorArbitraryUpdate(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_UPDATE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the start and stop time of the copied waveform part in seconds.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_START
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_END
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     WGENerator:ARBitrary:RANGe:START
/// HIFN     WGENerator:ARBitrary:RANGe:STOP
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR rangeStart/Sets the start time of the copied waveform part in seconds.
/// HIPAR rangeEnd/Sets the end time of the copied waveform part in seconds.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitraryRange(
							ViSession instrSession,
							ViReal64  rangeStart,
							ViReal64  rangeEnd)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_START, rangeStart),
    		2, "Range Start");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_RANGE_END, rangeEnd),
    		3, "Range End");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the display of the arbitrary waveform.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_DISPLAY_ENABLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     WGENerator:ARBitrary:VISible
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR displayWaveformEnable/Enables the display of the arbitrary waveform.
ViStatus _VI_FUNC rsrtx_ConfigureWaveformGeneratorArbitraryDisplayEnable(
							ViSession instrSession,
							ViBoolean displayWaveformEnable)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_WAVEFORM_GENERATOR_ARBITRARY_DISPLAY_ENABLE, displayWaveformEnable),
    		2, "Display Waveform Enable");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Enables the pattern generator and outputs the waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR patternGeneratorEnabled/Enables the pattern generator and outputs the waveform.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorState(ViSession instrSession,
                                                       ViBoolean state)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_ENABLED, state),
    		2, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the function type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR functionType/Configures the function type.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorFunctionType(
							ViSession instrSession,
							ViInt32   functionType)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_FUNCTION_TYPE, functionType),
    		2, "Function Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures generator frequency.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR frequency/Configures generator frequency.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorFrequency(ViSession instrSession,
                                                           ViReal64  frequency)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_FREQUENCY, frequency),
    		2, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures pattern generator period.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR period/Configures pattern generator period.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPeriod(ViSession instrSession,
                                                        ViReal64  period)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PERIOD, period),
    		2, "period");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the square waveform.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR polarity/Configures the waveform polarity.
/// HIPAR dutyCycle/Configures the waveform duty cycle.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorSquareWaveform(
							ViSession instrSession,
							ViInt32   polarity,
							ViReal64  dutyCycle)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_POLARITY, polarity),
    		2, "polarity");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_DUTY_CYCLE, dutyCycle),
			3, "Duty Cycle");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures generator sample time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR sampleTime/Configures generator sample time.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorSampleTime(ViSession instrSession,
                                                            ViReal64  sampleTime)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_SAMPLE_TIME, sampleTime),
    		2, "Sample Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the counter.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR direction/Configures the counter direction.
/// HIPAR frequency/Configures generator counter  frequency.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorCounter(ViSession instrSession,
                                                         ViInt32   direction,
                                                         ViReal64  frequency)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_COUNTER_DIRECTION, direction),
    		2, "Direction");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_COUNTER_FREQUENCY, frequency),
			3, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures burst.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Turns burst on/off.
/// HIPAR numberOfCycles/Configures number of burst cycles.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorBurst(ViSession instrSession,
                                                       ViBoolean state,
                                                       ViInt32   numberOfCycles)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_BURST_ENABLED, state),
    		2, "State");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_BURST_CYCLES, numberOfCycles),
			3, "Number Of Cycles");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures generator idle time.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR idleTime/Configures generator idle time.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorIdleTime(ViSession instrSession,
                                                          ViReal64  idleTime)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_IDLE_TIME, idleTime),
    		2, "Idle Time");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the trigger mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/Configures the trigger mode.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorTriggerMode(ViSession instrSession,
                                                             ViInt32   mode)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_TRIGGER_MODE, mode),
    		2, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Run pattern trigur once.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PatternGeneratorTriggerRunSingle(ViSession instrSession)
{
 	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_TRIGGER_RUN_SINGLE, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Defines the slope of the external arbitrary pattern trigger.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_EXTERNAL_TRIGGER_SLOPE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PGENerator:PATTern:TRIGger:EXTern:SLOPe
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR externalTriggerSlope/Defines the slope of the external arbitrary pattern trigger.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorExternalTriggerSlope(
							ViSession instrSession,
							ViInt32   externalTriggerSlope)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_EXTERNAL_TRIGGER_SLOPE, externalTriggerSlope),
    		2, "External Trigger Slope");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures pattern generator data length.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR patternLength/Configures pattern generator data length.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBPatternLength(
							ViSession instrSession,
							ViInt32   patternLength)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_ARB_PATTERN_LENGTH, patternLength),
    		2, "Pattern Length");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the ARB index.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR index/Configures the ARB index.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBIndex(ViSession instrSession,
                                                          ViInt32   index)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_ARB_INDEX, index),
    		2, "Index");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures the arbitrary data set.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of elements in the array parameters.
/// HIPAR data/Configures the arbitrary data set.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataSet(ViSession instrSession,
                                                            ViInt32   arraySize,
                                                            ViInt32   data[])
{
 	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_WriteAsciiViInt32Array(instrSession, "PGEN:PATT:ARB:DATA ", data, arraySize));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Appends the data to data set.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of elements in the array parameters.
/// HIPAR data/Configures the arbitrary data set.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppend(
							ViSession instrSession,
							ViInt32   arraySize,
							ViInt32   data[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_WriteAsciiViInt32Array(instrSession, "PGEN:PATT:ARB:DATA:APP ", data, arraySize));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Appends the data to data set.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of elements in the array parameters.
/// HIPAR data/Configures the arbitrary data set.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppendAND(
							ViSession instrSession,
							ViInt32   arraySize,
							ViInt32   data[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_WriteAsciiViInt32Array(instrSession, "PGEN:PATT:ARB:DATA:APP:BAND ", data, arraySize));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Appends the data to data set.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arraySize/Pass the number of elements in the array parameters.
/// HIPAR data/Configures the arbitrary data set.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorARBDataAppendOR(
							ViSession instrSession,
							ViInt32   arraySize,
							ViInt32   data[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_WriteAsciiViInt32Array(instrSession, "PGEN:PATT:ARB:DATA:APP:BOR ", data, arraySize));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN  Configures manual state.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Configures manual state.
/// HIPAR outputPin/Selects the output pin.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorManualState(ViSession instrSession,
                                                             ViInt32   outputPin,
                                                             ViBoolean state)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_PATTERN_GENERATOR_MANUAL_STATE,
    		"OutputPin", outputPin , RS_REPCAP_BUF_SIZE, repCap),
    		2, "Output Pin");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_PATTERN_GENERATOR_MANUAL_STATE, state),
    		3, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Switches the motor on or off if the motor driver uses a dedicated
/// HIFN  enable signal.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_ENABLE
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_DIRECTION
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_DUTY_CYCLE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PGENerator:PATTern:PWM:ENABle
/// HIFN     PGENerator:PATTern:PWM:DIRection
/// HIFN     PGENerator:PATTern:PWM:DCYCle
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR motorEnable/Switches the motor on or off if the motor driver uses a dedicated
/// HIPAR motorEnable/enable signal.
/// HIPAR motorDirection/Sets the direction of motor rotation.
/// HIPAR dutyCycle/Sets the duty cycle of the PWM signal at P0, and thus the motor speed.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMMotorSettings(
							ViSession instrSession,
							ViBoolean motorEnable,
							ViInt32   motorDirection,
							ViReal64  dutyCycle)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_ENABLE, motorEnable),
    		2, "Motor Enable");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_MOTOR_DIRECTION, motorDirection),
			3, "Motor Direction");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_DUTY_CYCLE, dutyCycle),
    		4, "Duty Cycle");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Sets the duty cycle of the signal at P3, which corresponds to the
/// HIFN  intensity of the light. You can use this signal if the controller
/// HIFN  supports separate intensity control.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PGENerator:PATTern:LED:INTens
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR ledIntensity/Sets the duty cycle of the signal at P3, which corresponds to the
/// HIPAR ledIntensity/intensity of the light. You can use this signal if the controller
/// HIPAR ledIntensity/supports separate intensity control.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMLEDIntensity(
							ViSession instrSession,
							ViReal64  ledIntensity)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY, ledIntensity),
    		2, "LED Intensity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Set the duty cycle of the red, green, and blue colors, which
/// HIFN  corresponds to the color intensity.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_BLUE
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_GREEN
/// HIFN     RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_RED
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     PGENerator:PATTern:LED:BLUE
/// HIFN     PGENerator:PATTern:LED:GREen
/// HIFN     PGENerator:PATTern:LED:RED
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR blueIntensity/Set the duty cycle of the blue color, which corresponds to the color
/// HIPAR blueIntensity/intensity.
/// HIPAR greenIntensity/Set the duty cycle of the green color, which corresponds to the color
/// HIPAR greenIntensity/intensity.
/// HIPAR redIntensity/Set the duty cycle of the red color, which corresponds to the color
/// HIPAR redIntensity/intensity.
ViStatus _VI_FUNC rsrtx_ConfigurePatternGeneratorPWMLEDIntensityColor(
							ViSession instrSession,
							ViReal64  blueIntensity,
							ViReal64  greenIntensity,
							ViReal64  redIntensity)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_BLUE, blueIntensity),
    		2, "Blue Intensity");

    viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_GREEN, greenIntensity),
    		3, "Green Intensity");

	viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_PATTERN_GENERATOR_PWM_LED_INTENSITY_RED, redIntensity),
			4, "Red Intensity");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables the logic probe.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR state/Enables the logic probe.
ViStatus _VI_FUNC rsrtx_ConfigureLogicState(ViSession instrSession,
                                            ViInt32   logic,
                                            ViBoolean state)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_STATE,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_LOGIC_STATE, state),
    		3, "state");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the logic type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR type/Selects the logic type.
ViStatus _VI_FUNC rsrtx_ConfigureLogicType(ViSession instrSession,
                                           ViInt32   logic,
                                           ViInt32   type)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_TYPE,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_TYPE, type),
    		3, "Type");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures logic threshold.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR threshold/Configures logic threshold.
/// HIPAR userLevel/Configures threshold user level.
ViStatus _VI_FUNC rsrtx_ConfigureLogicThreshold(ViSession instrSession,
                                                ViInt32   logic,
                                                ViInt32   threshold,
                                                ViReal64  userLevel)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_THRESHOLD,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_THRESHOLD, threshold),
    		3, "Threshold");

	if (threshold == RSRTX_VAL_LOGIC_THRESHOLD_USER)
	{
		viCheckParm(rsrtx_SetAttributeViReal64(instrSession, "", RSRTX_ATTR_LOGIC_THRESHOLD_USER_LEVEL, userLevel),
				4, "User Level");
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures logic hysteresis.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR hysteresis/Configures logic hysteresis.
ViStatus _VI_FUNC rsrtx_ConfigureLogicHysteresis(ViSession instrSession,
                                                 ViInt32   logic,
                                                 ViInt32   hysteresis)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_HYSTERESIS,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_HYSTERESIS, hysteresis),
    		3, "Hysteresis");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Configures logic arithmetics.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR arithmetics/Configures logic arithmetics.
ViStatus _VI_FUNC rsrtx_ConfigureLogicArithmetics(ViSession instrSession,
                                                  ViInt32   logic,
                                                  ViInt32   arithmetics)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_ARITHMETICS,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_ARITHMETICS, arithmetics),
    		3, "Arithmetics");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Checks if the logic probe is connected.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_LOGIC_PROBE_CONNECTED
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     LOGic<p>:PROBe[:ENABle]?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR probeConnected/Checks if the logic probe is connected.
ViStatus _VI_FUNC rsrtx_QueryLogicProbeConnected(ViSession  instrSession,
                                                 ViInt32    logic,
                                                 ViBoolean* probeConnected)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_PROBE_CONNECTED,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViBoolean(instrSession, "", RSRTX_ATTR_LOGIC_PROBE_CONNECTED, probeConnected),
    		3, "Probe Connected");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Queries current maximum.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR maximum/Queries current maximum.
/// HIPAR minimum/Queries current minimum.
ViStatus _VI_FUNC rsrtx_QueryLogicCurrent(ViSession instrSession,
                                          ViInt32   logic,
                                          ViInt32*  maximum,
                                          ViInt32*  minimum)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_STATE,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_CURRENT_MAXIMUM, maximum),
    		3, "Maximum");

	viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_CURRENT_MINIMUM, minimum),
			4, "Minimum");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Selects a range of samples that will be returned with LOGic<p>:DATA.
/// HIFN  Depending on the current settings, the memory can contain more data
/// HIFN  samples than the screen is able to display. In this case, you can
/// HIFN  decide which data will be saved: samples stored in the memory or only
/// HIFN  the displayed samples. Note: The sample range can be changed only in
/// HIFN  STOP mode. If the acquisition is running, DEF is always used
/// HIFN  automatically. If the acquisition has been stopped, data can be read
/// HIFN  from the memory, and all settings are available.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_LOGIC_POINT_SELECTION
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     LOGic<p>:DATA:POINts
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR logicPointSelection/Selects a range of samples that will be returned with LOGic<p>:DATA.
/// HIPAR logicPointSelection/Depending on the current settings, the memory can contain more data
/// HIPAR logicPointSelection/samples than the screen is able to display. In this case, you can
/// HIPAR logicPointSelection/decide which data will be saved: samples stored in the memory or only
/// HIPAR logicPointSelection/the displayed samples. Note: The sample range can be changed only in
/// HIPAR logicPointSelection/STOP mode. If the acquisition is running, DEF is always used
/// HIPAR logicPointSelection/automatically. If the acquisition has been stopped, data can be read
/// HIPAR logicPointSelection/from the memory, and all settings are available.
ViStatus _VI_FUNC rsrtx_ConfigureLogicPointSelection(ViSession instrSession,
                                                     ViInt32   logic,
                                                     ViInt32   logicPointSelection)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_POINT_SELECTION,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_POINT_SELECTION, logicPointSelection),
    		3, "Logic Point Selection");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of returned samples for the selected range.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_LOGIC_WAVEFORM_DATA_POINTS
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     LOGic<p>:DATA:POINts?
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR logic/Selects the logic probe.
/// HIPAR waveformDataPoints/Returns the number of returned samples for the selected range.
ViStatus _VI_FUNC rsrtx_QueryLogicWaveformDataPoints(ViSession instrSession,
                                                     ViInt32   logic,
                                                     ViInt32*  waveformDataPoints)
{
	ViStatus error = VI_SUCCESS;
	ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_GetAttributeRepCapName(instrSession, RSRTX_ATTR_LOGIC_WAVEFORM_DATA_POINTS,
    		"Logic", logic -1, RS_REPCAP_BUF_SIZE, repCap),
    		2, "Logic");

    viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_LOGIC_WAVEFORM_DATA_POINTS, waveformDataPoints),
    		3, "Waveform Data Points");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function enables and disables all configured voltmeter
/// HIFN  measurements.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementPlace/Sets the measurement place.
/// HIPAR state/Enables and disables all configured voltmeter measurements.
ViStatus _VI_FUNC rsrtx_ConfigureDVMState(ViSession instrSession,
                                          ViInt32   measurementPlace,
                                          ViBoolean state)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurementPlace, 1, 4),
			2, "Measurement Place");

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "DVM%ld", measurementPlace);

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, repCap, RSRTX_ATTR_DVM_ENABLE, state),
    		3, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function configures the Digital Voltmeter.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementPlace/Sets the measurement place.
/// HIPAR source/Sets the measurement source for the indicated DVM measurement.
/// HIPAR type/Sets the measurement type for the indicated DVM measurement.
/// HIPAR position/Sets the corner of the screen in which the measurement results are
/// HIPAR position/displayed.
ViStatus _VI_FUNC rsrtx_ConfigureDVM(ViSession instrSession,
                                     ViInt32   measurementPlace,
                                     ViInt32   source,
                                     ViInt32   type,
                                     ViInt32   position)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurementPlace, 1, 4),
    		2, "Measurement Place");

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "DVM%ld", measurementPlace);

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DVM_SOURCE, source),
    		3, "Source");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DVM_TYPE, type),
			4, "Type");

	viCheckParm(rsrtx_SetAttributeViInt32(instrSession, repCap, RSRTX_ATTR_DVM_POSITION, position),
			5, "Position");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function returns the current value of the indicated measurement.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR measurementPlace/Sets the measurement place.
/// HIPAR result/Returns the current value of the indicated measurement.
ViStatus _VI_FUNC rsrtx_QueryDVMResult(ViSession instrSession,
                                       ViInt32   measurementPlace,
                                       ViReal64* result)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, measurementPlace, 1, 4),
    		2, "Measurement Place");

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "DVM%ld", measurementPlace);

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, repCap, RSRTX_ATTR_DVM_RESULT, result),
    		3, "Result");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  This function enables or disables the trigger counter measurements.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR counter/This control is reserved.
/// HIPAR state/Enables or disables the trigger counter measurements.
ViStatus _VI_FUNC rsrtx_ConfigureCounterState(ViSession instrSession,
                                              ViInt32   counter,
                                              ViBoolean state)
{
    ViStatus error = VI_SUCCESS;
             counter;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_COUNTER_ENABLE, state),
    		3, "State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Sets the measurement source for the counter.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_COUNTER_SOURCE
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     TCOunter:SOURce
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR counterSource/Sets the measurement source for the counter.
ViStatus _VI_FUNC rsrtx_ConfigureCounterSource(ViSession instrSession,
                                               ViInt32   counterSource)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_COUNTER_SOURCE, counterSource),
    		2, "Counter Source");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the frequency of the trigger source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR counter/This control is reserved.
/// HIPAR frequency/Returns the frequency of the trigger source.
ViStatus _VI_FUNC rsrtx_QueryCounterFrequency(ViSession instrSession,
                                              ViInt32   counter,
                                              ViReal64* frequency)
{
	ViStatus error = VI_SUCCESS;
	         counter;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_COUNTER_FREQUENCY, frequency),
    		3, "Frequency");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the period of the trigger source.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR counter/This control is reserved.
/// HIPAR period/Returns the period of the trigger source.
ViStatus _VI_FUNC rsrtx_QueryCounterPeriod(ViSession instrSession,
                                           ViInt32   counter,
                                           ViReal64* period)
{
	ViStatus error = VI_SUCCESS;
	         counter;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViReal64(instrSession, "", RSRTX_ATTR_COUNTER_PERIOD, period),
    		3, "Period");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Configures the device mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR deviceMode/Configures the device mode.
ViStatus _VI_FUNC rsrtx_ConfigureDeviceMode(ViSession instrSession,
                                            ViInt32   deviceMode)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_DEVICE_MODE, deviceMode),
    		2, "Device Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the interface for remote control and web browser access (
/// HIFN  ETHernet only).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR interface/Selects the interface for remote control and web browser access (
/// HIPAR interface/ETHernet only).
ViStatus _VI_FUNC rsrtx_ConfigureInterface(ViSession instrSession,
                                           ViInt32   remoteControlInterface)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_INTERFACE_SELECT, remoteControlInterface),
    		2, "Remote Control Interface");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Selects the USB mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR usbClass/Selects the USB mode.
ViStatus _VI_FUNC rsrtx_ConfigureUSBClass(ViSession instrSession,
                                          ViInt32   usbClass)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_USB_CLASS, usbClass),
    		2, "USB Class");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables DHCP for automatic network parameter distribution.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR dhcp/Enables DHCP for automatic network parameter distribution.
ViStatus _VI_FUNC rsrtx_ConfigureEthernetDHCP(ViSession instrSession,
                                              ViBoolean dhcp)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViBoolean(instrSession, "", RSRTX_ATTR_ETHERNET_DHCP, dhcp),
    		2, "DHCP");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns or specifies the HTTP port number.
/// HIFN
/// HIFN     Attribute(s):
/// HIFN     RSRTX_ATTR_ETHERNET_HTTP_PORT
/// HIFN
/// HIFN     Remote-control command(s):
/// HIFN     SYSTem:COMMunicate:INTerface:ETHernet:HTTPport
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR httpPortNumber/Returns or specifies the HTTP port number.
ViStatus _VI_FUNC rsrtx_ConfigureEthernetHTTPPort(ViSession instrSession,
                                                  ViInt32   httpPortNumber)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ETHERNET_HTTP_PORT, httpPortNumber),
    		2, "HTTP Port Number");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Specify the IP port number.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR ipPort/Specify the IP port number.
ViStatus _VI_FUNC rsrtx_ConfigureEthernetIPPort(ViSession instrSession,
                                                ViInt32   ipPort)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ETHERNET_IP_PORT, ipPort),
    		2, "IP Port");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns or specifies the VXI-11 port number.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR vxi11Port/Returns or specifies the VXI-11 port number.
ViStatus _VI_FUNC rsrtx_ConfigureEthernetVXI11Port(ViSession instrSession,
                                                   ViInt32   vxi11Port)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ETHERNET_VXI11_PORT, vxi11Port),
    		2, "VXI 11 Port");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Enables automatic transfer speed selection, or selects one of the
/// HIFN  predefined settings that corresponds to your network data rate.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR transfer/Enables automatic transfer speed selection, or selects one of the
/// HIPAR transfer/predefined settings that corresponds to your network data rate.
ViStatus _VI_FUNC rsrtx_ConfigureEthernetTransfer(ViSession instrSession,
                                                  ViInt32   transfer)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_ETHERNET_TRANSFER, transfer),
    		2, "Transfer");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the instrument's media access control address.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bufferSize/Sets the size of atring array.
/// HIPAR ethernetMACAddress/Returns the instrument's media access control address.
ViStatus _VI_FUNC rsrtx_QueryEthernetMACAddress(ViSession instrSession,
                                                ViInt32   bufferSize,
                                                ViChar    ethernetMACAddress[])
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_ETHERNET_MAC_ADDRESS,
    		bufferSize, ethernetMACAddress),
    		2, "Ethernet MAC Address");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Deletes the password of the education mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_PresetEducation(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_PRESET_EDUCATION, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/// HIFN  Returns the device footprint of the instrument. The device footprint
/// HIFN  contains the configuration of the instrument, installed modules,
/// HIFN  installed software and software licenses. This information is written
/// HIFN  in the device footprint xml file might be useful in case of maintenance
/// HIFN  or support request.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR bufferSize/Sets the size of atring array.
/// HIPAR deviceFootprint/Returns the device footprint of the instrument. The device footprint
/// HIPAR deviceFootprint/contains the configuration of the instrument, installed modules,
/// HIPAR deviceFootprint/installed software and software licenses. This information is written
/// HIPAR deviceFootprint/in the device footprint xml file might be useful in case of maintenance
/// HIPAR deviceFootprint/or support request.
ViStatus _VI_FUNC rsrtx_QueryDeviceFootprint(ViSession instrSession,
                                             ViInt32   bufferSize,
                                             ViChar    deviceFootprint[])
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_DEVICE_FOOTPRINT,
    		bufferSize, deviceFootprint),
    		3, "Device Footprint");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function resets the instrument to a known state and sends initialization commands to the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
ViStatus _VI_FUNC rsrtx_reset(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	if (RsCore_Simulating(instrSession) == VI_FALSE)
	{
		checkErr(rsrtx_ClearStatus(instrSession));
		checkErr(RsCore_Write(instrSession, "*RST")); // IGNORE: Check double write
		checkErr(RsCore_QueryViStringShort(instrSession, "*OPC?", NULL));
	}

	checkErr(rsrtx_DefaultInstrSetup(instrSession));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);

	return error;
}

/// HIFN This function switches ON/OFF various error checkings performed inside of the driver.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR optionChecking/This control switches option checking On or Off.
/// HIPAR rangeChecking/This control enables or disables range checking.
/// HIPAR statusChecking/This control enables or disables instrument state checking
ViStatus _VI_FUNC rsrtx_ConfigureErrorChecking(ViSession instrSession,
                                               ViBoolean optionChecking,
                                               ViBoolean rangeChecking,
                                               ViBoolean statusChecking)
{
	ViStatus         error = VI_SUCCESS;
	RsCoreSessionPtr rsSession = NULL;

	checkErr(RsCore_GetRsSession(instrSession, &rsSession));
	rsSession->optionChecking = optionChecking;
	checkErr(RsCore_SetAttributeViBoolean(instrSession, "", RS_ATTR_QUERY_INSTRUMENT_STATUS, 0, statusChecking));
	checkErr(RsCore_SetAttributeViBoolean(instrSession, "", RS_ATTR_RANGE_CHECK, 0, rangeChecking));

Error:
	return error;
}
/// HIFN If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
/// HIFN Use the function rsrtx_GetError afterwards to get the detailed information about the instrument error(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR autoSystErrQuery/If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
ViStatus _VI_FUNC rsrtx_ConfigureAutoSystemErrQuery(ViSession instrSession,
                                                    ViBoolean autoSystErrQuery)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    rsSession->autoSystErrQuery = autoSystErrQuery;

Error:
    return error;
}
/// HIFN Session-related mutex switch.
/// HIFN If TRUE (default after init is FALSE), the driver sets a mutual-exclusion mechanism for every driver's hi-level function and attribute access.
/// HIFN Set this value to TRUE if you plan to use one session in more than one thread.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR multiThreadLocking/Session-related mutex switch
ViStatus _VI_FUNC rsrtx_ConfigureMultiThreadLocking(ViSession instrSession,
                                                    ViBoolean multiThreadLocking)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    rsSession->multiThreadLocking = multiThreadLocking;

Error:
    return error;
}




/// HIFN This function runs the instrument's self test routine and returns the test result(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR testResult/Contains the value returned from the instrument self test.
/// HIPAR testMessage/Returns the self-test response string from the instrument.
ViStatus _VI_FUNC rsrtx_self_test(ViSession instrSession,
                                  ViInt16   *testResult,
                                  ViChar    testMessage[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidNullPointer(instrSession, testResult), 2, "Null address for Test Result");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, testMessage), 3, "Null address for Test Message");

	checkErr(RsCore_SelfTest(instrSession, testResult, 48, testMessage));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function returns the driver and instrument revisions.
/// HIRET /// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR driverRev/Returns the instrument driver software revision numbers in the form of a string.
/// HIPAR instrRev/Returns the instrument firmware revision numbers in the form of a string.
ViStatus _VI_FUNC rsrtx_revision_query(ViSession instrSession,
                                       ViChar    driverRev[],
                                       ViChar    instrRev[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidNullPointer(instrSession, driverRev), 2, "Null address for Instrument Driver Revision");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, instrRev), 3, "Null address for Instrument Revision");

	checkErr(RsCore_GetAttributeViString(instrSession, NULL, RS_ATTR_SPECIFIC_DRIVER_REVISION, 0, 256, driverRev));
	checkErr(RsCore_GetAttributeViString(instrSession, NULL, RS_ATTR_INSTRUMENT_FIRMWARE_REVISION, 0, 256, instrRev));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function reads an error code and a message from the
/// HIFN instrument's error queue.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR errCode/Returns the error code read from the instrument's error queue.
/// HIPAR errMessage/Returns the error message string read from the instrument's error message queue.
ViStatus _VI_FUNC rsrtx_error_query(ViSession instrSession,
                                    ViInt32   *errCode,
                                    ViChar    errMessage[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidNullPointer(instrSession, errCode), 2, "Null address for Error Code");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, errMessage), 3, "Null address for Error Message");

	checkErr(RsCore_ErrorQueryAll(instrSession, errCode, 1024, errMessage));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}



/// HIFN Queries the error/event queue for all unread items and removes them from the queue.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR bufferSize/Sets the size of Errors string.
/// HIPAR errors/Returns the error message string read from the instrument's error message queue.
ViStatus _VI_FUNC rsrtx_ErrorList(ViSession instrSession,
                                  ViInt32   bufferSize,
                                  ViChar    errors[])
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	viCheckParm(rsrtx_GetAttributeViString(instrSession, NULL, RSRTX_ATTR_SYST_ERR_LIST,
			bufferSize, errors),
			3, "Errors");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function converts a status code returned by an instrument driver function into a user-readable string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR errorCode/Pass the Status parameter that is returned from any of the instrument driver functions.
/// HIPAR errorMessage/Returns the user-readable message string that corresponds to the status code you specify.
ViStatus _VI_FUNC rsrtx_error_message(ViSession instrSession,
                                      ViStatus  errorCode,
                                      ViChar    errorMessage[256])
{
	ViStatus error = VI_SUCCESS;
	static   RsCoreStringValueTable errorTable =
	         {
	         RSRTX_ERROR_CODES_AND_MSGS,
	{0,      NULL}
	         };

	(void)(RsCore_LockSession(instrSession));

	// all VISA and RS error codes are handled as well as codes in the table
	viCheckParm(RsCore_InvalidNullPointer(instrSession, errorMessage), 3, "Null address for Error Message");

	checkErr(RsCore_GetSpecificDriverStatusDesc(instrSession, errorCode, errorMessage, 256, errorTable));

Error:  
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function resets all STATUS:QUESTIONALBLE registers.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
ViStatus _VI_FUNC rsrtx_ResetStatusRegisters(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_SetAttributeViString(instrSession, NULL, RSRTX_ATTR_RESET_STATUS_REGISTER, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function sets the status reporting system.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR registerType/This control selects type of the registers that will be configured.
/// HIPAR statusRegister/This control selects the registers that will be configured.
/// HIPAR registerPart/This control selects the registers that will be configured.
/// HIPAR registerValue/Value of selected register.
ViStatus _VI_FUNC rsrtx_SetStatusRegister(ViSession instrSession,
                                          ViInt32   registerType,
                                          ViInt32   statusRegister,
                                          ViInt32   registerPart,
                                          ViInt32   registerValue)
{
    ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    switch   (registerType)
    {
    case     RSRTX_VAL_REG_OPER:
		switch   (registerPart)
				 {
					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_P_TRANSITION, registerValue),
								5, "Register Value");
						break;
					default:
						viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
				}
		break;

	case RSRTX_VAL_REG_QUES:
		switch (statusRegister)
		{
			case RSRTX_VAL_REG_NONE:
				switch (registerPart)
				{
					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_P_TRANSITION, registerValue),
								5, "Register Value");
						break;
					default:
						viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
				}
				break;

			case RSRTX_VAL_REG_COV:
				switch (registerPart)
				{
					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_P_TRANSITION, registerValue),
								5, "Register Value");
						break;
					default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
				}
				break;
			case RSRTX_VAL_REG_LIM:
				switch (registerPart)
				{
					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_P_TRANSITION, registerValue),
								5, "Register Value");
						break;
					default:
						viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
				}
					break;
			case RSRTX_VAL_REG_MASK:
				switch (registerPart)
				{
					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_P_TRANSITION, registerValue),
								5, "Register Value");
						break;
					default:
						viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
					}
					break;

			case RSRTX_VAL_REG_ADC:
				switch (registerPart)
				{

					case RSRTX_VAL_REG_ENABLE:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_ENABLE, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_NTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_N_TRANSITION, registerValue),
								5, "Register Value");
						break;
					case RSRTX_VAL_REG_PTR:
						viCheckParm(rsrtx_SetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_P_TRANSITION, registerValue),
								5, "Register Value");
							break;
					default:
						viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
						break;
					}
					break;
				default:
					viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 3, "Status Register");
					break;
			}
			break;
		default:
			viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 2, "Register Type");
			break;
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function queries the status reporting system.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR registerType/This control selects type of the registers that will be queried.
/// HIPAR statusRegister/This control selects the registers that will be queried.
/// HIPAR registerPart/This control selects the registers that will be queried.
/// HIPAR registerValue/Returns value of selected register.
ViStatus _VI_FUNC rsrtx_GetStatusRegister(ViSession instrSession,
                                          ViInt32   registerType,
                                          ViInt32   statusRegister,
                                          ViInt32   registerPart,
                                          ViInt32   *registerValue)
{
    ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

    switch   (registerType)
             {
    case     RSRTX_VAL_REG_OPER:
    switch   (registerPart)
             {
    case     RSRTX_VAL_REG_COND:

					viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_CONDITION, registerValue),
							5, "Register Value");
					break;
				case RSRTX_VAL_REG_ENABLE:
					viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_ENABLE, registerValue),
							5, "Register Value");
					break;
				case RSRTX_VAL_REG_EVENT:
					viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_EVENT, registerValue),
							5, "Register Value");
					break;
				case RSRTX_VAL_REG_NTR:
					viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_N_TRANSITION, registerValue),
							5, "Register Value");
					break;
				case RSRTX_VAL_REG_PTR:
					viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_OPERATION_P_TRANSITION, registerValue),
							5, "Register Value");
					break;
				default:
					viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
					break;
			}
			break;
		case RSRTX_VAL_REG_QUES:
			switch (statusRegister)
			{
				case RSRTX_VAL_REG_NONE:
					switch (registerPart)
					{
						case RSRTX_VAL_REG_COND:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CONDITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_ENABLE:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ENABLE, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_EVENT:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_EVENT, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_NTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_N_TRANSITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_PTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_P_TRANSITION, registerValue),
									5, "Register Value");
							break;
						default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
							break;
					}
					break;
				case RSRTX_VAL_REG_COV:
					switch (registerPart)
					{
						case RSRTX_VAL_REG_COND:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_CONDITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_ENABLE:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_ENABLE, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_EVENT:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_EVENT, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_NTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_N_TRANSITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_PTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_CHANNEL_OVERLOAD_P_TRANSITION, registerValue),
									5, "Register Value");
							break;
						default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
							break;
					}
					break;
				case RSRTX_VAL_REG_LIM:
					switch (registerPart)
					{
						case RSRTX_VAL_REG_COND:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_CONDITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_ENABLE:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_ENABLE, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_EVENT:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_EVENT, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_NTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_N_TRANSITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_PTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_LIMIT_P_TRANSITION, registerValue),
									5, "Register Value");
							break;
						default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
							break;
					}
					break;
				case RSRTX_VAL_REG_MASK:
					switch (registerPart)
					{
						case RSRTX_VAL_REG_COND:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_CONDITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_ENABLE:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_ENABLE, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_EVENT:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_EVENT, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_NTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_N_TRANSITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_PTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_MASK_P_TRANSITION, registerValue),
									5, "Register Value");
							break;
						default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
							break;
					}
					break;

					case RSRTX_VAL_REG_ADC:
					switch (registerPart)
					{
						case RSRTX_VAL_REG_COND:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_CONDITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_ENABLE:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_ENABLE, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_EVENT:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_EVENT, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_NTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_N_TRANSITION, registerValue),
									5, "Register Value");
							break;
						case RSRTX_VAL_REG_PTR:
							viCheckParm(rsrtx_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_QUESTIONABLE_ADC_STATE_P_TRANSITION, registerValue),
									5, "Register Value");
							break;
						default:
							viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 4, "Register Part");
							break;
					}
					break;
				default:
					viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 3, "Status Register");
					break;
			}
			break;
		default:
			viCheckParm(RsCore_InvalidViInt32Value(instrSession, registerType), 2, "Register Type");
			break;
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function specifies the minimum timeout value to use (in
/// HIFN milliseconds) when accessing the device associated with the
/// HIFN given session.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR VISATimeout/This control sets the timeout value.
ViStatus _VI_FUNC rsrtx_SetVISATimeout(ViSession instrSession,
                                       ViUInt32  VISATimeout)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_SetVisaTimeout(instrSession, VISATimeout));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function returns the minimum timeout value to use (in
/// HIFN milliseconds) when accessing the device associated with the
/// HIFN given session.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR VISATimeout/This control gets the timeout value.
ViStatus _VI_FUNC rsrtx_GetVISATimeout(ViSession instrSession,
                                       ViUInt32  *VISATimeout)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_GetVisaTimeout(instrSession, VISATimeout));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function executes an internal self-alignment of the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_SelfAlingment(ViSession instrSession,
                                      ViInt32   maximumTime)
{
	ViStatus error = VI_SUCCESS;
	ViInt32  oldTimeout = 0;

    checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_GetOPCTimeout(instrSession, &oldTimeout));
	checkErr(rsrtx_SetOPCTimeout(instrSession, maximumTime));

	checkErr(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_SELF_ALIGNMENT, NULL));

	checkErr(rsrtx_SetOPCTimeout(instrSession, oldTimeout));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function clears status.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ClearStatus(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_ClearStatus(instrSession));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function returns the ID Query response string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR IDQueryResponse/Returns the ID Query response string.
ViStatus _VI_FUNC rsrtx_IDQueryResponse(ViSession instrSession,
                                        ViChar    IDQueryResponse[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_QueryViString(instrSession, "*IDN?", 1024, IDQueryResponse));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  Stops further command processing until all commands sent before
/// HIFN  *WAI have been executed.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rsrtx_ProcessAllPreviousCommands(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_WriteInstrData(instrSession, "*WAI"));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function queries the OPC.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR OPC/Queries the OPC.
ViStatus _VI_FUNC rsrtx_QueryOPC(ViSession instrSession,
                                 ViInt32   *opc)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(rsrtx_QueryViInt32(instrSession, "*OPC?", opc));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}


/// HIFN This function switches ON/OFF instrument status checking of the
/// HIFN Tinstrument
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR statusChecking/This control selects ON or OFF instrument state checking.
ViStatus _VI_FUNC rsrtx_setCheckStatus(ViSession instrSession,
                                       ViBoolean statusChecking)
{
	return RsCore_SetAttributeViBoolean(instrSession, "", RS_ATTR_QUERY_INSTRUMENT_STATUS, 0, statusChecking);
}

/// HIFN This function retrieves and then clears the error information
/// HIFN for the session or the current execution thread.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR errorCode/Returns the error code for the session or execution thread.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Description parameter.
/// HIPAR description/Returns the error description for the session or execution thread. If there is no description, the function returns an empty string.
ViStatus _VI_FUNC rsrtx_GetError(ViSession instrSession,
                                 ViStatus  *errorCode,
                                 ViInt32   bufferSize,
                                 ViChar    description[])
{
	ViStatus error = VI_SUCCESS;

	(void)(RsCore_LockSession(instrSession));

	// Test for nulls and acquire error data
	viCheckParm(RsCore_InvalidNullPointer(instrSession, errorCode), 2, "Null address for Error");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, description), 4, "Null address for Description");

	checkErr(RsCore_GetErrorCompleteDescription(instrSession, &rsrtx_error_message, errorCode, bufferSize, description)
    );

Error:  
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function clears the error code and error description for
/// HIFN the session.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
ViStatus _VI_FUNC rsrtx_ClearError(ViSession instrSession)
{
	return RsCore_ClearErrorInfo(instrSession);
}

/// HIFN This function writes a user-specified string to the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR writeBuffer/Pass the string to be written to the instrument.
ViStatus _VI_FUNC rsrtx_WriteInstrData(ViSession instrSession,
                                       ViString  writeBuffer)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	error = RsCore_Write(instrSession, writeBuffer);

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN Document your function here.
/// HIFN You may use multiple lines for documentation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR numBytes/Pass the maximum number of bytes to read from the instruments.
/// HIPAR rdBuf/After this function executes, this parameter contains the data that was read from the instrument.
/// HIPAR bytesRead/Returns the number of bytes actually read from the instrument and stored in the Read Buffer.
ViStatus _VI_FUNC rsrtx_ReadInstrData(ViSession instrSession,
                                      ViInt32   numBytes,
                                      ViChar    rdBuf[],
                                      ViUInt32  *bytesRead)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  responseString = NULL;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_ReadViStringUnknownLength(instrSession, &responseString));
	checkErr(RsCore_CopyToUserBufferAsciiData(rdBuf, numBytes, responseString));
	*bytesRead = (ViUInt32)strlen(responseString);

Error:
	if (responseString)
		free(responseString);

	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function queries the ViBoolean value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViBoolean value.
ViStatus _VI_FUNC rsrtx_QueryViBoolean(ViSession instrSession,
                                       ViString  cmd,
                                       ViBoolean *value)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Command (null string length)");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

	checkErr(RsCore_QueryViBoolean(instrSession, cmd, value));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function queries the ViInt32 value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViInt32 value.
ViStatus _VI_FUNC rsrtx_QueryViInt32(ViSession instrSession,
                                     ViString  cmd,
                                     ViInt32   *value)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Command (null string length)");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

	checkErr(RsCore_QueryViInt32(instrSession, cmd, value));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function queries the ViReal64 value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViReal64 value.
ViStatus _VI_FUNC rsrtx_QueryViReal64(ViSession instrSession,
                                      ViString  cmd,
                                      ViReal64  *value)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Command (null string length)");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

	checkErr(RsCore_QueryViReal64(instrSession, cmd, value));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function queries the ViString value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Value parameter.
/// HIPAR value/Returns the string value.
ViStatus _VI_FUNC rsrtx_QueryViString(ViSession instrSession,
                                      ViString  cmd,
                                      ViInt32   bufferSize,
                                      ViChar    _VI_FAR value[])
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Command (null string length)");
	viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

	checkErr(RsCore_QueryViStringUnknownLengthToUserBuffer(instrSession, cmd, bufferSize, value, NULL));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}
/// HIFN Sends a command to the instrument synchronised with OPC-polling.
/// HIFN Use this function to wait for an instrument operation that can
/// HIFN take a long time to complete, e.g. self-alignment.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR writeBuffer/Pass the string to be written to the instrument.
/// HIPAR timeout/This control sets the timeout value.
ViStatus _VI_FUNC rsrtx_WriteCommandWithOPCSync(ViSession instrSession,
                                                ViString  cmd,
                                                ViUInt32  timeout)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Command (string length)");

	checkErr(RsCore_WriteWithOpc(instrSession, cmd, timeout));

Error:
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Sends a query to the instrument synchronised with OPC-polling.
/// HIFN Use this function to wait for a response that can take a long
/// HIFN time to complete e.g. self-alignment, calibration or self-test.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR writeBuffer/Pass the string to be written to the instrument.
/// HIPAR timeout/This control sets the timeout value.
/// HIPAR bufferSize/Pass the maximum number of bytes to read from the instruments.
/// HIPAR readBuffer/After this function executes, this parameter contains the data
/// HIPAR readBuffer/that was read from the instrument.
/// HIPAR numBytesRead/Returns the number of bytes actually read from the instrument
/// HIPAR numBytesRead/and stored in the Read Buffer.
ViStatus _VI_FUNC rsrtx_QueryWithOPCSync(ViSession instrSession,
                                         ViString  cmd,
                                         ViUInt32  timeout,
                                         ViInt32   bufferSize,
                                         ViChar    readBuffer[],
                                         ViUInt32  *numBytesRead)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	viCheckParm(RsCore_InvalidStringLength(instrSession, cmd, 1, -1),
		2, "Write Buffer (string length)");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, readBuffer),
    	5, "Read Buffer");

	checkErr(RsCore_QueryViStringUnknownLengthToUserBufferWithOpc(instrSession, cmd, timeout, bufferSize, readBuffer, (ViInt32*)numBytesRead));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function provides mass storage capabilities for the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR operation/This control selects the type of memory operation to be performed.
/// HIPAR source/This control specifies the source of the operation to be performed. If
/// HIPAR source/the operation requires a single parameter, this control specifies that
/// HIPAR source/parameter.
/// HIPAR destination/This control specifies the destination of the operation to be
/// HIPAR destination/performed.
ViStatus _VI_FUNC rsrtx_FileManagerOperations(ViSession instrSession,
                                              ViInt32   operation,
                                              ViString  source,
                                              ViString  destination)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    switch (operation)
    {
        case RSRTX_VAL_FILE_COPY:
            snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:COPY '%s','%s'", source, destination);
            checkErr(RsCore_Write(instrSession, cmd));
            checkErr(rsrtx_CheckStatus(instrSession));
            break;
        case RSRTX_VAL_FILE_MOVE:
			snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:MOVE '%s','%s'", source, destination);
            checkErr(RsCore_Write(instrSession, cmd));
            checkErr(rsrtx_CheckStatus(instrSession));
            break;
        case RSRTX_VAL_FILE_DELETE:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_DELETE_FILE, source),
            		3, "Source");
            break;
        case RSRTX_VAL_FILE_NEW_DIR:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CREATE_DIRECTORY, source),
            		3, "Source");
            break;
        case RSRTX_VAL_FILE_CDIR:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CURRENT_DIRECTORY, source),
            		3, "Source");
            break;
        case RSRTX_VAL_FILE_RDIR:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_REMOVE_DIRECTORY, source),
            		3, "Source");
            break;
        case RSRTX_VAL_FILE_CDRIVE:
            viCheckParm(rsrtx_SetAttributeViString(instrSession, "", RSRTX_ATTR_CHANGE_DRIVE, source),
            		3, "Source");
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, operation), 2, "Operation");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of files and subdirectories of the current or of a
/// HIFN  specified directory. The number includes the parent directory strings
/// HIFN  "." and ".." so that it corresponds to the number of strings returned
/// HIFN  by the rsrtx_FileDirectoryContent function after the initial numeric
/// HIFN  parameters.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR directory/This control specifies the directory in which the command will be
/// HIPAR directory/performed.
/// HIPAR numberofFilesAndFolders/Returns the number of files and subdirectories of the current or of a
/// HIPAR numberofFilesAndFolders/specified directory.
ViStatus _VI_FUNC rsrtx_FileCount(ViSession instrSession,
                                  ViString  directory,
                                  ViInt32*  numberofFilesAndFolders)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar   *p2buf = cmd;

    checkErr(RsCore_LockSession(instrSession));

    viCheckAlloc (numberofFilesAndFolders);

    p2buf += snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:CAT:LENG?");

    if ((directory != NULL) && (strlen (directory) > 0))
		printf (p2buf, " '%s'", directory);

    checkErr(RsCore_QueryViInt32(instrSession, cmd, numberofFilesAndFolders));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function reads the indicated directory. According to DOS
/// HIFN  convention, wild card characters can be entered in order to query eg. a
/// HIFN  list of all file of a certain type.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR directory/This control specifies the directory in which the command will be
/// HIPAR directory/performed.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the
/// HIPAR bufferSize/Output parameter.
/// HIPAR output/This indicator returns the files in the indicated directory as comma
/// HIPAR output/separated strings, for example: 'SPOOL1.WMF','SPOOL2.WMF','SPOOL3.WMF'
ViStatus _VI_FUNC rsrtx_FileDirectoryContent(ViSession instrSession,
                                             ViString  directory,
                                             ViInt32   bufferSize,
                                             ViChar    output[])
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];
    ViChar   *p2buf = cmd;

    checkErr(RsCore_LockSession(instrSession));

    viCheckAlloc (output);

    p2buf += snprintf (p2buf, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:CAT?");

    if ((directory != NULL) && (strlen (directory) > 0))
        sprintf (p2buf, " '%s'", directory);

    checkErr(RsCore_QueryViStringUnknownLengthToUserBuffer(instrSession, cmd, bufferSize, output, NULL));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the number of subdirectories of the current or of a specified
/// HIFN  directory. The number includes the parent directory strings "." and
/// HIFN  ".." so that it corresponds to the number of strings returned by the
/// HIFN  rsrtx_FileSubdirectories.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR directory/This control specifies the directory in which the command will be
/// HIPAR directory/performed.
/// HIPAR numberofSubdirectories/Returns the number of files and subdirectories of the current or of a
/// HIPAR numberofSubdirectories/specified directory.
ViStatus _VI_FUNC rsrtx_FileSubdirectoriesCount(ViSession instrSession,
                                                ViString  directory,
                                                ViInt32*  numberofSubdirectories)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViChar   *p2buf = cmd;

    checkErr(RsCore_LockSession(instrSession));

    viCheckAlloc (numberofSubdirectories);

    p2buf += snprintf (cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:DCAT:LENG?");

    if ((directory != NULL) && (strlen (directory) > 0))
		sprintf (p2buf, " '%s'", directory);

    checkErr(RsCore_QueryViInt32(instrSession, cmd, numberofSubdirectories));
    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns the subdirectories of the current or of a specified directory.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR directory/This control specifies the directory in which the command will be
/// HIPAR directory/performed.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the
/// HIPAR bufferSize/Output parameter.
/// HIPAR output/This indicator returns the files in the indicated directory as comma
/// HIPAR output/separated strings, for example: 'SPOOL1.WMF','SPOOL2.WMF','SPOOL3.WMF'
ViStatus _VI_FUNC rsrtx_FileSubdirectories(ViSession instrSession,
                                           ViString  directory,
                                           ViInt32   bufferSize,
                                           ViChar    output[])
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViChar   *p2buf = cmd;

    checkErr(RsCore_LockSession(instrSession));

    viCheckAlloc (output);

    p2buf += snprintf (p2buf, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:DCAT?");

    if ((directory != NULL) && (strlen (directory) > 0))
		sprintf (p2buf, " '%s'", directory);

    checkErr(RsCore_QueryViStringUnknownLengthToUserBuffer(instrSession, cmd, bufferSize, output, NULL));

    checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Returns a list of the drives of the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR output/Returns a list of the drives of the instrument.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the
/// HIPAR bufferSize/Output parameter.
ViStatus _VI_FUNC rsrtx_FileDrives(ViSession instrSession,
                                   ViInt32   bufferSize,
                                   ViChar    output[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(rsrtx_GetAttributeViString(instrSession, "", RSRTX_ATTR_DRIVES,
    		bufferSize, output),
    		2, "Drives");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function is used to read data from the instrument and write it to
/// HIFN  a user specified file on the host computer.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR source/This control selects file for the data transfer from instrument to
/// HIPAR source/control computer.
/// HIPAR destination/This control defines destination file to which the data transfer from
/// HIPAR destination/instrument to control computer applies.
ViStatus _VI_FUNC rsrtx_ReadToFileFromInstrument(ViSession instrSession,
                                                 ViString  source,
                                                 ViString  destination)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:DATA? '%s'", source);
	checkErr(RsCore_QueryBinaryDataBlockToFile(instrSession, cmd, destination, RS_VAL_TRUNCATE));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function is used to read data from the host computer and write it
/// HIFN  to a user specified file in the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR source/This control selects file for the data transfer from control computer
/// HIPAR source/to instrument.
/// HIPAR destination/This control defines destination file to which the data transfer from
/// HIPAR destination/control computer to instrument applies.
ViStatus _VI_FUNC rsrtx_WriteFromFileToInstrument(ViSession instrSession,
                                                  ViString  source,
                                                  ViString  destination)
{
	ViStatus error = VI_SUCCESS;
	ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

	checkErr(RsCore_LockSession(instrSession));

	snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:DATA '%s',", destination);
	checkErr(RsCore_WriteBinaryDataFromFile(instrSession, cmd, source));
	checkErr(rsrtx_CheckStatus(instrSession));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function allows to provide data set operation for Save/Recall
/// HIFN  items of memory subsystem.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR operation/This control selects the type of memory operation to be performed.
/// HIPAR stateNumber/Defines save and recall state position.
/// HIPAR path/This control specifies the source of the operation to be performed.
ViStatus _VI_FUNC rsrtx_DataSetFileOperations(ViSession instrSession,
                                              ViInt32   operation,
                                              ViInt32   stateNumber,
                                              ViString  path)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    switch (operation)
    {
        case RSRTX_VAL_MEM_SAVE:
            snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:STOR:STAT %ld,'%s'", stateNumber, path);
            checkErr(RsCore_Write(instrSession, cmd));
            checkErr(rsrtx_CheckStatus(instrSession));
            break;
        case RSRTX_VAL_MEM_RECALL:
            snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "MMEM:LOAD:STAT %ld,'%s'", stateNumber, path);
            checkErr(RsCore_Write(instrSession, cmd));
            checkErr(rsrtx_CheckStatus(instrSession));
            break;
        default:
            viCheckParm(RsCore_InvalidViInt32Value(instrSession, operation), 2, "Operation");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Saves the device settings that can be saved and load manually with
/// HIFN  [File] > Device Settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR path/Path and filename on the local computer in which to save the
/// HIPAR path/instrument settings.
ViStatus _VI_FUNC rsrtx_SaveInstrumentSettingsToPC(ViSession instrSession,
                                                   ViString  path)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryBinaryDataBlockToFile(instrSession, "SYST:SET?", path, RS_VAL_TRUNCATE));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Recalls the device settings previously saved using SYSTem:SET that can
/// HIFN  be saved and loaded manually with [File] > Device Settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR path/Path and filename on the local computer from which to recall the
/// HIPAR path/instrument settings.
ViStatus _VI_FUNC rsrtx_RecallInstrumentSettingsFromPC(ViSession instrSession,
                                                       ViString  path)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_WriteBinaryDataFromFile(instrSession, "SYST:SET ", path));

	checkErr(rsrtx_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the OPC timeout.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR timeout/This control returns the timeout value.
ViStatus _VI_FUNC rsrtx_GetOPCTimeout(ViSession instrSession,
                                      ViInt32*  timeout)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_GetAttributeViInt32(instrSession, NULL, RS_ATTR_OPC_TIMEOUT, 0, timeout));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN  This function sets the OPC timeout.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR opcTimeout/This control sets the timeout value.
ViStatus _VI_FUNC rsrtx_SetOPCTimeout(ViSession instrSession,
                                      ViUInt32  timeout)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_SetAttributeViInt32(instrSession, NULL, RS_ATTR_OPC_TIMEOUT, 0, (ViInt32)timeout));

Error:
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/// HIFN This function closes the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsrtx_init or
/// HIPAR instrSession/rsrtx_InitWithOptions function.
ViStatus _VI_FUNC rsrtx_close(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	checkErr(RsCore_LockSession(instrSession));

	checkErr(RsCore_ViClose(instrSession));

Error:
	(void)RsCore_Dispose(instrSession);
	(void)RsCore_UnlockSession(instrSession);
	return error;
}

/*****************************************************************************
 *------------------- End Instrument Driver Source Code ---------------------*
 *****************************************************************************/
