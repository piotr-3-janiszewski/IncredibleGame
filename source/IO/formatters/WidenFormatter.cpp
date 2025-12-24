#include <IO/formatters/WidenFormatter.hpp>

#include <iostream>

std::string WidenFormatter::execute_command(Command command) {
	if (command.arguments.size() != 1) {
		std::cerr << get_name() << " bad number of arguments, is " << command.arguments.size() << " should be 1." << std::endl;
		return command.str();
	}

	if (command.arguments[0].type != ArgumentType::CODE) {
		std::cerr << get_name() << " argument not code type: " << command.arguments[0].str() << std::endl;
	}

	
	std::vector<ParseUnit> units = CommandParser::parse_to_units(command.arguments[0].payload);
	std::ostringstream result_stream;

	for (ParseUnit& unit : units) {
		if (unit.type == ParseUnitType::PLAINTEXT) {
			bool first_character_printed = false;
			for (const char& character : unit.plaintext_payload) {
				// Strings use UTF-8 encoding. Each code point may have either 1, 2, 3 or 4 bytes, but the first one never beggins with 0b10
				if (first_character_printed && (((character ^ 0x40) & 0xc0) != 0xc0))
					result_stream << " ";

				result_stream << character;
				first_character_printed = true;
			}
		}
		else if (unit.type == ParseUnitType::COMMAND) {
			for (Argument& argument : unit.command_payload.arguments) {
				if (argument.type == ArgumentType::CODE) {
					Command sub_command;
					sub_command.command_name = "widen";
					sub_command.arguments.push_back(argument);
					std::clog << "Ale zabawa: " << sub_command.str() << std::endl;
					argument.payload = execute_command(sub_command);
				}
			}
			result_stream << unit.command_payload.str();
		}
		else 
			result_stream << "UNASSIGNED";
	}

	return result_stream.str();
}

const std::vector<std::string>& WidenFormatter::get_command_names() {
	static std::vector<std::string> command_names{"widen"};
	return command_names;
}

const char* WidenFormatter::get_name() {
	return "WidenFormatter";
}

WidenFormatter::~WidenFormatter() {}
