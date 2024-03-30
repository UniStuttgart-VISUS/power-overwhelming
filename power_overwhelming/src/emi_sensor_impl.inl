// <copyright file="emi_sensor_impl.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(_WIN32)

/*
 * visus::power_overwhelming::detail::emi_sensor_impl::create
 */
template<class TPredicate>
std::size_t visus::power_overwhelming::detail::emi_sensor_impl::create(
        emi_sensor *out_sensors, std::size_t cnt_sensors,
        TPredicate predicate) {
    std::size_t retval = 0;

    if (out_sensors == nullptr) {
        cnt_sensors = 0;
    }

    detail::enumerate_device_interface(::GUID_DEVICE_ENERGY_METER,
            [out_sensors, cnt_sensors, &retval, predicate](HDEVINFO h,
            SP_DEVICE_INTERFACE_DATA& d) {
        auto path = detail::get_device_path(h, d);
        auto dev = emi_device_factory::create(path);

        switch (dev->version().EmiVersion) {
            case EMI_VERSION_V1:
                if (predicate(path, nullptr, 0)) {
                    if (retval < cnt_sensors) {
                        out_sensors[retval]._impl->set(dev, path, 0);
                    }
                    ++retval;
                }
                break;

            case EMI_VERSION_V2: {
                const auto md = dev->metadata_as<EMI_METADATA_V2>();
                const auto cnt = md->ChannelCount;
                auto c = md->Channels;

                for (auto i = 0; i < cnt; ++i) {
                    if (predicate(path, c, i)) {
                        if (retval < cnt_sensors) {
                            out_sensors[retval]._impl->set(dev, path, i);
                        }
                        ++retval;
                    }
                    c = EMI_CHANNEL_V2_NEXT_CHANNEL(c);
                }

                } break;
        }

        return true;
    });

    return retval;
}
#endif /* defined(_WIN32) */
