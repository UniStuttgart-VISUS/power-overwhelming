#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "ftd2xx.h"
#include "pdConfig.h"

static const char *deviceName(FT_DEVICE deviceType)
{
    switch(deviceType)
    {
        default: return "Unknown";
        case FT_DEVICE_2233HP: return "FT_DEVICE_2233HP";
            break;
        case FT_DEVICE_4233HP: return "FT_DEVICE_4233HP";
            break;
        case FT_DEVICE_4232HP: return "FT_DEVICE_4232HP";
            break;
        case FT_DEVICE_2232HP: return "FT_DEVICE_2232HP";
            break;
        case FT_DEVICE_233HP: return "FT_DEVICE_233HP";
            break;
        case FT_DEVICE_232HP: return "FT_DEVICE_232HP";
            break;
    }
}

void PD_Write(FT_EEPROM_PD *pd)
{
    /// PD Configuration functions
    PD_CFG_EnableSinkReqPRSwap(pd, TRUE);
    PD_CFG_EnableSinkAccPRSwap(pd, TRUE);
    PD_CFG_EnableSourceReqPRSwap(pd,FALSE);
    PD_CFG_EnableSourceAccPRSwap(pd, FALSE);
    PD_CFG_EnableExtVConn(pd,  FALSE);

    PD_CFG_DualMode(pd);
    PD1_LoadEnable(pd, GPIO2);
    PD2_LoadEnable(pd, GPIO4); 
	PD_DischargePin(pd, GPIO5);
    
    PD_CFG_EnablePD2(pd, TRUE);
    PD_CFG_EnableAutoCLK(pd, FALSE, FALSE);
    PD_CFG_EnableUseEfuse(pd, TRUE);

	PD_DischargeEnableBM(pd, GPIO_DRIVE_HI);
	PD_DischargeDisableBM(pd, GPIO_DRIVE_LOW);
	PD_CCSelectInd(pd, NOT_APPLICABLE);

    /// ISET Configuration
	PD_ISET3Config(pd,NA);
	PD_ExtISETEnable(pd,FALSE);
	PD_ISETPD2Enable(pd,FALSE);
	PD_ISETEnable(pd,FALSE);

    /// PD Timer and Control 
    /// PD Timers
    /// Sender Response Timer (Default=27) 
    PD_SenderResponseTimer(pd, SENDER_RESPONSE_TIMER);
    /// Hard Reset Timer (Default=30)
    PD_HardResetTimer(pd, HARD_RESET_TIMER);
    /// Source Capability Timer (Default=190)
    PD_SourceCapabilityTimer(pd, SOURCE_CAPABILITY_TIMER);
    /// Discover Identity Timer (Default=45)
    PD_DiscoverIdentityTimer(pd, DISCOVER_IDENTITY_TIMER);
    /// Source Recover Timer (Default=750)
    PD_SenderRecoverTimer(pd, SOURCE_RECOVER_TIMER);
    /// Transition Timer (Default=500)
    PD_TransitionTimer(pd, TRANSITION_TIMER);
    /// Source off timer (Default=890)
    PD_SourceoffTimer(pd, SOURCE_OFF_TIMER);
    /// No Response Timer (Default=4000)
    PD_NoResponseTimer(pd, NO_RESPONSE_TIMER);
    /// Sink Wait Capability Timer (Default=320)
    PD_SinkWaitCapabilityTimer(pd, SINK_WAIT_CAPABILITY_TIMER);
    /// Sink Request Timer (Default=110)
    PD_SinkRequestTimer(pd, SINK_REQUEST_TIMER);
    /// Discharge Timer (Default=100)
    PD_DischargeTimer(pd, DISCHARGE_TIMER);
    /// Chunk not supported timer (Default=40)
    PD_ChunkNotSupportedTimer(pd,CHUNK_NOT_SUPPORTED_TIMER);
    /// Idle Timer (Default=10000)
    PD_IdleTimer(pd, IDLE_TIMER);
    /// I2C Address (hex)
    PD_I2CAddress(pd,I2C_ADDRESS);
    /// Power Reserved for OWN use (default=2500)
    PD_PowerReserved(pd, POWER_RESERVED_FOR_OWN_USE);
    PD_Trim(pd,TRIM1, TRIM2);
    /// non-zero to enable EXTERNAL_DC_POWER (default = 0)
    PD_ExtDCPower(pd, ENABLE_EXTERNAL_DC_POWER);

    /// PDO  Sink
    // Voltage-mv , Current-ma
    PD_BM_PDO1_Sink(pd,5000,3000); // 5v 3a 
    PD_BM_PDO2_Sink(pd,0,0);
    PD_BM_PDO3_Sink(pd,0,0);
    PD_BM_PDO4_Sink(pd,0,0);
    PD_BM_PDO5_Sink(pd,0,0);
    PD_BM_PDO6_Sink(pd,0,0);
    PD_BM_PDO7_Sink(pd,0,0 );
    /// Source
    PD_BM_PDO1_Source(pd,5000,3000); // 5v 3a
    PD_BM_PDO2_Source(pd,9000,3000); // 9v 3a
    PD_BM_PDO3_Source(pd,15000,3000); // 15v 3a
    PD_BM_PDO4_Source(pd,20000,3000); // 20v 3a
    PD_BM_PDO5_Source(pd,0,0);
    PD_BM_PDO6_Source(pd,0,0);
    PD_BM_PDO7_Source(pd,0,0);
    /// Sink2
    PD_BM_PDO1_Sink_2(pd,5000,3000); // 5v 3a 
    PD_BM_PDO2_Sink_2(pd,20000,5000); // 20v 5a
    PD_BM_PDO3_Sink_2(pd,0,0);
    PD_BM_PDO4_Sink_2(pd,0,0);
    PD_BM_PDO5_Sink_2(pd,0,0);
    PD_BM_PDO6_Sink_2(pd,0,0);
    PD_BM_PDO7_Sink_2(pd,0,0);

}

