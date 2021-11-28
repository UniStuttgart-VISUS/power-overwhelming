/*****************************************************************************
 *
 *  Rohde&Schwarz Instrument Driver Core Include File (Non-exported)
 *
 *****************************************************************************/

#ifndef __RS_CORE_HEADER
#define __RS_CORE_HEADER

#include <visa.h>
#include <visatype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Useful constants --------------------------------------------------------*
 *****************************************************************************/
/* Macro */
#define ATTRLIST(variable_name,prefix)\
    variable_name = (RsAttrPropertiesPtr *) prefix##_RsAttrPropertiesList
#define REPCAPTABLE(variable_name,prefix)\
    variable_name = (RsRepCapPtr) prefix##_RsRepCapTable    
    
/* Version Info */

#define RS_ENGINE_REVISION                      "Rev 2.43, 02/2016"
#define RS_ENGINE_MAJOR_VERSION                 2L
#define RS_ENGINE_MINOR_VERSION                 43

/* Misc */

#define RS_MAX_MESSAGE_LEN                      255
#define RS_MAX_MESSAGE_BUF_SIZE                 4096
#define RS_MAX_ATTR_RCAPS                       10 /* Max number of repeated capability names per attribute */

/*****************************************************************************
 *- Constants for the Rs_ReadToFile function --------------------------------*
 *****************************************************************************/

#define RS_VAL_TRUNCATE                         1
#define RS_VAL_APPEND                           2

/*****************************************************************************
 *- Error constants ---------------------------------------------------------*
 *****************************************************************************/

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

/*****************************************************************************/
/*= Base values for attribute contants.                             ======== */
/*= A private attribute is one that is defined for use within       ======== */
/*= that module and is not exported via an include file.            ======== */
/*****************************************************************************/

#define RS_ATTR_BASE                    1000000
#define RS_ENGINE_PRIVATE_ATTR_BASE     (RS_ATTR_BASE +  00000)   /* base for private attributes of the RS engine */
#define RS_ENGINE_PUBLIC_ATTR_BASE      (RS_ATTR_BASE +  50000)   /* base for public attributes of the RS engine */
#define RS_SPECIFIC_PRIVATE_ATTR_BASE   (RS_ATTR_BASE + 100000)   /* base for private attributes of specific drivers */
#define RS_SPECIFIC_PUBLIC_ATTR_BASE    (RS_ATTR_BASE + 150000)   /* base for public attributes of specific drivers */
#define RS_CLASS_PRIVATE_ATTR_BASE      (RS_ATTR_BASE + 200000)   /* base for private attributes of class drivers */
#define RS_CLASS_PUBLIC_ATTR_BASE       (RS_ATTR_BASE + 250000)   /* base for public attributes of specific drivers */

/*****************************************************************************/
/*= Public RS engine attributes                                     ======== */
/*= The data type of each attribute is listed, followed by the      ======== */
/*= default value or a remark.                                      ======== */
/*= Note:  "hidden" means not readable or writable by the end-user. ======== */
/*****************************************************************************/

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
#define RS_ATTR_SPECIFIC_DRIVER_LOCATOR                     /* ViString, not writable */        (RS_ENGINE_PUBLIC_ATTR_BASE + 303)  /* the pathnname of the specific driver code module; from the configuration file */
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

#define RS_ATTR_INSTRUMENT_MANUFACTURER                     /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 511)
#define RS_ATTR_INSTRUMENT_MODEL                            /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 512)
#define RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                /* ViString, not user-writable */   (RS_ENGINE_PUBLIC_ATTR_BASE + 510)
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

#define RS_ATTR_OPC_CALLBACK                                /* ViAddr,    hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 602)  /* see Rs_OPCCallbackPtr typedef */
#define RS_ATTR_CHECK_STATUS_CALLBACK                       /* ViAddr,    hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 603)  /* see Rs_CheckStatusCallbackPtr typedef */
#define RS_ATTR_OPC_TIMEOUT                                 /* ViInt32,   hidden */             (RS_ENGINE_PUBLIC_ATTR_BASE + 1001)

/*****************************************************************************
 *- Macros for checking for errors. -----------------------------------------*
 *- The checkErr and viCheckErr macros discard warnings. --------------------*
 *- The checkWarn and viCheckWarn macros preserve warnings. -----------------*
 *****************************************************************************/

