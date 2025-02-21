// <copyright file="blob.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_BLOB_H)
#define _PWROWG_BLOB_H
#pragma once

#include <algorithm>
#include <cinttypes>
#include <cstddef>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A block of binary data.
/// </summary>
class POWER_OVERWHELMING_API blob final {

public:

    /// <summary>
    /// The type used to represent a single byte.
    /// </summary>
    typedef std::uint8_t byte_type;

    /// <summary>
        /// Initialises a new and empty instance.
        /// </summary>
    inline blob(void) noexcept : _data(nullptr), _size(0) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="size">The size of the blob in bytes.</param>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    explicit inline blob(_In_ const std::size_t size)
        : _data(new byte_type[size]), _size(size) { }

    /// <summary>
    /// Initialises a new blob from existing data.
    /// </summary>
    /// <typeparam name="TElement">The type of the elements that will be
    /// used for initialising the blob.</typeparam>
    /// <param name="data">The initialiser determining initial size and
    /// content of the blob.</param>
    template<class TElement>
    blob(_In_ const std::initializer_list<TElement>& data);

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    blob(_In_ const blob& rhs);

    /// <summary>
    /// Move construction.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    blob(_Inout_ blob&& rhs) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~blob(void);

    /// <summary>
    /// Answer a typed pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <typeparam name="TPointer">The type of the pointer requested.
    /// </typeparam>
    /// <returns>A pointer to the data.</returns>
    template<class TPointer>
    inline _Ret_maybenull_ TPointer *as(void) noexcept {
        return static_cast<TPointer *>(this->data());
    }

    /// <summary>
    /// Answer a typed pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <typeparam name="TPointer">The type of the pointer requested.
    /// </typeparam>
    /// <returns>A pointer to the data.</returns>
    template<class TPointer>
    inline _Ret_maybenull_ const TPointer *as(void) const noexcept {
        return static_cast<const TPointer *>(this->data());
    }

    /// <summary>
    /// Answer a typed pointer to the specified location in the  data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>The returned pointer can be <c>nullptr</c> in two cases:
    /// first, if the blob is empty, ie the data pointer itself is
    /// <c>nullptr</c>, and second if the offset reaches beyond the end
    /// of the allocated range.</para>
    /// </remarks>
    /// <typeparam name="TPointer">The type of the pointer requested.
    /// </typeparam>
    /// <param name="offset">The offset into the data, in bytes.</param>
    /// <returns>The pointer to the data at the given offset.</returns>
    template<class TPointer>
    inline _Ret_maybenull_ TPointer *as(
            _In_ const std::size_t offset) noexcept {
        return static_cast<TPointer *>(this->at(offset));
    }

    /// <summary>
    /// Answer a typed pointer to the specified location in the  data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>The returned pointer can be <c>nullptr</c> in two cases:
    /// first, if the blob is empty, ie the data pointer itself is
    /// <c>nullptr</c>, and second if the offset reaches beyond the end
    /// of the allocated range.</para>
    /// </remarks>
    /// <typeparam name="TPointer">The type of the pointer requested.
    /// </typeparam>
    /// <param name="offset">The offset into the data, in bytes.</param>
    /// <returns>The pointer to the data at the given offset.</returns>
    template<class TPointer>
    inline _Ret_maybenull_ const TPointer *as(
            _In_ const std::size_t offset) const noexcept {
        return static_cast<const TPointer *>(this->at(offset));
    }

    /// <summary>
    /// Answer the pointer to the given offset into the data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>The returned pointer can be <c>nullptr</c> in two cases:
    /// first, if the blob is empty, ie the data pointer itself is
    /// <c>nullptr</c>, and second if the offset reaches beyond the end
    /// of the allocated range.</para>
    /// </remarks>
    /// <param name="offset">The offset into the data, in bytes.</param>
    /// <returns>The pointer to the data at the given offset.</returns>
    _Ret_maybenull_ void *at(_In_ const std::size_t offset) noexcept;

