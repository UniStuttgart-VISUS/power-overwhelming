/*****************************************************************************
 *- Utility Function Declarations (Non-Exported) ----------------------------*
 *****************************************************************************/

#pragma once
#include <visatype.h>

ViStatus rsrtx_InitAttributes(ViSession instrSession);

ViStatus rsrtx_DefaultInstrSetup(ViSession openInstrSession);

ViStatus rsrtx_CheckStatus(ViSession instrSession);

