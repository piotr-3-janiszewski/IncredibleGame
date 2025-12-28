#include <IO/formatters/SlashEscapeFormatter.hpp>
#include <iostream>
#include <regex>

std::string SlashEscapeFormatter::in_template_format(std::string message) {
	std::regex double_slash_pattern{"//"};
	std::smatch matched_double_slashes;
	message = std::regex_replace(message, double_slash_pattern, "/slash.");

	std::regex escaped_slash_pattern{"/slash\\."};
	return std::regex_replace(message, escaped_slash_pattern, "/");
}

const char* SlashEscapeFormatter::get_name() {
	return "SlashEscapeFormatter";
}
