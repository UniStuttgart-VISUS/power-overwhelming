// <copyright file="csv2pwog.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include <nlohmann/json.hpp>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/dump_sensors.h"
#include "visus/pwrowg/literal.h"
#include "visus/pwrowg/pwog_file.h"
#include "visus/pwrowg/string_functions.h"
#include "visus/pwrowg/timestamp.h"


/// <summary>
/// Holds the implementations for parsing the cells of the CSV file.
/// </summary>
template<class TChar> struct cell_parser;

/// <summary>
/// Specialisation for <see langword="char" />.
/// </summary>
template<> struct cell_parser<char> final {

    static inline visus::pwrowg::sample::source_type parse_source(
            _Inout_ std::vector<char>& buffer,
            _In_ const std::size_t begin,
            _In_ const std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        auto b = buffer.data() + begin;
        b[end - begin] = 0;
        return std::strtol(b, nullptr, 10);
    }

    static inline std::string parse_string(
            _Inout_ std::vector<char>& buffer,
            _In_ const std::size_t begin,
            _In_ const std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        auto b = buffer.data() + begin;
        b[end - begin] = 0;
        return b;
    }

    static inline visus::pwrowg::timestamp parse_timestamp(
            _Inout_ std::vector<char>& buffer,
            _In_ const std::size_t begin,
            _In_ const std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        auto b = buffer.data() + begin;
        b[end - begin] = 0;
        return visus::pwrowg::timestamp(std::strtoll(b, nullptr, 10));
    }

    static inline float parse_value(
            _Inout_ std::vector<char>& buffer,
            _In_ const std::size_t begin,
            _In_ const std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        auto b = buffer.data() + begin;
        b[end - begin] = 0;
        return std::strtof(b, nullptr);
    }
};

/// <summary>
/// Specialisation for <see langword="wchar_t" />.
/// </summary>
template<> struct cell_parser<wchar_t> final {

    static inline visus::pwrowg::sample::source_type parse_source(
            _Inout_ std::vector<char>& buffer,
            _In_ std::size_t begin,
            _In_ std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        assert(begin % sizeof(wchar_t) == 0);
        assert(end % sizeof(wchar_t) == 0);
        end /= sizeof(wchar_t);
        auto b = reinterpret_cast<wchar_t *>(buffer.data() + begin);
        begin /= sizeof(wchar_t);
        b[end - begin] = 0;
        return std::wcstol(b, nullptr, 10);
    }

    static inline std::string parse_string(
            _Inout_ std::vector<char>& buffer,
            _In_ std::size_t begin,
            _In_ std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        assert(begin % sizeof(wchar_t) == 0);
        assert(end % sizeof(wchar_t) == 0);
        end /= sizeof(wchar_t);
        auto b = reinterpret_cast<wchar_t *>(buffer.data() + begin);
        begin /= sizeof(wchar_t);
        b[end - begin] = 0;
        return visus::pwrowg::convert_string<char>(b);
    }

    static inline visus::pwrowg::timestamp parse_timestamp(
            _Inout_ std::vector<char>& buffer,
            _In_ std::size_t begin,
            _In_ std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        assert(begin % sizeof(wchar_t) == 0);
        assert(end % sizeof(wchar_t) == 0);
        end /= sizeof(wchar_t);
        auto b = reinterpret_cast<wchar_t *>(buffer.data() + begin);
        begin /= sizeof(wchar_t);
        b[end - begin] = 0;
        return visus::pwrowg::timestamp(std::wcstoll(b, nullptr, 10));
    }

    static inline float parse_value(
            _Inout_ std::vector<char>& buffer,
            _In_ std::size_t begin,
            _In_ std::size_t end) {
        assert(begin < buffer.size());
        assert(end <= buffer.size());
        assert(begin % sizeof(wchar_t) == 0);
        assert(end % sizeof(wchar_t) == 0);
        end /= sizeof(wchar_t);
        auto b = reinterpret_cast<wchar_t *>(buffer.data() + begin);
        begin /= sizeof(wchar_t);
        b[end - begin] = 0;
        return std::wcstof(b, nullptr);
    }
};

