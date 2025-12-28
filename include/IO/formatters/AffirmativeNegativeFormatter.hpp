#pragma once

#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /affirmative<Yes, very much so!> ~ printed out in an affirmative style ^^
// /negative<No. I have to decline.> ~ printed out in a negative style >:(
class AffirmativeNegativeFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
};
