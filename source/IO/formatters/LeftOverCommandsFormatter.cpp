#include <IO/formatters/LeftOverCommandsFormatter.hpp>
#include <iostream>
#include <regex>
#include <sstream>

std::string LeftOverCommandsFormatter::in_template_format(std::string message) {
	std::regex command_pattern{"/(?!paint)\\w*(\\.|\\{)"};
	std::sregex_iterator matched_commands_iterator(message.begin(), message.end(), command_pattern);

	std::ostringstream error_buffer;
	bool errors_encountered = false;
	
	for (;matched_commands_iterator != std::sregex_iterator(); ++matched_commands_iterator) {
		error_buffer << "Found an unmatched command: `" << matched_commands_iterator->str() << "`" << std::endl;
		errors_encountered = true;
	}

	if (errors_encountered) {
		std::clog << get_name() << " Encountered left over commands in the follwing message:" << std::endl;
		std::clog << message << std::endl;
		std::clog << std::string(10, '-') << std::endl;
		std::clog << error_buffer.str() << std::endl;
	}
	
	return message;
}

const char* LeftOverCommandsFormatter::get_name() {
	return "LeftOverCommandsFormatter";
}
