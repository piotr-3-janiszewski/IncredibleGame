#pragma once

#include <IO/formatters/parser/ParseUnit.hpp>

#include <vector>

class CommandParser {
public:
	static std::string::size_type calculate_code_codepoints(std::string message);
	static std::string::const_iterator pair_bracket(std::string::const_iterator beginning, std::string::const_iterator end, std::string::value_type opening_bracket = '{', std::string::value_type closing_bracket = '}');
	static std::vector<ParseUnit> parse_to_units(std::string to_parse, std::vector<std::string> commands);
};
