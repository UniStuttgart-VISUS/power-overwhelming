// <copyright file="daqmx_channel_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/daqmx_current_channel.h>
#include <visus/pwrowg/daqmx_power_channel.h>
#include <visus/pwrowg/daqmx_voltage_channel.h>

#include <daqmx_serialisation.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_channel_test) {

public:

    TEST_METHOD(current_char_ctor) {
        daqmx_current_channel c("ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(current_wchar_ctor) {
        daqmx_current_channel c(L"ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(current_setters) {
        daqmx_current_channel c("ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.max_value(1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.min_value(-1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name("hugo");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("hugo", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name(L"heinz");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("heinz", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name(std::string("horst"));
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.shunt_resistor_location(daqmx_shunt_resistor_location::external);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.shunt_resistor_value(42.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.terminal_configuration(daqmx_terminal_configuration::differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::differential), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(current_serialisation) {
        daqmx_current_channel c(L"ai0");
        c.min_value(-1.0).max_value(1.0).name("horst").shunt_resistor_value(42.0f);
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.shunt_resistor_location(daqmx_shunt_resistor_location::external);
        c.terminal_configuration(daqmx_terminal_configuration::differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        const auto json = detail::json_serialise(c);
        const auto d = detail::json_deserialise<daqmx_current_channel>(json);
        Assert::AreEqual(c.channel(), d.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(c.max_value(), d.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(c.min_value(), d.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual(c.name(), d.name(), L"name", LINE_INFO());
        Assert::AreEqual(c.shunt_resistor_value(), d.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(c.shunt_resistor_location()), int(d.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
        Assert::AreEqual(int(c.terminal_configuration()), int(d.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(power_char_ctor) {
        daqmx_power_channel c("ai0", "ai1");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());
    }

    TEST_METHOD(power_wchar_ctor) {
        daqmx_power_channel c(L"ai0", L"ai1");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());
    }

    TEST_METHOD(power_setters) {
        daqmx_power_channel c("ai0", "ai1");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

        c.current_max_value(1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

        c.current_min_value(-1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::standard), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.shunt_resistor_location(daqmx_shunt_resistor_location::external);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(0.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

        c.shunt_resistor_value(42.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.terminal_configuration(daqmx_terminal_configuration::pseudo_differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::pseudo_differential), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

        c.voltage_max_value(2.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(2.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::pseudo_differential), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(2.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());

        c.voltage_min_value(-2.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual("ai1", c.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(1.0, c.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(2.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-2.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_shunt_resistor_location::external), int(c.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual(42.0, c.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::pseudo_differential), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::AreEqual(2.0, c.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(-2.0, c.voltage_min_value(), L"voltage_min_value", LINE_INFO());
    }

    TEST_METHOD(power_serialisation) {
        daqmx_power_channel c("ai0", "ai1");
        c.current_min_value(-1.0).current_max_value(1.0).voltage_min_value(-2.0).voltage_max_value(2.0).name("horst").shunt_resistor_value(42.0f);
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.shunt_resistor_location(daqmx_shunt_resistor_location::external);
        c.terminal_configuration(daqmx_terminal_configuration::pseudo_differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        const auto json = detail::json_serialise(c);
        const auto d = detail::json_deserialise<daqmx_power_channel>(json);
        Assert::AreEqual(c.channel(), d.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(c.current_channel(), d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(c.current_max_value(), d.current_max_value(), L"current_max_value", LINE_INFO());
        Assert::AreEqual(c.current_min_value(), d.current_min_value(), L"current_min_value", LINE_INFO());
        Assert::AreEqual(c.max_value(), d.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(c.min_value(), d.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual(c.name(), d.name(), L"name", LINE_INFO());
        Assert::AreEqual(c.shunt_resistor_value(), d.shunt_resistor_value(), L"shunt_resistor_value", LINE_INFO());
        Assert::AreEqual(c.voltage_max_value(), d.voltage_max_value(), L"voltage_max_value", LINE_INFO());
        Assert::AreEqual(c.voltage_min_value(), d.voltage_min_value(), L"voltage_min_value", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(c.shunt_resistor_location()), int(d.shunt_resistor_location()), L"shunt_resistor_location", LINE_INFO());
        Assert::AreEqual(int(c.terminal_configuration()), int(d.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(voltage_char_ctor) {
        daqmx_voltage_channel c("ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(voltage_wchar_ctor) {
        daqmx_voltage_channel c(L"ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(voltage_setters) {
        daqmx_voltage_channel c(L"ai0");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(0.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.max_value(1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(0.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.min_value(-1.0);
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name("hugo");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("hugo", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name(L"heinz");
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("heinz", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        c.name(std::wstring(L"horst"));
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::standard), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.terminal_configuration(daqmx_terminal_configuration::differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        Assert::AreEqual("ai0", c.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(1.0, c.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(-1.0, c.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual("horst", c.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(daqmx_terminal_configuration::differential), int(c.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    TEST_METHOD(voltage_serialisation) {
        daqmx_voltage_channel c(L"ai0");
        c.min_value(-1.0).max_value(1.0).name("horst");
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        c.terminal_configuration(daqmx_terminal_configuration::differential);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

        const auto json = detail::json_serialise(c);
        const auto d = detail::json_deserialise<daqmx_voltage_channel>(json);
        Assert::AreEqual(c.channel(), d.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(c.max_value(), d.max_value(), L"max_value", LINE_INFO());
        Assert::AreEqual(c.min_value(), d.min_value(), L"min_value", LINE_INFO());
        Assert::AreEqual(c.name(), d.name(), L"name", LINE_INFO());
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        Assert::AreEqual(int(c.terminal_configuration()), int(d.terminal_configuration()), L"terminal_configuration", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

};

PWROWG_TEST_NAMESPACE_END
