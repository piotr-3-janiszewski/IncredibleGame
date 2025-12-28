#pragma once

#include <string>

class IOEnvironment {
public:
	virtual void print_formatted(std::string message) = 0;
	virtual char read_choice() = 0;
	virtual void wait() = 0;
	virtual const char* get_name() = 0;
	virtual std::string::size_type get_width() = 0;
};
