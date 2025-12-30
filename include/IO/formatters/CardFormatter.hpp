#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /hand{FS}{FS}{FS}...{FS}
// F ∈ {A, 2, 3, 4, 5, 6, 7, 8, 9, 0, J, Q, K}
// S ∈ {S, s, C, c, D, d, H, h}
// Output:
// A printout of the passed cards
class CardFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
private:
	std::string get_card_art(char card_type, char suit);
	std::string get_nth_line(const char* text, int line);
};