/*- checkAlloc(pointer) -*/
/* If pointer is VI_NULL, assign VI_ERROR_ALLOC to the error variable and
   jump to the Error label. */

#ifndef checkAlloc
#define checkAlloc(fCall)    if ((fCall) == 0) \
                                 {error = VI_ERROR_ALLOC; goto Error;}
#endif

/*- checkErr(status) -*/
/* Assign status to the error variable. If status is positive,
   coerce the error variable to zero. If status is negative,
   jump to the Error label. */

#ifndef checkErr
#define checkErr(fCall)      error = (fCall);\
                             if (error < 0)\
                                 {goto Error;}
#endif

/*- checkWarn(status) -*/
/* Assign status to the error variable. If negative, jump to the Error label. */

#ifndef checkWarn
#define checkWarn(fCall)     if (error = (fCall), error < 0) \
                                 {goto Error;}  else
#endif

/*- viCheckAlloc(pointer) -*/
/* If pointer is VI_NULL, assign VI_ERROR_ALLOC to the error variable,
   call Rs_SetErrorInfo with VI_ERROR_ALLOC as the primary error code,
   and jump to the Error label. */

#ifndef viCheckAlloc
#define viCheckAlloc(fCall)  if ((fCall) == 0) \
                                 {error = VI_ERROR_ALLOC; Rs_SetErrorInfo(instrSession, VI_FALSE, error, 0, ""); goto Error;}
#endif

/*- viCheckErr(status) -*/
/* Assign status to the error variable. If status is positive,
   coerce the error variable to zero. If status is negative,
   pass it to Rs_SetErrorInfo and jump to the Error label. */

#ifndef viCheckErr
#define viCheckErr(fCall)    error = (fCall);\
                             if (error < 0)\
                                 {(void)Rs_SetErrorInfo(instrSession, VI_FALSE, error, 0, ""); goto Error;}
#endif

/*- viCheckErrElab(status, elabString) -*/
/* Assign status to the error variable. If status is positive,
   coerce the error variable to zero. If status is negative,
   pass it and elabString to Rs_SetErrorInfo and jump to the Error label. */

#ifndef viCheckErrElab
#define viCheckErrElab(fCall, elab) error = (fCall);\
                             if (error < 0) \
                                 {Rs_SetErrorInfo(instrSession, VI_FALSE, error, 0, elab); goto Error;}
#endif

/*- viCheckParm(status, parameterPosition, parameterName) -*/
/* Assign status to the error variable. If status is positive,
   coerce the error variable to zero. If status is negative,
   do the following:

   - Convert parameterPosition into one of the VXIplug&play error
   codes for invalid parameters, and pass it as the secondary
   error code to Rs_SetErrorInfo. Pass status as the primary
   error code, and pass parameterName as the error elaboration.
   - Jump to the Error label. */

#ifndef viCheckParm
#define viCheckParm(fCall, parameterPosition, parameterName) \
                             error = (fCall);\
                             if (error != 0) \
                                 {Rs_SetErrorInfo(instrSession, VI_TRUE, error, Rs_ParamPositionError(parameterPosition), parameterName); goto Error;}
#endif

/*- viCheckWarn(status) -*/
/* Assign status to error. If status is nonzero, pass it to
   Rs_SetErrorInfo. If status is negative, jump to the Error label.

   Notice that the checkWarn and viCheckWarn macros preserve
   warnings whereas the other viCheck macros discard them. Also,
   viCheckWarn calls Rs_SetErrorInfo on both warnings and errors,
   whereas the other macros call Rs_SetErrorInfo only on errors. */

#ifndef viCheckWarn
#define viCheckWarn(fCall)   if (error = (fCall), (error ? Rs_SetErrorInfo(instrSession, VI_FALSE, error, 0, VI_NULL) : 0), error < 0) \
                                 {goto Error;}  else
#endif

/*****************************************************************************/
/*- Typedefs and related constants for the range tables ---------------------*/
/*****************************************************************************/

/* Defined values for the type of RsRangeTable */

#define RS_VAL_DISCRETE         0   /* Discrete set - discreteOrMinValue, and cmdString (or cmdValue) fields used */
#define RS_VAL_RANGED           1   /* Ranged value - discreteOrMinValue, maxValue, and cmdString (or cmdValue) fields used */
#define RS_VAL_COERCED          2   /* Coerced value - discreteOrMinValue, maxValue, coercedValue, and cmdString (or cmdValue) fields used */

