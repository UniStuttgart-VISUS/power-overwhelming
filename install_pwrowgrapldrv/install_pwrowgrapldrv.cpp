// <copyright file="install_pwrowgrapldrv.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

int main(void) { return 0; }

#if false
#include <DriverSpecs.h>
_Analysis_mode_(_Analysis_code_type_user_code_)

#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "public.h"

#include <wdfinstaller.h>

#define ARRAY_SIZE(x)        (sizeof(x) /sizeof(x[0]))

extern
PCHAR
GetCoinstallerVersion(
    VOID
);

BOOLEAN
InstallDriver(
    IN SC_HANDLE  SchSCManager,
    IN LPCTSTR    DriverName,
    IN LPCTSTR    ServiceExe
);


BOOLEAN
RemoveDriver(
    IN SC_HANDLE  SchSCManager,
    IN LPCTSTR    DriverName
);

BOOLEAN
StartDriver(
    IN SC_HANDLE  SchSCManager,
    IN LPCTSTR    DriverName
);

BOOLEAN
StopDriver(
    IN SC_HANDLE  SchSCManager,
    IN LPCTSTR    DriverName
);

#define SYSTEM32_DRIVERS "\\System32\\Drivers\\"
#define NONPNP_INF_FILENAME  L"\\nonpnp.inf"
#define WDF_SECTION_NAME L"nonpnp.NT.Wdf"

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
PFN_WDFPREDEVICEINSTALLEX pfnWdfPreDeviceInstallEx;
PFN_WDFPOSTDEVICEINSTALL   pfnWdfPostDeviceInstall;
PFN_WDFPREDEVICEREMOVE     pfnWdfPreDeviceRemove;
PFN_WDFPOSTDEVICEREMOVE   pfnWdfPostDeviceRemove;

//-----------------------------------------------------------------------------
// 4127 -- Conditional Expression is Constant warning
//-----------------------------------------------------------------------------
#define WHILE(a) \
__pragma(warning(suppress:4127)) while(a)

LONG
GetPathToInf(
    _Out_writes_(InfFilePathSize) PWCHAR InfFilePath,
    IN ULONG InfFilePathSize
)
{
    LONG    error = ERROR_SUCCESS;

    if (GetCurrentDirectoryW(InfFilePathSize, InfFilePath) == 0) {
        error = GetLastError();
        printf("InstallDriver failed!  Error = %d \n", error);
        return error;
    }
    if (FAILED(StringCchCatW(InfFilePath,
        InfFilePathSize,
        NONPNP_INF_FILENAME))) {
        error = ERROR_BUFFER_OVERFLOW;
        return error;
    }
    return error;

}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
BOOLEAN
InstallDriver(
    IN SC_HANDLE  SchSCManager,
    IN LPCTSTR    DriverName,
    IN LPCTSTR    ServiceExe
)
/*++
Routine Description:
Arguments:
Return Value:
--*/
{
    SC_HANDLE   schService;
    DWORD       err;
    WCHAR      infPath[MAX_PATH];
    WDF_COINSTALLER_INSTALL_OPTIONS clientOptions;

    WDF_COINSTALLER_INSTALL_OPTIONS_INIT(&clientOptions);

    //
    // NOTE: This creates an entry for a standalone driver. If this
    //       is modified for use with a driver that requires a Tag,
    //       Group, and/or Dependencies, it may be necessary to
    //       query the registry for existing driver information
    //       (in order to determine a unique Tag, etc.).
    //
    //
    // PRE-INSTALL for WDF support
    //
    err = GetPathToInf(infPath, ARRAY_SIZE(infPath));
    if (err != ERROR_SUCCESS) {
        return  FALSE;
    }
    err = pfnWdfPreDeviceInstallEx(infPath, WDF_SECTION_NAME, &clientOptions);

    if (err != ERROR_SUCCESS) {
        if (err == ERROR_SUCCESS_REBOOT_REQUIRED) {
            printf("System needs to be rebooted, before the driver installation can proceed.\n");
        }

        return  FALSE;
    }

    //
    // Create a new a service object.
    //

    schService = CreateService(SchSCManager,           // handle of service control manager database
        DriverName,             // address of name of service to start
        DriverName,             // address of display name
        SERVICE_ALL_ACCESS,     // type of access to service
        SERVICE_KERNEL_DRIVER,  // type of service
        SERVICE_DEMAND_START,   // when to start service
        SERVICE_ERROR_NORMAL,   // severity if service fails to start
        ServiceExe,             // address of name of binary file
        NULL,                   // service does not belong to a group
        NULL,                   // no tag requested
        NULL,                   // no dependency names
        NULL,                   // use LocalSystem account
        NULL                    // no password for service account
    );

    if (schService == NULL) {

        err = GetLastError();

        if (err == ERROR_SERVICE_EXISTS) {

            //
            // Ignore this error.
            //

            return TRUE;

        } else {

            printf("CreateService failed!  Error = %d \n", err);

            //
            // Indicate an error.
            //

            return  FALSE;
        }
    }

    //
    // Close the service object.
    //
    CloseServiceHandle(schService);

    //
    // POST-INSTALL for WDF support
    //
    err = pfnWdfPostDeviceInstall(infPath, WDF_SECTION_NAME);

    if (err != ERROR_SUCCESS) {
        return  FALSE;
    }

    //
    // Indicate success.
    //

    return TRUE;

}   // InstallDriver

