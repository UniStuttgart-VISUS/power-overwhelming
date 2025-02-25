// <copyright file="csv_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::csv_sink<TStream>::csv_sink
 */
template<class TStream>
PWROWG_NAMESPACE::csv_sink<TStream>::csv_sink(_Inout_ stream_type&& stream)
        : _columns(csv_column::none), _stream(std::move(stream)) {
    if (!this->_stream.is_open()) {
        throw std::invalid_argument("An open output stream must be provided.");
    }

    this->_columns = getcsvcolumns(this->_stream);
    this->_delimiter = getcsvdelimiter(this->_stream);
}


/*
 * PWROWG_NAMESPACE::csv_sink<TStream>::write_sample
 */
template<class TStream>
template<class TIterator>
void PWROWG_NAMESPACE::csv_sink<TStream>::write_samples(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const sensor_description *sensors) {
    assert(sensors != nullptr);

    if (check_csvheader(this->_stream)) {
        this->_stream
            << PWROWG_TPL_LITERAL(char_type, "Timestamp") << this->_delimiter
            << PWROWG_TPL_LITERAL(char_type, "Sensor") << this->_delimiter;

        if ((this->_columns & csv_column::id) == csv_column::id) {
            this->_stream << PWROWG_TPL_LITERAL(char_type, "ID")
                << this->_delimiter;
        }

        if ((this->_columns & csv_column::name) == csv_column::name) {
            this->_stream << PWROWG_TPL_LITERAL(char_type, "Name")
                << this->_delimiter;
        }

        if ((this->_columns & csv_column::label) == csv_column::label) {
            this->_stream << PWROWG_TPL_LITERAL(char_type, "Label")
                << this->_delimiter;
        }

        this->_stream << PWROWG_TPL_LITERAL(char_type, "Value") << std::endl;
    }

    for (auto it = begin; it != end; ++it) {
        auto& desc = sensors[it->source];

        this->_stream
            << it->timestamp << this->_delimiter
            << it->source << this->_delimiter;

        if ((this->_columns & csv_column::id) == csv_column::id) {
            this->_stream << convert_string<char_type>(desc.id())
                << this->_delimiter;
        }

        if ((this->_columns & csv_column::name) == csv_column::name) {
            this->_stream << convert_string<char_type>(desc.name())
                << this->_delimiter;
        }

        if ((this->_columns & csv_column::label) == csv_column::label) {
            this->_stream << convert_string<char_type>(desc.label())
                << this->_delimiter;
        }

        switch (desc.reading_type()) {
            case reading_type::floating_point:
                this->_stream << it->reading.floating_point;
                break;

            case reading_type::signed_integer:
                this->_stream << it->reading.signed_integer;
                break;

            case reading_type::unsigned_integer:
                this->_stream << it->reading.unsigned_integer;
                break;
        }

        this->_stream << std::endl;
    }
}


///*
// * PWROWG_NAMESPACE::csv_sink<TStream>::write_header
// */
//template<class TStream>
//void PWROWG_NAMESPACE::csv_sink<TStream>::write_header(void) {
//    const auto delimiter = getcsvdelimiter(this->_stream);
//    this->_stream
//        << PWROWG_TPL_LITERAL(char_type, "Timestamp") << delimiter
//        << PWROWG_TPL_LITERAL(char_type, "Sensor") << delimiter
//        << PWROWG_TPL_LITERAL(char_type, "Value") << std::endl;
//}
//
