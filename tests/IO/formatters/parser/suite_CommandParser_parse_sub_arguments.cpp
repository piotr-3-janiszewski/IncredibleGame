#include <IO/formatters/parser/CommandParser.hpp>
#include <utils/test_utils.hpp>

int main() {
	std::vector<Argument> sub_arguments;

	int result = 0;

	Argument argument;
	argument.payload = "{a}{big}<bat>{boy}";
	argument.type = ArgumentType::OPTION;
	sub_arguments = CommandParser::parse_sub_arguments(argument);

	result |= assert_strings_equal("4", std::to_string(sub_arguments.size()));
	if (result)
		return result;
	result |= assert_strings_equal("{a}", sub_arguments[0].str());
	result |= assert_strings_equal("big", sub_arguments[1].payload);
	result |= assert_strings_equal("<bat>", sub_arguments[2].str());
	result |= assert_strings_equal("{boy}", sub_arguments[3].str());

	argument.payload = "";
	sub_arguments = CommandParser::parse_sub_arguments(argument);
	result |= assert_strings_equal("1", std::to_string(static_cast<int>(sub_arguments.empty())));

	argument.payload = "{a}";
	sub_arguments = CommandParser::parse_sub_arguments(argument);
	result |= assert_strings_equal("1", std::to_string(sub_arguments.size()));
	if (result)
		return result;
	result |= assert_strings_equal("{a}", sub_arguments[0].str());

	return result;
}
