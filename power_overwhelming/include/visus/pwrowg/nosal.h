// <copyright file="nosal.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NOSAL_H)
#define _PWROWG_NOSAL_H
#pragma once

#if defined(_WIN32)
#error "This file must not be included on Windows."
#endif /* defined(_WIN32) */

// Empty SAL annotations for rancid platforms.
#if !defined(_Analysis_assume_)
#define _Analysis_assume_(expr)
#endif /* !defined(_Analysis_assume_) */

#if !defined(_Check_return_)
#define _Check_return_
#endif /* !defined(_Check_return_) */

#if !defined(_In_)
#define _In_
#endif /* !defined(_In_) */

#if !defined(_Inout_)
#define _Inout_
#endif /* !defined(_Inout_) */

#if !defined(_Inout_opt_)
#define _Inout_opt_
#endif /* !defined(_Inout_opt_) */

#if !defined(_Inout_opt_z_)
#define _Inout_opt_z_
#endif /* !defined(_Inout_opt_z_) */

#if !defined(_Inout_updates_)
#define _Inout_updates_(cnt)
#endif /* !defined(_Inout_updates_) */

#if !defined(_In_opt_)
#define _In_opt_
#endif /* !defined(_In_opt_) */

#if !defined(_In_opt_z_)
#define _In_opt_z_
#endif /* !defined(_In_opt_z_) */

#if !defined(_In_reads_)
#define _In_reads_(cnt)
#endif /* !defined(_In_reads_) */

#if !defined(_In_reads_bytes_)
#define _In_reads_bytes_(cnt)
#endif /* !defined(_In_reads_bytes_) */

#if !defined(_In_reads_or_z_)
#define _In_reads_or_z_(cnt)
#endif /* !defined(_In_reads_or_z_) */

#if !defined(_In_reads_opt_)
#define _In_reads_opt_(cnt)
#endif /* !defined(_In_reads_opt_) */

#if !defined(_In_z_)
#define _In_z_
#endif /* !defined(_In_z_) */

#if !defined(_Out_)
#define _Out_
#endif /* !defined(_Out_) */

#if !defined(_Out_opt_)
#define _Out_opt_
#endif /* !defined(_Out_opt_) */

#if !defined(_Out_writes_)
#define _Out_writes_(cnt)
#endif /* !defined(_Out_writes_) */

#if !defined(_Out_writes_bytes_)
#define _Out_writes_bytes_(cnt)
#endif /* !defined(_Out_writes_bytes_) */

#if !defined(_Out_writes_opt_)
#define _Out_writes_opt_(cnt)
#endif /* !defined(_Out_writes_opt_) */

#if !defined(_Out_writes_opt_z_)
#define _Out_writes_opt_z_(cnt)
#endif /* !defined(_Out_writes_opt_z_) */

#if !defined(_Ret_)
#define _Ret_
#endif /* !defined(_Ret_) */

#if !defined(_Ret_maybenull_)
#define _Ret_maybenull_
#endif /* !defined(_Ret_maybenull_) */

#if !defined(_Ret_maybenull_z_)
#define _Ret_maybenull_z_
#endif /* !defined(_Ret_maybenull_z_) */

#if !defined(_Ret_null_)
#define _Ret_null_
#endif /* !defined(_Ret_null_) */

#if !defined(_Ret_valid_)
#define _Ret_valid_
#endif /* !defined(_Ret_valid_) */

#if !defined(_Ret_z_)
#define _Ret_z_
#endif /* !defined(_Ret_z_) */

#if !defined(_When_)
#define _When_(expr, annotes)
#endif /* !defined(_When_) */

#endif /* !defined(_PWROWG_NOSAL_H) */
