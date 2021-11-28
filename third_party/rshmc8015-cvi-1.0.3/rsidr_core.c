/*****************************************************************************
 *  Rohde&Schwarz Instrument Driver Core
 *  Non-exported instrument driver core functions implementation.
 *  Original Release: October 2005
 *  By: Martin Koutny
 *
 *  Should you have any technical questions please contact the hotline of
 *  Rohde & Schwarz Vertriebs-GmbH Rohde & Schwarz Support Center
 *
 *  e-mail: CustomerSupport@rohde-schwarz.com
 *
 *  Modification History:
 *      - Rs_GetAttribute - bug fixed in copy returned string to return value for caching. No MAX_BUFFER_SIZE can be copied.
 *                          returned value is allocated by user and its size hasn't to be MAX_BUFFER_SIZE 
 *      - Rs_CheckCallback, Rs_CoerceCallback - user defined Range Table callback moved from "if (rangeTable)" case
 *
 *  1.1, 2005-10-05 by Jiri Kominek
 *      - Rs_WriteCallback, Rs_SetAttribute: added RS_VAL_EVENT to switch structure to support
 *                          attributes with no argument.
 *  1.2, 2005-10-07 by Martin Koutny
 *      - Rs_CheckModelOpt: added missing implementation of option checking,
 *                          functions Rs_SetAttribute, Rs_GetAttribute and
 *                          Rs_CheckAttribute are also modified.
 *      - Range checking (range tables handling) added. Functions
 *                          Rs_SetAttribute, Rs_GetAttribute and
 *                          Rs_CheckAttribute are also modified.
 *      - Added missing implementation for following functions:
 *                          Rs_CoerceCallback
 *                          Rs_CheckCallback
 *      - Updated macros:   Added parameter instrSession instead of vi
 *                          viCheckErrElab
 *                          viCheckParm
 *                          viCheckWarn
 *      - Changed functions: exported vi parameter is replaced by session
 *                          Rs_SetErrorInfo
 *                          Rs_GetErrorInfo
 *                          Rs_ClearErrorInfo
 *      - Reimplemented functions:  Rs_WriteCallback
 *                                  Rs_ReadCallback
 *      - code debugging and fixing
 *  1.3, 2005-10-13 
 *      - Rs_GetRepCapCmdValue - incorrect operation with restricted capabilities fixed
 *      - Rs_CheckModelOpt - if no model listed, option checking was skipped, fixed
 *  1.4, 2005-11-03 
 *      - removed unnecessary warnings
 *      - Rs_CheckModelOpt - various fixes, incorrect recognition of supported models, failed if no option is selected
 *      - fixed Rs_ParamPositionError - incorrect condition for parameter > 8
 *      - fixed Rs_GetErrorInfo - memcpy replaced by memset
 *  1.5, 2005-12-14
 *      - Rs_ReadCallback - ifdef section (RS_LONG_RESPONSE) added for non-standard instrument response 
 *        in long form. If RS_LONG_RESPONSE defined, the values in list has to be sorted since longer to shorter
 *        eg. {UNSP,ETSI2,MMDS2,ETSI,MMDS}
 *  1.6, 2006-03-20
 *      - Rs_Delay - fixed for non-Windows environment. Added Sleep (0) to
 *        prevent live lock.
 *  1.7, 2006-06-06
 *      - Code optimized according to LINT recommendations
 *  1.8, 2006-07-21                                         
 *      - RS_ATTR_... constant values changed in rsidr_core.h 
 *  1.9, 2006-07-26
 *      - Rs_GetAttribute - wait for OPC before read support added
 *      - Rs_GetIndexOfToken - search algorithm modified to distinguish CM10 and CM1
 *        in string CM1, CM2, CM3, ... CM10     
 *      - Rs_WriteCallback - wait for OPC after read support added
 *  1.10, 2006-08-24
 *      - Rs_CheckModelOpt - modified, strtok removed
 *  1.11, 2006-09-04
 *      - removed vi session from API of all functions
 *      - implemented simple resource management; modified Rs_ViSession to avoid too many calls into viGetAttribute
 *      - fixed Rs_WriteCallback, string attribute write fixed
 *  1.12, 2006-12-11
 *      - Rs_ApplyAttributeDefaults - data_size calculation modified for RS_VAL_STRING, the length of default string
 *        is not allways RS_VAL_STRING_SIZE. 
 *      - Rs_WriteCallback - sprintf format string modified for RS_VAL_REAL64   
 *  1.13, 2007-07-16
 *      - RsCompareAttr_CallbackPtr - rcaps, numberOfRestRepCaps, restrictedRcaps removed from RsAttrProperties definition
 *      - Rs_ReadCallback, Rs_WriteCallback - repCap replace changed
 *      - Rs_ValidateAttrForRepCapNameId - repeatid capability working changed
 *      - restricted capability checking removed, no restricted capability supported
 *  2.0, 2007-09-25
 *      - redesigned to support two drivers in one application
 *      - Rs_BuildCommandString function added
 *      - Rs_ClearBeforeRead function added
 *      - *OPC checking modified
 *  2.1, 2007-11-15
 *      - fixed Rs_BuildCommandString for Visual Studio compilation
 *  2.2, 2008-02-27
 *      - added option checking switching, added to structure RsSessionProperties, 
 *        changes in functions: Rs_SpecificDriverNew, Rs_CheckModelOpt
 *  2.3, 2008-09-08
 *      - fixed Rs_SpecificDriverNew - incorrect status query attribute used
 *  2.4, 2008-10-01
 *      - RS_STATUS_CODE_BASE changed from 0x3FFA0000L to 0x3FFF0000L (customer request)
 *  2.5, 2009-02-24
 *      - fixed Rs_BuildCommandString - if there was nothing between repcaps ({repcap1}{repcap2}), function failed
 *      - larger repeated capability buffer (RS_MAX_MESSAGE_BUF_SIZE)
 *  2.6, 2009-04-02
 *      - fixed Rs_SetErrorInfo. When no overwrite selected, attributes have not been filled
 *  2.7, 2009-06-18
 *      - RS_STATUS_CODE_BASE: value changed
 *  2.8, 2010-03-09
 *      - %.12Le changed to %.lG
 *  2.9, 2010-03-10 
 *      - Rs SetAttribute - Check status - attribute specified callback added
 *  2.10, 2010-03-29
 *      - Rs_Delay - Sleep redesigned for Windows and CVI platforms only
 *  2.11, 2010-05-13
 *      - fixed rep_cap comparing method in:
 *        Rs_ValidateAttrForRepCapNameId
 *        Rs_GetAttributeRepCapName
 *        Rs_GetRepCapCmdValue
 *  2.12, 2010-06-07
 *      - fixed Rs_ReadCallback: incorrect ViBoolean reading
 *  2.13, 2010-06-09
 *      - Rs_BuildCommandString, Rs_GetRepCapCmdValue - repCapNames size increased 3 times
 *      - Rs_GetAttributeRepCapName - strncpy is now 3 times bigger (relates to above fix)
 *  2.14, 2010-06-29
 *      - Modifications for 64bit compatibility
 *  2.15, 2010-09-07
 *      - Modification: if repeated capability is NULL or empty string, attributes
 *        does not fail with error, but takes default (zeroth) repeated capability
 *        name
 *  2.16, 2011-06-12
 *      - added dynamic repeated capability
 *      - repeated capabilities are deep copied to session instead of shallow copy
 *      - added Rs_AddRepCap, Rs_RemoveRepCap, Rs_ResetRepCap, Rs_ResetRepCapTable
 *  2.17, 2011-07-03
 *      - removed <userint.h> and ProcessSystemEvents
 *  2.18, 2011-07-18
 *      - added function that returns the count of values in repeated capability:
 *        Rs_RepCapCount
 *  2.19, 2011-12-01
 *      - Rs_GetErrorInfo : modified error elaboration for RS_ERROR_INSTRUMENT_STATUS
 *  2.20, 2011-12-20
 *      - Rs_Dispose : fixed memory leaks
 *  2.21, 2012-02-06
 *      - Rs_GetErrorInfo : modified error elaboration
 *      - Changed some error codes' values
 *  2.22, 2012-05-17
 *      - Added RS_WARN_UNKNOWN_INSTRUMENT_STATUS
 *  2.23, 2012-07-09
 *      - Rs_RepCapCount, Rs_AddRepCap - buffer size changed from RS_IO_BUFFER_SIZE to RS_MAX_MESSAGE_LEN
 *      - RS_IO_BUFFER_SIZE changed value to 1Mi (1048576)
 *  2.24, 2012-07-11
 *      - Changed RS_RANGE_TABLE_LAST_ENTRY to remove warnings, introduced RS_RANGE_TABLE_END_VALUE in unused cmdValue item
 *      - Fixed Rs_CoerceCallback - could have livelock for user values larger than largest coerced range value
 *      - Fixed missing termination character for optionString local copy in Rs_SpecificDriverNew
 *  2.25, 2012-07-13
 *      - Rs_ReadToFile, Rs_WriteFromFile - buffer allocation changed to dynamic
 *  2.26, 2012-09-04
 *      - Rs_ReadCallback : changed parsing of the string response to eliminate
 *        callbacks for quoted strings
 *  2.27, 2012-09-24
 *      - Rs_SetAttribute : added query of ESR register for attributes waiting for OPC to reset ESR register.
 *        It is necessary for synchronization of control and data queue if connected via HiSLIP, 
 *        where *CLS at the begining of command string is not fast enough and consequent call into viRedSTB
 *        reads previous value of STB register
 *  2.29, 2012-10-05
 *      - Rs_ClearBeforeRead : HiSLIP problem (see 2.27) solved.
 *      - Rs_SetAttribute : reverted back to previous version (without ESR query)
 *  2.30, 2012-10-24
 *      - changed macro viCheckParm : now it overwrites old errors. This macro is used in HL
 *        functions and there it is required to do the overwrite
 *  2.31, 2013-01-22
 *      - Rs_ReadCallback : parsing quoted string formating fixed
 *  2.32, 2013-03-13
 *      - Rs_ReadCallback : parsing quoted string formating adapted to single and double quotes
 *  2.33, 2013-04-05
 *      - some includes moved from header file to source file
 *  2.34, 2013-05-15
 *      - ViInt64 data type added
 *  2.35, 2013-09-30
 *      - CVI 2013 warnings fixed
 *  2.36, 2013-12-11
 *      - Rs_ClearBeforeRead - removed local shadowing problem
 *  2.37, 2014-06-26
 *      - viCheckParm macro modified to work with both ways of its use
 *  2.38, 2014-07-07
 *    - Modifications for Int64 data type
 *  2.39, 2014-08-19
 *    - Modified Rs_ClearBeforeRead to support serial interfaces
 *  2.40, 2014-08-21
 *    - Improved robustness of code
 *    - Removed coercing for boolean data type
 *  2.41, 2015-02-26
 *    - new flag RS_VAL_WAIT_TO_CONTINUE added
 *  2.42, 2015-07-07
 *    - added ViStatus Rs_SpreadsheetStringToDblArray
 *  2.43, 2016-02-02
 *    - renumbered overlapping error codes
 *****************************************************************************/
#pragma warning (disable:4100 4055)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <locale.h>
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

#include "rsidr_core.h"

/*****************************************************************************
 *- Useful Constants --------------------------------------------------------*
 *****************************************************************************/
#define RS_IO_BUFFER_SIZE               1048576UL   /* I/O buffer size */

/*****************************************************************************
 *- Non Exported Functions --------------------------------------------------*
 *****************************************************************************/
ViStatus Rs_DisposeRepCapTable (RsSessionPropertiesPtr sessionProperties);
ViStatus Rs_ValidateAttrForRepCapNameId (RsSessionPropertiesPtr  sessionProperties,
                                         ViConstString repCapNameId,
                                         ViAttr attributeId);
/*****************************************************************************
 *- Recource managing -------------------------------------------------------*
 *****************************************************************************/
#define MAX_NUMBER_OF_SESSIONS 50
typedef struct
{
    ViSession              session;
    RsSessionPropertiesPtr properties;
} TsessionData;

static TsessionData gresources[MAX_NUMBER_OF_SESSIONS];
static ViInt32 gresCount = 0;

/*****************************************************************************
 *- Functions to be used in the specific to create and dispose viSession ----*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_SpecificDriverNew
 * Purpose:  This function performs the following initialization actions:
 *
 *           Creates a new RS session to a specific instrument driver and
 *           optionally sets the initial state of the following session
 *           attributes:
 *
 *           RS_ATTR_RANGE_CHECK
 *           RS_ATTR_QUERY_INSTR_STATUS
 *           RS_ATTR_CACHE              ... not supported
 *           RS_ATTR_SIMULATE
 *           RS_ATTR_RECORD_COERCIONS   ... not supported
 *           RS_ATTR_DRIVER_SETUP
 *           RS_ATTR_INTERCHANGE_CHECK  ... not supported
 *
 *           Returns a ViSession handle which you use in subsequent function
 *           calls to identify the session.
 *           This function creates a new session each time you invoke it.
 *           Although you can open more than one RS session for the same
 *           resource, it is best not to do so. You can use the same session
 *           in multiple program threads. You can use the Rs_LockSession and
 *           Rs_UnlockSession functions to protect sections of code that
 *           require exclusive access to the resource.
 *
 *           Note:  This function does not create a VISA session to any
 *           instrument resources. If you use VISA to communicate to the
 *           instrument, you must create a VISA session yourself and set the
 *           RS_ATTR_IO_SESSION attribute to that value. Otherwise, you can
 *           use the RS_ATTR_IO_SESSION attribute to hold a handle to
 *           whatever communications resource you use.
 *
 *****************************************************************************/
ViStatus Rs_SpecificDriverNew (ViSession io,
                               ViConstString specificPrefix,
                               ViConstString optionsString,
                               RsAttrPropertiesPtr *attrList)
{
    RsAttrPropertiesPtr     attrPropertiesList;
    void                    *p2value;

    ViStatus    error           = VI_SUCCESS;
    ViUInt32    numberOfAttr    = 0;
    size_t      length          = 0;
    ViInt32     idx             = 0;
    ViBoolean   boolean         = VI_FALSE;
    ViChar      *p2buf,
                *p2temp,
                *driver_setup   = VI_NULL;
    size_t      data_size       = 0;
    ViInt32     resource_idx    = 0;
    RsSessionPropertiesPtr      sessionProperties;
    
    /* --- Set "C" locale --- */
    {
       char   *locale;

       locale = setlocale(LC_ALL, "C");
    }

    if ((gresCount + 1) > MAX_NUMBER_OF_SESSIONS)
        return RS_ERROR_OUT_OF_MEMORY;
    
    /* --- Allocate session properties structure --- */

    if ((sessionProperties = (RsSessionProperties*) malloc (sizeof (RsSessionProperties))) == VI_NULL)
        return RS_ERROR_OUT_OF_MEMORY;

    memset (sessionProperties, 0, sizeof (RsSessionProperties));

//    sessionProperties -> vi = (ViSession) sessionProperties;
    sessionProperties -> io = io;
    checkErr (viSetAttribute (io, VI_ATTR_USER_DATA, (ViAttrState) sessionProperties));
    
    if (gresCount == 0)
    {
        memset (gresources, 0, MAX_NUMBER_OF_SESSIONS * sizeof (TsessionData));
    }
    while ((gresources[resource_idx].session != 0) && (resource_idx < gresCount)) resource_idx++;
    gresources[resource_idx].session = io;
    gresources[resource_idx].properties = sessionProperties;
    gresCount++;
    
    /* --- Default option checking --- */
    sessionProperties -> optionChecking = VI_TRUE;
    
    /* --- Determine number of attributes --- */
    for (numberOfAttr = 0; attrList[numberOfAttr]; numberOfAttr++);
    //for (numberOfAttr = 0; RsAttrPropertiesList[numberOfAttr]; numberOfAttr++);

    sessionProperties -> numberOfAttr = numberOfAttr;

    /* --- Allocate memory for attribute properties list --- */

    if ((attrPropertiesList = (RsAttrProperties *) malloc (sizeof (RsAttrProperties) * numberOfAttr)) == VI_NULL)
        return RS_ERROR_OUT_OF_MEMORY;

    memset (attrPropertiesList, 0, sizeof (RsAttrProperties) * numberOfAttr);

    sessionProperties -> attr = attrPropertiesList;

    /* ---
            Allocate memory for current (cached) value of each attribute and copy statically
            declared attribute properties into session-based allocated memory space.
    --- */

    for (idx = 0; idx < (ViInt32) numberOfAttr; idx++)
        {
        memcpy (&sessionProperties -> attr[idx], attrList[idx], sizeof (RsAttrProperties));

        switch (sessionProperties -> attr[idx].dataType)
            {
            case RS_VAL_INT32:
                data_size = RS_VAL_INT32_SIZE;
                break;
            case RS_VAL_INT64:
                data_size = RS_VAL_INT64_SIZE;
                break;
            case RS_VAL_REAL64:
                data_size = RS_VAL_REAL64_SIZE;
                break;
            case RS_VAL_STRING:
                data_size = RS_VAL_STRING_SIZE;
                break;
            case RS_VAL_ADDR:
                data_size = RS_VAL_ADDR_SIZE;
                break;
            case RS_VAL_SESSION:
                data_size = RS_VAL_SESSION_SIZE;
                break;
            case RS_VAL_BOOLEAN:
                data_size = RS_VAL_BOOLEAN_SIZE;
                break;
            case RS_VAL_UNKNOWN_TYPE:
            default:
                data_size = RS_VAL_UNKNOWN_TYPE_SIZE;
            }

        p2value = malloc (data_size);
        
        if (p2value == VI_NULL)
            return RS_ERROR_OUT_OF_MEMORY;

        memset (p2value, 0, data_size);

        sessionProperties -> attr[idx].p2value = p2value;
        }

    /* --- Pass value to RS_ATTR_SPECIFIC_DRIVER_PREFIX --- */

    checkErr (Rs_GetAttributeIndex (io, RS_ATTR_SPECIFIC_DRIVER_PREFIX, &idx));
    switch (sessionProperties -> attr[idx].dataType)
        {
        case RS_VAL_INT32:
            data_size = RS_VAL_INT32_SIZE;
            break;
        case RS_VAL_INT64:
            data_size = RS_VAL_INT64_SIZE;
            break;
        case RS_VAL_REAL64:
            data_size = RS_VAL_REAL64_SIZE;
            break;
        case RS_VAL_STRING:
            data_size = RS_VAL_STRING_SIZE - 1;
            break;
        case RS_VAL_ADDR:
            data_size = RS_VAL_ADDR_SIZE;
            break;
        case RS_VAL_SESSION:
            data_size = RS_VAL_SESSION_SIZE;
            break;
        case RS_VAL_BOOLEAN:
            data_size = RS_VAL_BOOLEAN_SIZE;
            break;
        case RS_VAL_UNKNOWN_TYPE:
        default:
            data_size = RS_VAL_UNKNOWN_TYPE_SIZE;
        }

    strncpy ((ViString)sessionProperties -> attr[idx].p2value, specificPrefix, data_size - 1);

    /* --- Parse option string and optionally sets the initial state of the following session attributes --- */

    /* Tokenize option string and search for known options */

    if (optionsString)
        if (strlen (optionsString) > 0)
            {
            if ((driver_setup = (ViChar*) malloc (strlen (optionsString)+1)) == VI_NULL)
                return RS_ERROR_OUT_OF_MEMORY;

            memset (driver_setup, 0, strlen (optionsString)+1);

            p2buf = (ViChar *)optionsString;
            p2buf = strtok (p2buf, ",");

            while (p2buf)
            {
                /* RangeCheck */
                if (strncmp (p2buf, "RangeCheck", 10) == 0)
                {
                    p2temp = strstr (p2buf, "=");
            
                    if (p2temp)
                        {
                        checkErr (Rs_GetAttributeIndex (io, RS_ATTR_RANGE_CHECK, &idx));
                
                        if ((strstr (p2temp, "1")       != NULL) || 
                            (strstr (p2temp, "True")    != NULL) ||
                            (strstr (p2temp, "VI_TRUE") != NULL))
                            {
                            boolean = VI_TRUE;
                            *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                            }
                        else
                            if ((strstr (p2temp, "0")        != NULL) || 
                                (strstr (p2temp, "False")    != NULL) || 
                                (strstr (p2temp, "VI_FALSE") != NULL))
                                {
                                boolean = VI_FALSE;
                                *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                                }
                        }
            
                    p2buf = strtok (NULL, ",");
                    continue;
                }
        
                /* QueryInstrStatus */
                if (strncmp (p2buf, "QueryInstrStatus", 16) == 0)
                {
                    p2temp = strstr (p2buf, "=");
            
                    if (p2temp)
                        {
                        checkErr (Rs_GetAttributeIndex (io, RS_ATTR_QUERY_INSTR_STATUS, &idx));
                
                        if ((strstr (p2temp, "1")       != NULL) || 
                            (strstr (p2temp, "True")    != NULL) || 
                            (strstr (p2temp, "VI_TRUE") != NULL))
                            {
                            boolean = VI_TRUE;
                            *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                            }
                        else
                            if ((strstr (p2temp, "0")        != NULL) ||
                                (strstr (p2temp, "False")    != NULL) || 
                                (strstr (p2temp, "VI_FALSE") != NULL))
                                {
                                boolean = VI_FALSE;
                                *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                                }
                        }
            
                    p2buf = strtok (NULL, ",");
                    continue;
                }
        
                /* Cache */
                if (strncmp (p2buf, "Cache", 5) == 0)
                {
                    p2temp = strstr (p2buf, "=");
            
                    if (p2temp)
                        {
                        checkErr (Rs_GetAttributeIndex (io, RS_ATTR_CACHE, &idx));
                
                        if ((strstr (p2temp, "1")       != NULL) ||
                            (strstr (p2temp, "True")    != NULL) ||
                            (strstr (p2temp, "VI_TRUE") != NULL))
                            {
                            boolean = VI_TRUE;
                            *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                            }
                        else
                            if ((strstr (p2temp, "0")        != NULL) || 
                                (strstr (p2temp, "False")    != NULL) ||
                                (strstr (p2temp, "VI_FALSE") != NULL))
                                {
                                boolean = VI_FALSE;
                                *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                                }
                        }
            
                    p2buf = strtok (NULL, ",");
                    continue;
                }
        
                /* Simulate */
                if (strncmp (p2buf, "Simulate", 8) == 0)
                {
                    p2temp = strstr (p2buf, "=");
            
                    if (p2temp)
                        {
                        checkErr (Rs_GetAttributeIndex (io, RS_ATTR_SIMULATE, &idx));
                
                        if ((strstr (p2temp, "1")       != NULL) || 
                            (strstr (p2temp, "True")    != NULL) ||
                            (strstr (p2temp, "VI_TRUE") != NULL))
                            {
                            boolean = VI_TRUE;
                            *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                            }
                        else
                            if ((strstr (p2temp, "0")        != NULL) || 
                                (strstr (p2temp, "False")    != NULL) || 
                                (strstr (p2temp, "VI_FALSE") != NULL))
                                {
                                boolean = VI_FALSE;
                                *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                                }
                        }
            
                    p2buf = strtok (NULL, ",");
                    continue;
                }
        
                /* RecordCoercions */
                if (strncmp (p2buf, "RecordCoercions", 15) == 0)
                {
                    p2temp = strstr (p2buf, "=");
            
                    if (p2temp)
                        {
                        checkErr (Rs_GetAttributeIndex (io, RS_ATTR_RECORD_COERCIONS, &idx));
                
                        if ((strstr (p2temp, "1")       != NULL) ||
                            (strstr (p2temp, "True")    != NULL) ||
                            (strstr (p2temp, "VI_TRUE") != NULL))
                            {
                            boolean = VI_TRUE;
                            *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                            }
                        else
                            if ((strstr (p2temp, "0")        != NULL) ||
                                (strstr (p2temp, "False")    != NULL) ||
                                (strstr (p2temp, "VI_FALSE") != NULL))
                                {
                                boolean = VI_FALSE;
                                *(ViBoolean *)sessionProperties -> attr[idx].p2value = boolean;
                                }
                        }
            
                    p2buf = strtok (NULL, ",");
                    continue;
                }

                /* Store unresolved option string for RS_ATTR_DRIVER_SETUP */

                strcat (driver_setup, p2buf);\
                strcat (driver_setup, ",");

                p2buf = strtok (NULL, ",");
            }

            length = strlen(driver_setup);
            if (length > 0)
                driver_setup[length - 1] = '\0';

            checkErr (Rs_GetAttributeIndex (io, RS_ATTR_DRIVER_SETUP, &idx));
            strncpy ((ViString)sessionProperties -> attr[idx].p2value, driver_setup, RS_MAX_MESSAGE_BUF_SIZE - 1);
            }

Error:

    if (driver_setup)
        free (driver_setup);

    return error;
}

