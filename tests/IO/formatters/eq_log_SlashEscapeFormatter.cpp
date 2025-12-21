#include <IO/formatters/SlashEscapeFormatter.hpp>
#include <iostream>
#include <sstream>

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		std::cout << "Bad test: incorrect number of arguments" << std::endl;
		return 1;
	}

	std::string input{argv[1]};
	std::string correct_logs{argv[2]};

	std::ostringstream log_stream;
	auto&& old_clog = std::clog.rdbuf();
	std::clog.rdbuf(log_stream.rdbuf());

	SlashEscapeFormatter slashEscapeFormatter{};
	slashEscapeFormatter.format(input);

	std::clog.rdbuf(old_clog);

	std::string logs = log_stream.str();

	if (logs == correct_logs)
		return 0;
	
	std::cout << "Incorrect logs, got:" << std::endl;
	std::cout << logs;
	std::cout << "Expected:" << std::endl;
	std::cout << correct_logs;

	return -1;
}
