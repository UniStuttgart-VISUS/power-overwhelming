/*****************************************************************************
 *  Rohde&Schwarz HMC 8015 Power Analyzer Driver
 *  LabWindows/CVI Instrument Driver                                     
 *  Original Release: 2015-07-10                                 
 *  By: Stanislav Vajs
 *                                                                           
 *  Modification History:                                                    
 *                                                                           
 *       See ChangeLog
 *                                                                           
 *****************************************************************************/
                         
#include <string.h>
#include <stdio.h>  
#include <stdlib.h>
#include <math.h>
#include "rshmc8015.h"

ViStatus _VI_FUNC  rshmc8015_RsClose (ViSession vi);

/*****************************************************************************
 *- Value Definition and Range Tables ---------------------------------------*
 *****************************************************************************/
static ViString deviceArr[] = {"INT","EXT","DEF",VI_NULL};
static ViString regOperArr[] = { "", "QUES", "OPER" };
static ViString regTypeArr[] = { "COND", "EVEN", "ENAB", "PTR", "NTR" };
                

/*****************************************************************************
 *- Callback Declarations ---------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- User-Callable Functions (Exportable Functions) --------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: rshmc8015_init
 * Purpose:  VXIplug&play required function. Calls the
 *           rshmc8015_InitWithOptions function.
 *****************************************************************************/
ViStatus _VI_FUNC rshmc8015_init (ViRsrc resourceName, ViBoolean IDQuery,
                                 ViBoolean resetDevice, ViSession *newInstrSession)
{
    ViStatus    error = VI_SUCCESS;

    if (newInstrSession == VI_NULL)
        {
        (void) Rs_SetErrorInfo (VI_NULL, VI_FALSE, RS_ERROR_INVALID_PARAMETER,
                          VI_ERROR_PARAMETER4, "Null address for Instrument Handle");
        checkErr( RS_ERROR_INVALID_PARAMETER);
        }

    checkErr( rshmc8015_InitWithOptions (resourceName, IDQuery, resetDevice,
                                      "QueryInstrStatus=1", newInstrSession));

Error:
    return error;
}

/*****************************************************************************
 * Function: rshmc8015_InitWithOptions
 * Purpose:  This function creates a new RS session and calls the
 *           RsInit function.
 *****************************************************************************/
ViStatus _VI_FUNC rshmc8015_InitWithOptions(
    ViRsrc          resourceName,
    ViBoolean       IDQuery,
    ViBoolean       resetDevice,
    ViString        optionString,
    ViSession      *newInstrSession
)
{
    ViStatus                error = VI_SUCCESS;
    ViChar                  newResourceName[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViChar                  newOptionString[RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViBoolean               isLogicalName = 0;
    ViSession               instrSession = 0, rmSession = 0;
    RsAttrPropertiesPtr     *attrList=NULL;
    RsRepCapPtr             repCapTable = NULL;
    
    if (newInstrSession == VI_NULL)
        {
        (void) Rs_SetErrorInfo (VI_NULL, VI_FALSE, RS_ERROR_INVALID_PARAMETER,
                         VI_ERROR_PARAMETER5, "Null address for Instrument Handle");
        checkErr( RS_ERROR_INVALID_PARAMETER);
        }

    /* Prepare resource manager session handle */
    checkErr (viOpenDefaultRM (&rmSession));

    /* Establish communication session with the instrument */

    viCheckErr( viOpen (rmSession, resourceName, VI_NULL, VI_NULL, &instrSession));
    
    /* Configure VISA Formatted I/O */
    viCheckErr( viSetAttribute (instrSession, VI_ATTR_TMO_VALUE, 5000 ));
    viCheckErr( viSetBuf (instrSession, (ViUInt16) (VI_READ_BUF | VI_WRITE_BUF), 4000));
    viCheckErr( viSetAttribute (instrSession, VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS));
    viCheckErr( viSetAttribute (instrSession, VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS));

    checkErr( Rs_GetInfoFromResourceName (resourceName,
                                          (ViString)optionString,
                                          newResourceName,
                                          newOptionString,
                                          &isLogicalName));
    
    ATTRLIST(attrList,rshmc8015);  
    checkErr( Rs_SpecificDriverNew (instrSession, "rshmc8015", newOptionString, attrList));
    
    /* Build repeated capability table */
    REPCAPTABLE(repCapTable,rshmc8015);
    checkErr( Rs_BuildRepCapTable (instrSession, repCapTable));

    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_VISA_RM_SESSION, 0, &rmSession));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_IO_SESSION, 0, &instrSession));

    /* With remote control via Ethernet, remote control is not automatically
       set by means of a command. The instrument must be explicitly set to
       the REMOTE state, e.g. by sending the intf command &GTR
    */
    /*- Reset instrument ----------------------------------------------------*/
    if (resetDevice == VI_TRUE)
    {
        checkErr( rshmc8015_reset (instrSession));
    }
    else  /*- Send Default Instrument Setup ---------------------------------*/
        checkErr( rshmc8015_DefaultInstrSetup (instrSession));

    /*- Identification Query ------------------------------------------------*/
    if (IDQuery == VI_TRUE)
        {
        ViChar rdBuffer[RSHMC8015_IO_BUFFER_SIZE] = "";

        checkErr( Rs_GetAttribute (instrSession, VI_NULL, (ViAttr) RSHMC8015_ATTR_ID_QUERY_RESPONSE,
                                   0, RSHMC8015_IO_BUFFER_SIZE, rdBuffer));

        if (strncmp (rdBuffer, RSHMC8015_VALID_ID_RESPONSE_STRING, strlen(RSHMC8015_VALID_ID_RESPONSE_STRING)) != 0)
            {
            viCheckErr( VI_ERROR_FAIL_ID_QUERY);
            }
        }

    if (isLogicalName == VI_FALSE)
        {
        ViInt32 oldFlag = 0;

        checkErr (Rs_GetAttributeFlags (instrSession, RS_ATTR_IO_RESOURCE_DESCRIPTOR, &oldFlag));
        checkErr (Rs_SetAttributeFlags (instrSession, RS_ATTR_IO_RESOURCE_DESCRIPTOR, oldFlag & 0xfffb | 0x0010));
        checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_IO_RESOURCE_DESCRIPTOR, 0, newResourceName));
        }
    
    if (isLogicalName == VI_TRUE)
        checkErr( Rs_ApplyDefaultSetup (instrSession));

    /* Instrument session accessible by the end user is native VISA session,
       or when simulated virtual instrument (instrSession) session. */
    
Error:

    if (error < VI_SUCCESS)
    {
        ViSession   rmSess = VI_NULL;
        
        (void) Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_VISA_RM_SESSION, 0, (ViInt32) sizeof (rmSess), &rmSess);
        (void) Rs_Dispose (instrSession); 
        if (instrSession != 0)
            (void) viClose (instrSession);
        (void) viClose (rmSess);
    }
    else
    {
        *newInstrSession = instrSession;
    }
    
    return error;
    
}

/// HIFN  Sets acq mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR acquisitionMode/Sets acq mode.
ViStatus _VI_FUNC rshmc8015_ConfigureAcquisitionMode(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	acquisitionMode
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_MODE,
												acquisitionMode), 3, "Acquisition Mode");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Configures AC acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR pllSource/Sets PLL source.