/* RsRangeTable contains an array of RsRangeTableEntry structures */

typedef struct
    {
    ViReal64                    discreteOrMinValue;
    ViReal64                    maxValue;
    ViReal64                    coercedValue;
    ViString                    cmdString;  /* optional */
    ViInt32                     cmdValue;   /* indicates end of range table */
    } RsRangeTableEntry;

typedef struct
    {
    ViInt32                     type;
    ViBoolean                   hasMin;
    ViBoolean                   hasMax;
    ViString                    customInfo;
    RsRangeTableEntry           *rangeValues;
        /* the end of rangeValues[] is marked by the entry  */
        /* RS_RANGE_TABLE_LAST_ENTRY                       */
    } RsRangeTable;

typedef RsRangeTable*           RsRangeTablePtr;

#define RS_RANGE_TABLE_END_STRING      NULL  /* The value for the command string of the last entry in an RsRangeTable */
#define RS_RANGE_TABLE_END_VALUE       -999999
#define RS_RANGE_TABLE_LAST_ENTRY      1.0E308, 1.0E308, 1.0E308, RS_RANGE_TABLE_END_STRING, RS_RANGE_TABLE_END_VALUE  /* Marks the last entry in an RsRangeTable */
									   
/*****************************************************************************/
/*- Typedefs for string-value tables ----------------------------------------*/
/*****************************************************************************/

typedef struct
    {
    ViInt32                     value;
    ViString                    string;
    } RsStringValueEntry;

typedef RsStringValueEntry RsStringValueTable[];

/*****************************************************************************
 *- String Value Pair -------------------------------------------------------*
 *****************************************************************************/

typedef struct
    {
    ViInt32                     value;
    ViChar                      string[RS_MAX_MESSAGE_BUF_SIZE];
    } RsStringValuePair;

/*****************************************************************************/
/*- Typedef and related constants for the attribute flags. The flags --------*/
/*- determine how the attributes operate. -----------------------------------*/
/*****************************************************************************/

typedef ViInt32                                 RsAttrFlags;

#define RS_VAL_NOT_SUPPORTED                    (1L << 0)  /* attribute automatically returns RS_ERROR_ATTRIBUTE_NOT_SUPPORTED when Set/Get/Checked/Invalidated */
#define RS_VAL_NOT_READABLE                     (1L << 1)  /* attribute cannot be Got */
#define RS_VAL_NOT_WRITABLE                     (1L << 2)  /* attribute cannot be Set */
#define RS_VAL_NOT_USER_READABLE                (1L << 3)  /* attribute cannot be Got by end-user */
#define RS_VAL_NOT_USER_WRITABLE                (1L << 4)  /* attribute cannot be Set by end-user */
#define RS_VAL_NEVER_CACHE                      (1L << 5)  /* always write/read to set/get attribute, i.e., never use a cached value, regardless of the state of RS_ATTR_CACHE */
#define RS_VAL_ALWAYS_CACHE                     (1L << 6)  /* specifies to always cache the value, regardless of the state of RS_ATTR_CACHE */
#define RS_VAL_WAIT_TO_CONTINUE			(1L << 7)  /* prevents servicing of the subsequent commands until all preceding commands have been executed and all signals have settled */
#define RS_VAL_FLUSH_ON_WRITE                   (1L << 9)  /* send RS_MSG_FLUSH to the BufferIOCallback (which by default calls viFlush) after the write callback */
#define RS_VAL_MULTI_CHANNEL                    (1L << 10) /* specified when the attribute is added. If set, the attribute has a separate value for each channel */
#define RS_VAL_COERCEABLE_ONLY_BY_INSTR         (1L << 11) /* specifies that the instrument coerces the attribue value in a way that the driver cannot anticipate in software. Do NOT use this flag UNLESS ABSOLUTELY NECESSARY !!! */
#define RS_VAL_WAIT_FOR_OPC_BEFORE_READS        (1L << 12) /* specifies to wait for operation complete before reads */
#define RS_VAL_WAIT_FOR_OPC_AFTER_WRITES        (1L << 13) /* specifies to wait for operation complete after writes */
#define RS_VAL_USE_CALLBACKS_FOR_SIMULATION     (1L << 14) /* specifies to call the read and write callbacks even in simulation mode */
#define RS_VAL_DONT_CHECK_STATUS                (1L << 15) /* specifies to not call the checkStatus callback even when RS_ATTR_QUERY_INSTR_STATUS is VI_TRUE */

