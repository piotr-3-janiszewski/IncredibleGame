#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>
#include <IO/formatters/parser/CommandParser.hpp>

#include <sstream>
#include <iostream>

std::string ParsingFormatterTemplate::in_template_format(std::string message) {
	const std::vector<std::string>& command_names = get_command_names();
	std::vector<ParseUnit> units = CommandParser::parse_to_units(message, command_names);

	std::ostringstream result_stream;

	for (ParseUnit& unit : units) {
		if (unit.type == ParseUnitType::PLAINTEXT) {
			result_stream << unit.plaintext_payload;
		}
		else if (unit.type == ParseUnitType::COMMAND) {
			result_stream << execute_command(unit.command_payload);
		}
		else
			std::clog << "UNASSIGNED encountered in a ParsingFormatter" << std::endl;
	}

	return result_stream.str();
}

ParsingFormatterTemplate::~ParsingFormatterTemplate() {}