/// HIPAR frequencyFilter/Sets state of acquisition frequency filter.
/// HIPAR digitalFilter/Sets state band width limit.
/// HIPAR bwl/Sets state of acquisition digital signal filter.
ViStatus _VI_FUNC rshmc8015_ConfigureACAcquisition(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	pllSource,
	ViBoolean	frequencyFilter,
	ViBoolean	digitalFilter,
	ViBoolean	bwl
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_PLL_SOURCE,
												pllSource), 3, "pll Source");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER,
												frequencyFilter), 4, "frequency Filter");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_DIGITAL_FILTER,
												digitalFilter), 5, "digital Filter");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_BWL,
												bwl), 6, "bwl");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Configures voltage acquisition.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR autorange/Sets state of auto range for voltage range.
/// HIPAR range/Selects an appropriate voltage range for passed RMS value.
/// HIPAR crestFactor/Sets the crest factor for voltage.
/// HIPAR invert/Sets state of voltage polarity inversion.
ViStatus _VI_FUNC rshmc8015_ConfigureVoltageAcquisition(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	autorange,
	ViReal64	range,
	ViInt32	crestFactor,
	ViBoolean	invert
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE,
												autorange), 3, "autorange");

	if (autorange == VI_FALSE)
	{
		viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
	                                                RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE,
													range), 4, "range");
	}
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR,
												crestFactor), 5, "crestFactor");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT,
												invert), 6, "invert");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Configures current acquisition.  
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR autorange/Sets state of auto range for current range.
/// HIPAR range/Selects an appropriate current range for passed RMS value.
/// HIPAR crestFactor/Sets the crest factor for current.
/// HIPAR invert/Sets state of current polarity inversion.
ViStatus _VI_FUNC rshmc8015_ConfigureCurrentAcquisition(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	autorange,
	ViReal64	range,
	ViInt32	crestFactor,
	ViBoolean	invert
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE,
												autorange), 3, "autorange");
	
	if (autorange == VI_FALSE)
	{
		viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
	                                                RSHMC8015_ATTR_ACQ_CURRENT_RANGE,
													range), 4, "range");
	}
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR,
												crestFactor), 5, "crestFactor");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_CURRENT_INVERT,
												invert), 6, "invert");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Query whether overcurrent protection was triggered.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR ocp/Query whether overcurrent protection was triggered.
ViStatus _VI_FUNC rshmc8015_QueryOCP(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean*	ocp
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_GetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_OCP,
												ocp), 3, "OCP");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Reset overcurrent protection.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
ViStatus _VI_FUNC rshmc8015_ResetOCP(
	ViSession	instrSession,
	ViInt32	channel
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, rep_cap,
                                                RSHMC8015_ATTR_ACQ_OCP_RESET,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN  Displays a text message box on the front display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR text/The text to display in the message box.
ViStatus _VI_FUNC rshmc8015_ShowMessageBox(
	ViSession	instrSession,
	ViString	text
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_DISPLAY_TEXT,
												text), 2, "Text");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Clears the text message box on the front display.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_ClearMessageBox(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL)); 

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_DISPLAY_CLEAR,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN  Sets view mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR viewMode/Sets view mode.
ViStatus _VI_FUNC rshmc8015_ConfigureViewMode(
	ViSession	instrSession,
	ViInt32	viewMode
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_MODE,
												viewMode), 2, "View Mode");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Sets page's cell count.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR page/Numerical selection of a page
/// HIPAR size/Sets page's cell count.
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewPageSize(
	ViSession	instrSession,
	ViInt32	page,
	ViInt32	size
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[10] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, page, 1, 4), 2, "Page");
    sprintf (rep_cap, "Page%ld", page);

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE,
												size), 3, "Size");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Selects active page.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR activePage/Selects active page.
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewActivePage(
	ViSession	instrSession,
	ViInt32	activePage
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE,
												activePage), 2, "Cctive Page");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Selects the normal view cell function.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR page/Numerical selection of a page
/// HIPAR cell/Numerical selection of a cell
/// HIPAR function/Selects the normal view cell function.
ViStatus _VI_FUNC rshmc8015_ConfigureNormalViewFunction(
	ViSession	instrSession,
	ViInt32	page,
	ViInt32	cell,
	ViInt32	function
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[20] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, page, 1, 4), 2, "Page");
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, cell, 1, 6), 3, "Cell"); 
	
    sprintf (rep_cap, "Page%ld,Cell%ld", page, cell);

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_VIEW_NORM_FUNCTION,
												function), 3, "Function");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Configures harmonics view.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR select/Selects harmonics view.
/// HIPAR source/Selects harmonics source.
/// HIPAR number/Sets number of harmonics.
/// HIPAR scaling/Selects harmonics scaling.
/// HIPAR subset/Selects harmonics subset.
ViStatus _VI_FUNC rshmc8015_ConfigureHarmonicsView(
	ViSession	instrSession,
	ViInt32	select,
	ViInt32	source,
	ViInt32	number,
	ViInt32	scaling,
	ViInt32	subset
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_HARM_SELECT,
												select), 2, "select");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_HARM_SOURCE,
												source), 3, "source");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_HARM_NUMBER,
												number), 4, "number");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_HARM_SCALING,
												scaling), 5, "scaling");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_VIEW_HARM_SUBSET,
												subset), 6, "subset");
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}

/// HIFN  Queries measurements specified via ConfigureFunctionList method.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR arrayLength/Number of array points requested.
/// HIPAR data/Queries measurements specified via ConfigureFunctionList method.
/// HIPAR actualDataLength/Number of points actually returned in the array.
ViStatus _VI_FUNC rshmc8015_QueryData(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	arrayLength,
	ViReal64	data[],
	ViInt32*	actualDataLength
)
{
	ViStatus	error = VI_SUCCESS;
    ViChar		*ext_buf = NULL, *p2buf = NULL;
	ViUInt32	ret_cnt;
	ViInt32		i=0;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 4), 2, "channel");
    
	checkErr (viPrintf(instrSession, "CHAN%ld:MEAS:FORM ASC;:CHAN%ld:MEAS:DATA?\n", channel, channel));
	checkErr (Rs_ReadDataUnknownLength(instrSession, &ext_buf, &ret_cnt));
	
	p2buf = strtok (ext_buf, ",\r\n"); 
	while(p2buf)
	{
		if(i < arrayLength)
		{
			data[i++] = rshmc8015_atof(p2buf);
		}
		p2buf = strtok(NULL, ",\r\n");
	}
	
	*actualDataLength = i;
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
	if(ext_buf) free(ext_buf);
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Sets list of function names.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR functionList/List of function names.
ViStatus _VI_FUNC rshmc8015_WriteFunctionList(
	ViSession	instrSession,
	ViInt32	channel,
	ViString	functionList
)
{
	ViStatus	error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 4), 2, "channel");
    
	checkErr (viPrintf(instrSession, "CHAN%ld:MEAS:FUNC %s\n", channel, functionList));
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Queries list of function name.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the 
/// HIPAR bufferSize/Output parameter.  
/// HIPAR functionList/This indicator returns the function names as comma separated strings, 
/// HIPAR functionList/for example: URMS,P,TEMP1
ViStatus _VI_FUNC rshmc8015_QueryFunctionList(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	bufferSize,
	ViChar	functionList[]
)
{
	ViStatus	error = VI_SUCCESS;
    ViChar		*ext_buf = NULL;
	ViUInt32	ret_cnt;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 4), 2, "channel");
    
	checkErr (viPrintf(instrSession, "CHAN%ld:MEAS:FUNC?\n", channel, channel));
	checkErr (Rs_ReadDataUnknownLength(instrSession, &ext_buf, &ret_cnt));
	
	strncpy (functionList, ext_buf, bufferSize);
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
	if(ext_buf) free(ext_buf);
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  This function returns the length of function list.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc804x_init or 
/// HIPAR instrSession/rshmc804x_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR length/Returns the length of function list.
ViStatus _VI_FUNC rshmc8015_QueryFunctionListLength(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32*	length
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_GetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH,
												length), 3, "length");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN  Configures the global data integrator function.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR enabled/Sets Integrator state (enables or disables the Integrator).