BOOLEAN
ManageDriver(
    IN LPCTSTR  DriverName,
    IN LPCTSTR  ServiceName,
    IN USHORT   Function
)
{

    SC_HANDLE   schSCManager;

    BOOLEAN rCode = TRUE;

    //
    // Insure (somewhat) that the driver and service names are valid.
    //

    if (!DriverName || !ServiceName) {

        printf("Invalid Driver or Service provided to ManageDriver() \n");

        return FALSE;
    }

    //
    // Connect to the Service Control Manager and open the Services database.
    //

    schSCManager = OpenSCManager(NULL,                   // local machine
        NULL,                   // local database
        SC_MANAGER_ALL_ACCESS   // access required
    );

    if (!schSCManager) {

        printf("Open SC Manager failed! Error = %d \n", GetLastError());

        return FALSE;
    }

    //
    // Do the requested function.
    //

    switch (Function) {

        case DRIVER_FUNC_INSTALL:

            //
            // Install the driver service.
            //

            if (InstallDriver(schSCManager,
                DriverName,
                ServiceName
            )) {

                //
                // Start the driver service (i.e. start the driver).
                //

                rCode = StartDriver(schSCManager,
                    DriverName
                );

            } else {

                //
                // Indicate an error.
                //

                rCode = FALSE;
            }

            break;

        case DRIVER_FUNC_REMOVE:

            //
            // Stop the driver.
            //

            StopDriver(schSCManager,
                DriverName
            );

            //
            // Remove the driver service.
            //

            RemoveDriver(schSCManager,
                DriverName
            );

            //
            // Ignore all errors.
            //

            rCode = TRUE;

            break;

        default:

            printf("Unknown ManageDriver() function. \n");

            rCode = FALSE;

            break;
    }

    //
    // Close handle to service control manager.
    //
    CloseServiceHandle(schSCManager);

    return rCode;

}   // ManageDriver