#define RS_VAL_HIDDEN                           (RS_VAL_NOT_USER_READABLE | RS_VAL_NOT_USER_WRITABLE)

/*****************************************************************************
 *- Constants for optionFlags argument to Set/Check/Get callback functions --*
 *****************************************************************************/

/* RS_VAL_DIRECT_USER_CALL applies to Set/Check/Get;
    if 1, then: the RS_VAL_NOT_USER_READABLE/WRITEABLE flags can apply,
                and the engine automatically checks status on a Set
                if RS_ATTR_QUERY_INSTR_STATUS is TRUE and the attribute's
                RS_VAL_DONT_CHECK_STATUS flag is 0 */

#define RS_VAL_DIRECT_USER_CALL            (1<<0)

/* RS_VAL_SET_CACHE_ONLY applies to Set only;
    if 1, then: only the cached value is set and no instrument I/O is performed;
                use this when you set multiple instrument attributes with one
                I/O command; if you call Set calls with this flag,
                the update is never deferred */

#define RS_VAL_SET_CACHE_ONLY              (1<<1)

/* RS_VAL_DONT_MARK_AS_SET_BY_USER applies to Set only;
    if 0 (which is the typical case), then: ... TODO: Not used feature */

#define RS_VAL_DONT_MARK_AS_SET_BY_USER    (1<<2)

/*****************************************************************************
 *- Typedef and related constants for data types ----------------------------*
 *****************************************************************************/

typedef ViInt32                     RsDataType;

#define RS_VAL_INT32                1L
#define RS_VAL_INT64                2L
#define RS_VAL_REAL64               4L
#define RS_VAL_STRING               5L
#define RS_VAL_ADDR                 10L
#define RS_VAL_SESSION              11L
#define RS_VAL_BOOLEAN              13L
#define RS_VAL_UNKNOWN_TYPE         14L
#define RS_VAL_EVENT                15L

#define RS_VAL_INT32_SIZE           sizeof (ViInt32)
#define RS_VAL_INT64_SIZE           sizeof (ViInt64)
#define RS_VAL_REAL64_SIZE          sizeof (ViReal64)
#define RS_VAL_STRING_SIZE          RS_MAX_MESSAGE_BUF_SIZE
#define RS_VAL_ADDR_SIZE            sizeof (ViAddr)
#define RS_VAL_SESSION_SIZE         sizeof (ViSession)
#define RS_VAL_BOOLEAN_SIZE         sizeof (ViBoolean)
#define RS_VAL_UNKNOWN_TYPE_SIZE    sizeof (void *)
#define RS_VAL_EVENT_SIZE           0

/*****************************************************************************
 *- Typedef and related constants for attribute access ----------------------*
 *****************************************************************************/

typedef ViInt32                     RsAttrAccess;

#define RS_VAL_READ_ONLY            0
#define RS_VAL_WRITE_ONLY           1
#define RS_VAL_READ_WRITE           2

/*****************************************************************************/
/*- Function pointer typedefs for attribute callbacks -----------------------*/
/*****************************************************************************/

typedef ViStatus (*RsReadAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 bufSize, void *value);
typedef ViStatus (*RsWriteAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, void *value);
typedef ViStatus (*RsCheckAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, void *value);
typedef ViStatus (*RsCheckStatusAttr_CallbackPtr)(ViSession io);
typedef ViStatus (*RsCompareAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, void *coercedNewValue, void *cacheValue, void *result);
typedef ViStatus (*RsCoerceAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, void *value, void *coercedValue);
typedef ViStatus (*RsRangeTable_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, RsRangeTablePtr *rangeTablePtr);
typedef ViStatus (*RsUserAttr_CallbackPtr)(ViSession io, ViConstString repCapName, ViAttr attributeId, ViInt32 bufSize, void *value);

