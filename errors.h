#pragma once

#include <string>

enum class err_code
{
    cmd_undefined,
    syntax_error,
    bad_ip_address,
    unknown_machine_type,
    network_full,
    no_such_machine,
    connect_failed,
    send_blocked,
    recv_blocked
};

void error_print(const std::string& cmd, err_code errcode);
