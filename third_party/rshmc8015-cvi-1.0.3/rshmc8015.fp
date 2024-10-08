s��           h ��  =   �   ����                               rshmc8015                       R&S HMC 8015 Power Analyzer Driver          _VI_FUNC                                                     � ��ViStatus     � ��ViRsrc     	� 	��ViBoolean     	� 	��ViSession     � ��ViString     � ��ViUInt32     � ��ViAttr  �  � ��ViInt32     � ��ViInt64  � � ��ViReal64     �  ViChar[]  � � ��ViInt16     
�  	ViReal64[]  � � ��ViUInt16     	�  ViInt16[]     	�  ViInt32[]     � 	 
ViBoolean[]   _    This instrument module provides programming support for the Rohde&Schwarz DC power supplies.
     $    This class configures acquisition.     ;    This class contains the attribute that configure display.         This class configures view.     $    This class configures measurement.     #    This class configures integrator.     B    This class contains the attribute that configure system logging.     G    This class contains the attribute that configure system logging file.         This class configures limit.     .    This class configures external input output.    Y    This class contains functions and sub-classes that control common instrument operations. These functions include many of functions that VXIplug&play require, such as reset, self-test, revision query, error query, and error message. This class also contains functions that access error infomation, lock the session, and perform instrument I/O.
     T    This class contains sub-classes for the set, get, and check attribute functions.       �    This class contains functions that set an attribute to a new value.  There are typesafe functions for each attribute data type.     V    This class contains functions that obtain the repeated capabilities of an attribute.     �    This class contains functions that obtain the current value of an attribute.  There are typesafe functions for each attribute data type.     �    This class contains functions that obtain the current value of an attribute.  There are typesafe functions for each attribute data type.     N    This class contains functions that retrieve and clear the error information.     F    This class contains functions that send and receive instrument data.     !    This class configures hardcopy.    �    This function performs the following initialization actions:

- Creates a new instrument driver session.

- Opens a session to the specified device using the interface and address you specify for the Resource Name parameter.

- If the ID Query parameter is set to VI_TRUE, this function queries the instrument ID and checks that it is valid for this instrument driver.

- If the Reset parameter is set to VI_TRUE, this function resets the instrument to a known state.

- Sends initialization commands to set the instrument to the state necessary for the operation of the instrument driver.

- Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Note:

This function creates a new session each time you invoke it. Although you can open more than one session for the same resource, it is best not to do so. You can use the same session in multiple program threads.    �    Reports the status of this operation.

To obtain a text description of the status code, or if the status code is not listed below, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFC0101  ID Query not supported.
3FFC0102  Reset not supported.

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFA0000  Cannot load RS engine.
BFFA0001  Instrument error. Call rshmc8015error_query.
BFFA000C  Invalid attribute.
BFFA000D  Attribute is not writable.
BFFA000E  Attribute is not readable.
BFFA000F  Invalid parameter.
BFFA0010  Invalid value.
BFFA0012  Attribute not supported.
BFFA0013  Value not supported.
BFFA0014  Invalid type.
BFFA0015  Types do not match.
BFFA0016  Attribute already has a value waiting to be updated.
BFFA0018  Not a valid configuration.
BFFA0019  Requested item does not exist or value not available.
BFFA001A  Requested attribute value not known.
BFFA001B  No range table.
BFFA001C  Range table is invalid.
BFFA001F  No channel table has been built for the session.
BFFA0020  Channel name specified is not valid.
BFFA0044  Channel name required.
BFFA0045  Channel name not allowed.
BFFA0046  Attribute not valid for channel.
BFFA0047  Attribute must be channel based.
BFFA0054  Bad channel name in Channel List.

BFFC0011  Instrument returned invalid response to ID Query.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  A "no listeners" condition was detected.
BFFF0060  This interface is not the controller-in-charge.
BFFF0067  Operation is not supported on this session.
    �    Pass the resource name of the device to initialize.

You can also pass the name of a virtual instrument or logical name that you configure with the VISA Configuration utility.  The virtual instrument identifies a specific device and specifies the initial settings for the session. A logical Name identifies a particular virtual instrument.

Refer to the following table below for the exact grammar to use for this parameter.  Optional fields are shown in square brackets ([]).

Syntax
------------------------------------------------------
GPIB[board]::<primary address>[::secondary address]::INSTR
VXI[board]::<logical address>::INSTR
GPIB-VXI[board]::<logical address>::INSTR
ASRL<port>::INSTR
<LogicalName>
<DriverSession>

If you do not specify a value for an optional field, the following values are used:

Optional Field - Value
------------------------------------------------------
board - 0
secondary address - none (31)

The following table contains example valid values for this parameter.

"Valid Value" - Description
------------------------------------------------------
"GPIB::22::INSTR" - GPIB board 0, primary address 22 no
                    secondary address
"GPIB::22::5::INSTR" - GPIB board 0, primary address 22
                       secondary address 5
"GPIB1::22::5::INSTR" - GPIB board 1, primary address 22
                        secondary address 5
"VXI::64::INSTR" - VXI board 0, logical address 64
"VXI1::64::INSTR" - VXI board 1, logical address 64
"GPIB-VXI::64::INSTR" - GPIB-VXI board 0, logical address 64
"GPIB-VXI1::64::INSTR" - GPIB-VXI board 1, logical address 64
"ASRL2::INSTR" - COM port 2
"SampleInstr" - Logical name "SampleInstr"
"xyz432" - Driver Session "xyz432"

Default Value:  "GPIB::14::INSTR"
        Specify whether you want the instrument driver to perform an ID Query.

Valid Range:
VI_TRUE  (1) - Perform ID Query (Default Value)
VI_FALSE (0) - Skip ID Query

When you set this parameter to VI_TRUE, the driver verifies that the instrument you initialize is a type that this driver supports.  

Circumstances can arise where it is undesirable to send an ID Query command string to the instrument.  When you set this parameter to VI_FALSE, the function initializes the instrument without performing an ID Query.     �    Specify whether you want the to reset the instrument during the initialization procedure.

Valid Range:
VI_TRUE  (1) - Reset Device (Default Value)
VI_FALSE (0) - Don't Reset

        Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Notes:

(1) This function creates a new session each time you invoke it.  This is useful if you have multiple physical instances of the same type of instrument.  

(2) Avoid creating multiple concurrent sessions to the same physical instrument. Although you can create more than one session for the same resource, it is best not to do so. A better approach is to use the same session in multiple execution threads.    �#����  `    Status                            � 9   �  �    Resource Name                     � 9 �       ID Query                          � 9� �       Reset Device                      F �� �  �    Instrument Handle                  	           "GPIB::14::INSTR"   Yes VI_TRUE No VI_FALSE   Yes VI_TRUE No VI_FALSE    	          9    This function performs the following initialization actions:

- Creates a new instrument driver session and optionally sets the initial state of the following session attributes:

    RSHMC8015_ATTR_RANGE_CHECK
    RSHMC8015_ATTR_QUERY_INSTRUMENT_STATUS

- Opens a session to the specified device using the interface and address you specify for the Resource Name parameter.

- If the ID Query parameter is set to VI_TRUE, this function queries the instrument ID and checks that it is valid for this instrument driver.

- If the Reset parameter is set to VI_TRUE, this function resets the instrument to a known state.

- Sends initialization commands to set the instrument to the state necessary for the operation of the instrument driver.

- Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Note:

This function creates a new session each time you invoke it. Although you can open more than one session for the same resource, it is best not to do so. You can use the same session in multiple program threads.    	�    Reports the status of this operation.

To obtain a text description of the status code, or if the status code is not listed below, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

Status Codes:

Status    Description
-------------------------------------------------
       0  No error (the call was successful).

3FFC0101  ID Query not supported.
3FFC0102  Reset not supported.

3FFF0005  The specified termination character was read.
3FFF0006  The specified number of bytes was read.

BFFA0000  Cannot load RS engine.
BFFA0001  Instrument error. Call rshmc8015error_query.
BFFA000C  Invalid attribute.
BFFA000D  Attribute is not writable.
BFFA000E  Attribute is not readable.
BFFA000F  Invalid parameter.
BFFA0010  Invalid value.
BFFA0012  Attribute not supported.
BFFA0013  Value not supported.
BFFA0014  Invalid type.
BFFA0015  Types do not match.
BFFA0016  Attribute already has a value waiting to be updated.
BFFA0018  Not a valid configuration.
BFFA0019  Requested item does not exist or value not available.
BFFA001A  Requested attribute value not known.
BFFA001B  No range table.
BFFA001C  Range table is invalid.
BFFA001F  No channel table has been built for the session.
BFFA0020  Channel name specified is not valid.
BFFA0044  Channel name required.
BFFA0045  Channel name not allowed.
BFFA0046  Attribute not valid for channel.
BFFA0047  Attribute must be channel based.
BFFA0049  Missing option name (nothing before the '=').
BFFA004A  Missing option value (nothing after the '=').
BFFA004B  Bad option name.
BFFA004C  Bad option value.
BFFA0054  Bad channel name in Channel List

BFFC0011  Instrument returned invalid response to ID Query.

BFFF0000  Miscellaneous or system error occurred.
BFFF000E  Invalid session handle.
BFFF0015  Timeout occurred before operation could complete.
BFFF0034  Violation of raw write protocol occurred.
BFFF0035  Violation of raw read protocol occurred.
BFFF0036  Device reported an output protocol error.
BFFF0037  Device reported an input protocol error.
BFFF0038  Bus error occurred during transfer.
BFFF003A  Invalid setup (attributes are not consistent).
BFFF005F  A "no listeners" condition was detected.
BFFF0060  This interface is not the controller-in-charge.
BFFF0067  Operation is not supported on this session.
    �    Pass the resource name of the device to initialize.

You can also pass the name of a virtual instrument or logical name that you configure with the VISA Configuration utility.  The virtual instrument identifies a specific device and specifies the initial settings for the session. A logical Name identifies a particular virtual instrument.

Refer to the following table below for the exact grammar to use for this parameter.  Optional fields are shown in square brackets ([]).

Syntax
------------------------------------------------------
GPIB[board]::<primary address>[::secondary address]::INSTR
VXI[board]::<logical address>::INSTR
GPIB-VXI[board]::<logical address>::INSTR
ASRL<port>::INSTR
<LogicalName>
<DriverSession>

If you do not specify a value for an optional field, the following values are used:

Optional Field - Value
------------------------------------------------------
board - 0
secondary address - none (31)

The following table contains example valid values for this parameter.

"Valid Value" - Description
------------------------------------------------------
"GPIB::22::INSTR" - GPIB board 0, primary address 22 no
                    secondary address
"GPIB::22::5::INSTR" - GPIB board 0, primary address 22
                       secondary address 5
"GPIB1::22::5::INSTR" - GPIB board 1, primary address 22
                        secondary address 5
"VXI::64::INSTR" - VXI board 0, logical address 64
"VXI1::64::INSTR" - VXI board 1, logical address 64
"GPIB-VXI::64::INSTR" - GPIB-VXI board 0, logical address 64
"GPIB-VXI1::64::INSTR" - GPIB-VXI board 1, logical address 64
"ASRL2::INSTR" - COM port 2
"SampleInstr" - Logical name "SampleInstr"
"xyz432" - Driver Session "xyz432"

Default Value:  "GPIB::14::INSTR"
        Specify whether you want the instrument driver to perform an ID Query.

Valid Range:
VI_TRUE  (1) - Perform ID Query (Default Value)
VI_FALSE (0) - Skip ID Query

When you set this parameter to VI_TRUE, the driver verifies that the instrument you initialize is a type that this driver supports.  

Circumstances can arise where it is undesirable to send an ID Query command string to the instrument.  When you set this parameter to VI_FALSE, the function initializes the instrument without performing an ID Query.     �    Specify whether you want the to reset the instrument during the initialization procedure.

Valid Range:
VI_TRUE  (1) - Reset Device (Default Value)
VI_FALSE (0) - Don't Reset

    o    You can use this control to set the initial value of certain attributes for the session.  The following table lists the attributes and the name you use in this parameter to identify the attribute.

Name              Attribute Defined Constant   
--------------------------------------------
RangeCheck        RSCMWWXM_ATTR_RANGE_CHECK
QueryInstrStatus  RSCMWWXM_ATTR_QUERY_INSTRUMENT_STATUS   