/*****************************************************************************
 * Function pointer typedef for the Operation Complete (OPC)
 * callback. The OPC callback is called after writing an
 * attribute value to the instrument (if the
 * RS_VAL_WAIT_FOR_OPC_AFTER_WRITES flag is set for the attribute)
 * and before reading an attribute value from the instrument (if
 * the RS_VAL_WAIT_FOR_OPC_BEFORE_READS flag is set for the
 * attribute). You can install an OPC callback by setting the
 * RS_ATTR_OPC_CALLBACK attribute for the instrument.
 *****************************************************************************/
typedef ViStatus (*Rs_OPCCallbackPtr)(ViSession io);

/*****************************************************************************
 * Function pointer typedef for the Check Status callback.
 * This Check Status callback is called after interaction with
 * the instrument if the RS_ATTR_QUERY_INSTR_STATUS is set to
 * VI_TRUE. The callback queries the instrument to determine if
 * the instrument encountered an error. You can install a Check
 * Status callback by using the RS_ATTR_CHECK_STATUS_CALLBACK
 * attribute for the instrument.
 *****************************************************************************/
typedef ViStatus (*Rs_CheckStatusCallbackPtr)(ViSession io);

/*****************************************************************************
 *- Repeated Capability data structure --------------------------------------* 
 *****************************************************************************/

typedef struct
{
    ViString                        repCapNameId;           /* Repeated capability name identifier */
    ViString                        repCapName;             /* Repeated capability name(s) (comma separated values) */
    ViString                        cmdValues;              /* Command values (comma separated values) */
    
} RsRepCap, *RsRepCapPtr;

/****************************************************************************
 *- Attribute Properties Data Structure ------------------------------------*
 ****************************************************************************/

typedef struct
{
    /* Properties */
    ViInt32                         constant;

#ifdef _DEBUG

    ViString                        constantName;

#endif

    RsAttrAccess                    access;
    RsDataType                      dataType;
    RsRangeTablePtr                 rangeTable;
    ViString                        command;
    /* Default value */
    ViInt32                         integerDefault;
    ViReal64                        doubleDefault;
    ViBoolean                       booleanDefault;
    ViString                        stringDefault;
    ViSession                       sessionDefault;
    ViReal64                        comparePrecision;
    /* User defined callbacks */
    RsReadAttr_CallbackPtr          readCallback;
    RsWriteAttr_CallbackPtr         writeCallback;
    RsCheckAttr_CallbackPtr         checkCallback;
    RsCheckStatusAttr_CallbackPtr         checkStatusCallback;
    //RsCompareAttr_CallbackPtr       compareCallback;
    RsCoerceAttr_CallbackPtr        coerceCallback;
    RsRangeTable_CallbackPtr        rangeTableCallback;
    RsUserAttr_CallbackPtr          userCallback;
    /* Attribute flags */
    RsAttrFlags                     flags;
    /* Supported models & options */
    ViString                        supportedModels;
    ViString                        instrumentOptions;
    /* Current value (cached).
    
        NOTE:   For repeated capabilities it should act
                as array of pointers to current values,
                but it is not implemented. Only one current
                value per attribute is used for simulation.
                
                Normally it should apply when RS_VAL_MULTI_CHANNEL is 1.
    */
    void                            *p2value;
    /* Repeated capabilities */
    ViBoolean                       usercaps;               /* Use repeated capability? */

} RsAttrProperties, *RsAttrPropertiesPtr;

/*****************************************************************************
 *- Structure used to track session properties ------------------------------*
 *****************************************************************************/

typedef struct
{
    /* Sessions */
    ViSession                       io;                         /* Instrument IO session (also stored in RS_ATTR_IO_SESSION value) */
    /* Session Globals */
    ViBoolean                       locked;                     /* States whether session is locked by the operation in the process */
    ViBoolean                       optionChecking;             /* Holds the option checking state */
    /* Attribute(s) */
    RsAttrPropertiesPtr             attr;                       /* Pointer to the list of all attributes */
    ViUInt32                        numberOfAttr;               /* Number of attributes in the list */
    /* Repeated Capabilities */
    RsRepCapPtr                     repCapTable;                /* List of repeated capabilities */
    ViUInt32                        numberOfRepCaps;            /* Number of repeated capabilities in the list */
    /* Error Info */
    ViStatus                        primaryError;                               /* Status code describing the primary error condition */
    ViStatus                        secondaryError;                             /* Status code that further describes the error or warning condition */
    ViChar                          errorElaboration[RS_MAX_MESSAGE_BUF_SIZE];  /* Elaboration string that further describes the error or warning condition. */

} RsSessionProperties, *RsSessionPropertiesPtr;

