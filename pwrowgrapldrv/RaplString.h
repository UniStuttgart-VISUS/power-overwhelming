// <copyright file="string_processing.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>


/// <summary>
/// Parse the given string as integer number, which can either be decimal or a
/// hexadecimal string (if it starts with &quot;0x&quot).
/// </summary>
/// <param name="dst">Receives the number in case of success.</param>
/// <param name="str">The string to be parsed.</param>
/// <param name="offset">The offset into <paramref name="str" /> at which the
/// number starts.</param>
/// <returns><c>STATUS_SUCCESS</c> in case of success,
/// <c>STATUS_INVALID_PARAMETER_2</c> if the string does not represent a valid
/// number.</returns>
NTSTATUS RaplParseInt32(_Out_ __int32& dst, _In_ UNICODE_STRING& str,
    _In_ decltype(UNICODE_STRING::Length) offset = 0);


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
