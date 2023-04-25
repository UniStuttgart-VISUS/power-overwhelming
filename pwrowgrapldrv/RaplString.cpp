// <copyright file="RaplParse.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplParse.h"

#include "RaplString.h"


/*
 * ::RaplParseInt32
 */
NTSTATUS RaplParseInt32(_Out_ __int32& dst, _In_ const UNICODE_STRING& str) {
    if ((str.Buffer == nullptr) || (str.Length == 0)) {
        KdPrint(("[PWROWG] RaplParseInt32 cannot parse an empty string\r\n"));
        return STATUS_INVALID_PARAMETER_2;
    }

    const auto end = ::RaplStringEnd(str);


}