/// <summary>
/// Answer whether the line described by the given <paramref name="offsets"/> is
/// empty, but not incomplete.
/// </summary>
static inline bool empty_line(
        _In_ const std::tuple<std::size_t, std::size_t, std::size_t>& offsets) {
    static constexpr auto invalid = (std::numeric_limits<std::size_t>::max)();
    return (std::get<0>(offsets) == invalid)
        && (std::get<1>(offsets) == invalid)
        && (std::get<2>(offsets) != invalid);
}

/// <summary>
/// Finds the command line switch <paramref name="name"/> in the given command
/// line.
/// </summary>
template<class TIterator> static TIterator find_switch(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_z_ const char *name) {
    return std::find_if(begin, end, [name](_In_ const char *arg) {
        return visus::pwrowg::detail::equals(arg, name, true);
    });
}

/// <summary>
/// Finds the value of the command line argument <paramref name="name"/> in the
/// given command line.
/// </summary>
template<class TIterator> static TIterator find_argument(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_z_ const char *name) {
    auto retval = ::find_switch(begin, end, name);
    if (retval != end) {
        ++retval;
    }
    return retval;
}

/// <summary>
/// Answer whether the line described by the given <paramref name="offsets"/> is
/// incomplete
/// </summary>
static inline bool incomplete_line(
        _In_ const std::tuple<std::size_t, std::size_t, std::size_t>& offsets) {
    static constexpr auto invalid = (std::numeric_limits<std::size_t>::max)();
    return (std::get<2>(offsets) == invalid);
}


/// <summary>
/// Scan until the end of the line starting at <paramref name="offset" />.
/// </summary>
template<class TChar>
static std::tuple<std::size_t, std::size_t, std::size_t> scan_line(
        _In_ const std::vector<char>& buffer,
        _In_ const std::size_t offset,
        _In_ const std::string& separator) {
    assert(offset < buffer.size());
    assert(offset % sizeof(TChar) == 0);
    static constexpr auto invalid = (std::numeric_limits<std::size_t>::max)();
    // Note: the following (static) only works because the 'separator' cannot
    // change at all while the programme is running.
    static const std::array<TChar, 3> tokens = {
        visus::pwrowg::convert_string<TChar>(separator).front(),
        PWROWG_TPL_LITERAL(TChar, '\r'),
        PWROWG_TPL_LITERAL(TChar, '\n'),
    };

    std::size_t source = invalid;
    std::size_t value = invalid;
    std::size_t next = invalid;

    for (std::size_t i = offset; i < buffer.size(); i += sizeof(TChar)) {
        const auto c = *reinterpret_cast<const TChar *>(buffer.data() + i);
        const auto it = std::find_if(tokens.begin(),
            tokens.end(),
            [&c](_In_ const TChar t) { return (c == t); });

        if (it == tokens.end()) {
            continue;
        }

        if (std::distance(tokens.begin(), it) > 0) {
            assert(i % sizeof(TChar) == 0);
            next = i;
            break;
        }

        if (source == invalid) {
            assert(i % sizeof(TChar) == 0);
            source = i;

        } else if (value == invalid) {
            assert(i % sizeof(TChar) == 0);
            value = i;
        }
    }

    return std::make_tuple(source, value, next);
}


