// <copyright file="hmc8015_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    typedef sensor_description_builder builder_type;
    assert(owner != nullptr);

    // Move all HMC sensors to the front of the descriptors.
    auto retval = move_front_if(begin, end, is_hmc8015_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Sort the range of HMC sensors by device.
    sort_by_path(begin, retval);

    // At this point, the sensors are grouped by their path and we can create one
    // for each device and a LUT that maps the configured quantity to an index in
    // the array of sensor descriptors.
    for (auto it = begin; it != retval; /* [sic] */) {
        auto pd = builder_type::private_data<private_data>(*it);
        auto instrument = pd->instrument;
        const std::wstring path = it->path();
        std::vector<hmc8015_function> functions;

        while ((it != retval) && equals(it->path(), path)) {
            pd = builder_type::private_data<private_data>(*it++);
            functions.push_back(pd->function);
#if (defined(DEBUG) || defined(_DEBUG))
            --_rem;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
        }

        //// Make sure that the local interface is locked.
        //instrument->write("SYST:REM\n");

        // Clear the memory if requested, but only now that we actually intend to
        // use the instrument.
        if (config.clear_internal_memory()) {
            instrument->clear_internal_memory();
        }

        // Notify users that a sensor is using the HMC.
        instrument->display("hmc8015_sensor is using the instrument.");

        // Prepare the device.
        instrument->reset(true, true);
        instrument->current_range(config.current_range(),
            config.current_range_value());
        instrument->voltage_range(config.voltage_range(),
            config.voltage_range_value());

        // Clamp the sampling interval according to the SCPI Programmer's
        // Manual p. 43.
        {
            using namespace std::chrono;
            auto interval = duration_cast<duration<float>>(
                owner->configuration->interval).count();
            if (interval < 0.1f) {
                interval = std::numeric_limits<float>::lowest();
            } else if (interval > 600.0f) {
                interval = (std::numeric_limits<float>::max)();
            }

            instrument->integrator_behaviour(hmc8015_integrator_mode::manual);
            instrument->log_behaviour(interval, hmc8015_log_mode::unlimited);
        }

        // Enable the requested functions.
        instrument->custom_functions(functions.data(), functions.size());

        // Create the sensor.
        const auto cnt_functions = functions.size();
        dst.emplace_back(std::move(*instrument),
            owner,
            index,
            std::move(functions));
        index += cnt_functions;
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;

#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    return begin;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}
