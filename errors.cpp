#include "errors.h"

#include <string>
#include <iostream>

using namespace std;

const char* error_name(err_code code)
{
    switch (code) {
        case err_code::cmd_undefined:
            return "command not found";
        case err_code::syntax_error:
            return "syntax error";
        case err_code::bad_ip_address:
            return "bad IP address";
        case err_code::unknown_machine_type:
            return "unknown machine type";
        case err_code::network_full:
            return "network is full";
        case err_code::no_such_machine:
            return "no such machine";
        case err_code::connect_failed:
            return "fail to connect";
        case err_code::send_blocked:
            return "outgoing buffer is full";
        case err_code::recv_blocked:
            return "incoming buffer is full";
    }
}

void error_print(const string& cmd, err_code code)
{
    cerr << cmd << ": " << error_name(code) << '\n';
}
