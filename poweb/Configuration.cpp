// <copyright file="Configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "Configuration.h"


using namespace visus::pwrowg;

static constexpr const char *FIELD_BLANK_PAGE = "blankPage";
static constexpr const char *FIELD_COOL_DOWN = "coolDown";
static constexpr const char *FIELD_INITIAL_WAIT = "initialWait";
static constexpr const char *FIELD_ITERATIONS = "iterations";
static constexpr const char *FIELD_ROOT = "poweb";
static constexpr const char *FIELD_URLS = "urls";
static constexpr const char *FIELD_VISIBLE_PERIOD = "visiblePeriod";


/*
 * Configuration::Configuration
 */
Configuration::Configuration(void) : _blankPage(L"about:blank"), _coolDown(0),
    _initialWait(0), _iterations(0), _visiblePeriod(0) { }


/*
 * Configuration::Configuration
 */
Configuration::Configuration(const std::wstring& path)
        : _collector(std::make_unique<CollectorType>(MakeStream(path))) {
    std::ifstream stream(path);
    assert(stream.good());
    nlohmann::json config;
    stream >> config;

    const auto& webConfig = config[FIELD_ROOT];

    this->_blankPage = convert_string<wchar_t>(
        webConfig[FIELD_BLANK_PAGE].get<std::string>());
    this->_coolDown = decltype(this->_coolDown)(
        webConfig[FIELD_COOL_DOWN].get<std::uint64_t>());
    this->_initialWait = decltype(this->_initialWait)(
        webConfig[FIELD_INITIAL_WAIT].get<std::uint64_t>());
    this->_iterations = webConfig[FIELD_ITERATIONS].get<std::uint32_t>();

    {
        auto urls = webConfig[FIELD_URLS].get<std::vector<std::string>>();
        this->_urls.resize(urls.size());
        std::transform(urls.begin(), urls.end(), this->_urls.begin(),
            [](const std::string &u) { return convert_string<wchar_t>(u); });
    }

    this->_visiblePeriod = decltype(this->_visiblePeriod)(
        webConfig[FIELD_VISIBLE_PERIOD].get<std::uint64_t>());
}


/*
 * Configuration::StartCollector
 */
void Configuration::StartCollector(void) {
    this->_collector.start();
}


/*
 * Configuration::StopCollector
 */
void Configuration::StopCollector(void) {
    this->_collector.stop();
}


/*
 * Configuration::WaitForCoolDown
 */
void Configuration::WaitForCoolDown(void) const {
    std::this_thread::sleep_for(this->_coolDown);
}


/*
 * Configuration::WaitForVisiblePeriod
 */
void Configuration::WaitForVisiblePeriod(void) const {
    std::this_thread::sleep_for(this->_visiblePeriod);
}


/*
 * Configuration::WaitInitially
 */
void Configuration::WaitInitially(void) {
    std::this_thread::sleep_for(this->_initialWait);
}
