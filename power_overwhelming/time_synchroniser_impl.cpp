// <copyright file="time_synchroniser_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "time_synchroniser_impl.h"

#if defined(_WIN32)
#include <WS2tcpip.h>
#endif /* defined(_WIN32) */

#include <cassert>
#include <chrono>
#include <system_error>

#include "on_exit.h"


#define TIMESYNC_MAX_DATAGRAM (1024)


/*
 * visus::power_overwhelming::detail::time_synchroniser_impl::time_synchroniser_impl
 */
visus::power_overwhelming::detail::time_synchroniser_impl
::time_synchroniser_impl(void)
    : grace_period(2), resolution(timestamp_resolution::milliseconds),
    running(false), socket(INVALID_SOCKET) { }


/*
 * visus::power_overwhelming::detail::time_synchroniser_impl::~time_synchroniser_impl
 */
visus::power_overwhelming::detail::time_synchroniser_impl
::~time_synchroniser_impl(void) {
    if (this->socket != INVALID_SOCKET) {
        ::closesocket(this->socket);
    }
}


/*
 * visus::power_overwhelming::detail::time_synchroniser_impl::on_request
 */
void visus::power_overwhelming::detail::time_synchroniser_impl::on_request(
        const tsmsg_request *request, const sockaddr& addr,
        const int addr_length) {
    assert(request != nullptr);
    tsmsg_response response(*request);

    // Note: fire and forget ...
    ::sendto(this->socket, reinterpret_cast<char *>(&response),
        sizeof(response), 0, &addr, addr_length);
}


/*
 * visus::power_overwhelming::detail::time_synchroniser_impl::on_response
 */
void visus::power_overwhelming::detail::time_synchroniser_impl::on_response(
        const tsmsg_response *response, const sockaddr& addr,
        const int addr_length) {
    assert(response != nullptr);
    const auto now = create_timestamp(this->resolution);

    // Search the corresponding request for this response. Also, clear all
    // all orphaned requests in the same pass.
    std::lock_guard<decltype(this->lock)> _l(this->lock);
    for (auto it = this->requests.begin(); it != this->requests.end(); ++it) {
        if (it->sequence_number == response->sequence_number) {
            assert(it->timestamp >= now);
            const auto roundtrip = static_cast<double>(now - it->timestamp);
            const auto server_time = response->timestamp + 0.5 * roundtrip;
            auto drift = server_time - now;

            throw "TODO: what do we do with this knowledge?";
            it = this->requests.erase(it);

        } else if (it->sequence_number + this->grace_period
                < response->sequence_number) {
            it = this->requests.erase(it);
        }
    }
}


/*
 * visus::power_overwhelming::detail::time_synchroniser_impl::receive
 */
void visus::power_overwhelming::detail::time_synchroniser_impl::receive(
        const int address_family, const std::uint16_t port) {
    assert(this->socket == INVALID_SOCKET);

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

    auto guard_wsa_cleanup = on_exit([](void) { ::WSACleanup(); });

    // Create, configure and bind the local socket.
    this->socket = ::socket(address_family, SOCK_DGRAM, IPPROTO_UDP);
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
    while (this->running.load(std::memory_order::memory_order_acquire)) {
        sockaddr addr;
        int addr_length = sizeof(addr);
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
