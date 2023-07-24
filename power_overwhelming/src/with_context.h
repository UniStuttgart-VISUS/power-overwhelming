// <copyright file="with_context.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A base class that allows attaching user-defined contexts to classes like
    /// samplers while allowing for the lack of contexts (<c>void</c>) by means
    /// of a template specialisation in combination with empty base class
    /// elision.
    /// </summary>
    /// <typeparam name="TContext">The type of the context being attached to
    /// classes inheriting from this one.</typeparam>
    template<class TContext> class with_context {

    public:

        /// <summary>
        /// The type of the context being attached to classes inheriting from
        /// this one.
        /// </summary>
        typedef TContext context_type;

    protected:

        /// <summary>
        /// The context.
        /// </summary>
        context_type _context;
    };


    /// <summary>
    /// Specialisations for no context.
    /// </summary>
    template<> class with_context<void> {

    public:

        /// <summary>
        /// Indicates that there is no context.
        /// </summary>
        typedef void context_type;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
