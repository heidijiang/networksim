#include "parsing.h"
#include "interface.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int parse_int(const string& s) {

    string str_strip;
    bool num_occur = false;
    int str2int = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        char str_val = s[i];

        int tmp_val = int_lookup(str_val);

        // if there are any non-ints, throw
        if (tmp_val==-1) {
            throw runtime_error("non-int detected");
        }

        // if there are no non-zero ints (only zero), return 0
        if (tmp_val==0 && i == s.size()-1 && !num_occur) {
            return 0;
        }

        // if non-zero ints occur, begin
        if (tmp_val>0 && tmp_val<10) {
            num_occur = true;
        }

        // if a non-zero int has previously been detected, begin looping
        if (num_occur) {
            // for each int following detection of non-zero num, add using power of 10 + numDigit incrementer
            str2int = str2int*10+tmp_val; //char2int * pow(10,numDigit-1);
        }
    }

    if (!num_occur) {
        throw runtime_error("no ints in string found!");
    }
    return str2int;
}

vector<string> tokenize(const string& line)
{
    vector<string> result;
    char space = ' ';
    char quote = '\"';
    int quoteCount = 0;
    size_t begin = 0;
    size_t length = 0;

    for (size_t i=0; i<line.size(); ++i) {
        char strVal = line[i];
        //check to see what kind char current input is
        if (strVal==quote) {
            ++quoteCount;
            if (length!=0 || quoteCount==2) {
                string completeStr = line.substr(begin, length);
                result.push_back(completeStr);
                begin = i + 1;
                length = 0;
            } else {
                begin = i+1;
            }
            // if this is an end quote, push back and reset
            if (quoteCount==2) {
                quoteCount = 0;
            }

        } else if (strVal==space) {
            // get rid of multiple spaces not enclosed by quotes
            if (length==0 && quoteCount==0) {
                begin = i+1;

            //if it's still part of a quote (unenclosed), continue
            } else if (quoteCount == 1) {
                ++length;
            }

            //if there's no quote, then push back and reset
            else {
                string completeStr = line.substr(begin,length);
                result.push_back(completeStr);
                begin = i+1;
                length = 0;
                quoteCount = 0;
            }
        } else {
            ++length;
        }

        if (i==line.size()-1 && length>0) {
            string completeStr = line.substr(begin,length);
            result.push_back(completeStr);
        }
    }

    if (quoteCount==1) {
        throw runtime_error("single quotation mark found");
    }

    if (result.empty()) {
        result = {""};
    };

    return result;
}

int int_lookup(char charInt) {

    const vector<char> ords{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < ords.size(); ++i) {
        if(charInt==ords[i]) {
            return i;
        }
    }
    return -1;

}