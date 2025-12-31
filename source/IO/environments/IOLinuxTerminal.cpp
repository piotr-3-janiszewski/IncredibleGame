#include <IO/environments/IOLinuxTerminal.hpp>
#include <IO/formatters/parser/CommandParser.hpp>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <cstdio>

std::string IOLinuxTerminal::begin_escape(std::vector<int> codes) {
	std::string result;

	if (codes.size() == 0)
		result =  "";
	else {
		std::ostringstream result_stream;
		bool first = true;
		result_stream << "\033[";

		for (int code : codes) {
			if (!first) {
				result_stream << ';';
			}
			result_stream << code;
			first = false;
		}

		result_stream << "m";

		result = result_stream.str();
	}

	escape_codes_history.push_back(result);
	return result;
}

std::string IOLinuxTerminal::end_escape() {
	if (escape_codes_history.empty())
		std::cerr << "Catastrophic error" << std::endl;
	
	escape_codes_history.pop_back();

	std::ostringstream result_stream;

	result_stream << "\033[0m";
	
	if (escape_codes_history.empty() == false)
		result_stream << escape_codes_history.back();
	
	return result_stream.str();
}

std::string IOLinuxTerminal::run_paint_command(Command command) {
	static std::unordered_map<std::string, int> name_to_escape {
		{"normal", 0},
		{"bold", 1},

		{"faint", 2},
		{"dim", 2},

		{"italic", 3},
		{"underline", 4},

		{"slow-blink", 5},
		{"blink", 5},

		{"fast-blink", 6},
		{"Blink", 6},
		{"blnk", 6},

		{"invert", 7},
		{"reverse", 7},

		//{"hide", 8}, // This one should have no use

		{"cross-out", 9},
		{"strike", 9},

		{"font0", 10},
		{"normal-font", 10},
		{"font1", 11},
		{"font2", 12},
		{"font3", 13},
		{"font4", 14},
		{"font5", 15},
		{"font6", 16},
		{"font7", 17},
		{"font8", 18},
		{"font9", 19},
		{"font10", 20}, // Apparently rarely supported
		
		{"double-underline", 21},

		// some turn off sequences

		{"black", 30},
		{"red", 31},
		{"green", 32},
		{"yellow", 33},
		{"blue", 34},
		{"magenta", 35},
		{"cyan", 36},
		{"white", 37},
		{"bright-black", 90},
		{"grey", 90},
		{"bright-red", 91},
		{"bright-green", 92},
		{"bright-yellow", 93},
		{"bright-blue", 94},
		{"bright-magenta", 95},
		{"bright-cyan", 96},
		{"bright-white", 97},

		{"bg-black", 40},
		{"bg-red", 41},
		{"bg-green", 42},
		{"bg-yellow", 44},
		{"bg-blue", 44},
		{"bg-magenta", 45},
		{"bg-cyan", 46},
		{"bg-white", 47},
		{"bg-bright-black", 100},
		{"bg-grey", 100},
		{"bg-bright-red", 101},
		{"bg-bright-green", 102},
		{"bg-bright-yellow", 103},
		{"bg-bright-blue", 104},
		{"bg-bright-magenta", 105},
		{"bg-bright-cyan", 106},
		{"bg-bright-white", 107},
	};
	
	std::vector<int> codes;
	std::string code_to_paint = "";
	bool found_code_to_paint = false;

	for (Argument& argument : command.arguments) {
		if (argument.type == ArgumentType::OPTION) {
			std::string escape_name = argument.payload;
			if (name_to_escape.contains(escape_name))
				codes.push_back(name_to_escape[escape_name]);
			else 
				std::cerr << get_name() << " There is no such escape code name as: " << escape_name << std::endl;
		}
		else if (argument.type == ArgumentType::CODE) {
			if (found_code_to_paint)
				std::cerr << get_name() << " Found more then one code argument in " << command.str() << std::endl;

			found_code_to_paint = true;
			code_to_paint += argument.payload;
		}
	}

	// I can't just write the sum of these functions normally, because
	// apparently they may get invoked in any order whatsoever!
	std::string beginning = begin_escape(codes);
	std::string middle = paint_text(code_to_paint);
	std::string end = end_escape();
	return beginning + middle + end;
}

std::string IOLinuxTerminal::paint_text(std::string message) {

	std::vector<ParseUnit> units = CommandParser::parse_to_units(message, {"paint"});
	std::ostringstream result_stream;

	for (ParseUnit& unit : units) {
		if (unit.type == ParseUnitType::PLAINTEXT)
			result_stream << unit.plaintext_payload;
		else if (unit.type == ParseUnitType::COMMAND) {
			Command command = unit.command_payload;
			result_stream << run_paint_command(command);
		}
	}

	return result_stream.str();
}

void IOLinuxTerminal::print_formatted(std::string message) {
	std::cout << paint_text(message);
}

char IOLinuxTerminal::read_choice() {
	char result;
	std::cin >> result;
	return result;
}

void IOLinuxTerminal::wait() {
	char garbage;
	system("stty -icanon icrnl");
	std::cin.get(garbage);
	system("stty cooked");
}

const char* IOLinuxTerminal::get_name() {
	return "Linux terminal environment";
}

std::string::size_type IOLinuxTerminal::get_width() {
	return 80;
}
