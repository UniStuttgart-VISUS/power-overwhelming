/******************************************************************************************************

Rohde&Schwarz Instrument Driver Core Include File (Non-exported)

*******************************************************************************************************/
#ifndef __RSCORE_HEADER
#define __RSCORE_HEADER

#include <visatype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/******************************************************************************************************
---- Useful constants --------------------------------------------------------------------------------*
******************************************************************************************************/

// Buffer sizes
#define RS_MAX_MESSAGE_LEN                      255
#define RS_MAX_SHORT_MESSAGE_BUF_SIZE           64 // Buffer for small messages
#define RS_REPCAP_BUF_SIZE                      128 // Buffer for repeated capability strings
#define RS_MAX_MESSAGE_BUF_SIZE                 4096 // The biggest buffer for messages on stack. Anything bigger is allocated on Heap

// NAN constants
#define RS_VAL_NAN_VI_REAL64        9.91e+37
#define RS_VAL_NAN_VI_INT32         0x80000000 // NAN for ViInt32 numbers
#define RS_VAL_NAN_VI_INT64			0x8000000000000000 // NAN for ViInt64 numbers
#define RS_VAL_INFINITY				1E300 // Infinity value for ViReal64 numbers
#define RS_VAL_MAX_REAL64			1E299 // Max value for ViReal64 numbers
#define RS_VAL_MIN_REAL64			-1E299 // Min value for ViReal64 numbers
/******************************************************************************************************
---- Constants for the Rs_TrimString function --------------------------------------------------------*
******************************************************************************************************/
#define RS_VAL_TRIM_WHITESPACES_AND_ALL_QUOTES          0 // Remove white chars and all quotes
#define RS_VAL_TRIM_WHITESPACES_AND_SINGLE_QUOTES       1 // Remove white chars and single quotes
#define RS_VAL_TRIM_WHITESPACES_AND_DOUBLE_QUOTES       2 // Remove white chars and double quotes
#define RS_VAL_TRIM_WHITESPACES                         3 // Remove white chars only

/******************************************************************************************************
---- Constants for OPC Wait Mode ---------------------------------------------------------------------*
******************************************************************************************************/
#define RS_VAL_OPCWAIT_STBPOLLING           0
#define RS_VAL_OPCWAIT_STBPOLLINGSLOW       1
#define RS_VAL_OPCWAIT_STBPOLLINGSUPERSLOW  2
#define RS_VAL_OPCWAIT_SERVICEREQUEST       3
#define RS_VAL_OPCWAIT_OPCQUERY             4

/******************************************************************************************************
---- Constants for the Option Parsing mode -----------------------------------------------------------*
******************************************************************************************************/
#define RS_VAL_OPTIONS_PARSING_KEEP_ORIGINAL    0 // No parsing, just trim white spaces and remove duplicates
#define RS_VAL_OPTIONS_PARSING_KEEP_BEFORE_DASH 1 // If the option element contains dashes, keep the part before the dash: "FSW-K30" -> "FSW"
#define RS_VAL_OPTIONS_PARSING_KEEP_AFTER_DASH  2 // If the option element contains dashes, keep the part after the dash: "FSW-K30" -> "K30"
#define RS_VAL_OPTIONS_PARSING_AUTO             3 // If the option element contains dashes, the function automatically detects which part contains Kxx or Bxx part

/******************************************************************************************************
---- Constants for the Binary Float and Integer Numbers Format ---------------------------------------*
******************************************************************************************************/
#define RS_VAL_BIN_FLOAT_FORMAT_SINGLE_4BYTES           0 // 4 bytes/number (FORMAT REAL,32)
#define RS_VAL_BIN_FLOAT_FORMAT_SINGLE_4BYTES_SWAPPED   1 // 4 bytes/number (FORMAT REAL,32) swapped endianness
#define RS_VAL_BIN_FLOAT_FORMAT_DOUBLE_8BYTES           2 // 8 bytes/number (FORMAT REAL,64 or FORMAT REAL)
#define RS_VAL_BIN_FLOAT_FORMAT_DOUBLE_8BYTES_SWAPPED   3 // 8 bytes/number (FORMAT REAL,64 or FORMAT REAL) swapped endianness

#define RS_VAL_BIN_INTEGER_FORMAT_INT32_4BYTES          0 // 4 bytes/number (FORMAT INT,32)
#define RS_VAL_BIN_INTEGER_FORMAT_INT32_4BYTES_SWAPPED  1 // 4 bytes/number (FORMAT INT,32) swapped endianness
#define RS_VAL_BIN_INTEGER_FORMAT_INT16_2BYTES          2 // 2 bytes/number (FORMAT INT,16)
#define RS_VAL_BIN_INTEGER_FORMAT_INT16_2BYTES_SWAPPED  3 // 2 bytes/number (FORMAT INT,16) swapped endianness

/******************************************************************************************************
---- Constants for the Rs_ReadToFile function --------------------------------------------------------*
******************************************************************************************************/
#define RS_VAL_TRUNCATE                         1
#define RS_VAL_APPEND                           2

/******************************************************************************************************
---- Error constants ---------------------------------------------------------------------------------*
******************************************************************************************************/
#define VI_WARN_NSUP_ID_QUERY     (          0x3FFC0101L)
#define VI_WARN_NSUP_RESET        (          0x3FFC0102L)
#define VI_WARN_NSUP_SELF_TEST    (          0x3FFC0103L)
#define VI_WARN_NSUP_ERROR_QUERY  (          0x3FFC0104L)
#define VI_WARN_NSUP_REV_QUERY    (          0x3FFC0105L)

#define VI_ERROR_PARAMETER1       (_VI_ERROR+0x3FFC0001L)
#define VI_ERROR_PARAMETER2       (_VI_ERROR+0x3FFC0002L)
#define VI_ERROR_PARAMETER3       (_VI_ERROR+0x3FFC0003L)
#define VI_ERROR_PARAMETER4       (_VI_ERROR+0x3FFC0004L)
#define VI_ERROR_PARAMETER5       (_VI_ERROR+0x3FFC0005L)
#define VI_ERROR_PARAMETER6       (_VI_ERROR+0x3FFC0006L)
#define VI_ERROR_PARAMETER7       (_VI_ERROR+0x3FFC0007L)
#define VI_ERROR_PARAMETER8       (_VI_ERROR+0x3FFC0008L)
#define VI_ERROR_FAIL_ID_QUERY    (_VI_ERROR+0x3FFC0011L)
#define VI_ERROR_INV_RESPONSE     (_VI_ERROR+0x3FFC0012L)

#ifndef VI_ERROR_TMO
#define VI_ERROR_TMO              (_VI_ERROR+0x3FFF0015L)
#endif

#ifndef VI_ERROR_RSRC_NFOUND
#define VI_ERROR_RSRC_NFOUND      (_VI_ERROR+0x3FFF0011L)
#endif
#define RS_STATUS_CODE_BASE                     0x3FFC0000L

#define RS_WARN_BASE                            (RS_STATUS_CODE_BASE)
#define RS_CROSS_CLASS_WARN_BASE                (RS_WARN_BASE + 0x1000)
#define RS_CLASS_WARN_BASE                      (RS_WARN_BASE + 0x2000)
#define RS_SPECIFIC_WARN_BASE                   (RS_WARN_BASE + 0x4000)
#define RS_MAX_SPECIFIC_WARN_CODE               (RS_WARN_BASE + 0x7FFF)
#define RS_NI_WARN_BASE                         (RS_WARN_BASE + 0x6000)

#define RS_ERROR_BASE                           (_VI_ERROR + RS_STATUS_CODE_BASE)
#define RS_CROSS_CLASS_ERROR_BASE               (RS_ERROR_BASE + 0x1000)
#define RS_CLASS_ERROR_BASE                     (RS_ERROR_BASE + 0x2000)
#define RS_SPECIFIC_ERROR_BASE                  (RS_ERROR_BASE + 0x4000)
#define RS_MAX_SPECIFIC_ERROR_CODE              (RS_ERROR_BASE + 0x7FFF)
#define RS_NI_ERROR_BASE                        (RS_ERROR_BASE + 0x6000)
#define RS_SHARED_COMPONENT_ERROR_BASE          (RS_ERROR_BASE + 0x1000)

/* engine warnings*/

#define RS_WARN_NSUP_ID_QUERY                   (RS_WARN_BASE + 0x65)
#define RS_WARN_NSUP_RESET                      (RS_WARN_BASE + 0x66)
#define RS_WARN_NSUP_SELF_TEST                  (RS_WARN_BASE + 0x67)
#define RS_WARN_NSUP_ERROR_QUERY                (RS_WARN_BASE + 0x68)
#define RS_WARN_NSUP_REV_QUERY                  (RS_WARN_BASE + 0x69)
#define RS_WARN_UNKNOWN_INSTRUMENT_STATUS       (RS_WARN_BASE + 0x6A)
#define RS_WARN_DUPLICATE_CHANNEL_STRING        (RS_WARN_BASE + 0x3E)

/* engine errors and general purpose vi errors */

#define RS_ERROR_CANNOT_RECOVER                 (RS_ERROR_BASE + 0x00)
#define RS_ERROR_INSTRUMENT_STATUS              (RS_ERROR_BASE + 0x101)
#define RS_ERROR_CANNOT_OPEN_FILE               (RS_ERROR_BASE + 0x102)
#define RS_ERROR_READING_FILE                   (RS_ERROR_BASE + 0x103)
#define RS_ERROR_WRITING_FILE                   (RS_ERROR_BASE + 0x104)
#define RS_ERROR_INVALID_PATHNAME               (RS_ERROR_BASE + 0x0B)
#define RS_ERROR_INVALID_ATTRIBUTE              (RS_ERROR_BASE + 0x0C)
#define RS_ERROR_RS_ATTR_NOT_WRITABLE           (RS_ERROR_BASE + 0x0D)
#define RS_ERROR_RS_ATTR_NOT_READABLE           (RS_ERROR_BASE + 0x0E)
#define RS_ERROR_INVALID_VALUE                  (RS_ERROR_BASE + 0x10)
#define RS_ERROR_FUNCTION_NOT_SUPPORTED         (RS_ERROR_BASE + 0x111)
#define RS_ERROR_ATTRIBUTE_NOT_SUPPORTED        (RS_ERROR_BASE + 0x112)
#define RS_ERROR_VALUE_NOT_SUPPORTED            (RS_ERROR_BASE + 0x13)
#define RS_ERROR_SESSION_TYPE_NOT_SUPPORTED     (RS_ERROR_BASE + 0x6B)
#define RS_ERROR_TYPES_DO_NOT_MATCH             (RS_ERROR_BASE + 0x15)
#define RS_ERROR_NOT_INITIALIZED                (RS_ERROR_BASE + 0x1D)
#define RS_ERROR_UNKNOWN_CHANNEL_NAME           (RS_ERROR_BASE + 0x20)
#define RS_ERROR_TOO_MANY_OPEN_FILES            (RS_ERROR_BASE + 0x23)
#define RS_ERROR_CHANNEL_NAME_REQUIRED          (RS_ERROR_BASE + 0x44)
#define RS_ERROR_CHANNEL_NAME_NOT_ALLOWED       (RS_ERROR_BASE + 0x45)
#define RS_ERROR_MISSING_OPTION_NAME            (RS_ERROR_BASE + 0x49)
#define RS_ERROR_MISSING_OPTION_VALUE           (RS_ERROR_BASE + 0x4A)
#define RS_ERROR_BAD_OPTION_NAME                (RS_ERROR_BASE + 0x4B)
#define RS_ERROR_BAD_OPTION_VALUE               (RS_ERROR_BASE + 0x4C)
#define RS_ERROR_OUT_OF_MEMORY                  (RS_ERROR_BASE + 0x56)
#define RS_ERROR_OPERATION_PENDING              (RS_ERROR_BASE + 0x57)
#define RS_ERROR_NULL_POINTER                   (RS_ERROR_BASE + 0x58)
#define RS_ERROR_UNEXPECTED_RESPONSE            (RS_ERROR_BASE + 0x59)
#define RS_ERROR_FILE_NOT_FOUND                 (RS_ERROR_BASE + 0x5B)
#define RS_ERROR_INVALID_FILE_FORMAT            (RS_ERROR_BASE + 0x5C)
#define RS_ERROR_STATUS_NOT_AVAILABLE           (RS_ERROR_BASE + 0x5D)
#define RS_ERROR_ID_QUERY_FAILED                (RS_ERROR_BASE + 0x5E)
#define RS_ERROR_RESET_FAILED                   (RS_ERROR_BASE + 0x5F)
#define RS_ERROR_RESOURCE_UNKNOWN               (RS_ERROR_BASE + 0x60)
#define RS_ERROR_ALREADY_INITIALIZED            (RS_ERROR_BASE + 0x61)
#define RS_ERROR_CANNOT_CHANGE_SIMULATION_STATE         (RS_ERROR_BASE + 0x62)
#define RS_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR   (RS_ERROR_BASE + 0x63)
#define RS_ERROR_INVALID_RANGE_IN_SELECTOR      (RS_ERROR_BASE + 0x64)
#define RS_ERROR_UNKOWN_NAME_IN_SELECTOR        (RS_ERROR_BASE + 0x65)
#define RS_ERROR_BADLY_FORMED_SELECTOR          (RS_ERROR_BASE + 0x66)
#define RS_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER    (RS_ERROR_BASE + 0x67)
#define RS_ERROR_STRING_TOO_LONG                (RS_ERROR_BASE + 0x6B)
#define RS_ERROR_DATA_TOO_LONG                  (RS_ERROR_BASE + 0x6C)
#define RS_ERROR_MAX_SESSION_COUNT_REACHED      (RS_ERROR_BASE + 0x6D)
#define RS_ERROR_ALLOC                          (RS_ERROR_BASE + 0x6E)

