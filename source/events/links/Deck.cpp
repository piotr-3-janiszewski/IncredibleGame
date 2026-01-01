#include <events/links/Deck.hpp>

#include <random>
#include <algorithm>
#include <ctime>

std::string Deck::draw() {
	if (cards.empty())
		return "#No cards in deck";
	
	std::string result = cards.back();
	cards.pop_back();

	return result;
}

void Deck::shuffle() {
	static std::mt19937 random_number_generator(static_cast<std::mt19937::result_type>(time(nullptr)));

	std::ranges::shuffle(cards, random_number_generator);
}

void Deck::replenish() {
	cards.clear();

	static const std::vector<std::string> suits = {"S", "C", "D", "H"};
	static const std::vector<std::string> faces = {"2", "3", "4", "5", "6", "7", "8", "9", "0", "J", "Q", "K", "A"};

	for (const std::string& suit : suits)
		for (const std::string& face : faces ) {
			cards.push_back(face + suit);
		}
}

Deck::size_type Deck::size() {
	return cards.size();
}
