// <copyright file="RaplString.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplString.h"


/*
 * ::RaplParseInt32
 */
NTSTATUS RaplParseInt32(_Out_ __int32 &dst, _In_ UNICODE_STRING &str,
    _In_ decltype(UNICODE_STRING::Length) offset) {
    if ((str.Buffer == nullptr) || (str.Length <= offset)) {
        KdPrint(("[PWROWG] RaplParseInt32 cannot parse an empty string.\r\n"));
        return STATUS_INVALID_PARAMETER_2;
    }

    const auto begin = str.Buffer + offset;
    const auto end = ::RaplStringEnd(str);
    const auto isHex = ((end - begin) > 2)
        && (begin[0] == L'0')
        && ((begin[1] == L'x') || (begin[1] == L'X'));

    dst = 0;

    for (auto d = begin + (isHex ? 2 : 0); d < end; ++d) {
        dst *= isHex ? 16 : 10;

        if ((*d >= L'0') && (*d <= L'9')) {
            dst += static_cast<__int32>(*d - L'0');

        } else if (isHex && (*d >= 'a') && (*d <= 'f')) {
            dst += static_cast<__int32>(*d - L'a') + 10;

        } else if (isHex && (*d >= 'A') && (*d <= 'F')) {
            dst += static_cast<__int32>(*d - L'A') + 10;

        } else {
            KdPrint(("[PWROWG] RaplParseInt32 found a non-digit.\r\n"));
            return STATUS_INVALID_PARAMETER_2;
        }
    }

    return STATUS_SUCCESS;
}
