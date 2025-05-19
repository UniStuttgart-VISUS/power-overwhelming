// <copyright file="Configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


/// <summary>
/// A container for the test configuration to be run.
/// </summary>
class Configuration final {

public:

    /// <summary>
    /// The implementation collecting the power measurements.
    /// </summary>
    typedef visus::pwrowg::atomic_sink<visus::pwrowg::csv_sink<std::ofstream>>
        CollectorType;

    /// <summary>
    /// Initialises an empty instance.
    /// </summary>
    Configuration(void);

    /// <summary>
    /// Initialises an instance from JSON
    /// </summary>
    /// <param name="path"></param>
    explicit Configuration(const std::wstring& path);

    /// <summary>
    /// Gets the URL of the blank page.
    /// </summary>
    /// <returns></returns>
    inline const std::wstring& GetBlankPage(void) const noexcept {
        return this->_blankPage;
    }

    /// <summary>
    /// Gets the power collector object.
    /// </summary>
    /// <returns></returns>
    inline CollectorType& GetCollector(void) noexcept {
        return *this->_collector;
    }

    /// <summary>
    /// Gets the cooldown period for which the blank site should be shown
    /// before navigating to the URL.
    /// </summary>
    /// <returns></returns>
    inline std::chrono::milliseconds GetCoolDown(void) const noexcept {
        return this->_coolDown;
    }

    /// <summary>
    /// Gets the waiting period before loading the initial test case.
    /// </summary>
    /// <remarks>
    /// We found that firing up the browser costs a significant amount of
    /// energy, which would be in the measurement for the first test case, so
    /// we wait until we assume every background task is done.
    /// </remarks>
    /// <returns></returns>
    inline std::chrono::milliseconds GetInitialWait(void) const noexcept {
        return this->_initialWait;
    }

    /// <summary>
    /// Gets the number of iterations for each URL.
    /// </summary>
    /// <returns></returns>
    inline std::uint32_t GetIterations(void) const noexcept {
        return this->_iterations;
    }

    /// <summary>
    /// Gets the URLs that should be visited.
    /// </summary>
    /// <returns></returns>
    inline const std::vector<std::wstring>& GetUrls(void) const noexcept {
        return this->_urls;
    }

    /// <summary>
    /// Gets the time for which the page should stay visible once the navigation
    /// has completed.
    /// </summary>
    /// <returns></returns>
    inline std::chrono::milliseconds GetVisiblePeriod(void) const noexcept {
        return this->_visiblePeriod;
    }

    /// <summary>
    /// Emits the marker indicating that the blank page is shown.
    /// </summary>
    inline void MarkerBlank(void) const noexcept {
        this->_sensors.marker(this->_markerBlank);
    }

    /// <summary>
    /// Emits the marker for navigating to the <paramref name="url" />th URL.
    /// </summary>
    /// <param name="url"></param>
    inline void MarkerNavigate(_In_ const std::size_t url) const {
        assert(url < this->_markersNav.size());
        this->_sensors.marker(this->_markersNav[url]);
    }

    /// <summary>
    /// Emits the marker for showing to the <paramref name="url" />th URL.
    /// </summary>
    /// <param name="url"></param>
    inline void MarkerShow(_In_ const std::size_t url) const {
        assert(url < this->_markersShow.size());
        this->_sensors.marker(this->_markersShow[url]);
    }

    /// <summary>
    /// Starts the power collector.
    /// </summary>
    void StartCollector(void);

    /// <summary>
    /// Stops the power collector.
    /// </summary>
    void StopCollector(void);

    /// <summary>
    /// Blocks the calling thread for the configured cool-down period.
    /// </summary>
    void WaitForCoolDown(void) const;

    /// <summary>
    /// Blocks the calling thread for the configured visibility period.
    /// </summary>
    void WaitForVisiblePeriod(void) const;

    /// <summary>
    /// Blocks the calling thread for the initial wait period.
    /// </summary>
    /// <param name=""></param>
    void WaitInitially(void);

private:

    static inline std::ofstream MakeStream(_In_ const std::wstring& path) {
        std::ofstream retval;
        retval.open(path.c_str(), std::ios::trunc);
        return retval;
    }

    std::wstring _blankPage;
    std::unique_ptr<CollectorType> _collector;
    std::chrono::milliseconds _coolDown;
    std::chrono::milliseconds _initialWait;
    std::uint32_t _iterations;
    unsigned int _markerBlank;
    std::vector<unsigned int> _markersNav;
    std::vector<unsigned int> _markersShow;
    visus::pwrowg::sensor_array _sensors;
    std::vector<std::wstring> _urls;
    std::chrono::milliseconds _visiblePeriod;
};
