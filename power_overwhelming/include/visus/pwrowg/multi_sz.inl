// <copyright file="multi_sz.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

/*
 * include\the\multi_sz.h
 *
 * Copyright (TChar) 2013 TheLib Team (http://www.thelib.org/license)
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
 * multi_sz.h
 *
 * Copyright (TChar) 2006 - 2007 by Universitaet Stuttgart (VIS). 
 * Alle Rechte vorbehalten.
 */


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator *
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::reference
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator *(void) const {
    return this->_current;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator ->
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::pointer
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator ->(void) const {
    return this->_current;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator ++
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::iterator::operator ++(void) {
    if (this->_current != nullptr) {
        assert(*this->_current != 0);
        while (*this->_current++ != 0);

        // Note: The loop above always increments the pointer, i.e. if we
        // detect a zero here, it is the second in a row. Hence, we set
        // 'current' to nullptr to signal that the end was reached.
        // Further note that we cannot use the second zero as end marker,
        // because an empty multi-sz is represented by nullptr and we must
        // recognise its begin as its end.
        if (*this->_current == 0) {
            this->_current = nullptr;
        }
    }

    return *this;
}



/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::add
 */
template<class TChar, class TTraits>
_Ret_maybenull_z_
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::value_type *
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::add(
        _In_opt_z_ const value_type *lhs,
        _In_opt_z_ const value_type *rhs) {
    const auto cnt_lhs = multi_sz::size(lhs);
    const auto cnt_rhs = (rhs != nullptr) ? traits_type::length(rhs) + 1 : 0;
    value_type *retval = nullptr;

    if ((cnt_lhs == 0) && (cnt_rhs > 0)) {
        // Copy 'rhs', which needs an additional terminator at the end.
        retval = new value_type[cnt_rhs + 1];
        ::memcpy(retval, rhs, cnt_rhs * sizeof(value_type));
        retval[cnt_rhs] = 0;

    } else if ((cnt_lhs > 0) && (cnt_rhs == 0)) {
        // Copy 'lhs'.
        retval = new value_type[cnt_lhs];
        ::memcpy(retval, lhs, cnt_lhs * sizeof(value_type));

    } else if ((cnt_lhs > 0) && (cnt_rhs > 0)) {
        // Perform the concatenation.
        retval = new value_type[cnt_lhs + cnt_rhs];
        ::memcpy(retval, lhs, cnt_lhs * sizeof(value_type));
        ::memcpy(retval + cnt_lhs - 1, rhs, cnt_rhs * sizeof(value_type));
        retval[cnt_lhs + cnt_rhs - 1] = 0;
    }

    return retval;
}


/* 
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::at
 */
template<class TChar, class TTraits>
_Ret_maybenull_z_
const typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::value_type *
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::at(
        _In_opt_z_ const value_type *multi_sz,
        _In_ const size_type idx) noexcept {
    auto retval = multi_sz;

    if (retval != nullptr) {
        for (size_type i = 0; (i < idx) && (*retval != 0); ++i) {
            while (*retval++ != 0);
        }

        if (*retval == 0) {
            retval = nullptr;
        }
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::copy
 */
template<class TChar, class TTraits>
template<class TIterator>
TIterator PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::copy(
        _In_opt_z_ const value_type *multi_sz,
        _In_ TIterator oit) {
    if (multi_sz != nullptr) {
        for (auto s = multi_sz; *s != 0; ++s) {
            *oit = s;
            while (*s++ != 0);
        }
    }

    return oit;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::count
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::size_type
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::count(
        _In_opt_z_ const value_type *multi_sz) noexcept {
    size_type retval = 0;
    const value_type *cursor = multi_sz;

    if (cursor != nullptr) {
        while (*cursor != static_cast<TChar>(0)) {
            while (*cursor++ != static_cast<TChar>(0));
            retval++;
        }
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::size
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::size_type
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::size(
        _In_opt_z_ const value_type *multi_sz) noexcept {
    const value_type *cursor = multi_sz;

    if (cursor != nullptr) {
        while ((*(++cursor - 1) != 0) || (*cursor != 0));
        return (cursor - multi_sz + 1);
    } else {
        return 0;
    }
}

/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz(
        _In_opt_z_ const value_type *value)
        : _value(nullptr) {
    if ((value != nullptr) && (*value != 0)) {
        auto cnt = multi_sz::size(value);
        assert(cnt > 2);
        this->_value = new value_type[cnt];
        ::memcpy(this->_value, value, cnt * sizeof(value_type));
    }
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz(
        _In_ const blob& value)
        : _value(nullptr) {
    if (!value.empty()) {
        auto cnt = multi_sz::size(value.as<TChar>());
        assert(cnt > 2);
        this->_value = new value_type[cnt];
        ::memcpy(this->_value, value.as<TChar>(), cnt * sizeof(value_type));
    }
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz
 */
template<class TChar, class TTraits> 
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::multi_sz(
        _In_reads_(cnt) const value_type **strings,
        _In_ const size_type cnt)
        : _value(nullptr) {
    if ((strings != nullptr) && (cnt> 0)) {
        // Compute the overall required buffer size.
        auto cnt_new = 0;
        for (size_type i = 0; i < cnt; i++) {
            cnt_new += traits_type::length(strings[i]) + 1;
        }

        // Alocate the buffer including the final terminator.
        this->_value = new value_type[cnt_new + 1];

        // Copy the individual strings.
        auto dst = this->_value;
        for (size_type i = 0; i < cnt; ++i) {
            if ((strings[i] != nullptr) && (*(strings[i]) != 0)) {
                auto src = strings[i];
                while ((*dst++ = *src++) != 0);
            }
        }

        // Add double-zero at end.
        *dst = 0;
    } /* if ((strings != nullptr) && (cnt> 0)) */
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::add
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::add(
        _In_opt_z_ const value_type *str) {
    auto value = add(this->_value, str);
    this->clear();
    this->_value = value;
    return *this;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::insert
 */
template<class TChar, class TTraits> 
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::insert(_In_ const size_type idx,
        _In_opt_z_ const value_type *str) {
    const auto cnt_cur = multi_sz::length(this->_value);

    if (idx >= multi_sz::count(this->_value)) {
        this->add(str);

    } else if ((str != nullptr) && (*str != 0)) {
        const auto cnt_str = traits_type::length(str) + 1;
        const auto offset = this->at(idx) - this->_value;
        assert(cnt_cur > 0);
        assert(cnt_str > 0);

        auto value = new value_type[cnt_cur + cnt_str];
        ::memcpy(value,
            this->_value,
            offset * sizeof(value_type));
        ::memcpy(value + offset,
            str,
            cnt_str * sizeof(value_type));
        ::memcpy(value + offset + cnt_str,
            this->_value + offset,
            (cnt_cur - offset) * sizeof(value_type));
        assert(value[cnt_cur + cnt_str - 1] == 0);
        assert(value[cnt_cur + cnt_str - 2] == 0);

        this->clear();
        this->_value = value;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::remove
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::remove(
        _In_opt_z_ const value_type *str) {
    if ((str != nullptr) && (*str != 0)) {
        this->remove_if([str](const value_type *s) {
            assert(s != nullptr);
            auto l = str;
            auto r = s;

            while ((*l != 0) && (*l == *r)) {
                ++l;
                ++r;
            }

            return (*l == *r);
        });
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::remove_if
 */
template<class TChar, class TTraits>
template<class TPredicate>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::remove_if(
        _In_ const TPredicate predicate) {
    if (this->_value != nullptr) {
        auto cnt_rem = static_cast<std::size_t>(0);
        std::vector<const value_type *> rems;

        // Find the matches to be removed.
        {
            auto cursor = this->_value;

            while (*cursor != 0) {
                if (predicate(cursor)) {
                    // Remember the match and consume it.
                    rems.push_back(cursor);

                    while (*cursor++ != 0) {
                        ++cnt_rem;
                    }

                    ++cnt_rem;  // Terminator must be removed as well.

                } else {
                    // Consume the non-match.
                    while (*cursor++ != 0);
                }
            }
        }

        // Reallocate and copy the non-removed elements.
        if (cnt_rem > 0) {
            const auto cnt_cur = multi_sz::size(this->_value);

            if (cnt_rem + 1 < cnt_cur) {
                const auto cnt_new = cnt_cur - cnt_rem;
                auto rem = rems.begin();
                auto src = this->_value;
                auto dst = new value_type[cnt_new];
                auto value = dst;

                while (*src != 0) {
                    if ((rem == rems.end()) || (src != *rem)) {
                        while ((*dst++ = *src++) != 0);
                    } else {
                        while (*src++ != 0);
                        ++rem;
                    }
                }

                *dst = 0;   // Add double terminator at end.

                delete[] this->_value;
                this->_value = value;
                assert(this->_value[cnt_new - 1] == 0);
                assert(this->_value[cnt_new - 2] == 0);

            } else {
                // Everything matched, so clear the whole data.
                this->clear();
            }
        }

    } /* if (this->_value != nullptr) */

    return *this;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator =
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator =(
        _In_ const multi_sz& rhs) {
    if (this != std::addressof(rhs)) {
        this->clear();

        auto cnt = rhs.size();
        if (cnt > 0) {
            assert(cnt > 2);
            this->_value = new value_type[cnt];
            ::memcpy(this->_value, rhs._value, cnt * sizeof(value_type));
        }
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator =
 */
template<class TChar, class TTraits>
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>&
PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator =(
        _Inout_ multi_sz&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_value = rhs._value;
        rhs._value = nullptr;
    }

    return *this;
}

/*
 * PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator ==
 */
template<class TChar, class TTraits>
bool PWROWG_NAMESPACE::multi_sz<TChar, TTraits>::operator ==(
        _In_ const multi_sz& rhs) const noexcept {
    if ((this->_value == nullptr) && (rhs._value == nullptr)) {
        // Trivial accept.
        return true;
    }

    if ((this->_value == nullptr) || (rhs._value == nullptr)) {
        // Trivial reject.
        return false;
    }

    auto l = this->_value;
    auto r = rhs._value;
    assert(l != nullptr);
    assert(r != nullptr);

    // Note: memcmp is not more efficient here as we need to count in any case.
    while ((*l != 0) && (*r != 0)) {
        while (*l++ == *r++) {
            if (*l == 0) {
                ++l; ++r;
                break;
            }
        }
    }

    return (*l == *r);
}