/* non-foundation-defined pre-existing errors */

#define RS_ERROR_DRIVER_MODULE_NOT_FOUND        (RS_ERROR_BASE + 0x105)
#define RS_ERROR_CANNOT_OPEN_DRIVER_MODULE      (RS_ERROR_BASE + 0x106)
#define RS_ERROR_INVALID_DRIVER_MODULE          (RS_ERROR_BASE + 0x107)
#define RS_ERROR_UNDEFINED_REFERENCES           (RS_ERROR_BASE + 0x108)
#define RS_ERROR_FUNCTION_NOT_FOUND             (RS_ERROR_BASE + 0x109)
#define RS_ERROR_LOADING_DRIVER_MODULE          (RS_ERROR_BASE + 0x0A)
#define RS_ERROR_INVALID_PARAMETER              (RS_ERROR_BASE + 0x0F)
#define RS_ERROR_INVALID_TYPE                   (RS_ERROR_BASE + 0x14)
#define RS_ERROR_MULTIPLE_DEFERRED_SETTING      (RS_ERROR_BASE + 0x16)
#define RS_ERROR_ITEM_ALREADY_EXISTS            (RS_ERROR_BASE + 0x17)
#define RS_ERROR_INVALID_CONFIGURATION          (RS_ERROR_BASE + 0x18)
#define RS_ERROR_VALUE_NOT_AVAILABLE            (RS_ERROR_BASE + 0x19)
#define RS_ERROR_ATTRIBUTE_VALUE_NOT_KNOWN      (RS_ERROR_BASE + 0x1A)
#define RS_ERROR_NO_RANGE_TABLE                 (RS_ERROR_BASE + 0x1B)
#define RS_ERROR_INVALID_RANGE_TABLE            (RS_ERROR_BASE + 0x1C)
#define RS_ERROR_NON_INTERCHANGEABLE_BEHAVIOR   (RS_ERROR_BASE + 0x1E)
#define RS_ERROR_NO_CHANNEL_TABLE               (RS_ERROR_BASE + 0x1F)
#define RS_ERROR_SYS_RSRC_ALLOC                 (RS_ERROR_BASE + 0x21)
#define RS_ERROR_ACCESS_DENIED                  (RS_ERROR_BASE + 0x22)
#define RS_ERROR_UNABLE_TO_CREATE_TEMP_FILE     (RS_ERROR_BASE + 0x24)
#define RS_ERROR_NO_UNUSED_TEMP_FILENAMES       (RS_ERROR_BASE + 0x25)
#define RS_ERROR_DISK_FULL                      (RS_ERROR_BASE + 0x26)
#define RS_ERROR_CONFIG_FILE_NOT_FOUND          (RS_ERROR_BASE + 0x27)
#define RS_ERROR_CANNOT_OPEN_CONFIG_FILE        (RS_ERROR_BASE + 0x28)
#define RS_ERROR_ERROR_READING_CONFIG_FILE      (RS_ERROR_BASE + 0x29)
#define RS_ERROR_BAD_INTEGER_IN_CONFIG_FILE     (RS_ERROR_BASE + 0x2A)
#define RS_ERROR_BAD_DOUBLE_IN_CONFIG_FILE      (RS_ERROR_BASE + 0x2B)
#define RS_ERROR_BAD_BOOLEAN_IN_CONFIG_FILE     (RS_ERROR_BASE + 0x2C)
#define RS_ERROR_CONFIG_ENTRY_NOT_FOUND         (RS_ERROR_BASE + 0x2D)
#define RS_ERROR_DRIVER_DLL_INIT_FAILED         (RS_ERROR_BASE + 0x2E)
#define RS_ERROR_DRIVER_UNRESOLVED_SYMBOL       (RS_ERROR_BASE + 0x2F)
#define RS_ERROR_CANNOT_FIND_CVI_RTE            (RS_ERROR_BASE + 0x30)
#define RS_ERROR_CANNOT_OPEN_CVI_RTE            (RS_ERROR_BASE + 0x31)
#define RS_ERROR_CVI_RTE_INVALID_FORMAT         (RS_ERROR_BASE + 0x32)
#define RS_ERROR_CVI_RTE_MISSING_FUNCTION       (RS_ERROR_BASE + 0x33)
#define RS_ERROR_CVI_RTE_INIT_FAILED            (RS_ERROR_BASE + 0x34)
#define RS_ERROR_CVI_RTE_UNRESOLVED_SYMBOL      (RS_ERROR_BASE + 0x35)
#define RS_ERROR_LOADING_CVI_RTE                (RS_ERROR_BASE + 0x36)
#define RS_ERROR_CANNOT_OPEN_DLL_FOR_EXPORTS    (RS_ERROR_BASE + 0x37)
#define RS_ERROR_DLL_CORRUPTED                  (RS_ERROR_BASE + 0x38)
#define RS_ERROR_NO_DLL_EXPORT_TABLE            (RS_ERROR_BASE + 0x39)
#define RS_ERROR_UNKNOWN_DEFAULT_SETUP_ATTR     (RS_ERROR_BASE + 0x3A)
#define RS_ERROR_INVALID_DEFAULT_SETUP_VAL      (RS_ERROR_BASE + 0x3B)
#define RS_ERROR_UNKNOWN_MEMORY_PTR             (RS_ERROR_BASE + 0x3C)
#define RS_ERROR_EMPTY_CHANNEL_LIST             (RS_ERROR_BASE + 0x3D)
#define RS_ERROR_DUPLICATE_CHANNEL_STRING       (RS_ERROR_BASE + 0x3E)
#define RS_ERROR_DUPLICATE_VIRT_CHAN_NAME       (RS_ERROR_BASE + 0x3F)
#define RS_ERROR_MISSING_VIRT_CHAN_NAME         (RS_ERROR_BASE + 0x40)
#define RS_ERROR_BAD_VIRT_CHAN_NAME             (RS_ERROR_BASE + 0x41)
#define RS_ERROR_UNASSIGNED_VIRT_CHAN_NAME      (RS_ERROR_BASE + 0x42)
#define RS_ERROR_BAD_VIRT_CHAN_ASSIGNMENT       (RS_ERROR_BASE + 0x43)
#define RS_ERROR_ATTR_NOT_VALID_FOR_CHANNEL     (RS_ERROR_BASE + 0x46)
#define RS_ERROR_ATTR_MUST_BE_CHANNEL_BASED     (RS_ERROR_BASE + 0x47)
#define RS_ERROR_CHANNEL_ALREADY_EXCLUDED       (RS_ERROR_BASE + 0x48)
#define RS_ERROR_NOT_CREATED_BY_CLASS           (RS_ERROR_BASE + 0x4D)
#define RS_ERROR_RS_INI_IS_RESERVED             (RS_ERROR_BASE + 0x4E)
#define RS_ERROR_DUP_RUNTIME_CONFIG_ENTRY       (RS_ERROR_BASE + 0x4F)
#define RS_ERROR_INDEX_IS_ONE_BASED             (RS_ERROR_BASE + 0x50)
#define RS_ERROR_INDEX_IS_TOO_HIGH              (RS_ERROR_BASE + 0x51)
#define RS_ERROR_ATTR_NOT_CACHEABLE             (RS_ERROR_BASE + 0x52)
#define RS_ERROR_ADDR_ATTRS_MUST_BE_HIDDEN      (RS_ERROR_BASE + 0x53)
#define RS_ERROR_BAD_CHANNEL_NAME               (RS_ERROR_BASE + 0x54)
#define RS_ERROR_BAD_PREFIX_IN_CONFIG_FILE      (RS_ERROR_BASE + 0x55)

#define RS_ERROR_REPEATED_CAPABILITY_NAME_REQUIRED          RS_ERROR_CHANNEL_NAME_REQUIRED
#define RS_ERROR_UNKNOWN_REPEATED_CAPABILITY_NAME           RS_ERROR_UNKNOWN_CHANNEL_NAME
#define RS_ERROR_EMPTY_REPEATED_CAPABILITY_LIST             RS_ERROR_EMPTY_CHANNEL_LIST
#define RS_ERROR_DUPLICATE_REPEATED_CAPABILITY_IDENTIFIER   RS_ERROR_DUPLICATE_CHANNEL_STRING
#define RS_ERROR_REPEATED_CAPABILITY_NAME_NOT_ALLOWED       RS_ERROR_CHANNEL_NAME_NOT_ALLOWED
#define RS_ERROR_ATTR_NOT_VALID_FOR_REPEATED_CAPABILITY     RS_ERROR_ATTR_NOT_VALID_FOR_CHANNEL
#define RS_ERROR_ATTR_MUST_BE_REPEATED_CAPABILITY_BASED     RS_ERROR_ATTR_MUST_BE_CHANNEL_BASED
#define RS_ERROR_BAD_REPEATED_CAPABILITY_NAME               RS_ERROR_BAD_CHANNEL_NAME

#define RS_ERROR_CANNOT_MODIFY_REPEATED_CAPABILITY_TABLE    (RS_NI_ERROR_BASE + 0)
#define RS_ERROR_CANNOT_RESTRICT_ATTRIBUTE_TWICE            (RS_NI_ERROR_BASE + 1)
#define RS_ERROR_REPEATED_CAPABILITY_ALREADY_EXISTS         (RS_NI_ERROR_BASE + 2)
#define RS_ERROR_REPEATED_CAPABILITY_NOT_DEFINED            (RS_NI_ERROR_BASE + 3)
#define RS_ERROR_INVALID_REPEATED_CAPABILITY_NAME           (RS_NI_ERROR_BASE + 4)
#define RS_ERROR_CONFIG_SERVER_NOT_PRESENT                  (RS_NI_ERROR_BASE + 0xD)

/* Renamed errors. Do not use these identifiers in your drivers and applications. */

#define RS_ERROR_CANNOT_LOAD_RS_ENGINE                      (RS_ERROR_BASE + 0x00)
#define RS_ERROR_INSTR_SPECIFIC                             (RS_ERROR_BASE + 0x101)
#define RS_ERROR_TOO_MANY_FILES_OPEN                        (RS_ERROR_BASE + 0x23)

/* Custom errors */

#define RS_ERROR_INSTRUMENT_OPTION                          (RS_ERROR_BASE + 0x9F1)
#define RS_ERROR_INSTRUMENT_MODEL                           (RS_ERROR_BASE + 0x9F2)

/* Misc */

#define RS_ERROR_INVALID_SESSION_HANDLE                     (RS_CROSS_CLASS_ERROR_BASE + 0x190)
#define RS_ERROR_CANNOT_CREATE_LOCK                         (RS_CROSS_CLASS_ERROR_BASE + 0x198)
#define RS_ERROR_CANNOT_CREATE_THREAD_LOCAL                 (RS_CROSS_CLASS_ERROR_BASE + 0x1A0)

#define RS_CONFIG_ERROR_DESERIALIZE_FAILED                  (RS_CROSS_CLASS_ERROR_BASE + 0x200)
#define RS_CONFIG_ERROR_ALREADY_DESERIALIZED                (RS_CROSS_CLASS_ERROR_BASE + 0x201)
#define RS_CONFIG_ERROR_SERIALIZE_FAILED                    (RS_CROSS_CLASS_ERROR_BASE + 0x202)
#define RS_CONFIG_ERROR_SESSION_NOT_FOUND                   (RS_CROSS_CLASS_ERROR_BASE + 0x203)
#define RS_CONFIG_ERROR_NOT_IN_GLOBAL                       (RS_CROSS_CLASS_ERROR_BASE + 0x204)
#define RS_CONFIG_ERROR_ALREADY_EXIST                       (RS_CROSS_CLASS_ERROR_BASE + 0x205)
#define RS_CONFIG_ERROR_MASTER_NOT_FOUND                    (RS_CROSS_CLASS_ERROR_BASE + 0x206)
#define RS_CONFIG_ERROR_NOT_EXIST                           (RS_CROSS_CLASS_ERROR_BASE + 0x207)
#define RS_CONFIG_ERROR_INVALID_DATA_COMPONENT              (RS_CROSS_CLASS_ERROR_BASE + 0x208)
#define RS_CONFIG_ERROR_LOCAL_REFERENCE_EXIST               (RS_CROSS_CLASS_ERROR_BASE + 0x209)
#define RS_CONFIG_ERROR_INVALID_HANDLE                      (RS_CROSS_CLASS_ERROR_BASE + 0x232)
#define RS_CONFIG_ERROR_INVALID_PROPERTY_ID                 (RS_CROSS_CLASS_ERROR_BASE + 0x233)

