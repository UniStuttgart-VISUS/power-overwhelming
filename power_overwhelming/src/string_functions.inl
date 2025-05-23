﻿// <copyright file="string_functions.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>
/*
 * the/text/format.cpp
 *
 * Copyright (TChar) 2012 - 2015 TheLib Team (http://www.thelib.org/license)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of TheLib, TheLib Team, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THELIB TEAM AS IS AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THELIB TEAM BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 /*
  * CharTraits.cpp
  *
  * Copyright (TChar) 2006 by Universitaet Stuttgart (VIS).
// Licensed under the MIT licence. See LICENCE file for details.
  */


/*
 * PWROWG_DETAIL_NAMESPACE::copy_string
 */
template<class TChar, class TTraits, class TAlloc>
bool PWROWG_DETAIL_NAMESPACE::copy_string(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) TChar *dst,
        _In_ const std::size_t cnt,
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& string) {
    if ((cnt > 0) && (dst == nullptr)) {
        throw std::invalid_argument("A valid output buffer must be provided "
            "unless the buffer size is declared to be zero.");
    }

    const auto retval = (cnt > string.size());

    if (retval) {
        std::copy(string.begin(), string.end(), dst);
        dst[string.size()] = static_cast<TChar>(0);
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::format_string
 */
template<class ...TArgs>
std::wstring PWROWG_DETAIL_NAMESPACE::format_string(
        _In_z_ const wchar_t *format, TArgs&&... args) {
    if (format == nullptr) {
        throw std::invalid_argument("The format string must not be null.");
    }

#if (defined(_WIN32))
    // Windows has a count-only API which tells us the required size of the
    // return value without trying to format. Of course, we make use of this
    // API to prevent reallocations.
    std::wstring retval(::_scwprintf(format, std::forward<TArgs>(args)...),
        L' ');

#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
    ::_snwprintf_s(&retval[0], retval.size() + 1, retval.size(), format,
        std::forward<TArgs>(args)...);
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    ::_snwprintf(&retval[0], retval.size() + 1, format,
        std::forward<TArgs>(args)...);
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */

    return retval;

#else /* (defined(_WIN32)) */
    // On other platforms, we need to test-format the output and repeat in case
    // the buffer was too small.
    typedef std::decay<decltype(*format)>::type char_type;
    std::vector<char_type> retval(std::char_traits<char_type>::length(format));
    auto status = -1;

    for (int i = 0; (status < 0) && (i < 16); ++i) {
        retval.resize(retval.size() + retval.size() / 2);
        status = ::swprintf(retval.data(), retval.size(), format,
            std::forward<TArgs>(args)...) + 1;
    }

    if (status < 0) {
        throw std::system_error(errno, std::system_category());
    }

    return retval.data();
#endif /* (defined(_WIN32)) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::format_string
 */
template<class ...TArgs>
std::string PWROWG_DETAIL_NAMESPACE::format_string(
        _In_z_ const char *format, TArgs&&... args) {
    if (format == nullptr) {
        throw std::invalid_argument("The format string must not be null.");
    }

#if (defined(_WIN32))
    // Windows has a count-only API which tells us the required size of the
    // return value without trying to format. Of course, we make use of this
    // API to prevent reallocations.
    std::string retval(::_scprintf(format, std::forward<TArgs>(args)...), ' ');

#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
    ::_snprintf_s(&retval[0], retval.size() + 1, retval.size(), format,
        std::forward<TArgs>(args)...);
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    ::_snprintf(&retval[0], retval.size() + 1, format,
        std::forward<TArgs>(args)...);
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */

    return retval;

#else /* (defined(_WIN32)) */
    // On other platforms, we need to test-format the output and repeat in case
    // the buffer was too small.
    typedef std::decay<decltype(*format)>::type char_type;
    auto len = std::char_traits<char_type>::length(format);
    len += (len / 2) + 1;
    std::vector<char_type> retval(len);
    len = ::snprintf(retval.data(), retval.size(), format,
        std::forward<TArgs>(args)...) + 1;
    retval.resize(len);

    len = ::snprintf(retval.data(), retval.size(), format,
        std::forward<TArgs>(args)...);
    if (len < 0) {
        throw std::system_error(errno, std::system_category());
    }

    return retval.data();
#endif /* (defined(_WIN32)) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::remove_spaces
 */
template<class TChar, class TTraits, class TAlloc>
std::basic_string<TChar> PWROWG_DETAIL_NAMESPACE::remove_spaces(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str) {
    std::vector<TChar> retval(str.begin(), str.end());
    auto end = std::remove_if(retval.begin(), retval.end(),
        [](const TChar c) { return std::isspace(c); });
    return std::basic_string<TChar>(retval.begin(), end);
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_assign
 */
template<class TChar>
void PWROWG_DETAIL_NAMESPACE::safe_assign(
        _Inout_opt_z_ TChar *& dst,
        _In_opt_z_ const TChar *src) {
    if (dst != src) {
        safe_assign(dst, nullptr);
        assert(dst == nullptr);
        dst = safe_duplicate(src);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_assign
 */
template<class TChar>
void PWROWG_DETAIL_NAMESPACE::safe_assign(
        _Inout_opt_z_ TChar *& dst,
        _Inout_opt_z_ TChar *&& src) noexcept {
    if (src != dst) {
        safe_assign(dst, nullptr);
        assert(dst == nullptr);
        dst = src;
        src = nullptr;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_assign
 */
template<class TChar>
PWROWG_NAMESPACE::blob& PWROWG_DETAIL_NAMESPACE::safe_assign(
        _Inout_ blob& dst, _In_opt_z_ const TChar *src) {
    if (dst.as<TChar>() != src) {
        if (src != nullptr) {
            auto len = std::char_traits<TChar>::length(src) + 1;
            len *= sizeof(TChar);
            dst.reserve(len);
            ::memcpy(dst.data(), src, len);

        } else {
            dst.reserve(1);
            *dst.as<TChar>() = static_cast<TChar>(0);
        }
    }

    return dst;
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_assign
 */
template<class TChar>
PWROWG_NAMESPACE::blob PWROWG_DETAIL_NAMESPACE::safe_assign(
        _Inout_ blob&& dst, _In_opt_z_ const TChar *src) {
    auto retval = std::move(dst);
    safe_assign(retval, src);
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_assign
 */
template<class TChar>
void PWROWG_DETAIL_NAMESPACE::safe_assign(_Inout_opt_z_ TChar *& dst,
        _In_ const std::nullptr_t) noexcept {
    if (dst != nullptr) {
        ::free(dst);
        dst = nullptr;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_begin_if
 */
template<class TChar, class TPredicate>
_When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
TChar *PWROWG_DETAIL_NAMESPACE::trim_begin_if(_In_opt_z_ TChar *str,
        _In_ const TPredicate predicate) {
    auto retval = str;

    if (retval == nullptr) {
        return retval;
    }

    while ((*retval != 0) && predicate(*retval)) {
        ++retval;
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_begin_if
 */
template<class TChar, class TTraits, class TAlloc, class TPredicate>
std::basic_string<TChar, TTraits, TAlloc>&
PWROWG_DETAIL_NAMESPACE::trim_begin_if(
        _Inout_ std::basic_string<TChar, TTraits, TAlloc>& str,
        _In_ const TPredicate& predicate) {
    auto end = std::find_if(str.begin(), str.end(), [&predicate](const TChar c) {
        return !predicate(c);
    });
    str.erase(str.begin(), end);
    return str;
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_end_if
 */
template<class TChar, class TPredicate>
_When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
TChar *PWROWG_DETAIL_NAMESPACE::trim_end_if(_In_opt_z_ TChar *str,
        _In_ const TPredicate predicate) {
    if (str == nullptr) {
        return nullptr;
    }

    auto retval = str;
    while (*retval != static_cast<TChar>(0)) {
        ++retval;
    }
    assert(*retval == 0);
    --retval;

    while ((retval >= str) && predicate(*retval)) {
        --retval;
    }
    assert((retval < str) || !predicate(*retval));

    return ++retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_end_if
 */
template<class TChar, class TTraits, class TAlloc, class TPredicate>
std::basic_string<TChar, TTraits, TAlloc>& PWROWG_DETAIL_NAMESPACE::trim_end_if(
        _Inout_ std::basic_string<TChar, TTraits, TAlloc>& str,
        _In_ const TPredicate& predicate) {
    auto end = std::find_if(str.rbegin(), str.rend(), [&predicate](const TChar c) {
        return !predicate(c);
    });
    str.erase(end.base(), str.end());
    return str;
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_eol
 */
template<class TChar>
void PWROWG_DETAIL_NAMESPACE::trim_eol(_In_opt_z_ TChar *str) {
    static constexpr auto cr = POWER_OVERWHELMING_TPL_LITERAL(TChar, '\r');
    static constexpr auto eos = static_cast<TChar>(0);
    static constexpr auto lf = POWER_OVERWHELMING_TPL_LITERAL(TChar, '\n');

    if (str != nullptr) {
        auto end = str;
        while ((*end != eos) && (*end != cr) && (*end != lf)) {
            ++end;
        }
        *end = eos;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::trim_if
 */
template<class TChar, class TPredicate>
_When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
TChar *PWROWG_DETAIL_NAMESPACE::trim_if(_In_opt_z_ TChar *str,
        _In_ const TPredicate predicate) {
    auto retval = trim_begin_if(str, predicate);
    auto end = trim_end_if(retval, predicate);
    if (end != nullptr) {
        *end = static_cast<TChar>(0);
    }

    return retval;
}
