#include "system.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

static void print_IP(const IP_address& ip)
{
    cout << "\"" << ip[0] << '.' << ip[1] <<
            '.' << ip[2] << '.' << ip[3] << "\"";
}

void System_print(const vector<IP_address>& ips_)
{
    cout << "System::print:";
    for (const IP_address& ip : ips_) {
        cout << ' ';
        print_IP(ip);
    }
    cout << '\n';
}

void System_create_machine(const string& type,
                           const string& name,
                           const IP_address& ip)
{
    cout << "System::create_machine: " << type << ' ' << name << ' ';
    print_IP(ip);
    cout << '\n';
}

void System_delete_machine(const IP_address& ip)
{
    cout << "System::delete_machine: ";
    print_IP(ip);
    cout << '\n';
}

void System_connect_machine(const IP_address& ip1, const IP_address& ip2)
{
    cout << "System::connect_machine: ";
    print_IP(ip1);
    cout << ", ";
    print_IP(ip2);
    cout << '\n';
}

void System_allocate_datagram(const IP_address& ip1,
                              const IP_address& ip2,
                              const string& message)
{
    cout << "System::allocate_datagram: ";
    print_IP(ip1);
    cout << ", ";
    print_IP(ip2);
    cout << ", \"" << message << "\"\n";
}

void System_release_datagram(const IP_address& ip)
{
    cout << "System::release_datagram: ";
    print_IP(ip);
    cout << '\n';
}

void System_time_click()
{
    cout << "System::time_click\n";
}