/// HIPAR mode/Sets the integration mode.
/// HIPAR duration/Sets the integration timer value.
ViStatus _VI_FUNC rshmc8015_ConfigureIntegrator(
	ViSession	instrSession,
	ViBoolean	enabled,
	ViInt32	mode,
	ViReal64	duration
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_STATE,
												enabled), 2, "enabled");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_MODE,
												mode), 3, "mode");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_DURATION,
												duration), 4, "duration");
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  This function specifies the type of integrator operation and performs 
/// HIFN  the operation.
/// HIFN     
/// HIFN     Attribute(s):
/// HIFN     RSHMC8015_ATTR_INTEGRATOR_START
/// HIFN     RSHMC8015_ATTR_INTEGRATOR_STOP
/// HIFN     RSHMC8015_ATTR_INTEGRATOR_RESET
/// HIFN     
/// HIFN     Remote-control command(s):
/// HIFN     INTegrator:STARt
/// HIFN     INTegrator:STOP
/// HIFN     INTegrator:RESet
/// HIFN     
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR operation/Selects the integration operation.
ViStatus _VI_FUNC rshmc8015_IntegratorOperation(
	ViSession	instrSession,
	ViInt32	operation
)
{
ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	switch (operation)
	{
		case RSHMC8015_VAL_INTEGRATOR_OPERATION_START:
			viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_START,
												VI_NULL));
			break;
		case RSHMC8015_VAL_INTEGRATOR_OPERATION_STOP:
			viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_STOP,
												VI_NULL));
			break;
		case RSHMC8015_VAL_INTEGRATOR_OPERATION_RESET:
			viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_INTEGRATOR_RESET,
												VI_NULL));
			break;
		default:
			viCheckParm (RS_ERROR_INVALID_PARAMETER, 2, "Operation"); 
			break;
	}
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Sets integrator's start time.  
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR year/This parameter representing the year.
/// HIPAR month/This parameter representing the month of the year.
/// HIPAR day/This parameter representing the day of the month.
/// HIPAR hour/This parameter representing the hour.
/// HIPAR minute/This parameter representing the minutes.
/// HIPAR second/This parameter representing the seconds.
ViStatus _VI_FUNC rshmc8015_ConfigureIntegratorStartTime(
	ViSession	instrSession,
	ViInt32	year,
	ViInt32	month,
	ViInt32	day,
	ViInt32	hour,
	ViInt32	minute,
	ViInt32	second
)
{
	ViStatus	error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	checkErr (viPrintf(instrSession, "INT:STIME %ld,%ld,%ld,%ld,%ld,%ld\n", 
					   								year, month, day, hour, minute, second));
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Set the filename and device for logging.   
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR filename/Selects the filename.
/// HIPAR device/Selects the device.
ViStatus _VI_FUNC rshmc8015_ConfigureLoggingFile(
	ViSession	instrSession,
	ViString	filename,
	ViInt32	device
)
{
	ViStatus	error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
	checkErr (viPrintf(instrSession, "LOG:FNAM '%s',%s\n", filename, deviceArr[device]));
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Configures the global data logging function.    
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR enabled/Sets logging state (starts or stops a logging session).
/// HIPAR mode/Selects the mode of the logging function.
/// HIPAR count/Sets maximum number of data rows of a log file.
/// HIPAR time/Sets the time in "TIME" mode.
ViStatus _VI_FUNC rshmc8015_ConfigureLogging(
	ViSession	instrSession,
	ViBoolean	enabled,
	ViInt32	mode,
	ViInt32	count,
	ViReal64	time
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, "",
                                                RSHMC8015_ATTR_LOGGING_STATE,
												enabled), 2, "enabled");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_LOGGING_MODE,
												mode), 3, "mode");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_LOGGING_COUNT,
												count), 4, "count");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, "",
                                                RSHMC8015_ATTR_LOGGING_TIME,
												time), 5, "time");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Sets logging start time.    
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR year/This parameter representing the year.
/// HIPAR month/This parameter representing the month of the year.
/// HIPAR day/This parameter representing the day of the month.
/// HIPAR hour/This parameter representing the hour.
/// HIPAR minute/This parameter representing the minutes.
/// HIPAR second/This parameter representing the seconds.
ViStatus _VI_FUNC rshmc8015_ConfigureLoggingStartTime(
	ViSession	instrSession,
	ViInt32	year,
	ViInt32	month,
	ViInt32	day,
	ViInt32	hour,
	ViInt32	minute,
	ViInt32	second
)
{
	ViStatus	error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	checkErr (viPrintf(instrSession, "LOG:STIME %ld,%ld,%ld,%ld,%ld,%ld\n", 
					   								year, month, day, hour, minute, second));
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;      
}


/// HIFN  Queries the result of limit check.  
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR limitCheckResult/Queries the result of limit check.
ViStatus _VI_FUNC rshmc8015_QueryLimitCheckResult(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	limit,
	ViBoolean*	limitCheckResult
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[20] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 1), 2, "channel");
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, limit, 1, 6), 3, "limit"); 
	
    sprintf (rep_cap, "CH%ld,Lim%ld", channel, limit);

    viCheckParm (rshmc8015_GetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_CHECK_RESULT,
												limitCheckResult), 4, "Limit Check Result");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Queries the result of limit calculation between min and max values.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR limitPercent/Queries the result of limit calculation between min and max values.
ViStatus _VI_FUNC rshmc8015_QueryLimitPercent(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	limit,
	ViReal64*	limitPercent
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[20] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 1), 2, "channel");
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, limit, 1, 6), 3, "limit"); 
	
    sprintf (rep_cap, "CH%ld,Lim%ld", channel, limit);

    viCheckParm (rshmc8015_GetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_PERCENT,
												limitPercent), 4, "Limit Percent");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Configures measurement limit.  
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR limit/Numerical selection of a limit
/// HIPAR state/Sets state of the limit.
/// HIPAR source/Sets source (function) of the limit.
/// HIPAR high/Sets limit's upper boundary.
/// HIPAR low/Sets limit's lower boundary.
ViStatus _VI_FUNC rshmc8015_ConfigureMeasurementLimit(
	ViSession	instrSession,
	ViInt32	channel,
	ViInt32	limit,
	ViBoolean	state,
	ViInt32	source,
	ViReal64	high,
	ViReal64	low
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[20] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));
	
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 1), 2, "channel");
	viCheckParm (rshmc8015_invalidViInt32Range (instrSession, limit, 1, 6), 3, "limit"); 
	
    sprintf (rep_cap, "CH%ld,Lim%ld", channel, limit);

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_STATE,
												state), 4, "state");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_SOURCE,
												source), 5, "source");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_HIGH,
												high), 6, "high");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_LIMIT_LOW,
												low), 7, "low");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}

