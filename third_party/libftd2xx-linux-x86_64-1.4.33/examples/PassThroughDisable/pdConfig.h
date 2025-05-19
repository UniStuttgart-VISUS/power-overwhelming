#ifndef PDCONFIG_HEADER_H
#define PDCONFIG_HEADER_H

#define NOT_APPLICABLE  0xF
#define NA NOT_APPLICABLE

typedef union Eeprom_GenericPd
{
    FT_EEPROM_2233HP ee2233pd;
    FT_EEPROM_4233HP ee4233pd;
    FT_EEPROM_233HP ee233pd;
    FT_EEPROM_4232HP ee4232pd;
    FT_EEPROM_2232HP ee2232pd;
    FT_EEPROM_232HP ee232pd;
} Eeprom_Pd_t,Eeprom_GenericPd;

typedef enum{
    GPIO0 = 0,
    GPIO1 = 1,
    GPIO2 = 2,
    GPIO3 = 3,
    GPIO4 = 4,
    GPIO5 = 5,
    GPIO6 = 6,
    GPIO7 = 7,
}GPIOVal;

typedef enum {
    PD1_LOAD_EN = 0,
    PD2_LOAD_EN = 1,
    DISCHARGE = 2,
    ISET1 = 3,
    ISET2 = 4,
    ISET3 = 5,
    CC_SELECT = 6,
} SinkPins;

typedef enum {
    P0 = 7,
    P1 = 8,
    P2 = 9,
    P3 = 10,
    P4 = 11,
    P5 = 12,
    P6 = 13,
}SrcPins;

typedef enum {
    VASFE5V_PIN = 0,
    CHARGE_THROUGH = 1,
    FULL_POWER = 2
}PassthroughPins;

FT_DEVICE gDeviceType;

#define GPIO_DRIVE_LOW  0
#define GPIO_DRIVE_HI  1
#define GPIO_INPUT_MODE  2
#define GPIO_DONT_CARE   3

/*PD Timer*/
#define SENDER_RESPONSE_TIMER       27
#define HARD_RESET_TIMER            30
#define SOURCE_CAPABILITY_TIMER     190
#define DISCOVER_IDENTITY_TIMER     45
#define SOURCE_RECOVER_TIMER        750
#define TRANSITION_TIMER            500
#define SOURCE_OFF_TIMER            890
#define NO_RESPONSE_TIMER           4000 	
#define SINK_WAIT_CAPABILITY_TIMER  320
#define SINK_REQUEST_TIMER          110
#define DISCHARGE_TIMER             100
#define CHUNK_NOT_SUPPORTED_TIMER   40
#define IDLE_TIMER                  10000
/*PD Control*/
#define I2C_ADDRESS                 0x20
#define POWER_RESERVED_FOR_OWN_USE  2500
#define TRIM1                       0x0
#define	TRIM2                       0x0
#define ENABLE_EXTERNAL_DC_POWER    0

#define READ_DEBUG_EN   0
#define WRITE_DEBUG_EN  0

