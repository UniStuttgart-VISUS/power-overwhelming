// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <chrono>
#include <cinttypes>
#include <ctime>
#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A strongly typed timestamp in 100 ns seconds since 1st January 1601 UTC.
    /// </summary>
    /// <remarks>
    /// <para>This class ensures that timestamps within the library carry
    /// semantics (fixing one of the biggest mistakes of previous versions which
    /// had time being represented as a number) while preventing STL templates
    /// being used in the ABI of the library at the same time. All chrono
    /// instantiations are either in the library or in the client code while
    /// information passes only as a number between both sides.</para>
    /// <para>The timestamp provides a variety of conversion facilities, which
    /// allow users to create their own from different other formats and to
    /// transform the timestamp into all kinds of STL time points.</para>
    /// </remarks>
    class POWER_OVERWHELMING_API timestamp final {

    public:

        /// <summary>
        /// The type used to represent timestamps.
        /// </summary>
#if defined(_WIN32)
        typedef decltype(LARGE_INTEGER::QuadPart) value_type;
#else  /* defined(_WIN32) */
        typedef std::int64_t value_type;
#endif /* defined(_WIN32) */

        /// <summary>
        /// Create a new timestamp with the specified value.
        /// </summary>
        /// <remarks>
        /// <para>As timestamps in Power Overwhelming are UTC, the input is
        /// assumed to be UTC, too.</para>
        /// </remarks>
        /// <param name="year">The year of the timestamp.</param>
        /// <param name="month">The one-based month of the timestamp.</param>
        /// <param name="day">The one-based day of the timestamp.</param>
        /// <param name="hours">The hours in 24-hours format.</param>
        /// <param name="minutes">The minutes. This parameter defaults to zero.
        /// </param>
        /// <param name="seconds">The seconds. This parameter defaults to zero.
        /// </param>
        /// <param name="millis">The milliseconds. This parameter defaults to
        /// zero.</param>
        /// <param name="nanos">The nanoseconds. This parameter defaults to
        /// zero.</param>
        /// <param name="micros">The microseconds. This parameter defaults to
        /// zero.</param>
        /// <returns>The timestamp representing the given point in time.
        /// </returns>
        static timestamp create(_In_ const int year,
            _In_ const int month,
            _In_ const int day,
            _In_ const int hours = 0,
            _In_ const int minutes = 0,
            _In_ const int seconds = 0,
            _In_ const int millis = 0,
            _In_ const int micros = 0,
            _In_ const int nanos = 0);

#if defined(_WIN32)
        /// <summary>
        /// Convert the given time in 100 ns units since 1st January 1601 UTC
        /// into a timestamp.
        /// </summary>
        /// <remarks>
        /// As <c>FILETIME</c> is the native representation of a timestamp, this
        /// is equivalent to using the constructor from
        /// <see cref="value_type" />.
        /// </remarks>
        /// <param name="t">The time since the <c>FILETIME</c> epoch. It is
        /// assumed that the input is in UTC.</param>
        /// <returns>The timestamp representing the given point in time.
        /// </returns>
        static inline timestamp from_file_time(
                _In_ const LARGE_INTEGER t) noexcept {
            return timestamp(t.QuadPart);
        }
#endif /* defined(_WIN32) */

#if defined(_WIN32)
        /// <summary>
        /// Convert the given <c>FILETIME</c> into a timestamp.
        /// </summary>
        /// <param name="t">The point in time represented by the timestamp being
        /// created. The value must be in UTC.</param>
        /// <returns>The timestamp representing the given point in time.
        /// </returns>
        static inline timestamp from_file_time(_In_ const FILETIME t) noexcept {
            // Note: Microsoft explicitly recommends this conversion instead of
            // reinterpreting the bit pattern or performing bit shifts.
            LARGE_INTEGER i;
            i.HighPart = t.dwHighDateTime;
            i.LowPart = t.dwLowDateTime;
            return timestamp(i.QuadPart);
        }
#endif /* defined(_WIN32) */

        /// <summary>
        /// Creates a new timestamp from the current value of the system clock.
        /// </summary>
        /// <returns>The current timestamp as derived from the system clock.
        /// </returns>
        static timestamp from_system_clock(void);

        /// <summary>
        /// Converts and STL time point into a timestamp.
        /// </summary>
        /// <remarks>
        /// This constructor allows for implicit conversions from any STL time
        /// point to a Power Overwhelming timestamp.
        /// </remarks>
        /// <typeparam name="TClock">The clock the time point is from.
        /// </typeparam>
        /// <typeparam name="TDuration">The duration measuring the time since
        /// the epoch of <typeparamref name="TClock" />.</typeparam>
        /// <param name="t">The time point to be converted.</param>
        template<class TClock, class TDuration>
        static inline timestamp from_time_point(
                _In_ const std::chrono::time_point<TClock, TDuration> t) {
            return timestamp(t);
        }

        /// <summary>
        /// Creates a new timestamp from the given <c>time_t</c>.
        /// </summary>
        /// <param name="t">The time to represent the timestamp.</param>
        /// <returns>The timestamp representing the given value
        /// <paramref name="t" />.</returns>
        static timestamp from_time_t(_In_ const std::time_t t);

        /// <summary>
        /// Creates a new timestamp from the given <c>std::tm</c>.
        /// </summary>
        /// <remarks>
        /// <para>As timestamps in Power Overwhelming are UTC, the input is
        /// assumed to be UTC, too.</para>
        /// </remarks>
        /// <param name="t">The time to represent the timestamp.</param>
        /// <returns>The timestamp representing the given value
        /// <paramref name="t" />.</returns>
        static timestamp from_tm(_In_ std::tm& t);

        /// <summary>
        /// Creates the current UTC timestamp.
        /// </summary>
        /// <returns>The current timestamp.</returns>
        inline static timestamp now(void) {
#if defined(_WIN32)
            FILETIME t;
            ::GetSystemTimePreciseAsFileTime(&t);
            return timestamp::from_file_time(t);
#else /* defined(_WIN32) */
            return timestamp::from_system_clock();
#endif /* defined(_WIN32) */
        }

        /// <summary>
        /// A timestamp with value zero (1st January 1601 UTC).
        /// </summary>
        static const timestamp zero;

        /// <summary>
        /// The number of ticks per second of the timestamps.
        /// </summary>
        /// <remarks>
        /// <c>std::ratio&lt;1, tick_rate&gt;</c> can be used to construct the
        /// period of a timestamp.
        /// </remarks>
        static constexpr const value_type tick_rate = 10000000LL;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor is explicit on purpose as we do not want any
        /// arbitrary number that might not represent time at all to become a
        /// timestamp without user intervention.
        /// </remarks>
        /// <param name="value">The value of the timestamp in 100 ns units
        /// since 1st January 1601 UTC.</param>
        explicit inline timestamp(_In_ const value_type value = 0) noexcept
            : _value(value) { }

        /// <summary>
        /// Converts and STL time point into a timestamp.
        /// </summary>
        /// <remarks>
        /// This constructor allows for implicit conversions from any STL time
        /// point to a Power Overwhelming timestamp.
        /// </remarks>
        /// <typeparam name="TClock">The clock the time point is from.
        /// </typeparam>
        /// <typeparam name="TDuration">The duration measuring the time since
        /// the epoch of <typeparamref name="TClock" />.</typeparam>
        /// <param name="t">The time point to be converted.</param>
        template<class TClock, class TDuration>
        timestamp(_In_ const std::chrono::time_point<TClock, TDuration> t);

        /// <summary>
        /// Converts the timestampm into a duration since 1st January 1601.
        /// </summary>
        /// <typeparam name="TPeriod">The period of the duration.</typeparam>
        /// <returns>The duration since the timestamp epoch.</returns>
        template<class TPeriod>
        std::chrono::duration<value_type, TPeriod> to_duration(void) const;

        /// <summary>
        /// Converts the timestamp into a time point of the given clock.
        /// </summary>
        /// <typeparam name="TClock">The clock defining the epoch and the 
        /// duration of a tick of the output.</typeparam>
        /// <returns>The timestamp as a time point of the specified clock.
        /// </returns>
        template<class TClock>
        typename TClock::time_point to_time_point(void) const;

        /// <summary>
        /// Advances the timestamp by the given duration.
        /// </summary>
        /// <typeparam name="TRep">The type used to represent the ticks of the
        /// duration.</typeparam>
        /// <typeparam name="TPeriod">The number of fractions of a second per
        /// tick.</typeparam>
        /// <param name="rhs">The duration to be added.</param>
        /// <returns><c>*this</c> after the duration has been added.</returns>
        template<class TRep, class TPeriod>
        inline timestamp& operator +=(_In_ const std::chrono::duration<TRep,
                TPeriod> rhs) noexcept {
            this->_value += timestamp::to_ticks(rhs);
            return *this;
        }

        /// <summary>
        /// Adds the given duration to the timestamp.
        /// </summary>
        /// <typeparam name="TRep">The type used to represent the ticks of the
        /// duration.</typeparam>
        /// <typeparam name="TPeriod">The number of fractions of a second per
        /// tick.</typeparam>
        /// <param name="rhs">The duration to be added.</param>
        /// <returns>The timestamp advanced by <paramref name="rhs" />.
        /// </returns>
        template<class TRep, class TPeriod>
        inline timestamp operator +(_In_ const std::chrono::duration<TRep,
                TPeriod> rhs) const noexcept {
            auto retval = *this;
            return (retval += rhs);
        }

        /// <summary>
        /// Decrements the timestamp by the given duration.
        /// </summary>
        /// <typeparam name="TRep">The type used to represent the ticks of the
        /// duration.</typeparam>
        /// <typeparam name="TPeriod">The number of fractions of a second per
        /// tick.</typeparam>
        /// <param name="rhs">The duration to be added.</param>
        /// <returns><c>*this</c> after the duration has been subtracted.
        /// </returns>
        template<class TRep, class TPeriod>
        inline timestamp& operator -=(_In_ const std::chrono::duration<TRep,
                TPeriod> rhs) noexcept {
            this->_value -= timestamp::to_ticks(rhs);
            return *this;
        }

        /// <summary>
        /// Subtracts the given duration to the timestamp.
        /// </summary>
        /// <typeparam name="TRep">The type used to represent the ticks of the
        /// duration.</typeparam>
        /// <typeparam name="TPeriod">The number of fractions of a second per
        /// tick.</typeparam>
        /// <param name="rhs">The duration to be added.</param>
        /// <returns>The timestamp advanced by <paramref name="rhs" />.
        /// </returns>
        template<class TRep, class TPeriod>
        inline timestamp operator -(_In_ const std::chrono::duration<TRep,
                TPeriod> rhs) const noexcept {
            auto retval = *this;
            return (retval -= rhs);
        }

        /// <summary>
        /// Answer the difference between this timestamp and the given one.
        /// </summary>
        /// <param name="rhs">The right-hand side operation that is being
        /// subtracted.</param>
        /// <returns>The duration between the two timestamps.</returns>
        inline std::chrono::duration<value_type, std::ratio<1, tick_rate>>
        operator -(_In_ const timestamp rhs) const noexcept {
            return std::chrono::duration<value_type, std::ratio<1, tick_rate>>(
                this->_value - rhs._value);
        }

        /// <summary>
        /// Gets the value of the timestamp in 100 ns units.
        /// </summary>
        /// <returns>The value of the timestamp.</returns>
        inline value_type value(void) const noexcept {
            return this->_value;
        }

        /// <summary>
        /// Gets the value of the timestamp in 100 ns units.
        /// </summary>
        /// <returns>The value of the timestamp.</returns>
        inline operator value_type(void) const noexcept {
            return this->_value;
        }

#if defined(_WIN32)
        /// <summary>
        /// Converts the timestamp to a <c>FILETIME</c>.
        /// </summary>
        /// <returns>The timestamp as <c>FILETIME</c>.</returns>
        inline operator FILETIME(void) const noexcept {
            // Note: Microsoft explicitly recommends this conversion instead of
            // reinterpreting the bit pattern or performing bit shifts.
            LARGE_INTEGER i;
            i.QuadPart = this->_value;
            FILETIME retval;
            retval.dwLowDateTime = i.LowPart;
            retval.dwHighDateTime = i.HighPart;
            return retval;
        }
#endif /* defined(_WIN32) */

        /// <summary>
        /// Converts the timestamp to a time point of the system clock.
        /// </summary>
        /// <returns>The timestamp in terms of a time point of the system clock.
        /// </returns>
        inline operator std::chrono::system_clock::time_point(void) const {
            return this->to_time_point<std::chrono::system_clock>();
        }

    private:

        /// <summary>
        /// Converts the given duration <paramref name="d" /> into timestamp
        /// ticks without changing the epoch.
        /// </summary>
        template<class TRep, class TPeriod>
        static inline constexpr value_type to_ticks(
                _In_ const std::chrono::duration<TRep, TPeriod> d) {
            typedef std::chrono::duration<value_type,
                std::ratio<1, tick_rate>> duration_type;
            return std::chrono::duration_cast<duration_type>(d).count();
        }

        /// <summary>
        /// The offset of the timestamp epoch from the UNIX epoch.
        /// </summary>
        /// <remarks>
        /// Cf.
        /// https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/SysInfo/converting-a-time-t-value-to-a-file-time.md
        /// </remarks>
        static constexpr const value_type unix_offset = 116444736000000000LL;

        value_type _value;
    };

} /* namespace power_overwhelming */
} /* namespace visus */

#include "power_overwhelming/timestamp.inl"
