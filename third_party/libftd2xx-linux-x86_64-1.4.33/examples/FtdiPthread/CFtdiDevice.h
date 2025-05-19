#pragma once
#include "ftd2xx.h"
#include <vector>
#include <thread>
#include <string>

//std::vector<std::thread> m_threadList;

class CFtdiDevice
{
public:
    CFtdiDevice(FT_DEVICE_LIST_INFO_NODE ftdiNode);
    ~CFtdiDevice();
    void OpenDevice(int deviceNumber);
    void CloseDevice();
    void ReadThread();

    void StartThreads();
    void IsTileThread();

    std::string GetSerial()
    {
        return m_serial;
    }

    std::string GetDescription()
    {
        return m_description;
    }

    int GetRxTotal() { return m_totalRxBytes; }
    int GetTxTotal() { return m_totalTxBytes; }
    int GetRxMax() { return m_maxRxBytes; }

private:
    std::string m_serial;
    std::string m_description;
    FT_HANDLE m_handle = nullptr;
    int m_totalTxBytes = 0;
    int m_totalRxBytes = 0;
    int m_maxRxBytes = 0;

    std::thread* m_pAckThread = nullptr;
    std::thread* m_pReadThread = nullptr;

    EVENT_HANDLE* m_pEventHandle = nullptr;

    void StopThreads();
    DWORD GetNumBytesAvailable();

    EVENT_HANDLE* NativeCreateFtdiEventHandle();
    int NativeEventTimedWait(EVENT_HANDLE* pEventHandle, int timeoutSecs, int timeoutMs);
    void LogMessage(std::string logMessage);
};