/// @brief This function sets the default PD configuration values.
/// @param pPD_EEProm Pointer to the FT_EEPROM_PD structure to be configured.
void PD_SetDefaultConfig(FT_EEPROM_PD *pPD_EEProm)
{
    /// Configuration
    pPD_EEProm->srprs    = 1; /// non-zero to enable Sink Request Power Role Swap
    pPD_EEProm->sraprs   = 0; /// non-zero to enable Sink Accept PR Swap
    pPD_EEProm->srrprs   = 0; /// non-zero to enable Source Request PR SWAP
    pPD_EEProm->saprs    = 0; /// non-zero to enable Source Accept PR SWAP
    pPD_EEProm->vconns   = 0; /// non-zero to enable vConn Swap
    pPD_EEProm->passthru = 1; /// non-zero to enable Pass Through (FTx233HP only)
    pPD_EEProm->extmcu   = 0; /// non-zero to enable External MCU
    pPD_EEProm->pd2en    = 1; /// non-zero to enable PD2 (FTx233HP only)
    pPD_EEProm->pd1autoclk   = 0; /// non-zero to enable PD1 Auto Clock
    pPD_EEProm->pd2autoclk   = 0; /// non-zero to enable PD2 Auto Clock (FTx233HP only)
    pPD_EEProm->useefuse     = 1; /// non-zero to Use EFUSE
    pPD_EEProm->extvconn     = 0; /// non-zero to enable External vConn

    pPD_EEProm->count        = 2;    /// GPIO Count, supported values are 0 to 7 
    pPD_EEProm->srcPin1      = GPIO3;    /// GPIO Number 1, supports device GPIO values
    pPD_EEProm->srcPin2      = GPIO4;    /// GPIO Number 2, supports device GPIO values
    pPD_EEProm->srcPin3	    = NA;  /// GPIO Number 3, supports device GPIO values
    pPD_EEProm->srcPin4	    = NA;  /// GPIO Number 4, supports device GPIO values
    pPD_EEProm->srcPin5	    = NA;  /// GPIO Number 5, supports device GPIO values (FTx233HP only)
    pPD_EEProm->srcPin6	    = NA;  /// GPIO Number 6, supports device GPIO values (FTx233HP only)
    pPD_EEProm->srcPin7	    = NA;  /// GPIO Number 7, supports device GPIO values (FTx233HP only)
    pPD_EEProm->pd1lden      = 2;    /// PD1 Load Enable, supports device GPIO values
    pPD_EEProm->pd2lden      = NA;  /// PD2 Load Enable, supports device GPIO values (FTx233HP only)
    pPD_EEProm->dispin       = NA;  /// Discharge Pin, supports device GPIO values
    pPD_EEProm->disenbm      = GPIO_DRIVE_LOW; /// Discharge Enable BM, 0 for "Drive Low", 1 for "Drive Hi", 2 for "Input Mode", 3 for "Don't Care"
    pPD_EEProm->disdisbm     = GPIO_DRIVE_HI; /// Discharge Disable BM, 0 for "Drive Low", 1 for "Drive Hi", 2 for "Input Mode", 3 for "Don't Care"
    pPD_EEProm->ccselect     = NA;  /// CC Select Indicator, supports device GPIO values

    /// ISET Configuration          
    pPD_EEProm->iset1     = 6; /// ISET1, supports device GPIO values
    pPD_EEProm->iset2     = 6; /// ISET2, supports device GPIO values
    pPD_EEProm->iset3     = 6; /// ISET3, supports device GPIO values
    pPD_EEProm->extiset   = 0; /// non-zero to enable EXTEND_ISET
    pPD_EEProm->isetpd2   = 0; /// non-zero to enable ISET_PD2
    pPD_EEProm->iseten    = 1; /// non-zero to set ISET_ENABLED

    /// BM Configuration, 0 for "Drive Low", 1 for "Drive Hi", 2 for "Input Mode", 3 for "Don't Care"
    for (int i = 0; i < 7; i++) {
        pPD_EEProm->PDO1_GPIO[i]  = GPIO_DONT_CARE;    // PDO1 GPIO1 to GPIO7
        pPD_EEProm->PDO2_GPIO[i]  = GPIO_DONT_CARE;    // PDO2 GPIO1 to GPIO7
        pPD_EEProm->PDO3_GPIO[i]  = GPIO_DONT_CARE;    // PDO3 GPIO1 to GPIO7
        pPD_EEProm->PDO4_GPIO[i]  = GPIO_DONT_CARE;    // PDO4 GPIO1 to GPIO7
        pPD_EEProm->PDO5_GPIO[i]  = GPIO_DONT_CARE;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
        pPD_EEProm->PDO6_GPIO[i]  = GPIO_DONT_CARE;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
        pPD_EEProm->PDO7_GPIO[i]  = GPIO_DONT_CARE;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
        pPD_EEProm->VSET0V_GPIO[i]    = GPIO_DONT_CARE;  // VSET0V GPIO1 to GPIO7
        pPD_EEProm->VSAFE5V_GPIO[i]   = GPIO_DONT_CARE; // VSAFE5V GPIO1 to GPIO7
    }

    pPD_EEProm->BM_PDO_Sink.PDO1ma	= 3000; /// PDO1 mA
    pPD_EEProm->BM_PDO_Sink.PDO1mv	= 5000; /// PDO1 mV
    pPD_EEProm->BM_PDO_Sink.PDO2ma	= 0;    /// PDO2 mA
    pPD_EEProm->BM_PDO_Sink.PDO2mv	= 0;    /// PDO2 mV
    pPD_EEProm->BM_PDO_Sink.PDO3ma	= 0;    /// PDO3 mA
    pPD_EEProm->BM_PDO_Sink.PDO3mv	= 0;    /// PDO3 mV
    pPD_EEProm->BM_PDO_Sink.PDO4ma	= 0;    /// PDO4 mA
    pPD_EEProm->BM_PDO_Sink.PDO4mv	= 0;    /// PDO4 mV
    pPD_EEProm->BM_PDO_Sink.PDO5ma	= 0;    /// PDO5 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink.PDO5mv	= 0;    /// PDO5 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink.PDO6ma	= 0;    /// PDO6 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink.PDO6mv	= 0;    /// PDO6 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink.PDO7ma	= 0;    /// PDO7 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink.PDO7mv	= 0;    /// PDO7 mV (FTx233HP only)

    pPD_EEProm->BM_PDO_Source.PDO1ma	= 3000; /// PDO1 mA
    pPD_EEProm->BM_PDO_Source.PDO1mv	= 5000; /// PDO1 mV
    pPD_EEProm->BM_PDO_Source.PDO2ma	= 0;    /// PDO2 mA
    pPD_EEProm->BM_PDO_Source.PDO2mv	= 0;    /// PDO2 mV
    pPD_EEProm->BM_PDO_Source.PDO3ma	= 0;    /// PDO3 mA
    pPD_EEProm->BM_PDO_Source.PDO3mv	= 0;    /// PDO3 mV
    pPD_EEProm->BM_PDO_Source.PDO4ma	= 0;    /// PDO4 mA
    pPD_EEProm->BM_PDO_Source.PDO4mv	= 0;    /// PDO4 mV
    pPD_EEProm->BM_PDO_Source.PDO5ma	= 0;    /// PDO5 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Source.PDO5mv	= 0;    /// PDO5 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Source.PDO6ma	= 0;    /// PDO6 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Source.PDO6mv	= 0;    /// PDO6 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Source.PDO7ma	= 0;    /// PDO7 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Source.PDO7mv	= 0;    /// PDO7 mV (FTx233HP only)

    /// (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO1ma	= 3000; /// PDO1 mA
    pPD_EEProm->BM_PDO_Sink_2.PDO1mv	= 5000; /// PDO1 mV
    pPD_EEProm->BM_PDO_Sink_2.PDO2ma	= 0;    /// PDO2 mA
    pPD_EEProm->BM_PDO_Sink_2.PDO2mv	= 0;    /// PDO2 mV
    pPD_EEProm->BM_PDO_Sink_2.PDO3ma	= 0;    /// PDO3 mA
    pPD_EEProm->BM_PDO_Sink_2.PDO3mv	= 0;    /// PDO3 mV
    pPD_EEProm->BM_PDO_Sink_2.PDO4ma	= 0;    /// PDO4 mA
    pPD_EEProm->BM_PDO_Sink_2.PDO4mv	= 0;    /// PDO4 mV
    pPD_EEProm->BM_PDO_Sink_2.PDO5ma	= 0;    /// PDO5 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO5mv	= 0;    /// PDO5 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO6ma	= 0;    /// PDO6 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO6mv	= 0;    /// PDO6 mV (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO7ma	= 0;    /// PDO7 mA (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO7mv	= 0;    /// PDO7 mV (FTx233HP only)

    /// PD Timers
    pPD_EEProm->srt     = SENDER_RESPONSE_TIMER;    /// Sender Response Timer
    pPD_EEProm->hrt     = HARD_RESET_TIMER;			/// Hard Reset Timer
    pPD_EEProm->sct     = SOURCE_CAPABILITY_TIMER;	/// Source Capability Timer
    pPD_EEProm->dit     = DISCOVER_IDENTITY_TIMER;	/// Discover Identity Timer
    pPD_EEProm->srcrt   = SOURCE_RECOVER_TIMER;		/// Source Recover Timer
    pPD_EEProm->trt     = TRANSITION_TIMER;			/// Transition Timer
    pPD_EEProm->sofft   = SOURCE_OFF_TIMER;			/// Source off timer
    pPD_EEProm->nrt     = NO_RESPONSE_TIMER;        /// No Response Timer
    pPD_EEProm->swct    = SINK_WAIT_CAPABILITY_TIMER;/// Sink Wait Capability Timer
    pPD_EEProm->snkrt   = SINK_REQUEST_TIMER;		/// Sink Request Timer
    pPD_EEProm->dt      = DISCHARGE_TIMER;			/// Discharge Timer
    pPD_EEProm->cnst    = CHUNK_NOT_SUPPORTED_TIMER;    /// Chunk not supported timer
    pPD_EEProm->it      = IDLE_TIMER;               /// Idle Timer

    /// PD Control
    pPD_EEProm->i2caddr  = I2C_ADDRESS;				/// I2C Address (hex)
    pPD_EEProm->prou     = POWER_RESERVED_FOR_OWN_USE;/// Power Reserved for OWN use
    pPD_EEProm->trim1    = TRIM1;					/// TRIM1
    pPD_EEProm->trim2    = TRIM2;					/// TRIM2
    pPD_EEProm->extdc    = ENABLE_EXTERNAL_DC_POWER;/// non-zero to enable ETERNAL_DC_POWER
}

