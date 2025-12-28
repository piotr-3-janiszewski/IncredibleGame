#pragma once

#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /rainbow<Unicorns! Rainbows! And FUNGI!!!> ~ All in rainbowy colors
class RainbowFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
};