/*****************************************************************************
 *- Utility Function Declarations (Non-Exported) ----------------------------*
 *****************************************************************************/

    /*- Functions to be used in the specific to create and dispose viSession */

ViStatus Rs_SpecificDriverNew (ViSession io,
                               ViConstString specificPrefix,
                               ViConstString optionsString,
                               RsAttrPropertiesPtr *attrList);
ViStatus Rs_Dispose (ViSession vi);

    /*- Set/Check/Get Attribute ---------------------------------------------*/

ViStatus Rs_SetAttribute (ViSession vi, ViConstString repCapName,
                          ViAttr attributeId, ViInt32 optionFlags, void *value);
ViStatus Rs_CheckAttribute (ViSession vi, ViConstString repCapName,
                            ViAttr attributeId, ViInt32 optionFlags, void *value);
ViStatus Rs_GetAttribute (ViSession vi, ViConstString repCapName,
                          ViAttr attributeId, ViInt32 optionFlags,
                          unsigned int bufSize, void *value);

    /*- Repeated Capability Functions ---------------------------------------*/

ViStatus Rs_BuildRepCapTable (ViSession vi, RsRepCapPtr repCapTable);
ViStatus Rs_ResetRepCapTable (ViSession instrSession, RsRepCapPtr repCapTable);
ViStatus Rs_GetAttributeRepCapNameId (ViSession vi,
                                      ViAttr attributeId,
                                      ViChar repCapNameId[]);
ViStatus Rs_GetAttributeRepCapName (ViSession vi,
                                    ViAttr attributeId,
                                    ViConstString repCapNameId,
                                    ViChar repCapName[]);
ViStatus Rs_AddRepCap (ViSession instrSession,
                       ViString repCapNameId,
                       ViString repCapName,
                       ViString cmdValue);
ViStatus Rs_RemoveRepCap (ViSession instrSession,
                          ViString repCapNameId,
                          ViString repCapName);
ViStatus Rs_ResetRepCap (ViSession instrSession,
                          ViString repCapNameId, RsRepCapPtr repCapTable);
ViStatus Rs_RepCapCount (ViSession instrSession,
                       ViString repCapNameId,
                       ViInt32* count);

    /*- Error Information functions -----------------------------------------*/

ViStatus Rs_SetErrorInfo (ViSession vi,
                          ViBoolean overWrite,
                          ViStatus primaryError,
                          ViStatus secondaryError,
                          ViConstString errorElaboration);
ViStatus Rs_GetErrorInfo (ViSession vi,
                          ViStatus *primaryError,
                          ViStatus *secondaryError,
                          ViChar errorElaboration[]);
ViStatus Rs_ClearErrorInfo (ViSession vi);

ViStatus Rs_ParamPositionError (ViInt32 parameterPosition);  /* returns one of VI_ERROR_PARAMETER1, VI_ERROR_PARAMETER2, ..., VI_ERROR_PARAMETER8, RS_ERROR_INVALID_PARAMETER */

ViStatus Rs_GetErrorMessage (ViStatus statusCode, ViChar messageBuf[]);

    /*- Locking functions for multithreading --------------------------------*/

ViStatus Rs_LockSession (ViSession vi, ViBoolean *callerHasLock);
ViStatus Rs_UnlockSession (ViSession vi, ViBoolean *callerHasLock);

    /*- Accessor functions for inherent attributes --------------------------*/

ViSession Rs_IOSession (RsSessionPropertiesPtr sessionProperties);
RsSessionPropertiesPtr Rs_ViSession (ViSession session);
ViBoolean Rs_RangeChecking (ViSession vi);
ViBoolean Rs_QueryInstrStatus (ViSession vi);
ViBoolean Rs_Simulating (ViSession vi);
ViBoolean Rs_UseSpecificSimulation (ViSession vi);

    /*- Helper functions for specific instrument drivers --------------------*/

ViStatus Rs_GetSpecificDriverStatusDesc (ViSession vi, ViStatus statusCode,
                                         ViChar messageBuf[],
                                         RsStringValueTable additionalTableToSearch);
