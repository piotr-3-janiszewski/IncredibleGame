#pragma once

#include <string>

class FormatterDecorator {
	FormatterDecorator* next_decorator = nullptr;
public:
	std::string format(std::string message);
	void set_next(FormatterDecorator* next_decorator);
	FormatterDecorator* get_next();
	virtual const char* get_name() = 0;
protected:
	virtual std::string in_template_format(std::string message) = 0;
	
public:
	FormatterDecorator();
	virtual ~FormatterDecorator();
	// I don't want to bother with the correct implementation of
	// copying, because I'm never going to use it
	// (If I will, then I can always add it later)
	FormatterDecorator(const FormatterDecorator&) = delete;
	FormatterDecorator& operator=(const FormatterDecorator&) = delete;
};
