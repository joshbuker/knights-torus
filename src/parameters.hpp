#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>

#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
std::unordered_map<std::string, int> parse_arguments(int argc, char *argv[]);
#endif
