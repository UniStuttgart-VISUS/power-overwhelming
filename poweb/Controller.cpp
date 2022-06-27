// <copyright file="Controller.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "Controller.h"

#include "resource.h"


// Maximum length of string resource loaded from binary.
#define MAX_LOADSTRING (128)

// A user-defined window message instructing the STA thread to navigate to the
// next page.
#define WM_NAVIGATE (WM_USER + 0)


/*
 * Controller::Controller
 */
Controller::Controller(void)
        : _hEvent(::CreateEvent(nullptr, FALSE, FALSE, nullptr)),
    _hWnd(NULL), _tokNavCompleted({}), _tokNavStarting({}) {
    if (this->_hEvent == NULL) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
}


/*
 * Controller::~Controller
 */
Controller::~Controller(void) {
    if (this->_worker.joinable()) {
        this->_worker.join();
    }

    ::CloseHandle(this->_hEvent);
}


/*
 * Controller::Start
 */
void Controller::Start(HINSTANCE hInstance, const std::wstring& configFile,
        const std::function<void(const Configuration&)>& onComplete) {
    // Create the window.
    this->CreateWnd(hInstance);

    // Create the browser.
    ::CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>([=](HRESULT result, ICoreWebView2Environment *env) {
        env->CreateCoreWebView2Controller(this->_hWnd, Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>([=](HRESULT result, ICoreWebView2Controller *controller) {
            if (controller != nullptr) {
                this->_webViewController = controller;
                this->_webViewController->get_CoreWebView2(&this->_webView);
            }

            //// Configure the view.
            //ICoreWebView2Settings *settings;
            //this->_webViewWindow->get_Settings(&settings);
            //settings->put_IsScriptEnabled(TRUE);
            //settings->put_AreDefaultScriptDialogsEnabled(TRUE);
            //settings->put_IsWebMessageEnabled(TRUE);

            // Resize view to fit the bounds of the parent window.
            this->SyncViewSize();

            // Register an ICoreWebView2NavigationStartingEventHandler to record when
            // navigation to a page has started.
            this->_webView->add_NavigationStarting(
                Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
                this, &Controller::OnNavigationStarting).Get(),
                &this->_tokNavStarting);

            //EventRegistrationToken tokLoading;
            //::webViewWindow->add_ContentLoading(Microsoft::WRL::Callback<ICoreWebView2ContentLoadingEventHandler>([hWnd](ICoreWebView2 *webview, ICoreWebView2ContentLoadingEventArgs *args) {
            //    //::MessageBox(hWnd, _T("HORST"), nullptr, MB_OK);
            //    ::OutputDebugString(_T("content loading\r\n"));
            //    return S_OK;
            //}).Get(), &tokLoading);

            this->_webView->add_NavigationCompleted(
                Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
                this, &Controller::OnNavigationCompleted).Get(),
                &this->_tokNavCompleted);

            // Signal to worker that we are ready.
            ::SetEvent(this->_hEvent);

            return S_OK;
        }).Get());

        return S_OK;
    }).Get());

    // Start the controller thread that waits for the navigation events, but
    // must not block the STA thread.
    this->_worker = std::thread(&Controller::Run, this, configFile, onComplete);
}


/*
 * Controller::WndProc
 */
LRESULT Controller::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT retval = 0;
    Controller *that = reinterpret_cast<Controller *>(
        ::GetWindowLongPtrW(hWnd, GWLP_USERDATA));

    switch (msg) {
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDM_EXIT:
                    ::DestroyWindow(hWnd);
                    break;

                default:
                    return ::DefWindowProc(hWnd, msg, wParam, lParam);
                }
            } break;

        case WM_CREATE: {
            auto cs = reinterpret_cast<CREATESTRUCT *>(lParam);
            if ((::SetWindowLongPtrW(hWnd, GWLP_USERDATA,
                    reinterpret_cast<LONG_PTR>(cs->lpCreateParams)) == 0)) {
                retval = ::GetLastError();
            } else {
                retval = 0;
            }
            } break;

        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;

        case WM_NAVIGATE:
            that->_webView->Navigate(that->_url.c_str());
            break;

        case WM_SIZE:
            that->SyncViewSize();
            break;

        default:
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return retval;
}


/*
 * Controller::CreateWnd
 */
void Controller::CreateWnd(HINSTANCE hInstance) {
    static constexpr const TCHAR *WINDOW_CLASS = _T("PowerOverwhelmingWindow");
    assert(hInstance != NULL);
    assert(this->_hWnd == NULL);

#pragma region Register window class
    {
        WNDCLASSEXW wc;

        if (!::GetClassInfoEx(hInstance, WINDOW_CLASS, &wc)) {
            ::ZeroMemory(&wc, sizeof(wc));
            wc.cbSize = sizeof(WNDCLASSEX);

            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = Controller::WndProc;
            wc.hInstance = hInstance;
            wc.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POWEB));
            wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
            wc.lpszMenuName = MAKEINTRESOURCEW(IDC_POWEB);
            wc.lpszClassName = WINDOW_CLASS;
            wc.hIconSm = ::LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));

            if (!RegisterClassExW(&wc)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }
    }
