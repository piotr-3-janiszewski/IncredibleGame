#include <IO/formatters/parser/Argument.hpp>

std::string Argument::str() const {
	if (type == ArgumentType::OPTION) 
		return "{" + payload + "}";
	else if (type == ArgumentType::CODE)
		return "<" + payload + ">";
	else 
		return payload;
}