/******************************************************************************************************
---- Base values for attribute constant --------------------------------------------------------------*
******************************************************************************************************/

#define RS_ATTR_BASE                    1000000
#define RS_ENGINE_PRIVATE_ATTR_BASE     (RS_ATTR_BASE +  00000)   /* base for private attributes of the RS engine */
#define RS_ENGINE_PUBLIC_ATTR_BASE      (RS_ATTR_BASE +  50000)   /* base for public attributes of the RS engine */
#define RS_SPECIFIC_PRIVATE_ATTR_BASE   (RS_ATTR_BASE + 100000)   /* base for private attributes of specific drivers */
#define RS_SPECIFIC_PUBLIC_ATTR_BASE    (RS_ATTR_BASE + 150000)   /* base for public attributes of specific drivers */
#define RS_CLASS_PRIVATE_ATTR_BASE      (RS_ATTR_BASE + 200000)   /* base for private attributes of class drivers */
#define RS_CLASS_PUBLIC_ATTR_BASE       (RS_ATTR_BASE + 250000)   /* base for public attributes of specific drivers */

/******************************************************************************************************
---- Public RS engine attributes ---------------------------------------------------------------------*
---- Note: "hidden" means not readable or writable by the end-user. ---------=------------------------*
******************************************************************************************************/

/*- Inherent Instrument Specific Attributes ----------------------------*/

/* User Options */

#define RS_ATTR_RANGE_CHECK                                 /* ViBoolean, VI_TRUE */            (RS_ENGINE_PUBLIC_ATTR_BASE + 2)
#define RS_ATTR_QUERY_INSTRUMENT_STATUS                     /* ViBoolean, VI_FALSE */           (RS_ENGINE_PUBLIC_ATTR_BASE + 3)   /* If VI_TRUE, the specific driver is allowed to query the instrument error status after each operation */
#define RS_ATTR_CACHE                                       /* ViBoolean, VI_TRUE */            (RS_ENGINE_PUBLIC_ATTR_BASE + 4)
#define RS_ATTR_SIMULATE                                    /* ViBoolean, VI_FALSE */           (RS_ENGINE_PUBLIC_ATTR_BASE + 5)
#define RS_ATTR_RECORD_COERCIONS                            /* ViBoolean, VI_FALSE */           (RS_ENGINE_PUBLIC_ATTR_BASE + 6)
#define RS_ATTR_INTERCHANGE_CHECK                           /* ViBoolean, VI_TRUE */            (RS_ENGINE_PUBLIC_ATTR_BASE + 21)
#define RS_ATTR_SPY                                         /* ViBoolean, VI_FALSE */           (RS_ENGINE_PUBLIC_ATTR_BASE + 22)
#define RS_ATTR_USE_SPECIFIC_SIMULATION                     /* ViBoolean */                     (RS_ENGINE_PUBLIC_ATTR_BASE + 23)  /* simulate values in specific rather than class driver;  default is VI_TRUE if session opened through class driver, VI_FALSE otherwise */

/* Class Driver Identification */

#define RS_ATTR_CLASS_DRIVER_DESCRIPTION                    /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 518)
#define RS_ATTR_CLASS_DRIVER_PREFIX                         /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 301)  /* instrument prefix for the class driver;  empty string if not using class driver */
#define RS_ATTR_CLASS_DRIVER_VENDOR                         /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 517)
#define RS_ATTR_CLASS_DRIVER_REVISION                       /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 552)
#define RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION       /* ViInt32, not user-writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 519)
#define RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION       /* ViInt32, not user-writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 520)

/* Driver Identification */

#define RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION                 /* ViString, not user-writable*/    (RS_ENGINE_PUBLIC_ATTR_BASE + 514)
#define RS_ATTR_SPECIFIC_DRIVER_PREFIX                      /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 302)  /* instrument prefix for the specific driver */
#define RS_ATTR_SPECIFIC_DRIVER_LOCATOR                     /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 303)  /* the pathname of the specific driver code module; from the configuration file */
#define RS_ATTR_SPECIFIC_DRIVER_VENDOR                      /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 513)
#define RS_ATTR_SPECIFIC_DRIVER_REVISION                    /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 551)
#define RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION    /* ViInt32, not user-writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 515)
#define RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION    /* ViInt32, not user-writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 516)

/* Driver Capabilities */

#define RS_ATTR_SUPPORTED_INSTRUMENT_MODELS                 /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 327)
#define RS_ATTR_GROUP_CAPABILITIES                          /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 401)
#define RS_ATTR_FUNCTION_CAPABILITIES                       /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 402)
#define RS_ATTR_CHANNEL_COUNT                               /* ViInt32,  not writable*/         (RS_ENGINE_PUBLIC_ATTR_BASE + 203)   /* set by the specific-driver;  default: 1 */

/* Driver Setup */

#define RS_ATTR_DRIVER_SETUP                                /* ViString,  "" */                 (RS_ENGINE_PUBLIC_ATTR_BASE + 7)

/* Instrument Identification */

#define RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 510)
#define RS_ATTR_INSTRUMENT_MANUFACTURER                     /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 511)
#define RS_ATTR_INSTRUMENT_MODEL                            /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 512)
#define RS_ATTR_OPTIONS_LIST                                /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 591)

/* Advanced Session Information */

#define RS_ATTR_IO_RESOURCE_DESCRIPTOR                      /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 304)  /* the string that describes how to find the physical instrument; from the configuration file */
#define RS_ATTR_LOGICAL_NAME                                /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 305)  /* for class drivers, the logical name used in the Init call to identify the specific instrument */

/*- Inherent Vendor Specific Attributes --------------------------------*/

#define RS_ATTR_NONE                                        /* no attribute */                  -1

/* Error Info */

#define RS_ATTR_PRIMARY_ERROR                               /* ViInt32  */                      (RS_ENGINE_PUBLIC_ATTR_BASE + 101)
#define RS_ATTR_SECONDARY_ERROR                             /* ViInt32  */                      (RS_ENGINE_PUBLIC_ATTR_BASE + 102)
#define RS_ATTR_ERROR_ELABORATION                           /* ViString */                      (RS_ENGINE_PUBLIC_ATTR_BASE + 103)

/* Session I/O */

#define RS_ATTR_VISA_RM_SESSION                             /* ViSession,hidden      */         (RS_ENGINE_PUBLIC_ATTR_BASE + 321)
#define RS_ATTR_IO_SESSION                                  /* ViSession,not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 322)
#define RS_ATTR_IO_SESSION_TYPE                             /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 324)

/* Version Info */

#define RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION               /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 503)
#define RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION               /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 504)
#define RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION         /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 590)
#define RS_ATTR_CLASS_DRIVER_MAJOR_VERSION                  /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 505)
#define RS_ATTR_CLASS_DRIVER_MINOR_VERSION                  /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 506)
#define RS_ATTR_ENGINE_MAJOR_VERSION                        /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 501)
#define RS_ATTR_ENGINE_MINOR_VERSION                        /* ViInt32,  not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 502)
#define RS_ATTR_ENGINE_REVISION                             /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 553)

/* Session Callbacks */

#define RS_ATTR_OPC_CALLBACK                                /* ViAddr,    hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 602)  /* see RsCoreOpcAttrCallback typedef */
#define RS_ATTR_CHECK_STATUS_CALLBACK                       /* ViAddr,    hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 603)  /* see Rs_CheckStatusCallbackPtr typedef */
#define RS_ATTR_OPC_TIMEOUT                                 /* ViInt32,   hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 1001)

/******************************************************************************************************
---- Macros for checking for errors. -----------------------------------------------------------------*
******************************************************************************************************/

// Check if the string is null or empty
#ifndef isNullOrEmpty
#define isNullOrEmpty(string)   ( (string) == NULL || strlen(string) == 0)
#endif

// checkErr(status)
// Assign status to the error variable. If status is negative,
// jump to the Error label.
#ifndef checkErr
#define checkErr(fCall)      if (error = (fCall), error < 0) goto Error;
#endif

// checkErrKeepWarn(status) -*/
// Assign status to the error variable. If negative, jump to the Error label.
// If the status is 0, keep the previous warning status.
// If the status is > 0, the old warning is overwritten
#ifndef checkErrKeepWarn
#define checkErrKeepWarn(fCall) if (warning = error, error = (fCall), error < 0) goto Error;\
                                else error = (error == 0) ? warning : error;
#endif

// checkStatusOnErr(status)
// Assign status to the error variable.
// If status is VI_ERROR_TMO or RS_ERROR_INSTRUMENT_STATUS, jump to the CheckStatus.
// Otherwise acts as the checkErr
#ifndef checkStatusOnErr
#define checkStatusOnErr(fCall)      error = (fCall); if (error < 0)\
                                        { if (error != RS_ERROR_INSTRUMENT_STATUS && error != VI_ERROR_TMO)\
                                            goto Error; else goto CheckStatus; }
#endif

// viCheckErrElab(status, elabString)
// Assign status to the error variable.
// If status is negative, pass it and elab string to Rs_SetErrorInfo
// and jump to the Error label.
#ifndef viCheckErrElab
#define viCheckErrElab(fCall, elab) error = (fCall); \
                                 if (error < 0) { (void)RsCore_SetErrorInfo(instrSession, VI_TRUE, error, 0, elab); goto Error;}
#endif

// checkAlloc(pointer)
// If pointer is NULL, assign RS_ERROR_ALLOC to the error variable
// and jump to the Error label.
#ifndef checkAlloc
#define checkAlloc(fCall)    {if ((fCall) == 0) \
                                { error = RS_ERROR_ALLOC; goto Error;}}
#endif

// viCheckAlloc(pointer)
// If pointer is NULL, assign RS_ERROR_ALLOC to the error variable,
// call Rs_SetErrorInfo with RS_ERROR_ALLOC as the primary error code,
// and jump to the Error label.
#ifndef viCheckAlloc
#define viCheckAlloc(fCall)  {if ((fCall) == 0) \
                                { error = RS_ERROR_ALLOC; RsCore_SetErrorInfo(instrSession, VI_TRUE, error, 0, ""); goto Error;}}
#endif

// viCheckAllocElab(pointer, elab)
// If pointer is NULL, assign RS_ERROR_ALLOC to the error variable,
// call Rs_SetErrorInfo with RS_ERROR_ALLOC as the primary error code, plus elabString
// and jump to the Error label.
#ifndef viCheckAllocElab
#define viCheckAllocElab(fCall, elab)  {if ((fCall) == 0) \
                                            {error = RS_ERROR_ALLOC; RsCore_SetErrorInfo(instrSession, VI_TRUE, error, 0, elab); goto Error;}}
#endif

// viCheckReallocElab(pointer, fReallocCall, elab)
// If pointer is NULL, free the old pointer, assign RS_ERROR_ALLOC to the error variable,
// call Rs_SetErrorInfo with RS_ERROR_ALLOC as the primary error code,
// plus elabString and jump to the Error label.
#ifndef viCheckReallocElab
#define viCheckReallocElab(ptr, fReallocCall, elab)  { void *oldptr = ptr; \
                                                if (((ptr) = (fReallocCall)) == 0) \
                                                {free(oldptr); error = RS_ERROR_ALLOC;\
                                                RsCore_SetErrorInfo(instrSession, VI_TRUE, error, 0, elab); goto Error;}}
#endif

//	viCheckParm(status, parameterPosition, parameterName) -*/
//	Assign status to the error variable.
//	If status is positive,
//	coerce the error variable to zero. If status is negative, do the following:
//  - Convert parameterPosition into one of the VXIplug&play error codes for invalid parameters,
//      and pass it as the secondary error code to Rs_SetErrorInfo.
//  - Pass status as the primary error code, and pass parameterName as the error elaboration.
//  - Jump to the Error label.
#ifndef viCheckParm
#define viCheckParm(fCall, parameterPosition, parameterName) \
                        { error = (fCall); if (error != 0) \
                        { (void)RsCore_AppendSecondaryError(instrSession, error, RsCore_ParamPositionError(parameterPosition), parameterName); \
                        goto Error; } }
