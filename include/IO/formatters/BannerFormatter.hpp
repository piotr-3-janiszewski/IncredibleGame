#pragma once

#include <IO/FormatterDecorator.hpp>

class BannerFormatter :public FormatterDecorator {
	int terminal_width = 80;
	int character_height = -1;
	int space_width = 3;
	std::map<std::string, std::string*> banners
public:
	const char* get_name() override;
	std::string in_template_format(std::string message) override;

	// Banner font file begins with two numbers separated with a
	// space. The first one specifies the character_height,
	// the second specifies the space width.
	// Then a sequence of new line separated character blocks
	// should follow. A character block begins with a key, which is 
	// just a string of characters to replace with one banner
	// character. Below in precisely character_height lines
	// put the ASCII-art banner for that key..
	void read_font_from_file(std::string file_name);
	BannerFormatter(std::string file_name);
}
