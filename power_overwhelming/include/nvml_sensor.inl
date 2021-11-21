// <copyright file="nvml_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::for_all
 */
template<class TMeasurement>
std::vector<visus::power_overwhelming::nvml_sensor<TMeasurement>>
visus::power_overwhelming::nvml_sensor<TMeasurement>::for_all(void) {
    unsigned int cnt = 0;
    nvml_scope scope;

    {
        auto status = ::nvmlDeviceGetCount(&cnt);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    std::vector<nvml_sensor> retval;
    retval.resize(cnt);

    for (unsigned int i = 0; i < cnt; ++i) {
        auto status = ::nvmlDeviceGetHandleByIndex(i, &retval[i]._device);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::from_bus_id
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::from_bus_id(
        const char *pciBusId) {
    nvml_sensor retval;

    auto status = ::nvmlDeviceGetHandleByPciBusId(pciBusId, &retval._device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::from_guid
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::from_guid(
        const char *guid) {
    nvml_sensor retval;

    auto status = ::nvmlDeviceGetHandleByUUID(guid, &retval._device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::from_index
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::from_index(
        const unsigned int index) {
    nvml_sensor retval;

    auto status = ::nvmlDeviceGetHandleByIndex(index, &retval._device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::from_serial
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::from_serial(
        const char *serial) {
    nvml_sensor retval;

    auto status = ::nvmlDeviceGetHandleBySerial(serial, &retval._device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return retval;
}

/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::nvml_sensor
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::nvml_sensor(void) noexcept
    : _device(nullptr) { }


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::nvml_sensor
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::nvml_sensor(
        nvml_sensor&& rhs) noexcept
        : __scope(std::move(rhs.__scope)), _device(rhs._device) {
    rhs._device = nullptr;
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::~nvml_sensor
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>::~nvml_sensor(void) { }


/*
 * ::power_overwhelming::nvml_sensor<TMeasurement>::sample
 */
template<class TMeasurement>
typename visus::power_overwhelming::nvml_sensor<TMeasurement>::measurement_type
visus::power_overwhelming::nvml_sensor<TMeasurement>::sample(void) const {
    unsigned int mw = 0;
    auto t = timestamp<timestamp_type>::create();

    // Get the power usage in milliwatts.
    auto status = ::nvmlDeviceGetPowerUsage(this->_device, &mw);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return measurement_type(t, static_cast<value_type>(mw)
        / static_cast<value_type>(1000));
}


/*
 * visus::power_overwhelming::nvml_sensor<TMeasurement>::operator =
 */
template<class TMeasurement>
visus::power_overwhelming::nvml_sensor<TMeasurement>&
visus::power_overwhelming::nvml_sensor<TMeasurement>::operator =(
        nvml_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->__scope = rhs.__scope;
        this->_device = rhs._device;
    }

    return *this;
}
