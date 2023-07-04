// <copyright file="oscilloscope_channel_data.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_channel_data.h"

#include "string_functions.h"
#include "tokenise.h"


/*
 * visus::power_overwhelming::oscilloscope_channel_data::oscilloscope_channel_data
 */
visus::power_overwhelming::oscilloscope_channel_data::oscilloscope_channel_data(
        _In_z_ const char *header, _Inout_ blob&& samples)
        : _record_length(0),  _time_begin(0), _time_end(0) {
    if (header == nullptr) {
        throw std::invalid_argument("The data header must not be nullptr.");
    }

    const auto tokens = detail::tokenise(std::string(header), ",", true);
    if (tokens.size() < 4) {
        throw std::invalid_argument("The specified data header does not have "
            "the expected format.");
    }

    this->_time_begin = std::stof(tokens[0]);
    this->_time_end = std::stof(tokens[1]);
    this->_record_length = std::stoul(tokens[2]);

    if (this->_record_length > samples.size() / sizeof(float)) {
        throw std::invalid_argument("The number of samples in the data header "
            "does not match the sample data provided.");
    }

    // Do not move samples unless everything else succeeded.
    this->_samples = std::move(samples);
}