static void ReadAndUpdatePDEeprom(DWORD locationId, FT_DEVICE deviceType)
{
    FT_STATUS       ftStatus;
    FT_HANDLE       ftHandle = (FT_HANDLE)NULL;
    char            manufacturer[64];
    char            manufacturerId[64];
    char            description[64];
    char            serialNumber[64];
    Eeprom_Pd_t     *pRWPDEeprom = NULL;
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
    pRWPDEeprom = calloc(1, sizeof(*pRWPDEeprom));
    if (pRWPDEeprom == NULL)
    {
        printf("Allocation failure.\n");
        goto exit;
    }

    /* EEPROM_HEADER is first member of every type of eeprom */
    header = (FT_EEPROM_HEADER *)pRWPDEeprom;
    header->deviceType = deviceType;

    manufacturer[0] = '\0';
    manufacturerId[0] = '\0';
    description[0] = '\0';
    serialNumber[0] = '\0';

    ftStatus = FT_EEPROM_Read(ftHandle,
                              pRWPDEeprom,
                              sizeof(*pRWPDEeprom),
                              manufacturer,
                              manufacturerId,
                              description,
                              serialNumber);
    if (ftStatus != FT_OK)
    {
        printf("FT_EEPROM_Read failed (error code %d)\n", (int)ftStatus);
        goto exit;
    }

    sleep(2); // Waiting for read complete.

    PD_Write(&pRWPDEeprom->ee4233pd.pd);
    switch(deviceType)
    {
        default:
        case FT_DEVICE_BM:
            // No further info to display
            break;

        case FT_DEVICE_2233HP:
            PD_Write(&pRWPDEeprom->ee2233pd.pd);
            break;

        case FT_DEVICE_4233HP:
           PD_Write(&pRWPDEeprom->ee4233pd.pd);
            break;

        case FT_DEVICE_4232HP:
            PD_Write(&pRWPDEeprom->ee4232pd.pd);
            break;

        case FT_DEVICE_2232HP:
            PD_Write(&pRWPDEeprom->ee2232pd.pd);
            break;

        case FT_DEVICE_233HP:
            PD_Write(&pRWPDEeprom->ee233pd.pd);
            break;

        case FT_DEVICE_232HP:
            PD_Write(&pRWPDEeprom->ee232pd.pd);
            break;
    }


    printf("%s:%s: FT_EEPROM_Program ...Start...\n",__FILE__,__FUNCTION__);  
    ftStatus = FT_EEPROM_Program(ftHandle,
                                 pRWPDEeprom,
                                 sizeof(*pRWPDEeprom),
                                 manufacturer,
                                 manufacturerId,
                                 description,
                                 serialNumber);
    if (ftStatus != FT_OK)
    {
        printf("FT_EEPROM_Program failed (error code %d)\n", (int)ftStatus);
        goto exit;
    }


exit:
    (void)FT_Close(ftHandle);
    free(pRWPDEeprom);
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

    gDeviceType = devInfo[0].Type;

    if((gDeviceType == FT_DEVICE_4233HP ) || 
    (gDeviceType == FT_DEVICE_2233HP ) || 
    (gDeviceType == FT_DEVICE_233HP )){
        /*Read and Update the EEPROM*/
        ReadAndUpdatePDEeprom(devInfo[0].LocId, devInfo[0].Type);
    }
    else{
        printf("%s Device is not supported \n",deviceName(gDeviceType));
    }
    printf("========================DEV INFO Write END============================\n");

exit:
    free(devInfo);
    return 0;
}
