#include <IO/formatters/BannerFormatter.hpp>

#include <sstream>
#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>

const char* BannerFormatter::get_name() {
	return "BannerFormatter";
}

std::string BannerFormatter::get_nth_line(const BannerCharacter& character, std::string::size_type line) {
	const std::string font_face = character.character_lines;
	
	std::istringstream font_face_stream{font_face};

	std::string result;
	std::string::size_type iteration = 0;
	do {
		std::getline(font_face_stream, result);
		iteration++;
	} while (iteration <= line);
	
	return result;
}

std::string BannerFormatter::execute_command(Command command) {
	if (command.arguments.size() < 2) {
		std::cerr << get_name() << " Bad number of arguments (<1)" << std::endl;
		return std::string("\n") + get_name() + " ERROR\n"; // Ladies and gentlemen! Behold! Beautiful code!
	}

	for (const Argument& argument : command.arguments) {
		if (argument.type != ArgumentType::OPTION) {
			std::cerr << get_name() << " argument is not an option!" << std::endl;
			return command.str();
		}
	}

	std::string font_name = command.arguments[0].payload;
	if (fonts.contains(font_name) == false && load_font_from_file(font_name) == false) {
		std::cerr << get_name() << " " << font_name << " font does not exist" << std::endl;
		return command.str();
	}

	BannerFont& font = fonts[font_name];


	std::ostringstream result_stream;

	std::vector<Argument>::iterator files_iterator = command.arguments.begin() + 1;
	for (; files_iterator != command.arguments.end(); ++files_iterator) {
		for (std::string::size_type line = 0; line < font.character_height; ++line) {
			std::string::const_iterator file_iterator = files_iterator->payload.cbegin();

			while (file_iterator != files_iterator->payload.cend()) {
				BannerCharacter character = font.get_char(file_iterator, files_iterator->payload.cend());
				if (character.character_lines == "Error") {
					return command.str();
				}
				result_stream << get_nth_line(character, line);

				if (file_iterator != files_iterator->payload.cend()) {
					result_stream << std::string(font.intercharacter_space_width, ' ');
				}

			}
			result_stream << std::endl;
		}
	}

	return result_stream.str();
}

const std::vector<std::string>& BannerFormatter::get_command_names() {
	static const std::vector<std::string> command{"banner"};
	return command;
}

bool BannerFormatter::load_font_from_file(std::string file_name) {
	if (fonts.contains(file_name) == true) {
		std::cerr << get_name() << " " << file_name << " has already been loaded" << std::endl;
		return false;
	}

	static const std::string font_directory{"fonts"};
	std::filesystem::path font_path = std::filesystem::path(FONTS_DIRECTORY_PARENT) / font_directory / file_name;
	std::ifstream font_stream(font_path);

	if (font_stream.good() == false) {
		std::cerr << get_name() << " " << font_path << " font couldn't be found" << std::endl;
		return false;
	}

	BannerFont new_font;

	try {
		BannerCharacter space;
		font_stream >> new_font.character_height >> space.width >> new_font.intercharacter_space_width;
		
		for (std::string::size_type i = 0; i < new_font.character_height; i++)
			space.character_lines += std::string(space.width, ' ') + '\n';

		new_font.character_dictionary[" "] = space;

		while (font_stream.eof() == false) {
			std::string character_key;
			BannerCharacter new_character;

			font_stream >> character_key;
			font_stream >> new_character.width;
			font_stream.ignore(100, '\n');

			for (std::string::size_type i = 0; i < new_font.character_height; i++) {
				std::string new_line;
				std::getline(font_stream, new_line);

				new_character.character_lines += new_line + '\n';
			}

			if (new_font.character_dictionary.contains(character_key) == true) {
				std::clog << get_name() << " Reduplication of the key \"" << character_key << std::endl;
			}

			new_font.character_dictionary[character_key] = new_character;
		}

	}
	catch (std::exception& exception) {
		std::cerr << get_name() << " " << font_path << " error while reading the file" << std::endl;
		std::cerr << exception.what() << std::endl;
		return false;
	}

	fonts[file_name] = new_font;
	return true;
}

BannerFormatter::BannerCharacter BannerFormatter::BannerFont::get_char(std::string::const_iterator& beginning, std::string::const_iterator end) {
	std::string::const_iterator sub_match_end = beginning + 1;
	std::string matched_key = "";
	while(sub_match_end != end) {
		matched_key = std::string(beginning, sub_match_end);
		if (character_dictionary.contains(matched_key) == true) {
			beginning = sub_match_end;
			return character_dictionary[matched_key];
		}
		++sub_match_end;
	}

	matched_key = std::string(beginning, end);
	if (character_dictionary.contains(matched_key) == true) {
		beginning = end;
		return character_dictionary[matched_key];
	}
	
	std::cerr << "BannerFont" << " couldn't match any key to: ";
	std::cerr << matched_key << std::endl;

	BannerCharacter error;
	error.character_lines = "Error";
	return error;
}
