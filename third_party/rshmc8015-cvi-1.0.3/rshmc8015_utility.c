/*****************************************************************************
 *------------------------ Utility  -----------------------------------------*
 *****************************************************************************/
#include <float.h>
#include <math.h>
#include "rshmc8015.h"

/*****************************************************************************
 *- Callback Declarations ---------------------------------------------------*
 *****************************************************************************/

ViStatus rshmc8015_CheckStatusCallback (ViSession io);

/*****************************************************************************
 *- Common Callback Declarations --------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: rshmc8015_InitAttributes
 * Purpose:  This function inits attributes to the desired values if needed.
 *****************************************************************************/
ViStatus rshmc8015_InitAttributes (ViSession instrSession)
{
    ViStatus    error           = VI_SUCCESS;
    ViInt32     p2value         = 0;
    void        *p2void;
    ViChar      buffer[RS_MAX_MESSAGE_BUF_SIZE],
                revision[RS_MAX_MESSAGE_BUF_SIZE],
                manufacturer[RS_MAX_MESSAGE_BUF_SIZE],
                model[RS_MAX_MESSAGE_BUF_SIZE],
                tmp_model[RS_MAX_MESSAGE_BUF_SIZE],
                idQ[RS_MAX_MESSAGE_BUF_SIZE],
                options_list[RS_MAX_MESSAGE_BUF_SIZE] = "";
                

    buffer[RS_MAX_MESSAGE_BUF_SIZE -1] = 0;

    /*- Misc -*/

    if (!Rs_Simulating(instrSession))
        {
        /* Instrument identification */
        viCheckErr (viQueryf (instrSession, "*IDN?\n", "%[^\r\n]", idQ));
        idQ[RS_MAX_MESSAGE_BUF_SIZE - 1] = 0;
        checkErr (Rs_SetAttribute (instrSession, "", RSHMC8015_ATTR_ID_QUERY_RESPONSE, 0, idQ));
        
        /* Option(s) string */
        //viCheckErr (viQueryf (instrSession, "*OPT?\n", "%[^\r\n]", options_list));
        //options_list[RS_MAX_MESSAGE_BUF_SIZE - 1] = 0;
        
        }
    else /* Simulating */
        {
        /* Instrument identification */
        strncpy (idQ, RSHMC8015_SIMULATION_ID_QUERY, RS_MAX_MESSAGE_BUF_SIZE - 1);
        checkErr (Rs_SetAttribute (instrSession, "", RSHMC8015_ATTR_ID_QUERY_RESPONSE, 0, idQ));
        
        /* Option(s) string */
        strncpy (options_list, RSHMC8015_SIMULATION_OPT_QUERY, RS_MAX_MESSAGE_BUF_SIZE - 1);
        }

    /*- Inherent Instrument Specific Attributes ----------------------------*/

    /*- User Options -*/

    /*
    RS_ATTR_RANGE_CHECK             ... Rs_SpecificDriverNew
    RS_ATTR_QUERY_INSTRUMENT_STATUS ... Rs_SpecificDriverNew
    RS_ATTR_CACHE                   ... Rs_SpecificDriverNew
    RS_ATTR_SIMULATE                ... Rs_SpecificDriverNew
    RS_ATTR_RECORD_COERCIONS        ... not supported
    RS_ATTR_INTERCHANGE_CHECK       ... not supported
    RS_ATTR_SPY                     ... not supported
    RS_ATTR_USE_SPECIFIC_SIMULATION ... not supported
    */

    /*- Class Driver Identification -*/

    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_DESCRIPTION, 0, RSHMC8015_CLASS_DRIVER_DESCRIPTION));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_PREFIX, 0, RSHMC8015_CLASS_DRIVER_PREFIX));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_VENDOR, 0, RSHMC8015_CLASS_DRIVER_VENDOR));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_REVISION, 0, RSHMC8015_CLASS_DRIVER_REVISION));
    p2value = RSHMC8015_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, &p2value));

    /*- Driver Identification -*/
                                                        
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 0, RSHMC8015_SPECIFIC_DRIVER_DESCRIPTION));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_PREFIX, 0, RSHMC8015_SPECIFIC_DRIVER_PREFIX));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_LOCATOR, 0, RSHMC8015_SPECIFIC_DRIVER_LOCATOR));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_VENDOR, 0, RSHMC8015_SPECIFIC_DRIVER_VENDOR));

    sprintf (buffer, 
             "Driver: %s %d.%d.%d, Compiler: %s %3.2f, "
             "Components: RSEngine %.2f, VISA-Spec %.2f",
             RSHMC8015_SPECIFIC_DRIVER_PREFIX,
             RSHMC8015_MAJOR_VERSION, RSHMC8015_MINOR_VERSION, RSHMC8015_MINOR_MINOR_VERSION,
             RS_COMPILER_NAME, RS_COMPILER_VER_NUM, 
             RS_ENGINE_MAJOR_VERSION + RS_ENGINE_MINOR_VERSION/10.0, 
             Rs_ConvertVISAVer(VI_SPEC_VERSION));

    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_REVISION, 0, buffer));
    p2value = RSHMC8015_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, &p2value));

    /*- Driver Capabilities -*/
                                   
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SUPPORTED_INSTRUMENT_MODELS, 0, RSHMC8015_SUPPORTED_INSTRUMENT_MODELS));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_GROUP_CAPABILITIES, 0, RSHMC8015_GROUP_CAPABILITIES));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_FUNCTION_CAPABILITIES, 0, RSHMC8015_FUNCTION_CAPABILITIES));
    /* RS_ATTR_CHANNEL_COUNT        ... Rs_BuildRepCapTable */

    /*- Driver Setup -*/

    /* RS_ATTR_DRIVER_SETUP         ... Rs_SpecificDriverNew */

    /*- Instrument Identification -*/

    checkErr (Rs_GetAttribute (instrSession, "", RSHMC8015_ATTR_ID_QUERY_RESPONSE, 0, RSHMC8015_IO_BUFFER_SIZE, idQ));
    sscanf (idQ, "%[^,],%[^,],%*[^,],%256[^\n]", manufacturer, tmp_model, revision); // added 2 spaces in the parsing string
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_MANUFACTURER, 0, manufacturer));
    sscanf (tmp_model,"%[^-0-9]",model); // added number elimination
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_MODEL, 0, model));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_INSTRUMENT_FIRMWARE_REVISION, 0, revision));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPTIONS_LIST, 0, options_list));

    /*- Advanced Session Information -*/
                                  
    /*  
    RS_ATTR_IO_RESOURCE_DESCRIPTOR  ... rshmc8015_InitWithOptions
    RS_ATTR_LOGICAL_NAME            ... not supported
    */

    /*- Inherent Vendor Specific Attributes --------------------------------*/

    /*- Error Info -*/

    /*
    RS_ATTR_PRIMARY_ERROR           ... Rs_SetErrorInfo
    RS_ATTR_SECONDARY_ERROR         ... Rs_SetErrorInfo
    RS_ATTR_ERROR_ELABORATION       ... Rs_SetErrorInfo
    */

    /*- Session I/O -*/

    /*
    RS_ATTR_VISA_RM_SESSION         ... rshmc8015_RsInit
    RS_ATTR_IO_SESSION              ... Rs_UpdateIOSession
    RS_ATTR_IO_SESSION_TYPE         ... not supported
    */

    /*- Version Info -*/                     

    p2value = RSHMC8015_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_MINOR_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_CLASS_SPEC_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_MAJOR_VERSION, 0, &p2value));
    p2value = RSHMC8015_CLASS_SPEC_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CLASS_DRIVER_MINOR_VERSION, 0, &p2value));
    p2value = RS_ENGINE_MAJOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_MAJOR_VERSION, 0, &p2value));
    p2value = RS_ENGINE_MINOR_VERSION;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_MINOR_VERSION, 0, &p2value));
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_ENGINE_REVISION, 0, RS_ENGINE_REVISION));

    /*- Session Callbacks -*/                

    p2void = rshmc8015_WaitForOPCCallback;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPC_CALLBACK, 0, &p2void));
    p2void = rshmc8015_CheckStatusCallback;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_CHECK_STATUS_CALLBACK, 0, &p2void));
    p2value = RSHMC8015_OPC_TIMEOUT;
    checkErr (Rs_SetAttribute (instrSession, "", RS_ATTR_OPC_TIMEOUT, 0, &p2value));

