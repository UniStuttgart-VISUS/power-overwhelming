// <copyright file="csv_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::sample_callback
 */
template<class TStream, std::size_t PageSize>
void PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::sample_callback(
        _In_reads_(cnt) const sample *samples,
        _In_ const std::size_t cnt,
        _In_opt_ void *context) {
    assert(context != nullptr);
    auto that = static_cast<csv_sink *>(context);

    for (std::size_t i = 0; i < cnt; ++i) {
        that->_collector.push(samples[i]);
    }
}


/*
 * PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::csv_sink
 */
template<class TStream, std::size_t PageSize>
PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::csv_sink(
        _Inout_ stream_type&& stream)
    : _evt_write(create_event(false, false)),
        _stream(std::move(stream)) {
    if (!this->_stream.is_open()) {
        throw std::invalid_argument("An open output stream must be provided.");
    }
}


/*
 * PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::write_header
 */
template<class TStream, std::size_t PageSize>
void PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::write_header(void) {
    const auto delimiter = getcsvdelimiter(this->_stream);
    this->_stream
        << PWROWG_TPL_LITERAL(char_type, "Timestamp") << delimiter
        << PWROWG_TPL_LITERAL(char_type, "Sensor") << delimiter
        << PWROWG_TPL_LITERAL(char_type, "Value") << std::endl;
}


/*
 * PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::write
 */
template<class TStream, std::size_t PageSize>
void PWROWG_NAMESPACE::csv_sink<TStream, PageSize>::write(void) {
    const auto delimiter = getcsvdelimiter(this->_stream);

    set_thread_name("PwrOwg CSV Writer");

    while (true) {
        wait_event(this->_evt_write);
        auto data = this->_collector.reset();

        for (auto& d : data) {
            this->_stream
                << d.sample.timestamp << delimiter
                << d.sensor << delimiter;

            // TODO: need to find out what the correct type is ...

            this->_stream << std::endl;
        }
    }
}
