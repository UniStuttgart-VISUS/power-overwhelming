﻿// <copyright file="csv_iomanip.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <iostream>

#include "power_overwhelming/literal.h"
#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Base class for proxied embedding characters into a stream.
    /// </summary>
    /// <typeparam name="TChar">The character type of the stream.</typeparam>
    template<class TChar> struct csv_char_value {
        static_assert(sizeof(TChar) <= sizeof(long), "The character type "
            "of a stream-embedded CSV character must not be larger that what "
            "can be stored using iword.");

        /// <summary>
        /// The actual value to be stored using
        ///  <see cref="std::ios_base::iword" />.
        /// </summary>
        long value;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="value">The character to be embedded in the stream.</param>
        inline csv_char_value(_In_ const TChar value) : value(value) { }
    };

    /// <summary>
    /// A proxy for injecting a CSV delimiter into a stream.
    /// </summary>
    /// <typeparam name="TChar">The character type of the stream.</typeparam>
    template<class TChar>
    struct csv_delimiter final : public csv_char_value<TChar> {
        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="value">The character to be used as delimiter.</param>
        inline csv_delimiter(_In_ const TChar value)
            : csv_char_value<TChar>(value) { }
    };

    /// <summary>
    /// A proxy for injecting a CSV quote character into a stream.
    /// </summary>
    /// <typeparam name="TChar">The character type of the stream.</typeparam>
    template<class TChar>
    struct csv_quote final : public csv_char_value<TChar> {
        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="value">The character to be used as quote.</param>
        inline csv_quote(_In_ const TChar value)
            : csv_char_value<TChar>(value) { }
    };

    /// <summary>
    /// Gets the unique index value for accessing the delimiter character in
    /// the private storage of std::ios_base.
    /// </summary>
    /// <returns></returns>
    extern int POWER_OVERWHELMING_API io_index_delimiter(void) noexcept;

    /// <summary>
    /// Gets the unique index value for accessing the header option in the
    /// private storage of std::ios_base.
    /// </summary>
    /// <returns></returns>
    extern int POWER_OVERWHELMING_API io_index_header(void) noexcept;

    /// <summary>
    /// Gets the unique index value for accessing the string quoting option in
    /// the private storage of std::ios_base.
    /// </summary>
    /// <returns></returns>
    extern int POWER_OVERWHELMING_API io_index_quote(void) noexcept;

} /* namespace detail */

    /// <summary>
    /// Instructs the stream to print the actual data of measurements instead
    /// of the header line.
    /// </summary>
    /// <param name="stream">The stream to manipulate.</param>
    /// <returns><paramref name="stream" /></returns>
    inline std::ios_base& csvdata(_In_ std::ios_base& stream) {
        stream.iword(detail::io_index_header()) = static_cast<long>(0);
        return stream;
    }

    /// <summary>
    /// Instructs the stream to print the header line of measurements instead
    /// of the actual data.
    /// </summary>
    /// <param name="stream">The stream to manipulate.</param>
    /// <returns><paramref name="stream" /></returns>
    inline std::ios_base& csvheader(_In_ std::ios_base& stream) {
        stream.iword(detail::io_index_header()) = static_cast<long>(1);
        return stream;
    }

    /// <summary>
    /// Disables quoting of strings for CSV output of measurements.
    /// </summary>
    /// <remarks>
    /// We use 1 to indicate that quoting is disabled, because all custom
    /// flags are initialised to 0 and we want quoting to be enabled by
    /// default.
    /// </remarks>
    /// <param name="stream">The stream to manipulate.</param>
    /// <returns><paramref name="stream" /></returns>
    inline std::ios_base& csvnoquote(_In_ std::ios_base& stream) {
        stream.iword(detail::io_index_quote()) = static_cast<long>(0);
        return stream;
    }

    /// <summary>
    /// Enables quoting of strings for CSV output of measurements.
    /// </summary>
    /// <remarks>
    /// We use 1 to indicate that quoting is disabled, because all custom
    /// flags are initialised to 0 and we want quoting to be enabled by
    /// default.
    /// </remarks>
        /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <typeparam name="TTraits">The traits type of the stream.</typeparam>
    /// <param name="stream">The stream to manipulate.</param>
    /// <returns><paramref name="stream" /></returns>
    template<class TChar, class TTraits>
    inline std::basic_ostream<TChar, TTraits>& csvquote(
            _In_ std::basic_ostream<TChar, TTraits>& stream) {
        return stream << setcsvquote(POWER_OVERWHELMING_TPL_LITERAL(
            TChar, '"'));
    }

    /// <summary>
    /// Retrieve the CSV delimiter configured for the given stream.
    /// </summary>
    /// <remarks>
    /// If no value has been configured, this function will return the tab
    /// character as fallback.
    /// </remarks>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <typeparam name="TTraits">The traits type of the stream.</typeparam>
    /// <param name="stream">The stream to retrieve the delimiter for.</param>
    /// <returns>The configured CSV delimiter for the given stream.</returns>
    template<class TChar, class TTraits> inline TChar getcsvdelimiter(
            _In_ std::basic_ostream<TChar, TTraits>& stream) {
        auto retval = stream.iword(detail::io_index_delimiter());
        return (retval > 0)
            ? static_cast<TChar>(retval)
            : POWER_OVERWHELMING_TPL_LITERAL(TChar, '\t');
    }

    /// <summary>
    /// Retrieve the CSV quote character configured for the given stream.
    /// </summary>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <typeparam name="TTraits">The traits type of the stream.</typeparam>
    /// <param name="stream">The stream to retrieve the quote character for.
    /// </param>
    /// <returns>The configured CSV quote character for the given stream. If
    /// this value is zero, no quotes will be added.</returns>
    template<class TChar, class TTraits> inline TChar getcsvquote(
            _In_ std::basic_ostream<TChar, TTraits>& stream) {
        return static_cast<TChar>(stream.iword(detail::io_index_quote()));
    }

    /// <summary>
    /// Constructs a proxy that can be piped into a stream to configure the
    /// delimiter for CSV output of measurements in a stream.
    /// </summary>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <param name="delimiter">The delimiter to be set.</param>
    /// <returns>A proxy that can be piped into a stream.</returns>
    template<class TChar>
    inline detail::csv_delimiter<TChar> setcsvdelimiter(
            _In_ const TChar delimiter) {
        return detail::csv_delimiter<TChar>(delimiter);
    }

    /// <summary>
    /// Constructs a proxy that can be piped into a stream to configure the
    /// character used for quoting strings in the CSV output of measurements.
    /// </summary>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <param name="quote">The quote character to be set.</param>
    /// <returns>A proxy that can be piped into a stream.</returns>
    template<class TChar>
    inline detail::csv_quote<TChar> setcsvquote(_In_ const TChar quote) {
        return detail::csv_quote<TChar>(quote);
    }

} /* namespace power_overwhelming */
} /* namespace visus */