#pragma endregion

#pragma region Create and show window
    auto width = CW_USEDEFAULT;
    auto height = CW_USEDEFAULT;

    TCHAR windowTitle[MAX_LOADSTRING];
    ::LoadString(hInstance, IDS_APP_TITLE, windowTitle, MAX_LOADSTRING);

    {
        RECT workArea;
        if (!::SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0)) {
            throw std::system_error(::GetLastError(),
                std::system_category());
        }

        width = std::abs(workArea.right - workArea.left);
        height = std::abs(workArea.bottom - workArea.top);
    }

    this->_hWnd = ::CreateWindow(WINDOW_CLASS, windowTitle, WS_OVERLAPPEDWINDOW,
        0, 0, width, height, nullptr, nullptr, hInstance, this);
    if (this->_hWnd == NULL) {
        throw std::system_error(::GetLastError(),
            std::system_category());
    }

    ::ShowWindow(this->_hWnd, SW_MAXIMIZE);
    ::UpdateWindow(this->_hWnd);
#pragma endregion
}


/*
 * Controller::Navigate
 */
void Controller::Navigate(const std::wstring& url) {
    if (!url.empty()) {
        this->_url = url;
        ::SendMessage(this->_hWnd, WM_NAVIGATE, 0, 0);
    }
}


/*
 * Controller::OnNavigationCompleted
 */
HRESULT Controller::OnNavigationCompleted(ICoreWebView2 *webView,
        ICoreWebView2NavigationCompletedEventArgs *args) {
    assert(webView != nullptr);
    assert(args != nullptr);
    ::OutputDebugString(_T("Navigation completed."));
    ::SetEvent(this->_hEvent);
    return S_OK;
}


/*
 * Controller::OnNavigationStarting
 */
HRESULT Controller::OnNavigationStarting(ICoreWebView2 *webView,
        ICoreWebView2NavigationStartingEventArgs *args) {
    assert(webView != nullptr);
    assert(args != nullptr);
    ::OutputDebugString(_T("Navigation starting."));
    return S_OK;
}


/*
 * Controller::Run
 */
void Controller::Run(const std::wstring configFile,
        const std::function<void(const Configuration &)> onComplete) {
    try {
        Configuration config(configFile);

        // Wait for the browser to become ready.
        this->WaitEvent();

        // Start collecting power samples.
        config.StartCollector();

        // Initially wait until the browser stops consuming excessive energy for
        // background initialisation tasks.
        config.GetCollector().marker(L"waiting");
        config.WaitInitially();

        // Go through the test URLs.
        for (auto &u : config.GetUrls()) {
            for (std::uint32_t i = 0; i < config.GetIterations(); ++i) {
                config.GetCollector().marker(L"blank");
                this->Navigate(config.GetBlankPage());
                this->WaitEvent();
                config.WaitForCoolDown();

                {
                    std::wstringstream ss;
                    ss << L"navigating \"" << u << L"\"" << std::ends;
                    config.GetCollector().marker(ss.str().c_str());
                }
                this->Navigate(u);
                this->WaitEvent();

                {
                    std::wstringstream ss;
                    ss << L"showing \"" << u << L"\"" << std::ends;
                    config.GetCollector().marker(ss.str().c_str());
                }
                config.WaitForVisiblePeriod();
            }
        }

        // Stop collecting power samples.
        config.StopCollector();

        // Notifiy the caller that we are done.
        onComplete(config);
    } catch (std::exception& ex) {
        ::MessageBoxA(this->_hWnd, ex.what(), nullptr, MB_ICONERROR | MB_OK);
    }
}


/*
 * Controller::SyncViewSize
 */
void Controller::SyncViewSize(void) {
    if ((this->_hWnd != NULL) && (this->_webViewController != nullptr)) {
        RECT bounds;
        ::GetClientRect(this->_hWnd, &bounds);
        this->_webViewController->put_Bounds(bounds);
    }
}


/*
 * Controller::WaitEvent
 */
bool Controller::WaitEvent(void) {
    auto status = ::WaitForSingleObject(this->_hEvent, INFINITE);
    switch (status) {
        case WAIT_OBJECT_0:
            return true;

        case WAIT_TIMEOUT:
            return false;

        default:
            throw std::system_error(::GetLastError(), std::system_category());
    }
}
