# Power Overwhelming
[![Build Status](https://visualisierungsinstitut.visualstudio.com/Power%20Overwhelming/_apis/build/status/UniStuttgart-VISUS.power-overwhelming?branchName=master)](https://visualisierungsinstitut.visualstudio.com/Power%20Overwhelming/_build/latest?definitionId=5&branchName=master)

This project provides a library for measuring the power consumption of GPUs (and other system components) by various means.

> **Note**
> If you are here for the [instructions for building a bench table for measuring GPU power consumption](docs/HARDWARE.md), look in the `docs` folder. Over there, you also find some [lessons we learned about measuring power with Tinkerforge bricklets.](docs/TINKERFORGE.md)

> **Note**
> The papers "Power Overwhelming: Quantifying the Energy Cost of Visualisation" and "Power overwhelming: The One With the Oscilloscopes", for which this software was written, can be found on [IEEEXplore](https://doi.org/10.1109/BELIV57783.2022.00009) and on [Springer Link](https://dx.doi.org/10.1007/s12650-024-01001-0) respectively.

## What's new in version 2.x?
1. The namespace of the library has been changed from `visus::power_overwhelming` to `visus::pwrowg`. Furthermore, ABI versioning via an `inline` namespace has been added.
1. Access to individual sensors has been removed. All sensors must be managed via the `visus::pwrowg::sensor_array`.
1. Synchronous APIs have been removed in favour of a "Don't call us, we call you" approach. All sensor data must be retrieved using callbacks passed to the `visus::pwrowg::sensor_array`.
1. All oscilloscope-related APIs have been renamed to `rtx_...` to indicate that they only support Rohde & Schwarz RTA and RTB series oscilloscopes.
1. All HMC 8015-related APIs have been renamed to `hmc8015_...` to indicate that they are specifically for these devices.
1. All Tinkerforge-related APIs have been renamed to `tinkerforge_...` to indicate that they are specifically for these devices.

## Building the library
The library is self-contained and most optional external dependencies are in the third_party folder. External dependencies from GitHub are fetched by CMake. Once built, the external dependencies are invisible to the user of the library. However, the required DLLs must be present on the target machine. Configure the project using [CMake](https://cmake.org/) and build with Visual Studio or alike.

### Sensors included in the repository
SDKs included in the repository are the [AMD Display Library (ADL)](https://github.com/GPUOpen-LibrariesAndSDKs/display-library), the [NVIDIA Management Library (NVML)](https://developer.nvidia.com/nvidia-management-library-nvml) and support for [Tinkerforge](https://github.com/Tinkerforge) bricks and bricklets. On Windows 11, the [Energy Meter Interface](https://learn.microsoft.com/en-us/windows-hardware/drivers/powermeter/energy-meter-interface) can be used to query the RAPL (Running Average Power Limit Energy Reporting) registers of the system. This sensor might be available on certain Windows 10  installations, but according to a [presentation by the Firefox team](https://fosdem.org/2023/schedule/event/energy_power_profiling_firefox/attachments/slides/5537/export/events/attachments/energy_power_profiling_firefox/slides/5537/FOSDEM_2023_Power_profiling_with_the_Firefox_Profiler.pdf), specialised hardware is required for that. The `msr_sensor` provides access to the RAPL registers on Linux and on Windows systems that run the [pwrowgrapdrv driver](pwrowgrapldrv/README.md).

### Support for Rohde & Schwarz instruments
The library supports reading Rohde & Schwarz oscilloscopes of the RTB 2000 family and HMC8015 power analysers. In order for this to work, VISA must be installed on the development machine. You can download the drivers from https://www.rohde-schwarz.com/de/driver-pages/fernsteuerung/3-visa-and-tools_231388.html. The VISA installation is automatically detected by CMAKE. If VISA was found `POWER_OVERWHELMING_WITH_VISA` will be defined. Otherwise, VISA will not be supported and using it will fail at runtime.

Only the power analyser is currently ready to use, **support for automating oscilloscopes is work in progress.**

## Using the library
In order to sample current, voltage and power samples, create a `sensor_array` for the sensors you are interested in. You can retrieve `sensor_description`s for all available sensors as follows:
```c++
using namespace visus::pwrowg;

// Create a configuration object to adjust the overall behaviour of the sensor
// families and potentially adjust specific ones. In this example, we modify
// how the Tinkerforge bricklets behave, but you can adjust the configuration
// object for each available sensor in a similar way.
sensor_array_configuration config;

config.sample_every(std::chrono::milliseconds(5))
    .deliver_sensors_as_context()
    .deliver_to([](std::size_t idx, const sample *samples, std::size_t cnt, void *ctx) {
        auto descs = static_cast<sensor_description *>(ctx);
        // Do something with the 'samples' here.
        // You can access the sensor meta data via 'idx' in 'descs'.
    })
    .configure<tinkerforge_configuration>([](tinkerforge_configuration& c) {
        // This is only an example which sets the timeout for connecting to
        // brickd to two seconds. Different sensor families might provide
        // different configuration options.
        c.timeout(std::chrono::seconds(2));
    });

std::vector<sensor_description> descs;
// Call 'all_descriptions' to determine the required buffer size.
sensors.resize(sensor_array::all_descriptions(nullptr, 0, config));
// Call 'all_descriptions' to actually get the descriptions.
const auto cnt = sensor_array::all_descriptions(descs.data(), descs.size());

// Create a sensor array for all sensors described in 'descs'. Note that using
// the size of 'descs' here would be unsafe in case plug-and-play sensors are
// involved which could be disconnected between enumerating them and creating
// the sensor array.
sensor_array sensors(std::move(config), descs.data(), cnt);
```

> [!NOTE]
> Note that the `sensor_array` takes ownership of the `sensor_array_configuration`. You cannot use it anymore once the array has created from it.

If you want to limit the sensors in your sensor array, you can filter `descs` before creating the array. Alternatively, there is a convenience method that does this for you by means of a unary predicate on the descriptions:
```c++
using namespace visus::pwrowg;

sensor_array_configuration config;

// Configure behaviour of sensors here as necessary.

auto sensors = sensor_array::for_matches(std::move(config), is_power_sensor);
```
The `is_power_sensor` predicate is a [built-in one](power_overwhelming/include/visus/pwrowg/sensor_filters.h) selecting only sensors of type `sensor_type::power`, but you can provide any unary predicate on `sensor_description` to select the sensors you are interested in. The library also supports different methods of combining filters out of the box:
```c++
using namespace visus::pwrowg;

// Create sensors for driver-based sensors by the GPU vendors:
{
    sensor_array_configuration config;
    auto sensors = sensor_array::for_matches(std::move(config), is_all_sensor_types_of<sensor_type::gpu, sensor_type::software>);
}

// Create all available current and voltage sensors:
{
    sensor_array_configuration config;
    auto sensors = sensor_array::for_matches(std::move(config), is_any_of<is_current_sensor, is_voltage_sensor>);
}
```


Instead of using a filter that allows all sensors, you can use the following shortcut:
```c++
using namespace visus::pwrowg;

sensor_array_configuration config;

// Configure behaviour of sensors here as necessary.

auto sensors = sensor_array::for_all(std::move(config));
```

Once you have created a sensor array, you can start receving samples to the configured callback:
```c++
sensors.start();
// Perform the work you want to benchmark and stop the sensors afterwards.
sensors.stop();
```


**TODO**

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

The specialisation of `visus::power_overwhelming::detail::sensor_desc` must fulfil the following contract:
* It must have a member `static constexpr const char *type_name` specifing the unique name of the sensor, which can be declared using the `POWER_OVERWHELMING_DECLARE_SENSOR_NAME` macro.
* It must have a member `static constexpr bool intrinsic_async` specifying whether the sensor can run asynchronously without emulating it by starting a sampler thread that regularly polls the sensor. You can use the `POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC` to declare this member.
* It must have a method `static inline nlohmann::json serialise(const value_type& value)` which serialises the given sensor into a JSON representation. The JSON representation must be an object which contains a string field named "type" (use the `visus::power_overwhelming::detail::json_field_type` constant in [sensor_desc.h](power_overwhelming/src/sensor_desc.h) for the name) which has the `type_name` constant as its value. This field is used in conjunction with the aforementioned `sensor_list` to automatically dispatch deserialisation to your specialisation of the traits class. 
* It must have a method `static inline value_type deserialise(const nlohmann::json& value)` which restores a sensor from a given JSON representation.
* If the sensor can serialise all of its instances more efficiently than creating an instance of it and converting these instances to JSON, it can implement a method `static inline nlohmann::json serialise_all(void)` which serialises all sensors into a JSON array. The library will prefer this method if it is provided.

## Acknowledgments
This work was partially funded by Deutsche Forschungsgemeinschaft (DFG) as part of [SFB/Transregio 161](https://www.sfbtrr161.de) (project ID 251654672).
