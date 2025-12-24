#include <IO/formatters/parser/Command.hpp>
#include <utils/test_utils.hpp>

#include <utility>
#include <iostream>

template<typename... Ts>
std::string make_command_string(std::string command_name, Ts... args) {
	Command command;
	command.command_name = command_name;
	command.arguments = std::vector<Argument>{std::forward<Ts>(args)...};
	return command.str();
}

int main() {
	return
		assert_strings_equal("/command.", make_command_string("command")) ||
		assert_strings_equal("/command{arg1}.", make_command_string("command", Argument{ArgumentType::OPTION, "arg1"})) ||
		assert_strings_equal("/command{arg1}{arg2}{arg3}.", make_command_string("command", Argument{ArgumentType::OPTION, "arg1"}, Argument{ArgumentType::OPTION, "arg2"}, Argument{ArgumentType::OPTION, "arg3"})) ||
		assert_strings_equal("/command{}{}{}.", make_command_string("command", Argument{ArgumentType::OPTION, ""}, Argument{ArgumentType::OPTION, ""}, Argument{ArgumentType::OPTION, ""}));
}
