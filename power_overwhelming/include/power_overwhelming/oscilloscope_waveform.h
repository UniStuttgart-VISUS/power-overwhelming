// <copyright file="oscilloscope_waveform.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/blob.h"
#include "power_overwhelming/measurement_data.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines a container for data obtained from an oscilloscope channel.
    /// </summary>
    /// <remarks>
    /// <para>The waveform is not copyable, but only movable for performance
    /// reasons.</para>
    /// </remarks>
    class POWER_OVERWHELMING_API oscilloscope_waveform final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        oscilloscope_waveform(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="header">The header string for the waveform data.
        /// Header data are a CSV string of the time points of the begin and
        /// the end of the waveform, the number of samples in the waveform and
        /// the number of values per sample.
        /// </param>
        /// <param name="segment_offset">The segment offset retrieved via
        /// <c>CHAN:HIST:TSR?</c>.</param>
        /// <param name="samples">A blob holding the <c>float</c> samples of
        /// the waveform. It is mandatory that the samples have been retrieved
        /// as <c>float</c> by setting <c>FORM REAL,32</c> and
        /// <c>FORM:BORD LSBF</c> (assuming an Intel architecture).</param>
        /// <exception cref="std::invalid_argument">If any of the inputs is
        /// <c>nullptr</c>.</exception>
        oscilloscope_waveform(_In_z_ const char *xor,
            _In_z_ const char *xinc,
            _In_z_ const char *segment_date,
            _In_z_ const char *segment_time,
            _In_z_ const char *segment_offset,
            _Inout_ blob&& samples);

        /// <summary>
        /// Initialise from move.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        oscilloscope_waveform(_Inout_ oscilloscope_waveform&& rhs) noexcept;

        /// <summary>
        /// A pointer to the first sample of the waveform.
        /// </summary>
        /// <returns>A pointer to the first sample.</returns>
        inline const float *begin(void) const noexcept {
            return this->samples();
        }

        /// <summary>
        /// Answer whether the waveform is empty.
        /// </summary>
        /// <returns><c>true</c> if the waveform is empty,
        /// <c>false</c> otherwise.</returns>
        inline bool empty(void) const noexcept {
            return ((this->_record_length == 0) || (this->_samples == nullptr));
        }

        /// <summary>
        /// A pointer past the last sample of the waveform.
        /// </summary>
        /// <returns>A pointer to invalid memory past the last sample.
        /// </returns>
        inline const float *end(void) const noexcept {
            return this->samples() + this->_record_length;
        }

        /// <summary>
        /// The length of the waveform in number of samples.
        /// </summary>
        /// <returns>The number of samples in the waveform.</returns>
        inline std::size_t record_length(void) const noexcept {
            return this->_record_length;
        }

        /// <summary>
        /// The offset of the begin of the waveform in seconds.
        /// </summary>
        /// <returns>The time offset of the first sample from the configured
        /// origin of the time axis, in seconds.</returns>
        inline float time_begin(void) const noexcept {
            return this->_time_begin;
        }

        /// <summary>
        /// The offset of the end of the waveform in seconds.
        /// </summary>
        /// <remarks>
        /// The end of the wavefrom is computed from <see cref="time_begin" />
        /// and <see cref="sample_distance" /> using the formula on p. 320 of
        /// the RTB2004 user manual, because these numbers are more precise than
        /// the range retrieved by <c>CHAN:DATA:HEAD</c>.
        /// </remarks>
        /// <returns>The end of the time axis in seconds.</returns>
        float time_end(void) const noexcept;

        /// <summary>
        /// Answer the specified sample value.
        /// </summary>
        /// <param name="i">The index of the sample to retrieve.</param>
        /// <returns>The value of the <paramref name="i" />th sample.</returns>
        /// <exception cref="std::range_error">If the method is called on an
        /// empty waveform (one that has no samples), or if
        /// <paramref name="i" /> is too large.</exception>
        float sample(_In_ const std::size_t i) const;

        /// <summary>
        /// A pointer to the first sample of the waveform.
        /// </summary>
        /// <returns>A pointer to the first sample.</returns>
        inline const float *samples(void) const noexcept {
            return this->_samples.as<float>();
        }

        /// <summary>
        /// Answer the temporal distance between two adjacent samples in
        /// seconds.
        /// </summary>
        /// <returns>The distance between two samples in seconds.</returns>
        inline float sample_distance(void) const noexcept {
            return this->_time_increment;
        }

        /// <summary>
        /// Answer the relative time (in seconds) within
        /// [<c>time_begin</c>, <c>time_end</c>] of the given sample.
        /// </summary>
        /// <remarks>
        /// The method does not perfom any range check, but will happily
        /// extrapolate beyond the last sample.
        /// </remarks>
        /// <param name="i">The zero-based index of the sample to retrieve the
        /// time for.</param>
        /// <returns>The time of the given sample.</returns>
        inline float sample_time(_In_ const std::size_t i) const noexcept {
            return static_cast<float>(i) * this->_time_increment
                + this->_time_begin;
        }

        /// <summary>
        /// Answer the absolute timestamp of the <paramref name="i" />th sample
        /// in the segment in 100 ns units from 1st January 1601 (UTC).
        /// </summary>
        /// <remarks>
        /// See <see cref="segment_timestamp" /> for detailed information on
        /// the form and quality of the timestamps.
        /// </remarks>
        /// <param name="i">The sample to retrieve the timestamp for.</param>
        /// <returns>The absolute timestamp of the sample.</returns>
        measurement_data::timestamp_type sample_timestamp(
            _In_ const std::size_t i) const noexcept;

        /// <summary>
        /// Answer the time difference of the segment of the waveform to the
        /// newest segment in the acquisition.
        /// </summary>
        /// <returns>The offset of the segment.</returns>
        inline float segment_offset(void) const noexcept {
            return this->_segment_offset;
        }

        /// <summary>
        /// Answer the absolute timestamp of the segment in 100 ns units from
        /// 1st January 1601 (UTC).
        /// </summary>
        /// <remarks>
        /// <para>The value of the timestamp is equivalent to the Windows
        /// <see cref="FILETIME" />. This makes it compatible with the ADL
        /// sensor, which we chose as our base as we cannot influence its
        /// implementation. In terms of STL clocks, the ratio of the timestamp
        /// is <c>std::ratio&lt;1, 10000000&gt;</c> using
        /// <see cref="timetamp_type" /> as the type of the counter.</para>
        /// <para>The timestamp is retrieved from the instrument itself, so it
        /// might not match the clock of the computer if the instrument has
        /// not been synchronised and/or the clocks are drifting. It also seems
        /// as if the instrument has only a second resolution for the first
        /// segment of an acquisition and fractional seconds are only available
        /// for subsequent timestamps.</para>
        /// </remarks>
        /// <returns>The absolute timestamp of the segment.</returns>
        measurement_data::timestamp_type segment_timestamp(
                void) const noexcept {
            return this->_segment_timestamp;
        }

        /// <summary>
        /// The length of the waveform in number of samples.
        /// </summary>
        /// <returns>The number of samples in the waveform.</returns>
        inline std::size_t size(void) const noexcept {
            return this->_record_length;
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_waveform& operator =(
            _Inout_ oscilloscope_waveform&& rhs) noexcept;

    private:

        std::size_t _record_length;
        blob _samples;
        float _segment_offset;
        measurement_data::timestamp_type _segment_timestamp;
        float _time_begin;
        float _time_increment;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