/*****************************************************************************
 * Function: Rs_Dispose
 * Purpose:  This function destroys the RS session, all of its attributes,
 *           and the memory resources it uses.
 *           This function does NOT close the instrument I/O session. You
 *           must do that yourself before calling this function.
 *           You must unlock the session before calling Rs_Dispose.
 *
 *****************************************************************************/
ViStatus Rs_Dispose (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error   = VI_SUCCESS;
    ViUInt32    idx     = 0;
    void        *p2value;

    if (sessionProperties != NULL)
    {
        (void) Rs_DisposeRepCapTable (sessionProperties);

    for (idx = 0; idx < sessionProperties -> numberOfAttr; idx++)
            {
            p2value = sessionProperties -> attr[idx].p2value;
        
            if (p2value != NULL)
                free (p2value);
      }
    
        /* Deallocate memory for attribute properties list */

        if (sessionProperties -> attr != NULL)
            free (sessionProperties -> attr);

        /* Deallocate session properties structure */

        if (sessionProperties != NULL)
            free (sessionProperties);
    }
    idx = 0;
    while ((idx < MAX_NUMBER_OF_SESSIONS) && (io != gresources[idx].session)) idx++;

    if ((idx<MAX_NUMBER_OF_SESSIONS)&&(gresources[idx].session != VI_NULL))
    {
        gresources[idx].session = 0;
        gresources[idx].properties = 0;
    }
    if (gresCount > 0)
        gresCount--;
    
    return error;
}

/*****************************************************************************
 *- Set/Check/Get Attribute -------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_SetAttribute
 * Purpose:  This function sets the ViInt32, ViReal64, ViBoolean and ViString
 *           attribute you specify to a new value. Depending on the
 *           configuration of the attribute, the function performs the
 *           following actions:
 *
 *           Checks whether the attribute is writable. If not, the function
 *           returns an error.
 *           Validates the value you specify if RS_ATTR_RANGE_CHECK is
 *           enabled for the session. If you provide a check callback, the
 *           function invokes the callback to validate the value. If you do
 *           not provide a check callback but you provide a range table or a
 *           range table callback, the function invokes the default RS check
 *           callback to validate the value. If the value is invalid, the
 *           function returns an error.
 *           Coerces the value you specify into a canonical value the
 *           instrument accepts. If you provide a coerce callback, the
 *           function invokes the callback to coerce the value. If you do not
 *           provide a coerce callback but you provide a coerced range table
 *           directly or through a range table callback, the function invokes
 *           the default RS coerce callback to coerce the value.
 *           Compares the new value with the current cache value for the
 *           attribute to see if they are equal. When the cache value is a
 *           value the RS Library obtained by querying the instrument and
 *           you provide a compare callback for the attribute, the function
 *           invokes the compare callback. Otherwise, the function makes the
 *           comparison based on strict equality.
 *           If the new value is not equal to the cache value or the cache
 *           value is invalid, the function invokes the write callback for
 *           the attribute. The write callback might perform I/O to send the
 *           value to the instrument. The RS Library stores the new value in
 *           the cache. If the function coerces the value, the function
 *           caches the coerced value rather than the value you pass.
 *           If the RS_VAL_WAIT_FOR_OPC_AFTER_WRITES flag is set for the
 *           attribute, the function invokes the operation complete (OPC)
 *           callback you provide for the session.
 *           If you set the RS_VAL_DIRECT_USER_CALL bit in the Option Flags
 *           parameter, the RS_ATTR_QUERY_INSTR_STATUS attribute is enabled,
 *           and the RS_VAL_DONT_CHECK_STATUS flag for the attribute is 0,
 *           then the function invokes the check status callback you provide
 *           for the session.
 *
 *           Note:  If you set the RS_VAL_SET_CACHE_ONLY bit in the Option
 *           Flags parameter, or if the RS_ATTR_SIMULATE attribute is
 *           enabled and the RS_VAL_USE_CALLBACKS_FOR_SIMULATION flag for
 *           the attribute is 0, the function does not call the write
 *           callback, the operation complete callback, or the check status
 *           callback. It merely updates the cache value of the attribute.
 *
 *****************************************************************************/
ViStatus Rs_SetAttribute (ViSession instrSession,
                          ViConstString repCapName,
                          ViAttr attributeId,
                          ViInt32 optionFlags,
                          void *value)
{
    RsSessionPropertiesPtr sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error                   = VI_SUCCESS;
    ViInt32     idx                     = 0;
    ViBoolean   simulation              = Rs_Simulating (instrSession),
                queryInstrumentStatus   = Rs_QueryInstrStatus (instrSession),
                rangeChecking           = Rs_RangeChecking (instrSession);
    void        *coercedValue           = VI_NULL,
                *p2value                = value;
    ViString    magic_code              = "DEADBEEF";

    /* Get the attribute index */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* --- Attribute access --- */
    switch (sessionProperties -> attr[idx].access)
        {
        case RS_VAL_WRITE_ONLY:
        case RS_VAL_READ_WRITE:
            /*
                Valid condition
            */
            break;
        case RS_VAL_READ_ONLY:
            viCheckErr (RS_ERROR_RS_ATTR_NOT_WRITABLE);
            break;
        default:
            viCheckErr (RS_ERROR_FUNCTION_NOT_SUPPORTED);
        }

    /* --- End user access --- */
    if (((optionFlags & RS_VAL_DIRECT_USER_CALL) != 0) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_NOT_USER_WRITABLE) != 0))
        {
        viCheckErr (RS_ERROR_ATTRIBUTE_NOT_SUPPORTED);
        }

    /* --- User callback --- */

    if (sessionProperties -> attr[idx].userCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].userCallback)(instrSession, repCapName, attributeId, VI_NULL, value));

        goto Update_Cache;
        }

    /* --- Instrument & option checking --- */
    if ((queryInstrumentStatus == VI_TRUE) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_DONT_CHECK_STATUS) == 0))
        {
        viCheckErr (Rs_CheckModelOpt (instrSession, attributeId));
        }

    /* --- Data type (range checking, coercing, ...) --- */

    switch (sessionProperties -> attr[idx].dataType)
        {
        case RS_VAL_INT32:
        case RS_VAL_REAL64:

            if (rangeChecking == VI_TRUE)
                {
                viCheckErr (Rs_CheckCallback (instrSession, repCapName, attributeId, value));
                }
            break;
        default:

            /* Other data types are not range checked. */

            break;
        }

    /* --- Update cache only --- */
    if ((optionFlags & RS_VAL_SET_CACHE_ONLY) == VI_TRUE)
        goto Update_Cache;

    /* --- Simulation --- */
    if ((simulation == VI_FALSE) ||
        ((simulation == VI_TRUE) && 
        ((sessionProperties -> attr[idx].flags & RS_VAL_USE_CALLBACKS_FOR_SIMULATION) != 0)))
        {
        /* --- Write callback --- */
        if (sessionProperties -> attr[idx].writeCallback)
            {
            viCheckErr ((sessionProperties -> attr[idx].writeCallback)(instrSession, repCapName, attributeId, value));
            }
        else
            {
            viCheckErr (Rs_WriteCallback (instrSession, repCapName, attributeId, value));
            }
        }
    else
        goto Update_Cache;

    if (simulation == VI_FALSE)
        {
        /* --- OPC --- */
        if ((sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES) != 0)
            {
            ViInt32             opc_callback_idx    = 0;
            ViAddr              value_address       = 0;
            Rs_OPCCallbackPtr   p2function;

            viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPC_CALLBACK, &opc_callback_idx));
            value_address = *(ViAddr *)sessionProperties -> attr[opc_callback_idx].p2value;
            p2function = (Rs_OPCCallbackPtr)value_address;
            viCheckErr (p2function(instrSession));
            }
    
        /* --- Check status --- */
        if ((queryInstrumentStatus == VI_TRUE) &&
            ((sessionProperties -> attr[idx].flags & RS_VAL_DONT_CHECK_STATUS) == 0) &&
            ((optionFlags & RS_VAL_DIRECT_USER_CALL) != 0))
            {
            ViInt32                     status_callback_idx = 0;
            ViAddr                      value_address       = 0;
            Rs_CheckStatusCallbackPtr   p2function;

                if (sessionProperties -> attr[idx].checkStatusCallback){
                    // user defined check status callback
                    viCheckErr ((sessionProperties -> attr[idx].checkStatusCallback)(instrSession));
                } else {
                    // default defined check status call back function
                    viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_CHECK_STATUS_CALLBACK, &status_callback_idx));
                    value_address = *(ViAddr *)sessionProperties -> attr[status_callback_idx].p2value;
                    p2function = (Rs_CheckStatusCallbackPtr)value_address;
                    viCheckErr (p2function(instrSession));
                }
            }
        }

Update_Cache: /* Update value in the cache */

    /* Redirect value to temporary pointer */
    p2value = value;

    /* Is the value coerced? */
    if (coercedValue != NULL)
        if (strncmp ((ViChar*) coercedValue, magic_code, strlen (magic_code)) != 0)
        {
            p2value = coercedValue;
        }
    
    switch (sessionProperties -> attr[idx].dataType)
        {
        case RS_VAL_INT32:
            *(ViInt32 *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViInt32 *)p2value : 0;
            break;
        case RS_VAL_INT64:
            *(ViInt64 *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViInt64 *)p2value : 0;
            break;
        case RS_VAL_REAL64:
            *(ViReal64 *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViReal64 *)p2value : 0;
            break;
        case RS_VAL_STRING:
            strncpy ((ViString)sessionProperties -> attr[idx].p2value, (ViString)p2value, RS_MAX_MESSAGE_BUF_SIZE - 1);
            break;
        case RS_VAL_ADDR:
            *(ViAddr *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViAddr *)p2value : 0;
            break;
        case RS_VAL_SESSION:
            *(ViSession *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViSession *)p2value : 0;
            break;
        case RS_VAL_BOOLEAN:
            *(ViBoolean *)sessionProperties -> attr[idx].p2value = (p2value) ? *(ViBoolean *)p2value : 0;
            break;
        case RS_VAL_EVENT:
            break;
        case RS_VAL_UNKNOWN_TYPE:
        default:
            viCheckErr (RS_ERROR_INVALID_TYPE);
        }

Error:

    if (coercedValue)
        free (coercedValue);

    return error;
}

/*****************************************************************************
 * Function: Rs_CheckAttribute
 * Purpose:  This function checks the validity of a value you specify for a
 *           ViInt32, ViReal64, ViBoolean and ViString attribute. The function
 *           performs the following actions:
 *
 *           Checks whether the attribute is writable. If not, the function
 *           returns an error.
 *           Validates the value you specify. If you provide a check
 *           callback, the function invokes the callback to validate the
 *           value. If you do not provide a check callback but you provide a
 *           range table or a range table callback (only for ViInt32 and
 *           ViReal64), the function invokes the default RS check callback
 *           to validate the value. If the value is invalid, the function
 *           returns an error. If the attribute has no range table or check
 *           callback, the function assumes the value is valid.
 *****************************************************************************/
ViStatus Rs_CheckAttribute (ViSession instrSession,
                            ViConstString repCapName,
                            ViAttr attributeId,
                            ViInt32 optionFlags,
                            void *value)
{
    RsSessionPropertiesPtr sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error                   = VI_SUCCESS;
    ViInt32     idx                     = 0;
    ViBoolean   queryInstrumentStatus   = Rs_QueryInstrStatus (instrSession);


    /* Get the attribute index */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* --- Attribute access --- */
    switch (sessionProperties -> attr[idx].access)
        {
        case RS_VAL_WRITE_ONLY:
        case RS_VAL_READ_WRITE:
            /*
                Valid condition
            */
            break;
        case RS_VAL_READ_ONLY:
            viCheckErr (RS_ERROR_RS_ATTR_NOT_WRITABLE);
            break;
        default:
            viCheckErr (RS_ERROR_FUNCTION_NOT_SUPPORTED);
        }

    /* --- End user access --- */
    if (((optionFlags & RS_VAL_DIRECT_USER_CALL) != 0) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_NOT_USER_WRITABLE) != 0) )
        {
        viCheckErr (RS_ERROR_ATTRIBUTE_NOT_SUPPORTED);
        }

    /* --- User callback --- */

    if (sessionProperties -> attr[idx].userCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].userCallback)(instrSession, repCapName, attributeId, VI_NULL, value));

        goto Error;
        }

    /* --- Instrument & option checking --- */
    if ((queryInstrumentStatus == VI_TRUE) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_DONT_CHECK_STATUS) == 0))
        {
        viCheckErr (Rs_CheckModelOpt (instrSession, attributeId));
        }

    /* --- Call check callback --- */

    if (sessionProperties -> attr[idx].checkCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].checkCallback)(instrSession, repCapName, attributeId, value));
        }
    else
        {
        viCheckErr (Rs_CheckCallback (instrSession, repCapName, attributeId, value));
        }

Error:
    return error;
}

/*****************************************************************************
 * Function: Rs_GetAttribute
 * Purpose:  This function obtains the current value of the ViInt32,
 *           ViReal64, ViBoolean and ViString attribute you specify.
 *
 *           If the attribute you specify is type of ViString, you must
 *           provide a ViChar array to serve as a buffer for the
 *           value. You pass the number of bytes in the buffer as the Buffer
 *           Size parameter. If the current value of the attribute, including
 *           the terminating NUL byte, is larger than the size you indicate
 *           in the Buffer Size parameter, the function copies Buffer Size -
 *           1 bytes into the buffer, places an ASCII NUL byte at the end of
 *           the buffer, and returns the buffer size you must pass to get the
 *           entire value. For example, if the value is "123456" and the
 *           Buffer Size is 4, the function places "123" into the buffer and
 *           returns 7.
 *           If you want the function to fill in the buffer regardless of the
 *           number of bytes in the value, pass a negative number for the
 *           Buffer Size parameter. If you want to call this function just to
 *           get the required buffer size, you can pass 0 for the Buffer Size
 *           and VI_NULL for the Attribute Value buffer.
 *           Remember that the checkErr and viCheckErr macros ignore positive
 *           return values. If you use one of these macros around a call to
 *           this function, you lose the required buffer size when the
 *           function returns it. To retain this information, declare a
 *           separate local variable to store the required buffer size, and
 *           use the macro around the assignment of the return value to the
 *           local variable.
 *
 *           The following is an example:
 *
 *           ViStatus error = VI_SUCCESS;
 *           ViInt32 requiredBufferSize;
 *
 *           checkErr( requiredBufferSize = Rs_GetAttribute (vi, channel, attr, 0, 0, VI_NULL));
 *
 *           Depending on the configuration of the attribute, the function
 *           performs the following actions:
 *
 *           Checks whether the attribute is readable. If not, the function
 *           returns an error.
 *           If the attribute cache value is currently valid, the read
 *           callback for the attribute is VI_NULL, or the RS_ATTR_SIMULATE
 *           attribute is enabled and the
 *           RS_ATTR_USE_CALLBACKS_FOR_SIMULATION flag for the attribute is
 *           0, the function returns the cache value.
 *           If the RS_VAL_WAIT_FOR_OPC_BEFORE_READS flag is set for the
 *           attribute, the function invokes the operation complete (OPC)
 *           callback you provide for the session.
 *           The function invokes the read callback for the attribute.
 *           Typically, the callback performs instrument I/O to obtain a new
 *           value. The RS Library stores the new value in the cache.
 *           If you set the RS_VAL_DIRECT_USER_CALL bit in the Option Flags
 *           parameter, the RS_ATTR_QUERY_INSTR_STATUS attribute is enabled,
 *           and the RS_VAL_DONT_CHECK_STATUS flag for the attribute is 0,
 *           then the function invokes the check status callback you provide
 *           for the session.
 *
 *****************************************************************************/
