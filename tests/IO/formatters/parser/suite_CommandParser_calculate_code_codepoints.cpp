#include <IO/formatters/parser/CommandParser.hpp>
#include <utils/test_utils.hpp>

int main() {
	std::string str1 = "Pelican";
	std::string str2 = "/william.";
	std::string str3 = "/william{carlos}<wiliams>.";
	std::string str4 = "/so_much_depends_upon{a}{red}{wheel}{barrow}<glazed><with><rain><water>./beside{the}<white>.chickens";
	std::string str5 = "of times — that is, draw as many cards as they /paint{red}<w>./paint{green}<i>./paint{blue}<s>./paint{bright-green}<h>..";
	return 
		assert_strings_equal(str1 + std::to_string(7), str1 + std::to_string(CommandParser::calculate_code_codepoints(str1))) ||
		assert_strings_equal(str2 + std::to_string(0), str2 + std::to_string(CommandParser::calculate_code_codepoints(str2))) ||
		assert_strings_equal(str3 + std::to_string(7), str3 + std::to_string(CommandParser::calculate_code_codepoints(str3))) ||
		assert_strings_equal(str4 + std::to_string(32), str4 + std::to_string(CommandParser::calculate_code_codepoints(str4))) ||
		assert_strings_equal(str5 + std::to_string(52), str5 + std::to_string(CommandParser::calculate_code_codepoints(str5)));

}
