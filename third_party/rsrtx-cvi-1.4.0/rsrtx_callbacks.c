/*****************************************************************************
 *  Rohde&Schwarz RTM20xx Digital Oscilloscope instrument driver
 *  Callbacks
 *
 *  Original Release: December 2013
 *  By: Jiri Kominek
 *
 *  Should you have any technical questions please contact the hotline of
 *  Rohde & Schwarz Vertriebs-GmbH Rohde & Schwarz Support Center
 *
 *  e-mail: CustomerSupport@rohde-schwarz.com
 *

 *****************************************************************************/

#include "rsrtx.h"
#include "rsrtx_utility.h"
#include <stdlib.h>

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
 * Function: rsrtx_doubleQuotedString_ReadCallback
 * Purpose:  Obsolete, the functionality is done by the standard RsCore_ReadCallback
 *****************************************************************************/
ViStatus rsrtx_doubleQuotedString_ReadCallback(ViSession          instrSession,
                                               ViConstString      repCapName,
                                               RsCoreAttributePtr attr)
{
	return RsCore_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
 * Function: rsrtx_doubleQuotedString_WriteCallback
 * Purpose:  Writes string with apostrophes
 *****************************************************************************/
ViStatus rsrtx_doubleQuotedString_WriteCallback(ViSession          instrSession,
                                                ViConstString      repCapName,
                                                RsCoreAttributePtr attr,
                                                void*              value)
{
	return RsCore_SpecialCallback_SurroundParamWrite(instrSession, repCapName, attr, " \"", value, "\"");
}

/*****************************************************************************
 * Function: rsrtx_doubleQuotedStringInt_WriteCallback
 * Purpose:  Writes value with double quotes
 *****************************************************************************/
ViStatus rsrtx_doubleQuotedStringInt_WriteCallback(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr,
                                                   void*              value)
{
	return RsCore_SpecialCallback_SurroundParamWrite(instrSession, repCapName, attr, " \"", value, "\"");
}


/*****************************************************************************
 * Function: rsrtx_doubleQuotedStringInt_ReadCallback
 * Purpose:  This function overrides standard calback funtion. Returns value
 *           from cache
 *****************************************************************************/
ViStatus rsrtx_doubleQuotedStringInt_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	return RsCore_SpecialCallback_AnyQuotedParamRead(instrSession, repCapName, attr);
}

/*****************************************************************************
 * Function: rsrtx_PatternCondition_ReadCallback
 * Purpose:  Boolean callback for converting "TRUE" or "FALSE" to boolean
 *****************************************************************************/
 ViStatus rsrtx_PatternCondition_ReadCallback(ViSession          instrSession,
                                             ViConstString      repCapName,
                                             RsCoreAttributePtr attr)
{
	 ViStatus error = VI_SUCCESS;

	 if (attr->dataType != RS_VAL_BOOLEAN)
	 {
		 checkErr(RsCore_GenerateInvalidDataTypeError(instrSession, attr->dataType, "Only Boolean attributes are supported"));
	 }

	 RsCore_SpecialCallback_AnyQuotedParamRead(instrSession, repCapName, attr);

Error:
	 return error;
}

/*****************************************************************************
 * Function: rsrtx_PatternCondition_WriteCallback
 * Purpose:  Boolean callback for converting boolean value to "TRUE" or "FALSE" parameter
 *****************************************************************************/
ViStatus rsrtx_PatternCondition_WriteCallback(ViSession          instrSession,
                                              ViConstString      repCapName,
                                              RsCoreAttributePtr attr,
                                              void*              value)
{
	ViStatus error = VI_SUCCESS;
	ViString cmd = NULL;

	if (attr->dataType != RS_VAL_BOOLEAN)
	{
		checkErr(RsCore_GenerateInvalidDataTypeError(instrSession, attr->dataType, "Only Boolean attributes are supported"));
	}

	// If no command is available, exit the function
	if (isNullOrEmpty(attr->command))
		goto Error;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &cmd));
	checkErr(RsCore_StrCatDynamicString(instrSession, &cmd, " \"", (*(ViBoolean*)value == VI_FALSE) ? "FALSE" : "TRUE", "\""));
	checkErr(RsCore_WriteAttributeCommand(instrSession, attr, cmd));

Error:
	if (cmd)
		free(cmd);

	return error;
}

