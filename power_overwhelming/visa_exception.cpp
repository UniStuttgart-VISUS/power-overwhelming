// <copyright file="visa_exception.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "visa_exception.h"


/*
 * visus::power_overwhelming::visa_exception::visa_exception
 */
visus::power_overwhelming::visa_exception::visa_exception(const value_type code)
        : std::exception(std::to_string(code).c_str()), _code(code) { }
// TODO: Is there any way to obtain a meaningful error string from VISA?
