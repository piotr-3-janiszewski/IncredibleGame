#pragma once

#include <events/links/Scenario.hpp>

class SadScenario : public Scenario {
public:
	void introduction(GameState& state) override;
	void rules_inquiry(GameState& state) override;
	void begin_game(GameState& state) override;
	void after_round(GameState& state, int round) override;
	void won(GameState& state) override;
	void lost(GameState& state) override;

	void small_win(GameState& state) override;
	void small_defeat(GameState& state) override;

	void bother(GameState& state) override;
};