/// @brief This function sets the default SrcPin configuration values.
/// @param pPD_EEProm Pointer to the FT_EEPROM_PD structure to be configured.
void PD_SetSourcePinDefaultConfig(FT_EEPROM_PD *pPD_EEProm)
{
    pPD_EEProm->count = 0;
    pPD_EEProm->srcPin1 = NA;
    pPD_EEProm->srcPin2 = NA;
    pPD_EEProm->srcPin3 = NA;
    pPD_EEProm->srcPin4 = NA;
    pPD_EEProm->srcPin5 = NA;
    pPD_EEProm->srcPin6 = NA;
    pPD_EEProm->srcPin7 = NA;

}

/// BM Configuration, 0 for "Drive Low", 1 for "Drive Hi", 2 for "Input Mode", 3 for "Don't Care"
/// @brief Set BM Configuration to Default
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
void BM_DefaultConfig(FT_EEPROM_PD *pPD_EEProm)
{
    for (int i = 0; i < 7; i++) {
        pPD_EEProm->PDO1_GPIO[i]  = GPIO_DONT_CARE;    // PDO1 GPIO1 to GPIO7
        pPD_EEProm->PDO2_GPIO[i]  = GPIO_DONT_CARE;    // PDO2 GPIO1 to GPIO7
        pPD_EEProm->PDO3_GPIO[i]  = GPIO_DONT_CARE;    // PDO3 GPIO1 to GPIO7
        pPD_EEProm->PDO4_GPIO[i]  = GPIO_DONT_CARE;    // PDO4 GPIO1 to GPIO7
        if((gDeviceType == FT_DEVICE_4233HP ) || 
            (gDeviceType == FT_DEVICE_2233HP ) || 
            (gDeviceType == FT_DEVICE_233HP ))
        {
            pPD_EEProm->PDO5_GPIO[i]  = GPIO_DONT_CARE;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO6_GPIO[i]  = GPIO_DONT_CARE;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO7_GPIO[i]  = GPIO_DONT_CARE;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
        }
        pPD_EEProm->VSET0V_GPIO[i]    = GPIO_DONT_CARE;  // VSET0V GPIO1 to GPIO7
        pPD_EEProm->VSAFE5V_GPIO[i]   = GPIO_DONT_CARE; // VSAFE5V GPIO1 to GPIO7
    }
}

