// <copyright file="visual_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include "visual_config.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <tchar.h>
#include <Windows.h>
#include <CommCtrl.h>

#include <wil/resource.h>
#include <wil/result.h>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/on_exit.h"
#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/sensor_array.h"
#include "visus/pwrowg/sensor_filters.h"

#include "resource.h"


/// <summary>
/// The configuration object that is being populated by the dialog.
/// </summary>
visus::pwrowg::rtx_configuration configuration;


/// <summary>
/// Gets access to the string resource with the given ID in the process image.
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
static std::basic_string<TCHAR> load_string(_In_ const UINT id) {
    const auto instance = ::GetModuleHandle(nullptr);
    auto len = 256;
    std::basic_string<TCHAR> retval(len, '\0');

    while (true) {
        len = ::LoadString(instance, id, &retval[0], len);
        THROW_LAST_ERROR_IF(len == 0);

        if (len <= retval.size()) {
            retval.resize(len);
            return retval;
        }

        retval.resize(len *= 2);
    } while (len >= retval.size());
}

/// <summary>
/// Answer the zero-based selection of a combo box.
/// </summary>
/// <param name="wnd"></param>
/// <returns></returns>
static int get_selection(_In_ const HWND wnd) {
    using visus::pwrowg::convert_string;

    const auto idx = ::SendMessage(wnd, CB_GETCURSEL, 0, 0);
    if (idx == CB_ERR) {
        const auto msg = convert_string<char>(::load_string(IDS_NO_SELECTION));
        throw std::invalid_argument(msg.c_str());
    }

    return static_cast<int>(idx);
}

/// <summary>
/// Gets the window text of the given window.
/// </summary>
/// <param name="wnd"></param>
/// <param name="mandatory"></param>
/// <returns></returns>
static std::basic_string<TCHAR> get_text(_In_ const HWND wnd,
        _In_ const bool mandatory = false) {
    using visus::pwrowg::convert_string;

    const auto len = ::GetWindowTextLength(wnd);
    if (mandatory && (len < 1)) {
        const auto msg = convert_string<char>(::load_string(IDS_NO_INPUT));
        throw std::invalid_argument(msg.c_str());
    }

    std::basic_string<TCHAR> retval(len, '\0');
    ::GetWindowText(wnd, &retval[0], len + 1);
    return retval;
}

/// <summary>
/// Creates a new sensor definition from the dialog and returns it.
/// </summary>
/// <param name="hWnd"></param>
/// <returns></returns>
static visus::pwrowg::rtx_sensor_definition make_sensor(_In_ const HWND hWnd) {
    using visus::pwrowg::convert_string;
    using visus::pwrowg::rtx_channel;
    using visus::pwrowg::rtx_channel_coupling;

    int idx_current = 0;
    int idx_voltage = 0;
    std::wstring name;

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CBSENSORVOL);
        assert(item != NULL);
        idx_voltage = ::get_selection(item);
    }

    rtx_channel chan_voltage(idx_voltage);

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBATTVOL);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_voltage.attenuation(std::stof(text), "V");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBRANGEVOL);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_voltage.attenuation(std::stof(text), "V");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBOFFSETVOL);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_voltage.attenuation(std::stof(text), "V");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CBCOUPVOL);
        assert(item != NULL);
        const auto value = get_selection(item);
        chan_voltage.coupling(static_cast<rtx_channel_coupling>(value));
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CBSENSORCUR);
        assert(item != NULL);
        idx_current = get_selection(item);
    }

    rtx_channel chan_current(idx_current);

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBATTCUR);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_current.attenuation(std::stof(text), "A");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBRANGECUR);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_current.attenuation(std::stof(text), "A");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBOFFSETCUR);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        chan_current.attenuation(std::stof(text), "A");
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CBCOUPCUR);
        assert(item != NULL);
        const auto value = get_selection(item);
        chan_current.coupling(static_cast<rtx_channel_coupling>(value));
    }

    {
        auto item = ::GetDlgItem(hWnd, IDC_TBSENSORNAME);
        assert(item != NULL);
        name = convert_string<wchar_t>(::get_text(item, true));
    }

    {
        auto item = ::GetDlgItem(hWnd, IDC_CBSENSORINST);
        assert(item != NULL);
        const auto path = ::get_text(item, true);

        return visus::pwrowg::rtx_sensor_definition(
            path.c_str(),
            chan_voltage,
            chan_current,
            name.empty() ? nullptr : name.c_str());
    }
}

