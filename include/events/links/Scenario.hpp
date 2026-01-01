#pragma once

#include <events/GameState.hpp>

#include <IO/IOManager.hpp>

class Scenario {
protected:
	IOManager& io;
public:
	virtual void introduction(GameState& state) = 0;
	virtual void rules_inquiry(GameState& state) = 0;
	virtual void begin_game(GameState& state) = 0;
	virtual void after_round(GameState& state, int round) = 0;
	virtual void won(GameState& state) = 0;
	virtual void lost(GameState& state) = 0;

	//virtual void what_is_it_going_to_be(GameState& state) = 0;
	virtual void small_win(GameState& state) = 0;
	virtual void small_defeat(GameState& state) = 0;

	virtual void bother(GameState& state) = 0;

	Scenario();
	virtual ~Scenario() = default;
};