/// HIFN  Configures analog input settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR state/Sets enabled state of the analog input.
ViStatus _VI_FUNC rshmc8015_ConfigureExtAnalogIn(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	state
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_AINPUT_STATE,
												state), 3, "state");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Configures analog output settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR state/Sets enabled state of the analog output.
/// HIPAR mode/Sets analog output mode.
ViStatus _VI_FUNC rshmc8015_ConfigureExtAnalogOut(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	state,
	ViInt32	mode
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_AOUTPUT_STATE,
												state), 3, "state");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_AOUTPUT_MODE,
												mode), 4, "mode");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Configures digital input settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR state/Sets enabled state of the digital input.
/// HIPAR mode/Sets digital input mode.
/// HIPAR invert/Sets negation of ext. digital input.
ViStatus _VI_FUNC rshmc8015_ConfigureExtDigitalIn(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	state,
	ViInt32	mode,
	ViBoolean	invert
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DINPUT_STATE,
												state), 3, "state");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DINPUT_MODE,
												mode), 4, "mode");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DINPUT_INVERT,
												invert), 5, "invert");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;      
}


/// HIFN  Configures digital output settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR state/Sets enabled state of the digital output.
/// HIPAR mode/Sets digital output mode.
/// HIPAR invert/Sets negation of ext. digital output.
/// HIPAR outputState/Sets digital output state.
ViStatus _VI_FUNC rshmc8015_ConfigureExtDigitalOut(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	state,
	ViInt32	mode,
	ViBoolean	invert,
	ViBoolean	outputState
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DOUTPUT_STATE,
												state), 3, "state");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DOUTPUT_MODE,
												mode), 4, "mode");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DOUTPUT_INVERT,
												invert), 5, "invert");
	
	viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE,
												outputState), 6, "Output State");
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;       
}


/// HIFN  Configures external sensor settings.
/// HIFN     
/// HIFN     Attribute(s):
/// HIFN     RSHMC8015_ATTR_EXT_SENSOR_STATE
/// HIFN     RSHMC8015_ATTR_EXT_SENSOR_MODE
/// HIFN     RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE
/// HIFN     RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO
/// HIFN     RSHMC8015_ATTR_EXT_SENSOR_RANGE
/// HIFN     
/// HIFN     Remote-control command(s):
/// HIFN     CHANnel<n>[:EXTern]:SENSor[:STATe]
/// HIFN     CHANnel<n>[:EXTern]:SENSor:MODE
/// HIFN     CHANnel<n>[:EXTern]:SENSor:EXTShunt[:RESistance]
/// HIFN     CHANnel<n>[:EXTern]:SENSor:CCLamp[:RATio]
/// HIFN     CHANnel<n>[:EXTern]:SENSor:RANGe
/// HIFN     
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR channel/Numerical selection of a channel
/// HIPAR state/Sets enabled state of the sensor.
/// HIPAR mode/Sets sensor mode.
/// HIPAR resistance/Sets resistance of the external shunt.
/// HIPAR ratio/Sets V/A ratio of the current clamp.
/// HIPAR range/Selects an appropriate sensor voltage range for passed peak voltage 
/// HIPAR range/value.
ViStatus _VI_FUNC rshmc8015_ConfigureExtSensor(
	ViSession	instrSession,
	ViInt32	channel,
	ViBoolean	state,
	ViInt32	mode,
	ViReal64	resistance,
	ViReal64	ratio,
	ViReal64	range
)
{
	ViStatus error = VI_SUCCESS;
	ViChar	rep_cap[5] = "";

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    checkErr(rshmc8015_channelRepCap (instrSession, channel, rep_cap));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_SENSOR_STATE,
												state), 3, "state");
	
	viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_SENSOR_MODE,
												mode), 4, "mode");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE,
												resistance), 5, "resistance");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO,
												ratio), 6, "ratio");
	
	viCheckParm (rshmc8015_SetAttributeViReal64 (instrSession, rep_cap,
                                                RSHMC8015_ATTR_EXT_SENSOR_RANGE,
												range), 7, "range");
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN  This function sets the value of a ViInt32 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViInt32 (ViSession instrSession, ViString channelName,
                                                ViAttr attributeId, ViInt32 value)
{
    return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function sets the value of a ViInt64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsavpavda_init or 
/// HIPAR instrSession/rsavpavda_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViInt64 (ViSession instrSession,
                                                 ViChar channelName[],
                                                 ViAttr attributeId,
                                                 ViInt64 value)
{
	return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function sets the value of a ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViReal64 (ViSession instrSession, ViString channelName,
                                                 ViAttr attributeId, ViReal64 value)
{
     return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function sets the value of a ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViString (ViSession instrSession, ViString channelName,
                                                 ViAttr attributeId, ViString value)
{
    return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);
}

/// HIFN  This function sets the value of a ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViBoolean (ViSession instrSession, ViString channelName,
                                                  ViAttr attributeId, ViBoolean value)
{
    return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function sets the value of a ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to set the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value to which you want to set the attribute.
ViStatus _VI_FUNC rshmc8015_SetAttributeViSession (ViSession instrSession, ViString channelName,
                                                  ViAttr attributeId, ViSession value)
{
    return Rs_SetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function queries the value of a ViInt32 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a 
/// HIPAR value/ViInt32 variable.
ViStatus _VI_FUNC rshmc8015_GetAttributeViInt32 (ViSession instrSession, ViString channelName,
                                                ViAttr attributeId, ViInt32 *value)
{
    return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            (ViInt32) sizeof (ViInt32), (ViInt32 *)value);
}

/// HIFN  This function queries the value of a ViInt64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsavpavda_init or 
/// HIPAR instrSession/rsavpavda_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a 
/// HIPAR value/ViInt64 variable.
ViStatus _VI_FUNC rshmc8015_GetAttributeViInt64 (ViSession instrSession,
                                                 ViChar channelName[],
                                                 ViAttr attributeId,
                                                 ViInt64 *value)
{
	return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            (ViInt32) sizeof (ViInt64), (ViInt64 *)value);
}

/// HIFN  This function queries the value of a ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a 
/// HIPAR value/ViReal64 variable.
ViStatus _VI_FUNC rshmc8015_GetAttributeViReal64 (ViSession instrSession, ViString channelName,
                                                 ViAttr attributeId, ViReal64 *value)
{
    return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            (ViInt32) sizeof (ViReal64), (ViReal64 *)value);
}

/// HIFN  This function queries the value of a ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR bufSize/Pass the number of bytes in the ViChar array you specify for the 
/// HIPAR bufSize/Attribute Value parameter.  
/// HIPAR value/The buffer in which the function returns the current value of the 
/// HIPAR value/attribute.  The buffer must be of type ViChar and have at least as many 
/// HIPAR value/bytes as indicated in the Buffer Size parameter.
ViStatus _VI_FUNC rshmc8015_GetAttributeViString (ViSession instrSession, ViString channelName,
                                                 ViAttr attributeId, ViInt32 bufSize,
                                                 ViChar value[])
{
    return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            bufSize, value);
}