/// <summary>
/// Updates the <see cref="configuration" /> from the dialog.
/// </summary>
/// <param name="hWnd"></param>
static void update_configuration(_In_ const HWND hWnd) {
    using visus::pwrowg::rtx_instrument_reset;
    using visus::pwrowg::rtx_reference_point;

    std::chrono::milliseconds duration;
    std::size_t samples = 0;
    visus::pwrowg::rtx_instrument_configuration::timeout_type timeout = 0;

    // First, create a new base configuration.
    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBDURATION);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        duration = std::chrono::milliseconds(std::stoul(text));
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBSAMPLES);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        samples = std::stoul(text);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBTIMEOUT);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        timeout = std::stoul(text);
    }

    visus::pwrowg::rtx_instrument_configuration config(duration, samples,
        timeout);

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CBREFPOS);
        assert(item != NULL);

        const auto idx = ::get_selection(item);
        switch (idx) {
            case 0:
                config.reference_position(rtx_reference_point::left);
                break;

            case 2:
                config.reference_position(rtx_reference_point::right);
                break;

            case 1:
            default:
                config.reference_position(rtx_reference_point::middle);
                break;
        }
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBTRIGPOS);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        std::chrono::milliseconds position(std::stoul(text));
        config.trigger_position(position);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CKBEEPERR);
        assert(item != NULL);
        const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
        config.beep_on_error(value == BST_CHECKED);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CKBEEPTRIGGER);
        assert(item != NULL);
        const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
        config.beep_on_trigger(value == BST_CHECKED);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CKBEEPAPPLY);
        assert(item != NULL);
        const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
        config.beep_on_apply((value == BST_CHECKED) ? 1 : 0);
    }

    ::configuration.base_configuration(std::move(config));

    // Next, update the properties directly in the sensor configuration.
    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBWAITRESET);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        std::chrono::milliseconds delay(std::stoul(text));
        ::configuration.reset_delay(delay);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_CKENUMRESET);
        assert(item != NULL);
        const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
        ::configuration.reset_on_enumerate(value == BST_CHECKED);
    }

    {
        auto reset = rtx_instrument_reset::none;

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKRESET);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::reset;
            }
        }

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKCLRBUF);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::buffers;
            }
        }

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKCLRSTAT);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::status;
            }
        }

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKCLRERR);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::errors;
            }
        }

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKSTOP);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::stop;
            }
        }

        {
            const auto item = ::GetDlgItem(hWnd, IDC_CKTRIGGER);
            assert(item != NULL);
            const auto value = ::SendMessage(item, BM_GETCHECK, 0, 0);
            if (value == BST_CHECKED) {
                reset = reset | rtx_instrument_reset::trigger;
            }
        }

        ::configuration.reset_flags(reset);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_TBDLTIMEOUT);
        assert(item != NULL);
        const auto text = ::get_text(item, true);
        std::chrono::milliseconds timeout(std::stoul(text));
        ::configuration.download_timeout(timeout);
    }

    {
        const auto item = ::GetDlgItem(hWnd, IDC_SLDLRETRIES);
        assert(item != NULL);
        const auto value = ::SendMessage(item, TBM_GETPOS, 0, 0);
        ::configuration.download_retries(value);
    }
}