ViStatus Rs_WriteInstrData (ViSession vi, ViConstString writeBuffer);
ViStatus Rs_ReadInstrData (ViSession vi, ViInt32 numBytes, ViChar rdBuf[], ViUInt32 *bytesRead);
ViStatus Rs_GetInfoFromResourceName (ViRsrc resourceName, ViString optionString,
                                     ViChar newResourceName[],
                                     ViChar newOptionString[],
                                     ViBoolean *isLogicalName);
void Rs_Delay (ViReal64 numberOfSeconds);

    /*- Helper functions for utilities or tools -----------------------------*/

ViStatus Rs_GetAttributeFlags (ViSession vi, ViAttr attributeId, RsAttrFlags *flags);
ViStatus Rs_SetAttributeFlags (ViSession vi, ViAttr attributeId, RsAttrFlags flags);
ViStatus Rs_GetAttributeIndex (ViSession io, ViAttr attributeId, ViInt32 *attributeIndex);
ViStatus Rs_ApplyAttributeDefaults (ViSession vi, ViBoolean updateInherent);

ViStatus Rs_GetTokenAtIndex (ViChar *string_to_separate, ViConstString delimiter, ViUInt32 index, ViChar token[], ViUInt32 token_max_length);
ViStatus Rs_GetIndexOfToken (ViChar *string_to_separate, ViConstString delimiter, ViUInt32 *index, ViConstString token);

ViStatus Rs_CheckModelOpt (ViSession vi, ViAttr attributeId);
ViStatus Rs_GetRepCapCmdValue (ViSession instrSession,
                               ViAttr attributeId,
                               ViConstString repCapNameId,
                               ViConstString repCapName,
                               ViChar cmdValue[]);
ViStatus Rs_SpreadsheetStringToDblArray (ViString str, ViString delim, ViUInt32 bufferSize, ViReal64 array[], ViUInt32* returnCount);

    /*- Instrument I/O utilities -*/

ViStatus Rs_ReadDataUnknownLength (ViSession io, ViChar **outputBuffer, ViUInt32 *byteCount);

    /*- Functions for class instrument drivers ------------------------------*/

ViStatus Rs_ApplyDefaultSetup (ViSession vi);

    /*- File I/O Utility Functions ------------------------------------------*/

ViStatus Rs_ReadToFile (ViSession vi, ViConstString filename,
                        ViInt32 maxBytesToRead, ViInt32 fileAction,
                        ViInt32 *totalBytesWritten);
ViStatus Rs_WriteFromFile (ViSession vi, ViConstString filename,
                           ViInt32 maxBytesToWrite, ViInt32 byteOffset,
                           ViInt32 *totalBytesWritten);

    /*- Misc Functions ------------------------------------------------------*/
ViStatus Rs_BuildCommandString (ViSession instrSession, ViAttr attributeId, ViInt32 idx, ViConstString repCapName, ViChar **cmd);

/*****************************************************************************
 *- Callback Declarations (Non-Exported) ------------------------------------*
 *****************************************************************************/

    /*- Global Attribute callbacks ------------------------------------------*/

ViStatus Rs_ReadCallback (ViSession io,
                          ViConstString repCapName, ViAttr attributeId,
                          ViInt32 bufSize, void *value);
ViStatus Rs_WriteCallback (ViSession io,
                           ViConstString repCapName, ViAttr attributeId,
                           void *value);
ViStatus Rs_CheckCallback (ViSession io, ViConstString repCapName,
                           ViAttr attributeId, void *value);
ViStatus Rs_CompareAttr_Callback (ViSession io,
                                  ViConstString repCapName,
                                  ViAttr attributeId,
                                  void *coercedNewValue,
                                  void *cacheValue, void *result);
ViStatus Rs_CoerceCallback (ViSession io, ViConstString repCapName,
                            ViAttr attributeId, void *value,
                            void *coercedValue);
ViStatus Rs_RangeTableCallback (ViSession io, ViConstString repCapName,
                                ViAttr attributeId,
                                RsRangeTablePtr rangeTablePtr);
ViStatus Rs_ClearBeforeRead (ViSession instrSession);
/****************************************************************************
 *---------------------------------- Misc ----------------------------------*
 ****************************************************************************/

#define Rs_Decimalize(x)         (((x>>8)*100)+(((x >> 4) & 0xF)*10)+(x & 0xF))

