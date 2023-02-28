// <copyright file="poweb.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include "Configuration.h"
#include "Controller.h"
#include "resource.h"


/* Global variables. */
static Controller controller;


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
    UNREFERENCED_PARAMETER(cmdShow);
    static constexpr const TCHAR *WINDOW_CLASS = _T("PowerOverwhelmingWindow");

    //auto nvmlSensor = visus::power_overwhelming::nvml_sensor::from_index(0);

    try {
        controller.Start(hInstance, cmdLine, [](const Configuration&) {
            ::MessageBox(controller, _T("All benchmarks have been completed."),
                _T("All done"), MB_ICONINFORMATION | MB_OK);
        });

        auto hAccelTable = ::LoadAccelerators(hInstance,
            MAKEINTRESOURCE(IDC_POWEB));
        MSG msg;

        while (::GetMessage(&msg, nullptr, 0, 0)) {
            if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }

        return static_cast<int>(msg.wParam);
    } catch (std::exception& ex) {
        ::MessageBoxA(NULL, ex.what(), nullptr, MB_OK | MB_ICONERROR);
        return -1;
    }
}
