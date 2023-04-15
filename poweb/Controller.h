// <copyright file="Controller.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "Configuration.h"


/// <summary>
/// Controls the browser to run the benchmarks.
/// </summary>
/// <remarks>
/// The benchmarks must run in a separate thread, because we block until the
/// pages are loaded to enforce our cool-down periods.
/// </remarks>
class Controller final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    Controller(void);

    Controller(const Controller&) = delete;

    /// <summary>
    /// Finalises instance.
    /// </summary>
    ~Controller(void);

    /// <summary>
    /// Runs the specified configuration.
    /// </summary>
    /// <param name="hInstance"></param>
    /// <param name="configFile"></param>
    /// <param name="onComplete"></param>
    void Start(HINSTANCE hInstance, const std::wstring& configFile,
        const std::function<void(const Configuration&)>& onComplete);

    Controller& operator =(const Controller&) = delete;

    /// <summary>
    /// Convert the controller into the browser window.
    /// </summary>
    inline operator HWND(void) const {
        return this->_hWnd;
    }

private:

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam,
        LPARAM lParam);

    void CreateWnd(HINSTANCE hInstance);

    void Navigate(const std::wstring& url);

    HRESULT OnNavigationCompleted(ICoreWebView2 *webView,
        ICoreWebView2NavigationCompletedEventArgs *args);

    HRESULT OnNavigationStarting(ICoreWebView2 *webView,
        ICoreWebView2NavigationStartingEventArgs *args);

    void Run(const std::wstring configFile,
        const std::function<void(const Configuration&)> onComplete);

    void SyncViewSize(void);

    bool WaitEvent(void);

    HANDLE _hEvent;
    HWND _hWnd;
    EventRegistrationToken _tokNavCompleted;
    EventRegistrationToken _tokNavStarting;
    std::wstring _url;
    wil::com_ptr<ICoreWebView2> _webView;
    wil::com_ptr<ICoreWebView2Controller> _webViewController;
    std::thread _worker;
};
