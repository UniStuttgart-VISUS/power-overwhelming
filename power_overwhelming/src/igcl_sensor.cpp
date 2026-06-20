// <copyright file="igcl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_sensor.h"

#include <array>
#include <limits>
#include <stdexcept>

#include "igcl_error_category.h"
#include "fnv1a.h"


/// <summary>
/// Creates a sample from IGCL data, possibly narrowing the precision. This
/// builder class is required to coerce the types used by Intel, which are
/// more than what we support, into one of the supported reading types.
/// </summary>
template<class TType,
    bool Float = std::is_floating_point_v<TType>,
    bool Unsigned = std::is_unsigned_v<TType>>
struct sample_builder;

/// <summary>
/// Specialisation for floating-point samples.
/// </summary>
template<class TType>
struct sample_builder<TType, true, false> final {
    static inline PWROWG_NAMESPACE::sample build(
            _In_ const PWROWG_NAMESPACE::sample::source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp time,
            _In_ const TType value) {
        return PWROWG_NAMESPACE::sample(source, time,
            static_cast<float>(value));
    }
};

/// <summary>
/// Specialisation for signed integer samples.
/// </summary>
template<class TType>
struct sample_builder<TType, false, false> final {
    static inline PWROWG_NAMESPACE::sample build(
            _In_ const PWROWG_NAMESPACE::sample::source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp time,
            _In_ const TType value) {
        typedef std::int32_t sample_type;
        assert(value >= (std::numeric_limits<sample_type>::min)());
        assert(value <= (std::numeric_limits<sample_type>::max)());
        return PWROWG_NAMESPACE::sample(source, time,
            static_cast<sample_type>(value));
    }
};

/// <summary>
/// Specialisation for unsigned integer samples.
/// </summary>
template<class TType>
struct sample_builder<TType, false, true> final {
    static inline PWROWG_NAMESPACE::sample build(
            _In_ const PWROWG_NAMESPACE::sample::source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp time,
            _In_ const TType value) {
        typedef std::uint32_t sample_type;
        assert(value >= (std::numeric_limits<sample_type>::min)());
        assert(value <= (std::numeric_limits<sample_type>::max)());
        return PWROWG_NAMESPACE::sample(source, time,
            static_cast<sample_type>(value));
    }
};


/// <summary>
/// A specialised builder that keeps track of the sample history of an energy
/// counter to compute the instantaneous power draw.
/// </summary>
template<class TTraits> struct power_sample_builder final {

    /// <summary>
    /// The type to represent fractional seconds when computing power from the
    /// energy and time difference.
    /// </summary>
    typedef std::chrono::duration<float> seconds_type;

    /// <summary>
    /// The type traits extracting the energy values.
    /// </summary>
    typedef TTraits type_traits;

    /// <summary>
    /// The offset of the field holding the energy in the telemetry.
    /// </summary>
    std::size_t offset;

    /// <summary>
    /// The previous energy reading.
    /// </summary>
    float previous_energy;

    /// <summary>
    /// The timestamp of the previous sample.
    /// </summary>
    PWROWG_NAMESPACE::timestamp previous_time;

    /// <summary>
    /// Initialses a new instance.
    /// </summary>
    inline power_sample_builder(_In_ const std::size_t offset) noexcept
        : offset(offset), previous_time(0) { }

    /// <summary>
    /// Computes the next sample from the given energy sample
    /// </summary>
    inline PWROWG_NAMESPACE::sample operator ()(
            PWROWG_NAMESPACE::sample::source_type source,
            const PWROWG_NAMESPACE::timestamp timestamp,
            const ctl_power_telemetry_t& telemetry) {
        auto& v = PWROWG_DETAIL_NAMESPACE::member_at<ctl_oc_telemetry_item_t>(
            telemetry, this->offset);
        assert(v.bSupported);
        assert(v.units == CTL_UNITS_ENERGY_JOULES);

        const auto energy = type_traits::get(v);
        auto value = 0.0f;
        auto time = timestamp;

        if (this->previous_time != PWROWG_NAMESPACE::timestamp::zero) {
            assert(this->previous_time <= timestamp);
            const auto dt = timestamp - this->previous_time;
            const auto de = std::abs(energy - this->previous_energy);
            const auto i = std::chrono::duration_cast<seconds_type>(dt);
            time = this->previous_time + 0.5f * dt;
            value = de / i.count();
        }

        this->previous_time = timestamp;
        this->previous_energy = static_cast<float>(energy);

        return PWROWG_NAMESPACE::sample(source, time, value);
    }
};


