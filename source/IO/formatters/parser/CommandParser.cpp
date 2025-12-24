#include <IO/formatters/parser/CommandParser.hpp>

#include <regex>
#include <iostream>

std::string::const_iterator CommandParser::pair_bracket(std::string::const_iterator beginning, std::string::const_iterator end, std::string::value_type opening_bracket, std::string::value_type closing_bracket) {
	int bracket_level = (*beginning == opening_bracket ? 1 : 0);

	std::string::const_iterator iterator = beginning;
	std::string::const_iterator last_closing_bracket = beginning;
	while (bracket_level > 0 && iterator < end) {
		++iterator;
		if (*iterator == opening_bracket)
			bracket_level++;
		else if (*iterator == closing_bracket) {
			bracket_level--;
			last_closing_bracket = iterator;
		}
	}

	if (bracket_level == 0)
		return iterator;
	
	if (bracket_level > 0)
		return last_closing_bracket;
	
	return beginning;
}

std::vector<ParseUnit> CommandParser::parse_to_units(std::string to_parse, std::vector<std::string> commands) {
	std::string command_name_regex_text = "/(";
	for (std::vector<std::string>::size_type i = 0; i < commands.size(); i++) {
		command_name_regex_text += commands[i];
		if (i != commands.size() - 1)
			command_name_regex_text += "|";
	}

	if (commands.empty())
		command_name_regex_text += "\\w+";

	command_name_regex_text += ")(?=(\\.|\\{|<))";
	std::regex command_name_regex{command_name_regex_text};

	std::sregex_iterator command_name_match_begin(to_parse.begin(), to_parse.end(), command_name_regex);
	std::sregex_iterator command_name_iterator_end{};

	std::vector<ParseUnit> result;
	std::string::const_iterator processed = to_parse.begin();
	for (std::sregex_iterator command_name_match_iterator = command_name_match_begin; command_name_match_iterator != command_name_iterator_end; ++command_name_match_iterator) {
		std::smatch match = *command_name_match_iterator;
		std::ssub_match matched_command = match[0];
		if (matched_command.first > processed) {
			ParseUnit omitted_plaintext{};
			omitted_plaintext.type = ParseUnitType::PLAINTEXT;
			omitted_plaintext.plaintext_payload = std::string{processed, matched_command.first};
			result.push_back(omitted_plaintext);
			processed = matched_command.first;
		}
		else if (matched_command.first < processed)
			continue;

		ParseUnit command_unit;
		command_unit.type = ParseUnitType::COMMAND;
		Command& command = command_unit.command_payload;
		command.command_name = matched_command.str().substr(1);

		bool properly_parsed_command = false;
		std::string::const_iterator argument_iterator = matched_command.second;
		while (argument_iterator < to_parse.end() && !properly_parsed_command) {
			// Skipping inner command matches
			if (*argument_iterator == '.') {
				argument_iterator++;
				properly_parsed_command = true;
			}
			else if (*argument_iterator == '{') {
				std::string::const_iterator corresponding_bracket = pair_bracket(argument_iterator, to_parse.end());
				if (corresponding_bracket == argument_iterator)
					std::cerr << "No corresponding option bracket found! Name of command that caused the error: " << command.command_name << std::endl;
			
				Argument option;
				option.type = ArgumentType::OPTION;
				option.payload = std::string{argument_iterator + 1, corresponding_bracket};

				command.arguments.push_back(option);
				argument_iterator = corresponding_bracket + 1;
			}
			else if (*argument_iterator == '<') {
				std::string::const_iterator corresponding_bracket = pair_bracket(argument_iterator, to_parse.end(), '<', '>');
				if (corresponding_bracket == argument_iterator)
					std::cerr << "No corresponding option bracket found! Name of command that caused the error: " << command.command_name << std::endl;

				Argument code;
				code.type = ArgumentType::CODE;
				code.payload = std::string{argument_iterator + 1, corresponding_bracket};

				command.arguments.push_back(code);
				argument_iterator = corresponding_bracket + 1;
			}
			else {
				std::cerr << "Unexpected character '" << *argument_iterator << "' after command name: " << std::string{processed, argument_iterator + 1} << std::endl; 
				break;
			}
		}
		
		if (properly_parsed_command) {
			processed = argument_iterator;
			result.push_back(command_unit);
		}
	}

	if (to_parse.end() > processed) {
		ParseUnit omitted_plaintext{};
		omitted_plaintext.type = ParseUnitType::PLAINTEXT;
		omitted_plaintext.plaintext_payload = std::string{processed, to_parse.cend()};
		result.push_back(omitted_plaintext);
		processed = to_parse.end();
	}

#ifndef NDEBUG
	std::clog << "Parsed: " << to_parse << std::endl;
	std::clog << "To: " << std::endl;;
	for (ParseUnit unit : result) {
		if (unit.type == ParseUnitType::PLAINTEXT)
			std::clog << "TXT\t"<< unit.plaintext_payload << std::endl;
		else if (unit.type == ParseUnitType::COMMAND)
			std::clog << "CMD\t" << unit.command_payload.str() << std::endl;
		else 
			std::clog << "UNASSIGNED!" << std::endl;
	}
#endif

	return result;
}
