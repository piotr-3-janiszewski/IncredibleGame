#include <IO/formatters/DiceFormatter.hpp>

#include <sstream>
#include <iostream>

const char* DiceFormatter::get_name() {
	return "DiceFormatter";
}

std::string get_nth_line(const char* text, int line) {
	const char* iterator = text;
	for (int i = 0; i < line; i++) {
		while (*iterator != '\n')
			iterator++;
		iterator++;
	}

	const char* end = iterator;
	while (*end != '\n')
		end++;
	
	return std::string(iterator, end);
}

std::string DiceFormatter::execute_command(Command command) {
	if (command.arguments.size() < 2) {
		std::cerr << get_name() << " Bad number of arguments (<2)" << std::endl;
		return std::string("\n") + get_name() + " ERROR\n"; // Ladies and gentlemen! Behold! Beautiful code!
	}

	for (const Argument& argument : command.arguments) {
		if (argument.type != ArgumentType::OPTION) {
			std::cerr << get_name() << " argument is not an option!" << std::endl;
			return std::string("\n") + get_name() + " ERROR\n" ;
		}
	}

	std::string dice_type = command.arguments[0].payload;

	if (
	  dice_type != "d4" &&
	  dice_type != "d6" &&
	  dice_type != "d8" &&
	  dice_type != "d10" &&
	  dice_type != "d12" &&
	  dice_type != "d20"
	) {
		std::cerr << dice_type << " is not a proper dice type!" << std::endl;
		return std::string(get_name()) + "error";
	}

	std::string::size_type lines_in_one_art = 0;
	for (const char* iterator = get_dice_art(dice_type, 1); *iterator != '\0'; iterator++)
		if (*iterator == '\n')
			lines_in_one_art++;

	std::ostringstream result_stream;

	std::vector<int> rolls;
	for (decltype(command.arguments.size()) i = 1; i < command.arguments.size(); i++)
		rolls.push_back(std::stoi(command.arguments[i].payload));

	for (std::string::size_type line = 0; line < lines_in_one_art; line++) {
		for (int roll : rolls)
			result_stream << std::string(get_nth_line(get_dice_art(dice_type, roll), line)); // types technically don't match here, but blazes if I care!
		result_stream << std::endl;
	}

	return result_stream.str();
}

const std::vector<std::string>& DiceFormatter::get_command_names() {
	static const std::vector<std::string> command{"roll"};
	return command;
}

const char* DiceFormatter::get_dice_art(std::string dice_type, int result) {
	static const char* d4_art[] = {
		"   ʌ    \n"
		"  ╱1╲   \n"
		" ╱   ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱2╲   \n"
		" ╱   ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱3╲   \n"
		" ╱   ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱4╲   \n"
		" ╱   ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n"
	};
	static const char* d6_art[] = {
		"┌─────┐\n"
		"│     │\n"
		"│     │\n"
		"│     │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│     │\n"
		"│  O  │\n"
		"│     │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│   O │\n"
		"│     │\n"
		"│ O   │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│   O │\n"
		"│  O  │\n"
		"│ O   │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│ O O │\n"
		"│     │\n"
		"│ O O │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│ O O │\n"
		"│  O  │\n"
		"│ O O │\n"
		"└─────┘\n",
		"┌─────┐\n"
		"│ O O │\n"
		"│ O O │\n"
		"│ O O │\n"
		"└─────┘\n"
	};
	static const char* d8_art[] = {
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 0 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 1 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 2 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 3 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 4 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 5 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 6 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 7 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 8 ╲  \n"
		"╱     ╲ \n"
		"▀█████▀ \n"
		"  ▀█▀   \n"
	};
	static const char* d10_art[] {
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 0 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 1 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 2 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 3 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 4 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 5 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 6 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 7 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 8 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 9 ╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 0╲  \n"
		"╱     ╲ \n"
		" ─   ─  \n"
		"   ▔    \n"
	};

	static const char* d12_art[] {
		"  ___   \n"
		" /   \\ \n"
		"/  0  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  1  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  2  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  3  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  4  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  5  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  6  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  7  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  8  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/  9  \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/ 1 0 \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/ 1 1 \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
		"  ___  \n"
		" /   \\ \n"
		"/ 1 2 \\\n"
		"\\     /\n"
		" \\   / \n"
		"  ▔▔▔  \n",
	};

	static const char* d20_art[] = {
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 0 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 1 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 2 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 3 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 4 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 5 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 6 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 7 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 8 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱ 9 ╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 0╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 1╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 2╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 3╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 4╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 5╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 6╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 7╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 8╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱1 9╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
		"   ʌ    \n"
		"  ╱ ╲   \n"
		" ╱2 0╲  \n"
		"╱     ╲ \n"
		"▔▔▔▔▔▔▔ \n",
	};

	if (dice_type == "d4")
		return d4_art[result];
	else if (dice_type == "d6")
		return d6_art[result];
	else if (dice_type == "d8")
		return d8_art[result];
	else if (dice_type == "d10")
		return d10_art[result];
	else if (dice_type == "d12")
		return d12_art[result];
	else if (dice_type == "d20")
		return d20_art[result];
	
	return "No dice! ;)";
}