/// <summary>
/// Retrieves all devices handles from the given library scope.
/// </summary>
static std::vector<ctl_device_adapter_handle_t> devices(
        _In_ PWROWG_DETAIL_NAMESPACE::igcl_scope& scope) {
    using namespace PWROWG_DETAIL_NAMESPACE;
    std::uint32_t cnt = 0;
    throw_if_igcl_failed(igcl_library::instance()
        ._ctlEnumerateDevices(scope, &cnt, nullptr));

    std::vector<ctl_device_adapter_handle_t> retval(cnt);
    throw_if_igcl_failed(igcl_library::instance()
        ._ctlEnumerateDevices(scope, &cnt, retval.data()));

    return retval;
}


/// <summary>
/// Adds, if available and representable in Power Overwhelming, the descrption
/// of the given telementry <paramref name="item" /> to the builder and returns
/// whether it should be emitted or not. The pointer to the
/// <paramref name="item" /> must point to an element of the given
/// <paramref name="telemetry" /> for the function to work correctly.
/// </summary>
static bool describe(
        _Inout_ PWROWG_DETAIL_NAMESPACE::sensor_description_builder& builder,
        _In_ const std::wstring& path,
        _In_z_ const char *dev_name,
        _In_z_ const wchar_t *sensor_name,
        _In_z_ const wchar_t *sensor_id,
        _In_ const ctl_power_telemetry_t* telemetry,
        _In_ const ctl_oc_telemetry_item_t* item) {
    assert(dev_name != nullptr);
    assert(sensor_name != nullptr);
    assert(sensor_id != nullptr);
    assert(telemetry != nullptr);
    assert(item != nullptr);
    using namespace PWROWG_NAMESPACE;
    using namespace PWROWG_DETAIL_NAMESPACE;
    typedef std::decay_t<decltype(*item)> item_type;
    auto retval = false;

    // Dispatch the unit measured first, which tells us whether we can support
    // the telemetry.
    dispatch_igcl_unit_traits(*item, [&](auto tag) {
        typedef std::remove_pointer_t<decltype(tag)> unit_traits;
        if (!(retval = unit_traits::supported)) {
            return;
        }

        if (!(retval = item->bSupported)) {
            return;
        }

        builder.with_name(L"%hs %s (IGCL)", dev_name, sensor_name);
        builder.with_id(L"IGCL/%s/%s", path.c_str(), sensor_id);
        builder.with_type(sensor_type::gpu  | sensor_type::software
            | unit_traits::type);
        builder.measured_in(unit_traits::unit);

        // Next, we need to find out what kind of values we get. This allows for
        // intantiating the correct conversion from IGCL telemetry to our sample
        // type.
        dispatch_igcl_data_type_traits(*item, [&](auto tag) {
            typedef std::remove_pointer_t<decltype(tag)> type_traits;
            const auto o = member_offset(telemetry, item);

            builder.produces(type_traits::reading_type);

            builder.with_new_private_data<igcl_sensor::sample_builder>([o](
                    const sample::source_type source,
                    const timestamp time,
                    const ctl_power_telemetry_t& data) {
                auto v = type_traits::get(member_at<item_type>(data, o));
                typedef std::decay_t<decltype(v)> value_type;
                return sample_builder<value_type>::build(source, time, v);
            });
        });
    });

    return retval;
}


/// <summary>
/// Adds a Boolean telemetry item to the <paramref name="builder" />, which is
/// used for the throttling states of the card. The pointer to the
///  <paramref name="item" /> must point to an element of the given
/// <paramref name="telemetry" /> for the function to work correctly.
/// </summary>
static bool describe(
        _Inout_ PWROWG_DETAIL_NAMESPACE::sensor_description_builder& builder,
        _In_ const std::wstring& path,
        _In_z_ const char *dev_name,
        _In_z_ const wchar_t *sensor_name,
        _In_z_ const wchar_t *sensor_id,
        _In_ const PWROWG_NAMESPACE::sensor_type type,
        _In_ const ctl_power_telemetry_t* telemetry,
        _In_ const bool* item) {
    assert(dev_name != nullptr);
    assert(sensor_name != nullptr);
    assert(sensor_id != nullptr);
    assert(telemetry != nullptr);
    assert(item != nullptr);
    using namespace PWROWG_NAMESPACE;
    using namespace PWROWG_DETAIL_NAMESPACE;
    typedef std::decay_t<decltype(*item)> item_type;

    builder.with_name(L"%hs %s (IGCL)", dev_name, sensor_name);
    builder.with_id(L"IGCL/%s/%s", path.c_str(), sensor_id);
    builder.with_type(sensor_type::gpu | sensor_type::software | type);
    builder.produces(reading_type::unsigned_integer);
    builder.measured_in(reading_unit::unknown);

    const auto o = member_offset(telemetry, item);
    builder.with_new_private_data<igcl_sensor::sample_builder>([o](
            const sample::source_type source,
            const timestamp time,
            const ctl_power_telemetry_t& data) {
        auto v = static_cast<std::uint32_t>(member_at<item_type>(data, o));
        return sample(source, time, v);
    });

    return true;
}