/// HIFN  This function queries the value of a ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a 
/// HIPAR value/ViBoolean variable.
ViStatus _VI_FUNC rshmc8015_GetAttributeViBoolean (ViSession instrSession, ViString channelName,
                                                  ViAttr attributeId, ViBoolean *value)
{
    return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            (ViInt32) sizeof (ViBoolean), (ViBoolean *)value);
}

/// HIFN  This function queries the value of a ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to obtain the value of the attribute. If the 
/// HIPAR channelName/attribute is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Returns the current value of the attribute.  Pass the address of a 
/// HIPAR value/ViSession variable.
ViStatus _VI_FUNC rshmc8015_GetAttributeViSession (ViSession instrSession, ViString channelName,
                                                  ViAttr attributeId, ViSession *value)
{
    return Rs_GetAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL,
                            (ViInt32) sizeof (ViSession), (ViSession *)value);
}

/// HIFN  This function checks the validity of a value you specify for a ViInt32 
/// HIFN  attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViInt32 (ViSession instrSession, ViString channelName,
                                                  ViAttr attributeId, ViInt32 value)
{
    return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function checks the validity of a value you specify for a ViInt64 
/// HIFN  attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rsavpavda_init or 
/// HIPAR instrSession/rsavpavda_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViInt64 (ViSession instrSession,
                                                   ViChar channelName[],
                                                   ViAttr attributeId,
                                                   ViInt64 value)
{
	return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function checks the validity of a value you specify for a 
/// HIFN  ViReal64 attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViReal64 (ViSession instrSession, ViString channelName,
                                                   ViAttr attributeId, ViReal64 value)
{
    return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function checks the validity of a value you specify for a 
/// HIFN  ViString attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViString (ViSession instrSession, ViString channelName,
                                                   ViAttr attributeId, ViString value)
{
    return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, value);
}

/// HIFN  This function checks the validity of a value you specify for a 
/// HIFN  ViBoolean attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViBoolean (ViSession instrSession, ViString channelName,
                                                    ViAttr attributeId, ViBoolean value)
{
    return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN  This function checks the validity of a value you specify for a 
/// HIFN  ViSession attribute.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR channelName/If the attribute is channel-based, this parameter specifies the name 
/// HIPAR channelName/of the channel on which to check the attribute value. If the attribute 
/// HIPAR channelName/is not channel-based, then pass VI_NULL or an empty string.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR value/Pass the value which you want to verify as a valid value for the 
/// HIPAR value/attribute.
ViStatus _VI_FUNC rshmc8015_CheckAttributeViSession (ViSession instrSession, ViString channelName,
                                                    ViAttr attributeId, ViSession value)
{
    return Rs_CheckAttribute (instrSession, channelName, attributeId, RS_VAL_DIRECT_USER_CALL, &value);
}

/// HIFN This function returns the repeated capability id(s) that belongs
/// HIFN to the attribute you specify. More then one id is listed in
/// HIFN comma separated string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR attributeID/Pass the ID of an attribute.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id(s) parameter.
/// HIPAR repeatedCapabilityIds/The buffer in which the function returns the repeated capability id(s) belonging to the attribute.
ViStatus _VI_FUNC rshmc8015_GetAttributeRepeatedCapabilityIds (ViSession instrSession,
                                                            ViUInt32 attributeID,
                                                            ViInt32 bufferSize,
                                                            ViChar _VI_FAR repeatedCapabilityIds[])
{
    ViStatus    error = VI_SUCCESS;
    ViChar      repCapNameId[RS_MAX_MESSAGE_BUF_SIZE] = "";

    if (bufferSize <= 0)
        viCheckParm(RS_ERROR_INVALID_PARAMETER, 3, "Buffer Size");

    viCheckErr (Rs_GetAttributeRepCapNameId (instrSession, attributeID, repCapNameId));

    strncpy (repeatedCapabilityIds, repCapNameId, RS_MAX_MESSAGE_BUF_SIZE);
    repeatedCapabilityIds[(bufferSize > RS_MAX_MESSAGE_BUF_SIZE) ?
        RS_MAX_MESSAGE_BUF_SIZE : bufferSize] = '\0';

Error:
    return error;
}

/// HIFN This function returns the repeated capability name(s) that
/// HIFN belongs to the attribute and single repeated capability id you
/// HIFN may specify. More then one name is listed in comma separated
/// HIFN string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR attributeID/Pass the ID of an attribute.
/// HIPAR repeatedCapabilityId/If the attribute applies to a repeated capability such as a trace, this parameter defines the Id of the repeated capability on which to query repeated capability id name(s).
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id Name(s) parameter.
/// HIPAR repeatedCapabilityIdNames/The buffer in which the function returns the repeated capability id name(s) belonging to the attribute.
ViStatus _VI_FUNC rshmc8015_GetAttributeRepeatedCapabilityIdNames (ViSession instrSession,
                                                                ViUInt32 attributeID,
                                                                ViString repeatedCapabilityId,
                                                                ViInt32 bufferSize,
                                                                ViChar _VI_FAR repeatedCapabilityIdNames[])
{
    ViStatus    error = VI_SUCCESS;
    ViChar      repCapName[RS_MAX_MESSAGE_BUF_SIZE] = "";

    if (bufferSize <= 0)
        viCheckParm(RS_ERROR_INVALID_PARAMETER, 4, "Buffer Size");

    viCheckErr (Rs_GetAttributeRepCapName (instrSession,
                                           attributeID,
                                           repeatedCapabilityId,
                                           repCapName));

    strncpy (repeatedCapabilityIdNames, repCapName, RS_MAX_MESSAGE_BUF_SIZE);
    repeatedCapabilityIdNames[(bufferSize >= RS_MAX_MESSAGE_BUF_SIZE) ?
        RS_MAX_MESSAGE_BUF_SIZE - 1 : bufferSize - 1] = '\0';

Error:
    return error;
}

/// HIFN This function resets the instrument to a known state and sends initialization commands to the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
ViStatus _VI_FUNC rshmc8015_reset (ViSession instrSession)
{
    ViStatus    error   = VI_SUCCESS;

    checkErr( Rs_LockSession (instrSession, VI_NULL));

    if (Rs_Simulating(instrSession) == 0)
    {
        viCheckErr (viPrintf (instrSession, "*RST\n"));
    }

    checkErr (rshmc8015_DefaultInstrSetup (instrSession));
    checkErr (rshmc8015_CheckStatus (instrSession));

Error:
    (void) Rs_UnlockSession (instrSession, VI_NULL);
    return error;
}


/// HIFN This function runs the instrument's self test routine and returns the test result(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR testResult/Contains the value returned from the instrument self test.
/// HIPAR testMessage/Returns the self-test response string from the instrument.
ViStatus _VI_FUNC rshmc8015_self_test (ViSession instrSession, ViInt16 *testResult, 
                                      ViChar testMessage[])
{
    ViStatus    error   = VI_SUCCESS;
    
    checkErr( Rs_LockSession (instrSession, VI_NULL));

    if (testResult == NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 2, "Null address for Test Result");
    if (testMessage == NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 3, "Null address for Test Message");

    checkErr (viQueryf (instrSession, "*TST?\n", "%hd", testResult));
	
    if (*testResult == 0)
        strcpy (testMessage, "Self-Test Passed.");
    else
        strcpy (testMessage, "Self-Test Failed.");

Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN This function returns the driver and instrument revisions.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR driverRev/Returns the instrument driver software revision numbers in the form of a string.
/// HIPAR instrRev/Returns the instrument firmware revision numbers in the form of a string.
ViStatus _VI_FUNC rshmc8015_revision_query (ViSession instrSession, ViChar driverRev[], 
                                           ViChar instrRev[])
{
    ViStatus    error   = VI_SUCCESS;

    checkErr( Rs_LockSession (instrSession, VI_NULL));

    if (driverRev == VI_NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 2, "Null address for Driver Revision");
    if (instrRev == VI_NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 3, "Null address for Instrument Revision");

    checkErr( Rs_GetAttribute (instrSession, VI_NULL, RSHMC8015_ATTR_SPECIFIC_DRIVER_REVISION,
                                        0, 256, driverRev));
    checkErr( Rs_GetAttribute (instrSession, "", RSHMC8015_ATTR_INSTRUMENT_FIRMWARE_REVISION,
                                        0, 256, instrRev));
    checkErr( rshmc8015_CheckStatus (instrSession));

Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN  Disables or enables the beeper tone.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR beeperState/Disables or enables the beeper tone.
ViStatus _VI_FUNC rshmc8015_BeeperState(
	ViSession	instrSession,
	ViBoolean	beeperState
)
{
 	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViBoolean (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED,
												beeperState), 2, "Beeper State");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;   
}


/// HIFN  When sending a command, the device emits a beep.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_StartBeep(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_START_BEEP,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Sets the name of the device (capped at 20 characters).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR name/The name of system.
ViStatus _VI_FUNC rshmc8015_SystemName(
	ViSession	instrSession,
	ViString	name
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_NAME,
												name), 2, "Name");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Local operating mode (front panel control). 
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_SystemLocal(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_LOCAL,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  Remote control (front panel control locked).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_SystemRemote(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_REMOTE,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  The front panel control is locked; with the SystemLocal method the 
/// HIFN  front panel control will be activated.
/// HIFN     
/// HIFN     Attribute(s):
/// HIFN     RSHMC8015_ATTR_SYSTEM_RWLOCK
/// HIFN     
/// HIFN     Remote-control command(s):
/// HIFN     SYSTem:RWLock
/// HIFN     
/// HIFN     
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_SystemRWLock(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_RWLOCK,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN  This function queries the number of the SCPI version, which is 
/// HIFN  relevant for the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR length/This control specifies the size of the buffer.
/// HIPAR systemVersion/Returns the number of the SCPI version, which is relevant for the 
/// HIPAR systemVersion/instrument.
ViStatus _VI_FUNC rshmc8015_SystemVersion(
	ViSession	instrSession,
	ViInt32		length,
	ViChar	  	systemVersion[]
)
{
    ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_VERSION,
												length, systemVersion
                                                ), 3, "System Version");

Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN  This function queries the device model.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR length/Sets the allocated memory length of System Version string.
/// HIPAR systemDevice/Returns the system device model.
ViStatus _VI_FUNC rshmc8015_SystemDevice(
	ViSession	instrSession,
	ViInt32	length,
	ViChar	systemDevice[]
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_DEVICE,
												length, systemDevice), 3, "System Device");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;       
}


/// HIFN  Turns the device off. The device can't be enabled remotely after this 
/// HIFN  command.     
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_SystemShutdown(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_SHUTDOWN,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;         
}


/// HIFN  This function queries the software version.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR length/Sets the allocated memory length of System Version string.
/// HIPAR systemSoftware/Returns the system software version.
ViStatus _VI_FUNC rshmc8015_SystemSoftware(
	ViSession	instrSession,
	ViInt32	length,
	ViChar	systemSoftware[]
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_SOFTWARE,
												length, systemSoftware), 3, "System Software");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  This function queries the hardware version.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR length/Sets the allocated memory length of System Version string.
