#pragma once

#include "datagram.h"

#include <string>
#include <vector>

struct System
{
};

void System_print(const std::vector<IP_address>& ips_);
void System_create_machine(const std::string& type, const std::string& name,
                           const IP_address& ip);
void System_delete_machine(const IP_address& ip);
void System_connect_machine(const IP_address& ip1, const IP_address& ip2);
void System_allocate_datagram(const IP_address& ip1, const IP_address& ip2,
                              const std::string& message);
void System_release_datagram(const IP_address& ip);
void System_time_click();
