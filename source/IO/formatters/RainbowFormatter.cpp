#include <IO/formatters/RainbowFormatter.hpp>
#include <utils/UTF_8_utils.hpp>

#include <iostream>
#include <sstream>

const char* RainbowFormatter::get_name() {
	return "RainbowFormatter";
}

std::string RainbowFormatter::execute_command(Command command) {
	if (command.arguments.size() != 1) {
		std::cerr << get_name() << " Bad number of arguments" << std::endl;
		return command.str();
	}

	if (command.arguments[0].type != ArgumentType::CODE) {
		std::cerr << get_name() << " Argument not code" << std::endl;
		return command.str();
	}

	static const std::vector<std::string> colors{"red", "green", "blue", "bright-green", "magenta", "yellow", "bright-red", "cyan"};
	static std::vector<std::string>::const_iterator color_iterator = colors.cbegin();

	std::string& code_argument = command.arguments[0].payload;

	std::vector<ParseUnit> units = CommandParser::parse_to_units(code_argument, {});

	std::ostringstream result_stream;
	for (ParseUnit& unit : units) {
		if (unit.type == ParseUnitType::PLAINTEXT) {
			std::string::const_iterator iterator = code_argument.begin();
			bool begun = false;
			while (iterator != code_argument.end()) {
				if (!is_continuation_byte(*iterator)) {
					if (begun) {
						result_stream << ">.";
					}
					result_stream << "/paint{" << *color_iterator << "}<";
					++color_iterator;
					if (color_iterator == colors.end())
						color_iterator = colors.begin();

					begun = true;
				}
				result_stream << *iterator;
				iterator++;

			}

			if (begun)
				result_stream << ">.";
		}
		else if (unit.type == ParseUnitType::COMMAND) {
			Command recursive_rainbow;
			recursive_rainbow.arguments.push_back(Argument());
			recursive_rainbow.command_name = "rainbow";

			for (Argument& argument : unit.command_payload.arguments) {
				if (argument.type == ArgumentType::CODE) {
					recursive_rainbow.arguments[0].payload = argument.payload;
					argument.payload = execute_command(recursive_rainbow);
				}
			}

			result_stream << unit.command_payload.str();
		}
	}
	
	return result_stream.str();
}

const std::vector<std::string>& RainbowFormatter::get_command_names() {
	static const std::vector<std::string> command{"rainbow"};
	return command;
}
