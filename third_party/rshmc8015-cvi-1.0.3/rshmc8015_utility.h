/*****************************************************************************
 *- Utility Function Declarations (Non-Exported) ----------------------------*
 *****************************************************************************/

#include <visa.h>

ViStatus rshmc8015_InitAttributes (ViSession vi);
ViStatus rshmc8015_DefaultInstrSetup (ViSession openInstrSession);
ViStatus rshmc8015_CheckStatus (ViSession vi);
ViStatus rshmc8015_invalidViInt32Range (ViSession instrSession, ViInt32 val, ViInt32 min, ViInt32 max);
ViStatus rshmc8015_invalidViUInt32Range (ViSession instrSession, ViUInt32 val, ViUInt32 min, ViUInt32 max);
ViStatus rshmc8015_invalidViReal64Range (ViSession instrSession, ViReal64 val, ViReal64 min, ViReal64 max);
ViStatus rshmc8015_invalidViBooleanRange (ViSession instrSession, ViBoolean val);
ViStatus rshmc8015_channelRepCap (ViSession instrSession, ViInt32 board, ViChar rep_cap[]);
void rshmc8015_ParseStatusString (ViChar buffer[], ViChar output[]);
void rshmc8015_ParseStatusInt (ViChar buffer[], ViInt32 *output);
void rshmc8015_ParseStatusInt64 (ViChar buffer[], ViInt64 *output);
void rshmc8015_ParseStatusReal (ViChar buffer[], ViReal64 *output);
void rshmc8015_ParseStatusEnum (ViChar buffer[], ViInt32 *output, ViString array[]);
ViInt32 rshmc8015_StringIndex(ViString array[], ViChar buff[]);
ViStatus rshmc8015_WaitForOPCCallback (ViSession instrSession);
ViInt32 rshmc8015_atol (ViChar *p2buf);
ViInt64 rshmc8015_atol64 (ViChar *p2buf); 
ViReal64 rshmc8015_atof (ViChar *p2buf);
ViStatus rshmc8015_readDataBlock (ViSession instrSession, ViChar **outputBuffer, ViUInt32 *byteCount);