    /// <summary>
    /// Answer the pointer to the given offset into the data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>The returned pointer can be <c>nullptr</c> in two cases:
    /// first, if the blob is empty, ie the data pointer itself is
    /// <c>nullptr</c>, and second if the offset reaches beyond the end
    /// of the allocated range.</para>
    /// </remarks>
    /// <param name="offset">The offset into the data, in bytes.</param>
    /// <returns>The pointer to the data at the given offset.</returns>
    _Ret_maybenull_ const void *at(
        _In_ const std::size_t offset) const noexcept;

    /// <summary>
    /// Answer the pointer to the begin of the blob.
    /// </summary>
    /// <returns>A pointer ot he begin of the blob.</returns>
    inline _Ret_maybenull_ byte_type *begin(void) noexcept {
        return this->_data;
    }

    /// <summary>
    /// Answer the pointer to the begin of the blob.
    /// </summary>
    /// <returns>A pointer ot he begin of the blob.</returns>
    inline _Ret_maybenull_ const byte_type *begin(void) const noexcept {
        return this->as<byte_type>();
    }

    /// <summary>
    /// Deallocate all data.
    /// </summary>
    void clear(void);

    /// <summary>
    /// Answer a pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <returns>A pointer to the data.</returns>
    inline _Ret_maybenull_ void *data(void) noexcept {
        return static_cast<void *>(this->_data);
    }

    /// <summary>
    /// Answer a pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <returns>A pointer to the data.</returns>
    inline _Ret_maybenull_ const void *data(void) const noexcept {
        return static_cast<const void *>(this->_data);
    }

    /// <summary>
    /// Answer whether the blob is empty.
    /// </summary>
    /// <returns><c>true</c> if the blob contains no data, <c>false</c>
    /// otherwise.</returns>
    inline bool empty(void) const noexcept {
        return ((this->_data == nullptr) || (this->_size < 1));
    }

    /// <summary>
    /// Answer the pointer to the position <i>after</i> the last byte in the
    /// blob.
    /// </summary>
    /// <returns>A pointer to the end of the blob.</returns>
    _Ret_maybenull_ byte_type *end(void) noexcept;

    /// <summary>
    /// Answer the pointer to the position <i>after</i> the last byte in the
    /// blob.
    /// </summary>
    /// <returns>A pointer to the end of the blob.</returns>
    _Ret_maybenull_ const byte_type *end(void) const noexcept;

    /// <summary>
    /// Make sure that the blob can hold at least <paramref name="size" />
    /// bytes and copy any existing content if the buffer needs to be
    /// reallocated.
    /// </summary>
    /// <remarks>
    /// <para>This method behaves like <see cref="blob::reserve" />, but
    /// preserves any existing content of the blob.</para>
    /// </remarks>
    /// <param name="size">The required minimum size of the blob, in bytes.
    /// </param>
    /// <returns><c>true</c> if the blob was reallocated, <c>false</c> if
    /// the previous capacity was sufficient.</returns>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    bool grow(_In_ const std::size_t size);

    /// <summary>
    /// Answer the pointer to last valid position in the blob.
    /// </summary>
    /// <returns>A pointer to the last position in the blob.</returns>
    _Ret_maybenull_ byte_type *rbegin(void) noexcept;

    /// <summary>
    /// Answer the pointer to last valid position in the blob.
    /// </summary>
    /// <returns>A pointer to the last position in the blob.</returns>
    _Ret_maybenull_ const byte_type *rbegin(void) const noexcept;

    /// <summary>
    /// Answer the pointer to the position <i>before</i> the first byte in
    /// the blob.
    /// </summary>
    /// <returns>A pointer to the position before the start of the blob.
    /// This pointer must not be dereferenced.</returns>
    _Ret_maybenull_ byte_type *rend(void) noexcept;

    /// <summary>
    /// Answer the pointer to the position <i>before</i> the first byte in
    /// the blob.
    /// </summary>
    /// <returns>A pointer to the position before the start of the blob.
    /// This pointer must not be dereferenced.</returns>
    _Ret_maybenull_ const byte_type *rend(void) const noexcept;

