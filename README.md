# Power Overwhelming
[![Build Status](https://visualisierungsinstitut.visualstudio.com/Power%20Overwhelming/_apis/build/status/UniStuttgart-VISUS.power-overwhelming?branchName=master)](https://visualisierungsinstitut.visualstudio.com/Power%20Overwhelming/_build/latest?definitionId=5&branchName=master)

This project provides a library for measuring the power consumption of GPUs (and other system components) by various means.

> **Note**
> If you are here for the [instructions for building a bench table for measuring GPU power consumption](docs/HARDWARE.md), look in the `docs` folder. Over there, you also find some [lessons we learned about measuring power with Tinkerforge bricklets.](docs/TINKERFORGE.md)

> **Note**
> The paper "Power Overwhelming: Quantifying the Energy Cost of Visualisation", for which this software was written, can be found on [IEEEXplore](https://doi.org/10.1109/BELIV57783.2022.00009).


## Building the library
The library is self-contained and most optional external dependencies are in the third_party folder. External dependencies from GitHub are fetched by CMake. Once built, the external dependencies are invisible to the user of the library. However, the required DLLs must be present on the target machine. Configure the project using [CMake](https://cmake.org/) and build with Visual Studio or alike.

### Sensors included in the repository
SDKs included in the repository are the [AMD Display Library (ADL)](https://github.com/GPUOpen-LibrariesAndSDKs/display-library), the [NVIDIA Management Library (NVML)](https://developer.nvidia.com/nvidia-management-library-nvml) and support for [Tinkerforge](https://github.com/Tinkerforge) bricks and bricklets. On Windows 11, the [Energy Meter Interface](https://learn.microsoft.com/en-us/windows-hardware/drivers/powermeter/energy-meter-interface) can be used to query the RAPL (Running Average Power Limit Energy Reporting) registers of the system. This sensor might be available on certain Windows 10  installations, but according to a [presentation by the Firefox team](https://fosdem.org/2023/schedule/event/energy_power_profiling_firefox/attachments/slides/5537/export/events/attachments/energy_power_profiling_firefox/slides/5537/FOSDEM_2023_Power_profiling_with_the_Firefox_Profiler.pdf), specialised hardware is supported for that.

### Support for Rohde & Schwarz instruments
The library supports reading Rohde & Schwarz oscilloscopes of the RTB 2000 family and HMC8015 power analysers. In order for this to work, VISA must be installed on the development machine. You can download the drivers from https://www.rohde-schwarz.com/de/driver-pages/fernsteuerung/3-visa-and-tools_231388.html. The VISA installation is automatically detected by CMAKE. If VISA was found `POWER_OVERWHELMING_WITH_VISA` will be defined. Otherwise, VISA will not be supported and using it will fail at runtime.

Only the power analyser is currently ready to use, **support for automating oscilloscopes is work in progress.**

## Using the library
The `podump` demo application is a good starting point to familiarise onself with the library. It contains a sample for each sensor available. Unfortunately, the way sensors are identified and instantiates is dependent on the underlying technology. For instance, ADL allows for creating sensors for the PCI device ID show in Windows task manager whereas NVML uses a custom GUID or the PCI bus ID. Whenever possible, the sensors provide a static factory method `for_all(sensor_type *dst, const std::size_t cnt)` that creates all available sensors of this type. The usage pattern for this API is:
```c++
using namespace visus::power_overwhelming;

std::vector<adl_sensor> sensors;
// Call 'for_all' to determine the required buffer size.
sensors.resize(adl_sensor::for_all(nullptr, 0));
// Call 'for_all' to actually get the sensors.
adl_sensor::for_all(sensors.data(), sensors.size());
```

Some sensors have a slightly different API. For instance, sensors using *Tinkerforge Voltage/Current Bricklets* are not directly created, but require enumerating a descriptor object that in turn can be used to make the sensor:
```c++
using namespace visus::power_overwhelming;

std::vector<tinkerforge_sensor_definiton> descs;
// Call 'get_definitions' to find out how many definitions there are.
descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
// Call 'get_definitions' to get the actual descriptors.
auto cnt = tinkerforge_sensor::get_definitions(descs.data(), descs.size());
// As Tinkerforge sensors can be hot-plugged, it might occur that there are now
// less sensors than initially reported. In this case, we need to truncate the
// array.
if (cnt < descs.size()) {
    descs.resize(cnt);
}

// Create a sensor for each of the descriptors.
std::vector<tinkerforge_sensor> sensors;
sensors.reserve(descs.size());

for (auto& d : descs) {
    // Add a description to the sensors in order to identify them later.
    // Typically, you would have map from the unique UID to a description
    // of what is attached to the bricklet.
    d.description(L"One of my great sensors");
    sensors.emplace_back(d);
}
```

The sensors returned are objects based on the PIMPL pattern. While they cannot be copied, the can be moved around. If the sensor object is destroyed while holding a valid implementation pointer, the sensor itself is freed.

Sensor readings are obtained via the `sample` method. The synchronous one returns a single reading with a a timestamp:
```c++
auto m = sensor.sample();
std::wcout << m.timestamp() << L": S = " << m.power() << " VA << std::endl;
```

If possible, there is also an asynchronous version that delivers samples to a user-specified callback function. When supported by the API, this method uses the asynchronicity of the API. Otherwise, the library will start a sampler thread that regularly calls the synchronous version. Sensors will be grouped into as few sampler threads as possible:
```c++
sensors.sample([](const measurement& m) {
    std::wcout << m.timestamp() << L": S = " << m.power() << " VA << std::endl;
});
// Do something else in this thread; afterwards, stop the asynchronous sampling
// by passing nullptr as callback.
sensor.sample(nullptr);
```

The `collector` class is a convenient way of sampling all sensors the library can find on the system it is running:
```c++
auto collector = collector::for_all(L"output.csv");
collector.start();
// Do something else in this thread; afterwards, stop the collector again.
collector.stop();
```

Using the Tinkerforge bricklets for measuring the power lanes of the GPU requires a custom setup. We have compiled some [instructions](docs/HARDWARE.md) for doing that.

## Extending the library
Adding new kinds of sensors requires several steps. First, a new sensor class is required, which needs to satisfy the following requirements:

* All sensors must inherit from `visus::power_overwhelming::sensor` and implement the interface defined therein.
* The name should end with `_sensor`.
* All implementation details must be hidden from the public interface using the [PIMPL pattern](https://learn.microsoft.com/en-us/cpp/cpp/pimpl-for-compile-time-encapsulation-modern-cpp).
* The sensor class must support move semantics (move constructor and move assignment).
* The sensor class must implement a method `static std::size_t for_all(emi_sensor *out_sensors, const std::size_t cnt_sensors)` that can be used to retrieve all sensors of this kind that are available on the machine. The method shall always return the number of sensors available, even if `out_sensors` is `nullptr` or the buffer is too small to hold all sensors. Sensors shall only be written to `out_sensors` if the buffer is valid and large enough to hold all of them.

Second, in order to be eligible for the automated enumeration by the sensor utility functions,
* a template specialisation of `visus::power_overwhelming::detail::sensor_desc` must be provided in [sensor_desc.h](power_overwhelming/src/sensor_desc.h), which provides means to serialise and deserialise sensors,
* the class must be added to the `sensor_list` template at the bottom of [sensor_desc.h](power_overwhelming/src/sensor_desc.h).

## Acknowledgments
This work was partially funded by Deutsche Forschungsgemeinschaft (DFG) as part of [SFB/Transregio 161](https://www.sfbtrr161.de) (project ID 251654672).
