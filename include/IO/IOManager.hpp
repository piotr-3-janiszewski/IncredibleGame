#pragma once

#include <IO/IOEnvironment.hpp>
#include <IO/FormatterDecorator.hpp>

class IOManager {
	FormatterDecorator* formatter_decorators;
	IOEnvironment* ioenvironment;
public:
	IOManager();

	static IOManager& access_singleton();
	IOManager(const IOManager&) = delete;
	IOManager& operator=(const IOManager&) = delete;
	
	int read_choice();
	void format_and_print(std::string message);
	std::string::size_type get_width();
};