/*Note: Don't Change this Logic*/
/// @brief Set BM Configuration Automatically
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucChargeThrough Charge through value
void BM_AutoConfigForPassThrough(FT_EEPROM_PD *pPD_EEProm,UCHAR ucChargeThrough)
{
    if(ucChargeThrough != NOT_APPLICABLE)
    {
        for (int i = 0; i < pPD_EEProm->count; i++) {
            if(i == 0){ // idx 0: CHARGE_THROUGH  
                pPD_EEProm->PDO1_GPIO[i]  = GPIO_DRIVE_HI;    // PDO1 GPIO1 to GPIO7
                pPD_EEProm->PDO2_GPIO[i]  = GPIO_DRIVE_HI;    // PDO2 GPIO1 to GPIO7
                pPD_EEProm->PDO3_GPIO[i]  = GPIO_DRIVE_HI;    // PDO3 GPIO1 to GPIO7
                pPD_EEProm->PDO4_GPIO[i]  = GPIO_DRIVE_HI;    // PDO4 GPIO1 to GPIO7
                if((gDeviceType == FT_DEVICE_4233HP ) || 
                    (gDeviceType == FT_DEVICE_2233HP ) || 
                    (gDeviceType == FT_DEVICE_233HP ))
                {
                    pPD_EEProm->PDO5_GPIO[i]  = GPIO_DRIVE_HI;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO6_GPIO[i]  = GPIO_DRIVE_HI;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO7_GPIO[i]  = GPIO_DRIVE_HI;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
                }
                pPD_EEProm->VSAFE5V_GPIO[i]   = GPIO_DRIVE_HI;  // VSAFE5V GPIO1 to GPIO7
            }
            else if(i == 1){ // VSAFE5V
                pPD_EEProm->PDO1_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
                pPD_EEProm->PDO2_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO2 GPIO1 to GPIO7
                pPD_EEProm->PDO3_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO3 GPIO1 to GPIO7
                pPD_EEProm->PDO4_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO4 GPIO1 to GPIO7
                if((gDeviceType == FT_DEVICE_4233HP ) || 
                    (gDeviceType == FT_DEVICE_2233HP ) || 
                    (gDeviceType == FT_DEVICE_233HP ))
                {
                    pPD_EEProm->PDO5_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO6_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO7_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
                }
                pPD_EEProm->VSAFE5V_GPIO[i]   = GPIO_DRIVE_HI;  // VSAFE5V GPIO1 to GPIO7
            }
            else if(i == 2) //idx 1: FULL POWER
            {
                pPD_EEProm->PDO1_GPIO[i]  = GPIO_DRIVE_HI;    // PDO1 GPIO1 to GPIO7
                pPD_EEProm->PDO2_GPIO[i]  = GPIO_DRIVE_HI;    // PDO2 GPIO1 to GPIO7
                pPD_EEProm->PDO3_GPIO[i]  = GPIO_DRIVE_HI;    // PDO3 GPIO1 to GPIO7
                pPD_EEProm->PDO4_GPIO[i]  = GPIO_DRIVE_HI;    // PDO4 GPIO1 to GPIO7
                if((gDeviceType == FT_DEVICE_4233HP ) || 
                    (gDeviceType == FT_DEVICE_2233HP ) || 
                    (gDeviceType == FT_DEVICE_233HP ))
                {
                    pPD_EEProm->PDO5_GPIO[i]  = GPIO_DRIVE_HI;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO6_GPIO[i]  = GPIO_DRIVE_HI;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
                    pPD_EEProm->PDO7_GPIO[i]  = GPIO_DRIVE_HI;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
                }
                pPD_EEProm->VSAFE5V_GPIO[i]   = GPIO_DRIVE_LOW;  // VSAFE5V GPIO1 to GPIO7
            }
            else
            {
             // No Change
            }
        }
    }
    else{
        { // idx 0: VSAFE5V 
            pPD_EEProm->PDO1_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
            pPD_EEProm->PDO2_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO2 GPIO1 to GPIO7
            pPD_EEProm->PDO3_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO3 GPIO1 to GPIO7
            pPD_EEProm->PDO4_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO4 GPIO1 to GPIO7
            pPD_EEProm->PDO5_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO6_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO7_GPIO[0]  = GPIO_DRIVE_LOW;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->VSAFE5V_GPIO[0]   = GPIO_DRIVE_HI;  // VSAFE5V GPIO1 to GPIO7
        }     
        { // idx 1: FULL POWER
            pPD_EEProm->PDO1_GPIO[1]  = GPIO_DRIVE_HI;    // PDO1 GPIO1 to GPIO7
            pPD_EEProm->PDO2_GPIO[1]  = GPIO_DRIVE_HI;    // PDO2 GPIO1 to GPIO7
            pPD_EEProm->PDO3_GPIO[1]  = GPIO_DRIVE_HI;    // PDO3 GPIO1 to GPIO7
            pPD_EEProm->PDO4_GPIO[1]  = GPIO_DRIVE_HI;    // PDO4 GPIO1 to GPIO7
            pPD_EEProm->PDO5_GPIO[1]  = GPIO_DRIVE_HI;    // PDO5 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO6_GPIO[1]  = GPIO_DRIVE_HI;    // PDO6 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->PDO7_GPIO[1]  = GPIO_DRIVE_HI;    // PDO7 GPIO1 to GPIO7 (FTx233HP only)
            pPD_EEProm->VSAFE5V_GPIO[1]   = GPIO_DRIVE_LOW;  // VSAFE5V GPIO1 to GPIO7
        }
    }

    // VSET0V
    for (int i = 0; i < pPD_EEProm->count; i++) {
        pPD_EEProm->VSET0V_GPIO[i]  = GPIO_DRIVE_LOW;  // VSET0V GPIO1 to GPIO7
    }
}