BOOLEAN
RemoveDriver(
    IN SC_HANDLE    SchSCManager,
    IN LPCTSTR      DriverName
)
{
    SC_HANDLE   schService;
    BOOLEAN     rCode;
    DWORD       err;
    WCHAR      infPath[MAX_PATH];

    err = GetPathToInf(infPath, ARRAY_SIZE(infPath));
    if (err != ERROR_SUCCESS) {
        return  FALSE;
    }

    //
    // PRE-REMOVE of WDF support
    //
    err = pfnWdfPreDeviceRemove(infPath, WDF_SECTION_NAME);

    if (err != ERROR_SUCCESS) {
        return  FALSE;
    }

    //
    // Open the handle to the existing service.
    //

    schService = OpenService(SchSCManager,
        DriverName,
        SERVICE_ALL_ACCESS
    );

    if (schService == NULL) {

        printf("OpenService failed!  Error = %d \n", GetLastError());

        //
        // Indicate error.
        //

        return FALSE;
    }

    //
    // Mark the service for deletion from the service control manager database.
    //

    if (DeleteService(schService)) {

        //
        // Indicate success.
        //

        rCode = TRUE;

    } else {

        printf("DeleteService failed!  Error = %d \n", GetLastError());

        //
        // Indicate failure.  Fall through to properly close the service handle.
        //

        rCode = FALSE;
    }

    //
    // Close the service object.
    //
    CloseServiceHandle(schService);

    //
    // POST-REMOVE of WDF support
    //
    err = pfnWdfPostDeviceRemove(infPath, WDF_SECTION_NAME);

    if (err != ERROR_SUCCESS) {
        rCode = FALSE;
    }

    return rCode;

}   // RemoveDriver



BOOLEAN
StartDriver(
    IN SC_HANDLE    SchSCManager,
    IN LPCTSTR      DriverName
)
{
    SC_HANDLE   schService;
    DWORD       err;
    BOOL        ok;

    //
    // Open the handle to the existing service.
    //
    schService = OpenService(SchSCManager,
        DriverName,
        SERVICE_ALL_ACCESS
    );

    if (schService == NULL) {
        //
        // Indicate failure.
        //
        printf("OpenService failed!  Error = %d\n", GetLastError());
        return FALSE;
    }

    //
    // Start the execution of the service (i.e. start the driver).
    //
    ok = StartService(schService, 0, NULL);

    if (!ok) {

        err = GetLastError();

        if (err == ERROR_SERVICE_ALREADY_RUNNING) {
            //
            // Ignore this error.
            //
            return TRUE;

        } else {
            //
            // Indicate failure.
            // Fall through to properly close the service handle.
            //
            printf("StartService failure! Error = %d\n", err);
            return FALSE;
        }
    }

    //
    // Close the service object.
    //
    CloseServiceHandle(schService);

    return TRUE;

}   // StartDriver



BOOLEAN
StopDriver(
    IN SC_HANDLE    SchSCManager,
    IN LPCTSTR      DriverName
)
{
    BOOLEAN         rCode = TRUE;
    SC_HANDLE       schService;
    SERVICE_STATUS  serviceStatus;

    //
    // Open the handle to the existing service.
    //

    schService = OpenService(SchSCManager,
        DriverName,
        SERVICE_ALL_ACCESS
    );

    if (schService == NULL) {

        printf("OpenService failed!  Error = %d \n", GetLastError());

        return FALSE;
    }

    //
    // Request that the service stop.
    //

    if (ControlService(schService,
        SERVICE_CONTROL_STOP,
        &serviceStatus
    )) {

        //
        // Indicate success.
        //

        rCode = TRUE;

    } else {

        printf("ControlService failed!  Error = %d \n", GetLastError());

        //
        // Indicate failure.  Fall through to properly close the service handle.
        //

        rCode = FALSE;
    }

    //
    // Close the service object.
    //
    CloseServiceHandle(schService);

    return rCode;

}   //  StopDriver


//
// Caller must free returned pathname string.
//
PCHAR
BuildDriversDirPath(
    _In_ PSTR DriverName
)
{
    size_t  remain;
    size_t  len;
    PCHAR   dir;

    if (!DriverName || strlen(DriverName) == 0) {
        return NULL;
    }

    remain = MAX_PATH;

    //
    // Allocate string space
    //
    dir = (PCHAR)malloc(remain + 1);

    if (!dir) {
        return NULL;
    }

    //
    // Get the base windows directory path.
    //
    len = GetWindowsDirectory(dir, (UINT)remain);

    if (len == 0 ||
        (remain - len) < sizeof(SYSTEM32_DRIVERS)) {
        free(dir);
        return NULL;
    }
    remain -= len;

    //
    // Build dir to have "%windir%\System32\Drivers\<DriverName>".
    //
    if (FAILED(StringCchCat(dir, remain, SYSTEM32_DRIVERS))) {
        free(dir);
        return NULL;
    }

    remain -= sizeof(SYSTEM32_DRIVERS);
    len += sizeof(SYSTEM32_DRIVERS);
    len += strlen(DriverName);

    if (remain < len) {
        free(dir);
        return NULL;
    }

    if (FAILED(StringCchCat(dir, remain, DriverName))) {
        free(dir);
        return NULL;
    }

    dir[len] = '\0';  // keeps prefast happy

    return dir;
}