#endif

/******************************************************************************************************
---- Formatting codes for ViInt32 and ViUInt32 -------------------------------------------------------*
******************************************************************************************************/
#if defined(LONG_MAX) && (LONG_MAX > 0x7FFFFFFFL)
#define _PERCD "%d"
#define _PERCU "%u"
#define _PERCX "%x"
#define _PERCLD "%ld"
#define _PERCLX "%lx"
#define _PERCLX "%lx"
#define _PERCLX "%lo"
#else
#define _PERCD "%ld"
#define _PERCU "%lu"
#define _PERCX "%lx"
#define _PERCO "%lo"
#define _PERCLD "%lld"
#define _PERCLX "%llx"
#define _PERCLO "%llo"
#endif

/******************************************************************************************************
---- Typedef for RsCore Session ----------------------------------------------------------------------*
******************************************************************************************************/
typedef ViInt32 RsCoreSessionType;
#define RS_INTF_UNKNOWN     (0)
#define RS_INTF_GPIB        (1)
#define RS_INTF_ASRL        (4)
#define RS_INTF_TCPIP       (6)
#define RS_INTF_USB         (7)
#define RS_INTF_SOCKET      (8)

/******************************************************************************************************
---- Typedefs and related constants for the range tables ---------------------------------------------*
******************************************************************************************************/

#define RS_VAL_DISCRETE         0   /* Discrete set - discreteOrMinValue, and cmdString (or cmdValue) fields used */
#define RS_VAL_RANGED           1   /* Ranged value - discreteOrMinValue, maxValue, and cmdString (or cmdValue) fields used */
#define RS_VAL_COERCED          2   /* Coerced value - discreteOrMinValue, maxValue, coercedValue, and cmdString (or cmdValue) fields used */

// RsCoreRangeTable contains an array of RsCoreRangeTableEntry structures
typedef struct RsCoreRangeTableEntry
{
    ViReal64     discreteOrMinValue;
    ViReal64     maxValue;
    ViReal64     coercedValue;
    ViString     cmdString; // Optional
    ViInt32      cmdValue; // Indicates end of range table
} RsCoreRangeTableEntry, *RsCoreRangeTableEntryPtr;

typedef struct RsCoreRangeTable
{
    ViInt32                type;
	ViBoolean              reserved1;
	ViBoolean              reserved2;
    ViString               customInfo;
    RsCoreRangeTableEntry* rangeValues;
    // The end of rangeValues[] is marked by the entry RS_RANGE_TABLE_LAST_ENTRY
} RsCoreRangeTable;

typedef RsCoreRangeTable* RsCoreRangeTablePtr;

#define RS_RANGE_TABLE_END_STRING      NULL  /* The value for the command string of the last entry in an RsCoreRangeTable */
#define RS_RANGE_TABLE_END_VALUE       -999999
#define RS_RANGE_TABLE_LAST_ENTRY      1.0E308, 1.0E308, 1.0E308, RS_RANGE_TABLE_END_STRING, RS_RANGE_TABLE_END_VALUE  /* Marks the last entry in an RsCoreRangeTable */

/******************************************************************************************************
---- Typedefs for string-value tables (Driver-custom error codes) ------------------------------------*
******************************************************************************************************/
typedef struct RsCoreStringValueEntry
{
    ViInt32 value;
    ViString string;
} RsCoreStringValueEntry;

typedef RsCoreStringValueEntry RsCoreStringValueTable[];

typedef struct RsCoreStringValuePair
{
    ViInt32 value;
    ViChar string[RS_MAX_MESSAGE_BUF_SIZE];
} RsCoreStringValuePair;

/******************************************************************************************************
---- Typedef and related constants for the attribute flags -------------------------------------------*
******************************************************************************************************/
typedef ViInt32 RsCoreAttrFlags;

#define RS_VAL_NOT_SUPPORTED                    (1L << 0)  /* attribute automatically returns RS_ERROR_ATTRIBUTE_NOT_SUPPORTED when Set/Get/Checked/Invalidated */
#define RS_VAL_NOT_READABLE                     (1L << 1)  /* attribute cannot be Got */
#define RS_VAL_NOT_WRITABLE                     (1L << 2)  /* attribute cannot be Set */
#define RS_VAL_NOT_USER_READABLE                (1L << 3)  /* attribute cannot be Got by end-user */
#define RS_VAL_NOT_USER_WRITABLE                (1L << 4)  /* attribute cannot be Set by end-user */
#define RS_VAL_NEVER_CACHE                      (1L << 5)  /* always write/read to set/get attribute, i.e., never use a cached value, regardless of the state of RS_ATTR_CACHE */
#define RS_VAL_ALWAYS_CACHE                     (1L << 6)  /* specifies to always cache the value, regardless of the state of RS_ATTR_CACHE */
#define RS_VAL_WAIT_TO_CONTINUE					(1L << 7)  /* prevents servicing of the subsequent commands until all preceding commands have been executed and all signals have settled */
#define RS_VAL_FLUSH_ON_WRITE                   (1L << 9)  /* send RS_MSG_FLUSH to the BufferIOCallback (which by default calls viFlush) after the write callback */
#define RS_VAL_MULTI_CHANNEL                    (1L << 10) /* specified when the attribute is added. If set, the attribute has a separate value for each channel */
#define RS_VAL_COERCEABLE_ONLY_BY_INSTR         (1L << 11) /* specifies that the instrument coerces the attribute value in a way that the driver cannot anticipate in software. Do NOT use this flag UNLESS ABSOLUTELY NECESSARY !!! */
#define RS_VAL_WAIT_FOR_OPC_BEFORE_READS        (1L << 12) /* specifies to wait for operation complete before reads */
#define RS_VAL_WAIT_FOR_OPC_AFTER_WRITES        (1L << 13) /* specifies to wait for operation complete after writes */
#define RS_VAL_USE_CALLBACKS_FOR_SIMULATION     (1L << 14) /* specifies to call the read and write callbacks even in simulation mode */
#define RS_VAL_DONT_CHECK_STATUS                (1L << 15) /* specifies to not call the checkStatus callback even when RS_ATTR_QUERY_INSTR_STATUS is VI_TRUE */

#define RS_VAL_HIDDEN                           (RS_VAL_NOT_USER_READABLE | RS_VAL_NOT_USER_WRITABLE)

/******************************************************************************************************
---- Constants for optionFlags argument to Set/Check/Get callback functions --------------------------*
******************************************************************************************************/

/******************************************************************************************************
 RS_VAL_DIRECT_USER_CALL applies to Set/Check/Get attributes
 If TRUE, it signals an end-user call.
 If FALSE, the call comes from the core or from inside the driver.
 It causes:
- Blocking of the StatusCheck procedure
- access to attributes with the flag RS_VAL_HIDDEN
- ignores RS_VAL_NOT_USER_READABLE and RS_VAL_NOT_USER_WRITABLE
******************************************************************************************************/
#define RS_VAL_DIRECT_USER_CALL            (1<<0)

/******************************************************************************************************
    RS_VAL_SET_CACHE_ONLY applies to Set only;
    if 1, then: only the cached value is set and no instrument I/O is performed;
                use this when you set multiple instrument attributes with one
                I/O command; if you call Set calls with this flag,
                the update is never deferred
******************************************************************************************************/

#define RS_VAL_SET_CACHE_ONLY              (1<<1)

/******************************************************************************************************
---- Typedef and related constants for data types ----------------------------------------------------*
******************************************************************************************************/
typedef ViInt32 RsCoreDataType;

#define RS_VAL_INT32                1L
#define RS_VAL_INT64                2L
#define RS_VAL_REAL64               4L
#define RS_VAL_STRING               5L
#define RS_VAL_ADDR                 10L
#define RS_VAL_SESSION              11L
#define RS_VAL_BOOLEAN              13L
#define RS_VAL_UNKNOWN_TYPE         14L
#define RS_VAL_EVENT                15L
#define RS_VAL_RAWSTRING			16L

/******************************************************************************************************
---- Typedef and related constants for attribute access ----------------------------------------------*
******************************************************************************************************/
typedef ViInt32 RsCoreAttrAccess;

#define RS_VAL_READ_ONLY            0
#define RS_VAL_WRITE_ONLY           1
#define RS_VAL_READ_WRITE           2

/******************************************************************************************************
---- Function pointer typedefs for attribute callbacks -----------------------------------------------*
******************************************************************************************************/

typedef struct RsCoreAttribute RsCoreAttribute;
typedef RsCoreAttribute* RsCoreAttributePtr;

typedef ViStatus (*RsCoreReadAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr);
typedef ViStatus (*RsCoreWriteAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, void* value);
typedef ViStatus (*RsCoreCheckAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, void* value);
typedef ViStatus (*RsCoreCheckStatusAttrCallback)(ViSession instrSession, ViStatus errorBefore);
typedef ViStatus (*RsCoreCompareAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, void* coercedNewValue, void* cacheValue, void* result);
typedef ViStatus (*RsCoreCoerceAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, void* value);
typedef ViStatus (*RsCoreRangeTableAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, RsCoreRangeTablePtr* rangeTablePtr);
typedef ViStatus (*RsCoreUserAttrCallback)(ViSession instrSession, ViConstString repCapName, RsCoreAttributePtr attr, ViUInt32 bufSize, void* value);

// OPC Wait Callback type, by default the Rs_WaitForOPCCallback()
typedef ViStatus (*RsCoreOpcAttrCallback)(ViSession instrSession, ViInt32 timeout);

// Check status callback, by default Rs_CheckStatusCallback()
typedef ViStatus (*RsCoreCheckStatusCallback)(ViSession instrSession, ViStatus errorBefore);

// Function pointer typedef for the PREFIX_error_message function
typedef ViStatus (_VI_FUNC *RsCoreErrorMessage)(ViSession, ViStatus, ViChar*);

/******************************************************************************************************
---- Repeated Capability data structure --------------------------------------------------------------*
******************************************************************************************************/
typedef struct RsCoreRepCap
{
    ViString repCapNameId; /* Repeated capability name identifier */
    ViString repCapNames; /* Repeated capability names (comma separated values) */
    ViString cmdValues; /* Command values (comma separated values) */
} RsCoreRepCap, *RsCoreRepCapPtr;

/******************************************************************************************************
---- Attribute Properties Data Structure -------------------------------------------------------------*
******************************************************************************************************/
typedef struct RsCoreAttribute
{
    ViInt32 constant;

#ifdef _DEBUG
    ViString                      constantName;
#endif
    RsCoreAttrAccess              access;
    RsCoreDataType                dataType;
    RsCoreRangeTablePtr           rangeTable;
    ViString                      command;
    ViInt32                       integerDefault;
    ViReal64                      doubleDefault;
    ViBoolean                     booleanDefault;
    ViString                      stringDefault;
    ViSession                     sessionDefault;
    ViReal64                      comparePrecision;
    RsCoreReadAttrCallback        readCallback;
    RsCoreWriteAttrCallback       writeCallback;
    RsCoreCheckAttrCallback       checkCallback;
    RsCoreCheckStatusAttrCallback checkStatusCallback;
    RsCoreCoerceAttrCallback      coerceCallback;
    RsCoreRangeTableAttrCallback  rangeTableCallback;
    RsCoreUserAttrCallback        userCallback;
    RsCoreAttrFlags               flags;
    ViString                      supportedModels;
    ViString                      instrumentOptions;
    void*                         p2value;
    ViBoolean                     usercaps; /* Use repeated capability? */
} RsCoreAttribute;

/******************************************************************************************************
---- Used Attributes cache table ---------------------------------------------------------------------*
******************************************************************************************************/
typedef struct RsCoreUsedAttributesCache
{
    ViAttr*                  IDs;
    RsCoreAttributePtr*      attrs;
    ViInt32                  cachedCount;
    ViInt32                  allocatedSize;
} RsCoreUsedAttributesCache, *RsCoreUsedAttributesCachePtr;

