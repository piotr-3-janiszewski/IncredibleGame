#pragma once

#include <IO/formatter/parser/ParseUnit.hpp>

#include <memory>
#include <span>
#include <vector>

class CommandParser {
public:
	std::unique_ptr<ParseUnit[]> parse_to_units(std::string to_parse, std::span<std::string> commands);
}