/*Note: Don't Change this Logic*/
/// @brief Set BM PDO Configuration Automatically
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
void BM_AutoConfigForDualMode(FT_EEPROM_PD *pPD_EEProm)
{
    UCHAR count = pPD_EEProm->count;

    // VSET0V
    for (int i = 0; i < count ; i++) {
        pPD_EEProm->VSET0V_GPIO[i]  = GPIO_DRIVE_LOW;  // VSET0V GPIO1 to GPIO7
    }
    // VSAFE5V
    if(pPD_EEProm->srcPin1 != NA)
    {
        pPD_EEProm->VSAFE5V_GPIO[0] = GPIO_DRIVE_HI;
        for(int i = 1; i < count ; i++)
        {   
            pPD_EEProm->VSAFE5V_GPIO[i] = GPIO_DRIVE_LOW;
        }
    }
    //5v - PDO1
    if(pPD_EEProm->srcPin1 != NA)
    {
        pPD_EEProm->PDO1_GPIO[0]  = GPIO_DRIVE_HI;
        for(int i = 1; i< count; i++)
        {
            pPD_EEProm->PDO1_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
    }

    // 9v - PDO2
    if(pPD_EEProm->srcPin2 != NA)
    {
        pPD_EEProm->PDO2_GPIO[0]  = GPIO_DRIVE_HI;
        pPD_EEProm->PDO2_GPIO[1]  = GPIO_DRIVE_HI;
        for(int i = 2; i<count; i++)
        {
            pPD_EEProm->PDO2_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }

    }
    // 15v - PDO3
    if(pPD_EEProm->srcPin3 != NA)
    {
        pPD_EEProm->PDO3_GPIO[0]  = GPIO_DRIVE_HI;
        pPD_EEProm->PDO3_GPIO[1]  = GPIO_DRIVE_LOW;
        pPD_EEProm->PDO3_GPIO[2]  = GPIO_DRIVE_HI;
        for(int i = 3; i<count; i++)
        {
            pPD_EEProm->PDO3_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
    }
    //20v - PDO4 
    if(pPD_EEProm->srcPin4 != NA)
    {
        pPD_EEProm->PDO4_GPIO[0]  = GPIO_DRIVE_HI;
        pPD_EEProm->PDO4_GPIO[1]  = GPIO_DRIVE_LOW;
        pPD_EEProm->PDO4_GPIO[2]  = GPIO_DRIVE_LOW;
        pPD_EEProm->PDO4_GPIO[3]  = GPIO_DRIVE_HI;
        for(int i = 4; i<count; i++)
        {
            pPD_EEProm->PDO4_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
    }
    // PDO5
    if(pPD_EEProm->srcPin5 != NA)
    {
        pPD_EEProm->PDO5_GPIO[0]  = GPIO_DRIVE_HI;
        for(int i = 1; i<4; i++)
        {
            pPD_EEProm->PDO5_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
        pPD_EEProm->PDO5_GPIO[4]  = GPIO_DRIVE_HI;
        for(int i = 5; i<count; i++)
        {
            pPD_EEProm->PDO5_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
    }
    //PDO6
    if(pPD_EEProm->srcPin6 != NA)
    {
        pPD_EEProm->PDO6_GPIO[0]  = GPIO_DRIVE_HI;
        pPD_EEProm->PDO6_GPIO[5]  = GPIO_DRIVE_HI;
        for(int i = 1; i<5; i++)
        {
            pPD_EEProm->PDO6_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
        for(int i = 6; i<count; i++)
        {
            pPD_EEProm->PDO6_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
    }
    //PDO7
    if(pPD_EEProm->srcPin7 != NA)
    {
        pPD_EEProm->PDO7_GPIO[0]  = GPIO_DRIVE_HI;
        pPD_EEProm->PDO7_GPIO[6]  = GPIO_DRIVE_HI; 
        for(int i = 1; i<6; i++)
        {
            pPD_EEProm->PDO7_GPIO[i]  = GPIO_DRIVE_LOW;    // PDO1 GPIO1 to GPIO7
        }
        pPD_EEProm->PDO7_GPIO[7]  = GPIO_DRIVE_LOW;
    }
}

/// @brief Configures the PD to enable or disable Sink Request Power Role Swap.
/// @param pPD_EEProm Pointer to the FT_EEPROM_PD structure to be configured.
/// @param bEnSRPRSwap Boolean value to enable (true) or disable (false) the Sink Request Power Role Swap.
void PD_CFG_EnableSinkReqPRSwap(FT_EEPROM_PD *pPD_EEProm, bool bEnSRPRSwap)
{
    pPD_EEProm->srprs = bEnSRPRSwap;
}
/// @brief Enable Sink Accept PR Swap
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnSAPRSwap Boolean value to enable Sink Accept PR Swap
void PD_CFG_EnableSinkAccPRSwap(FT_EEPROM_PD *pPD_EEProm, bool bEnSRAPRSwap)
{
    pPD_EEProm->sraprs = bEnSRAPRSwap;
}
/// @brief Enable Source Request PR Swap
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnSRRPRSwap Boolean value to enable Source Request PR Swap
void PD_CFG_EnableSourceReqPRSwap(FT_EEPROM_PD *pPD_EEProm, bool bEnSRRPRSwap)
{
    pPD_EEProm->srrprs = bEnSRRPRSwap;
}
/// @brief Enable Source Accept PR Swap
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnSAPRSwap Boolean value to enable Source Accept PR Swap
void PD_CFG_EnableSourceAccPRSwap(FT_EEPROM_PD *pPD_EEProm, bool bEnSAPRSwap)
{
    pPD_EEProm->saprs = bEnSAPRSwap;
}
/// @brief Enable External VConn
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnExtVconn Boolean value to enable External VConn
void PD_CFG_EnableExtVConn(FT_EEPROM_PD *pPD_EEProm, bool bEnExtVconn)
{
    pPD_EEProm->extvconn = bEnExtVconn;
}

/// @brief Enable PD2
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bPD2 Boolean value to enable PD2
void PD_CFG_EnablePD2(FT_EEPROM_PD *pPD_EEProm,bool bPD2)
{
    if((gDeviceType == FT_DEVICE_4233HP ) || 
        (gDeviceType == FT_DEVICE_2233HP ) || 
            (gDeviceType == FT_DEVICE_233HP ))
    {
        pPD_EEProm->pd2en = bPD2;
    }
}
/// @brief Enable Auto Clock
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bPD1AutoClk Boolean value to enable PD1 Auto Clock
/// @param bPD2AutoClk Boolean value to enable PD2 Auto Clock
void PD_CFG_EnableAutoCLK(FT_EEPROM_PD *pPD_EEProm,bool bPD1AutoClk,bool bPD2AutoClk)
{
    pPD_EEProm->pd1autoclk = bPD1AutoClk;
    if((gDeviceType == FT_DEVICE_4233HP ) || 
        (gDeviceType == FT_DEVICE_2233HP ) || 
            (gDeviceType == FT_DEVICE_233HP ))
    {
        pPD_EEProm->pd2autoclk = bPD2AutoClk;
    }
}
/// @brief Enable eFuse Usage
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnUseEfuse Boolean value to enable eFuse usage
void PD_CFG_EnableUseEfuse(FT_EEPROM_PD *pPD_EEProm,bool bEnUseEfuse)
{
    pPD_EEProm->useefuse = bEnUseEfuse;
}

/// @brief Set Power Source for GPIO
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ePowerSrcVal Power source value (7 to 13)
/// @param ucGpioVal  GPIO Number (0 to 7)
void PD_GpioCfg_SetPowerSource(FT_EEPROM_PD *pPD_EEProm, SrcPins ePowerSrcVal, UCHAR ucGpioVal )
{
    if(ePowerSrcVal >= P0 && ePowerSrcVal <= P6)
    {
        switch (ePowerSrcVal)
        {
        case P0:
            if (!(pPD_EEProm->srcPin1 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                pPD_EEProm->count++;
            }
            else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin1 != NOT_APPLICABLE)) {
                pPD_EEProm->count--;
            }
            pPD_EEProm->srcPin1 = ucGpioVal;
            break;
        case P1:
            if (!(pPD_EEProm->srcPin2 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                pPD_EEProm->count++;
            }
            else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin2 != NOT_APPLICABLE)) {
                pPD_EEProm->count--;
            }
            pPD_EEProm->srcPin2 = ucGpioVal;
            break;
        case P2:
            if (!(pPD_EEProm->srcPin3 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                pPD_EEProm->count++;
            }
            else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin3 != NOT_APPLICABLE)) {
                pPD_EEProm->count--;
            }
            pPD_EEProm->srcPin3 = ucGpioVal;
            break;
        case P3:
            if (!(pPD_EEProm->srcPin4 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                pPD_EEProm->count++;
            }
            else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin4 != NOT_APPLICABLE)) {
                pPD_EEProm->count--;
            }
            pPD_EEProm->srcPin4 = ucGpioVal;
            break;
        case P4:
            if((gDeviceType == FT_DEVICE_4233HP ) || 
                (gDeviceType == FT_DEVICE_2233HP ) || 
                (gDeviceType == FT_DEVICE_233HP ))
            {
                if (!(pPD_EEProm->srcPin5 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                    pPD_EEProm->count++;
                }
                else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin5 != NOT_APPLICABLE)) {
                    pPD_EEProm->count--;
                }
                pPD_EEProm->srcPin5 = ucGpioVal;
            }
            break;
        case P5:
            if((gDeviceType == FT_DEVICE_4233HP ) || 
                (gDeviceType == FT_DEVICE_2233HP ) || 
                (gDeviceType == FT_DEVICE_233HP ))
            {
                if (!(pPD_EEProm->srcPin6 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                    pPD_EEProm->count++;
                }
                else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin6 != NOT_APPLICABLE)) {
                    pPD_EEProm->count--;
                }
                pPD_EEProm->srcPin6 = ucGpioVal;
            }
            break;
        case P6:
            if((gDeviceType == FT_DEVICE_4233HP ) || 
                (gDeviceType == FT_DEVICE_2233HP ) || 
                (gDeviceType == FT_DEVICE_233HP ))
            {
                if (!(pPD_EEProm->srcPin7 <= 7) && (ucGpioVal != NOT_APPLICABLE)) {
                    pPD_EEProm->count++;
                }
                else if ((ucGpioVal == NOT_APPLICABLE) && (pPD_EEProm->srcPin7 != NOT_APPLICABLE)) {
                    pPD_EEProm->count--;
                }
                pPD_EEProm->srcPin7 = ucGpioVal;
            }
            break;
        default:
            printf("GPIO Number is Wrong....\n Note:GPIO Number should be(0 to 7)\n");
            break;
        }
    }
}

/// @brief Enable Pass Through
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEnPassThrough Boolean value to enable Pass Through
/// @param ucChargeThrough Charge through value - GPIO Number 4 (assign to SrcPin1)
/// @param ucfullPower Full power value - GPIO Number 3 (assign to SrcPin3)
/// @param ucVsafe5v Vsafe5v value - GPIO Number 0  (assign to SrcPin2)
void PD_CFG_EnablePassThrough(FT_EEPROM_PD *pPD_EEProm, bool bEnPassThrough, UCHAR ucChargeThrough, UCHAR ucfullPower, UCHAR ucVsafe5v )
{
    BM_DefaultConfig(pPD_EEProm);
    PD_SetSourcePinDefaultConfig(pPD_EEProm);

    if(bEnPassThrough){
        if(ucChargeThrough != NA){
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P0, ucChargeThrough);
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P1, ucVsafe5v);
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P2, ucfullPower);
        }
        else{
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P0, ucVsafe5v);
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P1, ucfullPower);
            PD_GpioCfg_SetPowerSource(pPD_EEProm,P2, NA);
        }

        BM_AutoConfigForPassThrough(pPD_EEProm,ucChargeThrough);
    }
    pPD_EEProm->passthru = bEnPassThrough;
}
/// @brief Configure Dual Mode
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
void PD_CFG_DualMode(FT_EEPROM_PD *pPD_EEProm)
{
    BM_DefaultConfig(pPD_EEProm);
    PD_SetSourcePinDefaultConfig(pPD_EEProm);
    // disable pass through 
    pPD_EEProm->passthru = FALSE;

    PD_GpioCfg_SetPowerSource(pPD_EEProm,P0, GPIO0); // 5v 
    PD_GpioCfg_SetPowerSource(pPD_EEProm,P1, GPIO1); // 9v
    PD_GpioCfg_SetPowerSource(pPD_EEProm,P2, GPIO6); // 15v 
    PD_GpioCfg_SetPowerSource(pPD_EEProm,P3, GPIO3); // 20v
    
    BM_AutoConfigForDualMode(pPD_EEProm);

}