/******************************************************************************************************
---- Session Property structure ----------------------------------------------------------------------*
******************************************************************************************************/
typedef struct RsCoreSession
{
    ViSession                 io; // Instrument IO session (also stored in RS_ATTR_IO_SESSION value)
    ViSession                 rmSession; // Resource Manager session
    void*                     mutex; // Session locking mutual exclusion handle
    ViBoolean                 multiThreadLocking; // If TRUE (default is FALSE), the session multi-thread locking mechanism is ON
    ViChar                    resourceName[RS_MAX_SHORT_MESSAGE_BUF_SIZE]; // ResourceName
    ViChar                    specificPrefix[RS_MAX_SHORT_MESSAGE_BUF_SIZE]; // specific driver prefix
    ViInt32                   sessionsListIndex; // Index in the global sessions list
    ViBoolean                 allowViClear; // Allow performing viClear, default = True
    ViBoolean                 reuseSession; // If FALSE (default), the init opens a new session. If TRUE, it reuses a session if it exists
    RsCoreSessionType         sessionType; // session type: TCPIP | GPIB | USB | SOCKET | SERIAL
    ViBoolean                 vxiCapable; // False for SOCKET and ASRL
    ViInt32                   opcWaitMode; // Defines OPC wait mode - STB polling, service request, OPC Query
    ViBoolean                 locked; // States whether session is locked by the operation in the process
    ViBoolean                 optionChecking; // Holds the option checking state
	ViChar                    idnString[RS_MAX_MESSAGE_BUF_SIZE]; // Idn string of the instrument. In case of simulation, the value is equal to the PREFIX_SIMULATION_ID_QUERY
	ViChar                    instrModelForErrMsg[RS_MAX_SHORT_MESSAGE_BUF_SIZE]; // Only used in error messages. If no alias is matched, the instrModelForErrMsg = 'modelFull'. Else, instrModelForErrMsg = '<realModel>' (treated as '<alias>')
    ViBoolean                 idnModelFullName; // if FALSE (default), RS_ATTR_INSTRUMENT_MODEL = e.g. "NRP33SN" If TRUE, RS_ATTR_INSTRUMENT_MODEL = e.g. "NRP"
    RsCoreAttributePtr        attributes; // Pointer to the list of all attributes
    ViInt32                   attributesCount; // Number of attributes in the list
    RsCoreUsedAttributesCache usedAttributesCache; // Table with used attribute pointers for very fast access
    RsCoreRepCapPtr           repCapTables; // List of repeated capabilities
    ViInt32                   repCapsCount; // Number of repeated capabilities in the list
    ViStatus                  primaryError; // Status code describing the primary error condition
    ViStatus                  secondaryError; // Status code that further describes the error or warning condition
    ViChar                    errorElaboration[RS_MAX_MESSAGE_BUF_SIZE]; // Elaboration string that further describes the error or warning condition.
    ViInt32                   fastSweepInstrument;
    ViInt32                   selfTestTimeout;
    ViInt32                   readDelay; // Delay before each read. For segmented reads it applies only to the the very first read
    ViInt32                   writeDelay; // Delay before each write. For segmented writes it applies only to the the very first write
    ViInt32                   ioSegmentSize; // Maximum size of one data block used by read or write
    ViBoolean                 addTermCharToWriteBinBlock; // If true, when writing bin data to instrument, an additional LF is added at the end.
    ViBoolean                 assureWriteWithLF; // If true, when writing a command, it makes sure that exactly one LF is at the command end.
    ViInt32                   viReadStbVisaTimeoutMs; // If bigger than 0 (default), every viReadSTB() sets this VISA timeout
    ViBoolean                 sendOpcInCheckStatus; // If true, the check status sends additionally an *OPC? query after *STB? query
    ViBoolean                 autoSystErrQuery; // If true, the check status also queries the SYST:ERR? Default: FALSE
    ViInt32                   binaryFloatNumbersFormat; // Coding of float numbers in binary data responses, usually RS_VAL_BIN_FLOAT_FORMAT_SINGLE_4BYTES
    ViInt32                   binaryIntegerNumbersFormat; // Coding of integer numbers in binary data responses, usually RS_VAL_BIN_INTEGER_FORMAT_INT32_4BYTES
    ViBoolean                 recogniseLongResponses; // If TRUE (default is FALSE), also long-form SCPI instrument responses are recognised
    ViBoolean                 reportAttrDataTypeMismatch; // If TRUE (default is FALSE), the driver reports error if an attribute is accessed with wrong data type
	ViBoolean                 recogniseScalarNumberBinFormat; // If TRUE (default is TRUE), in VXI-capable sessions, the expected float and integer return values are correctly parsed even in Binary format
	ViBoolean				  instrStatusStbQueryFirst; // If TRUE (default is TRUE), the error checking sends *STB? first and optionally SYST:ERR? afterwards. If FALSE, SYST:ERR? is called directly
	ViBoolean				  assureResponseEndWithLF; // If TRUE (default is FALSE), the string readings from the instrument are repeated until the LF character is read
    RsCoreAttributePtr        attrOptionsListPtr; // Pointer to the attribute RS_ATTR_OPTIONS_LIST
    RsCoreAttributePtr        attrInstrModelPtr; // Pointer to the attribute RS_ATTR_INSTRUMENT_MODEL
    RsCoreAttributePtr        attrOpcCallbackPtr; // Pointer to the attribute RS_ATTR_OPC_CALLBACK
    RsCoreAttributePtr        attrQueryInstrStatusPtr; // Pointer to the attribute RS_ATTR_QUERY_INSTR_STATUS
    RsCoreAttributePtr        attrRangeCheckPtr; // Pointer to the attribute RS_ATTR_RANGE_CHECK
    RsCoreAttributePtr        attrCheckStatusCallbackPtr; // Pointer to the attribute RS_ATTR_CHECK_STATUS_CALLBACK
    RsCoreAttributePtr        attrSimulatePtr; // Pointer to the attribute RS_ATTR_SIMULATE
} RsCoreSession,              *RsCoreSessionPtr;

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Exported functions ------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Session - related functions ---------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

ViStatus RsCore_NewSpecificDriver(ViRsrc              resourceName,
                                  ViConstString       specificPrefix,
                                  ViConstString       optionsString,
                                  RsCoreAttributePtr* attrList,
                                  ViBoolean           idnModelFullName,
                                  ViInt32             writeDelay,
                                  ViInt32             readDelay,
                                  ViInt32             ioSegmentSize,
                                  ViInt32             opcWaitMode,
                                  ViInt32             opcTimeout,
                                  ViInt32             visaTimeout,
                                  ViInt32             selfTestTimeout,
                                  ViInt32             binaryFloatNumbersFormat,
                                  ViInt32             binaryIntegerNumbersFormat,
                                  ViPSession          outSession);

ViStatus RsCore_CheckMinimalEngineVersion(ViSession instrSession,
                                          ViInt32   minMajorVersion,
                                          ViInt32   minMinorVersion,
                                          ViInt32   minFixVersion);

ViStatus RsCore_ApplyOptionString(ViSession     instrSession,
                                  ViConstString optionsString);

ViStatus RsCore_GetRsSession(ViSession         instrSession,
                             RsCoreSessionPtr* rsSession);

ViStatus RsCore_ViClose(ViSession instrSession);

ViStatus RsCore_Dispose(ViSession instrSession);

ViStatus RsCore_SetSpecificDriverRevision(ViSession instrSession,
                                          ViAttr    specificDriverRevisionAttrId);

ViStatus RsCore_ViClear(ViSession instrSession);

ViStatus RsCore_ClearStatus(ViSession instrSession);

ViStatus RsCore_LockSession(ViSession instrSession);

ViStatus RsCore_UnlockSession(ViSession instrSession);

ViBoolean RsCore_Simulating(ViSession instrSession);

ViBoolean RsCore_RangeChecking(ViSession instrSession);

ViBoolean RsCore_QueryInstrStatus(ViSession instrSession);

ViStatus RsCore_SetVisaTimeout(ViSession instrSession,
                               ViUInt32  timeoutMs);

ViStatus RsCore_GetVisaTimeout(ViSession instrSession,
                               ViPUInt32 outTimeoutMs);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Set / Get / Clear Error info --------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_SetErrorInfo(ViSession     instrSession,
                             ViBoolean     overWrite,
                             ViStatus      primaryError,
                             ViStatus      secondaryError,
                             ViConstString errorElab);

ViStatus RsCore_GetErrorInfo(ViSession instrSession,
                             ViPStatus outPrimaryError,
                             ViPStatus outSecondaryError,
                             ViChar    outErrorElab[]);

ViStatus RsCore_AppendSecondaryError(ViSession     instrSession,
                                     ViStatus      primaryError,
                                     ViStatus      secondaryError,
                                     ViConstString errorElab);

ViStatus RsCore_ClearErrorInfo(ViSession instrSession);

ViStatus RsCore_ParamPositionError(ViInt32 parameterPosition);

ViStatus RsCore_GetErrorCompleteDescription(ViSession          instrSession,
                                            RsCoreErrorMessage errorMessageFnc,
                                            ViPStatus          outErrorCode,
                                            ViInt32            bufferSize,
                                            ViChar             outDescription[]);

ViStatus RsCore_GetSpecificDriverStatusDesc(ViSession              instrSession,
                                            ViStatus               statusCode,
                                            ViChar                 outMessageBuf[],
                                            ViInt32                bufferSize,
                                            RsCoreStringValueTable additionalTableToSearch);

ViStatus RsCore_GenerateInvalidDataTypeError(ViSession      instrSession,
                                             RsCoreDataType dataType,
                                             ViConstString  context);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Instrument Model and Instrument Options ---------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_QueryAndParseIDNstringWithAliases(ViSession     instrSession,
                                                  ViConstString simulationIDNstring,
                                                  ViConstString customScanString,
                                                  ViConstString aliases,
                                                  ViConstString reserved);

ViStatus RsCore_QueryAndParseIDNstring(ViSession     instrSession,
                                       ViConstString simulationIDNstring,
                                       ViConstString customScanString);

ViStatus RsCore_FitsIDNpattern(ViSession     instrSession,
                               ViConstString requiredIdnPattern1,
                               ViConstString requiredIdnPattern2);

ViStatus RsCore_QueryAndParseOPTstring(ViSession     instrSession,
                                       ViConstString simulationOPTstring,
                                       ViInt32       optionsParseMode);

ViStatus RsCore_CheckInstrumentModel(ViSession     instrSession,
                                     ViConstString modelsList);

ViBoolean RsCore_IsInstrumentModel(ViSession     instrSession,
                                   ViConstString modelsList);

ViStatus RsCore_CheckInstrumentOptions(ViSession     instrSession,
                                       ViConstString optionsExpression);

ViBoolean RsCore_HasInstrumentOptions(ViSession     instrSession,
                                      ViConstString optionsExpression);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Attributes - related functions ------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_SetAttributeViReal64(ViSession     instrSession,
                                     ViConstString repCap,
                                     ViUInt32      attributeId,
                                     ViInt32       optionFlag,
                                     ViReal64      value);

ViStatus RsCore_SetAttributeViInt32(ViSession     instrSession,
                                    ViConstString repCap,
                                    ViUInt32      attributeId,
                                    ViInt32       optionFlag,
                                    ViInt32       value);

ViStatus RsCore_SetAttributeViInt64(ViSession     instrSession,
                                    ViConstString repCap,
                                    ViUInt32      attributeId,
                                    ViInt32       optionFlag,
                                    ViInt64       value);

ViStatus RsCore_SetAttributeViString(ViSession     instrSession,
                                     ViConstString repCap,
                                     ViUInt32      attributeId,
                                     ViInt32       optionFlag,
                                     ViConstString value);

ViStatus RsCore_SetAttributeViRawString(ViSession     instrSession,
										ViConstString repCap,
										ViUInt32      attributeId,
										ViInt32       optionFlag,
										ViConstString value);

ViStatus RsCore_SetAttributeViBoolean(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViBoolean     value);

ViStatus RsCore_SetAttributeViSession(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViSession     value);

ViStatus RsCore_SetAttributeViAddress(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViAddr        value);

ViStatus RsCore_GetAttributeViReal64(ViSession     instrSession,
                                     ViConstString repCap,
                                     ViUInt32      attributeId,
                                     ViInt32       optionFlag,
                                     ViPReal64     outValue);

ViStatus RsCore_GetAttributeViInt32(ViSession     instrSession,
                                    ViConstString repCap,
                                    ViUInt32      attributeId,
                                    ViInt32       optionFlag,
                                    ViPInt32      outValue);

ViStatus RsCore_GetAttributeViInt64(ViSession     instrSession,
                                    ViConstString repCap,
                                    ViUInt32      attributeId,
                                    ViInt32       optionFlag,
                                    ViPInt64      outValue);

ViStatus RsCore_GetAttributeViString(ViSession     instrSession,
                                     ViConstString repCap,
                                     ViUInt32      attributeId,
                                     ViInt32       optionFlag,
                                     ViInt32       bufferSize,
                                     ViChar        outValue[]);

ViStatus RsCore_GetAttributeViStringUnknownLen(ViSession     instrSession,
											   ViConstString repCap,
											   ViUInt32      attributeId,
											   ViInt32       optionFlag,
											   ViString*     outValue);

ViStatus RsCore_GetAttributeViRawString(ViSession     instrSession,
										ViConstString repCap,
										ViUInt32      attributeId,
										ViInt32       optionFlag,
										ViInt32       bufferSize,
										ViChar        outValue[]);

