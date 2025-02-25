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
    .deliver_to([](const sample *samples, std::size_t cnt, const sensor_description *sensors, void *ctx) {
        // Do something with the 'samples' here.
        // You can access the sensor meta data via samples[i].source in 'descs'.
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

## Extending the library
The main motivation for modifying the library is adding additional sensors. The new design of the API directly changes how sensors are implemented and most importantly drastically reduces the amount of code typically required to implement a sensor.

### What's new
The main changes when implementing a sensor are
* Sensors are now fully opaque to the user of the library. There is no need for using the [PIMPL pattern](https://learn.microsoft.com/en-us/cpp/cpp/pimpl-for-compile-time-encapsulation-modern-cpp) anymore. You can use all template classes you desire when implementing your sensor.
* A sensor is no longer a source of a single type of data, but can produce multiple data streams. For instance, the ADL sensor for AMD GPUs wraps a single GPU and produces all data we can get from it. This way, handles and other resources required to produce different data from the same origin can be easily shared.
* Each sensor has a configuration class which allows for specifying implementation-specific data. Typically, these configuration objects to not configure a specific sensor instance, but the whole sensor class. For instance, users can configure the hosts where to look for Tinkerforge bricklets, but they cannot configure individual bricklets in different ways. However, you are in principle free to provide means to address individual sensors in your configuration object.
* Each sensor produces one or more data streams (data of the same type from the same source) which are described via a [sensor_description](power_overwhelming/include/visus/pwrowg/sensor_description.h). The sensor description allows for uniquely identifying a sensor and provides information about the data the sensor produces. One sensor class might have multiple sensor descriptions. For instance, a single ADL sensor provides different power and temperature readings for the GPU it is responsible for. Sensor descriptions are mandatory and can be used by the library to reflect on all available sensors. There is no longer the need to provide special metadata objects, but it is sufficient to fill all the required descriptions.
* A sensor can either produce samples synchronously (by polling) or asynchronously (pushing). The framework will detect the type of sensor via the signature of its `sample` method and automatically poll synchronous sensors. There is no longer the need for sensors to implement synchronous and asynchronous sampling methods.
* A sensor class must be able to enumerate [sensor_descriptions](power_overwhelming/include/visus/pwrowg/sensor_description.h) for all of the data it produces and create actual sensor instances from a list of such descriptions.

### Your sensor class
The framework interacts with your sensor class based on conventions (described below) rather than requiring the implementation of abstract classes. This gives implementors the maximum amount of freedom when designing their classes. The framework even does not require sensors to be copyable, so you can delete the copy constructor and assignment operator. This is actually the recommended way for dealing with a sensor object that manages unique resources like a device or file handle.

Sensor classes are not publicly visible, so they are declared and defined in the [src](power_overwhelming/src) folder and located in the `detail` namespace. It is strongly recommended to use the `PWROWG_DETAIL_NAMESPACE_BEGIN` and `PWROWG_DETAIL_NAMESPACE_END` macros to ensure proper API versioning.

Sensor classes are typically named with the "_sensor" suffix. For instance, if you were to provide a sensor for power readings for a toaster, you would call it `toaster_sensor`.

A sensor class must have the following `public` members:
* A `typedef configuration_type` which refers to the class that users of the library can use to modify the behaviour of the sensor.
* A `typedef list_type` which refers to a container for the sensor. Typically, we use `std::list<>` for that, because it does not have any copyability or constructability requirements. This data structure is not used for obtaining actual samples from the sensors, so it does not need to be maximally efficient. 
* A `static descriptions` method which provides `sensor_description`s for all sensors of the class on the system.
* A `static from_descriptions` which transforms `sensor_description`s into actual sensor instances.
* A `sample` instance method which either synchronously samples the sensor or starts/stops asynchronous sampling.

### The `configuration_type`
The `configuration_type` is a `typedef` for a [public API](power_overwhelming/include/visus/pwrowg/) that allows the users to influence the behaviour of your sensors. Your configuration class can also be empty if there is nothing to configure, but it must exist and it must be unique. Typically, the configuration class is named with the suffix "_configuration". For the above-mentioned toaster example, it would be called `toaster_configuration`.

The sensor class must fulfill two requirements:
* It must derive from [`sensor_configuration`](power_overwhelming/include/visus/pwrowg/sensor_configuration.h).
* It must have a member `static const guid id`, which is a unique GUID for your sensor.
* It must be copyable.
* It must be located in the public namespace. It is strongly recommended to use the `PWROWG_NAMESPACE_BEGIN` and `PWROWG_NAMESPACE_END` macros to ensure proper API versioning.
* It must not use `template` members, including classes like `std::string`. If you need to store dynamically allocated string, use a [`blob`](power_overwhelming/include/visus/pwrowg/blob.h), manage your memory manually or use the [PIMPL pattern](https://learn.microsoft.com/en-us/cpp/cpp/pimpl-for-compile-time-encapsulation-modern-cpp).

### The `descriptions` methods
A sensor must return descriptions for all kinds of data it can produce on a system via a method 
```c++
static std::size_t descriptions(sensor_description *dst, std::size_t cnt, configuration_type& config);
```
The caller provides a buffer `dst` for at most `cnt` descriptions. This buffer may also be `nullptr`, in which case the method shall write nothing, but still return the required number of elements in `dst`. The framework will call the method once `descriptions(nullptr, 0)` to measure the required buffer size and afterwards with the actual buffer and its size.

Sensors that rely on dynamic discovery of devices, for instance via USB enumeration, should make best efforts to report the required buffer size. If the situation changes between calls due to hardware being unplugged, the method shall return the maximum possible number of sensors in the given buffer and discard the remaining ones. In any case, a call to the method made with a valid, non-empty buffer must always return the number of valid elements that have been written to the buffer.

The [sensor_descriptions](power_overwhelming/include/visus/pwrowg/sensor_description.h) is mostly a read-only class. In order to fill it, sensors must use a [sensor_description_builder](power_overwhelming/src/sensor_description_builder.h). Sensors must fill all properties of the description class except for the user-defined label, which can be modified later.

### The `from_descriptions` method

### The `sample` method

### Registering your sensor
All sensors are centrally registered at one place, in the [`sensor_registry`](power_overwhelming/src/sensor_registry.h). Just add your class in the `typedef` at the bottom of the file.

## Acknowledgments
This work was partially funded by Deutsche Forschungsgemeinschaft (DFG) as part of [SFB/Transregio 161](https://www.sfbtrr161.de) (project ID 251654672).
