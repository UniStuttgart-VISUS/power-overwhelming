// <copyright file="visa_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

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


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::detail::visa_sensor_impl::query
 */
std::vector<ViByte>
visus::power_overwhelming::detail::visa_sensor_impl::query(ViConstBuf query,
        ViUInt32 cnt, ViUInt32 buffer_size) {
    this->write(query, cnt);
    std::vector<ViByte> retval(buffer_size);
    retval.resize(this->read(retval.data(), buffer_size));
    return retval;
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::query
 */
std::vector<ViByte> visus::power_overwhelming::detail::visa_sensor_impl::query(
        const std::string& query, ViUInt32 buffer_size) {
    this->printf(query.c_str());
    std::vector<ViByte> retval(buffer_size);
    retval.resize(this->read(retval.data(), buffer_size));
    return retval;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::detail::visa_sensor_impl::read
 */
ViUInt32 visus::power_overwhelming::detail::visa_sensor_impl::read(
        ViPBuf buffer, ViUInt32 cnt) {
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viRead(this->scope, buffer, cnt, &retval));
    return retval;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


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
        ViUInt16 mask, ViUInt32 size) {
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


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * visus::power_overwhelming::detail::visa_sensor_impl::write
 */
ViUInt32 visus::power_overwhelming::detail::visa_sensor_impl::write(
        ViConstBuf buffer, ViUInt32 cnt) {
    ViUInt32 retval = 0;
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viWrite(this->scope, buffer, cnt, &retval));
    return retval;
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