The format of this string is, "AttributeName=Value" where AttributeName is the name of the attribute and Value is the value to which the attribute will be set.  To set multiple attributes, separate their assignments with a comma.  

If you pass NULL or an empty string for this parameter, the session uses the default values for the attributes.   You can override the default values by assigning a value explicitly in a string you pass for this parameter.  You do not have to specify all of the attributes and may leave any of them out.  If you do not specify one of the attributes, its default value will be used.  

The default values for the attributes are shown below:

    Attribute Name     Default Value
    ----------------   -------------
    RangeCheck         VI_TRUE
    QueryInstrStatus   VI_FALSE
    

The following are the valid values for ViBoolean attributes:

    True:     1, True, or VI_TRUE
    False:    0, False, or VI_FALSE


Default Value:
       "QueryInstrStatus=1"
        Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Notes:

(1) This function creates a new session each time you invoke it.  This is useful if you have multiple physical instances of the same type of instrument.  

(2) Avoid creating multiple concurrent sessions to the same physical instrument. Although you can create more than one RS session for the same resource, it is best not to do so. A better approach is to use the same RS session in multiple execution threads.    '#����  `    Status                            0� 9   �  �    Resource Name                     7� 9 �       ID Query                          9� 9� �       Reset Device                      :U �  � �    Option String                     ?� �� �  �    Instrument Handle                  	           "GPIB::14::INSTR"   Yes VI_TRUE No VI_FALSE   Yes VI_TRUE No VI_FALSE    "QueryInstrStatus=1"    	           q    Sets acq mode.

Attribute(s):
RSHMC8015_ATTR_ACQ_MODE

Remote-control command(s):
CHANnel<n>[:ACQuisition]:MODE    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets acq mode.

Valid Values:
RSHMC8015_VAL_ACQ_MODE_AC     (0) - AC
RSHMC8015_VAL_ACQ_MODE_DC     (1) - DC
RSHMC8015_VAL_ACQ_MODE_EXTERN (2) - Extern

Default Value: RSHMC8015_VAL_ACQ_MODE_AC  (0)

Attribute:
RSHMC8015_ATTR_ACQ_MODE
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    D$#����  `    Status                            K�-   �  `    Instrument Handle                 L] GM � `    Acquisition Mode                  MQ G t �  `    Channel                            	                          _AC RSHMC8015_VAL_ACQ_MODE_AC DC RSHMC8015_VAL_ACQ_MODE_DC Extern RSHMC8015_VAL_ACQ_MODE_EXTERN    1   x    Configures AC acquisition.

Attribute(s):
RSHMC8015_ATTR_ACQ_PLL_SOURCE
RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER
RSHMC8015_ATTR_ACQ_DIGITAL_FILTER
RSHMC8015_ATTR_ACQ_BWL

Remote-control command(s):
CHANnel<n>[:ACQuisition]:MODE[:AC]:PLL
CHANnel<n>[:ACQuisition]:MODE[:FILTer]:FREQuency
CHANnel<n>[:ACQuisition]:MODE[:FILTer]:DIGital
CHANnel<n>[:ACQuisition]:MODE[:FILTer]:ANALog
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets PLL source.

Valid Values:
RSHMC8015_VAL_PLL_SOURCE_VOLTAGE  (0) - Voltage
RSHMC8015_VAL_PLL_SOURCE_CURRENT  (1) - Current

Default Value: RSHMC8015_VAL_PLL_SOURCE_VOLTAGE  (0)

Attribute:
RSHMC8015_ATTR_ACQ_PLL_SOURCE
     �    Sets state band width limit.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_DIGITAL_FILTER     �    Sets state of acquisition frequency filter.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_FREQUENCY_FILTER     �    Sets state of acquisition digital signal filter.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_BWL     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    Pv#����  `    Status                            W�-   �  `    Instrument Handle                 X� Ga � `    PLL Source                        Y� � �       Digital Filter                    Z> � � �       Frequency Filter                  Z� �j �       BWL                               [� G g �  `    Channel                            	                          RVoltage RSHMC8015_VAL_PLL_SOURCE_VOLTAGE Current RSHMC8015_VAL_PLL_SOURCE_CURRENT    On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    1   �    Configures voltage acquisition.

Attribute(s):
RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE
RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE
RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR
RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT

Remote-control command(s):
CHANnel<n>[:ACQuisition]:VOLTage:RANGe:AUTO
CHANnel<n>[:ACQuisition]:VOLTage:RANGe
CHANnel<n>[:ACQuisition]:VOLTage:CFACtor
CHANnel<n>[:ACQuisition]:VOLTage:INVert
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets the crest factor for voltage.

Valid Values:
RSHMC8015_VAL_CREST_FACTOR_3  (0) - 3
RSHMC8015_VAL_CREST_FACTOR_6  (1) - 6

Default Value: RSHMC8015_VAL_CREST_FACTOR_3  (0)

Attribute:
RSHMC8015_ATTR_ACQ_VOLTAGE_CREST_FACTOR
     �    Sets state of auto range for voltage range.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_VOLTAGE_AUTORANGE     �    Sets state of voltage polarity inversion.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_VOLTAGE_INVERT     �    Selects an appropriate voltage range for passed RMS value.

Valid Values: 0.0 - 6.0e2

Default Value: 300.0 V

Attribute:
RSHMC8015_ATTR_ACQ_VOLTAGE_RANGE

Note(s):

(1) This control is only available when Autorange is set to Off.     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    _�#����  `    Status                            g0-   �  `    Instrument Handle                 g� � � `    Crest Factor                      h� G	 �       Autorange                         i� �� �       Invert                            jC G[ � `    Range                             k3 G d �  `    Channel                            	                          >3 RSHMC8015_VAL_CREST_FACTOR_3 6 RSHMC8015_VAL_CREST_FACTOR_6    On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    300.0    1   �    Configures current acquisition.

Attribute(s):
RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE
RSHMC8015_ATTR_ACQ_CURRENT_RANGE
RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR
RSHMC8015_ATTR_ACQ_CURRENT_INVERT

Remote-control command(s):
CHANnel<n>[:ACQuisition]:CURRent:RANGe:AUTO
CHANnel<n>[:ACQuisition]:CURRent:RANGe
CHANnel<n>[:ACQuisition]:CURRent:CFACtor
CHANnel<n>[:ACQuisition]:CURRent:INVert

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets the crest factor for current.

Valid Values:
RSHMC8015_VAL_CREST_FACTOR_3  (0) - 3
RSHMC8015_VAL_CREST_FACTOR_6  (1) - 6

Default Value: RSHMC8015_VAL_CREST_FACTOR_3  (0)

Attribute:
RSHMC8015_ATTR_ACQ_CURRENT_CREST_FACTOR
     �    Sets state of auto range for current range.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_CURRENT_AUTORANGE     �    Sets state of current polarity inversion.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_ACQ_CURRENT_INVERT     �    Selects an appropriate current range for passed RMS value.

Valid Values: 0.0 - 2.0e1

Default Value: 100.0e-3 A

Attribute:
RSHMC8015_ATTR_ACQ_CURRENT_RANGE

Note(s):

(1) This control is only available when Autorange is set to Off.     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    o#����  `    Status                            v�-   �  `    Instrument Handle                 wX � � `    Crest Factor                      xF G	 �       Autorange                         x� �� �       Invert                            y� G[ � `    Range                             z� G ] �  `    Channel                            	                          >3 RSHMC8015_VAL_CREST_FACTOR_3 6 RSHMC8015_VAL_CREST_FACTOR_6    On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    	100.0e-3    1    �    Query whether overcurrent protection was triggered.

Attribute(s):
RSHMC8015_ATTR_ACQ_OCP

Remote-control command(s):
CHANnel<n>[:ACQuisition]:CURRent:PROTection?

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Query whether overcurrent protection was triggered.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Attribute:
RSHMC8015_ATTR_ACQ_OCP     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    }�#����  `    Status                            �2-   �  `    Instrument Handle                 �� GO �  �    OCP                               �� G m �  `    Channel                            	               	            1    �    Reset overcurrent protection.

Attribute(s):
RSHMC8015_ATTR_ACQ_OCP_RESET

Remote-control command(s):
CHANnel<n>[:ACQuisition]:CURRent:PROTection:RESet


    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
    �i#����  `    Status                            ��-   �  `    Instrument Handle                 �� Q r �  `    Channel                            	               1    �    Displays a text message box on the front display.

Attribute(s):
RSHMC8015_ATTR_DISPLAY_TEXT

Remote-control command(s):
DISPlay:TEXT[:DATA]    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     e    The text to display in the message box.

Default Value: ""

Attribute:
RSHMC8015_ATTR_DISPLAY_TEXT
    �:#����  `    Status                            ��-   �  `    Instrument Handle                 �s G � �  �    Text                               	               ""    �    Clears the text message box on the front display.

Attribute(s):
RSHMC8015_ATTR_DISPLAY_CLEAR

Remote-control command(s):
DISPlay:TEXT:CLEar    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �+#����  `    Status                            ��-   �  `    Instrument Handle                  	               Z    Sets view mode.

Attribute(s):
RSHMC8015_ATTR_VIEW_MODE

Remote-control command(s):
VIEW    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    Sets view mode.

Valid Values:
RSHMC8015_VAL_VIEW_MODE_NORMAL     (0) - Normal
RSHMC8015_VAL_VIEW_MODE_HARMONICS  (1) - Harmonics
RSHMC8015_VAL_VIEW_MODE_TRENDCHART (2) - Trendchart
RSHMC8015_VAL_VIEW_MODE_SIGNALS    (3) - Signals
RSHMC8015_VAL_VIEW_MODE_STANDARDS  (4) - Standards
RSHMC8015_VAL_VIEW_MODE_INRUSH     (5) - Inrush

Default Value: RSHMC8015_VAL_VIEW_MODE_NORMAL  (0)

Attribute:
RSHMC8015_ATTR_VIEW_MODE
    �@#����  `    Status                            ��-   �  `    Instrument Handle                 �y G � � `    View Mode                          	                          �Normal RSHMC8015_VAL_VIEW_MODE_NORMAL Harmonics RSHMC8015_VAL_VIEW_MODE_HARMONICS Trendchart RSHMC8015_VAL_VIEW_MODE_TRENDCHART Signals RSHMC8015_VAL_VIEW_MODE_SIGNALS Standards RSHMC8015_VAL_VIEW_MODE_STANDARDS Inrush RSHMC8015_VAL_VIEW_MODE_INRUSH    �    Sets page's cell count.

Attribute(s):
RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE

Remote-control command(s):
VIEW:NORMal:PAGE<n>:SIZE    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets page's cell count.

Valid Values:
RSHMC8015_VAL_VIEW_PAGE_SIZE_6   (0) - 6
RSHMC8015_VAL_VIEW_PAGE_SIZE_10  (1) - 10

Default Value: RSHMC8015_VAL_VIEW_PAGE_SIZE_6  (0)

Attribute:
RSHMC8015_ATTR_VIEW_NORM_PAGE_SIZE
     H    Numerical selection of a page

Valid Values:
1 to 4

Default Value: 1
    �f#����  `    Status                            ��-   �  `    Instrument Handle                 �� Gk � `    Size                              �� G J �  `    Page                               	                          D6 RSHMC8015_VAL_VIEW_PAGE_SIZE_6 10 RSHMC8015_VAL_VIEW_PAGE_SIZE_10    1    y    Selects active page.

Attribute(s):
RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE

Remote-control command(s):
VIEW:NORMal[:SHOW]    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     o    Selects active page.

Valid Values: 1 - 4

Default Value: 1

Attribute:
RSHMC8015_ATTR_VIEW_NORM_ACTIVE_PAGE
    ��#����  `    Status                            �-   �  `    Instrument Handle                 �� G � � `    Active Page                        	               1    �    Selects the normal view cell function.

Attribute(s):
RSHMC8015_ATTR_VIEW_NORM_FUNCTION

Remote-control command(s):
VIEW:NORMal:PAGE<n>:CELL<n>:FUNCtion    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    	�    Selects the normal view cell function.

