#pragma once

#include <vector>
#include <string>

class Deck {
	std::vector<std::string> cards;
public:
	using size_type = decltype(cards)::size_type;

	std::string draw();
	void shuffle();
	void replenish();
	size_type size();
};
