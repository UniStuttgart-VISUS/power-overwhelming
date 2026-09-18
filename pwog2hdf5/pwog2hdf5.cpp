// <copyright file="pwog2hdf5.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
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
#include "visus/pwrowg/timestamp.h"


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
                ? std::string(input) + ".h5"
                : *it;
        }

        const auto overwrite = (::find_switch(argv, end, "--force") != end);

        const auto raw = (::find_switch(argv, end, "--raw") != end);

        std::size_t batch_size = 4096;
        {
            auto it = ::find_argument(argv, end, "--batch-size");
            if (it != end) {
                batch_size = std::stoul(*it);
            }
        }

        auto config = hdf5_configuration(output.c_str(), overwrite)
            .chunk_size(batch_size)
            .raw(raw);
        config.meta_data("Pwog2Hdf5ConvertedFrom", input);
        config.meta_data("Pwog2Hdf5FileTime", std::to_string(
            timestamp::now().value()));

        // Open the file and convert it.
        auto file = pwog_file::read(input);
        const auto written = pwog_file::to_hdf5(file, config);
        assert(written == file.samples());
        std::cout << written << " samples copied to " << output << std::endl;

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
