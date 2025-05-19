#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "ftd2xx.h"
#include "display.h"

bool once = TRUE;

static void readEeprom (DWORD locationId, FT_DEVICE deviceType)
{
    FT_STATUS            ftStatus;
    FT_HANDLE            ftHandle = (FT_HANDLE)NULL;
    char                 manufacturer[64];
    char                 manufacturerId[64];
    char                 description[64];
    char                 serialNumber[64];
    Eeprom_GenericPd      *eeprom = NULL;
    FT_EEPROM_HEADER    *header;

    ftStatus = FT_OpenEx((PVOID)(uintptr_t)locationId,
                         FT_OPEN_BY_LOCATION,
                         &ftHandle);
    if (ftStatus != FT_OK)
    {
        printf("%s: FT_OpenEx failed (error code %d)\n",__FILE__, (int)ftStatus);
        goto exit;
    }

    /* Allocate enough to hold biggest EEPROM structure */
    eeprom = calloc(1, sizeof(*eeprom));
    if (eeprom == NULL)
    {
        printf("Allocation failure.\n");
        goto exit;
    }

    /* EEPROM_HEADER is first member of every type of eeprom */
    header = (FT_EEPROM_HEADER *)eeprom;
    header->deviceType = deviceType;
    printf("%s: deviceType = %s\n",__FILE__,(char *)deviceName( deviceType));
    manufacturer[0] = '\0';
    manufacturerId[0] = '\0';
    description[0] = '\0';
    serialNumber[0] = '\0';

    ftStatus = FT_EEPROM_Read(ftHandle,
                              eeprom,
                              sizeof(*eeprom),
                              manufacturer,
                              manufacturerId,
                              description,
                              serialNumber);
    if (ftStatus != FT_OK)
    {
        printf("%s: FT_EEPROM_Read failed (error code %d)\n",__FILE__, (int)ftStatus);
        goto exit;
    }

    printf("%s: Manufacturer = %s\n",__FILE__, manufacturer);
    printf("%s: ManufacturerId = %s\n",__FILE__, manufacturerId);
    printf("%s: Description = %s\n",__FILE__, description);
    printf("%s: Serial number = %s\n",__FILE__, serialNumber);

    DisplayHeader((FT_EEPROM_HEADER *)eeprom);

    switch(deviceType)
    {
        default:
        case FT_DEVICE_BM:
            // No further info to display
            break;

        case FT_DEVICE_2233HP:
            DisplayEepromPD(&eeprom->ee2233pd.pd, deviceType);
            break;

        case FT_DEVICE_4233HP:
            DisplayEepromPD(&eeprom->ee4233pd.pd, deviceType);
            break;

        case FT_DEVICE_4232HP:
            DisplayEepromPD(&eeprom->ee4232pd.pd, deviceType);
            break;

        case FT_DEVICE_2232HP:
            DisplayEepromPD(&eeprom->ee2232pd.pd, deviceType);
            break;

        case FT_DEVICE_233HP:
            DisplayEepromPD(&eeprom->ee233pd.pd, deviceType);
            break;

        case FT_DEVICE_232HP:
            DisplayEepromPD(&eeprom->ee232pd.pd, deviceType);
            break;
    }

    printf("\n");

exit:
    (void)FT_Close(ftHandle);
    free(eeprom);
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
        printf("%s: FT_CreateDeviceInfoList failed (error code %d)\n",__FILE__,(int)ftStatus);
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
        printf("%s: FT_GetDeviceInfoList failed (error code %d)\n",__FILE__,
               (int)ftStatus);
        goto exit;
    }

    printf("%s: No of Devices : %d \n",__FILE__,(int)numDevs);
    /* Display info (including EEPROM fields) for each connected FTDI device */

    printf("%s: Flags = 0x%x\n",__FILE__,devInfo[0].Flags);
    printf("%s: Type = 0x%x\n",__FILE__,devInfo[0].Type);
    printf("%s: ID = 0x%04x\n",__FILE__,devInfo[0].ID);
    printf("%s: LocId = 0x%x\n",__FILE__,devInfo[0].LocId);
    printf("%s: SerialNumber = %s\n",__FILE__,devInfo[0].SerialNumber);
    printf("%s: Description = %s\n",__FILE__,devInfo[0].Description);
    printf("%s: ftHandle = %p\n",__FILE__,devInfo[0].ftHandle);
    readEeprom(devInfo[0].LocId, devInfo[0].Type);

exit:
    free(devInfo);
    return 0;
}
