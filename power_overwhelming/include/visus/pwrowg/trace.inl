// <copyright file="trace.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 206 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tracer::operator ()
 */
template<class... TArguments>
void PWROWG_DETAIL_NAMESPACE::tracer::operator ()(
        _In_z_ const char *const format,
        TArguments&&... arguments) noexcept {
#if defined(_WIN32)
    constexpr const char *const prefix = "[0x%08x, %s:%d] ";
    const auto tid = ::GetCurrentThreadId();
    std::vector<char> buffer(::_scprintf(prefix, tid, this->_file,
        this->_line) + 1);

    if (::sprintf_s(buffer.data(),
            buffer.size(),
            prefix,
            tid,
            this->_file,
            this->_line) < 0) {
        return;
    }

    const auto offset = ::strlen(buffer.data());
    const auto size = ::_scprintf(format,
        std::forward<TArguments>(arguments)...) + 1;
    buffer.resize(offset + size + 2);

    if (::sprintf_s(buffer.data() + offset,
            size,
            format,
            std::forward<TArguments>(arguments)...) < 0) {
        return;
    }

    ::strcat_s(buffer.data(), buffer.size(), "\r\n");

    ::OutputDebugStringA(buffer.data());
#else /* defined(_WIN32) */
    std::cout << "[0x"
        << std::hex << std::uppercase << std::this_thread::get_id() << ", "
        << this->_file << ':' << this->_line << "] ";

    std::vector<char> buffer(::snprintf(nullptr, 0, format,
        std::forward<TArguments>(arguments)...) + 1);

    if (::snprintf(buffer.data(),
            buffer.size(),
            format,
            std::forward<TArguments>(arguments)...) < 0) {
        return;
    }

    std::cout << buffer.data() << std::endl;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tracer::operator ()
 */
template<class... TArguments>
void PWROWG_DETAIL_NAMESPACE::tracer::operator ()(
        _In_z_ const wchar_t *const format,
        TArguments&&... arguments) noexcept {
#if defined(_WIN32)
    constexpr const wchar_t *const prefix = L"[0x%08x, %hs:%d] ";
    const auto tid = ::GetCurrentThreadId();
    std::vector<wchar_t> buffer(::_scwprintf(prefix, tid, this->_file,
        this->_line) + 1);

    if (::swprintf_s(buffer.data(),
            buffer.size(),
            prefix,
            tid,
            this->_file,
            this->_line) < 0) {
        return;
    }

    const auto offset = ::wcslen(buffer.data());
    const auto size = ::_scwprintf(format,
        std::forward<TArguments>(arguments)...) + 1;
    buffer.resize(offset + size + 2);

    if (::swprintf_s(buffer.data() + offset,
            size,
            format,
            std::forward<TArguments>(arguments)...) < 0) {
        return;
    }

    ::wcscat_s(buffer.data(), buffer.size(), L"\r\n");

    ::OutputDebugStringW(buffer.data());
#else /* defined(_WIN32) */
    std::wcout << L"[0x"
        << std::hex << std::uppercase << std::this_thread::get_id() << L", "
        << this->_file << L':' << this->_line << L"] ";

    std::vector<wchar_t> buffer(::swprintf(nullptr, 0, format,
        std::forward<TArguments>(arguments)...) + 1);

    if (::swprintf(buffer.data(),
            buffer.size(),
            format,
            std::forward<TArguments>(arguments)...) < 0) {
        return;
    }

    std::wcout << buffer.data() << std::endl;
#endif /* defined(_WIN32) */
}
