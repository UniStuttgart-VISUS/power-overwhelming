// <copyright file="oscilloscope_sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/oscilloscope_channel.h"
#include "power_overwhelming/oscilloscope_waveform.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines a raw sample that is obtained from an oscilloscope.
    /// </summary>
    /// <remarks>
    /// <para>The raw sample comprises the waveforms of all channels and all
    /// history segments that are active when obtaining the sample. Callers can
    /// use <see cref="channel_waveform::channel" /> and
    /// <see cref="oscilloscope_waveform::segment_offset" /> to find out from
    /// which channel each of the waveforms originated and which segment it is.
    /// </para>
    /// </remarks>
    class POWER_OVERWHELMING_API oscilloscope_sample final {

    public:

        /// <summary>
        /// Container for the waveform of a single channel.
        /// </summary>
        class channel_waveform final {

        public:

            /// <summary>
            /// The type to number channels.
            /// </summary>
            typedef oscilloscope_channel::channel_type channel_type;

            /// <summary>
            /// Initialises a new instance.
            /// </summary>
            inline channel_waveform(void) : _channel(0) { }

            /// <summary>
            /// Initialises a new instance.
            /// </summary>
            /// <param name="channel">The number of the channel the waveform was
            /// obtained from.</param>
            /// <param name="waveform">The waveform holding the samples for the
            /// channel.</param>
            inline channel_waveform(_In_ const channel_type channel,
                    _Inout_ oscilloscope_waveform&& waveform) noexcept
                : _channel(channel), _waveform(std::move(waveform)) { }

            /// <summary>
            /// Gets the number of the channel the waveform was obtained from.
            /// </summary>
            /// <returns>The one-based number of the channel.</returns>
            inline channel_type channel(void) const noexcept {
                return this->_channel;
            }

            /// <summary>
            /// Gets the waveform of the channel.
            /// </summary>
            /// <returns>The waveform obtained from the oscilloscope.</returns>
            inline const oscilloscope_waveform& waveform(void) const noexcept {
                return this->_waveform;
            }

            /// <summary>
            /// Gets the waveform of the channel.
            /// </summary>
            /// <returns>The waveform obtained from the oscilloscope.</returns>
            inline operator const oscilloscope_waveform&(void) const noexcept {
                return this->_waveform;
            }

        private:

            channel_type _channel;
            oscilloscope_waveform _waveform;
        };

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline oscilloscope_sample(void) : _size(0), _waveforms(nullptr) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// Instances created via this constructor are usually produced by the
        /// instrument. There should be no need for consumers of the library to
        /// use this. If you must create your own sample, make sure to carefully
        /// read the documentation on the layout expected by the constructor.
        /// The channel-to-waveform mapping might be wrong if you fail to do so.
        /// </remarks>
        /// <param name="channels">An array of <paramref name="cnt" /> channel
        /// IDs.</param>
        /// <param name="waveforms">An array of
        /// <paramref name="cnt" /> * <paramref name="segments" /> waveforms
        /// that are in the same order as the <paramref name="channels" />. It
        /// is assumed that the segments are contiguous, ie first come the first
        /// segments for all channels, followed by the second segments, etc. For
        /// performance reasons, the waveforms are moved into the sample. The
        /// caller, however, remains owner of the memory of the array.</param>
        /// <param name="cnt">The number of channels for which waveforms are
        /// provided.</param>
        /// <param name="segments">The number of segments provided per channel.
        /// This defaults to one segment.</param>
        /// <exception cref="std::bad_alloc">If the allocation of the buffer for
        /// the waveforms failed.</exception>
        oscilloscope_sample(
            _In_reads_(cnt) const oscilloscope_channel::channel_type *channels,
            _Inout_updates_(cnt) oscilloscope_waveform *waveforms,
            _In_ const std::size_t cnt,
            _In_ const std::size_t segments = 1);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="waveforms">An array of <paramref name="cnt" />
        /// per-channel waveforms. For performance reasons, the waveforms are
        /// moved into the sample. The caller, however, remains owner of the
        /// memory of the array.</param>
        /// <param name="cnt">The number of waveforms provided.</param>
        /// <exception cref="std::bad_alloc">If the allocation of the buffer for
        /// the waveforms failed.</exception>
        oscilloscope_sample(_Inout_updates_(cnt) channel_waveform *waveforms,
            _In_ const std::size_t cnt);

        /// <summary>
        /// Initialise from move.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline oscilloscope_sample(_Inout_ oscilloscope_sample&& rhs) noexcept
                : _size(rhs._size), _waveforms(rhs._waveforms) {
            rhs._size = 0;
            rhs._waveforms = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// <summary>
        ~oscilloscope_sample(void);

        /// <summary>
        /// Answer a pointer to the first waveform in the sample.
        /// </summary>
        /// <returns>A pointer to the first waveform or <c>nullptr</c> if the
        /// sample is empty.</returns>
        const _Ret_maybenull_ channel_waveform *begin(void) const noexcept {
            return this->_waveforms;
        }

        /// <summary>
        /// Clears all data in the sample.
        /// </summary>
        void clear(void) noexcept;

        /// <summary>
        /// Answer whether the sample is empty.
        /// </summary>
        /// <returns><c>true</c> if the sample contains no waveforms,
        /// <c>false</c> otherwise.</returns>
        inline bool empty(void) const noexcept {
            return ((this->_size < 1) || (this->_waveforms == nullptr));
        }

        /// <summary>
        /// Answer a pointer <i>past</c> the last waveform in the sample.
        /// </summary>
        /// <returns>A pointer after the last waveform in the sample. This
        /// pointer is never valid! This pointer may be <c>nullptr</c> if
        /// the sample is empty.</returns>
        const _Ret_maybenull_ channel_waveform *end(void) const noexcept;

        /// <summary>
        /// Answer the number of waveforms (number of channels multiplied by the
        /// number of segments) stored in the sample.
        /// </summary>
        /// <returns>The number of waveforms stored in the sample.</returns>
        inline std::size_t size(void) const noexcept {
            return this->_size;
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_sample& operator =(
            _Inout_ oscilloscope_sample&& rhs) noexcept;

        /// <summary>
        /// Answer the waveform at the specified position.
        /// </summary>
        /// <remarks>
        /// <para>Callers should use <see cref="channel_waveform::channel" />
        /// and <see cref="oscilloscope_waveform::segment_offset" /> to
        /// determine the source and offset of each individual waveform.</para>
        /// </remarks>
        /// <param name="index">An index between [0, <see cref="size" />[.
        /// </param>
        /// <returns>The waveform at the specified position.</returns>
        /// <exception cref="std::range_error">If <paramref name="index" />
        /// is invalid.</exception>
        const channel_waveform& operator [](_In_ const int index) const;

    private:

        std::size_t _size;
        channel_waveform *_waveforms;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
