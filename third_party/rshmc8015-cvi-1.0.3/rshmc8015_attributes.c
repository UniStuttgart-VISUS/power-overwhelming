/*****************************************************************************
 *  Rohde&Schwarz Instrument Driver Specific Attribute callbacks
 *
 *  WARNING: Do not add to, delete from, or otherwise modify the contents
 *           of this source file. It is generated from DrBase repository.
 *
 *  Built on: 2016-03-22 12:47:52Z
 *****************************************************************************/

#include "rshmc8015.h"

/*****************************************************************************
 *- Repeated Capabilities ---------------------------------------------------*
 *****************************************************************************/

RsRepCap rshmc8015_RsRepCapTable[] =
    {
/*
        {
        repCapName      ... Repeated capability name, e.g. "Channel"
        identifiers     ... Repeated capability identifiers (comma separated values), e.g. "Ch1,Ch2,Ch3"
        cmdValues       ... Command values (comma separated values), e.g. "1,2,3"
        },
*/

       {
        "Page",
        "Page1,Page2,Page3,Page4",
        "1,2,3,4"
       },
       {
        "Cell",
        "Cell1,Cell2,Cell3,Cell4,Cell5,Cell6",
        "1,2,3,4,5,6"
       },
       {
        "Limit",
        "Lim1,Lim2,Lim3,Lim4,Lim5,Lim6",
        "1,2,3,4,5,6"
       },
       {
        "Channel",
        "CH1",
        "1"
       },
         NULL
    };

/*****************************************************************************
 *- Range Tables ------------------------------------------------------------*
 *****************************************************************************/

static RsRangeTableEntry rshmc8015_rngViewModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"NORM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"HARM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"TREN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"SIGN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"STAN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"INR",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngViewMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngViewModeEntries
};

static RsRangeTableEntry rshmc8015_rngNormalViewFunctionEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EMP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"P",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"S",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"Q",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LAMB",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PHI",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */6,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FU",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */7,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FI",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */8,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UPP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */9,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UMP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */10,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IPP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */11,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IMP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */12,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PPP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */13,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PMP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */14,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"URMS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */15,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UAVG",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */16,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IRMS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */17,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IAVG",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */18,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UTHD",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */19,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"ITHD",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */20,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"DIN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */21,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"AIN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */22,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"TIME",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */23,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"WH",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */24,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"WHP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */25,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"WHM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */26,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"AH",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */27,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"AHP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */28,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"AHM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */29,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"TEMP1",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */30,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM1",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */31,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM2",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */32,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM3",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */33,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM4",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */34,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM5",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */35,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM6",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */36,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"URAN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */37,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IRAN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */38,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FPLL",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngNormalViewFunction =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngNormalViewFunctionEntries
};

static RsRangeTableEntry rshmc8015_rngViewNormalPageSizeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"6",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"10",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngViewNormalPageSize =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngViewNormalPageSizeEntries
};

static RsRangeTableEntry rshmc8015_rngHarmonicsViewEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"BAR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"TABL",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngHarmonicsView =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngHarmonicsViewEntries
};

static RsRangeTableEntry rshmc8015_rngHarmonicsSourceEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"VOLT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"CURR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"BOTH",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngHarmonicsSource =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngHarmonicsSourceEntries
};

static RsRangeTableEntry rshmc8015_rngHarmonicsNumberEntries[] =
{
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */50,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngHarmonicsNumber =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngHarmonicsNumberEntries
};

static RsRangeTableEntry rshmc8015_rngHarmonicsScalingEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"ABS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PERC",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngHarmonicsScaling =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngHarmonicsScalingEntries
};

static RsRangeTableEntry rshmc8015_rngHarmonicsSubsetEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EVEN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"ODD",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngHarmonicsSubset =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngHarmonicsSubsetEntries
};

static RsRangeTableEntry rshmc8015_rngActivePageEntries[] =
{
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */4,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngActivePage =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngActivePageEntries
};

static RsRangeTableEntry rshmc8015_rngIntegratorModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"MAN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"DUR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"SPAN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EXT",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngIntegratorMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngIntegratorModeEntries
};

static RsRangeTableEntry rshmc8015_rngIntegratorDurationEntries[] =
{
  {
      /* discreteOrMinValue = */0.0,
      /* maxValue           = */2.15e9,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngIntegratorDuration =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */"s",
  /* rangeValues = */rshmc8015_rngIntegratorDurationEntries
};

static RsRangeTableEntry rshmc8015_rngLoggingModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UNL",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"COUN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"DUR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"SPAN",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngLoggingMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngLoggingModeEntries
};

