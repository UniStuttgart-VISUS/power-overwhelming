#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "ftd2xx.h"
#include "display.h"
#include "pdConfig.h"

static void writeEeprom(DWORD locationId, FT_DEVICE deviceType)
{
    FT_STATUS            ftStatus;
    FT_HANDLE            ftHandle = (FT_HANDLE)NULL;
    char                 manufacturer[64] = "FTDI";
    char                 manufacturerId[64] = "FT";
    char                 description[64] = "USB-Serial Converter";
    char                 serialNumber[64] = "FT98MV7Y";
    Eeprom_Pd_t         *pPDEEprom = NULL;
    FT_EEPROM_HEADER    *header; 

    ftStatus = FT_OpenEx((PVOID)(uintptr_t)locationId, 
                         FT_OPEN_BY_LOCATION, 
                         &ftHandle);
    if (ftStatus != FT_OK)
    {
        printf("FT_OpenEx failed (error code %d)\n", (int)ftStatus);
        goto exit;
    }

    /* Allocate enough to hold biggest EEPROM structure */
    pPDEEprom = calloc(1, sizeof(*pPDEEprom));
    if (pPDEEprom == NULL)
    {
        printf("pPDEEprom Allocation failure.\n");
        goto exit;
    }
    
    /* EEPROM_HEADER is first member of every type of eeprom */
    header = (FT_EEPROM_HEADER *)pPDEEprom;
    header->deviceType = deviceType;
    header->VendorId = 0x0403;
    header->ProductId = 0x6041;
    // ProductId is device-specific, assigned below.
    header->SerNumEnable = 1;  // non-zero if serial number to be used
    header->MaxPower = 0x0064;    // 0 < MaxPower <= 500
    header->SelfPowered = 0;   // 0 = bus powered, 1 = self powered
    header->RemoteWakeup = 0;  // 0 = not capable, 1 = capable
    header->PullDownEnable = 0;// non-zero if pull down in suspend enabled

    printf("Setting default PD Configuration...\n");
    switch(deviceType)
    {
        default:
        case FT_DEVICE_BM:
            // No further info to display
            break;

        case FT_DEVICE_2233HP:
            PD_SetDefaultConfig(&pPDEEprom->ee2233pd.pd);
            break;

        case FT_DEVICE_4233HP:
            PD_SetDefaultConfig(&pPDEEprom->ee4233pd.pd);
            break;

        case FT_DEVICE_4232HP:
            PD_SetDefaultConfig(&pPDEEprom->ee4232pd.pd);
            break;
        case FT_DEVICE_2232HP:
            PD_SetDefaultConfig(&pPDEEprom->ee2232pd.pd);
            break;

        case FT_DEVICE_233HP:
            PD_SetDefaultConfig(&pPDEEprom->ee233pd.pd);
            break;

        case FT_DEVICE_232HP:
            PD_SetDefaultConfig(&pPDEEprom->ee232pd.pd);
            break;
    }


    ftStatus = FT_EEPROM_Program(ftHandle,
                                 pPDEEprom,
                                 sizeof(*pPDEEprom),
                                 manufacturer,
                                 manufacturerId,
                                 description,
                                 serialNumber);
    if (ftStatus != FT_OK)
    {
        printf("FT_EEPROM_Program failed (error code %d)\n", (int)ftStatus);
        goto exit;
    }
    
    switch(deviceType)
    {
        default:
        case FT_DEVICE_BM:
            // No further info to display
            break;

        case FT_DEVICE_2233HP:
            DisplayEepromPD(&pPDEEprom->ee2233pd.pd, deviceType);
            break;

        case FT_DEVICE_4233HP:
            DisplayEepromPD(&pPDEEprom->ee4233pd.pd, deviceType);  
            break;

        case FT_DEVICE_4232HP:
            DisplayEepromPD(&pPDEEprom->ee4232pd.pd, deviceType);
            break;

        case FT_DEVICE_2232HP:
            DisplayEepromPD(&pPDEEprom->ee2232pd.pd, deviceType);
            break;

        case FT_DEVICE_233HP:
            DisplayEepromPD(&pPDEEprom->ee233pd.pd, deviceType);
            break;

        case FT_DEVICE_232HP:
            DisplayEepromPD(&pPDEEprom->ee232pd.pd, deviceType);
            break;
    }

exit:
    (void)FT_Close(ftHandle);
    free(pPDEEprom);
    return ;
}

int main (int argc, char *argv[])
{
    FT_STATUS                 ftStatus;
    FT_DEVICE_LIST_INFO_NODE *devInfo = NULL;
    DWORD                     numDevs = 0;

    /* Unused parameters */
    (void)argc;
    (void)argv;

    /* Discover how many FTDI devices are connected */
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus != FT_OK)
    {
        printf("FT_CreateDeviceInfoList failed (error code %d)\n",
               (int)ftStatus);
        goto exit;
    }

    if (numDevs == 0)
    {
        printf("No devices connected.\n");
        goto exit;
    }

    /* Allocate storage */
    devInfo = calloc((size_t)numDevs,
                     sizeof(FT_DEVICE_LIST_INFO_NODE));
    if (devInfo == NULL)
    {
        printf("Allocation failure.\n");
        goto exit;
    }

    /* Populate the list of info nodes */
    ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
    if (ftStatus != FT_OK)
    {
        printf("FT_GetDeviceInfoList failed (error code %d)\n",
               (int)ftStatus);
        goto exit;
    }

    printf("No of Devices : %d \n",(int)numDevs);
    /* Display info (including EEPROM fields) for each connected FTDI device */
    printf("\n========================DEV(0) INFO ============================\n"); 
    printf("    Flags = 0x%x\n",devInfo[0].Flags);
    printf("    Type = 0x%x\n",devInfo[0].Type);
    printf("    ID = 0x%04x\n",devInfo[0].ID);
    printf("    LocId = 0x%x\n",devInfo[0].LocId);
    printf("    SerialNumber = %s\n",devInfo[0].SerialNumber);
    printf("    Description = %s\n",devInfo[0].Description);
    printf("    ftHandle = %p\n",devInfo[0].ftHandle);
    printf("========================END DEV INFO============================\n");
    writeEeprom(devInfo[0].LocId, devInfo[0].Type);



exit:
    free(devInfo);
    return 0;
}
