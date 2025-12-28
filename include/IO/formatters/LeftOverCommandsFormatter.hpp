#pragma once
#include <IO/FormatterDecorator.hpp>

class LeftOverCommandsFormatter :public FormatterDecorator {
public:
	const char* get_name() override;
private:
	std::string in_template_format(std::string message) override;
};
