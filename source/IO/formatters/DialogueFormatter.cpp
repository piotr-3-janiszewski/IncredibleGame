#include <IO/formatters/DialogueFormatter.hpp>

#include <iostream>
#include <set>
#include <sstream>

std::string DialogueFormatter::execute_command(Command command) {
	if (command.command_name == "say") {
		if (command.arguments.size() == 0) {
			std::cerr << get_name() << " say Too few arguments in:" << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}

		if (command.arguments[0].type != ArgumentType::OPTION) {
			std::cerr << get_name() << " say First argument is not an option, in:" << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}

		std::string key = command.arguments[0].payload;

		if (!dramatis_personae.contains(key)) {
			std::cerr << get_name() << " say \"" << key << "\" person hasn't been added, in:" << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}
		BubbleProperties speaking_style = dramatis_personae[key];

		std::ostringstream result;
		result <<"/box";
		result << speaking_style.box_arguments;
		result << (speaking_style.name_set ? (std::string("<") + speaking_style.name_begin_modifiers + speaking_style.name + speaking_style.name_end_modifiers + ">") : "");

		for (std::vector<Argument>::iterator argument_iterator = command.arguments.begin() + 1; argument_iterator != command.arguments.end(); ++argument_iterator) {
			// Sometimes, there may be a /name command inside a speech bubble.
			// that's why we need to rerun the format method :<
			argument_iterator->payload = this->format(argument_iterator->payload);
			result << argument_iterator->str();
		}

		result << ".";
		return result.str();
	}
	else if (command.command_name == "add_speaker") {
		std::string key;
		BubbleProperties speaking_style;

		std::vector<Argument>::size_type option = 0;
		for (; option < command.arguments.size(); option++) {
			if (option == 0) {
				key = command.arguments[option].payload;
			}
			else if (option == 1) {
				speaking_style.box_arguments = command.arguments[option].payload;
			}
			else if (option == 2) {
				std::string name_set_to_parse = command.arguments[option].payload;

				bool name_set_parsed;
				if (std::set<std::string>{
				  "yes",
				  "true",
				  "1",
				  "name-set",
				  "set"
				  }.contains(name_set_to_parse))
					name_set_parsed = true;
				else if (std::set<std::string>{
				  "no",
				  "false",
				  "0",
				  "name-unset",
				  "unset"
				  }.contains(name_set_to_parse))
					name_set_parsed = false;
				else {
					std::cerr << get_name() << "Argument (name set) couldn't be parsed: " << name_set_to_parse << ", in:" << std::endl;
					std::cerr<< command.str();
				}

				speaking_style.name_set = name_set_parsed;
			}
			else if (option == 3) {
				std::vector<Argument> sub_arguments;
				sub_arguments = CommandParser::parse_sub_arguments(command.arguments[option]);

				for (const Argument& argument : sub_arguments) {
					if (argument.type != ArgumentType::OPTION) {
						std::cerr << get_name() << " name modifier may not be a code argument, in" << std::endl;
						std::cerr << command.str() << std::endl;
					}

					speaking_style.name_begin_modifiers += argument.payload;
					speaking_style.name_begin_modifiers += "<";
					speaking_style.name_end_modifiers += ">.";
				}
			}
			else if (option == 4) {
				speaking_style.name = command.arguments[option].payload;
			}
		}

		if ((option != 4 && !speaking_style.name_set)){
			std::cerr << get_name() << " Name is not set, while the number of arguments is not equal to 4" << std::endl;
			return command.str();
		}
		else if (option != 5 && speaking_style.name_set) {
			std::cerr << get_name() << " Name is set, while the number of arguments is not equal to 5" << std::endl;
			return command.str();
		}

		dramatis_personae[key] = speaking_style;

		std::clog << "\"" << key << "\" speaker has been added successfully" << std::endl;
		
		return "";
	}
	else if (command.command_name == "name") {
		if (command.arguments.size() < 1 || command.arguments.size() > 2) {
			std::cerr << get_name() << " Bad number of arguments in: " << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}

		if (command.arguments[0].type != ArgumentType::OPTION) {
			std::cerr << get_name() << " The first argument in \"name\" command is not an option, in:"  << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}

		BubbleProperties speaking_style;
		if (dramatis_personae.contains(command.arguments[0].payload) == false) {
			std::cerr << get_name() << " There is no registered speaker named \"" << command.arguments[0].payload << "\", in:" << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}
		else {
			speaking_style = dramatis_personae[command.arguments[0].payload];
		}

		std::string name;
		if (command.arguments.size() == 2)
			name = command.arguments[1].payload;
		else 
			name = speaking_style.name;

		return speaking_style.name_begin_modifiers + name + speaking_style.name_end_modifiers;
	}
	else {
		std::cerr << get_name() << " Bad command name \"" << command.command_name << "\" in:\n";
		std::cerr << command.str() << std::endl;
		return command.str();

	}
}

const std::vector<std::string>& DialogueFormatter::get_command_names() {
	static std::vector<std::string> command_names{"say", "add_speaker", "name"};
	return command_names;
}

const char* DialogueFormatter::get_name() {
	return "DialogueFormatter";
}
