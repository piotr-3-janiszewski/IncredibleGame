#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

#include <sstream>

class WidenFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
public:
	virtual ~WidenFormatter();
};
