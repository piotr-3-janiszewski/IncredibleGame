#pragma once

#include <IO/formatters/parser/ArgumentType.hpp>

#include <string>

struct Argument {
	ArgumentType type;
	std::string payload;
	std::string str() const;
};
