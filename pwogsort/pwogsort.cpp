// <copyright file="pwogsort.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/pwog_file.h"
#include "visus/pwrowg/string_functions.h"


/// <summary>
/// Finds the command line switch <paramref name="name"/> in the given command
/// line.
/// </summary>
template<class TIterator> TIterator find_switch(_In_ const TIterator begin,
        _In_ const TIterator end, _In_z_ const char *name) {
    return std::find_if(begin, end, [name](_In_ const char *arg) {
        return visus::pwrowg::detail::equals(arg, name, true);
    });
}

/// <summary>
/// Finds the value of the command line argument <paramref name="name"/> in the
/// given command line.
/// </summary>
template<class TIterator> TIterator find_argument(_In_ const TIterator begin,
        _In_ const TIterator end, _In_z_ const char *name) {
    auto retval = find_switch(begin, end, name);
    if (retval != end) {
        ++retval;
    }
    return retval;
}


/// <summary>
/// Entry point of the pwog2parquet application, which converts a PWOG file to
/// a Parquet file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(const int argc, const char **argv) {
    using namespace visus::pwrowg;
    typedef std::underlying_type_t<reading_type> reading_t;
    typedef std::underlying_type_t<sensor_type> sensor_t;
    typedef std::underlying_type_t<reading_unit> unit_t;

    const auto end = argv + argc;

    try {
        // Process command line arguments.
        std::string input;
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
            if (it == end) {
                auto pos = input.find_last_of('.');
                if (pos == std::string::npos) {
                    output = input + "-sorted.pwog";
                } else {
                    output = input.substr(0, pos) + "-sorted.pwog";
                }
            } else {
                output = *it;
            }
        }

        const auto timestamp = (::find_switch(argv, end, "--timestamp") != end);

        // Open the file and sort it.
        auto file = pwog_file::read(input);
        const auto written = pwog_file::sort(output, file, timestamp);
        assert(written == file.samples());
        std::cout << written << " samples sorted to " << output << std::endl;

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
