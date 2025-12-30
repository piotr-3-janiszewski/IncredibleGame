#include <IO/FormatterDecoratorConfigurator.hpp>
#include <IO/formatters/BoxFormatter.hpp>
#include <IO/formatters/DiceFormatter.hpp>
#include <IO/formatters/SlashEscapeFormatter.hpp>
#include <IO/formatters/WidenFormatter.hpp>
#include <IO/formatters/LeftOverCommandsFormatter.hpp>
#include <IO/formatters/AffirmativeNegativeFormatter.hpp>
#include <IO/formatters/RainbowFormatter.hpp>
#include <IO/formatters/ChoiceFormatter.hpp>
#include <IO/formatters/DialogueFormatter.hpp>
#include <IO/formatters/CardFormatter.hpp>


FormatterDecorator* FormatterDecoratorConfigurator::make_decorator_chain(std::initializer_list<FormatterDecorator*> decorators) {
	FormatterDecorator* const * result_handle = decorators.begin();
	FormatterDecorator* const * last_added_handle = result_handle;
	FormatterDecorator* const * to_add_handle = decorators.begin() + 1;

	while (to_add_handle < decorators.end()) {
		(*last_added_handle)->set_next(*to_add_handle);

		last_added_handle++;
		to_add_handle++;
	}

	return *result_handle;
}

FormatterDecorator* FormatterDecoratorConfigurator::get_decorator_chain() {
	return make_decorator_chain({
		new ChoiceFormatter(),
		new DialogueFormatter(),
		new AffirmativeNegativeFormatter(),
		new WidenFormatter(),
		new CardFormatter(),
		new DiceFormatter(),
		new RainbowFormatter(),
		new BoxFormatter(),
		new LeftOverCommandsFormatter(),
		new SlashEscapeFormatter(),
	});
}
