﻿// <copyright file="time_synchroniser_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER)
#include "time_synchroniser_impl.h"

#include <cassert>
#include <chrono>
#include <cstring>
#include <system_error>

#if defined(_WIN32)
#include <WS2tcpip.h>
#else /* defined(_WIN32) */
#include <errno.h>
#include <unistd.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/on_exit.h"


#define TIMESYNC_MAX_DATAGRAM (1024)

#if !defined(SOCKET_ERROR)
#define SOCKET_ERROR (-1)
#endif /* !defined(SOCKET_ERROR) */

#if !defined(INVALID_SOCKET)
#define INVALID_SOCKET (-1)
#endif /* !defined(INVALID_SOCKET) */


#if !defined(_WIN32)
/// <summary>
/// Returns <c>errno</c>.
/// </summary>
static inline int WSAGetLastError(void) {
    return errno;
}
#endif /* !defined(_WIN32) */


/*
 * std::less<sockaddr>::operator ()
 */
bool std::less<sockaddr>::operator ()(const sockaddr & lhs,
        const sockaddr & rhs) const {
    if (lhs.sa_family == rhs.sa_family) {
        switch (lhs.sa_family) {
            case AF_INET:
                return (::memcmp(&lhs, &rhs, sizeof(sockaddr_in)) < 0);

            case AF_INET6:
                return (::memcmp(&lhs, &rhs, sizeof(sockaddr_in6)) < 0);

            default:
                return (::memcmp(&lhs, &rhs, sizeof(sockaddr)) < 0);
        }

    } else {
        return lhs.sa_family < rhs.sa_family;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::time_synchroniser_impl
 */
PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl
::time_synchroniser_impl(void) : grace_period(2), socket(INVALID_SOCKET),
    state(0) { }


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::~time_synchroniser_impl
 */
PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::~time_synchroniser_impl(void) {
    this->stop();

    if (this->receiver.joinable()) {
        this->receiver.join();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::on_request
 */
void PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::on_request(
        const tsmsg_request *request, const sockaddr& addr,
        const int addr_length) {
    assert(request != nullptr);
    tsmsg_response response(*request);

    // Note: fire and forget ...
    ::sendto(this->socket, reinterpret_cast<char *>(&response),
        sizeof(response), 0, &addr, addr_length);
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::on_response
 */
void PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::on_response(
        const tsmsg_response *response, const sockaddr& addr,
        const int addr_length) {
    assert(response != nullptr);
    const auto now = timestamp::now();

    // Search the corresponding request for this response. Also, clear all
    // all orphaned requests in the same pass.
    std::lock_guard<decltype(this->lock)> _l(this->lock);
    for (auto it = this->requests.begin(); it != this->requests.end(); ++it) {
        if (it->sequence_number == response->sequence_number) {
            // We found a corresponding request for the response. Update the
            // estimate for the clock drift based on the round trip time of the
            // request/response pair and the time we received from the server.
            assert(it->timestamp >= now);
            const auto roundtrip = now - it->timestamp;
            auto& peer = this->peers[addr];

            if (peer.roundtrip > roundtrip.count()) {
                auto server_time = response->timestamp.value()
                    + (0.5 * roundtrip.count());
                peer.roundtrip = roundtrip.count();
                peer.timestamp = now;
                peer.drift = server_time - now;
            }

            it = this->requests.erase(it);

        } else if (it->sequence_number + this->grace_period
                < response->sequence_number) {
            // We consider this request to be orphaned, so we delete it. If we
            // still receive a response for it, it will be ignored.
            it = this->requests.erase(it);
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::receive
 */
void PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::receive(
        const int address_family, const std::uint16_t port) {
    assert(this->socket == INVALID_SOCKET);

    // Set the state of the receiver and install an exit handler that
    // marks it stopped if this scope is left. The exit guard will make
    // sure that the state is reset regardless of whether the thread
    // existed in an orderly manner or died due to an exception.
    this->state.store(1, std::memory_order::memory_order_release);

    const auto guard_state = on_exit([this](void) {
        this->state.store(0, std::memory_order::memory_order_release);
    });

#if defined(_WIN32)
    // Winsock must be initialised per thread. Also, make sure to install
    // an exit handler cleaning it up if the scope is left.
    {
        WSADATA wsa_data = { };
        auto retval = ::WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (retval != 0) {
            throw std::system_error(::WSAGetLastError(),
                std::system_category());
        }
    }

    const auto guard_wsa_cleanup = on_exit([](void) { ::WSACleanup(); });
#endif /*defined(_WIN32) */

    // Create, configure and bind the local socket.
#if defined(_WIN32)
    this->socket = ::WSASocket(address_family, SOCK_DGRAM, IPPROTO_UDP,
        nullptr, 0, WSA_FLAG_OVERLAPPED);
#else /* defined(_WIN32) */
    this->socket = ::socket(address_family, SOCK_DGRAM, IPPROTO_UDP);
#endif /* defined(_WIN32) */
    if (this->socket == INVALID_SOCKET) {
        throw std::system_error(::WSAGetLastError(),
            std::system_category());
    }

    {
        int reuse = 1;
        if (::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR,
                reinterpret_cast<char *>(&reuse), sizeof(reuse))
                == SOCKET_ERROR) {
            throw std::system_error(::WSAGetLastError(),
                std::system_category());
        }
    }

    switch (address_family) {
        case AF_INET: {
            sockaddr_in addr = { };
            addr.sin_family = address_family;
            addr.sin_port = ::htons(port);
            if (::bind(this->socket, reinterpret_cast<sockaddr *>(&addr),
                    sizeof(addr)) == SOCKET_ERROR) {
                throw std::system_error(::WSAGetLastError(),
                    std::system_category());
            }
            } break;

        case AF_INET6: {
            sockaddr_in6 addr = { };
            addr.sin6_family = address_family;
            addr.sin6_port = ::htons(port);
            if (::bind(this->socket, reinterpret_cast<sockaddr *>(&addr),
                    sizeof(addr)) == SOCKET_ERROR) {
                throw std::system_error(::WSAGetLastError(),
                    std::system_category());
            }
            } break;

        default:
            throw std::invalid_argument("Only IPv4 and IPv6 are supported by "
                "the time_synchroniser.");
    } /* end switch (address_family) */

    // Receive until indicated to leave.
    while (this->state.load(std::memory_order::memory_order_acquire) == 1) {
        sockaddr addr;
        socklen_t addr_length = sizeof(addr);
        char buffer[TIMESYNC_MAX_DATAGRAM];

        const auto cnt = ::recvfrom(this->socket, buffer, sizeof(buffer), 0,
            &addr, &addr_length);

        if (cnt != SOCKET_ERROR) {
            switch (*reinterpret_cast<std::uint32_t *>(buffer)) {
                case tsmsg_request::id:
                    this->on_request(
                        reinterpret_cast<tsmsg_request *>(buffer),
                        addr, addr_length);
                    break;

                case tsmsg_response::id:
                    this->on_response(
                        reinterpret_cast<tsmsg_response *>(buffer),
                        addr, addr_length);
                    break;

                default:
                    // Ignore anything we do not understand.
                    break;
            }
        }
    } /* end while (this->running.load(... */
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::start
 */
void PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::start(
        const int address_family, const std::uint16_t port) {
    auto expected = 0;
    if (!this->state.compare_exchange_strong(expected, 2,
            std::memory_order::memory_order_release)) {
        throw std::runtime_error("The time_synchroniser is already running");
    }

    this->receiver = std::thread(&time_synchroniser_impl::receive,
        this, address_family, port);
}


/*
 * PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::stop
 */
void PWROWG_DETAIL_NAMESPACE::time_synchroniser_impl::stop(void) {
    auto expected = 1;
    if (this->state.compare_exchange_weak(expected, 2,
            std::memory_order::memory_order_release)) {
        // Closing the socket will cause the receive to fail and the thread will
        // notice that the state has changed and it should exit.
        assert(this->socket != INVALID_SOCKET);
#if defined(_WIN32)
        ::closesocket(this->socket);
#else /* defined(_WIN3) */
        ::close(this->socket);
#endif /* defined(_WIN3) */
        this->socket = INVALID_SOCKET;
    }
}
#endif /* defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER) */
