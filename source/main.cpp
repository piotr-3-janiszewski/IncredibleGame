#include <iostream>
#include <IO/IOManager.hpp>

int main() {
	IOManager& io = IOManager::access_singleton(); 
	io.format_and_print("Formatted message/slash.");
	std::cout << "Hewo word" << std::endl;
}