static RsRangeTableEntry rshmc8015_rngLoggingTimeEntries[] =
{
  {
      /* discreteOrMinValue = */1.0,
      /* maxValue           = */6.05e5,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngLoggingTime =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */"s",
  /* rangeValues = */rshmc8015_rngLoggingTimeEntries
};

static RsRangeTableEntry rshmc8015_rngLoggingCountEntries[] =
{
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */2147483647,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngLoggingCount =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngLoggingCountEntries
};

static RsRangeTableEntry rshmc8015_rngLimitSourceEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"URMS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UAVG",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FU",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IRMS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"IAVG",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FI",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */6,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"P",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */7,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"S",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */8,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"Q",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */9,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LAMB",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */10,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PHI",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */11,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FPLL",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */12,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"UTHD",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */13,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"ITHD",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngLimitSource =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngLimitSourceEntries
};

static RsRangeTableEntry rshmc8015_rngAcquisitionModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"AC",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"DC",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EXT",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngAcquisitionMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngAcquisitionModeEntries
};

static RsRangeTableEntry rshmc8015_rngAcquisitionVoltageRangeEntries[] =
{
  {
      /* discreteOrMinValue = */5.0,
      /* maxValue           = */6.0e2,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngAcquisitionVoltageRange =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngAcquisitionVoltageRangeEntries
};

static RsRangeTableEntry rshmc8015_rngAcquisitionCrestFactorEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"3",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"6",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngAcquisitionCrestFactor =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngAcquisitionCrestFactorEntries
};

static RsRangeTableEntry rshmc8015_rngAcquisitionCurrentRangeEntries[] =
{
  {
      /* discreteOrMinValue = */5.0e-3,
      /* maxValue           = */2.0e1,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngAcquisitionCurrentRange =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngAcquisitionCurrentRangeEntries
};

static RsRangeTableEntry rshmc8015_rngPLLSourceEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"VOLT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"CURR",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngPLLSource =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngPLLSourceEntries
};

static RsRangeTableEntry rshmc8015_rngImageFormatEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"BMP",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PNG",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngImageFormat =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngImageFormatEntries
};

static RsRangeTableEntry rshmc8015_rngAnalogOutputModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"VOLT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"CURR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"POW",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM1",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM2",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM3",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */6,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM4",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */7,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM5",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */8,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM6",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngAnalogOutputMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngAnalogOutputModeEntries
};

static RsRangeTableEntry rshmc8015_rngDigitalInputModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FREQ",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PWM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"STAT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"COMM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"INT",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngDigitalInputMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngDigitalInputModeEntries
};

static RsRangeTableEntry rshmc8015_rngDigitalOutputModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"FPLL",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"COMM",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM1",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM2",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM3",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */5,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM4",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */6,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM5",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */7,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"LIM6",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngDigitalOutputMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngDigitalOutputModeEntries
};

static RsRangeTableEntry rshmc8015_rngSensorModeEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EXTS",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"CCL",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngSensorMode =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngSensorModeEntries
};

