#include <IO/formatters/SlashEscapeFormatter.hpp>
#include <iostream>
#include <regex>

std::string SlashEscapeFormatter::in_template_format(std::string message) {
	std::regex double_slash_pattern{"//"};
	std::smatch matched_double_slashes;
	message = std::regex_replace(message, double_slash_pattern, "/slash.");

	std::regex command_pattern{"/(?!slash\\.)\\w*(\\.|\\{)"};
	std::sregex_iterator matched_commands_iterator(message.begin(), message.end(), command_pattern);

	for (;matched_commands_iterator != std::sregex_iterator(); ++matched_commands_iterator)
		std::clog << "Found an unmatched command: `" << matched_commands_iterator->str() << "`" << std::endl;
	
	std::regex single_slash_pattern{"/(?!slash\\.)(?!\\w*(\\.|\\{))"};
	std::sregex_iterator single_slashes_iterator(message.begin(), message.end(), single_slash_pattern);

	int unescaped_slashes = std::distance(single_slashes_iterator, std::sregex_iterator());
	if (unescaped_slashes > 0)
		std::clog << "Found " << unescaped_slashes << " unescaped slashes" << std::endl;

	std::regex escaped_slash_pattern{"/slash\\."};
	return std::regex_replace(message, escaped_slash_pattern, "/");

}

const char* SlashEscapeFormatter::get_name() {
	return "SlashEscapeFormatter";
}
