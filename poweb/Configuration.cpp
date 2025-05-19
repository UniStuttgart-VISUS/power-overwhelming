// <copyright file="Configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
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
static constexpr const char *FIELD_WRITE_INTERVAL = "writeInterval";


/*
 * Configuration::Configuration
 */
Configuration::Configuration(void) : _blankPage(L"about:blank"), _coolDown(0),
    _initialWait(0), _iterations(0), _markerBlank(0), _visiblePeriod(0) { }


/*
 * Configuration::Configuration
 */
Configuration::Configuration(const std::wstring& path) {
    const auto timestamp = std::to_wstring(timestamp::now().value());

    std::ifstream stream;
    stream.exceptions(stream.exceptions() | std::ios::failbit);
    stream.open(path, std::ios::in);

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

    {
        sensor_array_configuration cfg;
        cfg.configure<marker_configuration>(
            [this](marker_configuration& c) {
            this->_markerBlank = c += L"blank";

            for (auto &u : this->_urls) {
                {
                    std::wstringstream ss;
                    ss << L"navigating \"" << u << L"\"" << std::ends;
                    this->_markersNav.push_back(c += ss.str());
                }
                {
                    std::wstringstream ss;
                    ss << L"showing \"" << u << L"\"" << std::ends;
                    this->_markersShow.push_back(c += ss.str());
                }
            }
        });

        this->_sensors = sensor_array::for_all(std::move(cfg));

        dump_sensors(this->_sensors, timestamp + L".json");
    }

    this->_visiblePeriod = decltype(this->_visiblePeriod)(
        webConfig[FIELD_VISIBLE_PERIOD].get<std::uint64_t>());

    {
        auto p = path + timestamp + L".csv";
        std::chrono::milliseconds writeInterval(
            webConfig[FIELD_WRITE_INTERVAL].get<std::uint64_t>());
        this->_collector.reset(new CollectorType(writeInterval, MakeStream(p)));
    }
}


/*
 * Configuration::StartCollector
 */
void Configuration::StartCollector(void) {
    if (this->_collector) {
        std::vector<visus::pwrowg::sensor_description> descs;
        descs.resize(this->_sensors.descriptions(nullptr, 0));
        this->_sensors.descriptions(descs.data(), descs.size());

        this->_sensors.start(CollectorType::sample_callback,
            this->_collector.get());
    }
}


/*
 * Configuration::StopCollector
 */
void Configuration::StopCollector(void) {
    this->_sensors.stop();
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
