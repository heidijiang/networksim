#include "datagram.h"
#include "parsing.h"
#include "errors.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

IP_address parse_IP(string s)
{
    IP_address IP;
    size_t begin = 0;
    unsigned long length = 0;
    int period_count = 0;
    int IP_count = 0;
    string new_str;

    for (size_t i=0; i<s.size(); ++i) {
        char cval = s[i];
        int tmp_val = int_lookup(cval);
        // begin storing if a period is detected, or if it's the last value in the string (and it's an int)
        if (cval=='.' || (i==s.size()-1 && tmp_val!=-1)) {
            if (cval=='.') {
                ++period_count;
            }
            //make sure there aren't too many periods and that ints are found between periods
            if (period_count>3) {
                throw err_code::bad_ip_address;
            }

            if (length==0 && i!=s.size()-1) {
                throw err_code::bad_ip_address;
            }

            else {
                //save int string, make sure to include the current char if it's the last loop
                if (i==s.size()-1) {
                    new_str = s.substr(begin,length+1);
                } else {
                    new_str = s.substr(begin, length);
                }

                //make sure there aren't wrong IP numbers like '05'
                if(new_str[0]=='0' && new_str.size()>1)  {
                    throw err_code::bad_ip_address;
                }

                int IP_val = parse_int(new_str);

                if (IP_val>255) {
                    throw err_code::bad_ip_address;
                }

                //store and reset
                IP[IP_count] = IP_val;
                ++IP_count;
                length=0;
                begin = i+1;

            }

        } else if (tmp_val==-1) {
            throw err_code::bad_ip_address;

        } else {
            ++length;
        }
    }

    //last check to make sure IP address had 4 separate ints
    if (IP_count!=4 || period_count!=3) {
        throw err_code::bad_ip_address;
    }

    return IP;
}
