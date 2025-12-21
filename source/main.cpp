#include <iostream>
#include <IO/IOManager.hpp>

int main() {
	IOManager& io = IOManager::access_singleton(); 
	std::cout << "Hewo word" << std::endl;
}
