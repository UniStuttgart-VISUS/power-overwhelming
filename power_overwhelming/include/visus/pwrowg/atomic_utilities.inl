// <copyright file="atomic_utilities.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::atomic_change
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum>
PWROWG_DETAIL_NAMESPACE::atomic_change(
        _In_ std::atomic<TEnum>& state,
        _In_ const TEnum add,
        _In_ const TEnum remove) noexcept {
    typedef std::underlying_type_t<TEnum> t;
    const auto a = static_cast<t>(add);
    const auto r = static_cast<t>(remove);
    auto expected = state.load(std::memory_order_acquire);
    auto desired = static_cast<TEnum>((static_cast<t>(expected) | a) & ~r);

    while (!state.compare_exchange_weak(expected, desired,
            std::memory_order_acq_rel, std::memory_order_acquire)) {
        desired = static_cast<TEnum>((static_cast<t>(expected) | a) & ~r);
    }

    return expected;
}


/*
 * PWROWG_DETAIL_NAMESPACE::atomic_set
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum>
PWROWG_DETAIL_NAMESPACE::atomic_set(
        _In_ std::atomic<TEnum>& state,
        _In_ const TEnum flags) noexcept {
    typedef std::underlying_type_t<TEnum> t;
    const auto f = static_cast<t>(flags);
    auto expected = state.load(std::memory_order_acquire);
    auto desired = static_cast<TEnum>(static_cast<t>(expected) | f);

    while (!state.compare_exchange_weak(expected, desired,
            std::memory_order_acq_rel, std::memory_order_acquire)) {
        desired = static_cast<TEnum>(static_cast<t>(expected) | f);
    }

    return expected;
}


/*
 * PWROWG_DETAIL_NAMESPACE::atomic_unset
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum>
PWROWG_DETAIL_NAMESPACE::atomic_unset(
        _In_ std::atomic<TEnum>& state,
        _In_ const TEnum flags) noexcept {
    typedef std::underlying_type_t<TEnum> t;
    const auto f = static_cast<t>(flags);
    auto expected = state.load(std::memory_order_acquire);
    auto desired = static_cast<TEnum>(static_cast<t>(expected) & ~f);

    while (!state.compare_exchange_weak(expected, desired,
            std::memory_order_acq_rel, std::memory_order_acquire)) {
        desired = static_cast<TEnum>(static_cast<t>(expected) & ~f);
    }

    return expected;
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_until_all
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>> PWROWG_DETAIL_NAMESPACE::spin_until_all(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    while (!check_all(state, reference)) {
        std::this_thread::yield();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_until_all
 */
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool>
PWROWG_DETAIL_NAMESPACE::spin_until_all(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference,
        _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept {
    const auto d = std::chrono::steady_clock::now() + timeout;

    while (!check_all(state, reference)) {
        if (std::chrono::steady_clock::now() >= d) {
            return false;
        }
    }

    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_until_any
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>> PWROWG_DETAIL_NAMESPACE::spin_until_any(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    while (!check_any(state, reference)) {
        std::this_thread::yield();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_until_any
 */
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool>
PWROWG_DETAIL_NAMESPACE::spin_until_any(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference,
        _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept {
    const auto d = std::chrono::steady_clock::now() + timeout;

    while (!check_any(state, reference)) {
        if (std::chrono::steady_clock::now() >= d) {
            return false;
        }
    }

    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_while_all
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>> PWROWG_DETAIL_NAMESPACE::spin_while_all(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    while (check_all(state, reference)) {
        std::this_thread::yield();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_while_all
 */
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool>
PWROWG_DETAIL_NAMESPACE::spin_while_all(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference,
        _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept {
    const auto d = std::chrono::steady_clock::now() + timeout;

    while (check_all(state, reference)) {
        if (std::chrono::steady_clock::now() >= d) {
            return false;
        }
    }

    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_while_any
 */
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>> PWROWG_DETAIL_NAMESPACE::spin_while_any(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    while (!check_any(state, reference)) {
        std::this_thread::yield();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::spin_while_any
 */
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool>
PWROWG_DETAIL_NAMESPACE::spin_while_any(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference,
        _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept {
    const auto d = std::chrono::steady_clock::now() + timeout;

    while (!check_any(state, reference)) {
        if (std::chrono::steady_clock::now() >= d) {
            return false;
        }
    }

    return true;
}