BOOLEAN
SetupDriverName(
    _Inout_updates_all_(BufferLength) PCHAR DriverLocation,
    _In_ ULONG BufferLength
)
{
    HANDLE fileHandle;
    DWORD  driverLocLen = 0;
    BOOL   ok;
    PCHAR  driversDir;

    //
    // Setup path name to driver file.
    //
    driverLocLen =
        GetCurrentDirectory(BufferLength, DriverLocation);

    if (!driverLocLen) {

        printf("GetCurrentDirectory failed!  Error = %d \n",
            GetLastError());

        return FALSE;
    }

    if (FAILED(StringCchCat(DriverLocation, BufferLength, "\\" DRIVER_NAME ".sys"))) {
        return FALSE;
    }

    //
    // Insure driver file is in the specified directory.
    //
    fileHandle = CreateFile(DriverLocation,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (fileHandle == INVALID_HANDLE_VALUE) {
        //
        // Indicate failure.
        //
        printf("Driver: %s.SYS is not in the %s directory. \n",
            DRIVER_NAME, DriverLocation);
        return FALSE;
    }

    //
    // Build %windir%\System32\Drivers\<DRIVER_NAME> path.
    // Copy the driver to %windir%\system32\drivers
    //
    driversDir = BuildDriversDirPath(DRIVER_NAME ".sys");

    if (!driversDir) {
        printf("BuildDriversDirPath failed!\n");
        return FALSE;
    }

    ok = CopyFile(DriverLocation, driversDir, FALSE);

    if (!ok) {
        printf("CopyFile failed: error(%d) - \"%s\"\n",
            GetLastError(), driversDir);
        free(driversDir);
        return FALSE;
    }

    if (FAILED(StringCchCopy(DriverLocation, BufferLength, driversDir))) {
        free(driversDir);
        return FALSE;
    }

    free(driversDir);

    //
    // Close open file handle.
    //
    if (fileHandle) {
        CloseHandle(fileHandle);
    }

    //
    // Indicate success.
    //
    return TRUE;

}   // SetupDriverName


HMODULE
LoadWdfCoInstaller(
    VOID
)
{
    HMODULE library = NULL;
    DWORD   error = ERROR_SUCCESS;
    CHAR   szCurDir[MAX_PATH];
    CHAR   tempCoinstallerName[MAX_PATH];
    PCHAR  coinstallerVersion;

    do {

        if (GetCurrentDirectory(MAX_PATH, szCurDir) == 0) {

            printf("GetCurrentDirectory failed!  Error = %d \n", GetLastError());
            break;
        }
        coinstallerVersion = GetCoinstallerVersion();
        if (FAILED(StringCchPrintf(tempCoinstallerName,
            MAX_PATH,
            "\\WdfCoInstaller%s.dll",
            coinstallerVersion))) {
            break;
        }
        if (FAILED(StringCchCat(szCurDir, MAX_PATH, tempCoinstallerName))) {
            break;
        }

        library = LoadLibrary(szCurDir);

        if (library == NULL) {
            error = GetLastError();
            printf("LoadLibrary(%s) failed: %d\n", szCurDir, error);
            break;
        }

        pfnWdfPreDeviceInstallEx =
            (PFN_WDFPREDEVICEINSTALLEX)GetProcAddress(library, "WdfPreDeviceInstallEx");

        if (pfnWdfPreDeviceInstallEx == NULL) {
            error = GetLastError();
            printf("GetProcAddress(\"WdfPreDeviceInstallEx\") failed: %d\n", error);
            return NULL;
        }

        pfnWdfPostDeviceInstall =
            (PFN_WDFPOSTDEVICEINSTALL)GetProcAddress(library, "WdfPostDeviceInstall");

        if (pfnWdfPostDeviceInstall == NULL) {
            error = GetLastError();
            printf("GetProcAddress(\"WdfPostDeviceInstall\") failed: %d\n", error);
            return NULL;
        }

        pfnWdfPreDeviceRemove =
            (PFN_WDFPREDEVICEREMOVE)GetProcAddress(library, "WdfPreDeviceRemove");

        if (pfnWdfPreDeviceRemove == NULL) {
            error = GetLastError();
            printf("GetProcAddress(\"WdfPreDeviceRemove\") failed: %d\n", error);
            return NULL;
        }

        pfnWdfPostDeviceRemove =
            (PFN_WDFPREDEVICEREMOVE)GetProcAddress(library, "WdfPostDeviceRemove");

        if (pfnWdfPostDeviceRemove == NULL) {
            error = GetLastError();
            printf("GetProcAddress(\"WdfPostDeviceRemove\") failed: %d\n", error);
            return NULL;
        }

    } WHILE(0);

    if (error != ERROR_SUCCESS) {
        if (library) {
            FreeLibrary(library);
        }
        library = NULL;
    }

    return library;
}


VOID
UnloadWdfCoInstaller(
    HMODULE Library
)
{
    if (Library) {
        FreeLibrary(Library);
    }
}



#include <DriverSpecs.h>
_Analysis_mode_(_Analysis_code_type_user_code_)

#include <windows.h>

#pragma warning(disable:4201)  // nameless struct/union
#include <winioctl.h>
#pragma warning(default:4201)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <strsafe.h>
#include "public.h"


BOOLEAN
ManageDriver(
    IN LPCTSTR  DriverName,
    IN LPCTSTR  ServiceName,
    IN USHORT   Function
);

HMODULE
LoadWdfCoInstaller(
    VOID
);

VOID
UnloadWdfCoInstaller(
    HMODULE Library
);

BOOLEAN
SetupDriverName(
    _Inout_updates_all_(BufferLength) PCHAR DriverLocation,
    _In_ ULONG BufferLength
);

BOOLEAN
DoFileReadWrite(
    HANDLE HDevice
);

VOID
DoIoctls(
    HANDLE hDevice
);

// for example, WDF 1.9 is "01009". the size 6 includes the ending NULL marker
//
#define MAX_VERSION_SIZE 6

CHAR G_coInstallerVersion[MAX_VERSION_SIZE] = { 0 };
BOOLEAN  G_fLoop = FALSE;
BOOL G_versionSpecified = FALSE;



//-----------------------------------------------------------------------------
// 4127 -- Conditional Expression is Constant warning
//-----------------------------------------------------------------------------
#define WHILE(constant) \
__pragma(warning(disable: 4127)) while(constant); __pragma(warning(default: 4127))


#define USAGE  \
"Usage: nonpnpapp <-V version> <-l> \n" \
       " -V version  {if no version is specified the version specified in the build environment will be used.}\n" \
       "    The version is the version of the KMDF coinstaller to use \n"  \
       "    The format of version  is MMmmm where MM -- major #, mmm - serial# \n" \
       " -l  { option to continuously read & write to the file} \n"

BOOL
ValidateCoinstallerVersion(
    _In_ PSTR Version
)
{
    BOOL ok = FALSE;
    INT i;

    for (i = 0; i < MAX_VERSION_SIZE; i++) {
        if (!IsCharAlphaNumericA(Version[i])) {
            break;
        }
    }
    if (i == (MAX_VERSION_SIZE - sizeof(CHAR))) {
        ok = TRUE;
    }
    return ok;
}

LONG
Parse(
    _In_ int argc,
    _In_reads_(argc) char *argv[]
)
/*++
Routine Description:
    Called by main() to parse command line parms
Arguments:
    argc and argv that was passed to main()
Return Value:
    Sets global flags as per user function request
--*/
{
    int i;
    BOOL ok;
    LONG error = ERROR_SUCCESS;

    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-' ||
            argv[i][0] == '/') {
            switch (argv[i][1]) {
                case 'V':
                case 'v':
                    if (((i + 1 < argc) &&
                        (argv[i + 1][0] != '-' && argv[i + 1][0] != '/'))) {
                        //
                        // use version in commandline
                        //
                        i++;
                        ok = ValidateCoinstallerVersion(argv[i]);
                        if (!ok) {
                            printf("Not a valid format for coinstaller version\n"
                                "It should be characters between A-Z, a-z , 0-9\n"
                                "The version format is MMmmm where MM -- major #, mmm - serial#");
                            error = ERROR_INVALID_PARAMETER;
                            break;
                        }
                        if (FAILED(StringCchCopy(G_coInstallerVersion,
                            MAX_VERSION_SIZE,
                            argv[i]))) {
                            break;
                        }
                        G_versionSpecified = TRUE;

                    } else {
                        printf(USAGE);
                        error = ERROR_INVALID_PARAMETER;
                    }
                    break;
                case 'l':
                case 'L':
                    G_fLoop = TRUE;
                    break;
                default:
                    printf(USAGE);
                    error = ERROR_INVALID_PARAMETER;

            }
        }
    }
    return error;
}