ViStatus Rs_GetAttribute (ViSession instrSession,
                          ViConstString repCapName,
                          ViAttr attributeId,
                          ViInt32 optionFlags,
                          unsigned int bufSize,
                          void *value)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error                   = VI_SUCCESS;
    ViInt32     idx                     = 0;
    void        *p2value;
    ViBoolean   simulation              = Rs_Simulating (instrSession),
                queryInstrumentStatus   = Rs_QueryInstrStatus (instrSession);
    size_t      size=0;            

    /* Get the attribute index */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* --- Work with the ptr to a value in the cache --- */
    p2value = sessionProperties -> attr[idx].p2value;

    /* --- Attribute access --- */
    switch (sessionProperties -> attr[idx].access)
        {
        case RS_VAL_READ_ONLY:
        case RS_VAL_READ_WRITE:
            /*
                Valid condition
            */
            break;
        case RS_VAL_WRITE_ONLY:
            viCheckErr (RS_ERROR_RS_ATTR_NOT_READABLE);
            break;
        default:
            viCheckErr (RS_ERROR_FUNCTION_NOT_SUPPORTED);
        }

    /* --- End user access --- */
    if (((optionFlags & RS_VAL_DIRECT_USER_CALL) != 0) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_NOT_USER_READABLE) !=0 ))
        {
        viCheckErr (RS_ERROR_ATTRIBUTE_NOT_SUPPORTED);
        }

    /* --- User callback --- */

    if (sessionProperties -> attr[idx].userCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].userCallback)(instrSession, repCapName, attributeId, (ViInt32) bufSize, p2value));

        goto Update_Cache;
        }

    /* --- Instrument & option checking --- */
    if ((queryInstrumentStatus == VI_TRUE) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_DONT_CHECK_STATUS) == 0))
        {
        viCheckErr (Rs_CheckModelOpt (instrSession, attributeId));
        }

    /* --- OPC --- */

    if ((simulation == VI_FALSE) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_BEFORE_READS) != 0))
        {
            ViInt32             opc_callback_idx    = 0;
            ViAddr              p2v                 = 0;
            Rs_OPCCallbackPtr   p2function;

            viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPC_CALLBACK, &opc_callback_idx));
            p2v = *(ViAddr *)sessionProperties -> attr[opc_callback_idx].p2value;
            p2function = (Rs_OPCCallbackPtr)p2v;
            viCheckErr (p2function(instrSession));
        }

    /* --- Simulation --- */

    if ((simulation == VI_FALSE) ||
        ((simulation == VI_TRUE) &&
        ((sessionProperties -> attr[idx].flags & RS_VAL_USE_CALLBACKS_FOR_SIMULATION) != 0)))
        {
        /* --- Read callback --- */
        if (sessionProperties -> attr[idx].readCallback)
            {
            viCheckErr ((sessionProperties -> attr[idx].readCallback)(instrSession, repCapName, attributeId, (ViInt32) bufSize, p2value));
            }
        else
            {
            viCheckErr (Rs_ReadCallback (instrSession, repCapName, attributeId, (ViInt32) bufSize, p2value));
            }
        }
    else
        goto Update_Cache;

    /* --- Simulation --- */
    if (simulation == VI_FALSE)
        {
            /* --- Check status --- */
            if ((queryInstrumentStatus == VI_TRUE) &&
                ((sessionProperties -> attr[idx].flags & RS_VAL_DONT_CHECK_STATUS) == 0) &&
                ((optionFlags & RS_VAL_DIRECT_USER_CALL) != 0))
                {
                ViInt32                     status_callback_idx = 0;
                ViAddr                      value_address       = 0;
                Rs_CheckStatusCallbackPtr   p2function;

                    if (sessionProperties -> attr[idx].checkStatusCallback){
                        // user defined check status callback
                        viCheckErr ((sessionProperties -> attr[idx].checkStatusCallback)(instrSession));
                    } else {
                        // default defined check status call back function
                        viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_CHECK_STATUS_CALLBACK, &status_callback_idx));
                        value_address = *(ViAddr *)sessionProperties -> attr[status_callback_idx].p2value;
                        p2function = (Rs_CheckStatusCallbackPtr)value_address;
                        viCheckErr (p2function(instrSession));
                    }
                }
        }

Update_Cache: /* Get value from the cache */

    switch (sessionProperties -> attr[idx].dataType)
        {
        case RS_VAL_INT32:
            if (value)
                *(ViInt32 *)value = *(ViInt32 *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_INT64:
            if (value)
                *(ViInt64 *)value = *(ViInt64 *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_REAL64:
            if (value)
                *(ViReal64 *)value = *(ViReal64 *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_STRING:
            if (value){
                size=(bufSize > (ViUInt32) strlen((ViString)sessionProperties -> attr[idx].p2value)) ? strlen((ViString)sessionProperties -> attr[idx].p2value) : (size_t) bufSize-1;
                strncpy ((ViString)value, (ViString)sessionProperties -> attr[idx].p2value, size);
                ((ViChar *)value)[size]='\0';
            }    
            break;
        case RS_VAL_ADDR:
            if (value)
                *(ViAddr *)value = *(ViAddr *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_SESSION:
            if (value)
                *(ViSession *)value = *(ViSession *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_BOOLEAN:
            if (value)
                *(ViBoolean *)value = *(ViBoolean *)sessionProperties -> attr[idx].p2value;
            break;
        case RS_VAL_UNKNOWN_TYPE:
        default:
            viCheckErr (RS_ERROR_INVALID_TYPE);
        }

Error:
    return error;
}

/*****************************************************************************
 *- Repeated Capability Functions -------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_BuildRepCapTable
 * Purpose:  This function creates a repeated capability table for an RS
 *           session. A repeated capability table consists of a name that
 *           identifies the repeated capability, the identifier strings and
 *           command values that are valid for the instrument session.
 *
 *           Calling  this function more than once for the same repeated
 *           capability will return the RS_ERROR_REPEATED_CAPABILITY_ALREADY_EXISTS
 *           error.
 *
 *           The RS Library maintains the repeated capability table for the
 *           session.
 *
 *****************************************************************************/
ViStatus Rs_BuildRepCapTable (ViSession instrSession, RsRepCapPtr repCapTable)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViUInt32    numberOfRepCaps = 0;
    size_t      table_size      = 0;
    ViInt32     idx             = 0;
    ViUInt32    i               = 0;

    if (sessionProperties -> repCapTable)
        viCheckErr (RS_ERROR_REPEATED_CAPABILITY_ALREADY_EXISTS);

    /* Determine number of repeated capabilities */
    for (numberOfRepCaps = 0; repCapTable[numberOfRepCaps].repCapNameId; numberOfRepCaps++);

    checkErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_CHANNEL_COUNT, &idx));

    sessionProperties -> numberOfRepCaps = numberOfRepCaps;
    *(ViUInt32 *)sessionProperties -> attr[idx].p2value = numberOfRepCaps;

    /* Allocate memory for session based repeated capabilities */
    table_size = (size_t) (numberOfRepCaps * sizeof (repCapTable[0]));
    checkAlloc (sessionProperties -> repCapTable = (RsRepCapPtr) malloc (table_size));
    for (i = 0; i < numberOfRepCaps; i++)
    {
        checkAlloc (sessionProperties -> repCapTable[i].repCapNameId = (ViChar*) malloc (strlen(repCapTable[i].repCapNameId) + 1));
        strcpy (sessionProperties -> repCapTable[i].repCapNameId, repCapTable[i].repCapNameId);
        
        checkAlloc (sessionProperties -> repCapTable[i].repCapName = (ViChar*) malloc (strlen(repCapTable[i].repCapName) + 1));
        strcpy (sessionProperties -> repCapTable[i].repCapName, repCapTable[i].repCapName);
        
        checkAlloc (sessionProperties -> repCapTable[i].cmdValues = (ViChar*) malloc (strlen(repCapTable[i].cmdValues) + 1));
        strcpy (sessionProperties -> repCapTable[i].cmdValues, repCapTable[i].cmdValues);
    }   

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_ResetRepCapTable
 * Purpose:  This function removes all existing repeated capabilities and
 *           creates the table again with default values
 *
 *****************************************************************************/
ViStatus Rs_ResetRepCapTable (ViSession instrSession, RsRepCapPtr repCapTable)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;

    checkErr (Rs_DisposeRepCapTable (sessionProperties));
    checkErr (Rs_BuildRepCapTable (instrSession, repCapTable));

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_ValidateAttrForRepCapNameId
 * Purpose:  This function checks whether you can use an attribute on a
 *           particular repeated capability instance. If either the
 *           AttributeId or Repeated Capability Name Id parameter is invalid for
 *           the session, this function returns an error. Otherwise, it
 *           checks for the following cases in which the combination of the
 *           AttributeId and Repeated Capability Name Id is invalid:
 *
 *           The repeated capability name is VI_NULL or the empty string and
 *           the attribute applies to a repeated capability. In this case,
 *           the function returns the
 *           RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED error code.
 *
 *           The repeated capability name identifier refers to a specific repeated
 *           capability and the attribute does not apply to a repeated
 *           capability. In this case, the function returns the
 *           RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED error code.
 *
 *****************************************************************************/
ViStatus Rs_ValidateAttrForRepCapNameId (RsSessionPropertiesPtr  sessionProperties,
                                         ViConstString repCapNameId,
                                         ViAttr attributeId)
{
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    ViUInt32    rcap            = 0;
    ViSession   instrSession    = sessionProperties->io; /* used due to checking macro */
    ViChar      rCaps[RS_MAX_MESSAGE_BUF_SIZE] = "";
    
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* Check if the attribute is enabled to use repeated capabilities */
    if (sessionProperties -> attr[idx].usercaps == VI_FALSE)
        viCheckErr (RS_ERROR_ATTR_MUST_BE_REPEATED_CAPABILITY_BASED);

    /* Repeated capability name must be valid string */
    if (!repCapNameId)
    {
        viCheckErr (RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED);
    }
    else
        if (strlen (repCapNameId) == 0)
            viCheckErr (RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED);

    /* Check if the repeated capability name is valid for session */
    for (rcap = 0; rcap < sessionProperties -> numberOfRepCaps; rcap++)
        if (strcmp (sessionProperties -> repCapTable[rcap].repCapNameId, repCapNameId) == 0)
            break;

    if (rcap >= sessionProperties -> numberOfRepCaps)
        viCheckErr (RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME);

    /* Check if the attribute has defined repeated capability names and
       if the define repeated capability name id is for that attribute valid */

    viCheckErr (Rs_GetAttributeRepCapNameId (instrSession, attributeId, rCaps)); 
    if (strlen (rCaps) == 0)
            viCheckErr (RS_ERROR_EMPTY_REPEATED_CAPABILITY_LIST);

    if (!strstr (rCaps, repCapNameId))
        viCheckErr (RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED);

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_GetAttributeRepCapNameId
 * Purpose:  This function returns the repeated capability id(s) that
 *           belongs to the attribute you specify. More then one id is listed
 *           in comma separated string.
 *****************************************************************************/
ViStatus Rs_GetAttributeRepCapNameId (ViSession instrSession,
                                    ViAttr attributeId,
                                    ViChar repCapNameId[])
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    ViChar      *p2cmd,
                tmp[RS_MAX_MESSAGE_BUF_SIZE] = "";
    
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));
    p2cmd =  sessionProperties -> attr[idx].command;
    /* Check if the attribute is enabled to use repeated capabilities */
    if (sessionProperties -> attr[idx].usercaps == VI_FALSE)
        viCheckErr (RS_ERROR_ATTR_MUST_BE_REPEATED_CAPABILITY_BASED);

    /* Is output string valid? */
    if (repCapNameId == NULL)
        viCheckErr (RS_ERROR_NULL_POINTER);

    strcpy (repCapNameId,"");
    p2cmd = strchr(p2cmd,'{');
    while (p2cmd != NULL)
    {
        (void) sscanf (p2cmd, "{%[^}]}", tmp);
        p2cmd++;
        p2cmd = strchr(p2cmd,'{');
        strcat (repCapNameId, tmp);
        strcat (repCapNameId, ",");
    }
    p2cmd = strrchr(repCapNameId,',');
    p2cmd[0] = '\0';

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_RepCapCount
 * Purpose:  This function returns the number of values in repeated capability.
 *****************************************************************************/
ViStatus Rs_RepCapCount (ViSession instrSession,
                       ViString repCapNameId,
                       ViInt32* count)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViUInt32    i = 0, j = 0;
    ViBoolean   found = VI_FALSE;
    ViChar      *p2buffer = NULL;
    ViChar      buffer[RS_MAX_MESSAGE_LEN] = "";
    
    if ((repCapNameId == NULL) || (count == NULL))
        viCheckErr (RS_ERROR_NULL_POINTER);
    
    /* Find repeated capability */
    for (i = 0; i < sessionProperties->numberOfRepCaps; i++)
    {
        found = (ViBoolean) (strcmp (sessionProperties->repCapTable[i].repCapNameId, repCapNameId) == 0);
        if (found)
            break;
    }
    
    if (!found)
        return RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME;
    
    strcpy (buffer, sessionProperties->repCapTable[i].repCapName);
    
    p2buffer = strtok (buffer, ",");
    
    while (p2buffer)
    {
        j++;
        p2buffer = strtok (NULL, ",");
    }
    
    if (count) *count = j;
    
Error:    
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_AddRepCap
 * Purpose:  This function adds new dynamic repeated capability.
 *****************************************************************************/
ViStatus Rs_AddRepCap (ViSession instrSession,
                       ViString repCapNameId,
                       ViString repCapName,
                       ViString cmdValue)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViUInt32    i = 0;
    ViBoolean   found = VI_FALSE;
    ViBoolean   rep_cap_exists = VI_FALSE;
    ViChar      *p2buf = NULL;
    ViChar      *p2buffer = NULL;
    ViChar      buffer[RS_MAX_MESSAGE_LEN] = "";
    size_t      new_size, orig_size;

    if ((repCapName == NULL) || (repCapNameId == NULL) || (cmdValue == NULL))
        viCheckErr (RS_ERROR_NULL_POINTER);
    
    /* Find repeated capability */
    for (i = 0; i < sessionProperties->numberOfRepCaps; i++)
    {
        found = (strcmp (sessionProperties->repCapTable[i].repCapNameId, repCapNameId) == 0);
        if (found)
            break;
    }
    
    if (!found)
        return RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME;
    
    strcpy (buffer, sessionProperties->repCapTable[i].repCapName);
    
    p2buffer = strtok (buffer, ",");
    
    while (p2buffer)
    {
        rep_cap_exists = (strncmp (p2buffer, repCapName, strlen (repCapName)) == 0);
        p2buffer = strtok (NULL, ",");
        if (rep_cap_exists)
            break;
    }
    p2buffer = NULL;
    
    if (!rep_cap_exists)
    {
        /* add 2 characters - terminating nul and separating comma */
        orig_size = strlen (sessionProperties->repCapTable[i].repCapName);
        new_size = strlen (sessionProperties->repCapTable[i].repCapName) + strlen (repCapName) + 2;
        p2buf = (ViChar*)realloc (sessionProperties->repCapTable[i].repCapName, new_size);
    
        if (p2buf == NULL)
            return RS_ERROR_OUT_OF_MEMORY;
        else
            sessionProperties->repCapTable[i].repCapName = p2buf;
    
        if (orig_size != 0)
            strcat (p2buf, ",");
        
        strcat (p2buf, repCapName);
    
        p2buf = NULL;

        /* add 2 characters - terminating nul and separating comma */
        new_size = strlen (sessionProperties->repCapTable[i].cmdValues) + strlen (cmdValue) + 2;
        p2buf = (ViChar*)realloc (sessionProperties->repCapTable[i].cmdValues, new_size);
    
        if (p2buf == NULL)
            return RS_ERROR_OUT_OF_MEMORY;
        else
            sessionProperties->repCapTable[i].cmdValues = p2buf;
    
        if (orig_size != 0)
            strcat (p2buf, ",");
        
        strcat (p2buf, cmdValue);
    }
Error:    
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_RemoveRepCap
 * Purpose:  This function removes new dynamic repeated capability.
 *****************************************************************************/
ViStatus Rs_RemoveRepCap (ViSession instrSession,
                          ViString repCapNameId,
                          ViString repCapName)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViUInt32    i = 0;
    ViBoolean   found = VI_FALSE;
    ViChar      *p2buf = NULL;
    size_t      new_size;
    ViChar      *new_buffer = NULL;
    ViChar      *comma = NULL;
    ViUInt32    index = 0;
    ViChar      cmd_value [RS_MAX_MESSAGE_LEN] = "";

    if ((repCapName == NULL) || (repCapNameId == NULL))
        viCheckErr (RS_ERROR_NULL_POINTER);
    
    /* Find repeated capability */
    for (i = 0; i < sessionProperties->numberOfRepCaps; i++)
    {
        found = (strcmp (sessionProperties->repCapTable[i].repCapNameId, repCapNameId) == 0);
        if (found)
            break;
    }
    
    if (!found)
        return RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME;
    
    p2buf = strstr (sessionProperties->repCapTable[i].repCapName, repCapName);
    if (p2buf == NULL) // cannot remove, ID does not exist
        return RS_ERROR_CANNOT_MODIFY_REPEATED_CAPABILITY_TABLE;

    /* original size minus separating comma plus terminating nul => no extra character needed */
    new_size = strlen (sessionProperties->repCapTable[i].repCapName) - strlen (repCapName);
    
    if (new_size == 0) // only one repeated capability
        new_size = 1; // terminating zero for empty string
    
    checkAlloc (new_buffer = (ViChar *) malloc (new_size));
    memset (new_buffer, 0, new_size);
    
    // find index of repCapNameId token. It will be used for removal of corresponding cmdValue
    checkErr (Rs_GetIndexOfToken (sessionProperties->repCapTable[i].repCapName, ",", &index, repCapName));
    
    if (p2buf == sessionProperties->repCapTable[i].repCapName) // first position
    {
        comma = strchr (sessionProperties->repCapTable[i].repCapName, ',');
        if (comma != NULL) // if the only repcap id in the set, do nothing and copy empty buffer
        {
            comma++; // move pointer behind comma
            new_buffer = strcpy (new_buffer, comma);
        }
    }
    else
    {
        comma = strchr (p2buf, ','); // find next comma
        new_buffer = strncpy (new_buffer, sessionProperties->repCapTable[i].repCapName, p2buf - sessionProperties->repCapTable[i].repCapName - 1);
        if (comma != NULL) // last position
        {
            new_buffer = strcat (new_buffer, comma);
        }
    }
    
    free (sessionProperties->repCapTable[i].repCapName);
    sessionProperties->repCapTable[i].repCapName = new_buffer;
    
    // remove cmdValue

    checkErr (Rs_GetTokenAtIndex (sessionProperties->repCapTable[i].cmdValues, ",", index, cmd_value, RS_MAX_MESSAGE_LEN));
    p2buf = strstr (sessionProperties->repCapTable[i].cmdValues, cmd_value);
    if (p2buf == NULL) // cannot remove, ID does not exist
        return RS_ERROR_CANNOT_MODIFY_REPEATED_CAPABILITY_TABLE;

    /* original size minus separating comma plus terminating nul => no extra character needed */
    new_size = strlen (sessionProperties->repCapTable[i].cmdValues) - strlen (cmd_value);
    if (new_size == 0) // only one repeated capability
        new_size = 1; // terminating zero for empty string
    checkAlloc (new_buffer = (ViChar *) malloc (new_size));
    memset (new_buffer, 0, new_size);
    
    if (p2buf == sessionProperties->repCapTable[i].cmdValues) // first position
    {
        comma = strchr (sessionProperties->repCapTable[i].cmdValues, ',');
        if (comma != NULL) // if the only repcap id in the set, do nothing and copy empty buffer
        {
            comma++; // move pointer behind comma
            new_buffer = strcpy (new_buffer, comma);
        }
    }
    else
    {
        comma = strchr (p2buf, ','); // find next comma
        new_buffer = strncpy (new_buffer, sessionProperties->repCapTable[i].cmdValues, p2buf - sessionProperties->repCapTable[i].cmdValues - 1);
        if (comma != NULL) // last position
        {
            new_buffer = strcat (new_buffer, comma);
        }
    }
    
    free (sessionProperties->repCapTable[i].cmdValues);
    sessionProperties->repCapTable[i].cmdValues = new_buffer;

Error:
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_ResetRepCap
 * Purpose:  This function sets selected repeated capability to default values
 *****************************************************************************/
ViStatus Rs_ResetRepCap (ViSession instrSession,
                          ViString repCapNameId, RsRepCapPtr repCapTable)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus                error             = VI_SUCCESS;
    ViUInt32                i                 = 0;
    ViBoolean               found             = VI_FALSE;

    /* Find repeated capability */
    for (i = 0; i < sessionProperties->numberOfRepCaps; i++)
    {
        found = (strcmp (sessionProperties->repCapTable[i].repCapNameId, repCapNameId) == 0);
        if (found)
            break;
    }
    
    if (!found)
        return RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME;


    free (sessionProperties -> repCapTable[i].repCapName);
    checkAlloc (sessionProperties -> repCapTable[i].repCapName = (ViChar*) malloc (strlen(repCapTable[i].repCapName) + 1));
    strcpy (sessionProperties -> repCapTable[i].repCapName, repCapTable[i].repCapName);
    
    free (sessionProperties -> repCapTable[i].cmdValues);
    checkAlloc (sessionProperties -> repCapTable[i].cmdValues = (ViChar*) malloc (strlen(repCapTable[i].cmdValues) + 1));
    strcpy (sessionProperties -> repCapTable[i].cmdValues, repCapTable[i].cmdValues);

Error:
    return error;
}

