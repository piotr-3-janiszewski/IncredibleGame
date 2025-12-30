#pragma once

#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>
#include <unordered_map>

// Usage:
// /banner{banner_file_name}{line_1}{line_2}...{line_nth}.
//
// Banner font file begins with two numbers separated with a
// space. The first one specifies the character_height,
// the second specifies the space width.
// Then a sequence of new line separated character blocks
// should follow. A character block begins with a key, which is 
// just a string of characters to replace with one banner
// character. Below in precisely character_height lines
// of the ASCII-art banner for that key..
class BannerFormatter :public ParsingFormatterTemplate {
	struct BannerCharacter {
		std::string::size_type width;
		std::string character_lines{};
	};

	struct BannerFont {
		std::string::size_type character_height;
		std::string::size_type intercharacter_space_width;
		std::unordered_map<std::string, BannerCharacter> character_dictionary{};

		BannerCharacter get_char(std::string::const_iterator& beginning, std::string::const_iterator end);
	};

	std::unordered_map<std::string, BannerFont> fonts;
	std::string get_nth_line(const BannerCharacter& character, std::string::size_type line);
protected:
	const std::vector<std::string>& get_command_names() override;
	std::string execute_command(Command command) override;
public:
	const char* get_name() override;

	bool load_font_from_file(std::string file_name);
};