    /// <summary>
    /// Make sure that the blob can hold at least <paramref name="size" />
    /// bytes.
    /// </summary>
    /// <remarks>
    /// <para>Reserving data may invalidate existing data if the requested
    /// minimum size is larger than the current size. Existing data will
    /// not be copied to the new memory block in this case. The method will
    /// incicate this by returning <c>true</c>. If the method returns
    /// <c>false</c>, the existing allocation and its content remain
    /// untouched.</para>
    /// <para>You can use <see cref="blob::grow" /> if existing content of
    /// the blob needs to be preserved while increasing its capacity.</para>
    /// </remarks>
    /// <param name="size">The required minimum size of the blob, in bytes.
    /// </param>
    /// <returns><c>true</c> if the blob was reallocated, <c>false</c> if
    /// the previous capacity was sufficient.</returns>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    bool reserve(_In_ const std::size_t size);

    /// <summary>
    /// Make sure that the blob has exactly the the specified
    /// <paramref name="size" /> in bytes.
    /// </summary>
    /// <remarks>
    /// <para>If the buffer does not already have the requested size, any
    /// existing data will be lost.</para>
    /// <para>You can achieve the same effect by calling
    /// <see cref="blob::truncate" />, but preserve any exisiting content
    /// during the operation.</para>
    /// </remarks>
    /// <param name="size">The requested size in bytes.</param>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    void resize(_In_ const std::size_t size);

    /// <summary>
    /// Answer the overall size of the blob in bytes.
    /// </summary>
    /// <returns>The size of the packet in bytes.</returns>
    inline std::size_t size(void) const noexcept {
        return this->_size;
    }

    /// <summary>
    /// Make sure that the blob has exactly the specified
    /// <paramref name="size" /> in bytes, but keep any existing data up to
    /// this point.
    /// </summary>
    /// <remarks>
    /// <para>This method behaves like <see cref="blob::resize" />, but
    /// it will keep any existing data within the specified size.</para>
    /// <para>Although this method is called <see cref="blob::truncate" />,
    /// it can also increase the capacity of the blob. Any new data behind
    /// the existing range of content will remain uninitialised.</para>
    /// </remarks>
    /// <param name="size">The requested size in bytes.</param>
    /// <param name="noalloc">If <c>true</c>, the truncation will be performed
    /// by decreasing the indicated size without actually freeing the excess
    /// memory. This flag has no effect if the requested <paramref name="size" />
    /// is more than what is currently allocated.</param>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    void truncate(_In_ const std::size_t size, _In_ const bool noalloc = false);

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::bad_alloc">If the required memory could not
    /// be allocated.</exception>
    blob& operator =(_In_ const blob& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    blob& operator =(_Inout_ blob&& rhs) noexcept;

    /// <summary>
    /// Answer a pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <returns>A pointer to the data.</returns>
    inline _Ret_maybenull_ operator void *(void) noexcept {
        return static_cast<void *>(this->_data);
    }

    /// <summary>
    /// Answer a pointer to the allocated data.
    /// </summary>
    /// <remarks>
    /// <para>The object remains owner of the memory the returned pointer
    /// refers to.</para>
    /// <para>A blob can be empty, wherefore the data pointer can be
    /// <c>nullptr</c>.</para>
    /// </remarks>
    /// <returns>A pointer to the data.</returns>
    inline _Ret_maybenull_ operator const void *(void) const noexcept {
        return static_cast<const void *>(this->_data);
    }

    /// <summary>
    /// Answer whether the blob is non-empty.
    /// </summary>
    /// <returns><c>true</c> if the blob has at least one byte allocated,
    /// <c>false</c> if the data pointer is <c>nullptr</c>.</returns>
    inline operator bool(void) const noexcept {
        return (this->_data != nullptr);
    }

private:

    byte_type *_data;
    std::size_t _size;

};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/blob.inl"

#endif /* !defined(_PWROWG_BLOB_H) */
