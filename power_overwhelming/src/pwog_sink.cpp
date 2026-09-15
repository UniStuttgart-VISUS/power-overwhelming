// <copyright file="pwog_sink.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/pwog_sink.h"

#if defined(_WIN32)
#include <processenv.h>
#endif /* defined(_WIN32) */

#include "friendly_timestamp.h"
#include "io_util.h"


/*
 * PWROWG_NAMESPACE::pwog_sink::write_meta_data
 */
void PWROWG_NAMESPACE::pwog_sink::write_meta_data(void) {
    auto timestamp = detail::friendly_timestamp<char>();
    this->_file << make_pwog_meta_data("Timestamp", timestamp);

#if defined(_WIN32)
    this->_file << make_pwog_meta_data("CommandLine", ::GetCommandLineA());
#else /* defined(_WIN32) */
    auto fh = detail::open("/proc/self/cmdline", O_RDONLY);
    try {
        const auto cmd = detail::read_all_bytes(fh);
        this->_file << make_pwog_meta_data("CommandLine",
            reinterpret_cast<const char *>(cmd.data()));
        ::close(fh);
    } catch (...) {
        ::close(fh);
    }
#endif /* defined(_WIN32) */
}
