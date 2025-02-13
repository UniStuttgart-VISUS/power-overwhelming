// <copyright file="sampler_thread.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SAMPLER_THREAD_H)
#define _PWROWG_SAMPLER_THREAD_H
#pragma once

#include <chrono>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "thread_name.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A thread that performs periodic sampling of inherently synchronous
/// sources.
/// </summary>
class sampler_thread {

//public:
//
//    explicit sampler_thread(_In_ sampler_source *source);
//
//    ~sampler_thread(void) noexcept;
//
//private:
//
//    void sample(void);
//
//    std::chrono::milliseconds _interval;
//    mutable std::mutex _lock;
//    std::thread _thread;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SAMPLER_THREAD_H) */
