// <copyright file="rtx_trigger_type.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_trigger_type.h"

#include <stdexcept>

#include "visus/pwrowg/literal.h"
#include "visus/pwrowg/string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implements parsing of a trigger type.
/// </summary>
/// <typeparam name="TChar"></typeparam>
/// <param name="str"></param>
/// <returns></returns>
template<class TChar>
rtx_trigger_type parse_rtx_trigger_type(_In_z_ const TChar *str) noexcept {
#define _CHECK_STR(s, r) if (equals(str, PWROWG_TPL_LITERAL(TChar, s), true))\
    return rtx_trigger_type::r;

    if ((str == nullptr) || (*str == static_cast<TChar>(0))) {
        return rtx_trigger_type::none;
    }

    _CHECK_STR("EDGE", edge);
    _CHECK_STR("WIDT", width);
    _CHECK_STR("TV", tv);
    _CHECK_STR("BUS", bus);
    _CHECK_STR("LOG", logic);
    _CHECK_STR("LINE", line);
    _CHECK_STR("RIS", rise_time);
    _CHECK_STR("RUNT", runt);

    return rtx_trigger_type::none;
#undef _CHECK_STR
}

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_NAMESPACE::parse_rtx_trigger_type
 */
PWROWG_NAMESPACE::rtx_trigger_type PWROWG_NAMESPACE::parse_rtx_trigger_type(
        _In_z_ const wchar_t *str) noexcept {
    return detail::parse_rtx_trigger_type(str);
}


/*
 * PWROWG_NAMESPACE::parse_rtx_trigger_type
 */
PWROWG_NAMESPACE::rtx_trigger_type PWROWG_NAMESPACE::parse_rtx_trigger_type(
        _In_z_ const char *str) noexcept {
    return detail::parse_rtx_trigger_type(str);
}


/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_z_ const char *PWROWG_NAMESPACE::to_string(
        _In_ const rtx_trigger_type value) {
    switch (value) {
        case rtx_trigger_type::edge: return "EDGE";
        case rtx_trigger_type::edge_ab: return "EDGE";
        case rtx_trigger_type::width: return "WIDT";
        case rtx_trigger_type::tv: return "TV";
        case rtx_trigger_type::bus: return "BUS";
        case rtx_trigger_type::logic: return "LOG";
        case rtx_trigger_type::line: return "LINE";
        case rtx_trigger_type::rise_time: return "RIS";
        case rtx_trigger_type::runt: return "RUNT";

        default:
            throw std::invalid_argument("The specified type of trigger is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }
}