/*****************************************************************************
 * Function: Rs_GetAttributeRepCapName
 * Purpose:  This function returns the repeated capability name(s) that
 *           belongs to the attribute and single repeated capability id you
 *           may specify. More then one name is listed in comma separated
 *           string.
 *****************************************************************************/
ViStatus Rs_GetAttributeRepCapName (ViSession instrSession,
                                    ViAttr attributeId,
                                    ViConstString repCapNameId,
                                    ViChar repCapName[])
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0,
                rcap            = 0;

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* Is output string valid? */
    if (repCapName == NULL)
        viCheckErr (RS_ERROR_NULL_POINTER);
    
    /* splint hack */
    if (repCapName != NULL) *repCapName = '\0';

    /* Check validity of data entries */
    viCheckErr (Rs_ValidateAttrForRepCapNameId (sessionProperties, repCapNameId, attributeId));

        /* Find repCapNameId associated names */
        for (rcap = 0; rcap < (ViInt32) sessionProperties -> numberOfRepCaps; rcap++)
            //if (strncmp (sessionProperties -> repCapTable[rcap].repCapNameId, repCapNameId, strlen (repCapNameId)) == 0)
            if (strcmp (sessionProperties -> repCapTable[rcap].repCapNameId, repCapNameId) == 0)
                break;

        if (rcap < (ViInt32) sessionProperties -> numberOfRepCaps)
    {
            strncpy (repCapName, sessionProperties -> repCapTable[rcap].repCapName, RS_MAX_MESSAGE_BUF_SIZE - 1);
      repCapName[RS_MAX_MESSAGE_BUF_SIZE - 1] = '\0';
    }

    /* Check if any of the identifiers is returned */
    if (strlen (repCapName) == 0)
        viCheckErr (RS_ERROR_EMPTY_REPEATED_CAPABILITY_LIST);

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_GetRepCapCmdValue
 * Purpose:  This function obtains the command value of a repeated capability
 *           in the internal repeated capability for an RS session.
 *
 *           If you pass VI_NULL or an empty string for the Repeated
 *           Capability Name parameter, this function returns the command
 *           value of first repeated capability name in the list.
 *
 *           If you pass a specific driver identifier for the Repeated
 *           Capability Name parameter, this function returns the command
 *           value of the identifier string in the internal repeated
 *           capability table.
 *
 *           If you pass any other value for the Repeated Capability
 *           parameter identifier, this function sets the output command
 *           value parameter to empty string and returns an error code.
 *
 *****************************************************************************/
ViStatus Rs_GetRepCapCmdValue (ViSession instrSession,
                               ViAttr attributeId,
                               ViConstString repCapNameId,
                               ViConstString repCapName,
                               ViChar cmdValue[])
{
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
                //rcap            = 0;
    ViUInt32    cmd_idx         = 0,
                rcap            = 0;
    ViChar      repCapNameList[RS_MAX_MESSAGE_BUF_SIZE*3] = "";
    RsSessionPropertiesPtr      sessionProperties = Rs_ViSession (instrSession);

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* Repeated capability name must be valid string */
    if (!repCapNameId)
    {
        viCheckErr (RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED);
    }
    else
        if (strlen (repCapNameId) == 0)
            viCheckErr (RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED);

    /* Is output value valid? */
    if (cmdValue == NULL)
        viCheckErr (RS_ERROR_NULL_POINTER);

    /* Check if the repeated capability name is valid for the attribute */
    viCheckErr (Rs_GetAttributeRepCapName (instrSession, attributeId, repCapNameId, repCapNameList));

    /* Find and return command value */
    for (rcap = 0; rcap < sessionProperties -> numberOfRepCaps; rcap++)
        if (strcmp (sessionProperties -> repCapTable[rcap].repCapNameId, repCapNameId) == 0)
            break;

    if ((Rs_GetIndexOfToken (sessionProperties -> repCapTable[rcap].repCapName, ",", &cmd_idx, repCapName) != VI_SUCCESS))
        {
        viCheckErrElab (RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED,
                        "The passed repeated capability name is either"
                        " restricted for the attribute or not supported"
                        " at all.");
        }

    if ((Rs_GetTokenAtIndex (sessionProperties -> repCapTable[rcap].cmdValues,
        ",", cmd_idx, cmdValue, RS_MAX_MESSAGE_BUF_SIZE) != VI_SUCCESS))
        {
        viCheckErrElab (RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED,
                        "The repeated capability name has no command value attached to it.");
        }

Error:

    return error;
}

/*****************************************************************************
 *- Error Information functions ---------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_SetErrorInfo
 * Purpose:  This function sets the error information for the current
 *           execution thread and the RS session you specify. If you pass
 *           VI_NULL for the vi parameter, this function sets the error
 *           information only for the current execution thread.
 *           The error information includes a primary error code, secondary
 *           error code, and an error elaboration string. For a particular
 *           session, this information is the same as the values held in the
 *           following attributes:
 *
 *           RS_ATTR_PRIMARY_ERROR or PREFIX_ATTR_PRIMARY_ERROR
 *           RS_ATTR_SECONDARY_ERROR or PREFIX_ATTR_SECONDARY_ERROR
 *           RS_ATTR_ERROR_ELABORATION or PREFIX_ATTR_ERROR_ELABORATION
 *           The RS Library also maintains this error information separately
 *           for each thread. This is useful if you do not have a session
 *           handle to pass to Rs_SetErrorInfo or Rs_GetErrorInfo, which
 *           occurs when a call to Rs_SpecificDriverNew fails.
 *           The RS Library retains the information you specify with
 *           Rs_SetErrorInfo until the end-user retrieves it by calling
 *           PREFIX_GetError, the end-user clears it by calling
 *           PREFIX_ClearError, or you overwrite it with another call to
 *           Rs_SetErrorInfo. Rs_GetErrorInfo, which the end-user calls
 *           through PREFIX_GetError, always clears the error information.
 *           Normally, it is the responsibility of the end-user to decide
 *           when to clear the error information by calling PREFIX_GetError
 *           or PREFIX_ClearError. If an instrument driver calls
 *           Rs_GetErrorInfo, it should restore the error information by
 *           calling Rs_SetErrorInfo, possibly adding a secondary error code
 *           or elaboration string.
 *           Rs_SetErrorInfo does not overwrite existing significant error
 *           information unless you pass VI_TRUE for the Overwrite parameter.
 *           Typically, you pass VI_FALSE for this parameter so you can make
 *           multiple calls to this function at different levels in your
 *           instrument driver source code without the risk of losing
 *           important error information. Also, end-users can make multiple
 *           calls to the instrument driver and be assured that
 *           PREFIX_GetError returns significant information about the first
 *           error that occurred since their last call to PREFIX_GetError or
 *           PREFIX_ClearError.
 *           The viCheckErr, viCheckErrElab, viCheckParm, viCheckAlloc, and
 *           viCheckWarn macros use Rs_SetErrorInfo. The RsSpecAn_core.h include file
 *           defines these macros. The viCheckWarn macro calls
 *           Rs_SetErrorInfo on both warnings and errors, whereas the other
 *           macros discard warnings and call Rs_SetErrorInfo only on
 *           errors.
 *
 *****************************************************************************/
ViStatus Rs_SetErrorInfo (ViSession io,
                          ViBoolean overWrite,
                          ViStatus primaryError,
                          ViStatus secondaryError,
                          ViConstString errorElab)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error   = VI_SUCCESS;
    ViInt32     idx     = 0;

    if (sessionProperties == NULL)
        return VI_ERROR_INV_OBJECT;
            
    if (overWrite == VI_TRUE)
        {
        sessionProperties -> primaryError = primaryError;
        sessionProperties -> secondaryError = secondaryError;
        strncpy (sessionProperties -> errorElaboration, errorElab, RS_MAX_MESSAGE_BUF_SIZE - 1);

        (void) Rs_GetAttributeIndex (io, RS_ATTR_PRIMARY_ERROR, &idx);
        memcpy ((ViStatus *)sessionProperties -> attr[idx].p2value, &primaryError, sizeof (ViStatus));

        (void) Rs_GetAttributeIndex (io, RS_ATTR_SECONDARY_ERROR, &idx);
        memcpy ((ViStatus *)sessionProperties -> attr[idx].p2value, &secondaryError, sizeof (ViStatus));

        (void) Rs_GetAttributeIndex (io, RS_ATTR_ERROR_ELABORATION, &idx);
        strncpy ((ViString)sessionProperties -> attr[idx].p2value, errorElab, RS_MAX_MESSAGE_BUF_SIZE - 1);
        }
    else
    {
        /* Primary Error Code */
        if ((sessionProperties -> primaryError >= VI_SUCCESS) && (primaryError < VI_SUCCESS))
        {
            /* Secondary Error Code */
            if ((sessionProperties -> secondaryError >= VI_SUCCESS) && (secondaryError < VI_SUCCESS))
            {
                (void) Rs_GetAttributeIndex (io, RS_ATTR_SECONDARY_ERROR, &idx);
                memcpy ((ViStatus *)sessionProperties -> attr[idx].p2value, &secondaryError, sizeof (ViStatus));
                sessionProperties -> secondaryError = secondaryError;
            }

            /* Error Elaboration */
            if (strlen (sessionProperties -> errorElaboration) == 0)
            {
                (void) Rs_GetAttributeIndex (io, RS_ATTR_ERROR_ELABORATION, &idx);
                strncpy ((ViString)sessionProperties -> attr[idx].p2value, errorElab, RS_MAX_MESSAGE_BUF_SIZE - 1);
        strncpy (sessionProperties -> errorElaboration, errorElab, RS_MAX_MESSAGE_BUF_SIZE - 1);
            }

            (void) Rs_GetAttributeIndex (io, RS_ATTR_PRIMARY_ERROR, &idx);
            memcpy ((ViStatus *)sessionProperties -> attr[idx].p2value, &primaryError, sizeof (ViStatus));
            sessionProperties -> primaryError = primaryError;
        }
    }

    return error;
}

/*****************************************************************************
 * Function: Rs_GetErrorInfo
 * Purpose:  This function retrieves and then clears the error information
 *           for an RS session or for the current execution thread. If you
 *           specify a valid RS session for the vi parameter, this function
 *           retrieves and then clears the error information for the session.
 *           If you pass VI_NULL for the vi parameter, this function
 *           retrieves and then clears the error information for the current
 *           execution thread.
 *           Instrument drivers export this function to the end-user through
 *           the PREFIX_GetErrorInfo function. Normally, the error
 *           information describes the first error that occurred since the
 *           end-user last called PREFIX_GetErrorInfo or
 *           PREFIX_ClearErrorInfo.
 *           The error information includes a primary error code, secondary
 *           code error, and an error elaboration string. For a particular
 *           session, this information is the same as the values held in the
 *           following attributes:
 *
 *           RS_ATTR_PRIMARY_ERROR or PREFIX_ATTR_PRIMARY_ERROR
 *           RS_ATTR_SECONDARY_ERROR or PREFIX_ATTR_SECONDARY_ERROR
 *           RS_ATTR_ERROR_ELABORATION or PREFIX_ATTR_ERROR_ELABORATION
 *           The RS Library also maintains this error information separately
 *           for each thread. This is useful if you do not have a session
 *           handle to pass to Rs_SetErrorInfo or Rs_GetErrorInfo, which
 *           occurs when a call to Rs_SpecificDriverNew fails.
 *           Normally, it is the responsibility of the end-user to decide
 *           when to clear the error information by calling
 *           PREFIX_GetErrorInfo or PREFIX_ClearErrorInfo. If an instrument
 *           driver calls Rs_GetErrorInfo, it must restore the error
 *           information by calling Rs_SetErrorInfo, possibly adding a
 *           secondary error code or elaboration string.
 *           You can call Rs_GetErrorMessage to obtain a text description of
 *           the primary or secondary error value.
 *
 *****************************************************************************/
ViStatus Rs_GetErrorInfo (ViSession io,
                          ViStatus *primaryError,
                          ViStatus *secondaryError,
                          ViChar errorElaboration[])
{

    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error   = VI_SUCCESS;
    ViInt32     idx     = 0;
 
    *primaryError = sessionProperties -> primaryError;
    sessionProperties -> primaryError = VI_SUCCESS;
 
    (void) Rs_GetAttributeIndex (io, RS_ATTR_PRIMARY_ERROR, &idx);
    memset ((ViStatus *)sessionProperties -> attr[idx].p2value, 0,
    sizeof (ViStatus));
 
    *secondaryError = sessionProperties -> secondaryError;
    sessionProperties -> secondaryError = VI_SUCCESS;
 
    (void ) Rs_GetAttributeIndex (io, RS_ATTR_SECONDARY_ERROR, &idx);
    memset ((ViStatus *)sessionProperties -> attr[idx].p2value, 0, sizeof (ViStatus));
 
    strncpy (errorElaboration, sessionProperties -> errorElaboration, RS_MAX_MESSAGE_BUF_SIZE - 1);
    memset (sessionProperties -> errorElaboration, 0, RS_MAX_MESSAGE_BUF_SIZE);
 
    (void) Rs_GetAttributeIndex (io, RS_ATTR_ERROR_ELABORATION, &idx);
    memset ((ViString)sessionProperties -> attr[idx].p2value, 0, RS_MAX_MESSAGE_BUF_SIZE);
 
    return error;
}

/*****************************************************************************
 * Function: Rs_ClearErrorInfo
 * Purpose:  This function clears the error information for the current
 *           execution thread and the RS session you specify. If you pass
 *           VI_NULL for the vi parameter, this function clears the error
 *           information only for the current execution thread.
 *           Instrument drivers export this function to the end-user through
 *           the PREFIX_ClearError function. Normally, the error information
 *           describes the first error that occurred since the end-user last
 *           called PREFIX_GetErrorInfo or PREFIX_ClearError.
 *           The error information includes a primary error code, secondary
 *           code error, and an error elaboration string. For a particular
 *           session, this information is the same as the values held in the
 *           following attributes:
 *           RS_ATTR_PRIMARY_ERROR or
 *           PREFIX_ATTR_PRIMARY_ERRORRS_ATTR_SECONDARY_ERROR or
 *           PREFIX_ATTR_SECONDARY_ERRORRS_ATTR_ERROR_ELABORATION or
 *           PREFIX_ATTR_ERROR_ELABORATION
 *           The RS Library also maintains this error information separately
 *           for each thread. This is useful if you do not have a session
 *           handle to pass to Rs_SetErrorInfo or Rs_GetErrorInfo, which
 *           occurs when a call to Rs_SpecificDriverNew fails.
 *           This function sets the primary and secondary error codes to
 *           VI_SUCCESS (0), and sets the error elaboration string to ".
 *           Avoid calling this function except to implement the
 *           PREFIX_ClearError function. Normally, it is the responsibility
 *           of the end-user to decide when to clear the error information.
 *           Rs_GetErrorInfo, which the end-user calls through
 *           PREFIX_GetErrorInfo, always clears the error information.
 *
 *****************************************************************************/
ViStatus Rs_ClearErrorInfo (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error   = VI_SUCCESS;
    ViInt32     idx     = 0;

    sessionProperties -> primaryError = VI_SUCCESS;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_PRIMARY_ERROR, &idx);
    memset ((ViStatus *)sessionProperties -> attr[idx].p2value, VI_SUCCESS, sizeof (ViStatus));

    sessionProperties -> secondaryError = VI_SUCCESS;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_SECONDARY_ERROR, &idx);
    memset ((ViStatus *)sessionProperties -> attr[idx].p2value, VI_SUCCESS, sizeof (ViStatus));

    memset (sessionProperties -> errorElaboration, 0, RS_MAX_MESSAGE_BUF_SIZE);

    (void) Rs_GetAttributeIndex (io, RS_ATTR_ERROR_ELABORATION, &idx);
    memset ((ViString)sessionProperties -> attr[idx].p2value, 0, RS_MAX_MESSAGE_BUF_SIZE);

    return error;
}

/*****************************************************************************
 * Function: Rs_ParamPositionError
 * Purpose:  Returns one of VI_ERROR_PARAMETER1, VI_ERROR_PARAMETER2, ...,
 *           VI_ERROR_PARAMETER8, RS_ERROR_INVALID_PARAMETER.
 *****************************************************************************/
ViStatus Rs_ParamPositionError (ViInt32 parameterPosition)
{
    ViInt32 error[] = {RS_ERROR_INVALID_PARAMETER,
                       VI_ERROR_PARAMETER1, VI_ERROR_PARAMETER2,
                       VI_ERROR_PARAMETER3, VI_ERROR_PARAMETER4,
                       VI_ERROR_PARAMETER5, VI_ERROR_PARAMETER6,
                       VI_ERROR_PARAMETER7, VI_ERROR_PARAMETER8};

    return ((0 < parameterPosition) && (parameterPosition < 9)) ?
        error[parameterPosition] : RS_ERROR_INVALID_PARAMETER;
}

/*****************************************************************************
 * Function: Rs_GetErrorMessage
 * Purpose:  This function converts an RS or VISA status code into a
 *           meaningful message string. For all other values, it reports the
 *           "Unknown status value" message and returns the
 *           VI_WARN_UNKNOWN_STATUS warning code.
 *           If you have a table of error codes and messages that are
 *           specific to the instrument driver, call
 *           Rs_GetSpecificDriverStatusDesc instead.
 *****************************************************************************/
