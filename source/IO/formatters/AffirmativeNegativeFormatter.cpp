#include <IO/formatters/AffirmativeNegativeFormatter.hpp>

#include <iostream>

const char* AffirmativeNegativeFormatter::get_name() {
	return "AffirmativeNegativeFormatter";
}

std::string AffirmativeNegativeFormatter::execute_command(Command command) {
	if (command.arguments.size() != 0 && command.arguments.size() != 1) {
		std::cerr << get_name() << " Bad number of arguments" << std::endl;
		return command.str();
	}

	if (command.arguments.size() == 0) {
		Argument default_message;
		default_message.payload = command.command_name;
		default_message.type = ArgumentType::CODE;
		command.arguments.push_back(default_message);
	}

	if (command.command_name == "affirmative") {
		return "/paint{green}{bold}<" + command.arguments[0].payload + ">.";
	}

	return "/paint{red}<" + command.arguments[0].payload + ">.";
}

const std::vector<std::string>& AffirmativeNegativeFormatter::get_command_names() {
	static const std::vector<std::string> commands{"affirmative", "negative"};
	return commands;
}