Error:
    return error;
}

/*****************************************************************************
 * Function: rshmc8015_DefaultInstrSetup
 * Purpose:  This function sends a default setup to the instrument. The
 *           rshmc8015_reset function calls this function. The
 *           rshmc8015_RsInit function calls this function when the
 *           user passes VI_FALSE for the reset parameter. This function is
 *           useful for configuring settings that other instrument driver
 *           functions require.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rshmc8015_DefaultInstrSetup (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;

    /* Set all the attributes to the default state. Do not update inherent attributes! */
    checkErr (Rs_ApplyAttributeDefaults (instrSession, VI_FALSE));

    /* Init attributes */
    checkErr( rshmc8015_InitAttributes (instrSession));

    if (!Rs_Simulating(instrSession))
        {

        viCheckErr( viPrintf (instrSession, "*CLS;*ESE %hu;*SRE 40\n", IEEE_488_2_ESE_MASK));
        }

Error:
    return error;
}

/*****************************************************************************
 * Function: rshmc8015_CheckStatus
 * Purpose:  This function checks the status of the instrument to detect
 *           whether the instrument has encountered an error. This function
 *           is called at the end of most exported driver functions. If the
 *           instrument reports an error, this function returns
 *           RS_ERROR_INSTRUMENT_SPECIFIC. The user can set the
 *           rshmc8015_ATTR_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE to disable this
 *           check and increase execution speed.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus rshmc8015_CheckStatus (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;

    if (Rs_QueryInstrStatus (instrSession) && !Rs_Simulating (instrSession))
        {
        checkErr( rshmc8015_CheckStatusCallback (instrSession));
        }

Error:
    return error;
}

/*****************************************************************************
 * Function: rshmc8015_hardwareRepCap
 * Purpose:  This function checks instance repeated capability and 
 *           creates proper string.
 *****************************************************************************/
