// <copyright file="blob_streambuf.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::seekoff
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::pos_type
PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::seekoff(
        _In_ const off_type offset,
        _In_ const std::ios_base::seekdir direction,
        _In_ const std::ios_base::openmode mode) {
    switch (direction) {
        case std::ios_base::beg:
            return this->seekpos(offset, mode);

        case std::ios_base::cur:
            return this->seekpos(this->gptr() - this->begin() + offset, mode);

        case std::ios_base::end:
            return this->seekpos(static_cast<off_type>(this->_blob.size())
                + offset, mode);

        default:
            return static_cast<pos_type>(-1);
    }
}


/*
 * PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::seekpos
 */
template<class TChar, class TTraits>
typename PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::pos_type
PWROWG_NAMESPACE::blob_streambuf<TChar, TTraits>::seekpos(
        _In_ const pos_type position,
        _In_ const std::ios_base::openmode mode) {
    if ((mode & std::ios_base::in) != 0) {
        auto pos = this->_blob.template as<TChar>(position);
        if (position <= 0) {
            pos = this->begin();
        } else if (position >= this->limit()) {
            pos = this->end();
        }

        this->setg(this->begin(), pos, this->end());

        return (pos - this->begin());

    } else {
        return static_cast<pos_type>(-1);
    }
}
