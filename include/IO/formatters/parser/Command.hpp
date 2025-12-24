#pragma once

#include <IO/formatters/parser/Argument.hpp>

#include <string>
#include <vector>

class Command {
public:
	std::string command_name;
	std::vector<Argument> arguments;

	std::string str(); // Short name to fit the standard C++ convention
};