Valid Values:
RSHMC8015_VAL_NORMAL_VIEW_FUNC_EMPTY   (0) - Empty
RSHMC8015_VAL_NORMAL_VIEW_FUNC_P       (1) - Active Power
RSHMC8015_VAL_NORMAL_VIEW_FUNC_S       (2) - Apparent Power
RSHMC8015_VAL_NORMAL_VIEW_FUNC_Q       (3) - Reactive Power
RSHMC8015_VAL_NORMAL_VIEW_FUNC_PF      (4) - Power Factor Lambda
RSHMC8015_VAL_NORMAL_VIEW_FUNC_PHI     (5) - Phase Difference Phi
RSHMC8015_VAL_NORMAL_VIEW_FUNC_FU      (6) - Voltage Frequency
RSHMC8015_VAL_NORMAL_VIEW_FUNC_FI      (7) - Current Frequency
RSHMC8015_VAL_NORMAL_VIEW_FUNC_UPP     (8) - Maximum Voltage
RSHMC8015_VAL_NORMAL_VIEW_FUNC_UMP     (9) - Minimum Voltage
RSHMC8015_VAL_NORMAL_VIEW_FUNC_IPP    (10) - Maximum Current
RSHMC8015_VAL_NORMAL_VIEW_FUNC_IMP    (11) - Minimum Current
RSHMC8015_VAL_NORMAL_VIEW_FUNC_PPP    (12) - Maximum Power
RSHMC8015_VAL_NORMAL_VIEW_FUNC_PMP    (13) - Minimum Power
RSHMC8015_VAL_NORMAL_VIEW_FUNC_URMS   (14) - True RMS Voltage
RSHMC8015_VAL_NORMAL_VIEW_FUNC_UAVG   (15) - Average Voltage
RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRMS   (16) - True RMS Current
RSHMC8015_VAL_NORMAL_VIEW_FUNC_IAVG   (17) - Average Current
RSHMC8015_VAL_NORMAL_VIEW_FUNC_UTHD   (18) - Total Harmonic Dist U
RSHMC8015_VAL_NORMAL_VIEW_FUNC_ITHD   (19) - Total Harmonic Dist I
RSHMC8015_VAL_NORMAL_VIEW_FUNC_DIN    (20) - Digital Input Value
RSHMC8015_VAL_NORMAL_VIEW_FUNC_AIN    (21) - Analog Input Value
RSHMC8015_VAL_NORMAL_VIEW_FUNC_TIME   (22) - Integration Time
RSHMC8015_VAL_NORMAL_VIEW_FUNC_WH     (23) - Watt Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHP    (24) - Positive Watt Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHM    (25) - Negative Watt Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_AH     (26) - Ampere Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHP    (27) - Positive Ampere Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHM    (28) - Negative Ampere Hour
RSHMC8015_VAL_NORMAL_VIEW_FUNC_TEMP   (29) - Temperature
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM1   (30) - Limit 1
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM2   (31) - Limit 2
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM3   (32) - Limit 3
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM4   (33) - Limit 4
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM5   (34) - Limit 5
RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM6   (35) - Limit 6
RSHMC8015_VAL_NORMAL_VIEW_FUNC_URANGE (36) - Range Voltage
RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRANGE (37) - Range Current
RSHMC8015_VAL_NORMAL_VIEW_FUNC_FPLL   (38) - PLL Source Frequency

Default Value: RSHMC8015_VAL_NORMAL_VIEW_FUNC_EMPTY  (0)

Attribute:
RSHMC8015_ATTR_VIEW_NORM_FUNCTION
     H    Numerical selection of a page

Valid Values:
1 to 4

Default Value: 1
     H    Numerical selection of a cell

Valid Values:
1 to 6

Default Value: 1
    ƙ#����  `    Status                            �-   �  `    Instrument Handle                 �� Gk � `    Function                          ب G J �  `    Page                              �� G � �  `    Cell                               	                       '  �Empty RSHMC8015_VAL_NORMAL_VIEW_FUNC_EMPTY Active Power RSHMC8015_VAL_NORMAL_VIEW_FUNC_P Apparent Power RSHMC8015_VAL_NORMAL_VIEW_FUNC_S Reactive Power RSHMC8015_VAL_NORMAL_VIEW_FUNC_Q Power Factor Lambda RSHMC8015_VAL_NORMAL_VIEW_FUNC_PF Phase Difference Phi RSHMC8015_VAL_NORMAL_VIEW_FUNC_PHI Voltage Frequency RSHMC8015_VAL_NORMAL_VIEW_FUNC_FU Current Frequency RSHMC8015_VAL_NORMAL_VIEW_FUNC_FI Maximum Voltage RSHMC8015_VAL_NORMAL_VIEW_FUNC_UPP Minimum Voltage RSHMC8015_VAL_NORMAL_VIEW_FUNC_UMP Maximum Current RSHMC8015_VAL_NORMAL_VIEW_FUNC_IPP Minimum Current RSHMC8015_VAL_NORMAL_VIEW_FUNC_IMP Maximum Power RSHMC8015_VAL_NORMAL_VIEW_FUNC_PPP Minimum Power RSHMC8015_VAL_NORMAL_VIEW_FUNC_PMP True RMS Voltage RSHMC8015_VAL_NORMAL_VIEW_FUNC_URMS Average Voltage RSHMC8015_VAL_NORMAL_VIEW_FUNC_UAVG True RMS Current RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRMS Average Current RSHMC8015_VAL_NORMAL_VIEW_FUNC_IAVG Total Harmonic Dist. U RSHMC8015_VAL_NORMAL_VIEW_FUNC_UTHD Total Harmonic Dist. I RSHMC8015_VAL_NORMAL_VIEW_FUNC_ITHD Digital Input Value RSHMC8015_VAL_NORMAL_VIEW_FUNC_DIN Analog Input Value RSHMC8015_VAL_NORMAL_VIEW_FUNC_AIN Integration Time RSHMC8015_VAL_NORMAL_VIEW_FUNC_TIME Watt Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_WH Positive Watt Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHP Negative Watt Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_WHM Ampere Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_AH Positive Ampere Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHP Negative Ampere Hour RSHMC8015_VAL_NORMAL_VIEW_FUNC_AHM Temperature RSHMC8015_VAL_NORMAL_VIEW_FUNC_TEMP Limit 1 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM1 Limit 2 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM2 Limit 3 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM3 Limit 4 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM4 Limit 5 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM5 Limit 6 RSHMC8015_VAL_NORMAL_VIEW_FUNC_LIM6 Range Voltage RSHMC8015_VAL_NORMAL_VIEW_FUNC_URANGE Range Current RSHMC8015_VAL_NORMAL_VIEW_FUNC_IRANGE PLL Source Frequency RSHMC8015_VAL_NORMAL_VIEW_FUNC_FPLL    1    1   V    Configures harmonics view.

Attribute(s):
RSHMC8015_ATTR_VIEW_HARM_SELECT
RSHMC8015_ATTR_VIEW_HARM_SOURCE
RSHMC8015_ATTR_VIEW_HARM_NUMBER
RSHMC8015_ATTR_VIEW_HARM_SCALING
RSHMC8015_ATTR_VIEW_HARM_SUBSET

Remote-control command(s):
VIEW:HARMonics:VIEW
VIEW:HARMonics:SOURce
VIEW:HARMonics:NUMBer
VIEW:HARMonics:SCALing
VIEW:HARMonics:SUBSet
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Selects harmonics view.

Valid Values:
RSHMC8015_VAL_VIEW_HARM_VIEW_BAR  (0) - Bar
RSHMC8015_VAL_VIEW_HARM_VIEW_TAB  (1) - Table

Default Value: RSHMC8015_VAL_VIEW_HARM_VIEW_BAR  (0)

Attribute:
RSHMC8015_ATTR_VIEW_HARM_SELECT
    2    Selects harmonics source.

Valid Values:
RSHMC8015_VAL_VIEW_HARM_SOURCE_VOLTAGE  (0) - Voltage
RSHMC8015_VAL_VIEW_HARM_SOURCE_CURRENT  (1) - Current
RSHMC8015_VAL_VIEW_HARM_SOURCE_BOTH     (2) - Both

Default Value: RSHMC8015_VAL_VIEW_HARM_SOURCE_VOLTAGE  (0)

Attribute:
RSHMC8015_ATTR_VIEW_HARM_SOURCE
     Z    Sets number of harmonics.

Default Value: 5

Attribute:
RSHMC8015_ATTR_VIEW_HARM_NUMBER
        Selects harmonics scaling.

Valid Values:
RSHMC8015_VAL_VIEW_HARM_SCALING_ABSOLUTE  (0) - Absolute
RSHMC8015_VAL_VIEW_HARM_SCALING_PERCENT  (1) - Percent


Default Value: RSHMC8015_VAL_VIEW_HARM_SCALING_ABSOLUTE  (0)

Attribute:
RSHMC8015_ATTR_VIEW_HARM_SCALING
     �    Selects harmonics subset.

Valid Values:
RSHMC8015_VAL_VIEW_HARM_SUBSET_EVEN  (0) - Even
RSHMC8015_VAL_VIEW_HARM_SUBSET_ODD   (1) - Odd


Default Value: RSHMC8015_VAL_VIEW_HARM_SUBSET_EVEN  (0)

Attribute:
RSHMC8015_ATTR_VIEW_HARM_SUBSET
    �#����  `    Status                            �-   �  `    Instrument Handle                 �� G ] � `    Select                            � G � � `    Source                            �� Gn �  `    Number                            �P � � � `    Scaling                           �` �6 � `    Subset                             	                          LBar RSHMC8015_VAL_VIEW_HARM_VIEW_BAR Table RSHMC8015_VAL_VIEW_HARM_VIEW_TAB               �Voltage RSHMC8015_VAL_VIEW_HARM_SOURCE_VOLTAGE Current RSHMC8015_VAL_VIEW_HARM_SOURCE_CURRENT Both RSHMC8015_VAL_VIEW_HARM_SOURCE_BOTH    5               bAbsolute RSHMC8015_VAL_VIEW_HARM_SCALING_ABSOLUTE Percent RSHMC8015_VAL_VIEW_HARM_SCALING_PERCENT               PEven RSHMC8015_VAL_VIEW_HARM_SUBSET_EVEN Odd RSHMC8015_VAL_VIEW_HARM_SUBSET_ODD    �    Queries measurements specified via ConfigureFunctionList method.

Attribute(s):
-

Remote-control command(s):
CHANnel<n>:MEASurement:FORMat
CHANnel<n>:MEASurement:DATA?
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
     C    Queries measurements specified via ConfigureFunctionList method.
     #    Number of array points requested.     2    Number of points actually returned in the array.    �T#����  `    Status                            ��-   �  `    Instrument Handle                 �� G 4 �  `    Channel                           �� G� �  `    Data                              �& G � �  �    Array Length                      �Q �K �  �    Actual Data Length                 	               1    	                	            �    Sets list of function names.

Attribute(s):
-

Remote-control command(s):
CHANnel<n>:MEASurement:FUNCtions   <function>{,<function>}
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
         List of function names.
    ��#����  `    Status                           -   �  `    Instrument Handle                � G R �  `    Channel                           GW �  `    Function List                      	               1    ""    p    Queries list of function name.

Attribute(s):
-

Remote-control command(s):
CHANnel<n>:MEASurement:FUNCtions?
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    Pass the number of bytes in the ViChar array you specify for the Output parameter.  

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Attribute Value buffer parameter.
    �    This indicator returns the function names as comma separated strings, for example: URMS,P,TEMP1

The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you specify 0 for the Buffer Size parameter, you can pass VI_NULL for this parameter.     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   	�#����  `    Status                           -   �  `    Instrument Handle                � Gt �  �    Buffer Size                      � �  �      Function List                    � G 4 �  `    Channel                            	                   	            1    �    This function returns the length of function list.

Attribute(s):
RSHMC8015_ATTR_MEAS_FUNCTION_LIST_LENGTH

Remote-control command(s):
CHANnel<n>:MEASurement:FUNCtions:COUNt?    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc804x_error_message function.  To obtain additional information about the error condition, call the rshmc804x_GetError function.  To clear the error information from the driver, call the rshmc804x_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc804x_init or rshmc804x_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     &    Returns the length of function list.     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   �#����  `    Status                           !>-   �  `    Instrument Handle                !� G` �  `    Length                           "( G H �  `    Channel                            	               	            1    �    Configures the global data integrator function.

