#pragma once

#include <events/links/Game.hpp>
#include <events/links/Hand.hpp>

class Blackjack : public Game {
	int hand_value(const Hand& hand);
public:
	bool play_round(GameState& state, int round) override;
	std::string get_rules() override;
	const char* get_name() override;

	Blackjack(Scenario* scenario);
};