/// <summary>
/// The window procedure for the dialog.
/// </summary>
/// <param name="hWnd"></param>
/// <param name="msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
static LRESULT CALLBACK wnd_proc(_In_ HWND hWnd, _In_ UINT msg,
        _In_ WPARAM wParam, _In_ LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDADD:
                    try {
                        auto sensor = ::make_sensor(hWnd);
                        ::configuration.add_sensor(std::move(sensor));
                    } catch (std::exception& ex) {
                        ::MessageBoxA(hWnd,
                            ex.what(),
                            ::load_string(IDS_ERROR).c_str(),
                            MB_ICONERROR);
                    }
                    return TRUE;

                case IDSAVE:
                    try {
                        auto filter = ::load_string(IDS_FILE_FILTER);
                        std::replace(filter.begin(),filter.end(),
                            _T('|'), _T('\0'));

                        TCHAR path[2 * MAX_PATH] = { 0 };

                        OPENFILENAME ofn { };
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = hWnd;
                        ofn.hInstance = ::GetModuleHandle(NULL);
                        ofn.lpstrFilter = filter.c_str();
                        ofn.lpstrFile = &path[0];
                        ofn.nMaxFile = static_cast<DWORD>(std::size(path));
                        ofn.Flags = OFN_OVERWRITEPROMPT;
                        ofn.lpstrDefExt = _T("json");

                        ::update_configuration(hWnd);

                        if (::GetSaveFileName(&ofn)) {
                            ::configuration.save(ofn.lpstrFile);
                        }
                    } catch (std::exception& ex) {
                        ::MessageBoxA(hWnd,
                            ex.what(),
                            ::load_string(IDS_ERROR).c_str(),
                            MB_ICONERROR);
                    }
                    return TRUE;

                case IDTEST:
                    try {
                        ::SetCursor(::LoadCursor(NULL, IDC_WAIT));
                        pwrowg_on_exit([](void) {
                            ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
                        });

                        ::update_configuration(hWnd);

                        visus::pwrowg::sensor_array_configuration config;
                        config.configure<visus::pwrowg::rtx_configuration>(
                            [](visus::pwrowg::rtx_configuration& c) {
                                c = ::configuration;
                            });
                        auto sensors = visus::pwrowg::sensor_array::for_matches(
                            std::move(config),
                            visus::pwrowg::is_rtx_sensor);
                        sensors.start();
                        sensors.stop();
                    } catch (std::exception& ex) {
                        ::MessageBoxA(hWnd,
                            ex.what(),
                            ::load_string(IDS_ERROR).c_str(),
                            MB_ICONERROR);
                    }
                    return TRUE;

                default:
                    return FALSE;
            }
        break;

        case WM_INITDIALOG:
            // When the dialog is initialised, apply all the defaults.
            {
                auto item = ::GetDlgItem(hWnd, IDC_TBDURATION);
                assert(item != NULL);
                auto value = std::to_string(5000);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBSAMPLES);
                assert(item != NULL);
                auto value = std::to_string(10000);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBTIMEOUT);
                assert(item != NULL);
                auto value = std::to_string(5000);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_CBREFPOS);
                assert(item != NULL);
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_REFERENCE_LEFT).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_REFERENCE_MIDDLE).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_REFERENCE_RIGHT).c_str()));
                ::SendMessage(item, CB_SETCURSEL, 1, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBTRIGPOS);
                assert(item != NULL);
                auto value = std::to_string(5000 / 2);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBWAITRESET);
                assert(item != NULL);
                auto value = std::to_string(100);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                const auto item = ::GetDlgItem(hWnd, IDC_CKRESET);
                assert(item != NULL);
                ::SendMessage(item, BM_SETCHECK, BST_CHECKED, 0);
            }

            {
                const auto item = ::GetDlgItem(hWnd, IDC_CKCLRSTAT);
                assert(item != NULL);
                ::SendMessage(item, BM_SETCHECK, BST_CHECKED, 0);
            }

            try {
                auto item = ::GetDlgItem(hWnd, IDC_CBSENSORINST);
                assert(item != NULL);

                std::vector<visus::pwrowg::rtx_instrument> devices(
                    visus::pwrowg::rtx_instrument::all(nullptr, 0));
                visus::pwrowg::rtx_instrument::all(devices.data(),
                    devices.size());

                for (auto& d : devices) {
                    ::SendMessageA(item, CB_ADDSTRING, 0,
                        reinterpret_cast<LPARAM>(d.path()));
                }

                if (!devices.empty()) {
                    ::SendMessage(item, CB_SETCURSEL, 0, 0);
                }
            } catch (std::exception& ex) {
                ::MessageBoxA(hWnd,
                    ex.what(),
                    ::load_string(IDS_ERROR).c_str(),
                    MB_ICONERROR);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBSENSORNAME);
                assert(item != NULL);
                ::SendMessage(item, EM_LIMITTEXT, 7, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_CBSENSORVOL);
                assert(item != NULL);
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("1")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("2")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("3")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("4")));
                ::SendMessage(item, CB_SETCURSEL, 0, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_CBSENSORCUR);
                assert(item != NULL);
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("1")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("2")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("3")));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    _T("4")));
                ::SendMessage(item, CB_SETCURSEL, 1, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBATTVOL);
                assert(item != NULL);
                auto value = std::to_string(10);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBATTCUR);
                assert(item != NULL);
                auto value = std::to_string(10);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBRANGEVOL);
                assert(item != NULL);
                auto value = std::to_string(13);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBRANGECUR);
                assert(item != NULL);
                auto value = std::to_string(5);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBOFFSETVOL);
                assert(item != NULL);
                auto value = std::to_string(0);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBOFFSETCUR);
                assert(item != NULL);
                auto value = std::to_string(0);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_CBCOUPVOL);
                assert(item != NULL);
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_DCL).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_ACL).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_GND).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_DC).c_str()));
                ::SendMessage(item, CB_SETCURSEL, 0, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_CBCOUPCUR);
                assert(item != NULL);
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_DCL).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_ACL).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_GND).c_str()));
                ::SendMessage(item, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
                    ::load_string(IDS_COUPLING_DC).c_str()));
                ::SendMessage(item, CB_SETCURSEL, 0, 0);
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_TBDLTIMEOUT);
                assert(item != NULL);
                auto value = std::to_string(10000);
                ::SendMessage(item, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(
                    value.c_str()));
            }

            {
                auto item = ::GetDlgItem(hWnd, IDC_SLDLRETRIES);
                assert(item != NULL);
                ::SendMessage(item, TBM_SETRANGEMIN, 0, 0);
                ::SendMessage(item, TBM_SETRANGEMAX, 0, 8);
            }
            return TRUE;

        case WM_CLOSE:
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return FALSE;

        default:
            return FALSE;
    }
}


/*
 * ::visual_config
 */
int visual_config(void) {
    const auto instance = ::GetModuleHandle(NULL);
    const auto accelerators = ::LoadAccelerators(instance,
        MAKEINTRESOURCE(IDR_ACCELERATOR));
    MSG msg;

    wil::unique_hwnd wnd(::CreateDialog(instance,
        MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, wnd_proc));
    THROW_LAST_ERROR_IF(!wnd);
    ::ShowWindow(wnd.get(), SW_SHOW);

    while (::GetMessage(&msg, nullptr, 0, 0)) {
        if (::IsDialogMessage(wnd.get(), &msg)) {
            continue;
        }

        if (::TranslateAccelerator(wnd.get(), accelerators, &msg)) {
            continue;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return 0;
}

#endif /* defined(_WIN32) */