/// HIPAR systemHardware/Returns the system hardware version.
ViStatus _VI_FUNC rshmc8015_SystemHardware(
	ViSession	instrSession,
	ViInt32	length,
	ViChar	systemHardware[]
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_HARDWARE,
												length, systemHardware), 3, "System Hardware");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  This function queries the serial number.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR length/Sets the allocated memory length of System Version string.
/// HIPAR systemSerialNumber/Returns the system serial number.
ViStatus _VI_FUNC rshmc8015_SystemSerialNumber(
	ViSession	instrSession,
	ViInt32	length,
	ViChar	systemSerialNumber[]
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER,
												length, systemSerialNumber), 3, "System Serial Number");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;      
}

/// HIFN This function reads an error code and a message from the
/// HIFN instrument's error queue.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR errCode/Returns the error code read from the instrument's error queue.
/// HIPAR errMessage/Returns the error message string read from the instrument's error message queue.
ViStatus _VI_FUNC rshmc8015_error_query (ViSession instrSession, ViInt32 *errCode, 
                                        ViChar errMessage[])
{
    ViStatus    error   = VI_SUCCESS;
    ViChar      buffer[RSHMC8015_IO_BUFFER_SIZE] = "";
    
    checkErr( Rs_LockSession (instrSession, VI_NULL));

    if (errCode == NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 2, "Null address for Error Code");
    if (errMessage == NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 3, "Null address for Error Message");

    if (Rs_Simulating(instrSession) == 0)                /* call only when locked */
        {
        viCheckErr (rshmc8015_GetAttributeViString( instrSession, "", RSHMC8015_ATTR_SYSTEM_ERROR, RSHMC8015_IO_BUFFER_SIZE, buffer));
        if  (sscanf (buffer, "%ld,\"%256[^\"]", errCode, errMessage) != 2)
            viCheckErr(RS_ERROR_UNEXPECTED_RESPONSE);

        }
    else
        {
            /* Simulate Error Query */
        *errCode = 0;
        strcpy (errMessage, "No error.");
        }

Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN This function converts a status code returned by an instrument driver function into a user-readable string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR errorCode/Pass the Status parameter that is returned from any of the instrument driver functions.
/// HIPAR errorMessage/Returns the user-readable message string that corresponds to the status code you specify.
ViStatus _VI_FUNC rshmc8015_error_message (ViSession instrSession, ViStatus errorCode,
                                          ViChar errorMessage[256])
{
    ViStatus    error   = VI_SUCCESS;

    static      RsStringValueTable errorTable =
        {
            RSHMC8015_ERROR_CODES_AND_MSGS,
            {VI_NULL, VI_NULL}
        };

    (void) Rs_LockSession(instrSession, VI_NULL);

        /* all VISA and RS error codes are handled as well as codes in the table */
    if (errorMessage == VI_NULL)
        viCheckParm( RS_ERROR_INVALID_PARAMETER, 3, "Null address for Error Message");

    checkErr( Rs_GetSpecificDriverStatusDesc(instrSession, errorCode, errorMessage, errorTable));

Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN  This function sets the Enable of selected registers.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR registerOperation/This control selects the registers that will be configured. 
/// HIPAR enable/Sets content of enable register.
/// HIPAR ptransition/Sets content of PTransition register.
/// HIPAR ntransition/Sets content of NTransition register.
ViStatus _VI_FUNC rshmc8015_SetStatusRegister(
	ViSession	instrSession,
	ViInt32	registerOperation,
	ViInt32	enable,
	ViInt32	ptransition,
	ViInt32	ntransition
)
{
	ViStatus	error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, registerOperation, 1, 2), 2, "registerOperation");
    
	checkErr (viPrintf(instrSession, "STAT:%s:ENAB %ld\n", regOperArr[registerOperation], enable));
	
	checkErr (viPrintf(instrSession, "STAT:%s:PTR %ld\n", regOperArr[registerOperation], ptransition));
	
	checkErr (viPrintf(instrSession, "STAT:%s:NTR %ld\n", regOperArr[registerOperation], ntransition));
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;    
}


