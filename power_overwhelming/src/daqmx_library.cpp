// <copyright file="daqmx_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "daqmx_library.h"


#define __POWER_OVERWHELMING_DAQMX_FUNC(f) \
    this->_##f = this->get_function<decltype(this->_##f)>(#f)


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_library::instance
 */
const PWROWG_DETAIL_NAMESPACE::daqmx_library&
PWROWG_DETAIL_NAMESPACE::daqmx_library::instance(void) {
    static const daqmx_library instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_library
 */
PWROWG_DETAIL_NAMESPACE::daqmx_library::daqmx_library(void)
#if defined(_WIN32)
        : library_base(TEXT("nicaiu.dll")) {
#endif /* defined(_WIN32) */
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
    __POWER_OVERWHELMING_DAQMX_FUNC(DAQmxGetDevAIPhysicalChans);
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
}

#undef __POWER_OVERWHELMING_DAQMX_FUNC
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
