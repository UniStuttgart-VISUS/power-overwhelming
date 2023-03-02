// <copyright file="collector.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "collector.h"


/*
 * ::collect_all
 */
void collect_all(const wchar_t *output, const unsigned int dt) {
    using namespace visus::power_overwhelming;

    auto collector = collector::for_all(output);
    collector.start();

    std::this_thread::sleep_for(std::chrono::seconds(dt));
    collector.stop();
}


/*
 * ::collect_template
 */
void collect_template(const wchar_t *tpl, const unsigned int dt) {
    using namespace visus::power_overwhelming;

    collector::make_configuration_template(tpl);
    auto collector = collector::from_json(tpl);
    collector.start();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    collector.stop();
}
