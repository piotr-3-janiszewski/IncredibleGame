#pragma once
#include <IO/IOEnvironment.hpp>

class IOLinuxTerminal :public IOEnvironment {
public:
	void print_formatted(std::string message) override;
	char read_choice() override;
	const char* get_name() override;
};