/*****************************************************************************
 * Function: rsrtx_singleStatisticalValue_ReadCallback
 * Purpose:  Appends integer value of RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_INDEX to the query
 *****************************************************************************/
 ViStatus rsrtx_singleStatisticalValue_ReadCallback(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr)
{
    ViStatus error = VI_SUCCESS;
    ViChar*  customCmd = NULL;
    ViInt32  index = 0;

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_AUTOMATIC_MEASUREMENT_RESULT_INDEX, 0, &index));
	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));
	RsCore_StrCatDynamicViInt32(instrSession, &customCmd, "", index, "");
	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
    if (customCmd)
        free (customCmd);

    return error;
}

 /*****************************************************************************
  * Function: rsrtx_I2C_Replace_FrameByte_ReadCallback
  * Purpose:  Replaces <Frame> and <Byte> with numbers in the command string
  *****************************************************************************/
ViStatus rsrtx_I2C_Replace_FrameByte_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;
	ViChar   byteString[RS_MAX_MESSAGE_LEN];
	ViInt32  byte = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_I2C_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_I2C_SELECTED_BYTE, 0, &byte));
	snprintf(byteString, RS_MAX_MESSAGE_LEN, _PERCD, byte);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Byte>", byteString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatI2CFrameRepCapBool_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                    ViConstString      repCapName,
                                                    RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameByteRepCapBool_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameByteRepCapInt_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatI2CFrameByteRepCapReal_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_I2C_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
