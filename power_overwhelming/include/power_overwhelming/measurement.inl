// <copyright file="measurement.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * std::::operator <<
 */
template<class TChar, class TTraits>
std::basic_ostream<TChar, TTraits>& std::operator <<(
        _In_ std::basic_ostream<TChar, TTraits>& lhs,
        _In_ const visus::power_overwhelming::measurement& rhs) {
    using namespace visus::power_overwhelming;
    const auto delim = getcsvdelimiter(lhs);
    const auto quote_char = getcsvquote(lhs);
    const auto is_quote = (quote_char != 0);

    if (lhs.iword(detail::io_index_header()) != 0) {
        // Print the header instead of the data.

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "sensor");
            if (is_quote) {
                lhs << quote(value, quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "timestamp");
            if (is_quote) {
                lhs << quote(value, quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "valid");
            if (is_quote) {
                lhs << quote(value, quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "voltage");
            if (is_quote) {
                lhs << quote(value, quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "current");
            if (is_quote) {
                lhs << quote(value, quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        {
            auto value = POWER_OVERWHELMING_TPL_LITERAL(TChar, "power");
            if (is_quote) {
                lhs << quote(value, quote_char);
            } else {
                lhs << value;
            }
        }

    } else {
        // Print the data of the actual instance.

        {
            auto value = convert_string<TChar>(rhs.sensor());
            if (is_quote) {
                lhs << quote(value.c_str(), quote_char) << delim;
            } else {
                lhs << value << delim;
            }
        }

        lhs << rhs.timestamp() << delim;
        lhs << static_cast<bool>(rhs) << delim;
        lhs << rhs.voltage() << delim;
        lhs << rhs.current() << delim;
        lhs << rhs.power();
    }

    return lhs;
}