/// HIFN  This function queries the status reporting system.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR registerOperation/This control selects the registers that will be configured. 
/// HIPAR statusRegisterQuery/This control selects the registers that will be configured. 
/// HIPAR registerValue/Returns content of selected register.
ViStatus _VI_FUNC rshmc8015_GetStatusRegister(
	ViSession	instrSession,
	ViInt32	registerOperation,
	ViInt32	statusRegisterQuery,
	ViInt32*	registerValue
)
{
	ViStatus	error = VI_SUCCESS;
    ViChar		*ext_buf = NULL;
	ViUInt32	ret_cnt;

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, registerOperation, 1, 2), 
				 													2, "Register Operation");
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, statusRegisterQuery, 0, 4), 
				 													2, "Status Register Query");
    
	checkErr (viPrintf(instrSession, "STAT:%s:%s?\n", regOperArr[registerOperation], regTypeArr[statusRegisterQuery]));
	checkErr (Rs_ReadDataUnknownLength(instrSession, &ext_buf, &ret_cnt));
	
	*registerValue = rshmc8015_atol(ext_buf);
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
	if(ext_buf) free(ext_buf);
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}


/// HIFN  Clears all bits in the Questionable Data enable register and the 
/// HIFN  Standard Operation enable register.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
ViStatus _VI_FUNC rshmc8015_StatusPreset(
	ViSession	instrSession
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckErr (rshmc8015_SetAttributeViString (instrSession, "",
                                                RSHMC8015_ATTR_STATUS_PRESET,
												VI_NULL));
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN This function retrieves and then clears the error information
/// HIFN for the session or the current execution thread.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR errorCode/Returns the error code for the session or execution thread.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Description parameter.
/// HIPAR description/Returns the error description for the session or execution thread. If there is no description, the function returns an empty string.
ViStatus _VI_FUNC rshmc8015_GetError (ViSession instrSession, 
                                     ViStatus *errorCode, 
                                     ViInt32 bufferSize,
                                     ViChar description[])  
{
    ViStatus    error       = VI_SUCCESS;
    ViStatus    primary     = VI_SUCCESS,
                secondary   = VI_SUCCESS;
    ViChar      elaboration[RS_MAX_MESSAGE_BUF_SIZE]    = "";
    ViChar      errorMessage[RS_MAX_MESSAGE_BUF_SIZE]  = "";
    ViChar     *appendPoint = errorMessage;
    ViInt32     actualSize  = 0;
    ViBoolean   locked      = VI_FALSE;
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);

    /* Lock Session */
    checkErr( Rs_LockSession(instrSession, &locked));

    /* Test for nulls and acquire error data */
    if (bufferSize != 0)
    {
        if (errorCode == VI_NULL)
        {
            viCheckParm( RS_ERROR_INVALID_PARAMETER, 2, "Null address for Error");
        }
        if (sessionProperties == NULL)
        {
            primary = VI_ERROR_RSRC_NFOUND;
            secondary = 0;
        }
        else
        {
            checkErr( Rs_GetErrorInfo (instrSession, &primary, &secondary, elaboration));
        }
    }

    else
        {
            if (sessionProperties == NULL)
            {
                (void) Rs_UnlockSession (instrSession, &locked);
                return 1024;
            }
            else
            {
                checkErr( Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_ERROR_ELABORATION, 0, 256, elaboration));
                checkErr( Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_SECONDARY_ERROR, 0, (ViInt32) sizeof (secondary), &secondary));
                checkErr( Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_PRIMARY_ERROR, 0, (ViInt32) sizeof (primary), &primary));
            }
        }

    /* Format data */
    if (primary != VI_SUCCESS)
        {
        ViChar msg[256] = "";
        checkErr( rshmc8015_error_message (instrSession, primary, msg));
        appendPoint += sprintf(appendPoint, "Primary Error: (Hex 0x%08X) %s\n", (unsigned int) primary, msg);
        }

    if (secondary != VI_SUCCESS)
        {
        ViChar msg[256] = "";
        checkErr( rshmc8015_error_message (instrSession, secondary, msg));
        appendPoint += sprintf(appendPoint, "Secondary Error: (Hex 0x%08X) %s\n", (unsigned int) secondary, msg);
        }

    if (strlen (elaboration) > 0)
        {
        sprintf(appendPoint, "Elaboration: %s", elaboration);
        }

    actualSize = (ViInt32) (strlen(errorMessage) + 1);

    /* Prepare return values */
    if (bufferSize == 0)
        {
        error = (ViStatus) actualSize;
        }
    else
        {
        if (bufferSize > 0)
            {
            if (actualSize > bufferSize)
                {
                error = actualSize;
                actualSize = bufferSize;
                }
            }
        if (description == VI_NULL)
            {
            viCheckParm( RS_ERROR_INVALID_PARAMETER, 4, "Null address for Description");
            }
        memcpy(description, errorMessage, (size_t)(actualSize-1));
        description[actualSize-1] = '\0';
        }

    if (errorCode)
        {
        *errorCode = primary;
        }

Error:
    /* Unlock Session */
    (void) Rs_UnlockSession (instrSession, &locked);
    return error;
}

/// HIFN This function clears the error code and error description for
/// HIFN the session.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
ViStatus _VI_FUNC rshmc8015_ClearError (ViSession instrSession)                                                        
{                                                                                                           
    return Rs_ClearErrorInfo (instrSession);                                                                             
}

/// HIFN This function writes a user-specified string to the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR writeBuffer/Pass the string to be written to the instrument.
ViStatus _VI_FUNC rshmc8015_WriteInstrData (ViSession instrSession, ViString writeBuffer)
{
    ViStatus error = VI_SUCCESS;

    checkErr (Rs_WriteInstrData (instrSession, writeBuffer));
    
    //checkErr (rshmc8015_CheckStatus (instrSession));
 
Error:   
    return error;
}

/// HIFN Document your function here.
/// HIFN You may use multiple lines for documentation.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR numBytes/Pass the maximum number of bytes to read from the instruments.
/// HIPAR rdBuf/After this function executes, this parameter contains the data that was read from the instrument.
/// HIPAR bytesRead/Returns the number of bytes actually read from the instrument and stored in the Read Buffer.
ViStatus _VI_FUNC rshmc8015_ReadInstrData (ViSession instrSession, ViInt32 numBytes,
                                          ViChar rdBuf[], ViUInt32 *bytesRead)
{
    return Rs_ReadInstrData (instrSession, numBytes, rdBuf, bytesRead);
}