*Function: rsrtx_SPI_Replace_FrameWord_ReadCallback
* Purpose : Replaces <Frame> and <Word> with numbers in the command string
*****************************************************************************/
ViStatus rsrtx_SPI_Replace_FrameWord_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;
	ViChar   wordString[RS_MAX_MESSAGE_LEN];
	ViInt32  word = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_SPI_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_SPI_SELECTED_WORD, 0, &word));
	snprintf(wordString, RS_MAX_MESSAGE_LEN, _PERCD, word);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Word>", wordString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatSPIFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_SPI_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSPIFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_SPI_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSPIFrameWordRepCapInt_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_SPI_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSPIFrameWordRepCapReal_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_SPI_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSPIFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                    ViConstString      repCapName,
                                                    RsCoreAttributePtr attr)
{
	return rsrtx_SPI_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
*Function: rsrtx_UART_Replace_FrameWord_ReadCallback
* Purpose : Replaces <Frame> and <Word> with numbers in the command string
*****************************************************************************/
ViStatus rsrtx_UART_Replace_FrameWord_ReadCallback(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;
	ViChar   wordString[RS_MAX_MESSAGE_LEN];
	ViInt32  word = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_UART_SELECTED_WORD, 0, &word));
	snprintf(wordString, RS_MAX_MESSAGE_LEN, _PERCD, word);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Word>", wordString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatUARTFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_UART_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatUARTFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                      ViConstString      repCapName,
                                                      RsCoreAttributePtr attr)
{
	return rsrtx_UART_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatUARTFrameWordRepCapInt_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_UART_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatUARTFrameWordRepCapReal_ReadCallback(ViSession          instrSession,
                                                          ViConstString      repCapName,
                                                          RsCoreAttributePtr attr)
{
	return rsrtx_UART_Replace_FrameWord_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_LIN_Replace_FrameByte_ReadCallback
* Purpose : Replaces <Frame> and <Byte> with numbers in the command string
*****************************************************************************/
ViStatus rsrtx_LIN_Replace_FrameByte_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;
	ViChar   byteString[RS_MAX_MESSAGE_LEN];
	ViInt32  byte = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_LIN_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_LIN_SELECTED_BYTE, 0, &byte));
	snprintf(byteString, RS_MAX_MESSAGE_LEN, _PERCD, byte);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Byte>", byteString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatLINFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                    ViConstString      repCapName,
                                                    RsCoreAttributePtr attr)
{
	return rsrtx_LIN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatLINFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_LIN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatLINFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_LIN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatLINFrameByteRepCapInt_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_LIN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_CAN_Replace_FrameByte_ReadCallback
* Purpose : Replaces <Frame> and <Byte> with numbers in the command string
*****************************************************************************/
ViStatus rsrtx_CAN_Replace_FrameByte_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;
	ViChar   byteString[RS_MAX_MESSAGE_LEN];
	ViInt32  byte = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_CAN_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_CAN_SELECTED_BYTE, 0, &byte));
	snprintf(byteString, RS_MAX_MESSAGE_LEN, _PERCD, byte);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Byte>", byteString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatCANFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                    ViConstString      repCapName,
                                                    RsCoreAttributePtr attr)
{
	return rsrtx_CAN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatCANFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_CAN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatCANFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_CAN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatCANFrameByteRepCapInt_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_CAN_Replace_FrameByte_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_PARALLEL_Replace_Frame_ReadCallback
* Purpose : Replaces <Frame> with number in the command string
*****************************************************************************/
ViStatus rsrtx_PARALLEL_Replace_Frame_ReadCallback(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PARALLEL_BUS_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatParallelFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_PARALLEL_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatParallelFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                          ViConstString      repCapName,
                                                          RsCoreAttributePtr attr)
{
	return rsrtx_PARALLEL_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatParallelFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                            ViConstString      repCapName,
                                                            RsCoreAttributePtr attr)
{
	return rsrtx_PARALLEL_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_CLOCKED_Replace_Frame_ReadCallback
* Purpose : Replaces <Frame> with number in the command string
*****************************************************************************/
ViStatus rsrtx_CLOCKED_Replace_Frame_ReadCallback(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PARALLEL_BUS_CLOCKED_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatClockedFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_CLOCKED_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatClockedFrameRepCapString_ReadCallback(ViSession          instrSession,
                                                           ViConstString      repCapName,
                                                           RsCoreAttributePtr attr)
{
	return rsrtx_CLOCKED_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatClockedFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_CLOCKED_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_AUDIO_Replace_Frame_ReadCallback
* Purpose : Replaces <Frame> with number in the command string
*****************************************************************************/
ViStatus rsrtx_AUDIO_Replace_Frame_ReadCallback(ViSession          instrSession,
                                                ViConstString      repCapName,
                                                RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   frameString[RS_MAX_MESSAGE_LEN];
	ViInt32  frame = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_AUDIO_SELECTED_FRAME, 0, &frame));
	snprintf(frameString, RS_MAX_MESSAGE_LEN, _PERCD, frame);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Frame>", frameString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatAudioFrameRepCapInt_ReadCallback(ViSession          instrSession,
                                                      ViConstString      repCapName,
                                                      RsCoreAttributePtr attr)
{
	return rsrtx_AUDIO_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

//Replaces <Frame> with number in the command string
ViStatus rsrtx_FormatAudioFrameRepCapReal_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_AUDIO_Replace_Frame_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_MILSTD_Replace_Word_ReadCallback
* Purpose : Replaces <Word> with number in the command string
*****************************************************************************/
ViStatus rsrtx_MILSTD_Replace_Word_ReadCallback(ViSession          instrSession,
                                                ViConstString      repCapName,
                                                RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   wordString[RS_MAX_MESSAGE_LEN];
	ViInt32  word = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_MILSTD_SELECTED_WORD, 0, &word));
	snprintf(wordString, RS_MAX_MESSAGE_LEN, _PERCD, word);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Word>", wordString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatMILSTDWordRepCapString_ReadCallback(ViSession          instrSession,
                                                         ViConstString      repCapName,
                                                         RsCoreAttributePtr attr)
{
	return rsrtx_MILSTD_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatMILSTDWordRepCapInt_ReadCallback(ViSession          instrSession,
                                                      ViConstString      repCapName,
                                                      RsCoreAttributePtr attr)
{
	return rsrtx_MILSTD_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatMILSTDWordRepCapReal_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_MILSTD_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_ARINC_Replace_Word_ReadCallback
* Purpose : Replaces <Word> with number in the command string
*****************************************************************************/
ViStatus rsrtx_ARINC_Replace_Word_ReadCallback(ViSession          instrSession,
                                               ViConstString      repCapName,
                                               RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   wordString[RS_MAX_MESSAGE_LEN];
	ViInt32  word = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_PROTOCOL_ARINC429_SELECTED_WORD, 0, &word));
	snprintf(wordString, RS_MAX_MESSAGE_LEN, _PERCD, word);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Word>", wordString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatARINCWordRepCapInt_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_ARINC_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatARINCWordRepCapReal_ReadCallback(ViSession          instrSession,
                                                      ViConstString      repCapName,
                                                      RsCoreAttributePtr attr)
{
	return rsrtx_ARINC_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatARINCWordRepCapString_ReadCallback(ViSession          instrSession,
                                                        ViConstString      repCapName,
                                                        RsCoreAttributePtr attr)
{
	return rsrtx_ARINC_Replace_Word_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_SOA_Replace_Point_ReadCallback
* Purpose : Replaces <Point> with number in the command string
*****************************************************************************/
ViStatus rsrtx_SOA_Replace_Point_ReadCallback(ViSession          instrSession,
                                              ViConstString      repCapName,
                                              RsCoreAttributePtr attr)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   pointString[RS_MAX_MESSAGE_LEN];
	ViInt32  point = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, 0, &point));
	snprintf(pointString, RS_MAX_MESSAGE_LEN, _PERCD, point);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Point>", pointString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandRead(instrSession, repCapName, attr, customCmd));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

ViStatus rsrtx_FormatSOAPointRepCapReal_ReadCallback(ViSession          instrSession,
                                                     ViConstString      repCapName,
                                                     RsCoreAttributePtr attr)
{
	return rsrtx_SOA_Replace_Point_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSOAPointRepCapInt_ReadCallback(ViSession          instrSession,
                                                    ViConstString      repCapName,
                                                    RsCoreAttributePtr attr)
{
	return rsrtx_SOA_Replace_Point_ReadCallback(instrSession, repCapName, attr);
}

ViStatus rsrtx_FormatSOAPointRepCapString_ReadCallback(ViSession          instrSession,
                                                       ViConstString      repCapName,
                                                       RsCoreAttributePtr attr)
{
	return rsrtx_SOA_Replace_Point_ReadCallback(instrSession, repCapName, attr);
}

/*****************************************************************************
* Function: rsrtx_FormatSOAPointRepCapReal_WriteCallback
* Purpose : Replaces <Point> with number in the command string
*****************************************************************************/
ViStatus rsrtx_FormatSOAPointRepCapReal_WriteCallback(ViSession          instrSession,
                                                      ViConstString      repCapName,
                                                      RsCoreAttributePtr attr,
                                                      void*              value)
{
	ViStatus error = VI_SUCCESS;
	ViChar*  customCmd = NULL;
	ViChar   pointString[RS_MAX_MESSAGE_LEN];
	ViInt32  point = 0;

	checkErr(RsCore_BuildAttrCommandString(instrSession, attr, repCapName, &customCmd));

	checkErr(RsCore_GetAttributeViInt32(instrSession, "", RSRTX_ATTR_POWER_SAFE_OPERATING_AREA_SELECTED_POINT, 0, &point));
	snprintf(pointString, RS_MAX_MESSAGE_LEN, _PERCD, point);
	RsCore_ReplaceString(customCmd, RS_MAX_MESSAGE_BUF_SIZE, "<Point>", pointString, VI_TRUE);

	checkErr(RsCore_SpecialCallback_CustomCommandWrite(instrSession, repCapName, attr, customCmd, value));

Error:
	if (customCmd)
		free(customCmd);

	return error;
}

/*****************************************************************************
 * Function: rsrtx_logging_ReadCallback
 * Purpose:  This function overrides standard calback funtion. Returns value
 *           from cache
 *****************************************************************************/
ViStatus rsrtx_logging_ReadCallback(ViSession          instrSession,
                                    ViConstString      repCapName,
                                    RsCoreAttributePtr attr)
{
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: rsrtx_logging_WriteCallback
 * Purpose:  This function overrides standard calback funtion.
 *****************************************************************************/
ViStatus rsrtx_logging_WriteCallback(ViSession          instrSession,
                                     ViConstString      repCapName,
                                     RsCoreAttributePtr attr,
                                     void*              value)
{
    return VI_SUCCESS;
}
/*****************************************************************************
 * Function: rsrtx_empty_ReadCallback
 * Purpose:  This function overrides standard calback funtion. Returns value
 *           from cache
 *****************************************************************************/
ViStatus rsrtx_empty_ReadCallback(ViSession          instrSession,
                                  ViConstString      repCapName,
                                  RsCoreAttributePtr attr)
{
    return VI_SUCCESS;
}

/*****************************************************************************
 * Function: rsrtx_empty_WriteCallback
 * Purpose:  This function overrides standard calback funtion. Does not write
 *           anything to instrument, just updates the cache
 *****************************************************************************/
ViStatus rsrtx_empty_WriteCallback(ViSession          instrSession,
                                   ViConstString      repCapName,
                                   RsCoreAttributePtr attr,
                                   void*              value)
{
    return VI_SUCCESS;
}
