#include "interface.h"
#include "errors.h"
#include "system.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

const vector<Command_syntax> command_syntaxes {
    {cmd_code::halt, "halt", 1},
    {cmd_code::system_status, "stat", -1},
    {cmd_code::create_machine, "create", 4},
    {cmd_code::delete_machine, "delete", 2},
    {cmd_code::connect_machine, "connect", 3},
    {cmd_code::send_datagram, "send", 4},
    {cmd_code::receive_datagram, "recv", 2},
    {cmd_code::time_click, "tick", 1},
    {cmd_code::undefined, "", -1}
};

cmd_code get_command_number(const string& name)
{
    for (const Command_syntax& stx : command_syntaxes)
        if (name == stx.name)
            return stx.cmd;
    return cmd_code::undefined;
}

int get_command_tokens(cmd_code cmd)
{
    for (const Command_syntax& stx : command_syntaxes)
        if (cmd == stx.cmd)
            return stx.token_num;
    return -1;
}

bool execute_command(System& sys, const vector<string>& tokens)
{
    cmd_code cmd = get_command_number(tokens.empty()? "" : tokens[0]);
    int token_num = get_command_tokens(cmd);

    bool done = false;
    if (token_num != -1 && tokens.size() != token_num)
        throw err_code::syntax_error;

    if (cmd == cmd_code::halt) {
        done = true;
    } else if (cmd == cmd_code::system_status) {
        vector<IP_address> ips;
        for (size_t i = 1; i != tokens.size(); ++i)
            ips.push_back(parse_IP(tokens[i]));
        System_print(ips);
    } else if (cmd == cmd_code::create_machine) {
        System_create_machine(tokens[1], tokens[2], parse_IP(tokens[3]));
    } else if (cmd == cmd_code::delete_machine) {
        System_delete_machine(parse_IP(tokens[1]));
    } else if (cmd == cmd_code::connect_machine) {
        System_connect_machine(parse_IP(tokens[1]), parse_IP(tokens[2]));
    } else if (cmd == cmd_code::send_datagram) {
        System_allocate_datagram(parse_IP(tokens[1]), parse_IP(tokens[2]),
                                 tokens[3]);
    } else if (cmd == cmd_code::receive_datagram) {
        System_release_datagram(parse_IP(tokens[1]));
    } else if (cmd == cmd_code::time_click) {
        System_time_click();
    } else if (cmd == cmd_code::undefined) {
        throw err_code::cmd_undefined;
    }
    return done;
}
