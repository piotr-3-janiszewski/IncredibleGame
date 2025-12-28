#pragma once
#include <IO/IOEnvironment.hpp>
#include <IO/formatters/parser/Command.hpp>

#include <vector>

class IOLinuxTerminal :public IOEnvironment {
	std::vector<std::string> escape_codes_history;

	std::string begin_escape(std::vector<int> codes);
	std::string end_escape();
	std::string run_paint_command(Command command);
	std::string paint_text(std::string message);
public:
	void print_formatted(std::string message) override;
	char read_choice() override;
	const char* get_name() override;
	void wait() override;
	std::string::size_type get_width() override;
};
