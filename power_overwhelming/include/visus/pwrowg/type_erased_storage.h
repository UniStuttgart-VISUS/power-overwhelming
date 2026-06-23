// <copyright file="type_erased_storage.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_ERASED_STORAGE_H)
#define _PWROWG_TYPE_ERASED_STORAGE_H
#pragma once

#include <cassert>
#include <cinttypes>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <utility>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A container for potentially any runtime type.
/// </summary>
/// <remarks>
/// <para>This type allows for sensors to store any data in the
/// <see cref="sensor_description" />.</para>
/// </remarks>
class POWER_OVERWHELMING_API type_erased_storage final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    type_erased_storage(void) noexcept;

    /// <summary>
    /// Initialise a copy of <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    type_erased_storage(_In_ const type_erased_storage& rhs);

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    type_erased_storage(_Inout_ type_erased_storage&& rhs) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    /// <remarks>
    /// This will destruct the data stored within the object provided a valid
    /// destructor has been registered.
    /// </remarks>
    ~type_erased_storage(void) noexcept;

    /// <summary>
    /// Emplaces an object of type <typeparamref name="TType" />.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call the method on a valid object, in which case
    /// this object will be destroyed before emplacing a new one.</para>
    /// </remarks>
    /// <typeparam name="TType">The type of the new object.</typeparam>
    /// <typeparam name="TArgs">The type of the arguments passed to the
    /// constructor.</typeparam>
    /// <param name="args">The arguments passed to the constuctor.</param>
    /// <returns>A reference for the newly created object.</returns>
    template<class TType, class... TArgs>
    TType& emplace(TArgs&&... args);

    /// <summary>
    /// Gets the data in form of a pointer to <typeparamref name="TType" />.
    /// </summary>
    /// <remarks>
    /// No type checks will be performed on behalf of the caller. The caller must
    /// know the correct type of the data.
    /// </remarks>
    /// <typeparam name="TType">The type contained in the object.</typeparam>
    /// <returns>A pointer to the data.</returns>
    template<class TType> inline _Ret_maybenull_ TType *get(void) noexcept {
        switch (this->_state) {
            case state::small_value:
                return reinterpret_cast<TType *>(this->_data.small_value);
            case state::large_value:
                assert(this->_data.value != nullptr);
                return static_cast<TType *>(this->_data.value);
            default:
                return nullptr;
        }
    }

    /// <summary>
    /// Gets the data in form of a pointer to <typeparamref name="TType" />.
    /// </summary>
    /// <remarks>
    /// No type checks will be performed on behalf of the caller. The caller must
    /// know the correct type of the data.
    /// </remarks>
    /// <typeparam name="TType">The type contained in the object.</typeparam>
    /// <returns>A pointer to the data.</returns>
    template<class TType>
    inline _Ret_maybenull_ const TType *get(void) const noexcept {
        switch (this->_state) {
            case state::small_value:
                return reinterpret_cast<const TType *>(this->_data.small_value);
            case state::large_value:
                assert(this->_data.value != nullptr);
                return static_cast<const TType *>(this->_data.value);
            default:
                return nullptr;
        }
    }

    /// <summary>
    /// Destructs the contained object if any.
    /// </summary>
    /// <remarks>
    /// It is safe to call this method if no destructor has been registered or
    /// if the object has been already reset. The method will erase all
    /// operations once the contained object was destroyed to prevent them being
    /// invoked on invalid data.
    /// </remarks>
    void reset(void) noexcept;

    /// <summary>
    /// Copy assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    type_erased_storage& operator =(_In_ const type_erased_storage& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    type_erased_storage& operator =(_Inout_ type_erased_storage&& rhs) noexcept;

    /// <summary>
    /// Answer whether the storage holds any data.
    /// </summary>
    /// <returns><c>true</c> if there are data in the object, <c>false</c> if it
    /// is empty.</returns>
    inline operator bool(void) const noexcept {
        return (this->_state != state::empty);
    }

private:

    /// <summary>
    /// A union used for small value optimisation.
    /// </summary>
    union data {
        std::uint8_t small_value[2 * sizeof(void *)];
        void *value;
    };

    /// <summary>
    /// Possible states of the object.
    /// </summary>
    enum class state {
        empty,
        small_value,
        large_value
    };

    /// <summary>
    /// The type of a copy operation, either copy construct or assignment.
    /// </summary>
    typedef void (*copy_type)(_Out_ data& dst, _In_ const data& src);

    /// <summary>
    /// The type of a destructor function.
    /// </summary>
    typedef void (*destruct_type)(_In_ data& obj);

    /// <summary>
    /// Answer whether <typeparamref name="TType" /> is small enough to be
    /// stored in-place in the data union.
    /// </summary>
    template<class TType>
    static constexpr auto is_small_v = (sizeof(TType) <= sizeof(data));

    /// <summary>
    /// Creates the copy callback for a non-copyable type.
    /// </summary>
    template<class TType>
    static std::enable_if_t<!std::is_copy_constructible_v<TType>, copy_type>
    make_copy(void) noexcept;

    /// <summary>
    /// Creates the copy callback for a small type.
    /// </summary>
    template<class TType>
    static std::enable_if_t<std::is_copy_constructible_v<TType>
        && is_small_v<TType>, copy_type>
    make_copy(void) noexcept;

    /// <summary>
    /// Creates the copy callback for a large type.
    /// </summary>
    template<class TType>
    static std::enable_if_t<std::is_copy_constructible_v<TType>
        && !is_small_v<TType>, copy_type>
    make_copy(void) noexcept;

    /// <summary>
    /// Creates a destructor callback for a small type.
    /// </summary>
    template<class TType>
    static std::enable_if_t<is_small_v<TType>, destruct_type> make_dtor(
        void) noexcept;

    /// <summary>
    /// Creates a destructor callback for a heap-allocated type.
    /// </summary>
    template<class TType>
    static std::enable_if_t<!is_small_v<TType>, destruct_type> make_dtor(
        void) noexcept;

    copy_type _cp;
    data _data;
    destruct_type _dtor;
    state _state;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/type_erased_storage.inl"

#endif /* !defined(_PWROWG_TYPE_ERASED_STORAGE_H) */