ViStatus RsCore_GetAttributeViRawStringUnknownLen(ViSession     instrSession,
												  ViConstString repCap,
												  ViUInt32      attributeId,
												  ViInt32       optionFlag,
												  ViString*     outValue);

ViStatus RsCore_GetAttributeViBoolean(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViPBoolean    outValue);

ViStatus RsCore_GetAttributeViSession(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViPSession    outValue);

ViStatus RsCore_GetAttributeViAddress(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViPAddr       outValue);

ViStatus RsCore_CheckAttributeViReal64(ViSession     instrSession,
                                       ViConstString repCap,
                                       ViUInt32      attributeId,
                                       ViInt32       optionFlag,
                                       ViReal64      value);

ViStatus RsCore_CheckAttributeViInt32(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViInt32       value);

ViStatus RsCore_CheckAttributeViInt64(ViSession     instrSession,
                                      ViConstString repCap,
                                      ViUInt32      attributeId,
                                      ViInt32       optionFlag,
                                      ViInt64       value);

ViStatus RsCore_CheckAttributeViString(ViSession     instrSession,
                                       ViConstString repCap,
                                       ViUInt32      attributeId,
                                       ViInt32       optionFlag,
                                       ViConstString value);

ViStatus RsCore_CheckAttributeViBoolean(ViSession     instrSession,
                                        ViConstString repCap,
                                        ViUInt32      attributeId,
                                        ViInt32       optionFlag,
                                        ViBoolean     value);

ViStatus RsCore_CheckAttributeViSession(ViSession     instrSession,
                                        ViConstString repCap,
                                        ViUInt32      attributeId,
                                        ViInt32       optionFlag,
                                        ViSession     value);

ViStatus RsCore_CheckAttributeViAddress(ViSession     instrSession,
                                        ViConstString repCap,
                                        ViUInt32      attributeId,
                                        ViInt32       optionFlag,
                                        ViAddr        value);

ViStatus RsCore_GetAttributeFlags(ViSession        instrSession,
                                  ViAttr           attributeId,
                                  RsCoreAttrFlags* flags);

ViStatus RsCore_SetAttributeFlags(ViSession       instrSession,
                                  ViAttr          attributeId,
                                  RsCoreAttrFlags flags);

ViStatus RsCore_SetAttributeP2Value(ViSession          instrSession,
                                    RsCoreAttributePtr attr,
                                    void*              value);

ViStatus RsCore_ApplyAttributeDefaults(ViSession instrSession,
                                       ViBoolean updateInherentAttr);

ViStatus RsCore_BuildAttrCommandString(ViSession          instrSession,
                                       RsCoreAttributePtr attr,
                                       ViConstString      repCapsInputString,
                                       ViString*          cmd);

ViStatus RsCore_WriteAttributeCommand(ViSession          instrSession,
                                      RsCoreAttributePtr attr,
                                      ViConstString      command);

ViStatus RsCore_QueryAttributeCommand(ViSession          instrSession,
                                      RsCoreAttributePtr attr,
                                      ViConstString      query,
                                      ViChar             outResponse[]);

ViStatus RsCore_QueryAttributeCommandUnknownLength(ViSession          instrSession,
                                                   RsCoreAttributePtr attr,
                                                   ViConstString      query,
                                                   ViString*          outResponse,
                                                   ViPInt32           outByteCount);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Repeated Capabilities ---------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_BuildRepCapTable(ViSession       instrSession,
                                 RsCoreRepCapPtr repCapTable);

ViStatus RsCore_ResetRepCapTable(ViSession       instrSession,
                                 RsCoreRepCapPtr repCapTable);

ViStatus RsCore_GetRepCapCmdValue(ViSession     instrSession,
                                  ViConstString repCapName,
                                  ViConstString repCaps,
                                  ViInt32       bufferSize,
                                  ViChar        outRepCapCmd[],
                                  ViPBoolean    outFound);

ViStatus RsCore_GetAttributeRepCapName(ViSession     instrSession,
                                       ViUInt32      attributeId,
                                       ViConstString repCapNameId,
                                       ViInt32       index,
                                       ViInt32       bufferSize,
                                       ViChar        outRepCapName[]);

ViStatus RsCore_GetAttributeRepCapNameIds(ViSession instrSession,
                                          ViUInt32  attributeId,
                                          ViInt32   bufferSize,
                                          ViChar    outRepCapNameIds[]);

ViStatus RsCore_GetAttributeRepCapNamesAll(ViSession     instrSession,
                                           ViUInt32      attributeId,
                                           ViConstString repCapNameId,
                                           ViInt32       bufferSize,
                                           ViChar        outRepCapNames[]);

ViStatus RsCore_AddRepCap(ViSession     instrSession,
                          ViConstString repCapNameId,
                          ViConstString repCapName,
                          ViConstString cmdValue);

ViStatus RsCore_RemoveRepCap(ViSession     instrSession,
                             ViConstString repCapNameId,
                             ViConstString repCapName);

ViStatus RsCore_ResetRepCapID(ViSession       instrSession,
                              ViConstString   repCapNameId,
                              RsCoreRepCapPtr repCapTable);

ViStatus RsCore_GetRepCapIdItemsCount(ViSession     instrSession,
                                      ViConstString repCapNameId,
                                      ViInt32*      count);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Range Tables ------------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_FindDiscreteRangeTableNumericValue(ViSession           instrSession,
                                                   RsCoreRangeTablePtr rangeTable,
                                                   ViConstString       cmdString,
                                                   ViPReal64           outNumericValue);

ViStatus RsCore_FindRangeTableCmdStringViReal64(ViSession           instrSession,
                                                RsCoreRangeTablePtr rangeTable,
                                                ViReal64            rangeTableValue,
                                                ViReal64            precision,
                                                ViPChar*            p2cmdString);

ViStatus RsCore_FindRangeTableCmdString(ViSession           instrSession,
                                        RsCoreRangeTablePtr rangeTable,
                                        ViInt32             rangeTableValue,
                                        ViPChar*            p2cmdString);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Instrument ASCII IO -----------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_Write(ViSession     instrSession,
                      ViConstString writeBuffer);

ViStatus RsCore_WriteWithOpc(ViSession     instrSession,
                             ViConstString writeBuffer,
                             ViInt32       timeoutMs);

ViStatus RsCore_WriteViStringArray(ViSession     instrSession,
                                   ViConstString command,
                                   ViString      table[],
                                   ViInt32       indexes[],
                                   ViInt32       arraySize);

ViStatus RsCore_WriteAsciiViInt32Array(ViSession     instrSession,
                                       ViConstString command,
                                       ViInt32       inputIntArray[],
                                       ViInt32       arraySize);

ViStatus RsCore_WriteAsciiViReal64Array(ViSession     instrSession,
                                        ViConstString command,
                                        ViReal64      inputDblArray[],
                                        ViInt32       arraySize);

ViStatus RsCore_WriteAsciiViBooleanArray(ViSession     instrSession,
                                         ViConstString command,
                                         ViBoolean     inputBoolArray[],
                                         ViInt32       arraySize);

ViStatus RsCore_WriteAsciiViReal64ArraysInterleaved(ViSession     instrSession,
                                                    ViConstString command,
                                                    ViInt32       arraySize,
                                                    ViReal64      inputDblArray1[],
                                                    ViReal64      inputDblArray2[],
                                                    ViReal64      inputDblArray3[],
                                                    ViReal64      inputDblArray4[],
                                                    ViReal64      inputDblArray5[],
                                                    ViReal64      inputDblArray6[]);

ViStatus RsCore_WriteAsciiViInt32ArraysInterleaved(ViSession     instrSession,
                                                   ViConstString command,
                                                   ViInt32       arraySize,
                                                   ViInt32       inputIntArray1[],
                                                   ViInt32       inputIntArray2[],
                                                   ViInt32       inputIntArray3[],
                                                   ViInt32       inputIntArray4[],
                                                   ViInt32       inputIntArray5[],
                                                   ViInt32       inputIntArray6[]);

ViStatus RsCore_ReadViStringUnknownLength(ViSession instrSession,
                                          ViString* outResponseString);

ViStatus RsCore_ReadUpToCharacter(ViSession instrSession,
                                  ViChar    stopChar,
                                  ViInt32   bufferSize,
                                  ViBuf     buffer,
                                  ViPInt32  outCount);

ViStatus RsCore_QueryViString(ViSession     instrSession,
                              ViConstString query,
                              ViChar        outResponseString[]);

ViStatus RsCore_QueryViStringShort(ViSession     instrSession,
                                   ViConstString query,
                                   ViChar        outResponseString[]);

ViStatus RsCore_QueryViStringUnknownLength(ViSession     instrSession,
                                           ViConstString query,
                                           ViString*     outResponseString);

ViStatus RsCore_QueryViStringUnknownLengthToUserBuffer(ViSession     instrSession,
                                                       ViConstString query,
                                                       ViInt32       bufferSize,
                                                       ViChar        outResponseString[],
                                                       ViPInt32      outResponseLength);

ViStatus RsCore_QueryCatalog(ViSession     instrSession,
                             ViConstString query,
                             ViInt32       bufferSize,
                             ViChar        outCatalog[],
                             ViPInt32      outElementsCount);

ViStatus RsCore_QueryViStringWithOpc(ViSession     instrSession,
                                     ViConstString query,
                                     ViInt32       timeoutMs,
                                     ViInt32       bufferSize,
                                     ViChar        outResponseString[]);

ViStatus RsCore_QueryViStringUnknownLengthWithOpc(ViSession     instrSession,
                                                  ViConstString query,
                                                  ViInt32       timeoutMs,
                                                  ViString*     outResponseString);

ViStatus RsCore_QueryViStringUnknownLengthToUserBufferWithOpc(
							ViSession     instrSession,
							ViConstString query,
							ViInt32       timeoutMs,
							ViInt32       bufferSize,
							ViChar        outResponseString[],
							ViPInt32      outResponseLength);

ViStatus RsCore_QueryViInt32(ViSession     instrSession,
                             ViConstString query,
                             ViPInt32      outValue);

ViStatus RsCore_QueryViInt32WithOpc(ViSession     instrSession,
                                    ViConstString query,
                                    ViInt32       timeoutMs,
                                    ViPInt32      outValue);

ViStatus RsCore_QueryTupleViInt32(ViSession     instrSession,
                                  ViConstString query,
                                  ViPInt32      outValue1,
                                  ViPInt32      outValue2,
                                  ViPInt32      outValue3,
                                  ViPInt32      outValue4);

ViStatus RsCore_QueryTupleViInt32WithOpc(ViSession     instrSession,
                                         ViConstString query,
                                         ViInt32       timeoutMs,
                                         ViPInt32      outValue1,
                                         ViPInt32      outValue2,
                                         ViPInt32      outValue3,
                                         ViPInt32      outValue4);

ViStatus RsCore_QueryViInt64(ViSession     instrSession,
							 ViConstString query,
							 ViPInt64      outValue);

ViStatus RsCore_QueryViInt64WithOpc(ViSession     instrSession,
									ViConstString query,
									ViInt32       timeoutMs,
									ViPInt64      outValue);

ViStatus RsCore_QueryViReal64(ViSession     instrSession,
                              ViConstString query,
                              ViPReal64     outValue);

ViStatus RsCore_QueryViReal64WithOpc(ViSession     instrSession,
                                     ViConstString query,
                                     ViInt32       timeoutMs,
                                     ViPReal64     outValue);

ViStatus RsCore_QueryTupleViReal64(ViSession     instrSession,
                                   ViConstString query,
                                   ViPReal64     outValue1,
                                   ViPReal64     outValue2,
                                   ViPReal64     outValue3,
                                   ViPReal64     outValue4);

ViStatus RsCore_QueryTupleViReal64WithOpc(ViSession     instrSession,
                                          ViConstString query,
                                          ViInt32       timeoutMs,
                                          ViPReal64     outValue1,
                                          ViPReal64     outValue2,
                                          ViPReal64     outValue3,
                                          ViPReal64     outValue4);

ViStatus RsCore_QueryViBoolean(ViSession     instrSession,
                               ViConstString query,
                               ViPBoolean    outValue);

ViStatus RsCore_QueryViBooleanWithOpc(ViSession     instrSession,
                                      ViConstString query,
                                      ViInt32       timeoutMs,
                                      ViPBoolean    outValue);

ViStatus RsCore_QueryTupleViBoolean(ViSession     instrSession,
                                    ViConstString query,
                                    ViPBoolean    outValue1,
                                    ViPBoolean    outValue2,
                                    ViPBoolean    outValue3,
                                    ViPBoolean    outValue4);

ViStatus RsCore_QueryTupleViBooleanWithOpc(ViSession     instrSession,
                                           ViConstString query,
                                           ViInt32       timeoutMs,
                                           ViPBoolean    outValue1,
                                           ViPBoolean    outValue2,
                                           ViPBoolean    outValue3,
                                           ViPBoolean    outValue4);

