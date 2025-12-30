#include <IO/formatters/ChoiceFormatter.hpp>

#include <iostream>

std::string ChoiceFormatter::execute_command(Command command) {
	bool contains_option = false;
	for (const Argument& argument : command.arguments)
		if (argument.type == ArgumentType::OPTION)
			contains_option = true;
	
	if (!contains_option) {
		std::cerr << get_name() << " doesn't contain any choice";
		return command.str();
	}

	std::ostringstream result_stream;
	std::vector<Argument>::const_iterator argument_iterator = command.arguments.begin();

	result_stream << "/say{choice}</paint{bold}<";
	if (argument_iterator->type == ArgumentType::CODE) {
		result_stream << argument_iterator->payload;
		++argument_iterator;
	}
	else
		result_stream << "What would you like to do?";
	result_stream << ">.>";

	while (argument_iterator->type == ArgumentType::CODE) {
		result_stream << "<" << argument_iterator->payload << ">";
		++argument_iterator;
	}

	while(argument_iterator != command.arguments.end()) {
		result_stream << "<[";
		result_stream << argument_iterator->payload;
		++argument_iterator;
		result_stream << "] /paint{underline}<";

		if (argument_iterator->type == ArgumentType::CODE) {
			result_stream << argument_iterator->payload;
			++argument_iterator;
		}
		result_stream << ">.>";

		while (argument_iterator->type == ArgumentType::CODE) {
			result_stream << "</paint{faint}<" << argument_iterator->payload << ">.>";
			++argument_iterator;
		}
	}

	result_stream << ".";

	return result_stream.str();
}

const std::vector<std::string>& ChoiceFormatter::get_command_names() {
	static std::vector<std::string> command_names{"choice"};
	return command_names;
}

const char* ChoiceFormatter::get_name() {
	return "ChoiceFormatter";
}

ChoiceFormatter::~ChoiceFormatter() {}