ViStatus rshmc8015_channelRepCap (ViSession instrSession, ViInt32 channel, ViChar rep_cap[])
{
    ViStatus    error   = VI_SUCCESS;
    
    viCheckParm (rshmc8015_invalidViInt32Range (instrSession, channel, 1, 1), 2, "Channel");
    sprintf (rep_cap, "CH%d", channel);
	
Error:    
    return error;
}

/*===========================================================================*/
/* Function: Long Signed Integer Value Out Of Range - ViInt32                */
/* Purpose:  This function checks a long signed integer value to see if it   */
/*           lies between a minimum and maximum value.  If the value is out  */
/*           of range, the return value is VI_TRUE, otherwise the return     */
/*           value is VI_FALSE.                                              */
/*===========================================================================*/
ViStatus rshmc8015_invalidViInt32Range (ViSession instrSession, ViInt32 val, ViInt32 min, ViInt32 max)
{
    return (Rs_RangeChecking (instrSession) && (ViBoolean)((val < min || val > max) ? RS_ERROR_INVALID_PARAMETER : VI_SUCCESS));
}

void rshmc8015_ParseStatusString (ViChar buffer[], ViChar output[])
{
	ViChar *p2buf; 
	
	p2buf = strtok (buffer, ",");

	if (strcmp (p2buf , "OK") == 0)
	{
		p2buf = strtok (NULL, "\n");
		strcpy (output, p2buf);
	}
	else
	{
		strcpy (output, p2buf);
	}
}

void rshmc8015_ParseStatusInt (ViChar buffer[], ViInt32 *output)
{
	ViChar *p2buf;
	
	p2buf = strtok (buffer, ",");

	if (strcmp (p2buf , "OK") == 0)
	{
		p2buf = strtok (NULL, "\n");
		*output = rshmc8015_atol (p2buf);
	}
	else
	{
		*output = RSHMC8015_NAN_VI_INT32;
	}
}

void rshmc8015_ParseStatusInt64 (ViChar buffer[], ViInt64 *output)
{
	ViChar *p2buf;
	
	p2buf = strtok (buffer, ",");

	if (strcmp (p2buf , "OK") == 0)
	{
		p2buf = strtok (NULL, "\n");
		*output = rshmc8015_atol64 (p2buf);
	}
	else
	{
		*output = RSHMC8015_NAN_VI_INT64;
	}
}

void rshmc8015_ParseStatusReal (ViChar buffer[], ViReal64 *output)
{
	ViChar *p2buf;
	
	p2buf = strtok (buffer, ",");

	if (strcmp (p2buf , "OK") == 0)
	{
		p2buf = strtok (NULL, "\n");
		*output = rshmc8015_atof (p2buf);
	}
	else
	{
		*output = RSHMC8015_NAN;
	}
}

void rshmc8015_ParseStatusEnum (ViChar buffer[], ViInt32 *output, ViString array[])
{
	ViChar *p2buf;
	
	p2buf = strtok (buffer, ",");

	if (strcmp (p2buf , "OK") == 0)
	{
		p2buf = strtok (NULL, "\n");
		*output = rshmc8015_StringIndex (array, p2buf);
	}
	else
	{
		*output = RSHMC8015_NAN_VI_INT32;
	}
}

/*===========================================================================*/
/* Function: String Index                                                    */
/* Purpose:  Returns the index of string in string array                     */
/*===========================================================================*/
ViInt32 rshmc8015_StringIndex(ViString array[], ViChar buff[])
{
    ViInt32 index = 0;

    while (array[index]){
        if (!strcmp(buff, array[index]))
            break; 
        index++;    
    }        
    /* If found string is not found returns -1. */
    if (!array[index]) return -1;

    return index;
}

