#include <IO/formatters/parser/CommandParser.hpp>
#include <utils/test_utils.hpp>

std::string get_string_to_next_bracket(std::string input, int beginning_position, char openning_bracket = '{', char closing_bracket = '}') {
	std::string::const_iterator beginning_iterator = input.cbegin() + beginning_position;
	std::string::const_iterator next_bracket = CommandParser::pair_bracket(beginning_iterator, input.cend(), openning_bracket, closing_bracket);
	
	if (next_bracket <= beginning_iterator)
		return std::string{"NOT FOUND"};

	if (next_bracket > input.cend())
		return std::string{"ITERATOR TOO BIG"};

	return std::string{beginning_iterator + 1, next_bracket};
}

int main() {
	return
		assert_strings_equal("hello world", get_string_to_next_bracket("{hello world}", 0)) ||
		assert_strings_equal("你好", get_string_to_next_bracket("{{你好}}", 1)) ||
		assert_strings_equal("{{你好}}", get_string_to_next_bracket("{{{你好}}}", 0)) ||	
		assert_strings_equal("konstantyn{{{{{{{{opolitańczykówianeczka", get_string_to_next_bracket("{konstantyn{{{{{{{{opolitańczykówianeczka}", 0)) ||
		assert_strings_equal("konstantyn{op}", get_string_to_next_bracket("{konstantyn{op}}}}}}}}}olitańczykówianeczka}", 0)) ||
		assert_strings_equal("Bóg", get_string_to_next_bracket("{{Bóg} {Honor} {Ojczyzna}}", 1)) ||
		assert_strings_equal("Honor", get_string_to_next_bracket("{Bóg {Honor} {Ojczyzna}}", 6)) || // ó is two characters so 6 instead of 5
		assert_strings_equal("Ojczyzna", get_string_to_next_bracket("{Bóg Honor {Ojczyzna}}", 12)) || // same as above
		assert_strings_equal("mody", get_string_to_next_bracket("{Wszystkie <mody> wszystkie style}", 11, '<', '>'));
}
