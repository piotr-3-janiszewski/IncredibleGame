#pragma once

#include <IO/formatters/parser/ParseUnitType.hpp>

struct ParseUnit {
	ParseUnitType type;
	std::string payload;
}
