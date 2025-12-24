#include <IO/formatters/parser/CommandParser.hpp>
#include <utils/test_utils.hpp>
#include <sstream>

std::string parse_to_units(std::string to_parse, std::vector<std::string> commands) {
	std::vector<ParseUnit> units = CommandParser::parse_to_units(to_parse, commands);

	std::ostringstream result;
	for (ParseUnit& unit : units) {
		if (unit.type == ParseUnitType::PLAINTEXT)
			result << "TXT\t" << unit.plaintext_payload << std::endl;
		else if (unit.type == ParseUnitType::COMMAND)
			result << "CMD\t" << unit.command_payload.str() << std::endl;
		else 
			result << "UNASSIGNED" << std::endl;
	}

	return result.str();
}

int main() {
	std::string commands_0[0] = {};
	std::string commands_1[3] = {"a", "bc", "def"};
	std::string command_bold[1] = {"bold"};

	return
		assert_strings_equal(
		"TXT\tHello world!\n",
		parse_to_units("Hello world!", {})) ||
		assert_strings_equal(
		"CMD\t/a.\n"
		"CMD\t/b.\n"
		"CMD\t/c.\n",
		parse_to_units("/a./b./c.", {})) ||
		assert_strings_equal(
		"TXT\tall\n"
		"CMD\t/abba{abba}<abba>.\n"
		"TXT\tpraise the sun\n",
		parse_to_units("all/abba{abba}<abba>.praise the sun", {})) ||
		assert_strings_equal(
		"CMD\t/a.\n",
		parse_to_units("/a.", {"a"})) ||
		assert_strings_equal(
		"TXT\tHello\n"
		"CMD\t/a.\n"
		"TXT\tworld!\n",
		parse_to_units("Hello/a.world!", {"a", "bc"})) ||
		assert_strings_equal(
		"CMD\t/a.\n"
		"CMD\t/a.\n"
		"CMD\t/a.\n"
		"CMD\t/a.\n"
		"CMD\t/a.\n",
		parse_to_units("/a./a./a./a./a.", {"a", "bc", "list"})) ||
		assert_strings_equal(
		"CMD\t/a{HELL}.\n",
		parse_to_units("/a{HELL}.", {"a"})) ||
		assert_strings_equal(
		"CMD\t/def{HEAVEN}{cloud nine}.\n",
		parse_to_units("/def{HEAVEN}{cloud nine}.", {"def"})) ||
		assert_strings_equal(
		"CMD\t/a{1}{2}.\n"
		"CMD\t/bc{1}{2}{瑞本很有趣}.\n",
		parse_to_units("/a{1}{2}./bc{1}{2}{瑞本很有趣}.", {"a", "bc"})) ||
		assert_strings_equal(
		"TXT\t你好\n"
		"CMD\t/bold{波兰}.\n"
		"TXT\t!\n",
		parse_to_units("你好/bold{波兰}.!", {"bold"})) ||
		assert_strings_equal(
		"CMD\t/banner{comic-sans}<后记!>.\n",
		parse_to_units("/banner{comic-sans}<后记!>.", {"banner"})) ||
		assert_strings_equal(
		"TXT\tEntonces \n"
		"CMD\t/bold<todo>.\n"
		"CMD\t/banner{nya-font}</paint{pink}< está >.>.\n"
		"TXT\t \n"
		"CMD\t/glow<bien>.\n"
		"TXT\t.\n",
		parse_to_units("Entonces /bold<todo>./banner{nya-font}</paint{pink}< está >.>. /glow<bien>..", {"banner", "bold", "paint", "glow"})) ||
		0;
}
