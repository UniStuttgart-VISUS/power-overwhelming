// <copyright file="time_synchroniser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/time_synchroniser.h"

#include "time_synchroniser_impl.h"


/*
 * visus::power_overwhelming::time_synchroniser::create
 */
visus::power_overwhelming::time_synchroniser
visus::power_overwhelming::time_synchroniser::create(const int address_family,
        const std::uint16_t port) {
    time_synchroniser retval;

#if defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER)
    // TODO: set other options.
    retval._impl = new detail::time_synchroniser_impl();
    retval._impl->start(address_family, port);

#else /* defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER) */
    throw std::logic_error("The library was compiled without support for "
        "Cristian's algorithm.");
#endif /* defined(POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER) */

    return retval;
}


/*
 * visus::power_overwhelming::time_synchroniser::~time_synchroniser
 */
visus::power_overwhelming::time_synchroniser::~time_synchroniser(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::time_synchroniser::operator =
 */
visus::power_overwhelming::time_synchroniser&
visus::power_overwhelming::time_synchroniser::operator =(
        time_synchroniser&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::time_synchroniser::operator bool
 */
visus::power_overwhelming::time_synchroniser::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}