/// <summary>
/// Adds the description of a power sensor that is derived from the given energy
/// counter.
/// </summary>
static bool describe_power(
        _Inout_ PWROWG_DETAIL_NAMESPACE::sensor_description_builder& builder,
        _In_ const std::wstring& path,
        _In_z_ const char *dev_name,
        _In_z_ const wchar_t *sensor_name,
        _In_z_ const wchar_t *sensor_id,
        _In_ const ctl_power_telemetry_t* telemetry,
        _In_ const ctl_oc_telemetry_item_t* item) {
    assert(dev_name != nullptr);
    assert(sensor_name != nullptr);
    assert(sensor_id != nullptr);
    assert(telemetry != nullptr);
    assert(item != nullptr);
    using namespace PWROWG_NAMESPACE;
    using namespace PWROWG_DETAIL_NAMESPACE;
    typedef std::decay_t<decltype(*item)> item_type;
    auto retval = false;

    // Dispatch the unit measured first, which tells us whether we can support
    // the telemetry.
    dispatch_igcl_unit_traits(*item, [&](auto tag) {
        typedef std::remove_pointer_t<decltype(tag)> unit_traits;
        if (!(retval = unit_traits::supported)) {
            return;
        }

        if (!(retval = (unit_traits::type == sensor_type::energy))) {
            // Power sensors can only be derived from energy counters.
            return;
        }

        if (!(retval = item->bSupported)) {
            return;
        }

        builder.with_name(L"%hs %s (IGCL)", dev_name, sensor_name);
        builder.with_id(L"IGCL/%s/%s", path.c_str(), sensor_id);
        builder.with_type(sensor_type::gpu  | sensor_type::software
            | sensor_type::power);
        builder.produces(reading_type::floating_point);
        builder.measured_in(reading_unit::watt);

        // Next, we need to find out what kind of values we get. This allows for
        // intantiating a power_sample_builder performing the correct conversion.
        dispatch_igcl_data_type_traits(*item, [&](auto tag) {
            typedef std::remove_pointer_t<decltype(tag)> type_traits;
            const auto o = member_offset(telemetry, item);
            builder.with_new_private_data<igcl_sensor::sample_builder>(
                power_sample_builder<type_traits>(o));
        });
    });

    return retval;
}

/// <summary>
/// Compute a hash of the given adapter properties (except for the reserved
/// part at the end of the structure).
/// </summary>
static std::uint64_t hash(_In_ const ctl_device_adapter_properties_t& p) {
    PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint64_t> retval;
    retval(reinterpret_cast<const std::uint8_t*>(&p),
        reinterpret_cast<const std::uint8_t*>(&p.reserved));
    return retval;
}


