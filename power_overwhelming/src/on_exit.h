// <copyright file="on_exit.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ON_EXIT_H)
#define _PWROWG_ON_EXIT_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A scope guard object that invokes a user-defined function.
/// </summary>
/// <typeparam name="TExitHandler">The type of the lambda expression to
/// be invoked.Note that the lambda expression passed for this type must
/// not throw as it might be called from the destructor.</typeparam>
template<class TExitHandler> class on_exit_guard {

public:

    /// <summary>
    /// The type of the lambda expression to be invoked.
    /// </summary>
    typedef TExitHandler exit_handler_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="exitHandler">The lambda to be invoked.</param>
    inline explicit on_exit_guard(exit_handler_type &&exitHandler)
        : _exitHandler(std::forward<exit_handler_type>(exitHandler)),
        _isInvoked(false) { }

    on_exit_guard(const on_exit_guard&) = delete;

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline on_exit_guard(on_exit_guard&& rhs)
        : _exitHandler(std::move(rhs._exitHandler)),
            _isInvoked(rhs._isInvoked) {
        rhs._isInvoked = true;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~on_exit_guard(void) {
        this->invoke();
    }

    /// <summary>
    /// If not yet called or cancelled, invoke the exit handler.
    /// </summary>
    void invoke(void) noexcept;

    /// <summary>
    /// Prevent the exit handler from being called.
    /// </summary>
    /// <remarks>
    /// This method marks the handler as being called without actually
    /// calling it. Note that this operation cannot be undone, it will
    /// ultimately prevent the lambda from being called.
    /// </remarks>
    inline void cancel(void) noexcept {
        this->_isInvoked = true;
    }

    on_exit_guard& operator =(const on_exit_guard&) = delete;

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    /// <returns><c>*this</c></returns>
    on_exit_guard& operator =(on_exit_guard&& rhs);

    /// <summary>
    /// Answer whether the exit handler is still to be invoked.
    /// </summary>
    /// <returns><c>true</c> if the lambda needs to be invoked, <c>false</c>
    /// otherwise.</returns>
    inline operator bool(void) const {
        return !this->_isInvoked;
    }

private:

    exit_handler_type _exitHandler;
    bool _isInvoked;

};

PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Create an exit guard that executes <paramref name="exitHandler" /> if
/// it is destroyed.
/// </summary>
/// <typeparam name="TExitHandler"></typeparam>
/// <param name="exitHandler"></param>
/// <returns></returns>
template<class TExitHandler>
detail::on_exit_guard<TExitHandler> on_exit(TExitHandler&& exitHandler) {
    return detail::on_exit_guard<TExitHandler>(
        std::forward<TExitHandler>(exitHandler));
}

PWROWG_NAMESPACE_END

#include "on_exit.inl"

#endif /* !defined(_PWROWG_ON_EXIT_H) */
