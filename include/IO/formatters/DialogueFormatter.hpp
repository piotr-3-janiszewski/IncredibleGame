#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

#include <unordered_map>

// Say:
// /say{name}<line_1><line_2> ... <line_3>.
// If the character doesn't have a specified name the `line_1` is the boxes
// title
//
// Add speaker:
// /add_speaker{name}{box_arguments}{name_specified}{list_of_name_modifiers}{displayed_name}.
// name_specified ∈ {yes, true, 1, name-set, set, no, false, 0, name-unset, unset}
//
// Name:
// /name{name}<display name>.
// /name{name}.
class DialogueFormatter :public ParsingFormatterTemplate {
	struct BubbleProperties {
		std::string box_arguments;
		bool name_set;
		std::string name_begin_modifiers;
		std::string name_end_modifiers;
		std::string name;
	};

	std::unordered_map<std::string, BubbleProperties> dramatis_personae;

protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
public:
	const char* get_name() override;
};
