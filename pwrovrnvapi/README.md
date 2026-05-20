# Power Over NVAPI
This is a wrapper around the NDA-version of NVAPI, which allows for calling a selected subset of the functions available in the API by name.

## Rationale
NVAPI is installed along with NVIDIA's drivers, but its functions are not exported by name, so it is very hard to call them when loading the library dynamically. As we do not want Power Overwhelming to depend on the NVAPI library, we cannot link the main DLL using the import library that comes with the SDK. Doing so would crash any application using Power Overwhelming at startup unless the NVIDIA driver is present on the system.

In order to word around this issue, the `pwrovrnvapi` uses the import library to call into NVAPI and exposes exactly the functions we need by name. Power Overwhelming then dynamically loads `pwrovrnvapi` and retrieves the entry points using `GetProcAddress`. Loading the wrapper might fail if NVAPI is not present on the system. However, as we do that manually, we can choose to ignore the issue as we do for any vendor-specific library.
