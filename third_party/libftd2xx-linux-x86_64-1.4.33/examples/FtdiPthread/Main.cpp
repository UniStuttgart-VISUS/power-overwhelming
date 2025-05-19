#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <iomanip>
#include <chrono>
#include <ctime>

#include "WinTypes.h"
#include "ftd2xx.h"
#include "CFtdiDevice.h"


//static bool s_stopThread = false;

static int WaitForExit()
{
    return std::cin.get();
}

// Populates a vector of FT_DEVICE_LIST_INFO_NODE with the currently detected devices
bool DetectFtdiDevices(std::vector<FT_DEVICE_LIST_INFO_NODE>& detectedDevices)
{
    // clear any existing entries
    detectedDevices.clear();

    // get the number of devices
    DWORD numDevices = 0;
    FT_STATUS status = FT_CreateDeviceInfoList(&numDevices);
    if (status != FT_OK)
    {
        std::cout << "Failed device detection. FT_STATUS :" << status << std::endl;
        return false;
    }

    // ensure that there is enough space in the vector to store the device details
    if (detectedDevices.size() < numDevices)
    {
        detectedDevices.resize(numDevices);
    }

    // retrieve the device information from Ftdi.
    status = FT_GetDeviceInfoList(&detectedDevices[0], &numDevices);
    if (status != FT_OK)
    {
        std::cout << "FT_GetDeviceInfoList failed with " << status << std::endl;
        return false;
    }

    return true;
}

// Prints the details for all the Ftdi devices
void PrintFtdiDevices(std::vector<FT_DEVICE_LIST_INFO_NODE>& devices)
{
    DWORD numDevices = devices.size();

    std::cout << "Detected " << numDevices << " devices" << std::endl;

    for (DWORD deviceIndex = 0; deviceIndex < numDevices; ++deviceIndex)
    {
        auto device = devices[deviceIndex];
        std::cout << " Device " << deviceIndex << ", Serial '" << device.SerialNumber << "' Description '" << device.Description << "'" << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

// The actual test program
int main()
{
    std::cout << "Registering our vids and pids" << std::endl;

    // add the vid and pid of our device to the ones to look for.
    FT_SetVIDPID(0x31e9, 0x0021);
    FT_SetVIDPID(0x31e9, 0x0027);
    FT_SetVIDPID(0x31e9, 0x0028);

    // get a list for the detected devices
    std::vector<FT_DEVICE_LIST_INFO_NODE> ftdiDevices;

    // get the currently connected Ftdi devices
    std::cout << "Detecting devices..." << std::endl;
    if (!DetectFtdiDevices(ftdiDevices))
    {
        std::cout << "DetectFtdiDevices error." << std::endl;
        return 1;
    }

    // debug show the detected devices
    PrintFtdiDevices(ftdiDevices);

    std::vector<CFtdiDevice*> ourDevices;

    // open each detected device 
    for (size_t i = 0; i< ftdiDevices.size(); ++i)
    {
        auto pDevice = new CFtdiDevice(ftdiDevices[i]);
        ourDevices.push_back(pDevice);
        std::cout << "Opening " << pDevice->GetSerial() << std::endl;
        // open the device
        pDevice->OpenDevice(i);
        // start the threads
        pDevice->StartThreads();
    }

    // wait for input to stop the program
    std::cout << "Press enter to quit" << std::endl;

    std::future<int> future = std::async(WaitForExit);
    std::chrono::milliseconds checkLoop(30000);
    while(future.wait_for(checkLoop) != std::future_status::ready)
    {
        auto timeNow = std::time(nullptr);
        std::tm localTime = *std::localtime(&timeNow);
        std::cout << std::put_time(&localTime, "%H:%M:%S") << " Waiting for end." << std::endl;

        for (size_t i = 0; i < ourDevices.size(); ++i)
        {
            auto device = ourDevices[i];
            std::cout << "Device " << device->GetSerial() << " RxTotal: " << device->GetRxTotal() << ", TxTotal : " << device->GetTxTotal() << ", MaxRx " << device->GetRxMax() << std::endl;
        }
    }

    std::cout << "ending Program" << std::endl;

    for (size_t i = 0; i < ourDevices.size(); ++i)
    { 
        ourDevices[i]->CloseDevice();
    }

    std::cout << "Program complete" << std::endl;
    return 0;
}