ViStatus Rs_GetErrorMessage (ViStatus statusCode, ViChar messageBuf[])
{
    ViStatus    error   = VI_SUCCESS;
    ViInt16     cnt     = 0;

    static RsStringValueEntry statusDescArray[] = {

        {VI_SUCCESS,                                        "The call was successful."},
        {RS_ERROR_CANNOT_RECOVER,                           "Unrecoverable failure."},
        {RS_ERROR_INSTRUMENT_STATUS,                        "Instrument error detected."},
        {RS_ERROR_CANNOT_OPEN_FILE,                         "File could not be opened."},
        {RS_ERROR_READING_FILE,                             "File is being read."},
        {RS_ERROR_WRITING_FILE,                             "File is being modified."},

        {RS_ERROR_DRIVER_MODULE_NOT_FOUND,                  "Driver module file not found."},
        {RS_ERROR_CANNOT_OPEN_DRIVER_MODULE,                "Cannot open driver module file for reading."},
        {RS_ERROR_INVALID_DRIVER_MODULE,                    "Driver module has invalid file format or contains invalid data."},
        {RS_ERROR_UNDEFINED_REFERENCES,                     "Driver module contains undefined references."},
        {RS_ERROR_FUNCTION_NOT_FOUND,                       "Cannot find function in driver module."},
        {RS_ERROR_LOADING_DRIVER_MODULE,                    "Failure loading driver module."},

        {RS_ERROR_INVALID_PATHNAME,                         "The path name is invalid."},
        {RS_ERROR_INVALID_ATTRIBUTE,                        "Attribute ID not recognized."},
        {RS_ERROR_RS_ATTR_NOT_WRITABLE,                     "Attribute is read-only."},
        {RS_ERROR_RS_ATTR_NOT_READABLE,                     "Attribute is write-only."},
        {RS_ERROR_INVALID_PARAMETER,                        "Invalid parameter."},
        {RS_ERROR_INVALID_VALUE,                            "Invalid value for parameter or property."},
        {RS_ERROR_FUNCTION_NOT_SUPPORTED,                   "Function or method not supported."},
        {RS_ERROR_ATTRIBUTE_NOT_SUPPORTED,                  "Attribute or property not supported."},
        {RS_ERROR_VALUE_NOT_SUPPORTED,                      "The enumeration value for the parameter is not supported."},
        {RS_ERROR_INVALID_TYPE,                             "Invalid Type."},
        {RS_ERROR_TYPES_DO_NOT_MATCH,                       "The attribute and function parameter types do not match."},
        {RS_ERROR_MULTIPLE_DEFERRED_SETTING,                "The specified attribute already has a value waiting to be updated."},
        {RS_ERROR_ITEM_ALREADY_EXISTS,                      "The specified item already exists."},
        {RS_ERROR_INVALID_CONFIGURATION,                    "Not a valid configuration."},
        {RS_ERROR_VALUE_NOT_AVAILABLE,                      "The requested item or value does not exist or is not available."},
        {RS_ERROR_ATTRIBUTE_VALUE_NOT_KNOWN,                "The requested attribute value not known and cannot be determined."},
        {RS_ERROR_NO_RANGE_TABLE,                           "There is no range table for this attribute."},
        {RS_ERROR_INVALID_RANGE_TABLE,                      "The range table is invalid."},
        {RS_ERROR_NOT_INITIALIZED,                          "A connection to the instrument has not been initialized."},
        {RS_ERROR_NON_INTERCHANGEABLE_BEHAVIOR,             "The class instrument driver has encountered underspecified instrument configurations that limit interchangeability."},
        {RS_ERROR_NO_CHANNEL_TABLE,                         "No channel table has been built for the session. The instrument driver must call Rs_BuildChannelTable in its RsInit function."},
        {RS_ERROR_UNKNOWN_CHANNEL_NAME,                     "Channel or repeated capability name specified is not valid for the instrument."},
        {RS_ERROR_SYS_RSRC_ALLOC,                           "Unable to allocate system resource."},
        {RS_ERROR_ACCESS_DENIED,                            "Permission to access file was denied."},
        {RS_ERROR_TOO_MANY_OPEN_FILES,                      "Too many files opened."},
        {RS_ERROR_UNABLE_TO_CREATE_TEMP_FILE,               "Unable to create temporary file in target directory."},
        {RS_ERROR_NO_UNUSED_TEMP_FILENAMES,                 "All temporary filenames already used in target directory."},
        {RS_ERROR_DISK_FULL,                                "Disk is full."},
        {RS_ERROR_CONFIG_FILE_NOT_FOUND,                    "Configuration file was not found on disk."},
        {RS_ERROR_CANNOT_OPEN_CONFIG_FILE,                  "Cannot open configuration file."},
        {RS_ERROR_ERROR_READING_CONFIG_FILE,                "Error reading configuration file."},
        {RS_ERROR_BAD_INTEGER_IN_CONFIG_FILE,               "Invalid ViInt32 value in configuration file."},
        {RS_ERROR_BAD_DOUBLE_IN_CONFIG_FILE,                "Invalid ViReal64 value in configuration file."},
        {RS_ERROR_BAD_BOOLEAN_IN_CONFIG_FILE,               "Invalid ViBoolean value in configuration file."},
        {RS_ERROR_CONFIG_ENTRY_NOT_FOUND,                   "Entry missing from configuration file."},
        {RS_ERROR_DRIVER_DLL_INIT_FAILED,                   "Initialization failed in driver DLL."},
        {RS_ERROR_DRIVER_UNRESOLVED_SYMBOL,                 "Driver module could not be loaded because of an unresolved external reference."},
        {RS_ERROR_CANNOT_FIND_CVI_RTE,                      "Cannot find CVI Run-Time Engine."},
        {RS_ERROR_CANNOT_OPEN_CVI_RTE,                      "Cannot open CVI Run-Time Engine."},
        {RS_ERROR_CVI_RTE_INVALID_FORMAT,                   "CVI Run-Time Engine has invalid format."},
        {RS_ERROR_CVI_RTE_MISSING_FUNCTION,                 "CVI Run-Time Engine is missing one or more required functions."},
        {RS_ERROR_CVI_RTE_INIT_FAILED,                      "CVI Run-Time Engine initialization failed, probably because of insufficient memory."},
        {RS_ERROR_CVI_RTE_UNRESOLVED_SYMBOL,                "CVI Run-Time Engine could not be loaded because of an unresolved external reference."},
        {RS_ERROR_LOADING_CVI_RTE,                          "Failure loading CVI Run-Time Engine."},
        {RS_ERROR_CANNOT_OPEN_DLL_FOR_EXPORTS,              "Cannot open DLL to read exports."},
        {RS_ERROR_DLL_CORRUPTED,                            "DLL file is corrupt."},
        {RS_ERROR_NO_DLL_EXPORT_TABLE,                      "No export table in DLL."},
        {RS_ERROR_UNKNOWN_DEFAULT_SETUP_ATTR,               "Unknown attribute name for initial setting in configuration file."},
        {RS_ERROR_INVALID_DEFAULT_SETUP_VAL,                "Invalid attribute value for initial setting in configuration file."},
        {RS_ERROR_UNKNOWN_MEMORY_PTR,                       "Memory pointer specified is not known."},
        {RS_ERROR_EMPTY_CHANNEL_LIST,                       "Unable to find any channel or repeated capability strings."},
        {RS_ERROR_DUPLICATE_CHANNEL_STRING,                 "The channel or repeated capability list contains two instances of the same name."},
        {RS_ERROR_DUPLICATE_VIRT_CHAN_NAME,                 "The VirtualChannelNames item in the configuration file contains a duplicate virtual channel name."},
        {RS_ERROR_MISSING_VIRT_CHAN_NAME,                   "The VirtualChannelNames item in the configuration file contains an entry without a virtual channel name (nothing before the '=')."},
        {RS_ERROR_BAD_VIRT_CHAN_NAME,                       "The VirtualChannelNames item in the configuration file contains an invalid virtual channel name. Channel names must contain only alphanumerics, underscores, or an exclamation point."},
        {RS_ERROR_UNASSIGNED_VIRT_CHAN_NAME,                "The VirtualChannelNames item in the configuration file contains a virtual channel name without an assigned channel string (i.e., nothing after '=')."},
        {RS_ERROR_BAD_VIRT_CHAN_ASSIGNMENT,                 "The VirtualChannelNames item in the configuration file contains a virtual channel name that is assigned to an unknown or invalid channel string."},
        {RS_ERROR_CHANNEL_NAME_REQUIRED,                    "Channel or repeated capability name required."},
        {RS_ERROR_CHANNEL_NAME_NOT_ALLOWED,                 "The channel or repeated capability name is not allowed."},
        {RS_ERROR_ATTR_NOT_VALID_FOR_CHANNEL,               "The attribute is not valid for the specified channel or repeated capability."},
        {RS_ERROR_ATTR_MUST_BE_CHANNEL_BASED,               "This operation requires a channel or repeated capability based attribute. The specified attribute is not channel or repeated capability based."},
        {RS_ERROR_CHANNEL_ALREADY_EXCLUDED,                 "The channel has already been excluded for the specified attribute and cannot be re-included."},
        {RS_ERROR_MISSING_OPTION_NAME,                      "The option string parameter contains an entry without a name."},
        {RS_ERROR_MISSING_OPTION_VALUE,                     "The option string parameter contains an entry without a value."},
        {RS_ERROR_BAD_OPTION_NAME,                          "The option string parameter contains an entry with an unknown option name."},
        {RS_ERROR_BAD_OPTION_VALUE,                         "The option string parameter contains an entry with an unknown option value."},
        {RS_ERROR_NOT_CREATED_BY_CLASS,                     "This operation is valid only on a sesssion created by a class driver."},
        {RS_ERROR_RS_INI_IS_RESERVED,                       "You cannot create a configuration file named \"rs.ini\". That filename is reserved."},
        {RS_ERROR_DUP_RUNTIME_CONFIG_ENTRY,                 "There already is an entry of the same name in the run-time configuration."},
        {RS_ERROR_INDEX_IS_ONE_BASED,                       "The index parameter is one-based. You must pass a number greater than or equal to 1."},
        {RS_ERROR_INDEX_IS_TOO_HIGH,                        "The index exceeds the number of items available."},
        {RS_ERROR_ATTR_NOT_CACHEABLE,                       "You cannot set the cache for an attribute that has the RS_VAL_NEVER_CACHE flag."},
        {RS_ERROR_ADDR_ATTRS_MUST_BE_HIDDEN,                "An instrument driver cannot export a ViAddr attribute to the end-user. Use the RS_VAL_HIDDEN flag macro to make it a private attribute."},
        {RS_ERROR_BAD_CHANNEL_NAME,                         "Channel or repeated capability strings must contain only alphanumerics, underscores, or an exclamation point."},
        {RS_ERROR_BAD_PREFIX_IN_CONFIG_FILE,                "The Prefix item in the configuration file does not match the specific driver's prefix."}, 
        {RS_ERROR_OUT_OF_MEMORY,                            "The necessary memory could not be allocated."},
        {RS_ERROR_OPERATION_PENDING,                        "Operation in progress."},
        {RS_ERROR_NULL_POINTER,                             "NULL pointer passed for parameter or property."},
        {RS_ERROR_UNEXPECTED_RESPONSE,                      "Unexpected response from the instrument."},
        {RS_ERROR_FILE_NOT_FOUND,                           "File not found."},
        {RS_ERROR_INVALID_FILE_FORMAT,                      "The file format is invalid."},
        {RS_ERROR_STATUS_NOT_AVAILABLE,                     "The instrument status is not available."},
        {RS_ERROR_ID_QUERY_FAILED,                          "Instrument ID Query failed."},
        {RS_ERROR_RESET_FAILED,                             "Instrument reset failed."},
        {RS_ERROR_RESOURCE_UNKNOWN,                         "Insufficient location information or resource not present in the system."},
        {RS_ERROR_ALREADY_INITIALIZED,                      "The driver is already initialized."},
        {RS_ERROR_CANNOT_CHANGE_SIMULATION_STATE,           "The simulation state cannot be changed."},
        {RS_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR,     "Invalid number of levels in selector."},
        {RS_ERROR_INVALID_RANGE_IN_SELECTOR,                "Invalid range in selector."},
        {RS_ERROR_UNKOWN_NAME_IN_SELECTOR,                  "Unknown name in selector."},
        {RS_ERROR_BADLY_FORMED_SELECTOR,                    "Badly-formed selector."},
        {RS_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER,              "Unknown physical selector."},

        {RS_ERROR_INVALID_SESSION_HANDLE,                   "The session handle is not valid."},
        {RS_ERROR_CANNOT_CREATE_LOCK,                       "The session handle is not valid."},
        {RS_ERROR_CANNOT_CREATE_THREAD_LOCAL,               "Could not create thread local."},

        {RS_CONFIG_ERROR_DESERIALIZE_FAILED,                "The specified configuration store file could not be deserialized."},
        {RS_CONFIG_ERROR_ALREADY_DESERIALIZED,              "A deserialize was attempted after a previous deserialize had already succeeded."},
        {RS_CONFIG_ERROR_SERIALIZE_FAILED,                  "The specified configuration store file could not be serialized."},
        {RS_CONFIG_ERROR_SESSION_NOT_FOUND,                 "The session name or logical name could not be resolved to a session or driver session."},
        {RS_CONFIG_ERROR_NOT_IN_GLOBAL,                     "The item does not exist in the global collection."},
        {RS_CONFIG_ERROR_ALREADY_EXIST,                     "An entry with name already exists in the collection."},
        {RS_CONFIG_ERROR_MASTER_NOT_FOUND,                  "The registry entry for the master configuration store does not exist or the file could not be found."},
        {RS_CONFIG_ERROR_NOT_EXIST,                         "The item does not exist in the collection."},
        {RS_CONFIG_ERROR_INVALID_DATA_COMPONENT,            "The data component is not a valid data component."},
        {RS_CONFIG_ERROR_LOCAL_REFERENCE_EXIST,             "The element cannot be removed from the global collection when it is referenced in the local collections."},
        {RS_CONFIG_ERROR_INVALID_HANDLE,                    "The specified handle is invalid or of an incorrect type."},
        {RS_CONFIG_ERROR_INVALID_PROPERTY_ID,               "The specified property ID is not valid for this function."},

        {RS_ERROR_CANNOT_MODIFY_REPEATED_CAPABILITY_TABLE,  "Repeated Capability lists cannot be modified after attributes have been added to them."},
        {RS_ERROR_CANNOT_RESTRICT_ATTRIBUTE_TWICE,          "An attribute can only be restricted to a subset of a repeated capability once."},
        {RS_ERROR_REPEATED_CAPABILITY_ALREADY_EXISTS,       "The repeated capability table cannot be built because it already exists."},
        {RS_ERROR_REPEATED_CAPABILITY_NOT_DEFINED,          "The repeated capability has not been defined yet."},
        {RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME,         "The repeated capability name cannot be an empty or NULL string."},
        {RS_ERROR_CONFIG_SERVER_NOT_PRESENT,                "The Config Server module is not present on the system."},
 
        {VI_WARN_NSUP_ID_QUERY,                             "Identification query not supported."},
        {VI_WARN_NSUP_RESET,                                "Reset operation not supported."},
        {VI_WARN_NSUP_SELF_TEST,                            "Self test operation not supported."},
        {VI_WARN_NSUP_ERROR_QUERY,                          "Error query operation not supported."},
        {VI_WARN_NSUP_REV_QUERY,                            "Revision query not supported."},

        /* Common Instrument Driver Errors and Warnings */

        {VI_ERROR_PARAMETER1,                               "Parameter 1 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER2,                               "Parameter 2 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER3,                               "Parameter 3 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER4,                               "Parameter 4 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER5,                               "Parameter 5 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER6,                               "Parameter 6 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER7,                               "Parameter 7 out of range, or error trying to set it."},
        {VI_ERROR_PARAMETER8,                               "Parameter 8 out of range, or error trying to set it."},
        {VI_ERROR_FAIL_ID_QUERY,                            "Instrument failed the ID Query."},
        {VI_ERROR_INV_RESPONSE,                             "Invalid response from instrument."},
        
        {RS_ERROR_INSTRUMENT_OPTION,                        "Required instrument option(s) not present."},
        {RS_ERROR_INSTRUMENT_MODEL,                         "Required instrument model(s) not present."},

        {VI_NULL, VI_NULL}
    };

    error = viStatusDesc (VI_NULL, statusCode, messageBuf);

    if (error != VI_SUCCESS)
        {
        for (cnt = 0; statusDescArray[cnt].string; cnt++)
            {
            if (statusDescArray[cnt].value == statusCode)
                {
                sprintf (messageBuf, "%s", statusDescArray[cnt].string);
                
                return VI_SUCCESS;
                }
            }
        sprintf (messageBuf, "The status code passed to the operation could not be interpreted.");

        return VI_WARN_UNKNOWN_STATUS;
        }

    return error;
}

/*****************************************************************************
 *- Locking functions for multithreading ------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_LockSession
 * Purpose:  This operation is used to obtain a lock on the specified
 *           resource. Obtains a multithread lock on the instrument session.
 *           Before it does so, it waits until all other execution threads
 *           have released their locks on the instrument session.
 *
 *****************************************************************************/
ViStatus Rs_LockSession (/*@unused@*/ViSession session, /*@unused@*/ViBoolean *callerHasLock)
{
    return 0;
    
#if 0
    RsSessionPropertiesPtr  sessionProperties = NULL;
    ViStatus    error   = VI_SUCCESS;
    ViSession   vi      = Rs_ViSession(session);

    /* Verify passed session handle */
    checkErr (Rs_CheckSession (vi));

    sessionProperties = (RsSessionPropertiesPtr)vi;

    /* Check if the io session is opened (not simulated) */
    if (sessionProperties -> vi != sessionProperties -> io)
        {
        /* If you do not want to use this parameter, pass VI_NULL. */
        if (callerHasLock)
            {
            if (*callerHasLock == VI_FALSE)
                {
                /*
                    If the value is VI_TRUE, Rs_LockSession does not lock the session
                    again. If the value is VI_FALSE, Rs_LockSession obtains the lock
                    and sets the value of the parameter to VI_TRUE.
                */
                *callerHasLock = VI_TRUE;
                
                checkErr (viLock (sessionProperties -> io, VI_EXCLUSIVE_LOCK,
                    VI_TMO_INFINITE, VI_NULL, VI_NULL));

                sessionProperties -> locked = VI_TRUE;
                }
            }
        else
            {
            checkErr (viLock (sessionProperties -> io, VI_EXCLUSIVE_LOCK,
                VI_TMO_INFINITE, VI_NULL, VI_NULL));

            sessionProperties -> locked = VI_TRUE;
            }
        }
    else
        {
        sessionProperties -> locked = VI_TRUE;

        if (callerHasLock)
            *callerHasLock = VI_TRUE;
        }

Error:

    return error;
#endif
}

/*****************************************************************************
 * Function: Rs_UnlockSession
 * Purpose:  This function releases a lock that you acquired on an instrument
 *           session using Rs_LockSession.
 *
 *****************************************************************************/
ViStatus Rs_UnlockSession (/*@unused@*/ViSession session, /*@unused@*/ViBoolean *callerHasLock)
{

    return 0;
#if 0    
    RsSessionPropertiesPtr  sessionProperties = NULL;
    ViStatus    error   = VI_SUCCESS;
    ViSession   vi      = Rs_ViSession(session);
    /* Verify passed session handle */
    checkErr (Rs_CheckSession (vi));

    sessionProperties = (RsSessionPropertiesPtr)vi;

    /* Check if the io session is opened (not simulated) */
    if (sessionProperties -> vi != sessionProperties -> io)
        {
        /* If you do not want to use this parameter, pass VI_NULL. */
        if (callerHasLock)
            {
            /*
                If the value is VI_FALSE, Rs_UnlockSession does not attempt to
                unlock the session. If the value is VI_TRUE, Rs_UnlockSession
                unlocks the lock and sets the value of the parameter to VI_FALSE.
            */
            if (*callerHasLock == VI_TRUE)
                {
                sessionProperties -> locked = VI_FALSE;
                *callerHasLock = VI_FALSE;

                checkErr (viUnlock (sessionProperties -> io));
                }
            }
        else
            {
            checkErr (viUnlock (sessionProperties -> io));
            sessionProperties -> locked = VI_FALSE;
            }
        }
    else
        {
        sessionProperties -> locked = VI_FALSE;

        if (callerHasLock)
            *callerHasLock = VI_FALSE;
        }

Error:

    return error;
#endif
}

/*****************************************************************************
 *- Accessor functions for inherent attributes ------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_IOSession
 * Purpose:  This function returns the current value of the
 *           RS_ATTR_IO_SESSION attribute for the session you specify.
 *           Use Rs_IOSession in the high-level functions in specific
 *           instrument drivers. Rs_IOSession provides fast, convenient
 *           access to the RS_ATTR_IO_SESSION attribute because it does no
 *           error checking and does not lock the session.
 *
 *****************************************************************************/
