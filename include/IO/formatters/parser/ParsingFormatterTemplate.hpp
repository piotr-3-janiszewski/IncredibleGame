#include <IO/formatters/parser/CommandParser.hpp>
#include <IO/FormatterDecorator.hpp>

class ParsingFormatterTemplate :public FormatterDecorator {
protected:
	std::string in_template_format(std::string message) override;
	virtual std::string execute_command(Command command) = 0;
	virtual const std::vector<std::string>& get_command_names() = 0;

public:
	virtual ~ParsingFormatterTemplate();
};