Attribute(s):
RSHMC8015_ATTR_INTEGRATOR_STATE
RSHMC8015_ATTR_INTEGRATOR_MODE
RSHMC8015_ATTR_INTEGRATOR_DURATION

Remote-control command(s):
INTegrator[:STATe]
INTegrator:MODE
INTegrator:DURation
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets Integrator state (enables or disables the Integrator).

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_INTEGRATOR_STATE     g    Sets the integration timer value.

Default Value: 0.0

Attribute:
RSHMC8015_ATTR_INTEGRATOR_DURATION
    e    Sets the integration mode.

Valid Values:
RSHMC8015_VAL_INTEGRATOR_MODE_MANUAL    (0) - Manual
RSHMC8015_VAL_INTEGRATOR_MODE_DURATION  (1) - Duration
RSHMC8015_VAL_INTEGRATOR_MODE_SPAN      (2) - Span
RSHMC8015_VAL_INTEGRATOR_MODE_EXTERN    (3) - Extern

Default Value: RSHMC8015_VAL_INTEGRATOR_MODE_MANUAL  (0)

Attribute:
RSHMC8015_ATTR_INTEGRATOR_MODE
   $i#����  `    Status                           +�-   �  `    Instrument Handle                ,� G f �       Enabled                          -d Gy �  `    Duration                         -� G � � `    Mode                               	               On VI_TRUE Off VI_FALSE    0.0               �Manual RSHMC8015_VAL_INTEGRATOR_MODE_MANUAL Duration RSHMC8015_VAL_INTEGRATOR_MODE_DURATION Span RSHMC8015_VAL_INTEGRATOR_MODE_SPAN Extern RSHMC8015_VAL_INTEGRATOR_MODE_EXTERN       This function specifies the type of integrator operation and performs the operation.

Attribute(s):
RSHMC8015_ATTR_INTEGRATOR_START
RSHMC8015_ATTR_INTEGRATOR_STOP
RSHMC8015_ATTR_INTEGRATOR_RESET

Remote-control command(s):
INTegrator:STARt
INTegrator:STOP
INTegrator:RESet
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    ~    Selects the integration operation.

Valid Values:
RSHMC8015_VAL_INTEGRATOR_OPERATION_START  (0) - Start
RSHMC8015_VAL_INTEGRATOR_OPERATION_STOP   (1) - Stop
RSHMC8015_VAL_INTEGRATOR_OPERATION_RESET  (2) - Reset

Default Value: RSHMC8015_VAL_INTEGRATOR_OPERATION_START  (0)

Attribute:
RSHMC8015_ATTR_INTEGRATOR_START
RSHMC8015_ATTR_INTEGRATOR_STOP
RSHMC8015_ATTR_INTEGRATOR_RESET
   2U#����  `    Status                           9�-   �  `    Instrument Handle                :� G � � `    Operation                          	                          �Start RSHMC8015_VAL_INTEGRATOR_OPERATION_START Stop RSHMC8015_VAL_INTEGRATOR_OPERATION_STOP Reset RSHMC8015_VAL_INTEGRATOR_OPERATION_RESET    �    Sets integrator's start time.

Attribute(s):
-

Remote-control command(s):
INTegrator:STIME   <year>,<month>,<day>,<hour>,<minute>,<second>

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     K    This parameter representing the year.

Default Value: 2015

Attribute:
-
     l    This parameter representing the month of the year.

Valid values: 1 to 12

Default Value: 6

Attribute:
-
     l    This parameter representing the day of the month.

Valid values: 1 to 31

Default Value: 16

Attribute:
-
     H    This parameter representing the hour.

Default Value: 9

Attribute:
-
     L    This parameter representing the minutes.

Default Value: 20

Attribute:
-
     K    This parameter representing the seconds.

Default Value: 0

Attribute:
-
   =�#����  `    Status                           Eq-   �  `    Instrument Handle                F- G M �  `    Year                             F� G � �  `    Month                            F� G� �  `    Day                              Gh � M �  `    Hour                             G� � � �  `    Minute                           H �� �  `    Second                             	               2015    6    16    9    20    0    �    Set the filename and device for logging.

Attribute(s):
-

Remote-control command(s):
LOG:FNAMe {<File_Name>},[{INT | EXT | DEF}]

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    !    Selects the device.

Valid Values:
RSHMC8015_VAL_DEVICE_INT (0) - Internal
RSHMC8015_VAL_DEVICE_EXT (1) - External
RSHMC8015_VAL_DEVICE_DEF (2) - Def

Default Value: RSHMC8015_VAL_DEVICE_INT  (0)

Note(s):

(1) Internal: Internal Memory

(2) External: USB Stick

(3) Def: Internal Memory     ,    Selects the filename.

Default Value:  ""
   J�#����  `    Status                           RD-   �  `    Instrument Handle                S  GC � `    Device                           T) G � �  �    Filename                           	                          aInternal RSHMC8015_VAL_DEVICE_INT External RSHMC8015_VAL_DEVICE_EXT Def RSHMC8015_VAL_DEVICE_DEF    ""    �    Configures the global data logging function.

Attribute(s):
RSHMC8015_ATTR_LOGGING_STATE
RSHMC8015_ATTR_LOGGING_MODE
RSHMC8015_ATTR_LOGGING_COUNT
RSHMC8015_ATTR_LOGGING_TIME

Remote-control command(s):
LOG[:STATe]
LOG:MODE
LOG:COUNt
LOG:DURation

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets logging state (starts or stops a logging session).

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_LOGGING_STATE     \    Sets the time in "TIME" mode.

Default Value: 1.0

Attribute:
RSHMC8015_ATTR_LOGGING_TIME
    �    Selects the mode of the logging function.

Valid Values:
RSHMC8015_VAL_LOGGING_MODE_UNLIMITED  (0) - Unlimited
RSHMC8015_VAL_LOGGING_MODE_COUNT      (1) - Count
RSHMC8015_VAL_LOGGING_MODE_TIME       (2) - Time
RSHMC8015_VAL_LOGGING_MODE_SPAN       (3) - Span

Default Value: RSHMC8015_VAL_LOGGING_MODE_UNLIMITED  (0)

Attribute:
RSHMC8015_ATTR_LOGGING_MODE

Note(s):

(1) Unlimited: Selects unlimited logging mode

(2) Count: Selects count logging mode

(3) Time: Selects time logging mode     m    Sets maximum number of data rows of a log file.

Default Value: 1

Attribute:
RSHMC8015_ATTR_LOGGING_COUNT
   V�#����  `    Status                           ^5-   �  `    Instrument Handle                ^� G f �       Enabled                          _� � � �  `    Time                             ` G � � `    Mode                             b Gy �  `    Count                              	               On VI_TRUE Off VI_FALSE    1.0               �Unlimited RSHMC8015_VAL_LOGGING_MODE_UNLIMITED Count RSHMC8015_VAL_LOGGING_MODE_COUNT Time RSHMC8015_VAL_LOGGING_MODE_TIME Span RSHMC8015_VAL_LOGGING_MODE_SPAN    1    �    Sets logging start time.

Attribute(s):
-

Remote-control command(s):
LOG:STIME   <year>,<month>,<day>,<hour>,<minute>,<second>

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     K    This parameter representing the year.

Default Value: 2015

Attribute:
-
     l    This parameter representing the month of the year.

Valid values: 1 to 12

Default Value: 6

Attribute:
-
     l    This parameter representing the day of the month.

Valid values: 1 to 31

Default Value: 16

Attribute:
-
     H    This parameter representing the hour.

Default Value: 9

Attribute:
-
     L    This parameter representing the minutes.

Default Value: 20

Attribute:
-
     K    This parameter representing the seconds.

Default Value: 0

Attribute:
-
   e'#����  `    Status                           l�-   �  `    Instrument Handle                m` G M �  `    Year                             m� G � �  `    Month                            n' G� �  `    Day                              n� � M �  `    Hour                             n� � � �  `    Minute                           o? �� �  `    Second                             	               2015    6    16    9    20    0    �    Queries the result of limit check.

Attribute(s):
RSHMC8015_ATTR_LIMIT_CHECK_RESULT

Remote-control command(s):
CHANnel<n>:LIMit<n>:RESult[:STATe]?

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Queries the result of limit check.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Attribute:
RSHMC8015_ATTR_LIMIT_CHECK_RESULT     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
     I    Numerical selection of a limit

Valid Values:
1 to 6

Default Value: 1
   r#����  `    Status                           y�-   �  `    Instrument Handle                zE Gm �  �    Limit Check Result               z� G T �  `    Channel                          {! G � �  `    Limit                              	               	            1    1    �    Queries the result of limit calculation between min and max values.

Attribute(s):
RSHMC8015_ATTR_LIMIT_PERCENT

Remote-control command(s):
CHANnel<n>:LIMit<n>:PERCent?

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     n    Queries the result of limit calculation between min and max values.

Attribute:
RSHMC8015_ATTR_LIMIT_PERCENT     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
     I    Numerical selection of a limit

Valid Values:
1 to 6

Default Value: 1
   }U#����  `    Status                           ��-   �  `    Instrument Handle                �� G� �  �    Limit Percent                    � G N �  `    Channel                          �R G � �  `    Limit                              	               	           1    1       Configures measurement limit.

Attribute(s):
RSHMC8015_ATTR_LIMIT_STATE
RSHMC8015_ATTR_LIMIT_SOURCE
RSHMC8015_ATTR_LIMIT_HIGH
RSHMC8015_ATTR_LIMIT_LOW

Remote-control command(s):
CHANnel<n>:LIMit<n>[:STATe]
CHANnel<n>:LIMit<n>:SOURce
CHANnel<n>:LIMit<n>:HIGH
CHANnel<n>:LIMit<n>:LOW
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets state of the limit.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_LIMIT_STATE     h    Sets limit's upper boundary.

Valid Values:

Default Value: 1.0

Attribute:
RSHMC8015_ATTR_LIMIT_HIGH
     I    Numerical selection of a limit

Valid Values:
1 to 6

Default Value: 1
    �    Sets source (function) of the limit.

Valid Values:
RSHMC8015_VAL_LIMIT_SOURCE_URMS   (0) - True RMS Voltage
RSHMC8015_VAL_LIMIT_SOURCE_UAVG   (1) - Average Voltage
RSHMC8015_VAL_LIMIT_SOURCE_FU     (2) - Voltage Frequency
RSHMC8015_VAL_LIMIT_SOURCE_IRMS   (3) - True RMS Current
RSHMC8015_VAL_LIMIT_SOURCE_IAVG   (4) - Average Current
RSHMC8015_VAL_LIMIT_SOURCE_FI     (5) - Current Frequency
RSHMC8015_VAL_LIMIT_SOURCE_P      (6) - Active Power
RSHMC8015_VAL_LIMIT_SOURCE_S      (7) - Apparent Power
RSHMC8015_VAL_LIMIT_SOURCE_Q      (8) - Reactive Power
RSHMC8015_VAL_LIMIT_SOURCE_PF     (9) - Power Factor Lambda
RSHMC8015_VAL_LIMIT_SOURCE_PHI   (10) - Phase Difference Phi
RSHMC8015_VAL_LIMIT_SOURCE_FPLL  (11) - PLL Source Frequency
RSHMC8015_VAL_LIMIT_SOURCE_UTHD  (12) - Total Harmonic Dist U
RSHMC8015_VAL_LIMIT_SOURCE_ITHD  (13) - Total Harmonic Dist I

Default Value: RSHMC8015_VAL_LIMIT_SOURCE_URMS  (0)

Attribute:
RSHMC8015_ATTR_LIMIT_SOURCE
     Y    Sets limit's lower boundary.

Default Value: -1.0