namespace std {

    /// <summary>
    /// Sets the given delimiter for CSV output of measurements in the given
    /// stream.
    /// </summary>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <typeparam name="TTraits">The traits type of the stream.</typeparam>
    /// <param name="lhs">The stream to set the I/O manipulation bits.</param>
    /// <param name="rhs">A proxy that can be obtained from
    /// <see cref="setcsvdelimiter" />.</param>
    /// <returns><paramref name="lhs" /></returns>
    template<class TChar, class TTraits>
    inline std::basic_ostream<TChar, TTraits>& operator <<(
            _In_ std::basic_ostream<TChar, TTraits>& lhs,
            _In_ const visus::power_overwhelming::detail::csv_delimiter<TChar> rhs) {
        lhs.iword(visus::power_overwhelming::detail::io_index_delimiter())
            = rhs.value;
        return lhs;
    }


    /// <summary>
    /// Sets the given quote character for CSV output of measurements in the
    /// given stream.
    /// </summary>
    /// <typeparam name="TChar">The character type used in the stream.
    /// </typeparam>
    /// <typeparam name="TTraits">The traits type of the stream.</typeparam>
    /// <param name="lhs">The stream to set the I/O manipulation bits.</param>
    /// <param name="rhs">A proxy that can be obtained from
    /// <see cref="setcsvquote" />.</param>
    /// <returns><paramref name="lhs" /></returns>
    template<class TChar, class TTraits>
    inline std::basic_ostream<TChar, TTraits>& operator <<(
            _In_ std::basic_ostream<TChar, TTraits>& lhs,
            _In_ const visus::power_overwhelming::detail::csv_quote<TChar> rhs) {
        lhs.iword(visus::power_overwhelming::detail::io_index_quote()) = rhs.value;
        return lhs;
    }
} /* end namespace std */
