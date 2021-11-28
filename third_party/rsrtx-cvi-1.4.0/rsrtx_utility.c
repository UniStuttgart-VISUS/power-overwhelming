/*****************************************************************************
 *------------------------ Utility  -----------------------------------------*
 *****************************************************************************/
#include <float.h>
#include <math.h>
#include "rsrtx.h"

/*****************************************************************************
 *- Callback Declarations ---------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Common Callback Declarations --------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: rsrtx_InitAttributes
 * Purpose:  This function inits attributes to the desired values if needed.
 *****************************************************************************/
ViStatus rsrtx_InitAttributes(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	// - Class Driver Identification -
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_CLASS_DRIVER_DESCRIPTION, 0, RSRTX_CLASS_DRIVER_DESCRIPTION));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_CLASS_DRIVER_PREFIX, 0, RSRTX_CLASS_DRIVER_PREFIX));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_CLASS_DRIVER_VENDOR, 0, RSRTX_CLASS_DRIVER_VENDOR));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_CLASS_DRIVER_REVISION, 0, RSRTX_CLASS_DRIVER_REVISION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, RSRTX_CLASS_SPEC_MAJOR_VERSION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, RSRTX_CLASS_SPEC_MINOR_VERSION));

	// - Driver Identification -
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 0, RSRTX_SPECIFIC_DRIVER_DESCRIPTION));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_PREFIX, 0, RSRTX_SPECIFIC_DRIVER_PREFIX));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_LOCATOR, 0, RSRTX_SPECIFIC_DRIVER_LOCATOR));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_VENDOR, 0, RSRTX_SPECIFIC_DRIVER_VENDOR));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, RSRTX_CLASS_SPEC_MAJOR_VERSION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, RSRTX_CLASS_SPEC_MINOR_VERSION));

	// - Driver Capabilities -
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SUPPORTED_INSTRUMENT_MODELS, 0, RSRTX_SUPPORTED_INSTRUMENT_MODELS));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_GROUP_CAPABILITIES, 0, RSRTX_GROUP_CAPABILITIES));
	checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_FUNCTION_CAPABILITIES, 0, RSRTX_FUNCTION_CAPABILITIES));

	// - Version Info -
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION, 0, RSRTX_MAJOR_VERSION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION, 0, RSRTX_MINOR_VERSION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION, 0, RSRTX_MINOR_MINOR_VERSION));

	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_MAJOR_VERSION, 0, RSRTX_CLASS_SPEC_MAJOR_VERSION));
	checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_MINOR_VERSION, 0, RSRTX_CLASS_SPEC_MINOR_VERSION));

	checkErr(RsCore_SetSpecificDriverRevision(instrSession, RS_ATTR_SPECIFIC_DRIVER_REVISION));

Error:
	return error;
}

/*****************************************************************************
 * Function: rsrtx_DefaultInstrSetup
 * Purpose:  This function sends a default setup to the instrument. The
 *           rsrtx_reset function calls this function. The
 *           rsrtx_RsInit function calls this function when the
 *           user passes VI_FALSE for the reset parameter. This function is
 *           useful for configuring settings that other instrument driver
 *           functions require.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsrtx_DefaultInstrSetup(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    // Set all the attributes to the default state. Do not update inherent attributes!
    checkErr(RsCore_ApplyAttributeDefaults(instrSession, VI_FALSE));

    // Init attributes
    checkErr(rsrtx_InitAttributes(instrSession));

    if (!RsCore_Simulating(instrSession))
    {
        checkErr(RsCore_Write(instrSession, "FORM:BORD LSBF"));
    }

Error:
    return error;
}

/*****************************************************************************
 * Function: rsrtx_CheckStatus
 * Purpose:  This function checks the status of the instrument to detect
 *           whether the instrument has encountered an error. This function
 *           is called at the end of most exported driver functions. If the
 *           instrument reports an error, this function returns
 *           RS_ERROR_INSTRUMENT_SPECIFIC. The user can set the
 *           rsrtx_ATTR_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE to disable this
 *           check and increase execution speed.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rsrtx_CheckStatus(ViSession instrSession)
{
	ViStatus error = VI_SUCCESS;

	if (RsCore_QueryInstrStatus(instrSession) && !RsCore_Simulating(instrSession))
	{
		checkErr(RsCore_CheckStatus(instrSession, VI_SUCCESS));
	}

Error:
	return error;
}