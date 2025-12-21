#include <IO/environments/IOLinuxTerminal.hpp>
#include <iostream>

void IOLinuxTerminal::print_formatted(std::string message) {
	std::cout << message << std::endl;
}

char IOLinuxTerminal::read_choice() {
	char result;
	std::cin >> result;
	return result;
}

const char* IOLinuxTerminal::get_name() {
	return "Linux terminal environment";
}