#define Rs_ConvertVISAVer(x)     ((((x>>20)*100)+(((x >> 8) & 0xFFF)*10)+(x & 0xFF))/100.0)

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

/*  This section lists all attributes and values that became obsolete. Do not use   */
/*  those attributes and values in your drivers and applications.                   */

/*  RS_ATTR_CLASS_PREFIX is obsolete. Use RS_ATTR_CLASS_DRIVER_PREFIX instead       */
#define RS_ATTR_CLASS_PREFIX            /* ViString, not writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 301)  /* instrument prefix for the class driver;  empty string if not using class driver */
/*  RS_ATTR_SPECIFIC_PREFIX is obsolete. Use RS_ATTR_SPECIFIC_DRIVER_PREFIX instead */
#define RS_ATTR_SPECIFIC_PREFIX         /* ViString, not writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 302)  /* instrument prefix for the specific driver */ 
/*  RS_ATTR_MODULE_PATHNAME is obsolete. Use RS_ATTR_SPECIFIC_DRIVER_LOCATOR instead */
#define RS_ATTR_MODULE_PATHNAME         /* ViString, not writable */    (RS_ENGINE_PUBLIC_ATTR_BASE + 303)  /* the pathnname of the specific driver code module; from the configuration file */
/*  RS_ATTR_DRIVER_MAJOR_VERSION is obsolete. Use RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION instead */
#define RS_ATTR_DRIVER_MAJOR_VERSION    /* ViInt32,  not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 503)   
/*  RS_ATTR_DRIVER_MINOR_VERSION is obsolete. Use RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION instead */
#define RS_ATTR_DRIVER_MINOR_VERSION    /* ViInt32,  not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 504)   
/*  RS_ATTR_CLASS_MAJOR_VERSION is obsolete. Use RS_ATTR_CLASS_DRIVER_MAJOR_VERSION instead */
#define RS_ATTR_CLASS_MAJOR_VERSION     /* ViInt32,  not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 505)   
/*  RS_ATTR_CLASS_MINOR_VERSION is obsolete. Use RS_ATTR_CLASS_DRIVER_MINOR_VERSION instead */
#define RS_ATTR_CLASS_MINOR_VERSION     /* ViInt32,  not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 506)   
/*  RS_ATTR_DRIVER_REVISION is obsolete. Use RS_ATTR_SPECIFIC_DRIVER_REVISION instead */
#define RS_ATTR_DRIVER_REVISION         /* ViString, not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 551)    
/*  RS_ATTR_CLASS_REVISION is obsolete. Use RS_ATTR_CLASS_DRIVER_REVISION instead */
#define RS_ATTR_CLASS_REVISION          /* ViString, not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 552)   
/*  RS_ATTR_FIRMWARE_REVISION is obsolete. Use RS_ATTR_INSTRUMENT_FIRMWARE_REVISION instead */
#define RS_ATTR_FIRMWARE_REVISION       /* ViString, not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 510)
/*  RS_ATTR_SUPPORTED_CLASSES is obsolete. */
#define RS_ATTR_SUPPORTED_CLASSES       /* ViString, not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 323)
/*  RS_ATTR_NUM_CHANNELS is obsolete. Use RS_ATTR_CHANNEL_COUNT instead */
#define RS_ATTR_NUM_CHANNELS            /* ViInt32,  not writable*/     (RS_ENGINE_PUBLIC_ATTR_BASE + 203)   /* set by the specific-driver;  default: 1 */

/*  RS_ATTR_QUERY_INSTR_STATUS is obsolete. Use RS_ATTR_QUERY_INSTRUMENT_STATUS instead */
#define RS_ATTR_QUERY_INSTR_STATUS RS_ATTR_QUERY_INSTRUMENT_STATUS  
/*  RS_ATTR_RESOURCE_DESCRIPTOR is obsolete. Use RS_ATTR_IO_RESOURCE_DESCRIPTOR instead */
#define RS_ATTR_RESOURCE_DESCRIPTOR RS_ATTR_IO_RESOURCE_DESCRIPTOR
#define RS_ATTR_ATTRIBUTE_CAPABILITIES /* ViString, not user-writable*/(RS_ENGINE_PUBLIC_ATTR_BASE + 403)    

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif  /* __RS_CORE_HEADER */