/// @brief Load Enable for PD1
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucPd1LdEn PD1 load enable value
void PD1_LoadEnable(FT_EEPROM_PD *pPD_EEProm,UCHAR ucPd1LdEn)
{
    pPD_EEProm->pd1lden      = ucPd1LdEn;
}
/// @brief Load Enable for PD2 - supports device GPIO values (FTx233HP only)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucPd2LdEn PD2 load enable value
void PD2_LoadEnable(FT_EEPROM_PD *pPD_EEProm,UCHAR ucPd2LdEn)
{
    if((gDeviceType == FT_DEVICE_4233HP ) || 
    (gDeviceType == FT_DEVICE_2233HP ) || 
    (gDeviceType == FT_DEVICE_233HP ))
    {
        pPD_EEProm->pd2lden      = ucPd2LdEn;
    }
}
/// @brief Discharge Pin
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucGpioVal GPIO value 
void PD_DischargePin(FT_EEPROM_PD *pPD_EEProm,UCHAR ucGpioVal)
{
    pPD_EEProm->dispin       = ucGpioVal;
}
/// @brief Enable Discharge for BM - 0 for "Drive Low", 1 for "Drive Hi", 2 for "Input Mode", 3 for "Don't Care"
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucDeviceState Device state value
void PD_DischargeEnableBM(FT_EEPROM_PD *pPD_EEProm,UCHAR ucDeviceState)
{
    pPD_EEProm->disenbm      = ucDeviceState;
}
/// @brief Disable Discharge for BM
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucDeviceState Device state value
void PD_DischargeDisableBM(FT_EEPROM_PD *pPD_EEProm,UCHAR ucDeviceState)
{
    pPD_EEProm->disdisbm     = ucDeviceState;
}
/// @brief CC Select Indication
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucGpioVal GPIO value 
void PD_CCSelectInd(FT_EEPROM_PD *pPD_EEProm,UCHAR ucGpioVal)
{
    pPD_EEProm->ccselect     = ucGpioVal;
}
/// @brief ISET1 Configuration
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucGpioVal GPIO value
void PD_ISET1Config(FT_EEPROM_PD *pPD_EEProm,UCHAR ucGpioVal)
{
    pPD_EEProm->iset1     = ucGpioVal;
}
/// @brief ISET2 Configuration
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucGpioVal GPIO value
void PD_ISET2Config(FT_EEPROM_PD *pPD_EEProm,UCHAR ucGpioVal)
{
    pPD_EEProm->iset2     = ucGpioVal;
}
/// @brief ISET3 Configuration
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucGpioVal GPIO value 
void PD_ISET3Config(FT_EEPROM_PD *pPD_EEProm,UCHAR ucGpioVal)
{
    pPD_EEProm->iset3     = ucGpioVal;
}
/// @brief Enable External ISET
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bEXTEND_ISET Boolean value to enable External ISET
void PD_ExtISETEnable(FT_EEPROM_PD *pPD_EEProm,bool bEXTEND_ISET)
{
    pPD_EEProm->extiset   = bEXTEND_ISET;
}
/// @brief Enable ISET for PD2
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bISET_PD2 Boolean value to enable ISET for PD2
void PD_ISETPD2Enable(FT_EEPROM_PD *pPD_EEProm,bool bISET_PD2)
{
    pPD_EEProm->isetpd2   = bISET_PD2;
}
/// @brief Enable ISET
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bISET_ENABLED Boolean value to enable ISET
void PD_ISETEnable(FT_EEPROM_PD *pPD_EEProm,bool bISET_ENABLED)
{
    pPD_EEProm->iseten    = bISET_ENABLED;
}
/*ISET Configuration*/

