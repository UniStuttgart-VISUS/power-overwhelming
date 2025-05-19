
#ifndef DISPLAY_HEADER_H
#define DISPLAY_HEADER_H

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

static void DisplayHeader (FT_EEPROM_HEADER *header)
{
    printf("\n================ Header =========================\n");
    printf("deviceType      : %s\n", deviceName(header->deviceType));
    printf("VendorId        : %04x\n", header->VendorId);
    printf("ProductId       : %04x\n", header->ProductId);
    printf("SerNumEnable    : %02x\n", header->SerNumEnable);
    printf("MaxPower        : %04x\n", header->MaxPower);
    printf("SelfPowered     : %02x\n", header->SelfPowered);
    printf("RemoteWakeup    : %02x\n", header->RemoteWakeup);
    printf("PullDownEnable  : %02x\n", header->PullDownEnable);
    printf("\n================ Header Done=========================\n");
}

static void DisplayEepromPD(FT_EEPROM_PD *PD_EEProm,FT_DEVICE deviceType)
{
    char str[4] = {0}; 
    (void)deviceType;
	//FT_EEPROM_PD	pd;
    /// Configuration
	printf("Configuration:\n");
    printf("\tSink Request Power Role Swap  : %d \n",PD_EEProm->srprs);		
    printf("\tSink Accept PR Swap           : %d \n",PD_EEProm->sraprs);		
    printf("\tSource Request PR SWAP        : %d \n",PD_EEProm->srrprs);		
    printf("\tSource Accept PR SWAP         : %d \n",PD_EEProm->saprs);		
    printf("\tvConn Swap                    : %d \n",PD_EEProm->vconns);		
    printf("\tPass Through (FTx233HP only)  : %d \n",PD_EEProm->passthru);		
    printf("\tExternal MCU                  : %d \n",PD_EEProm->extmcu);		
    printf("\tPD2 (FTx233HP only)           : %d \n",PD_EEProm->pd2en);		
    printf("\tPD1 Auto Clock                : %d \n",PD_EEProm->pd1autoclk);	
    printf("\tPD2 Auto Clock (FTx233HP only): %d \n",PD_EEProm->pd2autoclk);	
    printf("\tUse EFUSE                     : %d \n",PD_EEProm->useefuse);		
    printf("\tExternal vConn                : %d \n",PD_EEProm->extvconn);

    /// GPIO Configuration 
	printf("GPIO Configuration:\n");
    printf("\tGPIO Count    : %d\n", PD_EEProm->count);	
    printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin1 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin1), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin2 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin2), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin3 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin3), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin4 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin4), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin5 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin5), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin6 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin6), str));
	printf("\tGPIO Number   : %s\n", PD_EEProm->srcPin7 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->srcPin7), str));
			
    printf("\tPD1 Load Enable   : %s \n",PD_EEProm->pd1lden	 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->pd1lden), str));		
    printf("\tPD2 Load Enable   : %s \n",PD_EEProm->pd2lden	 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->pd2lden), str));		
    printf("\tDischarge Pin     : %s \n",PD_EEProm->dispin	 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->dispin ), str));		
    printf("\tDischarge Enable BM   : %s \n",PD_EEProm->disenbm	 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->disenbm), str));				
    printf("\tDischarge Disable BM  : %s \n",PD_EEProm->disdisbm == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->disdisbm), str));				
    printf("\tCC Select Indicator   : %s \n",PD_EEProm->ccselect == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->ccselect), str));		

    /// ISET Configuration
	printf("\tISET Configuration: \n");
    printf("\tISET1         : %s \n",PD_EEProm->iset1 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->iset1), str));  
    printf("\tISET2         : %s \n",PD_EEProm->iset2 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->iset2), str)); 
    printf("\tISET3         : %s \n",PD_EEProm->iset3 == NA ? "NA" : (sprintf(str, "%d", PD_EEProm->iset3), str));  
    printf("\tEXTEND_ISET   : %d \n",PD_EEProm->extiset);
    printf("\tISET_PD2      : %d \n",PD_EEProm->isetpd2);
    printf("\tISET_ENABLED  : %d \n",PD_EEProm->iseten); 

    printf("\nBM Configuration: 0 for \"Drive Low\", 1 for \"Drive Hi\", 2 for \"Input Mode\", 3 for \"Don't Care\" \n");
    for (int i = 0; i < 7; i++){
        printf("\tPDO1_GPIO[%d]     : %s \n",i,PD_EEProm->PDO1_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO1_GPIO[i]), str));
        printf("\tPDO2_GPIO[%d]     : %s \n",i,PD_EEProm->PDO2_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO2_GPIO[i]), str));
        printf("\tPDO3_GPIO[%d]     : %s \n",i,PD_EEProm->PDO3_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO3_GPIO[i]), str));
        printf("\tPDO4_GPIO[%d]     : %s \n",i,PD_EEProm->PDO4_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO4_GPIO[i]), str));
        printf("\tPDO5_GPIO[%d]     : %s \n",i,PD_EEProm->PDO5_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO5_GPIO[i]), str));
        printf("\tPDO6_GPIO[%d]     : %s \n",i,PD_EEProm->PDO6_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO6_GPIO[i]), str));
        printf("\tPDO7_GPIO[%d]     : %s \n",i,PD_EEProm->PDO7_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->PDO7_GPIO[i]), str));
        printf("\tVSET0V_GPIO[%d]   : %s \n",i,PD_EEProm->VSET0V_GPIO[i]  == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->VSET0V_GPIO[i]), str));
        printf("\tVSAFE5V_GPIO[%d]  : %s \n",i,PD_EEProm->VSAFE5V_GPIO[i] == GPIO_DONT_CARE ? "DONT_CAR" : (sprintf(str, "%d",PD_EEProm->VSAFE5V_GPIO[i]), str));
        printf("\n\n");
    }

    printf("BM_PDO_Sink:\n");
    printf("\tPDO1ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO1ma);
    printf("\tPDO1mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO1mv);
    printf("\tPDO2ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO2ma);
    printf("\tPDO2mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO2mv);
    printf("\tPDO3ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO3ma);
    printf("\tPDO3mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO3mv);
    printf("\tPDO4ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO4ma);
    printf("\tPDO4mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO4mv);
    printf("\tPDO5ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO5ma);
    printf("\tPDO5mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO5mv);
    printf("\tPDO6ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO6ma);
    printf("\tPDO6mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO6mv);
    printf("\tPDO7ma	: %d mA\n",PD_EEProm->BM_PDO_Sink.PDO7ma);
    printf("\tPDO7mv	: %d mV\n",PD_EEProm->BM_PDO_Sink.PDO7mv);

    printf("BM_PDO_Source:\n");
    printf("\tPDO1ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO1ma);	
    printf("\tPDO1mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO1mv);	
    printf("\tPDO2ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO2ma);	
    printf("\tPDO2mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO2mv);	
    printf("\tPDO3ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO3ma);	
    printf("\tPDO3mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO3mv);	
    printf("\tPDO4ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO4ma);	
    printf("\tPDO4mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO4mv);	
    printf("\tPDO5ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO5ma);	
    printf("\tPDO5mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO5mv);	
    printf("\tPDO6ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO6ma);	
    printf("\tPDO6mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO6mv);	
    printf("\tPDO7ma	: %d mA\n",PD_EEProm->BM_PDO_Source.PDO7ma);	
    printf("\tPDO7mv	: %d mV\n",PD_EEProm->BM_PDO_Source.PDO7mv);	
	
    printf("BM_PDO_Sink_2:\n");
	/// (FTx233HP only)
    printf("\tPDO1ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO1ma);
    printf("\tPDO1mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO1mv);
    printf("\tPDO2ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO2ma);
    printf("\tPDO2mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO2mv);
    printf("\tPDO3ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO3ma);
    printf("\tPDO3mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO3mv);
    printf("\tPDO4ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO4ma);
    printf("\tPDO4mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO4mv);
    printf("\tPDO5ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO5ma);
    printf("\tPDO5mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO5mv);
    printf("\tPDO6ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO6ma);
    printf("\tPDO6mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO6mv);
    printf("\tPDO7ma	: %d mA\n",PD_EEProm->BM_PDO_Sink_2.PDO7ma);
    printf("\tPDO7mv	: %d mV\n",PD_EEProm->BM_PDO_Sink_2.PDO7mv);

    printf("PD Timers:\n");
    /// PD Timers
    printf("\tSender Response Timer     : %d ms \n",PD_EEProm->srt);   
    printf("\tHard Reset Timer          : %d ms \n",PD_EEProm->hrt);   
    printf("\tSource Capability Timer   : %d ms \n",PD_EEProm->sct);   
    printf("\tDiscover Identity Timer   : %d ms \n",PD_EEProm->dit);   
    printf("\tSource Recover Timer      : %d ms \n",PD_EEProm->srcrt); 
    printf("\tTransition Timer          : %d ms \n",PD_EEProm->trt);   
    printf("\tSource off timer          : %d ms \n",PD_EEProm->sofft); 
    printf("\tNo Response Timer         : %d ms \n",PD_EEProm->nrt);   
    printf("\tSink Wait Capability Timer: %d ms \n",PD_EEProm->swct);
    printf("\tSink Request Timer        : %d ms \n",PD_EEProm->snkrt);   
    printf("\tDischarge Timer           : %d ms \n",PD_EEProm->dt);   
    printf("\tChunk not supported timer : %d ms \n",PD_EEProm->cnst); 
    printf("\tIdle Timer                : %d ms \n",PD_EEProm->it);  
	
    printf("PD Control:\n");
    /// PD Control
    printf("\tI2C Address                   : 0x%X \n",PD_EEProm->i2caddr);
    printf("\tPower Reserved for OWN use    : %d \n",PD_EEProm->prou);
    printf("\tTRIM1                         : %d \n",PD_EEProm->trim1);
    printf("\tTRIM2                         : %d \n",PD_EEProm->trim2);
    printf("\tETERNAL_DC_POWER              : %d \n",PD_EEProm->extdc);
    printf("\n=========================END===============================\n");

}

#endif /*DISPLAY_HEADER_H*/