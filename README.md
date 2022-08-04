# Power Overwhelming
This project provides a library for measuring the power consumption of GPUs (and other system components) by various means.


## Building the library
The library is self-contained and most optional external dependencies are in the third_party folder. Make sure that you clone all of the submodules (`git submodule update --init --recursive`). The Visual Studio solution should build right of the box without any further preparation.

### Sensors included in the repository
SDKs included in the repository are the [AMD Display Library (ADL)](https://github.com/GPUOpen-LibrariesAndSDKs/display-library), the [NVIDIA Management Library (NVML)](https://developer.nvidia.com/nvidia-management-library-nvml) and support for [Tinkerforge](https://github.com/Tinkerforge) bricks and bricklets.

### Support for Rohde & Schwarz instruments
The library supports reading Rohde & Schwarz oscilloscopes of the RTB 2000 family and HMC8015 power analysers. In order for this to work, VISA must be installed on the development machine. You can download the drivers from https://www.rohde-schwarz.com/de/driver-pages/fernsteuerung/3-visa-and-tools_231388.html. The VISA installation is automatically detected from the respective property sheet (visa.props). If VISA was found `POWER_OVERWHELMING_WITH_VISA` will be defined. Otherwise, VISA will not be supported and using it will fail at runtime.

Only the power analyser is currently ready to use, **support for automating oscilloscopes is work in progress.**

## Using the library
[Instructions for building the hardware setup](docs/HARDWARE.md)

## Acknowledgments
This work was partially funded by Deutsche Forschungsgemeinschaft (DFG) as part of [SFB/Transregio 161](https://www.sfbtrr161.de) (project ID 251654672).
