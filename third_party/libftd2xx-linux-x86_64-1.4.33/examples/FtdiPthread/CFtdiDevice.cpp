#include <iostream>
#include <vector>
#include <thread>
#include "CFtdiDevice.h"


CFtdiDevice::CFtdiDevice(FT_DEVICE_LIST_INFO_NODE ftdiNode)
{
    std::vector<std::thread> apthread;

    m_serial = ftdiNode.SerialNumber;
    m_description = ftdiNode.Description;
    m_handle = nullptr;
}

CFtdiDevice::~CFtdiDevice()
{
    StopThreads();
}

void CFtdiDevice::StopThreads()
{
    if (m_pReadThread != nullptr && m_pReadThread->joinable())
    {
        m_pReadThread->join();
        m_pReadThread = nullptr;
    }

    if (m_pAckThread != nullptr && m_pAckThread->joinable())
    {
        m_pAckThread->join();
        m_pAckThread = nullptr;
    }
}

void CFtdiDevice::OpenDevice(int deviceNumber)
{
    if (m_handle != nullptr)
    {
        LogMessage("Device is already open");
        return;
    }

    FT_STATUS status = FT_Open(deviceNumber, &m_handle);
    if (status == FT_OK)
    {
        std::cout << "Opened device " << m_serial << " has handle " << m_handle << std::endl;

        LogMessage("Set usb parameters");

        FT_STATUS ftStatus;
        ftStatus = FT_SetUSBParameters(m_handle, 64, 64 * 1024);
        std::cout << m_serial << " FT_SetUSBParameters result " << ftStatus << std::endl;

        ftStatus = FT_SetTimeouts(m_handle, 1, 1);
        std::cout << m_serial << " FT_SetTimeouts result " << ftStatus << std::endl;
        FT_SetLatencyTimer(m_handle,2);
        LogMessage("Init event handle");

        m_pEventHandle = NativeCreateFtdiEventHandle();
        std::cout << "Device " << m_serial << " Event handle is " << m_pEventHandle << std::endl;

        LogMessage("Registering event handle with FT_SetEventNotification");
        ftStatus = FT_SetEventNotification(m_handle, FT_EVENT_RXCHAR, m_pEventHandle);

        std::cout << "Device " << m_serial << " FT_SetEventNotification result " << ftStatus << std::endl;
    }
    else
    {
        std::cout << "Failed to open device " << m_serial << std::endl;
    }
}


void CFtdiDevice::CloseDevice()
{
    if (m_handle == nullptr)
    {
        LogMessage("Device is already closed");
        return;
    }

    FT_STATUS status = FT_Close(m_handle);
    if (status == FT_OK)
    {
        LogMessage("Closed device ");
        m_handle = nullptr;
    }
    else
    {
        std::cout << "Failed to close device " << m_serial << " has handle " << m_handle << std::endl;
    }

    StopThreads();
}

DWORD CFtdiDevice::GetNumBytesAvailable()
{
    DWORD numTxBytesAvailable;
    DWORD numRxBytesAvailable;
    DWORD eventStatus;

    // check how much data is available to read
    FT_STATUS ftStatus = FT_GetStatus(m_handle, &numRxBytesAvailable, &numTxBytesAvailable, &eventStatus);

    if (FT_OK != ftStatus)
    {
        std::cout << "Device " << m_serial << " FT_GetStatus Failed, FT_STATUS: " << ftStatus << std::endl;
    }
    else
    {
        m_maxRxBytes = (numRxBytesAvailable > m_maxRxBytes) ? numRxBytesAvailable : m_maxRxBytes;
    }

    return numRxBytesAvailable;
}


