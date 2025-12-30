#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /roll{d*}{}{}...{}
// Output:
// A printout of the d* dice results passed in the list of arguments
// Example:
// /roll{d6}{1}{1}{3}{3}{6}{6}
class DiceFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
private:
	std::string get_nth_line(const char* text, int line);
	const char* get_dice_art(std::string dice_type, int result);
};