PCHAR
GetCoinstallerVersion(
    VOID
)
{
    if (!G_versionSpecified &&
        FAILED(StringCchPrintf(G_coInstallerVersion,
            MAX_VERSION_SIZE,
            "%02d%03d",    // for example, "01009"
            KMDF_VERSION_MAJOR,
            KMDF_VERSION_MINOR)))
    {
        printf("StringCchCopy failed with error \n");
    }

    return (PCHAR)&G_coInstallerVersion;
}

VOID __cdecl
main(
    _In_ ULONG argc,
    _In_reads_(argc) PCHAR argv[]
)
{
    HANDLE   hDevice;
    DWORD    errNum = 0;
    CHAR     driverLocation[MAX_PATH];
    BOOL     ok;
    HMODULE  library = NULL;
    LONG     error;
    PCHAR    coinstallerVersion;

    //
    // Parse command line args
    //   -l     -- loop option
    //
    if (argc > 1) {// give usage if invoked with no parms
        error = Parse(argc, argv);
        if (error != ERROR_SUCCESS) {
            return;
        }
    }

    if (!G_versionSpecified) {
        coinstallerVersion = GetCoinstallerVersion();

        //
        // if no version is specified or an invalid one is specified use default version
        //
        printf("No version specified. Using default version:%s\n",
            coinstallerVersion);

    } else {
        coinstallerVersion = (PCHAR)&G_coInstallerVersion;
    }

    //
    // open the device
    //
    hDevice = CreateFile(DEVICE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {

        errNum = GetLastError();

        if (!(errNum == ERROR_FILE_NOT_FOUND ||
            errNum == ERROR_PATH_NOT_FOUND)) {

            printf("CreateFile failed!  ERROR_FILE_NOT_FOUND = %d\n",
                errNum);
            return;
        }

        //
        // Load WdfCoInstaller.dll.
        //
        library = LoadWdfCoInstaller();

        if (library == NULL) {
            printf("The WdfCoInstaller%s.dll library needs to be "
                "in same directory as nonpnpapp.exe\n", coinstallerVersion);
            return;
        }

        //
        // The driver is not started yet so let us install the driver.
        // First setup full path to driver name.
        //
        ok = SetupDriverName(driverLocation, MAX_PATH);

        if (!ok) {
            return;
        }

        ok = ManageDriver(DRIVER_NAME,
            driverLocation,
            DRIVER_FUNC_INSTALL);

        if (!ok) {

            printf("Unable to install driver. \n");

            //
            // Error - remove driver.
            //
            ManageDriver(DRIVER_NAME,
                driverLocation,
                DRIVER_FUNC_REMOVE);
            return;
        }

        hDevice = CreateFile(DEVICE_NAME,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (hDevice == INVALID_HANDLE_VALUE) {
            printf("Error: CreatFile Failed : %d\n", GetLastError());
            return;
        }
    }

    DoIoctls(hDevice);

    do {

        if (!DoFileReadWrite(hDevice)) {
            break;
        }

        if (!G_fLoop) {
            break;
        }
        Sleep(1000); // sleep for 1 sec.

    } WHILE(TRUE);

    //
    // Close the handle to the device before unloading the driver.
    //
    CloseHandle(hDevice);

    //
    // Unload the driver.  Ignore any errors.
    //
    ManageDriver(DRIVER_NAME,
        driverLocation,
        DRIVER_FUNC_REMOVE);

    //
    // Unload WdfCoInstaller.dll
    //
    if (library) {
        UnloadWdfCoInstaller(library);
    }
    return;
}


VOID
DoIoctls(
    HANDLE hDevice
)
{
    char OutputBuffer[100];
    char InputBuffer[200];
    BOOL bRc;
    ULONG bytesReturned;

    //
    // Printing Input & Output buffer pointers and size
    //

    printf("InputBuffer Pointer = %p, BufLength = %Id\n", InputBuffer,
        sizeof(InputBuffer));
    printf("OutputBuffer Pointer = %p BufLength = %Id\n", OutputBuffer,
        sizeof(OutputBuffer));
    //
    // Performing METHOD_BUFFERED
    //

    if (FAILED(StringCchCopy(InputBuffer, sizeof(InputBuffer),
        "this String is from User Application; using METHOD_BUFFERED"))) {
        return;
    }

    printf("\nCalling DeviceIoControl METHOD_BUFFERED:\n");

    memset(OutputBuffer, 0, sizeof(OutputBuffer));

    bRc = DeviceIoControl(hDevice,
        (DWORD)IOCTL_NONPNP_METHOD_BUFFERED,
        InputBuffer,
        (DWORD)strlen(InputBuffer) + 1,
        OutputBuffer,
        sizeof(OutputBuffer),
        &bytesReturned,
        NULL
    );

    if (!bRc)
    {
        printf("Error in DeviceIoControl : %d", GetLastError());
        return;

    }
    printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);


    //
    // Performing METHOD_NEITHER
    //

    printf("\nCalling DeviceIoControl METHOD_NEITHER\n");

    if (FAILED(StringCchCopy(InputBuffer, sizeof(InputBuffer),
        "this String is from User Application; using METHOD_NEITHER"))) {
        return;
    }

    memset(OutputBuffer, 0, sizeof(OutputBuffer));

    bRc = DeviceIoControl(hDevice,
        (DWORD)IOCTL_NONPNP_METHOD_NEITHER,
        InputBuffer,
        (DWORD)strlen(InputBuffer) + 1,
        OutputBuffer,
        sizeof(OutputBuffer),
        &bytesReturned,
        NULL
    );

    if (!bRc)
    {
        printf("Error in DeviceIoControl : %d\n", GetLastError());
        return;

    }

    printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);

    //
    // Performing METHOD_IN_DIRECT
    //

    printf("\nCalling DeviceIoControl METHOD_IN_DIRECT\n");

    if (FAILED(StringCchCopy(InputBuffer, sizeof(InputBuffer),
        "this String is from User Application; using METHOD_IN_DIRECT"))) {
        return;
    }

    if (FAILED(StringCchCopy(OutputBuffer, sizeof(OutputBuffer),
        "This String is from User Application in OutBuffer; using METHOD_IN_DIRECT"))) {
        return;
    }

    bRc = DeviceIoControl(hDevice,
        (DWORD)IOCTL_NONPNP_METHOD_IN_DIRECT,
        InputBuffer,
        (DWORD)strlen(InputBuffer) + 1,
        OutputBuffer,
        sizeof(OutputBuffer),
        &bytesReturned,
        NULL
    );

    if (!bRc)
    {
        printf("Error in DeviceIoControl : : %d", GetLastError());
        return;
    }

    printf("    Number of bytes transfered from OutBuffer: %d\n",
        bytesReturned);

    //
    // Performing METHOD_OUT_DIRECT
    //

    printf("\nCalling DeviceIoControl METHOD_OUT_DIRECT\n");
    if (FAILED(StringCchCopy(InputBuffer, sizeof(InputBuffer),
        "this String is from User Application; using METHOD_OUT_DIRECT"))) {
        return;
    }

    memset(OutputBuffer, 0, sizeof(OutputBuffer));

    bRc = DeviceIoControl(hDevice,
        (DWORD)IOCTL_NONPNP_METHOD_OUT_DIRECT,
        InputBuffer,
        (DWORD)strlen(InputBuffer) + 1,
        OutputBuffer,
        sizeof(OutputBuffer),
        &bytesReturned,
        NULL
    );

    if (!bRc)
    {
        printf("Error in DeviceIoControl : : %d", GetLastError());
        return;
    }

    printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);

    return;

}


