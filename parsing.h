#pragma once

#include "interface.h"

#include <string>
#include <vector>

int parse_int(const std::string& s);
std::vector<std::string> tokenize(const std::string& line);
int int_lookup(char str);