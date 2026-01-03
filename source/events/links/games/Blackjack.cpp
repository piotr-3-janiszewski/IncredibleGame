#include <events/links/games/Blackjack.hpp>
#include <events/links/Deck.hpp>
#include <events/links/Hand.hpp>

int Blackjack::hand_value(const Hand& hand) {
	int value = 0;
	for (const std::string& card : hand) {
		if (card[0] == '0')
			value += 10;
		else if (card[0] > '0' && card[0] <= '9')
			value += card[0] - '0';
		else if (card[0] == 'A')
			value += 1;
		else
			value += 10;
	}

	for (const std::string& card : hand) {
		if (card[0] == 'A' && value <= 21 - 9) 	// value - 9 <= 21 is more readible
			value += 9;			// but the silly little compiler
	}						// nags me about the oh so real
							// possibility of an overflow
	return value;					// O _ O
}

std::string Blackjack::get_rules() {
	return
R"block(     /widen<Blackjack>.

The rules of Blackjack are extremely simple (such that
the house can rip off as many patsies as humanely
(or not so humanely) possible.

During the game you and the dealer draw cards. The
side to get closer to 21 in overall value of cards
without going over wins. Exceeding 21 is called
"/paint{italic}<busting>."
The game begins with the player getting delt two cards.
Then the dealer draws two cards and places one of them
face up. Then the player may "/paint{italic}<hit>." any number
of times — that is, draw as many cards as they /rainbow<wish>..
Refusing to "/paint{italic}<hit>. is called "/paint{italic}<staying>.".
Afterwards dealer reveals the other card and
is required to hit for as long as his cards don't add
up to 17 or more. Going over 21 means an automatic
win for the other size. The side that got closer to 21
wins. A "/paint{italic}<push>." occurs whenever
the dealer and the player get the same result. Such
rounds don't count.

Values of all cards:
2-10 = the number listed on the card
Jack, Queen and King = 10 points
Ace = 1 or 10 points, whichever benefits the card
owner more.

The dealer will reshuflle the deck when it gets below
16 cards.

Each round takes 10 sub rounds. You need to win at
least 5 sub rounds to win a round
)block";
}

bool Blackjack::play_round(GameState& state, int round) {
	Deck deck;

	int wins = 0;
	int defeats = 0;

	constexpr int subrounds = 4;

	io.wait();

	while (wins <= subrounds / 2 && defeats <= subrounds / 2) {
		if (deck.size() <= 16) {
			deck.replenish();
			deck.shuffle();

			io.format_and_print("/say{game master}<Deck has been reshuffled>.");
		}

		Hand players_hand;
		Hand dealers_hand;

		io.format_and_print("/say{game master}<Croupier deals cards>.");
		
		io.wait();
		//scenario->what_is_it_going_to_be(state);

		dealers_hand.push_back(deck.draw());
		players_hand.push_back(deck.draw());
		players_hand.push_back(deck.draw());

		bool stay = false;
		do {
			io.format_and_print("Dealer's hand (" + std::to_string(hand_value(dealers_hand)) + "):\n");
			io.format_and_print(dealers_hand.str());
			io.format_and_print("Your hand (" + std::to_string(hand_value(players_hand)) + "):\n");
			io.format_and_print(players_hand.str());

			io.wait();

			if (hand_value(players_hand) < 21) {
				io.format_and_print("/choice<What do you do?>{q}<Hit>{w}<Stay>.");
				char choice = io.read_repeat("qw");

				if (choice == 'q')
					players_hand.push_back(deck.draw());
				else
					stay = true;
			}
			else
				stay = true;

		} while (!stay);

		io.format_and_print("/say{game master}<Croupier deals cards to himself untill he goes over 16...>.");

		while (hand_value(dealers_hand) < 17) {
			dealers_hand.push_back(deck.draw());

			io.format_and_print("Dealer's hand (" + std::to_string(hand_value(dealers_hand)) + "):\n");
			io.format_and_print(dealers_hand.str());
			io.format_and_print("Your hand (" + std::to_string(hand_value(players_hand)) + "):\n");
			io.format_and_print(players_hand.str());

			io.wait();
		}

		const int dealers_hand_value = hand_value(dealers_hand);
		const int players_hand_value = hand_value(players_hand);
		if (players_hand_value > 21) {
			io.format_and_print("/say{game master}<You busted!><You lose this subround!>.");
			scenario->small_defeat(state);
			defeats++;
		}
		else if (dealers_hand_value == players_hand_value) {
			io.format_and_print("/say{game master}</widen<PUSH!>.><Nobody wins this subround.>.");
		}
		else if (dealers_hand_value > 21) {
			io.format_and_print("/say{game master}<Dealer busted!><You win this subround!>.");
			wins++;
			scenario->small_win(state);
		}
		else if (dealers_hand_value < players_hand_value) {
			io.format_and_print("/say{game master}<You have the better hand!><You win this subround!>.");
			wins++;
			scenario->small_win(state);
		}
		else {
			io.format_and_print("/say{game master}<Dealer has the better hand!><You lose this subround!>.");
			defeats++;
			scenario->small_defeat(state);
		}

		io.format_and_print(std::string("/say{game master}<The current score:><") + "/affirmative<Your wins: " + std::to_string(wins) + ">.></negative<Your loses:  " + std::to_string(defeats) + ">.>.");

		io.wait();
	}

	if (wins >= subrounds / 2)
		return true;
	
	return false;
}

const char* Blackjack::get_name() {
	return "BLACKJACK"; 	// TODO: probably it should have the
				// name of the scenario attached
				// to the name of the game by default
				// I'm too lazy to implement that though
				// :|
}

Blackjack::Blackjack(Scenario* scenario) :Game(scenario) {};
