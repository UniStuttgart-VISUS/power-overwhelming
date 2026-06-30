// <copyright file="daqmx_task.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::daqmx_task::on_done
 */
template<class TCallback>
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::on_done(
        _In_ TCallback&& callback) {
    this->_on_done.emplace<TCallback>(std::forward<TCallback>(callback));
    this->set_on_done();
    return *this;
}
