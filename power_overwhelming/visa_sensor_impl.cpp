// <copyright file="visa_sensor_impl.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "visa_sensor_impl.h"

#include <algorithm>


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl
 */
visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl(
        const char *path, const std::int32_t timeout) : scope(path, timeout) {
    this->clear();
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::clear
 */
void visus::power_overwhelming::detail::visa_sensor_impl::clear(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viClear(this->scope));
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::clear_status
 */
void visus::power_overwhelming::detail::visa_sensor_impl::clear_status(void) {
    this->printf("*CLS\n");
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::identify
 */
std::string visus::power_overwhelming::detail::visa_sensor_impl::identify(
        void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto retval = this->query("*IDN?\n");
    retval.erase(std::remove_if(retval.begin(), retval.end(),
        [](const ViByte b) { return ((b == '\r') || (b == '\n')); }));
    return std::string(retval.begin(), retval.end());
#else/*defined(POWER_OVERWHELMING_WITH_VISA) */
    return "";
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::query
 */
std::vector<std::uint8_t>
visus::power_overwhelming::detail::visa_sensor_impl::query(
        const std::uint8_t *query, const std::size_t cnt,
        const std::size_t buffer_size) {
    if (query == nullptr) {
        throw std::invalid_argument("The query sent ot the instrument must "
            "not be null.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    this->write(query, cnt);
    return this->read(buffer_size);
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return std::vector<std::uint8_t>();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::query
 */
std::vector<std::uint8_t>
visus::power_overwhelming::detail::visa_sensor_impl::query(
        const std::string& query, const std::size_t buffer_size) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    this->printf(query.c_str());
    return this->read(buffer_size);
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return std::vector<std::uint8_t>();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::read
 */
std::size_t visus::power_overwhelming::detail::visa_sensor_impl::read(
        std::uint8_t *buffer, const std::size_t cnt) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viRead(this->scope, buffer, static_cast<ViUInt32>(cnt), &retval));
    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::read
 */
std::vector<std::uint8_t>
visus::power_overwhelming::detail::visa_sensor_impl::read(
        const std::size_t buffer_size) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    static const std::size_t min_size = 1;
    std::vector<std::uint8_t> retval((std::max)(buffer_size, min_size));
    ViUInt32 offset = 0;
    ViUInt32 read = 0;
    ViStatus status = VI_SUCCESS_MAX_CNT;

    while (status == VI_SUCCESS_MAX_CNT) {
        status = detail::visa_library::instance().viRead(this->scope,
            retval.data() + offset,
            static_cast<ViUInt32>(retval.size() - offset),
            &read);
        offset += read;

        if (status == VI_SUCCESS_MAX_CNT) {
            // Increase the buffer size if the message was not completely read.
            // The 50% increase is something used by many STL vector
            // implementations, so it is probably a reasonable heuristic.
            retval.resize(retval.size() + (std::max)(retval.size() / 2,
                min_size));
        } else {
            // Terminate in case of any error.
            visa_exception::throw_on_error(status);
        }
    };

    retval.resize(offset);

    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return std::vector<std::uint8_t>();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::reset
 */
void visus::power_overwhelming::detail::visa_sensor_impl::reset(void) {
    this->printf("*RST\n");
    this->throw_on_system_error();
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::detail::visa_sensor_impl::set_attribute
 */
void visus::power_overwhelming::detail::visa_sensor_impl::set_attribute(
        ViAttr name, ViAttrState value) {
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viSetAttribute(this->scope, name, value));
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::detail::visa_sensor_impl::set_buffer
 */
void visus::power_overwhelming::detail::visa_sensor_impl::set_buffer(
        const std::uint16_t mask, const std::uint32_t size) {
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viSetBuf(this->scope, mask, size));
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::system_error
 */
int visus::power_overwhelming::detail::visa_sensor_impl::system_error(
        std::string& message) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto status = this->query(":SYST:ERR?\n");
    auto delimiter = std::find_if(status.begin(), status.end(),
        [](const ViByte b) { return b == ','; });

    if (delimiter != status.end()) {
        *delimiter = '\0';

        // Skip the delimiter itself.
        ++delimiter;

        // Trim any leading spaces and quotes.
        for (; (delimiter != status.end()) && (std::isspace(*delimiter)
                || (*delimiter == '"')); ++delimiter);

        // Trim any trailing spaces and quotes.
        auto end = status.rbegin();
        for (; (end != status.rend()) && (std::isspace(*end)
            || (*end == '"')); ++end);

        message = std::string(delimiter, end.base());

        return std::atoi(reinterpret_cast<char *>(status.data()));
    } else {
        throw std::runtime_error("The instrumed did responded unexpectedly.");
    }
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::system_error
 */
int visus::power_overwhelming::detail::visa_sensor_impl::system_error(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto status = this->query(":SYST:ERR?\n");
    auto delimiter = std::find_if(status.begin(), status.end(),
        [](const ViByte b) { return b == ','; });

    if (delimiter != status.end()) {
        *delimiter = '\0';
        return std::atoi(reinterpret_cast<char *>(status.data()));
    } else {
        throw std::runtime_error("The instrumed did responded unexpectedly.");
    }
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::throw_on_system_error
 */
void visus::power_overwhelming::detail::visa_sensor_impl::throw_on_system_error(
        void) {
    std::string message;
    auto error = this->system_error(message);

    if (error != 0) {
        if (message.empty()) {
            message = std::to_string(error);
        }

        throw std::runtime_error(message);
    }
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::write
 */
std::size_t visus::power_overwhelming::detail::visa_sensor_impl::write(
        const std::uint8_t *buffer, const std::size_t cnt) {
    if (buffer == nullptr) {
        throw std::invalid_argument("The buffer being written to the "
            "instrument must not be null.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viWrite(this->scope, buffer, static_cast<ViUInt32>(cnt), &retval));
    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}
