/*
 * Interface to ftdiUnixHelper dynamic library.
 *************************************/

#include "WinTypes.h"

//
// Exported functions start here.
//

// Create an FTDI EVENT_HANDLE structure.
extern "C" EVENT_HANDLE* NativeCreateFtdiEventHandle();

// Wait on the FTDI EVENT_HANDLE for period of time specified in timeout.
extern "C" int NativeEventTimedWait(EVENT_HANDLE* pEventHandle, int timeoutSecs, int timeoutMs);

// Signal the FTDI EVENT_HANDLE.
extern "C" bool NativeEventSignal(EVENT_HANDLE* pEventHandle);

// Destroy an FTDI EVENT_HANDLE structure.
extern "C" bool NativeDestroyFtdiEventHandle(EVENT_HANDLE* pEventHandle);

extern "C" float NativeGetCurrentVersion();

extern "C" float NativeGetCompatibilityVersion();

//
// Private internal functions start here.
//

// Some private logging methods
void LogMessage(std::string logMessage);
void LogDebugMessage(std::string logMessage);

//
// Useful template function for converting the version defines to a string to return, i.e. convert a float like "0.500000" to what it originally was, i.e. "0.5"
//
//	Copied from:
//
//		https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values/16606128#16606128
// 		
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6);
