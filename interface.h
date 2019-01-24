#pragma once

#include "system.h"

#include <string>
#include <vector>

enum class cmd_code
{
    halt,
    system_status,
    create_machine,
    delete_machine,
    connect_machine,
    send_datagram,
    receive_datagram,
    time_click,
    undefined,
};

struct Command_syntax
{
    cmd_code cmd;
    std::string name;
    int token_num;
};

const extern std::vector<Command_syntax> command_syntaxes;
bool execute_command(System& sys, const std::vector<std::string>& tokens);
