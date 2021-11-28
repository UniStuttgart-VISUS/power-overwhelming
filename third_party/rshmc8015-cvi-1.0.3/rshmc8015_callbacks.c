/*****************************************************************************
 *  Rohde&Schwarz Audio Video Platform HDMI Analyzer
 *  Callbacks
 *
 *  Original Release: October 2013
 *  By: Martin Krcmar
 *
 *  Should you have any technical questions please contact the hotline of
 *  Rohde & Schwarz Vertriebs-GmbH Rohde & Schwarz Support Center
 *
 *  e-mail: CustomerSupport@rohde-schwarz.com
 *

 *****************************************************************************/

#include "rshmc8015.h"
#include "rshmc8015_utility.h"
#include <float.h>
#include <math.h>

#include "time.h"
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    #define ANSI
#endif
#ifndef ANSI                /* UNIX compatible */
    #include <sys/timeb.h>
    #include <sys/types.h>
    #include <unistd.h>
    #define Sleep sleep
#else                       /* ANSI compatible */
        #include <windows.h>
#endif

#pragma warning (disable:4100) // unreferenced formal parameter

/*****************************************************************************
 * Function: Rs_CheckStatusCallback
 * Purpose:  This function queries the instrument to determine if it has
 *           encountered an error. If the instrument has encountered an
 *           error, this function returns the RS_ERROR_INSTRUMENT_SPECIFIC
 *           error code. This function is called by the
 *           Rs_CheckStatus utility function. The
 *           Rs_SetAttribute and Rs_GetAttribute functions invoke this
 *           function when the optionFlags parameter includes the
 *           RS_VAL_DIRECT_USER_CALL flag.
 *
 *           The user can disable calls to this function by setting the
 *           RSSPECAN_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE.  The driver can
 *           disable the check status callback for a particular attribute by
 *           setting the RS_VAL_DONT_CHECK_STATUS flag.
 *
 *****************************************************************************/
ViStatus rshmc8015_CheckStatusCallback (ViSession instrSession)
{
    ViStatus    error   = VI_SUCCESS;
    ViInt16     esr     = 0;

    viCheckErr (viQueryf (instrSession, "*STB?\n", "%hd", &esr));

    if ((esr & IEEE_488_2_ERROR_MASK) != 0)
    {
        viCheckErr (RS_ERROR_INSTR_SPECIFIC);
    }

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_WaitForOPCCallback
 * Purpose:  This function waits until the instrument has finished processing
 *           all pending operations. This function is called by the
 *           Rs_WaitForOPC utility function. The RS engine invokes
 *           this function in the following two cases:
 *           - Before invoking the read callback for attributes for which the
 *             RS_VAL_WAIT_FOR_OPC_BEFORE_READS flag is set.
 *           - After invoking the write callback for attributes for which the
 *             RS_VAL_WAIT_FOR_OPC_AFTER_WRITES flag is set.
 *
 *****************************************************************************/
ViStatus rshmc8015_WaitForOPCCallback (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS;
    ViUInt16    response    = 0;
    //ViInt32     counter     = 0;
    ViInt32     opc_timeout = 0;
    clock_t     start_time = clock();
	ViReal64    opc_timeout_s = 0.0;
    
    checkErr( Rs_GetAttribute (instrSession, NULL, RS_ATTR_OPC_TIMEOUT, 0,
        (ViInt32) sizeof (opc_timeout), &opc_timeout));
	
	opc_timeout_s = (ViReal64) opc_timeout / 1000;

    /* Check STB for errors. */
    do
    {
		error = viReadSTB (instrSession, &response);

        if ((((double)(clock() - start_time))/(double)CLOCKS_PER_SEC) >= opc_timeout_s)
            return VI_ERROR_TMO;
		else
			Sleep (0);

        /* Wait while STB is non zero value. Only Error/Event Queue
           and ESB bits are taken into consideration. */
    
    } while ((response & IEEE_488_2_SRE_MASK) == 0);
    /* (check Error Queue bit in STB) */
    error = ((response & IEEE_488_2_ERROR_MASK) != 0) ? RS_ERROR_INSTRUMENT_STATUS : error;


Error:
    return error;

}

/*****************************************************************************
 *- Read Callbacks ----------------------------------------------------------*
 *****************************************************************************/
 ViStatus rshmc8015_parseNAN_ReadCallback (ViSession instrSession, ViConstString repCapName, ViAttr attributeId, ViInt32 bufSize, void *value)
 {
	 RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    ViChar      *cmd            = VI_NULL,
                buffer[RS_MAX_MESSAGE_BUF_SIZE] = "";

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* If no command available, exit the function */
    if (sessionProperties -> attr[idx].command == VI_NULL)
        return VI_SUCCESS;

    /* Check if attribute uses repeated capabilities */
    if (sessionProperties -> attr[idx].usercaps == VI_TRUE)
        {
        if (!repCapName)
            viCheckErr (RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME);

        if (strlen (repCapName) == 0)
            viCheckErr (RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME);
        }

    /* Build the command string */
    viCheckErr (Rs_BuildCommandString (instrSession, attributeId, idx, repCapName, &cmd));
	
	if (sessionProperties -> attr[idx].access==RS_VAL_READ_ONLY) 
    {
		viCheckErr (viPrintf (instrSession, "%s", cmd));
    }
    else
    {
    	viCheckErr (viPrintf (instrSession, "%s?", cmd));
    }
	
	viCheckErr (viRead (instrSession, (ViBuf) buffer, RS_MAX_MESSAGE_BUF_SIZE, NULL));
	if (strstr (buffer, "NAN") != NULL)
	{
		*((ViReal64*)value) = RSHMC8015_NAN;
	}
	else
	{
		*((ViReal64*)value) = rshmc8015_atof (buffer);
	}
Error:
	
    if (cmd)
        free (cmd);

    return error;
 }
 
/*****************************************************************************
 *- Write Callbacks ---------------------------------------------------------*
 *****************************************************************************/

 /*****************************************************************************
 *- Check Callbacks ---------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Coerce Callbacks --------------------------------------------------------*
 *****************************************************************************/


/*****************************************************************************
 *- Range Table Callbacks ---------------------------------------------------*
 *****************************************************************************/
