#pragma once

#include <IO/formatters/parser/ParsingFormatterTemplate.hpp>

// Use:
// /box<title>{type}{thickness}{box_position}{width}{border-modifier_1}{vorder-modifier_2}...{border-modifier_n}<line_1><line_2>...<line_n>
// ~type ∈ {normal, double-dash, triple-dash, dots, double, ascii, funky}
// ~thickness ∈ {light, heavy} 					# Doesn't have any effect if you use type {double} 
// ~box_position ∈ {left, center, right, justify}
// ~text_position ∈ {left, center, right} 			# Maybe someday I will implement justify here, but for now, I'm a tad bit too lazy :)
// ~width ∈  {0, 75}						# 0 is just the smallest box that fits. 
// ~border_modifier_n ∈ Modifiers				# modifier is just any command accepting a code argument as the last argument
class BoxFormatter :public ParsingFormatterTemplate {
public:
	const char* get_name() override;
protected:
	std::string execute_command(Command command) override;
	const std::vector<std::string>& get_command_names() override;
};