/// <summary>
/// Entry point of the csv2pwog application, which converts the outputs from a
/// CSV sink into a PWOG file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(const int argc, const char **argv) {
    const auto end = argv + argc;

    std::cout << "csv2pwog" << std::endl;
    std::cout << visus::pwrowg::convert_to_oem_string(L"© 2026 "
        L"Visualisierungsinstitut der Universität Stuttgart.")
        << std::endl << std::endl;

    try {
        // Process command line arguments.
        std::size_t batch_size = 8192;
        {
            auto it = ::find_argument(argv, end, "--batch-size");
            if (it != end) {
                batch_size = std::stoul(*it);
            }
        }

        const char *input = nullptr;
        {
            auto it = ::find_argument(argv, end, "--input");
            if (it == end) {
                throw std::invalid_argument("Missing required argument --input");
            }
            input = *it;
        }

        std::string output;
        {
            auto it = ::find_argument(argv, end, "--output");
            output = (it == end)
                ? std::string(input) + ".pwog"
                : *it;
        }

        const auto overwrite = (::find_switch(argv, end, "--force") != end);

        const char *sensors = nullptr;
        {
            auto it = ::find_argument(argv, end, "--sensors");
            if (it != end) {
                sensors = *it;
            } else {
                std::cerr << "Consider providing the sensor descriptions via "
                    << "--sensors <path>. The conversion can be performed "
                    << "without this information, but the result will not be "
                    << "a self-contained data set that can be used without "
                    << "having the sensor description." << std::endl;
            }
        }

        std::string separator = ",";
        {
            auto it = ::find_argument(argv, end, "--separator");
            if ((it != end) && (**it != 0)) {
                separator = *it;
            }
        }

        // TODO: Find a CSV library that can handle our files. rapidcsv needs too much memory for actual data sets.
        std::vector<char> buffer;
        std::size_t char_size = 1;
        decltype(&cell_parser<char>::parse_source) parse_source = nullptr;
        decltype(&cell_parser<char>::parse_string) parse_string = nullptr;
        decltype(&cell_parser<char>::parse_timestamp) parse_timestamp = nullptr;
        decltype(&cell_parser<char>::parse_value) parse_value = nullptr;
        decltype(&::scan_line<char>) scan_line = nullptr;
        std::ifstream stream(input, std::ios::binary);

        // Check whether we can potentially read everything at once.
        stream.seekg(0, std::ios::end);

        try {
            buffer.resize(static_cast<std::size_t>(stream.tellg()));
        } catch (std::bad_alloc) {
            buffer.resize(batch_size);
        }

        // Process the input.
        stream.seekg(0, std::ios::beg);
        stream.read(buffer.data(), buffer.size());
        if (stream.gcount() < buffer.size()) {
            buffer.resize(stream.gcount());
        }

        // Make sure we have sufficient data to make our next decision, which is
        // whether we have UTF-16 input (from Unreal).
        {
            auto len =::strnlen(buffer.data(), buffer.size());
            while (len == buffer.size()) {
                const auto off = buffer.size();
                buffer.resize(buffer.size() * 2 + 1);
                stream.read(buffer.data() + off, buffer.size() - off);
                len = ::strnlen(buffer.data(), buffer.size());
            }

            assert(len > 0);
            if (len <= 1) {
                typedef ::cell_parser<wchar_t> parser_type;
                char_size = sizeof(wchar_t);
                parse_source = &parser_type::parse_source;
                parse_string = &parser_type::parse_string;
                parse_timestamp = &parser_type::parse_timestamp;
                parse_value = &parser_type::parse_value;
                scan_line = &::scan_line<wchar_t>;
            } else {
                typedef ::cell_parser<char> parser_type;
                parse_source = &parser_type::parse_source;
                parse_string = &parser_type::parse_string;
                parse_timestamp = &parser_type::parse_timestamp;
                parse_value = &parser_type::parse_value;
                scan_line = &::scan_line<char>;
            }
        }
        assert(parse_source != nullptr);
        assert(parse_string != nullptr);
        assert(parse_timestamp != nullptr);
        assert(parse_value != nullptr);
        assert(scan_line != nullptr);

        // Now, make sure that the buffer if sufficient to hold the first line
        // and that the first line holds the expected header information.
        std::size_t offset = 0;
        {
            auto [src, val, nxt] = scan_line(buffer, 0, separator);
            while ((nxt >= buffer.size()) && !stream.eof()) {
                buffer.resize(buffer.size() * 2 + char_size);

                assert(buffer.size() > offset);
                const auto req = buffer.size() - offset;
                stream.read(buffer.data() + offset, req);
                if (stream.gcount() < req) {
                    buffer.resize(offset + stream.gcount());
                }
                offset += stream.gcount();

                std::tie(src, val, nxt) = scan_line(buffer, 0, separator);
            }

            if ((src == std::string::npos) || (val == std::string::npos)
                    || (nxt == std::string::npos)) {
                throw std::invalid_argument("The input file does not contain "
                    "the required number of columns.");
            }

            if (parse_string(buffer, 0, src) != "Timestamp") {
                throw std::invalid_argument("The first column must be entitled "
                    "\"Timestamp\".");
            }

            if (parse_string(buffer, src + char_size, val) != "Sensor") {
                throw std::invalid_argument("The second column must be entitled "
                    "\"Sensor\".");
            }

            if (parse_string(buffer, val + char_size, nxt) != "Value") {
                throw std::invalid_argument("The third column must be entitled "
                    "\"Value\".");
            }

            offset = nxt + char_size;
        }

        // Now we are ready to parse the data, so we create the output file and
        // write the meta data.
        auto file = visus::pwrowg::pwog_file::create(output, overwrite);
        file << visus::pwrowg::make_pwog_meta_data("ConvertedFrom", input);
        file << visus::pwrowg::make_pwog_meta_data("ConvertedAt",
            std::to_string(visus::pwrowg::timestamp::now().value()));

        // If we have sensor meta data, record the source and copy it to the
        // output.
        if (sensors != nullptr) {
            file << visus::pwrowg::make_pwog_meta_data("SensorsFrom", sensors);
            const auto descs = visus::pwrowg::restore_sensor_descriptions(
                sensors);

            for (auto& d : descs) {
                file << d;
            }

            std::cout << "Embedded " << descs.size() << " sensor "
                "description(s) from " << sensors << std::endl;
        }

        // Process the rest of the input, which must only be data.
        std::size_t cnt = 0;
        while (offset < buffer.size()) {
            const auto offsets = scan_line(buffer, offset, separator);

            if (::incomplete_line(offsets) && !stream.eof()) {
                // We do not have sufficient data, so read more from the file.
                auto off = buffer.size();

                if (offset == 0) {
                    // The buffer is too small to hold the line, so we allocate
                    // more space.
                    assert(buffer.size() > 0);
                    buffer.resize(buffer.size() * 2);

                } else {
                    // The buffer contains data that has already been processed.
                    std::memmove(buffer.data(),
                        buffer.data() + offset,
                        buffer.size() - offset);
                    off = buffer.size() - offset;
                    offset = 0;
                }

                assert(buffer.size() > off);
                const auto req = buffer.size() - off;
                stream.read(buffer.data() + off, req);
                if (req > stream.gcount()) {
                    buffer.resize(off + stream.gcount());
                }
                continue;

            } else if (!::empty_line(offsets)) {
                auto [s, v, n] = offsets;

                if (n > buffer.size()) {
                    // Handle the case where the last line in the file does not
                    // end with a line break.
                    assert(stream.eof());
                    n = buffer.size();
                }

                const auto ts = parse_timestamp(buffer, offset, s);
                const auto src = parse_source(buffer, s + char_size, v);
                const auto val = parse_value(buffer, v + char_size, n);
                file << visus::pwrowg::sample(src, ts, val);
                ++cnt;
            }

            // At this point, we have at least a line break. We only consume
            // one character at this point and let the Windows line break be
            // treated as an empty input line, which is ignored.
            assert(std::get<2>(offsets) < buffer.size());
            offset = std::get<2>(offsets) + char_size;
            assert(offset % char_size == 0);

            if (offset == buffer.size()) {
                // We have consumed exactly one buffer, refill it.
                stream.read(buffer.data(), buffer.size());
                if (stream.gcount() < buffer.size()) {
                    buffer.resize(stream.gcount());
                }
                offset = 0;
            }
        }

        std::cout << "Wrote " << cnt << " samples to " << output << std::endl;

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
