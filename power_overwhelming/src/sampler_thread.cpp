//// <copyright file="sampler_thread.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#include "sampler_thread.h"
//
//
///*
// * PWROWG_DETAIL_NAMESPACE::sampler_thread::~sampler_thread
// */
//PWROWG_DETAIL_NAMESPACE::sampler_thread::~sampler_thread(void) noexcept {
//    {
//        std::lock_guard<decltype(this->_lock)> l(this->_lock);
//        //this->_sources.clear();
//    }
//    this->_thread.join();
//}
////
////
/////*
//// * PWROWG_DETAIL_NAMESPACE::sampler_thread::add
//// */
////void PWROWG_DETAIL_NAMESPACE::sampler_thread::add(
////        _In_ sampler_source *source) {
////    if (source != nullptr) {
////        if (source->interval() != this->_interval.count()) {
////            throw std::invalid_argument("The specified source does not match "
////                "the sampling interval of the sampler thread.");
////        }
////
////        std::lock_guard<decltype(this->_lock)> l(this->_lock);
////        this->_sources.push_back(source);
////    }
////}
////
////
/////*
//// * PWROWG_DETAIL_NAMESPACE::sampler_thread::remove
//// */
////bool PWROWG_DETAIL_NAMESPACE::sampler_thread::remove(
////        _In_ sampler_source *source) {
////    std::lock_guard<decltype(this->_lock)> l(this->_lock);
////    auto it = std::remove(this->_sources.begin(), this->_sources.end(),
////        source);
////    this->_sources.erase(it, this->_sources.end());
////    return this->_sources.empty();
////}
////
////
/////*
//// * PWROWG_DETAIL_NAMESPACE::sampler_thread::samples
//// */
////bool PWROWG_DETAIL_NAMESPACE::sampler_thread::samples(
////        _In_ const sampler_source *source) const {
////    std::lock_guard<decltype(this->_lock)> l(this->_lock);
////    return (std::find(this->_sources.begin(), this->_sources.end(),
////        source) != this->_sources.end());
////}
////
////
/////*
//// * PWROWG_DETAIL_NAMESPACE::sampler_thread::sample
//// */
////void PWROWG_DETAIL_NAMESPACE::sampler_thread::sample(void) {
////    auto have_sources = true;
////
////    {
////        std::stringstream stream;
////        stream << "PwrOwg Sampler Thread @" << this->_interval.count() << "us";
////        auto name = stream.str();
////        set_thread_name(name.c_str());
////    }
////
////    while (have_sources) {
////        auto now = std::chrono::high_resolution_clock::now();
////
////        {
////            std::lock_guard<decltype(this->_lock)> l(this->_lock);
////            for (auto it = this->_sources.begin();
////                    it != this->_sources.end();) {
////                if ((**it).deliver()) {
////                    ++it;
////                } else {
////                    // If the source did not deliver a sample, remove it from
////                    // the thread.
////                    it = this->_sources.erase(it);
////                }
////            }
////
////            have_sources = !this->_sources.empty();
////        }
////
////        if (have_sources) {
////            std::this_thread::sleep_until(now + this->_interval);
////        }
////    }
////}
