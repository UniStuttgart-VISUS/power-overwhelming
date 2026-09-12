// <copyright file="pwog_file.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/pwog_file.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "io_util.h"
#include "sensor_description_builder.h"


/*
 * PWROWG_NAMESPACE::pwog_file::create
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::create(
        _In_z_ const wchar_t *path,
        _In_ const bool force) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW),
        state::header);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU),
        state::header);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::create
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::create(
        _In_z_ const char *path,
        _In_ const bool force) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW),
        state::header);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU),
        state::header);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const wchar_t *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(
        detail::open(path, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING),
        state::read);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDONLY), state::read);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const char *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(
        detail::open(path, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING),
        state::read);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDONLY), state::read);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(void) noexcept
    : _data(0),
    _handle(invalid),
    _state(state::read),
    _swap(false),
    _version { 1, 0 } { }


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(_Inout_ pwog_file&& rhs) noexcept
        : _data(rhs._data),
        _handle(rhs._handle),
        _meta_data(std::move(rhs._meta_data)),
        _sensors(std::move(rhs._sensors)),
        _state(rhs._state),
        _swap(rhs._swap) {
    rhs._data = 0;
    rhs._handle = invalid;
    std::copy(std::begin(rhs._version),
        std::end(rhs._version),
        std::begin(this->_version));
}


/*
 * PWROWG_NAMESPACE::pwog_file::close
 */