ViSession Rs_IOSession (RsSessionPropertiesPtr sessionProperties)
{
    if (sessionProperties != VI_NULL)
                return sessionProperties -> io;
    else
        return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_ViSession
 * Purpose:  This function returns virtual session handle.
 *           Use Rs_ViSession in the high-level functions in specific
 *           instrument drivers.
 *
 *****************************************************************************/
RsSessionPropertiesPtr Rs_ViSession (ViSession session)
{
    int i = 0;
    RsSessionPropertiesPtr psession = NULL;


    while ((i < MAX_NUMBER_OF_SESSIONS) && (session != gresources[i].session)) i++;

    if ((i < MAX_NUMBER_OF_SESSIONS) && (gresources[i].session != VI_NULL))
        psession = gresources[i].properties;
    else
        psession = NULL;

    return psession;
}

/*****************************************************************************
 * Function: Rs_RangeChecking
 * Purpose:  This function returns the current value of the
 *           RS_ATTR_RANGE_CHECK attribute for the session you specify.
 *
 *           Use Rs_RangeChecking in the high-level functions in specific
 *           instrument drivers. Rs_RangeChecking provides fast, convenient
 *           access to the RS_ATTR_RANGE_CHECK attribute because it does no
 *           error checking and does not lock the session.
 *
 *           Note:  Do not call this function unless you have already locked
 *           the session.
 *
 *****************************************************************************/
ViBoolean Rs_RangeChecking (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViInt32     idx = 0;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_RANGE_CHECK, &idx);

    return (sessionProperties != 0) ? *(ViBoolean *)(sessionProperties -> attr[idx].p2value) : VI_TRUE;
}

/*****************************************************************************
 * Function: Rs_QueryInstrStatus
 * Purpose:  This function returns the current value of the
 *           RS_ATTR_QUERY_INSTR_STATUS attribute for the session you
 *           specify.
 *           Use Rs_QueryInstrStatus in the high-level functions in specific
 *           instrument drivers. Rs_QueryInstrStatus provides fast,
 *           convenient access to the RS_ATTR_QUERY_INSTR_STATUS attribute
 *           because it does no error checking and does not lock the session.
 *
 *           Note:  Do not call this function unless you have already locked
 *           the session.
 *
 *****************************************************************************/
ViBoolean Rs_QueryInstrStatus (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViInt32     idx = 0;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_QUERY_INSTR_STATUS, &idx);

    return (sessionProperties != 0) ? *(ViBoolean *)(sessionProperties -> attr[idx].p2value) : VI_TRUE;
}

/*****************************************************************************
 * Function: Rs_Simulating
 * Purpose:  This function returns the current value of the RS_ATTR_SIMULATE
 *           attribute for the session you specify.
 *           Use Rs_Simulating in the high-level functions in specific and
 *           class instrument drivers. Rs_Simulate provides fast, convenient
 *           access to the RS_ATTR_SIMULATE attribute because it does no
 *           error checking and does not lock the session.
 *
 *           Note:  Do not call this function unless you have already locked
 *           the session.
 *
 *****************************************************************************/
ViBoolean Rs_Simulating (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViInt32     idx = 0;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_SIMULATE, &idx);

    return (sessionProperties != 0) ? *(ViBoolean *)(sessionProperties -> attr[idx].p2value) : VI_FALSE;
}

/*****************************************************************************
 * Function: Rs_UseSpecificSimulation
 * Purpose:  This function returns the current value of the
 *           RS_ATTR_USE_SPECIFIC_SIMULATION attribute for the session you
 *           specify.
 *           Use Rs_UseSpecificSimulation in the high-level functions in
 *           specific and class instrument drivers. Rs_UseSpecificSimulation
 *           provides fast, convenient access to the
 *           RS_ATTR_USE_SPECIFIC_SIMULATION attribute because it does no
 *           error checking and does not lock the session.
 *
 *           Note:  Do not call this function unless you have already locked
 *           the session.
 *
 *****************************************************************************/
ViBoolean Rs_UseSpecificSimulation (ViSession io)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViInt32     idx = 0;

    (void) Rs_GetAttributeIndex (io, RS_ATTR_USE_SPECIFIC_SIMULATION, &idx);

    return (sessionProperties != NULL) ? *(ViBoolean *)(sessionProperties -> attr[idx].p2value) : VI_FALSE;
}

/*****************************************************************************
 *- Helper functions for utilities or tools ---------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_GetAttributeFlags
 * Purpose:  This function obtains the current values of the flags for the
 *           attribute you specify.
 *
 *****************************************************************************/
ViStatus Rs_GetAttributeFlags (ViSession instrSession,
                               ViAttr attributeId,
                               RsAttrFlags *flags)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    *flags = sessionProperties -> attr[idx].flags;

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_SetAttributeFlags
 * Purpose:  This function sets the flags of an attribute to new values. It
 *           always sets all of the flags. If you want to change one flag,
 *           use Rs_GetAttributeFlags to obtain the current values of all
 *           the flags, modify the bit for the flag you want to change, and
 *           then call Rs_SetAttributeFlags.
 *           You cannot modify the value of the RS_VAL_MULTI_CHANNEL flag.
 *
 *****************************************************************************/
ViStatus Rs_SetAttributeFlags (ViSession instrSession,
                               ViAttr attributeId,
                               RsAttrFlags flags)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    sessionProperties -> attr[idx].flags &= RS_VAL_MULTI_CHANNEL;
    sessionProperties -> attr[idx].flags |= (flags & (~RS_VAL_MULTI_CHANNEL));

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_GetAttributeIndex
 * Purpose:  This function returns index of attribute in the attribute list.
 *****************************************************************************/
ViStatus Rs_GetAttributeIndex (ViSession io, ViAttr attributeId, ViInt32 *attributeIndex)
{
    ViStatus    error = VI_SUCCESS;
    RsSessionPropertiesPtr sessionProperties = Rs_ViSession (io);

    if (sessionProperties == NULL)
        return VI_ERROR_INV_OBJECT;
    
    for (*attributeIndex = 0; *attributeIndex < (ViInt32) sessionProperties -> numberOfAttr; (*attributeIndex)++)
            if (sessionProperties -> attr[*attributeIndex].constant == (ViInt32) attributeId)
                break;

    if (*attributeIndex >= (ViInt32) sessionProperties -> numberOfAttr)
        return RS_ERROR_INVALID_ATTRIBUTE;

    if ((sessionProperties -> attr[*attributeIndex].flags & RS_VAL_NOT_SUPPORTED) != 0)
        return RS_ERROR_ATTRIBUTE_NOT_SUPPORTED;

    return error;
}

/*****************************************************************************
 * Function: Rs_ApplyAttributeDefaults
 * Purpose:  This function applies the default attribute values. Optionally
 *           exclude inherent attributes from update.
 *****************************************************************************/
ViStatus Rs_ApplyAttributeDefaults (ViSession io, ViBoolean updateInherentAttr)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error   = VI_SUCCESS;
    ViUInt32    idx     = 0;

    for (idx = 0; idx < sessionProperties -> numberOfAttr; idx++)
        {
        /* Update inherent attributes? */
        if ((updateInherentAttr == VI_FALSE) && 
            (sessionProperties -> attr[idx].constant < RS_SPECIFIC_PRIVATE_ATTR_BASE))
            {
            /* Inherent attributes are not updated */
            }
        else
            {
            size_t      data_size = 0;
            void        *p2value,
                        *p2default;
      size_t      offset= 0;

            p2value = sessionProperties -> attr[idx].p2value;
        
            switch (sessionProperties -> attr[idx].dataType)
                {
                case RS_VAL_INT32:
                    data_size = RS_VAL_INT32_SIZE;
                    p2default = &sessionProperties -> attr[idx].integerDefault;
                    break;
                case RS_VAL_INT64:
                    data_size = RS_VAL_INT32_SIZE;
                    p2default = &sessionProperties -> attr[idx].integerDefault;
          offset = RS_VAL_INT64_SIZE - RS_VAL_INT32_SIZE;
                    break;
                case RS_VAL_REAL64:
                    data_size = RS_VAL_REAL64_SIZE;
                    p2default = &sessionProperties -> attr[idx].doubleDefault;
                    break;
                case RS_VAL_STRING:
                    //data_size = RS_VAL_STRING_SIZE;
                    if (sessionProperties -> attr[idx].stringDefault)
                        data_size=strlen(sessionProperties -> attr[idx].stringDefault);
                    else
                        data_size=0;
                    p2default = &sessionProperties -> attr[idx].stringDefault;
                    break;
                case RS_VAL_ADDR:
                    data_size = RS_VAL_ADDR_SIZE;
                    p2default = &sessionProperties -> attr[idx].integerDefault;
                    break;
                case RS_VAL_SESSION:
                    data_size = RS_VAL_SESSION_SIZE;
                    p2default = &sessionProperties -> attr[idx].sessionDefault;
                    break;
                case RS_VAL_BOOLEAN:
                    data_size = RS_VAL_BOOLEAN_SIZE;
                    p2default = &sessionProperties -> attr[idx].booleanDefault;
                    break;
                default:
                    data_size = RS_VAL_UNKNOWN_TYPE_SIZE;
                    p2default = sessionProperties -> attr[idx].p2value;
                }

      memset (p2value, 0, data_size + offset);
            memcpy (((char*)p2value) + offset, p2default, data_size);
            }
        }

    return error;
}

/*****************************************************************************
 * Function: Rs_GetTokenAtIndex
 * Purpose:  This function breaks a string into tokens, which are separated
 *           by the specified delimiter and then returns token at index
 *           or error code if there is no token.
 *****************************************************************************/
ViStatus Rs_GetTokenAtIndex (ViChar *stringToSeparate,
                             ViConstString delimiter,
                             ViUInt32 index,
                             ViChar token[],
                             ViUInt32 tokenMaxLength)
{
    ViStatus    error   = VI_SUCCESS;
    ViUInt32    cnt     = 0;
    size_t      n       = 0;
    size_t      token_length = 0;
    ViChar      *p2string,
                *p2token;

    if ((delimiter == NULL) || (token == NULL) || (stringToSeparate == NULL))
        return RS_ERROR_NULL_POINTER;

    p2string = stringToSeparate;

    while (p2string != NULL)
        {
        p2token = p2string;
        p2string = strstr (p2string, delimiter);
        token_length = (p2string > p2token) ? p2string - p2token : p2token - p2string ;


        if (index == cnt)
            {
            n = (tokenMaxLength < token_length) ? (size_t) (tokenMaxLength - 1) : token_length;
            strncpy (token, p2token, n);
            token[n] = '\0';

            break;
            }

        if (p2string)
            p2string += strlen (delimiter);
        else
            return RS_ERROR_INDEX_IS_TOO_HIGH;

        cnt++;
        }

    return error;
}

/*****************************************************************************
 * Function: Rs_GetIndexOfToken
 * Purpose:  This function breaks a string into tokens, which are separated
 *           by the specified delimiter and then returns index of selected
 *           token or error code if there is no token found. If passed NUL
 *           pointer as a token or delimiter and string length of token or 
 *           delimiter is zero, it returns zero as index.
 *****************************************************************************/
ViStatus Rs_GetIndexOfToken (ViChar *string_to_separate,
                             ViConstString delimiter,
                             ViUInt32 *index,
                             ViConstString token)
{
    ViStatus    error   = VI_SUCCESS;
    ViUInt32    cnt     = 0;
    ViChar      *p2string,
                *p2token;
    size_t      length = 0;
    size_t      token_length = 0;

    if (!string_to_separate || !index)
        return RS_ERROR_NULL_POINTER;

    if (!token || !delimiter)
        {
        *index = 0;
        return error;
        }
    else
        if ((strlen (token) == 0) || (strlen (delimiter) == 0))
        {
        *index = 0;
        return error;
        }

    p2string = string_to_separate;

    while (p2string)
        {
        p2token = p2string;
        p2string = strstr (p2string, delimiter);
        token_length = (p2string > p2token) ? p2string - p2token : p2token - p2string ;
        length = (strlen(token) > token_length ? strlen(token) : token_length);
        if (strncmp (p2token, token, length)==0)
            {
            *index = cnt;
            break;
            }

        if (p2string != NULL)
            p2string += strlen (delimiter);
        else
            return RS_ERROR_INVALID_VALUE;

        cnt++;
        }

    return error;
}

/*****************************************************************************
 * Function: Rs_CheckModelOpt
 * Purpose:  Check if the attribute is supported for the currently used
 *           instrument model (and options included).
 *
 *****************************************************************************/
ViStatus Rs_CheckModelOpt (ViSession instrSession, ViAttr attributeId)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    ViBoolean   boolean         = VI_FALSE;
    ViChar      options_string[RS_MAX_MESSAGE_BUF_SIZE] = "",
                token[RS_MAX_MESSAGE_BUF_SIZE] = "",
                tmp_instr_model[RS_MAX_MESSAGE_BUF_SIZE] = "";
                
    ViChar      *p2string       = NULL,
                *p2token        = NULL,
                operation;
    ViChar*     options_list = NULL;
    ViChar*     instrument_model = NULL;
    size_t      len = 0;
    
    viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPTIONS_LIST, &idx));
  checkAlloc (options_list = (ViChar*) malloc (1 + strlen((ViString)sessionProperties -> attr[idx].p2value)));
    strcpy (options_list, (ViString)sessionProperties -> attr[idx].p2value);

    viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_INSTRUMENT_MODEL, &idx));
  checkAlloc (instrument_model = (ViChar*) malloc (1 + strlen((ViString)sessionProperties -> attr[idx].p2value)));
    strcpy (instrument_model, (ViString)sessionProperties -> attr[idx].p2value);

    /* Instrument model */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* No model(s) listed, skip model checking */
    if (sessionProperties -> attr[idx].supportedModels)
    {
        p2token=sessionProperties -> attr[idx].supportedModels;
        while (p2token){
            if (sscanf (p2token, "%[^|]", tmp_instr_model) != 1)
        checkErr (RS_ERROR_DRIVER_UNRESOLVED_SYMBOL);
            len=strlen(tmp_instr_model);
            if (!strncmp(tmp_instr_model,instrument_model,len))
                break;
            p2token = strchr (p2token, '|');
            if (p2token) p2token++;
        }
        if (!p2token)
        {
            checkErr (RS_ERROR_INSTRUMENT_MODEL);
        } 
     } 
     
    /* Verify if the instrument model & option are available.
           User option checking syntax:
    
                InstrModel(option1&option2|option3)|InstrModel(option1&option2|option3)...

                or

                option1&option2|option3...

           No operator priorities (behaves as stack automat). */
     if ((sessionProperties -> attr[idx].instrumentOptions) && (sessionProperties -> optionChecking == VI_TRUE))
     {
        p2token=sessionProperties -> attr[idx].instrumentOptions;
     
        while (p2token)
        {
            if (sscanf (p2token, "%[^(]", tmp_instr_model) != 1)
        checkErr (RS_ERROR_DRIVER_UNRESOLVED_SYMBOL);
            len=strlen(tmp_instr_model);
            if (!strncmp(tmp_instr_model,instrument_model,len))
                break;
            
            p2token = strchr (p2token, '(');
            if (p2token) 
            {
                p2token = strchr (p2token, ')');
                p2token+=2;
            }
        }
        
         
         if (p2token)
         {
            p2token = strchr (p2token,'(');
            if (p2token)
      {
                if (sscanf (p2token,"(%[^)]", options_string) != 1)
          checkErr (RS_ERROR_DRIVER_UNRESOLVED_SYMBOL);
      }
         }
        else
        {
            strcpy (options_string, sessionProperties -> attr[idx].instrumentOptions);
        }
        /* Parse option string */
        strcpy (token, options_string);
        p2token = token;
        p2string = strpbrk (token, "&|");
        boolean = VI_FALSE;

        if (p2string != NULL) /* Parse option string, evaluate expression */
        {
            operation = *p2string;
            *p2string = '\0';
    
            boolean = (ViBoolean) ((strstr (options_list, p2token)) ? VI_TRUE : VI_FALSE);

            do
            {
          
                ViChar operation2 = '&';
        
                p2token = p2string + 1;
                p2string = strpbrk (p2token, "&|");
                if (p2string)
                {
                    operation2 = *p2string;
                    *p2string = '\0';
                }

                switch (operation)
                    {
                    case '|':
                        boolean |= (strstr (options_list, p2token)) ? VI_TRUE : VI_FALSE;
                        break;
                    case '&':
                        boolean &= (strstr (options_list, p2token)) ? VI_TRUE : VI_FALSE;
                        break;
                    default:
                        break;
                    }

                operation = operation2;

             } while (p2string);
        }
        else /* Check presence of single option only */
        {
            if (!strstr (options_list, options_string))
                boolean = VI_FALSE;
            else
                boolean = VI_TRUE;
        }
    }
    else
        boolean = VI_TRUE;

    if (boolean == VI_FALSE)
        error = RS_ERROR_INSTRUMENT_OPTION;

Error:
  if (options_list) free (options_list);
  if (instrument_model) free (instrument_model);
    return error;
}

/*****************************************************************************
 *- Instrument I/O utilities ------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Read Data With Unknown length
 * Purpose:  This function allocates buffer, reads data from the
 *           instrument and returns number of taken bytes.
 *
 * WARNING:  - When this function is completed, deallocate buffer, if any
 *             pointer has been returned.
 *           - This function does not work correctly over the serial interface
 *             if the binary data are transferred.
 *****************************************************************************/
ViStatus Rs_ReadDataUnknownLength (ViSession io,
                                   ViChar **outputBuffer,
                                   ViUInt32 *byteCount)
{
    ViStatus    error       = VI_SUCCESS;
    ViUInt32    count       = 0;
    ViChar      *buffer,
                *p2buffer;
    size_t      actualSize  = 0;

    *outputBuffer = VI_NULL;

    if (byteCount)
        *byteCount = 0;

    /* Allocate Buffer */
    actualSize = RS_MAX_MESSAGE_BUF_SIZE;
    checkAlloc (buffer = (ViChar *)calloc (actualSize, sizeof (ViChar)));

    p2buffer = buffer;

    do
        {
        if ((error = viRead (io, (ViPBuf)p2buffer, RS_MAX_MESSAGE_BUF_SIZE, &count)) < 0)
            {
            free (buffer);
            *outputBuffer = VI_NULL;
            
            return error;
            }

        if (count == RS_MAX_MESSAGE_BUF_SIZE) /* Buffer is small, reallocate it */
            {
            actualSize += RS_MAX_MESSAGE_BUF_SIZE;
            checkAlloc (buffer = (ViChar *)realloc (buffer, actualSize));

            p2buffer = buffer + (actualSize - RS_MAX_MESSAGE_BUF_SIZE); /* Set pointer to end of data in reallocated buffer */
            }
        else
            {
            *(p2buffer + count) = '\0'; /* For sure set end of string at the end of data */
            }

        } while (error == VI_SUCCESS_MAX_CNT); /* if buffer was small, continue with next read */

    *outputBuffer = buffer;

    if (byteCount != NULL)
        *byteCount = (ViUInt32) ((actualSize - RS_MAX_MESSAGE_BUF_SIZE) + count);

Error:

    return error;
}

/*****************************************************************************
 *- Functions for class instrument drivers ----------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_ApplyDefaultSetup
 * Purpose:  This function applies the default attribute setup you specify in
 *           the Rs Configuration file. The specific driver should call this
 *           function after completely initializing a new session.
 *           This function has no effect on the instrument session unless the
 *           application initializes the driver using an RS class driver, or
 *           unless the application initializes the specific driver using an
 *           RS logical name.
 *
 *****************************************************************************/
ViStatus Rs_ApplyDefaultSetup (/*@unused@*/ViSession vi)
{
    // TODO: Currently not implemented
    
    return VI_SUCCESS;
}

/*****************************************************************************
 *- Helper functions for specific instrument drivers ------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_GetSpecificDriverStatusDesc
 * Purpose:  This function converts a status code that an instrument driver
 *           function returns into a meaningful message string. It interprets
 *           RS and VISA status codes just as Rs_GetErrorMessage does, but
 *           it also allows you to pass a table of error codes and messages
 *           that are specific to the instrument driver.
 *           Use this function to implement the PREFIX_error_message function
 *           in the instrument driver.
 *           If the function cannot find a description for the status code,
 *           it reports the "Unknown status value" message and returns the
 *           VI_WARN_UNKNOWN_STATUS warning code.
 *
 *****************************************************************************/
