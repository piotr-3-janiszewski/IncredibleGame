#include <events/links/Hand.hpp>

#include <sstream>

std::string Hand::str() {
	std::ostringstream result;
	result << "/hand";
	for (std::string card : *this) {
		result << "{" << card << "}";
	}
	result << ".";

	return result.str();
}
