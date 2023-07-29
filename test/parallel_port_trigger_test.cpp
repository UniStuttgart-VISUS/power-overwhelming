// <copyright file="parallel_port_trigger_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(parallel_port_trigger_test) {

    public:

        TEST_METHOD(test_to_morse) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                parallel_port_trigger::to_morse(nullptr, 0, nullptr);
            }, L"Invalid message", LINE_INFO());

            {
                const wchar_t *message = L"abcdefghijklmnopqrstuvwxyzäöü0123456789,.-:+=!";
                std::vector<wchar_t> code(parallel_port_trigger::to_morse(nullptr, 0, message));
                parallel_port_trigger::to_morse(code.data(), code.size(), message);
                Assert::AreEqual(L".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. .-.- ---. ..-- ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----. --..-- .-.-.- -....- ---... .-.-. -...- -.-.--", code.data(), message, LINE_INFO());
            }

            {
                const wchar_t *message = L"Power Overwhelming";
                std::vector<wchar_t> code(parallel_port_trigger::to_morse(nullptr, 0, message));
                parallel_port_trigger::to_morse(code.data(), code.size(), message);
                Assert::AreEqual(L".--. --- .-- . .-. / --- ...- . .-. .-- .... . .-.. -- .. -. --.", code.data(), message, LINE_INFO());
            }

            {
                const wchar_t *message = L"Die Kraft ist überwältigend!";
                std::vector<wchar_t> code(parallel_port_trigger::to_morse(nullptr, 0, message));
                parallel_port_trigger::to_morse(code.data(), code.size(), message);
                Assert::AreEqual(L"-.. .. . / -.- .-. .- ..-. - / .. ... - / ..-- -... . .-. .-- .-.- .-.. - .. --. . -. -.. -.-.--", code.data(), message, LINE_INFO());
            }

            {
                const wchar_t *message = L"Oberleutnant Behnisch, wir sind getroffen! Feuer im Maschinenraum!";
                std::vector<wchar_t> code(parallel_port_trigger::to_morse(nullptr, 0, message));
                parallel_port_trigger::to_morse(code.data(), code.size(), message);
                Assert::AreEqual(L"--- -... . .-. .-.. . ..- - -. .- -. - / -... . .... -. .. ... -.-. .... --..-- / .-- .. .-. / ... .. -. -.. / --. . - .-. --- ..-. ..-. . -. -.-.-- / ..-. . ..- . .-. / .. -- / -- .- ... -.-. .... .. -. . -. .-. .- ..- -- -.-.--", code.data(), message, LINE_INFO());
            }

            {
                const wchar_t *message = L"F€hler";
                std::vector<wchar_t> code(parallel_port_trigger::to_morse(nullptr, 0, message));
                parallel_port_trigger::to_morse(code.data(), code.size(), message);
                Assert::AreEqual(L"..-. .... .-.. . .-.", code.data(), message, LINE_INFO());
            }
        }
        TEST_METHOD(test_to_value) {
            Assert::AreEqual(parallel_port_trigger::value_type(0), parallel_port_trigger::to_value(parallel_port_pin::none), L"none", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 0), parallel_port_trigger::to_value(parallel_port_pin::data0), L"data0", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 1), parallel_port_trigger::to_value(parallel_port_pin::data1), L"data1", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 2), parallel_port_trigger::to_value(parallel_port_pin::data2), L"data2", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 3), parallel_port_trigger::to_value(parallel_port_pin::data3), L"data3", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 4), parallel_port_trigger::to_value(parallel_port_pin::data4), L"data4", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 5), parallel_port_trigger::to_value(parallel_port_pin::data5), L"data5", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 6), parallel_port_trigger::to_value(parallel_port_pin::data6), L"data6", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(1 << 7), parallel_port_trigger::to_value(parallel_port_pin::data7), L"data7", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(255), parallel_port_trigger::to_value(parallel_port_pin::data), L"data", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(255), parallel_port_trigger::to_value(parallel_port_pin::all), L"all", LINE_INFO());
            Assert::AreEqual(parallel_port_trigger::value_type(0), parallel_port_trigger::to_value(parallel_port_pin::acknowledge), L"acknowledge", LINE_INFO());
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
