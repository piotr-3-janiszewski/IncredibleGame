#include <IO/FormatterDecorator.hpp>
#include <iostream>

std::string FormatterDecorator::format(std::string message) {
	std::string intermediate_result = in_template_format(message);

	if (get_next() == nullptr)
		return intermediate_result;
	
	std::clog << get_name() << ": " << intermediate_result << std::endl;

	return get_next()->format(intermediate_result);
}

void FormatterDecorator::set_next(FormatterDecorator* next_decorator) {
	this->next_decorator = next_decorator;
	return;
}

FormatterDecorator* FormatterDecorator::get_next() {
	return next_decorator;
}

FormatterDecorator::FormatterDecorator() {}

FormatterDecorator::~FormatterDecorator() {
	delete next_decorator;
}
