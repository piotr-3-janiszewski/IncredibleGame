#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /hand{}...{}
// Output:
// A string of cards, one for each argument
// Card format:
// {SR} or just {RJ} {BJ}
// ~S ∈ {D, H, S, C}
// ~R ∈ {2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A}
// RJ ~ red joker
// BJ ~ black joker
class CardFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
};
