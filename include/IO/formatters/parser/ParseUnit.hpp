#pragma once

#include <IO/formatters/parser/ParseUnitType.hpp>
#include <IO/formatters/parser/Command.hpp>

struct ParseUnit {
	ParseUnitType type;
	 
	std::string plaintext_payload;
	Command command_payload;
};
