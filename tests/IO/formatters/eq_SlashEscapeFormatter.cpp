#include <IO/formatters/SlashEscapeFormatter.hpp>
#include <iostream>

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		std::cout << "Bad test: incorrect number of arguments" << std::endl;
		return 1;
	}

	std::string input{argv[1]};
	std::string correct_output{argv[2]};

	SlashEscapeFormatter slashEscapeFormatter{};

	std::string output = slashEscapeFormatter.format(input);
	if (output == correct_output)
		return 0;

	std::cout << "Incorrect output, got:\n" << output << "\nShould be:" << correct_output << std::endl;
	
	return -1;
}