void PWROWG_NAMESPACE::pwog_file::close(void) noexcept {
    if (*this) {
#if defined(_WIN32)
        ::CloseHandle(this->_handle);
#else /* defined(_WIN32) */
        ::close(this->_handle);
#endif /* defined(_WIN32) */
        this->_handle = invalid;

        this->_data = 0;
        this->_meta_data.reset();
        this->_sensors.reset();
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::meta_data
 */
std::size_t PWROWG_NAMESPACE::pwog_file::meta_data(
        _Out_writes_opt_(cnt) const char **keys,
        _In_ std::size_t cnt) const {
    auto retval = this->_meta_data.get<std::map<std::string, std::string>>();
    if (retval == nullptr) {
        return 0;
    }

    // Fix nonsensical input.
    if (keys == nullptr) {
        cnt = 0;
    }

    if (cnt >= retval->size()) {
        std::transform(retval->begin(), retval->end(), keys,
            [](const auto& item) { return item.first.c_str(); });
    }

    return retval->size();
}


/*
 * PWROWG_NAMESPACE::pwog_file::sensors
 */
std::size_t PWROWG_NAMESPACE::pwog_file::sensors(
        _Out_writes_opt_(cnt) sensor_description *sensors,
        _In_ std::size_t cnt) const {
    auto retval = this->_sensors.get<std::vector<sensor_description>>();
    if (retval == nullptr) {
        return 0;
    }

    // Fix nonsensical input.
    if (sensors == nullptr) {
        cnt = 0;
    }

    std::copy_n(retval->begin(), (std::min)(cnt, retval->size()), sensors);
    return retval->size();
}


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::write(
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ std::size_t cnt) {
    assert((sensors != nullptr) || (cnt == 0));
    // An empty key/value pair marks the end of the meta data block.
    const std::uint8_t sep[2] = { 0, 0 };

    switch (this->_state) {
        case state::meta_data:
            detail::write_all_bytes(this->_handle, sep, sizeof(sep));
            this->_state = state::sensors;
            __fallthrough;
        case state::sensors:
            break;

        default:
            throw std::logic_error("The file is not in the state to receive "
                "sensor descriptions.");
    }

    // Fix nonsensical input.
    if (sensors == nullptr) {
        cnt = 0;
    }

    for (std::size_t i = 0; i < cnt; ++i) {
        auto& sensor = sensors[i];
        this->write(sensor.id());
        this->write(sensor.path());
        this->write(sensor.name());
        this->write(sensor.label());
        this->write(sensor.vendor());
        {
            auto value = sensor.sensor_type();
            static_assert(sizeof(value) == sizeof(std::uint32_t), "The sensor "
                "type is expected to occupy 32 bits.");
            detail::write_all_bytes(this->_handle, &value, sizeof(value));
        }
        {
            auto value = sensor.reading_type();
            static_assert(sizeof(value) == sizeof(std::uint32_t), "The reading "
                "type is expected to occupy 32 bits.");
            detail::write_all_bytes(this->_handle, &value, sizeof(value));
        }
        {
            auto value = sensor.reading_unit();
            static_assert(sizeof(value) == sizeof(std::uint32_t), "The reading "
                "unit is expected to occupy 32 bits.");
            detail::write_all_bytes(this->_handle, &value, sizeof(value));
        }
        {
            auto& value = sensor.sensor_class();
            static_assert(sizeof(value) == sizeof(PWROWG_NAMESPACE::guid),
                "The sensor class is expected be a GUID.");
            detail::write_all_bytes(this->_handle, &value, sizeof(value));
        }
    }

    return *this;
}




/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::write(
        _In_reads_(cnt) const sample* samples,
        _In_ std::size_t cnt) {
    assert(samples != nullptr);
    // An empty sensor ID marks the end of the sensor description block.
    const std::uint8_t sep[1] = { 0 };

    switch (this->_state) {
        case state::sensors:
            detail::write_all_bytes(this->_handle, sep, sizeof(sep));
            this->_data = detail::tell(this->_handle);
            this->_state = state::samples;
            __fallthrough;
        case state::samples:
            break;

        default:
            throw std::logic_error("The file is not in the state to receive "
                "samples.");
    }

    // Fix nonsensical input.
    if (samples == nullptr) {
        cnt = 0;
    }

    static_assert(sizeof(sample)
        == sizeof(PWROWG_NAMESPACE::sample::reading)
        + sizeof(PWROWG_NAMESPACE::sample::source)
        + sizeof(PWROWG_NAMESPACE::sample::timestamp), "The implementation "
        "expected samples to be without padding.");
    for (std::size_t i = 0; i < cnt; ++i) {
        auto& sample = samples[i];
        detail::write_all_bytes(this->_handle, &sample, sizeof(sample));
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator =
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::operator =(
        _Inout_ pwog_file&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->close();
        assert(!*this);
        assert(this->_data == 0);
        std::swap(this->_data, rhs._data);
        std::swap(this->_handle, rhs._handle);
        assert(!rhs);
        this->_meta_data = std::move(rhs._meta_data);
        assert(!rhs._meta_data);
        this->_sensors = std::move(rhs._sensors);
        assert(!rhs._sensors);
        this->_state = rhs._state;
        this->_swap = rhs._swap;
        std::copy(std::begin(rhs._version),
            std::end(rhs._version),
            std::begin(this->_version));
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator []
 */
_Ret_maybenull_z_ const char *PWROWG_NAMESPACE::pwog_file::operator [](
        _In_ const char *key) const noexcept {
    if (key == nullptr) {
        return nullptr;
    }

    auto map = this->_meta_data.get<std::map<std::string, std::string>>();
    if (map == nullptr) {
        return nullptr;
    }

    auto it = map->find(key);
    if (it == map->end()) {
        return nullptr;
    }

    return it->second.c_str();
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator []
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::sensor_description *
PWROWG_NAMESPACE::pwog_file::operator [](_In_ const int index) const noexcept {
    if (index < 0) {
        return nullptr;
    }

    auto sensors = this->_sensors.get<std::vector<sensor_description>>();
    if (sensors == nullptr) {
        return nullptr;
    }

    if (index >= sensors->size()) {
        return nullptr;
    }

    return sensors->data() + index;
}


/*
 * PWROWG_NAMESPACE::pwog_file::check_fourcc
 */
void PWROWG_NAMESPACE::pwog_file::check_fourcc(void) {
    std::decay_t<decltype(fourcc)> actual = 0;
    detail::read_bytes(this->_handle, &actual, sizeof(actual));

    if (actual != fourcc) {
        // If we did not find the expected FOURCC, it could be that the byte
        // order is reversed. We check that next and, in case of success, we
        // remember that we need to swap the byte order when reading.
        auto b = reinterpret_cast<std::uint8_t *>(&actual);
        auto e = b + sizeof(actual);
        std::reverse(b, e);

        if (actual != fourcc) {
            throw std::invalid_argument("The specified file does not start "
                "with the expected FOURCC.");
        }

        this->_swap = true;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::check_version
 */
void PWROWG_NAMESPACE::pwog_file::check_version(void) {
    detail::read_bytes(this->_handle, this->_version, sizeof(this->_version));
    if ((this->_version[0] != 1) || (this->_version[1] != 0)) {
        throw std::invalid_argument("The specified file has a version that the "
            "reader does not understand.");
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::initialise
 */
void PWROWG_NAMESPACE::pwog_file::initialise(
        _In_ const handle_type handle,
        _In_ const state state) {
    assert(handle != invalid);
    assert((state == state::read) || (state == state::header));
    assert(this->_handle == invalid);
    this->_handle = handle;

    switch (this->_state = state) {
        case state::read:
            this->check_fourcc();
            this->check_version();
            this->read_meta_data();
            this->read_sensors();
            break;

        case state::header:
            // We can always write our native format.
            assert(!this->_swap);
            detail::write_all_bytes(this->_handle, &fourcc, sizeof(fourcc));
            // Adjust this as the version changes.
            assert(this->_version[0] == 1);
            assert(this->_version[1] == 0);
            detail::write_all_bytes(this->_handle, this->_version,
                sizeof(this->_version));
            // Meta data are next.
            this->_state = state::meta_data;
            break;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::read_meta_data
 */
void PWROWG_NAMESPACE::pwog_file::read_meta_data(void) {
    assert(this->_handle != invalid);
    assert(this->_state == state::read);
    auto& map = this->_meta_data.emplace<std::map<std::string, std::string>>();

    // TODO: this could be improved by not reallocating the buffer to the
    // total size of the meta data block, but this part is not perf-critical.
    std::vector<char> buffer(256);
    std::size_t key = 0;
    auto is_key = true;
    std::size_t offset = 0;
    const auto start = detail::tell(this->_handle);
    std::size_t value = 0;

    while (true) {
        const auto read = detail::try_read(this->_handle, buffer, offset);
        if (read == 0) {
            throw std::runtime_error("Unexpected end of file while reading "
                "meta data.");
        }

        for (std::size_t end = offset + read; offset < end; ++offset) {
            if (buffer[offset] == 0) {
                if (is_key) {
                    if (offset - key == 0) {
                        // An empty key marks the end of the meta data block.
                        // Before returning, make sure that we reset the file
                        // pointer to the first byte after the meta data block.
                        detail::seek(this->_handle,
                            start + offset + 2,
                            detail::native_seek_origin::begin);
                        return;
                    }

                    // The value starts at the next character.
                    value = offset + 1;
                } else {
                    // The next key starts at the next character.
                    map.emplace(buffer.data() + key, buffer.data() + value);
                    key = offset + 1;
                }

                // Whenever we encounter the end of a string, switch between key
                // and value.
                is_key = !is_key;
            } /* if (buffer[i] == 0) */
        } /* for (std::size_t i = offset; i < offset + read; ++i) */

        buffer.resize(buffer.size() * 2);
    } /* while (true) */
}


/*
 * PWROWG_NAMESPACE::pwog_file::read_sensors
 */
void PWROWG_NAMESPACE::pwog_file::read_sensors(void) {
    assert(this->_handle != invalid);
    assert(this->_state == state::read);
    std::size_t begin = 0;
    std::vector<char> buffer(512);
    std::size_t end = 0;
    assert(!this->_sensors);
    auto& sensors = this->_sensors.emplace<std::vector<sensor_description>>();
    auto seek_to = detail::tell(this->_handle);

    // Tries parsing a sensor starting at 'begin'. Returns whether a sensor was
    // written to 'sensors'. Once the lambda returns, 'begin' is set to the
    // start of the next sensor description.
    const auto parse_sensor = [this, &buffer, &begin, &end, &sensors](void) {
        // Searches for the end of the next null-terminated string in 'buffer'
        // starting at 'b' but before 'end'. If case of success, returns 'b' and
        // the position past the null terminator.
        const auto scan_string = [&buffer, &end](const std::size_t b) {
            std::size_t e = b;
            while ((e < end) && (buffer[e] != 0)) {
                ++e;
            }
            return (e < end)
                ? std::make_pair(b, e + 1)
                : std::make_pair(std::string::npos, std::string::npos);
        };

        const auto id = scan_string(begin);
        if (id.first == std::string::npos) {
            return false;
        }

        if (buffer[id.first] == 0) {
            // There are no more sensors.
            return false;
        }

        const auto path = scan_string(id.second);
        if (path.first == std::string::npos) {
            return false;
        }

        const auto name = scan_string(path.second);
        if (name.first == std::string::npos) {
            return false;
        }

        const auto label = scan_string(name.second);
        if (label.first == std::string::npos) {
            return false;
        }

        const auto vendor = scan_string(label.second);
        if (vendor.first == std::string::npos) {
            return false;
        }

        // After the variably sized strings, there is only fixed-size data left,
        // so we can directly check whether we have enough data in the buffer to
        // build the sensor description.
        const auto sensor = vendor.second;
        const auto reading = sensor + sizeof(sensor_type);
        const auto unit = reading + sizeof(reading_type);
        const auto clazz = unit + sizeof(reading_unit);
        const auto next = clazz + sizeof(guid);
        if (next > end) {
            return false;
        }

        // At this point, we have all data to build a description.
        const auto l = convert_string<wchar_t>(buffer.data() + label.first);
        const auto v = convert_string<wchar_t>(buffer.data() + vendor.first);
        auto s = *reinterpret_cast<sensor_type *>(buffer.data() + sensor);
        this->swap(s);
        auto r = *reinterpret_cast<reading_type *>(buffer.data() + reading);
        this->swap(r);
        auto u = *reinterpret_cast<reading_unit *>(buffer.data() + unit);
        this->swap(u);
        const guid c(reinterpret_cast<std::uint8_t *>(buffer.data()) + clazz);
        sensors.emplace_back(detail::sensor_description_builder()
            .with_id(buffer.data() + id.first)
            .with_path(buffer.data() + path.first)
            .with_name(buffer.data() + name.first)
            .with_label(l.c_str())
            .with_vendor(v.c_str())
            .with_type(s)
            .produces(r)
            .measured_in(u)
            .with_class(c)
            .build());

        begin = next;
        return true;
    };

    while (true) {
        const auto read = detail::try_read(this->_handle, buffer, end);
        if (read == 0) {
            throw std::runtime_error("Unexpected end of file while reading "
                "the sensor descriptions.");
        }
        end += read;

        auto any = false;
        while (parse_sensor()) {
            any = true;
        }

        if (!any) {
            // We could not parse any sensor description, so we need to read more
            // data from the file.
            buffer.resize(buffer.size() * 2);
            continue;
        }

        seek_to += begin;

        if (buffer[begin] == 0) {
            // An empty sensor ID marks the end of the sensor description block.
            // Before returning, reset the file pointer to the first data entry.
            detail::seek(this->_handle,
                seek_to,
                detail::native_seek_origin::begin);
            return;
        }

        std::vector<char> next(buffer.size());
        assert(begin <= end);
        std::copy(buffer.data() + begin, buffer.data() + end, next.data());
        buffer.swap(next);
        end -= begin;
        begin = 0;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::swap
 */
void PWROWG_NAMESPACE::pwog_file::swap(
        _Inout_ timestamp& value) const noexcept {
    auto t = value.value();
    this->swap(t);
    value = timestamp(t);
}


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
void PWROWG_NAMESPACE::pwog_file::write(_In_opt_z_ const char *string) {
    if (string != nullptr) {
        const auto len = std::strlen(string) + 1;
        detail::write_all_bytes(this->_handle, string, len);
    } else {
        const char n = 0;
        detail::write_all_bytes(this->_handle, &n, sizeof(n));
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
void PWROWG_NAMESPACE::pwog_file::write(_In_z_ const wchar_t *string) {
    const auto s = convert_string<char>(string);
    this->write(s.c_str());
}