/*****************************************************************************
 * Function: rshmc8015_atol
 * Purpose:  This function converts a string to float number. Instrument
 *           may return also string indicating invalid value
 *****************************************************************************/
ViInt32 rshmc8015_atol (ViChar *p2buf)
{
    ViInt32 value = 0;
    ViInt32 returned = 0;
    
    returned = sscanf (p2buf, "%ld", &value);
    
    if (returned == 0)
        value = RSHMC8015_NAN_VI_INT32;
    
    return value;
}

/*****************************************************************************
 * Function: rshmc8015_atol64
 * Purpose:  This function converts a string to float number. Instrument
 *           may return also string indicating invalid value
 *****************************************************************************/
ViInt64 rshmc8015_atol64 (ViChar *p2buf)
{
    ViInt64 value = 0;
    ViInt32 returned = 0;
    
    returned = sscanf (p2buf, "%I64d", &value);
    
    if (returned == 0)
        value = RSHMC8015_NAN_VI_INT64;
    
    return value;
}

/*****************************************************************************
 * Function: rshmc8015_atof
 * Purpose:  This function converts a string to float number. Instrument
 *           may return also string indicating invalid value
 *****************************************************************************/
ViReal64 rshmc8015_atof (ViChar *p2buf)
{
    ViReal64 value = 0;
    ViInt32 returned = 0;
    
    returned = sscanf (p2buf, "%le", &value);
    
    if (returned == 0)
        value = RSHMC8015_NAN;
    
    return value;
}

/*===========================================================================*/
/* Function: Read Binary Data Block                                          */
/* Purpose:  Reads the binary data from instrument. Allocates memory for data*/
/* WARNING:  You must deallocate buffer, if any pointer has been returned.   */
/*           This function does not work correctly, when you read bin data   */
/*           via serial intfc                                            */
/*===========================================================================*/
ViStatus rshmc8015_readDataBlock (ViSession instrSession,
                                  ViChar **outputBuffer, ViUInt32 *byteCount)
{
    ViStatus    error   = VI_SUCCESS;
    ViUInt16    term_en;
    ViUInt32    ret_cnt;
    ViInt32     len;
    ViChar      buffer[RSHMC8015_IO_BUFFER_SIZE];
    
    *outputBuffer = VI_NULL;
	
	if (byteCount == NULL)
		return VI_ERROR_PARAMETER3;
    
    /* Disable termination character */
    checkErr (viGetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, &term_en));
    checkErr (viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_FALSE));

    /* Parse header */
    checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt)); 
    if (buffer[0]=='#')
    {   /* Binary data */
        /* Disable termination character */
        checkErr (viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_FALSE));
    
        /* Parse header */
        checkErr (viRead (instrSession, (ViBuf) buffer, 1, &ret_cnt));

        buffer[1] = '\0';
		if (buffer[0] == '(')
		{
			checkErr (viScanf (instrSession, "%ld)", &len));
		}
		else
			sscanf (buffer, "%ld", &len);
		
		if (len > 0)
		{
	        checkErr (viRead (instrSession, (ViBuf) buffer, len, &ret_cnt));
	        buffer[len] = '\0';
	        sscanf (buffer, "%ld", &len);
			
			if (len > 0)
			{
		        checkAlloc (*outputBuffer = (ViChar*) malloc (len));
		        /* Read useful data */
		        checkErr (viRead (instrSession, (ViBuf) *outputBuffer, len, &ret_cnt));
    
		        if (len != (ViInt32) ret_cnt)
		            viCheckErr (RS_ERROR_UNEXPECTED_RESPONSE);
			}

			/* Flush garbage */
	        viScanf (instrSession,"%*[^\r\n]");
			*byteCount = len;
			if (error > 0) error = VI_SUCCESS;
		}
		else
		{
			/* Unlimited size of data */
			checkErr (Rs_ReadDataUnknownLength (instrSession, outputBuffer, byteCount));
		}
    }
    else
    {   /* ASCII data */
        /* read rest of first value */
		ViChar* extBuf = NULL;

		/* read all values */
		viCheckErr (Rs_ReadDataUnknownLength(instrSession, &extBuf, byteCount));
		checkAlloc (*outputBuffer = (ViChar *)calloc (*byteCount + 2, sizeof (ViChar)));
        **outputBuffer = buffer[0];
		memcpy (*outputBuffer + 1, extBuf, *byteCount);
		*byteCount = *byteCount + 1;
		error = 1;
		
		if (extBuf) free (extBuf);
    }

Error:
    viSetAttribute (instrSession, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    return error;
}