static RsRangeTableEntry rshmc8015_rngShuntResistanceEntries[] =
{
  {
      /* discreteOrMinValue = */1.0e-6,
      /* maxValue           = */9.9e7,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngShuntResistance =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngShuntResistanceEntries
};

static RsRangeTableEntry rshmc8015_rngClampRatioEntries[] =
{
  {
      /* discreteOrMinValue = */1.0e-4,
      /* maxValue           = */9.9e1,
      /* coercedValue       = */0,
      /* cmdString          = */NULL,
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngClampRatio =
{
  /* type        = */RS_VAL_RANGED,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */"V",
  /* rangeValues = */rshmc8015_rngClampRatioEntries
};

static RsRangeTableEntry rshmc8015_rngStatusRegisterOperationEntries[] =
{
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"QUES",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"OPER",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngStatusRegisterOperation =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngStatusRegisterOperationEntries
};

static RsRangeTableEntry rshmc8015_rngStatusRegisterQueryEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"COND",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EVEN",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"ENAB",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */3,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"PTR",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */4,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"NTR",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngStatusRegisterQuery =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngStatusRegisterQueryEntries
};

static RsRangeTableEntry rshmc8015_rngDeviceEntries[] =
{
  {
      /* discreteOrMinValue = */0,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"INT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */1,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"EXT",
      /* cmdValue           = */0
  },
  {
      /* discreteOrMinValue = */2,
      /* maxValue           = */0,
      /* coercedValue       = */0,
      /* cmdString          = */"DEF",
      /* cmdValue           = */0
  },
  RS_RANGE_TABLE_LAST_ENTRY
};

RsRangeTable rshmc8015_rngDevice =
{
  /* type        = */RS_VAL_DISCRETE,
  /* hasMin      = */1,
  /* hasMax      = */1,
  /* customInfo  = */NULL,
  /* rangeValues = */rshmc8015_rngDeviceEntries
};


/*****************************************************************************
*- Attributes --------------------------------------------------------------*
 *****************************************************************************/

RsAttrProperties  g_RSHMC8015_RS_ATTR_RANGE_CHECK =
{
  /* constant           = */RS_ATTR_RANGE_CHECK,
#if defined (_DEBUG)
  /* debug name         = */"Range Check",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_TRUE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_QUERY_INSTRUMENT_STATUS =
{
  /* constant           = */RS_ATTR_QUERY_INSTRUMENT_STATUS,
#if defined (_DEBUG)
  /* debug name         = */"Query Instrument Status",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_TRUE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CACHE =
{
  /* constant           = */RS_ATTR_CACHE,
#if defined (_DEBUG)
  /* debug name         = */"Cache",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_TRUE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SIMULATE =
{
  /* constant           = */RS_ATTR_SIMULATE,
#if defined (_DEBUG)
  /* debug name         = */"Simulate",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_RECORD_COERCIONS =
{
  /* constant           = */RS_ATTR_RECORD_COERCIONS,
#if defined (_DEBUG)
  /* debug name         = */"Record Value Coercions",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_INTERCHANGE_CHECK =
{
  /* constant           = */RS_ATTR_INTERCHANGE_CHECK,
#if defined (_DEBUG)
  /* debug name         = */"Interchangeability Check",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_TRUE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPY =
{
  /* constant           = */RS_ATTR_SPY,
#if defined (_DEBUG)
  /* debug name         = */"Spy",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_USE_SPECIFIC_SIMULATION =
{
  /* constant           = */RS_ATTR_USE_SPECIFIC_SIMULATION,
#if defined (_DEBUG)
  /* debug name         = */"Use Specific Simulation",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_TRUE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_COERCEABLE_ONLY_BY_INSTR | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_DESCRIPTION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_DESCRIPTION,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Description",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_PREFIX =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_PREFIX,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Prefix",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_VENDOR =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_VENDOR,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Vendor",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_REVISION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_REVISION,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Revision",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Major Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Driver Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION,
#if defined (_DEBUG)
  /* debug name         = */"Driver Description",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_PREFIX =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_PREFIX,
#if defined (_DEBUG)
  /* debug name         = */"Driver Prefix",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_LOCATOR =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_LOCATOR,
#if defined (_DEBUG)
  /* debug name         = */"Driver Locator",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_VENDOR =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_VENDOR,
#if defined (_DEBUG)
  /* debug name         = */"Driver Vendor",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_REVISION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_REVISION,
#if defined (_DEBUG)
  /* debug name         = */"Driver Revision",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Specification Major Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Specification Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS =
{
  /* constant           = */RS_ATTR_SUPPORTED_INSTRUMENT_MODELS,
#if defined (_DEBUG)
  /* debug name         = */"Supported Instrument Models",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_GROUP_CAPABILITIES =
{
  /* constant           = */RS_ATTR_GROUP_CAPABILITIES,
#if defined (_DEBUG)
  /* debug name         = */"Class Group Capabilities",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_FUNCTION_CAPABILITIES =
{
  /* constant           = */RS_ATTR_FUNCTION_CAPABILITIES,
#if defined (_DEBUG)
  /* debug name         = */"Function Capabilities",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CHANNEL_COUNT =
{
  /* constant           = */RS_ATTR_CHANNEL_COUNT,
#if defined (_DEBUG)
  /* debug name         = */"Channel Count",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_DRIVER_SETUP =
{
  /* constant           = */RS_ATTR_DRIVER_SETUP,
#if defined (_DEBUG)
  /* debug name         = */"Driver Setup",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_INSTRUMENT_MANUFACTURER =
{
  /* constant           = */RS_ATTR_INSTRUMENT_MANUFACTURER,
#if defined (_DEBUG)
  /* debug name         = */"Instrument Manufacturer",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"Rohde&Schwarz",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_INSTRUMENT_MODEL =
{
  /* constant           = */RS_ATTR_INSTRUMENT_MODEL,
#if defined (_DEBUG)
  /* debug name         = */"Instrument Model",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION =
{
  /* constant           = */RS_ATTR_INSTRUMENT_FIRMWARE_REVISION,
#if defined (_DEBUG)
  /* debug name         = */"Instrument Firmware Revision",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_OPTIONS_LIST =
{
  /* constant           = */RS_ATTR_OPTIONS_LIST,
#if defined (_DEBUG)
  /* debug name         = */"Options List",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_IO_RESOURCE_DESCRIPTOR =
{
  /* constant           = */RS_ATTR_IO_RESOURCE_DESCRIPTOR,
#if defined (_DEBUG)
  /* debug name         = */"Resource Descriptor",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_LOGICAL_NAME =
{
  /* constant           = */RS_ATTR_LOGICAL_NAME,
#if defined (_DEBUG)
  /* debug name         = */"Logical Name",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_PRIMARY_ERROR =
{
  /* constant           = */RS_ATTR_PRIMARY_ERROR,
#if defined (_DEBUG)
  /* debug name         = */"Primary Error",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SECONDARY_ERROR =
{
  /* constant           = */RS_ATTR_SECONDARY_ERROR,
#if defined (_DEBUG)
  /* debug name         = */"Secondary Error",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_ERROR_ELABORATION =
{
  /* constant           = */RS_ATTR_ERROR_ELABORATION,
#if defined (_DEBUG)
  /* debug name         = */"Error Elaboration",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_HIDDEN | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_VISA_RM_SESSION =
{
  /* constant           = */RS_ATTR_VISA_RM_SESSION,
#if defined (_DEBUG)
  /* debug name         = */"VISA Resource Manager Session",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_SESSION,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_HIDDEN | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_IO_SESSION =
{
  /* constant           = */RS_ATTR_IO_SESSION,
#if defined (_DEBUG)
  /* debug name         = */"Instrument IO Session",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_SESSION,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_IO_SESSION_TYPE =
{
  /* constant           = */RS_ATTR_IO_SESSION_TYPE,
#if defined (_DEBUG)
  /* debug name         = */"IO Session Type",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"0",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_SUPPORTED | RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Driver Major Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Driver Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Driver Minor Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_MAJOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Major Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_CLASS_DRIVER_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Class Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_ENGINE_MAJOR_VERSION =
{
  /* constant           = */RS_ATTR_ENGINE_MAJOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Engine Major Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_ENGINE_MINOR_VERSION =
{
  /* constant           = */RS_ATTR_ENGINE_MINOR_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"Engine Minor Version",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_ENGINE_REVISION =
{
  /* constant           = */RS_ATTR_ENGINE_REVISION,
#if defined (_DEBUG)
  /* debug name         = */"Engine Revision",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"0",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_NOT_WRITABLE | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_OPC_CALLBACK =
{
  /* constant           = */RS_ATTR_OPC_CALLBACK,
#if defined (_DEBUG)
  /* debug name         = */"Operation Complete (OPC) Callback",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_ADDR,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_HIDDEN | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_CHECK_STATUS_CALLBACK =
{
  /* constant           = */RS_ATTR_CHECK_STATUS_CALLBACK,
#if defined (_DEBUG)
  /* debug name         = */"Check Status Callback",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_ADDR,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_HIDDEN | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_RS_ATTR_OPC_TIMEOUT =
{
  /* constant           = */RS_ATTR_OPC_TIMEOUT,
#if defined (_DEBUG)
  /* debug name         = */"Operation Complete (OPC) Timeout",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_HIDDEN | RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_MODE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngAcquisitionMode,
  /* command            = */"CHAN{Channel}:MODE",
  /* integerDefault     = */RSHMC8015_VAL_ACQ_MODE_DC,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_PLL_SOURCE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_PLL_SOURCE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition PLL Source",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngPLLSource,
  /* command            = */"CHAN{Channel}:MODE:PLL",
  /* integerDefault     = */RSHMC8015_VAL_PLL_SOURCE_VOLTAGE,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Frequency Filter",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:MODE:FREQ",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_DIGITAL_FILTER =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_DIGITAL_FILTER,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Digital Filter",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:MODE:DIG",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_BWL =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_BWL,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition BWL",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:MODE:ANAL",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Voltage Autorange",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:VOLT:RANG:AUTO",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Voltage Range",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngAcquisitionVoltageRange,
  /* command            = */"CHAN{Channel}:VOLT:RANG",
  /* integerDefault     = */0,
  /* doubleDefault      = */300.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Voltage Crest Factor",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngAcquisitionCrestFactor,
  /* command            = */"CHAN{Channel}:VOLT:CFAC",
  /* integerDefault     = */RSHMC8015_VAL_CREST_FACTOR_3,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Voltage Invert",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:VOLT:INV",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Current Autorange",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:CURR:RANG:AUTO",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_CURRENT_RANGE =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_CURRENT_RANGE,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Current Range",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngAcquisitionCurrentRange,
  /* command            = */"CHAN{Channel}:CURR:RANG",
  /* integerDefault     = */0,
  /* doubleDefault      = */100.0e-3,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Current Crest Factor",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngAcquisitionCrestFactor,
  /* command            = */"CHAN{Channel}:CURR:CFAC",
  /* integerDefault     = */RSHMC8015_VAL_CREST_FACTOR_3,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_CURRENT_INVERT =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_CURRENT_INVERT,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Current Invert",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:CURR:INV",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_OCP =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_OCP,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Overcurrent Protection",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:CURR:PROT?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_ACQ_OCP_RESET =
{
  /* constant           = */RSHMC8015_ATTR_ACQ_OCP_RESET,
#if defined (_DEBUG)
  /* debug name         = */"Acquisition Reset Overcurrent Protection",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:CURR:PROT:RES",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH =
{
  /* constant           = */RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH,
#if defined (_DEBUG)
  /* debug name         = */"Function List Length",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:MEAS:FUNC:COUN?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Limit State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:LIM{Limit}",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_SOURCE =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_SOURCE,
#if defined (_DEBUG)
  /* debug name         = */"Limit Source",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngLimitSource,
  /* command            = */"CHAN{Channel}:LIM{Limit}:SOUR",
  /* integerDefault     = */RSHMC8015_VAL_LIMIT_SOURCE_URMS,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_HIGH =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_HIGH,
#if defined (_DEBUG)
  /* debug name         = */"Limit High",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:LIM{Limit}:HIGH",
  /* integerDefault     = */0,
  /* doubleDefault      = */1.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_LOW =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_LOW,
#if defined (_DEBUG)
  /* debug name         = */"Limit Low",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:LIM{Limit}:LOW",
  /* integerDefault     = */0,
  /* doubleDefault      = */-1.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_CHECK_RESULT =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_CHECK_RESULT,
#if defined (_DEBUG)
  /* debug name         = */"Limit Check Result",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:LIM{Limit}:RES?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_LIMIT_PERCENT =
{
  /* constant           = */RSHMC8015_ATTR_LIMIT_PERCENT,
#if defined (_DEBUG)
  /* debug name         = */"Limit Percent",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:LIM{Limit}:PERC?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)rshmc8015_parseNAN_ReadCallback,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_AINPUT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_AINPUT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Analog Input State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:AINP",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_AOUTPUT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_AOUTPUT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Analog Output State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:AOUT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_AOUTPUT_MODE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_AOUTPUT_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Analog Output Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngAnalogOutputMode,
  /* command            = */"CHAN{Channel}:AOUT:MODE",
  /* integerDefault     = */RSHMC8015_VAL_AOUT_MODE_VOLTAGE,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DINPUT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DINPUT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Digital Input State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:DINP",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DINPUT_MODE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DINPUT_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Digital Input Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngDigitalInputMode,
  /* command            = */"CHAN{Channel}:DINP:MODE",
  /* integerDefault     = */RSHMC8015_VAL_DINP_MODE_FREQUENCY,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DINPUT_INVERT =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DINPUT_INVERT,
#if defined (_DEBUG)
  /* debug name         = */"Digital Input Invert",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:DINP:INV",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DOUTPUT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DOUTPUT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Digital Output State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:DOUT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DOUTPUT_MODE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DOUTPUT_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Digital Output Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngDigitalOutputMode,
  /* command            = */"CHAN{Channel}:DOUT:MODE",
  /* integerDefault     = */RSHMC8015_VAL_DOUT_MODE_LIM1,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Output State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:DOUT:OUTP",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_DOUTPUT_INVERT =
{
  /* constant           = */RSHMC8015_ATTR_EXT_DOUTPUT_INVERT,
#if defined (_DEBUG)
  /* debug name         = */"Digital Output Invert",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:DOUT:INV",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_SENSOR_STATE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_SENSOR_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Sensor State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:SENS",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_SENSOR_MODE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_SENSOR_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Sensor Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngSensorMode,
  /* command            = */"CHAN{Channel}:SENS:MODE",
  /* integerDefault     = */RSHMC8015_VAL_SENSOR_MODE_SHUNT,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE,
#if defined (_DEBUG)
  /* debug name         = */"Shunt Resistance",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngShuntResistance,
  /* command            = */"CHAN{Channel}:SENS:EXTS",
  /* integerDefault     = */0,
  /* doubleDefault      = */1.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO =
{
  /* constant           = */RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO,
#if defined (_DEBUG)
  /* debug name         = */"Clamp Ratio",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngClampRatio,
  /* command            = */"CHAN{Channel}:SENS:CCL",
  /* integerDefault     = */0,
  /* doubleDefault      = */1.0e-3,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_EXT_SENSOR_RANGE =
{
  /* constant           = */RSHMC8015_ATTR_EXT_SENSOR_RANGE,
#if defined (_DEBUG)
  /* debug name         = */"Range",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */NULL,
  /* command            = */"CHAN{Channel}:SENS:RANG",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_MODE =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngViewMode,
  /* command            = */"VIEW",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_MODE_NORMAL,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE,
#if defined (_DEBUG)
  /* debug name         = */"Active Page",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngActivePage,
  /* command            = */"VIEW:NORM",
  /* integerDefault     = */1,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE,
#if defined (_DEBUG)
  /* debug name         = */"Size",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngViewNormalPageSize,
  /* command            = */"VIEW:NORM:PAGE{Page}:SIZE",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_PAGE_SIZE_6,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_NORM_FUNCTION =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_NORM_FUNCTION,
#if defined (_DEBUG)
  /* debug name         = */"Function",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngNormalViewFunction,
  /* command            = */"VIEW:NORM:PAGE{Page}:CELL{Cell}:FUNC",
  /* integerDefault     = */RSHMC8015_VAL_NORMAL_VIEW_FUNC_EMPTY,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_TRUE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_HARM_SELECT =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_HARM_SELECT,
#if defined (_DEBUG)
  /* debug name         = */"Select",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngHarmonicsView,
  /* command            = */"VIEW:HARM:VIEW",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_HARM_VIEW_BAR,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_HARM_SOURCE =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_HARM_SOURCE,
#if defined (_DEBUG)
  /* debug name         = */"Source",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngHarmonicsSource,
  /* command            = */"VIEW:HARM:SOUR",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_HARM_SOURCE_VOLTAGE,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_HARM_NUMBER =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_HARM_NUMBER,
#if defined (_DEBUG)
  /* debug name         = */"Number",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngHarmonicsNumber,
  /* command            = */"VIEW:HARM:NUMB",
  /* integerDefault     = */5,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_HARM_SCALING =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_HARM_SCALING,
#if defined (_DEBUG)
  /* debug name         = */"Scaling",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngHarmonicsScaling,
  /* command            = */"VIEW:HARM:SCAL",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_HARM_SCALING_ABSOLUTE,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_VIEW_HARM_SUBSET =
{
  /* constant           = */RSHMC8015_ATTR_VIEW_HARM_SUBSET,
#if defined (_DEBUG)
  /* debug name         = */"Subset",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngHarmonicsSubset,
  /* command            = */"VIEW:HARM:SUBS",
  /* integerDefault     = */RSHMC8015_VAL_VIEW_HARM_SUBSET_EVEN,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_STATE =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Integrator State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"INT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_MODE =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Integrator Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngIntegratorMode,
  /* command            = */"INT:MODE",
  /* integerDefault     = */RSHMC8015_VAL_INTEGRATOR_MODE_MANUAL,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_DURATION =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_DURATION,
#if defined (_DEBUG)
  /* debug name         = */"Integrator Duration",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngIntegratorDuration,
  /* command            = */"INT:DUR",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_RESET =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_RESET,
#if defined (_DEBUG)
  /* debug name         = */"Integrator Reset",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"INT:RES",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_START =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_START,
#if defined (_DEBUG)
  /* debug name         = */"Integrator Start",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"INT:STAR",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_INTEGRATOR_STOP =
{
  /* constant           = */RSHMC8015_ATTR_INTEGRATOR_STOP,
#if defined (_DEBUG)
  /* debug name         = */"Integrator Stop",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"INT:STOP",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_LOGGING_STATE =
{
  /* constant           = */RSHMC8015_ATTR_LOGGING_STATE,
#if defined (_DEBUG)
  /* debug name         = */"Logging State",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"LOG",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_LOGGING_PAGE =
{
  /* constant           = */RSHMC8015_ATTR_LOGGING_PAGE,
#if defined (_DEBUG)
  /* debug name         = */"Logging Page",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */"LOG:PAGE",
  /* integerDefault     = */1,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_LOGGING_MODE =
{
  /* constant           = */RSHMC8015_ATTR_LOGGING_MODE,
#if defined (_DEBUG)
  /* debug name         = */"Logging Mode",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngLoggingMode,
  /* command            = */"LOG:MODE",
  /* integerDefault     = */RSHMC8015_VAL_LOGGING_MODE_UNLIMITED,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_LOGGING_TIME =
{
  /* constant           = */RSHMC8015_ATTR_LOGGING_TIME,
#if defined (_DEBUG)
  /* debug name         = */"Logging Time",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_REAL64,
  /* rangeTable         = */&rshmc8015_rngLoggingTime,
  /* command            = */"LOG:DUR",
  /* integerDefault     = */0,
  /* doubleDefault      = */1.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_LOGGING_COUNT =
{
  /* constant           = */RSHMC8015_ATTR_LOGGING_COUNT,
#if defined (_DEBUG)
  /* debug name         = */"Logging Count",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngLoggingCount,
  /* command            = */"LOG:COUN",
  /* integerDefault     = */1,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_ID_QUERY_RESPONSE =
{
  /* constant           = */RSHMC8015_ATTR_ID_QUERY_RESPONSE,
#if defined (_DEBUG)
  /* debug name         = */"ID Query Response",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */NULL,
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"test",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */RS_VAL_DONT_CHECK_STATUS,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_DISPLAY_CLEAR =
{
  /* constant           = */RSHMC8015_ATTR_DISPLAY_CLEAR,
#if defined (_DEBUG)
  /* debug name         = */"Clear",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"DISP:TEXT:CLE",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_DISPLAY_TEXT =
{
  /* constant           = */RSHMC8015_ATTR_DISPLAY_TEXT,
#if defined (_DEBUG)
  /* debug name         = */"Text",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"DISP:TEXT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"'message'",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT =
{
  /* constant           = */RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT,
#if defined (_DEBUG)
  /* debug name         = */"Image Format",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */&rshmc8015_rngImageFormat,
  /* command            = */"HCOP:FORM",
  /* integerDefault     = */RSHMC8015_VAL_IMAGE_FORMAT_BMP,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH =
{
  /* constant           = */RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH,
#if defined (_DEBUG)
  /* debug name         = */"Image Width",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */"HCOP:SIZE:X?",
  /* integerDefault     = */1920,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT =
{
  /* constant           = */RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT,
#if defined (_DEBUG)
  /* debug name         = */"Image Height",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_INT32,
  /* rangeTable         = */NULL,
  /* command            = */"HCOP:SIZE:Y?",
  /* integerDefault     = */1080,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED,
#if defined (_DEBUG)
  /* debug name         = */"Beeper Enabled",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_BOOLEAN,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:BEEP:STAT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_START_BEEP =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_START_BEEP,
#if defined (_DEBUG)
  /* debug name         = */"Start Beep",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:BEEP",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_NAME =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_NAME,
#if defined (_DEBUG)
  /* debug name         = */"System Name",
#endif
  /* access             = */RS_VAL_READ_WRITE,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:NAME",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"'HMC 8015'",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_ERROR =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_ERROR,
#if defined (_DEBUG)
  /* debug name         = */"System Error",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:ERR?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_LOCAL =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_LOCAL,
#if defined (_DEBUG)
  /* debug name         = */"System Local",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:LOC",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_REMOTE =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_REMOTE,
#if defined (_DEBUG)
  /* debug name         = */"System Remote",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:REM",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_RWLOCK =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_RWLOCK,
#if defined (_DEBUG)
  /* debug name         = */"System RWLock",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:RWL",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_VERSION =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_VERSION,
#if defined (_DEBUG)
  /* debug name         = */"System Version",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:VERS?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_DEVICE =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_DEVICE,
#if defined (_DEBUG)
  /* debug name         = */"System Device",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:DEV?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_SHUTDOWN =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_SHUTDOWN,
#if defined (_DEBUG)
  /* debug name         = */"System Shutdown",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:SHUT",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_SOFTWARE =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_SOFTWARE,
#if defined (_DEBUG)
  /* debug name         = */"System Software",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:SOFT?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_HARDWARE =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_HARDWARE,
#if defined (_DEBUG)
  /* debug name         = */"System Hardware",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:HARD?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER =
{
  /* constant           = */RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER,
#if defined (_DEBUG)
  /* debug name         = */"System Serial Number",
#endif
  /* access             = */RS_VAL_READ_ONLY,
  /* dataType           = */RS_VAL_STRING,
  /* rangeTable         = */NULL,
  /* command            = */"SYST:SNUM?",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */"""",
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};

RsAttrProperties  g_RSHMC8015_ATTR_STATUS_PRESET =
{
  /* constant           = */RSHMC8015_ATTR_STATUS_PRESET,
#if defined (_DEBUG)
  /* debug name         = */"Status Preset",
#endif
  /* access             = */RS_VAL_WRITE_ONLY,
  /* dataType           = */RS_VAL_EVENT,
  /* rangeTable         = */NULL,
  /* command            = */"STAT:PRES",
  /* integerDefault     = */0,
  /* doubleDefault      = */0.0,
  /* booleanDefault     = */VI_FALSE,
  /* stringDefault      = */NULL,
  /* sessionDefault     = */0,
  /* comparePrecision   = */0.001,
  /* readCallback       = */(RsReadAttr_CallbackPtr)NULL,
  /* writeCallback      = */(RsWriteAttr_CallbackPtr)NULL,
  /* checkCallback      = */(RsCheckAttr_CallbackPtr)NULL,
  /* checkStatusCallback      = */(RsCheckStatusAttr_CallbackPtr)NULL,
  /* coerceCallback     = */(RsCoerceAttr_CallbackPtr)NULL,
  /* rngTableCallback   = */(RsRangeTable_CallbackPtr)NULL,
  /* userCallback       = */(RsUserAttr_CallbackPtr)NULL,
  /* flags              = */0,
  /* supportedModels    = */NULL,
  /* instrumentOptions  = */NULL,
  /* p2value            = */NULL,
  /* usercaps           = */VI_FALSE
};


/*****************************************************************************
 *- Attributes List ---------------------------------------------------------*
 *****************************************************************************/

RsAttrPropertiesPtr rshmc8015_RsAttrPropertiesList[] =
{
&g_RSHMC8015_RS_ATTR_RANGE_CHECK,
&g_RSHMC8015_RS_ATTR_QUERY_INSTRUMENT_STATUS,
&g_RSHMC8015_RS_ATTR_CACHE,
&g_RSHMC8015_RS_ATTR_SIMULATE,
&g_RSHMC8015_RS_ATTR_RECORD_COERCIONS,
&g_RSHMC8015_RS_ATTR_INTERCHANGE_CHECK,
&g_RSHMC8015_RS_ATTR_SPY,
&g_RSHMC8015_RS_ATTR_USE_SPECIFIC_SIMULATION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_DESCRIPTION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_PREFIX,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_VENDOR,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_REVISION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_PREFIX,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_LOCATOR,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_VENDOR,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_REVISION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS,
&g_RSHMC8015_RS_ATTR_GROUP_CAPABILITIES,
&g_RSHMC8015_RS_ATTR_FUNCTION_CAPABILITIES,
&g_RSHMC8015_RS_ATTR_CHANNEL_COUNT,
&g_RSHMC8015_RS_ATTR_DRIVER_SETUP,
&g_RSHMC8015_RS_ATTR_INSTRUMENT_MANUFACTURER,
&g_RSHMC8015_RS_ATTR_INSTRUMENT_MODEL,
&g_RSHMC8015_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION,
&g_RSHMC8015_RS_ATTR_OPTIONS_LIST,
&g_RSHMC8015_RS_ATTR_IO_RESOURCE_DESCRIPTOR,
&g_RSHMC8015_RS_ATTR_LOGICAL_NAME,
&g_RSHMC8015_RS_ATTR_PRIMARY_ERROR,
&g_RSHMC8015_RS_ATTR_SECONDARY_ERROR,
&g_RSHMC8015_RS_ATTR_ERROR_ELABORATION,
&g_RSHMC8015_RS_ATTR_VISA_RM_SESSION,
&g_RSHMC8015_RS_ATTR_IO_SESSION,
&g_RSHMC8015_RS_ATTR_IO_SESSION_TYPE,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION,
&g_RSHMC8015_RS_ATTR_CLASS_DRIVER_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_ENGINE_MAJOR_VERSION,
&g_RSHMC8015_RS_ATTR_ENGINE_MINOR_VERSION,
&g_RSHMC8015_RS_ATTR_ENGINE_REVISION,
&g_RSHMC8015_RS_ATTR_OPC_CALLBACK,
&g_RSHMC8015_RS_ATTR_CHECK_STATUS_CALLBACK,
&g_RSHMC8015_RS_ATTR_OPC_TIMEOUT,
&g_RSHMC8015_ATTR_ACQ_MODE,
&g_RSHMC8015_ATTR_ACQ_PLL_SOURCE,
&g_RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER,
&g_RSHMC8015_ATTR_ACQ_DIGITAL_FILTER,
&g_RSHMC8015_ATTR_ACQ_BWL,
&g_RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE,
&g_RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE,
&g_RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR,
&g_RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT,
&g_RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE,
&g_RSHMC8015_ATTR_ACQ_CURRENT_RANGE,
&g_RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR,
&g_RSHMC8015_ATTR_ACQ_CURRENT_INVERT,
&g_RSHMC8015_ATTR_ACQ_OCP,
&g_RSHMC8015_ATTR_ACQ_OCP_RESET,
&g_RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH,
&g_RSHMC8015_ATTR_LIMIT_STATE,
&g_RSHMC8015_ATTR_LIMIT_SOURCE,
&g_RSHMC8015_ATTR_LIMIT_HIGH,
&g_RSHMC8015_ATTR_LIMIT_LOW,
&g_RSHMC8015_ATTR_LIMIT_CHECK_RESULT,
&g_RSHMC8015_ATTR_LIMIT_PERCENT,
&g_RSHMC8015_ATTR_EXT_AINPUT_STATE,
&g_RSHMC8015_ATTR_EXT_AOUTPUT_STATE,
&g_RSHMC8015_ATTR_EXT_AOUTPUT_MODE,
&g_RSHMC8015_ATTR_EXT_DINPUT_STATE,
&g_RSHMC8015_ATTR_EXT_DINPUT_MODE,
&g_RSHMC8015_ATTR_EXT_DINPUT_INVERT,
&g_RSHMC8015_ATTR_EXT_DOUTPUT_STATE,
&g_RSHMC8015_ATTR_EXT_DOUTPUT_MODE,
&g_RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE,
&g_RSHMC8015_ATTR_EXT_DOUTPUT_INVERT,
&g_RSHMC8015_ATTR_EXT_SENSOR_STATE,
&g_RSHMC8015_ATTR_EXT_SENSOR_MODE,
&g_RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE,
&g_RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO,
&g_RSHMC8015_ATTR_EXT_SENSOR_RANGE,
&g_RSHMC8015_ATTR_VIEW_MODE,
&g_RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE,
&g_RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE,
&g_RSHMC8015_ATTR_VIEW_NORM_FUNCTION,
&g_RSHMC8015_ATTR_VIEW_HARM_SELECT,
&g_RSHMC8015_ATTR_VIEW_HARM_SOURCE,
&g_RSHMC8015_ATTR_VIEW_HARM_NUMBER,
&g_RSHMC8015_ATTR_VIEW_HARM_SCALING,
&g_RSHMC8015_ATTR_VIEW_HARM_SUBSET,
&g_RSHMC8015_ATTR_INTEGRATOR_STATE,
&g_RSHMC8015_ATTR_INTEGRATOR_MODE,
&g_RSHMC8015_ATTR_INTEGRATOR_DURATION,
&g_RSHMC8015_ATTR_INTEGRATOR_RESET,
&g_RSHMC8015_ATTR_INTEGRATOR_START,
&g_RSHMC8015_ATTR_INTEGRATOR_STOP,
&g_RSHMC8015_ATTR_LOGGING_STATE,
&g_RSHMC8015_ATTR_LOGGING_PAGE,
&g_RSHMC8015_ATTR_LOGGING_MODE,
&g_RSHMC8015_ATTR_LOGGING_TIME,
&g_RSHMC8015_ATTR_LOGGING_COUNT,
&g_RSHMC8015_ATTR_ID_QUERY_RESPONSE,
&g_RSHMC8015_ATTR_DISPLAY_CLEAR,
&g_RSHMC8015_ATTR_DISPLAY_TEXT,
&g_RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT,
&g_RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH,
&g_RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT,
&g_RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED,
&g_RSHMC8015_ATTR_SYSTEM_START_BEEP,
&g_RSHMC8015_ATTR_SYSTEM_NAME,
&g_RSHMC8015_ATTR_SYSTEM_ERROR,
&g_RSHMC8015_ATTR_SYSTEM_LOCAL,
&g_RSHMC8015_ATTR_SYSTEM_REMOTE,
&g_RSHMC8015_ATTR_SYSTEM_RWLOCK,
&g_RSHMC8015_ATTR_SYSTEM_VERSION,
&g_RSHMC8015_ATTR_SYSTEM_DEVICE,
&g_RSHMC8015_ATTR_SYSTEM_SHUTDOWN,
&g_RSHMC8015_ATTR_SYSTEM_SOFTWARE,
&g_RSHMC8015_ATTR_SYSTEM_HARDWARE,
&g_RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER,
&g_RSHMC8015_ATTR_STATUS_PRESET,

VI_NULL
};
