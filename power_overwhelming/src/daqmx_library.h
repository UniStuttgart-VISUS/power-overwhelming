// <copyright file="daqmx_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_LIBRARY_H)
#define _PWROWG_DAQMX_LIBRARY_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_DAQMX)

#include <NIDAQmx.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __POWER_OVERWHELMING_DAQMX_FUNC(f) decltype(&::f) _##f = nullptr

/// <summary>
/// Wrapper for lazily loading the NI-DAQmx library.
/// </summary>
class PWROWG_TEST_API daqmx_library final : library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error">If the library could not
    /// be loaded, eg because NI-DAQmx is not installed on the system.
    /// </exception>
    static const daqmx_library& instance(void);

    //__POWER_OVERWHELMING_DAQMX_FUNC(CVIAbsoluteTimeFromLocalCalendar);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgAnlgEdgeStartTrig);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgImplicitTiming);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgInputBuffer);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgOutputBuffer);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgSampClkTiming);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCfgTimeStartTrig);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxClearTask);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCreateAICalculatedPowerChan);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCreateAICurrentChan);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCreateAIVoltageChan);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxCreateTask);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetAIMax);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetAIMin);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevAICurrentRngs);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevAIPhysicalChans);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevAIVoltageRngs);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevAOPhysicalChans);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevBusType);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevIsSimulated);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevProductType);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevSerialNum);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevTerminals);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetSysDevNames);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxDisableStartTrig);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetErrorString);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetExtendedErrorInfo);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxIsTaskDone);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxReadAnalogF64);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxRegisterDoneEvent);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxRegisterEveryNSamplesEvent);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxRegisterSignalEvent);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxResetDevice);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxSendSoftwareTrigger);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxStartTask);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxStopTask);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxWaitForNextSampleClock);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxWaitForValidTimestamp);
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxWaitUntilTaskDone);

private:

    daqmx_library(void);
};

#undef __POWER_OVERWHELMING_DAQMX_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_LIBRARY_H) */
