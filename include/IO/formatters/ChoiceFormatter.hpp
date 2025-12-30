#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

#include <sstream>

// Use:
// /choice<What would you like to do?>{q}<Finish the project>{w}<Sleep>{e}<Not much>.
// Output:
// /say{choice}<What would you like to do?></paint{underline}<[q] Finish the project>.></paint{underline}<[w] Sleep>.></paint{underline}<[e] Not much>.>.
class ChoiceFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
public:
	virtual ~ChoiceFormatter();
};
