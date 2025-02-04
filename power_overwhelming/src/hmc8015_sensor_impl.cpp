//// <copyright file="hmc8015_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#include "hmc8015_sensor_impl.h"
//
//#include "visus/pwrowg/timestamp.h"
//
//#include "tokenise.h"
//
//
///*
// * visus::power_overwhelming::detail::hmc8015_sensor_impl::initialise
// */
//void visus::power_overwhelming::detail::hmc8015_sensor_impl::initialise(void) {
//#if defined(POWER_OVERWHELMING_WITH_VISA)
//    // Query the instrument name for use a sensor name.
//    {
//        std::vector<wchar_t> n(this->instrument.identify(nullptr, 0));
//        this->instrument.identify(n.data(), n.size());
//        this->sensor_name = n.data();
//    }
//
//    // Reset the device to default state.
//    this->instrument.reset();
//
//    // Configure the device as in the R&S instrument driver.
//    this->instrument.attribute(VI_ATTR_TMO_VALUE, 5000);
//    this->instrument.buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
//    this->instrument.attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
//    this->instrument.attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
//
//    // Lock the system to indicate that it is controlled by the software. As
//    // locking the system is not critical, do not check for system errors here.
//    this->instrument.write("SYST:REM\n");
//
//    // Clear any error that might have been caused by our setup. We do not want
//    // to abort just because the display does not look as expected.
//    this->instrument.clear_status();
//#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
//}
//
//
///*
// * visus::power_overwhelming::detail::hmc8015_sensor_impl::sample
// */
//visus::power_overwhelming::measurement_data
//visus::power_overwhelming::detail::hmc8015_sensor_impl::sample(void) const {
//    auto response = this->instrument.query("CHAN1:MEAS:DATA?\n");
//    auto timestamp = power_overwhelming::timestamp::now();
//    auto tokens = detail::tokenise(std::string(response.begin(),
//        response.end()), ',', true);
//
//    auto v = static_cast<measurement::value_type>(::atof(tokens[0].c_str()));
//    auto c = static_cast<measurement::value_type>(::atof(tokens[1].c_str()));
//    auto p = static_cast<measurement::value_type>(::atof(tokens[2].c_str()));
//
//    return measurement_data(timestamp, v, c, p);
//}