Attribute:
RSHMC8015_ATTR_LIMIT_LOW
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   ��#����  `    Status                           �t-   �  `    Instrument Handle                �0 GG �       State                            �� � � � `    High                             �: G � �  `    Limit                            �� G� � `    Source                           �Q �. � `    Low                              �� G D �  `    Channel                            	               On VI_TRUE Off VI_FALSE    1.0    1              �True RMS Voltage RSHMC8015_VAL_LIMIT_SOURCE_URMS Average Voltage RSHMC8015_VAL_LIMIT_SOURCE_UAVG Voltage Frequency RSHMC8015_VAL_LIMIT_SOURCE_FU True RMS Current RSHMC8015_VAL_LIMIT_SOURCE_IRMS Average Current RSHMC8015_VAL_LIMIT_SOURCE_IAVG Current Frequency RSHMC8015_VAL_LIMIT_SOURCE_FI Active Power RSHMC8015_VAL_LIMIT_SOURCE_P Apparent Power RSHMC8015_VAL_LIMIT_SOURCE_S Reactive Power RSHMC8015_VAL_LIMIT_SOURCE_Q Power Factor Lambda RSHMC8015_VAL_LIMIT_SOURCE_PF Phase Difference Phi RSHMC8015_VAL_LIMIT_SOURCE_PHI PLL Source Frequency RSHMC8015_VAL_LIMIT_SOURCE_FPLL Total Harmonic Dist U RSHMC8015_VAL_LIMIT_SOURCE_UTHD Total Harmonic Dist I RSHMC8015_VAL_LIMIT_SOURCE_ITHD    -1.0    1    �    Configures analog input settings.

Attribute(s):
RSHMC8015_ATTR_EXT_AINPUT_STATE

Remote-control command(s):
CHANnel<n>[:EXTern]:AINPut[:STATe]
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets enabled state of the analog input.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_AINPUT_STATE     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   �@#����  `    Status                           ��-   �  `    Instrument Handle                �y GO �       State                            �' G � �  `    Channel                            	               On VI_TRUE Off VI_FALSE    1    �    Configures analog output settings.

Attribute(s):
RSHMC8015_ATTR_EXT_AOUTPUT_STATE
RSHMC8015_ATTR_EXT_AOUTPUT_MODE

Remote-control command(s):
CHANnel<n>[:EXTern]:AOUTput[:STATe]
CHANnel<n>[:EXTern]:AOUTput:MODE
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets enabled state of the analog output.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_AOUTPUT_STATE    9    Sets analog output mode.

Valid Values:
RSHMC8015_VAL_AOUT_MODE_VOLTAGE   (0) - Voltage
RSHMC8015_VAL_AOUT_MODE_CURRENT   (1) - Current
RSHMC8015_VAL_AOUT_MODE_POWER     (2) - Power
RSHMC8015_VAL_AOUT_MODE_LIM1      (3) - Limit 1
RSHMC8015_VAL_AOUT_MODE_LIM2      (4) - Limit 2
RSHMC8015_VAL_AOUT_MODE_LIM3      (5) - Limit 3
RSHMC8015_VAL_AOUT_MODE_LIM4      (6) - Limit 4
RSHMC8015_VAL_AOUT_MODE_LIM5      (7) - Limit 5
RSHMC8015_VAL_AOUT_MODE_LIM6      (8) - Limit 6

Default Value: RSHMC8015_VAL_AOUT_MODE_VOLTAGE  (0)

Attribute:
RSHMC8015_ATTR_EXT_AOUTPUT_MODE
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   �W#����  `    Status                           ��-   �  `    Instrument Handle                �� G	 �       State                            �@ Gv � `    Mode                             �� G K �  `    Channel                            	               On VI_TRUE Off VI_FALSE            	  RVoltage RSHMC8015_VAL_AOUT_MODE_VOLTAGE Current RSHMC8015_VAL_AOUT_MODE_CURRENT Power RSHMC8015_VAL_AOUT_MODE_POWER Limit 1 RSHMC8015_VAL_AOUT_MODE_LIM1 Limit 2 RSHMC8015_VAL_AOUT_MODE_LIM2 Limit 3 RSHMC8015_VAL_AOUT_MODE_LIM3 Limit 4 RSHMC8015_VAL_AOUT_MODE_LIM4 Limit 5 RSHMC8015_VAL_AOUT_MODE_LIM5 Limit 6 RSHMC8015_VAL_AOUT_MODE_LIM6    1       Configures digital input settings.

Attribute(s):
RSHMC8015_ATTR_EXT_DINPUT_STATE
RSHMC8015_ATTR_EXT_DINPUT_MODE
RSHMC8015_ATTR_EXT_DINPUT_INVERT

Remote-control command(s):
CHANnel<n>[:EXTern]:DINPut[:STATe]
CHANnel<n>[:EXTern]:DINPut:MODE
CHANnel<n>[:EXTern]:DINPut:INVert
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets enabled state of the digital input.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_DINPUT_STATE    �    Sets digital input mode.

Valid Values:
RSHMC8015_VAL_DINP_MODE_FREQUENCY   (0) - Frequency
RSHMC8015_VAL_DINP_MODE_PWM         (1) - PWM
RSHMC8015_VAL_DINP_MODE_STATE       (2) - State
RSHMC8015_VAL_DINP_MODE_COMM        (3) - Communication
RSHMC8015_VAL_DINP_MODE_INT         (4) - Integrator

Default Value: RSHMC8015_VAL_DINP_MODE_FREQUENCY  (0)

Attribute:
RSHMC8015_ATTR_EXT_DINPUT_MODE
     �    Sets negation of ext. digital input.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_DINPUT_INVERT     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   ��#����  `    Status                           �-   �  `    Instrument Handle                �� Q � �       State                            �n Q0 � `    Mode                             � Q� �       Invert                           �� Q O �  `    Channel                            	               On VI_TRUE Off VI_FALSE               �Frequency RSHMC8015_VAL_DINP_MODE_FREQUENCY PWM RSHMC8015_VAL_DINP_MODE_PWM State RSHMC8015_VAL_DINP_MODE_STATE Communication RSHMC8015_VAL_DINP_MODE_COMM Integrator RSHMC8015_VAL_DINP_MODE_INT    On VI_TRUE Off VI_FALSE    1   g    Configures digital output settings.

Attribute(s):
RSHMC8015_ATTR_EXT_DOUTPUT_STATE
RSHMC8015_ATTR_EXT_DOUTPUT_MODE
RSHMC8015_ATTR_EXT_DOUTPUT_INVERT
RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE

Remote-control command(s):
CHANnel<n>[:EXTern]:DOUTput[:STATe]
CHANnel<n>[:EXTern]:DOUTput:MODE
CHANnel<n>[:EXTern]:DOUTput:INVert
CHANnel<n>[:EXTern]:DOUTput:OUTPut
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets enabled state of the digital output.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_DOUTPUT_STATE    �    Sets digital output mode.

Valid Values:
RSHMC8015_VAL_DOUT_MODE_FPLL   (0) - FPLL
RSHMC8015_VAL_DOUT_MODE_COMM   (1) - Communication
RSHMC8015_VAL_DOUT_MODE_LIM1   (2) - Limit 1
RSHMC8015_VAL_DOUT_MODE_LIM2   (3) - Limit 2
RSHMC8015_VAL_DOUT_MODE_LIM3   (4) - Limit 3
RSHMC8015_VAL_DOUT_MODE_LIM4   (5) - Limit 4
RSHMC8015_VAL_DOUT_MODE_LIM5   (6) - Limit 5
RSHMC8015_VAL_DOUT_MODE_LIM6   (7) - Limit 6

Default Value: RSHMC8015_VAL_DOUT_MODE_LIM1  (2)

Attribute:
RSHMC8015_ATTR_EXT_DOUTPUT_MODE
     �    Sets negation of ext. digital output.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_DOUTPUT_INVERT     �    Sets digital output state.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_DOUTPUT_OUTPUT_STATE     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   ��#����  `    Status                           �A-   �  `    Instrument Handle                �� G � �       State                            ή Gb � `    Mode                             Ъ � � �       Invert                           �X �4 �       Output State                     � G L �  `    Channel                            	               On VI_TRUE Off VI_FALSE             +FPLL RSHMC8015_VAL_DOUT_MODE_FPLL Communication RSHMC8015_VAL_DOUT_MODE_COMM Limit 1 RSHMC8015_VAL_DOUT_MODE_LIM1 Limit 2 RSHMC8015_VAL_DOUT_MODE_LIM2 Limit 3 RSHMC8015_VAL_DOUT_MODE_LIM3 Limit 4 RSHMC8015_VAL_DOUT_MODE_LIM4 Limit 5 RSHMC8015_VAL_DOUT_MODE_LIM5 Limit 6 RSHMC8015_VAL_DOUT_MODE_LIM6    On VI_TRUE Off VI_FALSE    On VI_TRUE Off VI_FALSE    1   �    Configures external sensor settings.

Attribute(s):
RSHMC8015_ATTR_EXT_SENSOR_STATE
RSHMC8015_ATTR_EXT_SENSOR_MODE
RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE
RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO
RSHMC8015_ATTR_EXT_SENSOR_RANGE

Remote-control command(s):
CHANnel<n>[:EXTern]:SENSor[:STATe]
CHANnel<n>[:EXTern]:SENSor:MODE
CHANnel<n>[:EXTern]:SENSor:EXTShunt[:RESistance]
CHANnel<n>[:EXTern]:SENSor:CCLamp[:RATio]
CHANnel<n>[:EXTern]:SENSor:RANGe
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Sets enabled state of the sensor.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_EXT_SENSOR_STATE     �    Sets sensor mode.

Valid Values:
RSHMC8015_VAL_SENSOR_MODE_SHUNT   (0) - Shunt
RSHMC8015_VAL_SENSOR_MODE_CLAMP   (1) - Clamp

Default Value: RSHMC8015_VAL_SENSOR_MODE_SHUNT  (0)

Attribute:
RSHMC8015_ATTR_EXT_SENSOR_MODE
     �    Sets resistance of the external shunt.

Valid Values: 1.0e-6 - 9.9e7

Default Value: 1.0

Attribute:
RSHMC8015_ATTR_EXT_SENSOR_SHUNT_RESISTANCE
     �    Sets V/A ratio of the current clamp.

Valid Values: 1.0e-4 - 9.9e1

Default Value: 1.0e-3

Attribute:
RSHMC8015_ATTR_EXT_SENSOR_CLAMP_RATIO
     �    Selects an appropriate sensor voltage range for passed peak voltage value.

Default Value: 0.0

Attribute:
RSHMC8015_ATTR_EXT_SENSOR_RANGE
     F    Numerical selection of a channel

Valid Values: 1