/// <summary>
/// Generates a unique ID for the given adapter.
/// </summary>
static std::wstring path(_In_ const ctl_device_adapter_properties_t& p) {
    if ((p.adapter_bdf.bus == 0)
            && (p.adapter_bdf.device == 0)
            && (p.adapter_bdf.function == 0)) {
        // IGCL is too old, we cannot use the PCI location. We generate a hash
        // which hopefully uniquely identifies the GPU.
        return std::to_wstring(hash(p));

    }
    else {
        return std::to_wstring(p.adapter_bdf.bus) + L":"
            + std::to_wstring(p.adapter_bdf.device) + L"."
            + std::to_wstring(p.adapter_bdf.function);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::igcl_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::igcl_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Intel")
        .with_class(configuration_type::id);

    try {
        // Get handles for all devices.
        igcl_scope scope;
        auto devices = ::devices(scope);
        std::size_t retval = 0;

        // Add the current content of the 'builder' to 'dst' if there is enough
        // space for another item and unconditionally count the number of
        // elements in 'retval'
        const auto output = [&retval, dst, cnt, &builder](void) {
            if ((dst != nullptr) && (retval < cnt)) {
                dst[retval] = builder.build();
            }
            ++retval;
        };

        // Create descriptors for each device.
        for (auto& d : devices) {
            ctl_device_adapter_properties_t dev_props { };
            dev_props.Size = sizeof(dev_props);
            dev_props.Version = 2;
            ctl_power_telemetry_t telemetry { };
            telemetry.Size = sizeof(telemetry);
            telemetry.Version = 1;

            throw_if_igcl_failed(igcl_library::instance()
                ._ctlGetDeviceProperties(d, &dev_props));
            throw_if_igcl_failed(igcl_library::instance()
                ._ctlPowerTelemetryGet(d, &telemetry));

            // The path is the same for all devices as we use it to group all
            // telemetry from a single source into one sensor.
            const auto dev_path = ::path(dev_props);
            builder.with_path(dev_path);

            // Describes the specified telemetry item 't' and answers whether
            // it should be added to the output.
            const auto describe_telemetry = [&](const wchar_t *n,
                    const wchar_t *i,
                    const ctl_oc_telemetry_item_t *t) {
                return ::describe(builder, dev_path, dev_props.name, n, i,
                    &telemetry, t);
            };

            // Tries to construct a power sensor from an energy counter and
            // answers whether this was successful.
            const auto describe_power = [&](const wchar_t *n,
                    const wchar_t *i,
                    const ctl_oc_telemetry_item_t *t) {
                return ::describe_power(builder, dev_path, dev_props.name, n, i,
                    &telemetry, t);
            };

            // Describes the specified throttling indicator 't' and answers
            // whether it should be added to the output.
            const auto describe_throttling = [&](const wchar_t *n,
                    const wchar_t *i,
                    const bool *t) {
                return ::describe(builder, dev_path, dev_props.name, n, i,
                    sensor_type::throttling, &telemetry, t);
            };

            // Add the telemetry data.
            if (describe_telemetry(L"GPU Energy Counter", L"GPU-Energy",
                    &telemetry.gpuEnergyCounter)) {
                output();
            }

            if (describe_power(L"GPU Power", L"GPU-Power",
                    &telemetry.gpuEnergyCounter)) {
                output();
            }

            if (describe_telemetry(L"GPU Voltage", L"GPU-Voltage",
                    &telemetry.gpuVoltage)) {
                output();
            }

            if (describe_telemetry(L"GPU Temperature", L"GPU-Temperature",
                    &telemetry.gpuCurrentTemperature)) {
                output();
            }

            if (describe_telemetry(L"VRAM Energy Counter", L"VRAM-Energy",
                    &telemetry.vramEnergyCounter)) {
                output();
            }

            if (describe_power(L"VRAM Power", L"VRAM-Power",
                    &telemetry.vramEnergyCounter)) {
                output();
            }

            if (describe_telemetry(L"VRAMVoltage", L"VRAM-Voltage",
                    &telemetry.vramVoltage)) {
                output();
            }

            if (describe_telemetry(L"VRAM Temperature", L"VRAM-Temperature",
                    &telemetry.vramCurrentTemperature)) {
                output();
            }

            for (std::size_t p = 0; p < CTL_PSU_COUNT; ++p) {
                std::wstring psu(L"PSU");
                psu += std::to_wstring(p);

                auto name = psu + L" Energy Counter";
                auto id = psu + L"-Energy";
                if (describe_telemetry(name.c_str(), id.c_str(),
                        &telemetry.psu[p].energyCounter)) {
                    output();
                }

                name = psu + L" Power";
                id = psu + L"-Power";
                if (describe_power(name.c_str(), id.c_str(),
                        &telemetry.psu[p].energyCounter)) {
                    output();
                }

                name = psu + L" Voltage";
                id = psu + L"-Voltage";
                if (describe_telemetry(name.c_str(), id.c_str(),
                        &telemetry.psu[p].voltage)) {
                    output();
                }
            } /* for (std::size_t p = 0; p < CTL_PSU_COUNT; ++p) */

            // Add all the throttling indicators.
            if (describe_throttling(L"GPU Power-Limited",
                    L"GPU-Power-Limited",
                    &telemetry.gpuPowerLimited)) {
                output();
            }

            if (describe_throttling(L"GPU Temperature-Limited",
                    L"GPU-Temperature-Limited",
                    &telemetry.gpuTemperatureLimited)) {
                output();
            }

            if (describe_throttling(L"GPU Current-Limited",
                    L"GPU-Current-Limited",
                    &telemetry.gpuCurrentLimited)) {
                output();
            }

            if (describe_throttling(L"GPU Voltage-Limited",
                    L"GPU-Voltage-Limited",
                    &telemetry.gpuVoltageLimited)) {
                output();
            }

            if (describe_throttling(L"GPU Utilisation-Limited",
                    L"GPU-Utilisation-Limited",
                    &telemetry.gpuUtilizationLimited)) {
                output();
            }
        } /* for (auto& d : devices) */

        return retval;
    } catch (...) {
        // Probably no Intel GPU, ignore it.
        return 0;
    }
    return 0;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::igcl_sensor
 */
PWROWG_DETAIL_NAMESPACE::igcl_sensor::igcl_sensor(
        _In_ const std::wstring& path,
        _In_ const std::size_t index,
        _Inout_ std::vector<sample_builder>&& builders)
    : _builders(std::move(builders)),
        _device(nullptr),
        _index(index),
        _offset(0) {
    // Search for the adapter that produces the specified hash for its
    // properties. The reason for this implementation is that the device handle
    // is tied to the igcl_scope taht was used to enumerate it. As each sensor
    // has its own scope, we need to re-open the devices here.
    const auto devices = ::devices(this->_scope);
    for (auto& d : devices) {
        ctl_device_adapter_properties_t dev_props { };
        dev_props.Size = sizeof(dev_props);
        dev_props.Version = 2;
        throw_if_igcl_failed(igcl_library::instance()
            ._ctlGetDeviceProperties(d, &dev_props));
        const auto p = ::path(dev_props);
        if (path == p) {
            this->_device = d;
            break;
        }
    }

    // Create a dispatcher for delivering a sample from telemetry data.
    this->_deliver_sample = make_igcl_telemetry_disps<timestamp, std::size_t,
            const sensor_array_callback, const sensor_description *, void *>(
        [this](auto value, const ctl_units_t, timestamp timestamp,
                const std::size_t index, const sensor_array_callback callback,
                const sensor_description *sensors, void *context) {
            PWROWG_NAMESPACE::sample s(index, timestamp);
            callback(&s, 1, sensors, context);
        });

    // Create a dispatcher for generating a timestamp from a sample.
    this->_make_timestamp = make_igcl_telemetry_disps<timestamp&>(
        [this](auto value, const ctl_units_t, timestamp& retval) {
            assert(std::is_floating_point_v<std::decay_t<decltype(value)>>);
            retval = this->make_timestamp(value);
        });

    // Allocate a buffer to collect the samples that are delivered at once. The
    // size of this buffer never changes; there is always one for each builder.
    // As we need the history of the last sample to compute the instantaneous
    // power draw, allocate twice the size of what we need to preserve the last
    // result.
    this->_samples.resize(this->_builders.size());
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    // Get the telemetry data from the device.
    ctl_power_telemetry_t telemetry { };
    telemetry.Size = sizeof(telemetry);
    telemetry.Version = 1;

    throw_if_igcl_failed(igcl_library::instance()
        ._ctlPowerTelemetryGet(this->_device, &telemetry));

    // Convert the timestamp of the sample. This is the same for all data
    // points, so we do it only once.
    timestamp timestamp;
    find_igcl_telemetry_disp(this->_make_timestamp, telemetry.timeStamp)(
        telemetry.timeStamp, timestamp);

    // Collect the samples for all reading enabled via the '_builders'.
    assert(this->_samples.size() >= this->_builders.size());
    for (std::size_t i = 0; i < this->_builders.size(); ++i) {
        this->_samples[i] = this->_builders[i](this->_index + i, timestamp,
            telemetry);
    }

    // Deliver the data.
    callback(this->_samples.data(), this->_samples.size(), sensors, context);
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::time_sync
 */
void PWROWG_DETAIL_NAMESPACE::igcl_sensor::time_sync(
        _In_ std::size_t samples) {
    using namespace std::chrono;

    const auto sample = [](void) {
        const auto s = timestamp::now();
#if (_WIN32_WINNT >= 0x0600)
        const auto t = std::chrono::milliseconds(::GetTickCount64());
#else /* (_WIN32_WINNT >= 0x0600) */
        const auto t = std::chrono::milliseconds(::GetTickCount());
#endif /* (_WIN32_WINNT >= 0x0600) */
        return std::make_pair(s, t);
    };

    if (samples < 1) {
        samples = 1;
    }

    this->_offset = std::chrono::duration<double>(0);
    for (std::size_t i = 0; i < samples; ++i) {
        const auto s = sample();
        const auto d = (s.first - timestamp::from_duration(s.second));
        this->_offset += (d - this->_offset) / (i + 1.0);
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