void CFtdiDevice::ReadThread()
{
    DWORD numTxBytesAvailable;
    DWORD numRxBytesAvailable;
    DWORD eventStatus;
    std::vector<unsigned char> rxBuffer(255);
    DWORD numBytesRead = 0;
    bool logMessage = false;

    LogMessage("ReadThread");

    while (m_handle != nullptr)
    {
        // check how much data is available to read
        FT_STATUS ftStatus = FT_GetStatus(m_handle, &numRxBytesAvailable, &numTxBytesAvailable, &eventStatus);
        if (FT_OK != ftStatus)
        {
            std::cout << "Device " << m_serial<< " FT_GetStatus Failed, FT_STATUS: " << ftStatus << std::endl;
            //break;
        }
        else
        {
            m_maxRxBytes = (numRxBytesAvailable > m_maxRxBytes)? numRxBytesAvailable: m_maxRxBytes;
            if(logMessage)
            {
                std::cout << "Device " << m_serial << " FT_GetStatus said " << numRxBytesAvailable << " bytes available" << std::endl;
                logMessage = false;
            }
        }

        if (numRxBytesAvailable == 0)
        {
            //std::cout << "No Data, wait for data to be signalled" << std::endl;
            int retValue = NativeEventTimedWait(m_pEventHandle, 4, 321);

            if (retValue != 0)
            {
                std::cout << "Device " << m_serial << " WaitForData complete. Result: " << retValue << ", total Tx "<< m_totalTxBytes << ", total Rx " << m_totalRxBytes << ", maxBytes " << m_maxRxBytes << std::endl;
                logMessage = true;
            }
            continue;
        }
        else if(numRxBytesAvailable > 32000)
        {
            std::cout << "Device " << m_serial << " FT_GetStatus said " << numRxBytesAvailable << " bytes available" << std::endl;
        }

        // ensure the buffer is large enough
        if (rxBuffer.size() < numRxBytesAvailable)
        {
            rxBuffer.resize(numRxBytesAvailable);
        }

        // read the waiting data back
        ftStatus = FT_Read(m_handle, &rxBuffer[0], numRxBytesAvailable, &numBytesRead);
        if (FT_OK != ftStatus)
        {
            std::cout << "Device " << m_serial << " FT_Read Failed, FT_STATUS: " << ftStatus << std::endl;
            break;
        }
        m_totalRxBytes += numBytesRead;

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CFtdiDevice::IsTileThread()
{
    unsigned char txBuffer[] = { 
        0xFF, 0x1B, 0x01, 0x02, 0x1E,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
        0xFF, 0x63, 0x02, 0x01, 0x00, 0x66,
    };

    unsigned char txMessageSize = 65;
    DWORD numBytesWritten;

    LogMessage("IsTile Thread!");

    while (m_handle != nullptr)
    {
        // send the ack message
        FT_STATUS ftStatus = FT_Write(m_handle, txBuffer, txMessageSize, &numBytesWritten);
        if (FT_OK != ftStatus)
        {
            std::cout << "Device " << m_serial << " FT_Write Failed, FT_STATUS: " << ftStatus << std::endl;
            break;
        }

        m_totalTxBytes += numBytesWritten;

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    LogMessage("Ftdi device ack thread stopped.");
}

void CFtdiDevice::StartThreads()
{
    if (m_pReadThread == nullptr)
    {
        LogMessage("Start ReadThread!");
        m_pReadThread = new std::thread(&CFtdiDevice::ReadThread, this);
    }
    else
    {
        LogMessage("Already created ReadThread.");
    }

    // init tile message
    unsigned char txMessageSize = 4;
    unsigned char txBuffer[] = { 0xFF, 0x05, 0x00, 0x05 };
    DWORD numBytesWritten;
    
    FT_STATUS ftStatus = FT_Write(m_handle, txBuffer, txMessageSize, &numBytesWritten);
    if (FT_OK != ftStatus)
    {
        std::cout << "FT_Write init message Failed, FT_STATUS: " << ftStatus << std::endl;
    }

    if (m_pAckThread == nullptr)
    {
        LogMessage("Start isTile thread!");
        m_pAckThread = new std::thread(&CFtdiDevice::IsTileThread, this);
    }
    else
    {
        LogMessage("Already created ack thread.");
    }
}



EVENT_HANDLE* CFtdiDevice::NativeCreateFtdiEventHandle()
{
    // Create an EVENT_HANDLE to use with FTDI.
    EVENT_HANDLE* pEventHandle = new EVENT_HANDLE();
    // Attempt to initialise the pthread condition variable.

    int condRetVal = pthread_cond_init(&(pEventHandle->eCondVar), NULL);
    if (condRetVal != 0)
    {
        LogMessage("NativeCreateFtdiEventHandle call to pthread_cond_init failed with error code: " + std::to_string(condRetVal));

        // Delete the EVENT_HANDLE that we created, since we can't use it now.
        delete pEventHandle;

        // return NULL to indicate that we didn't create an EVENT_HANDLE.
        return NULL;
    }

    // Attempt to initialise the pthread mutex.
    int mutexRetval = pthread_mutex_init(&(pEventHandle->eMutex), NULL);
    if (mutexRetval != 0)
    {
        LogMessage("NativeCreateFtdiEventHandle call to pthread_mutex_init failed with error code: " + std::to_string(mutexRetval));

        // Destroy the pthread condition variable that we created.
        pthread_cond_destroy(&(pEventHandle->eCondVar));

        // Delete the EVENT_HANDLE that we created, since we can't use it now.
        delete pEventHandle;

        // return NULL to indicate that we didn't create an EVENT_HANDLE.
        return NULL;
    }

    // Success, return the valid pEventHandle.
    return pEventHandle;
}


int CFtdiDevice::NativeEventTimedWait(EVENT_HANDLE* pEventHandle, int timeoutSecs, int timeoutMs)
{
    if (pEventHandle == NULL)
    {
        LogMessage("NativeEventTimedWait called with NULL pEventHandle");
        return false;
    }

    // Convert the specified timeoutSecs and timeoutMs into a timespec structure for use with pthread_cond_timedwait.
    // We do this before we perform the lock, to prevent unnecessary time inside the lock.

    // https://www.ibm.com/docs/en/zos/2.3.0?topic=lf-pthread-cond-timedwait-pthread-cond-timedwait64-wait-condition-variable
    // 
    // Below is what the timespec structure is expected to contain for our call to pthread_cond_timedwait. We're not currently using
    // the '64' long version of the methods, we will need to work this out in future.
    // 
    // tv_sec
    //      The time to wait for the condition signal. It is expressed in seconds from midnight, January 1, 1970 UTC.
    //      The value specified must be greater than or equal to current calendar time expressed in seconds since midnight, January 1, 1970 UTC 
    //      and less than 2, 147, 483, 648 seconds.
    // tv_nsec
    //      The time in nanoseconds to be added to tv_sec to determine when to stop waiting.
    //      The value specified must be greater than or equal to zero(0) and less than 1, 000, 000, 000 (1, 000 million).
    //

    struct timespec timeout;

    // Get the time since the Unix epoch.
    int timeRetVal = clock_gettime(CLOCK_REALTIME, &timeout);
    if (timeRetVal != 0)
    {
        LogMessage("NativeEventTimedWait call to clock_gettime failed with error code: " + std::to_string(timeRetVal));

        // Fail early, as we can't continue without absolute time measurement.
        return false;
    }

    // Add in the required timeout, converting from milliseconds to nanoseconds (multiplying by 1 million).
    timeout.tv_sec += timeoutSecs;
    timeout.tv_nsec += (timeoutMs * 1000000);

    // Check that we didn't go over the one thousand million barrier, otherwise wrap around, and add on one second for doing so.
    if (timeout.tv_nsec >= 1000000000)
    {
        timeout.tv_sec += 1;
        timeout.tv_nsec -= 1000000000;
    }

    int mutexStatus;
    int waitRetVal;
    int maxRetryCount = 5;

    do
    {
        auto beforeGettingMutex = std::chrono::high_resolution_clock::now();
        mutexStatus = pthread_mutex_lock(&pEventHandle->eMutex);
        auto afterGettingMutex = std::chrono::high_resolution_clock::now();
        auto getMutexDuration = std::chrono::duration_cast<std::chrono::milliseconds>(afterGettingMutex - beforeGettingMutex).count();

        if (getMutexDuration > 10)
        {
            std::cout << m_serial <<" acquiring mutex took " << getMutexDuration << "ms." << std::endl;
        }

        // Check the status of the lock.
        if (mutexStatus != 0)
        {
            LogMessage("NativeEventTimedWait call to pthread_mutex_lock failed with error code: " + std::to_string(mutexStatus));

            // Locking failed, can't call pthread_cond_wait and no need to unlock so return failure here.
            return false;
        }

        // Attempt to perform timed wait. This can often report timeout with ETIMEDOUT, which we can ignore as this is 
        // a common return code when the tile is idle and not sending data.
        auto beforeThreadWait = std::chrono::high_resolution_clock::now();
        waitRetVal = pthread_cond_timedwait(&(pEventHandle->eCondVar), &(pEventHandle->eMutex), &timeout);
        auto afterThreadWait = std::chrono::high_resolution_clock::now();
        auto waitDuration = std::chrono::duration_cast<std::chrono::milliseconds>(afterThreadWait - beforeThreadWait).count();

        mutexStatus = pthread_mutex_unlock(&pEventHandle->eMutex);
        // Check the status of the lock.
        if (mutexStatus != 0)
        {
            LogMessage("pthread_mutex_unlock failed with error code: " + std::to_string(mutexStatus));
            return false;
        }

        if (waitDuration > 200)
        {
            DWORD bytesAvailable = GetNumBytesAvailable();
            std::cout << "### " << m_serial << ". pThread wait took " << waitDuration << "ms. RxBytes available: " << bytesAvailable << std::endl;
        }

        if (m_handle == nullptr)
        {
            LogMessage("NativeEventTimedWait: Device has been closed");
            return waitRetVal;
        }
        else if (waitRetVal == ETIMEDOUT)
        {
            timeout.tv_sec += 2;
            std::cout << "### Retrying " << m_serial << " count " << maxRetryCount << std::endl;
        }
        else if (waitRetVal != 0)
        {
            // Log the important failure.
            LogMessage("NativeEventTimedWait call to pthread_cond_wait failed with: " + std::to_string(waitRetVal));
        }
        else
        {
            return waitRetVal;
        }
    } while (--maxRetryCount > 0);
    
    // Successful when pthread_cond_timedwait reports 0 for success or ETIMEDOUT for a typical timeout when tile is idle.
    return waitRetVal;
}


void CFtdiDevice::LogMessage(std::string logMessage)
{
    // Log every message (MUST be important!).
    std::cout << "Device " << m_serial << " " << logMessage << std::endl;
}
