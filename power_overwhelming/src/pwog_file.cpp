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
