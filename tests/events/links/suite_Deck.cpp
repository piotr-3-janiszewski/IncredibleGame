#include <events/links/Deck.hpp>

#include <iostream>

#define ASSERT_SIZE(correct_size) \
	{ \
		Deck::size_type size = deck.size(); \
		if (size != correct_size) { \
			std::cout << "Bad deck size = " << size << " should be " << correct_size << std::endl; \
			return -1; \
		} \
	}

int main() {
	Deck deck;
	
	ASSERT_SIZE(0);

	deck.replenish();

	ASSERT_SIZE(52);

	for (int i = 0; i < 52; i++) 
		std::cout  << deck.draw() << std::endl;

	ASSERT_SIZE(0);

	deck.replenish();
	deck.draw();
	deck.replenish();

	ASSERT_SIZE(52);

	Deck second_deck;
	second_deck.replenish();

	for (int i = 0; i < 52; i++) {
		if (deck.draw() != second_deck.draw()) {
			std::cout << "new decks not the same" << std::endl;
			return -1;
		}
	}

	deck.replenish();
	second_deck.replenish();

	deck.shuffle();
	second_deck.shuffle();

	int count_same = 0;
	for (int  i = 0; i < 52; i++)
		if (deck.draw() == second_deck.draw())
			count_same++;
	
	if (count_same > 13) {
		std::cout << "Either you are extremely lucky (probability >> 1.6*10^-10) or the deck aren't well shuffled" << std::endl;
		return -1;
	}
}
