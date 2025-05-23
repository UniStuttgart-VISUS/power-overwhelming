// <copyright file="sensor_array_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2025 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(sensor_array_test) {

public:

    TEST_METHOD(test_configuration) {
        sensor_array_configuration config;
#if defined(POWER_OVERWHELMING_WITH_NVML)
        config.configure<nvml_configuration>([](nvml_configuration& c) {
            Assert::IsTrue(true, L"NVML configure called.", LINE_INFO());
        });
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
        config.configure<msr_configuration>([](msr_configuration& c) {
            Assert::IsTrue(true, L"MSR configure called.", LINE_INFO());
        });
    }

    TEST_METHOD(test_descriptions) {
        sensor_array_configuration config;

        std::vector<sensor_description> descs;
        descs.resize(sensor_array::all_descriptions(nullptr, 0, config));
        const auto actual = sensor_array::all_descriptions(descs.data(), descs.size(), config);
        Assert::AreEqual(descs.size(), actual, L"All descriptions retrieved", LINE_INFO());
    }

    TEST_METHOD(test_ctor) {
        sensor_array_configuration config;

        std::vector<sensor_description> descs;
        descs.resize(sensor_array::all_descriptions(nullptr, 0, config));
        sensor_array::all_descriptions(descs.data(), descs.size(), config);

        sensor_array sensors(std::move(config), descs.data(), descs.size());
    }

    TEST_METHOD(test_for_matches) {
        {
            sensor_array_configuration config;

            config.configure<tinkerforge_configuration>([](tinkerforge_configuration &c) {
                c.current_conversion_time(tinkerforge_conversion_time::microseconds_140);
            });

            auto sensors = sensor_array::for_matches(std::move(config), is_current_sensor);
            for (std::size_t i = 0; i < sensors.size(); ++i) {
                Assert::IsTrue(sensors[i].is_sensor_type(sensor_type::current), L"Is correct type", LINE_INFO());
            }
        }

        {
            sensor_array_configuration config;

            config.configure<tinkerforge_configuration>([](tinkerforge_configuration &c) {
                c.averaging(tinkerforge_sample_averaging::average_of_4);
            });

            auto sensors = sensor_array::for_matches(std::move(config), is_power_sensor);
            for (std::size_t i = 0; i < sensors.size(); ++i) {
                Assert::IsTrue(sensors[i].is_sensor_type(sensor_type::power), L"Is correct type", LINE_INFO());
            }
        }

        {
            sensor_array_configuration config;

            config.configure<tinkerforge_configuration>([](tinkerforge_configuration &c) {
                c.voltage_conversion_time(tinkerforge_conversion_time::microseconds_140);
            });

            auto sensors = sensor_array::for_matches(std::move(config), is_voltage_sensor);
            for (std::size_t i = 0; i < sensors.size(); ++i) {
                Assert::IsTrue(sensors[i].is_sensor_type(sensor_type::voltage), L"Is correct type", LINE_INFO());
            }
        }
    }

    TEST_METHOD(test_exclude) {
        sensor_array_configuration config;
        config.exclude<hmc8015_configuration>()
#if defined(POWER_OVERWHELMING_WITH_NVML)
            .exclude<nvml_configuration>()
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
            .exclude<tinkerforge_configuration>();

        std::vector<sensor_description> descs;
        descs.resize(sensor_array::all_descriptions(nullptr, 0, config));
        sensor_array::all_descriptions(descs.data(), descs.size(), config);

        Assert::IsFalse(std::any_of(descs.begin(), descs.end(), is_hmc8015_sensor), L"No HMC 8015 sensor", LINE_INFO());
        Assert::IsFalse(std::any_of(descs.begin(), descs.end(), is_nvml_sensor), L"No NVML sensor", LINE_INFO());
        Assert::IsFalse(std::any_of(descs.begin(), descs.end(), is_tinkerforge_sensor), L"No Tinkerforge sensor", LINE_INFO());

        sensor_array sensors(std::move(config), descs.data(), descs.size());
    }
};

PWROWG_TEST_NAMESPACE_END
