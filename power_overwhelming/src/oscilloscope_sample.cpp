// <copyright file="oscilloscope_sample.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_sample.h"

#include <memory>
#include <new>
#include <stdexcept>


/*
 * visus::power_overwhelming::oscilloscope_sample::oscilloscope_sample
 */
visus::power_overwhelming::oscilloscope_sample::oscilloscope_sample(
        _In_reads_(cnt) const oscilloscope_channel::channel_type *channels,
        _Inout_updates_(cnt) oscilloscope_waveform *waveforms,
        _In_ const std::size_t cnt)
        : _size(cnt), _waveforms(nullptr) {
    if (this->_size > 0) {
        this->_waveforms = static_cast<channel_waveform *>(
            ::operator new(this->_size * sizeof(channel_waveform)));

        for (std::size_t i = 0; i < this->_size; ++i) {
            new (this->_waveforms + i) channel_waveform(channels[i],
                std::move(waveforms[i]));
        }
    }
}


/*
 * visus::power_overwhelming::oscilloscope_sample::oscilloscope_sample
 */
visus::power_overwhelming::oscilloscope_sample::oscilloscope_sample(
        _Inout_updates_(cnt) channel_waveform *waveforms,
        _In_ const std::size_t cnt)
        : _size(cnt), _waveforms(nullptr) {
    if (this->_size > 0) {
        this->_waveforms = static_cast<channel_waveform *>(
            ::operator new(this->_size * sizeof(channel_waveform)));

        for (std::size_t i = 0; i < this->_size; ++i) {
            new (this->_waveforms + i) channel_waveform(
                std::move(waveforms[i]));
        }
    }
}


/*
 * visus::power_overwhelming::oscilloscope_sample::~oscilloscope_sample
 */
visus::power_overwhelming::oscilloscope_sample::~oscilloscope_sample(void) {
    this->clear();
}


/*
 * visus::power_overwhelming::oscilloscope_sample::clear
 */
void visus::power_overwhelming::oscilloscope_sample::clear(void) noexcept {
    for (auto it = this->begin(), end = this->end(); it != end; ++it) {
        it->~channel_waveform();
    }

    ::operator delete(this->_waveforms);

    this->_size = 0;
    this->_waveforms = nullptr;
}


/*
 * visus::power_overwhelming::oscilloscope_sample::end
 */
_Ret_maybenull_
const visus::power_overwhelming::oscilloscope_sample::channel_waveform *
visus::power_overwhelming::oscilloscope_sample::end(void) const noexcept {
    return (this->_waveforms != nullptr)
        ? this->_waveforms + this->_size
        : nullptr;
}


/*
 * visus::power_overwhelming::oscilloscope_sample::operator =
 */
visus::power_overwhelming::oscilloscope_sample&
visus::power_overwhelming::oscilloscope_sample::operator =(
        _Inout_ oscilloscope_sample&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->clear();

        this->_size = rhs._size;
        rhs._size = 0;
        this->_waveforms = rhs._waveforms;
        rhs._waveforms = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_sample::operator []
 */
const visus::power_overwhelming::oscilloscope_sample::channel_waveform&
visus::power_overwhelming::oscilloscope_sample::operator [](
        _In_ const int index) const {
    if (this->_waveforms == nullptr) {
        throw std::range_error("The sample does not contain any waveforms.");
    }
    if ((index < 0) || (index >= this->_size)) {
        throw std::range_error("The specified sample index is out of range.");
    }

    return this->_waveforms[index];
}
