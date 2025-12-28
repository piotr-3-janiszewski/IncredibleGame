#include <events/GameState.hpp>

#include <sstream>

std::string GameState::str() {
	std::ostringstream result_stream;
	result_stream << "/box<Game results!>";
	result_stream << "<Score: " << score << ">";
	result_stream << ".";
	return result_stream.str();
}
