#include <IO/formatters/BoxFormatter.hpp>
#include <utils/UTF_8_utils.hpp>
#include <IO/IOManager.hpp>

#include <iostream>
#include <unordered_map>
#include <array>
#include <sstream>

const char* BoxFormatter::get_name() {
	return "BoxFormatter";
}

const std::vector<std::string>& BoxFormatter::get_command_names() {
	static const std::vector<std::string> command{"box"};
	return command;
}

std::string BoxFormatter::execute_command(Command command) {
	enum class BoxType {NORMAL, DOUBLE_DASH, TRIPLE_DASH, DOTS, DOUBLE, CROSS, FUNKY};
	enum class BoxThickness {LIGHT, HEAVY};
	enum class BoxPosition {LEFT, CENTER, RIGHT, JUSTIFY};
	enum class TextPosition {LEFT, CENTER, RIGHT};

	BoxType box_type = BoxType::NORMAL;
	BoxThickness box_thickness = BoxThickness::LIGHT;
	BoxPosition box_position = BoxPosition::CENTER;
	TextPosition text_position = TextPosition::CENTER;
	std::string::size_type desired_width = 0;
	std::vector<std::string> lines{};

	bool one_code_argument = false;
	for (const Argument& argument : command.arguments)
		if (argument.type == ArgumentType::CODE) {
			one_code_argument = true;
			lines.push_back(argument.payload);
		}
	
	if (!one_code_argument) {
		std::cerr << get_name() << "No code arguments!" << std::endl;
		return std::string(get_name()) + " ERROR\n";
	}

	int option_counter = 0;

	std::string begin_border_modifiers;
	std::string end_border_modifiers;

	for (const Argument& argument : command.arguments) {
		if (argument.type != ArgumentType::OPTION)
			continue;

		if (option_counter == 0) {
			option_counter++;
			static const std::unordered_map<std::string, BoxType> to_enum{
				{"normal", BoxType::NORMAL},
				{"double-dash", BoxType::DOUBLE_DASH},
				{"triple-dash", BoxType::TRIPLE_DASH},
				{"dots", BoxType::DOTS},
				{"double", BoxType::DOUBLE},
				{"cross", BoxType::CROSS},
				{"funky", BoxType::FUNKY}
			};

	 		if (!to_enum.contains(argument.payload)) {
				std::clog << get_name() << " improper box type" << std::endl;
				continue;
			}

			box_type = to_enum.at(argument.payload);

		}
		else if (option_counter == 1) {
			option_counter++;
			static const std::unordered_map<std::string, BoxThickness> to_enum{
				{"light", BoxThickness::LIGHT},
				{"heavy", BoxThickness::HEAVY}

			};

	 		if (!to_enum.contains(argument.payload)) {
				std::clog << get_name() << " improper thickness" << std::endl;
				continue;
			}

			box_thickness = to_enum.at(argument.payload);
		}
		else if (option_counter == 2) {
			option_counter++;
			static const std::unordered_map<std::string, BoxPosition> to_enum{
				{"left", BoxPosition::LEFT},
				{"center", BoxPosition::CENTER},
				{"right", BoxPosition::RIGHT},
				{"justify", BoxPosition::JUSTIFY}
			};

	 		if (!to_enum.contains(argument.payload)) {
				std::clog << get_name() << " improper box position" << std::endl;
				continue;
			}

			box_position = to_enum.at(argument.payload);
		}
		else if (option_counter == 3) {
			option_counter++;
			static const std::unordered_map<std::string, TextPosition> to_enum{
				{"left", TextPosition::LEFT},
				{"center", TextPosition::CENTER},
				{"right", TextPosition::RIGHT},
			};

	 		if (!to_enum.contains(argument.payload)) {
				std::clog << get_name() << " improper text position" << std::endl;
				continue;
			}

			text_position = to_enum.at(argument.payload);
		}
		else if (option_counter == 4) {
			option_counter++;

			desired_width = static_cast<std::string::size_type>(std::stoi(argument.payload));
		}
		else {
			begin_border_modifiers += argument.payload + "<";
			end_border_modifiers += ">.";
		}
	}

	// 0. upper_left, 1. up, 2. upper_right, 3. left, 4. right, 5. bottom_left, 6. bottom, 7. bottom_right
	using Borders = std::vector<std::string>;
	Borders borders;

	if (box_type == BoxType::NORMAL && box_thickness == BoxThickness::LIGHT)
		borders = {"┌─","─", "─┐", "│ ", " │", "└─", "─", "─┘"};
	else if (box_type == BoxType::NORMAL && box_thickness == BoxThickness::HEAVY)
		borders = {"┏━","━", "━┓", "┃ ", " ┃", "┗━", "━", "━┛"};
	else if (box_type == BoxType::DOUBLE_DASH && box_thickness == BoxThickness::LIGHT)
		borders = {"  ","╌", "  ", "╎ ", " ╎", "  ", "╌", "  "};
	else if (box_type == BoxType::DOUBLE_DASH && box_thickness == BoxThickness::HEAVY)
		borders = {"  ","╍", "  ", "╏ ", " ╏", "  ", "╍", "  "};
	else if (box_type == BoxType::TRIPLE_DASH && box_thickness == BoxThickness::LIGHT)
		borders = {"  ","┄", "  ", "┆ ", " ┆", "  ", "┄", "  "};
	else if (box_type == BoxType::TRIPLE_DASH && box_thickness == BoxThickness::HEAVY)
		borders = {"  ","┅", "  ", "┇ ", " ┇", "  ", "┅", "  "};
	else if (box_type == BoxType::DOTS && box_thickness == BoxThickness::LIGHT)
		borders = {"  ","┈", "  ", "┊ ", " ┊", "  ", "┈", "  "};
	else if (box_type == BoxType::DOTS && box_thickness == BoxThickness::HEAVY)
		borders = {"  ","┉", "  ", "┋ ", " ┋", "  ", "┉", "  "};
	else if (box_type == BoxType::DOUBLE)
		borders = {"╔═","═", "═╗", "║ ", " ║", "╚═", "═", "═╝"};
	else if (box_type == BoxType::FUNKY)
		borders = {"╽╼╾"," ", "╼╾╽", "┃  ", "  ┃", "╿╼╾", " ", "╼╾╿"};
	else if (box_type == BoxType::CROSS && box_thickness == BoxThickness::LIGHT)
		borders = {"┼─","─", "─┼", "│ ", " │", "┼─", "─", "─┼"};
	else if (box_type == BoxType::CROSS && box_thickness == BoxThickness::HEAVY)
		borders = {"╋━","━", "━╋", "┃ ", " ┃", "╋━", "━", "━╋"};

	std::string::size_type border_width = 0;
	for (const std::string& border : borders) {
		std::string::size_type current_border_width = count_code_points(border);
		if (current_border_width > border_width)
			border_width = current_border_width;
	}

	std::string::size_type max_line_width = 0;
	for (const std::string& line : lines) {
		std::string::size_type current_line_width = count_code_points(line);
		if (current_line_width > max_line_width)
			max_line_width = current_line_width;
	}

	std::string::size_type box_width = 2 * border_width + max_line_width;
		
	if (box_position == BoxPosition::JUSTIFY)
		box_width = IOManager::access_singleton().get_width();
	else if (desired_width > box_width)
		box_width = desired_width;

	std::string::size_type box_inside_width = box_width - 2 * border_width;
	
	if (box_width > IOManager::access_singleton().get_width())
		std::clog << get_name() << " line too long for the environment" << std::endl;

	std::string::size_type margin_left_length = 0;

	if (box_width >= IOManager::access_singleton().get_width()) {

	}
	else if (box_position == BoxPosition::CENTER)
		margin_left_length = (IOManager::access_singleton().get_width() - box_width + 1) / 2;
	else if (box_position == BoxPosition::RIGHT)
		margin_left_length = IOManager::access_singleton().get_width() - box_width;

	std::string margin(margin_left_length, ' ');
	
	std::ostringstream result_stream;
	result_stream << margin << begin_border_modifiers << borders[0];
	for (std::string::size_type i = 0; i < box_inside_width; i++)
		result_stream << borders[1];
	result_stream << borders[2] << end_border_modifiers << std::endl;
	for (const std::string& line : lines) {
		result_stream << margin << begin_border_modifiers << borders[3] << end_border_modifiers;

		std::string::size_type line_length = count_code_points(line);
		std::string::size_type spaces = box_inside_width - line_length;

		if (text_position == TextPosition::LEFT) {
			result_stream << line << std::string(spaces, ' ');
		}
		else if (text_position == TextPosition::CENTER) {
			result_stream << std::string(spaces / 2, ' ') << line << std::string((spaces + 1) / 2, ' ');
		}
		else {
			result_stream << std::string(spaces, ' ') << line;
		}

		result_stream << begin_border_modifiers << borders[4] << end_border_modifiers << std::endl;
	}
	result_stream << margin << begin_border_modifiers << borders[5];
	for (std::string::size_type i = 0; i < box_inside_width; i++)
		result_stream << borders[6];
	result_stream << borders[7] << end_border_modifiers << std::endl;

	return result_stream.str();
}
