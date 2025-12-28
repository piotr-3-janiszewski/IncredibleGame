#pragma once
#include <IO/FormatterDecorator.hpp>

#include <vector>

class FormatterDecoratorConfigurator {
public:
	static FormatterDecorator* make_decorator_chain(std::initializer_list<FormatterDecorator*> decorators);
	FormatterDecorator* get_decorator_chain();
};