/// HIFN This function queries the ViBoolean value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViBoolean value.
ViStatus _VI_FUNC rshmc8015_QueryViBoolean (ViSession instrSession,
                                           ViString command, 
                                           ViBoolean *value)
{
    ViStatus    error = VI_SUCCESS;
    
    checkErr( Rs_LockSession (instrSession, VI_NULL)); 
    if (strlen(command)==0)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 2, "Command");
    if (value==VI_NULL)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 3, "Value");
    viCheckErr (viQueryf (instrSession, "%s\n", "%d", command, value));
    checkErr( rshmc8015_CheckStatus (instrSession)); 
Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN This function queries the ViInt32 value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViInt32 value.
ViStatus _VI_FUNC rshmc8015_QueryViInt32 (ViSession instrSession,
                                         ViString command, 
                                         ViInt32 *value)
{
    ViStatus    error = VI_SUCCESS;
    
    checkErr( Rs_LockSession (instrSession, VI_NULL)); 
    if (strlen(command)==0)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 2, "Command");
    if (value==VI_NULL)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 3, "Value");
    viCheckErr (viQueryf (instrSession, "%s\n", "%ld", command, value));
    checkErr( rshmc8015_CheckStatus (instrSession)); 
Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN This function queries the ViReal64 value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR value/Returns the ViReal64 value.
ViStatus _VI_FUNC rshmc8015_QueryViReal64 (ViSession instrSession,
                                          ViString command, 
                                          ViReal64 *value)
{
    ViStatus    error = VI_SUCCESS;
    
    checkErr( Rs_LockSession (instrSession, VI_NULL)); 
    if (strlen(command)==0)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 2, "Command");
    if (value==VI_NULL)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 3, "Value");
    viCheckErr (viQueryf (instrSession, "%s\n", "%le", command, value));
    checkErr( rshmc8015_CheckStatus (instrSession)); 
Error:
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN This function queries the ViString value.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
/// HIPAR command/The query to be sent to the instrument.
/// HIPAR bufferSize/Pass the number of bytes in the ViChar array you specify for the Value parameter.
/// HIPAR value/Returns the string value.
ViStatus _VI_FUNC rshmc8015_QueryViString (ViSession instrSession,
                                          ViString command, 
                                          ViInt32 bufferSize,
                                          ViChar _VI_FAR value[])
{
    ViStatus    error = VI_SUCCESS;
    ViChar      *pbuffer = NULL;
    ViUInt32        bytesRead;
    
    checkErr( Rs_LockSession (instrSession, VI_NULL)); 
    if (strlen(command)==0)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 2, "Command");
    if (value==VI_NULL)
        viCheckParm (RS_ERROR_INVALID_PARAMETER, 3, "Value");
    viCheckErr (viPrintf (instrSession, "%s\n", command));
    viCheckErr(Rs_ReadDataUnknownLength (instrSession, &pbuffer, &bytesRead));  
    if (bytesRead>=(ViUInt32)bufferSize)
    {
        strncpy(value, pbuffer, (size_t) (bufferSize-1));
        value[bufferSize-1]='\0';
        error = (ViStatus) (bytesRead+1);
    } 
    else
    {
        strncpy(value, pbuffer, (size_t) bytesRead); 
        value[bytesRead]='\0';   
    }
    checkErr( rshmc8015_CheckStatus (instrSession)); 
Error:
    if (pbuffer) free (pbuffer);
    (void) Rs_UnlockSession(instrSession, VI_NULL);
    return error;
}

/// HIFN  The DATA? query responses screenshot data in binary format
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR destination/Defines destination file to which the data transfer from instrument to 
/// HIPAR destination/control computer applies.
ViStatus _VI_FUNC rshmc8015_ImageSnapshot(
	ViSession	instrSession,
	ViString	destination
)
{
	ViStatus	error = VI_SUCCESS;
    ViChar		*ext_buf = NULL;
	ViUInt32	ret_cnt;
	FILE        *targetFile = NULL; 

    checkErr (Rs_LockSession (instrSession, VI_NULL));
    
	checkErr (viPrintf(instrSession, "HCOP:DATA?\n"));
	
	checkErr (rshmc8015_readDataBlock(instrSession, &ext_buf, &ret_cnt));
	
	if ((targetFile = fopen (destination, "wb")) == NULL)
        return RS_ERROR_CANNOT_OPEN_FILE;
	
	fwrite (ext_buf, sizeof (ViByte), (size_t)ret_cnt, targetFile);
	
	if (fclose(targetFile) != 0)
		return RS_ERROR_CANNOT_OPEN_FILE;
	
    checkErr (rshmc8015_CheckStatus (instrSession));
Error:
	if(ext_buf) free(ext_buf);
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;        
}


/// HIFN  Configures the data format of the screenshot. 
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR imageFormat/Selects the data format of the screenshot.
ViStatus _VI_FUNC rshmc8015_ConfigureImageFormat(
	ViSession	instrSession,
	ViInt32	imageFormat
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_SetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT,
												imageFormat), 2, "Image Format");
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error; 	    
}


/// HIFN  Returns the width and height of the screenshot.
/// HIFN     
/// HIFN     Attribute(s):
/// HIFN     RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH
/// HIFN     RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT
/// HIFN     
/// HIFN     Remote-control command(s):
/// HIFN     HCOPy:SIZE:X?
/// HIFN     HCOPy:SIZE:Y?
/// HIFN     
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.  The handle identifies a particular 
/// HIPAR instrSession/instrument session.
/// HIPAR imageWidth/Returns the width of the screenshot.
/// HIPAR imageHeight/Returns the height of the screenshot.
ViStatus _VI_FUNC rshmc8015_QueryImageSize(
	ViSession	instrSession,
	ViInt32*	imageWidth,
	ViInt32*	imageHeight
)
{
	ViStatus error = VI_SUCCESS;

    checkErr (Rs_LockSession (instrSession, VI_NULL));

    viCheckParm (rshmc8015_GetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH,
												imageWidth), 2, "Image Width");
	
	viCheckParm (rshmc8015_GetAttributeViInt32 (instrSession, "",
                                                RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT,
												imageHeight), 3, "Image Height");
	
Error:
    Rs_UnlockSession(instrSession, VI_NULL);
    return error;     
}

/// HIFN This function closes the instrument.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
ViStatus _VI_FUNC rshmc8015_close (ViSession instrSession)
{
    ViStatus    error   = VI_SUCCESS;

    checkErr( Rs_LockSession (instrSession, VI_NULL));
    checkErr( rshmc8015_RsClose (instrSession));

Error:

    (void) Rs_UnlockSession (instrSession, VI_NULL);
    (void) Rs_Dispose (instrSession);

    return error;
}

/// HIFN This function performs all of the drivers clean-up operations
/// HIFN except for closing the RS session.  This function is called by
/// HIFN rshmc8015_close or by an RS class driver.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rshmc8015_init or 
/// HIPAR instrSession/rshmc8015_InitWithOptions function.
ViStatus _VI_FUNC rshmc8015_RsClose (ViSession instrSession)
{
    ViStatus    error   = VI_SUCCESS;
    ViSession   io      = VI_NULL;

    /* Do not lock here. The caller manages the lock. */

Error:

    if(io != 0)
        {
        ViSession   rmSession = VI_NULL;

        checkErr( Rs_GetAttribute (instrSession, VI_NULL, RS_ATTR_VISA_RM_SESSION, 0, (ViInt32) sizeof (rmSession), &rmSession));
        
        (void) viClose (io);
        (void) viClose (rmSession);
        }
    
    return error;
}

/*****************************************************************************
 *------------------- End Instrument Driver Source Code ---------------------*
 *****************************************************************************/