ViStatus Rs_GetSpecificDriverStatusDesc (/*@unused@*/ViSession vi,
                                         ViStatus statusCode,
                                         ViChar messageBuf[],
                                         RsStringValueTable additionalTableToSearch)
{
    ViStatus    error   = VI_SUCCESS;
    ViInt16     cnt     = 0;

    error = Rs_GetErrorMessage (statusCode, messageBuf);

    if (error == VI_WARN_UNKNOWN_STATUS)
        {
        for (cnt = 0; additionalTableToSearch[cnt].string; cnt++)
            {
            if (additionalTableToSearch[cnt].value == statusCode)
                {
                sprintf (messageBuf, "%s", additionalTableToSearch[cnt].string);
                
                return VI_SUCCESS;
                }
            }
        sprintf (messageBuf, "The status code passed to the operation could not be interpreted.");

        return VI_WARN_UNKNOWN_STATUS;
        }

    return error;
}

/*****************************************************************************
 * Function: Rs_WriteInstrData
 * Purpose:  This function writes a command string directly to an instrument
 *           using VISA I/O. The function bypasses the attribute state
 *           caching mechanism and therefore always invalidates all attribute
 *           cache values for the session. Use this function only to
 *           implement the PREFIX_WriteInstrData function that your
 *           instrument driver exports to the end-user.
 *
 *****************************************************************************/
ViStatus Rs_WriteInstrData (ViSession io, ViConstString writeBuffer)
{
    return viWrite (io, (ViBuf)writeBuffer, (ViUInt32) strlen(writeBuffer), VI_NULL);
}

/*****************************************************************************
 * Function: Rs_ReadInstrData
 * Purpose:  This function reads data directly from an instrument using VISA
 *           I/O. The function bypasses the attribute state caching
 *           mechanism. Use this function only to implement the
 *           PREFIX_ReadInstrData function that your instrument driver
 *           exports to the end-user.
 *           If data is not available at the instrument's output buffer when
 *           you call this function, the instrument might hang up. In that
 *           case, the function does not return until the VISA I/O call times
 *           out. If you have disabled the timeout, the function hangs
 *           indefinitely.
 *
 *****************************************************************************/
ViStatus Rs_ReadInstrData (ViSession io,
                           ViInt32 numBytes,
                           ViChar rdBuf[],
                           ViUInt32 *bytesRead)
{
    return viRead (io, (ViBuf) rdBuf, (ViUInt32) numBytes, bytesRead);
}

/*****************************************************************************
 * Function: Rs_GetInfoFromResourceName
 * Purpose:  This function returns the appropriate resource name and option
 *           string that Rs_SpecificDriverNew function uses to create a new
 *           RS session. The Resource Name can be an actual resource
 *           descriptor or a logical name or driver session name that the
 *           user configures with the RS Configuration utility.
 *           If the string that the user passes in the Resource Name
 *           parameter is an actual resource descriptor, this function
 *           returns the original resource descriptor and option string in
 *           the New Resource Name and New Option String parameters and
 *           returns VI_FALSE in the Is Logical Name parameter.
 *           If the string that the user passes in the Resource Name
 *           parameter is a logical name or driver session name, this
 *           function returns strings in the New Resource Name and New Option
 *           String parameters based on the settings of the logical name or
 *           virtual instrument in the RS Configuration utility. The
 *           function return VI_TRUE in the Is Logical Name parameter.
 *
 *           Example:
 *
 *           Rs_GetInfoFromResourceName ("GPIB0::2::INSTR", "Simulate=1",
 *                                        newRsrcString, newOptionString,
 *                                        &isLogicalName);
 *
 *           newRsrcString and newOptionString contain the same values you
 *           pass to the function, and isLogicalName is VI_FALSE.
 *
 *           Rs_GetInfoFromResourceName ("SampleDMM", "", newRsrcString,
 *                                        newOptionString,&isLogicalName);
 *
 *           newRsrcString and newOptionString now contain the resource
 *           descriptor from the RS configuration and the option that tells
 *           the engine through the Rs_SpecificDriverNew function that the
 *           initial session setup comes from the RS configuration.
 *           isLogicalName is VI_TRUE.
 *
 *****************************************************************************/
ViStatus Rs_GetInfoFromResourceName (ViRsrc resourceName,
                                     ViString optionString,
                                     ViChar newResourceName[],
                                     ViChar newOptionString[],
                                     ViBoolean *isLogicalName)
{
    strcpy (newResourceName, resourceName);
    strcpy (newOptionString, optionString);

    *isLogicalName = VI_FALSE;
    
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_Delay
 * Purpose : With a call to Rs_Delay, the current program is suspended
 *           from execution for the number of seconds specified by the
 *           argument seconds. Rs_Delay is accurate to a millisecond.
 *           This function is platform independent.
 *****************************************************************************/
void Rs_Delay (ViReal64 numberOfSeconds)
{
    clock_t StartTime = clock();

    while ((((double)(clock() - StartTime))/(double)CLOCKS_PER_SEC) < (numberOfSeconds)) Sleep(0);

    return;
}

/*****************************************************************************
 * Function: Rs_ReadToFile
 * Purpose:  This function reads data from an instrument using VISA I/O and
 *           writes it to a file you specify. Use this function internally in
 *           your instrument driver.
 *           The function assumes that the RS_ATTR_IO_SESSION attribute for
 *           the RS session you specify holds a valid VISA session for the
 *           instrument.
 *           The function opens the file in binary mode.
 *
 *****************************************************************************/
ViStatus Rs_ReadToFile (ViSession io,
                        ViConstString filename,
                        ViInt32 maxBytesToRead,
                        ViInt32 fileAction,
                        ViInt32 *totalBytesWritten)
{
    ViStatus    error               = VI_SUCCESS;
    ViUInt32    bytesReadInstr      = 0,
                readBytes           = (ViUInt32) maxBytesToRead,
                bytesWrittenFile    = 0;
    FILE        *targetFile         = NULL;
    ViByte*     buffer = NULL;

    if (totalBytesWritten)
        *totalBytesWritten = 0L;

    if ((targetFile = fopen (filename, (fileAction == RS_VAL_APPEND) ? "ab" : "wb")) == NULL)
        return RS_ERROR_CANNOT_OPEN_FILE;

  checkAlloc (buffer = (ViByte*) malloc(RS_IO_BUFFER_SIZE));

    memset ((void *) buffer, 0, (size_t) RS_IO_BUFFER_SIZE);

    for (;;)
        {
        if (readBytes > RS_IO_BUFFER_SIZE)
            error = viRead (io, buffer, RS_IO_BUFFER_SIZE, &bytesReadInstr);
        else
            error = viRead (io, buffer, readBytes, &bytesReadInstr);

        bytesWrittenFile = (ViUInt32) fwrite (buffer, sizeof (ViByte), (size_t)bytesReadInstr, targetFile);

        if (totalBytesWritten)
            *totalBytesWritten += bytesWrittenFile;
        if (bytesWrittenFile < bytesReadInstr)
            error = RS_ERROR_WRITING_FILE;

        if ((readBytes <= RS_IO_BUFFER_SIZE) || (error <= 0) || (error == VI_SUCCESS_TERM_CHAR))
            break;

        readBytes -= RS_IO_BUFFER_SIZE;
        }

Error:
    (void) fclose (targetFile);

  if (buffer) free (buffer);

    return error;
}

/*****************************************************************************
 * Function: Rs_WriteFromFile
 * Purpose:  This function reads data from a file you specify and writes it
 *           to an instrument using VISA I/O. Use this function internally in
 *           your instrument driver.
 *           The function assumes that the RS_ATTR_IO_SESSION attribute for
 *           the RS session you specify holds a valid VISA session for the
 *           instrument.
 *
 *****************************************************************************/
ViStatus Rs_WriteFromFile (ViSession io,
                           ViConstString filename,
                           ViInt32 maxBytesToWrite,
                           ViInt32 byteOffset,
                           ViInt32 *totalBytesWritten)
{
    ViStatus    error           = VI_SUCCESS;
    ViBoolean   sendEnd         = VI_FALSE;
    ViUInt32    bytesRead       = 0,
                writeBytes      = (ViUInt32) maxBytesToWrite,
                bytesWritten    = 0;
    FILE        *sourceFile;
    ViByte*     buffer = NULL;

    if (totalBytesWritten)
        *totalBytesWritten = 0L;
    if ((sourceFile = fopen (filename, "rb")) == NULL)
        return RS_ERROR_CANNOT_OPEN_FILE;

    if (fseek (sourceFile, byteOffset, SEEK_SET) != VI_SUCCESS)
        return RS_ERROR_READING_FILE;

  checkAlloc (buffer = (ViByte*) malloc(RS_IO_BUFFER_SIZE));
    memset ((void *) buffer, 0, (size_t) RS_IO_BUFFER_SIZE);

    while (feof (sourceFile) == 0)
        {
        bytesRead = (ViUInt32) fread (buffer, sizeof (ViByte), (size_t) RS_IO_BUFFER_SIZE, sourceFile);
        if ((writeBytes > RS_IO_BUFFER_SIZE) && (bytesRead == RS_IO_BUFFER_SIZE))
            {
            (void) viGetAttribute (io, VI_ATTR_SEND_END_EN, &sendEnd);
            (void) viSetAttribute (io, VI_ATTR_SEND_END_EN, VI_FALSE);
            error = viWrite (io, buffer, RS_IO_BUFFER_SIZE, &bytesWritten);
            (void) viSetAttribute (io, VI_ATTR_SEND_END_EN, sendEnd);
            writeBytes -= RS_IO_BUFFER_SIZE;
            if (totalBytesWritten)
                *totalBytesWritten += bytesWritten;
            if (error < 0)
                break;
            }
        else
            {
            error = viWrite (io, buffer, ((bytesRead < writeBytes) ? bytesRead : writeBytes), &bytesWritten);
            if (totalBytesWritten)
                *totalBytesWritten += bytesWritten;
            break;
            }
        }

Error:  
    (void) fclose (sourceFile);
  if (buffer) free (buffer);

    return error;
}

/*****************************************************************************
 *- Global Attribute callbacks ----------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: Rs_ReadCallback
 * Purpose:  This function sets the read callback function for the ViInt32,
 *           ViReal64, ViBoolean, ViString and ViSession attribute. The RS
 *           Library calls the read callback function when you request
 *           the current value of the attribute.
 *
 *****************************************************************************/
ViStatus Rs_ReadCallback (ViSession instrSession,
                          ViConstString repCapName,
                          ViAttr attributeId,
                          ViInt32 bufSize,
                          void *value)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     count           = (ViUInt32) bufSize;
    ViInt32     idx             = 0;
    ViChar      *cmd            = VI_NULL;
    ViChar      buffer[RS_MAX_MESSAGE_BUF_SIZE] = "";
  ViChar      format_string[20] = "";
    //ViUInt32    n               = 0;  
    //size_t      max_cmd_size    = 0;
  
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* If no command available, exit the function */
    if (sessionProperties -> attr[idx].command == VI_NULL)
        return VI_SUCCESS;
    
    /* Build the command string */
    viCheckErr (Rs_BuildCommandString (instrSession, attributeId, idx, repCapName, &cmd));

    /* --- If the range table for the attribute exists, revert 'command string'
       back to the 'discreteOrMinValue' and return it as attribute value. --- */

    /* Range Table Callback */
    if (sessionProperties -> attr[idx].rangeTableCallback)
    {                                                          
        viCheckErr ((sessionProperties -> attr[idx].rangeTableCallback)(instrSession, repCapName, attributeId, &(sessionProperties -> attr[idx].rangeTable)));
    }
    
    if (sessionProperties -> attr[idx].rangeTable)
        if (sessionProperties -> attr[idx].rangeTable -> type == RS_VAL_DISCRETE)
            {
            ViUInt16    i = 0;
            ViChar      *p2string;
            ViInt32     found;

            buffer[0] = '\0';
            count = RS_MAX_MESSAGE_BUF_SIZE;

            if ((sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES) != 0)
            {
                ViInt32             opc_callback_idx    = 0;
                ViAddr              value_address       = 0;
                Rs_OPCCallbackPtr   p2function;
                checkErr (Rs_ClearBeforeRead (instrSession));
                    
                if (sessionProperties -> attr[idx].access==RS_VAL_READ_ONLY)
                    sprintf (buffer, "%s;*OPC\n", cmd);
                else
                    sprintf (buffer, "%s?;*OPC\n", cmd);
                viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen(buffer), NULL));
                viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPC_CALLBACK, &opc_callback_idx));
                value_address = *(ViAddr *)sessionProperties -> attr[opc_callback_idx].p2value;
                p2function = (Rs_OPCCallbackPtr)value_address;
                viCheckErr (p2function(instrSession));
            }
            else
            {
                if (sessionProperties -> attr[idx].access==RS_VAL_READ_ONLY)
                    sprintf(buffer, "%s\n", cmd);
                else
                    sprintf(buffer, "%s?\n", cmd);
                viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
            }
            viCheckErr (viRead (instrSession, (ViBuf) buffer, RS_MAX_MESSAGE_BUF_SIZE, NULL));
            if (sscanf (buffer, "%[^\r\n]", buffer) != 1)
        checkErr (RS_ERROR_INVALID_VALUE);

            /* Go over range table values and check if the command string is present */
            do
                {
                p2string = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdString;

                if (sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdValue == RS_RANGE_TABLE_END_VALUE)
                {
                    viCheckErr (RS_ERROR_INVALID_VALUE);
                }
#ifdef RS_LONG_RESPONSE            
                if ((strlen (p2string) <= 3) || (strlen (buffer) > 4))
                    found = strcmp (buffer,p2string);
                else
                    found = strncmp (buffer, p2string, strlen (p2string));
#else
                found = strcmp (buffer,p2string);
#endif
                if (found == 0)
                    break;

                i++;

                } while (i != 0);

            /* Return value from range table */
            switch (sessionProperties -> attr[idx].dataType)
            {
                case RS_VAL_INT32:
                    *(ViInt32 *)value = (ViInt32) sessionProperties -> attr[idx].rangeTable -> rangeValues[i].discreteOrMinValue;
                    break;
                case RS_VAL_REAL64:
                    *(ViReal64 *)value = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].discreteOrMinValue;
                    break;
                case RS_VAL_STRING:
                case RS_VAL_BOOLEAN:
                case RS_VAL_ADDR:
                case RS_VAL_SESSION:
                case RS_VAL_EVENT:
                case RS_VAL_UNKNOWN_TYPE:
                default:
                    viCheckErr (RS_ERROR_INVALID_TYPE);
            }
            
            goto Error;
            }
            if (sessionProperties -> attr[idx].access==RS_VAL_READ_ONLY)
            {
                 if ((sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES) != 0)
                {
                    ViInt32             opc_callback_idx    = 0;
                    ViAddr              value_address       = 0;
                    Rs_OPCCallbackPtr   p2function;
                    
                    checkErr (Rs_ClearBeforeRead (instrSession));
                        
                    sprintf(buffer, "%s;*OPC\n", cmd);
                    viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
                    viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPC_CALLBACK, &opc_callback_idx));
                        value_address = *(ViAddr *)sessionProperties -> attr[opc_callback_idx].p2value;
                        p2function = (Rs_OPCCallbackPtr)value_address;
                    viCheckErr (p2function(instrSession));
                }
                else
                {
                    sprintf(buffer, "%s\n", cmd);
                    viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
                }   
            }
            else
            {
                if ((sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES) != 0)
                {
                    ViInt32             opc_callback_idx    = 0;
                    ViAddr              value_address       = 0;
                    Rs_OPCCallbackPtr   p2function;
                    
                    checkErr (Rs_ClearBeforeRead (instrSession));
                        
                    sprintf(buffer, "%s?;*OPC\n", cmd);
                    viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
                    viCheckErr (Rs_GetAttributeIndex (instrSession, RS_ATTR_OPC_CALLBACK, &opc_callback_idx));
                        value_address = *(ViAddr *)sessionProperties -> attr[opc_callback_idx].p2value;
                        p2function = (Rs_OPCCallbackPtr)value_address;
                    viCheckErr (p2function(instrSession));
                }
                else
                {
                    sprintf(buffer, "%s?\n", cmd);
                    viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
                }   
            }   
        viCheckErr (viRead (instrSession, (ViBuf) buffer, RS_MAX_MESSAGE_BUF_SIZE, NULL));
        switch (sessionProperties -> attr[idx].dataType)
        {
            case RS_VAL_INT32:
        *((ViInt32*)value) = atol (buffer);
                break;
            case RS_VAL_INT64:
                if (sscanf(buffer, "%I64d", (ViInt64*) value) != 1)
          checkErr (RS_ERROR_INVALID_VALUE);
                break;
            case RS_VAL_REAL64:
        *((ViReal64*)value) = atof (buffer);
                break;
            case RS_VAL_STRING:
                if (strspn (buffer, "\"") != 0)
          strcpy (format_string, "%*1[\"]%[^\"]");
        else if (strspn (buffer, "'") != 0)
          strcpy (format_string, "%*1[']%[^']");
        else
          strcpy (format_string, "%[^\r\n]");
        
        if (sscanf(buffer, format_string, value) != 1)
                    memset (value,0,1);
                break;
            case RS_VAL_BOOLEAN:
                if (strncmp (buffer, "ON", 2) == 0)
                        *(ViBoolean*)value = 1;
                    else
                    {
                    if (strncmp (buffer, "OFF", 3) == 0)
                            *(ViBoolean*)value = 0;
                        else
                        (void) sscanf(buffer, "%hu", (ViBoolean*) value);
                }
                break;
            default:
                viCheckErr (RS_ERROR_INVALID_TYPE);
        }
            

Error:

    if (cmd)
        free (cmd);

    return error;
}

/*****************************************************************************
 * Function: Rs_WriteCallback
 * Purpose:  This function sets the write callback function for the ViInt32,
 *           ViReal64, ViBoolean and ViString attribute. The RS Library calls
 *           the write callback function when you request the current value of
 *           the attribute.
 *
 *****************************************************************************/
