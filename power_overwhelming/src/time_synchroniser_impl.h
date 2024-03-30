// <copyright file="time_synchroniser_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include <WinSock2.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#include <netinet/in.h>
#include <sys/socket.h>
#endif /* defined(_WIN32) */

#include <atomic>
#include <cinttypes>
#include <limits>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

#include "power_overwhelming/timestamp.h"


#if !defined(_WIN32)
#define SOCKET int
#endif /* !defined(_WIN32) */


namespace std {

    /// <summary>
    /// Specialisation of the <see cref="std::less" /> operator for socket
    /// addresses.
    /// </summary>
    template<> struct less<sockaddr> {
        bool operator ()(const sockaddr& lhs, const sockaddr& rhs) const;
    };
}


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Represents a request for retrieving the time from another node.
    /// </summary>
    struct tsmsg_request {
        typedef power_overwhelming::timestamp timestamp_type;

        static constexpr std::uint32_t id = 0x0001;

        std::uint32_t msg_id;
        std::uint32_t sequence_number;
        timestamp_type timestamp;

        inline tsmsg_request(const std::uint32_t sequence_number)
            : msg_id(id),
                sequence_number(sequence_number),
                timestamp(timestamp_type::now()) { }
    };

    /// <summary>
    /// Represents the response to a specific request.
    /// </summary>
    struct tsmsg_response {
        typedef power_overwhelming::timestamp timestamp_type;

        static constexpr std::uint32_t id = 0x0002;

        std::uint32_t msg_id;
        std::uint32_t sequence_number;
        timestamp_type timestamp;

        inline tsmsg_response(const tsmsg_request& request)
            : msg_id(id),
            sequence_number(request.sequence_number),
            timestamp(timestamp_type::now()) { }
    };

    /// <summary>
    /// Represents the state of a peer node of the time synchroniser.
    /// </summary>
    struct tsstate {
        typedef power_overwhelming::timestamp timestamp_type;

        timestamp_type timestamp;
        timestamp_type::value_type roundtrip;
        double drift;

        inline tsstate(void)
            : timestamp(0),
            roundtrip((std::numeric_limits<timestamp_type::value_type>::max)()),
            drift(0.0) { }
    };

    /// <summary>
    /// The actual implementation of <see cref="time_synchroniser" />, which is
    /// managing the network and threading resources.
    /// </summary>
    struct time_synchroniser_impl final {

#if defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER)
        /// <summary>
        /// The grace period for out-of-sequence requests before they are
        /// discarded.
        /// </summary>
        /// <remarks>
        /// <para>If a response is received, all outstanding
        /// <see cref="requests" /> are checked whether they have a smaller
        /// sequence number than the currently received one minus this value.
        /// If this is the case, the requests are discarded.</para>
        /// <para>This value defaults to 2.</para>
        /// </remarks>
        std::uint32_t grace_period;

        /// <summary>
        /// A lock protecting the state of the object.
        /// </summary>
        std::mutex lock;

        /// <summary>
        /// The peer nodes for which we know the drift.
        /// </summary>
        std::map<sockaddr, tsstate> peers;

        /// <summary>
        /// The receiver thread waiting for incoming synchronisation requests.
        /// </summary>
        std::thread receiver;

        /// <summary>
        /// Holds the outstanding requests for timestamps from other nodes.
        /// </summary>
        /// <remarks>
        /// <para>This list holds all outstanding requests we sent to other
        /// nodes for which no response was received yet. Once we receive a
        /// response with a matching sequence number, we use Cristian's
        /// algorithm (https://www.geeksforgeeks.org/cristians-algorithm) to
        /// compute the clock drift between the nodes.</para>
        /// </remarks>
        std::vector<tsmsg_request> requests;

        /// <summary>
        /// The datagram socket used to exchange network packets.
        /// </summary>
        SOCKET socket;

        /// <summary>
        /// Remembers the state of the thread, which is 0 if it is not running,
        /// 1 while it is running and 2 in transitional states.
        /// </summary>
        std::atomic<int> state;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        time_synchroniser_impl(void);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~time_synchroniser_impl(void);

        /// <summary>
        /// Handle a request on behalf of <see cref="receive" />.
        /// </summary>
        /// <param name="request"></param>
        /// <param name="addr"></param>
        /// <param name="addr_length"></param>
        void on_request(const tsmsg_request *request, const sockaddr& addr,
            const int addr_length);

        /// <summary>
        /// Handle a response on behalf of <see cref="receive" />.
        /// </summary>
        /// <param name="response"></param>
        /// <param name="addr"></param>
        /// <param name="addr_length"></param>
        void on_response(const tsmsg_response *response, const sockaddr& addr,
            const int addr_length);

        /// <summary>
        /// Runs the receive operations.
        /// </summary>
        /// <param name="address_family"></param>
        /// <param name="port"></param>
        void receive(const int address_family, const std::uint16_t port);

        /// <summary>
        /// Starts the time synchroniser.
        /// </summary>
        /// <param name="address_family"></param>
        /// <param name="port"></param>
        /// <exception cref="std::runtime_error">If the synchroniser is already
        /// running.</exception>
        void start(const int address_family, const std::uint16_t port);

        /// <summary>
        /// Stops the time synchroniser if it is running.
        /// </summary>
        void stop(void);
#endif /* defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER) */

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
