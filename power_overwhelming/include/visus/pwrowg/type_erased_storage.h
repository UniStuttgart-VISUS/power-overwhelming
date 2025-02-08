// <copyright file="type_erased_storage.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_ERASED_STORAGE_H)
#define _PWROWG_TYPE_ERASED_STORAGE_H
#pragma once

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A container for potentially any runtime type.
/// </summary>
/// <remarks>
/// <para>This type allows for sensors to store any data in the
/// <see cref="sensor_description" />.</para>
/// <para>The type-erased storage does not support move, because we would need to
/// generate an exception for non-movable types, which violates the contract of
/// a move operation.</para>
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

    type_erased_storage(type_erased_storage&& rhs) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    /// <remarks>
    /// This will destruct the data stored within the object provided a valid
    /// destructor has been registered.
    /// </remarks>
    ~type_erased_storage(void) noexcept;

    template<class TType, class... TArgs> TType *emplace(TArgs&&... args);

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
        return this->_data.as<TType>();
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
        return this->_data.as<TType>();
    }

    /// <summary>
    /// Copy assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    type_erased_storage& operator =(_In_ const type_erased_storage& rhs);

    type_erased_storage& operator =(type_erased_storage&& rhs) = delete;

private:

    /// <summary>
    /// The type of a copy operation, either copy construct or assignment.
    /// </summary>
    typedef void (*copy_type)(_In_ blob& dst, _In_ const blob& src);

    /// <summary>
    /// The type of a destructor function.
    /// </summary>
    typedef void (*destruct_type)(_In_ blob& obj);

    /// <summary>
    /// Invokes <see cref="_dtor" /> on <see cref="_data" /> if possible. It is
    /// safe to call this method if no destructor has been registered. The method
    /// will erase all operations once the contained object was destroyed to
    /// prevent them being invoked on invalid data.
    /// </summary>
    void clear(void) noexcept;

    /// <summary>
    /// Registers the assignment operator of <typeparamref name="TType" /> as
    /// <see cref="_cp" />.
    /// </summary>
    template<class TType> void reg_cp(void) noexcept;

    /// <summary>
    /// Registers the copy constructor of <typeparamref name="TType" /> as
    /// <see cref="_cp_ctor" />.
    /// </summary>
    template<class TType> void reg_cp_ctor(void) noexcept;

    /// <summary>
    /// Registers the destructor of <typeparamref name="TType" /> as
    /// <see cref="_dtor" />.
    /// </summary>
    template<class TType> void reg_dtor(void) noexcept;

    copy_type _cp;
    copy_type _cp_ctor;
    blob _data;
    destruct_type _dtor;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/type_erased_storage.inl"

#endif /* !defined(_PWROWG_TYPE_ERASED_STORAGE_H) */