/// @brief Configure BM PDO1 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO1mv PDO1 voltage in mV
/// @param usPDO1ma PDO1 current in mA
void PD_BM_PDO1_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO1mv,USHORT usPDO1ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO1ma	= usPDO1ma;
    pPD_EEProm->BM_PDO_Sink.PDO1mv	= usPDO1mv;
}
/// @brief Configure BM PDO2 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO2mv PDO2 voltage in mV
/// @param usPDO2ma PDO2 current in mA
void PD_BM_PDO2_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO2mv,USHORT usPDO2ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO2ma	= usPDO2ma;
    pPD_EEProm->BM_PDO_Sink.PDO2mv	= usPDO2mv;
}
/// @brief Configure BM PDO3 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO3mv PDO3 voltage in mV
/// @param usPDO3ma PDO3 current in mA
void PD_BM_PDO3_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO3mv,USHORT usPDO3ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO3mv	= usPDO3mv;
    pPD_EEProm->BM_PDO_Sink.PDO3ma	= usPDO3ma;
}
/// @brief Configure BM PDO4 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO4mv PDO4 voltage in mV
/// @param usPDO4ma PDO4 current in mA
void PD_BM_PDO4_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO4mv,USHORT usPDO4ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO4mv	= usPDO4mv;
    pPD_EEProm->BM_PDO_Sink.PDO4ma	= usPDO4ma;
}
/// @brief Configure BM PDO5 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO5mv PDO5 voltage in mV
/// @param usPDO5ma PDO5 current in mA
void PD_BM_PDO5_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO5mv,USHORT usPDO5ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO5mv	= usPDO5mv;
    pPD_EEProm->BM_PDO_Sink.PDO5ma	= usPDO5ma;
}
/// @brief Configure BM PDO6 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO6mv PDO6 voltage in mV
/// @param usPDO6ma PDO6 current in mA
void PD_BM_PDO6_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO6mv,USHORT usPDO6ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO6mv	= usPDO6mv;
    pPD_EEProm->BM_PDO_Sink.PDO6ma	= usPDO6ma;

}
/// @brief Configure BM PDO7 as Sink
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO7mv PDO7 voltage in mV
/// @param usPDO7ma PDO7 current in mA
void PD_BM_PDO7_Sink(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO7mv,USHORT usPDO7ma)
{
    pPD_EEProm->BM_PDO_Sink.PDO7mv	= usPDO7mv;
    pPD_EEProm->BM_PDO_Sink.PDO7ma	= usPDO7ma;
}
/// @brief Configure BM PDO1 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO1mv PDO1 voltage in mV
/// @param usPDO1ma PDO1 current in mA
void PD_BM_PDO1_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO1mv,USHORT usPDO1ma)
{
    pPD_EEProm->BM_PDO_Source.PDO1mv	= usPDO1mv;
    pPD_EEProm->BM_PDO_Source.PDO1ma	= usPDO1ma;
}
/// @brief Configure BM PDO2 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO2mv PDO2 voltage in mV
/// @param usPDO2ma PDO2 current in mA
void PD_BM_PDO2_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO2mv,USHORT usPDO2ma)
{
    pPD_EEProm->BM_PDO_Source.PDO2mv	= usPDO2mv;
    pPD_EEProm->BM_PDO_Source.PDO2ma	= usPDO2ma;
}
/// @brief Configure BM PDO3 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO3mv PDO3 voltage in mV
/// @param usPDO3ma PDO3 current in mA
void PD_BM_PDO3_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO3mv,USHORT usPDO3ma)
{
    pPD_EEProm->BM_PDO_Source.PDO3mv	= usPDO3mv;
    pPD_EEProm->BM_PDO_Source.PDO3ma	= usPDO3ma;
}
/// @brief Configure BM PDO4 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO4mv PDO4 voltage in mV
/// @param usPDO4ma PDO4 current in mA
void PD_BM_PDO4_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO4mv,USHORT usPDO4ma)
{
    pPD_EEProm->BM_PDO_Source.PDO4mv	= usPDO4mv;
    pPD_EEProm->BM_PDO_Source.PDO4ma	= usPDO4ma;
}
/// @brief Configure BM PDO5 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO5mv PDO5 voltage in mV
/// @param usPDO5ma PDO5 current in mA
void PD_BM_PDO5_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO5mv,USHORT usPDO5ma)
{
    pPD_EEProm->BM_PDO_Source.PDO5mv	= usPDO5mv;
    pPD_EEProm->BM_PDO_Source.PDO5ma	= usPDO5ma;
}
/// @brief Configure BM PDO6 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO6mv PDO6 voltage in mV
/// @param usPDO6ma PDO6 current in mA
void PD_BM_PDO6_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO6mv,USHORT usPDO6ma)
{
    pPD_EEProm->BM_PDO_Source.PDO6mv	= usPDO6mv;
    pPD_EEProm->BM_PDO_Source.PDO6ma	= usPDO6ma;
}
/// @brief Configure BM PDO7 as Source
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO7mv PDO7 voltage in mV
/// @param usPDO7ma PDO7 current in mA
void PD_BM_PDO7_Source(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO7mv,USHORT usPDO7ma )
{
    pPD_EEProm->BM_PDO_Source.PDO7mv	= usPDO7mv;
    pPD_EEProm->BM_PDO_Source.PDO7ma	= usPDO7ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO1mv PDO voltage in mV for PDO1
/// @param usPDO1ma PDO current in mA for PDO1
void PD_BM_PDO1_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO1mv,USHORT usPDO1ma)
{
    /// (FTx233HP only)
    pPD_EEProm->BM_PDO_Sink_2.PDO1mv	= usPDO1mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO1ma	= usPDO1ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO2mv PDO voltage in mV for PDO2
/// @param usPDO2ma PDO current in mA for PDO2
void PD_BM_PDO2_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO2mv,USHORT usPDO2ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO2mv	= usPDO2mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO2ma	= usPDO2ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO3mv PDO voltage in mV for PDO3
/// @param usPDO3ma PDO current in mA for PDO3
void PD_BM_PDO3_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO3mv,USHORT usPDO3ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO3mv	= usPDO3mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO3ma	= usPDO3ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO4mv PDO voltage in mV for PDO4
/// @param usPDO4ma PDO current in mA for PDO4
void PD_BM_PDO4_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO4mv,USHORT usPDO4ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO4mv	= usPDO4mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO4ma	= usPDO4ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO5mv PDO voltage in mV for PDO5
/// @param usPDO5ma PDO current in mA for PDO5
void PD_BM_PDO5_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO5mv,USHORT usPDO5ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO5mv	= usPDO5mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO5ma	= usPDO5ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO6mv PDO voltage in mV for PDO6
/// @param usPDO6ma PDO current in mA for PDO6
void PD_BM_PDO6_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO6mv,USHORT usPDO6ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO6mv	= usPDO6mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO6ma	= usPDO6ma;
}
/// @brief BM PDO Sink 2 Configuration
///        Voltage in 1mv Unit - 5000 (5v). And in 50mV Steps.
///        Current in 1ma Unit – 3000 (3A), 10mA Steps
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usPDO7mv PDO voltage in mV for PDO7
/// @param usPDO7ma PDO current in mA for PDO7
void PD_BM_PDO7_Sink_2(FT_EEPROM_PD *pPD_EEProm,USHORT usPDO7mv,USHORT usPDO7ma)
{
    pPD_EEProm->BM_PDO_Sink_2.PDO7mv	= usPDO7mv;
    pPD_EEProm->BM_PDO_Sink_2.PDO7ma	= usPDO7ma;
}

