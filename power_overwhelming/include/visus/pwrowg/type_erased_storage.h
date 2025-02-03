// <copyright file="type_erased_storage.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_ERASED_STORAGE_H)
#define _PWROWG_TYPE_ERASED_STORAGE_H
#pragma once

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// 
/// </summary>
class POWER_OVERWHELMING_API type_erased_storage final {


public:

    /// <summary>
    /// The type of a copy operation, either copy construct or assignment.
    /// </summary>
    typedef void (*copy_type)(_In_ void *dst, _In_ const void *src);

    /// <summary>
    /// The type of a destructor function.
    /// </summary>
    typedef void (*destruct_type)(_In_ void *obj);

    /// <summary>
    /// The type of a move operation, either move construct or move assignment.
    /// </summary>
    typedef void (*move_type)(_In_ void *dst, _In_ const void *src);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    type_erased_storage(void) noexcept;

    /// <summary>
    /// Initialises a new instance by creating a copy of
    /// <paramref name="data" />.
    /// </summary>
    /// <typeparam name="TType">The type of the data stored in the new instance.
    /// </typeparam>
    /// <param name="data">The data to be copied to the instance.</param>
    template<class TType>
    explicit type_erased_storage(_In_ const TType& data);

    type_erased_storage(_In_ const type_erased_storage& rhs);

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

    type_erased_storage& operator =(_In_ const type_erased_storage& rhs);

    type_erased_storage& operator =(_Inout_ type_erased_storage&& rhs) noexcept;

private:

    /// <summary>
    /// Invokes <see cref="_dtor" /> on <see cref="_data" /> if possible.
    /// </summary>
    void clear(void) noexcept;

    /// <summary>
    /// Registers the assignment operator of <typeparamref name="TType" /> as
    /// <see cref="_cp" />.
    /// </summary>
    template<class TType>
    std::enable_if_t<std::is_copy_assignable_v<TType>> reg_cp(void) noexcept;

    /// <summary>
    /// Clears <see cref="_cp" />.
    /// </summary>
    template<class TType>
    std::enable_if_t<!std::is_copy_assignable_v<TType>> reg_cp(void) noexcept;

    /// <summary>
    /// Registers the copy constructor of <typeparamref name="TType" /> as
    /// <see cref="_cp_ctor" />.
    /// </summary>
    template<class TType> std::enable_if_t<std::is_copy_constructible_v<TType>>
    reg_cp_ctor(void) noexcept;

    /// <summary>
    /// Clears <see cref="_cp_ctor" />.
    /// </summary>
    template<class TType> std::enable_if_t<!std::is_copy_constructible_v<TType>>
    reg_cp_ctor(void) noexcept;

    /// <summary>
    /// Registers the destructor of <typeparamref name="TType" /> as
    /// <see cref="_dtor" />.
    /// </summary>
    template<class TType> void reg_dtor(void) noexcept;

    /// <summary>
    /// Registers the move assignment operator of <typeparamref name="TType" />
    /// as <see cref="_mv" />.
    /// </summary>
    template<class TType>
    std::enable_if_t<std::is_move_assignable_v<TType>> reg_mv(void) noexcept;

    /// <summary>
    /// Clears <see cref="_mv" />.
    /// </summary>
    template<class TType>
    std::enable_if_t<!std::is_move_assignable_v<TType>> reg_mv(void) noexcept;

    /// <summary>
    /// Registers the move constructor operator of <typeparamref name="TType" />
    /// as <see cref="_mv_ctor" />.
    /// </summary>
    template<class TType> std::enable_if_t<std::is_move_constructible_v<TType>>
    reg_mv_ctor(void) noexcept;

    /// <summary>
    /// Clears <see cref="_mv_cp" />.
    /// </summary>
    template<class TType> std::enable_if_t<!std::is_move_constructible_v<TType>>
    reg_mv_ctor(void) noexcept;

    copy_type _cp;
    copy_type _cp_ctor;
    blob _data;
    destruct_type _dtor;
    move_type _mv;
    move_type _mv_ctor;

};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/type_erased_storage.inl"

#endif /* !defined(_PWROWG_TYPE_ERASED_STORAGE_H) */
