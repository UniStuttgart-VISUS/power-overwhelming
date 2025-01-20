// <copyright file="rtx_sample.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_sample.h"

#include <memory>
#include <new>
#include <stdexcept>


/*
 * PWROWG_NAMESPACE::rtx_sample::rtx_sample
 */
PWROWG_NAMESPACE::rtx_sample::rtx_sample(
        _In_reads_(cnt) const rtx_channel::channel_type *channels,
        _Inout_updates_(cnt) rtx_waveform *waveforms,
        _In_ const std::size_t cnt,
        _In_ const std::size_t segments)
        : _size(cnt * segments), _waveforms(nullptr) {
    if (this->_size > 0) {
        this->_waveforms = new channel_waveform[this->_size];

        for (std::size_t i = 0; i < this->_size; ++i) {
            this->_waveforms[i] = channel_waveform(channels[i % cnt],
                std::move(waveforms[i]));
        }
    }
}


/*
 * PWROWG_NAMESPACE::rtx_sample::rtx_sample
 */
PWROWG_NAMESPACE::rtx_sample::rtx_sample(
        _Inout_updates_(cnt) channel_waveform *waveforms,
        _In_ const std::size_t cnt)
        : _size(cnt), _waveforms(nullptr) {
    if (this->_size > 0) {
        this->_waveforms = new channel_waveform[this->_size];

        for (std::size_t i = 0; i < this->_size; ++i) {
            this->_waveforms[i] = std::move(waveforms[i]);
        }
    }
}


/*
 * PWROWG_NAMESPACE::rtx_sample::~rtx_sample
 */
PWROWG_NAMESPACE::rtx_sample::~rtx_sample(void) {
    delete[] this->_waveforms;
}


/*
 * PWROWG_NAMESPACE::rtx_sample::clear
 */
void PWROWG_NAMESPACE::rtx_sample::clear(void) noexcept {
    delete[] this->_waveforms;
    this->_size = 0;
    this->_waveforms = nullptr;
}


/*
 * PWROWG_NAMESPACE::rtx_sample::end
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::rtx_sample::channel_waveform *
PWROWG_NAMESPACE::rtx_sample::end(void) const noexcept {
    return (this->_waveforms != nullptr)
        ? this->_waveforms + this->_size
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::rtx_sample::operator =
 */
PWROWG_NAMESPACE::rtx_sample&
PWROWG_NAMESPACE::rtx_sample::operator =(_Inout_ rtx_sample&& rhs) noexcept {
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
 * PWROWG_NAMESPACE::rtx_sample::operator []
 */
const PWROWG_NAMESPACE::rtx_sample::channel_waveform&
PWROWG_NAMESPACE::rtx_sample::operator [](
        _In_ const int index) const {
    if (this->_waveforms == nullptr) {
        throw std::range_error("The sample does not contain any waveforms.");
    }
    if ((index < 0) || (index >= this->_size)) {
        throw std::range_error("The specified sample index is out of range.");
    }

    return this->_waveforms[index];
}
