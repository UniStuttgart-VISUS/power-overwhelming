# usbpd
This is a minimal wrapper around the C++ API of the PassMark USB-PD tester. The reason for this library is that we cannot link the C++ API directly, because the power overwhelming library would not load due to missing dependencies if we did so.
