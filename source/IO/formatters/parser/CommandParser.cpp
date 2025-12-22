#pragma once

#include <IO/formatter/parser/CommandParser.hpp>

#include <regex>

CommandParser::parse_to_units(std::string to_parse, std::span<std::string> commands) {
	std::string any_given_command_regex_text = "/(";
	for (size_t i = 0; i < commands.size(); i++) {
		any_given_command_regex_text += commands[i];
		if (i != commands.size() - 1)
			any_given_command_regex_text += "|";
	}

	any_given_command_regex_text += ")(())(?=.*)";
}