Default Value: 1
   �+#����  `    Status                           ި-   �  `    Instrument Handle                �d G � �       State                            � Gb � `    Mode                             �� � g � `    Resistance                       � � � � `    Ratio                            �# �d � `    Range                            � G g �  `    Channel                            	               On VI_TRUE Off VI_FALSE               LShunt RSHMC8015_VAL_SENSOR_MODE_SHUNT Clamp RSHMC8015_VAL_SENSOR_MODE_CLAMP    1.0    1.0e-3    0.0    1   �    This function sets the value of a ViInt32 attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes.  It is best to use the high-level driver functions as much as possible.  They handle order dependencies and multithread locking for you.  In addition, they perform status checking only after setting all of the attributes.  In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change.  Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.


    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    (    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Attributes 
  whose value cannot be set are dim.  Help text is shown for 
  each attribute.  Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box.  If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all the attributes of the ViInt32 type.   
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim.  If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          �#����  `    Status                           �-   �  `    Instrument Handle                �X =  �  �    Repeated Capability Name         �4 = � � �    Attribute ID                     �d � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViInt64 attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes.  It is best to use the high-level driver functions as much as possible.  They handle order dependencies and multithread locking for you.  In addition, they perform status checking only after setting all of the attributes.  In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change.  Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.


    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    (    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Attributes 
  whose value cannot be set are dim.  Help text is shown for 
  each attribute.  Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box.  If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all the attributes of the ViInt32 type.   
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim.  If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          �#����  `    Status                           	e-   �  `    Instrument Handle                
! =  �  �    Repeated Capability Name         � = � � �    Attribute ID                     - � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViReal64 attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    5    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViReal64
  type.  If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViReal64 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          �#����  `    Status                           !(-   �  `    Instrument Handle                !� =  �  �    Repeated Capability Name         #� = � � �    Attribute ID                     (� � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViString attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    4    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViString
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViString are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          1{#����  `    Status                           8�-   �  `    Instrument Handle                9� =  �  �    Repeated Capability Name         ;� = � � �    Attribute ID                     @� � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViBoolean attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    6    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViBoolean
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViBoolean are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          IK#����  `    Status                           P�-   �  `    Instrument Handle                Q� =  �  �    Repeated Capability Name         S` = � � �    Attribute ID                     X� � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViSession attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    6    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViSession
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViSession are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          a#����  `    Status                           h�-   �  `    Instrument Handle                iV =  �  �    Repeated Capability Name         k2 = � � �    Attribute ID                     pp � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        �    This function returns the repeated capability id(s) that belongs to the attribute you specify. More then one id is listed in comma separated string.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         Pass the ID of an attribute.
     ~    Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id(s) parameter.  

Default Value: 256
    |    The buffer in which the function returns the repeated capability id(s) belonging to the attribute. The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.

If the attribute applies to a repeated capability such as a trace, this parameter returns the Ids of the repeated capability on which to set the value of the attribute.
   t�#����  `    Status                           |B-   �  `    Instrument Handle                |� G L � �    Attribute ID                     }% G[ �  �    Buffer Size                      }� � L � �    Repeated Capability Id(s)          	                           0    256    	            �    This function returns the repeated capability name(s) that belongs to the attribute and single repeated capability id you may specify. More then one name is listed in comma separated string.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         Pass the ID of an attribute.
     �    If the attribute applies to a repeated capability such as a trace, this parameter defines the Id of the repeated capability on which to query repeated capability id name(s).

Default Value: ""
     �    Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id Name(s) parameter.  

Default Value: 256
     �    The buffer in which the function returns the repeated capability id name(s) belonging to the attribute. The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.
   �6#����  `    Status                           ��-   �  `    Instrument Handle                �o G  � �    Attribute ID                     �� G �  �    Repeated Capability Id           �a G� �  b    Buffer Size                      �� � L � �    Repeated Capability Id Name(s)     	                           0    ""    256    	           �    This function queries the value of a ViInt32 attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViInt32 type. 
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box.  
  Attributes with data types other than ViInt32 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViInt32 variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   ��#����  `    Status                           �w-   �  `    Instrument Handle                �3 =  �  �    Repeated Capability Name         � = � � �    Attribute ID                     �� � � �  �    Attribute Value                    	               ""                0    	           �    This function queries the value of a ViInt64 attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViInt32 type. 
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box.  
  Attributes with data types other than ViInt32 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViInt64 variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   �V#����  `    Status                           ��-   �  `    Instrument Handle                �� =  �  �    Repeated Capability Name         �k = � � �    Attribute ID                     � � � �  �    Attribute Value                    	               ""                0    	           �    This function queries the value of a ViReal64 attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViReal64
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViReal64 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViReal64 variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   ��#����  `    Status                           �0-   �  `    Instrument Handle                �� =  �  �    Repeated Capability Name         �� = � � �    Attribute ID                     �] � � �  �    Attribute Value                    	               ""                0    	          )    This function queries the value of a ViString attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid. 

You must provide a ViChar array to serve as a buffer for the value. You pass the number of bytes in the buffer as the Buffer Size parameter. If the current value of the attribute, including the terminating NUL byte, is larger than the size you indicate in the Buffer Size parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you want to call this function just to get the required buffer size, you can pass 0 for the Buffer Size and VI_NULL for the Attribute Value buffer.  

If you want the function to fill in the buffer regardless of the   number of bytes in the value, pass a negative number for the Buffer Size parameter.
    	/    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

If the current value of the attribute, including the terminating NUL byte, is larger than the size you indicate in the Buffer Size parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Help text is
  shown for each attribute.  Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViString
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViString are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Pass the number of bytes in the ViChar array you specify for the Attribute Value parameter.  

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Attribute Value buffer parameter.

Default Value: 512    &    The buffer in which the function returns the current value of the attribute.  The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you specify 0 for the Buffer Size parameter, you can pass VI_NULL for this parameter.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   ̊#����  `    Status or Required Size          ��-   �  `    Instrument Handle                �} =  �  �    Repeated Capability Name         �X = � � �    Attribute ID                     �� =� �  �    Buffer Size                      �� � L � �    Attribute Value                    	               ""                0    512    	           �    This function queries the value of a ViBoolean attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Help text is
  shown for each attribute.  Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViBoolean
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViBoolean are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViBoolean variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   �E#����  `    Status                           ��-   �  `    Instrument Handle                �~ =  �  �    Repeated Capability Name         �Y = � � �    Attribute ID                     �� � � �  �    Attribute Value                    	               ""                0    	           �    This function queries the value of a ViSession attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViSession
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViSession are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViSession variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   ��#����  `    Status                           %-   �  `    Instrument Handle                � =  �  �    Repeated Capability Name         � = � � �    Attribute ID                     	U � � �  �    Attribute Value                    	               ""                0    	            S    This function checks the validity of a value you specify for a ViInt32 attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    4    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViInt32 type. 
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          �#����  `    Status                           *-   �  `    Instrument Handle                � =  �  �    Repeated Capability Name         � = � � �    Attribute ID                     � � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        S    This function checks the validity of a value you specify for a ViInt64 attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    4    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViInt32 type. 
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                           $#����  `    Status                           '�-   �  `    Instrument Handle                (] =  �  �    Repeated Capability Name         *9 = � � �    Attribute ID                     /u � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        T    This function checks the validity of a value you specify for a ViReal64 attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    5    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViReal64
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViReal64 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          3�#����  `    Status                           ;-   �  `    Instrument Handle                ;� =  �  �    Repeated Capability Name         =� = � � �    Attribute ID                     B� � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        T    This function checks the validity of a value you specify for a ViString attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    5    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViString
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViString are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          G#����  `    Status                           N�-   �  `    Instrument Handle                ON =  �  �    Repeated Capability Name         Q* = � � �    Attribute ID                     Vg � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        U    This function checks the validity of a value you specify for a ViBoolean attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    7    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViBoolean
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViBoolean are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          Z�#����  `    Status                           b-   �  `    Instrument Handle                b� =  �  �    Repeated Capability Name         d� = � � �    Attribute ID                     i� � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        U    This function checks the validity of a value you specify for a ViSession attribute.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    7    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViSession
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViSession are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    (    Pass the value which you want to verify as a valid value for the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          n#����  `    Status                           u�-   �  `    Instrument Handle                vD =  �  �    Repeated Capability Name         x  = � � �    Attribute ID                     }_ � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       X    This function resets the instrument to a known state and sends initialization commands to the instrument. The initialization commands set instrument settings such as Headers Off, Short Command form, and Data Transfer Binary to the state necessary for the operation of the instrument driver.

Attribute(s):
-

Remote-control command(s):
*RST

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   ��#����  `    Status                           �-   �  `    Instrument Handle                  	               �    This function runs the instrument's self test routine and returns the test result(s). 

Attribute(s):
no attribute

Remote-control command(s):
*TST?
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    This control contains the value returned from the instrument self test.  Zero means success.  For any other code, see the device's operator's manual.
     �    This control contains the string returned from the self test. See the device's operation manual for an explanation of the string's contents.

Notes:

(1) The array must contain at least 256 elements ViChar[256].   ��#����  `    Status                           �Y-   �  `    Instrument Handle                � G Q �  `    Self Test Result                 �� G � � ,    Self-Test Message                  	               	           	            �    This function returns the revision numbers of the instrument driver and instrument firmware.

Attribute(s):

Remote-control command(s):



    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Returns the instrument driver software revision numbers in the form of a string.

You must pass a ViChar array with at least 256 bytes.     �    Returns the instrument firmware revision numbers in the form of a string.

You must pass a ViChar array with at least 256 bytes.
   �##����  `    Status                           ��-   �  `    Instrument Handle                �\ 9  �  �    Instrument Driver Revision       �� 9Y �  �    Firmware Revision                  	               	            	            �    Disables or enables the beeper tone.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED

Remote-control command(s):
SYSTem:BEEPer:STATe    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Disables or enables the beeper tone.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute:
RSHMC8015_ATTR_SYSTEM_BEEPER_ENABLED   �#����  `    Status                           ��-   �  `    Instrument Handle                �? G �       Beeper State                       	               On VI_TRUE Off VI_FALSE    �    When sending a command, the device emits a beep.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_START_BEEP

Remote-control command(s):
SYSTem:BEEPer[:IMMediate]

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   �[#����  `    Status                           ��-   �  `    Instrument Handle                  	               �    Sets the name of the device (capped at 20 characters).

Attribute(s):
RSHMC8015_ATTR_SYSTEM_NAME

Remote-control command(s):
SYSTem:NAME    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     P    The name of system.

Default Value: ""

Attribute:
RSHMC8015_ATTR_SYSTEM_NAME
   ��#����  `    Status                           �-   �  `    Instrument Handle                �� G � �  �    Name                               	               ""    �    Local operating mode (front panel control).

Attribute(s):
RSHMC8015_ATTR_SYSTEM_LOCAL

Remote-control command(s):
SYSTem:LOCal

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   �q#����  `    Status                           ��-   �  `    Instrument Handle                  	               �    Remote control (front panel control locked).

Attribute(s):
RSHMC8015_ATTR_SYSTEM_REMOTE

Remote-control command(s):
SYSTem:REMote

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   Ȳ#����  `    Status                           �/-   �  `    Instrument Handle                  	               �    The front panel control is locked; with the SystemLocal method the front panel control will be activated.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_RWLOCK

Remote-control command(s):
SYSTem:RWLock

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   �0#����  `    Status                           ٭-   �  `    Instrument Handle                  	               �    This function queries the number of the SCPI version, which is relevant for the instrument.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_VERSION

Remote-control command(s):
SYSTem:VERSion?    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.
          
The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state when the
          measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
BFFA4001  The Active Marker is not a span marker.
BFFA4002  The Active Marker is not a band marker.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code  Types    
-------------------------------------------------
3FFA2000 to 3FFA3FFF     IviSpecAn    Warnings
3FFA0000 to 3FFA1FFF     IVI          Warnings
3FFF0000 to 3FFFFFFF     VISA         Warnings
3FFC0000 to 3FFCFFFF     VXIPnP       Driver Warnings
          
BFFA2000 to BFFA3FFF     IviSpecAn    Errors
BFFA0000 to BFFA1FFF     IVI          Errors
BFFF0000 to BFFFFFFF     VISA         Errors
BFFC0000 to BFFCFFFF     VXIPnP       Driver Errors     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     P    Returns the number of the SCPI version, which is relevant for the instrument.
   ۡ#����  `    Status                           �P-   �  `    Instrument Handle                � G | �  `    Length                           �u GE �  `    System Version                     	               255    	           �    This function queries the device model.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_DEVICE

Remote-control command(s):
SYSTem:DEVice?    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.
          
The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state when the
          measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
BFFA4001  The Active Marker is not a span marker.
BFFA4002  The Active Marker is not a band marker.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code  Types    
-------------------------------------------------
3FFA2000 to 3FFA3FFF     IviSpecAn    Warnings
3FFA0000 to 3FFA1FFF     IVI          Warnings
3FFF0000 to 3FFFFFFF     VISA         Warnings
3FFC0000 to 3FFCFFFF     VXIPnP       Driver Warnings
          
BFFA2000 to BFFA3FFF     IviSpecAn    Errors
BFFA0000 to BFFA1FFF     IVI          Errors
BFFF0000 to BFFFFFFF     VISA         Errors
BFFC0000 to BFFCFFFF     VXIPnP       Driver Errors     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     #    Returns the system device model.
   �L#����  `    Status                           ��-   �  `    Instrument Handle                � G | �  `    Length                           �  GE �  `    System Device                      	               255    	            �    Turns the device off. The device can't be enabled remotely after this command.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_SHUTDOWN

Remote-control command(s):
SYSTem:SHUTdown

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   ��#����  `    Status                           �s-   �  `    Instrument Handle                  	               �    This function queries the software version.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_SOFTWARE

Remote-control command(s):
SYSTem:SOFTware?    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.
          
The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state when the
          measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
BFFA4001  The Active Marker is not a span marker.
BFFA4002  The Active Marker is not a band marker.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code  Types    
-------------------------------------------------
3FFA2000 to 3FFA3FFF     IviSpecAn    Warnings
3FFA0000 to 3FFA1FFF     IVI          Warnings
3FFF0000 to 3FFFFFFF     VISA         Warnings
3FFC0000 to 3FFCFFFF     VXIPnP       Driver Warnings
          
BFFA2000 to BFFA3FFF     IviSpecAn    Errors
BFFA0000 to BFFA1FFF     IVI          Errors
BFFF0000 to BFFFFFFF     VISA         Errors
BFFC0000 to BFFCFFFF     VXIPnP       Driver Errors     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     '    Returns the system software version.
   �9#����  `    Status                           �-   �  `    Instrument Handle                � G | �  `    Length                            GE �  `    System Software                    	               255    	            �    This function queries the hardware version.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_HARDWARE

Remote-control command(s):
SYSTem:HARDware?    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.
          
The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state when the
          measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
BFFA4001  The Active Marker is not a span marker.
BFFA4002  The Active Marker is not a band marker.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code  Types    
-------------------------------------------------
3FFA2000 to 3FFA3FFF     IviSpecAn    Warnings
3FFA0000 to 3FFA1FFF     IVI          Warnings
3FFF0000 to 3FFFFFFF     VISA         Warnings
3FFC0000 to 3FFCFFFF     VXIPnP       Driver Warnings
          
BFFA2000 to BFFA3FFF     IviSpecAn    Errors
BFFA0000 to BFFA1FFF     IVI          Errors
BFFF0000 to BFFFFFFF     VISA         Errors
BFFC0000 to BFFCFFFF     VXIPnP       Driver Errors     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     '    Returns the system hardware version.
   �#����  `    Status                           r-   �  `    Instrument Handle                - G | �  `    Length                           � GE �  `    System Hardware                    	               255    	            �    This function queries the serial number.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_SERIAL_NUMBER

Remote-control command(s):
SYStem:SNUMber?    �    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.
          
The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state when the
          measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
BFFA4001  The Active Marker is not a span marker.
BFFA4002  The Active Marker is not a band marker.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code  Types    
-------------------------------------------------
3FFA2000 to 3FFA3FFF     IviSpecAn    Warnings
3FFA0000 to 3FFA1FFF     IVI          Warnings
3FFF0000 to 3FFFFFFF     VISA         Warnings
3FFC0000 to 3FFCFFFF     VXIPnP       Driver Warnings
          
BFFA2000 to BFFA3FFF     IviSpecAn    Errors
BFFA0000 to BFFA1FFF     IVI          Errors
BFFF0000 to BFFFFFFF     VISA         Errors
BFFC0000 to BFFCFFFF     VXIPnP       Driver Errors     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     $    Returns the system serial number.
   N#����  `    Status                           �-   �  `    Instrument Handle                � G | �  `    Length                           " GE �  `    System Serial Number               	               255    	            �    This function reads an error code and a message from the instrument's error queue.

Attribute(s):
RSHMC8015_ATTR_SYSTEM_ERROR

Remote-control command(s):
SYSTem:ERRor?    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     B    Returns the error code read from the instrument's error queue.

     �    Returns the error message string read from the instrument's error message queue.

You must pass a ViChar array with at least 256 bytes.
   �#����  `    Status                           !s-   �  `    Instrument Handle                "/ 9  �  �    Error Code                       "y 9 � � ,    Error Message                      	               	           	            �    This function converts a status code returned by an instrument driver function into a user-readable string. 

Attribute(s):

Remote-control command(s):
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
        The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     z    Pass the Status parameter that is returned from any of the instrument driver functions.

Default Value:  0  (VI_SUCCESS)     �    Returns the user-readable message string that corresponds to the status code you specify.

You must pass a ViChar array with at least 256 bytes.
   $�#����  `    Status                           ,&-   �  `    Instrument Handle                -J 9  �  h    Error Code                       -� 9 � � �    Error Message                      	           VI_NULL    0    	           k    This function sets the Enable of selected registers.

Note:

(1) For detailed description of Status Reporting System see also operating manual.

Attribute(s):
-

Remote-control command(s):
STATus:OPERation:ENABle
STATus:OPERation:PTRansition
STATus:OPERation:NTRansition
STATus:QUEStionable:ENABle
STATus:QUEStionable:PTRansition
STATus:QUEStionable:NTRansition    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
        The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL     �    This control selects the registers that will be configured. 

Valid Values:
RSHMC8015_VAL_STAT_REG_QUESTIONABLE  (1) - Questionable
RSHMC8015_VAL_STAT_REG_OPERATION     (2) - Operation


Default Value: RSHMC8015_VAL_STAT_REG_QUESTIONABLE (1)     #    Sets content of enable register.
     (    Sets content of PTransition register.
     (    Sets content of NTransition register.
   0�����  �    Status                           8S   �  �    Instrument Handle                9v G R � `    Register Operation               :q � P �  `    Enable                           :� � � �  `    PTransition                      :� �� �  `    NTransition                        	                          \Questionable RSHMC8015_VAL_STAT_REG_QUESTIONABLE Operation RSHMC8015_VAL_STAT_REG_OPERATION               �    This function queries the status reporting system.

Note:

For detailed description of Status Reporting System see also operating manual.

Attribute(s):
-

Remote-control command(s):
STATus:QUEStionable:CONDition?
STATus:QUEStionable:ENABle?
STATus:QUEStionable[:EVENt]?
STATus:QUEStionable:PTRansition?
STATus:QUEStionable:NTRansition?
STATus:OPERation:CONDition?
STATus:OPERation:ENABle?
STATus:OPERation[:EVENt]?
STATus:OPERation:PTRansition?
STATus:OPERation:NTRansition?    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
        The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL         Returns content of selected register.

Note:

For detailed description of Status Reporting System see also operating manual.
     �    This control selects the registers that will be configured. 

Valid Values:
RSHMC8015_VAL_STAT_REG_QUESTIONABLE  (1) - Questionable
RSHMC8015_VAL_STAT_REG_OPERATION     (2) - Operation

Default Value: RSHMC8015_VAL_STAT_REG_QUESTIONABLE (1)    �    This control selects the registers that will be configured. 

Valid Values:
RSHMC8015_VAL_STAT_REG_QUERY_COND          (0) - Condition
RSHMC8015_VAL_STAT_REG_QUERY_EVENT         (1) - Event
RSHMC8015_VAL_STAT_REG_QUERY_ENABLE        (2) - Enable
RSHMC8015_VAL_STAT_REG_QUERY_PTRANSITION   (3) - PTransition
RSHMC8015_VAL_STAT_REG_QUERY_NTRANSITION   (4) - NTransition

Default Value: RSHMC8015_VAL_STAT_REG_QUERY_COND (0)   >�����  �    Status                           F#   �  �    Instrument Handle                GF �� �  `    Register Value                   G� G W � `    Register Operation               H� G � � `    Status Register Query              	               	                       \Questionable RSHMC8015_VAL_STAT_REG_QUESTIONABLE Operation RSHMC8015_VAL_STAT_REG_OPERATION               �Condition RSHMC8015_VAL_STAT_REG_QUERY_COND Event RSHMC8015_VAL_STAT_REG_QUERY_EVENT Enable RSHMC8015_VAL_STAT_REG_QUERY_ENABLE PTransition RSHMC8015_VAL_STAT_REG_QUERY_PTRANSITION NTransition RSHMC8015_VAL_STAT_REG_QUERY_NTRANSITION    �    Clears all bits in the Questionable Data enable register and the Standard Operation enable register.

Attribute(s):
RSHMC8015_ATTR_STATUS_PRESET

Remote-control command(s):
STATus:PRESet    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   M�#����  `    Status                           U@-   �  `    Instrument Handle                  	              �    This function retrieves and then clears the error information for the session or the current execution thread. One exception exists: If the BufferSize parameter is 0, the function does not clear the error information. By passing 0 for the buffer size, the caller can ascertain the buffer size required to get the entire error description string and then call the function again with a sufficiently large buffer.

If the user specifies a valid session for the InstrumentHandle parameter, Get Error retrieves and then clears the error information for the session. If the user passes VI_NULL for the InstrumentHandle parameter, this function retrieves and then clears the error information for the current execution thread.  If the InstrumentHandle parameter is an invalid session, the function does nothing and returns an error. Normally, the error information describes the first error that occurred since the user last called rshmc8015_GetError or rshmc8015_ClearError.
    	/    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

If the current value of the attribute, including the terminating NUL byte, is larger than the size you indicate in the Buffer Size parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Returns the error code for the session or execution thread.

If you pass 0 for the Buffer Size, you can pass VI_NULL for this parameter.
    �    Pass the number of bytes in the ViChar array you specify for the Description parameter.

If the error description, including the terminating NUL byte, contains more bytes than you indicate in this parameter, the function copies BufferSize - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Description buffer parameter.

Default Value:  None    �    Returns the error description for the session or execution thread. If there is no description, the function returns an empty string.

The buffer must contain at least as many elements as the value you specify with the Buffer Size parameter. If the error description, including the terminating NUL byte, contains more bytes than you indicate with the Buffer Size parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value. For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass 0 for the Buffer Size, you can pass VI_NULL for this parameter.
   ZJ#����  `    Status or Required Size          c�-   �  `    Instrument Handle                d= 9  �  �    Code                             d� 9� �  �    BufferSize                       g� � Q � �    Description                        	               	               	           `    This function clears the error code and error description for the session. If the user specifies a valid session for the InstrumentHandle parameter, this function clears the error information for the session. If the user passes VI_NULL for the Vi parameter, this function clears the error information for the current execution thread. If the Vi parameter is an invalid session, the function does nothing and returns an error.
The function clears the error code by setting it to VI_SUCCESS.  If the error description string is non-NULL, the function de-allocates the error description string and sets the address to VI_NULL.

Maintaining the error information separately for each thread is useful if the user does not have a session handle to pass to the rshmc8015_GetError function, which occurs when a call to rshmc8015_init or rshmc8015_InitWithOptions fails.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   oC#����  `    Status                           v�-   �  `    Instrument Handle                  	               �    This function writes a user-specified string to the instrument.

Note:

This function bypasses attribute state caching. Therefore, when you call this function, the cached values for all attributes will be invalidated.
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     2    Pass the string to be written to the instrument.   x�#����  `    Status                           �W-   �  `    Instrument Handle                � 9 � �  �    Write Buffer                       	               ""    /    This function reads data from the instrument.    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Pass the maximum number of bytes to read from the instruments.  

Valid Range:  0 to the number of elements in the Read Buffer.

Default Value:  0

     c    After this function executes, this parameter contains the data that was read from the instrument.     ^    Returns the number of bytes actually read from the instrument and stored in the Read Buffer.   �9#����  `    Status                           ��-   �  `    Instrument Handle                �r 9  �  �    Number of Bytes To Read          � 9 � �  �    Read Buffer                      �{ 9x �  �    Num Bytes Read                     	               0    	            	            .    This function queries the ViBoolean value.

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViBoolean value
   �M#����  `    Status                           ��-   �  `    Instrument Handle                �� I  �      Command                          �� �q �  �    Value                              	               ""    	            ,    This function queries the ViInt32 value.

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViInt32 value
   �#����  `    Status                           ��-   �  `    Instrument Handle                �T I  �      Command                          �� �q �  �    Value                              	               ""    	            -    This function queries the ViReal64 value.

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViReal64 value
   ��#����  `    Status                           �e-   �  `    Instrument Handle                �! I  �      Command                          �f �q �  �    Value                              	               ""    	           -    This function queries the ViString value.

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""    �    Pass the number of bytes in the ViChar array you specify for the  Value parameter.  

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Value buffer parameter.

Default Value: 512         Returns the ViBoolean value
   ��#����  `    Status                           �3-   �  `    Instrument Handle                �� I  �      Command                          �4 �  �  �    Buffer Size                      � �q �  �    Value                              	               ""    512    	            v    The DATA? query responses screenshot data in binary format

Attribute(s):
-

Remote-control command(s):
HCOPy:DATA?
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     w    Defines destination file to which the data transfer from instrument to control computer applies.

Default Value:  ""
   ��#����  `    Status                           �j-   �  `    Instrument Handle                �& G � �  �    Destination                        	               ""    �    Configures the data format of the screenshot.

Attribute(s):
RSHMC8015_ATTR_HCOPY_IMAGE_FORMAT

Remote-control command(s):
HCOPy:FORMat
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
        Selects the data format of the screenshot.

Valid Values:
RSHMC8015_VAL_IMAGE_FORMAT_BMP (0) - BMP
RSHMC8015_VAL_IMAGE_FORMAT_PNG (1) - PNG

Default Value: RSHMC8015_VAL_IMAGE_FORMAT_BMP  (0)

Note(s):

(1) BMP: Selects BMP image format

(2) PNG: Selects PNG image format   ��#����  `    Status                           �i-   �  `    Instrument Handle                �% G � � `    Image Format                       	                          FBMP RSHMC8015_VAL_IMAGE_FORMAT_BMP PNG RSHMC8015_VAL_IMAGE_FORMAT_PNG    �    Returns the width and height of the screenshot.

Attribute(s):
RSHMC8015_ATTR_HCOPY_IMAGE_WIDTH
RSHMC8015_ATTR_HCOPY_IMAGE_HEIGHT

Remote-control command(s):
HCOPy:SIZE:X?
HCOPy:SIZE:Y?
    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     '    Returns the width of the screenshot.
     (    Returns the height of the screenshot.
   �#����  `    Status                           ԃ-   �  `    Instrument Handle                �? G` �  `    Image Width                      �n �` �  `    Image Height                       	               	            	           �    This function performs the following operations:

- Closes the instrument I/O session.

- Destroys the instrument driver session and all of its attributes.

- Deallocates any memory resources the driver uses.

Notes:

(1) You must unlock the session before calling rshmc8015close.

(2) After calling rshmc8015close, you cannot use the instrument driver again until you call rshmc8015_init or rshmc8015_InitWithOptions.

    u    Returns the status code of this operation.  The status code  either indicates success or describes an error or warning condition.  You examine the status code from each call to an instrument driver function to determine if an error occurred.

To obtain a text description of the status code, call the rshmc8015_error_message function.  To obtain additional information about the error condition, call the rshmc8015_GetError function.  To clear the error information from the driver, call the rshmc8015_ClearError function.

The general meaning of the status code is as follows:

Value                  Meaning
-------------------------------
0                      Success
Positive Values        Warnings
Negative Values        Errors

This driver defines the following status codes:
          
Status    Description
-------------------------------------------------
WARNINGS:
3FFA2001  The instrument was in an uncalibrated state
          when the measurement was taken.
3FFA2002  The measurement taken was over the instrument's
          range.
  
ERRORS:
BFFA2001  The Active Marker is not enabled.
BFFA2002  The Active Marker is not a delta marker.
BFFA2003  The maximum waiting time for this operation was
          exceeded.
          
This instrument driver also returns errors and warnings defined by other sources.  The following table defines the ranges of additional status codes that this driver can return.  The table lists the different include files that contain the defined constants for the particular status codes:
          
Numeric Range (in Hex)   Status Code Types    
-------------------------------------------------
3FFA0000 to 3FFA1FFF     IVI    Warnings
3FFF0000 to 3FFFFFFF     VISA   Warnings
3FFC0000 to 3FFCFFFF     VXIPnP Driver Warnings
          
BFFA0000 to BFFA1FFF     IVI    Errors
BFFF0000 to BFFFFFFF     VISA   Errors
BFFC0000 to BFFCFFFF     VXIPnP Driver Errors
     �    The ViSession handle that you obtain from the rshmc8015_init or rshmc8015_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   �H#����  `    Status                           ��-   �  `    Instrument Handle                  	            ����         �  !f             K.        init                                                                                                                                    ����         "�  A�             K.        InitWithOptions                                                                                                                         ����         C�  M�             K.        ConfigureAcquisitionMode                                                                                                                ����         N�  [�             K.        ConfigureACAcquisition                                                                                                                  ����         ^*  k�             K.        ConfigureVoltageAcquisition                                                                                                             ����         m�  z�             K.        ConfigureCurrentAcquisition                                                                                                             ����         }  ��             K.        QueryOCP                                                                                                                                ����         ��  ��             K.        ResetOCP                                                                                                                                ����         ��  ��             K.        ShowMessageBox                                                                                                                          ����         ��  �d             K.        ClearMessageBox                                                                                                                         ����         ��  �&             K.        ConfigureViewMode                                                                                                                       ����         ��  ��             K.        ConfigureNormalViewPageSize                                                                                                             ����         �  �C             K.        ConfigureNormalViewActivePage                                                                                                           ����         ��  �H             K.        ConfigureNormalViewFunction                                                                                                             ����         �0  �X             K.        ConfigureHarmonicsView                                                                                                                  ����         �  ��             K.        QueryData                                                                                                                               ����         �� 2             K.        WriteFunctionList                                                                                                                       ����        	! �             K.        QueryFunctionList                                                                                                                       ����        	 "v             K.        QueryFunctionListLength                                                                                                                 ����        #k /@             K.        ConfigureIntegrator                                                                                                                     ����        1: <             K.        IntegratorOperation                                                                                                                     ����        =] H_             K.        ConfigureIntegratorStartTime                                                                                                            ����        J: T]             K.        ConfigureLoggingFile                                                                                                                    ����        U� bx             K.        ConfigureLogging                                                                                                                        ����        d� o�             K.        ConfigureLoggingStartTime                                                                                                               ����        qm {r             K.        QueryLimitCheckResult                                                                                                                   ����        |� ��             K.        QueryLimitPercent                                                                                                                       ����        �� �              K.        ConfigureMeasurementLimit                                                                                                               ����        �� �u             K.        ConfigureExtAnalogIn                                                                                                                    ����        �y ��             K.        ConfigureExtAnalogOut                                                                                                                   ����        �i ��             K.        ConfigureExtDigitalIn                                                                                                                   ����        �U �O             K.        ConfigureExtDigitalOut                                                                                                                  ����        �b �             K.        ConfigureExtSensor                                                                                                                      ����        �Q �             K.        SetAttributeViInt32                                                                                                                     ����        � H             K.        SetAttributeViInt64                                                                                                                     ����        � +             K.        SetAttributeViReal64                                                                                                                    ����        ,� B�             K.        SetAttributeViString                                                                                                                    ����        D� Z�             K.        SetAttributeViBoolean                                                                                                                   ����        \T r�             K.        SetAttributeViSession                                                                                                                   ����        t& /             K.        GetAttributeRepeatedCapabilityIds                                                                                                       ����        �m ��             K.        GetAttributeRepeatedCapabilityIdNames                                                                                                   ����        �D �c             K.        GetAttributeViInt32                                                                                                                     ����        �� ��             K.        GetAttributeViInt64                                                                                                                     ����        �� �             K.        GetAttributeViReal64                                                                                                                    ����        �Y �             K.        GetAttributeViString                                                                                                                    ����        � ��             K.        GetAttributeViBoolean                                                                                                                   ����        ��              K.        GetAttributeViSession                                                                                                                   ����        R .             K.        CheckAttributeViInt32                                                                                                                   ����        � 1�             K.        CheckAttributeViInt64                                                                                                                   ����        3@ E             K.        CheckAttributeViReal64                                                                                                                  ����        F� X�             K.        CheckAttributeViString                                                                                                                  ����        Z2 l             K.        CheckAttributeViBoolean                                                                                                                 ����        m� �             K.        CheckAttributeViSession                                                                                                                 ����        �* ��             K.        reset                                                                                                                                   ����        �= ��             K.        self_test                                                                                                                               ����        �� �x             K.        revision_query                                                                                                                          ����        �t ��             K.        BeeperState                                                                                                                             ����        �� ��             K.        StartBeep                                                                                                                               ����        � �1             K.        SystemName                                                                                                                              ����        �� Ǫ             K.        SystemLocal                                                                                                                             ����        �$ ��             K.        SystemRemote                                                                                                                            ����        �e �i             K.        SystemRWLock                                                                                                                            ����        �� ��             K.        SystemVersion                                                                                                                           ����        �� �K             K.        SystemDevice                                                                                                                            ����        �B �/             K.        SystemShutdown                                                                                                                          ����        �� <             K.        SystemSoftware                                                                                                                          ����        3 �             K.        SystemHardware                                                                                                                          ����        � N             K.        SystemSerialNumber                                                                                                                      ����        E #             K.        error_query                                                                                                                             ����        $ .g             K.        error_message                                                                                                                           ����        /c :�             K.        SetStatusRegister                                                                                                                       ����        <� Jv             K.        GetStatusRegister                                                                                                                       ����        L� U�             K.        StatusPreset                                                                                                                            ����        Vv j�             K.        GetError                                                                                                                                ����        k� w|             K.        ClearError                                                                                                                              ����        w� �M             K.        WriteInstrData                                                                                                                          ����        � ��             K.        ReadInstrData                                                                                                                           ����        � ��             K.        QueryViBoolean                                                                                                                          ����        �� ��             K.        QueryViInt32                                                                                                                            ����        �� ��             K.        QueryViReal64                                                                                                                           ����        �� �=             K.        QueryViString                                                                                                                           ����        �o ��             K.        ImageSnapshot                                                                                                                           ����        �Z �>             K.        ConfigureImageFormat                                                                                                                    ����        �B ՞             K.        QueryImageSize                                                                                                                          ����        ֚ ��             K.        close                                                                                                                                         "                                                                                     �Initialize                                                                           �Initialize With Options                                                             �Acquisition                                                                          �Configure Acquisition Mode                                                           �Configure AC Acquisition                                                             �Configure Voltage Acquisition                                                        �Configure Current Acquisition                                                        �Query OCP                                                                            �Reset OCP                                                                           �Display                                                                              �Show Message Box                                                                     �Clear Message Box                                                                   �View                                                                                 �Configure View Mode                                                                  �Configure Normal View Page Size                                                      �Configure Normal View Active Page                                                    �Configure Normal View Function                                                       �Configure Harmonics View                                                            Measurement                                                                          �Query Data                                                                           �Write Function List                                                                  �Query Function List                                                                  �Query Function List Length                                                          IIntegrator                                                                           �Configure Integrator                                                                 �Integrator Operation                                                                 �Configure Integrator Start Time                                                     tLogging                                                                             �File                                                                                 �Configure Logging File                                                               �Configure Logging                                                                    �Configure Logging Start Time                                                        Limit                                                                                �Query Limit Check Result                                                             �Query Limit Percent                                                                  �Configure Measurement Limit                                                         3External                                                                             �Configure External Analog Input                                                      �Configure External Analog Output                                                     �Configure External Digital Input                                                     �Configure External Digital Output                                                    �Configure External Sensor                                                           iUtility Functions                                                                   �Set/Get/Check Attribute                                                             &Set Attribute                                                                        �Set Attribute ViInt32                                                                �Set Attribute ViInt64                                                                �Set Attribute ViReal64                                                               �Set Attribute ViString                                                               �Set Attribute ViBoolean                                                              �Set Attribute ViSession                                                             �Repeated Capability                                                                  �Get Attribute Repeated Capability Id(s)                                              �Get Attribute Repeated Capability Id Name(s)                                        Get Attribute                                                                        �Get Attribute ViInt32                                                                �Get Attribute ViInt64                                                                �Get Attribute ViReal64                                                               �Get Attribute ViString                                                               �Get Attribute ViBoolean                                                              �Get Attribute ViSession                                                             �Check Attribute                                                                      �Check Attribute ViInt32                                                              �Check Attribute ViInt64                                                              �Check Attribute ViReal64                                                             �Check Attribute ViString                                                             �Check Attribute ViBoolean                                                            �Check Attribute ViSession                                                            �Reset                                                                                �Self-Test                                                                            �Revision Query                                                                       �Beeper State                                                                         �Start Beep                                                                           �System Name                                                                          �System Local                                                                         �System Remote                                                                        �System RW Lock                                                                       �System Version                                                                       �System Device                                                                        �System Shutdown                                                                      �System Software                                                                      �System Hardware                                                                      �System Serial Number                                                                 �Error-Query                                                                          �Error Message                                                                        �Set Status Register                                                                  �Get Status Register                                                                  �Status Preset                                                                       1Error Info                                                                           �Get Error                                                                            �Clear Error                                                                         �Instrument I/O                                                                       �Write Instrument Data                                                                �Read Instrument Data                                                                 �Query ViBoolean                                                                      �Query ViInt32                                                                        �Query ViReal64                                                                       �Query ViString                                                                      �Hard Copy                                                                            �Image Snapshot                                                                       �Configure Image Format                                                               �Query Image Size                                                                     �Close                                                                           