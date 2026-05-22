// <copyright file="intel_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include "igcl_sensor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(intel_test) {

public:


#if defined(POWER_OVERWHELMING_WITH_IGCL)
    TEST_METHOD(test_igcl_descriptions) {
        typedef detail::igcl_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        for (auto& d : descs) {
            Assert::AreEqual(L"Intel", d.vendor(), L"Vendor name", LINE_INFO());
            Assert::IsTrue((d.sensor_type() & sensor_type::gpu) == sensor_type::gpu, L"GPU sensor", LINE_INFO());
            Assert::IsTrue((d.sensor_type() & sensor_type::software) == sensor_type::software, L"Software sensor", LINE_INFO());
        }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */


#if defined(POWER_OVERWHELMING_WITH_IGCL)
    TEST_METHOD(test_igcl_sensor_creation) {
        typedef detail::igcl_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        detail::sensor_array_impl dummy;

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::AreEqual(descs.size(), sensors.size(), L"Sensors created", LINE_INFO());
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

        for (std::size_t i = 0; i < 2; ++i) {
            for (auto& s : sensors) {
                s.sample([](const sample *samples, const std::size_t cnt, const sensor_description *sensors, void *context) {
                    Assert::IsTrue(cnt > 0, L"IGCL creates at least one sample in default config.", LINE_INFO());

                    for (std::size_t i = 0; i < cnt; ++i) {
                        auto& sample = samples[i];
                        std::wstring dump(sensors[sample.source].name());
                        dump += L": ";

                        switch (sensors[sample.source].reading_type()) {
                            case reading_type::floating_point:
                                dump += std::to_wstring(sample.reading.floating_point);
                                break;

                            case reading_type::signed_integer:
                                dump += std::to_wstring(sample.reading.signed_integer);
                                break;

                            case reading_type::unsigned_integer:
                                dump += std::to_wstring(sample.reading.unsigned_integer);
                                break;
                        }

                        dump += L"\r\n";
                        ::OutputDebugStringW(dump.c_str());
                    }
                    }, descs.data());
            }
        }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */

};

PWROWG_TEST_NAMESPACE_END