BOOLEAN
DoFileReadWrite(
    HANDLE HDevice
)
{
    ULONG bufLength, index;
    PUCHAR readBuf = NULL;
    PUCHAR writeBuf = NULL;
    BOOLEAN ret;
    ULONG   bytesWritten, bytesRead;

    //
    // Seed the random-number generator with current time so that
    // the numbers will be different every time we run.
    //
    srand((unsigned)time(NULL));

    //
    // rand function returns a pseudorandom integer in the range 0 to RAND_MAX
    // (0x7fff)
    //
    bufLength = rand();
    //
    // Try until the bufLength is not zero.
    //
    while (bufLength == 0) {
        bufLength = rand();
    }

    //
    // Allocate a buffer of that size to use for write operation.
    //
    writeBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufLength);
    if (!writeBuf) {
        ret = FALSE;
        goto End;
    }
    //
    // Fill the buffer with randon number less than UCHAR_MAX.
    //
    index = bufLength;
    while (index) {
        writeBuf[index - 1] = (UCHAR)rand() % UCHAR_MAX;
        index--;
    }

    printf("Write %d bytes to file\n", bufLength);

    //
    // Tell the driver to write the buffer content to the file from the
    // begining of the file.
    //

    if (!WriteFile(HDevice,
        writeBuf,
        bufLength,
        &bytesWritten,
        NULL)) {

        printf("ReadFile failed with error 0x%x\n", GetLastError());

        ret = FALSE;
        goto End;

    }

    //
    // Allocate another buffer of same size.
    //
    readBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufLength);
    if (!readBuf) {

        ret = FALSE;
        goto End;
    }

    printf("Read %d bytes from the same file\n", bufLength);

    //
    // Tell the driver to read the file from the begining.
    //
    if (!ReadFile(HDevice,
        readBuf,
        bufLength,
        &bytesRead,
        NULL)) {

        printf("Error: ReadFile failed with error 0x%x\n", GetLastError());

        ret = FALSE;
        goto End;

    }

    //
    // Now compare the readBuf and writeBuf content. They should be the same.
    //

    if (bytesRead != bytesWritten) {
        printf("bytesRead(%d) != bytesWritten(%d)\n", bytesRead, bytesWritten);
        ret = FALSE;
        goto End;
    }

    if (memcmp(readBuf, writeBuf, bufLength) != 0) {
        printf("Error: ReadBuf and WriteBuf contents are not the same\n");
        ret = FALSE;
        goto End;
    }

    ret = TRUE;

End:

    if (readBuf) {
        HeapFree(GetProcessHeap(), 0, readBuf);
    }

    if (writeBuf) {
        HeapFree(GetProcessHeap(), 0, writeBuf);
    }

    return ret;


}


#endif