#include <IO/formatters/parser/Command.hpp>

std::string Command::str() {
	std::string result{};
	result += "/";
	result += command_name;

	for (const Argument& argument : arguments) {
		result += argument.str();
	}
	
	result += ".";

	return result;
}
