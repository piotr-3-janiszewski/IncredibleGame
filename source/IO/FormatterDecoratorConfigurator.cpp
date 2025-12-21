#include <IO/FormatterDecoratorConfigurator.hpp>
#include <IO/formatters/SlashEscapeFormatter.hpp>

FormatterDecorator* FormatterDecoratorConfigurator::get_decorator_chain() {
	return new SlashEscapeFormatter();
}
