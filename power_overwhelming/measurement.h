#pragma once

#include <chrono>
#include <limits>
#include <type_traits>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Represents a single measurement sample for current, voltage and power.
    /// </summary>
    /// <typeparam name="TTimestamp"></typeparam>
    /// <typeparam name="TValue"></typeparam>
    template<class TTimestamp = std::chrono::high_resolution_clock::time_point,
        class TValue = float>
    class measurement {

    public:

        static_assert(std::is_signed<TValue>::value, "The value type for "
            "measurements must be signed");

        /// <summary>
        /// The type of a timestamp associated with a measurement.
        /// </summary>
        typedef TTimestamp timestamp_type;

        /// <summary>
        /// The type of current and voltage measurements.
        /// </summary>
        typedef TValue value_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp"></param>
        /// <param name="voltage"></param>
        /// <param name="current"></param>
        /// <param name="power"></param>
        inline measurement(const timestamp_type timestamp,
                const value_type voltage, const value_type current,
                const value_type power)
            : _current(current), _power(power), _voltage(voltage) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp"></param>
        /// <param name="voltage"></param>
        /// <param name="current"></param>
        inline measurement(const timestamp_type timestamp,
                const value_type voltage, const value_type current)
            : _current(current),
            _power(std::numeric_limits<value_type>::lowest()),
            _voltage(voltage) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp"></param>
        /// <param name="power"></param>
        inline measurement(const timestamp_type timestamp,
                const value_type power)
            : _current(std::numeric_limits<value_type>::lowest()),
                _power(power),
                _voltage(std::numeric_limits<value_type>::lowest()) { }

        /// <summary>
        /// Gets the electric current (in Amperes) measured at the given point
        /// in time.
        /// </summary>
        /// <returns></returns>
        inline value_type current(void) const noexcept {
            return this->_current;
        }

        /// <summary>
        /// Gets the electric power (in Watts) measured at the given point in
        /// time.
        /// </summary>
        /// <remarks>
        /// If the specified power is negative, it is considered as not given
        /// and computed from current and voltage on the fly.
        /// </remarks>
        /// <returns></returns>
        inline value_type power(void) const noexcept {
            return (this->_power > static_cast<value_type>(0))
                ? this->_power
                : this->_current * this->_voltage;
        }

        /// <summary>
        /// Gets the timestamp of the measurement.
        /// </summary>
        /// <returns></returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

        /// <summary>
        /// Gets the electric potential (in Volts) measured at the given point
        /// in time.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        inline value_type voltage(void) const noexcept {
            return this->_voltage;
        }

    private:

        value_type _current;
        value_type _power;
        timestamp_type _timestamp;
        value_type _voltage;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