ViStatus RsCore_QueryStringIndex(ViSession     instrSession,
                                 ViConstString query,
                                 ViConstString patternsArray[],
                                 ViPInt32      outPatternIdx);

ViStatus RsCore_QueryStringIndexesArray(ViSession     instrSession,
                                        ViConstString query,
                                        ViConstString patternsArray[],
                                        ViPInt32      outPatternIdxArray[],
                                        ViPInt32      outArraySize);

ViStatus RsCore_QueryStringIndexesArrayToUserBuffer(ViSession     instrSession,
                                                    ViConstString query,
                                                    ViConstString patternsArray[],
                                                    ViInt32       userBufferLength,
                                                    ViInt32	      outPatternIdxArray[],
                                                    ViPInt32      outActualArraySize);

ViStatus RsCore_QueryAsciiViReal64Array(ViSession     instrSession,
                                        ViConstString query,
                                        ViPReal64     outDblArray[],
                                        ViPInt32      outArraySize);

ViStatus RsCore_QueryAsciiViInt32Array(ViSession     instrSession,
                                       ViConstString query,
                                       ViPInt32      outIntArray[],
                                       ViPInt32      outArraySize);

ViStatus RsCore_QueryAsciiViBooleanArray(ViSession     instrSession,
                                         ViConstString query,
                                         ViPBoolean    outBoolArray[],
                                         ViPInt32      outArraySize);

ViStatus RsCore_QueryAsciiViBooleanArrayWithOpc(ViSession     instrSession,
                                                ViConstString query,
                                                ViInt32       timeoutMs,
                                                ViPBoolean    outBoolArray[],
                                                ViPInt32      outArraySize);

ViStatus RsCore_QueryAsciiViBooleanArrayToUserBuffer(ViSession     instrSession,
                                                     ViConstString query,
                                                     ViInt32       userBufferLength,
                                                     ViBoolean     outUserBuffer[],
                                                     ViPInt32      outActualPointsCount);

ViStatus RsCore_QueryAsciiViBooleanArrayToUserBufferWithOpc(ViSession     instrSession,
                                                            ViConstString query,
                                                            ViInt32       timeoutMs,
                                                            ViInt32       userBufferLength,
                                                            ViBoolean     outUserBuffer[],
                                                            ViPInt32      outActualPointsCount);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Instrument Binary Data IO -----------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

ViStatus RsCore_WriteBinaryDataBlock(ViSession     instrSession,
                                     ViConstString command,
                                     ViBuf         data,
                                     ViInt64       dataSize);

ViStatus RsCore_QueryBinaryDataBlock(ViSession     instrSession,
                                     ViConstString query,
                                     ViBoolean     errorIfNotBinDataBlock,
                                     ViPBoolean    outIsBinDataBlock,
                                     ViPByte       outputBuffer[],
                                     ViPInt64      outByteCount);

ViStatus RsCore_QueryBinaryDataBlockWithOpc(ViSession     instrSession,
                                            ViConstString query,
                                            ViBoolean     errorIfNotBinDataBlock,
                                            ViInt32       timeoutMs,
                                            ViPBoolean    outIsBinDataBlock,
                                            ViPByte       outputBuffer[],
                                            ViPInt64      outByteCount);

ViStatus RsCore_QueryBinaryDataBlockToFile(ViSession     instrSession,
                                           ViConstString query,
                                           ViConstString filename,
                                           ViInt32       fileAction);

ViStatus RsCore_WriteBinaryDataFromFile(ViSession     instrSession,
                                        ViConstString command,
                                        ViConstString sourceFile);

ViStatus RsCore_QueryFloatArray(ViSession     instrSession,
                                ViConstString query,
                                ViPReal64     outDblArray[],
                                ViPInt32      outArraySize);

ViStatus RsCore_QueryFloatArrayWithOpc(ViSession     instrSession,
                                       ViConstString query,
                                       ViInt32       timeoutMs,
                                       ViPReal64     outDblArray[],
                                       ViPInt32      outArraySize);

ViStatus RsCore_QueryMixedFloatArray(ViSession     instrSession,
                                     ViConstString query,
                                     ViInt32       asciiMaxLen,
                                     ViChar        asciiDelimiter,
                                     ViChar        outAsciiPart[],
                                     ViPReal64     outDblArray[],
                                     ViPInt32      outArraySize);

ViStatus RsCore_QueryMixedFloatArrayWithOpc(ViSession     instrSession,
                                            ViConstString query,
                                            ViInt32       asciiMaxLen,
                                            ViChar        asciiDelimiter,
                                            ViChar        outAsciiPart[],
                                            ViInt32       timeoutMs,
                                            ViPReal64     outDblArray[],
                                            ViPInt32      outArraySize);

ViStatus RsCore_QueryFloatArrayToUserBuffer(ViSession     instrSession,
                                            ViConstString query,
                                            ViInt32       userBufferLength,
                                            ViReal64      outUserBuffer[],
                                            ViPInt32      outActualPointsCount);

ViStatus RsCore_QueryFloatArrayToUserBufferWithOpc(ViSession     instrSession,
                                                   ViConstString query,
                                                   ViInt32       timeoutMs,
                                                   ViInt32       userBufferLength,
                                                   ViReal64      outUserBuffer[],
                                                   ViPInt32      outActualPointsCount);
												   
ViStatus RsCore_QueryFloatArraysInterleavedToUserBuffer(ViSession     instrSession,
                                                        ViConstString query,
                                                        ViInt32       arraySizes,
                                                        ViPInt32      outActualPointsCount,
                                                        ViReal64      outUserBuffer1[],
                                                        ViReal64      outUserBuffer2[],
                                                        ViReal64      outUserBuffer3[],
                                                        ViReal64      outUserBuffer4[],
                                                        ViReal64      outUserBuffer5[]);												   

ViStatus RsCore_QueryIntegerArray(ViSession     instrSession,
                                  ViConstString query,
                                  ViPInt32      outInt32Array[],
                                  ViPInt32      outArraySize);

ViStatus RsCore_QueryIntegerArrayWithOpc(ViSession     instrSession,
                                         ViConstString query,
                                         ViInt32       timeoutMs,
                                         ViPInt32      outInt32Array[],
                                         ViPInt32      outArraySize);

ViStatus RsCore_QueryMixedIntegerArray(ViSession     instrSession,
                                       ViConstString query,
                                       ViInt32       asciiMaxLen,
                                       ViChar        asciiDelimiter,
                                       ViChar        outAsciiPart[],
                                       ViPInt32      outInt32Array[],
                                       ViPInt32      outArraySize);

ViStatus RsCore_QueryMixedIntegerArrayWithOpc(ViSession     instrSession,
                                              ViConstString query,
                                              ViInt32       asciiMaxLen,
                                              ViChar        asciiDelimiter,
                                              ViChar        outAsciiPart[],
                                              ViInt32       timeoutMs,
                                              ViPInt32      outInt32Array[],
                                              ViPInt32      outArraySize);

ViStatus RsCore_QueryIntegerArrayToUserBuffer(ViSession     instrSession,
                                              ViConstString query,
                                              ViInt32       userBufferLength,
                                              ViInt32       outUserBuffer[],
                                              ViPInt32      outActualPointsCount);

ViStatus RsCore_QueryIntegerArrayToUserBufferWithOpc(ViSession     instrSession,
                                                     ViConstString query,
                                                     ViInt32       timeoutMs,
                                                     ViInt32       userBufferLength,
                                                     ViInt32       outUserBuffer[],
                                                     ViPInt32      outActualPointsCount);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Instrument Helper IO Functions ------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_ResetRegistersEseSre(ViSession instrSession);

ViStatus RsCore_ErrorQuery(ViSession  instrSession,
                           ViPInt32   outErrorCode,
                           ViChar     outErrorMessage[],
                           ViPBoolean outErrorFlag);

ViStatus RsCore_ErrorQueryAll(ViSession instrSession,
                              ViPInt32  outErrorCode,
                              ViInt32   bufferSize,
                              ViChar    outErrors[]);

ViStatus RsCore_SelfTest(ViSession instrSession,
                         ViPInt16  outSelfTestResult,
                         ViInt32   bufferSize,
                         ViChar    outSelfTestMessage[]);

ViStatus RsCore_CheckStatus(ViSession instrSession,
                            ViStatus  errorBefore);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Default Core Callback Routines ------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

ViStatus RsCore_ReadCallback(ViSession          instrSession,
                             ViConstString      repCapName,
                             RsCoreAttributePtr attr);

ViStatus RsCore_WriteCallback(ViSession          instrSession,
                              ViConstString      repCapName,
                              RsCoreAttributePtr attr,
                              void*              value);

ViStatus RsCore_CheckCallback(ViSession          instrSession,
                              ViConstString      repCapName,
                              RsCoreAttributePtr attr,
                              void*              value);

ViStatus RsCore_CoerceCallback(ViSession          instrSession,
                               ViConstString      repCapName,
                               RsCoreAttributePtr attr,
                               void*              value);

ViStatus RsCore_RangeTableCallback(ViSession           instrSession,
                                   ViConstString       repCapName,
                                   RsCoreAttributePtr  attr,
                                   RsCoreRangeTablePtr rangeTablePtr);

ViStatus RsCore_WaitForOpcCallback(ViSession instrSession,
                                   ViInt32   opcTimeoutMs);

ViStatus RsCore_CheckStatusCallback(ViSession instrSession,
                                    ViStatus  errorBefore);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Range Checking ----------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViStatus RsCore_InvalidViInt32Range(ViSession instrSession,
                                    ViInt32   value,
                                    ViInt32   min,
                                    ViInt32   max);

ViStatus RsCore_InvalidViInt32RangeMin(ViSession instrSession,
                                       ViInt32   value,
                                       ViInt32   min);

ViStatus RsCore_InvalidViInt32RangeMax(ViSession instrSession,
                                       ViInt32   value,
                                       ViInt32   max);

ViStatus RsCore_InvalidViInt32Value(ViSession instrSession,
                                    ViInt32   value);

ViStatus RsCore_InvalidViInt32ArrayRange(ViSession instrSession,
                                         ViInt32   values[],
                                         ViInt32   arraySize,
                                         ViInt32   min,
                                         ViInt32   max);

ViStatus RsCore_InvalidViInt64Range(ViSession instrSession,
                                    ViInt64   value,
                                    ViInt64   min,
                                    ViInt64   max);

ViStatus RsCore_InvalidViInt64ArrayRange(ViSession instrSession,
                                         ViInt64   values[],
                                         ViInt32   arraySize,
                                         ViInt64   min,
                                         ViInt64   max);

ViStatus RsCore_InvalidViUInt32Range(ViSession instrSession,
                                     ViUInt32  value,
                                     ViUInt32  min,
                                     ViUInt32  max);

ViStatus RsCore_InvalidViUInt32ArrayRange(ViSession instrSession,
                                          ViUInt32  values[],
                                          ViInt32   arraySize,
                                          ViUInt32  min,
                                          ViUInt32  max);

ViStatus RsCore_InvalidViReal64Range(ViSession instrSession,
                                     ViReal64  value,
                                     ViReal64  min,
                                     ViReal64  max);

ViStatus RsCore_InvalidViReal64RangeMin(ViSession instrSession,
                                        ViReal64  value,
                                        ViReal64  min);

ViStatus RsCore_InvalidViReal64RangeMax(ViSession instrSession,
                                        ViReal64  value,
                                        ViReal64  max);

ViStatus RsCore_InvalidViReal64Value(ViSession instrSession,
                                     ViReal64  value);

ViStatus RsCore_InvalidViReal64ArrayRange(ViSession instrSession,
                                          ViReal64  values[],
                                          ViInt32   arraySize,
                                          ViReal64  min,
                                          ViReal64  max);

ViStatus RsCore_InvalidViBooleanRange(ViSession instrSession,
                                      ViBoolean value);

ViStatus RsCore_InvalidViBooleanArrayRange(ViSession instrSession,
                                           ViBoolean values[],
                                           ViInt32   arraySize);

ViStatus RsCore_InvalidNullPointer(ViSession instrSession,
                                   void*     parameter);

ViStatus RsCore_InvalidStringLength(ViSession instrSession,
                                    ViChar    *string,
                                    ViInt32   minLen,
                                    ViInt32   maxLen);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Conversions -------------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViBoolean RsCore_Convert_String_To_Boolean(ViConstString string);

ViInt32 RsCore_Convert_String_To_ViInt32(ViConstString value);
ViInt64 RsCore_Convert_String_To_ViInt64(ViConstString value);

ViReal64 RsCore_Convert_String_To_ViReal64(ViConstString value);

