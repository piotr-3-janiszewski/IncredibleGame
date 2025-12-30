#include <IO/formatters/CardFormatter.hpp>

#include <sstream>
#include <iostream>
#include <regex>

const char* CardFormatter::get_name() {
	return "CardFormatter";
}

std::string CardFormatter::get_nth_line(const char* text, int line) {
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

std::string CardFormatter::execute_command(Command command) {
	if (command.arguments.size() < 1) {
		std::cerr << get_name() << " Bad number of arguments (<1)" << std::endl;
		return std::string("\n") + get_name() + " ERROR\n"; // Ladies and gentlemen! Behold! Beautiful code!
	}

	for (const Argument& argument : command.arguments) {
		if (argument.type != ArgumentType::OPTION) {
			std::cerr << get_name() << " argument is not an option!" << std::endl;
			return std::string("\n") + get_name() + " ERROR\n" ;
		}
	}

	std::string::size_type lines_in_one_art = 0;
	{
		std::string example_specimen = get_card_art('2', 'S');
		for (const char* iterator = example_specimen.c_str(); *iterator != '\0'; iterator++)
			if (*iterator == '\n')
				lines_in_one_art++;
	}

	std::ostringstream result_stream;

	std::vector<std::pair<char, char>> cards;
	for (const  Argument& argument : command.arguments) {
		if (argument.payload.size() != 2) {
			std::cerr << get_name() << " Bad option, in:" << std::endl;
			std::cerr << command.str() << std::endl;
			return command.str();
		}
	
		cards.push_back(std::pair<char, char>{argument.payload[0], argument.payload[1]});
	}

	for (std::string::size_type line = 0; line < lines_in_one_art; line++) {
		for (std::pair<char, char> card_encoding: cards) {
			std::string card = get_card_art(card_encoding.first, card_encoding.second);
			if (card == "Error") {
				return command.str();
			}
			result_stream << std::string(get_nth_line(card.c_str(), line)); // types technically don't match here, but blazes if I care!
		}
		result_stream << std::endl;
	}

	return result_stream.str();
}

const std::vector<std::string>& CardFormatter::get_command_names() {
	static const std::vector<std::string> command{"hand"};
	return command;
}

std::string CardFormatter::get_card_art(char card_type, char suit) {
	static const char* aces[] = {
		"┌oA♠c ───────┐\n"
		"│o    ▗▖   c │\n"
		"│o  ▗▟██▙▖ c │\n"
		"│o ▗██████▖c │\n"
		"│o ████████c │\n"
		"│o ▝▀▘▟▙▝▀▘c │\n"
		"│o   ▟██▙  c │\n"
		"│o         c │\n"
		"└───────o♠ Ac┘\n",
		"┌oA♣c ───────┐\n"
		"│o    ▄▄   c │\n"
		"│o   ▟██▙  c │\n"
		"│o ▗▄▝██▘▄▖c │\n"
		"│o ████████c │\n"
		"│o ▝▀▘▟▙▝▀▘c │\n"
		"│o   ▟██▙  c │\n"
		"│o         c │\n"
		"└───────o♣ Ac┘\n",
		"┌oA♦c ───────┐\n"
		"│o    ▟▙   c │\n"
		"│o   ▟██▙  c │\n"
		"│o  ▟████▙ c │\n"
		"│o ▝██████▘c │\n"
		"│o  ▝████▘ c │\n"
		"│o   ▝██▘  c │\n"
		"│o    ▝▘   c │\n"
		"└───────o♦ Ac┘\n",
		"┌oA♥ c───────┐\n"
		"│o         c │\n"
		"│o ▗██▖▗██▖c │\n"
		"│o ████████c │\n"
		"│o ▝██████▘c │\n"
		"│o  ▝████▘ c │\n"
		"│o   ▝██▘  c │\n"
		"│o    ▝▘   c │\n"
		"└───────o♥ Ac┘\n",
	};

	static const char* two_to_king[] = {
		"┌o2♠c ───────┐\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"│o         c │\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"└───────o♠ 2c┘\n",
		"┌o3♠c ───────┐\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"└───────o♠ 3c┘\n",
		"┌o4♠c ───────┐\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"│o         c │\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"└───────o♠ 4c┘\n",
		"┌o5♠c ───────┐\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"│o    ♠    c │\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"└───────o♠ 5c┘\n",
		"┌o6♠c ───────┐\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"│o  ♠   ♠  c │\n"
		"│o         c │\n"
		"└───────o♠ 6c┘\n",
		"┌o7♠c ───────┐\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"└───────o♠ 7c┘\n",
		"┌o8♠c ───────┐\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"└───────o♠ 8c┘\n",
		"┌o9♠c ───────┐\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"└───────o♠ 9c┘\n",
		"┌o10♠c ──────┐\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"│o         c │\n"
		"│o ♠     ♠ c │\n"
		"│o    ♠    c │\n"
		"│o ♠     ♠ c │\n"
		"└──────o♠ 10c┘\n",
		"┌oJ♠c ───────┐\n"
		"│o 手▀▀-‡▗▖ c│\n"
		"│o | ╲_[:)] c│\n"
		"│o ╲   | || c│\n"
		"│o  /----/  c│\n"
		"│o ||    ╲  c│\n"
		"│o [(:]‾╲ | c│\n"
		"│o  ▝▘‡▄▄手 c│\n"
		"└───────o♠ Jc┘\n",
		"┌oQ♠c ───────┐\n"
		"│o ⚘     Ш  c│\n"
		"│o | ╲_ :3  c│\n"
		"│o ╲   | || c│\n"
		"│o  /----/  c│\n"
		"│o ||    ╲  c│\n"
		"│o  ℇ:‾‾╲ | c│\n"
		"│o  W    ⚘  c│\n"
		"└───────o♠ Qc┘\n",
		"┌oK♠ c───────┐\n"
		"│o ♠    Ш   c│\n"
		"│o II__ :[  c│\n"
		"│o ╲   | || c│\n"
		"│o  /----/  c│\n"
		"│o ||    ╲  c│\n"
		"│o  ]: ‾‾II c│\n"
		"│o  W    ♠  c│\n"
		"└───────o♠ Kc┘\n",

	};

	std::string card;
	
	if (card_type == 'A') {
		if (suit == 'S' || suit == 's')
			card = aces[0];
		else if (suit == 'C' || suit == 'c')
			card = aces[1];
		else if (suit == 'D' || suit == 'd')
			card = aces[2];
		else if (suit == 'H' || suit == 'h')
			card = aces[3];
	}
	else {
		static char figures[] = "234567890JQK";

		int i = 0;
		while (figures[i] != '\0' && figures[i] != card_type) {i++;}

		if (figures[i] == '\0') {
			std::cerr << get_name() << " " << card_type << " has not been found" << std::endl;
			return "Error";
		}
			

		card = two_to_king[i];
	}

	std::string suit_symbol;
	std::string color;

	if (suit == 'S' || suit == 's') {
		suit_symbol = "♠";
		color = "black";
	}
	else if (suit == 'C' || suit == 'c') {
		suit_symbol = "♣";
		color = "black";
	}
	else if (suit == 'D' || suit == 'd') {
		suit_symbol = "♦";
		color = "red";
	}
	else if (suit == 'H' || suit == 'h') {
		suit_symbol = "♥";
		color = "red";
	}
	else {
		std::cerr << get_name() << " " << suit << " has not been found" << std::endl;
		return "Error";
	}

	card = std::regex_replace(card, std::regex{"♠"}, suit_symbol);
	std::string open_instruction = "/paint{" + color + "}<";
	card = std::regex_replace(card, std::regex{"c"}, ">.");
	card = std::regex_replace(card, std::regex{"o"}, open_instruction);
	card = std::regex_replace(card, std::regex{"^"}, "/paint{bg-white}{grey}<");
	card = std::regex_replace(card, std::regex{"\n"}, ">.\n/paint{bg-white}{grey}<");
	card = std::regex_replace(card, std::regex{"$"}, ">.");

	return card;
}
