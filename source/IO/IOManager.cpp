#include <IO/IOManager.hpp>
#include <IO/FormatterDecoratorConfigurator.hpp>
#include <iostream>

#ifdef __linux__
#include <IO/environments/IOLinuxTerminal.hpp>
#else
#error "Unsupported OS, in case you wish to enforce compilation, you may chose to define one of the following environment variables:\n * __linux__"
#endif

IOManager::IOManager() {
	FormatterDecoratorConfigurator configurator{};
	formatter_decorators = configurator.get_decorator_chain();

#ifdef __linux__
	ioenvironment = new IOLinuxTerminal();
#else
#error "OS declared as supported is unimplemented"
#endif

	std::clog << "Using " <<  ioenvironment->get_name() << std::endl;
	std::clog << "Current formatter chain:" << std::endl;

	if (formatter_decorators == nullptr) {
		std::cerr << "Error! Formatter chain empty!" << std::endl;
		return;
	}

	FormatterDecorator* formatter_iterator = formatter_decorators;
	while (formatter_iterator != nullptr) {
		std::clog << "\t" << formatter_iterator->get_name() << std::endl;
		formatter_iterator = formatter_iterator->get_next();
	}

	return;
}


IOManager& IOManager::access_singleton() {
	static IOManager the_only_instance;
	return the_only_instance;
}

int IOManager::read_choice() {
	int result = ioenvironment->read_choice();

	std::clog << "Read in the " << result << ". choice" << std::endl;

	return result;
}

void IOManager::format_and_print(std::string message) {
	std::clog << "---format_and_print---" << std::endl;
	std::clog << "Got: " << message << std::endl;
	std::string formatted_message = formatter_decorators->format(message);
	std::clog << "Formatted to: " << formatted_message << std::endl;
	ioenvironment->print_formatted(formatted_message);
	return;
}