ViInt32 RsCore_Convert_ViReal64_To_String(ViReal64 value,
                                          ViInt32  bufferSize,
                                          ViChar   outBuffer[]);

ViBoolean RsCore_Convert_HexaPattern_To_BinPattern(ViConstString hexaPattern,
                                                   ViInt32       bufferSize,
                                                   ViChar        outBinPattern[]);

ViInt64 RsCore_Convert_BinaryString_To_ViInt64(ViConstString binPattern);

ViStatus RsCore_Convert_String_To_ViReal64Array(ViSession     instrSession,
                                                ViConstString inputString,
                                                ViPReal64     outDblArray[],
                                                ViPInt32      outArraySize);

ViStatus RsCore_Convert_ViReal64array_To_String(ViSession     instrSession,
                                                ViReal64      inputDblArray[],
                                                ViInt32       arraySize,
                                                ViConstString beforeString,
                                                ViString*     outResultString);

ViStatus RsCore_Convert_ViReal64ArraysInterleaved_To_String(ViSession     instrSession,
                                                            ViInt32       arraySizes,
                                                            ViReal64      inputDblArray1[],
                                                            ViReal64      inputDblArray2[],
                                                            ViReal64      inputDblArray3[],
                                                            ViReal64      inputDblArray4[],
                                                            ViReal64      inputDblArray5[],
                                                            ViReal64      inputDblArray6[],
                                                            ViConstString beforeString,
                                                            ViString*     outResultString);

ViStatus RsCore_Convert_String_To_ViInt32Array(ViSession     instrSession,
                                               ViConstString inputString,
                                               ViPInt32      outIntArray[],
                                               ViPInt32      outArraySize);

ViStatus RsCore_Convert_ViInt32array_To_String(ViSession     instrSession,
                                               ViInt32       inputIntArray[],
                                               ViInt32       arraySize,
                                               ViConstString beforeString,
                                               ViString*     outResultString);

ViStatus RsCore_Convert_ViInt32ArraysInterleaved_To_String(ViSession     instrSession,
                                                           ViInt32       arraySizes,
                                                           ViInt32       inputIntArray1[],
                                                           ViInt32       inputIntArray2[],
                                                           ViInt32       inputIntArray3[],
                                                           ViInt32       inputIntArray4[],
                                                           ViInt32       inputIntArray5[],
                                                           ViInt32       inputIntArray6[],
                                                           ViConstString beforeString,
                                                           ViString*     outResultString);

ViStatus RsCore_Convert_String_To_ViBooleanArray(ViSession     instrSession,
                                                 ViConstString inputString,
                                                 ViPBoolean    outBoolArray[],
                                                 ViPInt32      outArraySize);

ViStatus RsCore_Convert_ViBooleanArray_To_String(ViSession     instrSession,
                                                 ViBoolean     inputBoolArray[],
                                                 ViInt32       arraySize,
                                                 ViConstString beforeString,
                                                 ViString*     outResultString);

ViStatus RsCore_Convert_BinaryDataBlock_To_Float32Array(ViSession instrSession,
                                                        ViBuf     inputBinDataBlock,
                                                        ViInt32   inputBinDataSize,
                                                        ViPReal64 outDblArray[],
                                                        ViPInt32  outArraySize,
                                                        ViBoolean swapEndianness);

ViStatus RsCore_Convert_Float32Array_To_BinaryDataBlock(ViSession instrSession,
                                                        ViReal64  inputDlbArray[],
                                                        ViInt32   inputArraySize,
                                                        ViPByte   outBinData[],
                                                        ViPInt32  outDataSize,
                                                        ViBoolean swapEndianness);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Utility functions -------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/
ViInt32 RsCore_TrimString(ViString text,
                          ViInt32  mode);

ViStatus RsCore_ParseCatalog(ViConstString inputCatalog,
                             ViInt32       bufferSize,
                             ViChar        outCatalog[],
                             ViPInt32      outElementsCount);

ViInt32 RsCore_ReplaceString(ViChar        string[],
                             ViInt32       bufferSize,
                             ViConstString searchString,
                             ViConstString replaceString,
                             ViBoolean     replaceAll);

ViStatus RsCore_SwapEndianness(void* block, ViInt32 arrayElementsCount, ViInt32 elementSize);
ViInt32 RsCore_FindStringIndex(ViConstString patternsArray[],
                               ViConstString stringToFind);

ViStatus RsCore_FindStringIndexWithError(ViSession     instrSession,
                                         ViConstString patternsArray[],
                                         ViConstString stringToFind,
                                         ViPInt32      outIdx);

ViInt32 RsCore_GetElementsCount(ViConstString string,
                                ViChar        delimiter);

ViStatus RsCore_GetTokenAtIndex(ViConstString inputString,
                                ViChar        delimiter,
                                ViInt32       idx,
                                ViChar        outToken[],
                                ViInt32       bufferSize,
                                ViPInt32      outTokenOffset);

ViStatus RsCore_GetIndexOfToken(ViConstString inputString,
                                ViChar        delimiter,
                                ViConstString tokenToFind,
                                ViPInt32      outFoundIdx,
                                ViPInt32      outTokenOffset);

ViBoolean RsCore_StrcatMaxLen(ViChar        target[],
                              ViInt32       bufferSize,
                              ViConstString append1,
                              ViConstString append2,
                              ViConstString append3);

ViStatus RsCore_StrCatDynamicString(ViSession     instrSession,
                                    ViString*     target,
                                    ViConstString append1,
                                    ViConstString append2,
                                    ViConstString append3);

ViStatus RsCore_StrCatDynamicViInt32(ViSession     instrSession,
                                     ViString*     target,
                                     ViConstString append1,
                                     ViInt32       valueToAppend,
                                     ViConstString append2);

ViStatus RsCore_StrCatDynamicViInt64(ViSession     instrSession,
                                     ViString*     target,
                                     ViConstString append1,
                                     ViInt64       valueToAppend,
                                     ViConstString append2);

ViStatus RsCore_StrCatDynamicViReal64(ViSession     instrSession,
                                      ViString*     target,
                                      ViConstString append1,
                                      ViReal64      valueToAppend,
                                      ViConstString append2);

ViStatus RsCore_StrCatDynamicViBoolean(ViSession     instrSession,
                                       ViString*     target,
                                       ViConstString append1,
                                       ViBoolean     valueToAppend,
                                       ViConstString append2);

ViString RsCore_AppendToCsvString(ViChar        target[],
                                  ViString      delimiter,
                                  ViInt32       targetBufferSize,
                                  ViConstString element);

void RsCore_Delay(ViReal64 numberOfSeconds);

ViStatus RsCore_CopyToUserBufferBinData(ViBuf   userBuffer,
                                        ViInt32 userBufferSize,
                                        ViBuf   sourceData,
                                        ViInt64 dataSize);

ViStatus RsCore_CopyToUserBufferViReal64Array(ViReal64 outUserBuffer[],
                                              ViInt32  userBufferSize,
                                              ViReal64 sourceArray[],
                                              ViInt64  dataSize);

ViStatus RsCore_CopyToUserBufferViInt32Array(ViInt32 outUserBuffer[],
                                             ViInt32 userBufferSize,
                                             ViInt32 sourceArray[],
                                             ViInt64 dataSize);

ViStatus RsCore_DecimateViReal64ArrayToUserBuffers(ViReal64 sourceArray[],
                                                   ViInt32  sourceArraySize,
                                                   ViInt32  userBufferSizes,
                                                   ViPInt32 outActualPointsCount,
                                                   ViReal64 outUserBuffer1[],
                                                   ViReal64 outUserBuffer2[],
                                                   ViReal64 outUserBuffer3[],
                                                   ViReal64 outUserBuffer4[],
                                                   ViReal64 outUserBuffer5[],
                                                   ViReal64 outUserBuffer6[]);

ViStatus RsCore_DecimateViInt32ArrayToUserBuffers(ViInt32  sourceArray[],
                                                  ViInt32  sourceArraySize,
                                                  ViInt32  userBufferSizes,
                                                  ViPInt32 outActualPointsCount,
                                                  ViInt32  outUserBuffer1[],
                                                  ViInt32  outUserBuffer2[],
                                                  ViInt32  outUserBuffer3[],
                                                  ViInt32  outUserBuffer4[],
                                                  ViInt32  outUserBuffer5[],
                                                  ViInt32  outUserBuffer6[]);

ViStatus RsCore_DecimateViBooleanArrayToUserBuffers(ViBoolean sourceArray[],
                                                    ViInt32   sourceArraySize,
                                                    ViInt32   userBufferSizes,
                                                    ViPInt32  outActualPointsCount,
                                                    ViBoolean outUserBuffer1[],
                                                    ViBoolean outUserBuffer2[],
                                                    ViBoolean outUserBuffer3[],
                                                    ViBoolean outUserBuffer4[],
                                                    ViBoolean outUserBuffer5[],
                                                    ViBoolean outUserBuffer6[]);

ViStatus RsCore_CopyToUserBufferViBooleanArray(ViBoolean outUserBuffer[],
                                               ViInt32   userBufferSize,
                                               ViBoolean sourceArray[],
                                               ViInt64   dataSize);

ViStatus RsCore_CopyToUserBufferAsciiData(ViChar        outUserBuffer[],
                                          ViInt32       userBufferSize,
                                          ViConstString sourceString);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Special Write/Read callbacks --------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

ViStatus RsCore_SpecialCallback_SurroundParamWrite(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr,
                                                   ViConstString      beforeParam,
                                                   void*              value,
                                                   ViConstString      afterParam);

ViStatus RsCore_SpecialCallback_AnyQuotedParamRead(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr);

ViStatus RsCore_SpecialCallback_CustomCommandWrite(ViSession          instrSession,
                                                   ViConstString      repCapName,
                                                   RsCoreAttributePtr attr,
                                                   ViConstString      customCmd,
                                                   void*              value);

ViStatus RsCore_SpecialCallback_CustomCommandRead(ViSession          instrSession,
                                                  ViConstString      repCapName,
                                                  RsCoreAttributePtr attr,
                                                  ViConstString      customCmd);

ViStatus RsCore_SpecialCallback_HexPatternRead(ViSession          instrSession,
                                               ViConstString      repCapName,
                                               RsCoreAttributePtr attr);

ViStatus RsCore_SpecialCallback_HexPatternWrite(ViSession          instrSession,
                                                ViConstString      repCapName,
                                                RsCoreAttributePtr attr,
                                                void*              value);

ViStatus RsCore_SpecialCallback_HexNumberRead(ViSession          instrSession,
                                              ViConstString      repCapName,
                                              RsCoreAttributePtr attr);

ViStatus RsCore_SpecialCallback_HexNumberWrite(ViSession          instrSession,
                                               ViConstString      repCapName,
                                               RsCoreAttributePtr attr,
                                               void*              value);

ViStatus RsCore_SpecialCallback_BinPatternRead(ViSession          instrSession,
                                               ViConstString      repCapName,
                                               RsCoreAttributePtr attr);

ViStatus RsCore_SpecialCallback_BinPatternWrite(ViSession          instrSession,
                                                ViConstString      repCapName,
                                                RsCoreAttributePtr attr,
                                                void*              value);

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- Misc --------------------------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

#define Rs_Decimalize(x)         (((x>>8)*100)+(((x >> 4) & 0xF)*10)+(x & 0xF))

#if defined (_CVI_)
    #define RS_COMPILER_NAME        "CVI"
    #define RS_COMPILER_VER_NUM     ((_CVI_)/100.0)
#elif defined(__WATCOMC__)
    #define RS_COMPILER_NAME        "Watcom"
    #define RS_COMPILER_VER_NUM     ((__WATCOMC__)/100.0)
#elif defined(_MSC_VER)
#define RS_COMPILER_NAME        "MSVC"
#define RS_COMPILER_VER_NUM     ((_MSC_VER - 600)/100.0)
#elif defined(__BORLANDC__)
    #define RS_COMPILER_NAME        "Borland"
    #define RS_COMPILER_VER_NUM     ((Rs_Decimalize(__BORLANDC__))/100.0)
#elif defined(__SC__)
    #define RS_COMPILER_NAME        "Symantec"
    #define RS_COMPILER_VER_NUM     ((Rs_Decimalize(__SC__))/100.0)
#elif defined(__SUNPRO_C)
    #define RS_COMPILER_NAME        "Sun C"
    #define RS_COMPILER_VER_NUM     ((Rs_Decimalize(__SUNPRO_C))/100.0)
#else
    #define RS_COMPILER_NAME        "Unknown"
    #define RS_COMPILER_VER_NUM     1.0
#endif

/******************************************************************************************************
------------------------------------------------------------------------------------------------------*
---- End RsCore Include FILE -------------------------------------------------------------------------*
------------------------------------------------------------------------------------------------------*
******************************************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif  /* __RS_CORE_HEADER */

