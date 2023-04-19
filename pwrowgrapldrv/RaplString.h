// <copyright file="string_processing.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>


/// <summary>
/// Answers the length of the given string in number of characters.
/// </summary>
/// <param name="string"></param>
/// <returns></returns>
inline __int32 RaplStringCount(_In_ UNICODE_STRING& string) noexcept {
    static_assert(sizeof(*string.Buffer) == 2, "Characters should be UTF-16.");
    return static_cast<__int32>(string.Length) / 2;
}


/// <summary>
/// Provides the pointer to the character after the end of the string (the
/// null if the string is null-terminated).
/// </summary>
/// <param name="string"></param>
/// <returns></returns>
_Ret_maybenull_ inline PWCH RaplStringEnd(
        _In_ UNICODE_STRING& string) noexcept {
    auto ptr = reinterpret_cast<__int8 *>(string.Buffer);
    return reinterpret_cast<PWCH>(ptr + string.Length);
}


/// <summary>
/// Provides the pointer to the character after the end of the string (the
/// null if the string is null-terminated).
/// </summary>
/// <param name="string"></param>
/// <returns></returns>
_Ret_maybenull_ inline PWCH RaplStringEnd(
        _In_opt_ PUNICODE_STRING string) noexcept {
    return (string != nullptr) ? ::RaplStringEnd(*string) : nullptr;
}
