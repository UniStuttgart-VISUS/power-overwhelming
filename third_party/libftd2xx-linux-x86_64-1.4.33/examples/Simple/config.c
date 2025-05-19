#include <stdio.h>
#include<stdlib.h>
#include "../ftd2xx.h"
static
const char * statusString(FT_STATUS status)
{
    switch (status)
    {
        case FT_OK:
            return "OK";
        case FT_INVALID_HANDLE:
            return "INVALID_HANDLE";
        case FT_DEVICE_NOT_FOUND:
            return "DEVICE_NOT_FOUND";
        case FT_DEVICE_NOT_OPENED:
            return "DEVICE_NOT_OPENED";
        case FT_IO_ERROR:
            return "IO_ERROR";
        case FT_INSUFFICIENT_RESOURCES:
            return "INSUFFICIENT_RESOURCES";
        case FT_INVALID_PARAMETER:
            return "INVALID_PARAMETER";
        case FT_INVALID_BAUD_RATE:
            return "INVALID_BAUD_RATE";
        case FT_DEVICE_NOT_OPENED_FOR_ERASE:
            return "DEVICE_NOT_OPENED_FOR_ERASE";
        case FT_DEVICE_NOT_OPENED_FOR_WRITE:
            return "DEVICE_NOT_OPENED_FOR_WRITE";
        case FT_FAILED_TO_WRITE_DEVICE:
            return "FAILED_TO_WRITE_DEVICE";
        case FT_EEPROM_READ_FAILED:
            return "EEPROM_READ_FAILED";
        case FT_EEPROM_WRITE_FAILED:
            return "EEPROM_WRITE_FAILED";
        case FT_EEPROM_ERASE_FAILED:
            return "EEPROM_ERASE_FAILED";
        case FT_EEPROM_NOT_PRESENT:
            return "EEPROM_NOT_PRESENT";
        case FT_EEPROM_NOT_PROGRAMMED:
            return "EEPROM_NOT_PROGRAMMED";
        case FT_INVALID_ARGS:
            return "INVALID_ARGS";
        case FT_NOT_SUPPORTED:
            return "NOT_SUPPORTED";
        case FT_OTHER_ERROR:
            return "OTHER_ERROR";
        case FT_DEVICE_LIST_NOT_READY:
            return "DEVICE_LIST_NOT_READY";
        default:
            return "unknown error";
    }
}

int main(int argc, char *argv[])
{
	FT_STATUS	ftStatus = FT_OK;
	FT_HANDLE	ftHandle = NULL;;
    FT_DEVICE_LIST_INFO_NODE *devInfo = NULL;
    DWORD       numDevs = 0;
    int         i = 0;
	int         portNumber;
	portNumber = 0;
#if 1
	ftStatus = FT_Open(portNumber, &ftHandle);
	if (ftStatus != FT_OK) 
	{
		/* FT_Open can fail if the ftdi_sio module is already loaded. */
		printf("FT_Open(%d) failed (error %d).\n", portNumber, (int)ftStatus);
		printf("Use lsmod to check if ftdi_sio (and usbserial) are present.\n");
		printf("If so, unload them using rmmod, as they conflict with ftd2xx.\n");
		return 1;
	}
#endif
while(i < 5){
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus != FT_OK) 
    {
        printf("FT_CreateDeviceInfoList failed (%s)\n", 
               statusString(ftStatus));
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
        printf("FT_GetDeviceInfoList failed (%s)\n",
               statusString(ftStatus));
        goto exit;
    }   
    printf("=======================< %d >=====================\n",++i);
}

exit:

    if (ftHandle != NULL)
        (void)FT_Close(ftHandle);
    
    if(devInfo != NULL)
        free(devInfo);

    return 0;

}