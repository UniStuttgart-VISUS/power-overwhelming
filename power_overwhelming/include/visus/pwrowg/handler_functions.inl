// <copyright file="handler_functions.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::allocate_with_context
 */
template<class TContext>
void *PWROWG_DETAIL_NAMESPACE::allocate_with_context(
        _In_ const std::size_t size, _In_ TContext&& context) {
    typedef std::decay_t<TContext> context_type;
    auto retval = ::operator new(size + sizeof(context_type));
    assert(retval != nullptr);

    try {
        auto ctx = reinterpret_cast<std::uint8_t *>(retval) + size;
        new (ctx) context_type(std::forward<TContext>(context));
    } catch (...) {
        free_with_context(retval);
        throw;
    }

    return retval;
}