ViStatus Rs_WriteCallback (ViSession instrSession,
                           ViConstString repCapName,
                           ViAttr attributeId,
                           void *value)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViChar      buffer [RS_MAX_MESSAGE_BUF_SIZE] = "";
    ViStatus    error               = VI_SUCCESS;
    //ViInt32     n                   = 0;
    //size_t      max_cmd_size        = 0;
    ViInt32     idx                 = 0;
    ViChar      *cmd                = VI_NULL;
    ViChar      *p2buffer = buffer;

    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* If no command available, exit the function */
    if (sessionProperties -> attr[idx].command == VI_NULL)
        return VI_SUCCESS;

    /* Build the command string */
    viCheckErr (Rs_BuildCommandString (instrSession, attributeId, idx, repCapName, &cmd));  

    if (sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES)   
    {
        checkErr (Rs_ClearBeforeRead (instrSession));
        p2buffer += sprintf (p2buffer, "*CLS;");   
    }
    /* --- If the range table for the attribute exists, pass 'command string' or
       'discreteOrMinValue' instead of attribute value. --- */

    /* Range Table Callback */
    if (sessionProperties -> attr[idx].rangeTableCallback)
    {                                                          
        viCheckErr ((sessionProperties -> attr[idx].rangeTableCallback)(instrSession, repCapName, attributeId, &(sessionProperties -> attr[idx].rangeTable)));
    }
    
    if (sessionProperties -> attr[idx].rangeTable)
    {
        if (sessionProperties -> attr[idx].rangeTable -> type == RS_VAL_DISCRETE)
            {
            ViUInt16    i = 0;
            ViChar      *p2string;
            ViReal64    *p2discrete;
            ViInt32     data_type = sessionProperties -> attr[idx].dataType;
            ViReal64    precision = sessionProperties -> attr[idx].comparePrecision;

            precision = (precision < DBL_MIN) ? DBL_MIN : precision;

            /* Allowed data types are only ViInt32 or ViReal64 */
            switch (data_type)
                {
                case RS_VAL_INT32:
                case RS_VAL_REAL64:
                    /* Valid data types */
                    break;
                case RS_VAL_STRING:
                case RS_VAL_BOOLEAN:
                case RS_VAL_EVENT:
                case RS_VAL_ADDR:
                case RS_VAL_SESSION:
                case RS_VAL_UNKNOWN_TYPE:
                default:
                    viCheckErr (RS_ERROR_INVALID_TYPE);
                }

            /* Go over range table values and find appropriate command string for passed
               attribute value. For floating point values use predefined attribute precision. */
            do
                {
                p2discrete = &sessionProperties -> attr[idx].rangeTable -> rangeValues[i].discreteOrMinValue;
                p2string = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdString;

                if (sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdValue == RS_RANGE_TABLE_END_VALUE)
                    viCheckErr(RS_ERROR_INVALID_VALUE);

                if (data_type == RS_VAL_INT32)
                    if (fabs(*p2discrete - *(ViInt32 *)value) <= DBL_MIN)
                        {
                        break;
                        }

                if (data_type == RS_VAL_REAL64)
                    if (fabs(*p2discrete - *(ViReal64 *)value) <= precision)
                        {
                        break;
                        }

                i++;

                } while (i != 0);
    /* Check Wait to continue and Wait for OPC after writes flags */
            p2buffer+= sprintf(p2buffer, "%s %s", cmd, p2string);          
            if (sessionProperties -> attr[idx].flags & RS_VAL_WAIT_TO_CONTINUE)
                strcat (buffer, ";*WAI");

            if (sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES)
                strcat (buffer, ";*OPC");

            strcat (buffer, "\n");
                
            viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
            goto Error; /* Exit the function */
            }
    }            
    /* --- Attribute data type is used for VISA I/O --- */
    /* Check Wait for OPC after writes flag */
        switch (sessionProperties -> attr[idx].dataType)
            {
            case RS_VAL_INT32:
            sprintf(buffer, "%s %ld", cmd, *(ViInt32 *)value);
                break;
            case RS_VAL_INT64:
            sprintf(buffer, "%s %I64d", cmd, *(ViInt64 *)value);
                break;
            case RS_VAL_REAL64:
              //sprintf(buffer, "%s %.12lf", cmd, *(ViReal64 *)value);
              //Modified to fix CVI bug formating 1.0e+11 to 0:00000.0000
              p2buffer += sprintf(p2buffer, "%s %.12lG", cmd, *(ViReal64 *)value);
                break;
            case RS_VAL_STRING:
              p2buffer += sprintf(p2buffer, "%s \'%s\'", cmd, (ViString) value);
                break;
            case RS_VAL_BOOLEAN:
              p2buffer += sprintf(p2buffer, "%s %s", cmd, (*(ViBoolean *)value == VI_FALSE) ? "OFF" : "ON");
                break;
            case RS_VAL_EVENT:
              p2buffer += sprintf(p2buffer, "%s", cmd);
                break;
            case RS_VAL_ADDR:
            case RS_VAL_SESSION:
            case RS_VAL_UNKNOWN_TYPE:
            default:
                viCheckErr (RS_ERROR_INVALID_TYPE);
            }
     if (sessionProperties -> attr[idx].flags & RS_VAL_WAIT_TO_CONTINUE)
       strcat (buffer, ";*WAI");    
   
   if (sessionProperties -> attr[idx].flags & RS_VAL_WAIT_FOR_OPC_AFTER_WRITES)
        strcat (buffer,";*OPC");
     
     strcat (buffer,"\n");
    
     viCheckErr (viWrite (instrSession, (ViBuf) buffer, (ViUInt32) strlen (buffer), NULL));
    
Error:
    if (cmd)
        free (cmd);

    return error;
}

/*****************************************************************************
 * Function: Rs_CheckCallback
 * Purpose:  This function performs the default actions for checking the
 *           validity of a ViInt32 or ViReal64 attribute value.
 *
 *****************************************************************************/
ViStatus Rs_CheckCallback (ViSession instrSession,
                           ViConstString repCapName,
                           ViAttr attributeId,
                           void *value)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    void        *coercedValue   = VI_NULL;
    
    
                                             
    /* Get the attribute index */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));

    /* Default range table callback? */
    if (sessionProperties -> attr[idx].rangeTableCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].rangeTableCallback)(instrSession, repCapName, attributeId, &(sessionProperties -> attr[idx].rangeTable)));
        }
 
    /* Proceed only when the range table exists */
    if (sessionProperties -> attr[idx].rangeTable)
    {
        viCheckErr (Rs_RangeTableCallback (instrSession, repCapName, attributeId, sessionProperties -> attr[idx].rangeTable));
       
        /* Resolve range tables according the its type */
        switch (sessionProperties -> attr[idx].rangeTable -> type)
            {

            case RS_VAL_RANGED: /*--------------------------------------------*/

                {
                /* Only first RsRangeTableEntry from the range table plays the role */
                
                ViReal64    *p2min = &sessionProperties -> attr[idx].rangeTable -> rangeValues[0].discreteOrMinValue,
                            *p2max = &sessionProperties -> attr[idx].rangeTable -> rangeValues[0].maxValue;

                if (!p2min || !p2max)
                    return RS_ERROR_INVALID_RANGE_TABLE;

                switch (sessionProperties -> attr[idx].dataType)
                    {
                    case RS_VAL_INT32:
                        
                        return ((*(ViInt32 *)value < (ViInt32) (*p2min) || *(ViInt32 *)value > (ViInt32)(*p2max)) ? RS_ERROR_INVALID_VALUE : error);

                    case RS_VAL_INT64:
                        
                        return ((*(ViInt64 *)value < (ViInt64) (*p2min) || *(ViInt64 *)value > (ViInt64)(*p2max)) ? RS_ERROR_INVALID_VALUE : error);

          case RS_VAL_REAL64:

                        return ((*(ViReal64 *)value < *p2min || *(ViReal64 *)value > *p2max) ? RS_ERROR_INVALID_VALUE : error);

                    default:
                        /* No action */
                        break;
                    }
                }

                break;

            case RS_VAL_DISCRETE: /*------------------------------------------*/

                {
                ViUInt16    i = 0;
                ViReal64    *p2discrete;
                ViInt32     data_type = sessionProperties -> attr[idx].dataType;
                ViReal64    precision = sessionProperties -> attr[idx].comparePrecision;

                precision = (precision < DBL_MIN) ? DBL_MIN : precision;

                do
                    {
                    p2discrete = &sessionProperties -> attr[idx].rangeTable -> rangeValues[i].discreteOrMinValue;

                    if (sessionProperties -> attr[idx].rangeTable -> rangeValues[i].cmdValue == RS_RANGE_TABLE_END_VALUE)
                        return RS_ERROR_INVALID_VALUE;

                    if (data_type == RS_VAL_INT32)
                        if (fabs(*p2discrete - *(ViInt32 *)value) <= DBL_MIN)
                            break;

                    if (data_type == RS_VAL_REAL64)
                        if (fabs(*p2discrete - *(ViReal64 *)value) <= precision)
                            break;

                    i++;

                    } while (i != 0);
                }

                break;

            case RS_VAL_COERCED: /*-------------------------------------------*/

                if ((sessionProperties -> attr[idx].flags & RS_VAL_COERCEABLE_ONLY_BY_INSTR) == 0)
                    {
                    checkAlloc (coercedValue = malloc (sizeof (ViReal64)));

                    viCheckErr (Rs_CoerceCallback (instrSession, repCapName, attributeId, value, coercedValue));
                    }

                break;

            default:
                viCheckErr (RS_ERROR_INVALID_RANGE_TABLE);
                break;
            }
        }

Error:

    if (coercedValue)
        free (coercedValue);

    return error;
}

/*****************************************************************************
 * Function: Rs_CompareAttr_Callback
 * Purpose:  This function performs the default compare actions for a ViReal64
 *           attribute. The RS engine invokes the compare callback to compare
 *           the cache values it obtains from the instrument against new values
 *           you set the attribute to. If the compare callback determines that
 *           the two values are equal, the RS engine does not call the write
 *           callback for the attribute.
 *
 *****************************************************************************/
ViStatus Rs_CompareAttr_Callback (/*@unused@*/ViSession vi,
                                  /*@unused@*/ViConstString repCapName,
                                  /*@unused@*/ViAttr attributeId,
                                  /*@unused@*/void *coercedNewValue,
                                  /*@unused@*/void *cacheValue,
                                  /*@unused@*/void *result)
{
    // Currently not implemented.

    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: Rs_CoerceCallback
 * Purpose:  This function performs the default actions for coercing a value
 *           for the ViReal64 or ViInt32 attribute.
 *
 *****************************************************************************/
ViStatus Rs_CoerceCallback (ViSession instrSession,
                            ViConstString repCapName,
                            ViAttr attributeId,
                            void *value,
                            void *coercedValue)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (instrSession);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;

    /* Get the attribute index */
    viCheckErr (Rs_GetAttributeIndex (instrSession, attributeId, &idx));
        
    /* Proceed only when the range table exists */
    if (sessionProperties -> attr[idx].rangeTable)
        {
            /* Default range table callback? */
        if (sessionProperties -> attr[idx].rangeTableCallback)
        {
        viCheckErr ((sessionProperties -> attr[idx].rangeTableCallback)(instrSession, repCapName, attributeId, &(sessionProperties -> attr[idx].rangeTable)));
        }
        else
        {
        viCheckErr (Rs_RangeTableCallback (instrSession, repCapName, attributeId, sessionProperties -> attr[idx].rangeTable));
        }
         
        

        /* Default coerce callback? */
        if (sessionProperties -> attr[idx].coerceCallback)
            {
            viCheckErr ((sessionProperties -> attr[idx].coerceCallback)(instrSession, repCapName, attributeId, value, coercedValue));
            }
        else
            {
            
            /* Coerce the value if the table type is COERCED */
            if (sessionProperties -> attr[idx].rangeTable -> type == RS_VAL_COERCED)
                {
                
                 /* Coerce entered value to the nearest value from the range table.
                    Data must be in ascending order! */

                ViInt16     i               = 0;
                ViInt32     data_type       = sessionProperties -> attr[idx].dataType;
                ViReal64    copy_of_value   = 0.0,
                            precision       = sessionProperties -> attr[idx].comparePrecision;

                /* precision = (precision < DBL_MIN) ? DBL_MIN : precision; */
                precision = DBL_MIN; /* Use rather lowest possible precision value to be accurate when coerced values are at the edge */

                switch (data_type)
                    {
                    case RS_VAL_INT32:
                        copy_of_value = (ViReal64)(*(ViInt32 *)value);
                        break;
                    case RS_VAL_INT64:
                        copy_of_value = (ViReal64)(*(ViInt64 *)value);
                        break;
                    case RS_VAL_REAL64:
                        copy_of_value = *(ViReal64 *)value;
                        break;
                    default:
                        viCheckErr (RS_ERROR_INVALID_TYPE);
                    }

                /* Coerce the value ... */
                while (
             (copy_of_value > sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue) &&
                       (fabs (sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue) > precision)
             )
                    {
            if (sessionProperties -> attr[idx].rangeTable -> rangeValues[i+1].cmdValue == RS_RANGE_TABLE_END_VALUE)
            {
              break;
            }
            else
                    {
                    i++;
                    }
                    }

                if ((copy_of_value > precision) && (i > 0))
                    {
                    if (fabs ((copy_of_value - sessionProperties -> attr[idx].rangeTable -> rangeValues[i - 1].coercedValue) / 2) <
                        fabs ((copy_of_value - sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue) / 2))
                        {
                        i--;
                        copy_of_value = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue;
                        }
                    else
                        {
                        copy_of_value = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue;
                        }
                    }
                else
                    {
                    i = 0;
                    copy_of_value = sessionProperties -> attr[idx].rangeTable -> rangeValues[i].coercedValue;
                    }

                switch (data_type)
                    {
                    case RS_VAL_INT32:
                        *(ViInt32 *)coercedValue = (ViInt32) copy_of_value;
                        break;
                    case RS_VAL_INT64:
                        *(ViInt64 *)coercedValue = (ViInt64) copy_of_value;
                        break;
                    case RS_VAL_REAL64:
                        *(ViReal64 *)coercedValue = copy_of_value;
                        break;
                    default:
                        viCheckErr (RS_ERROR_INVALID_TYPE);
                    }

                }
            }
        }

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_RangeTableCallback
 * Purpose:  This function performs if the default range table or user defined
 *           range table for the ViReal64 or ViInt32 attribute is used.
 *
 *****************************************************************************/
ViStatus Rs_RangeTableCallback (ViSession io,
                                /*@unused@*/ViConstString repCapName,
                                ViAttr attributeId,
                                RsRangeTablePtr rangeTablePtr)
{
    RsSessionPropertiesPtr  sessionProperties = Rs_ViSession (io);
    ViStatus    error           = VI_SUCCESS;
    ViInt32     idx             = 0;
    ViSession   instrSession    = io; /* used due to checking macro */

    /* Update range table ptr only when available */
    if (rangeTablePtr)
        {
        viCheckErr (Rs_GetAttributeIndex (io, attributeId, &idx));

        sessionProperties -> attr[idx].rangeTable = rangeTablePtr;
        }
    else
        checkErr (RS_ERROR_NO_RANGE_TABLE);

Error:

    return error;
}

/*****************************************************************************
 * Function: Rs_DisposeRepCapTable
 * Purpose:  This function disposes a repeated capability table for an RS
 *           session.
 *****************************************************************************/
ViStatus Rs_DisposeRepCapTable (RsSessionPropertiesPtr sessionProperties)
{
    ViStatus    error = VI_SUCCESS;
    ViUInt32    i = 0;

    if (sessionProperties -> repCapTable)
    {
        for (i = 0; i < sessionProperties->numberOfRepCaps; i++)
        {
            if (sessionProperties -> repCapTable[i].cmdValues)
                free (sessionProperties -> repCapTable[i].cmdValues);
            if (sessionProperties -> repCapTable[i].repCapName)
                free (sessionProperties -> repCapTable[i].repCapName);
            if (sessionProperties -> repCapTable[i].repCapNameId)
                free (sessionProperties -> repCapTable[i].repCapNameId);
        }
    
        free (sessionProperties -> repCapTable);
        sessionProperties -> repCapTable = NULL;
    }
    return error;
}


/*****************************************************************************
 * Function: Rs_BuildCommandString
 * Purpose:  This function buidls the command string, replaces repCap strings
 *
 *           Note: cmd is allocated in function! Don´t forget dealocate it!
 *****************************************************************************/
ViStatus Rs_BuildCommandString (ViSession instrSession, ViAttr attributeId, 
                                ViInt32 idx, ViConstString repCapName, 
                                ViChar **cmd)
{
    RsSessionPropertiesPtr sessionProperties = Rs_ViSession (instrSession); 
    ViStatus    error           = VI_SUCCESS;  
    ViChar      single_repCapName[RS_MAX_MESSAGE_BUF_SIZE] = "",
                single_repCapNameId[RS_MAX_MESSAGE_BUF_SIZE] = "",
                tmp[RS_MAX_MESSAGE_BUF_SIZE] = "",
                *p2cmd = sessionProperties -> attr[idx].command;
    ViUInt32    index = 0, i=0;
    ViChar*     repCapNames = NULL;
    size_t      max_cmd_size    = 0;
    ViInt32     n;
  ViChar*     old_cmd = NULL;
  ViChar*     command_value = NULL;
    
    /* Build the command string */
    max_cmd_size = strlen (sessionProperties -> attr[idx].command);

    viCheckAlloc (*cmd = (ViChar*) malloc (++max_cmd_size));
  viCheckAlloc (repCapNames = (ViChar*) calloc (RS_MAX_MESSAGE_BUF_SIZE * 3, 1));
  viCheckAlloc (command_value = (ViChar*) calloc (RS_MAX_MESSAGE_BUF_SIZE, 1));

    *cmd[0] = '\0';

    if (sessionProperties -> attr[idx].usercaps == VI_TRUE)
        {
        /* Repeated Capabilities */
               

            for (index = 0; index < RS_MAX_ATTR_RCAPS; index++)  
            {
                /* Scan repCap from command*/
                single_repCapNameId[0] = '\0';
                if (*p2cmd != '{')
                    n = (ViUInt32) sscanf (p2cmd, "%[^{]{%[^}]}", tmp, single_repCapNameId);
                else
                {
                    n = (ViUInt32) sscanf (p2cmd, "{%[^}]}", single_repCapNameId);
                    tmp[0] = '\0';
                }

                if (single_repCapNameId[0] == '\0')
                    break;
                p2cmd = strchr(p2cmd, '}') + 1;
                viCheckErr (Rs_GetAttributeRepCapName (instrSession, attributeId, single_repCapNameId, repCapNames));
                for (i = 0; i < strlen (repCapNames); i++) 
                {
                    if ((error = Rs_GetTokenAtIndex ((ViChar *)repCapNames, ",", i, single_repCapName, RS_MAX_MESSAGE_BUF_SIZE)) != VI_SUCCESS)
                    {
                        checkErr (RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED);
                        break;
                    }
                    if ((repCapName == NULL) || (strlen (repCapName) == 0))
                    {
                        i = 0;
                        break;
                    }
                    else
                    if (Rs_GetIndexOfToken ((ViChar *)repCapName, ",", &i ,single_repCapName) == VI_SUCCESS)
                        break;
                }
                //Only if an error in database occures - bad attribute ID in command
                if (index == RS_MAX_ATTR_RCAPS)
                {
                    checkErr (RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED);
                }
                viCheckErr (Rs_GetRepCapCmdValue (instrSession, attributeId, single_repCapNameId, single_repCapName, command_value));
                max_cmd_size += strlen (command_value);
        old_cmd = *cmd;
        *cmd = (ViChar*) realloc (*cmd, max_cmd_size);
        if (*cmd == NULL)
        {
          free (old_cmd);
          viCheckAlloc (0);
        }
                /* Build the command */
                strcat (*cmd, tmp);
                strcat (*cmd, command_value);
            }
        //Add rest of command
        strcat (*cmd, p2cmd);
        }
    else
        strcpy (*cmd, sessionProperties -> attr[idx].command);
    
Error:
  if (repCapNames) free (repCapNames);
  if (command_value) free (command_value);
    return error;   
}   

/*===========================================================================*/
/* Function: Clear STB Before Read                                           */
/* Purpose:  This is a utility function which clears error and message queue */
/*           before starting a query                                         */
/*===========================================================================*/
ViStatus Rs_ClearBeforeRead (ViSession instrSession)
{
    ViStatus    error = VI_SUCCESS; 
    ViInt16     response = 0;
    ViChar      garbage[10];

  checkErr (viQueryf (instrSession, "*STB?\n", "%hd", &response));
    
    while (response)
    {
         /* Message available */
        if (response & 0x10)
            viRead (instrSession, (ViBuf) garbage, 10, VI_NULL);
    
        /* Operation complete */
    if (response & 0x20)
        {
            ViInt32 error;
            checkErr(viQueryf(instrSession, "*ESR?\n", "%ld", &error));
        }

    /* Error queue not empty */
    if (response & 0x4)
        {
            checkErr(viQueryf(instrSession, ":SYST:ERR?\n", "%*[^\r\n]"));
        }
        
        checkErr (viQueryf (instrSession, "*STB?\n", "%hd", &response));
    }
Error:
    return error;
}

/// HIFN Document your function here.
/// HIFN You may use multiple lines for documentation.
/// HIRET Document return value here.
/// HIRET You may use multiple lines for documentation.
/// HIPAR str/Document parameter here.
/// HIPAR delim/Document parameter here.
/// HIPAR bufferSize/Document parameter here.
/// HIPAR array/Document parameter here.
/// HIPAR returnCount/Document parameter here.
ViStatus Rs_SpreadsheetStringToDblArray (ViString str, ViString delim, ViUInt32 bufferSize, ViReal64 array[], ViUInt32* returnCount)
{
	ViChar* p2buf = NULL;
	ViInt32 i = 0;
	
	if (str == NULL || delim == NULL || array == NULL)
		return RS_ERROR_NULL_POINTER;
	
	p2buf = strtok (str, delim);
	if (p2buf == NULL)
		return RS_ERROR_UNEXPECTED_RESPONSE;
	
	do
	{
		if (bufferSize < i)
			return RS_ERROR_INDEX_IS_TOO_HIGH;
		else
			array[i++] = atof (p2buf);
		p2buf = strtok (NULL, delim);
			
	} while (p2buf);
	
	if (returnCount) *returnCount = i;

	return VI_SUCCESS;
}