/// @brief Sender Response Timer - (Default=27)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucSrcResTimer Sender Response Timer value
void PD_SenderResponseTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucSrcResTimer)
{
    pPD_EEProm->srt     = ucSrcResTimer;
}
/// @brief Hard Reset Timer - (Default=30)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucHrdRstTimer Hard Reset Timer value
void PD_HardResetTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucHrdRstTimer)
{
    pPD_EEProm->hrt     = ucHrdRstTimer;    
}
/// @brief Source Capability Timer - (Default=190)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucSrcCapTimer Source Capability Timer value
void PD_SourceCapabilityTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucSrcCapTimer)
{
    pPD_EEProm->sct     = ucSrcCapTimer;   
}

/// @brief Discover Identity Timer - (Default=45)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucDiscIdeTimer Discover Identity Timer value
void PD_DiscoverIdentityTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucDiscIdeTimer)
{
    pPD_EEProm->dit     = ucDiscIdeTimer;    
}
/// @brief Source Recover Timer - (Default=750)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usSrcRecTimer Source Recover Timer value
void PD_SenderRecoverTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usSrcRecTimer)
{
    pPD_EEProm->srcrt   = usSrcRecTimer;   
}
/// @brief Transition Timer -  (Default=500)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usTrTimer Transition Timer value
void PD_TransitionTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usTrTimer)
{
    pPD_EEProm->trt     = usTrTimer;   
}
/// @brief Source off timer - (Default=890)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usSrcOffTimer Source off timer value
void PD_SourceoffTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usSrcOffTimer)
{
    pPD_EEProm->sofft   = usSrcOffTimer;   
}
/// @brief No Response Timer -  (Default=4000)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usNRTimer No Response Timer value
void PD_NoResponseTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usNRTimer)
{
    pPD_EEProm->nrt     = usNRTimer;  
}
/// @brief Sink Wait Capability Timer - (Default=320)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usSWCTimer Sink Wait Capability Timer value
void PD_SinkWaitCapabilityTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usSWCTimer)
{
    pPD_EEProm->swct    = usSWCTimer;   
}
/// @brief Sink Request Timer - (Default=110)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usSnkReqTimer Sink Request Timer value
void PD_SinkRequestTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usSnkReqTimer)
{
    pPD_EEProm->snkrt   = usSnkReqTimer;   
}
/// @brief Discharge Timer -  (Default=100)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucDiscTimer Discharge Timer value
void PD_DischargeTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucDiscTimer)
{
    pPD_EEProm->dt      = ucDiscTimer;   
}
/// @brief Chunk not supported timer - (Default=40)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucCNSTimer Chunk not supported timer value
void PD_ChunkNotSupportedTimer(FT_EEPROM_PD *pPD_EEProm, UCHAR ucCNSTimer)
{
    pPD_EEProm->cnst    = ucCNSTimer;    
}
/// @brief Idle Timer - (Default=10000)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param usIdleTimer Idle Timer value
void PD_IdleTimer(FT_EEPROM_PD *pPD_EEProm, USHORT usIdleTimer)
{
    pPD_EEProm->it      = usIdleTimer; 
}
/// @brief I2C Address (hex)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param ucI2cAddr I2C Address value
void PD_I2CAddress(FT_EEPROM_PD *pPD_EEProm,UCHAR ucI2cAddr)
{
    pPD_EEProm->i2caddr  = ucI2cAddr;
}
/// @brief Power Reserved for OWN use - (default=2500)  Min-0 , Max-65535 (65Watts)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param uiPowerRes Power Reserved value in milli-watts (mw)
void PD_PowerReserved(FT_EEPROM_PD *pPD_EEProm,UINT uiPowerRes)
{
    pPD_EEProm->prou     = uiPowerRes;
}
/// @brief Trim settings
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param uiTrim1 Trim 1 value
/// @param uiTrim2 Trim 2 value
void PD_Trim(FT_EEPROM_PD *pPD_EEProm,UINT uiTrim1, UINT uiTrim2)
{
    pPD_EEProm->trim1    = uiTrim1;
    pPD_EEProm->trim2    = uiTrim2;
}
/// @brief Enable/disable EXTERNAL_DC_POWER - (default = 0)
/// @param pPD_EEProm Pointer to FT_EEPROM_PD structure
/// @param bExtDCPower true to enable EXTERNAL_DC_POWER, false otherwise
void PD_ExtDCPower(FT_EEPROM_PD *pPD_EEProm, bool bExtDCPower)
{
    pPD_EEProm->extdc    = bExtDCPower;
}


#endif //PDCONFIG_HEADER_H