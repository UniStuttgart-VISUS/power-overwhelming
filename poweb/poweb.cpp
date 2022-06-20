// <copyright file="poweb.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"

#include "resource.h"

#define MAX_LOADSTRING 100

/* Forward declarations. */
void SyncViewSize(HWND);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* Global variables. */
static wil::com_ptr<ICoreWebView2Controller> webViewController;
static wil::com_ptr<ICoreWebView2> webViewWindow;


/// <summary>
/// Entry point of the application.
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="cmdLine"></param>
/// <param name="cmdShow"></param>
/// <returns></returns>
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR cmdLine,
        _In_ int cmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(cmdLine);
    static constexpr const TCHAR *WINDOW_CLASS = _T("PowerOverwhelmingWindow");

    auto nvmlSensor = visus::power_overwhelming::nvml_sensor::from_index(0);

    TCHAR windowTitle[MAX_LOADSTRING];
    ::LoadString(hInstance, IDS_APP_TITLE, windowTitle, MAX_LOADSTRING);

#pragma region Register window class
    {
        WNDCLASSEXW wc;
        ::ZeroMemory(&wc, sizeof(wc));
        wc.cbSize = sizeof(WNDCLASSEX);

        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = ::WndProc;
        wc.hInstance = hInstance;
        wc.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POWEB));
        wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        wc.lpszMenuName = MAKEINTRESOURCEW(IDC_POWEB);
        wc.lpszClassName = WINDOW_CLASS;
        wc.hIconSm = ::LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        if (!RegisterClassExW(&wc)) {
            return -1;
        }
    }
#pragma endregion

#pragma region Create and show window
    HWND hWnd = ::CreateWindow(WINDOW_CLASS, windowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance,
        nullptr);
    if (!hWnd) {
        return -2;
    }

    ::ShowWindow(hWnd, cmdShow);
    ::UpdateWindow(hWnd);
#pragma endregion

    ::CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [hWnd, &nvmlSensor](HRESULT result, ICoreWebView2Environment *env) {
            // Create a CoreWebView2Controller and get the associated
            // CoreWebView2 whose parent is the main window hWnd.
            env->CreateCoreWebView2Controller(hWnd, Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                [hWnd, &nvmlSensor](HRESULT result, ICoreWebView2Controller *controller) {
                if (controller != nullptr) {
                    ::webViewController = controller;
                    ::webViewController->get_CoreWebView2(&webViewWindow);
                }

                // Configure the view.
                ICoreWebView2Settings *settings;
                ::webViewWindow->get_Settings(&settings);
                settings->put_IsScriptEnabled(TRUE);
                settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                settings->put_IsWebMessageEnabled(TRUE);

                // Resize view to fit the bounds of the parent window.
                ::SyncViewSize(hWnd);

                // Register an ICoreWebView2NavigationStartingEventHandler to cancel any non-https navigation
                EventRegistrationToken token;
                webViewWindow->add_NavigationStarting(Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
                    [&nvmlSensor](ICoreWebView2 *webview, ICoreWebView2NavigationStartingEventArgs *args) -> HRESULT {
                    nvmlSensor.sample([](const visus::power_overwhelming::measurement& m) {
                        ::OutputDebugStringW((std::to_wstring(m.power()) + L"\r\n").c_str());
                    });
                    //PWSTR uri;
                    //args->get_Uri(&uri);
                    //std::wstring source(uri);
                    //if (source.substr(0, 5) != L"https") {
                    //    args->put_Cancel(true);
                    //}
                    //CoTaskMemFree(uri);
                    return S_OK;
                }).Get(), &token);

                EventRegistrationToken tokNavCompleted;
                ::webViewWindow->add_NavigationCompleted(Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
                    [&nvmlSensor](ICoreWebView2 *webview, ICoreWebView2NavigationCompletedEventArgs *args) {
                    ::OutputDebugString(_T("nav complete\r\n"));
                    //nvmlSensor.sample(nullptr);
                    //PWSTR uri;
                    //args->get_Uri(&uri);
                    //std::wstring source(uri);
                    //if (source.substr(0, 5) != L"https") {
                    //    args->put_Cancel(true);
                    //}
                    //CoTaskMemFree(uri);
                    return S_OK;
                }).Get(), &tokNavCompleted);


                EventRegistrationToken tokLoading;
                ::webViewWindow->add_ContentLoading(Microsoft::WRL::Callback<ICoreWebView2ContentLoadingEventHandler>(
                    [hWnd](ICoreWebView2 *webview, ICoreWebView2ContentLoadingEventArgs *args) {
                    //::MessageBox(hWnd, _T("HORST"), nullptr, MB_OK);
                    ::OutputDebugString(_T("content loading\r\n"));
                    return S_OK;
                }).Get(), &tokLoading);

                //// Schedule an async task to add initialization script that freezes the Object object
                //webViewWindow->AddScriptToExecuteOnDocumentCreated(L"Object.freeze(Object);", nullptr);
                //// Schedule an async task to get the document URL
                //webViewWindow->ExecuteScript(L"window.document.URL;", Microsoft::WRL::Callback<ICoreWebView2ExecuteScriptCompletedHandler>([](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
                //    LPCWSTR URL = resultObjectAsJson;
                //    //doSomethingWithURL(URL);
                //    return S_OK;
                //}).Get());

                // Set an event handler for the host to return received message back to the web content
                webViewWindow->add_WebMessageReceived(Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                    [](ICoreWebView2 *webview, ICoreWebView2WebMessageReceivedEventArgs *args) -> HRESULT {
                    PWSTR message;
                    args->TryGetWebMessageAsString(&message);
                    // processMessage(&message);
                    webview->PostWebMessageAsString(message);
                    CoTaskMemFree(message);
                    return S_OK;
                }).Get(), &token);

                // Schedule an async task to add initialization script that
                // 1) Add an listener to print message from the host
                // 2) Post document URL to the host
                //webViewWindow->AddScriptToExecuteOnDocumentCreated(
                //    L"window.chrome.webview.addEventListener(\'message\', event => alert(event.data));" \
                //    L"window.chrome.webview.postMessage(window.document.URL);",
                //    nullptr);

                // Navigate to the page to benchmark.
                //::webViewWindow->Navigate(L"https://www.bing.com/");
                ::webViewWindow->Navigate(L"https://bl.ocks.org/steveharoz/8c3e2524079a8c440df60c1ab72b5d03");

                return S_OK;
            }).Get());

            return S_OK;
        }).Get());

#pragma region Message loop
    auto hAccelTable = ::LoadAccelerators(hInstance,
        MAKEINTRESOURCE(IDC_POWEB));
    MSG msg;

    while (::GetMessage(&msg, nullptr, 0, 0)) {
        if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
#pragma endregion

    return static_cast<int>(msg.wParam);
}


/// <summary>
/// Synchronise the view size of the web view with the client rectangle of
/// <paramref name="hWnd" />.
/// </summary>
/// <param name="hWnd"></param>
void SyncViewSize(HWND hWnd) {
    if (::webViewController != nullptr) {
        RECT bounds;
        ::GetClientRect(hWnd, &bounds);
        ::webViewController->put_Bounds(bounds);
    }
}


/// <summary>
/// Processes messages for the main window.
/// </summary>
/// <param name="hWnd"></param>
/// <param name="msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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

        case WM_SIZE:
            ::SyncViewSize(hWnd);
            break;

        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;

        default:
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}
